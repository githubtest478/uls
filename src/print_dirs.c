#include "uls.h"

void print_dirs(t_names * names)
{
    char *dilim1 =  READ_FLAG(names->flags, flag_l | flag_i)     ? " "   : "";
    char *dilim2 =  READ_FLAG(names->flags, flag_m)     ? ", "  :
                    READ_FLAG(names->flags, flag_one)   ? "\n"  :
                    READ_FLAG(names->flags, flag_C)     ? " "   : "";
    // printf("Dir count: %d\n", names->dirs_count); //debug
    for(uint8_t index = 0; index < names->dirs_count;) {
        uint8_t count_line = 0;
        uint8_t list_size = 2;
        uint8_t test_point = 1; // debug
        list_size += READ_FLAG(names->flags, flag_l) ? 6 : 0;
        list_size += READ_FLAG(names->flags, flag_i);

        names->folder = opendir(names->dirs[index]);
        count_files(names);
        names->list = malloc(sizeof(char ***) * (names->file_count + 1));
        
        if(names->folder == NULL) {
            perror("Unable to read directory");
        }
        
        names->folder = opendir(names->dirs[index]);
        next_dir(names);
        
        if(names->dirs_count != 1) {
            mx_printstr(names->dirs[index]);
            mx_printstr(":\n");
        }
        
        while(names->dirs_content) {
            uint8_t count_word = 0;
            names->list[count_line] = (char **) malloc(sizeof(char *) * list_size);

            if(READ_FLAG(names->flags, flag_i)) {
                names->list[count_line][count_word++] = serial_number(&names->filestat);    //0
            }
            
            if(READ_FLAG(names->flags, flag_l)) {
                names->list[count_line][count_word++] = permision(&names->filestat);        //1 
                names->list[count_line][count_word++] = link_param(&names->filestat);       //2 
                names->list[count_line][count_word++] = owner(&names->filestat);            //3 
                names->list[count_line][count_word++] = group(&names->filestat);            //4 
                names->list[count_line][count_word++] = size(&names->filestat);             //5 
                names->list[count_line][count_word++] = last_modify(&names->filestat);      //6 
            }
            names->list[count_line][count_word++] = name(names->dirs_content);              //7
            names->list[count_line][count_word] = NULL;                                     //8
            names->list[++count_line] = NULL;
            next_dir(names);
        }

        print_total(names);
        form_colums(names);
        sort(names);
        mx_print_list(names->list, dilim1, dilim2);

        if(++index != names->dirs_count) { 
            mx_printchar('\n');
        }

        delete_list(names);
        closedir(names->folder);
    }
}

// void print_int_arr(uint8_t *arr, uint8_t n) // debug func
// {
//     for(uint8_t i = 0; i < n; ++i) {
//         mx_printint(arr[i]);
//         mx_printchar(' ');
//     }
//     mx_printchar('\n');
// }

void form_colums(t_names *names)
{
    uint8_t max_size[9] = {0};
    // printf("init value: ");
    // print_int_arr((void *) max_size, 9);    

    for(uint8_t i = 0; names->list[i]; ++i) {
        for(uint8_t j = 1; names->list[i][j]; ++j) {
            uint8_t size = mx_strlen(names->list[i][j]);
            
            if(size > max_size[j]) {
                max_size[j] = size;
            }
        }
    }
    // printf("get size: ");
    // print_int_arr((void *) max_size, 9);
    for(uint8_t i = 0; names->list[i]; ++i) {
        for(uint8_t j = 1; names->list[i][j]; ++j) {
            for(uint8_t k = 0; max_size[j] >= mx_strlen(names->list[i][j]); ++k) {
                char *temp = names->list[i][j];
                names->list[i][j] = mx_strjoin(" ", temp);
                free(temp);
            }
        }
    }
}



void next_dir(t_names *names)
{
    while((names->dirs_content = readdir(names->folder)) != NULL) {
        stat(names->dirs_content->d_name, &names->filestat);

        if((!mx_strcmp(names->dirs_content->d_name, ".")    ||
            !mx_strcmp(names->dirs_content->d_name, ".."))  &&
            !READ_FLAG(names->flags, flag_a)) {
            continue;
        }
        else if(!mx_strncmp(names->dirs_content->d_name, ".", 1)    &&
                !READ_FLAG(names->flags, flag_A | flag_a)) {
            continue;
        }
        else {
            break;
        }
    }
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

void print_total(t_names * names) {
    if(!READ_FLAG(names->flags, flag_l))
        return;

    uint64_t sum = 0;
    char *total;

    uint16_t i = 0;
    uint8_t count = READ_FLAG(names->flags, flag_i) ? 5 : 4;

    while(names->list[i] != NULL) {
        sum += mx_atoi(names->list[i++][count]);
    }

    while(sum > 102.4)
        sum /= 102.4;

    char *temp = mx_strjoin("total ", mx_itoa(sum));
    total = mx_strjoin(temp, "\n");
    free(temp);
    mx_printstr(total);
    free(total);
}
