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

void count_files_in_current_dir(t_names *names) {
   
    
    while(readdir(names->folder)) {
        // if (entry->d_type == DT_REG) { /* If the entry is a regular file */
        //     ++file_count;
        // }
       names->file_count++;
    }
    closedir(names->folder);
}

