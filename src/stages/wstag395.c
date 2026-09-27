#include "common.h"
#include "stage.h"
extern void (*D_800A61D4[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag395", func_800A4CA4);

StageTask *func_800A4D7C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A61D4[0]();
    return task;
}

void func_800A4DD8(void) {
    FLAGS_00.applyAction(0x4011, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag395", func_800A4E04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag395", func_800A4E64);
