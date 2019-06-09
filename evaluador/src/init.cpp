#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include "errs.h"
#include "cast.h"
#include "init.h"

using namespace std;

// ------------------------------------------------------------------------------------------------
void *inter_to_salida(void *arg)
{
    srand(time(NULL));
    struct ParamI *parI = (struct ParamI *)arg;
    int tipo_rct = parI->tipo_rct;
    string shm_name = string(parI->shm_name);

    int id_tem;
    int ban_tem;
    char reactivo_tem;
    int cantidad_tem;
    int tiempo_tem;

    sem_t *vacios, *llenos, *mutex;

    int fd = shm_open(shm_name.c_str(), O_RDWR, 0660);
    if (fd < 0)
    {
        cerr << "Couldn't find shared memory segment '" << shm_name
             << "': " << strerror(errno) << endl;
        exit(1);
    }

    void *dir;
    if ((dir = mmap(NULL, sizeof(struct Evaluador), PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << strerror(errno) << endl;
        exit(1);
    }

    struct Evaluador *pEval = (struct Evaluador *)dir;

    for (;;)
    {
        if (tipo_rct == 0)
        {
            // Semaforos Reactivo B
            vacios = sem_open("BIVB", 0);
            llenos = sem_open("BILB", 0);
            mutex = sem_open("BIMB", 0);
        }
        else if (tipo_rct == 1)
        {
            // Semaforos Reactivo D
            vacios = sem_open("BIVD", 0);
            llenos = sem_open("BILD", 0);
            mutex = sem_open("BIMD", 0);
        }
        else if (tipo_rct == 2)
        {
            // Semaforos Reactivo S
            vacios = sem_open("BIVS", 0);
            llenos = sem_open("BILS", 0);
            mutex = sem_open("BIMS", 0);
        }

        sem_wait(llenos);
        sem_wait(mutex);

        id_tem = pEval->ban_in.bandejas[tipo_rct].buffer[pEval->ban_in.bandejas[tipo_rct].sale].id;
        ban_tem = pEval->ban_in.bandejas[tipo_rct].buffer[pEval->ban_in.bandejas[tipo_rct].sale].ban;
        reactivo_tem = pEval->ban_in.bandejas[tipo_rct].buffer[pEval->ban_in.bandejas[tipo_rct].sale].tipo;
        cantidad_tem = pEval->ban_in.bandejas[tipo_rct].buffer[pEval->ban_in.bandejas[tipo_rct].sale].cant_react;
        tiempo_tem = pEval->ban_in.bandejas[tipo_rct].buffer[pEval->ban_in.bandejas[tipo_rct].sale].tiempo;

        // Como si se hubiera borrado el examen de la cola interna
        pEval->ban_in.bandejas[tipo_rct].buffer[pEval->ban_in.bandejas[tipo_rct].sale].cant_react = 0;
        pEval->ban_in.bandejas[tipo_rct].sale = (pEval->ban_in.bandejas[tipo_rct].sale + 1) % pEval->hdr.q;
        pEval->ban_in.bandejas[tipo_rct].cantidad--;

        sem_post(mutex);
        sem_post(vacios);

        // Semaforos Bandeja de salida
        vacios = sem_open("BSV", 0);
        llenos = sem_open("BSL", 0);
        mutex = sem_open("BSM", 0);

        sem_wait(vacios);
        sem_wait(mutex);
        int r;

        r = 1 + rand() % (51 - 1);

        if(r >= 0 && r <=15){
            pEval->ban_out.buffer[pEval->ban_out.entra].informe = '?';

        }else if (r >= 16 && r <=35)
        {
            pEval->ban_out.buffer[pEval->ban_out.entra].informe = 'N';
        }else if (r >= 35 && r <=50)
        {
            pEval->ban_out.buffer[pEval->ban_out.entra].informe = 'P';
        }
        
        pEval->ban_out.buffer[pEval->ban_out.entra].id = id_tem;
        pEval->ban_out.buffer[pEval->ban_out.entra].ban = ban_tem;
        pEval->ban_out.buffer[pEval->ban_out.entra].tipo = reactivo_tem;
        pEval->ban_out.buffer[pEval->ban_out.entra].cant_react = cantidad_tem;
        pEval->ban_out.buffer[pEval->ban_out.entra].tiempo = tiempo_tem;
        pEval->ban_out.entra = (pEval->ban_out.entra + 1) % pEval->hdr.oe;
        pEval->ban_out.cantidad++;

        sem_post(mutex);
        sem_post(llenos);
    }
}

// ------------------------------------------------------------------------------------------------
void *from_entr_to_inter(void *arg)
{
    srand(time(NULL));
    struct ParamE *parE = (struct ParamE *)arg;
    int ban_i = parE->ban_i;
    string shm_name = string(parE->shm_name);

    int id_tem;
    int ban_tem;
    char reactivo_tem;
    int cantidad_tem;
    int tiempo_tem;

    string ban_pos = to_string(ban_i);
    string be_vacios = "BEV" + ban_pos;
    string be_llenos = "BEL" + ban_pos;
    string be_mutex = "BEM" + ban_pos;

    sem_t *vacios, *llenos, *mutex, *mutex_reactivo;

    int fd = shm_open(shm_name.c_str(), O_RDWR, 0660);
    if (fd < 0)
    {
        cerr << "Couldn't find shared memory segment '" << shm_name
             << "': " << strerror(errno) << endl;
        exit(1);
    }

    void *dir;
    if ((dir = mmap(NULL, sizeof(struct Evaluador), PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << strerror(errno) << endl;
        exit(1);
    }

    struct Evaluador *pEval = (struct Evaluador *)dir;

    for (;;)
    {
        vacios = sem_open(be_vacios.c_str(), 0);
        llenos = sem_open(be_llenos.c_str(), 0);
        mutex = sem_open(be_mutex.c_str(), 0);

        sem_wait(llenos);
        sem_wait(mutex);

        id_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].id;
        ban_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].ban;
        reactivo_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].tipo;

        if (reactivo_tem == 'B')
        {
            mutex_reactivo = sem_open("RBM", 0);
        }
        else if (reactivo_tem == 'D')
        {
            mutex_reactivo = sem_open("RDM", 0);
        }
        else if (reactivo_tem == 'S')
        {
            mutex_reactivo = sem_open("RSM", 0);
        }

        sem_wait(mutex_reactivo);

        cantidad_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].cant_react;
<<<<<<< HEAD
=======
        
       

        if (reactivo_tem == 'B')
        {
            tiempo_tem = 1 + rand() % (8 - 1);
        }
        else if (reactivo_tem == 'D')
        {

            tiempo_tem = 5 + rand() % (21 - 5);
        }
        else if (reactivo_tem == 'S')
        {
            tiempo_tem = 8 + rand() % (26 - 8);
        }
        //cout << tiempo_tem << endl;



        // cout << "Id Tem = " << id_tem << " "
        //      << "Tipo React = " << reactivo_tem << " "
        //      << "Cantidad Tem = " << cantidad_tem << endl;
>>>>>>> 4c53dc8e17ea58a3bd15499d66e0d3e109448e5f

        // Verifica que haya suficiente material del reactivo correspondiente
        // para realizar la muestra, en caso contrario, espera evitando que entren mas examenes
        // hasta que se aumente el reactivo
        if (reactivo_tem == 'B')
        {
            while (cantidad_tem > pEval->hdr.b)
            {
                // Abro para que modifiquen
                sem_post(mutex_reactivo);
                // Cierro para leer
                sem_wait(mutex_reactivo);
                cantidad_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].cant_react;
            }
            pEval->hdr.b = pEval->hdr.b - cantidad_tem;
        }
        else if (reactivo_tem == 'D')
        {
            while (cantidad_tem > pEval->hdr.d)
            {
                sem_post(mutex_reactivo);
                sem_wait(mutex_reactivo);
                cantidad_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].cant_react;
            }
            pEval->hdr.d = pEval->hdr.d - cantidad_tem;
        }
        else if (reactivo_tem == 'S')
        {
            while (cantidad_tem > pEval->hdr.s)
            {
                sem_post(mutex_reactivo);
                sem_wait(mutex_reactivo);
                cantidad_tem = pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].cant_react;
            }
            pEval->hdr.s = pEval->hdr.s - cantidad_tem;
        }

        // Como si se hubiera borrado el examen de la cola de entrada
        pEval->ban_en.bandejas[ban_i].buffer[pEval->ban_en.bandejas[ban_i].sale].cant_react = 0;
        pEval->ban_en.bandejas[ban_i].sale = (pEval->ban_en.bandejas[ban_i].sale + 1) % pEval->hdr.ie;
        pEval->ban_en.bandejas[ban_i].cantidad--;

        sem_post(mutex_reactivo);
        sem_post(mutex);
        sem_post(vacios);

        int cola_int;
        if (reactivo_tem == 'B')
        {
            // Semaforos Reactivo B
            vacios = sem_open("BIVB", 0);
            llenos = sem_open("BILB", 0);
            mutex = sem_open("BIMB", 0);
            cola_int = 0;
        }
        else if (reactivo_tem == 'D')
        {
            // Semaforos Reactivo D
            vacios = sem_open("BIVD", 0);
            llenos = sem_open("BILD", 0);
            mutex = sem_open("BIMD", 0);
            cola_int = 1;
        }
        else if (reactivo_tem == 'S')
        {
            // Semaforos Reactivo S
            vacios = sem_open("BIVS", 0);
            llenos = sem_open("BILS", 0);
            mutex = sem_open("BIMS", 0);
            cola_int = 2;
        }

        sem_wait(vacios);
        sem_wait(mutex);

        pEval->ban_in.bandejas[cola_int].buffer[pEval->ban_in.bandejas[cola_int].entra].id = id_tem;
        pEval->ban_in.bandejas[cola_int].buffer[pEval->ban_in.bandejas[cola_int].entra].ban = ban_tem;
        pEval->ban_in.bandejas[cola_int].buffer[pEval->ban_in.bandejas[cola_int].entra].tipo = reactivo_tem;
        pEval->ban_in.bandejas[cola_int].buffer[pEval->ban_in.bandejas[cola_int].entra].cant_react = cantidad_tem;
        pEval->ban_in.bandejas[cola_int].buffer[pEval->ban_in.bandejas[cola_int].entra].tiempo = tiempo_tem;
        pEval->ban_in.bandejas[cola_int].entra = (pEval->ban_in.bandejas[cola_int].entra + 1) % pEval->hdr.q;
        pEval->ban_in.bandejas[cola_int].cantidad++;

        sem_post(mutex);
        sem_post(llenos);
    }
}

// ------------------------------------------------------------------------------------------------
void initialize_evaluador(Evaluador *pEval, Header &auxHdr)
{
    pEval->hdr.i = auxHdr.i;
    pEval->hdr.ie = auxHdr.ie;
    pEval->hdr.oe = auxHdr.oe;
    for (int i = 0; i < 40; i++)
    {
        pEval->hdr.n[i] = auxHdr.n[i];
    }
    pEval->hdr.b = auxHdr.b;
    pEval->hdr.d = auxHdr.d;
    pEval->hdr.s = auxHdr.s;
    pEval->hdr.q = auxHdr.q;
}

// ------------------------------------------------------------------------------------------------
void initialize_buffers(Evaluador *pEval)
{
    // Buffers de Bandejas de Entrada
    for (int k = 0; k < pEval->hdr.i; k++)
    {
        pEval->ban_en.bandejas[k].id_counter = 0;
        pEval->ban_en.bandejas[k].entra = 0;
        pEval->ban_en.bandejas[k].sale = 0;
        pEval->ban_en.bandejas[k].cantidad = 0;
    }

    // Buffers de Bandejs Internas
    // 'B' = 0
    pEval->ban_in.bandejas[0].entra = 0;
    pEval->ban_in.bandejas[0].sale = 0;
    pEval->ban_in.bandejas[0].cantidad = 0;
    // 'D' = 1
    pEval->ban_in.bandejas[1].entra = 0;
    pEval->ban_in.bandejas[1].sale = 0;
    pEval->ban_in.bandejas[1].cantidad = 0;
    // 'S' = 2
    pEval->ban_in.bandejas[2].entra = 0;
    pEval->ban_in.bandejas[2].sale = 0;
    pEval->ban_in.bandejas[2].cantidad = 0;

    // Buffer de Bandeja de Salida
    pEval->ban_out.entra = 0;
    pEval->ban_out.sale = 0;
    pEval->ban_out.cantidad = 0;
}

// ------------------------------------------------------------------------------------------------
void initialize_exams(Evaluador *pEval)
{
    // Exams Bandejas de Entrada
    for (int i = 0; i < pEval->hdr.i; i++)
    {
        for (int j = 0; j < pEval->hdr.ie; j++)
        {
            pEval->ban_en.bandejas[i].buffer[j].id = -1;
            pEval->ban_en.bandejas[i].buffer[j].ban = -1;
            pEval->ban_en.bandejas[i].buffer[j].tipo = ' ';
            pEval->ban_en.bandejas[i].buffer[j].cant_react = 0;
            pEval->ban_en.bandejas[i].buffer[j].tiempo = -1;
            pEval->ban_en.bandejas[i].buffer[j].informe = ' ';
        }
    }

    // Exams Bandejas Internas
    for (int i = 0; i < NUM_TIPO_REACTS; i++)
    {
        for (int j = 0; j < pEval->hdr.q; j++)
        {
            pEval->ban_in.bandejas[i].buffer[j].id = -1;
            pEval->ban_in.bandejas[i].buffer[j].ban = -1;
            pEval->ban_in.bandejas[i].buffer[j].tipo = ' ';
            pEval->ban_in.bandejas[i].buffer[j].cant_react = 0;
            pEval->ban_in.bandejas[i].buffer[j].tiempo = -1;
            pEval->ban_in.bandejas[i].buffer[j].informe = ' ';
        }
    }

    // Exams Bandejas de Salida
    for (int i = 0; i < pEval->hdr.oe; i++)
    {
        pEval->ban_out.buffer[i].id = -1;
        pEval->ban_out.buffer[i].ban = -1;
        pEval->ban_out.buffer[i].tipo = ' ';
        pEval->ban_out.buffer[i].cant_react = 0;
        pEval->ban_out.buffer[i].tiempo = -1;
        pEval->ban_out.buffer[i].informe = ' ';
    }
}

// ------------------------------------------------------------------------------------------------
void create_threads(Evaluador *pEval)
{
    // Hilos Bandejas de Entrada
    pthread_t hilosEntrada[LEN_BAN_ENTRA_ENTRY];
    for (int i = 0; i < pEval->hdr.i; i++)
    {
        void *arg = malloc(sizeof(struct ParamE));
        struct ParamE *parE = (struct ParamE *)arg;
        parE->ban_i = i;
        for (int j = 0; j < 40; j++)
        {
            parE->shm_name[j] = pEval->hdr.n[j];
        }
        pthread_create((hilosEntrada + i), NULL, from_entr_to_inter, (void *)parE);
    }

    pthread_t hilosInternos[NUM_TIPO_REACTS];
    for (int i = 0; i < NUM_TIPO_REACTS; i++)
    {
        void *arg = malloc(sizeof(struct ParamI));
        struct ParamI *parI = (struct ParamI *)arg;
        parI->tipo_rct = i;
        for (int j = 0; j < 40; j++)
        {
            parI->shm_name[j] = pEval->hdr.n[j];
        }
        pthread_create((hilosInternos + i), NULL, inter_to_salida, (void *)parI);
    }
}

// ------------------------------------------------------------------------------------------------
void create_semaphores(Evaluador *pEval)
{
    // Semaforos Bandejas Entrada
    string ban_pos;
    string be_vacios;
    string be_llenos;
    string be_mutex;

    for (int k = 0; k < pEval->hdr.i; k++)
    {
        ban_pos = to_string(k);
        be_vacios = "BEV" + ban_pos;
        be_llenos = "BEL" + ban_pos;
        be_mutex = "BEM" + ban_pos;

        sem_open(be_vacios.c_str(), O_CREAT | O_EXCL, 0660, pEval->hdr.ie);
        sem_open(be_llenos.c_str(), O_CREAT | O_EXCL, 0660, 0);
        sem_open(be_mutex.c_str(), O_CREAT | O_EXCL, 0660, 1);
    }

    // Semaforos Bandejas Internas
    // Semaforos Bandeja B
    sem_open("BIVB", O_CREAT | O_EXCL, 0660, pEval->hdr.q);
    sem_open("BILB", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BIMB", O_CREAT | O_EXCL, 0660, 1);
    // Semaforos Bandeja D
    sem_open("BIVD", O_CREAT | O_EXCL, 0660, pEval->hdr.q);
    sem_open("BILD", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BIMD", O_CREAT | O_EXCL, 0660, 1);
    // Semaforos Bandeja S
    sem_open("BIVS", O_CREAT | O_EXCL, 0660, pEval->hdr.q);
    sem_open("BILS", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BIMS", O_CREAT | O_EXCL, 0660, 1);

    // Semaforo Bandeja Salida
    sem_open("BSV", O_CREAT | O_EXCL, 0660, pEval->hdr.oe);
    sem_open("BSL", O_CREAT | O_EXCL, 0660, 0);
    sem_open("BSM", O_CREAT | O_EXCL, 0660, 1);

    // Semaforos Reactivos
    sem_open("RBM", O_CREAT | O_EXCL, 0660, 1);
    sem_open("RDM", O_CREAT | O_EXCL, 0660, 1);
    sem_open("RSM", O_CREAT | O_EXCL, 0660, 1);
}

// ------------------------------------------------------------------------------------------------
Evaluador *create_shared_mem(Header &auxHdr)
{
    int fd = shm_open(auxHdr.n, O_RDWR | O_CREAT | O_EXCL, 0660);
    if (ftruncate(fd, sizeof(struct Evaluador)) != 0)
    {
        cerr << "Error creando la memoria compartida: "
             << errno << " " << strerror(errno) << endl;
        exit(1);
    }

    void *dir;
    if ((dir = mmap(NULL, sizeof(struct Evaluador),
                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << " " << strerror(errno) << endl;
        exit(1);
    }

    struct Evaluador *pEval = (struct Evaluador *)dir;

    initialize_evaluador(pEval, auxHdr);
    initialize_buffers(pEval);
    initialize_exams(pEval);
    create_semaphores(pEval);
    create_threads(pEval);

    close(fd);

    return pEval;
}

// ------------------------------------------------------------------------------------------------
Evaluador *handle_init(int start, int end, char *argv[])
{
    struct Header auxHdr;

    bool i = false, ie = false, oe = false, n = false;
    bool b = false, d = false, s = false, q = false;

    string option;
    string val;

    for (int k = start; k < end; k++)
    {
        option = argv[k];
        if (k + 1 < end)
        {
            val = argv[k + 1];
        }

        if (option == "-i")
        {
            check_value(option, val);
            auxHdr.i = string_cast_pos(val);
            i = true;
            k++;
            continue;
        }
        else if (option == "-ie")
        {
            check_value(option, val);
            auxHdr.ie = string_cast_pos(val);
            ie = true;
            k++;
            continue;
        }
        else if (option == "-oe")
        {
            check_value(option, val);
            auxHdr.oe = string_cast_pos(val);
            i = true;
            k++;
            continue;
        }
        else if (option == "-n")
        {
            for (u_long i = 0; i < val.length(); i++)
            {
                auxHdr.n[i] = val[i];
            }
            n = true;
            k++;
            continue;
        }
        else if (option == "-b")
        {
            check_value(option, val);
            auxHdr.b = string_cast_pos(val);
            b = true;
            k++;
            continue;
        }
        else if (option == "-d")
        {
            check_value(option, val);
            auxHdr.d = string_cast_pos(val);
            d = true;
            k++;
            continue;
        }
        else if (option == "-s")
        {
            check_value(option, val);
            auxHdr.s = string_cast_pos(val);
            s = true;
            k++;
            continue;
        }
        else if (option == "-q")
        {
            check_value(option, val);
            auxHdr.q = string_cast_pos(val);
            q = true;
            k++;
            continue;
        }
        else
        {
            option_not_supported(option);
        }
    }

    if (!i)
    {
        auxHdr.i = 5;
    }

    if (!ie)
    {
        auxHdr.ie = 6;
    }

    if (!oe)
    {
        auxHdr.oe = 10;
    }

    if (!n)
    {
        string val = "evaluador";
        for (u_long i = 0; i < val.length(); i++)
        {
            auxHdr.n[i] = val[i];
        }
    }

    if (!b)
    {
        auxHdr.b = 100;
    }

    if (!d)
    {
        auxHdr.d = 100;
    }

    if (!s)
    {
        auxHdr.s = 100;
    }

    if (!q)
    {
        auxHdr.q = 6;
    }

    return create_shared_mem(auxHdr);
}