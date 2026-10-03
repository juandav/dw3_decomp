#include "common.h"
#include "stage.h"
extern void (*D_800A659C[])(void);

void func_800A5DE0(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5E28(void *owner) {
    StageTask *task = createTask(func_800A5DE0, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A659C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag937", func_800A5E84);

void func_800A5F6C(StageTween *tween, s32 up) {
    tween->active = 1;
    if (up) {
        SOUND.playSound(0x40019);
        tween->step = 0x1000 / tween->duration;
        tween->value = 0;
    } else {
        SOUND.playSound(0x4001A);
        tween->value = 0x1000;
        tween->step = -(0x1000 / tween->duration * 2);
    }
}

s32 func_800A6000(StageTween *tween) {
    if (tween->active == 0) {
        return 1;
    }
    tween->value += tween->step;
    if (tween->step > 0) {
        if (tween->value > 0x1000) {
            tween->value = 0x1000;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < 0) {
        tween->value = 0;
        tween->active = 0;
        return 1;
    }
    return 0;
}

void func_800A5E84();
extern s32 D_800A613C[];
extern s32 D_800A6144[];
extern s32 D_800A614C[];
extern s32 D_800A6154[];
extern s32 D_800A616C[];
extern s32 D_800A6184[];
extern s32 D_800A619C[];
extern s32 D_800A61B4[];
extern s32 D_800A61CC[];
extern s32 D_800A61F0[];
extern s32 D_800A6204[];
extern s32 D_800A6218[];
extern s32 D_800A622C[];
extern s32 D_800A6240[];
extern s32 D_800A6254[];
extern s32 D_800A6268[];

s32 D_800A606C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x17A0170, 0x7A00C0, 0x1FF0160,
    0x1000140, 0x1820140, 0x820000, 0x1FF0170,
    0x1000140, 0x1820148, 0x820020, 0x1FE0160,
    0x1000140, 0x1820150, 0x820040, 0x1FE0170,
    0x1000140, 0x1820158, 0x820060, 0x1FD0140,
    0x1000140, 0x1890160, 0x890080, 0x1FD0150,
    0, 0, 0, 0,
};
s32 D_800A613C[] = {
    0, 65535,
};
s32 D_800A6144[] = {
    0x10000, 65535,
};
s32 D_800A614C[] = {
    0x10000, 65535,
};
s32 D_800A6154[] = {
    0, 0, 101, 0,
    0, 0,
};
s32 D_800A616C[] = {
    0, 0, 100, 0,
    0, 0,
};
s32 D_800A6184[] = {
    0, 0, 102, 0,
    0, 0,
};
s32 D_800A619C[] = {
    0, 0, 98, 0,
    0, 0,
};
s32 D_800A61B4[] = {
    0, 0, 99, 0,
    0, 0,
};
s32 D_800A61CC[] = {
    (s32)D_800A613C, (s32)D_800A6144, 89, (s32)D_800A614C,
    0, 136, 0, 0,
    0,
};
s32 D_800A61F0[] = {
    0, (s32)D_800A6154, 0x40030, 0x12D0108,
    3,
};
s32 D_800A6204[] = {
    0, (s32)D_800A616C, 0x50031, 0x11500D8,
    7,
};
s32 D_800A6218[] = {
    0, (s32)D_800A6184, 0x60032, 0x1280160,
    5,
};
s32 D_800A622C[] = {
    0, (s32)D_800A619C, 0x70034, 0xE00170,
    1,
};
s32 D_800A6240[] = {
    0, (s32)D_800A61B4, 0x80035, 0xF501D7,
    3,
};
s32 D_800A6254[] = {
    0, (s32)D_800A61CC, 0x9010B, 0xA00161,
    7,
};
s32 D_800A6268[] = {
    0, 0, 0xA010C, 0xAC0168,
    7,
};
s32 D_800A627C[] = {
    (s32)D_800A61F0, (s32)D_800A6204, (s32)D_800A6218, (s32)D_800A622C,
    (s32)D_800A6240, (s32)D_800A6254, (s32)D_800A6268, 0,
};
s32 D_800A629C[] = {
    0x2400001, 10, 0x5D0000, 125,
    0x10000, 0xB0240, 0, 0x6D007E,
    0, 0x2400001, 12, 0x9E0000,
    93, 0x10000, 0xD0240, 0,
    0x4300EB, 0, 0x2400001, 14,
    0x11A0000, 43, 0x10000, 0xF0240,
    0, 0x22017B, 0, 0x2400001,
    16, 0x1930000, 46, 0x10000,
    0x110240, 0, 0x5A01AB, 0,
    0x2400001, 18, 0x1CF0000, 113,
    0x10000, 0x130240, 0, 0x6D01E2,
    0, 0x2400001, 20, 0x1F70000,
    123, 0x10000, 0x2320640, 0x40100,
    0x820054, 0, 0x6400001, 0x1000232,
    0x740004, 114, 0x10000, 0x2320640,
    0x40100, 0x620094, 0, 0x6400001,
    0x1000232, 0x1100004, 44, 0x10000,
    0x2320640, 0x40100, 0x240170, 0,
    0x6400001, 0x1000232, 0x1A10004, 91,
    0x10000, 0x2320640, 0x40100, 0x7101C5,
    0, 0x6400001, 0x1000232, 0x1D90004,
    112, 0x10000, 0x2320640, 0x40100,
    0x8601ED, 0, 0x6400001, 0x1000232,
    0x1F10004, 124, 0x10000, 0x2330640,
    0x40100, 0x680124, 0, 0x6400001,
    21, 0x1A00000, 59, 0x10000,
    0x2320640, 0x40100, 0x4400E0, 0,
    0x6400001, 0x1000232, 0x1880004, 48,
    0x10000, 0x2320640, 0x40100, 0x3C01A0,
    0, 0x4400001, 0, 0xD00000,
    0x1200107, 0x10000, 0x10440, 0,
    0xBF0180, 217, 0x4400001, 2,
    0x1400000, 0xB800A9, 0x10000, 0x30440,
    0, 0xA10130, 174, 0x4400001,
    4, 0x1500000, 0xAE00A1, 0x10000,
    0x50440, 0, 0x990120, 166,
    0x4400001, 6, 0x1600000, 0xA60099,
    0x10000, 0x70440, 0, 0x900110,
    158, 0x4400001, 8, 0x1700000,
    0x9E0091, 0, 0, 0,
    0, 0,
};
s32 D_800A6524[] = {
    65535, 65535, 0x2710001, 0xD80180,
    7, 0, 65535, 65535,
    0x2810001, 0x1A20092, 7, 0,
    65535, 65535, 0x30003, 0xB80110,
    0, 0, 65535, 65535,
    0x30002, 0xF00100, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A659C[])(void) = {
    func_800A5E84, func_800A5F6C, func_800A6000,
};
