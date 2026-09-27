#include "common.h"
#include "stage.h"
extern void (*D_800A570C[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4CA4);

StageTask *func_800A4D2C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A570C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4D88);

void func_800A4DBC(void) {
    FLAGS_00.applyAction(0x40A6, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag605", func_800A4E08);
