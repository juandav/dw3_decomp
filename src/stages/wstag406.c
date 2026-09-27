#include "common.h"
#include "stage.h"
extern void (*D_800A5958[])(void);
void func_800A4E98();

INCLUDE_ASM("asm/stages/nonmatchings/wstag406", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag406", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag406", func_800A4E6C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag406", func_800A4E98);

StageTask *func_800A4F48(void *owner) {
    StageTask *task = createTask(func_800A4E98, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5958[0]();
    return task;
}

void func_800A4FA4(void) {
    FLAGS_00.applyAction(0x407A, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag406", func_800A4FF0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag406", func_800A503C);
