#include "common.h"
#include "stage.h"
void func_800A4D7C();
extern void (*D_800A857C[])(void);
void func_800A4F78();

INCLUDE_ASM("asm/stages/nonmatchings/wstag305", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag305", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag305", func_800A4EDC);

void *func_800A4F48(s32 arg) {
    return createTaskWithId(func_800A4D7C, 0x5C, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag305", func_800A4F78);

StageTask *func_800A526C(void *owner) {
    StageTask *task = createTask(func_800A4F78, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A857C[0]();
    return task;
}

void func_800A52C8(void) {
    FLAGS_00.applyAction(0x1C0D, 1);
}

void func_800A52F4(void) {
    FLAGS_00.applyAction(0x1C0E, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag305", func_800A5320);

void func_800A534C(void) {
    GAME_PROGRESS = 23;
}

void func_800A535C(void) {
    FLAGS_00.applyAction(0x4057, 1);
}

void func_800A5388(void) {
    GAME_PROGRESS = 34;
}

void func_800A5398(void) {
    FLAGS_00.applyAction(0x1C39, 1);
}

void func_800A53C4(void) {
    GAME_PROGRESS = 34;
}

void func_800A53D4(void) {
    FLAGS_00.applyAction(0x4069, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag305", func_800A5400);
