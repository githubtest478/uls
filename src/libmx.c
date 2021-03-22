#include "uls.h"

int mx_strlen(const char *s) {
    int count = 0;

    while (*s++)
    { 
        ++count; 
    }
    return count;
}



