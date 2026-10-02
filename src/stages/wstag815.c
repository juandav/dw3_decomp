#include "common.h"
#include "stage.h"
void func_800A4E08();

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A4E08);

void *func_800A4F10(void) {
    return createTask(func_800A4E08, 0x60, 0);
}

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A4F3C);

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A5048);

s32 func_800A50A8(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A50A8(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A51C8);

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A52B0);

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A5374);

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A5604);

void func_800A5660(void) {
    FLAGS_00.applyAction(0x4070, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A56AC(void) {
    FLAGS_00.applyAction(0x4071, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A56F8(void) {
    FLAGS_00.applyAction(0x4072, 1);
}

void func_800A5724(void) {
    FLAGS_00.applyAction(0x40A9, 1);
}

void func_800A5750(void) {
    FLAGS_00.applyAction(0x4073, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag815", func_800A579C);
