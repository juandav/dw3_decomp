#include "common.h"
#include "stage.h"
extern u8 D_800A79D8[];
extern u8 D_800A7554[];
extern u8 D_800A776C[];
extern u8 D_800A7570[];
extern u8 D_800A798C[];
extern u8 D_800A7794[];
void func_800A5644();
void func_800A5094();
void func_800A4DF8();
extern void (*D_800A79D4[])(void);
void func_800A5AD4();

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A4CA8);

s32 func_800A4D04(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        func_800A4D04(anim, frames, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A4DF8);

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
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A4F74(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5094);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5458);

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
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5524(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5644);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5A08);

void *func_800A5A78(s32 arg) {
    return createTaskWithId(func_800A5644, 0x84, 0, arg);
}

void *func_800A5AA8(void) {
    return createTask(func_800A5644, 0x84, 0);
}

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5AD4);

StageTask *func_800A5C94(void *owner) {
    StageTask *task = createTask(func_800A5AD4, sizeof(StageTask), 0x1C);

    task->owner = owner;
    D_800A79D4[0]();
    return task;
}

s32 func_800A5CF0(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5CF0(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5E10);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5EF8);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A5FBC);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A624C);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A62A8);

INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A6324);

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

void func_800A6464(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x52C;
    D_800990B4.unkC = 0x52D0000;
    D_800990B4.unk10 = D_800A7794;
    D_800990B4.unk14 = D_800A798C;
    D_800990B4.unk1C = 0x52B;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13500;
    D_800990B4.unk30 = 0x19D00;
    D_800990B4.unk28 = D_800A7570;
    D_800990B4.unk3C = 0x2A;
    D_800990B4.unk40 = 0x60A80000;
    D_800990B4.unk4C = D_800A776C;
    D_800990B4.unk20 = D_800A7554;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A79D8;
    D_8009A70C.unk40(0, 0x52D0001);
    D_8009A70C.unk40(7, 0x52D0002);
    D_8009A70C.unk50(0);
}
