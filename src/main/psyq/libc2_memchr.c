#include "psyq.h"

void *memchr(unsigned char *s, int c, int n) {
    if (s == NULL || n <= 0) {
        return NULL;
    }
    while (--n >= 0) {
        if (*s++ == (u_char)c) {
            return s - 1;
        }
    }
    return NULL;
}

OBJECT_END();
