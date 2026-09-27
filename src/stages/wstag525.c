#include "common.h"
#include "stage.h"
extern void (*D_800A5CA8[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x402B, 1) && FLAGS_00.checkCondition(0x402C, 0)) {
            children[0] = func_80084B80(0x4FA);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4D44(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5CA8[0]();
    return task;
}

void func_800A4DA0(void) {
    FLAGS_00.applyAction(0x4003, 1);
}

void func_800A4DCC(void) {
    FLAGS_00.applyAction(0x402B, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4E18(void) {
    FLAGS_00.applyAction(0x402C, 1);
    FLAGS_00.applyAction(0x8013, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag525", func_800A4E64);
