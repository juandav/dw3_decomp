#include "common.h"
#include "stage.h"
extern void (*D_800A51D4[])(void);
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
    D_800A51D4[0]();
    return task;
}

extern s32 D_800A50C4[];
extern s32 D_800A5144[];
extern s32 D_800A4E28[];
extern s32 D_800A509C[];
#if VERSION_US
#define STAGE_TEXT 0xE2
#define STAGE_FILE 0x4DA
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xDA)
#define STAGE_FILE 0x4EA
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A50C4;
    D_800990B4.unk14 = D_800A5144;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xB700, 0x10900};
    D_800990B4.unk28 = D_800A4E28;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A509C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4F98[];
extern s32 D_800A4F08[];
extern s32 D_800A4FA0[];
extern s32 D_800A4F20[];
extern s32 D_800A4FA8[];
extern s32 D_800A4F38[];
extern s32 D_800A4FB0[];
extern s32 D_800A4F50[];
extern s32 D_800A4FBC[];
extern s32 D_800A4F68[];
extern s32 D_800A4FC8[];
extern s32 D_800A4F80[];
extern s32 D_800A4FD0[];
extern s32 D_800A4FD8[];
extern s32 D_800A4FE0[];
extern s32 D_800A4FE8[];
extern s32 D_800A4FFC[];
extern s32 D_800A5010[];
extern s32 D_800A5024[];
extern s32 D_800A5038[];
extern s32 D_800A504C[];
extern s32 D_800A5060[];
extern s32 D_800A5074[];
extern s32 D_800A5088[];

s32 D_800A4E28[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000140, 0, 0x1FF0160,
    0x1000140, 0x100014A, 40, 0x1FF0170,
    0x1000140, 0x1000154, 80, 0x1FE0160,
    0x1000140, 0x100015C, 112, 0x1FE0170,
    0x1000140, 0x1000164, 144, 0x1FD0140,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A4F08[] = {
    0, 0, 101, 0,
    0, 0,
};
s32 D_800A4F20[] = {
    0, 0, 102, 0,
    0, 0,
};
s32 D_800A4F38[] = {
    0, 0, 103, 0,
    0, 0,
};
s32 D_800A4F50[] = {
    0, 0, 99, 0,
    0, 0,
};
s32 D_800A4F68[] = {
    0, 0, 98, 0,
    0, 0,
};
s32 D_800A4F80[] = {
    0, 0, 100, 0,
    0, 0,
};
s32 D_800A4F98[] = {
    0x1602B, 65535,
};
s32 D_800A4FA0[] = {
    0x1602B, 65535,
};
s32 D_800A4FA8[] = {
    0x1602B, 65535,
};
s32 D_800A4FB0[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A4FBC[] = {
    0x1701C, 6666, 65535,
};
s32 D_800A4FC8[] = {
    0x1701A, 65535,
};
s32 D_800A4FD0[] = {
    0x1602B, 65535,
};
s32 D_800A4FD8[] = {
    0x1602B, 65535,
};
s32 D_800A4FE0[] = {
    0x1602B, 65535,
};
s32 D_800A4FE8[] = {
    (s32)D_800A4F98, (s32)D_800A4F08, 0x40028, 0xD40087,
    7,
};
s32 D_800A4FFC[] = {
    (s32)D_800A4FA0, (s32)D_800A4F20, 0x50029, 0x9B00AD,
    7,
};
s32 D_800A5010[] = {
    (s32)D_800A4FA8, (s32)D_800A4F38, 0x6002A, 0xC10038,
    1,
};
s32 D_800A5024[] = {
    (s32)D_800A4FB0, (s32)D_800A4F50, 0x70039, 0xA900E0,
    7,
};
s32 D_800A5038[] = {
    (s32)D_800A4FBC, (s32)D_800A4F68, 0x8009D, 0xA900E0,
    7,
};
s32 D_800A504C[] = {
    (s32)D_800A4FC8, (s32)D_800A4F80, 0x8009D, 0xA900E0,
    7,
};
s32 D_800A5060[] = {
    (s32)D_800A4FD0, 0, 0x900DD, 0xAD00B8,
    7,
};
s32 D_800A5074[] = {
    (s32)D_800A4FD8, 0, 0xA00DE, 0xF0008F,
    7,
};
s32 D_800A5088[] = {
    (s32)D_800A4FE0, 0, 0xB00DF, 0xE00040,
    7,
};
s32 D_800A509C[] = {
    (s32)D_800A4FE8, (s32)D_800A4FFC, (s32)D_800A5010, (s32)D_800A5024,
    (s32)D_800A5038, (s32)D_800A504C, (s32)D_800A5060, (s32)D_800A5074,
    (s32)D_800A5088, 0,
};
s32 D_800A50C4[] = {
    0x2400001, 0x1000200, 0x3E0004, 115,
    0x10000, 0x2000240, 0x40100, 0xAD007C,
    0, 0x2400001, 0x1000200, 0xDA0004,
    227, 0x10000, 0x2000240, 0x40100,
    0x9200F2, 0, 0x2400001, 0x1000200,
    0x1270004, 210, 0x10000, 0x2010240,
    0x40100, 0x8200E3, 0, 0,
    0, 0, 0, 0,
};
s32 D_800A5144[] = {
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
void (*D_800A51D4[])(void) = {
    func_800A4D48,
};
