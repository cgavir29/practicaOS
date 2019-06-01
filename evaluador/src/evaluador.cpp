#include <iostream>
#include <string>
#include "cast.h"
#include "init.h"
#include "reg.h"
#include "ctrl.h"
#include "rep.h"
// #include <cerrno>
// #include <fstream>
// #include <sstream>

using namespace std;


// -----------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Not enough arguments were given" << endl;
        exit(0);
    }
    else
    {
        int start = 2;
        int end = argc;
        string command = argv[1];
        // cout << "Running '" + command + "' command" << endl;

        if (command == "init")
        {
            handle_init(start, end, argv);
        }
        else if (command == "reg")
        {
            handle_reg(start, end, argv);
        }
        else if (command == "ctrl")
        {
            handle_ctrl(start, end, argv);
        }
        else if (command == "rep")
        {
            handle_rep(start, end, argv);
        }
        else
        {
            cout << "Command '" + command + "' not supported" << endl;
            exit(0);
        }
    }
    return 0;
}
