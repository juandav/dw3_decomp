#include "common.h"
#include "stage.h"
extern void (*D_800A57FC[])(void);
void func_800A51B8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag261", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag261", func_800A50DC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag261", func_800A5150);

INCLUDE_ASM("asm/stages/nonmatchings/wstag261", func_800A51B8);

StageTask *func_800A5210(void *owner) {
    StageTask *task = createTask(func_800A51B8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A57FC[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag261", func_800A526C);
