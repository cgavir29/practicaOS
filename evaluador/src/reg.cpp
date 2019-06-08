#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "errs.h"
#include "cast.h"
#include "reg.h"

using namespace std;

int handle_reg_exams(int ban_i, char tipo_muestra, int cantidad, Evaluador *pEval)
{
    string ban_pos = to_string(ban_i);
    string be_vacios = "BEV" + ban_pos;
    string be_llenos = "BEL" + ban_pos;
    string be_mutex = "BEM" + ban_pos;

    sem_t *vacios, *llenos, *mutex;

    vacios = sem_open(be_vacios.c_str(), 0);
    llenos = sem_open(be_llenos.c_str(), 0);
    mutex = sem_open(be_mutex.c_str(), 0);

    sem_wait(vacios);
    sem_wait(mutex);

    ostringstream oss;
    oss << ban_i << pEval->ban_en.bandejas[ban_i].id_counter;
    istringstream iss(oss.str());
    int id;
    iss >> id;

    pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].entra].id = id;
    pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].entra].reactivo = tipo_muestra;
    pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].entra].cantidad = cantidad;
    pEval->ban_en.bandejas[ban_i].entra = (pEval->ban_en.bandejas[ban_i].entra + 1) % pEval->hdr.ie;
    pEval->ban_en.bandejas[ban_i].id_counter++;
    pEval->ban_en.bandejas[ban_i].cantidad++;

    sem_post(mutex);
    sem_post(llenos);

    return id;
}

void handle_reg_files(int start, int end, char *argv[], Evaluador *pEval)
{
    // cout << "Handling Files" << endl;

    ifstream infile;
    ofstream outfile;

    int ban_i;
    char tipo_muestra;
    int cantidad;

    for (int i = start; i < end; i++)
    {
        string infile_name = argv[i];
        infile.open(infile_name);

        size_t lastindex = infile_name.find_last_of(".");
        string rawname = infile_name.substr(0, lastindex);

        if (infile.is_open())
        {
            outfile.open(rawname + ".spl");
        }

        while (infile >> ban_i >> tipo_muestra >> cantidad)
        {
            outfile << handle_reg_exams(ban_i, tipo_muestra, cantidad, pEval) << endl;
        }

        infile.close();
        outfile.close();
    }
}

void handle_reg(int size, char *argv[])
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

    if (size == 4)
    {
        int ban_i;
        char tipo_muestra;
        int cantidad;

        cout << "> ";
        cin >> ban_i >> tipo_muestra >> cantidad;

        while (!cin.eof())
        {
            cout << handle_reg_exams(ban_i, tipo_muestra, cantidad, pEval) << endl;
            cout << "> ";
            cin >> ban_i >> tipo_muestra >> cantidad;
        }
    }
    else
    {
        handle_reg_files(4, size, argv, pEval);
    }

    close(fd);
}
