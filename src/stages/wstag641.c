#include "common.h"
#include "stage.h"
extern void (*D_800A5614[])(void);
void func_800A4DA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag641", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag641", func_800A4DA4);

StageTask *func_800A4E18(void *owner) {
    StageTask *task = createTask(func_800A4DA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5614[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag641", func_800A4E74);
