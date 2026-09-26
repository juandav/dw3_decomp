#include "psyq.h"

long func_8002DE28(long value) {
    long old = D_8005A2D0;

    D_8005A2D0 = value;
    return old;
}

OBJECT_END();
