#include "uls.h"

/* new itoa from  −9,223,372,036,854,775,807, TO  +9,223,372,036,854,775,807 */ 
char *mx_itoa(long long number) {
    char *str = (char *) malloc(21);
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

void print_xattr(t_names *names, uint8_t index_i, uint8_t index_j) 
{
    if(!READ_FLAG(names->flags, flag_At))
        return;
    
    char *path = mx_path_build(names->dirs[names->count.dirs_index], "/", names->list[index_i][index_j]);

    ssize_t attr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    if(attr > 0) {
        char a[attr];
        
        listxattr(path, a, attr, XATTR_NOFOLLOW);
        mx_printchar('\t');
        mx_printstr(a);
        mx_printchar('\t');
        mx_printint(attr);
        mx_printchar('\n');

        if(attr == -1)
            perror("Error:");
    }
    free(path);
}
