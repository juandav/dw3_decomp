#include "psyq.h"

long func_8002A274(long *v);
long func_8002A33C(long value);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_131", func_80029DB8);

void func_8002A188(long *src, long *dst) {
    long shift = func_8002A33C(func_8002A274(src));

    if (shift >= 16) {
        shift -= 15;
        dst[0] = src[0] >> shift;
        dst[1] = src[1] >> shift;
        dst[2] = src[2] >> shift;
        dst[3] = src[3] >> shift;
        dst[4] = src[4] >> shift;
        dst[5] = src[5] >> shift;
    } else {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
    }
}

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
