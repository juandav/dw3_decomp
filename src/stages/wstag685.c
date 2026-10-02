#include "common.h"
#include "stage.h"
extern u8 D_800A5B00[];
extern u8 D_800A5928[];
extern u8 D_800A51DC[];
extern u8 D_800A5A3C[];
extern u8 D_800A5998[];
extern void (*D_800A5AFC[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag685", func_800A4CA4);

StageTask *func_800A4D1C(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5AFC[0]();
    return task;
}

void func_800A4D78(void) {
    GAME_PROGRESS = 16;
}

void func_800A4D88(void) {
    FLAGS_00.applyAction(0x4020, 1);
}

void func_800A4DB4(void) {
    GAME_PROGRESS = 25;
}

void func_800A4DC4(void) {
    D_800990B4.unk44 = 0xD4;
    D_800990B4.unk8 = 0x4B3;
    D_800990B4.unkC = 0x4B40000;
    D_800990B4.unk10 = D_800A5998;
    D_800990B4.unk14 = D_800A5A3C;
    D_800990B4.unk1C = 0x4B2;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x23700;
    D_800990B4.unk30 = 0x1AF00;
    D_800990B4.unk28 = D_800A51DC;
    D_800990B4.unk3C = 0x3C;
    D_800990B4.unk40 = 0x60F00000;
    D_800990B4.unk4C = D_800A5928;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5B00;
    D_8009A70C.unk40(0, 0x4B40001);
    D_8009A70C.unk40(7, 0x4B40002);
    D_8009A70C.unk50(0);
}
