#include "common.h"
#include "stage.h"
extern void (*D_800A5B48[])(void);
void func_800A5040();

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A4DC4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A5010);

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A5040);

StageTask *func_800A50C8(void *owner) {
    StageTask *task = createTask(func_800A5040, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5B48[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A5124);

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A5170);
