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
#include "rep.h"

using namespace std;

void handle_rep_opt_m(struct Evaluador *pEval)
{
    sem_t *vacios, *llenos, *mutex;

    vacios = sem_open("BSV", 0);
    llenos = sem_open("BSL", 0);
    mutex = sem_open("BSM", 0);

    sem_wait(llenos);
    sem_wait(mutex);

    int id = pEval->ban_out.buffer[pEval->ban_out.sale].id;
    int i = pEval->ban_out.buffer[pEval->ban_out.sale].ban;
    int cant = pEval->ban_out.buffer[pEval->ban_out.sale].cant_react;
    char k = pEval->ban_out.buffer[pEval->ban_out.sale].tipo;
    char r = pEval->ban_out.buffer[pEval->ban_out.sale].informe;

    pEval->ban_out.buffer[pEval->ban_out.sale].cant_react = 0;
    pEval->ban_out.sale = (pEval->ban_out.sale + 1) % pEval->hdr.oe;
    pEval->ban_out.cantidad--;

    sem_post(mutex);
    sem_post(vacios);

    cout << id << " " << i << " " << k << " " << r;

    if (r == '?')
    {
        handle_reg_exams(i, k, cant, pEval);
    }
}

void handle_rep_opt_i(struct Evaluador *pEval)
{
}

void handle_rep(char *argv[])
{
    string option = argv[2];
    char *option_value = argv[3];
    string extra_option = argv[4];
    int extra_option_value = string_cast_pos(argv[5]);

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

    if (extra_option == "-i")
    {
        handle_rep_opt_i(pEval);
    }
    else if (extra_option == "-m")
    {
        cout << "[";
        for (int i = 0; i < extra_option_value; i++)
        {
            handle_rep_opt_m(pEval);
            if (i != extra_option_value - 1)
            {
                cout << endl;
            }
        }
        cout << "]" << endl;
    }
    else
    {
        option_not_supported(extra_option);
    }
}