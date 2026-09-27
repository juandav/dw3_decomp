#include "psyq.h"

void StSetMask(u_long mask, u_long start, u_long end) {
    D_80080C18 = mask;
    D_80080BF4 = start;
    D_80080C14 = end;
}

OBJECT_END();
