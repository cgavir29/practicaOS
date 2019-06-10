#pragma once

#include "structs.h"

using namespace std;

void handle_reg(int size, char* argv[]);

void handle_reg_files(int start, int end, char* argv[], Evaluador *pEval);

int handle_reg_exams(int ban_i, char tipo_muestra, int cantidad, Evaluador *pEval, int id_set);
