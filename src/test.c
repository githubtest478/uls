#include "uls.h"

/* new itoa from  −9,223,372,036,854,775,807, TO  +9,223,372,036,854,775,807 */ 
char *mx_itoa(long long number) {
    char *str = (char *)malloc(21);
	int count = 0;
	unsigned long long num;
    int flag = 0;

	if(number & 0x8000000000000000) {
        flag = 1;
		str[count++] = '-';
		num = (number ^ 0xFFFFFFFFFFFFFFFF) + 1;
	}
	else {
		num = (unsigned long long) number;
    }

	if(num == 0) {
		str[count++] = '0';
    }

	for(; num != 0; num /= 10) {
		str[count++] = ((num % 10) + '0');
    }

    for(int i = 0; (i + flag) < (count + flag) / 2; ++i) {
            char temp = str[i + flag];
            str[i + flag] = str[count - i - 1];
            str[count - i - 1] = temp;
        }

    str[count] = '\0';

    return str;
}

void recursion_R_flag_test(char *str) {     //будет приходить t_names *names и char *str-имя директории для открытия  (!!! приходят только директории не файлы!!!)
    DIR * dirp;
    struct dirent * entry;

    /* имя директори */
    if(str[1] == '/') {
        mx_printstr(str);
        mx_printstr(":\n");
    }

    int i = 0;
    /* сначала считываем первый раз и выводим содержимое */
    dirp = opendir(str);
    while((entry = readdir(dirp)) != NULL) { 
        i++;
        if(entry->d_name[0] != '.') {
            mx_printstr(entry->d_name);
            mx_printstr(" ");
        }
    }
        /*  тут нужно смотреть есть ли файлы в директории !ЕСЛИ НЕТ то не нужно это печатать  */
        if(i != 2) {
            mx_printstr("\n\n");
        }

    

    closedir(dirp);

    /* второй раз открываем и смотрим на наличие директорий */ //Don't include lib for DT_DIR define 
    // dirp = opendir(str);
    // while((entry = readdir(dirp)) != NULL) {
    //     if(entry->d_type == DT_DIR && entry->d_name[0] != '.') {   // если приходит директория то РИКУРСИЯ ДЛЯ НЕЕ (надо  str_join (str + '/' + entry->d_name))
    //         recursion_R_flag_test(mx_strjoin(str, mx_strjoin("/", entry->d_name)));
    //     }
    // }
    // closedir(dirp);
}


