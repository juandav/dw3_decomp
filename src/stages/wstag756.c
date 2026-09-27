#include "common.h"
#include "stage.h"
extern void (*D_800A5A0C[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4CA8);

StageTask *func_800A4D64(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5A0C[0]();
    return task;
}

void func_800A4DC0(void) {
    FLAGS_00.applyAction(0x405B, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4E0C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4E44);
