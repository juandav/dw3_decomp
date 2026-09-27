#include "common.h"
#include "stage.h"
extern void (*D_800A587C[])(void);
void func_800A4F30();

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4D98);

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4F04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4F30);

StageTask *func_800A4F94(void *owner) {
    StageTask *task = createTask(func_800A4F30, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A587C[0]();
    return task;
}

void func_800A4FF0(void) {
    FLAGS_00.applyAction(0x400C, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A501C);
