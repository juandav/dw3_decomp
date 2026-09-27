#include "common.h"
#include "stage.h"
extern void (*D_800A5CA8[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag525", func_800A4CA4);

StageTask *func_800A4D44(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5CA8[0]();
    return task;
}

void func_800A4DA0(void) {
    FLAGS_00.applyAction(0x4003, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag525", func_800A4DCC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag525", func_800A4E18);

INCLUDE_ASM("asm/stages/nonmatchings/wstag525", func_800A4E64);
