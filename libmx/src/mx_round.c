#include "libmx.h"

long long mx_round(long long num)
{
    bool msb = 0;
    while(num > 10) {
        msb = num % 10 > 4;
        num /= 10;
        num += msb;
    }

    return num;
}
