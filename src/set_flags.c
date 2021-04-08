#include "uls.h"

void set_flags(t_names *names, char c)
{
    if(c == '@') {
        SET_FLAG(names->flags, flag_At);
    }
    else if(c == '1') { //the same grup as -1 -m -l -m
        RESET_FLAG(names->flags, flag_m | flag_x | flag_C | flag_l);
        SET_FLAG(names->flags, flag_one);
    }
    else if(c == 'A') { //the same grup as -a -A
        SET_FLAG(names->flags, flag_A);
    }
    else if(c == 'a') { //the same grup as -a -A
        RESET_FLAG(names->flags, flag_A);
        SET_FLAG(names->flags, flag_a);
    }
    else if(c == 'C') { //the same grup as -x -C -l -m
        RESET_FLAG(names->flags, flag_x | flag_l | flag_m | flag_one);
        SET_FLAG(names->flags, flag_C);
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
        RESET_FLAG(names->flags, flag_x | flag_m | flag_C);
        SET_FLAG(names->flags, flag_l | flag_one);
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
        SET_FLAG(names->flags, flag_t);
    }
    else if(c == 'u') {
        SET_FLAG(names->flags, flag_u);
    }
    else if(c == 'f') { //sort grup -c -r -t -S -f
        RESET_FLAG(names->flags, SORT_MASK); //optional set -s
        SET_FLAG(names->flags, flag_f | flag_a); //optional set -U
    }
    else if(c == 'i') {
        SET_FLAG(names->flags, flag_i);
    }
    else if(c == 'x') { //the same grup as -x -C -l -m
        RESET_FLAG(names->flags, flag_C | flag_l | flag_one | flag_m);
        SET_FLAG(names->flags, flag_x);
    }
    else if(c == 'p') {
        SET_FLAG(names->flags, flag_p);
    }
    else if(c == 'm') { //the same grup as -1 -m -l
        RESET_FLAG(names->flags, flag_one | flag_l);
        SET_FLAG(names->flags, flag_m);
    }
    else if(c == 's') {
        SET_FLAG(names->flags, flag_s);
    }
    else {
        perror(USAGE); //error flag didn't exist
        exit(1);
    }
}

//debug function
void print_set_flags(t_names *names)
{
    for(uint32_t i = 0; i < 24; ++i) {
        uint32_t flag = names->flags & 1 << i;
        if(!!flag) {
            switch(flag) {
                case flag_At:
                    mx_printstr("flag_At\n");
                    break;
                case flag_one:
                    mx_printstr("flag_one\n");
                    break;
                case flag_A:
                    mx_printstr("flag_A\n");
                    break;
                case flag_a:
                    mx_printstr("flag_a\n");
                    break;
                case flag_C:
                    mx_printstr("flag_C\n");
                    break;
                case flag_c:
                    mx_printstr("flag_c\n");
                    break;
                case flag_e:
                    mx_printstr("flag_e\n");
                    break;
                case flag_G:
                    mx_printstr("flag_G\n");
                    break;
                case flag_h:
                    mx_printstr("flag_h\n");
                    break;
                case flag_l:
                    mx_printstr("flag_l\n");
                    break;
                case flag_R:
                    mx_printstr("flag_R\n");
                    break;
                case flag_r:
                    mx_printstr("flag_r\n");
                    break;
                case flag_S:
                    mx_printstr("flag_S\n");
                    break;
                case flag_T:
                    mx_printstr("flag_T\n");
                    break;
                case flag_t:
                    mx_printstr("flag_t\n");
                    break;
                case flag_u:
                    mx_printstr("flag_u\n");
                    break;
                case flag_f:
                    mx_printstr("flag_f\n");
                    break;
                case flag_i:
                    mx_printstr("flag_i\n");
                    break;
                case flag_x:
                    mx_printstr("flag_x\n");
                    break;
                case flag_p:
                    mx_printstr("flag_p\n");
                    break;
                case flag_m:
                    mx_printstr("flag_m\n");
                    break;
                case flag_s:
                    mx_printstr("flag_s\n");
                    break;
                    
                default:
                    break;
            }
        }
    }
}
