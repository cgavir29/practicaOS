#include "errs.h"
#include "stop.h"

using namespace std;

void handle_stop_opt_n(string shared_mem) {
    // Verificar que un segmento de memoria compartida
    // con el nombre 'shared_mem' existe
    

    // Do stuff
}

void handle_stop(int start, int end, char *argv[]) {
    for (int i = start; i < end - 1; i++) {
        string option = argv[i];
        string shared_mem = argv[i + 1];

        if (option == "-n") {
            handle_stop_opt_n(shared_mem);
            i++;
            continue;
        } else {
            option_not_supported(option);
        }
    }
}