#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A587C[])(void);
void func_800A4F30();

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4D98);

void *func_800A4F04(void) {
    return createTask(func_800A4D98, 0x5C, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A4F30);

StageTask *func_800A4F94(void *owner) {
    StageTask *task = createTask(func_800A4F30, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A587C[0]();
    return task;
}

void func_800A4FF0(void) {
    FLAGS_00.applyAction(0x400C, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag555", func_800A501C);
