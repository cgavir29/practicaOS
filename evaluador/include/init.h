#pragma once

#include "structs.h"

using namespace std;

void initialize_evaluador(Evaluador *pEval, Header &auxHdr);

void initialize_buffers(Evaluador *pEval);

void create_semaphores(Evaluador *pEval);

Evaluador* create_shared_mem(Header& auxHdr);

Evaluador* handle_init(int start, int end, char* argv[]);




