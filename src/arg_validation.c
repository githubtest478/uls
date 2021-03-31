#include "uls.h"

void init_dir_structure(t_names *names)
{
    RESET_FLAG(names->flags, ~clear_flags);
    names->flags |= flag_C;
    names->dirs_count = 0;
    names->count_file = 0;
    names->total_size = 0;
    names->count_line = 0;
    names->dirs_index = 0;
    names->list_size = 0;
    names->sort = NULL;
    names->dirs = NULL;
    names->dilim1 = NULL;
    names->dilim2 = NULL;
    names->list = NULL;
    names->dirs_content = NULL;
    names->folder = NULL;
}

void arg_validation(int argn, char **argv, t_names *names)
{
    init_dir_structure(names);
    names->dirs = (char **) malloc(sizeof(char *) * argn);

    for(uint8_t i = 1; i < argn; ++i) {
        if(!mx_strncmp(argv[i], "--", 2)) {
            //set flags with "--" prefix (optional)
        }
        else if(!mx_strncmp(argv[i], "-", 1)) {
            for(int j = 1; j < mx_strlen(argv[i]); ++j) {
                set_flags(names, argv[i][j]);
            }
        }
        else {
            names->dirs[names->dirs_count] = argv[i];   //read dirs to structure
            names->dirs_count++;
        }
        
        if(errno) {
            strerror(errno);
        }
    }

    if(names->dirs_count == 0) {
        names->dirs[0] = ".";
        names->dirs_count++;
    }
    print_set_flags(names);
}
