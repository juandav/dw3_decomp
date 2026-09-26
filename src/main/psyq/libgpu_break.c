#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", BreakDraw);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", IsIdleGPU);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_break", ContinueDraw);

OBJECT_END();
