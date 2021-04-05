#include "uls.h"

static void print_total(t_names * names) {
    if(!READ_FLAG(names->flags, flag_l | flag_s))
        return;

    char *temp = mx_strjoin("total ", mx_itoa(names->total_size));
    char *total= mx_strjoin(temp, "\n");
    mx_printstr(total);
    free(temp);
    free(total);
}

void print_dirs(t_names * names)
{  
    for(names->dirs_index = 0; names->dirs_index < names->dirs_count;) {
        read_files_struct(names);

        if(names->dirs_count != 1) {
            mx_printstr(names->dirs[names->dirs_index]);
            mx_printstr(":\n");
        }

        sort(names);
        LineUp(names);
        print_total(names);
        print_list(names);

        if(++names->dirs_index != names->dirs_count) { 
            mx_printchar('\n');
        }

        delete_list(names);
    }
}
