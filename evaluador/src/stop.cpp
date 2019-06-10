#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <semaphore.h>
#include "structs.h"
#include "errs.h"
#include "stop.h"

using namespace std;

// ------------------------------------------------------------------------------------------------
void delete_semaphores(Evaluador *pEval)
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

        sem_unlink(be_vacios.c_str());
        sem_unlink(be_llenos.c_str());
        sem_unlink(be_mutex.c_str());
    }

    // Semaforos Bandejas Internas
    // Semaforos Bandeja B
    sem_unlink("BIVB");
    sem_unlink("BILB");
    sem_unlink("BIMB");
    // Semaforos Bandeja D
    sem_unlink("BIVD");
    sem_unlink("BILD");
    sem_unlink("BIMD");
    // Semaforos Bandeja S
    sem_unlink("BIVS");
    sem_unlink("BILS");
    sem_unlink("BIMS");

    // Semaforo Bandeja Salida
    sem_unlink("BSV");
    sem_unlink("BSL");
    sem_unlink("BSM");

    // Semaforos Reactivos
    sem_unlink("RBM");
    sem_unlink("RDM");
    sem_unlink("RSM");
}

// ------------------------------------------------------------------------------------------------
void handle_stop(char *argv[])
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
    if ((dir = mmap(NULL, sizeof(struct Evaluador),
                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << " " << strerror(errno) << endl;
        exit(1);
    }

    struct Evaluador *pEval = (struct Evaluador *)dir;

    delete_semaphores(pEval);
    shm_unlink(option_value);
}