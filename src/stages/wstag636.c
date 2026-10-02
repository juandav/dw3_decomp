#include "common.h"
#include "stage.h"
extern u8 D_800A53FC[];
extern u8 D_800A55D4[];
extern u8 D_800A5418[];
extern u8 D_800A5698[];
extern u8 D_800A55E4[];
extern void (*D_800A5710[])(void);
void func_800A4DA4();

INCLUDE_ASM("stages/nonmatchings/wstag636", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag636", func_800A4DA4);

StageTask *func_800A4E18(void *owner) {
    StageTask *task = createTask(func_800A4DA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5710[0]();
    return task;
}

void func_800A4E74(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x626;
    D_800990B4.unkC = 0x6270000;
    D_800990B4.unk10 = D_800A55E4;
    D_800990B4.unk14 = D_800A5698;
    D_800990B4.unk1C = 0x625;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x11F00;
    D_800990B4.unk30 = 0x2F100;
    D_800990B4.unk28 = D_800A5418;
    D_800990B4.unk3C = 56;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A55D4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A53FC;
    D_8009A70C.unk40(0, 0x6270001);
    D_8009A70C.unk40(7, 0x6270002);
    D_8009A70C.unk40(4, 0x6270003);
    D_8009A70C.unk50(0);
}
