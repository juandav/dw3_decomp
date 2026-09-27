#include "common.h"
#include "stage.h"
extern void (*D_800A5AA0[])(void);
void func_800A4F30();

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4F04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4F30);

StageTask *func_800A4F94(void *owner) {
    StageTask *task = func_800144DC(func_800A4F30, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5AA0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4FF0);
