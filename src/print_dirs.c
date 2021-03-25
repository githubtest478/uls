#include "uls.h"

void print_dirs(t_names * names)
{

    char *dilim1 =  READ_FLAG(names->flags, flag_l)     ? " "   : "";
    char *dilim2 =  READ_FLAG(names->flags, flag_m)     ? ", "  :
                    READ_FLAG(names->flags, flag_one)   ? "\n"  :
                    READ_FLAG(names->flags, flag_C)     ? " "   : "";

    for(uint8_t i = 0; i < names->dirs_count;) {
        
        names->list = malloc(sizeof(char ***) * names->dirs_count + 1);
        names->folder = opendir(names->dirs[i]);

        if(names->folder == NULL) {
            perror("Unable to read directory");
        }

        names->dirs_content = readdir(names->folder);

        if(READ_FLAG(names->flags, flag_l)) {
            mx_printstr(total(names->dirs[i]));
        }

        while(names->dirs_content) {
            stat(names->dirs_content->d_name, &names->filestat);
            
            if(READ_FLAG(names->flags, flag_l)) {
                names->list[i] = (char **) malloc(sizeof(char *) * 8);
                names->list[i][0] = permision(names->filestat);
                names->list[i][1] = link_param(names->filestat);
                names->list[i][2] = owner(names->filestat);
                names->list[i][3] = group(names->filestat);
                names->list[i][4] = size(names->filestat);
                names->list[i][5] = last_modify(names->filestat);
                names->list[i][6] = name(names->dirs_content);
                names->list[i][7] = NULL;            
            }
            else if(READ_FLAG(names->flags, flag_C)) {
                names->list[i] = (char **) malloc(sizeof(char *) * 2);
                names->list[i][0] = name(names->dirs_content);
                names->list[i][1] = NULL;
            }

            names->list[++i] = NULL;
            names->dirs_content = readdir(names->folder);
        }
    }
    
    mx_print_list(names->list, dilim1, dilim2);
}

char *total(char *dir_name) {
    DIR *folder = NULL;
    uint32_t sum = 0;
    struct dirent *entry = NULL;
    struct stat filestat;
    char *total;

    folder = opendir(dir_name);  
    
    if(folder == NULL) {   
        perror("Unable to read directory");
    }

    entry = readdir(folder);

    while(entry) {
        stat(entry->d_name, &filestat);
        sum += filestat.st_blocks;
        entry = readdir(folder);
    }
    closedir(folder);
    char *temp = mx_strjoin("total ", mx_itoa(sum));
    total = mx_strjoin(temp, "\n");
    mx_strdel(&temp);

    return total;
}
