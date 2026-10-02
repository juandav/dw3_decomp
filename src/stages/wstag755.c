#include "common.h"
#include "stage.h"
extern u8 D_800A592C[];
extern u8 D_800A52B4[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A5674[];
extern u8 D_800A52D0[];
extern u8 D_800A5838[];
extern u8 D_800A56AC[];
extern void (*D_800A5928[])(void);
void func_800A4CA8();

INCLUDE_ASM("stages/nonmatchings/wstag755", func_800A4CA8);

StageTask *func_800A4D30(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5928[0]();
    return task;
}

void func_800A4D8C(void) {
    FLAGS_00.applyAction(0x4001, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag755", func_800A4DD8);

void func_800A4E10(void) {
    D_800990B4.unk44 = 0xD4;
    D_800990B4.unk8 = 0x6C2;
    D_800990B4.unkC = 0x6C30000;
    D_800990B4.unk10 = D_800A56AC;
    D_800990B4.unk14 = D_800A5838;
    D_800990B4.unk1C = 0x6C1;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x19200;
    D_800990B4.unk30 = 0x34F00;
    D_800990B4.unk28 = D_800A52D0;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A5674;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A52B4;
    D_800990B4.events = D_800A592C;
    D_8009A70C.unk40(0, 0x6C30001);
    D_8009A70C.unk40(7, 0x6C30002);
    D_8009A70C.unk50(0);
}
