#include "common.h"
#include "stage.h"
extern void (*D_800A6348[])(void);
void func_800A4E28();

INCLUDE_ASM("asm/stages/nonmatchings/wstag375", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag375", func_800A4DFC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag375", func_800A4E28);

StageTask *func_800A4EDC(void *owner) {
    StageTask *task = createTask(func_800A4E28, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A6348[0]();
    return task;
}

void func_800A4F38(void) {
    FLAGS_00.applyAction(0x4053, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag375", func_800A4F84);

INCLUDE_ASM("asm/stages/nonmatchings/wstag375", func_800A4FD0);
