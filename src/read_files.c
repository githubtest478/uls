#include "uls.h"

static void next_dir(t_names *names)
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
        else
            break;
    }
}

static uint32_t count_files(t_names *names)
{
    uint32_t files_number = 0;
    names->folder = opendir(names->dirs[names->count.dirs_index]);
    next_dir(names);

    while(names->dirs_content) {
        files_number++;

        if(READ_FLAG(names->flags, flag_R)  && 
            names->dirs_content->d_type == DT_DIR     && 
            names->dirs_content->d_name[0] != '.')
            names->count.dirs++;

        next_dir(names);
    }

    closedir(names->folder);
    return files_number;
}

void read_files_struct(t_names *names) 
{
    if(READ_FLAG(names->flags, flag_S | flag_t)) { 
        names->sort = (uint32_t *) malloc(sizeof(uint32_t) * names->count.files);
    }

    if(names->count.files)
        names->list = (char ***) malloc(sizeof(char **) * (names->count.files + 1));
    else 
        return;

    names->count.line = 0;
    SET_FLAG(names->flags, flag_file);

    for(; names->files[names->count.line];) {
        lstat(names->files[names->count.line], &names->filestat);
        fill_line(names);
    }

    RESET_FLAG(names->flags, flag_file);
}

void read_links_struct(t_names *names) 
{
    if(READ_FLAG(names->flags, flag_S | flag_t)) { 
        names->sort = (uint32_t *) malloc(sizeof(uint32_t) * names->count.links);
    }
    
    if(names->count.links)
        names->list = (char ***) malloc(sizeof(char **) * (names->count.links + 1));
    else 
        return;

    names->list = (char ***) malloc(sizeof(char **) * (names->count.links + 1));
    names->count.line = 0; 
    SET_FLAG(names->flags, flag_link);

    for(; names->links[names->count.line];) {
        lstat(names->links[names->count.line], &names->filestat);
        fill_line(names);
    }

    RESET_FLAG(names->flags, flag_link);
}

void read_dirs_struct(t_names *names) {
    uint32_t files_number = 0;
    names->total_size = 0;

    if(names->dirs)
        files_number = count_files(names);

    if(!files_number)
        return;

    names->folder = opendir(names->dirs[names->count.dirs_index]);

    if(READ_FLAG(names->flags, flag_S | flag_t)) { 
        names->sort = (uint32_t *) malloc(sizeof(uint32_t) * files_number);
    }

    names->list = (char ***) malloc(sizeof(char **) * (files_number + 1));
    names->count.line = 0; 
    next_dir(names);

    while(names->dirs_content) {
        char *path = mx_path_build(names->dirs[names->count.dirs_index], "/", names->dirs_content->d_name);
        lstat(path, &names->filestat);
        fill_line(names);  
        next_dir(names);
        free(path);
    }
    
    closedir(names->folder);
}
