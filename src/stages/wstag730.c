#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A5834[])(void);
void func_800A4E84();

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

INCLUDE_ASM("stages/nonmatchings/wstag730", func_800A4D98);

void *func_800A4E58(void) {
    return createTask(func_800A4D98, 0x54, 0);
}

INCLUDE_ASM("stages/nonmatchings/wstag730", func_800A4E84);

StageTask *func_800A4EE8(void *owner) {
    StageTask *task = createTask(func_800A4E84, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5834[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag730", func_800A4F44);
