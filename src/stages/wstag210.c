#include "common.h"
#include "stage.h"
void func_800A5C80();
void func_800A56B8();
void func_800A4D38();
extern void (*D_800A8EF0[])(void);
void func_800A6248();

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A4D38);

void *func_800A568C(void) {
    return createTask(func_800A4D38, 0x84, 0x28);
}

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A56B8);

void *func_800A5C54(void) {
    return createTask(func_800A56B8, 0x64, 0x14);
}

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A5C80);

void *func_800A621C(void) {
    return createTask(func_800A5C80, 0x64, 0x14);
}

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A6248);

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

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A63B8);

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A63EC);

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A6550);

INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A65E4);
