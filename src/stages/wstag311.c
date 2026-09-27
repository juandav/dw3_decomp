#include "common.h"
#include "stage.h"
void func_800A5644();
void func_800A5094();
void func_800A4DF8();
extern void (*D_800A79D4[])(void);
void func_800A5AD4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A4D04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A4DF8);

void *func_800A4F48(void) {
    return createTask(func_800A4DF8, 0x60, 0);
}

s32 func_800A4F74(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4F74(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5094);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5458);

void *func_800A54C8(s32 arg) {
    return createTaskWithId(func_800A5094, 0x84, 0, arg);
}

void *func_800A54F8(void) {
    return createTask(func_800A5094, 0x84, 0);
}

s32 func_800A5524(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5524(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5644);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5A08);

void *func_800A5A78(s32 arg) {
    return createTaskWithId(func_800A5644, 0x84, 0, arg);
}

void *func_800A5AA8(void) {
    return createTask(func_800A5644, 0x84, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5AD4);

StageTask *func_800A5C94(void *owner) {
    StageTask *task = createTask(func_800A5AD4, sizeof(StageTask), 0x1C);

    task->owner = owner;
    D_800A79D4[0]();
    return task;
}

s32 func_800A5CF0(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5CF0(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5E10);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5EF8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A5FBC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A624C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A62A8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A6324);

void func_800A6384(void) {
    FLAGS_00.applyAction(0x4067, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A63D0(void) {
    FLAGS_00.applyAction(0x405F, 1);
}

void func_800A63FC(void) {
    FLAGS_00.applyAction(0x4060, 1);
}

void func_800A6428(void) {
    FLAGS_00.applyAction(0x406C, 1);
}

void func_800A6454(void) {
    GAME_PROGRESS = 40;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag311", func_800A6464);
