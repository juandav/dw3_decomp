#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A670C[])(void);
extern StagePoints *D_800A6264[];

void func_800A5DE4(StageSlot *slots, StagePoints **list, s32 id0, s32 id1) {
    StagePoints *place;
    StagePoint *point;

    for (;;) {
        place = *list;
        if (place == NULL) {
            return;
        }
        if (place->unk0 == id0 && place->unk2 == id1) {
            break;
        }
        list++;
    }
    point = place->points;
    slots->unkA = point->unk0;
    slots->unkC = point->unk6;
    slots->unkE = point->unk8;
    slots->unk10 = point->unkA;
    slots->unk14 = point->unk2;
    slots->unk16 = point->unk4;
    while (point->next != NULL) {
        point = point->next;
        slots++;
        slots->unkA = point->unk0;
        slots->unkC = point->unk6;
        slots->unkE = point->unk8;
        slots->unk10 = point->unkA;
        slots->unk14 = point->unk2;
        slots->unk16 = point->unk4;
    }
}

void func_800A5EE4(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A5DE4(D_800990B4.unk14, D_800A6264, GAME.unk44, GAME.unk46);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5F58(void *owner) {
    StageTask *task = createTask(func_800A5EE4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A670C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag964", func_800A5FB4);

void func_800A5FB4();
extern StagePoint D_800A60FC;
extern StagePoint D_800A610C;
extern StagePoint D_800A6124;
extern StagePoint D_800A6134;
extern StagePoint D_800A614C;
extern StagePoint D_800A615C;
extern StagePoint D_800A6174;
extern StagePoint D_800A6184;
extern StagePoint D_800A619C;
extern StagePoint D_800A61AC;
extern StagePoint D_800A61C4;
extern StagePoint D_800A61D4;
extern StagePoint D_800A61EC;
extern StagePoint D_800A61FC;
extern StagePoint D_800A6214;
extern StagePoint D_800A6224;
extern StagePoint D_800A623C;
extern StagePoint D_800A624C;
extern StagePoints D_800A611C;
extern StagePoints D_800A6144;
extern StagePoints D_800A616C;
extern StagePoints D_800A6194;
extern StagePoints D_800A61BC;
extern StagePoints D_800A61E4;
extern StagePoints D_800A620C;
extern StagePoints D_800A6234;
extern StagePoints D_800A625C;
extern s32 D_800A632C[];
extern s32 D_800A6338[];
extern s32 D_800A6344[];
extern s32 D_800A6350[];
extern s32 D_800A6358[];
extern s32 D_800A6364[];
extern s32 D_800A636C[];
extern s32 D_800A637C[];
extern s32 D_800A638C[];
extern s32 D_800A639C[];
extern s32 D_800A63A4[];
extern s32 D_800A63B0[];
extern s32 D_800A63B8[];
extern s32 D_800A63C8[];
extern s32 D_800A63D8[];
extern s32 D_800A64A8[];
extern s32 D_800A63E8[];
extern s32 D_800A64B8[];
extern s32 D_800A6400[];
extern s32 D_800A64C8[];
extern s32 D_800A6418[];
extern s32 D_800A64D8[];
extern s32 D_800A6430[];
extern s32 D_800A64F4[];
extern s32 D_800A646C[];
extern s32 D_800A6510[];
extern s32 D_800A6524[];
extern s32 D_800A6538[];
extern s32 D_800A654C[];
extern s32 D_800A6560[];
extern s32 D_800A6574[];
extern s32 D_800A6710[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A6740[];
extern s32 D_800A674C[];
extern s32 D_800A6758[];
extern s32 D_800A6764[];
extern s32 D_800A6794[];
extern s32 D_800A67A0[];
extern s32 D_800A67AC[];
extern s32 D_800A67B8[];
extern s32 D_800A67C4[];
extern s32 D_800A67D0[];
extern s32 D_800A67DC[];
extern s32 D_800A67E8[];
extern s32 D_800A6818[];
extern s32 D_800A6824[];
extern s32 D_800A6830[];
extern s32 D_800A683C[];
extern s32 D_800A6848[];
extern s32 D_800A6854[];
extern s32 D_800A6860[];
extern s32 D_800A686C[];
extern s32 D_800A689C[];
extern s32 D_800A68A8[];
extern s32 D_800A68B4[];
extern s32 D_800A68C0[];
extern s32 D_800A68CC[];
extern s32 D_800A68D8[];
extern s32 D_800A68E4[];
extern s32 D_800A68F0[];
extern s32 D_800A6920[];
extern s32 D_800A692C[];
extern s32 D_800A6938[];
extern s32 D_800A6944[];
extern s32 D_800A6950[];
extern s32 D_800A695C[];
extern s32 D_800A6968[];
extern s32 D_800A6974[];
extern s32 D_800A69A4[];
extern s32 D_800A69B0[];
extern s32 D_800A69BC[];
extern s32 D_800A69C8[];
extern s32 D_800A69D4[];
extern s32 D_800A69E0[];
extern s32 D_800A69EC[];
extern s32 D_800A69F8[];
extern s32 D_800A6A28[];
extern s32 D_800A6A34[];
extern s32 D_800A6A40[];
extern s32 D_800A6A4C[];
extern s32 D_800A6A58[];
extern s32 D_800A6A64[];
extern s32 D_800A6A70[];
extern s32 D_800A6A7C[];
extern s32 D_800A6AAC[];
extern s32 D_800A6AB8[];
extern s32 D_800A6AC4[];
extern s32 D_800A6AD0[];
extern s32 D_800A6ADC[];
extern s32 D_800A6AE8[];
extern s32 D_800A6AF4[];
extern s32 D_800A6B00[];
extern s32 D_800A6B30[];
extern s32 D_800A6B3C[];
extern s32 D_800A6B48[];
extern s32 D_800A6B54[];
extern s32 D_800A6B60[];
extern s32 D_800A6B6C[];
extern s32 D_800A6B78[];
extern s32 D_800A6B84[];
extern s32 D_800A6BB4[];
extern s32 D_800A6BC0[];
extern s32 D_800A6BCC[];
extern s32 D_800A6BD8[];
extern s32 D_800A6BE4[];
extern s32 D_800A6BF0[];
extern s32 D_800A6BFC[];
extern s32 D_800A6C08[];
extern s32 D_800A6C38[];
extern s32 D_800A6C44[];
extern s32 D_800A6C50[];
extern s32 D_800A6C5C[];
extern s32 D_800A6C68[];
extern s32 D_800A6C74[];
extern s32 D_800A6C80[];
extern s32 D_800A6C8C[];
extern s32 D_800A6CBC[];
extern s32 D_800A6CC8[];
extern s32 D_800A6CD4[];
extern s32 D_800A6CE0[];
extern s32 D_800A6CEC[];
extern s32 D_800A6CF8[];
extern s32 D_800A6D04[];
extern s32 D_800A6D10[];
extern s32 D_800A6D40[];
extern s32 D_800A6D4C[];
extern s32 D_800A6D58[];
extern s32 D_800A6D64[];
extern s32 D_800A6D70[];
extern s32 D_800A6D7C[];
extern s32 D_800A6D88[];
extern s32 D_800A6D94[];
extern s32 D_800A6DC4[];
extern s32 D_800A6DD0[];
extern s32 D_800A6DDC[];
extern s32 D_800A6DE8[];
extern s32 D_800A6DF4[];
extern s32 D_800A6E00[];
extern s32 D_800A6E0C[];
extern s32 D_800A6E18[];
extern s32 D_800A6E48[];
extern s32 D_800A6E54[];
extern s32 D_800A6E60[];
extern s32 D_800A6E6C[];
extern s32 D_800A6E78[];
extern s32 D_800A6E84[];
extern s32 D_800A6E90[];
extern s32 D_800A6E9C[];
extern s32 D_800A6ECC[];
extern s32 D_800A6ED8[];
extern s32 D_800A6EE4[];
extern s32 D_800A6EF0[];
extern s32 D_800A6EFC[];
extern s32 D_800A6F08[];
extern s32 D_800A6F14[];
extern s32 D_800A6F20[];
extern s32 D_800A6770[];
extern s32 D_800A67F4[];
extern s32 D_800A6878[];
extern s32 D_800A68FC[];
extern s32 D_800A6980[];
extern s32 D_800A6A04[];
extern s32 D_800A6A88[];
extern s32 D_800A6B0C[];
extern s32 D_800A6B90[];
extern s32 D_800A6C14[];
extern s32 D_800A6C98[];
extern s32 D_800A6D1C[];
extern s32 D_800A6DA0[];
extern s32 D_800A6E24[];
extern s32 D_800A6EA8[];
extern s32 D_800A6F2C[];

StagePoint D_800A60FC = { 0x2E6, 2, 2, 0x450, 0x248, 1, NULL };
StagePoint D_800A610C = { 0x2E6, 2, 1, 160, 0x150, 5, &D_800A60FC };
StagePoints D_800A611C = { 2, 1, &D_800A610C };
StagePoint D_800A6124 = { 0x2E4, 2, 3, 0x340, 160, 1, NULL };
StagePoint D_800A6134 = { 0x2E6, 2, 2, 160, 0x150, 5, &D_800A6124 };
StagePoints D_800A6144 = { 2, 2, &D_800A6134 };
StagePoint D_800A614C = { 0x2E6, 2, 3, 0x450, 0x248, 1, NULL };
StagePoint D_800A615C = { 0x2E4, 2, 2, 192, 0x180, 5, &D_800A614C };
StagePoints D_800A616C = { 2, 3, &D_800A615C };
StagePoint D_800A6174 = { 0x2E2, 2, 1, 0x330, 248, 1, NULL };
StagePoint D_800A6184 = { 0x2E6, 2, 3, 160, 0x150, 5, &D_800A6174 };
StagePoints D_800A6194 = { 2, 4, &D_800A6184 };
StagePoint D_800A619C = { 0x2E5, 3, 1, 0x3B0, 216, 1, NULL };
StagePoint D_800A61AC = { 0x2E0, 3, 1, 176, 0x178, 5, &D_800A619C };
StagePoints D_800A61BC = { 3, 1, &D_800A61AC };
StagePoint D_800A61C4 = { 0x2E7, 4, 1, 0x250, 232, 1, NULL };
StagePoint D_800A61D4 = { 0x2E6, 4, 1, 160, 0x150, 5, &D_800A61C4 };
StagePoints D_800A61E4 = { 4, 1, &D_800A61D4 };
StagePoint D_800A61EC = { 0x2E6, 5, 1, 0x450, 0x248, 1, NULL };
StagePoint D_800A61FC = { 0x2E0, 5, 1, 176, 0x178, 5, &D_800A61EC };
StagePoints D_800A620C = { 5, 1, &D_800A61FC };
StagePoint D_800A6214 = { 0x2E4, 5, 3, 0x340, 160, 1, NULL };
StagePoint D_800A6224 = { 0x2E6, 5, 1, 160, 0x150, 5, &D_800A6214 };
StagePoints D_800A6234 = { 5, 2, &D_800A6224 };
StagePoint D_800A623C = { 0x2E7, 5, 1, 0x250, 232, 1, NULL };
StagePoint D_800A624C = { 0x2E4, 5, 2, 192, 0x180, 5, &D_800A623C };
StagePoints D_800A625C = { 5, 3, &D_800A624C };
StagePoints *D_800A6264[] = {
    &D_800A611C, &D_800A6144, &D_800A616C, &D_800A6194,
    &D_800A61BC, &D_800A61E4, &D_800A620C, &D_800A6234,
    &D_800A625C, NULL,
};
s32 D_800A628C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1A0014A, 0xA00028, 0x1FF0150,
    0x1000180, 0x17801B0, 0x7801C0, 0x1FF0160,
    0x1000140, 0x1D00170, 0xD000C0, 0x1FF0170,
    0x1000180, 0x10001A0, 384, 0x1FE0140,
};
s32 D_800A632C[] = {
    0x10273, 0x18234, 65535,
};
s32 D_800A6338[] = {
    0x1026F, 0x1847D, 65535,
};
s32 D_800A6344[] = {
    0x10270, 0x1848A, 65535,
};
s32 D_800A6350[] = {
    0x18676, 65535,
};
s32 D_800A6358[] = {
    34422, 0, 65535,
};
s32 D_800A6364[] = {
    0x10000, 65535,
};
s32 D_800A636C[] = {
    34422, 0x10000, 33906, 65535,
};
s32 D_800A637C[] = {
    34422, 0x10000, 0x18472, 65535,
};
s32 D_800A638C[] = {
    0x18676, 34421, 33906, 65535,
};
s32 D_800A639C[] = {
    0x1869B, 65535,
};
s32 D_800A63A4[] = {
    34459, 0, 65535,
};
s32 D_800A63B0[] = {
    0x10000, 65535,
};
s32 D_800A63B8[] = {
    34459, 0x10000, 33943, 65535,
};
s32 D_800A63C8[] = {
    34459, 0x10000, 0x18497, 65535,
};
s32 D_800A63D8[] = {
    0x1869B, 34458, 33943, 65535,
};
s32 D_800A63E8[] = {
    0, (s32)D_800A632C, 11, 0,
    0, 0,
};
s32 D_800A6400[] = {
    0, (s32)D_800A6338, 7, 0,
    0, 0,
};
s32 D_800A6418[] = {
    0, (s32)D_800A6344, 8, 0,
    0, 0,
};
s32 D_800A6430[] = {
    (s32)D_800A6350, 0, 177, (s32)D_800A6358,
    (s32)D_800A6364, 178, (s32)D_800A636C, 0,
    179, (s32)D_800A637C, (s32)D_800A638C, 180,
    0, 0, 0,
};
s32 D_800A646C[] = {
    (s32)D_800A639C, 0, 181, (s32)D_800A63A4,
    (s32)D_800A63B0, 182, (s32)D_800A63B8, 0,
    183, (s32)D_800A63C8, (s32)D_800A63D8, 184,
    0, 0, 0,
};
s32 D_800A64A8[] = {
    0x17E01, 0x17E1E, 627, 65535,
};
s32 D_800A64B8[] = {
    0x17E01, 0x17E21, 623, 65535,
};
s32 D_800A64C8[] = {
    0x17E04, 0x17E1E, 624, 65535,
};
s32 D_800A64D8[] = {
    0x17E01, 0x17E1F, 0x17055, 0x17095,
    0x18675, 34422, 65535,
};
s32 D_800A64F4[] = {
    0x17E03, 0x17E1E, 0x17055, 0x17095,
    0x1869A, 34459, 65535,
};
s32 D_800A6510[] = {
    (s32)D_800A64A8, (s32)D_800A63E8, 0x40021, 0xF00220,
    1,
};
s32 D_800A6524[] = {
    (s32)D_800A64B8, (s32)D_800A6400, 0x40021, 0xF00220,
    1,
};
s32 D_800A6538[] = {
    (s32)D_800A64C8, (s32)D_800A6418, 0x40021, 0xF00220,
    1,
};
s32 D_800A654C[] = {
    (s32)D_800A64D8, (s32)D_800A6430, 0x500A8, 0xF00220,
    1,
};
s32 D_800A6560[] = {
    (s32)D_800A64F4, (s32)D_800A646C, 0x600AA, 0xF00220,
    1,
};
s32 D_800A6574[] = {
    0, 0, 0x70147, 0,
    0,
};
s32 D_800A6588[] = {
    (s32)D_800A6510, (s32)D_800A6524, (s32)D_800A6538, (s32)D_800A654C,
    (s32)D_800A6560, (s32)D_800A6574, 0,
};
s32 D_800A65A4[] = {
    0x28F0001, 0x4B370137, 0xC8000A, 265,
    0x10000, 0x137028F, 0xA4B37, 0xB90230,
    0, 0x28F0001, 0x4B370137, 0x359000A,
    33, 0x10000, 0x14C02B6, 0xA624C,
    0xB4018B, 0, 0x68F0001, 0x4B370137,
    0x1F4000A, 39, 0x10000, 0x14C06B6,
    0xA624C, 659, 0, 0x6680001,
    0x36340134, 0xB0000A, 128, 0x10000,
    0x1340668, 0xA3634, 0x2902F6, 0,
    0x48A0001, 3, 0x1A00000, 0x14700BF,
    0x10000, 0x40452, 0, 0xAE0180,
    311, 0x4830001, 5, 0x1600000,
    0x12700A9, 0x10000, 0x6048E, 0,
    0x9A0140, 279, 0x4540001, 8,
    0x2A00000, 0x10C00B1, 0x10000, 0x90466,
    0, 0xA20280, 251, 0x4600001,
    10, 0x2700000, 0xF2009C, 0,
    0, 0, 0, 0,
};
s32 D_800A66C4[] = {
    65535, 65535, 0x2E40001, 0xA00340,
    5, 0, 65535, 65535,
    0x2E40001, 0x18000C0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A670C[])(void) = {
    func_800A5FB4,
};
s32 D_800A6710[] = {
    62, 11, 0x60080000,
};
s32 D_800A671C[] = {
    62, 11, 0x60080000,
};
s32 D_800A6728[] = {
    62, 11, 0x60080000,
};
s32 D_800A6734[] = {
    106, 11, 0x60080000,
};
s32 D_800A6740[] = {
    106, 11, 0x60080000,
};
s32 D_800A674C[] = {
    106, 11, 0x60080000,
};
s32 D_800A6758[] = {
    276, 11, 0x60080000,
};
s32 D_800A6764[] = {
    276, 11, 0x60080000,
};
s32 D_800A6770[] = {
    3, (s32)D_800A6710, (s32)D_800A671C, (s32)D_800A6728,
    (s32)D_800A6734, (s32)D_800A6740, (s32)D_800A674C, (s32)D_800A6758,
    (s32)D_800A6764,
};
s32 D_800A6794[] = {
    0, 0, 0x60040000,
};
s32 D_800A67A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67F4[] = {
    0, (s32)D_800A6794, (s32)D_800A67A0, (s32)D_800A67AC,
    (s32)D_800A67B8, (s32)D_800A67C4, (s32)D_800A67D0, (s32)D_800A67DC,
    (s32)D_800A67E8,
};
s32 D_800A6818[] = {
    0, 0, 0x60040000,
};
s32 D_800A6824[] = {
    0, 0, 0x60040000,
};
s32 D_800A6830[] = {
    0, 0, 0x60040000,
};
s32 D_800A683C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6848[] = {
    0, 0, 0x60040000,
};
s32 D_800A6854[] = {
    0, 0, 0x60040000,
};
s32 D_800A6860[] = {
    0, 0, 0x60040000,
};
s32 D_800A686C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6878[] = {
    0, (s32)D_800A6818, (s32)D_800A6824, (s32)D_800A6830,
    (s32)D_800A683C, (s32)D_800A6848, (s32)D_800A6854, (s32)D_800A6860,
    (s32)D_800A686C,
};
s32 D_800A689C[] = {
    0, 0, 0x60040000,
};
s32 D_800A68A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68FC[] = {
    0, (s32)D_800A689C, (s32)D_800A68A8, (s32)D_800A68B4,
    (s32)D_800A68C0, (s32)D_800A68CC, (s32)D_800A68D8, (s32)D_800A68E4,
    (s32)D_800A68F0,
};
s32 D_800A6920[] = {
    64, 11, 0x60080000,
};
s32 D_800A692C[] = {
    64, 11, 0x60080000,
};
s32 D_800A6938[] = {
    64, 11, 0x60080000,
};
s32 D_800A6944[] = {
    64, 11, 0x60080000,
};
s32 D_800A6950[] = {
    64, 11, 0x60080000,
};
s32 D_800A695C[] = {
    64, 11, 0x60080000,
};
s32 D_800A6968[] = {
    64, 11, 0x60080000,
};
s32 D_800A6974[] = {
    64, 11, 0x60080000,
};
s32 D_800A6980[] = {
    3, (s32)D_800A6920, (s32)D_800A692C, (s32)D_800A6938,
    (s32)D_800A6944, (s32)D_800A6950, (s32)D_800A695C, (s32)D_800A6968,
    (s32)D_800A6974,
};
s32 D_800A69A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A04[] = {
    0, (s32)D_800A69A4, (s32)D_800A69B0, (s32)D_800A69BC,
    (s32)D_800A69C8, (s32)D_800A69D4, (s32)D_800A69E0, (s32)D_800A69EC,
    (s32)D_800A69F8,
};
s32 D_800A6A28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A34[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A88[] = {
    0, (s32)D_800A6A28, (s32)D_800A6A34, (s32)D_800A6A40,
    (s32)D_800A6A4C, (s32)D_800A6A58, (s32)D_800A6A64, (s32)D_800A6A70,
    (s32)D_800A6A7C,
};
s32 D_800A6AAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ADC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B0C[] = {
    0, (s32)D_800A6AAC, (s32)D_800A6AB8, (s32)D_800A6AC4,
    (s32)D_800A6AD0, (s32)D_800A6ADC, (s32)D_800A6AE8, (s32)D_800A6AF4,
    (s32)D_800A6B00,
};
s32 D_800A6B30[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B3C[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B48[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B54[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B60[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B6C[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B78[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B84[] = {
    159, 11, 0x60080000,
};
s32 D_800A6B90[] = {
    5, (s32)D_800A6B30, (s32)D_800A6B3C, (s32)D_800A6B48,
    (s32)D_800A6B54, (s32)D_800A6B60, (s32)D_800A6B6C, (s32)D_800A6B78,
    (s32)D_800A6B84,
};
s32 D_800A6BB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C14[] = {
    0, (s32)D_800A6BB4, (s32)D_800A6BC0, (s32)D_800A6BCC,
    (s32)D_800A6BD8, (s32)D_800A6BE4, (s32)D_800A6BF0, (s32)D_800A6BFC,
    (s32)D_800A6C08,
};
s32 D_800A6C38[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C44[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C98[] = {
    0, (s32)D_800A6C38, (s32)D_800A6C44, (s32)D_800A6C50,
    (s32)D_800A6C5C, (s32)D_800A6C68, (s32)D_800A6C74, (s32)D_800A6C80,
    (s32)D_800A6C8C,
};
s32 D_800A6CBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D04[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D1C[] = {
    0, (s32)D_800A6CBC, (s32)D_800A6CC8, (s32)D_800A6CD4,
    (s32)D_800A6CE0, (s32)D_800A6CEC, (s32)D_800A6CF8, (s32)D_800A6D04,
    (s32)D_800A6D10,
};
s32 D_800A6D40[] = {
    63, 11, 0x60080000,
};
s32 D_800A6D4C[] = {
    63, 11, 0x60080000,
};
s32 D_800A6D58[] = {
    63, 11, 0x60080000,
};
s32 D_800A6D64[] = {
    104, 11, 0x60080000,
};
s32 D_800A6D70[] = {
    104, 11, 0x60080000,
};
s32 D_800A6D7C[] = {
    104, 11, 0x60080000,
};
s32 D_800A6D88[] = {
    104, 11, 0x60080000,
};
s32 D_800A6D94[] = {
    104, 11, 0x60080000,
};
s32 D_800A6DA0[] = {
    4, (s32)D_800A6D40, (s32)D_800A6D4C, (s32)D_800A6D58,
    (s32)D_800A6D64, (s32)D_800A6D70, (s32)D_800A6D7C, (s32)D_800A6D88,
    (s32)D_800A6D94,
};
s32 D_800A6DC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E24[] = {
    0, (s32)D_800A6DC4, (s32)D_800A6DD0, (s32)D_800A6DDC,
    (s32)D_800A6DE8, (s32)D_800A6DF4, (s32)D_800A6E00, (s32)D_800A6E0C,
    (s32)D_800A6E18,
};
s32 D_800A6E48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EA8[] = {
    0, (s32)D_800A6E48, (s32)D_800A6E54, (s32)D_800A6E60,
    (s32)D_800A6E6C, (s32)D_800A6E78, (s32)D_800A6E84, (s32)D_800A6E90,
    (s32)D_800A6E9C,
};
s32 D_800A6ECC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ED8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F2C[] = {
    0, (s32)D_800A6ECC, (s32)D_800A6ED8, (s32)D_800A6EE4,
    (s32)D_800A6EF0, (s32)D_800A6EFC, (s32)D_800A6F08, (s32)D_800A6F14,
    (s32)D_800A6F20,
};
s32 D_800A6F50[] = {
    399, 2, 0, (s32)D_800A6770,
    (s32)D_800A67F4, (s32)D_800A6878, (s32)D_800A68FC, 402,
    3, 0, (s32)D_800A6980, (s32)D_800A6A04,
    (s32)D_800A6A88, (s32)D_800A6B0C, 407, 4,
    0, (s32)D_800A6B90, (s32)D_800A6C14, (s32)D_800A6C98,
    (s32)D_800A6D1C, 411, 5, 0,
    (s32)D_800A6DA0, (s32)D_800A6E24, (s32)D_800A6EA8, (s32)D_800A6F2C,
};
