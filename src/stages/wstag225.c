#include "common.h"
#include "stage.h"
void func_800A4DB4();
extern void (*D_800A59F8[])(void);
void func_800A5100();

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A4DB4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A5038);

void *func_800A50A4(s32 arg) {
    return createTaskWithId(func_800A4DB4, 0x70, 0, arg);
}

void *func_800A50D4(void) {
    return createTask(func_800A4DB4, 0x70, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A5100);

StageTask *func_800A5178(void *owner) {
    StageTask *task = createTask(func_800A5100, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A59F8[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A51D4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag225", func_800A51E4);
