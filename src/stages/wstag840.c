#include "common.h"
#include "stage.h"
extern void (*D_800A69A4[])(void);
void func_800A4DA8();

INCLUDE_ASM("stages/nonmatchings/wstag840", func_800A4CA8);

INCLUDE_ASM("stages/nonmatchings/wstag840", func_800A4DA8);

StageTask *func_800A4E14(void *owner) {
    StageTask *task = createTask(func_800A4DA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A69A4[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag840", func_800A4E70);
