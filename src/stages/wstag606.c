#include "common.h"
#include "stage.h"
extern void (*D_800A56D8[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag606", func_800A4CA4);

StageTask *func_800A4D44(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A56D8[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag606", func_800A4DA0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag606", func_800A4DEC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag606", func_800A4E38);
