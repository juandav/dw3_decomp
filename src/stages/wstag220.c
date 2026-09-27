#include "common.h"
#include "stage.h"
void func_800A58C8();
void func_800A5300();
void func_800A4D38();
extern void (*D_800A7010[])(void);
void func_800A5E90();

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A4D38);

void *func_800A52D4(void) {
    return createTask(func_800A4D38, 0x64, 0x14);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A5300);

void *func_800A589C(void) {
    return createTask(func_800A5300, 0x64, 0x14);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A58C8);

void *func_800A5E64(void) {
    return createTask(func_800A58C8, 0x64, 0x14);
}

void func_800A5E90(StageTask *task) {
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

StageTask *func_800A5ED8(void *owner) {
    StageTask *task = createTask(func_800A5E90, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7010[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A5F34);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A608C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag220", func_800A6120);
