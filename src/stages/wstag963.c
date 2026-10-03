#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A63D0[])(void);
extern StagePoints *D_800A6150[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A6150, GAME.unk44, GAME.unk46);
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
    D_800A63D0[0]();
    return task;
}

extern s32 D_800A61E8[];
extern s32 D_800A6388[];
extern s32 D_800A615C[];
extern s32 D_800A61E0[];
extern CVECTOR D_800A5DE0;
extern s32 D_800A67F4[];
void func_800A5FB4(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x74A;
    D_800990B4.unkC = 0x9350004;
    D_800990B4.unk10 = D_800A61E8;
    D_800990B4.unk14 = D_800A6388;
    D_800990B4.unk1C = 0x934;
    D_800990B4.unk2C = (Vec2){0x15300, 0x13900};
    D_800990B4.unk28 = D_800A615C;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A61E0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A67F4, GAME.unk44);
    D_8009A70C.setFile(0, 0x9350006);
    D_8009A70C.setFile(7, 0x9350007);
    D_8009A70C.setFile(4, 0x9350005);
    D_8009A70C.unk50(0);
}

void func_800A5FB4();
extern StagePoint D_800A6100;
extern StagePoint D_800A6110;
extern StagePoint D_800A6128;
extern StagePoint D_800A6138;
extern StagePoints D_800A6120;
extern StagePoints D_800A6148;
extern s32 D_800A61CC[];
extern s32 D_800A63D4[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6404[];
extern s32 D_800A6410[];
extern s32 D_800A641C[];
extern s32 D_800A6428[];
extern s32 D_800A6458[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A6488[];
extern s32 D_800A6494[];
extern s32 D_800A64A0[];
extern s32 D_800A64AC[];
extern s32 D_800A64DC[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A650C[];
extern s32 D_800A6518[];
extern s32 D_800A6524[];
extern s32 D_800A6530[];
extern s32 D_800A6560[];
extern s32 D_800A656C[];
extern s32 D_800A6578[];
extern s32 D_800A6584[];
extern s32 D_800A6590[];
extern s32 D_800A659C[];
extern s32 D_800A65A8[];
extern s32 D_800A65B4[];
extern s32 D_800A65E4[];
extern s32 D_800A65F0[];
extern s32 D_800A65FC[];
extern s32 D_800A6608[];
extern s32 D_800A6614[];
extern s32 D_800A6620[];
extern s32 D_800A662C[];
extern s32 D_800A6638[];
extern s32 D_800A6668[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A668C[];
extern s32 D_800A6698[];
extern s32 D_800A66A4[];
extern s32 D_800A66B0[];
extern s32 D_800A66BC[];
extern s32 D_800A66EC[];
extern s32 D_800A66F8[];
extern s32 D_800A6704[];
extern s32 D_800A6710[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A6740[];
extern s32 D_800A6770[];
extern s32 D_800A677C[];
extern s32 D_800A6788[];
extern s32 D_800A6794[];
extern s32 D_800A67A0[];
extern s32 D_800A67AC[];
extern s32 D_800A67B8[];
extern s32 D_800A67C4[];
extern s32 D_800A6434[];
extern s32 D_800A64B8[];
extern s32 D_800A653C[];
extern s32 D_800A65C0[];
extern s32 D_800A6644[];
extern s32 D_800A66C8[];
extern s32 D_800A674C[];
extern s32 D_800A67D0[];

StagePoint D_800A6100 = { 0x2E1, 1, 1, 0x390, 0x108, 1, NULL };
StagePoint D_800A6110 = { 0x28A, 0, 0, 128, 0x1E0, 0, &D_800A6100 };
StagePoints D_800A6120 = { 1, 1, &D_800A6110 };
StagePoint D_800A6128 = { 0x2E6, 4, 1, 0x450, 0x248, 1, NULL };
StagePoint D_800A6138 = { 0x28E, 0, 0, 224, 0x208, 0, &D_800A6128 };
StagePoints D_800A6148 = { 4, 1, &D_800A6138 };
StagePoints *D_800A6150[] = {
    &D_800A6120, &D_800A6148, NULL,
};
s32 D_800A615C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1A10140, 0xA10000, 0x1FF0160,
};
s32 D_800A61CC[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A61E0[] = {
    (s32)D_800A61CC, 0,
};
s32 D_800A61E8[] = {
    0x28F0001, 0x4B370137, 0x3B4000A, 29,
    0x10000, 0x14C02B6, 0xA624C, 0xCF0137,
    0, 0x2B60001, 0x624C014C, 0x27C000A,
    93, 0x10000, 0x14C02B6, 0xA624C,
    0x1B0367, 0, 0x28B0001, 0,
    0x2D00000, 158, 0x10000, 0x102A1,
    0, 0x8802B0, 0, 0x2400001,
    10, 0x1060000, 340, 0x10000,
    0xB0240, 0, 0x14A0140, 0,
    0x2400001, 12, 0x1800000, 299,
    0x10000, 0xD0240, 0, 0x10A01C0,
    0, 0x68F0001, 0x4B370137, 0x175000A,
    118, 0x10000, 0x137068F, 0xA4B37,
    0x4201EA, 0, 0x6680001, 0x36340134,
    0x94000A, 233, 0x10000, 0x1340668,
    0xA3634, 0x102F1, 0, 0x4FF0001,
    0x7000232, 0x35C0018, 0x78FF84, 0x10000,
    0x2048B, 0, 0x760290, 250,
    0x48A0001, 3, 0x2700000, 0xEA0068,
    0x10000, 0x40479, 0, 0x590250,
    218, 0x4980001, 5, 0x2300000,
    0xCA0046, 0x10000, 0x70455, 0,
    0xF90190, 338, 0x4670001, 8,
    0x1700000, 0x14200E9, 0x10000, 0x9045E,
    0, 0xE40160, 314, 0,
    0, 0, 0, 0,
};
s32 D_800A6388[] = {
    65535, 65535, 0x2E30001, 0x700380,
    4, 0, 65535, 65535,
    0x2E30001, 0x18000A0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A63D0[])(void) = {
    func_800A5FB4,
};
s32 D_800A63D4[] = {
    62, 11, 0x60080000,
};
s32 D_800A63E0[] = {
    62, 11, 0x60080000,
};
s32 D_800A63EC[] = {
    103, 11, 0x60080000,
};
s32 D_800A63F8[] = {
    103, 11, 0x60080000,
};
s32 D_800A6404[] = {
    103, 11, 0x60080000,
};
s32 D_800A6410[] = {
    273, 11, 0x60080000,
};
s32 D_800A641C[] = {
    273, 11, 0x60080000,
};
s32 D_800A6428[] = {
    273, 11, 0x60080000,
};
s32 D_800A6434[] = {
    5, (s32)D_800A63D4, (s32)D_800A63E0, (s32)D_800A63EC,
    (s32)D_800A63F8, (s32)D_800A6404, (s32)D_800A6410, (s32)D_800A641C,
    (s32)D_800A6428,
};
s32 D_800A6458[] = {
    0, 0, 0x60040000,
};
s32 D_800A6464[] = {
    0, 0, 0x60040000,
};
s32 D_800A6470[] = {
    0, 0, 0x60040000,
};
s32 D_800A647C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6488[] = {
    0, 0, 0x60040000,
};
s32 D_800A6494[] = {
    0, 0, 0x60040000,
};
s32 D_800A64A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64B8[] = {
    0, (s32)D_800A6458, (s32)D_800A6464, (s32)D_800A6470,
    (s32)D_800A647C, (s32)D_800A6488, (s32)D_800A6494, (s32)D_800A64A0,
    (s32)D_800A64AC,
};
s32 D_800A64DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6500[] = {
    0, 0, 0x60040000,
};
s32 D_800A650C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6518[] = {
    0, 0, 0x60040000,
};
s32 D_800A6524[] = {
    0, 0, 0x60040000,
};
s32 D_800A6530[] = {
    0, 0, 0x60040000,
};
s32 D_800A653C[] = {
    0, (s32)D_800A64DC, (s32)D_800A64E8, (s32)D_800A64F4,
    (s32)D_800A6500, (s32)D_800A650C, (s32)D_800A6518, (s32)D_800A6524,
    (s32)D_800A6530,
};
s32 D_800A6560[] = {
    0, 0, 0x60040000,
};
s32 D_800A656C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6578[] = {
    0, 0, 0x60040000,
};
s32 D_800A6584[] = {
    0, 0, 0x60040000,
};
s32 D_800A6590[] = {
    0, 0, 0x60040000,
};
s32 D_800A659C[] = {
    0, 0, 0x60040000,
};
s32 D_800A65A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C0[] = {
    0, (s32)D_800A6560, (s32)D_800A656C, (s32)D_800A6578,
    (s32)D_800A6584, (s32)D_800A6590, (s32)D_800A659C, (s32)D_800A65A8,
    (s32)D_800A65B4,
};
s32 D_800A65E4[] = {
    61, 11, 0x60080000,
};
s32 D_800A65F0[] = {
    61, 11, 0x60080000,
};
s32 D_800A65FC[] = {
    61, 11, 0x60080000,
};
s32 D_800A6608[] = {
    61, 11, 0x60080000,
};
s32 D_800A6614[] = {
    61, 11, 0x60080000,
};
s32 D_800A6620[] = {
    61, 11, 0x60080000,
};
s32 D_800A662C[] = {
    159, 11, 0x60080000,
};
s32 D_800A6638[] = {
    159, 11, 0x60080000,
};
s32 D_800A6644[] = {
    5, (s32)D_800A65E4, (s32)D_800A65F0, (s32)D_800A65FC,
    (s32)D_800A6608, (s32)D_800A6614, (s32)D_800A6620, (s32)D_800A662C,
    (s32)D_800A6638,
};
s32 D_800A6668[] = {
    0, 0, 0x60040000,
};
s32 D_800A6674[] = {
    0, 0, 0x60040000,
};
s32 D_800A6680[] = {
    0, 0, 0x60040000,
};
s32 D_800A668C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6698[] = {
    0, 0, 0x60040000,
};
s32 D_800A66A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A66B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66C8[] = {
    0, (s32)D_800A6668, (s32)D_800A6674, (s32)D_800A6680,
    (s32)D_800A668C, (s32)D_800A6698, (s32)D_800A66A4, (s32)D_800A66B0,
    (s32)D_800A66BC,
};
s32 D_800A66EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6704[] = {
    0, 0, 0x60040000,
};
s32 D_800A6710[] = {
    0, 0, 0x60040000,
};
s32 D_800A671C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6728[] = {
    0, 0, 0x60040000,
};
s32 D_800A6734[] = {
    0, 0, 0x60040000,
};
s32 D_800A6740[] = {
    0, 0, 0x60040000,
};
s32 D_800A674C[] = {
    0, (s32)D_800A66EC, (s32)D_800A66F8, (s32)D_800A6704,
    (s32)D_800A6710, (s32)D_800A671C, (s32)D_800A6728, (s32)D_800A6734,
    (s32)D_800A6740,
};
s32 D_800A6770[] = {
    0, 0, 0x60040000,
};
s32 D_800A677C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6788[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6770, (s32)D_800A677C, (s32)D_800A6788,
    (s32)D_800A6794, (s32)D_800A67A0, (s32)D_800A67AC, (s32)D_800A67B8,
    (s32)D_800A67C4,
};
s32 D_800A67F4[] = {
    396, 1, 0, (s32)D_800A6434,
    (s32)D_800A64B8, (s32)D_800A653C, (s32)D_800A65C0, 406,
    4, 0, (s32)D_800A6644, (s32)D_800A66C8,
    (s32)D_800A674C, (s32)D_800A67D0,
};
