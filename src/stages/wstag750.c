#include "common.h"
#include "stage.h"
void func_800A4DB4();
extern void (*D_800A670C[])(void);
void func_800A50B4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A4D7C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A4DB4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5034);

void *func_800A5084(s32 arg) {
    return createTaskWithId(func_800A4DB4, 0x70, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A50B4);

StageTask *func_800A52E8(void *owner) {
    StageTask *task = createTask(func_800A50B4, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A670C[0]();
    return task;
}

s32 func_800A5344(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5344(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5464);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A554C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A5610);

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A58A0);

void func_800A58FC(void) {
    GAME_PROGRESS = 32;
}

void func_800A590C(void) {
    FLAGS_00.applyAction(0x4048, 1);
}

void func_800A5938(void) {
    FLAGS_00.applyAction(0x4047, 1);
}

void func_800A5964(void) {
    FLAGS_00.applyAction(0x4062, 1);
}

void func_800A5990(void) {
    GAME_PROGRESS = 33;
}

void func_800A59A0(void) {
    FLAGS_00.applyAction(0x7C0A, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag750", func_800A59CC);
