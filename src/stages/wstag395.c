#include "common.h"
#include "stage.h"
extern u8 D_800A56DC[];
extern u8 D_800A61D8[];
extern u8 D_800A5E1C[];
extern u8 D_800A56F8[];
extern u8 D_800A612C[];
extern u8 D_800A5E48[];
extern void (*D_800A61D4[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag395", func_800A4CA4);

StageTask *func_800A4D7C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A61D4[0]();
    return task;
}

void func_800A4DD8(void) {
    FLAGS_00.applyAction(0x4011, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag395", func_800A4E04);

void func_800A4E64(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x20B;
    D_800990B4.unkC = 0x20C0000;
    D_800990B4.unk10 = D_800A5E48;
    D_800990B4.unk14 = D_800A612C;
    D_800990B4.unk1C = 0x310;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x30200;
    D_800990B4.unk30 = 0x23500;
    D_800990B4.unk28 = D_800A56F8;
    D_800990B4.unk3C = 0x2E;
    D_800990B4.unk40 = 0x60B80000;
    D_800990B4.unk4C = D_800A5E1C;
    D_800990B4.events = D_800A61D8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A56DC;
    D_8009A70C.unk40(0, 0x20C0001);
    D_8009A70C.unk40(7, 0x20C0002);
    D_8009A70C.unk40(4, 0x20C0003);
    D_8009A70C.unk50(0);
}
