#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A5508[])(void);
void func_800A4EBC();

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4D98);

void *func_800A4E90(void) {
    return createTask(func_800A4D98, 0x58, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4EBC);

StageTask *func_800A4F20(void *owner) {
    StageTask *task = createTask(func_800A4EBC, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5508[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag233", func_800A4F7C);
