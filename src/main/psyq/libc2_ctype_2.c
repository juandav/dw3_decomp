#include "psyq.h"

char tolower(char c) {
    if (D_800555C1[(u_char)c] & 1) {
        c += 0x20;
    }
    return c;
}

OBJECT_END();
