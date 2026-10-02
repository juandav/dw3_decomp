#include "common.h"
#include "stage.h"
extern void (*D_800A695C[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task) {
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

StageTask *func_800A4CEC(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A695C[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x400A, 1);
    FLAGS_00.applyAction(0x1A32, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag500", func_800A4D94);
