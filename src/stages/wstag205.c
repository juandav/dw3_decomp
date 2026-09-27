#include "common.h"
#include "stage.h"
extern void (*D_800A688C[])(void);
void func_800A4FA0();

INCLUDE_ASM("asm/stages/nonmatchings/wstag205", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag205", func_800A4F74);

INCLUDE_ASM("asm/stages/nonmatchings/wstag205", func_800A4FA0);

StageTask *func_800A5058(void *owner) {
    StageTask *task = createTask(func_800A4FA0, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A688C[0]();
    return task;
}

void func_800A50B4(void) {
    FLAGS_00.applyAction(0x4006, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5100(void) {
    FLAGS_00.applyAction(0x4016, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag205", func_800A512C);
