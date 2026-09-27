#include "common.h"
#include "stage.h"
extern void (*D_800A59A8[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag616", func_800A4CA8);

StageTask *func_800A4D48(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A59A8[0]();
    return task;
}

void func_800A4DA4(void) {
    FLAGS_00.applyAction(0x4080, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4DF0(void) {
    FLAGS_00.applyAction(0x4081, 1);
    FLAGS_00.applyAction(0x8F42, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag616", func_800A4E3C);
