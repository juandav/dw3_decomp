#include "common.h"
#include "stage.h"
extern void (*D_800A5854[])(void);
void func_800A52A0();

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A4DA0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A4E9C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A5140);

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A5270);

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A52A0);

StageTask *func_800A5318(void *owner) {
    StageTask *task = func_800144DC(func_800A52A0, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5854[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag680", func_800A5374);
