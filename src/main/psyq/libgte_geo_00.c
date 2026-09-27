#include "psyq.h"

extern short D_80055830[]; /* rsin_tbl */

int rsin(int a) {
    if (a < 0) {
        return -sin_1(-a & 0xFFF);
    }
    return sin_1(a & 0xFFF);
}

long sin_1(long a) {
    if (a <= 0x800) {
        if (a <= 0x400) {
            return D_80055830[a];
        }
        return D_80055830[0x800 - a];
    }
    if (a <= 0xC00) {
        return -D_80055830[a - 0x800];
    }
    return -D_80055830[0x1000 - a];
}

OBJECT_END();
