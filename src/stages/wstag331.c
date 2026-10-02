#include "common.h"
#include "stage.h"
extern void (*D_800A68DC[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4CF0(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A68DC[0]();
    return task;
}

void func_800A4D4C(void) {
    FLAGS_00.applyAction(0x405C, 1);
}

void func_800A4D78(void) {
    FLAGS_00.applyAction(0x406A, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag331", func_800A4DA4);
