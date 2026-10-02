#include "common.h"
#include "stage.h"
extern void (*D_800A5ACC[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag475", func_800A4CA4);

StageTask *func_800A4E4C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5ACC[0]();
    return task;
}

void func_800A4EA8(void) {
    FLAGS_00.applyAction(0x1A17, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag475", func_800A4ED4);

INCLUDE_ASM("stages/nonmatchings/wstag475", func_800A4F0C);
