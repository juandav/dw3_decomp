#include "common.h"
#include "stage.h"
extern void (*D_800A54D8[])(void);
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
    D_800A54D8[0]();
    return task;
}

extern s32 D_800A52C0[];
extern s32 D_800A5460[];
extern s32 D_800A50BC[];
extern s32 D_800A52A4[];
extern s32 D_800A50A0[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x561
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x571
#endif
void func_800A4D48(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A52C0;
    D_800990B4.unk14 = D_800A5460;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xE400, 0xA600};
    D_800990B4.unk28 = D_800A50BC;
    D_800990B4.unk3C = 9;
    D_800990B4.unk40 = 0x60240000;
    D_800990B4.unk4C = D_800A52A4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A50A0;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS != 0x26 || FLAGS_00.checkCondition(0x1A0A, 0) != 0) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}

void func_800A4D48();
extern s32 D_800A4E90[];
extern s32 D_800A4E9C[];
extern s32 D_800A4EA8[];
extern s32 D_800A4EB4[];
extern s32 D_800A4EC0[];
extern s32 D_800A4ECC[];
extern s32 D_800A4ED8[];
extern s32 D_800A4EE4[];
extern s32 D_800A4F14[];
extern s32 D_800A4F20[];
extern s32 D_800A4F2C[];
extern s32 D_800A4F38[];
extern s32 D_800A4F44[];
extern s32 D_800A4F50[];
extern s32 D_800A4F5C[];
extern s32 D_800A4F68[];
extern s32 D_800A4F98[];
extern s32 D_800A4FA4[];
extern s32 D_800A4FB0[];
extern s32 D_800A4FBC[];
extern s32 D_800A4FC8[];
extern s32 D_800A4FD4[];
extern s32 D_800A4FE0[];
extern s32 D_800A4FEC[];
extern s32 D_800A501C[];
extern s32 D_800A5028[];
extern s32 D_800A5034[];
extern s32 D_800A5040[];
extern s32 D_800A504C[];
extern s32 D_800A5058[];
extern s32 D_800A5064[];
extern s32 D_800A5070[];
extern s32 D_800A4EF0[];
extern s32 D_800A4F74[];
extern s32 D_800A4FF8[];
extern s32 D_800A507C[];
extern s32 D_800A51EC[];
extern s32 D_800A515C[];
extern s32 D_800A51F8[];
extern s32 D_800A5174[];
extern s32 D_800A5204[];
extern s32 D_800A518C[];
extern s32 D_800A5210[];
extern s32 D_800A51A4[];
extern s32 D_800A5218[];
extern s32 D_800A51BC[];
extern s32 D_800A5224[];
extern s32 D_800A51D4[];
extern s32 D_800A522C[];
extern s32 D_800A5240[];
extern s32 D_800A5254[];
extern s32 D_800A5268[];
extern s32 D_800A527C[];
extern s32 D_800A5290[];

s32 D_800A4E90[] = {
    93, 1, 0x60080000,
};
s32 D_800A4E9C[] = {
    93, 1, 0x60080000,
};
s32 D_800A4EA8[] = {
    93, 1, 0x60080000,
};
s32 D_800A4EB4[] = {
    93, 1, 0x60080000,
};
s32 D_800A4EC0[] = {
    127, 1, 0x60080000,
};
s32 D_800A4ECC[] = {
    127, 1, 0x60080000,
};
s32 D_800A4ED8[] = {
    127, 1, 0x60080000,
};
s32 D_800A4EE4[] = {
    127, 1, 0x60080000,
};
s32 D_800A4EF0[] = {
    3, (s32)D_800A4E90, (s32)D_800A4E9C, (s32)D_800A4EA8,
    (s32)D_800A4EB4, (s32)D_800A4EC0, (s32)D_800A4ECC, (s32)D_800A4ED8,
    (s32)D_800A4EE4,
};
s32 D_800A4F14[] = {
    93, 13, 0x60080000,
};
s32 D_800A4F20[] = {
    93, 13, 0x60080000,
};
s32 D_800A4F2C[] = {
    93, 13, 0x60080000,
};
s32 D_800A4F38[] = {
    93, 13, 0x60080000,
};
s32 D_800A4F44[] = {
    127, 13, 0x60080000,
};
s32 D_800A4F50[] = {
    127, 13, 0x60080000,
};
s32 D_800A4F5C[] = {
    127, 13, 0x60080000,
};
s32 D_800A4F68[] = {
    127, 13, 0x60080000,
};
s32 D_800A4F74[] = {
    3, (s32)D_800A4F14, (s32)D_800A4F20, (s32)D_800A4F2C,
    (s32)D_800A4F38, (s32)D_800A4F44, (s32)D_800A4F50, (s32)D_800A4F5C,
    (s32)D_800A4F68,
};
s32 D_800A4F98[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A4FF8[] = {
    0, (s32)D_800A4F98, (s32)D_800A4FA4, (s32)D_800A4FB0,
    (s32)D_800A4FBC, (s32)D_800A4FC8, (s32)D_800A4FD4, (s32)D_800A4FE0,
    (s32)D_800A4FEC,
};
s32 D_800A501C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5028[] = {
    0, 0, 0x60040000,
};
s32 D_800A5034[] = {
    0, 0, 0x60040000,
};
s32 D_800A5040[] = {
    329, 13, 0x60080000,
};
s32 D_800A504C[] = {
    330, 8, 0x60080000,
};
s32 D_800A5058[] = {
    0, 0, 0x60040000,
};
s32 D_800A5064[] = {
    93, 13, 0x60080000,
};
s32 D_800A5070[] = {
    180, 8, 0x60080000,
};
s32 D_800A507C[] = {
    0, (s32)D_800A501C, (s32)D_800A5028, (s32)D_800A5034,
    (s32)D_800A5040, (s32)D_800A504C, (s32)D_800A5058, (s32)D_800A5064,
    (s32)D_800A5070,
};
s32 D_800A50A0[] = {
    93, 0, 0, (s32)D_800A4EF0,
    (s32)D_800A4F74, (s32)D_800A4FF8, (s32)D_800A507C,
};
s32 D_800A50BC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1180166, 0x180098, 0x1FF0150,
    0x1000140, 0x118016E, 0x1800B8, 0x1FF0160,
    0x1000140, 0x1180176, 0x1800D8, 0x1FF0170,
    0x1000140, 0x1300154, 0x300050, 0x1FE0140,
};
s32 D_800A515C[] = {
    0, 0, 47, 0,
    0, 0,
};
s32 D_800A5174[] = {
    0, 0, 44, 0,
    0, 0,
};
s32 D_800A518C[] = {
    0, 0, 46, 0,
    0, 0,
};
s32 D_800A51A4[] = {
    0, 0, 48, 0,
    0, 0,
};
s32 D_800A51BC[] = {
    0, 0, 43, 0,
    0, 0,
};
s32 D_800A51D4[] = {
    0, 0, 45, 0,
    0, 0,
};
s32 D_800A51EC[] = {
    0x11A0A, 0x16026, 65535,
};
s32 D_800A51F8[] = {
    0x11A0A, 0x16026, 65535,
};
s32 D_800A5204[] = {
    6666, 0x1701E, 65535,
};
s32 D_800A5210[] = {
    0x1701A, 65535,
};
s32 D_800A5218[] = {
    0x1701E, 6666, 65535,
};
s32 D_800A5224[] = {
    0x1701A, 65535,
};
s32 D_800A522C[] = {
    (s32)D_800A51EC, (s32)D_800A515C, 0x40030, 0x1350187,
    7,
};
s32 D_800A5240[] = {
    (s32)D_800A51F8, (s32)D_800A5174, 0x50033, 0x2AC0169,
    1,
};
s32 D_800A5254[] = {
    (s32)D_800A5204, (s32)D_800A518C, 0x6009D, 0x1350187,
    7,
};
s32 D_800A5268[] = {
    (s32)D_800A5210, (s32)D_800A51A4, 0x6009D, 0x1350187,
    7,
};
s32 D_800A527C[] = {
    (s32)D_800A5218, (s32)D_800A51BC, 0x7009E, 0x2AC0169,
    1,
};
s32 D_800A5290[] = {
    (s32)D_800A5224, (s32)D_800A51D4, 0x7009E, 0x2AC0169,
    1,
};
s32 D_800A52A4[] = {
    (s32)D_800A522C, (s32)D_800A5240, (s32)D_800A5254, (s32)D_800A5268,
    (s32)D_800A527C, (s32)D_800A5290, 0,
};
s32 D_800A52C0[] = {
    0x2400001, 0, 0xC50000, 606,
    0x10000, 576, 0, 0xFFF0015F,
    0, 0x2400001, 0, 0x1FF0000,
    284, 0x10000, 0x12C0640, 0xA3B2C,
    0x1FD001B, 0, 0x6400001, 0x3B2C012C,
    0xFF000A, 408, 0x10000, 0x13C0640,
    0xA463C, 0x24A001C, 0, 0x6400001,
    0x463C013C, 0xA0000A, 515, 0x10000,
    0x13C0640, 0xA463C, 0x17A00B7, 0,
    0x464FF01, 56, 0xB80000, 0xE200E2,
    0xFF010000, 0x380464, 0, 0xFA00E8,
    250, 0x464FF01, 56, 0xF30000,
    0x2200220, 0xFF010000, 0x380464, 0,
    0x25A010B, 602, 0x464FF01, 56,
    0x10F0000, 0x870087, 0xFF010000, 0x380464,
    0, 0x2090115, 521, 0x464FF01,
    56, 0x1400000, 0x9F009F, 0xFF010000,
    0x380464, 0, 0xA7018F, 167,
    0x464FF01, 56, 0x1A60000, 0xBB00BB,
    0xFF010000, 0x380464, 0, 0x23801AF,
    568, 0x464FF01, 56, 0x1E90000,
    0x1F501F5, 0xFF010000, 0x380464, 0,
    0xCB01FA, 203, 0x464FF01, 56,
    0x21E0000, 0xE400E4, 0xFF010000, 0x380464,
    0, 0x11E0281, 286, 0,
    0, 0, 0, 0,
};
s32 D_800A5460[] = {
    65535, 65535, 0x28C0001, 0x39E05F4,
    3, 0, 65535, 65535,
    0x2900001, 0x7A0138, 7, 0,
    0x18005, 65535, 0xFFC00007, 48,
    0, 0, 0x18005, 65535,
    0xFFC80007, 65520, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A54D8[])(void) = {
    func_800A4D48,
};
