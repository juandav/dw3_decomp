#include "common.h"
#include "stage.h"
extern void (*D_800A6EAC[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag200", func_800A4CA8);

StageTask *func_800A4D40(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6EAC[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag200", func_800A4D9C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag200", func_800A4DE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag200", func_800A4DF8);
