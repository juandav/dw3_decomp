/* the VSync counter is read as volatile here (psyq.h's plain declaration suits intr_vb) */
#define D_8005B7C0 D_8005B7C0_plain
#include "psyq.h"
#undef D_8005B7C0

extern volatile long D_8005B7C0;
void puts(char *s);

extern volatile long *D_8005A688;
extern volatile long *D_8005A68C;
extern volatile long D_8005A690;
extern long D_8005A694;
void func_8002E580(long count, long timeout);

int VSync(int mode) {
    volatile long count;
    long status = *D_8005A688;
    long delta;
    long target;
    volatile long *gpu;

    do {
        count = *D_8005A68C;
    } while (count != *D_8005A68C);
    delta = (count - D_8005A690) & 0xFFFF;
    if (mode < 0) {
        return D_8005B7C0;
    }
    if (mode == 1) {
        return delta;
    }
    if (mode > 0) {
        target = D_8005A694 + (mode - 1);
    } else {
        target = D_8005A694;
    }
    func_8002E580(target, mode > 0 ? mode - 1 : 0);
    status = *D_8005A688;
    func_8002E580(D_8005B7C0 + 1, 1);
    if (status & 0x400000) {
        gpu = D_8005A688;
        while (!((status ^ *gpu) & 0x80000000)) {
        }
    }
    D_8005A694 = D_8005B7C0;
    do {
        D_8005A690 = *D_8005A68C;
    } while (D_8005A690 != *D_8005A68C);
    return delta;
}

void func_8002E580(long count, long timeout) {
    volatile long t = timeout << 15;

    while (D_8005B7C0 < count) {
        if (--t == -1) {
            puts("VSync: timeout\n");
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/psyq/libetc_vsync", ChangeClearPAD);

__asm__(".section .rodata\n"
        "\t.align 2\n"
        "\t.asciz \"$Id: intr.c,v 1.75 1997/02/07 09:00:36 makoto Exp $\"\n"
        "\t.align 2\n");

OBJECT_END();
