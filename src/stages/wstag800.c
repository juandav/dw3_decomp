#include "common.h"
#include "stage.h"
void func_800A5208();
void func_800A4DC4();
extern void (*D_800A6D44[])(void);
void func_800A5748();

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A4DC4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5038);

void *func_800A5084(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x64, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A50B4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A50E8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5208);

void *func_800A53D4(s32 arg) {
    return createTaskWithId(func_800A5208, 0x6C, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5404);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A554C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A571C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5748);

StageTask *func_800A5890(void *owner) {
    StageTask *task = createTask(func_800A5748, sizeof(StageTask), 0x20);

    task->owner = owner;
    D_800A6D44[0]();
    return task;
}

s32 func_800A58EC(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A58EC(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5A0C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5AF4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5BB8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5E48);

void func_800A5EA4(void) {
    FLAGS_00.applyAction(0x1C0A, 1);
    FLAGS_00.applyAction(0x4061, 1);
}

void func_800A5EF0(void) {
    FLAGS_00.applyAction(0x4044, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5F3C(void) {
    FLAGS_00.applyAction(0x4045, 1);
    FLAGS_00.applyAction(0x84CB, 1);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag800", func_800A5F88);
