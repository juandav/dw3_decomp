#include "common.h"
#include "stage.h"

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A4D04);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A4DF8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A4F48);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A54D0);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5A54);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5A80);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A5C40);

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

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A6888);

INCLUDE_ASM("asm/stages/nonmatchings/wstag310", func_800A6898);
