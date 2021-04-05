#include "uls.h"

char *serial_number(t_names *names) 
{
    return mx_itoa(names->filestat.st_ino);
}

char *blocksize(t_names *names) 
{
    return mx_itoa(names->filestat.st_blocks);
}

char *permision(t_names *names)
{   
    char *permision = mx_strnew(11);

    permision[0] = S_ISLNK(names->filestat.st_mode) ? 'l' : 
                   S_ISDIR(names->filestat.st_mode) ? 'd' : 
                   S_ISREG(names->filestat.st_mode) ? '-' : '?';
    permision[1] = (names->filestat.st_mode & S_IRUSR) ? 'r' : '-';
    permision[2] = (names->filestat.st_mode & S_IWUSR) ? 'w' : '-';
    permision[3] = (names->filestat.st_mode & S_IXUSR) ? 'x' : '-';
    permision[4] = (names->filestat.st_mode & S_IRGRP) ? 'r' : '-';
    permision[5] = (names->filestat.st_mode & S_IWGRP) ? 'w' : '-';
    permision[6] = (names->filestat.st_mode & S_IXGRP) ? 'x' : '-';
    permision[7] = (names->filestat.st_mode & S_IROTH) ? 'r' : '-';
    permision[8] = (names->filestat.st_mode & S_IWOTH) ? 'w' : '-';
    permision[9] = (names->filestat.st_mode & S_IXOTH) ? 'x' : '-';
    permision[10] = S_ISSOCK(names->filestat.st_mode) ? '@' : ' ';
    
    return permision;
}

char *link_param(t_names *names)
{
    return mx_itoa(names->filestat.st_nlink);
}

char *owner(t_names *names)
{
    struct passwd *pass = getpwuid(names->filestat.st_uid);
    return mx_strdup(pass->pw_name);
}

char *group(t_names *names)
{
    return mx_itoa(names->filestat.st_gid);
}

char *name(t_names *names)
{
    return mx_strdup(names->dirs_content->d_name);
}

char *get_time(t_names *names)
{
    time_t modify_time = 0;

    if(READ_FLAG(names->flags, flag_C)){
        modify_time = names->filestat.st_ctime;   
    }
    else if(READ_FLAG(names->flags, flag_c)) {
        modify_time = names->filestat.st_ctime; 
    }

    char *a = ctime(&modify_time);
    return mx_strndup(a + 4, 12); 
} 

char* get_size(t_names *names) 
{
    if(READ_FLAG(names->flags, flag_h)) {
        uint64_t bite_size = names->filestat.st_size;
        char *temp1 = NULL;
        char *dimension = NULL;

        if(bite_size < 1024) {
            temp1 = mx_itoa(bite_size);
            dimension = "B";
        }
        else { 
            char *temp2 = NULL;
            char *temp3 = NULL;

            if(bite_size < 1048576) {
                double res = (bite_size % 1024) / 102.4;
                temp2 = mx_itoa(res);
                temp3 = mx_itoa(bite_size / 1024);
                dimension = "K";
            }  
            else if(bite_size < 1073741824) {
                double res = (bite_size % 1048576) / 104857.6;
                temp2 = mx_itoa(res);
                temp3 = mx_itoa(bite_size / 1048576);
                dimension = "M";
            }
            else if(bite_size < 1099511627776) {
                double res = (bite_size % 1073741824);
                temp2 = mx_itoa(res);
                temp3 = mx_itoa(bite_size / 1073741824);
                dimension = "G";
            }
            char *temp4 = mx_strjoin(temp3, ".");
            temp1 = mx_strjoin(temp4, temp2);
            free(temp2);
            free(temp3);
            free(temp4);
        }

        char *res = mx_strjoin(temp1, dimension);
        free(temp1);
        return res;
    }
    else
        return mx_itoa(names->filestat.st_size); 
}
