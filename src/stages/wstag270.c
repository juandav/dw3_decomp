#include "common.h"
#include "stage.h"
extern void (*D_800A7620[])(void);
void func_800A5894();

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

StageTask *func_800A58DC(void *owner) {
    StageTask *task = func_800144DC(func_800A5894, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7620[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5938);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5998);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5A84);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5B18);
