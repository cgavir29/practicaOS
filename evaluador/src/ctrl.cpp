#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "errs.h"
#include "cast.h"
#include "ctrl.h"

using namespace std;

void handle_ctrl_sub_update_opt_s(const string &val, struct Evaluador *pEval)
{
    int num = string_cast_pos(val);
    sem_t *mutex = sem_open("RSM", 0);

    sem_wait(mutex);
    pEval->hdr.s = pEval->hdr.s + num;
    sem_post(mutex);
}

void handle_ctrl_sub_update_opt_d(const string &val, struct Evaluador *pEval)
{
    int num = string_cast_pos(val);
    sem_t *mutex = sem_open("RDM", 0);

    sem_wait(mutex);
    pEval->hdr.d = pEval->hdr.d + num;
    sem_post(mutex);
}

void handle_ctrl_sub_update_opt_b(const string &val, struct Evaluador *pEval)
{
    int num = string_cast_pos(val);
    sem_t *mutex = sem_open("RBM", 0);

    sem_wait(mutex);
    pEval->hdr.b = pEval->hdr.b + num;
    sem_post(mutex);
}

void handle_ctrl_sub_update(const string &sub_command_info, struct Evaluador *pEval)
{
    string option;
    string val;

    if (sub_command_info.find(" ") != string::npos)
    {
        option = sub_command_info.substr(0, sub_command_info.find(" "));
        val = sub_command_info.substr(option.length() + 1);
    }

    if (option == "B")
    {
        handle_ctrl_sub_update_opt_b(val, pEval);
    }
    else if (option == "D")
    {
        handle_ctrl_sub_update_opt_d(val, pEval);
    }
    else if (option == "S")
    {
        handle_ctrl_sub_update_opt_s(val, pEval);
    }
    else
    {
        option_not_supported(option);
    }
}

void handle_ctrl_sub_list_opt_reac(struct Evaluador *pEval)
{
    cout << "Reactives: " << endl;
    cout << "[";
    cout << "Blood = " << pEval->hdr.b << endl;
    cout << "Detritus = " << pEval->hdr.d << endl;
    cout << "Skin = " << pEval->hdr.s;
    cout << "]" << endl;
}

void handle_ctrl_sub_list_opt_repo(struct Evaluador *pEval)
{
    cout << "Reported:" << endl;
    cout << "[";

    struct Examen current_exam;
    for (int i = 0; i < pEval->hdr.oe; i++)
    {
        current_exam = pEval->ban_out.buffer[i];
        if (current_exam.cantidad != 0)
        {
            cout << current_exam.id << " " << current_exam.ban << " " << current_exam.tipo
                 << " " << current_exam.informe << endl;
        }
    }

    cout << "]" << endl;
}

void handle_ctrl_sub_list_opt_wait(struct Evaluador *pEval)
{
    cout << "Waiting:" << endl;
    cout << "[";

    struct Examen current_exam;
    for (int i = 0; i < pEval->hdr.i; i++)
    {
        for (int j = 0; j < pEval->hdr.ie; j++)
        {
            current_exam = pEval->ban_en.bandejas[i].buffer[j];
            if (current_exam.cantidad != 0)
            {
                cout << current_exam.id << " " << current_exam.ban << " " << current_exam.tipo
                     << " " << current_exam.cantidad << endl;
            }
        }
    }

    cout << "]" << endl;
}

void handle_ctrl_sub_list_opt_proc(struct Evaluador *pEval)
{
    cout << "Processing:" << endl;
    cout << "[";

    struct Examen current_exam;
    for (int i = 0; i < NUM_TIPO_REACTS; i++)
    {
        for (int j = 0; j < pEval->hdr.q; j++)
        {
            current_exam = pEval->ban_in.bandejas[i].buffer[j];
            if (current_exam.cantidad != 0)
            {
                cout << current_exam.id << " " << current_exam.ban << " " << current_exam.tipo
                     << " " << current_exam.cantidad << " " << current_exam.tiempo << endl;
            }
        }
    }

    cout << "]" << endl;
}

void handle_ctrl_sub_list_opt_all(struct Evaluador *pEval)
{
    handle_ctrl_sub_list_opt_proc(pEval);
    handle_ctrl_sub_list_opt_wait(pEval);
    handle_ctrl_sub_list_opt_repo(pEval);
    handle_ctrl_sub_list_opt_reac(pEval);
}

void handle_ctrl_sub_list(const string &option, struct Evaluador *pEval)
{
    if (option == "processing")
    {
        handle_ctrl_sub_list_opt_proc(pEval);
    }
    else if (option == "waiting")
    {
        handle_ctrl_sub_list_opt_wait(pEval);
    }
    else if (option == "reported")
    {
        handle_ctrl_sub_list_opt_repo(pEval);
    }
    else if (option == "reactive")
    {
        handle_ctrl_sub_list_opt_reac(pEval);
    }
    else if (option == "all")
    {
        handle_ctrl_sub_list_opt_all(pEval);
    }
    else
    {
        option_not_supported(option);
    }
}

void handle_ctrl(char *argv[])
{
    string option = argv[2];
    char *option_value = argv[3];

    if (option != "-n")
    {
        option_not_supported(option);
    }

    int fd = shm_open(option_value, O_RDWR, 0660);
    if (fd < 0)
    {
        cerr << "Couldn't find shared memory segment '" << option_value
             << "': " << strerror(errno) << endl;
        exit(1);
    }

    void *dir;
    if ((dir = mmap(NULL, sizeof(struct Evaluador), PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << strerror(errno) << endl;
        exit(1);
    }

    struct Evaluador *pEval = (struct Evaluador *)dir;

    string input;
    string sub_command;
    string sub_command_info;

    cout << "> ";
    getline(cin, input);

    while (!cin.eof())
    {
        if (input.find(" ") != string::npos)
        {
            sub_command = input.substr(0, input.find(" "));
            sub_command_info = input.substr(sub_command.length() + 1);
        }

        if (sub_command == "list")
        {
            // check_value(sub_command, sub_command_info);
            handle_ctrl_sub_list(sub_command_info, pEval);
        }
        else if (sub_command == "update")
        {
            // check_value(sub_command, sub_command_info);
            handle_ctrl_sub_update(sub_command_info, pEval);
        }

        sub_command.clear();
        sub_command_info.clear();

        cout << "> ";
        getline(cin, input);
    }

    close(fd);
}
