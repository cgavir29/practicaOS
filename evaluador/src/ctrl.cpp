#include <iostream>
#include "errs.h"
#include "cast.h"
#include "ctrl.h"

using namespace std;


void handle_ctrl_sub_update_opt_s(const string& val) {
    int num = string_cast_pos(val);
    // cout << "Num = " << num << endl;

}

void handle_ctrl_sub_update_opt_d(const string& val) {
    int num = string_cast_pos(val);
    // cout << "Num = " << num << endl;

}

void handle_ctrl_sub_update_opt_b(const string& val) {
    int num = string_cast_pos(val);
    // cout << "Num = " << num << endl;

}

void handle_ctrl_sub_update(const string& sub_command_info) 
{
    string option;
    string val;

    if (sub_command_info.find(" ") != string::npos)
    {
        option = sub_command_info.substr(0, sub_command_info.find(" "));
        val = sub_command_info.substr(option.length() + 1);
    }

    cout << "Option = " << option << endl;
    cout << "Value = " << val << endl;

    if (option == "B")
    {
        handle_ctrl_sub_update_opt_b(val);
    } 
    else if (option == "D")
    {
        handle_ctrl_sub_update_opt_d(val);
    } 
    else if (option == "S")
    {
        handle_ctrl_sub_update_opt_s(val);
    } 
    else 
    {
        option_not_supported(option);
    }
}

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

void handle_ctrl_sub_list(const string& option) {
    if (option == "processing") {
        handle_ctrl_sub_list_opt_proc();
    } 
    else if (option == "waiting")
    {
        handle_ctrl_sub_list_opt_wait();
    } 
    else if (option == "reported")
    {
        handle_ctrl_sub_list_opt_repo();
    } 
    else if (option == "reactive")
    {
        handle_ctrl_sub_list_opt_reac();
    } 
    else if (option == "all")
    {
        handle_ctrl_sub_list_opt_all();
    } 
    else {
        option_not_supported(option);
    }    
}




void handle_ctrl(char* argv[]) {
    char* option = argv[2];
    char* option_value = argv[3];

    string input;
    string sub_command;
    string sub_command_info;

    cout << "> ";
    getline(cin, input);
    
    while (input != "EOF") {
        if (input.find(" ") != string::npos)
        {
            sub_command = input.substr(0, input.find(" "));
            sub_command_info = input.substr(sub_command.length() + 1);
        }
        // cout << "Input = " << input << endl;
        // cout << "Sub_command = " << sub_command << endl;
        // cout << "Sub_command_info = " << sub_command_info << endl;

        if (sub_command == "list")
        {
            // check_value(sub_command, sub_command_info);
            handle_ctrl_sub_list(sub_command_info);
        } 
        else if (sub_command == "update")
        {
            // check_value(sub_command, sub_command_info);
            handle_ctrl_sub_update(sub_command_info);
        } 
        else
        {
            sub_command.clear();
            sub_command_info.clear();
        }

        cout << "> ";
        getline(cin, input);
        
    }

}

// void handle_ctrl_opt_n(string shared_mem) {
//     // Verificar que se encuentre la memoria compartida sino atrapar excepcion y salir

//     // Modo Interactivo
//     string input;
//     string sub_command;
//     string sub_command_info;
//     cout << "> ";
//     getline(cin, input);
    
//     while (input != "EOF") {
//         if (input.find(" ") != string::npos)
//         {
//             sub_command = input.substr(0, input.find(" "));
//             sub_command_info = input.substr(sub_command.length() + 1);
//         }
//         // cout << "Input = " << input << endl;
//         // cout << "Sub_command = " << sub_command << endl;
//         // cout << "Sub_command_info = " << sub_command_info << endl;

//         if (sub_command == "list")
//         {
//             check_value(sub_command, sub_command_info);
//             handle_ctrl_sub_list(sub_command_info);
//         } 
//         else if (sub_command == "update")
//         {
//             check_value(sub_command, sub_command_info);
//             handle_ctrl_sub_update(sub_command_info);
//         } 
//         else
//         {
//             // Hacer un error interactivo que no salga del programa
//             command_not_supported(sub_command);
//         }

//         cout << "> ";
//         getline(cin, input);
        
//     }

// }

// void handle_ctrl(int start, int end, char *argv[]) {
//     string option;
//     string shared_mem;
//     for (int i = start; i < end; i++) {
//         option = argv[i];

//         if (i + 1 < end) 
//         {
//             shared_mem = argv[i + 1];
//         }

//         if (option == "-n") 
//         {
//             cout << "mmm" << endl;
//             check_value(option, shared_mem);
//             handle_ctrl_opt_n(shared_mem);
//             i++;
//             continue;
//         } 
//         else 
//         {
//             option_not_supported(option);
//         }
//     } 
// }




