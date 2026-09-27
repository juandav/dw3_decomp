#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A4DB4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5034);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5084);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A50B4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A52E8);

s32 func_800A5344(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5344(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5464);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A554C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5610);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A58A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A58FC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A590C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5938);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5964);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5990);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A59A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A59CC);
