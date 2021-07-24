#include "uls.h"

static void count_input_args(int argn, char **argv, t_names *names)
{
    for(uint8_t index = 1; index < argn; ++index) {
        if(lstat(argv[index], &names->filestat) == -1) {
            continue;
        }
        else if(S_ISDIR(names->filestat.st_mode) && (names->filestat.st_mode & S_IRUSR)) {
            names->count.dirs++;
        }
        else if(S_ISREG(names->filestat.st_mode))
            names->count.files++;
        else if(S_ISLNK(names->filestat.st_mode))
            names->count.links++;
    }

    if(names->count.dirs) {
        names->dirs = (char **) malloc(sizeof(char *) * (names->count.dirs + 1));
        names->count.dirs = 0;
    }

    if(names->count.files) {
        names->files = (char **) malloc(sizeof(char *) * (names->count.files + 1));
        names->count.files = 0;
    }

    if(names->count.links) {
        names->links = (char **) malloc(sizeof(char *) * (names->count.links + 1));
        names->count.links = 0;
    }
}

static void read_args(int argn, char **argv, t_names *names)
{
    uint8_t i = 1;
    for(; i < argn; ++i) {
        if(!mx_strncmp(argv[i], "-", 1)) {
            for(int j = 1; argv[i][j]; ++j) {
                set_flags(names, argv[i][j]);
            }
        }
        else
            break;
    }

    while(i < argn) {

        if(lstat(argv[i], &names->filestat) == -1) {
            write(STDERR_FILENO, "uls: ", mx_strlen("uls: "));
            perror(argv[i++]);
            names->count.status = 1;
        } else if(S_ISDIR(names->filestat.st_mode)) {
            if(!(names->filestat.st_mode & S_IRUSR)) {
                write(STDERR_FILENO, "uls: ", mx_strlen("uls: "));
                write(STDERR_FILENO, argv[i], mx_strlen(argv[i]));
                write(STDERR_FILENO, ": Permission denied\n", mx_strlen(": Permission denied\n"));
                ++i;
                names->count.status = 1;
                continue;
            }
            names->dirs[names->count.dirs++] = mx_strdup(argv[i++]);
            names->dirs[names->count.dirs] = NULL;
        }
        else if(S_ISREG(names->filestat.st_mode)) {
            names->files[names->count.files++] = mx_strdup(argv[i++]);
            names->files[names->count.files] = NULL;
        }
        else if(S_ISLNK(names->filestat.st_mode)) {
            names->links[names->count.links++] = mx_strdup(argv[i++]);
            names->links[names->count.links] = NULL;
        }
    }
}

void arg_validation(int argn, char **argv, t_names *names)
{
    if (argn > 1) {
        count_input_args(argn, argv, names);
        read_args(argn, argv, names);
    }

    if(!names->count.dirs && !names->count.status && !names->count.files && !names->count.links) {
        names->dirs = (char **) malloc(sizeof(char *) * 2);
        names->dirs[names->count.dirs++] = ".";
        names->dirs[names->count.dirs] = NULL;
    }

    names->count.dirs = 0;
}
