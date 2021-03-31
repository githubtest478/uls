#include "uls.h"

static void sort_by_alphabet(t_names *names)
{
    uint8_t index = 0;
    index += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    index += READ_FLAG(names->flags, flag_i);

    for(uint16_t j = 0; j < names->count_line; ++j) {
        for(uint16_t i = 0; i < names->count_line - 1; ++i) {
            if(READ_FLAG(names->flags, flag_r) ? 
                mx_strcmp(names->list[i][index], names->list[i + 1][index]) < 0 : 
                mx_strcmp(names->list[i][index], names->list[i + 1][index]) > 0) {
                char** temp = names->list[i];
                names->list[i] = names->list[i + 1];
                names->list[i + 1] = temp;
            }
        }
    }
}

static void param_sort(t_names *names)
{
    for (uint32_t i = 0; i < names->count_line; i++) {
        for (uint32_t j = 0; j < names->count_line - 1; j++) {
            if (names->sort[j] < names->sort[j + 1]) {
                uint32_t temp_uint = names->sort[j];
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

void sort(t_names *names)
{
    if(READ_FLAG(names->flags, flag_f)) {
        return;
    }
    else if(READ_FLAG(names->flags, flag_t | flag_c | flag_S)) {
        param_sort(names);
    }
    else if(READ_FLAG(names->flags, flag_r | flag_C)) {
        sort_by_alphabet(names); 
    }
}   
