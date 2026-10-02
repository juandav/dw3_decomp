#include "common.h"
#include "stage.h"
extern void (*D_800A59F0[])(void);
void func_800A5030();

INCLUDE_ASM("asm/stages/nonmatchings/wstag640", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag640", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag640", func_800A4F04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag640", func_800A4F30);

INCLUDE_ASM("asm/stages/nonmatchings/wstag640", func_800A5030);

StageTask *func_800A50B8(void *owner) {
    StageTask *task = createTask(func_800A5030, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A59F0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag640", func_800A5114);
