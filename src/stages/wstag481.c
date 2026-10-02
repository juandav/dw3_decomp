#include "common.h"
#include "stage.h"
extern void (*D_800A5E6C[])(void);
void func_800A5054();

INCLUDE_ASM("asm/stages/nonmatchings/wstag481", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag481", func_800A4CBC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag481", func_800A4E48);

INCLUDE_ASM("asm/stages/nonmatchings/wstag481", func_800A5028);

INCLUDE_ASM("asm/stages/nonmatchings/wstag481", func_800A5054);

StageTask *func_800A50B8(void *owner) {
    StageTask *task = createTask(func_800A5054, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5E6C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag481", func_800A5114);
