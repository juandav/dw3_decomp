#include "psyq.h"

int strcmp(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL) {
        return s1 == s2 ? 0 : (s1 != NULL ? 1 : -1);
    }
    while (*s1 == *s2++) {
        if (*s1++ == '\0') {
            return 0;
        }
    }
    return *s1 - s2[-1];
}

OBJECT_END();
