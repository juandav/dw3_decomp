#include "common.h"
#include "stage.h"
extern void (*D_800A620C[])(void);

void func_800A5DE4(StageTask *task) {
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

StageTask *func_800A5E2C(void *owner) {
    StageTask *task = createTask(func_800A5DE4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A620C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag955", func_800A5E88);

void func_800A5E88();
extern s32 D_800A601C[];
extern s32 D_800A6028[];
extern s32 D_800A6034[];
extern s32 D_800A6040[];
extern s32 D_800A6050[];
extern s32 D_800A605C[];
extern s32 D_800A6064[];
extern s32 D_800A6070[];
extern s32 D_800A6078[];
extern s32 D_800A60FC[];
extern s32 D_800A6090[];
extern s32 D_800A6104[];
extern s32 D_800A60A8[];
extern s32 D_800A60E4[];
extern s32 D_800A610C[];
extern s32 D_800A6120[];
extern s32 D_800A6134[];
extern s32 D_800A6148[];

s32 D_800A5F8C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000174, 208, 0x1FF0170,
    0x1000140, 0x1300174, 0x3000D0, 0x1FE0160,
    0x1000140, 0x14E016A, 0x4E00A8, 0x1FE0170,
};
s32 D_800A601C[] = {
    0x10011, 16, 65535,
};
s32 D_800A6028[] = {
    17, 0, 65535,
};
s32 D_800A6034[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A6040[] = {
    17, 16, 0, 65535,
};
s32 D_800A6050[] = {
    17, 0, 65535,
};
s32 D_800A605C[] = {
    0x10000, 65535,
};
s32 D_800A6064[] = {
    17, 0x10000, 65535,
};
s32 D_800A6070[] = {
    0x17838, 65535,
};
s32 D_800A6078[] = {
    0, 0, 147, 0,
    0, 0,
};
s32 D_800A6090[] = {
    0, 0, 77, 0,
    0, 0,
};
s32 D_800A60A8[] = {
    (s32)D_800A601C, (s32)D_800A6028, 79, (s32)D_800A6034,
    (s32)D_800A6040, 80, (s32)D_800A6050, (s32)D_800A605C,
    77, (s32)D_800A6064, (s32)D_800A6070, 78,
    0, 0, 0,
};
s32 D_800A60E4[] = {
    0, 0, 148, 0,
    0, 0,
};
s32 D_800A60FC[] = {
    33170, 65535,
};
s32 D_800A6104[] = {
    0x18192, 65535,
};
s32 D_800A610C[] = {
    0, (s32)D_800A6078, 0x40025, 0x14001DF,
    1,
};
s32 D_800A6120[] = {
    (s32)D_800A60FC, (s32)D_800A6090, 0x5002E, 0x980270,
    7,
};
s32 D_800A6134[] = {
    (s32)D_800A6104, (s32)D_800A60A8, 0x5002E, 0x980270,
    7,
};
s32 D_800A6148[] = {
    0, (s32)D_800A60E4, 0x6016D, 0xD10210,
    1,
};
s32 D_800A615C[] = {
    (s32)D_800A610C, (s32)D_800A6120, (s32)D_800A6134, (s32)D_800A6148,
    0,
};
s32 D_800A6170[] = {
    0x2800001, 0, 0xDA0000, 322,
    0x10000, 0x2320640, 0x60500, 0x13401AD,
    0, 0x6400001, 0x5000233, 0x2A20006,
    320, 0x10000, 0x1340640, 0x43934,
    0x1880308, 0, 0x6800001, 1,
    0xDB0000, 367, 0, 0,
    0, 0, 0,
};
s32 D_800A61DC[] = {
    65535, 65535, 0x2990001, 0x2FC00D0,
    7, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A620C[])(void) = {
    func_800A5E88,
};
