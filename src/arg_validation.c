#include "uls.h"

void init_dir_structure(t_names *names)
{
    names->flags |= flag_C;
    names->dirs = (char **) malloc(sizeof(char *));
    names->dirs_count = 0;
    names->file_count = 0;
}

void arg_validation(int argn, char **argv, t_names *names)
{
    init_dir_structure(names);

    for(uint8_t i = 1; i < argn; ++i) {
        if(!mx_strncmp(argv[i], "--", 2)) {
            //set flags with "--" prefix (optional)
        }
        else if(!mx_strncmp(argv[i], "-", 1)) {
            for(int j = 1; j < mx_strlen(argv[i]); ++j) {
                set_flags(names, argv[i][j]);
            }   //set flags with "-" prefix
        }
        else {
            names->dirs[names->dirs_count++] = argv[i];   //read dirs to structure
        }
        
        if(errno) {
            strerror(errno);
        }
    }

    if(names->dirs_count == 0) {
        names->dirs[0] = ".";
        names->dirs_count++;
    }
}
