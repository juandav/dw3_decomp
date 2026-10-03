#include "common.h"
#include "stage.h"
extern void (*D_800A5378[])(void);
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
    D_800A5378[0]();
    return task;
}

extern s32 D_800A5198[];
extern s32 D_800A5348[];
extern s32 D_800A4E6C[];
extern s32 D_800A5168[];
#if VERSION_US
#define STAGE_TEXT 0xE2
#define STAGE_FILE 0x4A4
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xDA)
#define STAGE_FILE 0x4B4
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5198;
    D_800990B4.unk14 = D_800A5348;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xDB00, 0xDF00};
    D_800990B4.unk28 = D_800A4E6C;
    D_800990B4.unk3C = 5;
    D_800990B4.unk40 = 0x60140000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A5168;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS != 0x26 || FLAGS_00.checkCondition(0x1A0A, 0) != 0) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}

void func_800A4D48();
extern s32 D_800A501C[];
extern s32 D_800A4F5C[];
extern s32 D_800A5028[];
extern s32 D_800A4F74[];
extern s32 D_800A5030[];
extern s32 D_800A503C[];
extern s32 D_800A5044[];
extern s32 D_800A4F8C[];
extern s32 D_800A5050[];
extern s32 D_800A4FA4[];
extern s32 D_800A5058[];
extern s32 D_800A4FBC[];
extern s32 D_800A5060[];
extern s32 D_800A4FD4[];
extern s32 D_800A5068[];
extern s32 D_800A4FEC[];
extern s32 D_800A5074[];
extern s32 D_800A5080[];
extern s32 D_800A5004[];
extern s32 D_800A508C[];
extern s32 D_800A50A0[];
extern s32 D_800A50B4[];
extern s32 D_800A50C8[];
extern s32 D_800A50DC[];
extern s32 D_800A50F0[];
extern s32 D_800A5104[];
extern s32 D_800A5118[];
extern s32 D_800A512C[];
extern s32 D_800A5140[];
extern s32 D_800A5154[];

s32 D_800A4E6C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x161015C, 0x610070, 0x1FF0170,
    0x1000140, 0x1610164, 0x610090, 0x1FE0160,
    0x1000140, 0x1480174, 0x4800D0, 0x1FE0170,
    0x1000140, 0x1980170, 0x9800C0, 0x1FD0150,
    0x1000140, 0x161016C, 0x6100B0, 0x1FD0160,
    0x1000140, 0x1750140, 0x750000, 0x1FD0170,
    0x1000140, 0x1750150, 0x750040, 0x1FC0150,
    0x1000140, 0x1780174, 0x7800D0, 0x1FC0160,
    0x1000140, 0x1890158, 0x890060, 0x1FC0170,
};
s32 D_800A4F5C[] = {
    0, 0, 428, 0,
    0, 0,
};
s32 D_800A4F74[] = {
    0, 0, 432, 0,
    0, 0,
};
s32 D_800A4F8C[] = {
    0, 0, 429, 0,
    0, 0,
};
s32 D_800A4FA4[] = {
    0, 0, 433, 0,
    0, 0,
};
s32 D_800A4FBC[] = {
    0, 0, 434, 0,
    0, 0,
};
s32 D_800A4FD4[] = {
    0, 0, 435, 0,
    0, 0,
};
s32 D_800A4FEC[] = {
    0, 0, 430, 0,
    0, 0,
};
s32 D_800A5004[] = {
    0, 0, 431, 0,
    0, 0,
};
s32 D_800A501C[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A5028[] = {
    0x1602B, 65535,
};
s32 D_800A5030[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A503C[] = {
    0x1602B, 65535,
};
s32 D_800A5044[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A5050[] = {
    0x1602B, 65535,
};
s32 D_800A5058[] = {
    0x1602B, 65535,
};
s32 D_800A5060[] = {
    0x1602B, 65535,
};
s32 D_800A5068[] = {
    6666, 0x1700A, 65535,
};
s32 D_800A5074[] = {
    0x1700A, 6666, 65535,
};
s32 D_800A5080[] = {
    0x1700A, 6666, 65535,
};
s32 D_800A508C[] = {
    (s32)D_800A501C, (s32)D_800A4F5C, 0x40020, 0x1580110,
    7,
};
s32 D_800A50A0[] = {
    (s32)D_800A5028, (s32)D_800A4F74, 0x40020, 0x1580110,
    7,
};
s32 D_800A50B4[] = {
    (s32)D_800A5030, 0, 0x50024, 0x14900F0,
    3,
};
s32 D_800A50C8[] = {
    (s32)D_800A503C, 0, 0x50024, 0x14900F0,
    3,
};
s32 D_800A50DC[] = {
    (s32)D_800A5044, (s32)D_800A4F8C, 0x60025, 0xCA00ED,
    3,
};
s32 D_800A50F0[] = {
    (s32)D_800A5050, (s32)D_800A4FA4, 0x7002D, 0xB00120,
    1,
};
s32 D_800A5104[] = {
    (s32)D_800A5058, (s32)D_800A4FBC, 0x80030, 0xEF0160,
    1,
};
s32 D_800A5118[] = {
    (s32)D_800A5060, (s32)D_800A4FD4, 0x90036, 0xCA00ED,
    3,
};
s32 D_800A512C[] = {
    (s32)D_800A5068, (s32)D_800A4FEC, 0xA009D, 0x1580110,
    7,
};
s32 D_800A5140[] = {
    (s32)D_800A5074, 0, 0xB009E, 0x14900F0,
    3,
};
s32 D_800A5154[] = {
    (s32)D_800A5080, (s32)D_800A5004, 0xC009F, 0xCA00ED,
    3,
};
s32 D_800A5168[] = {
    (s32)D_800A508C, (s32)D_800A50A0, (s32)D_800A50B4, (s32)D_800A50C8,
    (s32)D_800A50DC, (s32)D_800A50F0, (s32)D_800A5104, (s32)D_800A5118,
    (s32)D_800A512C, (s32)D_800A5140, (s32)D_800A5154, 0,
};
s32 D_800A5198[] = {
    0x2400001, 3, 0xC00000, 256,
    0x10000, 0x2320640, 0x40100, 0x680090,
    0, 0x6400001, 0x1000232, 0xA80004,
    92, 0x10000, 0x2320640, 0x40100,
    0x4000E0, 0, 0x6400001, 0xB000233,
    0x7F0008, 112, 0x10000, 0x2330640,
    0x80B00, 0x90007F, 0, 0x6400001,
    0xB000233, 0x9F0008, 96, 0x10000,
    0x2330640, 0x80B00, 0x80009F, 0,
    0x6400001, 0xB000233, 0xBF0008, 80,
    0x10000, 0x2330640, 0x80B00, 0x7000BF,
    0, 0x6400001, 0xB000233, 0xDF0008,
    64, 0x10000, 0x2330640, 0x80B00,
    0x6000DF, 0, 0x6400001, 0xB000234,
    0xC40008, 289, 0x10000, 0x2340640,
    0x80B00, 0x11200E2, 0, 0x6400001,
    0xB000235, 0xD40008, 266, 0x10000,
    0x2350640, 0x80B00, 0x11900D4, 0,
    0x6400001, 0xB000236, 0xC40008, 275,
    0x10000, 0x2360640, 0x80B00, 0x10400E2,
    0, 0x6400001, 0x39370137, 0xC8000A,
    290, 0x10000, 0x20640, 0,
    0x1500100, 0, 0x4400001, 0x3C3A013A,
    0x100000A, 0x13B011E, 0x10000, 1088,
    0, 0x1380130, 329, 0x4400001,
    1, 0x1000000, 0x13B0118, 0,
    0, 0, 0, 0,
};
s32 D_800A5348[] = {
    65535, 65535, 0x2730001, 0x11C0200,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5378[])(void) = {
    func_800A4D48,
};
