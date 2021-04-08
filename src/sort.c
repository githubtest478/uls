#include "uls.h"

static void sort_by_alphabet(t_names *names)
{
    uint8_t offset = READ_FLAG(names->flags, flag_G) ? 4 : 0;
    uint8_t index = 0;
    index += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    index += READ_FLAG(names->flags, flag_i);
    index += READ_FLAG(names->flags, flag_s);

    for(uint16_t j = 0; j < names->count.line; ++j) {
        for(uint16_t i = 0; i < names->count.line - 1; ++i) {
            if(READ_FLAG(names->flags, flag_r) ? 
                mx_strcmp(&names->list[i][index][offset], &names->list[i + 1][index][offset]) < 0 : 
                mx_strcmp(&names->list[i][index][offset], &names->list[i + 1][index][offset]) > 0) {
                char** temp = names->list[i];
                names->list[i] = names->list[i + 1];
                names->list[i + 1] = temp;
            }
        }
    }
}

static void size_sort(t_names *names)
{
    for (uint32_t i = 0; i < names->count.line; i++) {
        for (uint32_t j = 0; j < names->count.line - 1; j++) {
            if (names->sort[j] < names->sort[j + 1]) {
                uint64_t temp_uint = names->sort[j];
                char** temp = names->list[j];
                names->sort[j] = names->sort[j + 1];
                names->list[j] = names->list[j + 1];
                names->sort[j + 1] = temp_uint;
                names->list[j + 1] = temp;
            }
        }
    }

    free(names->sort);
    names->sort = NULL;
}

static void time_sort(t_names *names)
{
    for (uint32_t i = 0; i < names->count.line; i++) {
        for (uint32_t j = 0; j < names->count.line - 1; j++) {
            if (/*  Unknown condition    */0) {
                time_t temp_time = names->time_sort[j + 1];
                char** temp = names->list[j];
                names->list[j + 1] = names->list[j];
                names->time_sort[j + 1] = names->time_sort[j];
                names->list[j] = temp;
                names->time_sort[j] = temp_time;
            }
        }
    }

    free(names->time_sort);
    names->time_sort = NULL;
}


void sort(t_names *names)
{
    if(READ_FLAG(names->flags, flag_f)) {
        return;
    }
    else if(READ_FLAG(names->flags, flag_S)) {
        size_sort(names);
    }
    else if(READ_FLAG(names->flags, flag_t)) {
        time_sort(names);
    }
    else {
        sort_by_alphabet(names); 
    }
}   
