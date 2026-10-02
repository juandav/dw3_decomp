#include "common.h"
#include "stage.h"
extern u8 D_800A5544[];
extern u8 D_800A5CF8[];
extern u8 D_800A5AF8[];
extern u8 D_800A5560[];
extern u8 D_800A5BBC[];
extern u8 D_800A5B3C[];
void func_800A4D98();
extern void (*D_800A5CF4[])(void);
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

INCLUDE_ASM("stages/nonmatchings/wstag405", func_800A4D98);

void *func_800A4E6C(void) {
    return createTask(func_800A4D98, 0x54, 0);
}

INCLUDE_ASM("stages/nonmatchings/wstag405", func_800A4E98);

StageTask *func_800A4F5C(void *owner) {
    StageTask *task = createTask(func_800A4E98, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5CF4[0]();
    return task;
}

void func_800A4FB8(void) {
    FLAGS_00.applyAction(0x400F, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5004(void) {
    FLAGS_00.applyAction(0x4010, 1);
    FLAGS_00.applyAction(0x8699, 1);
}

void func_800A5050(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x247;
    D_800990B4.unkC = 0x2480000;
    D_800990B4.unk10 = D_800A5B3C;
    D_800990B4.unk14 = D_800A5BBC;
    D_800990B4.unk1C = 0x3C9;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x16B00;
    D_800990B4.unk30 = 0x44400;
    D_800990B4.unk28 = D_800A5560;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A5AF8;
    D_800990B4.events = D_800A5CF8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5544;
    D_8009A70C.unk40(0, 0x2480001);
    D_8009A70C.unk40(7, 0x2480002);
    D_8009A70C.unk40(4, 0x2480003);
    D_8009A70C.unk50(0);
}
