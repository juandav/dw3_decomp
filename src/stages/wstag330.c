#include "common.h"
#include "stage.h"
extern void (*D_800A6DEC[])(void);
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
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6DEC[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag330", func_800A4D4C);
