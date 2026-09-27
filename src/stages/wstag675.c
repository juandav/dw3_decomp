#include "common.h"
#include "stage.h"
extern void (*D_800A6348[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag675", func_800A4CA4);

StageTask *func_800A4D38(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6348[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag675", func_800A4D94);

INCLUDE_ASM("asm/stages/nonmatchings/wstag675", func_800A4DC0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag675", func_800A4DEC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag675", func_800A4E4C);
