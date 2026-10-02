#include "common.h"
#include "stage.h"
extern void (*D_800A6324[])(void);
void func_800A4CA8();

INCLUDE_ASM("stages/nonmatchings/wstag615", func_800A4CA8);

StageTask *func_800A4D3C(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6324[0]();
    return task;
}

void func_800A4D98(void) {
    FLAGS_00.applyAction(0x4039, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4DE4(void) {
    GAME_PROGRESS = 19;
}

INCLUDE_ASM("stages/nonmatchings/wstag615", func_800A4DF4);
