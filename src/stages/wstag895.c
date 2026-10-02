#include "common.h"
#include "stage.h"
extern void (*D_800A9450[])(void);
void func_800A4DA4();

INCLUDE_ASM("stages/nonmatchings/wstag895", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag895", func_800A4DA4);

StageTask *func_800A4E18(void *owner) {
    StageTask *task = createTask(func_800A4DA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A9450[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag895", func_800A4E74);
