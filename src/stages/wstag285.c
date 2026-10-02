#include "common.h"
#include "stage.h"
extern void (*D_800A5BA0[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag285", func_800A4CA4);

StageTask *func_800A4D70(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5BA0[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag285", func_800A4DCC);

void func_800A4DF8(void) {
    FLAGS_00.applyAction(0x1C0C, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag285", func_800A4E24);
