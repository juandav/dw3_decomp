#include "psyq.h"

long func_8002E3B8(long value) {
    long old = D_80080C8C[0];

    D_80080C8C[0] = value;
    return old;
}

OBJECT_END();
