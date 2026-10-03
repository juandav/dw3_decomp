#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A6334[])(void);
extern StagePoints *D_800A6124[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A6124, GAME.unk44, GAME.unk46);
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
    D_800A6334[0]();
    return task;
}

extern s32 D_800A61B8[];
extern s32 D_800A62EC[];
extern s32 D_800A612C[];
extern s32 D_800A61B0[];
extern CVECTOR D_800A5DE0;
extern s32 D_800A6548[];
void func_800A5FB4(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x6E4;
    D_800990B4.unkC = 0x9330004;
    D_800990B4.unk10 = D_800A61B8;
    D_800990B4.unk14 = D_800A62EC;
    D_800990B4.unk1C = 0x932;
    D_800990B4.unk2C = (Vec2){0xC700, 0x16D00};
    D_800990B4.unk28 = D_800A612C;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A61B0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A6548, GAME.unk44);
    D_8009A70C.setFile(0, 0x9330006);
    D_8009A70C.setFile(7, 0x9330007);
    D_8009A70C.setFile(4, 0x9330005);
    D_8009A70C.unk50(0);
}

void func_800A5FB4();
extern StagePoint D_800A60FC;
extern StagePoint D_800A610C;
extern StagePoints D_800A611C;
extern s32 D_800A619C[];
extern s32 D_800A6338[];
extern s32 D_800A6344[];
extern s32 D_800A6350[];
extern s32 D_800A635C[];
extern s32 D_800A6368[];
extern s32 D_800A6374[];
extern s32 D_800A6380[];
extern s32 D_800A638C[];
extern s32 D_800A63BC[];
extern s32 D_800A63C8[];
extern s32 D_800A63D4[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6404[];
extern s32 D_800A6410[];
extern s32 D_800A6440[];
extern s32 D_800A644C[];
extern s32 D_800A6458[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A6488[];
extern s32 D_800A6494[];
extern s32 D_800A64C4[];
extern s32 D_800A64D0[];
extern s32 D_800A64DC[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A650C[];
extern s32 D_800A6518[];
extern s32 D_800A6398[];
extern s32 D_800A641C[];
extern s32 D_800A64A0[];
extern s32 D_800A6524[];

StagePoint D_800A60FC = { 0x2E4, 2, 4, 192, 0x180, 5, NULL };
StagePoint D_800A610C = { 0x28C, 0, 0, 0x328, 0x424, 0, &D_800A60FC };
StagePoints D_800A611C = { 2, 1, &D_800A610C };
StagePoints *D_800A6124[] = {
    &D_800A611C, NULL,
};
s32 D_800A612C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1980152, 0x980048, 0x1FF0160,
};
s32 D_800A619C[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A61B0[] = {
    (s32)D_800A619C, 0,
};
s32 D_800A61B8[] = {
    0x28F0001, 0x4B370137, 0xFE000A, 275,
    0x10000, 0x137028F, 0xA4B37, 0xF4026D,
    0, 0x28F0001, 0x4B370137, 0x354000A,
    128, 0x10000, 0x14C02B6, 0xA624C,
    0xAB0180, 0, 0x2B60001, 0x624C014C,
    0x2B1000A, 166, 0x10000, 0x23302FF,
    0x180700, 0xFFDC008C, 0, 0x2980001,
    5, 0x1B00000, 254, 0x10000,
    0x6028A, 0, 0x10C0198, 0,
    0x68F0001, 0x4B370137, 0x1DB000A, 113,
    0x10000, 0x1340668, 0xA3634, 0xCE00A9,
    0, 0x6680001, 0x36340134, 0x2EE000A,
    142, 0x10000, 0x23204FF, 0x180700,
    0x5C008C, 336, 0x4920001, 1,
    0x2300000, 0x13F00B3, 0x10000, 0x20479,
    0, 0xC60210, 335, 0x4880001,
    3, 0x1F00000, 0x15F00D8, 0x10000,
    0x40486, 0, 0xE801D0, 368,
    0, 0, 0, 0,
    0,
};
s32 D_800A62EC[] = {
    65535, 65535, 0x2E20001, 0x14800B0,
    4, 0, 65535, 65535,
    0x2E20001, 0xF80330, 5, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6334[])(void) = {
    func_800A5FB4,
};
s32 D_800A6338[] = {
    61, 11, 0x60080000,
};
s32 D_800A6344[] = {
    61, 11, 0x60080000,
};
s32 D_800A6350[] = {
    61, 11, 0x60080000,
};
s32 D_800A635C[] = {
    61, 11, 0x60080000,
};
s32 D_800A6368[] = {
    61, 11, 0x60080000,
};
s32 D_800A6374[] = {
    61, 11, 0x60080000,
};
s32 D_800A6380[] = {
    61, 11, 0x60080000,
};
s32 D_800A638C[] = {
    61, 11, 0x60080000,
};
s32 D_800A6398[] = {
    3, (s32)D_800A6338, (s32)D_800A6344, (s32)D_800A6350,
    (s32)D_800A635C, (s32)D_800A6368, (s32)D_800A6374, (s32)D_800A6380,
    (s32)D_800A638C,
};
s32 D_800A63BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6404[] = {
    0, 0, 0x60040000,
};
s32 D_800A6410[] = {
    0, 0, 0x60040000,
};
s32 D_800A641C[] = {
    0, (s32)D_800A63BC, (s32)D_800A63C8, (s32)D_800A63D4,
    (s32)D_800A63E0, (s32)D_800A63EC, (s32)D_800A63F8, (s32)D_800A6404,
    (s32)D_800A6410,
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
    0, 0, 0x60040000,
};
s32 D_800A64A0[] = {
    0, (s32)D_800A6440, (s32)D_800A644C, (s32)D_800A6458,
    (s32)D_800A6464, (s32)D_800A6470, (s32)D_800A647C, (s32)D_800A6488,
    (s32)D_800A6494,
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
    0, 0, 0x60040000,
};
s32 D_800A6524[] = {
    0, (s32)D_800A64C4, (s32)D_800A64D0, (s32)D_800A64DC,
    (s32)D_800A64E8, (s32)D_800A64F4, (s32)D_800A6500, (s32)D_800A650C,
    (s32)D_800A6518,
};
s32 D_800A6548[] = {
    398, 2, 0, (s32)D_800A6398,
    (s32)D_800A641C, (s32)D_800A64A0, (s32)D_800A6524,
};
