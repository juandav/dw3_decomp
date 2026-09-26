#include "psyq.h"

void *memcpy(u_char *dst, u_char *src, int n) {
    u_char *ret = NULL;
    u_char *d;

    if (dst != NULL) {
        d = dst;
        while (n > 0) {
            *dst++ = *src++;
            n--;
        }
        ret = d;
    }
    return ret;
}

OBJECT_END();
