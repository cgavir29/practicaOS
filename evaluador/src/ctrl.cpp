#include <iostream>
#include "errs.h"
#include "cast.h"
#include "ctrl.h"

using namespace std;


void handle_ctrl_opt_n(string shared_mem) {
    // Verificar que se encuentre la memoria compartida sino atrapar excepcion y salir

    // Modo Interactivo
    string sub_command;
    cout << "Enter a sub-command" << endl;
    getline(cin, sub_command);
    // cin >> sub_command;
    cout << sub_command << endl;

    // Hacer split para saber si es list o update
    // con base en ello mandar los argumentos
    // al respectivo commando
    
}

void handle_ctrl_list(string option) {
    if (option == "processing") {

    } else if (option == "waiting")
    {
        /* code */
    } else if (option == "reported")
    {
        /* code */
    } else if (option == "reactive")
    {
        /* code */
    } else if (option == "all")
    {
        /* code */
    } else {
        option_not_supported(option);
    }
    
    
    
    
}

void handle_ctrl(int start, int end, char *argv[]) {
    for (int i = start; i < end - 1; i++) {
        string option = argv[i];
        string shared_mem = argv[i + 1];

        if (option == "-n") {
            handle_ctrl_opt_n(shared_mem);
            i++;
            continue;
        } else {
            option_not_supported(option);
        }
    } 
}
