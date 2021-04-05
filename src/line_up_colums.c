#include "uls.h"

static void LineUp_colum(t_names *names, uint8_t colum_num)
{ 
    uint8_t max_size = 0;

    for(uint8_t i = 0; names->list[i]; ++i) {
        if(mx_strlen(names->list[i][colum_num]) > max_size)
            max_size = mx_strlen(names->list[i][colum_num]);
    }

    for(uint8_t i = 0; names->list[i]; ++i) {
        uint8_t size = mx_strlen(names->list[i][colum_num]);
        
        if(size < max_size) {
            char *sized_str = mx_strnew(max_size);
            uint8_t space_count = 0;

            for(; space_count < max_size - size;) {
                sized_str[space_count++] = ' ';
            }

            mx_strcpy(&sized_str[space_count], names->list[i][colum_num]);
            free(names->list[i][colum_num]);
            names->list[i][colum_num] = sized_str;
        }
    }
}

void LineUp(t_names *names)
{
    uint8_t lined_colum = 0;

    if(READ_FLAG(names->flags, flag_i)) {
        LineUp_colum(names, lined_colum++);
    }

    if(READ_FLAG(names->flags, flag_s)) {
        LineUp_colum(names, lined_colum++);
    }

    if(READ_FLAG(names->flags, flag_l)) {
        LineUp_colum(names, ++lined_colum);
        LineUp_colum(names, lined_colum + 3);
    }
}
