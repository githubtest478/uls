#include "uls.h"

static void LineUp_colum_right(t_names *names, uint8_t colum_num)
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

static void LineUp_colum_left(t_names *names, uint8_t colum_num)
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

            mx_strcpy(sized_str, names->list[i][colum_num]);
            
            for(; size < max_size;) {
                sized_str[size++] = ' ';
            }

            free(names->list[i][colum_num]);
            names->list[i][colum_num] = sized_str;
        }
    }
}

static void LineUp_add_borders(t_names *names, uint8_t colum_num)
{ 
    uint8_t max_size = mx_strlen(names->list[0][colum_num]);

    for(uint8_t i = 0; names->list[i]; ++i) {
        uint8_t size = mx_strlen(names->list[i][colum_num]);
        
        char *sized_str = mx_strnew(max_size + 2);
        
        sized_str[0] = ' ';

        mx_strcpy(&sized_str[1], names->list[i][colum_num]);
        sized_str[size + 1] = ' ';
        free(names->list[i][colum_num]);
        names->list[i][colum_num] = sized_str;
    }
}

void LineUp(t_names *names)
{
    uint8_t lined_colum = 0;

    if(READ_FLAG(names->flags, flag_i)) {
        LineUp_colum_right(names, lined_colum++);
    }

    if(READ_FLAG(names->flags, flag_s)) {
        LineUp_colum_right(names, lined_colum++);
    }

    if(READ_FLAG(names->flags, flag_l)) {
        LineUp_colum_right(names, ++lined_colum);
        LineUp_colum_left(names, ++lined_colum);
        LineUp_colum_left(names, ++lined_colum);
        LineUp_add_borders(names, lined_colum++);
        LineUp_colum_right(names, lined_colum++);
        //LineUp_colum_left(names, ++lined_colum);
        /* test */
        lined_colum++;
    }
     if(READ_FLAG(names->flags, flag_C))
        LineUp_colum_left(names, lined_colum);
}
