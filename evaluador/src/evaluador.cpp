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
        // cout << "Size Evaluador = " << sizeof(struct Evaluador) << endl;

        not_enough_args();
    }
    else
    {
        const string &command = argv[1];

        if (command == "init")
        {
            struct Evaluador *pEval = handle_init(2, argc, argv);

            int fd = shm_open(pEval->hdr.n, O_RDWR, 0660);
            while (fd != -1)
            {
                fd = shm_open(pEval->hdr.n, O_RDWR, 0660);
                close(fd);
            }

            exit(0);
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
    }

    return 0;
}
