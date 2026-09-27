#include "common.h"
#include "stage.h"
extern void (*D_800A5E28[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag421", func_800A4CA4);

StageTask *func_800A4DE0(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5E28[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag421", func_800A4E3C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag421", func_800A4E88);

INCLUDE_ASM("asm/stages/nonmatchings/wstag421", func_800A4ED4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag421", func_800A4EE4);
