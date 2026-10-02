#include "common.h"
#include "stage.h"
extern void (*D_800A7620[])(void);
void func_800A5894();

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A52A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A52CC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5868);

void func_800A5894(StageTask *task) {
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

StageTask *func_800A58DC(void *owner) {
    StageTask *task = createTask(func_800A5894, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A7620[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5938);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5998);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5A84);

INCLUDE_ASM("asm/stages/nonmatchings/wstag270", func_800A5B18);
