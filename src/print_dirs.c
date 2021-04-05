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

void print_dirs(t_names * names)
{
    // names->dilim1 = READ_FLAG(names->flags, flag_l | flag_i) ? " "   : " ";
    names->dilim1 = " ";
    names->dilim2 = READ_FLAG(names->flags, flag_m)     ? ", "  :
                    READ_FLAG(names->flags, flag_one)   ? "\n"  :
                    READ_FLAG(names->flags, flag_C)     ? " "   : "";

    names->list_size = 2;
    names->list_size += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    names->list_size += READ_FLAG(names->flags, flag_i);
    names->list_size += READ_FLAG(names->flags, flag_s);
   
    for(names->dirs_index = 0; names->dirs_index < names->dirs_count;) {
        read_files_struct(names);

        if(names->dirs_count != 1) {
            mx_printstr(names->dirs[names->dirs_index]);
            mx_printstr(":\n");
        }

        sort(names);
        LineUp(names);
        print_total(names);
        print_list(names);

        if(++names->dirs_index != names->dirs_count) { 
            mx_printchar('\n');
        }

        delete_list(names);
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

void fill_line(t_names *names)
{
    uint8_t count_word = 0;
    if(S_ISLNK(names->filestat.st_mode))
        names->list[names->count_line] = (char **) malloc(sizeof(char *) * names->list_size + 2);
    else
        names->list[names->count_line] = (char **) malloc(sizeof(char *) * names->list_size);

    if(READ_FLAG(names->flags, flag_S))
        names->sort[names->count_line] += names->filestat.st_size;
    else if(READ_FLAG(names->flags, flag_t))
        names->sort[names->count_line] += names->filestat.st_mtime;
    else if(READ_FLAG(names->flags, flag_c))
        names->sort[names->count_line] += names->filestat.st_ctime;
    
    if(READ_FLAG(names->flags, flag_l | flag_s))
        names->total_size += names->filestat.st_blocks;

    if(READ_FLAG(names->flags, flag_i))
        names->list[names->count_line][count_word++] = get_serial_number(names);    //0
    
    if(READ_FLAG(names->flags, flag_s))
        names->list[names->count_line][count_word++] = get_blocksize(names);        //1

    if(READ_FLAG(names->flags, flag_l)) {
        names->list[names->count_line][count_word++] = get_permision(names);        //2 
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

void next_dir(t_names *names)
{   
    while((names->dirs_content = readdir(names->folder)) != NULL) {
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

void print_list(t_names *names)
{
    for(int i = 0; names->list[i] != NULL;) {
        int j = 0;
        mx_printstr(names->list[i][j++]);

        for(; names->list[i][j] != NULL; ++j) {
            mx_printstr(names->dilim1);
            mx_printstr(names->list[i][j]);
        }

        if(names->list[++i] != NULL)
            mx_printstr(names->dilim2);
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

void print_total(t_names * names) {
    if(!READ_FLAG(names->flags, flag_l | flag_s))
        return;

    char *temp = mx_strjoin("total ", mx_itoa(names->total_size));
    char *total= mx_strjoin(temp, "\n");
    mx_printstr(total);
    free(temp);
    free(total);
}

void count_files(t_names *names)
{
    names->folder = opendir(names->dirs[names->dirs_index]);
    names->count_file = 0;
    struct dirent *curent_dir;
    
    while((curent_dir = readdir(names->folder)))
        names->count_file++;

    closedir(names->folder);
}

void read_files_struct(t_names *names) {
    count_files(names);
    names->folder = opendir(names->dirs[names->dirs_index]);
    
    // if(names->folder == NULL) {
    //     perror("Unable to read directory");
    // }

    next_dir(names);

    if(READ_FLAG(names->flags, flag_S | flag_t | flag_c)) { 
        names->sort = (uint32_t *) malloc(sizeof(uint32_t) * names->count_file);
    }

    names->list = (char ***) malloc(sizeof(char **) * (names->count_file + 1));
    names->count_line = 0;

    while(names->dirs_content) {
        char *temp1 = mx_strjoin("/", names->dirs_content->d_name);
        char *temp2 = mx_strjoin(names->dirs[names->dirs_index], temp1);
        lstat(temp2, &names->filestat);
        fill_line(names);  

        /* Resorch
        for(uint8_t i = 0; i < 16; ++i) {
            mx_printchar(((0x8000 >> i) & names->filestat.st_mode) ? '1' : '0');
            if(!((i + 1) % 4)) {
                mx_printchar(' ');
            }
        }
        mx_printchar('\n');
        */

        next_dir(names);
        free(temp1);
        free(temp2);
    }

    closedir(names->folder);
}
