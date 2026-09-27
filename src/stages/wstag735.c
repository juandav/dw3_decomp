#include "common.h"
#include "stage.h"
extern void (*D_800A6228[])(void);
void func_800A4CA4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A4CA4);

StageTask *func_800A4DA8(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0x2C);

    task->owner = owner;
    D_800A6228[0]();
    return task;
}

s32 func_800A4E04(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4E04(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A4F24);

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A500C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A50D0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A5360);

void func_800A53BC(void) {
    FLAGS_00.applyAction(0x400E, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A5408);

INCLUDE_ASM("asm/stages/nonmatchings/wstag735", func_800A5454);
