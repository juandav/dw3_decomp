#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A4DC4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5038);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5084);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A50B4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A50E8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5208);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A53D4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5404);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A554C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A571C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5748);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5890);

s32 func_800A58EC(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A58EC(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5A0C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5AF4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5BB8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5E48);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5EA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5EF0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5F3C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5F88);
