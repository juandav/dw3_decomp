#include "psyq.h"

void *bzero(unsigned char *p, int n) {
    unsigned char *s;

    if (p == NULL) {
        return NULL;
    }
    if (n <= 0) {
        return NULL;
    }
    s = p;
    while (n > 0) {
        *p++ = 0;
        n--;
    }
    return s;
}

OBJECT_END();
