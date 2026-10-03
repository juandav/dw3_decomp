#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A5508[])(void);
void func_800A4EBC();
extern AnimFrame D_800A5084[];
extern AnimFrame D_800A50D4[];

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

void func_800A4D98(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A5084[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A50D4[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = func_800A4CA4(&task->anims[0], D_800A5084, 0);
            }
            if (tile->anim == 2) {
                tile->frame = func_800A4CA4(&task->anims[1], D_800A50D4, 0);
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
    D_800A5508[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag233", func_800A4F7C);

void func_800A4F7C();
extern s32 D_800A5124[];
extern s32 D_800A5130[];
extern s32 D_800A513C[];
extern s32 D_800A5148[];
extern s32 D_800A5154[];
extern s32 D_800A5160[];
extern s32 D_800A516C[];
extern s32 D_800A5178[];
extern s32 D_800A51A8[];
extern s32 D_800A51B4[];
extern s32 D_800A51C0[];
extern s32 D_800A51CC[];
extern s32 D_800A51D8[];
extern s32 D_800A51E4[];
extern s32 D_800A51F0[];
extern s32 D_800A51FC[];
extern s32 D_800A522C[];
extern s32 D_800A5238[];
extern s32 D_800A5244[];
extern s32 D_800A5250[];
extern s32 D_800A525C[];
extern s32 D_800A5268[];
extern s32 D_800A5274[];
extern s32 D_800A5280[];
extern s32 D_800A52B0[];
extern s32 D_800A52BC[];
extern s32 D_800A52C8[];
extern s32 D_800A52D4[];
extern s32 D_800A52E0[];
extern s32 D_800A52EC[];
extern s32 D_800A52F8[];
extern s32 D_800A5304[];
extern s32 D_800A5184[];
extern s32 D_800A5208[];
extern s32 D_800A528C[];
extern s32 D_800A5310[];

AnimFrame D_800A5084[] = {
    { 50, 18 }, { 44, 6 }, { 50, 60 }, { 44, 6 },
    { 45, 6 }, { 46, 6 }, { 44, 6 }, { 51, 78 },
    { 44, 6 }, { 45, 6 }, { 46, 6 }, { 44, 6 },
    { 52, 60 }, { 44, 6 }, { 52, 18 }, { 44, 6 },
    { 45, 6 }, { 46, 6 }, { 44, 6 }, { 255, 0 },
};
AnimFrame D_800A50D4[] = {
    { 56, 60 }, { 47, 6 }, { 56, 18 }, { 47, 6 },
    { 48, 6 }, { 49, 6 }, { 47, 6 }, { 57, 78 },
    { 47, 6 }, { 48, 6 }, { 49, 6 }, { 47, 6 },
    { 58, 18 }, { 47, 6 }, { 58, 60 }, { 47, 6 },
    { 48, 6 }, { 49, 6 }, { 47, 6 }, { 255, 0 },
};
s32 D_800A5124[] = {
    0, 0, 0x60040000,
};
s32 D_800A5130[] = {
    0, 0, 0x60040000,
};
s32 D_800A513C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5148[] = {
    0, 0, 0x60040000,
};
s32 D_800A5154[] = {
    0, 0, 0x60040000,
};
s32 D_800A5160[] = {
    0, 0, 0x60040000,
};
s32 D_800A516C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5178[] = {
    0, 0, 0x60040000,
};
s32 D_800A5184[] = {
    3, (s32)D_800A5124, (s32)D_800A5130, (s32)D_800A513C,
    (s32)D_800A5148, (s32)D_800A5154, (s32)D_800A5160, (s32)D_800A516C,
    (s32)D_800A5178,
};
s32 D_800A51A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A51C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A51CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A51D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A51F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A51FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5208[] = {
    0, (s32)D_800A51A8, (s32)D_800A51B4, (s32)D_800A51C0,
    (s32)D_800A51CC, (s32)D_800A51D8, (s32)D_800A51E4, (s32)D_800A51F0,
    (s32)D_800A51FC,
};
s32 D_800A522C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5238[] = {
    0, 0, 0x60040000,
};
s32 D_800A5244[] = {
    0, 0, 0x60040000,
};
s32 D_800A5250[] = {
    0, 0, 0x60040000,
};
s32 D_800A525C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5268[] = {
    0, 0, 0x60040000,
};
s32 D_800A5274[] = {
    0, 0, 0x60040000,
};
s32 D_800A5280[] = {
    0, 0, 0x60040000,
};
s32 D_800A528C[] = {
    0, (s32)D_800A522C, (s32)D_800A5238, (s32)D_800A5244,
    (s32)D_800A5250, (s32)D_800A525C, (s32)D_800A5268, (s32)D_800A5274,
    (s32)D_800A5280,
};
s32 D_800A52B0[] = {
    258, 20, 0x600C0000,
};
s32 D_800A52BC[] = {
    259, 20, 0x600C0000,
};
s32 D_800A52C8[] = {
    260, 20, 0x600C0000,
};
s32 D_800A52D4[] = {
    261, 20, 0x600C0000,
};
s32 D_800A52E0[] = {
    262, 20, 0x608C0000,
};
s32 D_800A52EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5304[] = {
    0, 0, 0x60040000,
};
s32 D_800A5310[] = {
    0, (s32)D_800A52B0, (s32)D_800A52BC, (s32)D_800A52C8,
    (s32)D_800A52D4, (s32)D_800A52E0, (s32)D_800A52EC, (s32)D_800A52F8,
    (s32)D_800A5304,
};
s32 D_800A5334[] = {
    171, 0, 0, (s32)D_800A5184,
    (s32)D_800A5208, (s32)D_800A528C, (s32)D_800A5310,
};
s32 D_800A5350[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A53B0[] = {
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
void (*D_800A5508[])(void) = {
    func_800A4F7C,
};
