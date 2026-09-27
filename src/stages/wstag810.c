#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A4DC4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A503C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5088);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A50C4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5100);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A513C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A517C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A52DC);

s32 func_800A5338(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5338(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5458);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5540);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5604);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5894);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A58F0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5954);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A59BC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5A08);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5A54);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5AA0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag810", func_800A5AB0);
