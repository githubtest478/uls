#include "uls.h"

void set_flags(t_names *names, char c)
{
    if(c == '@') {
        SET_FLAG(names->flags, flag_At);
    }
    else if(c == '1') { //the same grup as -1 -m -l -m
        RESET_FLAG(names->flags, flag_m | flag_x);
        SET_FLAG(names->flags, flag_one);
    }
    else if(c == 'A') { //the same grup as -a -A
        RESET_FLAG(names->flags, flag_a);
        SET_FLAG(names->flags, flag_A);
    }
    else if(c == 'a') { //the same grup as -a -A
        RESET_FLAG(names->flags, flag_A);
        SET_FLAG(names->flags, flag_a);
    }
    else if(c == 'C') { //the same grup as -x -C -l -m
        RESET_FLAG(names->flags, flag_x | flag_l | flag_m | flag_one);
        SET_FLAG(names->flags, flag_C | flag_a);
    }
    else if(c == 'c') { //sort grup -c -r -t -S -f
        RESET_FLAG(names->flags, SORT_MASK);
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
    else if(c == 'l') { //the same grup as -x -C -l -1 -m
        RESET_FLAG(names->flags, flag_x | flag_m);
        SET_FLAG(names->flags, flag_l | flag_one | flag_C);
    }
    else if(c == 'R') {
        SET_FLAG(names->flags, flag_R);
    }
    else if(c == 'r') { //sort grup -c -r -t -S -f
        RESET_FLAG(names->flags, SORT_MASK);
        SET_FLAG(names->flags, flag_r);
    }
    else if(c == 'S') { //sort grup -c -r -t -S -f
        RESET_FLAG(names->flags, SORT_MASK);
        SET_FLAG(names->flags, flag_S);
    }
    else if(c == 'T') {
        SET_FLAG(names->flags, flag_T);
    }
    else if(c == 't') { //sort grup -c -r -t -S -f
        RESET_FLAG(names->flags, SORT_MASK);
        SET_FLAG(names->flags, flag_t);
    }
    else if(c == 'u') {
        SET_FLAG(names->flags, flag_u);
    }
    else if(c == 'f') { //sort grup -c -r -t -S -f
        RESET_FLAG(names->flags, SORT_MASK | flag_l); //optional set -s
        SET_FLAG(names->flags, flag_f | flag_a); //optional set -U
    }
    else if(c == 'i') {
        SET_FLAG(names->flags, flag_i);
    }
    else if(c == 'x') { //the same grup as -x -C -l -m
        RESET_FLAG(names->flags, flag_C | flag_l | flag_one | flag_m);
        SET_FLAG(names->flags, flag_x | flag_C);
    }
    else if(c == 'p') {
        SET_FLAG(names->flags, flag_p);
    }
    else if(c == 'm') { //the same grup as -1 -m -l
        RESET_FLAG(names->flags, flag_one | flag_l);
        SET_FLAG(names->flags, flag_m);
    }
    else {
        perror(USAGE); //error flag didn't exist
        exit(1);
    }
    //printf("Flag: %d\n", names->flags);
}
