#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A63F0[])(void);
extern StagePoints *D_800A6144[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A6144, GAME.unk44, GAME.unk46);
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
    D_800A63F0[0]();
    return task;
}

extern s32 D_800A62D4[];
extern s32 D_800A63C0[];
extern s32 D_800A6154[];
extern s32 D_800A62C0[];
const CVECTOR D_800A5DE0 = { 0x54, 0x67, 0x96, 0x01 };
extern s32 D_800A6A24[];
void func_800A5FB4(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x6F4;
    D_800990B4.unkC = 0x93D0004;
    D_800990B4.unk10 = D_800A62D4;
    D_800990B4.unk14 = D_800A63C0;
    D_800990B4.unk1C = 0x93C;
    D_800990B4.unk2C = (Vec2){0xEC00, 0x14D00};
    D_800990B4.unk28 = D_800A6154;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A62C0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A6A24, GAME.unk44);
    D_8009A70C.setFile(0, 0x93D0006);
    D_8009A70C.setFile(7, 0x93D0007);
    D_8009A70C.setFile(4, 0x93D0005);
    D_8009A70C.unk50(0);
}

void func_800A5FB4();
extern StagePoint D_800A60FC;
extern StagePoint D_800A6114;
extern StagePoint D_800A612C;
extern StagePoints D_800A610C;
extern StagePoints D_800A6124;
extern StagePoints D_800A613C;
extern s32 D_800A61D4[];
extern s32 D_800A61E0[];
extern s32 D_800A61EC[];
extern s32 D_800A6240[];
extern s32 D_800A61F8[];
extern s32 D_800A6250[];
extern s32 D_800A6210[];
extern s32 D_800A6260[];
extern s32 D_800A6228[];
extern s32 D_800A6270[];
extern s32 D_800A6284[];
extern s32 D_800A6298[];
extern s32 D_800A62AC[];
extern s32 D_800A63F4[];
extern s32 D_800A6400[];
extern s32 D_800A640C[];
extern s32 D_800A6418[];
extern s32 D_800A6424[];
extern s32 D_800A6430[];
extern s32 D_800A643C[];
extern s32 D_800A6448[];
extern s32 D_800A6478[];
extern s32 D_800A6484[];
extern s32 D_800A6490[];
extern s32 D_800A649C[];
extern s32 D_800A64A8[];
extern s32 D_800A64B4[];
extern s32 D_800A64C0[];
extern s32 D_800A64CC[];
extern s32 D_800A64FC[];
extern s32 D_800A6508[];
extern s32 D_800A6514[];
extern s32 D_800A6520[];
extern s32 D_800A652C[];
extern s32 D_800A6538[];
extern s32 D_800A6544[];
extern s32 D_800A6550[];
extern s32 D_800A6580[];
extern s32 D_800A658C[];
extern s32 D_800A6598[];
extern s32 D_800A65A4[];
extern s32 D_800A65B0[];
extern s32 D_800A65BC[];
extern s32 D_800A65C8[];
extern s32 D_800A65D4[];
extern s32 D_800A6604[];
extern s32 D_800A6610[];
extern s32 D_800A661C[];
extern s32 D_800A6628[];
extern s32 D_800A6634[];
extern s32 D_800A6640[];
extern s32 D_800A664C[];
extern s32 D_800A6658[];
extern s32 D_800A6688[];
extern s32 D_800A6694[];
extern s32 D_800A66A0[];
extern s32 D_800A66AC[];
extern s32 D_800A66B8[];
extern s32 D_800A66C4[];
extern s32 D_800A66D0[];
extern s32 D_800A66DC[];
extern s32 D_800A670C[];
extern s32 D_800A6718[];
extern s32 D_800A6724[];
extern s32 D_800A6730[];
extern s32 D_800A673C[];
extern s32 D_800A6748[];
extern s32 D_800A6754[];
extern s32 D_800A6760[];
extern s32 D_800A6790[];
extern s32 D_800A679C[];
extern s32 D_800A67A8[];
extern s32 D_800A67B4[];
extern s32 D_800A67C0[];
extern s32 D_800A67CC[];
extern s32 D_800A67D8[];
extern s32 D_800A67E4[];
extern s32 D_800A6814[];
extern s32 D_800A6820[];
extern s32 D_800A682C[];
extern s32 D_800A6838[];
extern s32 D_800A6844[];
extern s32 D_800A6850[];
extern s32 D_800A685C[];
extern s32 D_800A6868[];
extern s32 D_800A6898[];
extern s32 D_800A68A4[];
extern s32 D_800A68B0[];
extern s32 D_800A68BC[];
extern s32 D_800A68C8[];
extern s32 D_800A68D4[];
extern s32 D_800A68E0[];
extern s32 D_800A68EC[];
extern s32 D_800A691C[];
extern s32 D_800A6928[];
extern s32 D_800A6934[];
extern s32 D_800A6940[];
extern s32 D_800A694C[];
extern s32 D_800A6958[];
extern s32 D_800A6964[];
extern s32 D_800A6970[];
extern s32 D_800A69A0[];
extern s32 D_800A69AC[];
extern s32 D_800A69B8[];
extern s32 D_800A69C4[];
extern s32 D_800A69D0[];
extern s32 D_800A69DC[];
extern s32 D_800A69E8[];
extern s32 D_800A69F4[];
extern s32 D_800A6454[];
extern s32 D_800A64D8[];
extern s32 D_800A655C[];
extern s32 D_800A65E0[];
extern s32 D_800A6664[];
extern s32 D_800A66E8[];
extern s32 D_800A676C[];
extern s32 D_800A67F0[];
extern s32 D_800A6874[];
extern s32 D_800A68F8[];
extern s32 D_800A697C[];
extern s32 D_800A6A00[];

StagePoint D_800A60FC = { 0x2E6, 3, 1, 160, 0x150, 5, NULL };
StagePoints D_800A610C = { 3, 1, &D_800A60FC };
StagePoint D_800A6114 = { 0x2E4, 4, 1, 192, 0x180, 5, NULL };
StagePoints D_800A6124 = { 4, 1, &D_800A6114 };
StagePoint D_800A612C = { 0x2E4, 5, 3, 192, 0x180, 5, NULL };
StagePoints D_800A613C = { 5, 1, &D_800A612C };
StagePoints *D_800A6144[] = {
    &D_800A610C, &D_800A6124, &D_800A613C, NULL,
};
s32 D_800A6154[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x15F016E, 0x5F00B8, 0x1FF0150,
    0x1000140, 0x1600160, 0x600080, 0x1FF0160,
};
s32 D_800A61D4[] = {
    0x1026E, 0x18496, 65535,
};
s32 D_800A61E0[] = {
    0x10272, 0x18471, 65535,
};
s32 D_800A61EC[] = {
    0x10271, 0x18463, 65535,
};
s32 D_800A61F8[] = {
    0, (s32)D_800A61D4, 6, 0,
    0, 0,
};
s32 D_800A6210[] = {
    0, (s32)D_800A61E0, 10, 0,
    0, 0,
};
s32 D_800A6228[] = {
    0, (s32)D_800A61EC, 9, 0,
    0, 0,
};
s32 D_800A6240[] = {
    0x17E02, 0x17E1E, 622, 65535,
};
s32 D_800A6250[] = {
    0x17E03, 0x17E1E, 626, 65535,
};
s32 D_800A6260[] = {
    0x17E04, 0x17E1E, 625, 65535,
};
s32 D_800A6270[] = {
    (s32)D_800A6240, (s32)D_800A61F8, 0x40021, 0x11800C0,
    1,
};
s32 D_800A6284[] = {
    (s32)D_800A6250, (s32)D_800A6210, 0x40021, 0x11800C0,
    1,
};
s32 D_800A6298[] = {
    (s32)D_800A6260, (s32)D_800A6228, 0x40021, 0x11800C0,
    1,
};
s32 D_800A62AC[] = {
    0, 0, 0x50147, 0,
    0,
};
s32 D_800A62C0[] = {
    (s32)D_800A6270, (s32)D_800A6284, (s32)D_800A6298, (s32)D_800A62AC,
    0,
};
s32 D_800A62D4[] = {
    0x28F0001, 0x4B370137, 0x168000A, 185,
    0x10000, 0x137028F, 0xA4B37, 0x78024D,
    0, 0x2B60001, 0x624C014C, 0x10C000A,
    192, 0x10000, 0x14C02B6, 0xA624C,
    0x7A0200, 0, 0x68F0001, 0x4B370137,
    0x6E000A, 120, 0x10000, 0x1340668,
    0xA3634, 0x72019C, 0, 0x44A0001,
    0, 0x1A00000, 0x12000D7, 0x10000,
    0x10461, 0, 0xC60180, 288,
    0x45F0001, 2, 0x16D0000, 0x11900BF,
    0x10000, 0x3044F, 0, 0xAD0250,
    251, 0x4630001, 4, 0x2300000,
    0xF7009D, 0x10000, 0x50460, 0,
    0x96021D, 240, 0, 0,
    0, 0, 0,
};
s32 D_800A63C0[] = {
    65535, 65535, 0x2E70001, 0xE80250,
    5, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A63F0[])(void) = {
    func_800A5FB4,
};
s32 D_800A63F4[] = {
    105, 11, 0x60080000,
};
s32 D_800A6400[] = {
    105, 11, 0x60080000,
};
s32 D_800A640C[] = {
    105, 11, 0x60080000,
};
s32 D_800A6418[] = {
    105, 11, 0x60080000,
};
s32 D_800A6424[] = {
    105, 11, 0x60080000,
};
s32 D_800A6430[] = {
    275, 11, 0x60080000,
};
s32 D_800A643C[] = {
    275, 11, 0x60080000,
};
s32 D_800A6448[] = {
    275, 11, 0x60080000,
};
s32 D_800A6454[] = {
    5, (s32)D_800A63F4, (s32)D_800A6400, (s32)D_800A640C,
    (s32)D_800A6418, (s32)D_800A6424, (s32)D_800A6430, (s32)D_800A643C,
    (s32)D_800A6448,
};
s32 D_800A6478[] = {
    0, 0, 0x60040000,
};
s32 D_800A6484[] = {
    0, 0, 0x60040000,
};
s32 D_800A6490[] = {
    0, 0, 0x60040000,
};
s32 D_800A649C[] = {
    0, 0, 0x60040000,
};
s32 D_800A64A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D8[] = {
    0, (s32)D_800A6478, (s32)D_800A6484, (s32)D_800A6490,
    (s32)D_800A649C, (s32)D_800A64A8, (s32)D_800A64B4, (s32)D_800A64C0,
    (s32)D_800A64CC,
};
s32 D_800A64FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6508[] = {
    0, 0, 0x60040000,
};
s32 D_800A6514[] = {
    0, 0, 0x60040000,
};
s32 D_800A6520[] = {
    0, 0, 0x60040000,
};
s32 D_800A652C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6538[] = {
    0, 0, 0x60040000,
};
s32 D_800A6544[] = {
    0, 0, 0x60040000,
};
s32 D_800A6550[] = {
    0, 0, 0x60040000,
};
s32 D_800A655C[] = {
    0, (s32)D_800A64FC, (s32)D_800A6508, (s32)D_800A6514,
    (s32)D_800A6520, (s32)D_800A652C, (s32)D_800A6538, (s32)D_800A6544,
    (s32)D_800A6550,
};
s32 D_800A6580[] = {
    0, 0, 0x60040000,
};
s32 D_800A658C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6598[] = {
    0, 0, 0x60040000,
};
s32 D_800A65A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65E0[] = {
    0, (s32)D_800A6580, (s32)D_800A658C, (s32)D_800A6598,
    (s32)D_800A65A4, (s32)D_800A65B0, (s32)D_800A65BC, (s32)D_800A65C8,
    (s32)D_800A65D4,
};
s32 D_800A6604[] = {
    179, 11, 0x60080000,
};
s32 D_800A6610[] = {
    179, 11, 0x60080000,
};
s32 D_800A661C[] = {
    179, 11, 0x60080000,
};
s32 D_800A6628[] = {
    179, 11, 0x60080000,
};
s32 D_800A6634[] = {
    179, 11, 0x60080000,
};
s32 D_800A6640[] = {
    274, 11, 0x60080000,
};
s32 D_800A664C[] = {
    274, 11, 0x60080000,
};
s32 D_800A6658[] = {
    274, 11, 0x60080000,
};
s32 D_800A6664[] = {
    5, (s32)D_800A6604, (s32)D_800A6610, (s32)D_800A661C,
    (s32)D_800A6628, (s32)D_800A6634, (s32)D_800A6640, (s32)D_800A664C,
    (s32)D_800A6658,
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
    0, 0, 0x60040000,
};
s32 D_800A66D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66E8[] = {
    0, (s32)D_800A6688, (s32)D_800A6694, (s32)D_800A66A0,
    (s32)D_800A66AC, (s32)D_800A66B8, (s32)D_800A66C4, (s32)D_800A66D0,
    (s32)D_800A66DC,
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
    0, 0, 0x60040000,
};
s32 D_800A6754[] = {
    0, 0, 0x60040000,
};
s32 D_800A6760[] = {
    0, 0, 0x60040000,
};
s32 D_800A676C[] = {
    0, (s32)D_800A670C, (s32)D_800A6718, (s32)D_800A6724,
    (s32)D_800A6730, (s32)D_800A673C, (s32)D_800A6748, (s32)D_800A6754,
    (s32)D_800A6760,
};
s32 D_800A6790[] = {
    0, 0, 0x60040000,
};
s32 D_800A679C[] = {
    0, 0, 0x60040000,
};
s32 D_800A67A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67F0[] = {
    0, (s32)D_800A6790, (s32)D_800A679C, (s32)D_800A67A8,
    (s32)D_800A67B4, (s32)D_800A67C0, (s32)D_800A67CC, (s32)D_800A67D8,
    (s32)D_800A67E4,
};
s32 D_800A6814[] = {
    185, 11, 0x60080000,
};
s32 D_800A6820[] = {
    185, 11, 0x60080000,
};
s32 D_800A682C[] = {
    185, 11, 0x60080000,
};
s32 D_800A6838[] = {
    185, 11, 0x60080000,
};
s32 D_800A6844[] = {
    185, 11, 0x60080000,
};
s32 D_800A6850[] = {
    277, 11, 0x60080000,
};
s32 D_800A685C[] = {
    277, 11, 0x60080000,
};
s32 D_800A6868[] = {
    277, 11, 0x60080000,
};
s32 D_800A6874[] = {
    4, (s32)D_800A6814, (s32)D_800A6820, (s32)D_800A682C,
    (s32)D_800A6838, (s32)D_800A6844, (s32)D_800A6850, (s32)D_800A685C,
    (s32)D_800A6868,
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
    0, 0, 0x60040000,
};
s32 D_800A68E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68F8[] = {
    0, (s32)D_800A6898, (s32)D_800A68A4, (s32)D_800A68B0,
    (s32)D_800A68BC, (s32)D_800A68C8, (s32)D_800A68D4, (s32)D_800A68E0,
    (s32)D_800A68EC,
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
    0, 0, 0x60040000,
};
s32 D_800A6964[] = {
    0, 0, 0x60040000,
};
s32 D_800A6970[] = {
    0, 0, 0x60040000,
};
s32 D_800A697C[] = {
    0, (s32)D_800A691C, (s32)D_800A6928, (s32)D_800A6934,
    (s32)D_800A6940, (s32)D_800A694C, (s32)D_800A6958, (s32)D_800A6964,
    (s32)D_800A6970,
};
s32 D_800A69A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A00[] = {
    0, (s32)D_800A69A0, (s32)D_800A69AC, (s32)D_800A69B8,
    (s32)D_800A69C4, (s32)D_800A69D0, (s32)D_800A69DC, (s32)D_800A69E8,
    (s32)D_800A69F4,
};
s32 D_800A6A24[] = {
    405, 3, 0, (s32)D_800A6454,
    (s32)D_800A64D8, (s32)D_800A655C, (s32)D_800A65E0, 409,
    4, 0, (s32)D_800A6664, (s32)D_800A66E8,
    (s32)D_800A676C, (s32)D_800A67F0, 413, 5,
    0, (s32)D_800A6874, (s32)D_800A68F8, (s32)D_800A697C,
    (s32)D_800A6A00,
};
