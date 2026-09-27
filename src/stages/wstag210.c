#include "common.h"
#include "stage.h"
extern void (*D_800A8EF0[])(void);
void func_800A6248();

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A4D38);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A568C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A56B8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A5C54);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A5C80);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A621C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A6248);

StageTask *func_800A6310(void *owner) {
    StageTask *task = createTask(func_800A6248, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A8EF0[0]();
    return task;
}

void func_800A636C(void) {
    FLAGS_00.applyAction(0x4005, 1);
    FLAGS_00.applyAction(0x1C0B, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A63B8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A63EC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A6550);

INCLUDE_ASM("asm/stages/nonmatchings/wstag210", func_800A65E4);
