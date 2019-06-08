#pragma once

#include <string>
#include "structs.h"

using namespace std;

void handle_ctrl(char* argv[]);

void handle_ctrl_sub_list(const string& option, struct Evaluador *pEval);

void handle_ctrl_sub_list_opt_proc(struct Evaluador *pEval);

void handle_ctrl_sub_list_opt_wait(struct Evaluador *pEval);

void handle_ctrl_sub_list_opt_repo(struct Evaluador *pEval);

void handle_ctrl_sub_list_opt_reac(struct Evaluador *pEval);

void handle_ctrl_sub_list_opt_all(struct Evaluador *pEval);

void handle_ctrl_sub_update(const string& sub_command_info, struct Evaluador *pEval);

void handle_ctrl_sub_update_opt_b(const string& val, struct Evaluador *pEval);

void handle_ctrl_sub_update_opt_d(const string& val, struct Evaluador *pEval);

void handle_ctrl_sub_update_opt_s(const string& val, struct Evaluador *pEval);

