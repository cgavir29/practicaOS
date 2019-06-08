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
#include "structs.h"
#include "errs.h"
#include "cast.h"
#include "rep.h"

using namespace std;

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
        // Encuentra examenes hasta i <integer> segundos?
    }
    else if (extra_option == "-m")
    {
        // Encuentra m <integer> numero de examenes?
    }
    else
    {
        option_not_supported(extra_option);
    }

    int id = 5;                   // Identificador
    int i = 3;                    // 'i' Cola de entrada
    char k[] = "Tipo Muestra";    // Tipo de muestra
    char r[] = "Informe Muestra"; // Informe final de la muestra
    cout << "[" << id << " " << i << " " << k << " " << r << "]" << endl;
}