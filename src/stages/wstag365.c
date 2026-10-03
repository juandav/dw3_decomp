#include "common.h"
#include "stage.h"
extern void (*D_800A52B0[])(void);
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
    D_800A52B0[0]();
    return task;
}

extern s32 D_800A5184[];
extern s32 D_800A5280[];
extern s32 D_800A4E24[];
extern s32 D_800A5150[];
#if VERSION_US
#define STAGE_TEXT 0xF7
#define STAGE_FILE 0x22B
#define STAGE_ARCHIVE 0x3C7
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xEF)
#define STAGE_FILE 0x23A
#define STAGE_ARCHIVE 0x3D7
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5184;
    D_800990B4.unk14 = D_800A5280;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0xB700, 0xD300};
    D_800990B4.unk28 = D_800A4E24;
    D_800990B4.unk3C = 0x31;
    D_800990B4.unk40 = 0x60C40000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A5150;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 1);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4EB4[];
extern s32 D_800A4EBC[];
extern s32 D_800A4EC8[];
extern s32 D_800A4FFC[];
extern s32 D_800A4ED0[];
extern s32 D_800A5004[];
extern s32 D_800A4EE8[];
extern s32 D_800A500C[];
extern s32 D_800A4F00[];
extern s32 D_800A5014[];
extern s32 D_800A4F18[];
extern s32 D_800A501C[];
extern s32 D_800A4F30[];
extern s32 D_800A5024[];
extern s32 D_800A4F48[];
extern s32 D_800A502C[];
extern s32 D_800A4F60[];
extern s32 D_800A5034[];
extern s32 D_800A4F78[];
extern s32 D_800A503C[];
extern s32 D_800A4F90[];
extern s32 D_800A5044[];
extern s32 D_800A4FA8[];
extern s32 D_800A504C[];
extern s32 D_800A4FC0[];
extern s32 D_800A5058[];
extern s32 D_800A4FE4[];
extern s32 D_800A5060[];
extern s32 D_800A5074[];
extern s32 D_800A5088[];
extern s32 D_800A509C[];
extern s32 D_800A50B0[];
extern s32 D_800A50C4[];
extern s32 D_800A50D8[];
extern s32 D_800A50EC[];
extern s32 D_800A5100[];
extern s32 D_800A5114[];
extern s32 D_800A5128[];
extern s32 D_800A513C[];

s32 D_800A4E24[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1500176, 0x5000D8, 0x1FF0160,
    0x1000140, 0x138015E, 0x380078, 0x1FF0170,
    0x1000140, 0x14C0166, 0x4C0098, 0x1FE0160,
};
s32 D_800A4EB4[] = {
    33166, 65535,
};
s32 D_800A4EBC[] = {
    0x1818E, 0x17013, 65535,
};
s32 D_800A4EC8[] = {
    0x1818E, 65535,
};
s32 D_800A4ED0[] = {
    0, 0, 29, 0,
    0, 0,
};
s32 D_800A4EE8[] = {
    0, 0, 270, 0,
    0, 0,
};
s32 D_800A4F00[] = {
    0, 0, 263, 0,
    0, 0,
};
s32 D_800A4F18[] = {
    0, 0, 271, 0,
    0, 0,
};
s32 D_800A4F30[] = {
    0, 0, 266, 0,
    0, 0,
};
s32 D_800A4F48[] = {
    0, 0, 268, 0,
    0, 0,
};
s32 D_800A4F60[] = {
    0, 0, 262, 0,
    0, 0,
};
s32 D_800A4F78[] = {
    0, 0, 264, 0,
    0, 0,
};
s32 D_800A4F90[] = {
    0, 0, 265, 0,
    0, 0,
};
s32 D_800A4FA8[] = {
    0, 0, 267, 0,
    0, 0,
};
s32 D_800A4FC0[] = {
    (s32)D_800A4EB4, (s32)D_800A4EBC, 743, (s32)D_800A4EC8,
    0, 808, 0, 0,
    0,
};
s32 D_800A4FE4[] = {
    0, 0, 269, 0,
    0, 0,
};
s32 D_800A4FFC[] = {
    0x16004, 65535,
};
s32 D_800A5004[] = {
    0x1602B, 65535,
};
s32 D_800A500C[] = {
    0x1600C, 65535,
};
s32 D_800A5014[] = {
    0x17016, 65535,
};
s32 D_800A501C[] = {
    0x17018, 65535,
};
s32 D_800A5024[] = {
    0x16026, 65535,
};
s32 D_800A502C[] = {
    0x17015, 65535,
};
s32 D_800A5034[] = {
    0x1600E, 65535,
};
s32 D_800A503C[] = {
    0x17017, 65535,
};
s32 D_800A5044[] = {
    0x17019, 65535,
};
s32 D_800A504C[] = {
    0x16006, 0x11C47, 65535,
};
s32 D_800A5058[] = {
    0x1701A, 65535,
};
s32 D_800A5060[] = {
    (s32)D_800A4FFC, (s32)D_800A4ED0, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A5074[] = {
    (s32)D_800A5004, (s32)D_800A4EE8, 0x4002D, 0xC900F1,
    3,
};
s32 D_800A5088[] = {
    (s32)D_800A500C, (s32)D_800A4F00, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A509C[] = {
    (s32)D_800A5014, (s32)D_800A4F18, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A50B0[] = {
    (s32)D_800A501C, (s32)D_800A4F30, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A50C4[] = {
    (s32)D_800A5024, (s32)D_800A4F48, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A50D8[] = {
    (s32)D_800A502C, (s32)D_800A4F60, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A50EC[] = {
    (s32)D_800A5034, (s32)D_800A4F78, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A5100[] = {
    (s32)D_800A503C, (s32)D_800A4F90, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A5114[] = {
    (s32)D_800A5044, (s32)D_800A4FA8, 0x4002D, 0xC900F1,
    5,
};
s32 D_800A5128[] = {
    (s32)D_800A504C, (s32)D_800A4FC0, 0x50040, 0x27900C0,
    1,
};
s32 D_800A513C[] = {
    (s32)D_800A5058, (s32)D_800A4FE4, 0x6009D, 0xC900F1,
    5,
};
s32 D_800A5150[] = {
    (s32)D_800A5060, (s32)D_800A5074, (s32)D_800A5088, (s32)D_800A509C,
    (s32)D_800A50B0, (s32)D_800A50C4, (s32)D_800A50D8, (s32)D_800A50EC,
    (s32)D_800A5100, (s32)D_800A5114, (s32)D_800A5128, (s32)D_800A513C,
    0,
};
s32 D_800A5184[] = {
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
s32 D_800A5280[] = {
    65535, 65535, 0x2230001, 0x1B00156,
    3, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A52B0[])(void) = {
    func_800A4D48,
};
