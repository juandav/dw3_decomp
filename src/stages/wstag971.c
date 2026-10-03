#include "common.h"
#include "stage.h"
void func_800A5EE0();
extern void (*D_800A6798[])(void);
extern StagePoints *D_800A61C8[];

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
        func_800A5DE0(D_800990B4.unk14, D_800A61C8, GAME.unk44, GAME.unk46);
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
    D_800A6798[0]();
    return task;
}

extern s32 D_800A6754[];
extern s32 D_800A6768[];
extern s32 D_800A61F4[];
extern s32 D_800A6728[];
extern s32 D_800A6DCC[];
void func_800A5FB0(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x68F;
    D_800990B4.unkC = 0x9450004;
    D_800990B4.unk10 = D_800A6754;
    D_800990B4.unk14 = D_800A6768;
    D_800990B4.unk1C = 0x944;
    D_800990B4.unk2C = (Vec2){0xEB00, 0x1F500};
    D_800990B4.unk28 = D_800A61F4;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A6728;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A6DCC, GAME.unk44);
    D_8009A70C.setFile(0, 0x9450006);
    D_8009A70C.setFile(7, 0x9450007);
    D_8009A70C.setFile(4, 0x9450005);
    D_8009A70C.unk50(0);
}

void func_800A5FB0();
extern StagePoint D_800A60D8;
extern StagePoint D_800A60F0;
extern StagePoint D_800A6108;
extern StagePoint D_800A6120;
extern StagePoint D_800A6138;
extern StagePoint D_800A6150;
extern StagePoint D_800A6168;
extern StagePoint D_800A6180;
extern StagePoint D_800A6198;
extern StagePoint D_800A61B0;
extern StagePoints D_800A60E8;
extern StagePoints D_800A6100;
extern StagePoints D_800A6118;
extern StagePoints D_800A6130;
extern StagePoints D_800A6148;
extern StagePoints D_800A6160;
extern StagePoints D_800A6178;
extern StagePoints D_800A6190;
extern StagePoints D_800A61A8;
extern StagePoints D_800A61C0;
extern s32 D_800A62C4[];
extern s32 D_800A62CC[];
extern s32 D_800A62D4[];
extern s32 D_800A62E4[];
extern s32 D_800A62EC[];
extern s32 D_800A62FC[];
extern s32 D_800A6308[];
extern s32 D_800A6318[];
extern s32 D_800A6324[];
extern s32 D_800A6334[];
extern s32 D_800A6340[];
extern s32 D_800A6348[];
extern s32 D_800A6350[];
extern s32 D_800A6360[];
extern s32 D_800A6368[];
extern s32 D_800A6378[];
extern s32 D_800A6384[];
extern s32 D_800A6394[];
extern s32 D_800A63A0[];
extern s32 D_800A63B0[];
extern s32 D_800A63BC[];
extern s32 D_800A63C4[];
extern s32 D_800A63CC[];
extern s32 D_800A63DC[];
extern s32 D_800A63E4[];
extern s32 D_800A63F4[];
extern s32 D_800A6400[];
extern s32 D_800A6410[];
extern s32 D_800A641C[];
extern s32 D_800A642C[];
extern s32 D_800A6438[];
extern s32 D_800A6440[];
extern s32 D_800A6448[];
extern s32 D_800A6458[];
extern s32 D_800A6460[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A648C[];
extern s32 D_800A6498[];
extern s32 D_800A64A8[];
extern s32 D_800A65D4[];
extern s32 D_800A64B4[];
extern s32 D_800A65E8[];
extern s32 D_800A64FC[];
extern s32 D_800A65FC[];
extern s32 D_800A6544[];
extern s32 D_800A6610[];
extern s32 D_800A658C[];
extern s32 D_800A6624[];
extern s32 D_800A6630[];
extern s32 D_800A663C[];
extern s32 D_800A6648[];
extern s32 D_800A6654[];
extern s32 D_800A6660[];
extern s32 D_800A6674[];
extern s32 D_800A6688[];
extern s32 D_800A669C[];
extern s32 D_800A66B0[];
extern s32 D_800A66C4[];
extern s32 D_800A66D8[];
extern s32 D_800A66EC[];
extern s32 D_800A6700[];
extern s32 D_800A6714[];
extern s32 D_800A679C[];
extern s32 D_800A67A8[];
extern s32 D_800A67B4[];
extern s32 D_800A67C0[];
extern s32 D_800A67CC[];
extern s32 D_800A67D8[];
extern s32 D_800A67E4[];
extern s32 D_800A67F0[];
extern s32 D_800A6820[];
extern s32 D_800A682C[];
extern s32 D_800A6838[];
extern s32 D_800A6844[];
extern s32 D_800A6850[];
extern s32 D_800A685C[];
extern s32 D_800A6868[];
extern s32 D_800A6874[];
extern s32 D_800A68A4[];
extern s32 D_800A68B0[];
extern s32 D_800A68BC[];
extern s32 D_800A68C8[];
extern s32 D_800A68D4[];
extern s32 D_800A68E0[];
extern s32 D_800A68EC[];
extern s32 D_800A68F8[];
extern s32 D_800A6928[];
extern s32 D_800A6934[];
extern s32 D_800A6940[];
extern s32 D_800A694C[];
extern s32 D_800A6958[];
extern s32 D_800A6964[];
extern s32 D_800A6970[];
extern s32 D_800A697C[];
extern s32 D_800A69AC[];
extern s32 D_800A69B8[];
extern s32 D_800A69C4[];
extern s32 D_800A69D0[];
extern s32 D_800A69DC[];
extern s32 D_800A69E8[];
extern s32 D_800A69F4[];
extern s32 D_800A6A00[];
extern s32 D_800A6A30[];
extern s32 D_800A6A3C[];
extern s32 D_800A6A48[];
extern s32 D_800A6A54[];
extern s32 D_800A6A60[];
extern s32 D_800A6A6C[];
extern s32 D_800A6A78[];
extern s32 D_800A6A84[];
extern s32 D_800A6AB4[];
extern s32 D_800A6AC0[];
extern s32 D_800A6ACC[];
extern s32 D_800A6AD8[];
extern s32 D_800A6AE4[];
extern s32 D_800A6AF0[];
extern s32 D_800A6AFC[];
extern s32 D_800A6B08[];
extern s32 D_800A6B38[];
extern s32 D_800A6B44[];
extern s32 D_800A6B50[];
extern s32 D_800A6B5C[];
extern s32 D_800A6B68[];
extern s32 D_800A6B74[];
extern s32 D_800A6B80[];
extern s32 D_800A6B8C[];
extern s32 D_800A6BBC[];
extern s32 D_800A6BC8[];
extern s32 D_800A6BD4[];
extern s32 D_800A6BE0[];
extern s32 D_800A6BEC[];
extern s32 D_800A6BF8[];
extern s32 D_800A6C04[];
extern s32 D_800A6C10[];
extern s32 D_800A6C40[];
extern s32 D_800A6C4C[];
extern s32 D_800A6C58[];
extern s32 D_800A6C64[];
extern s32 D_800A6C70[];
extern s32 D_800A6C7C[];
extern s32 D_800A6C88[];
extern s32 D_800A6C94[];
extern s32 D_800A6CC4[];
extern s32 D_800A6CD0[];
extern s32 D_800A6CDC[];
extern s32 D_800A6CE8[];
extern s32 D_800A6CF4[];
extern s32 D_800A6D00[];
extern s32 D_800A6D0C[];
extern s32 D_800A6D18[];
extern s32 D_800A6D48[];
extern s32 D_800A6D54[];
extern s32 D_800A6D60[];
extern s32 D_800A6D6C[];
extern s32 D_800A6D78[];
extern s32 D_800A6D84[];
extern s32 D_800A6D90[];
extern s32 D_800A6D9C[];
extern s32 D_800A67FC[];
extern s32 D_800A6880[];
extern s32 D_800A6904[];
extern s32 D_800A6988[];
extern s32 D_800A6A0C[];
extern s32 D_800A6A90[];
extern s32 D_800A6B14[];
extern s32 D_800A6B98[];
extern s32 D_800A6C1C[];
extern s32 D_800A6CA0[];
extern s32 D_800A6D24[];
extern s32 D_800A6DA8[];

StagePoint D_800A60D8 = { 0x2EE, 1, 1, 224, 0x240, 5, NULL };
StagePoints D_800A60E8 = { 1, 1, &D_800A60D8 };
StagePoint D_800A60F0 = { 0x2ED, 1, 1, 224, 192, 5, NULL };
StagePoints D_800A6100 = { 1, 2, &D_800A60F0 };
StagePoint D_800A6108 = { 0x2ED, 1, 2, 224, 192, 5, NULL };
StagePoints D_800A6118 = { 1, 3, &D_800A6108 };
StagePoint D_800A6120 = { 0x2EE, 1, 2, 224, 0x240, 5, NULL };
StagePoints D_800A6130 = { 1, 4, &D_800A6120 };
StagePoint D_800A6138 = { 0x2ED, 1, 5, 224, 192, 5, NULL };
StagePoints D_800A6148 = { 1, 5, &D_800A6138 };
StagePoint D_800A6150 = { 0x2EE, 1, 4, 224, 0x240, 5, NULL };
StagePoints D_800A6160 = { 1, 6, &D_800A6150 };
StagePoint D_800A6168 = { 0x2ED, 5, 4, 224, 192, 5, NULL };
StagePoints D_800A6178 = { 5, 1, &D_800A6168 };
StagePoint D_800A6180 = { 0x2ED, 5, 5, 224, 192, 5, NULL };
StagePoints D_800A6190 = { 5, 2, &D_800A6180 };
StagePoint D_800A6198 = { 0x2ED, 5, 6, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A61A8 = { 5, 3, &D_800A6198 };
StagePoint D_800A61B0 = { 0x2ED, 6, 4, 224, 192, 5, NULL };
StagePoints D_800A61C0 = { 6, 1, &D_800A61B0 };
StagePoints *D_800A61C8[] = {
    &D_800A60E8, &D_800A6100, &D_800A6118, &D_800A6130,
    &D_800A6148, &D_800A6160, &D_800A6178, &D_800A6190,
    &D_800A61A8, &D_800A61C0, NULL,
};
s32 D_800A61F4[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140015E, 0x400078, 0x1FF0140,
    0x1000140, 0x1000140, 0, 0x1FF0150,
    0x1000140, 0x1400152, 0x400048, 0x1FF0160,
    0x1000140, 0x1400140, 0x400000, 0x1FF0170,
    0x1000140, 0x140016A, 0x4000A8, 0x1FE0140,
    0x1000140, 0x1000154, 80, 0x1FE0150,
    0x1000140, 0x1000168, 160, 0x1FE0160,
};
s32 D_800A62C4[] = {
    0x18168, 65535,
};
s32 D_800A62CC[] = {
    0x17038, 65535,
};
s32 D_800A62D4[] = {
    33128, 0, 2586, 65535,
};
s32 D_800A62E4[] = {
    0x10000, 65535,
};
s32 D_800A62EC[] = {
    33128, 0x10000, 2586, 65535,
};
s32 D_800A62FC[] = {
    0x17403, 0x10A1A, 65535,
};
s32 D_800A6308[] = {
    33128, 0x10A1A, 0, 65535,
};
s32 D_800A6318[] = {
    0x18168, 0x17038, 65535,
};
s32 D_800A6324[] = {
    33128, 0x10000, 0x10A1A, 65535,
};
s32 D_800A6334[] = {
    0x18168, 0x17038, 65535,
};
s32 D_800A6340[] = {
    0x18006, 65535,
};
s32 D_800A6348[] = {
    0x17031, 65535,
};
s32 D_800A6350[] = {
    32774, 0, 2580, 65535,
};
s32 D_800A6360[] = {
    0x10000, 65535,
};
s32 D_800A6368[] = {
    32774, 0x10000, 2580, 65535,
};
s32 D_800A6378[] = {
    0x17400, 0x10A14, 65535,
};
s32 D_800A6384[] = {
    0, 0x10A14, 32774, 65535,
};
s32 D_800A6394[] = {
    0x17031, 0x18006, 65535,
};
s32 D_800A63A0[] = {
    32774, 0x10000, 0x10A14, 65535,
};
s32 D_800A63B0[] = {
    0x18006, 0x17031, 65535,
};
s32 D_800A63BC[] = {
    0x18026, 65535,
};
s32 D_800A63C4[] = {
    0x17035, 65535,
};
s32 D_800A63CC[] = {
    32806, 0, 2583, 65535,
};
s32 D_800A63DC[] = {
    0x10000, 65535,
};
s32 D_800A63E4[] = {
    32806, 0x10000, 2583, 65535,
};
s32 D_800A63F4[] = {
    0x17402, 0x10A17, 65535,
};
s32 D_800A6400[] = {
    0, 0x10A17, 32806, 65535,
};
s32 D_800A6410[] = {
    0x17035, 0x18026, 65535,
};
s32 D_800A641C[] = {
    32806, 0x10000, 0x10A17, 65535,
};
s32 D_800A642C[] = {
    0x18026, 0x17035, 65535,
};
s32 D_800A6438[] = {
    0x18022, 65535,
};
s32 D_800A6440[] = {
    0x17033, 65535,
};
s32 D_800A6448[] = {
    32802, 0, 2581, 65535,
};
s32 D_800A6458[] = {
    0x10000, 65535,
};
s32 D_800A6460[] = {
    32802, 0x10000, 2581, 65535,
};
s32 D_800A6470[] = {
    0x17401, 0x10A15, 65535,
};
s32 D_800A647C[] = {
    0, 0x10A15, 32802, 65535,
};
s32 D_800A648C[] = {
    0x17033, 0x18022, 65535,
};
s32 D_800A6498[] = {
    32802, 0x10000, 0x10A15, 65535,
};
s32 D_800A64A8[] = {
    0x18022, 0x17033, 65535,
};
s32 D_800A64B4[] = {
    (s32)D_800A62C4, (s32)D_800A62CC, 233, (s32)D_800A62D4,
    (s32)D_800A62E4, 234, (s32)D_800A62EC, (s32)D_800A62FC,
    235, (s32)D_800A6308, (s32)D_800A6318, 236,
    (s32)D_800A6324, (s32)D_800A6334, 236, 0,
    0, 0,
};
s32 D_800A64FC[] = {
    (s32)D_800A6340, (s32)D_800A6348, 209, (s32)D_800A6350,
    (s32)D_800A6360, 210, (s32)D_800A6368, (s32)D_800A6378,
    211, (s32)D_800A6384, (s32)D_800A6394, 212,
    (s32)D_800A63A0, (s32)D_800A63B0, 212, 0,
    0, 0,
};
s32 D_800A6544[] = {
    (s32)D_800A63BC, (s32)D_800A63C4, 221, (s32)D_800A63CC,
    (s32)D_800A63DC, 222, (s32)D_800A63E4, (s32)D_800A63F4,
    223, (s32)D_800A6400, (s32)D_800A6410, 224,
    (s32)D_800A641C, (s32)D_800A642C, 224, 0,
    0, 0,
};
s32 D_800A658C[] = {
    (s32)D_800A6438, (s32)D_800A6440, 213, (s32)D_800A6448,
    (s32)D_800A6458, 214, (s32)D_800A6460, (s32)D_800A6470,
    215, (s32)D_800A647C, (s32)D_800A648C, 216,
    (s32)D_800A6498, (s32)D_800A64A8, 216, 0,
    0, 0,
};
s32 D_800A65D4[] = {
    0x17E05, 0x17E1E, 0x17095, 28689,
    65535,
};
s32 D_800A65E8[] = {
    0x17095, 28683, 0x17E04, 0x17E1F,
    65535,
};
s32 D_800A65FC[] = {
    0x17E04, 0x17E20, 0x17095, 28687,
    65535,
};
s32 D_800A6610[] = {
    0x17E04, 0x17E1E, 0x17095, 28684,
    65535,
};
s32 D_800A6624[] = {
    0x17E00, 8, 65535,
};
s32 D_800A6630[] = {
    0x17E04, 8, 65535,
};
s32 D_800A663C[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A6648[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A6654[] = {
    9, 0x17E20, 65535,
};
s32 D_800A6660[] = {
    (s32)D_800A65D4, (s32)D_800A64B4, 0x40064, 0x25800F0,
    1,
};
s32 D_800A6674[] = {
    (s32)D_800A65E8, (s32)D_800A64FC, 0x5007B, 0x25800F0,
    1,
};
s32 D_800A6688[] = {
    (s32)D_800A65FC, (s32)D_800A6544, 0x6007D, 0x25800F0,
    1,
};
s32 D_800A669C[] = {
    (s32)D_800A6610, (s32)D_800A658C, 0x7007E, 0x25800F0,
    1,
};
s32 D_800A66B0[] = {
    0, 0, 0x80146, 0,
    0,
};
s32 D_800A66C4[] = {
    (s32)D_800A6624, 0, 0x90148, 0xD001E0,
    1,
};
s32 D_800A66D8[] = {
    (s32)D_800A6630, 0, 0x90148, 0x1580190,
    1,
};
s32 D_800A66EC[] = {
    (s32)D_800A663C, 0, 0xA015F, 0x1900120,
    1,
};
s32 D_800A6700[] = {
    (s32)D_800A6648, 0, 0xA015F, 0x1E800F0,
    1,
};
s32 D_800A6714[] = {
    (s32)D_800A6654, 0, 0xA015F, 0x1100160,
    1,
};
s32 D_800A6728[] = {
    (s32)D_800A6660, (s32)D_800A6674, (s32)D_800A6688, (s32)D_800A669C,
    (s32)D_800A66B0, (s32)D_800A66C4, (s32)D_800A66D8, (s32)D_800A66EC,
    (s32)D_800A6700, (s32)D_800A6714, 0,
};
s32 D_800A6754[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A6768[] = {
    65535, 65535, 0x2EB0001, 0xA00240,
    5, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A6798[])(void) = {
    func_800A5FB0,
};
s32 D_800A679C[] = {
    140, 10, 0x60080000,
};
s32 D_800A67A8[] = {
    140, 10, 0x60080000,
};
s32 D_800A67B4[] = {
    140, 10, 0x60080000,
};
s32 D_800A67C0[] = {
    140, 10, 0x60080000,
};
s32 D_800A67CC[] = {
    141, 10, 0x60080000,
};
s32 D_800A67D8[] = {
    141, 10, 0x60080000,
};
s32 D_800A67E4[] = {
    141, 10, 0x60080000,
};
s32 D_800A67F0[] = {
    141, 10, 0x60080000,
};
s32 D_800A67FC[] = {
    3, (s32)D_800A679C, (s32)D_800A67A8, (s32)D_800A67B4,
    (s32)D_800A67C0, (s32)D_800A67CC, (s32)D_800A67D8, (s32)D_800A67E4,
    (s32)D_800A67F0,
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
    0, 0, 0x60040000,
};
s32 D_800A6850[] = {
    0, 0, 0x60040000,
};
s32 D_800A685C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6868[] = {
    0, 0, 0x60040000,
};
s32 D_800A6874[] = {
    0, 0, 0x60040000,
};
s32 D_800A6880[] = {
    0, (s32)D_800A6820, (s32)D_800A682C, (s32)D_800A6838,
    (s32)D_800A6844, (s32)D_800A6850, (s32)D_800A685C, (s32)D_800A6868,
    (s32)D_800A6874,
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
    0, 0, 0x60040000,
};
s32 D_800A6904[] = {
    0, (s32)D_800A68A4, (s32)D_800A68B0, (s32)D_800A68BC,
    (s32)D_800A68C8, (s32)D_800A68D4, (s32)D_800A68E0, (s32)D_800A68EC,
    (s32)D_800A68F8,
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
    0, 0, 0x60040000,
};
s32 D_800A6988[] = {
    0, (s32)D_800A6928, (s32)D_800A6934, (s32)D_800A6940,
    (s32)D_800A694C, (s32)D_800A6958, (s32)D_800A6964, (s32)D_800A6970,
    (s32)D_800A697C,
};
s32 D_800A69AC[] = {
    116, 10, 0x60080000,
};
s32 D_800A69B8[] = {
    116, 10, 0x60080000,
};
s32 D_800A69C4[] = {
    164, 10, 0x60080000,
};
s32 D_800A69D0[] = {
    164, 10, 0x60080000,
};
s32 D_800A69DC[] = {
    139, 10, 0x60080000,
};
s32 D_800A69E8[] = {
    139, 10, 0x60080000,
};
s32 D_800A69F4[] = {
    163, 10, 0x60080000,
};
s32 D_800A6A00[] = {
    163, 10, 0x60080000,
};
s32 D_800A6A0C[] = {
    3, (s32)D_800A69AC, (s32)D_800A69B8, (s32)D_800A69C4,
    (s32)D_800A69D0, (s32)D_800A69DC, (s32)D_800A69E8, (s32)D_800A69F4,
    (s32)D_800A6A00,
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
    0, 0, 0x60040000,
};
s32 D_800A6A60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A90[] = {
    0, (s32)D_800A6A30, (s32)D_800A6A3C, (s32)D_800A6A48,
    (s32)D_800A6A54, (s32)D_800A6A60, (s32)D_800A6A6C, (s32)D_800A6A78,
    (s32)D_800A6A84,
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
    0, 0, 0x60040000,
};
s32 D_800A6AE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B14[] = {
    0, (s32)D_800A6AB4, (s32)D_800A6AC0, (s32)D_800A6ACC,
    (s32)D_800A6AD8, (s32)D_800A6AE4, (s32)D_800A6AF0, (s32)D_800A6AFC,
    (s32)D_800A6B08,
};
s32 D_800A6B38[] = {
    301, 10, 0x60880000,
};
s32 D_800A6B44[] = {
    302, 10, 0x60880000,
};
s32 D_800A6B50[] = {
    304, 10, 0x60880000,
};
s32 D_800A6B5C[] = {
    311, 10, 0x60880000,
};
s32 D_800A6B68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B98[] = {
    0, (s32)D_800A6B38, (s32)D_800A6B44, (s32)D_800A6B50,
    (s32)D_800A6B5C, (s32)D_800A6B68, (s32)D_800A6B74, (s32)D_800A6B80,
    (s32)D_800A6B8C,
};
s32 D_800A6BBC[] = {
    162, 10, 0x60080000,
};
s32 D_800A6BC8[] = {
    162, 10, 0x60080000,
};
s32 D_800A6BD4[] = {
    162, 10, 0x60080000,
};
s32 D_800A6BE0[] = {
    162, 10, 0x60080000,
};
s32 D_800A6BEC[] = {
    135, 10, 0x60080000,
};
s32 D_800A6BF8[] = {
    135, 10, 0x60080000,
};
s32 D_800A6C04[] = {
    135, 10, 0x60080000,
};
s32 D_800A6C10[] = {
    135, 10, 0x60080000,
};
s32 D_800A6C1C[] = {
    3, (s32)D_800A6BBC, (s32)D_800A6BC8, (s32)D_800A6BD4,
    (s32)D_800A6BE0, (s32)D_800A6BEC, (s32)D_800A6BF8, (s32)D_800A6C04,
    (s32)D_800A6C10,
};
s32 D_800A6C40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CA0[] = {
    0, (s32)D_800A6C40, (s32)D_800A6C4C, (s32)D_800A6C58,
    (s32)D_800A6C64, (s32)D_800A6C70, (s32)D_800A6C7C, (s32)D_800A6C88,
    (s32)D_800A6C94,
};
s32 D_800A6CC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D24[] = {
    0, (s32)D_800A6CC4, (s32)D_800A6CD0, (s32)D_800A6CDC,
    (s32)D_800A6CE8, (s32)D_800A6CF4, (s32)D_800A6D00, (s32)D_800A6D0C,
    (s32)D_800A6D18,
};
s32 D_800A6D48[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D54[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D60[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D6C[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D78[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D84[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D90[] = {
    311, 10, 0x60880000,
};
s32 D_800A6D9C[] = {
    311, 10, 0x60880000,
};
s32 D_800A6DA8[] = {
    0, (s32)D_800A6D48, (s32)D_800A6D54, (s32)D_800A6D60,
    (s32)D_800A6D6C, (s32)D_800A6D78, (s32)D_800A6D84, (s32)D_800A6D90,
    (s32)D_800A6D9C,
};
s32 D_800A6DCC[] = {
    416, 1, 0, (s32)D_800A67FC,
    (s32)D_800A6880, (s32)D_800A6904, (s32)D_800A6988, 439,
    5, 0, (s32)D_800A6A0C, (s32)D_800A6A90,
    (s32)D_800A6B14, (s32)D_800A6B98, 445, 6,
    0, (s32)D_800A6C1C, (s32)D_800A6CA0, (s32)D_800A6D24,
    (s32)D_800A6DA8,
};
