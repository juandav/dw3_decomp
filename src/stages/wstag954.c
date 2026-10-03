#include "common.h"
#include "stage.h"
void func_800A5ED4();
void func_800A5FD4();
extern void (*D_800A6610[])(void);
extern AnimFrame D_800A61A4[];

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
        task->nextState(task);
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A61A4[0].duration;
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = func_800A5DE0(&task->anims[0], D_800A61A4, 0);
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5FA8(void) {
    return createTask(func_800A5ED4, 0x54, 0);
}

/* Creates the stage's object (its second child) */
void func_800A5FD4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[1] = func_800A5FA8();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A6038(void *owner) {
    StageTask *task = createTask(func_800A5FD4, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A6610[0]();
    return task;
}

extern s32 D_800A6458[];
extern s32 D_800A64D8[];
extern s32 D_800A6230[];
extern s32 D_800A6444[];
extern s32 D_800A6824[];
void func_800A6094(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x256;
    D_800990B4.unkC = 0x9230000;
    D_800990B4.unk10 = D_800A6458;
    D_800990B4.unk14 = D_800A64D8;
    D_800990B4.unk1C = 0x922;
    D_800990B4.unk2C = (Vec2){0x16B00, 0x44400};
    D_800990B4.unk28 = D_800A6230;
    D_800990B4.unk3C = 0x2F;
    D_800990B4.unk40 = 0x60BC0000;
    D_800990B4.unk4C = D_800A6444;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A6824;
    D_8009A70C.setFile(0, 0x9230002);
    D_8009A70C.setFile(7, 0x9230003);
    D_8009A70C.setFile(4, 0x9230001);
    D_8009A70C.unk50(0);
}

void func_800A6094();
extern s32 D_800A62C0[];
extern s32 D_800A62CC[];
extern s32 D_800A62D8[];
extern s32 D_800A62E4[];
extern s32 D_800A62F4[];
extern s32 D_800A6300[];
extern s32 D_800A6308[];
extern s32 D_800A6314[];
extern s32 D_800A631C[];
extern s32 D_800A6324[];
extern s32 D_800A6330[];
extern s32 D_800A633C[];
extern s32 D_800A6348[];
extern s32 D_800A63E4[];
extern s32 D_800A6360[];
extern s32 D_800A63EC[];
extern s32 D_800A6378[];
extern s32 D_800A63B4[];
extern s32 D_800A63F4[];
extern s32 D_800A6408[];
extern s32 D_800A641C[];
extern s32 D_800A6430[];
extern s32 D_800A6614[];
extern s32 D_800A6620[];
extern s32 D_800A662C[];
extern s32 D_800A6638[];
extern s32 D_800A6644[];
extern s32 D_800A6650[];
extern s32 D_800A665C[];
extern s32 D_800A6668[];
extern s32 D_800A6698[];
extern s32 D_800A66A4[];
extern s32 D_800A66B0[];
extern s32 D_800A66BC[];
extern s32 D_800A66C8[];
extern s32 D_800A66D4[];
extern s32 D_800A66E0[];
extern s32 D_800A66EC[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A6740[];
extern s32 D_800A674C[];
extern s32 D_800A6758[];
extern s32 D_800A6764[];
extern s32 D_800A6770[];
extern s32 D_800A67A0[];
extern s32 D_800A67AC[];
extern s32 D_800A67B8[];
extern s32 D_800A67C4[];
extern s32 D_800A67D0[];
extern s32 D_800A67DC[];
extern s32 D_800A67E8[];
extern s32 D_800A67F4[];
extern s32 D_800A6674[];
extern s32 D_800A66F8[];
extern s32 D_800A677C[];
extern s32 D_800A6800[];

AnimFrame D_800A61A4[] = {
    { 50, 8 }, { 51, 4 }, { 52, 8 }, { 53, 4 },
    { 54, 8 }, { 55, 4 }, { 56, 8 }, { 57, 16 },
    { 58, 4 }, { 59, 8 }, { 60, 4 }, { 61, 8 },
    { 62, 8 }, { 63, 12 }, { 64, 20 }, { 65, 4 },
    { 66, 8 }, { 67, 4 }, { 68, 8 }, { 69, 8 },
    { 70, 8 }, { 71, 8 }, { 72, 8 }, { 73, 4 },
    { 74, 8 }, { 75, 4 }, { 76, 8 }, { 77, 8 },
    { 78, 8 }, { 79, 8 }, { 80, 8 }, { 81, 12 },
    { 82, 8 }, { 83, 30 }, { 255, 0 },
};
s32 D_800A6230[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x148019C, 0x480170, 0x1FF0170,
    0x1000180, 0x12001AA, 0x2001A8, 0x1FE0150,
    0x1000180, 0x12001B2, 0x2001C8, 0x1FE0160,
};
s32 D_800A62C0[] = {
    0x10011, 16, 65535,
};
s32 D_800A62CC[] = {
    17, 0, 65535,
};
s32 D_800A62D8[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A62E4[] = {
    17, 16, 0, 65535,
};
s32 D_800A62F4[] = {
    17, 0, 65535,
};
s32 D_800A6300[] = {
    0x10000, 65535,
};
s32 D_800A6308[] = {
    17, 0x10000, 65535,
};
s32 D_800A6314[] = {
    0x1782F, 65535,
};
s32 D_800A631C[] = {
    28822, 65535,
};
s32 D_800A6324[] = {
    0x17096, 4112, 65535,
};
s32 D_800A6330[] = {
    0x11010, 0x17400, 65535,
};
s32 D_800A633C[] = {
    0x17096, 0x11010, 65535,
};
s32 D_800A6348[] = {
    0, 0, 146, 0,
    0, 0,
};
s32 D_800A6360[] = {
    0, 0, 73, 0,
    0, 0,
};
s32 D_800A6378[] = {
    (s32)D_800A62C0, (s32)D_800A62CC, 75, (s32)D_800A62D8,
    (s32)D_800A62E4, 76, (s32)D_800A62F4, (s32)D_800A6300,
    73, (s32)D_800A6308, (s32)D_800A6314, 74,
    0, 0, 0,
};
s32 D_800A63B4[] = {
    (s32)D_800A631C, 0, 143, (s32)D_800A6324,
    (s32)D_800A6330, 144, (s32)D_800A633C, 0,
    145, 0, 0, 0,
};
s32 D_800A63E4[] = {
    33170, 65535,
};
s32 D_800A63EC[] = {
    0x18192, 65535,
};
s32 D_800A63F4[] = {
    0, (s32)D_800A6348, 0x4002D, 0x47202FC,
    5,
};
s32 D_800A6408[] = {
    (s32)D_800A63E4, (s32)D_800A6360, 0x50038, 0x27803D0,
    1,
};
s32 D_800A641C[] = {
    (s32)D_800A63EC, (s32)D_800A6378, 0x50038, 0x27803D0,
    1,
};
s32 D_800A6430[] = {
    0, (s32)D_800A63B4, 0x60092, 0x143039C,
    1,
};
s32 D_800A6444[] = {
    (s32)D_800A63F4, (s32)D_800A6408, (s32)D_800A641C, (s32)D_800A6430,
    0,
};
s32 D_800A6458[] = {
    0x2E60101, 50, 0x3C60000, 364,
    0x10000, 0x2540240, 0x60200, 0x12503A3,
    0, 0x2400001, 0x6010101, 0xB30008,
    400, 0x10000, 0x1010240, 0x80601,
    0x42F025A, 0, 0x6C80001, 7,
    0x2E90000, 598, 0x10000, 1088,
    0, 0x1BA012A, 505, 0,
    0, 0, 0, 0,
};
s32 D_800A64D8[] = {
    65535, 65535, 0x2990001, 0xD00648,
    1, 0, 65535, 65535,
    0x80002, 0x4D800F0, 0, 0,
    65535, 65535, 0x80003, 0x4500100,
    0, 0, 65535, 65535,
    0x90002, 0x4200102, 0, 0,
    65535, 65535, 0x90003, 0x38800F2,
    0, 0, 65535, 65535,
    0x60002, 0x4C801D2, 0, 0,
    65535, 65535, 0x60003, 0x46001C2,
    0, 0, 65535, 65535,
    0xF0002, 0x42801AF, 0, 0,
    65535, 65535, 0xF0003, 0x33001BF,
    0, 0, 65535, 65535,
    0x160004, 0, 0, 0,
    65535, 65535, 0x90002, 0x2080330,
    0, 0, 65535, 65535,
    0x90003, 0x1700340, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6610[])(void) = {
    func_800A6094,
};
s32 D_800A6614[] = {
    50, 4, 0x60080000,
};
s32 D_800A6620[] = {
    50, 4, 0x60080000,
};
s32 D_800A662C[] = {
    130, 4, 0x60080000,
};
s32 D_800A6638[] = {
    130, 4, 0x60080000,
};
s32 D_800A6644[] = {
    131, 4, 0x60080000,
};
s32 D_800A6650[] = {
    131, 4, 0x60080000,
};
s32 D_800A665C[] = {
    134, 4, 0x60080000,
};
s32 D_800A6668[] = {
    134, 4, 0x60080000,
};
s32 D_800A6674[] = {
    3, (s32)D_800A6614, (s32)D_800A6620, (s32)D_800A662C,
    (s32)D_800A6638, (s32)D_800A6644, (s32)D_800A6650, (s32)D_800A665C,
    (s32)D_800A6668,
};
s32 D_800A6698[] = {
    100, 4, 0x60080000,
};
s32 D_800A66A4[] = {
    100, 4, 0x60080000,
};
s32 D_800A66B0[] = {
    100, 4, 0x60080000,
};
s32 D_800A66BC[] = {
    100, 4, 0x60080000,
};
s32 D_800A66C8[] = {
    100, 4, 0x60080000,
};
s32 D_800A66D4[] = {
    100, 4, 0x60080000,
};
s32 D_800A66E0[] = {
    100, 4, 0x60080000,
};
s32 D_800A66EC[] = {
    100, 4, 0x60080000,
};
s32 D_800A66F8[] = {
    5, (s32)D_800A6698, (s32)D_800A66A4, (s32)D_800A66B0,
    (s32)D_800A66BC, (s32)D_800A66C8, (s32)D_800A66D4, (s32)D_800A66E0,
    (s32)D_800A66EC,
};
s32 D_800A671C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6728[] = {
    0, 0, 0x60040000,
};
s32 D_800A6734[] = {
    0, 0, 0x60040000,
};
s32 D_800A6740[] = {
    0, 0, 0x60040000,
};
s32 D_800A674C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6758[] = {
    0, 0, 0x60040000,
};
s32 D_800A6764[] = {
    0, 0, 0x60040000,
};
s32 D_800A6770[] = {
    0, 0, 0x60040000,
};
s32 D_800A677C[] = {
    0, (s32)D_800A671C, (s32)D_800A6728, (s32)D_800A6734,
    (s32)D_800A6740, (s32)D_800A674C, (s32)D_800A6758, (s32)D_800A6764,
    (s32)D_800A6770,
};
s32 D_800A67A0[] = {
    308, 18, 0x608C0000,
};
s32 D_800A67AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6800[] = {
    0, (s32)D_800A67A0, (s32)D_800A67AC, (s32)D_800A67B8,
    (s32)D_800A67C4, (s32)D_800A67D0, (s32)D_800A67DC, (s32)D_800A67E8,
    (s32)D_800A67F4,
};
s32 D_800A6824[] = {
    391, 0, 0, (s32)D_800A6674,
    (s32)D_800A66F8, (s32)D_800A677C, (s32)D_800A6800,
};
