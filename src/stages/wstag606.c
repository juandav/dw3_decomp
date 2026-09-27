#include "common.h"
#include "stage.h"
extern void (*D_800A56D8[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x407E, 1) && FLAGS_00.checkCondition(0x407F, 0)) {
            children[0] = func_80084B80(0x50A);
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
    D_800A56D8[0]();
    return task;
}

void func_800A4DA0(void) {
    FLAGS_00.applyAction(0x407E, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4DEC(void) {
    FLAGS_00.applyAction(0x407F, 1);
    FLAGS_00.applyAction(0x8B0E, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag606", func_800A4E38);
