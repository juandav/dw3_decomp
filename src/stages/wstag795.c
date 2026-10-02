#include "common.h"
#include "stage.h"
extern u8 D_800A61E8[];
extern u8 D_800A5B50[];
extern u8 D_800A5F7C[];
extern u8 D_800A5B6C[];
extern u8 D_800A613C[];
extern u8 D_800A5FB0[];
void func_800A5240();
void func_800A4DC4();
extern void (*D_800A61E4[])(void);
void func_800A543C();

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A4DC4);

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A5044);

void *func_800A5094(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x68, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A50C4);

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A50F8);

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A5240);

void *func_800A5410(void) {
    return createTask(func_800A5240, 0x54, 0x4);
}

INCLUDE_ASM("stages/nonmatchings/wstag795", func_800A543C);

StageTask *func_800A5518(void *owner) {
    StageTask *task = createTask(func_800A543C, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A61E4[0]();
    return task;
}

void func_800A5574(void) {
    FLAGS_00.applyAction(0x4043, 1);
}

void func_800A55A0(void) {
    FLAGS_00.applyAction(0x1C05, 1);
    FLAGS_00.applyAction(0x4063, 1);
}

void func_800A55EC(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x711;
    D_800990B4.unkC = 0x6E60000;
    D_800990B4.unk10 = D_800A5FB0;
    D_800990B4.unk14 = D_800A613C;
    D_800990B4.unk1C = 0x6E2;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x4B200;
    D_800990B4.unk30 = 0x3AA00;
    D_800990B4.unk28 = D_800A5B6C;
    D_800990B4.unk3C = 0xD;
    D_800990B4.unk40 = 0x60340000;
    D_800990B4.unk4C = D_800A5F7C;
    D_800990B4.unk20 = D_800A5B50;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A61E8;
    D_8009A70C.unk40(0, 0x6E60001);
    D_8009A70C.unk40(7, 0x6E60002);
    D_8009A70C.unk40(4, 0x6E60003);
    D_8009A70C.unk50(0);
}
