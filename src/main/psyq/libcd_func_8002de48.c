#include "psyq.h"

void func_8002DE48(void) {
    CD_ready();
}

long func_8002DE68(long value) {
    long old = D_8005A2C8;

    D_8005A2C8 = value;
    return old;
}

OBJECT_END();
