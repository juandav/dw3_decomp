#include "common.h"
#include "stage.h"
extern u8 D_800A5B4C[];
extern u8 D_800A59CC[];
extern u8 D_800A5710[];
extern u8 D_800A5AE8[];
extern u8 D_800A59FC[];
void func_800A4DC4();
extern void (*D_800A5B48[])(void);
void func_800A5040();

s32 func_800A4CA4(Anim8 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4CA4(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A4DC4);

void *func_800A5010(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x80, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag625", func_800A5040);

StageTask *func_800A50C8(void *owner) {
    StageTask *task = createTask(func_800A5040, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5B48[0]();
    return task;
}

void func_800A5124(void) {
    FLAGS_00.applyAction(0x403D, 1);
    FLAGS_00.applyAction(0x8191, 1);
}

void func_800A5170(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x47B;
    D_800990B4.unkC = 0x47C0000;
    D_800990B4.unk10 = D_800A59FC;
    D_800990B4.unk14 = D_800A5AE8;
    D_800990B4.unk1C = 0x47A;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x20200;
    D_800990B4.unk30 = 0x17600;
    D_800990B4.unk28 = D_800A5710;
    D_800990B4.unk3C = 0x15;
    D_800990B4.unk40 = 0x60540000;
    D_800990B4.unk4C = D_800A59CC;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5B4C;
    D_8009A70C.unk40(0, 0x47C0001);
    D_8009A70C.unk40(7, 0x47C0002);
    D_8009A70C.unk50(0);
}
