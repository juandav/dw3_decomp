#include "common.h"
#include "stage.h"
extern void (*D_800A5698[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag575", func_800A4CA4);

StageTask *func_800A4D38(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5698[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag575", func_800A4D94);

INCLUDE_ASM("asm/stages/nonmatchings/wstag575", func_800A4DC0);
