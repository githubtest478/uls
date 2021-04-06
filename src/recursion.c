#include "uls.h"

static int recursion_R_flag_count(t_names *names, char *dir_path) { 
    struct dirent * entry;
    uint16_t count = 0;
    DIR *folder = opendir(dir_path);

    while((names->dirs_content = readdir(folder)) != NULL) {
        if(names->dirs_content->d_type == DT_DIR && names->dirs_content->d_name[0] != '.') {
            char *dir_path1 = mx_strjoin("/", names->dirs_content->d_name);
            char *dir_path2 = mx_strjoin(dir_path, dir_path1);  
            free(dir_path1);
            ++count;
            count += recursion_R_flag_count(names, dir_path2);
            free(dir_path2);
        }
    }

    closedir(folder);
    return count;
}

static void recursion_R_flag_search_add_dirs(t_names *names, char *dir_path) { 
    DIR *dirp = NULL;
    struct dirent * entry;

    dirp = opendir(dir_path);
    while((entry = readdir(dirp)) != NULL) {
        if(entry->d_type == DT_DIR && entry->d_name[0] != '.') {   // если приходит директория то РИКУРСИЯ ДЛЯ НЕЕ (надо  str_join (str + '/' + entry->d_name))
            char *dir_path1 = mx_strjoin("/", entry->d_name);
            char *dir_path2 = mx_strjoin(dir_path, dir_path1); //char a  новая память 
            free(dir_path1);
    
            names->recursion_dirs[names->recursion++] = dir_path2;

            recursion_R_flag_search_add_dirs(names, dir_path2);
        }
    }
    closedir(dirp);
}

void recursion_R_flag_main(t_names *names) {
    names->recursion = 0;
    uint16_t count = recursion_R_flag_count(names, names->dirs[0]); // 0 id temp
    uint16_t i = 0;

    names->recursion_dirs = (char**)malloc((count + 1) * sizeof(char*));

    while(i < count) {
        names->recursion_dirs[i] = mx_strdup(names->dirs[i]);
        recursion_R_flag_search_add_dirs(names, names->dirs[names->dirs_index]);
        i++;
    }
}
