#include "common.h"
#include "stage.h"
extern void (*D_800A5620[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task) {
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

StageTask *func_800A4CEC(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5620[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag316", func_800A4D48);
