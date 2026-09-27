#include "common.h"
#include "stage.h"
extern void (*D_800A5C00[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag295", func_800A4CA4);

StageTask *func_800A4DA4(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5C00[0]();
    return task;
}

void func_800A4E00(void) {
    FLAGS_00.applyAction(0x1C1A, 1);
    FLAGS_00.applyAction(0x404D, 1);
}

void func_800A4E4C(void) {
    FLAGS_00.applyAction(0x4058, 1);
}

void func_800A4E78(void) {
    FLAGS_00.applyAction(0x4059, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag295", func_800A4EA4);
