/* the VSync counter is read as volatile here (psyq.h's plain declaration suits intr_vb) */
#define D_8005B7C0 D_8005B7C0_plain
#include "psyq.h"
#undef D_8005B7C0

extern volatile long D_8005B7C0;
void puts(char *s);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_vsync", VSync);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_vsync", ChangeClearPAD);

__asm__(".section .rodata\n"
        "\t.align 2\n"
        "\t.asciz \"$Id: intr.c,v 1.75 1997/02/07 09:00:36 makoto Exp $\"\n"
        "\t.align 2\n");

OBJECT_END();
