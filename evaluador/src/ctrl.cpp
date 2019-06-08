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

void handle_ctrl_sub_update_opt_s(const string &val)
{
    int num = string_cast_pos(val);
    // cout << "Num = " << num << endl;
}

void handle_ctrl_sub_update_opt_d(const string &val)
{
    int num = string_cast_pos(val);
    // cout << "Num = " << num << endl;
}

void handle_ctrl_sub_update_opt_b(const string &val)
{
    int num = string_cast_pos(val);
    // cout << "Num = " << num << endl;
}

void handle_ctrl_sub_update(const string &sub_command_info)
{
    string option;
    string val;

    if (sub_command_info.find(" ") != string::npos)
    {
        option = sub_command_info.substr(0, sub_command_info.find(" "));
        val = sub_command_info.substr(option.length() + 1);
    }

    cout << "Option = " << option << endl;
    cout << "Value = " << val << endl;

    if (option == "B")
    {
        handle_ctrl_sub_update_opt_b(val);
    }
    else if (option == "D")
    {
        handle_ctrl_sub_update_opt_d(val);
    }
    else if (option == "S")
    {
        handle_ctrl_sub_update_opt_s(val);
    }
    else
    {
        // option_not_supported(option);
    }
}

void handle_ctrl_sub_list_opt_reac()
{
    // No esta en presentacion
}

void handle_ctrl_sub_list_opt_repo()
{
    int id;
    int i;
    char *k;
    char *r;

    cout << "Reported:" << endl;
    cout << "[" << id << " " << i << " " << k << " " << r << "]" << endl;
}

void handle_ctrl_sub_list_opt_wait(struct Evaluador *pEval)
{
    cout << "Waiting:" << endl;
    cout << "[";

    struct Examen current_exam;
    for (size_t i = 0; i < pEval->hdr.i; i++)
    {
        for (size_t j = 0; j < pEval->hdr.ie; j++)
        {
            current_exam = pEval->ban_en.bandejas[i].buffer[j];
            if (current_exam.cantidad != 0)
            {
                cout << current_exam.id << " " << i << " " << current_exam.reactivo << " " << current_exam.cantidad << endl;
            }
        }
    }
    cout << "]" << endl;
}

void handle_ctrl_sub_list_opt_proc()
{
    int id;
    int i;
    char *k;
    int q;
    int p;

    cout << "Processing:" << endl;
    cout << "[" << id << " " << i << " " << k << " " << q << " " << p << "]" << endl;
}

void handle_ctrl_sub_list_opt_all()
{
    // No esta en la presentacion, supongo que todos...
    handle_ctrl_sub_list_opt_proc();
    // handle_ctrl_sub_list_opt_wait();
    handle_ctrl_sub_list_opt_repo();
    handle_ctrl_sub_list_opt_reac();
}

void handle_ctrl_sub_list(const string &option, struct Evaluador *pEval)
{
    if (option == "processing")
    {
        handle_ctrl_sub_list_opt_proc();
    }
    else if (option == "waiting")
    {
        handle_ctrl_sub_list_opt_wait(pEval);
    }
    else if (option == "reported")
    {
        handle_ctrl_sub_list_opt_repo();
    }
    else if (option == "reactive")
    {
        handle_ctrl_sub_list_opt_reac();
    }
    else if (option == "all")
    {
        handle_ctrl_sub_list_opt_all();
    }
    else
    {
        option_not_supported(option);
    }
}

void handle_ctrl(char *argv[])
{
    char *option = argv[2];
    char *option_value = argv[3];

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
            handle_ctrl_sub_update(sub_command_info);
        }

        sub_command.clear();
        sub_command_info.clear();

        cout << "> ";
        getline(cin, input);
    }

    close(fd);
}
