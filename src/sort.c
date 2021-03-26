#include "uls.h"

void sort_by_alpgaber(t_names *names)
{
    uint8_t index = 0;
    index += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    index += READ_FLAG(names->flags, flag_i);

    for(uint8_t i = 0; i < names->file_count - 1; ++i) {
        for(uint8_t j = 0; j < names->file_count; ++j) {
            if(READ_FLAG(names->flags, flag_r) ? 
                mx_strcmp(names->list[i][index], names->list[j][index]) > 0 : 
                mx_strcmp(names->list[i][index], names->list[j][index]) < 0) {
                char** temp = names->list[i];
                names->list[i] = names->list[j];
                names->list[j] = temp;
            }
        }
    }
}

void sort_by_created_time(t_names *names)
{

}

void sort_by_changed_time(t_names *names)
{

}
