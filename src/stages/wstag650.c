#include "common.h"
#include "stage.h"
extern void (*D_800A5C6C[])(void);
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
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5C6C[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x7C15, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag650", func_800A4D74);
