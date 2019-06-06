#include <string>
#include "header.h"

using namespace std;

void handle_init(int start, int end, char* argv[], Header& headr);

int hande_init_opt_i(const string& val, bool given);

int handle_init_opt_ie(const string& val, bool given);

int handle_init_opt_oe(const string& val, bool given);

void handle_init_opt_n(const string& val, char* target, bool given);

int handle_init_opt_b(const string& val, bool given);

int handle_init_opt_d(const string& val, bool given);

int handle_init_opt_s(const string& val, bool given);

int handle_init_opt_q(const string& val, bool given);
