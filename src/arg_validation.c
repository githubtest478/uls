#include "uls.h"

void arg_validation(int argn, char **argv, t_names *names)
{
    names->dirs = (char **) malloc(sizeof(char *) * argn);
    uint8_t dirs_count = 0;

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
                names->dirs[dirs_count++] = mx_strdup(argv[i++]);
                names->dirs[dirs_count] = NULL;
            }
            else {
                perror(argv[i++]);
            }
            
            closedir(names->folder);
        }
    }

    if(dirs_count == 0) {
        names->dirs[dirs_count++] = ".";
        names->dirs[dirs_count] = NULL;
    }

    // print_set_flags(names);
}
