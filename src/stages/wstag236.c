#include "common.h"
#include "stage.h"
extern void (*D_800A5258[])(void);
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
    D_800A5258[0]();
    return task;
}

extern s32 D_800A50B4[];
extern s32 D_800A51B0[];
extern s32 D_800A4EA8[];
extern s32 D_800A5098[];
extern s32 D_800A525C[];
#if VERSION_US
#define STAGE_TEXT 0xE2
#define STAGE_FILE 0x4C8
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xDA)
#define STAGE_FILE 0x4D8
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A50B4;
    D_800990B4.unk14 = D_800A51B0;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x9200, 0x13C00};
    D_800990B4.unk28 = D_800A4EA8;
    D_800990B4.unk3C = 7;
    D_800990B4.unk40 = 0x601C0000;
    D_800990B4.unk4C = D_800A5098;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A525C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4F58[];
extern s32 D_800A4F60[];
extern s32 D_800A4F68[];
extern s32 D_800A4F80[];
extern s32 D_800A4FF8[];
extern s32 D_800A4F98[];
extern s32 D_800A5000[];
extern s32 D_800A4FB0[];
extern s32 D_800A500C[];
extern s32 D_800A4FC8[];
extern s32 D_800A5018[];
extern s32 D_800A4FE0[];
extern s32 D_800A5020[];
extern s32 D_800A5034[];
extern s32 D_800A5048[];
extern s32 D_800A505C[];
extern s32 D_800A5070[];
extern s32 D_800A5084[];
extern s32 D_800A4E34[];

s32 D_800A4E34[] = {
    0x20102, 0xD000CF, 0x1000003, 0xAF0015,
    0x10100C0, 0x10015, 0x1010007, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000003,
    0x3000006, 0x200001E, 0x10000, 21,
    0x3000301, 0x101001E, 0x360015, 0x1010007,
    0x375032D, 0x3030002, 0x1010015, 0x370015,
    0x3000007, 0x304005A, 3082, 0,
    0,
};
s32 D_800A4EA8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x16B0148, 0x6B0020, 0x1FF0160,
    0x1000140, 0x1000173, 204, 0x1FF0170,
    0x1000140, 0x169016C, 0x6900B0, 0x1FE0160,
    0x1000140, 0x16B0150, 0x6B0040, 0x1FE0170,
    0x1000140, 0x16B0158, 0x6B0060, 0x1FD0140,
};
s32 D_800A4F58[] = {
    0x17A28, 65535,
};
s32 D_800A4F60[] = {
    0x19002, 65535,
};
s32 D_800A4F68[] = {
    0, (s32)D_800A4F58, 419, 0,
    0, 0,
};
s32 D_800A4F80[] = {
    0, (s32)D_800A4F60, 418, 0,
    0, 0,
};
s32 D_800A4F98[] = {
    0, 0, 97, 0,
    0, 0,
};
s32 D_800A4FB0[] = {
    0, 0, 95, 0,
    0, 0,
};
s32 D_800A4FC8[] = {
    0, 0, 94, 0,
    0, 0,
};
s32 D_800A4FE0[] = {
    0, 0, 96, 0,
    0, 0,
};
s32 D_800A4FF8[] = {
    0x1602B, 65535,
};
s32 D_800A5000[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A500C[] = {
    0x1701C, 6666, 65535,
};
s32 D_800A5018[] = {
    0x1701A, 65535,
};
s32 D_800A5020[] = {
    0, (s32)D_800A4F68, 0x40014, 0x9A00BC,
    7,
};
s32 D_800A5034[] = {
    0, (s32)D_800A4F80, 0x50015, 0xC000AF,
    7,
};
s32 D_800A5048[] = {
    (s32)D_800A4FF8, (s32)D_800A4F98, 0x60030, 0x14C0058,
    7,
};
s32 D_800A505C[] = {
    (s32)D_800A5000, (s32)D_800A4FB0, 0x70039, 0x14C0058,
    7,
};
s32 D_800A5070[] = {
    (s32)D_800A500C, (s32)D_800A4FC8, 0x8009D, 0x14C0058,
    7,
};
s32 D_800A5084[] = {
    (s32)D_800A5018, (s32)D_800A4FE0, 0x8009D, 0x14C0058,
    7,
};
s32 D_800A5098[] = {
    (s32)D_800A5020, (s32)D_800A5034, (s32)D_800A5048, (s32)D_800A505C,
    (s32)D_800A5070, (s32)D_800A5084, 0,
};
s32 D_800A50B4[] = {
    0x2400001, 0x1000206, 0x4E0004, 77,
    0x10000, 0x2060240, 0x40100, 0x730061,
    0, 0x2400001, 0x1000206, 0x870004,
    231, 0x10000, 0x2060240, 0x40100,
    0x2C008D, 0, 0x2400001, 0x1000206,
    0x1050004, 63, 0x10000, 0x2060240,
    0x40100, 0x5F0146, 0, 0x2400001,
    0x1000207, 0xA50004, 76, 0x10000,
    1088, 0, 0x970100, 184,
    0x4400001, 1, 0xF00000, 0xA2007F,
    0x10000, 0x20440, 0, 0x1400D7,
    86, 0x4400001, 3, 0x900000,
    0xC800B9, 0x10000, 0x40440, 0,
    0xAF007D, 194, 0x4400001, 5,
    0x940000, 0xA7007F, 0, 0,
    0, 0, 0,
};
s32 D_800A51B0[] = {
    65535, 65535, 0x27B0001, 0x1140096,
    5, 0, 65535, 65535,
    0x2700001, 0x17A02A0, 7, 0,
    65535, 65535, 0x27E0001, 0xBA015A,
    1, 0, 65535, 65535,
    0x27A0001, 0xBA0146, 7, 0,
    65535, 65535, 0x40003, 0xEC00C8,
    0, 0, 65535, 65535,
    0x40002, 0x13200B8, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A5258[])(void) = {
    func_800A4D48,
};
s32 D_800A525C[] = {
    1201, (s32)D_800A4E34,
#if VERSION_US
    0x10B002B,
#elif VERSION_EU
    0x112002B,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
