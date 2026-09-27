#include "psyq.h"

extern u_long *D_8005BA38;
extern long D_8005BA4C;
extern long D_8005BA54;
extern long D_8005BA58;

long _spu_FsetRXXa(long reg, u_long value) {
    u_short v;

    if (D_8005BA4C != 0 && (value % D_8005BA54) != 0) {
        value += D_8005BA54;
        value &= ~D_8005BA58;
    }
    v = value >> D_8005BA50;
    switch (reg) {
    case -1:
        return v;
    case -2:
        return value;
    default:
        D_8005BA28[reg] = v;
        return value;
    }
}

u_long _spu_FgetRXXa(int reg, int mode) {
    u_short v = D_8005BA28[reg];

    if (mode == -1) {
        return v;
    }
    return v << D_8005BA50;
}

void _spu_FsetPCR(int flag) {
    *D_8005BA38 &= 0xFFF8FFFF;
    if (flag) {
        *D_8005BA38 |= 0x30000;
    } else {
        *D_8005BA38 |= 0x50000;
    }
}

void func_80038C00(void) {
    *D_8005BA3C = (*D_8005BA3C & 0xF0FFFFFF) | 0x20000000;
}

void func_80038C28(void) {
    *D_8005BA3C = (*D_8005BA3C & 0xF0FFFFFF) | 0x22000000;
}

void _spu_Fw1ts(void) {
    volatile int i;
    volatile int n = 13;

    for (i = 0; i < 60; i += 1) {
        n *= 13;
    }
}

OBJECT_END();
