#include "common.h"
#include "stage.h"
extern void (*D_800A503C[])(void);
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
    D_800A503C[0]();
    return task;
}

extern s32 D_800A4E9C[];
extern s32 D_800A4FF4[];
extern s32 D_800A4E3C[];
const CVECTOR D_800A4CA4 = { 0x54, 0x67, 0x96, 0x00 };
#if VERSION_US
#define STAGE_TEXT 0xF0
#define STAGE_FILE 0x1A3
#define STAGE_ARCHIVE 0x2C9
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE8)
#define STAGE_FILE 0x1B1
#define STAGE_ARCHIVE 0x2D8
#endif
void func_800A4D4C(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A4E9C;
    D_800990B4.unk14 = D_800A4FF4;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0xFD00, 0x1CD00};
    D_800990B4.unk28 = D_800A4E3C;
    D_800990B4.unk3C = 0x2C;
    D_800990B4.unk34 = 0;
    D_800990B4.unk40 = 0x60B00000;
    D_800990B4.unk38 = D_800A4CA4;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4D4C();

s32 D_800A4E3C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A4E9C[] = {
    0x29F0001, 0x39370137, 0x1C20006, 296,
    0x10000, 0x13A02BE, 0x63C3A, 0x10E0230,
    0, 0x28F0001, 0x311D011D, 0x2480008,
    352, 0x10000, 0x10602B6, 0x81C06,
    0x11501D7, 0, 0x2B60001, 0x1C060106,
    0x2170008, 294, 0x10000, 0x40270,
    0, 0x1360176, 0, 0x2D00001,
    5, 0x1B60000, 232, 0x10000,
    0x2320640, 0x40100, 0xFD0261, 0,
    0x6400001, 0x1000233, 0x2790004, 246,
    0x10000, 0x2340640, 0x40100, 0xF20280,
    0, 0x6400001, 0x1000235, 0x28C0004,
    281, 0x10000, 0x137069F, 0x63937,
    0xAA016E, 0, 0x6670001, 0x523D013D,
    0x1FB0008, 185, 0x10000, 0x10606B6,
    0x81C06, 0x6A01A5, 0, 0x6406401,
    2, 0x5B0000, 362, 0x65010000,
    0x30640, 0, 0x730302, 0,
    0x4900001, 0, 0, 0x19A0100,
    0x10000, 0x104B0, 0, 768,
    165, 0, 0, 0,
    0, 0,
};
s32 D_800A4FF4[] = {
    65535, 65535, 0x2130001, 0x144013A,
    0x640003, 0, 65535, 65535,
    0x2100001, 0x1A200E8, 0x650005, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A503C[])(void) = {
    func_800A4D4C,
};
