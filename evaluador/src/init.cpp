#include <string>
#include <iostream>
#include "errs.h"
#include "cast.h"
#include "init.h"

using namespace std;

void handle_init_opt_i(string val, bool given)
{
    int num_entries = 5;
    if (given)
    {
        num_entries = string_cast_pos(val);
    }

    // Do Stuff
}

void handle_init_opt_ie(string val, bool given)
{
    int ent_queue_len = 6;
    if (given)
    {
        ent_queue_len = string_cast_pos(val);
    }

    // Do Stuff
}

void handle_init_opt_oe(string val, bool given)
{
    int out_queue_len = 10;
    if (given)
    {
        out_queue_len = string_cast_pos(val);
    }

    // Do Stuff
}

void handle_init_opt_n(string val, bool given)
{
    string shared_mem = "evaluator";
    if (given)
    {
        shared_mem = val;
    }

    // Do Stuff
}

void handle_init_opt_b(string val, bool given)
{
    int blood_lvl = 100;
    if (given)
    {
        blood_lvl = string_cast_pos(val); // 100 es el default max pero no puede pasarse?
    }

    // Do Stuff
}

void handle_init_opt_d(string val, bool given)
{
    int detritus_lvl = 100;
    if (given)
    {
        detritus_lvl = string_cast_pos(val); // 100 es el default max pero no puede pasarse?
    }

    // Do Stuff
}

void handle_init_opt_s(string val, bool given)
{
    int skin_lvl = 100;
    if (given)
    {
        skin_lvl = string_cast_pos(val);
    }

    // Do stuff
}

void handle_init_opt_q(string val, bool given)
{
    int int_queue_len = 6;
    if (given)
    {
        int_queue_len = string_cast_pos(val);
    }

    // Do stuff
}

// Consider using enum when done
void handle_init(int start, int end, char *argv[])
{
    // Options for the init command, a default value must be set if none is given
    bool i = false, ie = false, oe = false, n = false;
    bool b = false, d = false, ee = false, s = false, q = false;

    // cout << "Start = " << start << endl;
    // cout << "End = " << end << endl;
    for (int k = start; k < end; k++)
    {
        string option = argv[k];
        string val;
        // cout << "Option = " << option << endl;
        if (k + 1 < end) {
            val = argv[k + 1];
        }
        // cout << "Value = " << val << endl;

        if (option == "-i")
        {
            if (i)
            {
                // Deberia parar o no? preguntar a mc
                cout << "Option has already been set, first given value will be used" << endl;
                // exit() if desired
            }
            else
            {   
                i = true;
                check_value(option, val);
                handle_init_opt_i(val, i);
            }
            k++; // Skip the next entire iteration (value)
            continue;
        }
        else if (option == "-ie")
        {
            if (ie)
            {
                cout << "Option has already been set, first given value will be used" << endl;
            }
            else
            {
                ie = true;
                check_value(option, val);
                handle_init_opt_ie(val, ie);
            }
            k++;
            continue;
        }
        else if (option == "-oe")
        {
            if (oe)
            {
                cout << "Option has already been set, first given value will be used" << endl;
            }
            else
            {
                oe = true;
                check_value(option, val);
                handle_init_opt_oe(val, oe);
            }
            k++;
            continue;
        }
        else if (option == "-n")
        {
            n = true;
            check_value(option, val);
            handle_init_opt_n(val, n);
            k++;
            continue;
        }
        else if (option == "-b")
        {
            if (b)
            {
                cout << "Option has already been set, first given value will be used" << endl;
            }
            else
            {
                b = true;
                check_value(option, val);
                handle_init_opt_b(val, b);
            }
            k++;
            continue;
        }
        else if (option == "-d")
        {
            d = true;
            check_value(option, val);
            handle_init_opt_d(val, d);
            k++;
            continue;
        }
        else if (option == "-s")
        {
            s = true;
            check_value(option, val);
            handle_init_opt_s(val, s);
            k++;
            continue;
        }
        else if (option == "-q")
        {
            q = true;
            check_value(option, val);
            handle_init_opt_q(val, q);
            k++;
            continue;
        }
        else
        {
            option_not_supported(option);
        }
    }
}
