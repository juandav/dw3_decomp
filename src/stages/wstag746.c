#include "common.h"
#include "stage.h"
extern void (*D_800A63BC[])(void);
void func_800A5070();

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4EB8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4EE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4F68);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A4FE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5070);

StageTask *func_800A517C(void *owner) {
    StageTask *task = createTask(func_800A5070, sizeof(StageTask), 0x58);

    task->owner = owner;
    D_800A63BC[0]();
    return task;
}

s32 func_800A51D8(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A51D8(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A52F8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A53E0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A54A4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5734);

void func_800A5790(void) {
    FLAGS_00.applyAction(0x4086, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A57DC(void) {
    FLAGS_00.applyAction(0x4087, 1);
    FLAGS_00.applyAction(0x8F41, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag746", func_800A5828);
