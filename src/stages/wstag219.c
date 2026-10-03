#include "common.h"
#include "stage.h"
extern void (*D_800A5364[])(void);
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
    D_800A5364[0]();
    return task;
}

extern s32 D_800A5118[];
extern s32 D_800A52EC[];
extern s32 D_800A50B8[];
const CVECTOR D_800A4CA4 = { 0x80, 0x80, 0x80, 0x00 };
extern s32 D_800A509C[];
#if VERSION_US
#define STAGE_TEXT 0xE2
#define STAGE_FILE 0x523
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xDA)
#define STAGE_FILE 0x533
#endif
void func_800A4D4C(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5118;
    D_800990B4.unk14 = D_800A52EC;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xE400, 0xD700};
    D_800990B4.unk28 = D_800A50B8;
    D_800990B4.unk3C = 4;
    D_800990B4.unk40 = 0x60100000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800A509C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS != 0x26 || FLAGS_00.checkCondition(0x1A0A, 0) != 0) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}

void func_800A4D4C();
extern s32 D_800A4E8C[];
extern s32 D_800A4E98[];
extern s32 D_800A4EA4[];
extern s32 D_800A4EB0[];
extern s32 D_800A4EBC[];
extern s32 D_800A4EC8[];
extern s32 D_800A4ED4[];
extern s32 D_800A4EE0[];
extern s32 D_800A4F10[];
extern s32 D_800A4F1C[];
extern s32 D_800A4F28[];
extern s32 D_800A4F34[];
extern s32 D_800A4F40[];
extern s32 D_800A4F4C[];
extern s32 D_800A4F58[];
extern s32 D_800A4F64[];
extern s32 D_800A4F94[];
extern s32 D_800A4FA0[];
extern s32 D_800A4FAC[];
extern s32 D_800A4FB8[];
extern s32 D_800A4FC4[];
extern s32 D_800A4FD0[];
extern s32 D_800A4FDC[];
extern s32 D_800A4FE8[];
extern s32 D_800A5018[];
extern s32 D_800A5024[];
extern s32 D_800A5030[];
extern s32 D_800A503C[];
extern s32 D_800A5048[];
extern s32 D_800A5054[];
extern s32 D_800A5060[];
extern s32 D_800A506C[];
extern s32 D_800A4EEC[];
extern s32 D_800A4F70[];
extern s32 D_800A4FF4[];
extern s32 D_800A5078[];

s32 D_800A4E8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4E98[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4ED4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EEC[] = {
    0, (s32)D_800A4E8C, (s32)D_800A4E98, (s32)D_800A4EA4,
    (s32)D_800A4EB0, (s32)D_800A4EBC, (s32)D_800A4EC8, (s32)D_800A4ED4,
    (s32)D_800A4EE0,
};
s32 D_800A4F10[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F28[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F34[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F40[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F58[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F64[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F70[] = {
    0, (s32)D_800A4F10, (s32)D_800A4F1C, (s32)D_800A4F28,
    (s32)D_800A4F34, (s32)D_800A4F40, (s32)D_800A4F4C, (s32)D_800A4F58,
    (s32)D_800A4F64,
};
s32 D_800A4F94[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FF4[] = {
    0, (s32)D_800A4F94, (s32)D_800A4FA0, (s32)D_800A4FAC,
    (s32)D_800A4FB8, (s32)D_800A4FC4, (s32)D_800A4FD0, (s32)D_800A4FDC,
    (s32)D_800A4FE8,
};
s32 D_800A5018[] = {
    195, 18, 0x60080000,
};
s32 D_800A5024[] = {
    0, 0, 0x60040000,
};
s32 D_800A5030[] = {
    0, 0, 0x60040000,
};
s32 D_800A503C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5048[] = {
    0, 0, 0x60040000,
};
s32 D_800A5054[] = {
    0, 0, 0x60040000,
};
s32 D_800A5060[] = {
    0, 0, 0x60040000,
};
s32 D_800A506C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5078[] = {
    0, (s32)D_800A5018, (s32)D_800A5024, (s32)D_800A5030,
    (s32)D_800A503C, (s32)D_800A5048, (s32)D_800A5054, (s32)D_800A5060,
    (s32)D_800A506C,
};
s32 D_800A509C[] = {
    144, 0, 0, (s32)D_800A4EEC,
    (s32)D_800A4F70, (s32)D_800A4FF4, (s32)D_800A5078,
};
s32 D_800A50B8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A5118[] = {
    0x2400001, 0x3000247, 0x2310006, 160,
    0x10000, 0x2470240, 0x60300, 0xD30298,
    0, 0x2400001, 0x3000249, 0x3870006,
    374, 0x10000, 0x80280, 0,
    0x1000380, 0, 0x2400001, 9,
    0x3800000, 384, 0x10000, 0x2480640,
    0x60300, 0x1B50035, 0, 0x6400001,
    0x3000248, 0x630006, 414, 0x10000,
    0x2480640, 0x60300, 0x1850095, 0,
    0x6400001, 0x3000249, 0x27F0006, 463,
    0x10000, 0x2490640, 0x60300, 0x158034F,
    0, 0x6400001, 0x300024A, 0xEF0006,
    331, 0x10000, 0x24A0640, 0x60300,
    0x134011D, 0, 0x6400001, 0x3B2C012C,
    0x389000A, 418, 0x10000, 0x13C0640,
    0xA463C, 0x19502FA, 0, 0x6400001,
    0x463C013C, 0x3DB000A, 453, 0x64010000,
    0x40640, 0, 0x67015F, 0,
    0x6406501, 5, 0x4E0000, 169,
    0x66010000, 0x60640, 0, 0xF6034E,
    0, 0x6406701, 7, 0x36F0000,
    347, 0x10000, 0x14B0A40, 0x64E4B,
    0x13C02C3, 0, 0xA400001, 0x524F014F,
    0x2CF0006, 338, 0x10000, 1088,
    0, 0xC40040, 224, 0x4440001,
    1, 0x1790000, 0xA3006C, 0x10000,
    0x20440, 0, 0x100032D, 304,
    0x4400001, 3, 0x3890000, 0x18A0158,
    0, 0, 0, 0,
    0,
};
s32 D_800A52EC[] = {
    65535, 65535, 0x2850001, 0x11801E0,
    0x650003, 0, 65535, 65535,
    0x2860001, 0xFC0078, 0x640005, 0,
    65535, 65535, 0x2860001, 0x1CC0508,
    0x660003, 0, 65535, 65535,
    0x2840001, 0x1F401A8, 0x670005, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A5364[])(void) = {
    func_800A4D4C,
};
