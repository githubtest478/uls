#include "uls.h"

void arg_validation(int argn, char **argv)
{
    if(argn == 1)
        return;
    
    for(uint8_t i = 1; i < argn; ++i) {
        if(!mx_strncmp(argv[i], "--", 2)) {
            //set flags with "--" prefix
        }
        else if(!mx_strncmp(argv[i], "-", 1)) {
            //set flags with "-" prefix
        }
        else {
            //get sourse address
        }
    }
}
