#include "common.h"
#include "stage.h"
extern void (*D_800A6224[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4CA4);

StageTask *func_800A4D6C(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6224[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4DC8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4E14);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4E60);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4EAC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4EF8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4F44);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4F90);

INCLUDE_ASM("asm/stages/nonmatchings/wstag580", func_800A4FBC);
