#include "common.h"
#include "stage.h"
extern u8 D_800A65A8[];
extern u8 D_800A6318[];
extern u8 D_800A64FC[];
extern u8 D_800A6334[];
extern u8 D_800A6544[];
extern u8 D_800A6520[];
extern void (*D_800A65A4[])(void);
void func_800A4ECC();

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A4D7C);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A4E78);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A4ECC);

StageTask *func_800A5024(void *owner) {
    StageTask *task = createTask(func_800A4ECC, sizeof(StageTask), 0x14);

    task->owner = owner;
    D_800A65A4[0]();
    return task;
}

s32 func_800A5080(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5080(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A51A0);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A5288);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A534C);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A55DC);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A5638);

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A5680);

void func_800A56B8(void) {
    FLAGS_00.applyAction(0x4074, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5704(void) {
    FLAGS_00.applyAction(0x4075, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A5730);

void func_800A5768(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x704;
    D_800990B4.unkC = 0x7050000;
    D_800990B4.unk10 = D_800A6520;
    D_800990B4.unk14 = D_800A6544;
    D_800990B4.unk1C = 0x703;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x24700;
    D_800990B4.unk30 = 0x18C00;
    D_800990B4.unk28 = D_800A6334;
    D_800990B4.unk3C = 0x44;
    D_800990B4.unk4C = D_800A64FC;
    D_800990B4.unk20 = D_800A6318;
    D_800990B4.unk34 = 0;
    D_800990B4.unk40 = 0x61100001;
    D_800990B4.events = D_800A65A8;
    D_8009A70C.unk40(0, 0x7050001);
    D_8009A70C.unk40(7, 0x7050002);
    D_8009A70C.unk50(0);
}
