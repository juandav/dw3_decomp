#include "common.h"
#include "stage.h"
extern u8 D_800A5A10[];
extern u8 D_800A52A4[];
extern CVECTOR D_800A4CA4;
extern u8 D_800A574C[];
extern u8 D_800A52C0[];
extern u8 D_800A591C[];
extern u8 D_800A5790[];
extern void (*D_800A5A0C[])(void);
void func_800A4CA8();

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4CA8);

StageTask *func_800A4D64(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5A0C[0]();
    return task;
}

void func_800A4DC0(void) {
    FLAGS_00.applyAction(0x405B, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag756", func_800A4E0C);

void func_800A4E44(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x6C5;
    D_800990B4.unkC = 0x6C60000;
    D_800990B4.unk10 = D_800A5790;
    D_800990B4.unk14 = D_800A591C;
    D_800990B4.unk1C = 0x6C4;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1B000;
    D_800990B4.unk30 = 0x34100;
    D_800990B4.unk28 = D_800A52C0;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A574C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A52A4;
    D_800990B4.events = D_800A5A10;
    D_8009A70C.unk40(0, 0x6C60001);
    D_8009A70C.unk40(7, 0x6C60002);
    D_8009A70C.unk50(0);
}
