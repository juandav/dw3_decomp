#include "common.h"
#include "stage.h"
extern void (*D_800A5DE0[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4CA8);

StageTask *func_800A4D8C(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5DE0[0]();
    return task;
}

void func_800A4DE8(void) {
    FLAGS_00.applyAction(0x4025, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4E34);

void func_800A4E80(void) {
    FLAGS_00.applyAction(0x402F, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4ECC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4F18);
