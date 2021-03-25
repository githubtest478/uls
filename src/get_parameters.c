#include "uls.h"

char *permision(struct stat filestat)
{   
    char *permision = mx_strnew(10);
    
    permision[0] = S_ISDIR(filestat.st_mode) ? 'd' : '-';
    permision[1] = (filestat.st_mode & S_IRUSR) ? 'r' : '-';
    permision[2] = (filestat.st_mode & S_IWUSR) ? 'w' : '-';
    permision[3] = (filestat.st_mode & S_IXUSR) ? 'x' : '-';
    permision[4] = (filestat.st_mode & S_IRGRP) ? 'r' : '-';
    permision[5] = (filestat.st_mode & S_IWGRP) ? 'w' : '-';
    permision[6] = (filestat.st_mode & S_IXGRP) ? 'x' : '-';
    permision[7] = (filestat.st_mode & S_IROTH) ? 'r' : '-';
    permision[8] = (filestat.st_mode & S_IWOTH) ? 'w' : '-';
    permision[9] = (filestat.st_mode & S_IXOTH) ? 'x' : '-';

    return permision;
}

char *link_param(struct stat filestat)
{
    return mx_itoa(filestat.st_nlink);
}

char *owner(struct stat filestat)
{
    struct passwd *pass = getpwuid(filestat.st_uid);
    return mx_strdup(pass->pw_name);
}

char *group(struct stat filestat)
{
    return mx_itoa(filestat.st_gid);
}

char *size(struct stat filestat)
{
    return mx_itoa(filestat.st_size); 
}

char *last_modify(struct stat filestat)
{
    time_t modify_time = filestat.st_mtime; 
    char *a = ctime(&modify_time);  
    return mx_strndup(a + 4, 12);
}

char *name(struct dirent *entry)
{
    return mx_strdup(entry->d_name);
}
