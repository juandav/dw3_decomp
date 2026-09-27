#include "common.h"
#include "stage.h"
extern void (*D_800A5990[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag676", func_800A4CA4);

StageTask *func_800A4D2C(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5990[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag676", func_800A4D88);

INCLUDE_ASM("asm/stages/nonmatchings/wstag676", func_800A4DD4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag676", func_800A4E0C);
