#include "common.h"
#include "stage.h"
extern void (*D_800A5A0C[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4CA8);

StageTask *func_800A4D64(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5A0C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4DC0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4E0C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4E44);
