#include "common.h"
#include "stage.h"
extern u8 D_800A622C[];
extern u8 D_800A5990[];
extern u8 D_800A5D2C[];
extern u8 D_800A59AC[];
extern u8 D_800A60D8[];
extern u8 D_800A5D64[];
extern void (*D_800A6228[])(void);
void func_800A4CA4();

INCLUDE_ASM("stages/nonmatchings/wstag735", func_800A4CA4);

StageTask *func_800A4DA8(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0x2C);

    task->owner = owner;
    D_800A6228[0]();
    return task;
}

s32 func_800A4E04(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A4E04(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag735", func_800A4F24);

INCLUDE_ASM("stages/nonmatchings/wstag735", func_800A500C);

INCLUDE_ASM("stages/nonmatchings/wstag735", func_800A50D0);

INCLUDE_ASM("stages/nonmatchings/wstag735", func_800A5360);

void func_800A53BC(void) {
    FLAGS_00.applyAction(0x400E, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag735", func_800A5408);

void func_800A5454(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x6AB;
    D_800990B4.unkC = 0x6AC0000;
    D_800990B4.unk10 = D_800A5D64;
    D_800990B4.unk14 = D_800A60D8;
    D_800990B4.unk1C = 0x6AA;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x12500;
    D_800990B4.unk30 = 0x24E00;
    D_800990B4.unk28 = D_800A59AC;
    D_800990B4.unk3C = 0x19;
    D_800990B4.unk40 = 0x60640000;
    D_800990B4.unk4C = D_800A5D2C;
    D_800990B4.unk20 = D_800A5990;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A622C;
    D_8009A70C.unk40(0, 0x6AC0001);
    D_8009A70C.unk40(7, 0x6AC0002);
    D_8009A70C.unk40(4, 0x6AC0003);
    D_8009A70C.unk50(0);
}
