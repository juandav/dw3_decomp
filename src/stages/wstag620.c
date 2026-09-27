#include "common.h"
#include "stage.h"
extern u8 D_800A6794[];
extern u8 D_800A6DF8[];
extern u8 D_800A6C4C[];
extern u8 D_800A67B0[];
extern u8 D_800A6D94[];
extern u8 D_800A6CA8[];
void func_800A4DC4();
extern void (*D_800A6DF4[])(void);
void func_800A508C();

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
            if (frame->id == 0xFF) {
                return 0xFF;
            }
        } else if (frame->id == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A4CA4(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A4DC4);

void *func_800A505C(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x80, 0, arg);
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag620", func_800A508C);

StageTask *func_800A51D8(void *owner) {
    StageTask *task = createTask(func_800A508C, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A6DF4[0]();
    return task;
}

void func_800A5234(void) {
    FLAGS_00.applyAction(0x403B, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5280(void) {
    GAME_PROGRESS = 20;
}

void func_800A5290(void) {
    FLAGS_00.applyAction(0x1C1C, 1);
    FLAGS_00.applyAction(0x403A, 1);
}

void func_800A52DC(void) {
    GAME_PROGRESS = 21;
}

void func_800A52EC(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x478;
    D_800990B4.unkC = 0x4790000;
    D_800990B4.unk10 = D_800A6CA8;
    D_800990B4.unk14 = D_800A6D94;
    D_800990B4.unk1C = 0x477;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x20200;
    D_800990B4.unk30 = 0x17800;
    D_800990B4.unk28 = D_800A67B0;
    D_800990B4.unk3C = 0x15;
    D_800990B4.unk40 = 0x60540000;
    D_800990B4.unk4C = D_800A6C4C;
    D_800990B4.events = D_800A6DF8;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A6794;
    D_8009A70C.unk40(0, 0x4790001);
    D_8009A70C.unk40(7, 0x4790002);
    D_8009A70C.unk50(0);
}
