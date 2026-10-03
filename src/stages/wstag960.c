#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A63AC[])(void);
extern StagePoints *D_800A6170[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A6170, GAME.unk44, GAME.unk46);
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
    D_800A63AC[0]();
    return task;
}

extern s32 D_800A620C[];
extern s32 D_800A6364[];
extern s32 D_800A6180[];
extern s32 D_800A6204[];
extern CVECTOR D_800A5DE0;
extern s32 D_800A69E0[];
void func_800A5FB4(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x69F;
    D_800990B4.unkC = 0x92F0000;
    D_800990B4.unk10 = D_800A620C;
    D_800990B4.unk14 = D_800A6364;
    D_800990B4.unk1C = 0x92E;
    D_800990B4.unk2C = (Vec2){0x9D00, 0x17F00};
    D_800990B4.unk28 = D_800A6180;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A6204;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A69E0, GAME.unk44);
    D_8009A70C.setFile(0, 0x92F0002);
    D_8009A70C.setFile(7, 0x92F0003);
    D_8009A70C.setFile(4, 0x92F0001);
    D_8009A70C.unk50(0);
}

void func_800A5FB4();
extern StagePoint D_800A60F8;
extern StagePoint D_800A6108;
extern StagePoint D_800A6120;
extern StagePoint D_800A6130;
extern StagePoint D_800A6148;
extern StagePoint D_800A6158;
extern StagePoints D_800A6118;
extern StagePoints D_800A6140;
extern StagePoints D_800A6168;
extern s32 D_800A61F0[];
extern s32 D_800A63B0[];
extern s32 D_800A63BC[];
extern s32 D_800A63C8[];
extern s32 D_800A63D4[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6404[];
extern s32 D_800A6434[];
extern s32 D_800A6440[];
extern s32 D_800A644C[];
extern s32 D_800A6458[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A6488[];
extern s32 D_800A64B8[];
extern s32 D_800A64C4[];
extern s32 D_800A64D0[];
extern s32 D_800A64DC[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A650C[];
extern s32 D_800A653C[];
extern s32 D_800A6548[];
extern s32 D_800A6554[];
extern s32 D_800A6560[];
extern s32 D_800A656C[];
extern s32 D_800A6578[];
extern s32 D_800A6584[];
extern s32 D_800A6590[];
extern s32 D_800A65C0[];
extern s32 D_800A65CC[];
extern s32 D_800A65D8[];
extern s32 D_800A65E4[];
extern s32 D_800A65F0[];
extern s32 D_800A65FC[];
extern s32 D_800A6608[];
extern s32 D_800A6614[];
extern s32 D_800A6644[];
extern s32 D_800A6650[];
extern s32 D_800A665C[];
extern s32 D_800A6668[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A668C[];
extern s32 D_800A6698[];
extern s32 D_800A66C8[];
extern s32 D_800A66D4[];
extern s32 D_800A66E0[];
extern s32 D_800A66EC[];
extern s32 D_800A66F8[];
extern s32 D_800A6704[];
extern s32 D_800A6710[];
extern s32 D_800A671C[];
extern s32 D_800A674C[];
extern s32 D_800A6758[];
extern s32 D_800A6764[];
extern s32 D_800A6770[];
extern s32 D_800A677C[];
extern s32 D_800A6788[];
extern s32 D_800A6794[];
extern s32 D_800A67A0[];
extern s32 D_800A67D0[];
extern s32 D_800A67DC[];
extern s32 D_800A67E8[];
extern s32 D_800A67F4[];
extern s32 D_800A6800[];
extern s32 D_800A680C[];
extern s32 D_800A6818[];
extern s32 D_800A6824[];
extern s32 D_800A6854[];
extern s32 D_800A6860[];
extern s32 D_800A686C[];
extern s32 D_800A6878[];
extern s32 D_800A6884[];
extern s32 D_800A6890[];
extern s32 D_800A689C[];
extern s32 D_800A68A8[];
extern s32 D_800A68D8[];
extern s32 D_800A68E4[];
extern s32 D_800A68F0[];
extern s32 D_800A68FC[];
extern s32 D_800A6908[];
extern s32 D_800A6914[];
extern s32 D_800A6920[];
extern s32 D_800A692C[];
extern s32 D_800A695C[];
extern s32 D_800A6968[];
extern s32 D_800A6974[];
extern s32 D_800A6980[];
extern s32 D_800A698C[];
extern s32 D_800A6998[];
extern s32 D_800A69A4[];
extern s32 D_800A69B0[];
extern s32 D_800A6410[];
extern s32 D_800A6494[];
extern s32 D_800A6518[];
extern s32 D_800A659C[];
extern s32 D_800A6620[];
extern s32 D_800A66A4[];
extern s32 D_800A6728[];
extern s32 D_800A67AC[];
extern s32 D_800A6830[];
extern s32 D_800A68B4[];
extern s32 D_800A6938[];
extern s32 D_800A69BC[];

StagePoint D_800A60F8 = { 0x2E6, 2, 1, 0x450, 0x248, 1, NULL };
StagePoint D_800A6108 = { 0x299, 0, 0, 0x32C, 0x232, 0, &D_800A60F8 };
StagePoints D_800A6118 = { 2, 1, &D_800A6108 };
StagePoint D_800A6120 = { 0x2E4, 3, 1, 0x340, 160, 1, NULL };
StagePoint D_800A6130 = { 0x297, 0, 0, 0x210, 0x370, 0, &D_800A6120 };
StagePoints D_800A6140 = { 3, 1, &D_800A6130 };
StagePoint D_800A6148 = { 0x2E4, 5, 1, 0x340, 160, 1, NULL };
StagePoint D_800A6158 = { 0x28F, 0, 0, 112, 184, 0, &D_800A6148 };
StagePoints D_800A6168 = { 5, 1, &D_800A6158 };
StagePoints *D_800A6170[] = {
    &D_800A6118, &D_800A6140, &D_800A6168, NULL,
};
s32 D_800A6180[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x15D01B0, 0x5D01C0, 0x1FF0160,
};
s32 D_800A61F0[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A6204[] = {
    (s32)D_800A61F0, 0,
};
s32 D_800A620C[] = {
    0x28F0001, 0x4B370137, 0x15A000A, 191,
    0x10000, 0x137028F, 0xA4B37, 0x70028D,
    0, 0x2B60001, 0x624C014C, 0xB3000A,
    218, 0x10000, 0x14C02B6, 0xA624C,
    0x780233, 0, 0x2A00001, 11,
    0x1C00000, 198, 0x10000, 0xC0295,
    0, 0xD201E0, 0, 0x6680001,
    0x36340134, 0x10A000A, 189, 0x10000,
    0x23204FF, 0x180700, 0xFFF4021C, 244,
    0x4580001, 0, 0xF00000, 0x15F0111,
    0x10000, 0x10468, 0, 0x10300D0,
    345, 0x4580001, 2, 0xC40000,
    0x14C00FE, 0x10000, 0x30458, 0,
    0xB401A0, 305, 0x4930001, 4,
    0x1800000, 0x12B009D, 0x10000, 0x50479,
    0, 0x970160, 270, 0x4940001,
    6, 0x1400000, 0x1150083, 0x10000,
    0x8045C, 0, 0xB40210, 268,
    0x4630001, 9, 0x1F00000, 0x10400A4,
    0x10000, 0xA045D, 0, 0x9F01E5,
    250, 0, 0, 0,
    0, 0,
};
s32 D_800A6364[] = {
    65535, 65535, 0x2E00001, 0xD80240,
    4, 0, 65535, 65535,
    0x2E00001, 0x17800B0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A63AC[])(void) = {
    func_800A5FB4,
};
s32 D_800A63B0[] = {
    61, 11, 0x60080000,
};
s32 D_800A63BC[] = {
    61, 11, 0x60080000,
};
s32 D_800A63C8[] = {
    61, 11, 0x60080000,
};
s32 D_800A63D4[] = {
    61, 11, 0x60080000,
};
s32 D_800A63E0[] = {
    61, 11, 0x60080000,
};
s32 D_800A63EC[] = {
    61, 11, 0x60080000,
};
s32 D_800A63F8[] = {
    61, 11, 0x60080000,
};
s32 D_800A6404[] = {
    61, 11, 0x60080000,
};
s32 D_800A6410[] = {
    3, (s32)D_800A63B0, (s32)D_800A63BC, (s32)D_800A63C8,
    (s32)D_800A63D4, (s32)D_800A63E0, (s32)D_800A63EC, (s32)D_800A63F8,
    (s32)D_800A6404,
};
s32 D_800A6434[] = {
    0, 0, 0x60040000,
};
s32 D_800A6440[] = {
    0, 0, 0x60040000,
};
s32 D_800A644C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6434, (s32)D_800A6440, (s32)D_800A644C,
    (s32)D_800A6458, (s32)D_800A6464, (s32)D_800A6470, (s32)D_800A647C,
    (s32)D_800A6488,
};
s32 D_800A64B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A64B8, (s32)D_800A64C4, (s32)D_800A64D0,
    (s32)D_800A64DC, (s32)D_800A64E8, (s32)D_800A64F4, (s32)D_800A6500,
    (s32)D_800A650C,
};
s32 D_800A653C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6548[] = {
    0, 0, 0x60040000,
};
s32 D_800A6554[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A653C, (s32)D_800A6548, (s32)D_800A6554,
    (s32)D_800A6560, (s32)D_800A656C, (s32)D_800A6578, (s32)D_800A6584,
    (s32)D_800A6590,
};
s32 D_800A65C0[] = {
    64, 11, 0x60080000,
};
s32 D_800A65CC[] = {
    64, 11, 0x60080000,
};
s32 D_800A65D8[] = {
    64, 11, 0x60080000,
};
s32 D_800A65E4[] = {
    64, 11, 0x60080000,
};
s32 D_800A65F0[] = {
    64, 11, 0x60080000,
};
s32 D_800A65FC[] = {
    64, 11, 0x60080000,
};
s32 D_800A6608[] = {
    64, 11, 0x60080000,
};
s32 D_800A6614[] = {
    64, 11, 0x60080000,
};
s32 D_800A6620[] = {
    3, (s32)D_800A65C0, (s32)D_800A65CC, (s32)D_800A65D8,
    (s32)D_800A65E4, (s32)D_800A65F0, (s32)D_800A65FC, (s32)D_800A6608,
    (s32)D_800A6614,
};
s32 D_800A6644[] = {
    0, 0, 0x60040000,
};
s32 D_800A6650[] = {
    0, 0, 0x60040000,
};
s32 D_800A665C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6644, (s32)D_800A6650, (s32)D_800A665C,
    (s32)D_800A6668, (s32)D_800A6674, (s32)D_800A6680, (s32)D_800A668C,
    (s32)D_800A6698,
};
s32 D_800A66C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A66E0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A66C8, (s32)D_800A66D4, (s32)D_800A66E0,
    (s32)D_800A66EC, (s32)D_800A66F8, (s32)D_800A6704, (s32)D_800A6710,
    (s32)D_800A671C,
};
s32 D_800A674C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6758[] = {
    0, 0, 0x60040000,
};
s32 D_800A6764[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A674C, (s32)D_800A6758, (s32)D_800A6764,
    (s32)D_800A6770, (s32)D_800A677C, (s32)D_800A6788, (s32)D_800A6794,
    (s32)D_800A67A0,
};
s32 D_800A67D0[] = {
    63, 11, 0x60080000,
};
s32 D_800A67DC[] = {
    63, 11, 0x60080000,
};
s32 D_800A67E8[] = {
    63, 11, 0x60080000,
};
s32 D_800A67F4[] = {
    63, 11, 0x60080000,
};
s32 D_800A6800[] = {
    63, 11, 0x60080000,
};
s32 D_800A680C[] = {
    63, 11, 0x60080000,
};
s32 D_800A6818[] = {
    63, 11, 0x60080000,
};
s32 D_800A6824[] = {
    63, 11, 0x60080000,
};
s32 D_800A6830[] = {
    4, (s32)D_800A67D0, (s32)D_800A67DC, (s32)D_800A67E8,
    (s32)D_800A67F4, (s32)D_800A6800, (s32)D_800A680C, (s32)D_800A6818,
    (s32)D_800A6824,
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
    0, 0, 0x60040000,
};
s32 D_800A6884[] = {
    0, 0, 0x60040000,
};
s32 D_800A6890[] = {
    0, 0, 0x60040000,
};
s32 D_800A689C[] = {
    0, 0, 0x60040000,
};
s32 D_800A68A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B4[] = {
    0, (s32)D_800A6854, (s32)D_800A6860, (s32)D_800A686C,
    (s32)D_800A6878, (s32)D_800A6884, (s32)D_800A6890, (s32)D_800A689C,
    (s32)D_800A68A8,
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
    0, 0, 0x60040000,
};
s32 D_800A6908[] = {
    0, 0, 0x60040000,
};
s32 D_800A6914[] = {
    0, 0, 0x60040000,
};
s32 D_800A6920[] = {
    0, 0, 0x60040000,
};
s32 D_800A692C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6938[] = {
    0, (s32)D_800A68D8, (s32)D_800A68E4, (s32)D_800A68F0,
    (s32)D_800A68FC, (s32)D_800A6908, (s32)D_800A6914, (s32)D_800A6920,
    (s32)D_800A692C,
};
s32 D_800A695C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6968[] = {
    0, 0, 0x60040000,
};
s32 D_800A6974[] = {
    0, 0, 0x60040000,
};
s32 D_800A6980[] = {
    0, 0, 0x60040000,
};
s32 D_800A698C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6998[] = {
    0, 0, 0x60040000,
};
s32 D_800A69A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69BC[] = {
    0, (s32)D_800A695C, (s32)D_800A6968, (s32)D_800A6974,
    (s32)D_800A6980, (s32)D_800A698C, (s32)D_800A6998, (s32)D_800A69A4,
    (s32)D_800A69B0,
};
s32 D_800A69E0[] = {
    397, 2, 0, (s32)D_800A6410,
    (s32)D_800A6494, (s32)D_800A6518, (s32)D_800A659C, 401,
    3, 0, (s32)D_800A6620, (s32)D_800A66A4,
    (s32)D_800A6728, (s32)D_800A67AC, 410, 5,
    0, (s32)D_800A6830, (s32)D_800A68B4, (s32)D_800A6938,
    (s32)D_800A69BC,
};
