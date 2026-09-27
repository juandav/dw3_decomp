#include "common.h"
#include "stage.h"
extern void (*D_800A572C[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag376", func_800A4CA8);

StageTask *func_800A4D48(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A572C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag376", func_800A4DA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag376", func_800A4DF0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag376", func_800A4E3C);
