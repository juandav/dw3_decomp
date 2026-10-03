#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A550C[])(void);
void func_800A4EBC();
extern AnimFrame D_800A5088[];
extern AnimFrame D_800A50D8[];

s32 func_800A4CA4(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        func_800A4CA4(anim, frames, depth + 1);
    }
    return frame->frame;
}

/* Sets the frame of the records of StageInfo.unk10 from two animations, which run once per record */
void func_800A4D98(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A5088[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A50D8[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = func_800A4CA4(&task->anims[0], D_800A5088, 0);
            }
            if (tile->anim == 2) {
                tile->frame = func_800A4CA4(&task->anims[1], D_800A50D8, 0);
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A4E90(void) {
    return createTask(func_800A4D98, 0x58, 0);
}

void func_800A4EBC(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4E90();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4F20(void *owner) {
    StageTask *task = createTask(func_800A4EBC, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A550C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag232", func_800A4F7C);

void func_800A4F7C();
extern s32 D_800A5128[];
extern s32 D_800A5134[];
extern s32 D_800A5140[];
extern s32 D_800A514C[];
extern s32 D_800A5158[];
extern s32 D_800A5164[];
extern s32 D_800A5170[];
extern s32 D_800A517C[];
extern s32 D_800A51AC[];
extern s32 D_800A51B8[];
extern s32 D_800A51C4[];
extern s32 D_800A51D0[];
extern s32 D_800A51DC[];
extern s32 D_800A51E8[];
extern s32 D_800A51F4[];
extern s32 D_800A5200[];
extern s32 D_800A5230[];
extern s32 D_800A523C[];
extern s32 D_800A5248[];
extern s32 D_800A5254[];
extern s32 D_800A5260[];
extern s32 D_800A526C[];
extern s32 D_800A5278[];
extern s32 D_800A5284[];
extern s32 D_800A52B4[];
extern s32 D_800A52C0[];
extern s32 D_800A52CC[];
extern s32 D_800A52D8[];
extern s32 D_800A52E4[];
extern s32 D_800A52F0[];
extern s32 D_800A52FC[];
extern s32 D_800A5308[];
extern s32 D_800A5188[];
extern s32 D_800A520C[];
extern s32 D_800A5290[];
extern s32 D_800A5314[];

AnimFrame D_800A5088[] = {
    { 50, 18 }, { 44, 6 }, { 50, 60 }, { 44, 6 },
    { 45, 6 }, { 46, 6 }, { 44, 6 }, { 51, 78 },
    { 44, 6 }, { 45, 6 }, { 46, 6 }, { 44, 6 },
    { 52, 60 }, { 44, 6 }, { 52, 18 }, { 44, 6 },
    { 45, 6 }, { 46, 6 }, { 44, 6 }, { 255, 0 },
};
AnimFrame D_800A50D8[] = {
    { 56, 60 }, { 47, 6 }, { 56, 18 }, { 47, 6 },
    { 48, 6 }, { 49, 6 }, { 47, 6 }, { 57, 78 },
    { 47, 6 }, { 48, 6 }, { 49, 6 }, { 47, 6 },
    { 58, 18 }, { 47, 6 }, { 58, 60 }, { 47, 6 },
    { 48, 6 }, { 49, 6 }, { 47, 6 }, { 255, 0 },
};
s32 D_800A5128[] = {
    0, 0, 0x60040000,
};
s32 D_800A5134[] = {
    0, 0, 0x60040000,
};
s32 D_800A5140[] = {
    0, 0, 0x60040000,
};
s32 D_800A514C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5158[] = {
    0, 0, 0x60040000,
};
s32 D_800A5164[] = {
    0, 0, 0x60040000,
};
s32 D_800A5170[] = {
    0, 0, 0x60040000,
};
s32 D_800A517C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5188[] = {
    3, (s32)D_800A5128, (s32)D_800A5134, (s32)D_800A5140,
    (s32)D_800A514C, (s32)D_800A5158, (s32)D_800A5164, (s32)D_800A5170,
    (s32)D_800A517C,
};
s32 D_800A51AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A51B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A51D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A51DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A51E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5200[] = {
    0, 0, 0x60040000,
};
s32 D_800A520C[] = {
    0, (s32)D_800A51AC, (s32)D_800A51B8, (s32)D_800A51C4,
    (s32)D_800A51D0, (s32)D_800A51DC, (s32)D_800A51E8, (s32)D_800A51F4,
    (s32)D_800A5200,
};
s32 D_800A5230[] = {
    0, 0, 0x60040000,
};
s32 D_800A523C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5248[] = {
    0, 0, 0x60040000,
};
s32 D_800A5254[] = {
    0, 0, 0x60040000,
};
s32 D_800A5260[] = {
    0, 0, 0x60040000,
};
s32 D_800A526C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5278[] = {
    0, 0, 0x60040000,
};
s32 D_800A5284[] = {
    0, 0, 0x60040000,
};
s32 D_800A5290[] = {
    0, (s32)D_800A5230, (s32)D_800A523C, (s32)D_800A5248,
    (s32)D_800A5254, (s32)D_800A5260, (s32)D_800A526C, (s32)D_800A5278,
    (s32)D_800A5284,
};
s32 D_800A52B4[] = {
    253, 20, 0x600C0000,
};
s32 D_800A52C0[] = {
    254, 20, 0x600C0000,
};
s32 D_800A52CC[] = {
    255, 20, 0x600C0000,
};
s32 D_800A52D8[] = {
    256, 20, 0x600C0000,
};
s32 D_800A52E4[] = {
    257, 20, 0x608C0000,
};
s32 D_800A52F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5308[] = {
    0, 0, 0x60040000,
};
s32 D_800A5314[] = {
    0, (s32)D_800A52B4, (s32)D_800A52C0, (s32)D_800A52CC,
    (s32)D_800A52D8, (s32)D_800A52E4, (s32)D_800A52F0, (s32)D_800A52FC,
    (s32)D_800A5308,
};
s32 D_800A5338[] = {
    170, 0, 0, (s32)D_800A5188,
    (s32)D_800A520C, (s32)D_800A5290, (s32)D_800A5314,
};
s32 D_800A5354[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A53B4[] = {
    0x2400001, 0x5000241, 0x15E0008, 180,
    0x10000, 0x2450240, 0x80500, 0xB4013A,
    0, 0x2580201, 56, 0xE50000,
    79, 0x1010000, 0x320258, 0,
    0x4F018B, 0, 0x2400001, 0x403E013E,
    0x1620008, 185, 0x10000, 0x1420240,
    0x84442, 0xB9013E, 0, 0x2400001,
    0x3000246, 0xCE0004, 186, 0x10000,
    0x2460240, 0x40300, 0x8A0172, 0,
    0x2400001, 0x3000247, 0xEE0004, 170,
    0x10000, 0x2470240, 0x40300, 0x9A0192,
    0, 0x2400001, 0x3000248, 0x10E0004,
    154, 0x10000, 0x2480240, 0x40300,
    0xAA01B2, 0, 0x2400001, 0x3000249,
    0x12E0004, 138, 0x10000, 0x2490240,
    0x40300, 0xBA01D2, 0, 0x6400001,
    0x5000236, 0x1830006, 77, 0x10000,
    0x2370640, 0x60500, 0x4F018B, 0,
    0x6400001, 0x500023C, 0xE50006, 77,
    0x10000, 0x23D0640, 0x60500, 0x4F00E5,
    0, 0, 0, 0,
    0, 0,
};
void (*D_800A550C[])(void) = {
    func_800A4F7C,
};
