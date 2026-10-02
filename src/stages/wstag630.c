#include "common.h"
#include "stage.h"
extern u8 D_800A53A0[];
extern u8 D_800A5934[];
extern u8 D_800A53BC[];
extern u8 D_800A5A58[];
extern u8 D_800A5980[];
void func_800A4D98();
extern void (*D_800A5AA0[])(void);
void func_800A4F30();

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4D98);

void *func_800A4F04(void) {
    return createTask(func_800A4D98, 0x5C, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag630", func_800A4F30);

StageTask *func_800A4F94(void *owner) {
    StageTask *task = createTask(func_800A4F30, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5AA0[0]();
    return task;
}

void func_800A4FF0(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x483;
    D_800990B4.unkC = 0x4840000;
    D_800990B4.unk10 = D_800A5980;
    D_800990B4.unk14 = D_800A5A58;
    D_800990B4.unk1C = 0x482;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1AF00;
    D_800990B4.unk30 = 0x11800;
    D_800990B4.unk28 = D_800A53BC;
    D_800990B4.unk3C = 56;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A5934;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A53A0;
    D_8009A70C.unk40(0, 0x4840001);
    D_8009A70C.unk40(7, 0x4840002);
    D_8009A70C.unk40(4, 0x4840003);
    D_8009A70C.unk50(0);
}
