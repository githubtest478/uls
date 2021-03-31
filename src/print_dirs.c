#include "uls.h"

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
        form_colums(names);
        print_total(names);
        print_list(names);

        if(++names->dirs_index != names->dirs_count) { 
            mx_printchar('\n');
        }

        delete_list(names);
    }
}

void form_colums(t_names *names)
{
    uint8_t max_size[9] = {0};   

    for(uint8_t i = 0; names->list[i]; ++i) {
        for(uint8_t j = 0; names->list[i][j + 1]; ++j) {
            uint8_t size = mx_strlen(names->list[i][j]);
            if(size > max_size[j]) {
                max_size[j] = size;
            }
        }
    }
    for(uint8_t i = 0; names->list[i]; ++i) {
        for(uint8_t j = 0; names->list[i][j + 1]; ++j) {
            for(uint8_t k = 0; max_size[j] > mx_strlen(names->list[i][j]); ++k) {
                char *temp = names->list[i][j];
                names->list[i][j] = mx_strjoin(" ", temp);
                free(temp);
            }
        }
    }
}

void fill_line(t_names *names)
{
    uint8_t count_word = 0;
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
        names->list[names->count_line][count_word++] = serial_number(names);    //0
    
    if(READ_FLAG(names->flags, flag_s))
        names->list[names->count_line][count_word++] = blocksize(names);        //1

    if(READ_FLAG(names->flags, flag_l)) {
        names->total_size += names->filestat.st_blocks;
        names->list[names->count_line][count_word++] = permision(names);        //2 
        names->list[names->count_line][count_word++] = link_param(names);       //3 
        names->list[names->count_line][count_word++] = owner(names);            //4 
        names->list[names->count_line][count_word++] = group(names);            //5 
        names->list[names->count_line][count_word++] = size(names);             //6
        if(READ_FLAG(names->flags, flag_C))
            names->list[names->count_line][count_word++] = last_modify(names);  //7
        else if(READ_FLAG(names->flags, flag_c))
            names->list[names->count_line][count_word++] = created(names);      //8
    }

    names->list[names->count_line][count_word++] = name(names);                 //9
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
        stat(temp2, &names->filestat);
        fill_line(names);  
        next_dir(names);
        free(temp1);
        free(temp2);
    }

    closedir(names->folder);
}
