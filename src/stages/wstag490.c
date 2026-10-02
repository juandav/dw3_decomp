#include "common.h"
#include "stage.h"
extern void (*D_800A5DE0[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4CA8);

StageTask *func_800A4D8C(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5DE0[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4DE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4E34);

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4E80);

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4ECC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4F18);
