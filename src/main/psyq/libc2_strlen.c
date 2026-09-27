#include "psyq.h"

int strlen(char *s) {
    int n = 0;
    int ret = 0;

    if (s != NULL) {
        while (*s++ != 0) {
            n++;
        }
        ret = n;
    }
    return ret;
}

OBJECT_END();
