#include "common.h"
#include "stage.h"
extern void (*D_800A5834[])(void);
void func_800A4E84();

INCLUDE_ASM("asm/stages/nonmatchings/wstag730", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag730", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag730", func_800A4E58);

INCLUDE_ASM("asm/stages/nonmatchings/wstag730", func_800A4E84);

StageTask *func_800A4EE8(void *owner) {
    StageTask *task = createTask(func_800A4E84, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5834[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag730", func_800A4F44);
