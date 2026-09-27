#include "common.h"
#include "stage.h"
extern void (*D_800A5BA0[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag285", func_800A4CA4);

StageTask *func_800A4D70(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5BA0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag285", func_800A4DCC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag285", func_800A4DF8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag285", func_800A4E24);
