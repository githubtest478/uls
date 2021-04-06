#include "uls.h"

static int recursion_R_flag_count(t_names *names) { 
    DIR *folder;
    int count = 0;
  
        folder = opendir(names->dirs[names->dirs_index]);
        while((names->dirs_content = readdir(folder)) != NULL) {
            if(names->dirs_content->d_type == DT_DIR && names->dirs_content->d_name[0] != '.') {
                char *a = mx_strjoin(names->dirs[names->dirs_index], mx_strjoin("/", names->dirs_content->d_name));  
    
                ++count;
                count += recursion_R_flag_count(names);
                free(a);
            }
        }
        closedir(folder);
        return count;
}

static void recursion_R_flag_search_add_dirs(char *str, char **all_dir_to_open) { 
    DIR * dirp;
    struct dirent * entry;

    dirp = opendir(names->dirs[names->dirs_index]);
    while((entry = readdir(dirp)) != NULL) {
        if(entry->d_type == DT_DIR && entry->d_name[0] != '.') {   // если приходит директория то РИКУРСИЯ ДЛЯ НЕЕ (надо  str_join (str + '/' + entry->d_name))
            char *a = mx_strjoin(str, mx_strjoin("/", entry->d_name)); //char a  новая память 
            //  тут надо добавлять куда-то а
            int i = 0;
            while(all_dir_to_open[i] != NULL) {
                ++i;
            }
            all_dir_to_open[i] = a;

            recursion_R_flag_search_add_dirs(a, all_dir_to_open);
        }
    }
    closedir(dirp);
}

void recursion_R_flag_main(t_names *names) {
    int count = recursion_R_flag_count(names);
    int i = 0;

    names->recursion_dirs = (char**)malloc((count + 1) * sizeof(char*));

    while(i < count) {
        names->recursion_dirs[i] = mx_strdup(names->dirs[i]);
        recursion_R_flag_search_add_dirs(names);
        i++;
    }


   

    /* test */
    // i = 0;
    // while(all_dir_to_open[i] != NULL) {
    //     //printf("%d ", i);
    //     printf("%s\n", all_dir_to_open[i]);
    //     ++i;
    // }


}




