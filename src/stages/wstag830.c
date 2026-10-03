#include "common.h"
#include "stage.h"
extern void (*D_800A570C[])(void);
void func_800A4DA8();
extern StagePoints *D_800A502C[];

void func_800A4CA8(StageSlot *slots, StagePoints **list, s32 id0, s32 id1) {
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

void func_800A4DA8(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A4CA8(D_800990B4.unk14, D_800A502C, GAME.unk44, GAME.unk46);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4E1C(void *owner) {
    StageTask *task = createTask(func_800A4DA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A570C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag830", func_800A4E78);

void func_800A4E78();
extern StagePoint D_800A4FB4;
extern StagePoint D_800A4FC4;
extern StagePoint D_800A4FD4;
extern StagePoint D_800A4FEC;
extern StagePoint D_800A4FFC;
extern StagePoint D_800A500C;
extern StagePoints D_800A4FE4;
extern StagePoints D_800A501C;
extern StagePoints D_800A5024;
extern s32 D_800A503C[];
extern s32 D_800A5048[];
extern s32 D_800A5054[];
extern s32 D_800A5060[];
extern s32 D_800A506C[];
extern s32 D_800A5078[];
extern s32 D_800A5084[];
extern s32 D_800A5090[];
extern s32 D_800A50C0[];
extern s32 D_800A50CC[];
extern s32 D_800A50D8[];
extern s32 D_800A50E4[];
extern s32 D_800A50F0[];
extern s32 D_800A50FC[];
extern s32 D_800A5108[];
extern s32 D_800A5114[];
extern s32 D_800A5144[];
extern s32 D_800A5150[];
extern s32 D_800A515C[];
extern s32 D_800A5168[];
extern s32 D_800A5174[];
extern s32 D_800A5180[];
extern s32 D_800A518C[];
extern s32 D_800A5198[];
extern s32 D_800A51C8[];
extern s32 D_800A51D4[];
extern s32 D_800A51E0[];
extern s32 D_800A51EC[];
extern s32 D_800A51F8[];
extern s32 D_800A5204[];
extern s32 D_800A5210[];
extern s32 D_800A521C[];
extern s32 D_800A524C[];
extern s32 D_800A5258[];
extern s32 D_800A5264[];
extern s32 D_800A5270[];
extern s32 D_800A527C[];
extern s32 D_800A5288[];
extern s32 D_800A5294[];
extern s32 D_800A52A0[];
extern s32 D_800A52D0[];
extern s32 D_800A52DC[];
extern s32 D_800A52E8[];
extern s32 D_800A52F4[];
extern s32 D_800A5300[];
extern s32 D_800A530C[];
extern s32 D_800A5318[];
extern s32 D_800A5324[];
extern s32 D_800A5354[];
extern s32 D_800A5360[];
extern s32 D_800A536C[];
extern s32 D_800A5378[];
extern s32 D_800A5384[];
extern s32 D_800A5390[];
extern s32 D_800A539C[];
extern s32 D_800A53A8[];
extern s32 D_800A53D8[];
extern s32 D_800A53E4[];
extern s32 D_800A53F0[];
extern s32 D_800A53FC[];
extern s32 D_800A5408[];
extern s32 D_800A5414[];
extern s32 D_800A5420[];
extern s32 D_800A542C[];
extern s32 D_800A509C[];
extern s32 D_800A5120[];
extern s32 D_800A51A4[];
extern s32 D_800A5228[];
extern s32 D_800A52AC[];
extern s32 D_800A5330[];
extern s32 D_800A53B4[];
extern s32 D_800A5438[];
extern s32 D_800A5504[];

StagePoint D_800A4FB4 = { 0x2E0, 2, 1, 176, 0x178, 5, NULL };
StagePoint D_800A4FC4 = { 0x202, 0, 0, 0x420, 0x1F0, 0, &D_800A4FB4 };
StagePoint D_800A4FD4 = { 0x202, 0, 0, 0x150, 0x148, 0, &D_800A4FC4 };
StagePoints D_800A4FE4 = { 2, 1, &D_800A4FD4 };
StagePoint D_800A4FEC = { 0x2E0, 12, 1, 176, 0x178, 5, NULL };
StagePoint D_800A4FFC = { 0x272, 0, 0, 0x420, 0x1F0, 0, &D_800A4FEC };
StagePoint D_800A500C = { 0x272, 0, 0, 0x150, 0x148, 0, &D_800A4FFC };
StagePoints D_800A501C = { 12, 1, &D_800A500C };
StagePoints D_800A5024 = { 0, 0, &D_800A4FD4 };
StagePoints *D_800A502C[] = {
    &D_800A4FE4, &D_800A501C, &D_800A5024, NULL,
};
s32 D_800A503C[] = {
    62, 11, 0x60080000,
};
s32 D_800A5048[] = {
    62, 11, 0x60080000,
};
s32 D_800A5054[] = {
    62, 11, 0x60080000,
};
s32 D_800A5060[] = {
    62, 11, 0x60080000,
};
s32 D_800A506C[] = {
    62, 11, 0x60080000,
};
s32 D_800A5078[] = {
    62, 11, 0x60080000,
};
s32 D_800A5084[] = {
    62, 11, 0x60080000,
};
s32 D_800A5090[] = {
    62, 11, 0x60080000,
};
s32 D_800A509C[] = {
    4, (s32)D_800A503C, (s32)D_800A5048, (s32)D_800A5054,
    (s32)D_800A5060, (s32)D_800A506C, (s32)D_800A5078, (s32)D_800A5084,
    (s32)D_800A5090,
};
s32 D_800A50C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A50CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A50D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A50E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A50F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A50FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5108[] = {
    0, 0, 0x60040000,
};
s32 D_800A5114[] = {
    0, 0, 0x60040000,
};
s32 D_800A5120[] = {
    0, (s32)D_800A50C0, (s32)D_800A50CC, (s32)D_800A50D8,
    (s32)D_800A50E4, (s32)D_800A50F0, (s32)D_800A50FC, (s32)D_800A5108,
    (s32)D_800A5114,
};
s32 D_800A5144[] = {
    0, 0, 0x60040000,
};
s32 D_800A5150[] = {
    0, 0, 0x60040000,
};
s32 D_800A515C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5168[] = {
    0, 0, 0x60040000,
};
s32 D_800A5174[] = {
    0, 0, 0x60040000,
};
s32 D_800A5180[] = {
    0, 0, 0x60040000,
};
s32 D_800A518C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5198[] = {
    0, 0, 0x60040000,
};
s32 D_800A51A4[] = {
    0, (s32)D_800A5144, (s32)D_800A5150, (s32)D_800A515C,
    (s32)D_800A5168, (s32)D_800A5174, (s32)D_800A5180, (s32)D_800A518C,
    (s32)D_800A5198,
};
s32 D_800A51C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A51E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A51EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A51F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5204[] = {
    0, 0, 0x60040000,
};
s32 D_800A5210[] = {
    0, 0, 0x60040000,
};
s32 D_800A521C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5228[] = {
    0, (s32)D_800A51C8, (s32)D_800A51D4, (s32)D_800A51E0,
    (s32)D_800A51EC, (s32)D_800A51F8, (s32)D_800A5204, (s32)D_800A5210,
    (s32)D_800A521C,
};
s32 D_800A524C[] = {
    178, 11, 0x60080000,
};
s32 D_800A5258[] = {
    178, 11, 0x60080000,
};
s32 D_800A5264[] = {
    178, 11, 0x60080000,
};
s32 D_800A5270[] = {
    178, 11, 0x60080000,
};
s32 D_800A527C[] = {
    178, 11, 0x60080000,
};
s32 D_800A5288[] = {
    178, 11, 0x60080000,
};
s32 D_800A5294[] = {
    178, 11, 0x60080000,
};
s32 D_800A52A0[] = {
    178, 11, 0x60080000,
};
s32 D_800A52AC[] = {
    4, (s32)D_800A524C, (s32)D_800A5258, (s32)D_800A5264,
    (s32)D_800A5270, (s32)D_800A527C, (s32)D_800A5288, (s32)D_800A5294,
    (s32)D_800A52A0,
};
s32 D_800A52D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A52F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5300[] = {
    0, 0, 0x60040000,
};
s32 D_800A530C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5318[] = {
    0, 0, 0x60040000,
};
s32 D_800A5324[] = {
    0, 0, 0x60040000,
};
s32 D_800A5330[] = {
    0, (s32)D_800A52D0, (s32)D_800A52DC, (s32)D_800A52E8,
    (s32)D_800A52F4, (s32)D_800A5300, (s32)D_800A530C, (s32)D_800A5318,
    (s32)D_800A5324,
};
s32 D_800A5354[] = {
    0, 0, 0x60040000,
};
s32 D_800A5360[] = {
    0, 0, 0x60040000,
};
s32 D_800A536C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5378[] = {
    0, 0, 0x60040000,
};
s32 D_800A5384[] = {
    0, 0, 0x60040000,
};
s32 D_800A5390[] = {
    0, 0, 0x60040000,
};
s32 D_800A539C[] = {
    0, 0, 0x60040000,
};
s32 D_800A53A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53B4[] = {
    0, (s32)D_800A5354, (s32)D_800A5360, (s32)D_800A536C,
    (s32)D_800A5378, (s32)D_800A5384, (s32)D_800A5390, (s32)D_800A539C,
    (s32)D_800A53A8,
};
s32 D_800A53D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A53F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5408[] = {
    0, 0, 0x60040000,
};
s32 D_800A5414[] = {
    0, 0, 0x60040000,
};
s32 D_800A5420[] = {
    0, 0, 0x60040000,
};
s32 D_800A542C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5438[] = {
    0, (s32)D_800A53D8, (s32)D_800A53E4, (s32)D_800A53F0,
    (s32)D_800A53FC, (s32)D_800A5408, (s32)D_800A5414, (s32)D_800A5420,
    (s32)D_800A542C,
};
s32 D_800A545C[] = {
    179, 2, 0, (s32)D_800A509C,
    (s32)D_800A5120, (s32)D_800A51A4, (s32)D_800A5228, 207,
    12, 0, (s32)D_800A52AC, (s32)D_800A5330,
    (s32)D_800A53B4, (s32)D_800A5438,
};
s32 D_800A5494[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x10001A0, 384, 0x1FF0160,
};
s32 D_800A5504[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A5518[] = {
    (s32)D_800A5504, 0,
};
s32 D_800A5520[] = {
    0x28F0001, 0x4B370137, 0x226000A, 238,
    0x10000, 0x14C02B6, 0xA624C, 0x9E00EF,
    0, 0x2B60001, 0x624C014C, 0x295000A,
    204, 0x10000, 0x14C02B6, 0xA624C,
    0x770380, 0, 0x2FF0001, 0x7000233,
    0xBC0018, 65444, 0x10000, 0x23302FF,
    0x180700, 0xFFEC01AC, 0, 0x2400001,
    0, 0x800000, 276, 0x10000,
    0x10240, 0, 0x12900C0, 0,
    0x2520001, 2, 0x1000000, 292,
    0x10000, 0x30240, 0, 0x1400140,
    0, 0x2480001, 4, 0x3000000,
    312, 0x10000, 0x50254, 0,
    0x10E0340, 0, 0x2400001, 6,
    0x2000000, 335, 0x10000, 0x70244,
    0, 0x13C0240, 0, 0x2400001,
    8, 0x2800000, 337, 0x10000,
    0x90240, 0, 0x15202C0, 0,
    0x68F0001, 0x4B370137, 0x1CC000A, 182,
    0x10000, 0x1340668, 0xA3634, 0xC2015C,
    0, 0x6680001, 0x36340134, 0x2F9000A,
    156, 0x10000, 0x23204FF, 0x180700,
    0x2400BC, 280, 0x4FF0001, 0x7000232,
    0x1AC0018, 0x160006C, 0, 0,
    0, 0, 0,
};
s32 D_800A56AC[] = {
    65535, 65535, 0x2E10001, 0x11000E0,
    4, 0, 65535, 65535,
    0x2E10001, 0x15401D0, 4, 0,
    65535, 65535, 0x2E10001, 0x1080390,
    5, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A570C[])(void) = {
    func_800A4E78,
};
