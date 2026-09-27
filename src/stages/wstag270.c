#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A52A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A52CC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5868);

void func_800A5894(StageTask *task) {
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

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A58DC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5938);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5998);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5A84);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5B18);
