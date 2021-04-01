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
    names->dirs = (char **) malloc(sizeof(char *) * argn);
    
    if (argn > 1) {
        uint8_t i = 1;

        while(i < argn) {
            if(!mx_strncmp(argv[i], "-", 1)) {
                for(int j = 1; j < mx_strlen(argv[i]); ++j) {
                    set_flags(names, argv[i][j]);
                }
                ++i;
            }
            else
                break;
        }

        while(i < argn) {
            names->folder = opendir(argv[i]);

            if(names->folder) {
                names->dirs[names->dirs_count++] = argv[i++];
            }
            else {
                perror(argv[i++]);
            }
            
            closedir(names->folder);
        }
    }

    if(names->dirs_count == 0) {
        names->dirs[names->dirs_count++] = ".";
    }

    // print_set_flags(names);
}
