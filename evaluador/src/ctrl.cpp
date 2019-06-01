#include "ctrl.h"

using namespace std;


void handle_ctrl_opt_s(string shared_mem) {
    // Verificar que se encuentre la memoria compartida sino atrapar excepcion y salir

    // Modo Interactivo
    string sub_command;
    cin << "Enter a sub-command" << endl;
    
}

void handle_ctrl(int start, int end, char *argv[]) {
    for (int i = start; i < end - 1, i++) {
        string option = argv[i];
        string shared_mem = argv[i + 1];

        if (option == "-s") {
            handle_ctrl_opt_s(shared_mem);
        } else {
            cout << "Option '" << option << "' not supported" << endl;
            exit(0); 
        }
    } 
}
