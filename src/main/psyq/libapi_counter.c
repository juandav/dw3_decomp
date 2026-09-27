#include "psyq.h"

long SetRCnt(unsigned long spec, unsigned short target, long mode) {
    int c = spec & 0xFFFF;
    int m = 0x48;

    if (c >= 3) {
        return 0;
    }
    D_8005B86C[c * 8 + 2] = 0;
    D_8005B86C[c * 8 + 4] = target;
    if (c == 0 || c == 1) {
        if (mode & 0x10) {
            m = 0x49;
        }
        if (!(mode & 1)) {
            m |= 0x100;
        }
    } else if (c == 2) {
        if (!(mode & 1)) {
            m = 0x248;
        }
    }
    if (mode & 0x1000) {
        m |= 0x10;
    }
    D_8005B86C[c * 8 + 2] = m;
    return 1;
}

long GetRCnt(unsigned long spec) {
    int c = spec & 0xFFFF;

    if (c >= 3) {
        return 0;
    }
    return D_8005B86C[c * 8];
}

long StartRCnt(u_long spec) {
    int timer = spec & 0xFFFF;

    D_8005B868[1] |= D_8005B870[timer];
    return timer < 3;
}

long StopRCnt(u_long spec) {
    D_8005B868[1] &= ~D_8005B870[spec & 0xFFFF];
    return 1;
}

long ResetRCnt(unsigned long spec) {
    int c = spec & 0xFFFF;

    if (c >= 3) {
        return 0;
    }
    D_8005B86C[c * 8] = 0;
    return 1;
}

OBJECT_END();
