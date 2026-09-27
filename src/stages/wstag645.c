#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A55B0[])(void);
void func_800A4F30();

INCLUDE_ASM("asm/stages/nonmatchings/wstag645", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag645", func_800A4D98);

void *func_800A4F04(void) {
    return createTask(func_800A4D98, 0x5C, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag645", func_800A4F30);

StageTask *func_800A4F94(void *owner) {
    StageTask *task = createTask(func_800A4F30, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A55B0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag645", func_800A4FF0);
