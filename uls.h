#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>



// структура для флагов
typedef struct s_flags {
    bool l;

}              t_flags;



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








// LIBMX function
int mx_strlen(const char *s);








