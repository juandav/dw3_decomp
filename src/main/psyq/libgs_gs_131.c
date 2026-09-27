#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_131", func_80029DB8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_131", func_8002A188);

long func_8002A274(long *v) {
    long max;
    long t;

    max = (v[0] >= 0) ? v[0] : -v[0];
    t = (v[1] >= 0) ? v[1] : -v[1];
    if (max < t) max = t;
    t = (v[2] >= 0) ? v[2] : -v[2];
    if (max < t) max = t;
    t = (v[3] >= 0) ? v[3] : -v[3];
    if (max < t) max = t;
    t = (v[4] >= 0) ? v[4] : -v[4];
    if (max < t) max = t;
    t = (v[5] >= 0) ? v[5] : -v[5];
    if (max < t) max = t;
    return max;
}

long func_8002A33C(long value) {
    long bits = 0;

    while (value > 0) {
        value >>= 1;
        bits++;
    }
    return bits;
}

OBJECT_END();
