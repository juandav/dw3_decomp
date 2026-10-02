#include "common.h"
#include "stage.h"
void func_800A5804();
void func_800A6174();
void func_800A508C();
void func_800A5668();
extern void (*D_800A80B4[])(void);
void func_800A6390();

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A4D84);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A4F20);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A4FF4);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A508C);

void *func_800A5220(s32 arg) {
    return createTaskWithId(func_800A508C, 0x54, 0, arg);
}

s32 func_800A5250(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A5250(anim, frames, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5344);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A53F0);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A553C);

s32 func_800A5574(Anim4 *obj, AnimFrame *frames, s32 depth) {
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
        if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5574(obj, frames, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5668);

void *func_800A57D8(void) {
    return createTask(func_800A5668, 0x60, 0);
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5804);

void *func_800A589C(void) {
    return createTask(func_800A5804, 0x50, 0x1C);
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A58C8);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5A10);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5C88);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5E04);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5E50);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A5E80);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A6174);

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A6314);

void *func_800A6360(s32 arg) {
    return createTaskWithId(func_800A6174, 0x78, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A6390);

StageTask *func_800A6474(void *owner) {
    StageTask *task = createTask(func_800A6390, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A80B4[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A64D0);

void func_800A64DC(void) {
    FLAGS_00.applyAction(0x4066, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag780", func_800A6508);
