#include "common.h"
#include "stage.h"
extern u8 D_800A5548[];
extern u8 D_800A5880[];
extern u8 D_800A55F0[];
extern u8 D_800A5564[];
extern u8 D_800A57BC[];
extern u8 D_800A55F8[];
void func_800A4D98();
extern void (*D_800A587C[])(void);
void func_800A4F30();

s32 func_800A4CA4(Anim *anim, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        anim->timer -= dt;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (frame->id == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A4CA4(anim, frames, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4D98);

void *func_800A4F04(void) {
    return createTask(func_800A4D98, 0x5C, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4F30);

StageTask *func_800A4F94(void *owner) {
    StageTask *task = createTask(func_800A4F30, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A587C[0]();
    return task;
}

void func_800A4FF0(void) {
    FLAGS_00.applyAction(0x400C, 1);
}

void func_800A501C(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x234;
    D_800990B4.unkC = 0x2350000;
    D_800990B4.unk10 = D_800A55F8;
    D_800990B4.unk14 = D_800A57BC;
    D_800990B4.unk1C = 0x312;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x4D700;
    D_800990B4.unk30 = 0x4B700;
    D_800990B4.unk28 = D_800A5564;
    D_800990B4.unk3C = 0x38;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A55F0;
    D_800990B4.events = D_800A5880;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5548;
    D_8009A70C.unk40(0, 0x2350002);
    D_8009A70C.unk40(7, 0x2350001);
    D_8009A70C.unk40(4, 0x2350003);
    D_8009A70C.unk50(0);
}
