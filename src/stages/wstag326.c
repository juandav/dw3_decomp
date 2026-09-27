#include "common.h"
#include "stage.h"
extern void (*D_800A57B0[])(void);
void func_800A4E8C();

INCLUDE_ASM("asm/stages/nonmatchings/wstag326", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag326", func_800A4E24);

INCLUDE_ASM("asm/stages/nonmatchings/wstag326", func_800A4E54);

INCLUDE_ASM("asm/stages/nonmatchings/wstag326", func_800A4E8C);

StageTask *func_800A4F2C(void *owner) {
    StageTask *task = createTask(func_800A4E8C, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A57B0[0]();
    return task;
}

void func_800A4F88(void) {
    FLAGS_00.applyAction(0x4076, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag326", func_800A4FD4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag326", func_800A5020);
