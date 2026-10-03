#include "common.h"
#include "stage.h"
extern void (*D_800A5614[])(void);
void func_800A4DA4();
extern StagePoints *D_800A51B4[];

void func_800A4CA4(StageSlot *slots, StagePoints **list, s32 id0, s32 id1) {
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

void func_800A4DA4(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A4CA4(D_800990B4.unk14, D_800A51B4, GAME.unk44, GAME.unk46);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4E18(void *owner) {
    StageTask *task = createTask(func_800A4DA4, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5614[0]();
    return task;
}

extern s32 D_800A5468[];
extern s32 D_800A559C[];
extern s32 D_800A5408[];
extern s32 D_800A53EC[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x623
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x633
#endif
void func_800A4E74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5468;
    D_800990B4.unk14 = D_800A559C;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xF500, 0x2FA00};
    D_800990B4.unk28 = D_800A5408;
    D_800990B4.unk3C = 0x38;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A53EC;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4E74();
extern StagePoint D_800A4F6C;
extern StagePoint D_800A4F7C;
extern StagePoint D_800A4F8C;
extern StagePoint D_800A4F9C;
extern StagePoint D_800A4FB4;
extern StagePoint D_800A4FC4;
extern StagePoint D_800A4FD4;
extern StagePoint D_800A4FE4;
extern StagePoint D_800A4FFC;
extern StagePoint D_800A500C;
extern StagePoint D_800A501C;
extern StagePoint D_800A502C;
extern StagePoint D_800A5044;
extern StagePoint D_800A5054;
extern StagePoint D_800A5064;
extern StagePoint D_800A5074;
extern StagePoint D_800A508C;
extern StagePoint D_800A509C;
extern StagePoint D_800A50AC;
extern StagePoint D_800A50BC;
extern StagePoint D_800A50D4;
extern StagePoint D_800A50E4;
extern StagePoint D_800A50F4;
extern StagePoint D_800A5104;
extern StagePoint D_800A511C;
extern StagePoint D_800A512C;
extern StagePoint D_800A513C;
extern StagePoint D_800A514C;
extern StagePoint D_800A5164;
extern StagePoint D_800A5174;
extern StagePoint D_800A5184;
extern StagePoint D_800A5194;
extern StagePoints D_800A4FAC;
extern StagePoints D_800A4FF4;
extern StagePoints D_800A503C;
extern StagePoints D_800A5084;
extern StagePoints D_800A50CC;
extern StagePoints D_800A5114;
extern StagePoints D_800A515C;
extern StagePoints D_800A51A4;
extern StagePoints D_800A51AC;
extern s32 D_800A51DC[];
extern s32 D_800A51E8[];
extern s32 D_800A51F4[];
extern s32 D_800A5200[];
extern s32 D_800A520C[];
extern s32 D_800A5218[];
extern s32 D_800A5224[];
extern s32 D_800A5230[];
extern s32 D_800A5260[];
extern s32 D_800A526C[];
extern s32 D_800A5278[];
extern s32 D_800A5284[];
extern s32 D_800A5290[];
extern s32 D_800A529C[];
extern s32 D_800A52A8[];
extern s32 D_800A52B4[];
extern s32 D_800A52E4[];
extern s32 D_800A52F0[];
extern s32 D_800A52FC[];
extern s32 D_800A5308[];
extern s32 D_800A5314[];
extern s32 D_800A5320[];
extern s32 D_800A532C[];
extern s32 D_800A5338[];
extern s32 D_800A5368[];
extern s32 D_800A5374[];
extern s32 D_800A5380[];
extern s32 D_800A538C[];
extern s32 D_800A5398[];
extern s32 D_800A53A4[];
extern s32 D_800A53B0[];
extern s32 D_800A53BC[];
extern s32 D_800A523C[];
extern s32 D_800A52C0[];
extern s32 D_800A5344[];
extern s32 D_800A53C8[];

StagePoint D_800A4F6C = { 0x2C1, 1, 1, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A4F7C = { 0x2C1, 1, 3, 0x340, 240, 1, &D_800A4F6C };
StagePoint D_800A4F8C = { 0x2C1, 1, 2, 0x110, 0x108, 7, &D_800A4F7C };
StagePoint D_800A4F9C = { 0x2C0, 0, 0, 0x100, 0x278, 5, &D_800A4F8C };
StagePoints D_800A4FAC = { 1, 1, &D_800A4F9C };
StagePoint D_800A4FB4 = { 0x2C1, 1, 2, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A4FC4 = { 0x2C1, 1, 4, 0x340, 240, 1, &D_800A4FB4 };
StagePoint D_800A4FD4 = { 0x2C1, 1, 1, 0x110, 0x108, 7, &D_800A4FC4 };
StagePoint D_800A4FE4 = { 0x2C0, 0, 0, 0x100, 0x278, 5, &D_800A4FD4 };
StagePoints D_800A4FF4 = { 1, 2, &D_800A4FE4 };
StagePoint D_800A4FFC = { 0x2C1, 1, 4, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A500C = { 0x2C1, 1, 5, 0x340, 240, 1, &D_800A4FFC };
StagePoint D_800A501C = { 0x2C1, 1, 3, 0x110, 0x108, 7, &D_800A500C };
StagePoint D_800A502C = { 0x2C1, 1, 1, 0x128, 0x2F4, 5, &D_800A501C };
StagePoints D_800A503C = { 1, 3, &D_800A502C };
StagePoint D_800A5044 = { 0x2C1, 1, 3, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5054 = { 0x2C1, 1, 6, 0x340, 240, 1, &D_800A5044 };
StagePoint D_800A5064 = { 0x2C1, 1, 4, 0x110, 0x108, 7, &D_800A5054 };
StagePoint D_800A5074 = { 0x2C1, 1, 2, 0x128, 0x2F4, 5, &D_800A5064 };
StagePoints D_800A5084 = { 1, 4, &D_800A5074 };
StagePoint D_800A508C = { 0x2C1, 1, 5, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A509C = { 0x2C1, 1, 7, 0x340, 240, 1, &D_800A508C };
StagePoint D_800A50AC = { 0x2C1, 1, 6, 0x110, 0x108, 7, &D_800A509C };
StagePoint D_800A50BC = { 0x2C1, 1, 3, 0x128, 0x2F4, 5, &D_800A50AC };
StagePoints D_800A50CC = { 1, 5, &D_800A50BC };
StagePoint D_800A50D4 = { 0x2C1, 1, 6, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A50E4 = { 0x2C1, 1, 8, 0x340, 240, 1, &D_800A50D4 };
StagePoint D_800A50F4 = { 0x2C1, 1, 5, 0x110, 0x108, 7, &D_800A50E4 };
StagePoint D_800A5104 = { 0x2C1, 1, 4, 0x128, 0x2F4, 5, &D_800A50F4 };
StagePoints D_800A5114 = { 1, 6, &D_800A5104 };
StagePoint D_800A511C = { 0x2C1, 1, 8, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A512C = { 0x2C1, 1, 1, 0x340, 240, 1, &D_800A511C };
StagePoint D_800A513C = { 0x2C1, 1, 7, 0x110, 0x108, 7, &D_800A512C };
StagePoint D_800A514C = { 0x2C1, 1, 5, 0x128, 0x2F4, 5, &D_800A513C };
StagePoints D_800A515C = { 1, 7, &D_800A514C };
StagePoint D_800A5164 = { 0x2C1, 1, 7, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5174 = { 0x2C1, 1, 2, 0x340, 240, 1, &D_800A5164 };
StagePoint D_800A5184 = { 0x2C1, 1, 8, 0x110, 0x108, 7, &D_800A5174 };
StagePoint D_800A5194 = { 0x2C1, 1, 6, 0x128, 0x2F4, 5, &D_800A5184 };
StagePoints D_800A51A4 = { 1, 8, &D_800A5194 };
StagePoints D_800A51AC = { 0, 0, &D_800A4F9C };
StagePoints *D_800A51B4[] = {
    &D_800A4FAC, &D_800A4FF4, &D_800A503C, &D_800A5084,
    &D_800A50CC, &D_800A5114, &D_800A515C, &D_800A51A4,
    &D_800A51AC, NULL,
};
s32 D_800A51DC[] = {
    72, 5, 0x60080000,
};
s32 D_800A51E8[] = {
    72, 5, 0x60080000,
};
s32 D_800A51F4[] = {
    72, 5, 0x60080000,
};
s32 D_800A5200[] = {
    72, 5, 0x60080000,
};
s32 D_800A520C[] = {
    162, 5, 0x60080000,
};
s32 D_800A5218[] = {
    162, 5, 0x60080000,
};
s32 D_800A5224[] = {
    162, 5, 0x60080000,
};
s32 D_800A5230[] = {
    162, 5, 0x60080000,
};
s32 D_800A523C[] = {
    3, (s32)D_800A51DC, (s32)D_800A51E8, (s32)D_800A51F4,
    (s32)D_800A5200, (s32)D_800A520C, (s32)D_800A5218, (s32)D_800A5224,
    (s32)D_800A5230,
};
s32 D_800A5260[] = {
    0, 0, 0x60040000,
};
s32 D_800A526C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5278[] = {
    0, 0, 0x60040000,
};
s32 D_800A5284[] = {
    0, 0, 0x60040000,
};
s32 D_800A5290[] = {
    0, 0, 0x60040000,
};
s32 D_800A529C[] = {
    0, 0, 0x60040000,
};
s32 D_800A52A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A52B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52C0[] = {
    0, (s32)D_800A5260, (s32)D_800A526C, (s32)D_800A5278,
    (s32)D_800A5284, (s32)D_800A5290, (s32)D_800A529C, (s32)D_800A52A8,
    (s32)D_800A52B4,
};
s32 D_800A52E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5308[] = {
    0, 0, 0x60040000,
};
s32 D_800A5314[] = {
    0, 0, 0x60040000,
};
s32 D_800A5320[] = {
    0, 0, 0x60040000,
};
s32 D_800A532C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5338[] = {
    0, 0, 0x60040000,
};
s32 D_800A5344[] = {
    0, (s32)D_800A52E4, (s32)D_800A52F0, (s32)D_800A52FC,
    (s32)D_800A5308, (s32)D_800A5314, (s32)D_800A5320, (s32)D_800A532C,
    (s32)D_800A5338,
};
s32 D_800A5368[] = {
    0, 0, 0x60040000,
};
s32 D_800A5374[] = {
    0, 0, 0x60040000,
};
s32 D_800A5380[] = {
    0, 0, 0x60040000,
};
s32 D_800A538C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5398[] = {
    0, 0, 0x60040000,
};
s32 D_800A53A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A53B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53C8[] = {
    0, (s32)D_800A5368, (s32)D_800A5374, (s32)D_800A5380,
    (s32)D_800A538C, (s32)D_800A5398, (s32)D_800A53A4, (s32)D_800A53B0,
    (s32)D_800A53BC,
};
s32 D_800A53EC[] = {
    103, 0, 0, (s32)D_800A523C,
    (s32)D_800A52C0, (s32)D_800A5344, (s32)D_800A53C8,
};
s32 D_800A5408[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
};
s32 D_800A5468[] = {
    0x2400001, 0, 0x1440000, 536,
    0x10000, 576, 0, 0xE00174,
    0, 0x2400001, 0, 0x2040000,
    664, 0x10000, 576, 0,
    0x1200214, 0, 0x2400001, 0,
    0x2440000, 456, 0x10000, 576,
    0, 0x26802C4, 0, 0x2400001,
    0, 0x2D40000, 272, 0x10000,
    576, 0, 0x1D00314, 0,
    0x4600001, 1, 0x1840000, 0x14800EE,
    0x10000, 0x20460, 0, 0x12E0224,
    392, 0x4600001, 3, 0x2E40000,
    0x179011E, 0x10000, 0x40460, 0,
    0x1D60254, 561, 0x4600001, 5,
    0x3240000, 0x23801DE, 0x10000, 0x60460,
    0, 0x2260154, 640, 0x4600001,
    7, 0x2140000, 0x30002A6, 0x10000,
    0x80460, 0, 0x27602D4, 717,
    0, 0, 0, 0,
    0,
};
s32 D_800A559C[] = {
    65535, 65535, 0x2C20001, 0xFC0358,
    5, 0, 65535, 65535,
    0x2C20001, 0x2F80350, 7, 0,
    65535, 65535, 0x2C20001, 0x2EC0118,
    1, 0, 65535, 65535,
    0x2C20001, 0x1000120, 3, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A5614[])(void) = {
    func_800A4E74,
};
