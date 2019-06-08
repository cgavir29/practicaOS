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
#include <fstream>
#include "errs.h"
#include "cast.h"
#include "structs.h"
#include "reg.h"

using namespace std;

// Mira si el fichero existe, sacado de https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
// bool exists_test3 (const string& name) {
//   struct stat buffer;   
//   return (stat (name.c_str(), &buffer) == 0); 
// }
int reg_reg(int bandeja_i, char tipo_muestra,int cantidad) 
{
    string ban_pos = to_string(bandeja_i);
    string be_vacios = "BEV" + ban_pos;
    string be_llenos = "BEL" + ban_pos;
    string be_mutex = "BEM" + ban_pos;

    sem_t *vacios, *llenos, *mutex;

    vacios = sem_open(be_vacios.c_str(), 0);
    llenos = sem_open(be_llenos.c_str(), 0);
    mutex = sem_open(be_mutex.c_str(),0);
    int fd = shm_open("/evaluador", O_RDWR, 0660); 

    if (fd < 0) {
    cerr << "Error abriendo la memoria compartida: "
	 << errno << strerror(errno) << endl;
    exit(1);
  }

  void *dir;

  if ((dir = mmap(NULL, sizeof(struct Evaluador), PROT_READ | PROT_WRITE, MAP_SHARED,
		  fd, 0)) == MAP_FAILED) {
    cerr << "Error mapeando la memoria compartida: "
	 << errno << strerror(errno) << endl;
    exit(1);
  }
  struct Evaluador *pEval = (struct Evaluador *) dir;

  for(;;) {

    sem_wait(vacios);
    sem_wait(mutex);

    pEval->ban_en.bandejas[bandeja_i].buffer[pEval->ban_en.bandejas[bandeja_i].entra].reactivo = tipo_muestra;
    pEval->ban_en.bandejas[bandeja_i].buffer[pEval->ban_en.bandejas[bandeja_i].entra].cantidad = cantidad;
    pEval->ban_en.bandejas[bandeja_i].entra = (pEval->ban_en.bandejas[bandeja_i].entra + 1) % bandeja_i;
    pEval->ban_en.bandejas[bandeja_i].cantidad++;

    sem_post(mutex);
    sem_post(llenos);
  }

}

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
