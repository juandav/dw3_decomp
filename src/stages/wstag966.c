#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A6558[])(void);
extern StagePoints *D_800A61F0[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A61F0, GAME.unk44, GAME.unk46);
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
    D_800A6558[0]();
    return task;
}

extern s32 D_800A6298[];
extern s32 D_800A6510[];
extern s32 D_800A620C[];
extern s32 D_800A6290[];
extern CVECTOR D_800A5DE0;
extern s32 D_800A6D9C[];
void func_800A5FB4(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x6F0;
    D_800990B4.unkC = 0x93B0004;
    D_800990B4.unk10 = D_800A6298;
    D_800990B4.unk14 = D_800A6510;
    D_800990B4.unk1C = 0x93A;
    D_800990B4.unk2C = (Vec2){0x13300, 0x13B00};
    D_800990B4.unk28 = D_800A620C;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A6290;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A6D9C, GAME.unk44);
    D_8009A70C.setFile(0, 0x93B0006);
    D_8009A70C.setFile(7, 0x93B0007);
    D_8009A70C.setFile(4, 0x93B0005);
    D_8009A70C.unk50(0);
}

void func_800A5FB4();
extern StagePoint D_800A6100;
extern StagePoint D_800A6110;
extern StagePoint D_800A6128;
extern StagePoint D_800A6138;
extern StagePoint D_800A6150;
extern StagePoint D_800A6160;
extern StagePoint D_800A6178;
extern StagePoint D_800A6188;
extern StagePoint D_800A61A0;
extern StagePoint D_800A61B0;
extern StagePoint D_800A61C8;
extern StagePoint D_800A61D8;
extern StagePoints D_800A6120;
extern StagePoints D_800A6148;
extern StagePoints D_800A6170;
extern StagePoints D_800A6198;
extern StagePoints D_800A61C0;
extern StagePoints D_800A61E8;
extern s32 D_800A627C[];
extern s32 D_800A655C[];
extern s32 D_800A6568[];
extern s32 D_800A6574[];
extern s32 D_800A6580[];
extern s32 D_800A658C[];
extern s32 D_800A6598[];
extern s32 D_800A65A4[];
extern s32 D_800A65B0[];
extern s32 D_800A65E0[];
extern s32 D_800A65EC[];
extern s32 D_800A65F8[];
extern s32 D_800A6604[];
extern s32 D_800A6610[];
extern s32 D_800A661C[];
extern s32 D_800A6628[];
extern s32 D_800A6634[];
extern s32 D_800A6664[];
extern s32 D_800A6670[];
extern s32 D_800A667C[];
extern s32 D_800A6688[];
extern s32 D_800A6694[];
extern s32 D_800A66A0[];
extern s32 D_800A66AC[];
extern s32 D_800A66B8[];
extern s32 D_800A66E8[];
extern s32 D_800A66F4[];
extern s32 D_800A6700[];
extern s32 D_800A670C[];
extern s32 D_800A6718[];
extern s32 D_800A6724[];
extern s32 D_800A6730[];
extern s32 D_800A673C[];
extern s32 D_800A676C[];
extern s32 D_800A6778[];
extern s32 D_800A6784[];
extern s32 D_800A6790[];
extern s32 D_800A679C[];
extern s32 D_800A67A8[];
extern s32 D_800A67B4[];
extern s32 D_800A67C0[];
extern s32 D_800A67F0[];
extern s32 D_800A67FC[];
extern s32 D_800A6808[];
extern s32 D_800A6814[];
extern s32 D_800A6820[];
extern s32 D_800A682C[];
extern s32 D_800A6838[];
extern s32 D_800A6844[];
extern s32 D_800A6874[];
extern s32 D_800A6880[];
extern s32 D_800A688C[];
extern s32 D_800A6898[];
extern s32 D_800A68A4[];
extern s32 D_800A68B0[];
extern s32 D_800A68BC[];
extern s32 D_800A68C8[];
extern s32 D_800A68F8[];
extern s32 D_800A6904[];
extern s32 D_800A6910[];
extern s32 D_800A691C[];
extern s32 D_800A6928[];
extern s32 D_800A6934[];
extern s32 D_800A6940[];
extern s32 D_800A694C[];
extern s32 D_800A697C[];
extern s32 D_800A6988[];
extern s32 D_800A6994[];
extern s32 D_800A69A0[];
extern s32 D_800A69AC[];
extern s32 D_800A69B8[];
extern s32 D_800A69C4[];
extern s32 D_800A69D0[];
extern s32 D_800A6A00[];
extern s32 D_800A6A0C[];
extern s32 D_800A6A18[];
extern s32 D_800A6A24[];
extern s32 D_800A6A30[];
extern s32 D_800A6A3C[];
extern s32 D_800A6A48[];
extern s32 D_800A6A54[];
extern s32 D_800A6A84[];
extern s32 D_800A6A90[];
extern s32 D_800A6A9C[];
extern s32 D_800A6AA8[];
extern s32 D_800A6AB4[];
extern s32 D_800A6AC0[];
extern s32 D_800A6ACC[];
extern s32 D_800A6AD8[];
extern s32 D_800A6B08[];
extern s32 D_800A6B14[];
extern s32 D_800A6B20[];
extern s32 D_800A6B2C[];
extern s32 D_800A6B38[];
extern s32 D_800A6B44[];
extern s32 D_800A6B50[];
extern s32 D_800A6B5C[];
extern s32 D_800A6B8C[];
extern s32 D_800A6B98[];
extern s32 D_800A6BA4[];
extern s32 D_800A6BB0[];
extern s32 D_800A6BBC[];
extern s32 D_800A6BC8[];
extern s32 D_800A6BD4[];
extern s32 D_800A6BE0[];
extern s32 D_800A6C10[];
extern s32 D_800A6C1C[];
extern s32 D_800A6C28[];
extern s32 D_800A6C34[];
extern s32 D_800A6C40[];
extern s32 D_800A6C4C[];
extern s32 D_800A6C58[];
extern s32 D_800A6C64[];
extern s32 D_800A6C94[];
extern s32 D_800A6CA0[];
extern s32 D_800A6CAC[];
extern s32 D_800A6CB8[];
extern s32 D_800A6CC4[];
extern s32 D_800A6CD0[];
extern s32 D_800A6CDC[];
extern s32 D_800A6CE8[];
extern s32 D_800A6D18[];
extern s32 D_800A6D24[];
extern s32 D_800A6D30[];
extern s32 D_800A6D3C[];
extern s32 D_800A6D48[];
extern s32 D_800A6D54[];
extern s32 D_800A6D60[];
extern s32 D_800A6D6C[];
extern s32 D_800A65BC[];
extern s32 D_800A6640[];
extern s32 D_800A66C4[];
extern s32 D_800A6748[];
extern s32 D_800A67CC[];
extern s32 D_800A6850[];
extern s32 D_800A68D4[];
extern s32 D_800A6958[];
extern s32 D_800A69DC[];
extern s32 D_800A6A60[];
extern s32 D_800A6AE4[];
extern s32 D_800A6B68[];
extern s32 D_800A6BEC[];
extern s32 D_800A6C70[];
extern s32 D_800A6CF4[];
extern s32 D_800A6D78[];

StagePoint D_800A6100 = { 0x2E4, 2, 1, 0x340, 160, 1, NULL };
StagePoint D_800A6110 = { 0x2E0, 2, 1, 176, 0x178, 5, &D_800A6100 };
StagePoints D_800A6120 = { 2, 1, &D_800A6110 };
StagePoint D_800A6128 = { 0x2E4, 2, 2, 0x340, 160, 1, NULL };
StagePoint D_800A6138 = { 0x2E4, 2, 1, 192, 0x180, 5, &D_800A6128 };
StagePoints D_800A6148 = { 2, 2, &D_800A6138 };
StagePoint D_800A6150 = { 0x2E4, 2, 4, 0x340, 160, 1, NULL };
StagePoint D_800A6160 = { 0x2E4, 2, 3, 192, 0x180, 5, &D_800A6150 };
StagePoints D_800A6170 = { 2, 3, &D_800A6160 };
StagePoint D_800A6178 = { 0x2E7, 3, 1, 0x250, 232, 1, NULL };
StagePoint D_800A6188 = { 0x2E5, 3, 1, 224, 0x120, 5, &D_800A6178 };
StagePoints D_800A6198 = { 3, 1, &D_800A6188 };
StagePoint D_800A61A0 = { 0x2E4, 4, 1, 0x340, 160, 1, NULL };
StagePoint D_800A61B0 = { 0x2E3, 4, 1, 160, 0x180, 5, &D_800A61A0 };
StagePoints D_800A61C0 = { 4, 1, &D_800A61B0 };
StagePoint D_800A61C8 = { 0x2E4, 5, 2, 0x340, 160, 1, NULL };
StagePoint D_800A61D8 = { 0x2E4, 5, 1, 192, 0x180, 5, &D_800A61C8 };
StagePoints D_800A61E8 = { 5, 1, &D_800A61D8 };
StagePoints *D_800A61F0[] = {
    &D_800A6120, &D_800A6148, &D_800A6170, &D_800A6198,
    &D_800A61C0, &D_800A61E8, NULL,
};
s32 D_800A620C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1BC0170, 0xBC00C0, 0x1FF0150,
};
s32 D_800A627C[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A6290[] = {
    (s32)D_800A627C, 0,
};
s32 D_800A6298[] = {
    0x28F0001, 0x4B370137, 0x9B000A, 230,
    0x10000, 0x137028F, 0xA4B37, 0x10501B8,
    0, 0x28F0001, 0x4B370137, 0x31D000A,
    447, 0x10000, 0x137028F, 0xA4B37,
    0x1CF0467, 0, 0x2B60001, 0x624C014C,
    0x138000A, 203, 0x10000, 0x14C02B6,
    0xA624C, 0x1560291, 0, 0x2B60001,
    0x624C014C, 0x394000A, 467, 0x10000,
    0x137068F, 0xA4B37, 0x1210300, 0,
    0x6680001, 0x36340134, 0xD7000A, 158,
    0x10000, 0x1340668, 0xA3634, 0x105024F,
    0, 0x6680001, 0x36340134, 0x3D7000A,
    460, 0x10000, 1104, 0,
    0x10100C0, 340, 0x4650001, 1,
    0xA00000, 0x14E00F1, 0x10000, 0x2045E,
    0, 0xED0090, 324, 0x4910001,
    3, 0x1700000, 0x13200B8, 0x10000,
    0x40477, 0, 0xCC0150, 322,
    0x4890001, 5, 0x1300000, 0x15B00DA,
    0x10000, 0x60482, 0, 0xEE0110,
    354, 0x45E0001, 7, 0x1D00000,
    0x1700116, 0x10000, 0x80466, 0,
    0x11B01B0, 375, 0x4520001, 9,
    0x19E0000, 0x17C012A, 0x10000, 0xA0451,
    0, 0x13C0220, 390, 0x4600001,
    11, 0x2000000, 0x1950140, 0x10000,
    0xC0452, 0, 0x15001EE, 415,
    0x4930001, 13, 0x2D00000, 0x1B30137,
    0x10000, 0xE0479, 0, 0x14B02B0,
    451, 0x48B0001, 15, 0x2900000,
    0x1DC0159, 0x10000, 0x100489, 0,
    0x1680270, 483, 0x45D0001, 17,
    0x2F00000, 0x1FA01A5, 0x10000, 0x120467,
    0, 0x1A802D0, 515, 0x4500001,
    19, 0x2BE0000, 0x20F01B9, 0x10000,
    0x140452, 0, 0x2090450, 606,
    0x4650001, 21, 0x4300000, 0x25601F9,
    0x10000, 0x16045D, 0, 0x1F50421,
    587, 0, 0, 0,
    0, 0,
};
s32 D_800A6510[] = {
    65535, 65535, 0x2E60001, 0x2480450,
    5, 0, 65535, 65535,
    0x2E60001, 0x15000A0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6558[])(void) = {
    func_800A5FB4,
};
s32 D_800A655C[] = {
    62, 11, 0x60080000,
};
s32 D_800A6568[] = {
    62, 11, 0x60080000,
};
s32 D_800A6574[] = {
    62, 11, 0x60080000,
};
s32 D_800A6580[] = {
    62, 11, 0x60080000,
};
s32 D_800A658C[] = {
    106, 11, 0x60080000,
};
s32 D_800A6598[] = {
    106, 11, 0x60080000,
};
s32 D_800A65A4[] = {
    106, 11, 0x60080000,
};
s32 D_800A65B0[] = {
    106, 11, 0x60080000,
};
s32 D_800A65BC[] = {
    3, (s32)D_800A655C, (s32)D_800A6568, (s32)D_800A6574,
    (s32)D_800A6580, (s32)D_800A658C, (s32)D_800A6598, (s32)D_800A65A4,
    (s32)D_800A65B0,
};
s32 D_800A65E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6604[] = {
    0, 0, 0x60040000,
};
s32 D_800A6610[] = {
    0, 0, 0x60040000,
};
s32 D_800A661C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6628[] = {
    0, 0, 0x60040000,
};
s32 D_800A6634[] = {
    0, 0, 0x60040000,
};
s32 D_800A6640[] = {
    0, (s32)D_800A65E0, (s32)D_800A65EC, (s32)D_800A65F8,
    (s32)D_800A6604, (s32)D_800A6610, (s32)D_800A661C, (s32)D_800A6628,
    (s32)D_800A6634,
};
s32 D_800A6664[] = {
    0, 0, 0x60040000,
};
s32 D_800A6670[] = {
    0, 0, 0x60040000,
};
s32 D_800A667C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6688[] = {
    0, 0, 0x60040000,
};
s32 D_800A6694[] = {
    0, 0, 0x60040000,
};
s32 D_800A66A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66C4[] = {
    0, (s32)D_800A6664, (s32)D_800A6670, (s32)D_800A667C,
    (s32)D_800A6688, (s32)D_800A6694, (s32)D_800A66A0, (s32)D_800A66AC,
    (s32)D_800A66B8,
};
s32 D_800A66E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6700[] = {
    0, 0, 0x60040000,
};
s32 D_800A670C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6718[] = {
    0, 0, 0x60040000,
};
s32 D_800A6724[] = {
    0, 0, 0x60040000,
};
s32 D_800A6730[] = {
    0, 0, 0x60040000,
};
s32 D_800A673C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6748[] = {
    0, (s32)D_800A66E8, (s32)D_800A66F4, (s32)D_800A6700,
    (s32)D_800A670C, (s32)D_800A6718, (s32)D_800A6724, (s32)D_800A6730,
    (s32)D_800A673C,
};
s32 D_800A676C[] = {
    105, 11, 0x60080000,
};
s32 D_800A6778[] = {
    105, 11, 0x60080000,
};
s32 D_800A6784[] = {
    105, 11, 0x60080000,
};
s32 D_800A6790[] = {
    105, 11, 0x60080000,
};
s32 D_800A679C[] = {
    105, 11, 0x60080000,
};
s32 D_800A67A8[] = {
    105, 11, 0x60080000,
};
s32 D_800A67B4[] = {
    105, 11, 0x60080000,
};
s32 D_800A67C0[] = {
    105, 11, 0x60080000,
};
s32 D_800A67CC[] = {
    5, (s32)D_800A676C, (s32)D_800A6778, (s32)D_800A6784,
    (s32)D_800A6790, (s32)D_800A679C, (s32)D_800A67A8, (s32)D_800A67B4,
    (s32)D_800A67C0,
};
s32 D_800A67F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6808[] = {
    0, 0, 0x60040000,
};
s32 D_800A6814[] = {
    0, 0, 0x60040000,
};
s32 D_800A6820[] = {
    0, 0, 0x60040000,
};
s32 D_800A682C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6838[] = {
    0, 0, 0x60040000,
};
s32 D_800A6844[] = {
    0, 0, 0x60040000,
};
s32 D_800A6850[] = {
    0, (s32)D_800A67F0, (s32)D_800A67FC, (s32)D_800A6808,
    (s32)D_800A6814, (s32)D_800A6820, (s32)D_800A682C, (s32)D_800A6838,
    (s32)D_800A6844,
};
s32 D_800A6874[] = {
    0, 0, 0x60040000,
};
s32 D_800A6880[] = {
    0, 0, 0x60040000,
};
s32 D_800A688C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6898[] = {
    0, 0, 0x60040000,
};
s32 D_800A68A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68D4[] = {
    0, (s32)D_800A6874, (s32)D_800A6880, (s32)D_800A688C,
    (s32)D_800A6898, (s32)D_800A68A4, (s32)D_800A68B0, (s32)D_800A68BC,
    (s32)D_800A68C8,
};
s32 D_800A68F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6904[] = {
    0, 0, 0x60040000,
};
s32 D_800A6910[] = {
    0, 0, 0x60040000,
};
s32 D_800A691C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6928[] = {
    0, 0, 0x60040000,
};
s32 D_800A6934[] = {
    0, 0, 0x60040000,
};
s32 D_800A6940[] = {
    0, 0, 0x60040000,
};
s32 D_800A694C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6958[] = {
    0, (s32)D_800A68F8, (s32)D_800A6904, (s32)D_800A6910,
    (s32)D_800A691C, (s32)D_800A6928, (s32)D_800A6934, (s32)D_800A6940,
    (s32)D_800A694C,
};
s32 D_800A697C[] = {
    61, 11, 0x60080000,
};
s32 D_800A6988[] = {
    61, 11, 0x60080000,
};
s32 D_800A6994[] = {
    159, 11, 0x60080000,
};
s32 D_800A69A0[] = {
    159, 11, 0x60080000,
};
s32 D_800A69AC[] = {
    159, 11, 0x60080000,
};
s32 D_800A69B8[] = {
    159, 11, 0x60080000,
};
s32 D_800A69C4[] = {
    159, 11, 0x60080000,
};
s32 D_800A69D0[] = {
    159, 11, 0x60080000,
};
s32 D_800A69DC[] = {
    5, (s32)D_800A697C, (s32)D_800A6988, (s32)D_800A6994,
    (s32)D_800A69A0, (s32)D_800A69AC, (s32)D_800A69B8, (s32)D_800A69C4,
    (s32)D_800A69D0,
};
s32 D_800A6A00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A24[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A30[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A60[] = {
    0, (s32)D_800A6A00, (s32)D_800A6A0C, (s32)D_800A6A18,
    (s32)D_800A6A24, (s32)D_800A6A30, (s32)D_800A6A3C, (s32)D_800A6A48,
    (s32)D_800A6A54,
};
s32 D_800A6A84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ACC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AE4[] = {
    0, (s32)D_800A6A84, (s32)D_800A6A90, (s32)D_800A6A9C,
    (s32)D_800A6AA8, (s32)D_800A6AB4, (s32)D_800A6AC0, (s32)D_800A6ACC,
    (s32)D_800A6AD8,
};
s32 D_800A6B08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B38[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B44[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B68[] = {
    0, (s32)D_800A6B08, (s32)D_800A6B14, (s32)D_800A6B20,
    (s32)D_800A6B2C, (s32)D_800A6B38, (s32)D_800A6B44, (s32)D_800A6B50,
    (s32)D_800A6B5C,
};
s32 D_800A6B8C[] = {
    185, 11, 0x60080000,
};
s32 D_800A6B98[] = {
    185, 11, 0x60080000,
};
s32 D_800A6BA4[] = {
    185, 11, 0x60080000,
};
s32 D_800A6BB0[] = {
    185, 11, 0x60080000,
};
s32 D_800A6BBC[] = {
    185, 11, 0x60080000,
};
s32 D_800A6BC8[] = {
    178, 11, 0x60080000,
};
s32 D_800A6BD4[] = {
    178, 11, 0x60080000,
};
s32 D_800A6BE0[] = {
    178, 11, 0x60080000,
};
s32 D_800A6BEC[] = {
    4, (s32)D_800A6B8C, (s32)D_800A6B98, (s32)D_800A6BA4,
    (s32)D_800A6BB0, (s32)D_800A6BBC, (s32)D_800A6BC8, (s32)D_800A6BD4,
    (s32)D_800A6BE0,
};
s32 D_800A6C10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C34[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C70[] = {
    0, (s32)D_800A6C10, (s32)D_800A6C1C, (s32)D_800A6C28,
    (s32)D_800A6C34, (s32)D_800A6C40, (s32)D_800A6C4C, (s32)D_800A6C58,
    (s32)D_800A6C64,
};
s32 D_800A6C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CF4[] = {
    0, (s32)D_800A6C94, (s32)D_800A6CA0, (s32)D_800A6CAC,
    (s32)D_800A6CB8, (s32)D_800A6CC4, (s32)D_800A6CD0, (s32)D_800A6CDC,
    (s32)D_800A6CE8,
};
s32 D_800A6D18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D24[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D30[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D78[] = {
    0, (s32)D_800A6D18, (s32)D_800A6D24, (s32)D_800A6D30,
    (s32)D_800A6D3C, (s32)D_800A6D48, (s32)D_800A6D54, (s32)D_800A6D60,
    (s32)D_800A6D6C,
};
s32 D_800A6D9C[] = {
    400, 2, 0, (s32)D_800A65BC,
    (s32)D_800A6640, (s32)D_800A66C4, (s32)D_800A6748, 404,
    3, 0, (s32)D_800A67CC, (s32)D_800A6850,
    (s32)D_800A68D4, (s32)D_800A6958, 408, 4,
    0, (s32)D_800A69DC, (s32)D_800A6A60, (s32)D_800A6AE4,
    (s32)D_800A6B68, 412, 5, 0,
    (s32)D_800A6BEC, (s32)D_800A6C70, (s32)D_800A6CF4, (s32)D_800A6D78,
};
