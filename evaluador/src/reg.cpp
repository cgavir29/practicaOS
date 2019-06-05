#include "errs.h"
#include "cast.h"
#include "reg.h"

using namespace std;

void handle_reg_opt_n(string shared_mem)
{

}

void handle_reg(int start, int end, char *argv[]) 
{
    for (int i = start; i < end; i++)
    {
        string option = argv[i];
        string shared_mem;

        if (i + 1 < end) 
        {
            shared_mem = argv[i + 1];
        }

        if (option == "-n")
        {
            check_value(option, shared_mem);
            handle_reg_opt_n(shared_mem);
            i++;
            continue;
        } 
        else
        {
            option_not_supported(option);
        }
        
        
    }
}