#include "common.h"
#include "stage.h"
extern void (*D_800A51B0[])(void);
void func_800A4CA8();

void func_800A4CA8(StageTask *task) {
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

StageTask *func_800A4CF0(void *owner) {
    StageTask *task = createTask(func_800A4CA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A51B0[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag441", func_800A4D4C);

void func_800A4D4C();
extern s32 D_800A5010[];
extern s32 D_800A4F50[];
extern s32 D_800A501C[];
extern s32 D_800A4F68[];
extern s32 D_800A5028[];
extern s32 D_800A4F80[];
extern s32 D_800A5030[];
extern s32 D_800A4F98[];
extern s32 D_800A5038[];
extern s32 D_800A4FB0[];
extern s32 D_800A5044[];
extern s32 D_800A4FC8[];
extern s32 D_800A504C[];
extern s32 D_800A4FE0[];
extern s32 D_800A5058[];
extern s32 D_800A4FF8[];
extern s32 D_800A5060[];
extern s32 D_800A5074[];
extern s32 D_800A5088[];
extern s32 D_800A509C[];
extern s32 D_800A50B0[];
extern s32 D_800A50C4[];
extern s32 D_800A50D8[];
extern s32 D_800A50EC[];

s32 D_800A4E90[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1300168, 0x3000A0, 0x1FE0170,
    0x1000140, 0x14A0140, 0x4A0000, 0x1FD0160,
    0x1000140, 0x14A0150, 0x4A0040, 0x1FD0170,
    0x1000140, 0x1500158, 0x500060, 0x1FC0160,
    0x1000140, 0x1500160, 0x500080, 0x1FC0170,
    0x1000140, 0x1500170, 0x5000C0, 0x1FB0160,
};
s32 D_800A4F50[] = {
    0, 0, 162, 0,
    0, 0,
};
s32 D_800A4F68[] = {
    0, 0, 159, 0,
    0, 0,
};
s32 D_800A4F80[] = {
    0, 0, 164, 0,
    0, 0,
};
s32 D_800A4F98[] = {
    0, 0, 165, 0,
    0, 0,
};
s32 D_800A4FB0[] = {
    0, 0, 158, 0,
    0, 0,
};
s32 D_800A4FC8[] = {
    0, 0, 160, 0,
    0, 0,
};
s32 D_800A4FE0[] = {
    0, 0, 161, 0,
    0, 0,
};
s32 D_800A4FF8[] = {
    0, 0, 163, 0,
    0, 0,
};
s32 D_800A5010[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A501C[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A5028[] = {
    0x1602B, 65535,
};
s32 D_800A5030[] = {
    0x1602B, 65535,
};
s32 D_800A5038[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A5044[] = {
    0x1701A, 65535,
};
s32 D_800A504C[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A5058[] = {
    0x1701A, 65535,
};
s32 D_800A5060[] = {
    (s32)D_800A5010, (s32)D_800A4F50, 0x40031, 0x1490091,
    5,
};
s32 D_800A5074[] = {
    (s32)D_800A501C, (s32)D_800A4F68, 0x50032, 0x13900B1,
    7,
};
s32 D_800A5088[] = {
    (s32)D_800A5028, (s32)D_800A4F80, 0x60039, 0x13900B1,
    7,
};
s32 D_800A509C[] = {
    (s32)D_800A5030, (s32)D_800A4F98, 0x7003A, 0x1490091,
    5,
};
s32 D_800A50B0[] = {
    (s32)D_800A5038, (s32)D_800A4FB0, 0x8009D, 0x13900B1,
    7,
};
s32 D_800A50C4[] = {
    (s32)D_800A5044, (s32)D_800A4FC8, 0x8009D, 0x13900B1,
    7,
};
s32 D_800A50D8[] = {
    (s32)D_800A504C, (s32)D_800A4FE0, 0x9009E, 0x1490091,
    5,
};
s32 D_800A50EC[] = {
    (s32)D_800A5058, (s32)D_800A4FF8, 0x9009E, 0x1490091,
    5,
};
s32 D_800A5100[] = {
    (s32)D_800A5060, (s32)D_800A5074, (s32)D_800A5088, (s32)D_800A509C,
    (s32)D_800A50B0, (s32)D_800A50C4, (s32)D_800A50D8, (s32)D_800A50EC,
    0,
};
s32 D_800A5124[] = {
    0x6400001, 0x5000232, 0x1B30009, 247,
    0x10000, 0x1330640, 0x93833, 0xFE01BB,
    0, 0x6400001, 0x3F3A013A, 0x1790006,
    384, 0x10000, 1088, 0,
    0xB101E2, 200, 0, 0,
    0, 0, 0,
};
s32 D_800A5180[] = {
    65535, 65535, 0x2A10001, 0x9C0208,
    7, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A51B0[])(void) = {
    func_800A4D4C,
};
