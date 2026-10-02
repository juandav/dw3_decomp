#include "common.h"
#include "stage.h"
extern void (*D_800A6EAC[])(void);
void func_800A4CA8();

INCLUDE_ASM("stages/nonmatchings/wstag200", func_800A4CA8);

StageTask *func_800A4D40(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6EAC[0]();
    return task;
}

void func_800A4D9C(void) {
    FLAGS_00.applyAction(0x400D, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

void func_800A4DE8(void) {
    GAME_PROGRESS = 4;
}

INCLUDE_ASM("stages/nonmatchings/wstag200", func_800A4DF8);
