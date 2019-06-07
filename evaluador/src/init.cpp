#include <string>
#include <iostream>
#include "errs.h"
#include "cast.h"
#include "init.h"

using namespace std;

void handle_init(int start, int end, char *argv[], Header &auxHdr)
{
    string option;
    string val;

    bool i = false, ie = false, oe = false, n = false;
    bool b = false, d = false, s = false, q = false;

    for (int k = start; k < end; k++)
    {
        option = argv[k];
        if (k + 1 < end)
        {
            val = argv[k + 1];
        }

        if (option == "-i")
        {
            check_value(option, val);
            auxHdr.i = string_cast_pos(val);
            i = true;
            k++;
            continue;
        }
        else if (option == "-ie")
        {
            check_value(option, val);
            auxHdr.ie = string_cast_pos(val);
            ie = true;
            k++;
            continue;
        }
        else if (option == "-oe")
        {
            check_value(option, val);
            auxHdr.oe = string_cast_pos(val);
            i = true;
            k++;
            continue;
        }
        else if (option == "-n")
        {
            for (u_long i = 0; i < val.length(); i++)
            {
                auxHdr.n[i] = val[i];
            }
            n = true;
            k++;
            continue;
        }
        else if (option == "-b")
        {
            check_value(option, val);
            auxHdr.b = string_cast_pos(val);
            b = true;
            k++;
            continue;
        }
        else if (option == "-d")
        {
            check_value(option, val);
            auxHdr.d = string_cast_pos(val);
            d = true;
            k++;
            continue;
        }
        else if (option == "-s")
        {
            check_value(option, val);
            auxHdr.s = string_cast_pos(val);
            s = true;
            k++;
            continue;
        }
        else if (option == "-q")
        {
            check_value(option, val);
            auxHdr.q = string_cast_pos(val);
            q = true;
            k++;
            continue;
        }
        else
        {
            option_not_supported(option);
        }
    }

    // Defaults, no seria mejor ponerlos en el struct?
    if (!i)
    {
        auxHdr.i = 5;
    }

    if (!ie)
    {
        auxHdr.ie = 6;
    }

    if (!oe)
    {
        auxHdr.oe = 10;
    }

    if (!n)
    {
        string val = "evaluador";
        for (u_long i = 0; i < val.length(); i++)
        {
            auxHdr.n[i] = val[i];
        }
    }

    if (!b)
    {
        auxHdr.b = 100;
    }

    if (!d)
    {
        auxHdr.d = 100;
    }

    if (!s)
    {
        auxHdr.s = 100;
    }

    if (!q)
    {
        auxHdr.q = 6;
    }
}