#include "common.h"
#include "stage.h"
extern void (*D_800A7164[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag400", func_800A4CA8);

StageTask *func_800A4D50(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A7164[0]();
    return task;
}

void func_800A4DAC(void) {
    FLAGS_00.applyAction(0x1C4B, 1);
}

void func_800A4DD8(void) {
    FLAGS_00.applyAction(0x1C4C, 1);
}

void func_800A4E04(void) {
    FLAGS_00.applyAction(0x1C4D, 1);
}

void func_800A4E30(void) {
    FLAGS_00.applyAction(0x1C4E, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag400", func_800A4E5C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag400", func_800A4EA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag400", func_800A4F30);
