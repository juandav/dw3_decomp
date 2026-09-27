#include "common.h"
#include "stage.h"
void func_800A4DB8();
extern void (*D_800A7D50[])(void);
void func_800A50F0();

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A4D80);

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A4DB8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A500C);

void *func_800A50C0(s32 arg) {
    return createTaskWithId(func_800A4DB8, 0x70, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A50F0);

StageTask *func_800A52A0(void *owner) {
    StageTask *task = createTask(func_800A50F0, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A7D50[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A52FC);

void func_800A530C(void) {
    FLAGS_00.applyAction(0x4005, 1);
    FLAGS_00.applyAction(0x4004, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A5358);

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A5368);

INCLUDE_ASM("asm/stages/nonmatchings/wstag212", func_800A539C);
