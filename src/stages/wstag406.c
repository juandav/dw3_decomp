#include "common.h"
#include "stage.h"
extern u8 D_800A595C[];
extern u8 D_800A5530[];
extern u8 D_800A5788[];
extern u8 D_800A554C[];
extern u8 D_800A5820[];
extern u8 D_800A57A0[];
void func_800A4D98();
extern void (*D_800A5958[])(void);
void func_800A4E98();

s32 func_800A4CA4(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A4CA4(anim, frames, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag406", func_800A4D98);

void *func_800A4E6C(void) {
    return createTask(func_800A4D98, 0x54, 0);
}

INCLUDE_ASM("stages/nonmatchings/wstag406", func_800A4E98);

StageTask *func_800A4F48(void *owner) {
    StageTask *task = createTask(func_800A4E98, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5958[0]();
    return task;
}

void func_800A4FA4(void) {
    FLAGS_00.applyAction(0x407A, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A4FF0(void) {
    FLAGS_00.applyAction(0x407B, 1);
    FLAGS_00.applyAction(0x8AF5, 1);
}

void func_800A503C(void) {
    D_800990B4.unk44 = 0xE9;
    D_800990B4.unk8 = 0x733;
    D_800990B4.unkC = 0x7340000;
    D_800990B4.unk10 = D_800A57A0;
    D_800990B4.unk14 = D_800A5820;
    D_800990B4.unk1C = 0x732;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x17A00;
    D_800990B4.unk30 = 0x44500;
    D_800990B4.unk28 = D_800A554C;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A5788;
    D_800990B4.unk20 = D_800A5530;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A595C;
    D_8009A70C.unk40(0, 0x7340001);
    D_8009A70C.unk40(7, 0x7340002);
    D_8009A70C.unk40(4, 0x7340003);
    D_8009A70C.unk50(0);
}
