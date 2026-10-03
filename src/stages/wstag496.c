#include "common.h"
#include "stage.h"
extern void (*D_800A543C[])(void);
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
    D_800A543C[0]();
    return task;
}

extern s32 D_800A5338[];
extern s32 D_800A53DC[];
extern s32 D_800A5078[];
extern s32 D_800A5314[];
extern s32 D_800A505C[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x5A6
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x5B6
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5338;
    D_800990B4.unk14 = D_800A53DC;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xEC00, 0x1AC00};
    D_800990B4.unk28 = D_800A5078;
    D_800990B4.unk3C = 0x36;
    D_800990B4.unk40 = 0x60D80000;
    D_800990B4.unk4C = D_800A5314;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A505C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4E4C[];
extern s32 D_800A4E58[];
extern s32 D_800A4E64[];
extern s32 D_800A4E70[];
extern s32 D_800A4E7C[];
extern s32 D_800A4E88[];
extern s32 D_800A4E94[];
extern s32 D_800A4EA0[];
extern s32 D_800A4ED0[];
extern s32 D_800A4EDC[];
extern s32 D_800A4EE8[];
extern s32 D_800A4EF4[];
extern s32 D_800A4F00[];
extern s32 D_800A4F0C[];
extern s32 D_800A4F18[];
extern s32 D_800A4F24[];
extern s32 D_800A4F54[];
extern s32 D_800A4F60[];
extern s32 D_800A4F6C[];
extern s32 D_800A4F78[];
extern s32 D_800A4F84[];
extern s32 D_800A4F90[];
extern s32 D_800A4F9C[];
extern s32 D_800A4FA8[];
extern s32 D_800A4FD8[];
extern s32 D_800A4FE4[];
extern s32 D_800A4FF0[];
extern s32 D_800A4FFC[];
extern s32 D_800A5008[];
extern s32 D_800A5014[];
extern s32 D_800A5020[];
extern s32 D_800A502C[];
extern s32 D_800A4EAC[];
extern s32 D_800A4F30[];
extern s32 D_800A4FB4[];
extern s32 D_800A5038[];
extern s32 D_800A5128[];
extern s32 D_800A5134[];
extern s32 D_800A513C[];
extern s32 D_800A5148[];
extern s32 D_800A5150[];
extern s32 D_800A5224[];
extern s32 D_800A5158[];
extern s32 D_800A5230[];
extern s32 D_800A5170[];
extern s32 D_800A523C[];
extern s32 D_800A5188[];
extern s32 D_800A5244[];
extern s32 D_800A51AC[];
extern s32 D_800A524C[];
extern s32 D_800A51C4[];
extern s32 D_800A5258[];
extern s32 D_800A51DC[];
extern s32 D_800A5260[];
extern s32 D_800A51F4[];
extern s32 D_800A526C[];
extern s32 D_800A520C[];
extern s32 D_800A5274[];
extern s32 D_800A5288[];
extern s32 D_800A529C[];
extern s32 D_800A52B0[];
extern s32 D_800A52C4[];
extern s32 D_800A52D8[];
extern s32 D_800A52EC[];
extern s32 D_800A5300[];

s32 D_800A4E4C[] = {
    157, 2, 0x60080000,
};
s32 D_800A4E58[] = {
    157, 2, 0x60080000,
};
s32 D_800A4E64[] = {
    157, 2, 0x60080000,
};
s32 D_800A4E70[] = {
    157, 2, 0x60080000,
};
s32 D_800A4E7C[] = {
    157, 2, 0x60080000,
};
s32 D_800A4E88[] = {
    157, 2, 0x60080000,
};
s32 D_800A4E94[] = {
    157, 2, 0x60080000,
};
s32 D_800A4EA0[] = {
    157, 2, 0x60080000,
};
s32 D_800A4EAC[] = {
    3, (s32)D_800A4E4C, (s32)D_800A4E58, (s32)D_800A4E64,
    (s32)D_800A4E70, (s32)D_800A4E7C, (s32)D_800A4E88, (s32)D_800A4E94,
    (s32)D_800A4EA0,
};
s32 D_800A4ED0[] = {
    95, 2, 0x60080000,
};
s32 D_800A4EDC[] = {
    95, 2, 0x60080000,
};
s32 D_800A4EE8[] = {
    95, 2, 0x60080000,
};
s32 D_800A4EF4[] = {
    95, 2, 0x60080000,
};
s32 D_800A4F00[] = {
    95, 2, 0x60080000,
};
s32 D_800A4F0C[] = {
    95, 2, 0x60080000,
};
s32 D_800A4F18[] = {
    95, 2, 0x60080000,
};
s32 D_800A4F24[] = {
    95, 2, 0x60080000,
};
s32 D_800A4F30[] = {
    3, (s32)D_800A4ED0, (s32)D_800A4EDC, (s32)D_800A4EE8,
    (s32)D_800A4EF4, (s32)D_800A4F00, (s32)D_800A4F0C, (s32)D_800A4F18,
    (s32)D_800A4F24,
};
s32 D_800A4F54[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F60[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F78[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F84[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F90[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FB4[] = {
    0, (s32)D_800A4F54, (s32)D_800A4F60, (s32)D_800A4F6C,
    (s32)D_800A4F78, (s32)D_800A4F84, (s32)D_800A4F90, (s32)D_800A4F9C,
    (s32)D_800A4FA8,
};
s32 D_800A4FD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5008[] = {
    332, 2, 0x60080000,
};
s32 D_800A5014[] = {
    0, 0, 0x60040000,
};
s32 D_800A5020[] = {
    0, 0, 0x60040000,
};
s32 D_800A502C[] = {
    106, 2, 0x60080000,
};
s32 D_800A5038[] = {
    0, (s32)D_800A4FD8, (s32)D_800A4FE4, (s32)D_800A4FF0,
    (s32)D_800A4FFC, (s32)D_800A5008, (s32)D_800A5014, (s32)D_800A5020,
    (s32)D_800A502C,
};
s32 D_800A505C[] = {
    77, 0, 0, (s32)D_800A4EAC,
    (s32)D_800A4F30, (s32)D_800A4FB4, (s32)D_800A5038,
};
s32 D_800A5078[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1300158, 0x300060, 0x1FF0150,
    0x1000140, 0x1300174, 0x3000D0, 0x1FF0160,
    0x1000140, 0x100015A, 104, 0x1FF0170,
    0x1000140, 0x13D0140, 0x3D0000, 0x1FE0140,
    0x1000140, 0x13D0148, 0x3D0020, 0x1FE0150,
};
s32 D_800A5128[] = {
    0x18028, 32809, 65535,
};
s32 D_800A5134[] = {
    0x19404, 65535,
};
s32 D_800A513C[] = {
    0x18028, 0x18029, 65535,
};
s32 D_800A5148[] = {
    0x19406, 65535,
};
s32 D_800A5150[] = {
    0x1940D, 65535,
};
s32 D_800A5158[] = {
    0, 0, 267, 0,
    0, 0,
};
s32 D_800A5170[] = {
    0, 0, 270, 0,
    0, 0,
};
s32 D_800A5188[] = {
    (s32)D_800A5128, (s32)D_800A5134, 730, (s32)D_800A513C,
    (s32)D_800A5148, 730, 0, 0,
    0,
};
s32 D_800A51AC[] = {
    0, (s32)D_800A5150, 730, 0,
    0, 0,
};
s32 D_800A51C4[] = {
    0, 0, 266, 0,
    0, 0,
};
s32 D_800A51DC[] = {
    0, 0, 268, 0,
    0, 0,
};
s32 D_800A51F4[] = {
    0, 0, 269, 0,
    0, 0,
};
s32 D_800A520C[] = {
    0, 0, 271, 0,
    0, 0,
};
s32 D_800A5224[] = {
    0x16026, 0x11A0A, 65535,
};
s32 D_800A5230[] = {
    0x11A0A, 0x16026, 65535,
};
s32 D_800A523C[] = {
    32810, 65535,
};
s32 D_800A5244[] = {
    0x1802A, 65535,
};
s32 D_800A524C[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A5258[] = {
    0x1701A, 65535,
};
s32 D_800A5260[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A526C[] = {
    0x1701A, 65535,
};
s32 D_800A5274[] = {
    (s32)D_800A5224, (s32)D_800A5158, 0x40036, 0x1E001E0,
    1,
};
s32 D_800A5288[] = {
    (s32)D_800A5230, (s32)D_800A5170, 0x50039, 0x218011F,
    7,
};
s32 D_800A529C[] = {
    (s32)D_800A523C, (s32)D_800A5188, 0x6008A, 0x19C00CC,
    7,
};
s32 D_800A52B0[] = {
    (s32)D_800A5244, (s32)D_800A51AC, 0x6008A, 0x19C00CC,
    7,
};
s32 D_800A52C4[] = {
    (s32)D_800A524C, (s32)D_800A51C4, 0x7009D, 0x1E001E0,
    1,
};
s32 D_800A52D8[] = {
    (s32)D_800A5258, (s32)D_800A51DC, 0x7009D, 0x1E001E0,
    1,
};
s32 D_800A52EC[] = {
    (s32)D_800A5260, (s32)D_800A51F4, 0x8009E, 0x218011F,
    7,
};
s32 D_800A5300[] = {
    (s32)D_800A526C, (s32)D_800A520C, 0x8009E, 0x218011F,
    7,
};
s32 D_800A5314[] = {
    (s32)D_800A5274, (s32)D_800A5288, (s32)D_800A529C, (s32)D_800A52B0,
    (s32)D_800A52C4, (s32)D_800A52D8, (s32)D_800A52EC, (s32)D_800A5300,
    0,
};
s32 D_800A5338[] = {
    0x2400001, 0, 0x1A80000, 218,
    0x10000, 0x12C0640, 0xA3B2C, 0x25C0119,
    0, 0x6400001, 0x3B2C012C, 0x208000A,
    144, 0x10000, 0x12C0640, 0xA3B2C,
    0x1A2026D, 0, 0x6400001, 0x463C013C,
    0x15B000A, 144, 0x10000, 0x13C0640,
    0xA463C, 0x13B017E, 0, 0x6400001,
    0x463C013C, 0x267000A, 560, 0x10000,
    0x60464, 0, 0x15F00D1, 391,
    0, 0, 0, 0,
    0,
};
s32 D_800A53DC[] = {
    65535, 65535, 0x2A90001, 0x1BE0088,
    7, 0, 0x17093, 65535,
    0x2E3000A, 0x700380, 1, 0x10013,
    0x18005, 65535, 0x500007, 65496,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A543C[])(void) = {
    func_800A4D48,
};
