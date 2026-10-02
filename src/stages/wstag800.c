#include "common.h"
#include "stage.h"
extern u8 D_800A6D48[];
extern u8 D_800A686C[];
extern u8 D_800A6AD0[];
extern u8 D_800A6888[];
extern u8 D_800A6C6C[];
extern u8 D_800A6AF0[];
void func_800A554C();
void func_800A5208();
void func_800A4DC4();
extern void (*D_800A6D44[])(void);
void func_800A5748();

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A4CA4);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A4DC4);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5038);

void *func_800A5084(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x64, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A50B4);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A50E8);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5208);

void *func_800A53D4(s32 arg) {
    return createTaskWithId(func_800A5208, 0x6C, 0, arg);
}

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5404);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A554C);

void *func_800A571C(void) {
    return createTask(func_800A554C, 0x54, 0x4);
}

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5748);

StageTask *func_800A5890(void *owner) {
    StageTask *task = createTask(func_800A5748, sizeof(StageTask), 0x20);

    task->owner = owner;
    D_800A6D44[0]();
    return task;
}

s32 func_800A58EC(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A58EC(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5A0C);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5AF4);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5BB8);

INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5E48);

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

void func_800A5F88(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x715;
    D_800990B4.unkC = 0x6EE0000;
    D_800990B4.unk10 = D_800A6AF0;
    D_800990B4.unk14 = D_800A6C6C;
    D_800990B4.unk1C = 0x6EA;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1E500;
    D_800990B4.unk30 = 0x38700;
    D_800990B4.unk28 = D_800A6888;
    D_800990B4.unk3C = 0xD;
    D_800990B4.unk40 = 0x60340000;
    D_800990B4.unk4C = D_800A6AD0;
    D_800990B4.unk20 = D_800A686C;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6D48;
    D_8009A70C.unk40(0, 0x6EE0001);
    D_8009A70C.unk40(7, 0x6EE0002);
    D_8009A70C.unk40(4, 0x6EE0003);
    D_8009A70C.unk50(0);
}
