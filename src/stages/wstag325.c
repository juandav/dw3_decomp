#include "common.h"
#include "stage.h"
void func_800A4CA4();
extern void (*D_800A5A08[])(void);
void func_800A4E8C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag325", func_800A4CA4);

void *func_800A4E24(s32 arg) {
    return createTaskWithId(func_800A4CA4, 0x50, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag325", func_800A4E54);

void func_800A4E8C(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (FLAGS_00.checkCondition(0x4008, 1) && FLAGS_00.checkCondition(0x4009, 0)) {
            children[1] = func_80084B80(0x178);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4F2C(void *owner) {
    StageTask *task = createTask(func_800A4E8C, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5A08[0]();
    return task;
}

void func_800A4F88(void) {
    FLAGS_00.applyAction(0x4008, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4FD4(void) {
    FLAGS_00.applyAction(0x4009, 1);
    FLAGS_00.applyAction(0x8674, 1);
}

void func_800A5020(void) {
    GAME_PROGRESS = 22;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag325", func_800A5030);
