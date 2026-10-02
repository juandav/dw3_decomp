#include "common.h"
#include "stage.h"
extern void (*D_800A5E28[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag421", func_800A4CA4);

StageTask *func_800A4DE0(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5E28[0]();
    return task;
}

void func_800A4E3C(void) {
    FLAGS_00.applyAction(0x40A3, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag421", func_800A4E88);

void func_800A4ED4(void) {
    GAME_PROGRESS = 28;
}

INCLUDE_ASM("stages/nonmatchings/wstag421", func_800A4EE4);
