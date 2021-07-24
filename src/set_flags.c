#include "uls.h"

void set_flags(t_names *names, char c)
{
    if(c == '@') {
        SET_FLAG(names->flags, flag_At);
    }
    else if(c == '1') {
        RESET_FLAG(names->flags, flag_m | flag_x | flag_C | flag_l);
        SET_FLAG(names->flags, flag_one);
    }
    else if(c == 'A') {
        SET_FLAG(names->flags, flag_A);
    }
    else if(c == 'a') {
        RESET_FLAG(names->flags, flag_A);
        SET_FLAG(names->flags, flag_a);
    }
    else if(c == 'C') {
        RESET_FLAG(names->flags, flag_x | flag_l | flag_m | flag_one);
        SET_FLAG(names->flags, flag_C);
    }
    else if(c == 'c') {
        SET_FLAG(names->flags, flag_c);
    }
    else if(c == 'e') {
        SET_FLAG(names->flags, flag_e);
    }
    else if(c == 'G') {
        SET_FLAG(names->flags, flag_G);
    }
    else if(c == 'h') {
        SET_FLAG(names->flags, flag_h);
    }
    else if(c == 'l') {
        RESET_FLAG(names->flags, flag_x | flag_m | flag_C);
        SET_FLAG(names->flags, flag_l | flag_one);
    }
    else if(c == 'R') {
        SET_FLAG(names->flags, flag_R);
    }
    else if(c == 'r') {
        RESET_FLAG(names->flags, flag_t | flag_S);
        SET_FLAG(names->flags, flag_r);
    }
    else if(c == 'S') {
        RESET_FLAG(names->flags, flag_r | flag_S);
        SET_FLAG(names->flags, flag_S);
    }
    else if(c == 'T') {
        SET_FLAG(names->flags, flag_T);
    }
    else if(c == 't') {
        RESET_FLAG(names->flags, flag_S | flag_r);
        SET_FLAG(names->flags, flag_t);
    }
    else if(c == 'u') {
        SET_FLAG(names->flags, flag_u);
    }
    else if(c == 'f') {
        RESET_FLAG(names->flags, flag_t | flag_S | flag_r);
        SET_FLAG(names->flags, flag_f | flag_a);
    }
    else if(c == 'i') {
        SET_FLAG(names->flags, flag_i);
    }
    else if(c == 'x') {
        RESET_FLAG(names->flags, flag_C | flag_l | flag_one | flag_m);
        SET_FLAG(names->flags, flag_x);
    }
    else if(c == 'p') {
        SET_FLAG(names->flags, flag_p);
    }
    else if(c == 'm') {
        RESET_FLAG(names->flags, flag_one | flag_l | flag_C | flag_x);
        SET_FLAG(names->flags, flag_m);
    }
    else if(c == 's') {
        SET_FLAG(names->flags, flag_s);
    }
    else {
        write(STDERR_FILENO, "uls: illegal option -- ", mx_strlen("uls: illegal option -- "));
        mx_printchar(c), mx_printchar('\n');
        write(STDERR_FILENO, USAGE, mx_strlen(USAGE));
        exit(1);
    }
}
