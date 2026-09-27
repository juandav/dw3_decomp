#include "common.h"
#include "stage.h"
extern void (*D_800A6280[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task) {
    switch (task->header.state) {
    case 0:
    default:
        task->header.nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

StageTask *func_800A4CF0(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A6280[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag465", func_800A4D4C);
