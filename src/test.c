#include "uls.h"

void uls_algorithm(t_names *entry)
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