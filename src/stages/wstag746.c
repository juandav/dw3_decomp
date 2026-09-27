#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4EB8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4EE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4F68);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4FE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5070);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A517C);

s32 func_800A51D8(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A51D8(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A52F8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A53E0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A54A4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5734);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5790);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A57DC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5828);
