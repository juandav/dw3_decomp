#include "common.h"
#include "stage.h"
void func_800A4F90();
extern void (*D_800A6614[])(void);
void func_800A58AC();

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A4CA8);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A4E28);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A4E60);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A4E90);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A4F90);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5288);

void *func_800A52E0(s32 arg) {
    return createTaskWithId(func_800A4F90, 0x70, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5310);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5464);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5528);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A55E8);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5854);

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A58AC);

StageTask *func_800A5A08(void *owner) {
    StageTask *task = createTask(func_800A58AC, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A6614[0]();
    return task;
}

void func_800A5A64(void) {
    FLAGS_00.applyAction(0x4046, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5AB0);

void func_800A5ADC(void) {
    FLAGS_00.applyAction(0x4065, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag805", func_800A5B08);
