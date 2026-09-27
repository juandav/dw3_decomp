#include "psyq.h"

long func_8002DE88(long value) {
    long old = D_8005A2CC;

    D_8005A2CC = value;
    return old;
}

OBJECT_END();
