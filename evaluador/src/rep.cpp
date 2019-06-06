#include <iostream>
#include <string>
#include "errs.h"
#include "cast.h"
#include "rep.h"

using namespace std;


// void handle_rep_opt_n(string option_info) { // que reciba el string del shared mem mas la otra opcion 
//     // string shared_mem;
//     cout << option_info << endl;

    
//     string option;
//     string val;

//     // option = sub_command_info.substr(sub_command_info.find(" "));
//     // val = sub_command_info.substr(option.length() + 1);
// }

// void handle_rep(int start, int end, char *argv[]) {
//     string option;
//     string option_info;
    
//     for (int i = start; i < end; i++) // hacerlo llegar hasta antes del {-i | -m}
//     {
//         option = argv[i];

//         if (i + 1 < end) 
//         {
//             option_info = argv[i + 1];
//         }

//         if (option == "-n")
//         {
//             check_value(option, option_info);
//             handle_rep_opt_n(option_info);
//             i++;
//             continue;
//         } else
//         {
//             option_not_supported(option);
//         }
        
        
//     }
    
// }



void handle_rep(char* argv[]) {
    string option = argv[2];
    // cout << option << endl;
    string option_value = argv[3];
    // cout << option_value << endl;
    string extra_option = argv[4];
    // cout << extra_option << endl;
    int extra_option_value = string_cast_pos(argv[5]);
    // cout << extra_option_value << endl;

    if (option != "-n") 
    {
        option_not_supported(option);
    }

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


    int id = 5; // Identificador
    int i = 3; // 'i' Cola de entrada
    char k[] = "Tipo Muestra"; // Tipo de muestra
    char r[] = "Informe Muestra"; // Informe final de la muestra
    cout << "[" << id << " " << i << " " << k << " " << r << "]" << endl;
}