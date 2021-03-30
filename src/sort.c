#include "uls.h"

static void sort_by_alphabet(t_names *names)
{
    uint8_t index = 0;
    index += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    index += READ_FLAG(names->flags, flag_i);
    for(uint16_t j = 0; j < names->count_file; ++j) {
        for(uint16_t i = 0; i < names->count_file - 1; ++i) {
            if(READ_FLAG(names->flags, flag_r) ? 
                mx_strcmp(names->list[i][index], names->list[i + 1][index]) > 0 : 
                mx_strcmp(names->list[i][index], names->list[i + 1][index]) < 0) {
                char** temp = names->list[i];
                names->list[i] = names->list[i + 1];
                names->list[i + 1] = temp;
            }
        }
    }
}

static void sort_by_time(t_names *names)
{

}

static void sort_by_size(t_names *names)
{
    uint8_t index = 0;
    index += READ_FLAG(names->flags, flag_l) ? 4 : 5;
    index += READ_FLAG(names->flags, flag_i);

    for(uint16_t j = 0; j < names->count_file; ++j) {
        for(uint16_t i = 0; i < names->count_file - 1; ++i) {
            if(mx_atoi(names->list[i][index]) < mx_atoi(names->list[i + 1][index])) {
                char** temp = names->list[i];
                names->list[i] = names->list[i + 1];
                names->list[i + 1] = temp;
            }
        }
    }
}

void sort(t_names *names)
{
    if(READ_FLAG(names->flags, flag_f)) {
        return;
    }
    else if(READ_FLAG(names->flags, flag_r | flag_C)) {
        sort_by_alphabet(names); 
    }
    else if(READ_FLAG(names->flags, flag_t | flag_c)) {
        sort_by_time(names);
    }
    else if(READ_FLAG(names->flags, flag_S)) {
        sort_by_size(names);
    }
}   
