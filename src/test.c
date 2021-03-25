#include "uls.h"

void uls_algorithm(t_names *s_names)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if(dir == NULL) {
        perror("uls: ");
    }
    if(isatty(STDOUT_FILENO)) {
        while((entry = readdir(dir)) != NULL) { 
            if(entry->d_name[0] != '.') {
                mx_printstr(entry->d_name);
                mx_printstr(" ");
            }
        }
        mx_printstr("\n");
    }
    else {
        while((entry = readdir(dir)) != NULL) { 
            if(entry->d_name[0] != '.') {
                mx_printstr(entry->d_name);
                mx_printstr("\n");
            }
        }
    }
    closedir(dir);
}

/* 
считает количество выделеной памяти для дирекрории 
*/

char *total_count(char *dir_name) {
    DIR *folder = NULL;
    uint32_t sum = 0;
    struct dirent *entry = NULL;
    struct stat filestat;
    char *total;

    folder = opendir(dir_name);  
    
    if(folder == NULL) {   
        perror("Unable to read directory");
    }

    entry = readdir(folder);

    while(entry) {
        stat(entry->d_name, &filestat);
        sum += filestat.st_blocks;
        entry = readdir(folder);
    }
    closedir(folder);
    char *temp = mx_strjoin("total ", mx_itoa(sum));
    total = mx_strjoin(temp, "\n");
    mx_strdel(&temp);

    return total;
}

/*вывод аналогочный ls -l нужно модифицировать под разные флаги и дирекрории, выводит содержимое !!!ТЕКУЩЕЙ дирекрории но можно передавать просто имя.*/
void mx_test_open_curent_dir(t_names *names) 
{
    DIR *folder = NULL;
    struct dirent *entry = NULL;
    struct stat filestat;
    char *temporary = NULL;

    mx_printstr("total ");
    temporary = total(".");    // must free
    mx_printstr(temporary);   
    free(temporary);           // free

    mx_printstr("\n");

    folder = opendir(".");

    if(folder == NULL) // ERROR
    {
        perror("Unable to read directory");
    }
    /* Read directory entries */
    entry = readdir(folder);

    while(entry)
    {
        if(entry->d_name[0] != '.') {
            stat(entry->d_name, &filestat);

            mx_printstr( S_ISDIR(filestat.st_mode) ? "d" : "-");
            mx_printstr( (filestat.st_mode & S_IRUSR) ? "r" : "-");
            mx_printstr( (filestat.st_mode & S_IWUSR) ? "w" : "-");
            mx_printstr( (filestat.st_mode & S_IXUSR) ? "x" : "-");
            mx_printstr( (filestat.st_mode & S_IRGRP) ? "r" : "-");
            mx_printstr( (filestat.st_mode & S_IWGRP) ? "w" : "-");
            mx_printstr( (filestat.st_mode & S_IXGRP) ? "x" : "-");
            mx_printstr( (filestat.st_mode & S_IROTH) ? "r" : "-");
            mx_printstr( (filestat.st_mode & S_IWOTH) ? "w" : "-");
            mx_printstr( (filestat.st_mode & S_IXOTH) ? "x" : "-");
            mx_printstr(" ");
          
            temporary = mx_itoa(filestat.st_nlink); // must free mx_itoa
            mx_printstr(temporary);       
            free(temporary);             // free
            mx_printstr(" ");
          
            struct passwd *pass = getpwuid(filestat.st_uid);
            mx_printstr(pass->pw_name);
            mx_printstr(" ");
                 
            temporary = mx_itoa(filestat.st_gid);       // must free mx_itoa
            mx_printstr(temporary);          
            free(temporary);            // free
            mx_printstr(" ");

            temporary = mx_itoa(filestat.st_size);       // must free mx_itoa
            mx_printstr(temporary);        
            free(temporary);             // free
            mx_printstr(" ");

            time_t modify_time = filestat.st_mtime; 
            char *a = ctime(&modify_time);  
            write(1, (a + 4), 12);
            mx_printstr(" ");
            mx_printstr(entry->d_name);
            mx_printstr("\n");
        }
        entry = readdir(folder);
    }
    closedir(folder);
}
