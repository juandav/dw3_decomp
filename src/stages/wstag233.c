#include "common.h"
#include "stage.h"
extern void (*D_800A5508[])(void);
void func_800A4EBC();

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4E90);

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4EBC);

StageTask *func_800A4F20(void *owner) {
    StageTask *task = func_800144DC(func_800A4EBC, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5508[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4F7C);
