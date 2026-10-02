#include "common.h"
#include "stage.h"
extern u8 D_800A5440[];
extern u8 D_800A5DE4[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5738[];
extern u8 D_800A545C[];
extern u8 D_800A5CF0[];
extern u8 D_800A5760[];
extern void (*D_800A5DE0[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag490", func_800A4CA8);

StageTask *func_800A4D8C(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5DE0[0]();
    return task;
}

void func_800A4DE8(void) {
    FLAGS_00.applyAction(0x4025, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4E34(void) {
    FLAGS_00.applyAction(0x4026, 1);
    FLAGS_00.applyAction(0x8022, 1);
}

void func_800A4E80(void) {
    FLAGS_00.applyAction(0x402F, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

void func_800A4ECC(void) {
    FLAGS_00.applyAction(0x4030, 1);
    FLAGS_00.applyAction(0x818B, 1);
}

void func_800A4F18(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x3EE;
    D_800990B4.unkC = 0x3EF0000;
    D_800990B4.unk10 = D_800A5760;
    D_800990B4.unk14 = D_800A5CF0;
    D_800990B4.unk1C = 0x3ED;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x33900;
    D_800990B4.unk30 = 0x3D200;
    D_800990B4.unk28 = D_800A545C;
    D_800990B4.unk3C = 0x35;
    D_800990B4.unk40 = 0x60D40000;
    D_800990B4.unk4C = D_800A5738;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.events = D_800A5DE4;
    D_800990B4.unk20 = D_800A5440;
    D_8009A70C.unk40(0, 0x3EF0001);
    D_8009A70C.unk40(7, 0x3EF0002);
    D_8009A70C.unk40(4, 0x3EF0003);
    D_8009A70C.unk50(0);
}
