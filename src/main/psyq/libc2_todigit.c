#include "psyq.h"

long todigit(char c) {
    if (D_800555C1[(u_char)c] & 4) {
        return c - '0';
    }
    if (!(D_800555C1[(u_char)c] & 3)) {
        return 9999999;
    }
    return tolower(c) - 'a' + 10;
}

OBJECT_END();
