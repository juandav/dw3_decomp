#include "common.h"
#include "stage.h"
extern void (*D_800A5F3C[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag520", func_800A4CA4);

StageTask *func_800A4D38(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5F3C[0]();
    return task;
}

void func_800A4D94(void) {
    FLAGS_00.applyAction(0x4002, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag520", func_800A4DE0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag520", func_800A4E14);

INCLUDE_ASM("asm/stages/nonmatchings/wstag520", func_800A4E24);
