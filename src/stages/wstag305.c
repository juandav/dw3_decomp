#include "common.h"
#include "stage.h"
extern u8 D_800A8580[];
extern u8 D_800A8378[];
extern u8 D_800A6ED0[];
extern u8 D_800A8534[];
extern u8 D_800A8480[];
void func_800A4D7C();
extern void (*D_800A857C[])(void);
void func_800A4F78();

INCLUDE_ASM("stages/nonmatchings/wstag305", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag305", func_800A4D7C);

INCLUDE_ASM("stages/nonmatchings/wstag305", func_800A4EDC);

void *func_800A4F48(s32 arg) {
    return createTaskWithId(func_800A4D7C, 0x5C, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag305", func_800A4F78);

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

INCLUDE_ASM("stages/nonmatchings/wstag305", func_800A5320);

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

void func_800A5400(void) {
    D_800990B4.unk44 = 0xF0;
    D_800990B4.unk8 = 0x33B;
    D_800990B4.unkC = 0x33C0000;
    D_800990B4.unk10 = D_800A8480;
    D_800990B4.unk14 = D_800A8534;
    D_800990B4.unk1C = 0x33A;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x12C00;
    D_800990B4.unk30 = 0x12C00;
    D_800990B4.unk28 = D_800A6ED0;
    D_800990B4.unk3C = 5;
    D_800990B4.unk40 = 0x60140000;
    D_800990B4.unk4C = D_800A8378;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A8580;
    D_8009A70C.unk40(0, 0x33C0001);
    D_8009A70C.unk40(7, 0x33C0002);
    D_8009A70C.unk50(0);
}
