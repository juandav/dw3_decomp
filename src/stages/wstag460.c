#include "common.h"
#include "stage.h"
void func_800A5368();
void func_800A4FDC();
extern void (*D_800A6594[])(void);
void func_800A5E70();

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4E54);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4E8C);

s32 func_800A4EBC(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4EBC(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A4FDC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A51D0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A51EC);

void *func_800A521C(void) {
    return createTask(func_800A4FDC, 0x5C, 0);
}

s32 func_800A5248(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5248(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5368);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5630);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A564C);

void *func_800A567C(void) {
    return createTask(func_800A5368, 0x64, 0);
}

s32 func_800A56A8(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A56A8(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A57C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5804);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5974);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5AF0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5DCC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5DE8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5E18);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5E70);

StageTask *func_800A5EE0(void *owner) {
    StageTask *task = createTask(func_800A5E70, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6594[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5F3C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag460", func_800A5F74);
