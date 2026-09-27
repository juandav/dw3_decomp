#include "psyq.h"

#define isspace(c) (D_800555C1[(u_char)(c)] & 8)

long todigit(char c);

long atoi(char *s) {
    long sign = 1;
    long base = 10;
    long n = 0;
    u_long d;

    if (s == NULL) {
        return 0;
    }
    while (isspace(*s++)) {
    }
    s--;
    while (*s == '-') {
        s++;
        sign = -sign;
    }
    if (*s == '0') {
        s++;
        switch (*s) {
        case 'x':
        case 'X':
            s++;
            base = 16;
            break;
        case 'b':
        case 'B':
            s++;
            base = 2;
            break;
        default:
            base = 8;
            break;
        }
    }
    while ((d = todigit(*s++)) < base) {
        n *= base;
        n += d;
    }
    return n * sign;
}

OBJECT_END();
