#include "common.h"
#include "stage.h"
extern void (*D_800A50E4[])(void);
void func_800A4CA4();

void func_800A4CA4(StageTask *task) {
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

StageTask *func_800A4CEC(void *owner) {
    StageTask *task = createTask(func_800A4CA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A50E4[0]();
    return task;
}

void func_800A4D48(void) {
    GAME_PROGRESS = 13;
}

INCLUDE_ASM("stages/nonmatchings/wstag237", func_800A4D58);

void func_800A4D58();
extern s32 D_800A4F58[];
extern s32 D_800A4F78[];
extern s32 D_800A4F60[];
extern s32 D_800A4F84[];
extern s32 D_800A4E44[];

s32 D_800A4E44[] = {
    0x10600, 0x1020002, 0x17C0002, 0x500A1,
    0xB0100, 0x9101A1, 0xB0101, 0x10001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x50001, 0x1E0300, 512, 0xB0001,
    0x1010002, 0x7000B, 0x3010001, 0xB0101,
    0x10001, 0x1E0300, 512, 0x20002,
    0x1010000, 0x70002, 0x3010005, 0x20101,
    0x50001, 0x1E0300, 512, 0xB0003,
    0x1010002, 0x7000B, 0x3010001, 0xB0101,
    0x10001, 0x1E0300, 0x2030304, 0x1900060,
    5,
};
s32 D_800A4EE8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1300148, 0x300020, 0x1FF0170,
};
s32 D_800A4F58[] = {
    0x1902D, 65535,
};
s32 D_800A4F60[] = {
    0, (s32)D_800A4F58, 88, 0,
    0, 0,
};
s32 D_800A4F78[] = {
    0x1600C, 0x1800F, 65535,
};
s32 D_800A4F84[] = {
    (s32)D_800A4F78, (s32)D_800A4F60, 0x4000B, 0x9101A1,
    7,
};
s32 D_800A4F98[] = {
    (s32)D_800A4F84, 0,
};
s32 D_800A4FA0[] = {
    0x2400001, 0x1000232, 0x1050006, 137,
    0x10000, 0x2320640, 0x60100, 0xDF0035,
    0, 0x6400001, 0x1000232, 0xAD0006,
    179, 0x10000, 0x2320640, 0x60100,
    0x690145, 0, 0x6400001, 0x1000233,
    0x1B30006, 83, 0x10000, 0x2330640,
    0x60100, 0x7F020B, 0, 0x6400001,
    0x1000233, 0x22B0006, 239, 0x64010000,
    0x10640, 0, 0x7F011E, 0,
    0x4400001, 0, 0xE00000, 0xB80090,
    0, 0, 0, 0,
    0,
};
s32 D_800A5054[] = {
    65535, 65535, 0x2010001, 0x10800F0,
    7, 0, 65535, 65535,
    0x21B0001, 0x640138, 7, 0,
    65535, 65535, 0x20A0001, 0x15300A7,
    0x640003, 0, 65535, 65535,
    0x60003, 0xC20203, 0, 0,
    65535, 65535, 0x60002, 0x1280212,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A50E4[])(void) = {
    func_800A4D58,
};
s32 D_800A50E8[] = {
    300, (s32)D_800A4E44,
#if VERSION_US
    0x10B001B,
#elif VERSION_EU
    0x112001B,
#endif
    0, (s32)func_800A4D48, -1, 0,
    0, 0, 0,
};
