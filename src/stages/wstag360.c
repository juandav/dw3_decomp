#include "common.h"
#include "stage.h"

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag360", func_800A4CEC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag360", func_800A4D48);

INCLUDE_ASM("asm/stages/nonmatchings/wstag360", func_800A4D74);
