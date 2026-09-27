#include "psyq.h"

char *strncpy(char *dst, char *src, int n) {
    char *d;
    int i;

    if (dst == NULL || src == NULL) {
        return NULL;
    }
    d = dst;
    i = 0;
    if (n > 0) {
        do {
            if ((*dst++ = *src++) == '\0') {
                for (i++; i < n; i++) {
                    *dst++ = '\0';
                }
                return d;
            }
        } while (++i < n);
    }
    return d;
}

OBJECT_END();
