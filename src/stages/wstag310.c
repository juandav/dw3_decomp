#include "common.h"
#include "stage.h"
extern u8 D_800A76C8[];
extern u8 D_800A7BA4[];
extern u8 D_800A7954[];
extern u8 D_800A76E4[];
extern u8 D_800A7B70[];
extern u8 D_800A7988[];
void func_800A561C();
void func_800A5094();
void func_800A4DF8();
extern void (*D_800A7BA0[])(void);
void func_800A5A80();

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A4CA8);

s32 func_800A4D04(Anim *anim, AnimFrame *frames, s32 depth) {
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
        if (frame->id == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A4D04(anim, frames, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A4DF8);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5094);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A545C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5498);

void *func_800A54D0(void) {
    return createTask(func_800A5094, 0x84, 0);
}

s32 func_800A54FC(Anim8 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A54FC(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A561C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A59E0);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5A1C);

void *func_800A5A54(void) {
    return createTask(func_800A561C, 0x9C, 0);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5A80);

StageTask *func_800A5C40(void *owner) {
    StageTask *task = createTask(func_800A5A80, sizeof(StageTask), 0x18);

    task->owner = owner;
    D_800A7BA0[0]();
    return task;
}

s32 func_800A5C9C(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5C9C(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5DBC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5EAC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5F70);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A6190);

s32 func_800A61FC(Anim *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A61FC(anim, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A631C);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A6404);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A64C8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A6758);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A67B0);

void func_800A6810(void) {
    FLAGS_00.applyAction(0x404F, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A685C(void) {
    FLAGS_00.applyAction(0x4050, 1);
}

void func_800A6888(void) {
    GAME_PROGRESS = 39;
}

void func_800A6898(void) {
    D_800990B4.unk44 = 0xF0;
    D_800990B4.unk8 = 0x333;
    D_800990B4.unkC = 0x3340000;
    D_800990B4.unk10 = D_800A7988;
    D_800990B4.unk14 = D_800A7B70;
    D_800990B4.unk1C = 0x332;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13E00;
    D_800990B4.unk30 = 0x19800;
    D_800990B4.unk28 = D_800A76E4;
    D_800990B4.unk3C = 0x2A;
    D_800990B4.unk40 = 0x60A80000;
    D_800990B4.unk4C = D_800A7954;
    D_800990B4.events = D_800A7BA4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A76C8;
    D_8009A70C.unk40(0, 0x3340001);
    D_8009A70C.unk40(7, 0x3340002);
    D_8009A70C.unk50(0);
}
