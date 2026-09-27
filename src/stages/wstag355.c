#include "common.h"
#include "stage.h"

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag355", func_800A4CEC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag355", func_800A4D48);
