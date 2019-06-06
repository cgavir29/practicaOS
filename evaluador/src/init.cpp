#include <string>
#include <iostream>
#include "errs.h"
#include "cast.h"
#include "init.h"

using namespace std;

int handle_init_opt_i(const string& val, bool given)
{
    int num_entries = 5;
    if (given)
    {
        num_entries = string_cast_pos(val);
    }

    return num_entries;
}

int handle_init_opt_ie(const string& val, bool given)
{
    int ent_queue_len = 6;
    if (given)
    {
        ent_queue_len = string_cast_pos(val);
    }

    return ent_queue_len;
}

int handle_init_opt_oe(const string& val, bool given)
{
    int out_queue_len = 10;
    if (given)
    {
        out_queue_len = string_cast_pos(val);
    }

    return out_queue_len;
}

void handle_init_opt_n(const string& val, char* target, bool given)
{
    string shared_mem = "evaluator";
    if (given)
    {
        shared_mem = val;
    }

    for (u_long i = 0; i < val.length(); i++) {
        target[i] = val[i];
    }

}

int handle_init_opt_b(const string& val, bool given)
{
    int blood_lvl = 100;
    if (given)
    {
        blood_lvl = string_cast_pos(val); // 100 es el default max pero no puede pasarse?
    }

    return blood_lvl;

}

int handle_init_opt_d(const string& val, bool given)
{
    int detritus_lvl = 100;
    if (given)
    {
        detritus_lvl = string_cast_pos(val); // 100 es el default max pero no puede pasarse?
    }

    return detritus_lvl;
}

int handle_init_opt_s(const string& val, bool given)
{
    int skin_lvl = 100;
    if (given)
    {
        skin_lvl = string_cast_pos(val);
    }

    return skin_lvl;
}

int handle_init_opt_q(const string& val, bool given)
{
    int int_queue_len = 6;
    if (given)
    {
        int_queue_len = string_cast_pos(val);
    }

    return int_queue_len;
}


void handle_init(int start, int end, char *argv[], Header& headr)
{
    string option;
    string val;

    bool i = false, ie = false, oe = false, n = false;
    bool b = false, d = false, s = false, q = false;

    for (int k = start; k < end; k++)
    {
        option = argv[k];
        if (k + 1 < end) {
            val = argv[k + 1];
        }

        if (option == "-i")
        {
            if (!i)
            {
                i = true;
                check_value(option, val);
                headr.i = handle_init_opt_i(val, i);
            }
            k++; // Skip the next entire iteration (value)
            continue;
        }
        else if (option == "-ie")
        {
            if (!ie)
            {
                ie = true;
                check_value(option, val);
                headr.ie = handle_init_opt_ie(val, ie);
            }
            k++;
            continue;
        }
        else if (option == "-oe")
        {
            if (!oe)
            {
                oe = true;
                check_value(option, val);
                headr.oe = handle_init_opt_oe(val, oe);
            }
            k++;
            continue;
        }
        else if (option == "-n")
        {
            if (!n) {
                n = true;
                check_value(option, val);
                handle_init_opt_n(val, headr.n, n);
            }
            k++;
            continue;
        }
        else if (option == "-b")
        {
            if (!b)
            {
                b = true;
                check_value(option, val);
                headr.b = handle_init_opt_b(val, b);
            }
            k++;
            continue;
        }
        else if (option == "-d")
        {
            if (!d) {
                d = true;
                check_value(option, val);
                headr.d = handle_init_opt_d(val, d);
            }
            k++;
            continue;
        }
        else if (option == "-s")
        {
            if (!s) {
                s = true;
                check_value(option, val);
                headr.s = handle_init_opt_s(val, s);
            }
            k++;
            continue;
        }
        else if (option == "-q")
        {
            if (!q) {
                q = true;
                check_value(option, val);
                headr.q = handle_init_opt_q(val, q);
            }
            k++;
            continue;
        }
        else
        {
            option_not_supported(option);
        }
    }
}
