#include "uls.h"

static void aditional_parameters(t_names *names)
{
    if(READ_FLAG(names->flags, flag_f));
    else if(READ_FLAG(names->flags, flag_S))
        names->sort[names->count_line] += names->filestat.st_size;
    else if(READ_FLAG(names->flags, flag_t))
        names->sort[names->count_line] += names->filestat.st_mtime;
    else if(READ_FLAG(names->flags, flag_c))
        names->sort[names->count_line] += names->filestat.st_ctime;
    else if(READ_FLAG(names->flags, flag_u))
        names->sort[names->count_line] += names->filestat.st_atime;

    if(READ_FLAG(names->flags, flag_l | flag_s))
        names->total_size += names->filestat.st_blocks;
}

void fill_line(t_names *names)
{
    uint8_t count_word = 0;

    if(S_ISLNK(names->filestat.st_mode))
        names->list[names->count_line] = (char **) malloc(sizeof(char *) * names->list_size + 2);
    else
        names->list[names->count_line] = (char **) malloc(sizeof(char *) * names->list_size);
    
    aditional_parameters(names);

    if(READ_FLAG(names->flags, flag_i))
        names->list[names->count_line][count_word++] = get_serial_number(names);    //0
    
    if(READ_FLAG(names->flags, flag_s))
        names->list[names->count_line][count_word++] = get_blocksize(names);        //1

    if(READ_FLAG(names->flags, flag_l)) {
        names->list[names->count_line][count_word++] = get_permission(names);        //2 
        names->list[names->count_line][count_word++] = get_link_param(names);       //3 
        names->list[names->count_line][count_word++] = get_owner(names);            //4 
        names->list[names->count_line][count_word++] = get_group(names);            //5 
        names->list[names->count_line][count_word++] = get_size(names);             //6
        names->list[names->count_line][count_word++] = get_time(names);             //7
    }

    names->list[names->count_line][count_word++] = get_name(names);                 //8
    
    if(S_ISLNK(names->filestat.st_mode) && READ_FLAG(names->flags, flag_l)) {
        names->list[names->count_line][count_word++] = mx_strdup("->");             //9
        names->list[names->count_line][count_word++] = mx_strdup("link_name");      //10 temporary
    }
        
    names->list[names->count_line++][count_word] = NULL;                       
    names->list[names->count_line] = NULL;
}

void print_list(t_names *names)
{
    char *dilim1 = " ";
    char *dilim2 = READ_FLAG(names->flags, flag_m)     ? ", "  :
                    READ_FLAG(names->flags, flag_one)   ? "\n"  :
                    READ_FLAG(names->flags, flag_C)     ? " "   : "";

    uint8_t list_size = 2;
    list_size += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    list_size += READ_FLAG(names->flags, flag_i);
    list_size += READ_FLAG(names->flags, flag_s);

    for(int i = 0, j = 0; names->list[i] != NULL;) {

        mx_printstr(names->list[i][j++]);

        for(; names->list[i][j] != NULL; ++j) {
            mx_printstr(dilim1);
            mx_printstr(names->list[i][j]);
        }

        if(names->list[++i] != NULL)
            mx_printstr(dilim2);
    }

    mx_printchar('\n');
}

void delete_list(t_names *names)
{
    uint8_t i = 0;
    
    while(names->list[i]) {
        mx_del_strarr(&names->list[i++]);
    }

    free(names->list);  
    names->list = NULL;
}
