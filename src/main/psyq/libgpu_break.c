#include "psyq.h"

extern volatile u_long *D_80055800;
extern volatile u_long *D_80055808;
extern volatile u_long *D_80055810;

u_long *BreakDraw(void) {
    volatile u_long addr;

    if (!(*D_80055808 & 0x01000000)) {
        return 0;
    }
    if (((*D_80055808 & 0x700) >> 8) == 4) {
        *D_80055808 &= ~0x01000000;
        addr = *D_80055808;
        addr = *D_80055800;
        if ((addr & 0xFFFFFF) == 0xFFFFFF) {
            return 0;
        }
        return (u_long *)addr;
    }
    return (u_long *)-1;
}

int IsIdleGPU(int max_count) {
    int count = 0;

    while (!(*D_80055810 & 0x04000000)) {
        if (count++ > max_count) {
            return -1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", ContinueDraw);

OBJECT_END();
