#pragma once

#include <string>

using namespace std;

void not_enough_args();

void command_not_supported(const string& command);

void option_not_supported(const string& option);

void check_value(const string& option, const string& val);

void string_not_num(const string& val);

void num_not_positive(int num);




