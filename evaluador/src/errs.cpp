#include <string>
#include <iostream>
#include "errs.h"

using namespace std;

// ------------------------------------------------------------------------------------------------
void not_enough_args() 
{
    cout << "Not enough arguments were given" << endl;
    exit(1);
}

// ------------------------------------------------------------------------------------------------
void command_not_supported(const string& command) 
{
    cout << "Command '" + command + "' not supported" << endl;
    exit(1);
}

// ------------------------------------------------------------------------------------------------
void option_not_supported(const string& option) 
{
    cout << "Option '" << option << "' not supported" << endl;
    exit(1);
}

// ------------------------------------------------------------------------------------------------
void check_value(const string& option, const string& val) 
{
    if (val.empty()) 
    {
        cout << "No value given for option '" << option << "'" << endl;
        exit(1);
    }
}

// ------------------------------------------------------------------------------------------------
void string_not_num(const string& val) 
{
    cout << "Invalid value, '" << val << "' must be a number" << endl;
    exit(1);
}

// ------------------------------------------------------------------------------------------------
void num_not_positive(int num) 
{
    cout << "Invalid value, '" << num << "' must be postive" << endl;
    exit(1);
}

