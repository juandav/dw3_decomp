#include "common.h"
#include "stage.h"
extern void (*D_800A570C[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4CA4);

StageTask *func_800A4D2C(void *owner) {
    StageTask *task = func_800144DC(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A570C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4D88);

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4DBC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4E08);
