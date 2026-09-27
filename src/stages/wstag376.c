#include "common.h"
#include "stage.h"
extern void (*D_800A572C[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4078, 1) && FLAGS_00.checkCondition(0x4079, 0)) {
            children[0] = func_80084B80(0x504);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4D48(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A572C[0]();
    return task;
}

void func_800A4DA4(void) {
    FLAGS_00.applyAction(0x4078, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

void func_800A4DF0(void) {
    FLAGS_00.applyAction(0x4079, 1);
    FLAGS_00.applyAction(0x8AF2, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag376", func_800A4E3C);
