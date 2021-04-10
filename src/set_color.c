#include "uls.h"

void set_color(t_names *names, char **file_name) {
    if(!READ_FLAG(names->flags, flag_G))
        return;

    char *temp1 = NULL;

    if(S_ISDIR(names->filestat.st_mode)) {
        temp1 = mx_strjoin(BLUE, *file_name);
    }
    else if(S_ISLNK(names->filestat.st_mode)) {
        temp1 = mx_strjoin(MAGENTA, *file_name);
    }
    else if(names->filestat.st_mode & S_IXUSR) {
        temp1 = mx_strjoin(RED, *file_name);
    }
    else {
        temp1 = mx_strjoin(LIGHT_GRAY, *file_name);
    }

    free(*file_name);
    *file_name = mx_strjoin(temp1, DEFAULT_COLLOR);
    free(temp1);
}
