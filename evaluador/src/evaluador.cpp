#include <iostream>
#include <string>
#include "cast.h"
#include "init.h"
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
        string command = argv[1];
        cout << "Running '" + command + "' command" << endl;

        int start = 2;
        int end = argc;

        if (command == "init")
        {
            handle_init(start, end, argv);
        }
        else if (command == "reg")
        {
            // {   handle_reg(start, end, argv);
            /* code */
        }
        else if (command == "ctrl")
        {
            //    handle_reg(start, end, argv);
        }
        else if (command == "rep")
        {
        }
        else
        {
            cout << "Command '" + command + "' not supported" << endl;
            exit(0);
        }
    }
    return 0;
}
