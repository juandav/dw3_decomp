#include "common.h"
#include "stage.h"
extern void (*D_800A5C10[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag440", func_800A4CA8);

StageTask *func_800A4D14(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5C10[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag440", func_800A4D70);

INCLUDE_ASM("asm/stages/nonmatchings/wstag440", func_800A4D80);
