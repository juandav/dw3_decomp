#include "common.h"
#include "stage.h"
extern void (*D_800A6624[])(void);

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
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0x50);

    task->owner = owner;
    D_800A6624[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag355", func_800A4D48);
