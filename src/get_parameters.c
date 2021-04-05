#include "uls.h"

static int32_t round_bytes(double num)
{
    bool msb = 0;
    int32_t integer_num = (num * 10);

    msb = integer_num % 10 >= 5;
    integer_num /= 10;
    integer_num += msb;

    return integer_num;
}

static char *str_char_join(char const *s, char const c)
{
    if(s == NULL) {
        char *new_str = mx_strnew(1);
        new_str[0] = c;
        return new_str;
    }

    char *new_str = mx_strnew(mx_strlen(s) + 1);
    
    if(!new_str)
        return NULL;

    new_str = mx_strcpy(new_str, s);
    new_str[mx_strlen(s)] = c;
    return new_str;
}

char *get_serial_number(t_names *names) 
{
    return mx_itoa(names->filestat.st_ino);
}

char *get_blocksize(t_names *names) 
{
    return mx_itoa(names->filestat.st_blocks);
}

char *get_permision(t_names *names)
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
    permision[10] = S_ISSOCK(names->filestat.st_mode)  ? '@' : ' '; //need to be modify
    
    return permision;
} 

char *get_link_param(t_names *names)
{
    return mx_itoa(names->filestat.st_nlink);
}

char *get_owner(t_names *names)
{
    struct passwd *pass = getpwuid(names->filestat.st_uid);
    return mx_strdup(pass->pw_name);
}

char *get_group(t_names *names)
{
    return mx_itoa(names->filestat.st_gid);
}

char *get_name(t_names *names)
{
    char *file_name = mx_strdup(names->dirs_content->d_name);

    if(READ_FLAG(names->flags, flag_G)) {
        char *temp1 = NULL;

        if(S_ISDIR(names->filestat.st_mode)) {
            temp1 = mx_strjoin(BLUE, file_name);
        }
        else if(S_ISLNK(names->filestat.st_mode)) {
            temp1 = mx_strjoin(MAGENTA, file_name);
        }
        else if(names->filestat.st_mode & S_IXUSR) {
            temp1 = mx_strjoin(RED, file_name);
        }
        else {
            temp1 = mx_strjoin(LIGHT_GRAY, file_name);
        }

        free(file_name);
        file_name = mx_strjoin(temp1, DEFAULT_COLLOR);
        free(temp1);
    }
    
    return file_name;
}

char *get_time(t_names *names)
{
    time_t time;

    if(READ_FLAG(names->flags, flag_C)){
        time = names->filestat.st_ctime;   
    }
    else if(READ_FLAG(names->flags, flag_c)) {
        time = names->filestat.st_ctime; 
    }

    char *a = ctime(&time);
    return mx_strndup(a + 4, 12); 
} //work incorect!!! need to be remastered 

char* get_size(t_names *names) 
{
    if(READ_FLAG(names->flags, flag_h)) {
        uint8_t iteration = 0;
        double bite_size = names->filestat.st_size;
        char *number = NULL;
        char *dimention = "BKMGTPEZY";

        while(bite_size > 1024) {
            bite_size /= 1024;
            ++iteration;
        }

        if(bite_size < 10) {
            uint64_t round = round_bytes(bite_size * 10);
            char *integer = mx_itoa(round / 10);
            char *fraction = mx_itoa(round % 10);
            char *integer_dot = mx_strjoin(integer, ".");
            number = mx_strjoin(integer_dot, fraction);
            free(integer);
            free(fraction);
            free(integer_dot);
        }
        else {
            uint64_t round = round_bytes(bite_size);
            number = mx_itoa(round);
        }

        char *res = str_char_join(number, dimention[iteration]);
        free(number);
        return res;
    }
    else
        return mx_itoa(names->filestat.st_size);
}
