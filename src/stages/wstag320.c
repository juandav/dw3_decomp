#include "common.h"
#include "stage.h"
extern void (*D_800A612C[])(void);
void func_800A4CA8();

INCLUDE_ASM("stages/nonmatchings/wstag320", func_800A4CA8);

StageTask *func_800A4D4C(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A612C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag320", func_800A4DA8);

INCLUDE_ASM("stages/nonmatchings/wstag320", func_800A4DD4);
