#include "common.h"
#include "stage.h"
extern void (*D_800A53C8[])(void);
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
    D_800A53C8[0]();
    return task;
}

extern s32 D_800A52B8[];
extern s32 D_800A5338[];
extern s32 D_800A4E24[];
extern s32 D_800A526C[];
#if VERSION_US
#define STAGE_TEXT 0xF0
#define STAGE_FILE 0x197
#define STAGE_ARCHIVE 0x2B3
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE8)
#define STAGE_FILE 0x1A5
#define STAGE_ARCHIVE 0x2C2
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A52B8;
    D_800990B4.unk14 = D_800A5338;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0xB300, 0xFF00};
    D_800990B4.unk28 = D_800A4E24;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A526C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4F14[];
extern s32 D_800A4F1C[];
extern s32 D_800A4F24[];
extern s32 D_800A4F2C[];
extern s32 D_800A4F44[];
extern s32 D_800A4F5C[];
extern s32 D_800A50A0[];
extern s32 D_800A4F74[];
extern s32 D_800A50A8[];
extern s32 D_800A4F8C[];
extern s32 D_800A50B0[];
extern s32 D_800A4FA4[];
extern s32 D_800A50B8[];
extern s32 D_800A4FBC[];
extern s32 D_800A50C0[];
extern s32 D_800A4FD4[];
extern s32 D_800A50C8[];
extern s32 D_800A4FEC[];
extern s32 D_800A50D0[];
extern s32 D_800A5004[];
extern s32 D_800A50D8[];
extern s32 D_800A501C[];
extern s32 D_800A50E0[];
extern s32 D_800A5034[];
extern s32 D_800A50E8[];
extern s32 D_800A504C[];
extern s32 D_800A50F0[];
extern s32 D_800A5064[];
extern s32 D_800A50FC[];
extern s32 D_800A5088[];
extern s32 D_800A5104[];
extern s32 D_800A5118[];
extern s32 D_800A512C[];
extern s32 D_800A5140[];
extern s32 D_800A5154[];
extern s32 D_800A5168[];
extern s32 D_800A517C[];
extern s32 D_800A5190[];
extern s32 D_800A51A4[];
extern s32 D_800A51B8[];
extern s32 D_800A51CC[];
extern s32 D_800A51E0[];
extern s32 D_800A51F4[];
extern s32 D_800A5208[];
extern s32 D_800A521C[];
extern s32 D_800A5230[];
extern s32 D_800A5244[];
extern s32 D_800A5258[];

s32 D_800A4E24[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000140, 0, 0x1FF0160,
    0x1000140, 0x100014A, 40, 0x1FF0170,
    0x1000140, 0x1000154, 80, 0x1FE0160,
    0x1000140, 0x100016C, 176, 0x1FE0170,
    0x1000140, 0x100015C, 112, 0x1FD0140,
    0x1000140, 0x1000164, 144, 0x1FD0150,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A4F14[] = {
    7236, 65535,
};
s32 D_800A4F1C[] = {
    0x11C44, 65535,
};
s32 D_800A4F24[] = {
    0x11C44, 65535,
};
s32 D_800A4F2C[] = {
    0, 0, 32, 0,
    0, 0,
};
s32 D_800A4F44[] = {
    0, 0, 33, 0,
    0, 0,
};
s32 D_800A4F5C[] = {
    0, 0, 34, 0,
    0, 0,
};
s32 D_800A4F74[] = {
    0, 0, 1071, 0,
    0, 0,
};
s32 D_800A4F8C[] = {
    0, 0, 1073, 0,
    0, 0,
};
s32 D_800A4FA4[] = {
    0, 0, 1075, 0,
    0, 0,
};
s32 D_800A4FBC[] = {
    0, 0, 1068, 0,
    0, 0,
};
s32 D_800A4FD4[] = {
    0, 0, 1069, 0,
    0, 0,
};
s32 D_800A4FEC[] = {
    0, 0, 1070, 0,
    0, 0,
};
s32 D_800A5004[] = {
    0, 0, 1072, 0,
    0, 0,
};
s32 D_800A501C[] = {
    0, 0, 1074, 0,
    0, 0,
};
s32 D_800A5034[] = {
    0, 0, 35, 0,
    0, 0,
};
s32 D_800A504C[] = {
    0, 0, 1077, 0,
    0, 0,
};
s32 D_800A5064[] = {
    (s32)D_800A4F14, (s32)D_800A4F1C, 185, (s32)D_800A4F24,
    0, 198, 0, 0,
    0,
};
s32 D_800A5088[] = {
    0, 0, 1076, 0,
    0, 0,
};
s32 D_800A50A0[] = {
    0x17016, 65535,
};
s32 D_800A50A8[] = {
    0x17018, 65535,
};
s32 D_800A50B0[] = {
    0x16026, 65535,
};
s32 D_800A50B8[] = {
    0x17015, 65535,
};
s32 D_800A50C0[] = {
    0x1600C, 65535,
};
s32 D_800A50C8[] = {
    0x1600E, 65535,
};
s32 D_800A50D0[] = {
    0x16016, 65535,
};
s32 D_800A50D8[] = {
    0x17019, 65535,
};
s32 D_800A50E0[] = {
    0x16004, 65535,
};
s32 D_800A50E8[] = {
    0x1602B, 65535,
};
s32 D_800A50F0[] = {
    33167, 0x16006, 65535,
};
s32 D_800A50FC[] = {
    0x1701A, 65535,
};
s32 D_800A5104[] = {
    0, (s32)D_800A4F2C, 0x40028, 0xD40087,
    7,
};
s32 D_800A5118[] = {
    0, (s32)D_800A4F44, 0x50029, 0x9B00AD,
    7,
};
s32 D_800A512C[] = {
    0, (s32)D_800A4F5C, 0x6002A, 0xC10038,
    1,
};
s32 D_800A5140[] = {
    (s32)D_800A50A0, (s32)D_800A4F74, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A5154[] = {
    (s32)D_800A50A8, (s32)D_800A4F8C, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A5168[] = {
    (s32)D_800A50B0, (s32)D_800A4FA4, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A517C[] = {
    (s32)D_800A50B8, (s32)D_800A4FBC, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A5190[] = {
    (s32)D_800A50C0, (s32)D_800A4FD4, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A51A4[] = {
    (s32)D_800A50C8, (s32)D_800A4FEC, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A51B8[] = {
    (s32)D_800A50D0, (s32)D_800A5004, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A51CC[] = {
    (s32)D_800A50D8, (s32)D_800A501C, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A51E0[] = {
    (s32)D_800A50E0, (s32)D_800A5034, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A51F4[] = {
    (s32)D_800A50E8, (s32)D_800A504C, 0x7002D, 0xA900E0,
    7,
};
s32 D_800A5208[] = {
    (s32)D_800A50F0, (s32)D_800A5064, 0x80040, 0xAC0158,
    5,
};
s32 D_800A521C[] = {
    (s32)D_800A50FC, (s32)D_800A5088, 0x9009D, 0xA900E0,
    7,
};
s32 D_800A5230[] = {
    0, 0, 0xA00DD, 0xAD00B8,
    7,
};
s32 D_800A5244[] = {
    0, 0, 0xB00DE, 0xF0008F,
    7,
};
s32 D_800A5258[] = {
    0, 0, 0xC00DF, 0xE00040,
    7,
};
s32 D_800A526C[] = {
    (s32)D_800A5104, (s32)D_800A5118, (s32)D_800A512C, (s32)D_800A5140,
    (s32)D_800A5154, (s32)D_800A5168, (s32)D_800A517C, (s32)D_800A5190,
    (s32)D_800A51A4, (s32)D_800A51B8, (s32)D_800A51CC, (s32)D_800A51E0,
    (s32)D_800A51F4, (s32)D_800A5208, (s32)D_800A521C, (s32)D_800A5230,
    (s32)D_800A5244, (s32)D_800A5258, 0,
};
s32 D_800A52B8[] = {
    0x2400001, 0x1000200, 0x3E0004, 115,
    0x10000, 0x2000240, 0x40100, 0xAD007C,
    0, 0x2400001, 0x1000200, 0xDA0004,
    227, 0x10000, 0x2000240, 0x40100,
    0x9200F2, 0, 0x2400001, 0x1000200,
    0x1270004, 210, 0x10000, 0x2010240,
    0x40100, 0x8200E3, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A5338[] = {
    65535, 65535, 0x20A0001, 0x5400D8,
    1, 0, 65535, 65535,
    0x30002, 0xF60100, 0, 0,
    65535, 65535, 0x30003, 0xBF00F0,
    0, 0, 65535, 65535,
    0x40002, 0xF60120, 0, 0,
    65535, 65535, 0x40003, 0xAE012F,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A53C8[])(void) = {
    func_800A4D48,
};
