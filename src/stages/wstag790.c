#include "common.h"
#include "stage.h"
extern void (*D_800A583C[])(void);
void func_800A5150();

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A4F94);

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A4FCC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A4FFC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A50E8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A5120);

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A5150);

StageTask *func_800A51E0(void *owner) {
    StageTask *task = createTask(func_800A5150, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A583C[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag790", func_800A523C);
