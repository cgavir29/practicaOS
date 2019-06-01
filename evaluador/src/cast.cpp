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

int string_cast_pos(string val) {
    {
    try
    {
        int num = stoi(val);
        if (num < 0) {
            cout << "Number must be positive" << endl;
            exit(0);
        } else {
            return num;
        }
    }
    catch (...)
    {
        cout << "Invalid value, '" << val << "' must be a number" << endl;
        exit(0);
    }
}
}