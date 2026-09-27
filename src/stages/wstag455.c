#include "common.h"
#include "stage.h"
void func_800A4D80();
extern void (*D_800A5F98[])(void);
void func_800A4F04();

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A4D80);

void *func_800A4ED4(s32 arg) {
    return createTaskWithId(func_800A4D80, 0x58, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A4F04);

StageTask *func_800A4F98(void *owner) {
    StageTask *task = createTask(func_800A4F04, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5F98[0]();
    return task;
}

void func_800A4FF4(void) {
    FLAGS_00.applyAction(0x4007, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A5020);
