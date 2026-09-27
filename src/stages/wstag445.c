#include "common.h"
#include "stage.h"
extern void (*D_800A6348[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag445", func_800A4CA8);

StageTask *func_800A4D48(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6348[0]();
    return task;
}

void func_800A4DA4(void) {
    FLAGS_00.applyAction(0x4023, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

void func_800A4DF0(void) {
    FLAGS_00.applyAction(0x4024, 1);
    FLAGS_00.applyAction(0x8006, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag445", func_800A4E3C);
