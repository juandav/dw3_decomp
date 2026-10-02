#include "common.h"
#include "stage.h"
extern u8 D_800A6E54[];
extern u8 D_800A6984[];
extern u8 D_800A6B44[];
extern u8 D_800A69A0[];
extern u8 D_800A6D60[];
extern u8 D_800A6B54[];
void func_800A5E78();
void func_800A5800();
void func_800A53C0();
void func_800A503C();
extern void (*D_800A6E50[])(void);
void func_800A62B4();

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A4CA4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A4EB4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A4EEC);

s32 func_800A4F1C(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4F1C(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A503C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5228);

void *func_800A5244(s32 arg) {
    return createTaskWithId(func_800A503C, 0x5C, 0, arg);
}

void *func_800A5274(void) {
    return createTask(func_800A503C, 0x5C, 0);
}

s32 func_800A52A0(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A52A0(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A53C0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5668);

void *func_800A5684(s32 arg) {
    return createTaskWithId(func_800A53C0, 0x64, 0, arg);
}

void *func_800A56B4(void) {
    return createTask(func_800A53C0, 0x64, 0);
}

s32 func_800A56E0(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A56E0(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5800);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A59B8);

void *func_800A59D4(s32 arg) {
    return createTaskWithId(func_800A5800, 0x5C, 0, arg);
}

void *func_800A5A04(void) {
    return createTask(func_800A5800, 0x5C, 0);
}

s32 func_800A5A30(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5A30(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5B50);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5B8C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5CFC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A5E78);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A6210);

void *func_800A622C(s32 arg) {
    return createTaskWithId(func_800A5E78, 0x88, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A625C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A62B4);

StageTask *func_800A6324(void *owner) {
    StageTask *task = createTask(func_800A62B4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6E50[0]();
    return task;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag526", func_800A6380);

void func_800A63B8(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x6A7;
    D_800990B4.unkC = 0x6A80000;
    D_800990B4.unk10 = D_800A6B54;
    D_800990B4.unk14 = D_800A6D60;
    D_800990B4.unk1C = 0x6A6;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13D00;
    D_800990B4.unk30 = 0x38500;
    D_800990B4.unk28 = D_800A69A0;
    D_800990B4.unk3C = 0x37;
    D_800990B4.unk40 = 0x60DC0000;
    D_800990B4.unk4C = D_800A6B44;
    D_800990B4.unk20 = D_800A6984;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6E54;
    D_8009A70C.unk40(0, 0x6A80001);
    D_8009A70C.unk40(7, 0x6A80002);
    D_8009A70C.unk40(4, 0x6A80003);
    D_8009A70C.unk50(0);
}
