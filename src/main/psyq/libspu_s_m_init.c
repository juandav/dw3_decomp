#include "psyq.h"

extern long D_8005BA88;
extern long D_8005BA8C;
extern char *D_8005BA90;

long SpuInitMalloc(long num, char *top) {
    long mode;

    if (num > 0) {
        mode = D_8005BA50;
        ((long *)top)[0] = 0x40001010;
        D_8005BA90 = top;
        D_8005BA8C = 0;
        D_8005BA88 = num;
        ((long *)top)[1] = (0x10000 << mode) - 0x1010;
        return num;
    }
    return 0;
}

OBJECT_END();
