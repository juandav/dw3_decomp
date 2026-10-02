#include "common.h"
#include "stage.h"
extern u8 D_800A5274[];
extern u8 D_800A569C[];
extern u8 D_800A5334[];
extern u8 D_800A5290[];
extern u8 D_800A5620[];
extern u8 D_800A533C[];
extern void (*D_800A5698[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag575", func_800A4CA4);

StageTask *func_800A4D38(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5698[0]();
    return task;
}

void func_800A4D94(void) {
    FLAGS_00.applyAction(0x40A2, 1);
}

void func_800A4DC0(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x470;
    D_800990B4.unkC = 0x4710000;
    D_800990B4.unk10 = D_800A533C;
    D_800990B4.unk14 = D_800A5620;
    D_800990B4.unk1C = 0x46F;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x15C00;
    D_800990B4.unk30 = 0xF800;
    D_800990B4.unk28 = D_800A5290;
    D_800990B4.unk3C = 0x39;
    D_800990B4.unk40 = 0x60E40000;
    D_800990B4.unk4C = D_800A5334;
    D_800990B4.events = D_800A569C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5274;
    D_8009A70C.unk40(0, 0x4710001);
    D_8009A70C.unk40(7, 0x4710002);
    D_8009A70C.unk40(4, 0x4710003);
    D_8009A70C.unk50(0);
}
