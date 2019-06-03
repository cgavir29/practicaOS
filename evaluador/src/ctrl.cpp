#include <iostream>
#include "errs.h"
#include "cast.h"
#include "ctrl.h"

using namespace std;


void handle_ctrl_sub_list_opt_all() {

}

void handle_ctrl_sub_list_opt_reac() {

}

void handle_ctrl_sub_list_opt_repo() {

}

void handle_ctrl_sub_list_opt_wait() {

}

void handle_ctrl_sub_list_opt_proc() {

}

void handle_ctrl_sub_list(string option) {
    if (option == "processing") {
        handle_ctrl_sub_list_opt_proc();
    } else if (option == "waiting")
    {
        handle_ctrl_sub_list_opt_wait();
    } else if (option == "reported")
    {
        handle_ctrl_sub_list_opt_repo();
    } else if (option == "reactive")
    {
        handle_ctrl_sub_list_opt_reac();
    } else if (option == "all")
    {
        handle_ctrl_sub_list_opt_all();
    } else {
        option_not_supported(option);
    }    
}

void handle_ctrl_opt_n(string shared_mem) {
    // Verificar que se encuentre la memoria compartida sino atrapar excepcion y salir

    // Modo Interactivo
    string input;
    string sub_command;
    string sub_command_info;
    while (input != "EOF") {

        // cout << "Enter a sub-command" << endl;
        cout << "> ";
        getline(cin, input);
        // trim imput
        sub_command = input.substr(0, input.find(" "));
        sub_command_info = input.substr(sub_command.length());
        // trim subcommand
        // sub_command_info.replace(sub_command_info.begin(), sub_command_info.end(), )
        if (input.find(" ") != string::npos) {
            // sub_command = input.substr(0, input.find(" "));
            sub_command_info = input.substr(sub_command.length() + 1);
        }
        // cout << "input = " << input << endl;
        // cout << "sub_command = " << sub_command << endl;
        // cout << "sub_command_info = " << sub_com_info << endl;
        // cout << "info = " << sub_com_info << endl;

        if (sub_command == "list")
        {
            check_value(sub_command, sub_command_info);
            handle_ctrl_sub_list(sub_command_info);
        } else if (sub_command == "update")
        {
            // handle_ctrl_sub_update("...");
        } else
        {
            // Hacer un error interactivo que no salga del programa
            command_not_supported(sub_command);
        }
        
    }

    // Hacer split para saber si es list o update
    // con base en ello mandar los argumentos
    // al respectivo commando
    
}



void handle_ctrl(int start, int end, char *argv[]) {
    for (int i = start; i < end; i++) {
        string option = argv[i];
        string shared_mem;

        if (i + 1 < end) {
            shared_mem = argv[i + 1];
        }

        if (option == "-n") {
            check_value(option, shared_mem);
            handle_ctrl_opt_n(shared_mem);
            i++;
            continue;
        } else {
            option_not_supported(option);
        }
    } 
}
