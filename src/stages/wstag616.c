#include "common.h"
#include "stage.h"
extern void (*D_800A59A8[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4080, 1) && FLAGS_00.checkCondition(0x4081, 0)) {
            children[0] = func_80084B80(0x50C);
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
    D_800A59A8[0]();
    return task;
}

void func_800A4DA4(void) {
    FLAGS_00.applyAction(0x4080, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4DF0(void) {
    FLAGS_00.applyAction(0x4081, 1);
    FLAGS_00.applyAction(0x8F42, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag616", func_800A4E3C);
