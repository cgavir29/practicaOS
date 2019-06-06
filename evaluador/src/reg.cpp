#include <iostream>
#include "errs.h"
#include "cast.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include "reg.h"

using namespace std;

// void handle_reg_opt_n(string shared_mem)
// {

// }

// void handle_reg(int start, int end, char *argv[]) 
// {
//     for (int i = start; i < end; i++)
//     {
//         string option = argv[i];
//         string shared_mem;

//         if (i + 1 < end) 
//         {
//             shared_mem = argv[i + 1];
//         }

//         if (option == "-n")
//         {
//             check_value(option, shared_mem);
//             handle_reg_opt_n(shared_mem);
//             i++;
//             continue;
//         } 
//         else
//         {
//             option_not_supported(option);
//         }
        
        
//     }
// }

// Mira si el fichero existe, sacado de https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
// bool exists_test3 (const string& name) {
//   struct stat buffer;   
//   return (stat (name.c_str(), &buffer) == 0); 
// }

void handle_reg_files(int start, int end, char* argv[])
{
    cout << "Handling Files" << endl;
    for (int i = start; i < end; i++)
    {
        // cout << exists_test3(argv[i]) << endl;
        cout << argv[i] << endl;
    }
}

void handle_reg(int size, char *argv[]) 
{
    char* option = argv[2];
    char* option_value = argv[3];

    if (size == 4) 
    {
        // Modo Interactivo
        string input;
        int bandeja_i;
        char tipo_muestra;
        int cantidad;
        
        cout << "> ";
        getline(cin, input);

        while (!cin.eof())
        {   
            string aux = "";
            bandeja_i = string_cast_pos(aux += input[0]);
            aux.clear();
            tipo_muestra = input[2];
            cantidad = string_cast_pos(aux += input[4]);

            cout << "> ";
            getline(cin, input);
        }
        
    } 
    else
    {
        handle_reg_files(4, size, argv);
    }
    
}



