#include <iostream>
#include "errs.h"
#include "stop.h"

using namespace std;


void handle_stop(char* argv[])
{
    char* option = argv[2];
    cout << option << endl;
    char* option_value = argv[3];
    cout << option_value << endl;

}

// void handle_stop_opt_n(string shared_mem) {
//     // Verificar que un segmento de memoria compartida
//     // con el nombre 'shared_mem' existe
    

//     // Do stuff
// }

// void handle_stop(int start, int end, char *argv[]) {
//     for (int i = start; i < end; i++) {
//         string option = argv[i];
//         string shared_mem;

//         if (i + 1 < end) 
//         {
//             shared_mem = argv[i + 1];
//         }

//         if (option == "-n") 
//         {
//             check_value(option, shared_mem);
//             handle_stop_opt_n(shared_mem);
//             i++;
//             continue;
//         } 
//         else 
//         {
//             option_not_supported(option);
//         }
//     }
// }