#include "uls.h"

static void print_total(t_names * names) {
    if(!READ_FLAG(names->flags, flag_l | flag_s))
        return;

    char *temp = mx_strjoin("total ", mx_itoa(names->total_size));
    char *total= mx_strjoin(temp, "\n");
    mx_printstr(total);
    names->total_size = 0;
    free(temp);
    free(total);
}

static void get_recursion_dirs(t_names *names)
{
    uint16_t dirs_index = 0;
    names->recursion_dirs = (char **) malloc(sizeof(char *) * names->count.dirs + 1);
    names->count.dirs = 0;
    names->folder = opendir(names->dirs[names->count.dirs_index]);

    while((names->dirs_content = readdir(names->folder))) {
        if(names->dirs_content->d_type == DT_DIR && names->dirs_content->d_name[0] != '.') {   
            char *dir_path1 = mx_strjoin("/", names->dirs_content->d_name);
            char *dir_path2 = mx_strjoin(names->dirs[names->count.dirs_index], dir_path1);
            free(dir_path1);
            names->recursion_dirs[dirs_index++] = dir_path2;
            names->recursion_dirs[dirs_index] = NULL;
        }
    }

    closedir(names->folder);
}

void print_dirs(t_names * names)
{  
    char **local_temp = NULL;

    if(READ_FLAG(names->flags, flag_R) && names->count.dirs) {
        get_recursion_dirs(names);
        local_temp = names->dirs;
        names->dirs = names->recursion_dirs; 
    }

    for(uint16_t dirs_index = 0; names->dirs[dirs_index];) {
        names->count.dirs_index = dirs_index;
        read_files_struct(names);

        if(names->dirs[dirs_index + 1] || names->count.recursion || dirs_index) {
            mx_printstr(names->dirs[dirs_index]);
            mx_printstr(":\n");
        }

        sort(names);

        print_total(names);
        LineUp(names);
        
        if(READ_FLAG(names->flags, flag_C | flag_x)) {
            multicolumn(names);
        }
        else {
            print_list(names);
        }

        if(names->dirs[++dirs_index] || names->count.dirs) { 
            mx_printchar('\n');
        }

        delete_list(names);
        
        if(READ_FLAG(names->flags, flag_R) && names->count.dirs) {
            ++names->count.recursion;
            print_dirs(names);
            --names->count.recursion;
        }
    }

    // for(uint16_t index = 0; names->dirs[index]; ) {
    //     mx_strdel(&names->dirs[index++]);
    // }
    
    if(local_temp) {
        names->dirs = local_temp;
    }
}
