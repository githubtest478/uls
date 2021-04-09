#include "uls.h"

static uint32_t convert_time(char *time)
{
    uint8_t char_len = mx_strlen(time);
    uint16_t year, month = 0, day, hour, minutes, seconds;
    uint32_t res = 0;
    char temp[5] = {0};
    char *month_list[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    mx_strncpy(temp, &time[4], 3);    //month

    for(uint8_t i = 0; i < 12; ++i) {
        if(!mx_strcmp(temp, month_list[i])) {
            month = i;
            break;
        }
    }
    
    mx_strncpy(temp, &time[8], 2);    //day
    day = atoi(temp);
    mx_strncpy(temp, &time[11], 2);    //hour
    hour = atoi(temp);
    mx_strncpy(temp, &time[14], 2);    //minute
    minutes = atoi(temp);
    mx_strncpy(temp, &time[17], 2);    //seconds    
    seconds = atoi(temp);
    mx_strncpy(temp, &time[20], 4);    //year
    year = atoi(temp);

    res = (seconds + minutes * 60 + hour * 3600 + day * 3600 * 24 + month * 3600 * 24 * 31 + (year - 1970) * 3600 * 24 * 31 * 12);

    return res;
}

static void aditional_parameters(t_names *names)
{
    if(READ_FLAG(names->flags, flag_f));
    else if(READ_FLAG(names->flags, flag_S))
        names->sort[names->count.line] = names->filestat.st_size;
    else if(READ_FLAG(names->flags, flag_t)) {
        char *time_param;
        if(READ_FLAG(names->flags, flag_c))
            time_param = ctime(&names->filestat.st_ctime);
        else if(READ_FLAG(names->flags, flag_u))
            time_param = ctime(&names->filestat.st_atime);
        else
            time_param = ctime(&names->filestat.st_mtime);

        names->sort[names->count.line] = convert_time(time_param);
    }

    if(READ_FLAG(names->flags, flag_l | flag_s))
        names->total_size += names->filestat.st_blocks;
}

void fill_line(t_names *names)
{
    uint8_t count_word = 0;
    uint8_t list_size = 2;
    list_size += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    list_size += READ_FLAG(names->flags, flag_i);
    list_size += READ_FLAG(names->flags, flag_s);

    if(S_ISLNK(names->filestat.st_mode))
        names->list[names->count.line] = (char **) malloc(sizeof(char *) * list_size + 2);
    else
        names->list[names->count.line] = (char **) malloc(sizeof(char *) * list_size);
    
    aditional_parameters(names);

    if(READ_FLAG(names->flags, flag_i))
        names->list[names->count.line][count_word++] = get_serial_number(names);    //0
    
    if(READ_FLAG(names->flags, flag_s))
        names->list[names->count.line][count_word++] = get_blocksize(names);        //1

    if(READ_FLAG(names->flags, flag_l)) {
        names->list[names->count.line][count_word++] = get_permission(names);       //2 
        names->list[names->count.line][count_word++] = get_link_param(names);       //3 
        names->list[names->count.line][count_word++] = get_owner(names);            //4 
        names->list[names->count.line][count_word++] = get_group(names);            //5 
        names->list[names->count.line][count_word++] = get_size(names);             //6
        names->list[names->count.line][count_word++] = get_time(names);             //7
    }

    if(READ_FLAG(names->flags, flag_file))
        names->list[names->count.line][count_word++] = names->files[names->count.line];                 //8
    else if(READ_FLAG(names->flags, flag_link))
        names->list[names->count.line][count_word++] = names->links[names->count.line];                 //8
    else
        names->list[names->count.line][count_word++] = get_name(names);                 //8

    if(S_ISLNK(names->filestat.st_mode) && READ_FLAG(names->flags, flag_l)) {
        names->list[names->count.line][count_word++] = mx_strdup("->");             //9
        names->list[names->count.line][count_word++] = get_link(names);             //10
    }
        
    names->list[names->count.line++][count_word] = NULL;                       
    names->list[names->count.line] = NULL;
}

void print_list(t_names *names)
{
    char *dilim1 = " ";
    char *dilim2 = READ_FLAG(names->flags, flag_m)   ? ", "  :
                   READ_FLAG(names->flags, flag_one) ? "\n"  :
                   READ_FLAG(names->flags, flag_C)   ? " "   : "";

    for(uint8_t i = 0; names->list[i] != NULL;) {
        uint8_t  j = 0;
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
