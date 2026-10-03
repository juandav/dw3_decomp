#include "common.h"
#include "stage.h"
extern void (*D_800A510C[])(void);
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
    D_800A510C[0]();
    return task;
}

extern s32 D_800A5094[];
extern s32 D_800A50DC[];
extern s32 D_800A4E90[];
extern s32 D_800A5078[];
const CVECTOR D_800A4CA4 = { 0x80, 0x80, 0x80, 0x00 };
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x59E
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x5AE
#endif
void func_800A4D4C(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5094;
    D_800990B4.unk14 = D_800A50DC;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x24400, 0xB800};
    D_800990B4.unk28 = D_800A4E90;
    D_800990B4.unk3C = 0xE;
    D_800990B4.unk40 = 0x60380000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A5078;
    D_800990B4.unk38 = D_800A4CA4;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS != 0x26 || FLAGS_00.checkCondition(0x1A0A, 0) != 0) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}

void func_800A4D4C();
extern s32 D_800A4FC0[];
extern s32 D_800A4F30[];
extern s32 D_800A4FCC[];
extern s32 D_800A4F48[];
extern s32 D_800A4FD8[];
extern s32 D_800A4F60[];
extern s32 D_800A4FE4[];
extern s32 D_800A4F78[];
extern s32 D_800A4FEC[];
extern s32 D_800A4F90[];
extern s32 D_800A4FF8[];
extern s32 D_800A4FA8[];
extern s32 D_800A5000[];
extern s32 D_800A5014[];
extern s32 D_800A5028[];
extern s32 D_800A503C[];
extern s32 D_800A5050[];
extern s32 D_800A5064[];

s32 D_800A4E90[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000174, 208, 0x1FF0170,
    0x1000140, 0x1280174, 0x2800D0, 0x1FE0160,
    0x1000140, 0x14F015C, 0x4F0070, 0x1FE0170,
    0x1000140, 0x14F0164, 0x4F0090, 0x1FD0160,
};
s32 D_800A4F30[] = {
    0, 0, 82, 0,
    0, 0,
};
s32 D_800A4F48[] = {
    0, 0, 79, 0,
    0, 0,
};
s32 D_800A4F60[] = {
    0, 0, 78, 0,
    0, 0,
};
s32 D_800A4F78[] = {
    0, 0, 80, 0,
    0, 0,
};
s32 D_800A4F90[] = {
    0, 0, 81, 0,
    0, 0,
};
s32 D_800A4FA8[] = {
    0, 0, 83, 0,
    0, 0,
};
s32 D_800A4FC0[] = {
    0x11A0A, 0x16026, 65535,
};
s32 D_800A4FCC[] = {
    0x11A0A, 0x16026, 65535,
};
s32 D_800A4FD8[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A4FE4[] = {
    0x1701A, 65535,
};
s32 D_800A4FEC[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A4FF8[] = {
    0x1701A, 65535,
};
s32 D_800A5000[] = {
    (s32)D_800A4FC0, (s32)D_800A4F30, 0x40034, 0xD10210,
    7,
};
s32 D_800A5014[] = {
    (s32)D_800A4FCC, (s32)D_800A4F48, 0x50037, 0xA80250,
    1,
};
s32 D_800A5028[] = {
    (s32)D_800A4FD8, (s32)D_800A4F60, 0x6009D, 0xA80250,
    1,
};
s32 D_800A503C[] = {
    (s32)D_800A4FE4, (s32)D_800A4F78, 0x6009D, 0xA80250,
    1,
};
s32 D_800A5050[] = {
    (s32)D_800A4FEC, (s32)D_800A4F90, 0x7009E, 0xD10210,
    7,
};
s32 D_800A5064[] = {
    (s32)D_800A4FF8, (s32)D_800A4FA8, 0x7009E, 0xD10210,
    7,
};
s32 D_800A5078[] = {
    (s32)D_800A5000, (s32)D_800A5014, (s32)D_800A5028, (s32)D_800A503C,
    (s32)D_800A5050, (s32)D_800A5064, 0,
};
s32 D_800A5094[] = {
    0x6400001, 0x5000232, 0x1AD0006, 308,
    0x10000, 0x1340640, 0x43934, 0x1880308,
    0, 0x6680001, 0, 0xDA0000,
    321, 0, 0, 0,
    0, 0,
};
s32 D_800A50DC[] = {
    65535, 65535, 0x2990001, 0x2FC00D0,
    7, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A510C[])(void) = {
    func_800A4D4C,
};
