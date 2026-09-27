#include "psyq.h"

extern volatile u_long *D_80055810;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", BreakDraw);

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
