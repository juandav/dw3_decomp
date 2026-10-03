#include "common.h"
#include "stage.h"
extern void (*D_800A6178[])(void);

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
    D_800A6178[0]();
    return task;
}

extern s32 D_800A604C[];
extern s32 D_800A6148[];
extern s32 D_800A5F68[];
extern s32 D_800A6040[];
void func_800A5E84(void) {
    D_800990B4.unk44 = LANGUAGE + 0xFD;
    D_800990B4.unk8 = 0x239;
    D_800990B4.unkC = 0x9140000;
    D_800990B4.unk10 = D_800A604C;
    D_800990B4.unk14 = D_800A6148;
    D_800990B4.unk1C = 0x915;
    D_800990B4.unk2C = (Vec2){0xB700, 0xD300};
    D_800990B4.unk28 = D_800A5F68;
    D_800990B4.unk3C = 0x31;
    D_800990B4.unk40 = 0x60C40000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A6040;
    D_8009A70C.setFile(0, 0x9140001);
    D_8009A70C.setFile(7, 0x9140002);
    D_8009A70C.unk50(0);
}

void func_800A5E84();
extern s32 D_800A5FE8[];
extern s32 D_800A6000[];
extern s32 D_800A6018[];
extern s32 D_800A602C[];

s32 D_800A5F68[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x138015E, 0x380078, 0x1FF0160,
    0x1000140, 0x14C0166, 0x4C0098, 0x1FF0170,
};
s32 D_800A5FE8[] = {
    0, 0, 112, 0,
    0, 0,
};
s32 D_800A6000[] = {
    0, 0, 113, 0,
    0, 0,
};
s32 D_800A6018[] = {
    0, (s32)D_800A5FE8, 0x40034, 0xC900F1,
    5,
};
s32 D_800A602C[] = {
    0, (s32)D_800A6000, 0x50171, 0x27900C0,
    1,
};
s32 D_800A6040[] = {
    (s32)D_800A6018, (s32)D_800A602C, 0,
};
s32 D_800A604C[] = {
    0x2400001, 0x7000234, 0x610004, 134,
    0x10000, 0x2350240, 0x40700, 0x720089,
    0, 0x6400001, 0x7000232, 0x1410004,
    137, 0x10000, 0x2320640, 0x40700,
    0x1390241, 0, 0x6400001, 0x7000233,
    0x1F10004, 272, 0x10000, 0x2340640,
    0x40700, 0x20400A7, 0, 0x6400001,
    0x7000235, 0xBB0004, 293, 0x10000,
    0x2360640, 0x40700, 0xE90133, 0,
    0x4400001, 0, 0x1140000, 0xF200D0,
    0x10000, 0x10440, 0, 0x9C0033,
    208, 0x4400001, 2, 0x1A90000,
    0x13A0122, 0x10000, 0x30440, 0,
    0x1AC01A5, 438, 0x4400001, 4,
    0x1A70000, 0x1AD0188, 0, 0,
    0, 0, 0,
};
s32 D_800A6148[] = {
    65535, 65535, 0x2920001, 0x1B00156,
    3, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A6178[])(void) = {
    func_800A5E84,
};
