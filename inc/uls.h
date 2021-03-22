#ifndef ULS_H
#define ULS_H //#include "uls.h"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libmx.h"
#include <stdint.h>

// структура для флагов
typedef struct s_flags {
    bool l;
}              t_flags;

// структура для файлов и директорий
typedef struct s_names {
    char **names;
    int count;
}              t_names;

/*
#define USAGE "usage: uls [-l] [file ...]\n"
*/

// ARGC_ARGV    process
int mx_count_flags(int argc, char **argv);
void mx_process_argc_argv(int argc, char **argv);

// FLAG HANDLE
t_flags *mx_process_flags(int flags_count, char **argv);
void mx_check_flags_in_str(char *str, t_flags *flags);
void mx_check_flag(char flag, t_flags *flags);

// ARGV HANDLE
t_names *mx_process_names(int flags_count, int argc, char **argv);

// LIBMX function
int mx_strlen(const char *s);
char *mx_strcpy(char *dst, const char *src);

#endif /* ULS_H */
