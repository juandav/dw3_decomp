#include "common.h"
#include "stage.h"
extern void (*D_800A5928[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag755", func_800A4CA8);

StageTask *func_800A4D30(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5928[0]();
    return task;
}

void func_800A4D8C(void) {
    FLAGS_00.applyAction(0x4001, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag755", func_800A4DD8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag755", func_800A4E10);
