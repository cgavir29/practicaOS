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
#include "structs.h"
#include "cast.h"
#include "init.h"
#include "reg.h"
#include "ctrl.h"
#include "rep.h"
#include "stop.h"

using namespace std;

// -----------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // cout << "Size Header = " << sizeof(struct Header) << endl;
        // cout << "Size Examen = " << sizeof(struct Examen) << endl;
        // cout << "Size BandejaEntrada = " << sizeof(struct BandejaEntrada) << endl;
        // cout << "Size BandejaEntradaEntry = " << sizeof(struct BandejaEntradaEntry) << endl;
        // cout << "Size Evaluador = " << sizeof(struct Evaluador) << endl;

        not_enough_args();
    }
    else
    {
        const string &command = argv[1];

        if (command == "init")
        {
            struct Header auxHdr;
            handle_init(2, argc, argv, auxHdr);

            // string pepito = string(auxHdr.n);
            // cout << pepito << endl;
            int fd = shm_open(auxHdr.n, O_RDWR | O_CREAT | O_EXCL, 0660);
            if (ftruncate(fd, sizeof(struct Evaluador)) != 0)
            {
                cerr << "Error creando la memoria compartida: "
                     << strerror(errno) << endl;
                exit(1);
            }

            // size of evaluador o que?
            void *dir = mmap(NULL, sizeof(struct Evaluador), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            struct Evaluador *pEval = (struct Evaluador *) dir;

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

            // i = # Bandejas de Entrada
            string ban_pos;
            string be_vacios;
            string be_llenos;
            string be_mutex;

            for (int k = 0; k < pEval->hdr.i; k++) {
                string ban_pos = to_string(k);
                be_vacios = "BEV" + ban_pos;
                be_llenos = "BEL" + ban_pos;
                be_mutex = "BEM" + ban_pos;
                // cout << be_vacios << endl;
                // cout << be_llenos << endl;
                // cout << be_mutex << endl;
                sem_open(be_vacios.c_str(), O_CREAT | O_EXCL, 0660, pEval->hdr.ie);
                sem_open(be_llenos.c_str(), O_CREAT | O_EXCL, 0660, 0);
                sem_open(be_mutex.c_str(), O_CREAT | O_EXCL, 0660, 1);
            }

        }
        else if (command == "reg")
        {
            handle_reg(argc, argv);
        }
        else if (command == "ctrl")
        {
            handle_ctrl(argv);
        }
        else if (command == "rep")
        {
            handle_rep(argv);
        }
        else if (command == "stop")
        {
            handle_stop(argv);
        }
        else
        {
            command_not_supported(command);
        }

        // cout << headr.i << headr.ie << headr.n << endl;
    }

    return 0;
}
