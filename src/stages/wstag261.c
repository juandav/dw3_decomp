#include "common.h"
#include "stage.h"
extern u8 D_800A5800[];
extern CVECTOR D_800A4CBC;
extern u8 D_800A56B0[];
extern u8 D_800A5570[];
extern u8 D_800A5784[];
extern u8 D_800A56BC[];
extern void (*D_800A57FC[])(void);
void func_800A51B8();

INCLUDE_ASM("stages/nonmatchings/wstag261", func_800A4CC0);

INCLUDE_ASM("stages/nonmatchings/wstag261", func_800A50DC);

INCLUDE_ASM("stages/nonmatchings/wstag261", func_800A5150);

INCLUDE_ASM("stages/nonmatchings/wstag261", func_800A51B8);

StageTask *func_800A5210(void *owner) {
    StageTask *task = createTask(func_800A51B8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A57FC[0]();
    return task;
}

void func_800A526C(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x516;
    D_800990B4.unkC = 0x5170000;
    D_800990B4.unk10 = D_800A56BC;
    D_800990B4.unk14 = D_800A5784;
    D_800990B4.unk1C = 0x515;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x10300;
    D_800990B4.unk30 = 0x18500;
    D_800990B4.unk28 = D_800A5570;
    D_800990B4.unk3C = 0x42;
    D_800990B4.unk4C = D_800A56B0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk40 = 0x61080002;
    D_800990B4.unk38 = D_800A4CBC;
    D_800990B4.events = D_800A5800;
    D_8009A70C.unk40(0, 0x5170001);
    D_8009A70C.unk40(1, 0x5170003);
    D_8009A70C.unk40(7, 0x5170002);
    D_8009A70C.unk50(0);
}
