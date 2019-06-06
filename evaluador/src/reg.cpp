#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include "errs.h"
#include "cast.h"
#include "reg.h"

using namespace std;

// Mira si el fichero existe, sacado de https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
// bool exists_test3 (const string& name) {
//   struct stat buffer;   
//   return (stat (name.c_str(), &buffer) == 0); 
// }

void handle_reg_files(int start, int end, char* argv[])
{
    cout << "Handling Files" << endl;

    ifstream infile;
    ofstream outfile;

    int bandeja_i;  
    char tipo_muestra;
    int cantidad;

    for (int i = start; i < end; i++)
    {
        string infile_name = argv[i];
        infile.open(infile_name);
        // ifstream infile(infile_name);

        size_t lastindex = infile_name.find_last_of("."); 
        string rawname = infile_name.substr(0, lastindex);
        outfile.open(rawname + ".spl");
        // ofstream outfile(infile_name + ".spl");

        // cout << argv[i] << endl;

        while (infile >> bandeja_i >> tipo_muestra >> cantidad) 
        {
            
            // cout << bandeja_i << tipo_muestra << cantidad << endl;

            outfile << 3 << endl; // obviamente tiene que ser el que se genere
        }

        infile.close();
        outfile.close();
    }
    
}

void handle_reg(int size, char *argv[]) 
{
    char* option = argv[2];
    char* option_value = argv[3];

    if (size == 4) 
    {
        // Modo Interactivo
        int bandeja_i;
        char tipo_muestra;
        int cantidad;
        
        cout << "> ";
        cin >> bandeja_i >> tipo_muestra >> cantidad;

        while (!cin.eof()) 
        {

            cout << "> ";
            cin >> bandeja_i >> tipo_muestra >> cantidad;

        }
        
    }
    else
    {
        handle_reg_files(4, size, argv);
    }
    
}
