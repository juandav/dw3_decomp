#include "common.h"
#include "stage.h"
extern u8 D_800A6230[];
extern u8 D_800A5EFC[];
extern u8 D_800A60AC[];
extern u8 D_800A5F18[];
extern u8 D_800A619C[];
extern u8 D_800A60C4[];
void func_800A5048();
extern void (*D_800A622C[])(void);
void func_800A5788();

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4CA8);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4CDC);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4DE4);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4F18);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A4F70);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5048);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A51C8);

void *func_800A5200(s32 arg) {
    return createTaskWithId(func_800A5048, 0x58, 0, arg);
}

s32 func_800A5230(Anim4 *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5230(obj, frames, once, depth + 1);
    }
    return frame->id;
}

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5350);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5644);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5758);

INCLUDE_ASM("asm/stages/nonmatchings/wstag545", func_800A5788);

StageTask *func_800A5848(void *owner) {
    StageTask *task = createTask(func_800A5788, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A622C[0]();
    return task;
}

void func_800A58A4(void) {
    FLAGS_00.applyAction(0x4051, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A58F0(void) {
    GAME_PROGRESS = 27;
}

void func_800A5900(void) {
    D_800990B4.unk44 = 0xF7;
    D_800990B4.unk8 = 0x266;
    D_800990B4.unkC = 0x2670000;
    D_800990B4.unk10 = D_800A60C4;
    D_800990B4.unk14 = D_800A619C;
    D_800990B4.unk1C = 0x3CF;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x18800;
    D_800990B4.unk30 = 0x24600;
    D_800990B4.unk28 = D_800A5F18;
    D_800990B4.unk3C = 0x13;
    D_800990B4.unk40 = 0x604C0000;
    D_800990B4.unk4C = D_800A60AC;
    D_800990B4.unk20 = D_800A5EFC;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6230;
    D_8009A70C.unk40(0, 0x2670001);
    D_8009A70C.unk40(7, 0x2670002);
    D_8009A70C.unk40(4, 0x2670003);
    D_8009A70C.unk50(0);
}
