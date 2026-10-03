#include "common.h"
#include "stage.h"
extern void (*D_800A607C[])(void);

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
    D_800A607C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag959", func_800A5E84);

void func_800A5E84();
extern s32 D_800A5FE0[];
extern s32 D_800A5FF8[];

s32 D_800A5F70[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000162, 136, 0x1FF0150,
};
s32 D_800A5FE0[] = {
    0, 0, 127, 0,
    0, 0,
};
s32 D_800A5FF8[] = {
    0, (s32)D_800A5FE0, 0x4003E, 0x1C70100,
    1,
};
s32 D_800A600C[] = {
    (s32)D_800A5FF8, 0,
};
s32 D_800A6014[] = {
    0x2D00001, 50, 0x330000, 95,
    0x10000, 0x3202D0, 0, 0x37012C,
    0, 0, 0, 0,
    0, 0,
};
s32 D_800A604C[] = {
    65535, 65535, 0x29C0001, 0x2300350,
    7, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A607C[])(void) = {
    func_800A5E84,
};
