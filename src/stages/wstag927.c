#include "common.h"
#include "stage.h"
void func_800A5ED4();
void func_800A5FF8();
extern void (*D_800A64C8[])(void);
extern AnimFrame D_800A6244[];
extern AnimFrame D_800A6294[];

s32 func_800A5DE0(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        func_800A5DE0(anim, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A5ED4(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A6244[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A6294[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = func_800A5DE0(&task->anims[0], D_800A6244, 0);
            }
            if (tile->anim == 2) {
                tile->frame = func_800A5DE0(&task->anims[1], D_800A6294, 0);
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5FCC(void) {
    return createTask(func_800A5ED4, 0x58, 0);
}

/* Creates an object and the event object of flag 0x100C */
void func_800A5FF8(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A5FCC();
        if (FLAGS_00.checkCondition(0x100C, 0)) {
            children[1] = func_80084B80(0x648);
        }
        if (FLAGS_00.checkCondition(0x100C, 1)) {
            children[1] = func_80084B80(0x64A);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A60BC(void *owner) {
    StageTask *task = createTask(func_800A5FF8, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A64C8[0]();
    return task;
}

/* Event: applies actions 0x100C and 0x7400 */
void func_800A6118(void) {
    FLAGS_00.applyAction(0x100C, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag927", func_800A6164);

void func_800A6164();
void func_800A6118();
extern s32 D_800A6354[];
extern s32 D_800A6508[];
extern s32 D_800A65FC[];
extern s32 D_800A66D0[];
extern s32 D_800A66DC[];
extern s32 D_800A66E8[];
extern s32 D_800A66F4[];
extern s32 D_800A6700[];
extern s32 D_800A670C[];
extern s32 D_800A6718[];
extern s32 D_800A6724[];
extern s32 D_800A6754[];
extern s32 D_800A6760[];
extern s32 D_800A676C[];
extern s32 D_800A6778[];
extern s32 D_800A6784[];
extern s32 D_800A6790[];
extern s32 D_800A679C[];
extern s32 D_800A67A8[];
extern s32 D_800A67D8[];
extern s32 D_800A67E4[];
extern s32 D_800A67F0[];
extern s32 D_800A67FC[];
extern s32 D_800A6808[];
extern s32 D_800A6814[];
extern s32 D_800A6820[];
extern s32 D_800A682C[];
extern s32 D_800A685C[];
extern s32 D_800A6868[];
extern s32 D_800A6874[];
extern s32 D_800A6880[];
extern s32 D_800A688C[];
extern s32 D_800A6898[];
extern s32 D_800A68A4[];
extern s32 D_800A68B0[];
extern s32 D_800A6730[];
extern s32 D_800A67B4[];
extern s32 D_800A6838[];
extern s32 D_800A68BC[];

AnimFrame D_800A6244[] = {
    { 50, 18 }, { 44, 6 }, { 50, 60 }, { 44, 6 },
    { 45, 6 }, { 46, 6 }, { 44, 6 }, { 51, 78 },
    { 44, 6 }, { 45, 6 }, { 46, 6 }, { 44, 6 },
    { 52, 60 }, { 44, 6 }, { 52, 18 }, { 44, 6 },
    { 45, 6 }, { 46, 6 }, { 44, 6 }, { 255, 0 },
};
AnimFrame D_800A6294[] = {
    { 56, 60 }, { 47, 6 }, { 56, 18 }, { 47, 6 },
    { 48, 6 }, { 49, 6 }, { 47, 6 }, { 57, 78 },
    { 47, 6 }, { 48, 6 }, { 49, 6 }, { 47, 6 },
    { 58, 18 }, { 47, 6 }, { 58, 60 }, { 47, 6 },
    { 48, 6 }, { 49, 6 }, { 47, 6 }, { 255, 0 },
};
s32 D_800A62E4[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1B80178, 0xB800E0, 0x1F40170,
};
s32 D_800A6354[] = {
    0, 0, 0x40068, 0,
    1,
};
s32 D_800A6368[] = {
    (s32)D_800A6354, 0,
};
s32 D_800A6370[] = {
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
void (*D_800A64C8[])(void) = {
    func_800A6164,
};
s32 D_800A64CC[] = {
    1608, (s32)D_800A6508, 0x1580004, 0,
    (s32)func_800A6118, 1610, (s32)D_800A65FC, 0x1580005,
    0, 0, -1, 0,
    0, 0, 0,
};
s32 D_800A6508[] = {
    1536, 0x1000002, 0xC00002, 0x1010158,
    0x10002, 0x1000005, 0x1800068, 0x10100F8,
    0x10068, 0x3000001, 0x1010078, 0x3250323,
    0x3000002, 0x101003C, 0x3260323, 0x3000002,
    0x101001E, 0x10002, 0x3000007, 0x101001E,
    0x10002, 0x3000003, 0x101001E, 0x10002,
    0x3000005, 0x200001E, 0x10000, 0x10002,
    0x1020301, 0x1400002, 0x50118, 0x20302,
    0x20101, 0x50001, 0x3230101, 0x20325,
    0x3C0300, 0x3230101, 0x20326, 0x1E0300,
    512, 0x680002, 0x3010000, 0x1E0300,
    512, 0x20003, 0x3010001, 0x1E0300,
    512, 0x680004, 0x3010000, 0x1E0300,
    512, 0x20005, 0x3010001, 0x1E0300,
    512, 0x680006, 0x3010000, 0x1E0300,
    0,
};
s32 D_800A65FC[] = {
    1536, 0x1000002, 0x1400002, 0x1010118,
    0x10002, 0x1000005, 0x1800068, 0x10100F8,
    0x10068, 0x3000001, 0x2000078, 0x10000,
    0x10002, 0x3000301, 0x200001E, 0x20000,
    104, 0x3000301, 0x200001E, 0x30000,
    0x10002, 0x3000301, 0x200001E, 0x40000,
    104, 0x3000301, 0x101001E, 0x3250323,
    0x3000002, 0x101003C, 0x3260323, 0x3000002,
    0x200001E, 0x50000, 0x10002, 0x3000301,
    0x200001E, 0x60000, 104, 0x3000301,
    0x200001E, 0x70000, 0x10002, 0x1010301,
    0x10002, 0x3000001, 0x102001E, 0xC00002,
    0x10158, 0x3C0300, 0x2770304, 0x168012F,
    5,
};
s32 D_800A66D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6700[] = {
    0, 0, 0x60040000,
};
s32 D_800A670C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6718[] = {
    0, 0, 0x60040000,
};
s32 D_800A6724[] = {
    0, 0, 0x60040000,
};
s32 D_800A6730[] = {
    0, (s32)D_800A66D0, (s32)D_800A66DC, (s32)D_800A66E8,
    (s32)D_800A66F4, (s32)D_800A6700, (s32)D_800A670C, (s32)D_800A6718,
    (s32)D_800A6724,
};
s32 D_800A6754[] = {
    0, 0, 0x60040000,
};
s32 D_800A6760[] = {
    0, 0, 0x60040000,
};
s32 D_800A676C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6778[] = {
    0, 0, 0x60040000,
};
s32 D_800A6784[] = {
    0, 0, 0x60040000,
};
s32 D_800A6790[] = {
    0, 0, 0x60040000,
};
s32 D_800A679C[] = {
    0, 0, 0x60040000,
};
s32 D_800A67A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B4[] = {
    0, (s32)D_800A6754, (s32)D_800A6760, (s32)D_800A676C,
    (s32)D_800A6778, (s32)D_800A6784, (s32)D_800A6790, (s32)D_800A679C,
    (s32)D_800A67A8,
};
s32 D_800A67D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6808[] = {
    0, 0, 0x60040000,
};
s32 D_800A6814[] = {
    0, 0, 0x60040000,
};
s32 D_800A6820[] = {
    0, 0, 0x60040000,
};
s32 D_800A682C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6838[] = {
    0, (s32)D_800A67D8, (s32)D_800A67E4, (s32)D_800A67F0,
    (s32)D_800A67FC, (s32)D_800A6808, (s32)D_800A6814, (s32)D_800A6820,
    (s32)D_800A682C,
};
s32 D_800A685C[] = {
    262, 47, 0x60940000,
};
s32 D_800A6868[] = {
    0, 0, 0x60040000,
};
s32 D_800A6874[] = {
    0, 0, 0x60040000,
};
s32 D_800A6880[] = {
    0, 0, 0x60040000,
};
s32 D_800A688C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6898[] = {
    0, 0, 0x60040000,
};
s32 D_800A68A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68BC[] = {
    0, (s32)D_800A685C, (s32)D_800A6868, (s32)D_800A6874,
    (s32)D_800A6880, (s32)D_800A688C, (s32)D_800A6898, (s32)D_800A68A4,
    (s32)D_800A68B0,
};
s32 D_800A68E0[] = {
    392, 0, 0, (s32)D_800A6730,
    (s32)D_800A67B4, (s32)D_800A6838, (s32)D_800A68BC,
};
