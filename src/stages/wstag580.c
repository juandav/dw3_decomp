#include "common.h"
#include "stage.h"
extern void (*D_800A6224[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag580", func_800A4CA4);

StageTask *func_800A4D6C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6224[0]();
    return task;
}

void func_800A4DC8(void) {
    FLAGS_00.applyAction(0x403C, 1);
    FLAGS_00.applyAction(0x1C1F, 1);
}

void func_800A4E14(void) {
    FLAGS_00.applyAction(0x4021, 1);
    FLAGS_00.applyAction(0x1C20, 1);
}

void func_800A4E60(void) {
    FLAGS_00.applyAction(0x4034, 1);
    FLAGS_00.applyAction(0x1C22, 1);
}

void func_800A4EAC(void) {
    FLAGS_00.applyAction(0x4035, 1);
    FLAGS_00.applyAction(0x1C23, 1);
}

void func_800A4EF8(void) {
    FLAGS_00.applyAction(0x4036, 1);
    FLAGS_00.applyAction(0x1C24, 1);
}

void func_800A4F44(void) {
    FLAGS_00.applyAction(0x4037, 1);
    FLAGS_00.applyAction(0x1C25, 1);
}

void func_800A4F90(void) {
    FLAGS_00.applyAction(0x4038, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag580", func_800A4FBC);
