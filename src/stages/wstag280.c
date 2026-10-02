#include "common.h"
#include "stage.h"
extern u8 D_800A67DC[];
extern u8 D_800A6404[];
extern u8 D_800A5780[];
extern u8 D_800A6758[];
extern u8 D_800A64D0[];
extern void (*D_800A67D0[])(void);
void func_800A529C();

INCLUDE_ASM("stages/nonmatchings/wstag280", func_800A4CA8);

INCLUDE_ASM("stages/nonmatchings/wstag280", func_800A5270);

INCLUDE_ASM("stages/nonmatchings/wstag280", func_800A529C);

StageTask *func_800A535C(void *owner) {
    StageTask *task = createTask(func_800A529C, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A67D0[0]();
    return task;
}

void func_800A53B8(void) {
    D_800990B4.unk44 = 0xCD;
    D_800990B4.unk8 = 0x1A4;
    D_800990B4.unkC = 0x1A50000;
    D_800990B4.unk10 = D_800A64D0;
    D_800990B4.unk14 = D_800A6758;
    D_800990B4.unk1C = 0x3C3;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1BB00;
    D_800990B4.unk30 = 0xF400;
    D_800990B4.unk28 = D_800A5780;
    D_800990B4.unk3C = 8;
    D_800990B4.unk40 = 0x60200000;
    D_800990B4.unk4C = D_800A6404;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A67DC;
    D_8009A70C.unk40(0, 0x1A50002);
    D_8009A70C.unk40(7, 0x1A50001);
    D_8009A70C.unk50(0);
}

INCLUDE_ASM("stages/nonmatchings/wstag280", func_800A54A4);

INCLUDE_ASM("stages/nonmatchings/wstag280", func_800A5538);
