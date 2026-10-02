#include "common.h"
#include "stage.h"
extern u8 D_800A5710[];
extern u8 D_800A5240[];
extern u8 D_800A5518[];
extern u8 D_800A525C[];
extern u8 D_800A56AC[];
extern u8 D_800A5544[];
extern void (*D_800A570C[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag605", func_800A4CA4);

StageTask *func_800A4D2C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A570C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag605", func_800A4D88);

void func_800A4DBC(void) {
    FLAGS_00.applyAction(0x40A6, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4E08(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x474;
    D_800990B4.unkC = 0x4750000;
    D_800990B4.unk10 = D_800A5544;
    D_800990B4.unk14 = D_800A56AC;
    D_800990B4.unk1C = 0x473;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1E800;
    D_800990B4.unk30 = 0x14000;
    D_800990B4.unk28 = D_800A525C;
    D_800990B4.unk3C = 0x39;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A5518;
    D_800990B4.unk20 = D_800A5240;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5710;
    D_8009A70C.unk40(0, 0x4750001);
    D_8009A70C.unk40(7, 0x4750002);
    D_8009A70C.unk40(4, 0x4750003);
    D_8009A70C.unk50(0);
}
