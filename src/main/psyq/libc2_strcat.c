#include "psyq.h"

int strlen(char *s);

char *strcat(char *dst, char *src) {
    char *d;

    if (dst == NULL || src == NULL) {
        return NULL;
    }
    if (dst + strlen(dst) != src + strlen(src)) {
        d = dst;
        while (*dst++ != 0) {
        }
        dst--;
        while ((*dst++ = *src++) != 0) {
        }
        return d;
    }
    return NULL;
}

OBJECT_END();
