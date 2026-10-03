#include "common.h"
#include "stage.h"
void func_800A5EE4();
extern void (*D_800A63B4[])(void);
extern StagePoints *D_800A6134[];

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
        func_800A5DE4(D_800990B4.unk14, D_800A6134, GAME.unk44, GAME.unk46);
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
    D_800A63B4[0]();
    return task;
}

extern s32 D_800A61C8[];
extern s32 D_800A6354[];
extern s32 D_800A613C[];
extern s32 D_800A61C0[];
extern CVECTOR D_800A5DE0;
extern s32 D_800A65C8[];
void func_800A5FB4(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x700;
    D_800990B4.unkC = 0x9310004;
    D_800990B4.unk10 = D_800A61C8;
    D_800990B4.unk14 = D_800A6354;
    D_800990B4.unk1C = 0x930;
    D_800990B4.unk2C = (Vec2){0xDB00, 0x12300};
    D_800990B4.unk28 = D_800A613C;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A61C0;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A65C8, GAME.unk44);
    D_8009A70C.setFile(0, 0x9310006);
    D_8009A70C.setFile(7, 0x9310007);
    D_8009A70C.setFile(4, 0x9310005);
    D_8009A70C.unk50(0);
}

void func_800A5FB4();
extern StagePoint D_800A60FC;
extern StagePoint D_800A610C;
extern StagePoint D_800A611C;
extern StagePoints D_800A612C;
extern s32 D_800A61AC[];
extern s32 D_800A63B8[];
extern s32 D_800A63C4[];
extern s32 D_800A63D0[];
extern s32 D_800A63DC[];
extern s32 D_800A63E8[];
extern s32 D_800A63F4[];
extern s32 D_800A6400[];
extern s32 D_800A640C[];
extern s32 D_800A643C[];
extern s32 D_800A6448[];
extern s32 D_800A6454[];
extern s32 D_800A6460[];
extern s32 D_800A646C[];
extern s32 D_800A6478[];
extern s32 D_800A6484[];
extern s32 D_800A6490[];
extern s32 D_800A64C0[];
extern s32 D_800A64CC[];
extern s32 D_800A64D8[];
extern s32 D_800A64E4[];
extern s32 D_800A64F0[];
extern s32 D_800A64FC[];
extern s32 D_800A6508[];
extern s32 D_800A6514[];
extern s32 D_800A6544[];
extern s32 D_800A6550[];
extern s32 D_800A655C[];
extern s32 D_800A6568[];
extern s32 D_800A6574[];
extern s32 D_800A6580[];
extern s32 D_800A658C[];
extern s32 D_800A6598[];
extern s32 D_800A6418[];
extern s32 D_800A649C[];
extern s32 D_800A6520[];
extern s32 D_800A65A4[];

StagePoint D_800A60FC = { 0x2E3, 1, 1, 160, 0x180, 5, NULL };
StagePoint D_800A610C = { 0x272, 0, 0, 0x420, 0x1F0, 0, &D_800A60FC };
StagePoint D_800A611C = { 0x272, 0, 0, 0x150, 0x148, 0, &D_800A610C };
StagePoints D_800A612C = { 1, 1, &D_800A611C };
StagePoints *D_800A6134[] = {
    &D_800A612C, NULL,
};
s32 D_800A613C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x10001A0, 384, 0x1FF0160,
};
s32 D_800A61AC[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A61C0[] = {
    (s32)D_800A61AC, 0,
};
s32 D_800A61C8[] = {
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
s32 D_800A6354[] = {
    65535, 65535, 0x2E10001, 0x11000E0,
    4, 0, 65535, 65535,
    0x2E10001, 0x15401D0, 4, 0,
    65535, 65535, 0x2E10001, 0x1080390,
    5, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A63B4[])(void) = {
    func_800A5FB4,
};
s32 D_800A63B8[] = {
    62, 11, 0x60080000,
};
s32 D_800A63C4[] = {
    62, 11, 0x60080000,
};
s32 D_800A63D0[] = {
    62, 11, 0x60080000,
};
s32 D_800A63DC[] = {
    62, 11, 0x60080000,
};
s32 D_800A63E8[] = {
    62, 11, 0x60080000,
};
s32 D_800A63F4[] = {
    62, 11, 0x60080000,
};
s32 D_800A6400[] = {
    103, 11, 0x60080000,
};
s32 D_800A640C[] = {
    103, 11, 0x60080000,
};
s32 D_800A6418[] = {
    5, (s32)D_800A63B8, (s32)D_800A63C4, (s32)D_800A63D0,
    (s32)D_800A63DC, (s32)D_800A63E8, (s32)D_800A63F4, (s32)D_800A6400,
    (s32)D_800A640C,
};
s32 D_800A643C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A643C, (s32)D_800A6448, (s32)D_800A6454,
    (s32)D_800A6460, (s32)D_800A646C, (s32)D_800A6478, (s32)D_800A6484,
    (s32)D_800A6490,
};
s32 D_800A64C0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A64C0, (s32)D_800A64CC, (s32)D_800A64D8,
    (s32)D_800A64E4, (s32)D_800A64F0, (s32)D_800A64FC, (s32)D_800A6508,
    (s32)D_800A6514,
};
s32 D_800A6544[] = {
    0, 0, 0x60040000,
};
s32 D_800A6550[] = {
    0, 0, 0x60040000,
};
s32 D_800A655C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6568[] = {
    0, 0, 0x60040000,
};
s32 D_800A6574[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6544, (s32)D_800A6550, (s32)D_800A655C,
    (s32)D_800A6568, (s32)D_800A6574, (s32)D_800A6580, (s32)D_800A658C,
    (s32)D_800A6598,
};
s32 D_800A65C8[] = {
    395, 1, 0, (s32)D_800A6418,
    (s32)D_800A649C, (s32)D_800A6520, (s32)D_800A65A4,
};
