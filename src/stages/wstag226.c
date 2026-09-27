#include "common.h"
#include "stage.h"
extern void (*D_800A5C44[])(void);
void func_800A50EC();

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A4DB4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A5028);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A5090);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A50C0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A50EC);

StageTask *func_800A518C(void *owner) {
    StageTask *task = createTask(func_800A50EC, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5C44[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A51E8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A51F8);
