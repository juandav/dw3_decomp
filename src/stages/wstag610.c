#include "common.h"
#include "stage.h"
extern void (*D_800A527C[])(void);
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
    D_800A527C[0]();
    return task;
}

extern s32 D_800A50CC[];
extern s32 D_800A5234[];
extern s32 D_800A506C[];
extern s32 D_800A5050[];
#if VERSION_US
#define STAGE_TEXT 0xF7
#define STAGE_FILE 0x4B0
#define STAGE_FILE_8 0x4AA
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xEF)
#define STAGE_FILE 0x4C0
#define STAGE_FILE_8 0x4BA
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE_8;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A50CC;
    D_800990B4.unk14 = D_800A5234;
    D_800990B4.unk1C = STAGE_FILE - 1;
    D_800990B4.unk2C = (Vec2){0xD300, 0x26100};
    D_800990B4.unk28 = D_800A506C;
    D_800990B4.unk3C = 0x3A;
    D_800990B4.unk40 = 0x60E80000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5050;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4D48();
extern s32 D_800A4E40[];
extern s32 D_800A4E4C[];
extern s32 D_800A4E58[];
extern s32 D_800A4E64[];
extern s32 D_800A4E70[];
extern s32 D_800A4E7C[];
extern s32 D_800A4E88[];
extern s32 D_800A4E94[];
extern s32 D_800A4EC4[];
extern s32 D_800A4ED0[];
extern s32 D_800A4EDC[];
extern s32 D_800A4EE8[];
extern s32 D_800A4EF4[];
extern s32 D_800A4F00[];
extern s32 D_800A4F0C[];
extern s32 D_800A4F18[];
extern s32 D_800A4F48[];
extern s32 D_800A4F54[];
extern s32 D_800A4F60[];
extern s32 D_800A4F6C[];
extern s32 D_800A4F78[];
extern s32 D_800A4F84[];
extern s32 D_800A4F90[];
extern s32 D_800A4F9C[];
extern s32 D_800A4FCC[];
extern s32 D_800A4FD8[];
extern s32 D_800A4FE4[];
extern s32 D_800A4FF0[];
extern s32 D_800A4FFC[];
extern s32 D_800A5008[];
extern s32 D_800A5014[];
extern s32 D_800A5020[];
extern s32 D_800A4EA0[];
extern s32 D_800A4F24[];
extern s32 D_800A4FA8[];
extern s32 D_800A502C[];

s32 D_800A4E40[] = {
    80, 12, 0x60080000,
};
s32 D_800A4E4C[] = {
    80, 12, 0x60080000,
};
s32 D_800A4E58[] = {
    80, 12, 0x60080000,
};
s32 D_800A4E64[] = {
    80, 12, 0x60080000,
};
s32 D_800A4E70[] = {
    75, 12, 0x60080000,
};
s32 D_800A4E7C[] = {
    75, 12, 0x60080000,
};
s32 D_800A4E88[] = {
    75, 12, 0x60080000,
};
s32 D_800A4E94[] = {
    75, 12, 0x60080000,
};
s32 D_800A4EA0[] = {
    2, (s32)D_800A4E40, (s32)D_800A4E4C, (s32)D_800A4E58,
    (s32)D_800A4E64, (s32)D_800A4E70, (s32)D_800A4E7C, (s32)D_800A4E88,
    (s32)D_800A4E94,
};
s32 D_800A4EC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4ED0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4EF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F00[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F18[] = {
    0, 0, 0x60040000,
};
s32 D_800A4F24[] = {
    0, (s32)D_800A4EC4, (s32)D_800A4ED0, (s32)D_800A4EDC,
    (s32)D_800A4EE8, (s32)D_800A4EF4, (s32)D_800A4F00, (s32)D_800A4F0C,
    (s32)D_800A4F18,
};
s32 D_800A4F48[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A4F48, (s32)D_800A4F54, (s32)D_800A4F60,
    (s32)D_800A4F6C, (s32)D_800A4F78, (s32)D_800A4F84, (s32)D_800A4F90,
    (s32)D_800A4F9C,
};
s32 D_800A4FCC[] = {
    0, 0, 0x60040000,
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
    0, 0, 0x60040000,
};
s32 D_800A5014[] = {
    0, 0, 0x60040000,
};
s32 D_800A5020[] = {
    0, 0, 0x60040000,
};
s32 D_800A502C[] = {
    0, (s32)D_800A4FCC, (s32)D_800A4FD8, (s32)D_800A4FE4,
    (s32)D_800A4FF0, (s32)D_800A4FFC, (s32)D_800A5008, (s32)D_800A5014,
    (s32)D_800A5020,
};
s32 D_800A5050[] = {
    47, 0, 0, (s32)D_800A4EA0,
    (s32)D_800A4F24, (s32)D_800A4FA8, (s32)D_800A502C,
};
s32 D_800A506C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A50CC[] = {
    0x2800001, 2, 0x1CF0000, 0,
    0x10000, 0x30280, 0, 512,
    0, 0x6400001, 0x37320132, 0xB40004,
    506, 0x10000, 0x1320640, 0x43732,
    0x18400F9, 0, 0x6400001, 0x3D380138,
    0xA00004, 486, 0x10000, 0x1380640,
    0x43D38, 0x17000E5, 0, 0x6400001,
    0x100023E, 0x1840004, 395, 0x10000,
    0x23E0640, 0x40100, 0x19F01AD, 0,
    0x6400001, 0x100023E, 0x1B90004, 565,
    0x10000, 0x23E0640, 0x40100, 0x1B301D4,
    0, 0x6400001, 0x100023E, 0x1E20004,
    585, 0x10000, 0x23F0440, 0x40100,
    0x8A01CC, 584, 0x4400001, 0x100023F,
    0x1EC0004, 0x248009A, 0x10000, 0x23F0440,
    0x40100, 0xC9024A, 584, 0x4650001,
    0, 0x540000, 0x24801E4, 0x10000,
    0x40440, 0, 0x8801E9, 190,
    0x4400001, 5, 0x1FD0000, 0xC60088,
    0x10000, 0x60440, 0, 0x88020D,
    207, 0x4400001, 7, 0x21D0000,
    0xD70088, 0, 0, 0,
    0, 0,
};
s32 D_800A5234[] = {
    65535, 65535, 0x24D0001, 0x22C0088,
    7, 0, 65535, 65535,
    0x2540001, 0x2F003F0, 3, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A527C[])(void) = {
    func_800A4D48,
};
