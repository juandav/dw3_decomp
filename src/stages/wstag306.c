#include "common.h"
#include "stage.h"
void func_800A4D7C();
extern void (*D_800A5AD4[])(void);
void func_800A4F78();

INCLUDE_ASM("stages/nonmatchings/wstag306", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag306", func_800A4D7C);

INCLUDE_ASM("stages/nonmatchings/wstag306", func_800A4EDC);

void *func_800A4F48(s32 arg) {
    return createTaskWithId(func_800A4D7C, 0x5C, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag306", func_800A4F78);

StageTask *func_800A5024(void *owner) {
    StageTask *task = createTask(func_800A4F78, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5AD4[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag306", func_800A5080);
