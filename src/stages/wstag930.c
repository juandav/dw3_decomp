#include "common.h"
#include "stage.h"
extern void (*D_800A6214[])(void);

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
    StageTask *task = createTask(func_800A5DE0, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A6214[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag930", func_800A5E84);

void func_800A5E84();
extern s32 D_800A6028[];
extern s32 D_800A6040[];
extern s32 D_800A6058[];
extern s32 D_800A6070[];
extern s32 D_800A6084[];
extern s32 D_800A6098[];
extern s32 D_800A60AC[];
extern s32 D_800A60C0[];
extern s32 D_800A60D4[];

s32 D_800A5F68[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000140, 0, 0x1FF0160,
    0x1000140, 0x100014A, 40, 0x1FF0170,
    0x1000140, 0x1000154, 80, 0x1FE0160,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A6028[] = {
    0, 0, 129, 0,
    0, 0,
};
s32 D_800A6040[] = {
    0, 0, 130, 0,
    0, 0,
};
s32 D_800A6058[] = {
    0, 0, 128, 0,
    0, 0,
};
s32 D_800A6070[] = {
    0, (s32)D_800A6028, 0x40028, 0xD40087,
    1,
};
s32 D_800A6084[] = {
    0, (s32)D_800A6040, 0x50029, 0x9B00AD,
    1,
};
s32 D_800A6098[] = {
    0, (s32)D_800A6058, 0x6002A, 0xC10038,
    1,
};
s32 D_800A60AC[] = {
    0, 0, 0x700DD, 0xAD00B8,
    7,
};
s32 D_800A60C0[] = {
    0, 0, 0x800DE, 0xF0008F,
    7,
};
s32 D_800A60D4[] = {
    0, 0, 0x900DF, 0xE00040,
    7,
};
s32 D_800A60E8[] = {
    (s32)D_800A6070, (s32)D_800A6084, (s32)D_800A6098, (s32)D_800A60AC,
    (s32)D_800A60C0, (s32)D_800A60D4, 0,
};
s32 D_800A6104[] = {
    0x2400001, 0x1000200, 0x3E0004, 115,
    0x10000, 0x2000240, 0x40100, 0xAD007C,
    0, 0x2400001, 0x1000200, 0xDA0004,
    227, 0x10000, 0x2000240, 0x40100,
    0x9200F2, 0, 0x2400001, 0x1000200,
    0x1270004, 210, 0x10000, 0x2010240,
    0x40100, 0x8200E3, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A6184[] = {
    65535, 65535, 0x2790001, 0x5400D8,
    1, 0, 65535, 65535,
    0x30002, 0xF60100, 0, 0,
    65535, 65535, 0x30003, 0xBF00F0,
    0, 0, 65535, 65535,
    0x40002, 0xF60120, 0, 0,
    65535, 65535, 0x40003, 0xAE012F,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A6214[])(void) = {
    func_800A5E84,
};
