#include <string>
#include <iostream>
#include "init.h"
#include "cast.h"

using namespace std;

void handle_init_opt_i(string val, bool given)
{
    int num_entries = 5;
    if (given)
    {
        num_entries = string_cast(val);
    }

    // Do Stuff
}

void handle_init_opt_ie(string val, bool given)
{
    int ent_queue_len = 6;
    if (given)
    {
        ent_queue_len = string_cast(val);
    }

    // Do Stuff
}

void handle_init_opt_oe(string val, bool given)
{
    int out_queue_len = 10;
    if (given)
    {
        out_queue_len = string_cast(val);
    }

    // Do Stuff
}

void handle_init_opt_n(string val, bool given)
{
    string mem_seg_name = "evaluator";
    if (given)
    {
        mem_seg_name = val;
    }

    // Do Stuff
}

void handle_init_opt_b(string val, bool given)
{
    int blood_lvl = 100;
    if (given)
    {
        blood_lvl = string_cast(val); // 100 es el default max pero no puede pasarse?
    }

    // Do Stuff
}

void handle_init_opt_d(string val, bool given)
{
    int detritus_lvl = 100;
    if (given)
    {
        detritus_lvl = string_cast(val); // 100 es el default max pero no puede pasarse?
    }

    // Do Stuff
}

void handle_init_opt_ee(string val, bool given)
{
    // No esta en la presentacion

    // Do Stuff
}

void handle_init_opt_s(string val, bool given)
{
    int skin_lvl = 100;
    if (given)
    {
        skin_lvl = string_cast(val);
    }

    // Do stuff
}

void handle_init_opt_q(string val, bool given)
{
    int int_queue_len = 6;
    if (given)
    {
        int_queue_len = string_cast(val);
    }

    // Do stuff
}

// Consider using enum when done
void handle_init(int start, int end, char *argv[])
{
    // Options for the init command, a default value must be set if none is given
    bool i = false, ie = false, oe = false, n = false;
    bool b = false, d = false, ee = false, s = false, q = false;

    for (int k = start; k < end - 1; k++)
    {
        string option = argv[k];
        string val = argv[k + 1];

        if (option == "-i")
        {
            if (i)
            {
                cout << "Option has already been set, first given value will be used" << endl;
                // exit() if desired
            }
            else
            {
                i = true;
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
                handle_init_opt_oe(val, oe);
            }
            k++;
            continue;
        }
        else if (option == "-n")
        {
            n = true;
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
                handle_init_opt_b(val, b);
            }
            k++;
            continue;
        }
        else if (option == "-d")
        {
            d = true;
            handle_init_opt_d(val, d);
            k++;
            continue;
        }
        else if (option == "-ee")
        {
            ee = true;
            handle_init_opt_ee(val, ee);
            k++;
            continue;
        }
        else if (option == "-s")
        {
            s = true;
            handle_init_opt_s(val, s);
            k++;
            continue;
        }
        else if (option == "-q")
        {
            q = true;
            handle_init_opt_q(val, q);
            k++;
            continue;
        }
        else
        {
            cout << "Option '" << option << "' not supported" << endl;
            exit(0);
        }
    }
}
