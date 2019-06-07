#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <semaphore.h>
#include "errs.h"
#include "stop.h"

using namespace std;


void handle_stop(char* argv[])
{
    string option = argv[2];
    
    if (option != "-n")
    {
        option_not_supported(option);
    }

    char* option_value = argv[3];

    // Quitar todos los semaforos
    // sem_unlink()
    
    // Quitar la memoria compartida
    shm_unlink(option_value);

}