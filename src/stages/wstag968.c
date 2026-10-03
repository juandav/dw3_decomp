#include "common.h"
#include "stage.h"
void func_800A5EE0();
extern void (*D_800A633C[])(void);
extern StagePoints *D_800A61A0[];

void func_800A5DE0(StageSlot *slots, StagePoints **list, s32 id0, s32 id1) {
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

void func_800A5EE0(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A5DE0(D_800990B4.unk14, D_800A61A0, GAME.unk44, GAME.unk46);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5F54(void *owner) {
    StageTask *task = createTask(func_800A5EE0, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A633C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag968", func_800A5FB0);

void func_800A5FB0();
extern StagePoint D_800A60D8;
extern StagePoint D_800A60E8;
extern StagePoint D_800A6100;
extern StagePoint D_800A6110;
extern StagePoint D_800A6128;
extern StagePoint D_800A6138;
extern StagePoint D_800A6150;
extern StagePoint D_800A6160;
extern StagePoint D_800A6178;
extern StagePoint D_800A6188;
extern StagePoints D_800A60F8;
extern StagePoints D_800A6120;
extern StagePoints D_800A6148;
extern StagePoints D_800A6170;
extern StagePoints D_800A6198;
extern s32 D_800A6248[];
extern s32 D_800A6254[];
extern s32 D_800A6260[];
extern s32 D_800A626C[];
extern s32 D_800A6280[];
extern s32 D_800A6294[];
extern s32 D_800A62A8[];
extern s32 D_800A6340[];
extern s32 D_800A634C[];
extern s32 D_800A6358[];
extern s32 D_800A6364[];
extern s32 D_800A6370[];
extern s32 D_800A637C[];
extern s32 D_800A6388[];
extern s32 D_800A6394[];
extern s32 D_800A63C4[];
extern s32 D_800A63D0[];
extern s32 D_800A63DC[];
extern s32 D_800A63E8[];
extern s32 D_800A63F4[];
extern s32 D_800A6400[];
extern s32 D_800A640C[];
extern s32 D_800A6418[];
extern s32 D_800A6448[];
extern s32 D_800A6454[];
extern s32 D_800A6460[];
extern s32 D_800A646C[];
extern s32 D_800A6478[];
extern s32 D_800A6484[];
extern s32 D_800A6490[];
extern s32 D_800A649C[];
extern s32 D_800A64CC[];
extern s32 D_800A64D8[];
extern s32 D_800A64E4[];
extern s32 D_800A64F0[];
extern s32 D_800A64FC[];
extern s32 D_800A6508[];
extern s32 D_800A6514[];
extern s32 D_800A6520[];
extern s32 D_800A6550[];
extern s32 D_800A655C[];
extern s32 D_800A6568[];
extern s32 D_800A6574[];
extern s32 D_800A6580[];
extern s32 D_800A658C[];
extern s32 D_800A6598[];
extern s32 D_800A65A4[];
extern s32 D_800A65D4[];
extern s32 D_800A65E0[];
extern s32 D_800A65EC[];
extern s32 D_800A65F8[];
extern s32 D_800A6604[];
extern s32 D_800A6610[];
extern s32 D_800A661C[];
extern s32 D_800A6628[];
extern s32 D_800A6658[];
extern s32 D_800A6664[];
extern s32 D_800A6670[];
extern s32 D_800A667C[];
extern s32 D_800A6688[];
extern s32 D_800A6694[];
extern s32 D_800A66A0[];
extern s32 D_800A66AC[];
extern s32 D_800A66DC[];
extern s32 D_800A66E8[];
extern s32 D_800A66F4[];
extern s32 D_800A6700[];
extern s32 D_800A670C[];
extern s32 D_800A6718[];
extern s32 D_800A6724[];
extern s32 D_800A6730[];
extern s32 D_800A6760[];
extern s32 D_800A676C[];
extern s32 D_800A6778[];
extern s32 D_800A6784[];
extern s32 D_800A6790[];
extern s32 D_800A679C[];
extern s32 D_800A67A8[];
extern s32 D_800A67B4[];
extern s32 D_800A67E4[];
extern s32 D_800A67F0[];
extern s32 D_800A67FC[];
extern s32 D_800A6808[];
extern s32 D_800A6814[];
extern s32 D_800A6820[];
extern s32 D_800A682C[];
extern s32 D_800A6838[];
extern s32 D_800A6868[];
extern s32 D_800A6874[];
extern s32 D_800A6880[];
extern s32 D_800A688C[];
extern s32 D_800A6898[];
extern s32 D_800A68A4[];
extern s32 D_800A68B0[];
extern s32 D_800A68BC[];
extern s32 D_800A68EC[];
extern s32 D_800A68F8[];
extern s32 D_800A6904[];
extern s32 D_800A6910[];
extern s32 D_800A691C[];
extern s32 D_800A6928[];
extern s32 D_800A6934[];
extern s32 D_800A6940[];
extern s32 D_800A6970[];
extern s32 D_800A697C[];
extern s32 D_800A6988[];
extern s32 D_800A6994[];
extern s32 D_800A69A0[];
extern s32 D_800A69AC[];
extern s32 D_800A69B8[];
extern s32 D_800A69C4[];
extern s32 D_800A69F4[];
extern s32 D_800A6A00[];
extern s32 D_800A6A0C[];
extern s32 D_800A6A18[];
extern s32 D_800A6A24[];
extern s32 D_800A6A30[];
extern s32 D_800A6A3C[];
extern s32 D_800A6A48[];
extern s32 D_800A6A78[];
extern s32 D_800A6A84[];
extern s32 D_800A6A90[];
extern s32 D_800A6A9C[];
extern s32 D_800A6AA8[];
extern s32 D_800A6AB4[];
extern s32 D_800A6AC0[];
extern s32 D_800A6ACC[];
extern s32 D_800A6AFC[];
extern s32 D_800A6B08[];
extern s32 D_800A6B14[];
extern s32 D_800A6B20[];
extern s32 D_800A6B2C[];
extern s32 D_800A6B38[];
extern s32 D_800A6B44[];
extern s32 D_800A6B50[];
extern s32 D_800A63A0[];
extern s32 D_800A6424[];
extern s32 D_800A64A8[];
extern s32 D_800A652C[];
extern s32 D_800A65B0[];
extern s32 D_800A6634[];
extern s32 D_800A66B8[];
extern s32 D_800A673C[];
extern s32 D_800A67C0[];
extern s32 D_800A6844[];
extern s32 D_800A68C8[];
extern s32 D_800A694C[];
extern s32 D_800A69D0[];
extern s32 D_800A6A54[];
extern s32 D_800A6AD8[];
extern s32 D_800A6B5C[];

StagePoint D_800A60D8 = { 0x2EE, 1, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A60E8 = { 0x298, 0, 0, 0x1F0, 0x360, 0, &D_800A60D8 };
StagePoints D_800A60F8 = { 1, 1, &D_800A60E8 };
StagePoint D_800A6100 = { 0x2EC, 1, 8, 0x3B0, 120, 1, NULL };
StagePoint D_800A6110 = { 0x298, 0, 0, 0x560, 0x238, 0, &D_800A6100 };
StagePoints D_800A6120 = { 1, 2, &D_800A6110 };
StagePoint D_800A6128 = { 0x2EC, 3, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A6138 = { 0x28F, 0, 0, 0x398, 0x270, 0, &D_800A6128 };
StagePoints D_800A6148 = { 3, 1, &D_800A6138 };
StagePoint D_800A6150 = { 0x2EC, 4, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A6160 = { 0x28C, 0, 0, 0x290, 0x200, 0, &D_800A6150 };
StagePoints D_800A6170 = { 4, 1, &D_800A6160 };
StagePoint D_800A6178 = { 0x2ED, 5, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A6188 = { 0x28F, 0, 0, 0x450, 0x226, 0, &D_800A6178 };
StagePoints D_800A6198 = { 5, 1, &D_800A6188 };
StagePoints *D_800A61A0[] = {
    &D_800A60F8, &D_800A6120, &D_800A6148, &D_800A6170,
    &D_800A6198, NULL,
};
s32 D_800A61B8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140014C, 0x400030, 0x1FF0150,
    0x1000140, 0x100014C, 48, 0x1FF0160,
    0x1000140, 0x1000160, 128, 0x1FF0170,
};
s32 D_800A6248[] = {
    32256, 8, 65535,
};
s32 D_800A6254[] = {
    0x17E04, 9, 65535,
};
s32 D_800A6260[] = {
    0x17E02, 9, 65535,
};
s32 D_800A626C[] = {
    0, 0, 0x40146, 0,
    0,
};
s32 D_800A6280[] = {
    (s32)D_800A6248, 0, 0x50148, 0x1580170,
    1,
};
s32 D_800A6294[] = {
    (s32)D_800A6254, 0, 0x6015F, 0x1180210,
    1,
};
s32 D_800A62A8[] = {
    (s32)D_800A6260, 0, 0x6015F, 0x1380110,
    1,
};
s32 D_800A62BC[] = {
    (s32)D_800A626C, (s32)D_800A6280, (s32)D_800A6294, (s32)D_800A62A8,
    0,
};
s32 D_800A62D0[] = {
    0x4FF0001, 0x7000232, 0x2280014, 0xD50064,
    0, 0, 0, 0,
    0,
};
s32 D_800A62F4[] = {
    65535, 65535, 0x2E80001, 0xD00240,
    4, 0, 65535, 65535,
    0x2E80001, 0x16800B0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A633C[])(void) = {
    func_800A5FB0,
};
s32 D_800A6340[] = {
    38, 10, 0x60080000,
};
s32 D_800A634C[] = {
    38, 10, 0x60080000,
};
s32 D_800A6358[] = {
    38, 10, 0x60080000,
};
s32 D_800A6364[] = {
    38, 10, 0x60080000,
};
s32 D_800A6370[] = {
    38, 10, 0x60080000,
};
s32 D_800A637C[] = {
    38, 10, 0x60080000,
};
s32 D_800A6388[] = {
    38, 10, 0x60080000,
};
s32 D_800A6394[] = {
    38, 10, 0x60080000,
};
s32 D_800A63A0[] = {
    3, (s32)D_800A6340, (s32)D_800A634C, (s32)D_800A6358,
    (s32)D_800A6364, (s32)D_800A6370, (s32)D_800A637C, (s32)D_800A6388,
    (s32)D_800A6394,
};
s32 D_800A63C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6400[] = {
    0, 0, 0x60040000,
};
s32 D_800A640C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6418[] = {
    0, 0, 0x60040000,
};
s32 D_800A6424[] = {
    0, (s32)D_800A63C4, (s32)D_800A63D0, (s32)D_800A63DC,
    (s32)D_800A63E8, (s32)D_800A63F4, (s32)D_800A6400, (s32)D_800A640C,
    (s32)D_800A6418,
};
s32 D_800A6448[] = {
    0, 0, 0x60040000,
};
s32 D_800A6454[] = {
    0, 0, 0x60040000,
};
s32 D_800A6460[] = {
    0, 0, 0x60040000,
};
s32 D_800A646C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6448, (s32)D_800A6454, (s32)D_800A6460,
    (s32)D_800A646C, (s32)D_800A6478, (s32)D_800A6484, (s32)D_800A6490,
    (s32)D_800A649C,
};
s32 D_800A64CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64F0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A64CC, (s32)D_800A64D8, (s32)D_800A64E4,
    (s32)D_800A64F0, (s32)D_800A64FC, (s32)D_800A6508, (s32)D_800A6514,
    (s32)D_800A6520,
};
s32 D_800A6550[] = {
    111, 10, 0x60080000,
};
s32 D_800A655C[] = {
    111, 10, 0x60080000,
};
s32 D_800A6568[] = {
    112, 10, 0x60080000,
};
s32 D_800A6574[] = {
    112, 10, 0x60080000,
};
s32 D_800A6580[] = {
    119, 10, 0x60080000,
};
s32 D_800A658C[] = {
    119, 10, 0x60080000,
};
s32 D_800A6598[] = {
    168, 10, 0x60080000,
};
s32 D_800A65A4[] = {
    168, 10, 0x60080000,
};
s32 D_800A65B0[] = {
    3, (s32)D_800A6550, (s32)D_800A655C, (s32)D_800A6568,
    (s32)D_800A6574, (s32)D_800A6580, (s32)D_800A658C, (s32)D_800A6598,
    (s32)D_800A65A4,
};
s32 D_800A65D4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A65D4, (s32)D_800A65E0, (s32)D_800A65EC,
    (s32)D_800A65F8, (s32)D_800A6604, (s32)D_800A6610, (s32)D_800A661C,
    (s32)D_800A6628,
};
s32 D_800A6658[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6658, (s32)D_800A6664, (s32)D_800A6670,
    (s32)D_800A667C, (s32)D_800A6688, (s32)D_800A6694, (s32)D_800A66A0,
    (s32)D_800A66AC,
};
s32 D_800A66DC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A66DC, (s32)D_800A66E8, (s32)D_800A66F4,
    (s32)D_800A6700, (s32)D_800A670C, (s32)D_800A6718, (s32)D_800A6724,
    (s32)D_800A6730,
};
s32 D_800A6760[] = {
    113, 10, 0x60080000,
};
s32 D_800A676C[] = {
    113, 10, 0x60080000,
};
s32 D_800A6778[] = {
    114, 10, 0x60080000,
};
s32 D_800A6784[] = {
    114, 10, 0x60080000,
};
s32 D_800A6790[] = {
    115, 10, 0x60080000,
};
s32 D_800A679C[] = {
    115, 10, 0x60080000,
};
s32 D_800A67A8[] = {
    167, 10, 0x60080000,
};
s32 D_800A67B4[] = {
    167, 10, 0x60080000,
};
s32 D_800A67C0[] = {
    3, (s32)D_800A6760, (s32)D_800A676C, (s32)D_800A6778,
    (s32)D_800A6784, (s32)D_800A6790, (s32)D_800A679C, (s32)D_800A67A8,
    (s32)D_800A67B4,
};
s32 D_800A67E4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A67E4, (s32)D_800A67F0, (s32)D_800A67FC,
    (s32)D_800A6808, (s32)D_800A6814, (s32)D_800A6820, (s32)D_800A682C,
    (s32)D_800A6838,
};
s32 D_800A6868[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6868, (s32)D_800A6874, (s32)D_800A6880,
    (s32)D_800A688C, (s32)D_800A6898, (s32)D_800A68A4, (s32)D_800A68B0,
    (s32)D_800A68BC,
};
s32 D_800A68EC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A68EC, (s32)D_800A68F8, (s32)D_800A6904,
    (s32)D_800A6910, (s32)D_800A691C, (s32)D_800A6928, (s32)D_800A6934,
    (s32)D_800A6940,
};
s32 D_800A6970[] = {
    74, 10, 0x60080000,
};
s32 D_800A697C[] = {
    77, 10, 0x60080000,
};
s32 D_800A6988[] = {
    78, 10, 0x60080000,
};
s32 D_800A6994[] = {
    79, 10, 0x60080000,
};
s32 D_800A69A0[] = {
    80, 10, 0x60080000,
};
s32 D_800A69AC[] = {
    75, 10, 0x60080000,
};
s32 D_800A69B8[] = {
    76, 10, 0x60080000,
};
s32 D_800A69C4[] = {
    89, 10, 0x60080000,
};
s32 D_800A69D0[] = {
    3, (s32)D_800A6970, (s32)D_800A697C, (s32)D_800A6988,
    (s32)D_800A6994, (s32)D_800A69A0, (s32)D_800A69AC, (s32)D_800A69B8,
    (s32)D_800A69C4,
};
s32 D_800A69F4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A69F4, (s32)D_800A6A00, (s32)D_800A6A0C,
    (s32)D_800A6A18, (s32)D_800A6A24, (s32)D_800A6A30, (s32)D_800A6A3C,
    (s32)D_800A6A48,
};
s32 D_800A6A78[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6A78, (s32)D_800A6A84, (s32)D_800A6A90,
    (s32)D_800A6A9C, (s32)D_800A6AA8, (s32)D_800A6AB4, (s32)D_800A6AC0,
    (s32)D_800A6ACC,
};
s32 D_800A6AFC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6AFC, (s32)D_800A6B08, (s32)D_800A6B14,
    (s32)D_800A6B20, (s32)D_800A6B2C, (s32)D_800A6B38, (s32)D_800A6B44,
    (s32)D_800A6B50,
};
s32 D_800A6B80[] = {
    414, 1, 0, (s32)D_800A63A0,
    (s32)D_800A6424, (s32)D_800A64A8, (s32)D_800A652C, 425,
    3, 0, (s32)D_800A65B0, (s32)D_800A6634,
    (s32)D_800A66B8, (s32)D_800A673C, 431, 4,
    0, (s32)D_800A67C0, (s32)D_800A6844, (s32)D_800A68C8,
    (s32)D_800A694C, 437, 5, 0,
    (s32)D_800A69D0, (s32)D_800A6A54, (s32)D_800A6AD8, (s32)D_800A6B5C,
};
