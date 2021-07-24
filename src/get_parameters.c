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

char *get_serial_number(t_names *names) 
{
    return mx_itoa(names->filestat.st_ino);
}

char *get_blocksize(t_names *names) 
{
    return mx_itoa(names->filestat.st_blocks);
}

char *get_permission(t_names *names)
{   
    char *permission = mx_strnew(11);

    permission[0] = S_ISDIR(names->filestat.st_mode) ? 'd' : 
                    S_ISREG(names->filestat.st_mode) ? '-' : 
                    S_ISLNK(names->filestat.st_mode) ? 'l' : 
                    S_ISBLK(names->filestat.st_mode) ? 'b' :
                    S_ISCHR(names->filestat.st_mode) ? 'c' : 
                    S_ISSOCK(names->filestat.st_mode) ? 's' : 'p';
    permission[1] = (names->filestat.st_mode & S_IRUSR) ? 'r' : '-';
    permission[2] = (names->filestat.st_mode & S_IWUSR) ? 'w' : '-';
    permission[3] = (names->filestat.st_mode & S_IXUSR) ? 'x' : '-';
    permission[4] = (names->filestat.st_mode & S_IRGRP) ? 'r' : '-';
    permission[5] = (names->filestat.st_mode & S_IWGRP) ? 'w' : '-';
    permission[6] = (names->filestat.st_mode & S_IXGRP) ? 'x' : '-';
    permission[7] = (names->filestat.st_mode & S_IROTH) ? 'r' : '-';
    permission[8] = (names->filestat.st_mode & S_IWOTH) ? 'w' : '-';
    permission[9] = (names->filestat.st_mode & S_IXOTH) ? 'x' : '-';
    permission[10] = ' ';

    return permission;
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
    struct group *pass = getgrgid(names->filestat.st_gid);
    char *result; 
    if(pass)
        result = mx_strdup(pass->gr_name);
    else
        result = mx_itoa(names->filestat.st_gid);
    return result;
}

char *get_name(t_names *names)
{
    char *file_name = NULL;

    if(READ_FLAG(names->flags, flag_link))
        file_name = mx_strdup(names->links[names->count.line]);
    else if (READ_FLAG(names->flags, flag_file)) 
        file_name = mx_strdup(names->files[names->count.line]);
    else
        file_name = mx_strdup(names->dirs_content->d_name);

    set_color(names, &file_name);
    
    if(READ_FLAG(names->flags, flag_p)) {
        if(S_ISDIR(names->filestat.st_mode)) {
            char *temp1 = mx_strjoin(file_name, "/");
            free(file_name);
            file_name = temp1;
        }
    }

    return file_name;
}

char *get_time(t_names *names)
{
    time_t time;

    if(READ_FLAG(names->flags, flag_c)) {
        time = names->filestat.st_ctime; 
    }
    else if(READ_FLAG(names->flags, flag_u)) {
        time = names->filestat.st_atime; 
    }
    else {
        time = names->filestat.st_mtime;   
    }

    char *a = ctime(&time);
    char *b = mx_strnew(21);
    
    if(READ_FLAG(names->flags, flag_T)) {
        mx_memcpy(b, a + 4, 20);
        b[20] = '\0';
    }
    else {
        mx_memcpy(b, a + 4, 7);
        mx_memcpy(b + 7, a + 20, 4);
        b[12] = '\0';
    }

    return b;
}

char* get_size(t_names *names) 
{
    if(READ_FLAG(names->flags, flag_h)) {
        uint8_t dimention = 0;
        double bite_size = names->filestat.st_size;
        char *number = NULL;
        char *dimention_symbol[] = {"B", "K", "M", "G", "T", "P", "E", "Z", "Y"};
        
        while(bite_size > 1024) {
            bite_size /= 1024;
            ++dimention;
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

        char *res = mx_strjoin(number, dimention_symbol[dimention]);
        free(number);
        return res;
    }
    else
        return mx_itoa(names->filestat.st_size);
}

char* get_link(t_names *names) {
    char *arg = NULL;

    if(READ_FLAG(names->flags, flag_link))
        arg = names->links[names->count.line];
    else if (READ_FLAG(names->flags, flag_file)) 
        arg = names->files[names->count.line];
    else
        arg = mx_path_build(names->dirs[names->count.dirs_index], "/", names->dirs_content->d_name);

    char buf[1024];
    int len = 0;

    if ((len = readlink(arg, buf, 1024)) != -1)
        buf[len] = '\0';

    if(!READ_FLAG(names->flags, flag_link | flag_file))
        free(arg);

    char *link = mx_strdup(buf);
    return link;
}
