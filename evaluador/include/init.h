#pragma once

#include "structs.h"

using namespace std;

void initialize_evaluador(Evaluador *pEval, Header &auxHdr);

void initialize_buffers(Evaluador *pEval);

void initialize_exams(Evaluador *pEval);

void create_semaphores(Evaluador *pEval);

void create_threads(Evaluador *pEval);

Evaluador* create_shared_mem(Header& auxHdr);

Evaluador* handle_init(int start, int end, char* argv[]);

void *inter_to_salida(void *arg);

void *from_entr_to_inter(void *arg);




