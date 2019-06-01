#include <string>
#include <iostream>
#include "cast.h"

using namespace std;

int string_cast(string val)
{
    try
    {
        return stoi(val);
    }
    catch (...)
    {
        cout << "Invalid value, '" << val << "' must be a number" << endl;
        exit(0);
    }
}