#include "common.h"
#include "stage.h"
extern void (*D_800A52BC[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag585", func_800A4CA4);

StageTask *func_800A4D4C(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A52BC[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag585", func_800A4DA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag585", func_800A4DD4);
