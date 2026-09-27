#include "common.h"
#include "stage.h"
extern u8 D_800A5734[];
extern u8 D_800A5C78[];
extern u8 D_800A5750[];
extern u8 D_800A5DF8[];
extern u8 D_800A5CA0[];
void func_800A4D98();
extern void (*D_800A5E70[])(void);
void func_800A5030();

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag635", func_800A4D98);

void *func_800A4F04(void) {
    return createTask(func_800A4D98, 0x5C, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag635", func_800A4F30);

INCLUDE_ASM("asm/stages/nonmatchings/wstag635", func_800A5030);

StageTask *func_800A50B8(void *owner) {
    StageTask *task = createTask(func_800A5030, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5E70[0]();
    return task;
}

void func_800A5114(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x48B;
    D_800990B4.unkC = 0x48C0000;
    D_800990B4.unk10 = D_800A5CA0;
    D_800990B4.unk14 = D_800A5DF8;
    D_800990B4.unk1C = 0x48A;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x20900;
    D_800990B4.unk30 = 0x31B00;
    D_800990B4.unk28 = D_800A5750;
    D_800990B4.unk3C = 56;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A5C78;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5734;
    D_8009A70C.unk40(0, 0x48C0001);
    D_8009A70C.unk40(7, 0x48C0002);
    D_8009A70C.unk40(4, 0x48C0003);
    D_8009A70C.unk50(0);
}
