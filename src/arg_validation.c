#include "uls.h"

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
