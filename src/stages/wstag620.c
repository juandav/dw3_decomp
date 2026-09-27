#include "common.h"
#include "stage.h"

s32 func_800A4CA4(Anim8 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4CA4(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A4DC4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A505C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A508C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A51D8);

void func_800A5234(void) {
    FLAGS_00.applyAction(0x403B, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A5280);

void func_800A5290(void) {
    FLAGS_00.applyAction(0x1C1C, 1);
    FLAGS_00.applyAction(0x403A, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A52DC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A52EC);
