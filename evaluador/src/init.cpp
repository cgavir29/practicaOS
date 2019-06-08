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
#include "errs.h"
#include "cast.h"
#include "init.h"

using namespace std;

void initialize_evaluador(Evaluador *pEval, Header &auxHdr)
{
    pEval->hdr.i = auxHdr.i;
    pEval->hdr.ie = auxHdr.ie;
    pEval->hdr.oe = auxHdr.oe;
    for (int i = 0; i < 40; i++)
    {
        pEval->hdr.n[i] = auxHdr.n[i];
    }
    pEval->hdr.b = auxHdr.b;
    pEval->hdr.d = auxHdr.d;
    pEval->hdr.s = auxHdr.s;
    pEval->hdr.q = auxHdr.q;
}

void create_semaphores(Evaluador *pEval)
{
    // Semaforos Bandejas Entrada
    string ban_pos;
    string be_vacios;
    string be_llenos;
    string be_mutex;

    for (int k = 0; k < pEval->hdr.i; k++)
    {
        ban_pos = to_string(k);
        be_vacios = "BEV" + ban_pos;
        be_llenos = "BEL" + ban_pos;
        be_mutex = "BEM" + ban_pos;
        sem_open(be_vacios.c_str(), O_CREAT | O_EXCL, 0660, pEval->hdr.ie);
        sem_open(be_llenos.c_str(), O_CREAT | O_EXCL, 0660, 0);
        sem_open(be_mutex.c_str(), O_CREAT | O_EXCL, 0660, 1);
    }

    // Semaforos Bandejas Internas
    // Semaforos Reactivo B
    sem_open("BIVB", O_CREAT | O_EXCL, 0660, pEval->hdr.q);
    sem_open("BILB", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BIMB", O_CREAT | O_EXCL, 0660, 1);

    // Semaforos Reactivo D
    sem_open("BIVD", O_CREAT | O_EXCL, 0660, pEval->hdr.q);
    sem_open("BILD", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BIMD", O_CREAT | O_EXCL, 0660, 1);

    // Semaforos Reactivo S
    sem_open("BIVS", O_CREAT | O_EXCL, 0660, pEval->hdr.q);
    sem_open("BILS", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BIMS", O_CREAT | O_EXCL, 0660, 1);


    // Semaforo Bandeja Salida
    sem_open("BSV", O_CREAT | O_EXCL, 0660, pEval->hdr.oe);
    sem_open("BSL", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BSM", O_CREAT | O_EXCL, 0660, 1);
}

Evaluador *create_shared_mem(Header &auxHdr)
{
    int fd = shm_open("evaluador", O_RDWR | O_CREAT | O_EXCL, 0660);
    if (ftruncate(fd, sizeof(struct Evaluador)) != 0)
    {
        cerr << "Error creando la memoria compartida: "
             << errno << " " << strerror(errno) << endl;
        exit(1);
    }

    void *dir;
    if ((dir = mmap(NULL, sizeof(struct Evaluador),
                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << " " << strerror(errno) << endl;
        exit(1);
    }

    struct Evaluador *pEval = (struct Evaluador *)dir;

    initialize_evaluador(pEval, auxHdr);
    create_semaphores(pEval);

    close(fd);

    return pEval;
}

Evaluador *handle_init(int start, int end, char *argv[])
{
    struct Header auxHdr;

    bool i = false, ie = false, oe = false, n = false;
    bool b = false, d = false, s = false, q = false;

    string option;
    string val;

    for (int k = start; k < end; k++)
    {
        option = argv[k];
        if (k + 1 < end)
        {
            val = argv[k + 1];
        }

        if (option == "-i")
        {
            check_value(option, val);
            auxHdr.i = string_cast_pos(val);
            i = true;
            k++;
            continue;
        }
        else if (option == "-ie")
        {
            check_value(option, val);
            auxHdr.ie = string_cast_pos(val);
            ie = true;
            k++;
            continue;
        }
        else if (option == "-oe")
        {
            check_value(option, val);
            auxHdr.oe = string_cast_pos(val);
            i = true;
            k++;
            continue;
        }
        else if (option == "-n")
        {
            for (u_long i = 0; i < val.length(); i++)
            {
                auxHdr.n[i] = val[i];
            }
            n = true;
            k++;
            continue;
        }
        else if (option == "-b")
        {
            check_value(option, val);
            auxHdr.b = string_cast_pos(val);
            b = true;
            k++;
            continue;
        }
        else if (option == "-d")
        {
            check_value(option, val);
            auxHdr.d = string_cast_pos(val);
            d = true;
            k++;
            continue;
        }
        else if (option == "-s")
        {
            check_value(option, val);
            auxHdr.s = string_cast_pos(val);
            s = true;
            k++;
            continue;
        }
        else if (option == "-q")
        {
            check_value(option, val);
            auxHdr.q = string_cast_pos(val);
            q = true;
            k++;
            continue;
        }
        else
        {
            option_not_supported(option);
        }
    }

    // Defaults, no seria mejor ponerlos en el struct?
    if (!i)
    {
        auxHdr.i = 5;
    }

    if (!ie)
    {
        auxHdr.ie = 6;
    }

    if (!oe)
    {
        auxHdr.oe = 10;
    }

    if (!n)
    {
        string val = "evaluador";
        for (u_long i = 0; i < val.length(); i++)
        {
            auxHdr.n[i] = val[i];
        }
    }

    if (!b)
    {
        auxHdr.b = 100;
    }

    if (!d)
    {
        auxHdr.d = 100;
    }

    if (!s)
    {
        auxHdr.s = 100;
    }

    if (!q)
    {
        auxHdr.q = 6;
    }

    return create_shared_mem(auxHdr);
}