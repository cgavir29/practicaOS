#include "errs.h"
#include "cast.h"
#include "rep.h"

using namespace std;


void handle_rep_opt_n(string shared_mem) {

}

void handle_rep(int start, int end, char *argv[]) {
    for (int i = start; i < end; i++)
    {
        string option = argv[i];
        string shared_mem;

        if (i + 1 < end) {
            shared_mem = argv[i + 1];
        }

        if (option == "-n")
        {
            check_value(option, shared_mem);
            handle_rep_opt_n(shared_mem);
            i++;
            continue;
        } else
        {
            option_not_supported(option);
        }
        
        
    }
    
}