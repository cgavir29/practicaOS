#include <string>
#include <iostream>
#include "errs.h"

using namespace std;

void not_enough_args() {
    cout << "Not enough arguments were given" << endl;
    exit(0);
}

void command_not_supported(string command) {
    cout << "Command '" + command + "' not supported" << endl;
    exit(0);
}

void option_not_supported(string option) {
    cout << "Option '" << option << "' not supported" << endl;
    exit(0);
}

void string_not_num(string val) {
    cout << "Invalid value, '" << val << "' must be a number" << endl;
    exit(0);
}

void num_not_positive(int num) {
    cout << "Invalid value, '" << num << "' must be postive" << endl;
    exit(0);
}