#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A5CF4[])(void);
void func_800A4E98();

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag405", func_800A4D98);

void *func_800A4E6C(void) {
    return createTask(func_800A4D98, 0x54, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag405", func_800A4E98);

StageTask *func_800A4F5C(void *owner) {
    StageTask *task = createTask(func_800A4E98, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5CF4[0]();
    return task;
}

void func_800A4FB8(void) {
    FLAGS_00.applyAction(0x400F, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5004(void) {
    FLAGS_00.applyAction(0x4010, 1);
    FLAGS_00.applyAction(0x8699, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag405", func_800A5050);
