#include "uls.h"

char *serial_number(t_names *names) 
{
    return mx_itoa(names->filestat.st_ino);
}

char *permision(t_names *names)
{   
    char *permision = mx_strnew(10);
    
    permision[0] = S_ISDIR(names->filestat.st_mode) ? 'd' : '-';
    permision[1] = (names->filestat.st_mode & S_IRUSR) ? 'r' : '-';
    permision[2] = (names->filestat.st_mode & S_IWUSR) ? 'w' : '-';
    permision[3] = (names->filestat.st_mode & S_IXUSR) ? 'x' : '-';
    permision[4] = (names->filestat.st_mode & S_IRGRP) ? 'r' : '-';
    permision[5] = (names->filestat.st_mode & S_IWGRP) ? 'w' : '-';
    permision[6] = (names->filestat.st_mode & S_IXGRP) ? 'x' : '-';
    permision[7] = (names->filestat.st_mode & S_IROTH) ? 'r' : '-';
    permision[8] = (names->filestat.st_mode & S_IWOTH) ? 'w' : '-';
    permision[9] = (names->filestat.st_mode & S_IXOTH) ? 'x' : '-';

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

char *size(t_names *names)
{
    return mx_itoa(names->filestat.st_size); 
}

char *last_modify(t_names *names)
{
    time_t modify_time = names->filestat.st_mtime; 
    char *a = ctime(&modify_time);  
    return mx_strndup(a + 4, 12);
}

char *last_created(t_names *names)
{
    time_t modify_time = names->filestat.st_mtime; 
    char *a = ctime(&modify_time);  
    return mx_strndup(a + 4, 12);
}//need to be developed

char *name(t_names *names)
{
    return mx_strdup(names->dirs_content->d_name);
}
