#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4CDC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4DE4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4F18);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4F70);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5048);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A51C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5200);

s32 func_800A5230(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
    AnimFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += frame->duration;
        if (once) {
            if (frame->id == 0xFF) {
                return 0xFF;
            }
        } else if (frame->id == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5230(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5350);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5644);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5758);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5788);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5848);

void func_800A58A4(void) {
    FLAGS_00.applyAction(0x4051, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A58F0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5900);
