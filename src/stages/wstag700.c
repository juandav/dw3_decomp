#include "common.h"
#include "stage.h"
extern void (*D_800A5050[])(void);
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
    D_800A5050[0]();
    return task;
}

void func_800A4D48(void) {
    FLAGS_00.applyAction(0x7C17, 1);
}

extern s32 D_800A4FC4[];
extern s32 D_800A5020[];
extern s32 D_800A4ED0[];
extern s32 D_800A4FB8[];
extern s32 D_800A5054[];
#if VERSION_US
#define STAGE_TEXT 0xDB
#define STAGE_FILE 0x635
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xD3)
#define STAGE_FILE 0x645
#endif
void func_800A4D74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A4FC4;
    D_800990B4.unk14 = D_800A5020;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x10000, 0x12500};
    D_800990B4.unk28 = D_800A4ED0;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A4FB8;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5054;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4D74();
extern s32 D_800A4F50[];
extern s32 D_800A4F58[];
extern s32 D_800A4F60[];
extern s32 D_800A4F78[];
extern s32 D_800A4F90[];
extern s32 D_800A4FA4[];
extern s32 D_800A4E60[];

s32 D_800A4E60[] = {
    0x20102, 0x10B013B, 0x1000003, 0x11B0015,
    0x10100FB, 0x10015, 0x1010007, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000003,
    0x2000024, 0x10000, 21, 0x3000301,
    0x101001E, 0x360015, 0x1010007, 0x375032D,
    0x3030002, 0x1010015, 0x370015, 0x3000007,
    0x304005A, 3093, 0, 0,
};
s32 D_800A4ED0[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x100016C, 176, 0x1FF0150,
    0x1000140, 0x1000160, 128, 0x1FF0160,
};
s32 D_800A4F50[] = {
    0x17A25, 65535,
};
s32 D_800A4F58[] = {
    0x19066, 65535,
};
s32 D_800A4F60[] = {
    0, (s32)D_800A4F50, 363, 0,
    0, 0,
};
s32 D_800A4F78[] = {
    0, (s32)D_800A4F58, 360, 0,
    0, 0,
};
s32 D_800A4F90[] = {
    0, (s32)D_800A4F60, 0x40014, 0x12100E1,
    7,
};
s32 D_800A4FA4[] = {
    0, (s32)D_800A4F78, 0x50015, 0xFB011B,
    7,
};
s32 D_800A4FB8[] = {
    (s32)D_800A4F90, (s32)D_800A4FA4, 0,
};
s32 D_800A4FC4[] = {
    0x6400001, 0x1000232, 0x13E0006, 111,
    0x10000, 0x2320640, 0x60100, 0x8E017F,
    0, 0x4400001, 0, 0xAC0000,
    0x126010B, 0x10000, 0x10440, 0,
    0xEB00E0, 262, 0, 0,
    0, 0, 0,
};
s32 D_800A5020[] = {
    65535, 65535, 0x2620001, 0x18C0248,
    7, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5050[])(void) = {
    func_800A4D74,
};
s32 D_800A5054[] = {
    1460, (s32)D_800A4E60,
#if VERSION_US
    0x1430026,
#elif VERSION_EU
    0x14A0026,
#endif
    0, (s32)func_800A4D48, -1, 0,
    0, 0, 0,
};
