#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4E78);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4ECC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5024);

s32 func_800A5080(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
            if (frame->id == 0xFF) {
                return 0xFF;
            }
        } else if (frame->id == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A5080(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A51A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5288);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A534C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A55DC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5638);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5680);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A56B8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5704);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5730);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5768);
