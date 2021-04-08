#include "uls.h"

/* считает ширину экрана и делит на длину str_len */
static int width_terminal(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

static int names_str_len(t_names *names) {
    uint8_t len = 0, index = 0;

    if(READ_FLAG(names->flags, flag_i)) 
        len += mx_strlen(names->list[0][index++]); ++len;
    if(READ_FLAG(names->flags, flag_s))
        len += mx_strlen(names->list[0][index++]), ++len;

    len += mx_strlen(names->list[0][index]);
    len += 3;

    return width_terminal() / len;
}

static void print_strarr(char **arr, const char *delim)
{
    if(arr == NULL || delim == NULL)
        return;

    for(int i = 0; arr[i] != NULL;) {
        for(int j = 0; arr[i][j] != '\0'; ++j) {
            write(1, &arr[i][j], 1);
        }

        if(arr[++i] != NULL) {
            for(int j = 0; delim[j] != '\0'; ++j) {
                write(1, &delim[j], 1);
            }
        }
    }
}

// -C
static void multicolumn_C(t_names *names) {
    uint16_t column_n = names_str_len(names);
    uint16_t lines_n = (names->count.line / column_n) + 1;

    for(uint8_t i = 0; i < lines_n; ++i) { 
        for(uint8_t g = i; g < names->count.line; g += lines_n) {
            print_strarr(names->list[g], " ");
            mx_printstr("   ");
        }
        mx_printchar('\n');
    }
}

// -x
static void multicolumn_x(t_names *names) {
    uint16_t column_n = names_str_len(names);

    for(uint8_t i = 0; names->list[i]; ++i) {
        print_strarr(names->list[i], " ");
        mx_printchar(' ');
        if((i + 1) % column_n == 0)
            mx_printchar('\n');
    }
}

// -C  -x
void multicolumn(t_names *names) {
    if(names->list[0] == NULL) {
        return;
    }
    if(READ_FLAG(names->flags, flag_C)) {
        multicolumn_C(names);
    }
    else {
        multicolumn_x(names);    
    }
}
