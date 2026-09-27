#include "common.h"
#include "stage.h"
extern u8 D_800A5F9C[];
extern u8 D_800A5488[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A55B4[];
extern u8 D_800A54A4[];
extern u8 D_800A5F50[];
extern u8 D_800A55C0[];
void func_800A4D80();
extern void (*D_800A5F98[])(void);
void func_800A4F04();

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A4D80);

void *func_800A4ED4(s32 arg) {
    return createTaskWithId(func_800A4D80, 0x58, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag455", func_800A4F04);

StageTask *func_800A4F98(void *owner) {
    StageTask *task = createTask(func_800A4F04, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5F98[0]();
    return task;
}

void func_800A4FF4(void) {
    FLAGS_00.applyAction(0x4007, 1);
}

void func_800A5020(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x380;
    D_800990B4.unkC = 0x3810000;
    D_800990B4.unk10 = D_800A55C0;
    D_800990B4.unk14 = D_800A5F50;
    D_800990B4.unk1C = 0x37F;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1FA00;
    D_800990B4.unk30 = 0x21F00;
    D_800990B4.unk28 = D_800A54A4;
    D_800990B4.unk3C = 0x34;
    D_800990B4.unk40 = 0x60D00000;
    D_800990B4.unk4C = D_800A55B4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A5488;
    D_800990B4.events = D_800A5F9C;
    D_8009A70C.unk40(0, 0x3810001);
    D_8009A70C.unk40(7, 0x3810002);
    D_8009A70C.unk40(4, 0x3810003);
    D_8009A70C.unk50(0);
}
