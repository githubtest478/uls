#include "uls.h"

static void next_dir(t_names *names)
{   
    while((names->dirs_content = readdir(names->folder)) != NULL) {
        if((!mx_strcmp(names->dirs_content->d_name, ".")    ||
            !mx_strcmp(names->dirs_content->d_name, ".."))  &&
            !READ_FLAG(names->flags, flag_a)) {
            continue;
        }
        else if(!mx_strncmp(names->dirs_content->d_name, ".", 1)    &&
                !READ_FLAG(names->flags, flag_A | flag_a)) {
            continue;
        }
        else
            break;
    }
}

void count_files(t_names *names)
{
    names->folder = opendir(names->dirs[names->dirs_index]);
    names->count_file = 0;
    struct dirent *curent_dir;
    
    while((curent_dir = readdir(names->folder)))
        names->count_file++;

    closedir(names->folder);
}

void read_files_struct(t_names *names) {
    count_files(names);
    names->folder = opendir(names->dirs[names->dirs_index]);
    
    // if(names->folder == NULL) {
    //     perror("Unable to read directory");
    // }

    next_dir(names);

    if(READ_FLAG(names->flags, flag_S | flag_t | flag_c)) { 
        names->sort = (uint32_t *) malloc(sizeof(uint32_t) * names->count_file);
    }

    names->list = (char ***) malloc(sizeof(char **) * (names->count_file + 1));
    names->count_line = 0;

    while(names->dirs_content) {
        char *temp1 = mx_strjoin("/", names->dirs_content->d_name);
        char *temp2 = mx_strjoin(names->dirs[names->dirs_index], temp1);
        lstat(temp2, &names->filestat);
        fill_line(names);  

        /* Resorch
        for(uint8_t i = 0; i < 16; ++i) {
            mx_printchar(((0x8000 >> i) & names->filestat.st_mode) ? '1' : '0');
            if(!((i + 1) % 4)) {
                mx_printchar(' ');
            }
        }
        mx_printchar('\n');
        */

        next_dir(names);
        free(temp1);
        free(temp2);
    }

    closedir(names->folder);
}
