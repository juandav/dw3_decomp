#include "common.h"
#include "stage.h"
extern void (*D_800A4FBC[])(void);
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
    D_800A4FBC[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag238", func_800A4D48);

void func_800A4D48();

s32 D_800A4E18[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A4E78[] = {
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
s32 D_800A4F2C[] = {
    65535, 65535, 0x2710001, 0x10800F0,
    7, 0, 65535, 65535,
    0x28A0001, 0x640138, 7, 0,
    65535, 65535, 0x2790001, 0x15300A7,
    0x640003, 0, 65535, 65535,
    0x60003, 0xC20203, 0, 0,
    65535, 65535, 0x60002, 0x1280212,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A4FBC[])(void) = {
    func_800A4D48,
};
