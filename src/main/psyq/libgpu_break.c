#include "psyq.h"

extern volatile u_long *D_80055810;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", BreakDraw);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", IsIdleGPU);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", ContinueDraw);

OBJECT_END();
