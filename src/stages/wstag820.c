#include "common.h"
#include "stage.h"
extern void (*D_800A65A4[])(void);
void func_800A4ECC();

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4E78);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A4ECC);

StageTask *func_800A5024(void *owner) {
    StageTask *task = createTask(func_800A4ECC, sizeof(StageTask), 0x14);

    task->owner = owner;
    D_800A65A4[0]();
    return task;
}

s32 func_800A5080(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5080(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A51A0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5288);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A534C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A55DC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5638);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5680);

void func_800A56B8(void) {
    FLAGS_00.applyAction(0x4074, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5704(void) {
    FLAGS_00.applyAction(0x4075, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5730);

INCLUDE_ASM("asm/stages/nonmatchings/wstag820", func_800A5768);
