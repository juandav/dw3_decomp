#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A550C[])(void);
void func_800A4EBC();

INCLUDE_ASM("asm/stages/nonmatchings/wstag232", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag232", func_800A4D98);

void *func_800A4E90(void) {
    return createTask(func_800A4D98, 0x58, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag232", func_800A4EBC);

StageTask *func_800A4F20(void *owner) {
    StageTask *task = createTask(func_800A4EBC, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A550C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag232", func_800A4F7C);
