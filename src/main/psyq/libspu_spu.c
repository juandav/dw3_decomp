#include "psyq.h"

extern u_long *D_8005BA38;

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libspu_spu", D_80010BCC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_init);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", func_800383F8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FiDMA);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_Fr_);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_t);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_Fw);

u_long _spu_Fr(char *addr, u_long size) {
    _spu_t(2, D_8005BA40 << D_8005BA50);
    _spu_t(0);
    _spu_t(3, addr, size);
    return size;
}

void _spu_FsetRXX(int reg, u_long value, int mode) {
    if (mode == 0) {
        D_8005BA28[reg] = value;
    } else {
        D_8005BA28[reg] = value >> D_8005BA50;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FsetRXXa);

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
