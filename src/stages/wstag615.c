#include "common.h"
#include "stage.h"
extern void (*D_800A6324[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag615", func_800A4CA8);

StageTask *func_800A4D3C(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6324[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag615", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag615", func_800A4DE4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag615", func_800A4DF4);
