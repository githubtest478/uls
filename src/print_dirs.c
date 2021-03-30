#include "uls.h"

void print_dirs(t_names * names)
{
    char *dilim1 =  READ_FLAG(names->flags, flag_l | flag_i)     ? " "   : "";
    char *dilim2 =  READ_FLAG(names->flags, flag_m)     ? ", "  :
                    READ_FLAG(names->flags, flag_one)   ? "\n"  :
                    READ_FLAG(names->flags, flag_C)     ? " "   : "";
    
    for(names->dirs_index = 0; names->dirs_index < names->dirs_count;) {
        read_files_struct(names);
        names->folder = opendir(names->dirs[names->dirs_index]);
        
        if(names->dirs_count != 1) {
            mx_printstr(names->dirs[names->dirs_index]);
            mx_printstr(":\n");
        }

        fill_list(names);
        //print_total(names);
        //sort(names);
        form_colums(names);
        // printf("TP 3\n");
        mx_print_list(names->list, dilim1, dilim2);

        if(++names->dirs_index != names->dirs_count) { 
            mx_printchar('\n');
        }

        delete_list(names);
        closedir(names->folder);
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

void fill_list(t_names *names)
{
    uint8_t list_size = 2;
    list_size += READ_FLAG(names->flags, flag_l) ? 6 : 0;
    list_size += READ_FLAG(names->flags, flag_i);
    //printf("count files = %d\n", names->count_file);
    names->list = (char ***) malloc(sizeof(char **) * (names->count_file + 1));
    names->count_line = 0;

    while(names->dirs_content[names->count_line]) {
        // printf("Test point 1t\n"); //debug
        names->count_word = 0;
        names->list[names->count_line] = (char **) malloc(sizeof(char *) * list_size);
        // printf("Test point 2t\n"); //debug
        if(READ_FLAG(names->flags, flag_i)) {
            names->list[names->count_line][names->count_word++] = serial_number(&names->filestat[names->count_line]);    //0
        }
        // printf("Test point 3t\n"); //debug
        if(READ_FLAG(names->flags, flag_l)) {
            names->list[names->count_line][names->count_word++] = permision(&names->filestat[names->count_line]);        //1 
            // printf("Test point permision\n"); //debug
            names->list[names->count_line][names->count_word++] = link_param(&names->filestat[names->count_line]);       //2 
            // printf("Test point link_param\n"); //debug
            names->list[names->count_line][names->count_word++] = owner(&names->filestat[names->count_line]);            //3 
            // printf("Test point owner\n"); //debug
            names->list[names->count_line][names->count_word++] = group(&names->filestat[names->count_line]);            //4 
            // printf("Test point group\n"); //debug
            names->list[names->count_line][names->count_word++] = size(&names->filestat[names->count_line]);             //5 
            // printf("Test point size\n"); //debug
            names->list[names->count_line][names->count_word++] = last_modify(&names->filestat[names->count_line]);      //6 
            // printf("Test point last_modify\n"); //debug
        }
        // printf("Test point 4t\n"); //debug

        
   //printf("%s <-> ", names->dirs_content[names->count_line]->d_name);
        names->list[names->count_line][names->count_word++] = name(names->dirs_content[names->count_line]);              //7
        //printf(">%s \n", names->list[names->count_line][names->count_word - 1]);
        
        names->list[names->count_line++][names->count_word] = NULL;                                                      //8
        names->list[names->count_line] = NULL;
        // printf("Test point 5t\n"); //debug
    }
}

void next_dir(t_names *names)
{   
    while((names->dirs_content[names->count_line] = readdir(names->folder)) != NULL) {
        if((!mx_strcmp(names->dirs_content[names->count_line]->d_name, ".")    ||
            !mx_strcmp(names->dirs_content[names->count_line]->d_name, ".."))  &&
            !READ_FLAG(names->flags, flag_a)) {
            continue;
        }
        else if(!mx_strncmp(names->dirs_content[names->count_line]->d_name, ".", 1)    &&
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
    free(names->dirs_content);
    free(names->filestat);
    names->list = NULL;
    names->dirs_content = NULL;
    names->filestat = NULL;
}

void print_total(t_names * names) {
    if(!READ_FLAG(names->flags, flag_l))
        return;

    names->total_size = 0;

    for(uint8_t i = 0; i < names->count_file; ++i) {
        names->total_size += names->filestat[i].st_blocks;
    }

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
    names->dirs_content =  malloc(sizeof(struct dirent*) * (names->count_file + 1));
    names->filestat = (struct stat *) malloc(sizeof(struct stat) * (names->count_file + 1));
    // if(names->folder == NULL) {
    //     perror("Unable to read directory");
    // }
    
    names->count_line = 0;
    
    next_dir(names);
    // printf("start pointer2 %p \n", (void *) names->dirs_content[0]);

    while(names->dirs_content[names->count_line]) {
        char *temp1 = mx_strjoin("/", names->dirs_content[names->count_line]->d_name);
        char *temp2 = mx_strjoin(names->dirs[names->dirs_index], temp1);
        stat(temp2 , &names->filestat[names->count_line]);
        // printf("name %d: %s\n", names->count_line, names->dirs_content[names->count_line]->d_name);
        // printf("stat %d: %lld\n", names->count_line, names->filestat[names->count_line].st_blocks);
        
        names->count_line++;
        next_dir(names);
        free(temp1);
        free(temp2);
    }

    names->count_line = 0;
    closedir(names->folder);
}
