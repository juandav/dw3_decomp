#include "common.h"
#include "stage.h"
void func_800A4DB4();
extern void (*D_800A5C44[])(void);
void func_800A50EC();

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A4DB4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A5028);

void *func_800A5090(s32 arg) {
    return createTaskWithId(func_800A4DB4, 0x70, 0, arg);
}

void *func_800A50C0(void) {
    return createTask(func_800A4DB4, 0x70, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A50EC);

StageTask *func_800A518C(void *owner) {
    StageTask *task = createTask(func_800A50EC, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5C44[0]();
    return task;
}

void func_800A51E8(void) {
    GAME_PROGRESS = 38;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag226", func_800A51F8);
