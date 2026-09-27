#include "psyq.h"

int strcspn(char *s1, char *s2)
{
    char *start = s1;
    char *q;

    for (; *s1 != '\0'; s1++) {
        for (q = s2; *q != '\0'; q++) {
            if (*q == *s1) {
                break;
            }
        }
        if (*q != '\0') {
            break;
        }
    }
    return s1 - start;
}

OBJECT_END();
