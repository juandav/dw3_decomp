#include "common.h"
#include "stage.h"
extern void (*D_800A67D0[])(void);
void func_800A529C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag280", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag280", func_800A5270);

INCLUDE_ASM("asm/stages/nonmatchings/wstag280", func_800A529C);

StageTask *func_800A535C(void *owner) {
    StageTask *task = createTask(func_800A529C, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A67D0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag280", func_800A53B8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag280", func_800A54A4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag280", func_800A5538);
