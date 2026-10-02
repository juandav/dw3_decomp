#include "common.h"
#include "stage.h"
extern u8 D_800A5C04[];
extern u8 D_800A5A74[];
extern u8 D_800A56AC[];
extern u8 D_800A5BB8[];
extern u8 D_800A5ACC[];
extern void (*D_800A5C00[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag295", func_800A4CA4);

StageTask *func_800A4DA4(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5C00[0]();
    return task;
}

void func_800A4E00(void) {
    FLAGS_00.applyAction(0x1C1A, 1);
    FLAGS_00.applyAction(0x404D, 1);
}

void func_800A4E4C(void) {
    FLAGS_00.applyAction(0x4058, 1);
}

void func_800A4E78(void) {
    FLAGS_00.applyAction(0x4059, 1);
}

void func_800A4EA4(void) {
    D_800990B4.unk44 = 0xF0;
    D_800990B4.unk8 = 0x5FE;
    D_800990B4.unkC = 0x5FF0000;
    D_800990B4.unk10 = D_800A5ACC;
    D_800990B4.unk14 = D_800A5BB8;
    D_800990B4.unk1C = 0x5FD;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x18400;
    D_800990B4.unk30 = 0xE400;
    D_800990B4.unk28 = D_800A56AC;
    D_800990B4.unk3C = 0x1F;
    D_800990B4.unk40 = 0x607C0000;
    D_800990B4.unk4C = D_800A5A74;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5C04;
    D_8009A70C.unk40(0, 0x5FF0001);
    D_8009A70C.unk40(7, 0x5FF0002);
    D_8009A70C.unk50(0);
}
