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
#include "reg.h"
#include "ctrl.h"
#include "rep.h"
#include "stop.h"

using namespace std;


// -----------------------------------------------------------------
int main(int argc, char* argv[])
{
    

    if (argc < 2)
    {
        not_enough_args();
    }
    else
    {
        
        Header headr;
        const string& command = argv[1];

        if (command == "init")
        {
            handle_init(2, argc, argv, headr);

            int fd = shm_open(headr.n , O_RDWR | O_CREAT | O_EXCL, 0660);
            // if (ftruncate(fd, sizeof(struct Buffer)) != 0) {
            //     cerr << "Error creando la memoria compartida: "
	        //         << errno << strerror(errno) << endl;
            //     exit(1);
            // }
            void *dir = mmap(NULL, sizeof(struct Header), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

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
