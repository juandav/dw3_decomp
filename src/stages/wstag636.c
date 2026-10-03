#include "common.h"
#include "stage.h"
extern s32 D_800A53FC[];
extern s32 D_800A55D4[];
extern u8 D_800A5418[];
extern u8 D_800A5698[];
extern u8 D_800A55E4[];
extern void (*D_800A5710[])(void);
void func_800A4DA4();
void func_800A4E74();
extern StagePoints *D_800A51C4[];

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

/* Copies the points of the current place to StageInfo.unk14's table */
void func_800A4DA4(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A4CA4(D_800990B4.unk14, D_800A51C4, GAME.unk44, GAME.unk46);
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
    D_800A5710[0]();
    return task;
}

#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x627
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x637
#endif
void func_800A4E74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A55E4;
    D_800990B4.unk14 = D_800A5698;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x11F00, 0x2F100};
    D_800990B4.unk28 = D_800A5418;
    D_800990B4.unk3C = 0x38;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A55D4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A53FC;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

extern StagePoint D_800A4F7C;
extern StagePoint D_800A4F8C;
extern StagePoint D_800A4F9C;
extern StagePoint D_800A4FAC;
extern StagePoint D_800A4FC4;
extern StagePoint D_800A4FD4;
extern StagePoint D_800A4FE4;
extern StagePoint D_800A4FF4;
extern StagePoint D_800A500C;
extern StagePoint D_800A501C;
extern StagePoint D_800A502C;
extern StagePoint D_800A503C;
extern StagePoint D_800A5054;
extern StagePoint D_800A5064;
extern StagePoint D_800A5074;
extern StagePoint D_800A5084;
extern StagePoint D_800A509C;
extern StagePoint D_800A50AC;
extern StagePoint D_800A50BC;
extern StagePoint D_800A50CC;
extern StagePoint D_800A50E4;
extern StagePoint D_800A50F4;
extern StagePoint D_800A5104;
extern StagePoint D_800A5114;
extern StagePoint D_800A512C;
extern StagePoint D_800A513C;
extern StagePoint D_800A514C;
extern StagePoint D_800A515C;
extern StagePoint D_800A5174;
extern StagePoint D_800A5184;
extern StagePoint D_800A5194;
extern StagePoint D_800A51A4;
extern StagePoints D_800A4FBC;
extern StagePoints D_800A5004;
extern StagePoints D_800A504C;
extern StagePoints D_800A5094;
extern StagePoints D_800A50DC;
extern StagePoints D_800A5124;
extern StagePoints D_800A516C;
extern StagePoints D_800A51B4;
extern StagePoints D_800A51BC;
extern s32 D_800A51EC[];
extern s32 D_800A51F8[];
extern s32 D_800A5204[];
extern s32 D_800A5210[];
extern s32 D_800A521C[];
extern s32 D_800A5228[];
extern s32 D_800A5234[];
extern s32 D_800A5240[];
extern s32 D_800A5270[];
extern s32 D_800A527C[];
extern s32 D_800A5288[];
extern s32 D_800A5294[];
extern s32 D_800A52A0[];
extern s32 D_800A52AC[];
extern s32 D_800A52B8[];
extern s32 D_800A52C4[];
extern s32 D_800A52F4[];
extern s32 D_800A5300[];
extern s32 D_800A530C[];
extern s32 D_800A5318[];
extern s32 D_800A5324[];
extern s32 D_800A5330[];
extern s32 D_800A533C[];
extern s32 D_800A5348[];
extern s32 D_800A5378[];
extern s32 D_800A5384[];
extern s32 D_800A5390[];
extern s32 D_800A539C[];
extern s32 D_800A53A8[];
extern s32 D_800A53B4[];
extern s32 D_800A53C0[];
extern s32 D_800A53CC[];
extern s32 D_800A524C[];
extern s32 D_800A52D0[];
extern s32 D_800A5354[];
extern s32 D_800A53D8[];
extern s32 D_800A54A8[];
extern s32 D_800A54B0[];
extern s32 D_800A54BC[];
extern s32 D_800A54C4[];
extern s32 D_800A54D4[];
extern s32 D_800A54E4[];
extern s32 D_800A5564[];
extern s32 D_800A54F8[];
extern s32 D_800A5570[];
extern s32 D_800A5510[];
extern s32 D_800A558C[];
extern s32 D_800A554C[];
extern s32 D_800A5598[];
extern s32 D_800A55AC[];
extern s32 D_800A55C0[];

StagePoint D_800A4F7C = { 0x2C2, 1, 2, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A4F8C = { 0x2C2, 1, 3, 0x358, 252, 1, &D_800A4F7C };
StagePoint D_800A4F9C = { 0x2C2, 1, 1, 0x120, 0x100, 7, &D_800A4F8C };
StagePoint D_800A4FAC = { 0x2C0, 0, 0, 0x100, 0x278, 5, &D_800A4F9C };
StagePoints D_800A4FBC = { 1, 1, &D_800A4FAC };
StagePoint D_800A4FC4 = { 0x2C2, 1, 1, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A4FD4 = { 0x2C2, 1, 4, 0x358, 252, 1, &D_800A4FC4 };
StagePoint D_800A4FE4 = { 0x2C2, 1, 2, 0x120, 0x100, 7, &D_800A4FD4 };
StagePoint D_800A4FF4 = { 0x2C0, 0, 0, 0x100, 0x278, 5, &D_800A4FE4 };
StagePoints D_800A5004 = { 1, 2, &D_800A4FF4 };
StagePoint D_800A500C = { 0x2C2, 1, 3, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A501C = { 0x2C2, 1, 5, 0x358, 252, 1, &D_800A500C };
StagePoint D_800A502C = { 0x2C2, 1, 4, 0x120, 0x100, 7, &D_800A501C };
StagePoint D_800A503C = { 0x2C2, 1, 1, 0x118, 0x2EC, 5, &D_800A502C };
StagePoints D_800A504C = { 1, 3, &D_800A503C };
StagePoint D_800A5054 = { 0x2C2, 1, 4, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A5064 = { 0x2C2, 1, 6, 0x358, 252, 1, &D_800A5054 };
StagePoint D_800A5074 = { 0x2C2, 1, 3, 0x120, 0x100, 7, &D_800A5064 };
StagePoint D_800A5084 = { 0x2C2, 1, 2, 0x118, 0x2EC, 5, &D_800A5074 };
StagePoints D_800A5094 = { 1, 4, &D_800A5084 };
StagePoint D_800A509C = { 0x2C2, 1, 6, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A50AC = { 0x2C2, 1, 7, 0x358, 252, 1, &D_800A509C };
StagePoint D_800A50BC = { 0x2C2, 1, 5, 0x120, 0x100, 7, &D_800A50AC };
StagePoint D_800A50CC = { 0x2C2, 1, 3, 0x118, 0x2EC, 5, &D_800A50BC };
StagePoints D_800A50DC = { 1, 5, &D_800A50CC };
StagePoint D_800A50E4 = { 0x2C3, 0, 0, 0x2F8, 0x244, 3, NULL };
StagePoint D_800A50F4 = { 0x2C2, 1, 8, 0x358, 252, 1, &D_800A50E4 };
StagePoint D_800A5104 = { 0x2C2, 1, 6, 0x120, 0x100, 7, &D_800A50F4 };
StagePoint D_800A5114 = { 0x2C2, 1, 4, 0x118, 0x2EC, 5, &D_800A5104 };
StagePoints D_800A5124 = { 1, 6, &D_800A5114 };
StagePoint D_800A512C = { 0x2C2, 1, 7, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A513C = { 0x2C2, 1, 1, 0x358, 252, 1, &D_800A512C };
StagePoint D_800A514C = { 0x2C2, 1, 8, 0x120, 0x100, 7, &D_800A513C };
StagePoint D_800A515C = { 0x2C2, 1, 5, 0x118, 0x2EC, 5, &D_800A514C };
StagePoints D_800A516C = { 1, 7, &D_800A515C };
StagePoint D_800A5174 = { 0x2C2, 1, 8, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A5184 = { 0x2C2, 1, 2, 0x358, 252, 1, &D_800A5174 };
StagePoint D_800A5194 = { 0x2C2, 1, 7, 0x120, 0x100, 7, &D_800A5184 };
StagePoint D_800A51A4 = { 0x2C2, 1, 6, 0x118, 0x2EC, 5, &D_800A5194 };
StagePoints D_800A51B4 = { 1, 8, &D_800A51A4 };
StagePoints D_800A51BC = { 0, 0, &D_800A4FAC };
StagePoints *D_800A51C4[] = {
    &D_800A4FBC, &D_800A5004, &D_800A504C, &D_800A5094,
    &D_800A50DC, &D_800A5124, &D_800A516C, &D_800A51B4,
    &D_800A51BC, NULL,
};
s32 D_800A51EC[] = {
    72, 5, 0x60080000,
};
s32 D_800A51F8[] = {
    72, 5, 0x60080000,
};
s32 D_800A5204[] = {
    72, 5, 0x60080000,
};
s32 D_800A5210[] = {
    72, 5, 0x60080000,
};
s32 D_800A521C[] = {
    162, 5, 0x60080000,
};
s32 D_800A5228[] = {
    162, 5, 0x60080000,
};
s32 D_800A5234[] = {
    162, 5, 0x60080000,
};
s32 D_800A5240[] = {
    162, 5, 0x60080000,
};
s32 D_800A524C[] = {
    3, (s32)D_800A51EC, (s32)D_800A51F8, (s32)D_800A5204,
    (s32)D_800A5210, (s32)D_800A521C, (s32)D_800A5228, (s32)D_800A5234,
    (s32)D_800A5240,
};
s32 D_800A5270[] = {
    0, 0, 0x60040000,
};
s32 D_800A527C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5288[] = {
    0, 0, 0x60040000,
};
s32 D_800A5294[] = {
    0, 0, 0x60040000,
};
s32 D_800A52A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A52C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52D0[] = {
    0, (s32)D_800A5270, (s32)D_800A527C, (s32)D_800A5288,
    (s32)D_800A5294, (s32)D_800A52A0, (s32)D_800A52AC, (s32)D_800A52B8,
    (s32)D_800A52C4,
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
    0, 0, 0x60040000,
};
s32 D_800A533C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5348[] = {
    0, 0, 0x60040000,
};
s32 D_800A5354[] = {
    0, (s32)D_800A52F4, (s32)D_800A5300, (s32)D_800A530C,
    (s32)D_800A5318, (s32)D_800A5324, (s32)D_800A5330, (s32)D_800A533C,
    (s32)D_800A5348,
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
    0, 0, 0x60040000,
};
s32 D_800A53C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53D8[] = {
    0, (s32)D_800A5378, (s32)D_800A5384, (s32)D_800A5390,
    (s32)D_800A539C, (s32)D_800A53A8, (s32)D_800A53B4, (s32)D_800A53C0,
    (s32)D_800A53CC,
};
s32 D_800A53FC[] = {
    102, 0, 0, (s32)D_800A524C,
    (s32)D_800A52D0, (s32)D_800A5354, (s32)D_800A53D8,
};
u8 D_800A5418[] = {
    0x00, 0x02, 0x00, 0x01, 0x1C, 0x02, 0xA6, 0x01,
    0x70, 0x00, 0xA6, 0x00, 0x30, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x16, 0x02, 0x38, 0x01,
    0x58, 0x00, 0x38, 0x00, 0x00, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x08, 0x02, 0xBC, 0x01,
    0x20, 0x00, 0xBC, 0x00, 0x10, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x10, 0x02, 0xBC, 0x01,
    0x40, 0x00, 0xBC, 0x00, 0x20, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0xBC, 0x01,
    0x00, 0x00, 0xBC, 0x00, 0x30, 0x02, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x62, 0x01, 0xA0, 0x01,
    0x88, 0x00, 0xA0, 0x00, 0x40, 0x01, 0xFF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x58, 0x01, 0xA0, 0x01,
    0x60, 0x00, 0xA0, 0x00, 0x50, 0x01, 0xFF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x62, 0x01, 0xC0, 0x01,
    0x88, 0x00, 0xC0, 0x00, 0x60, 0x01, 0xFF, 0x01,
};
s32 D_800A54A8[] = {
    0x18682, 65535,
};
s32 D_800A54B0[] = {
    34434, 0, 65535,
};
s32 D_800A54BC[] = {
    0x10000, 65535,
};
s32 D_800A54C4[] = {
    34434, 0x10000, 33918, 65535,
};
s32 D_800A54D4[] = {
    0x10000, 0x1847E, 34434, 65535,
};
s32 D_800A54E4[] = {
    0x18682, 34433, 33918, 0x17013,
    65535,
};
s32 D_800A54F8[] = {
    0, 0, 969, 0,
    0, 0,
};
s32 D_800A5510[] = {
    (s32)D_800A54A8, 0, 848, (s32)D_800A54B0,
    (s32)D_800A54BC, 849, (s32)D_800A54C4, 0,
    850, (s32)D_800A54D4, (s32)D_800A54E4, 851,
    0, 0, 0,
};
s32 D_800A554C[] = {
    0, 0, 970, 0,
    0, 0,
};
s32 D_800A5564[] = {
    0x17E00, 0x17E1E, 65535,
};
s32 D_800A5570[] = {
    0x17043, 0x1704B, 0x18681, 34434,
    0x17E00, 0x17E1F, 65535,
};
s32 D_800A558C[] = {
    0x17E00, 0x17E23, 65535,
};
s32 D_800A5598[] = {
    (s32)D_800A5564, (s32)D_800A54F8, 0x40040, 0x16C0198,
    7,
};
s32 D_800A55AC[] = {
    (s32)D_800A5570, (s32)D_800A5510, 0x500A7, 0x2B801E0,
    7,
};
s32 D_800A55C0[] = {
    (s32)D_800A558C, (s32)D_800A554C, 0x600B5, 0x2B801E0,
    7,
};
s32 D_800A55D4[] = {
    (s32)D_800A5598, (s32)D_800A55AC, (s32)D_800A55C0, 0,
};
u8 D_800A55E4[] = {
    0x01, 0x00, 0x40, 0x02, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x02, 0x8F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x03, 0xF7, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x01,
    0x16, 0x01, 0x49, 0x01, 0x00, 0x00, 0x01, 0x00,
    0x48, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5C, 0x01, 0x16, 0x01, 0x56, 0x01, 0x00, 0x00,
    0x01, 0x00, 0x4A, 0x04, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x11, 0x02, 0x63, 0x02, 0xA8, 0x02,
    0x00, 0x00, 0x01, 0x00, 0x5A, 0x04, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xA6, 0x01, 0x3A, 0x02,
    0x90, 0x02, 0x00, 0x00, 0x01, 0x00, 0x58, 0x04,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01,
    0x7B, 0x02, 0xCF, 0x02, 0x00, 0x00, 0x01, 0x00,
    0x64, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x96, 0x03, 0x05, 0x02, 0x60, 0x02, 0x00, 0x00,
    0x01, 0x00, 0x64, 0x04, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x46, 0x02, 0x9C, 0x00, 0xF8, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5698[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xC1, 0x02, 0x40, 0x03, 0xF0, 0x00,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xC1, 0x02, 0x68, 0x03, 0xEC, 0x02,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xC1, 0x02, 0x28, 0x01, 0xF4, 0x02,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xC1, 0x02, 0x10, 0x01, 0x08, 0x01,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A5710[])(void) = {
    func_800A4E74,
};
