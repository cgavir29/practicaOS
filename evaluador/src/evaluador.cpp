#include <iostream>
#include <string>
// #include <cerrno>
// #include <fstream>
// #include <sstream> 

using namespace std;

int string_cast(string val) {
    try {
        return stoi(val);
    } catch (...) {
        cout << "Invalid value, '" << val << "' must be a number" << endl;
        exit(0);
    }
}

void handle_init_opt_i(string val, bool given) {
    int x = 0;
    if (given) {
        x = string_cast(val);
    } else {
        // x = 6;
        cout << "Value is 6" << endl;
    }

    // Do Stuff
}


void handle_init_opt_ie(string val, bool given) {
    int x = 0;
    if (given) {
        x = string_cast(val);
    } else {
        // x = 6;
        cout << "Value is 6" << endl;
    }

    // Do Stuff
}

// -----------------------------------------------------------------
void handle_init(int start, int end, char *argv[]) {
    cout << "Init options..." << endl;
    // Options for the init command, a default value must be set if none is given
    bool i = false, ie = false, oe = false, n = false, b = false, d = false, ee = false, s = false, q = false;
    for (int k = start; k < end - 1; k++) {
        string option = argv[k];
        string val = argv[k + 1];

        if (option == "-i") {
            if (i) {
                cout << "Option has already been set, first given value will be used" << endl;
                // exit() if desired 
            } else {
                i = true;
                handle_init_opt_i(val, i);
            }
            k++; // Skip the next entire iteration
            continue; // Skip the rest of current iteration
        } else if (option == "-ie")
        {
            
            k++; // Skip the next entire iteration
            continue; // Skip the rest of current iteration
        }
        
    }

}





// -----------------------------------------------------------------
int handle_reg(int start, int end, char *argv[]) {
    return 0;
}

// -----------------------------------------------------------------
void handle_ctrl(int start, int end, char *argv[]) {

}

void handle_ctlr_list() {

}

void handle_ctlr_update() {

}


// -----------------------------------------------------------------
void handle_rep(int start, int end, char *argv[]) {

}


// -----------------------------------------------------------------
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Not enough arguments were given" << endl;
        exit(0);
    } else {
        string command = argv[1];
        cout << "Running '" + command + "' command" << endl;

        int start = 2;
        int end = argc;

        if (command == "init") {
            handle_init(start, end, argv);
        } else if (command == "reg")
        {   handle_reg(start, end, argv);
            /* code */
        } else if (command == "ctrl")
        {
           handle_reg(start, end, argv);

        } else if (command == "rep")
        {

        } else {
            cout << "Command '" + command + "' is not supported" << endl;
            exit(0);
        }
        
        
    }
    return 0;
}







