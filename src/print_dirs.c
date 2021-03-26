#include "uls.h"

void print_dirs(t_names * names)
{

    char *dilim1 =  READ_FLAG(names->flags, flag_l | flag_i)     ? " "   : "";
    char *dilim2 =  READ_FLAG(names->flags, flag_m)     ? ", "  :
                    READ_FLAG(names->flags, flag_one)   ? "\n"  :
                    READ_FLAG(names->flags, flag_C)     ? " "   : "";

    for(uint8_t i = 0; i < names->dirs_count;) {
        
        names->list = malloc(sizeof(char ***) * 6);
        names->folder = opendir(names->dirs[i]);

        if(names->folder == NULL) {
            perror("Unable to read directory");
        }

        names->dirs_content = readdir(names->folder);

        if(READ_FLAG(names->flags, flag_l)) {
            mx_printstr(total(names));
        }

        while(names->dirs_content) {
            stat(names->dirs_content->d_name, &names->filestat);
            uint8_t count = 0;
            uint8_t list_size = 2;
            list_size += READ_FLAG(names->flags, flag_l) ? 6 : 0;
            list_size += READ_FLAG(names->flags, flag_i);

            names->list[i] = (char **) malloc(sizeof(char *) * list_size);
            names->file_count++;

            // if(names->file_count > malloc_size(names->list) / sizeof(char***)) {
            //     names->list = realloc(names->list, names->file_count * sizeof(char***));
            // }

            if(READ_FLAG(names->flags, flag_i)) {
                names->list[i][count++] = serial_number(names->filestat);
            }

            if(READ_FLAG(names->flags, flag_l)) {
                names->list[i][count++] = permision(names->filestat);   //0
                names->list[i][count++] = link_param(names->filestat);  //1
                names->list[i][count++] = owner(names->filestat);       //2
                names->list[i][count++] = group(names->filestat);       //3
                names->list[i][count++] = size(names->filestat);        //4
                names->list[i][count++] = last_modify(names->filestat); //5
            }
            names->list[i][count++] = name(names->dirs_content);        //6
            names->list[i][count++] = NULL;                             //7

            names->list[++i] = NULL;
            names->dirs_content = readdir(names->folder);
        }
        sort_by_alpgaber(names);
        mx_print_list(names->list, dilim1, dilim2);
    }
}

// char *total(char *dir_name) {
//     DIR *folder = NULL;
//     uint32_t sum = 0;
//     struct dirent *entry = NULL;
//     struct stat filestat;
//     char *total;

//     folder = opendir(dir_name);  
    
//     if(folder == NULL) {   
//         perror("Unable to read directory");
//     }

//     entry = readdir(folder);

//     while(entry) {
//         stat(entry->d_name, &filestat);
//         sum += filestat.st_blocks;
//         entry = readdir(folder);
//     }
//     closedir(folder);
//     char *temp = mx_strjoin("total ", mx_itoa(sum));
//     total = mx_strjoin(temp, "\n");
//     mx_strdel(&temp);

//     return total;
// }

char *total(t_names * names) {
    uint32_t sum = 0;
    char *total;

    int i = 0, count = READ_FLAG(names->flags, flag_i) ? 5 : 4;
    while(names->list[i] != NULL) {
        sum += mx_atoi(names->list[i][count]);
        ++i;
    }
    char *temp = mx_strjoin("total ", mx_itoa(sum));
    total = mx_strjoin(temp, "\n");
    mx_strdel(&temp);

    return total;
}
