#include "common.h"
#include "stage.h"
extern void (*D_800A5F04[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag550", func_800A4CA8);

StageTask *func_800A4D48(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5F04[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag550", func_800A4DA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag550", func_800A4DF0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag550", func_800A4E3C);
