#include <string>
#include <iostream>
#include "errs.h"
#include "cast.h"

using namespace std;

int string_cast(const string& val)
{
    try
    {
        return stoi(val);
    }
    catch (...)
    {
        string_not_num(val);
    }
}

int string_cast_pos(const string& val) 
{
    try
    {
        int num = stoi(val);
        if (num < 0) 
        {
            num_not_positive(num);
        } 
        else 
        {
            return num;
        }
    }
    catch (...)
    {
        string_not_num(val);
    }
}
