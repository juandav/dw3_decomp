#include "common.h"
#include "stage.h"
void func_800A5178();
void func_800A4DC8();
extern void (*D_800A6494[])(void);
void func_800A54D0();

s32 func_800A4CA8(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4CA8(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A4DC8);

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A5068);

void *func_800A509C(s32 arg) {
    return createTaskWithId(func_800A4DC8, 0x6C, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A50CC);

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A5178);

void *func_800A53D4(s32 arg) {
    return createTaskWithId(func_800A5178, 0x58, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A5404);

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A54D0);

StageTask *func_800A5574(void *owner) {
    StageTask *task = createTask(func_800A54D0, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A6494[0]();
    return task;
}

void func_800A55D0(void) {
    GAME_PROGRESS = 1;
}

INCLUDE_ASM("stages/nonmatchings/wstag785", func_800A55E0);
