#include "common.h"
#include "stage.h"
extern void (*D_800A6494[])(void);
void func_800A54D0();

s32 func_800A4CA8(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4CA8(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A4DC8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A5068);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A509C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A50CC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A5178);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A53D4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A5404);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A54D0);

StageTask *func_800A5574(void *owner) {
    StageTask *task = createTask(func_800A54D0, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A6494[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A55D0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag785", func_800A55E0);
