#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A634C[])(void);
extern StagePoints *D_800A6138[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A6138, GAME.unk44, GAME.unk46);
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
    D_800A634C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag965", func_800A5FB4);

void func_800A5FB4();
extern StagePoint D_800A6100;
extern StagePoint D_800A6110;
extern StagePoint D_800A6120;
extern StagePoints D_800A6130;
extern s32 D_800A61B0[];
extern s32 D_800A6350[];
extern s32 D_800A635C[];
extern s32 D_800A6368[];
extern s32 D_800A6374[];
extern s32 D_800A6380[];
extern s32 D_800A638C[];
extern s32 D_800A6398[];
extern s32 D_800A63A4[];
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
extern s32 D_800A63B0[];
extern s32 D_800A6434[];
extern s32 D_800A64B8[];
extern s32 D_800A653C[];

StagePoint D_800A6100 = { 0x2E6, 3, 1, 0x450, 0x248, 1, NULL };
StagePoint D_800A6110 = { 0x2E4, 3, 1, 192, 0x180, 5, &D_800A6100 };
StagePoint D_800A6120 = { 0x296, 0, 0, 0x240, 0x200, 0, &D_800A6110 };
StagePoints D_800A6130 = { 3, 1, &D_800A6120 };
StagePoints *D_800A6138[] = {
    &D_800A6130, NULL,
};
s32 D_800A6140[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1CF0170, 0xCF00C0, 0x1FF0160,
};
s32 D_800A61B0[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A61C4[] = {
    (s32)D_800A61B0, 0,
};
s32 D_800A61CC[] = {
    0x28F0001, 0x4B370137, 0xE7000A, 159,
    0x10000, 0x137028F, 0xA4B37, 0xCB0182,
    0, 0x28F0001, 0x4B370137, 0x3AF000A,
    97, 0x10000, 0x14C02B6, 0xA624C,
    0xF1024B, 0, 0x2B60001, 0x624C014C,
    0x30F000A, 147, 0x10000, 0x23302FF,
    0x180700, 0xFFB4021C, 0, 0x2550001,
    0, 0x1800000, 299, 0x10000,
    0x10240, 0, 0x15801C0, 0,
    0x2400001, 2, 0x2800000, 339,
    0x10000, 0x30252, 0, 0x12E02C0,
    0, 0x68F0001, 0x4B370137, 0x29D000A,
    89, 0x10000, 0x14C06B6, 0xA624C,
    0x10021A, 0, 0x6680001, 0x36340134,
    0x1C0000A, 180, 0x10000, 0x1340668,
    0xA3634, 0x450350, 0, 0x4FF0001,
    0x7000232, 0x21C0018, 0x1280034, 0,
    0, 0, 0, 0,
};
s32 D_800A62EC[] = {
    65535, 65535, 0x2E50001, 0x1200240,
    4, 0, 65535, 65535,
    0x2E50001, 0xD803B0, 5, 0,
    65535, 65535, 0x2E50001, 0x12000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A634C[])(void) = {
    func_800A5FB4,
};
s32 D_800A6350[] = {
    64, 11, 0x60080000,
};
s32 D_800A635C[] = {
    64, 11, 0x60080000,
};
s32 D_800A6368[] = {
    64, 11, 0x60080000,
};
s32 D_800A6374[] = {
    64, 11, 0x60080000,
};
s32 D_800A6380[] = {
    64, 11, 0x60080000,
};
s32 D_800A638C[] = {
    64, 11, 0x60080000,
};
s32 D_800A6398[] = {
    64, 11, 0x60080000,
};
s32 D_800A63A4[] = {
    64, 11, 0x60080000,
};
s32 D_800A63B0[] = {
    3, (s32)D_800A6350, (s32)D_800A635C, (s32)D_800A6368,
    (s32)D_800A6374, (s32)D_800A6380, (s32)D_800A638C, (s32)D_800A6398,
    (s32)D_800A63A4,
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
    0, 0, 0x60040000,
};
s32 D_800A6428[] = {
    0, 0, 0x60040000,
};
s32 D_800A6434[] = {
    0, (s32)D_800A63D4, (s32)D_800A63E0, (s32)D_800A63EC,
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
    403, 3, 0, (s32)D_800A63B0,
    (s32)D_800A6434, (s32)D_800A64B8, (s32)D_800A653C,
};
