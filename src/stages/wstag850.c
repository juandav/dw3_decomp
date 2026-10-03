#include "common.h"
#include "stage.h"
extern void (*D_800A5BE4[])(void);
void func_800A4DA8();
extern StagePoints *D_800A5108[];

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
        task->nextState(task);
        func_800A4CA8(D_800990B4.unk14, D_800A5108, GAME.unk44, GAME.unk46);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4E14(void *owner) {
    StageTask *task = createTask(func_800A4DA8, sizeof(StageTask), 0);

    task->owner = owner;
    D_800A5BE4[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag850", func_800A4E70);

void func_800A4E70();
extern StagePoint D_800A4FB0;
extern StagePoint D_800A4FC0;
extern StagePoint D_800A4FD0;
extern StagePoint D_800A4FE8;
extern StagePoint D_800A4FF8;
extern StagePoint D_800A5008;
extern StagePoint D_800A5020;
extern StagePoint D_800A5030;
extern StagePoint D_800A5040;
extern StagePoint D_800A5058;
extern StagePoint D_800A5068;
extern StagePoint D_800A5078;
extern StagePoint D_800A5090;
extern StagePoint D_800A50A0;
extern StagePoint D_800A50B0;
extern StagePoint D_800A50C8;
extern StagePoint D_800A50D8;
extern StagePoint D_800A50E8;
extern StagePoints D_800A4FE0;
extern StagePoints D_800A5018;
extern StagePoints D_800A5050;
extern StagePoints D_800A5088;
extern StagePoints D_800A50C0;
extern StagePoints D_800A50F8;
extern StagePoints D_800A5100;
extern s32 D_800A5128[];
extern s32 D_800A5134[];
extern s32 D_800A5140[];
extern s32 D_800A514C[];
extern s32 D_800A5158[];
extern s32 D_800A5164[];
extern s32 D_800A5170[];
extern s32 D_800A517C[];
extern s32 D_800A51AC[];
extern s32 D_800A51B8[];
extern s32 D_800A51C4[];
extern s32 D_800A51D0[];
extern s32 D_800A51DC[];
extern s32 D_800A51E8[];
extern s32 D_800A51F4[];
extern s32 D_800A5200[];
extern s32 D_800A5230[];
extern s32 D_800A523C[];
extern s32 D_800A5248[];
extern s32 D_800A5254[];
extern s32 D_800A5260[];
extern s32 D_800A526C[];
extern s32 D_800A5278[];
extern s32 D_800A5284[];
extern s32 D_800A52B4[];
extern s32 D_800A52C0[];
extern s32 D_800A52CC[];
extern s32 D_800A52D8[];
extern s32 D_800A52E4[];
extern s32 D_800A52F0[];
extern s32 D_800A52FC[];
extern s32 D_800A5308[];
extern s32 D_800A5338[];
extern s32 D_800A5344[];
extern s32 D_800A5350[];
extern s32 D_800A535C[];
extern s32 D_800A5368[];
extern s32 D_800A5374[];
extern s32 D_800A5380[];
extern s32 D_800A538C[];
extern s32 D_800A53BC[];
extern s32 D_800A53C8[];
extern s32 D_800A53D4[];
extern s32 D_800A53E0[];
extern s32 D_800A53EC[];
extern s32 D_800A53F8[];
extern s32 D_800A5404[];
extern s32 D_800A5410[];
extern s32 D_800A5440[];
extern s32 D_800A544C[];
extern s32 D_800A5458[];
extern s32 D_800A5464[];
extern s32 D_800A5470[];
extern s32 D_800A547C[];
extern s32 D_800A5488[];
extern s32 D_800A5494[];
extern s32 D_800A54C4[];
extern s32 D_800A54D0[];
extern s32 D_800A54DC[];
extern s32 D_800A54E8[];
extern s32 D_800A54F4[];
extern s32 D_800A5500[];
extern s32 D_800A550C[];
extern s32 D_800A5518[];
extern s32 D_800A5548[];
extern s32 D_800A5554[];
extern s32 D_800A5560[];
extern s32 D_800A556C[];
extern s32 D_800A5578[];
extern s32 D_800A5584[];
extern s32 D_800A5590[];
extern s32 D_800A559C[];
extern s32 D_800A55CC[];
extern s32 D_800A55D8[];
extern s32 D_800A55E4[];
extern s32 D_800A55F0[];
extern s32 D_800A55FC[];
extern s32 D_800A5608[];
extern s32 D_800A5614[];
extern s32 D_800A5620[];
extern s32 D_800A5650[];
extern s32 D_800A565C[];
extern s32 D_800A5668[];
extern s32 D_800A5674[];
extern s32 D_800A5680[];
extern s32 D_800A568C[];
extern s32 D_800A5698[];
extern s32 D_800A56A4[];
extern s32 D_800A56D4[];
extern s32 D_800A56E0[];
extern s32 D_800A56EC[];
extern s32 D_800A56F8[];
extern s32 D_800A5704[];
extern s32 D_800A5710[];
extern s32 D_800A571C[];
extern s32 D_800A5728[];
extern s32 D_800A5758[];
extern s32 D_800A5764[];
extern s32 D_800A5770[];
extern s32 D_800A577C[];
extern s32 D_800A5788[];
extern s32 D_800A5794[];
extern s32 D_800A57A0[];
extern s32 D_800A57AC[];
extern s32 D_800A57DC[];
extern s32 D_800A57E8[];
extern s32 D_800A57F4[];
extern s32 D_800A5800[];
extern s32 D_800A580C[];
extern s32 D_800A5818[];
extern s32 D_800A5824[];
extern s32 D_800A5830[];
extern s32 D_800A5860[];
extern s32 D_800A586C[];
extern s32 D_800A5878[];
extern s32 D_800A5884[];
extern s32 D_800A5890[];
extern s32 D_800A589C[];
extern s32 D_800A58A8[];
extern s32 D_800A58B4[];
extern s32 D_800A58E4[];
extern s32 D_800A58F0[];
extern s32 D_800A58FC[];
extern s32 D_800A5908[];
extern s32 D_800A5914[];
extern s32 D_800A5920[];
extern s32 D_800A592C[];
extern s32 D_800A5938[];
extern s32 D_800A5188[];
extern s32 D_800A520C[];
extern s32 D_800A5290[];
extern s32 D_800A5314[];
extern s32 D_800A5398[];
extern s32 D_800A541C[];
extern s32 D_800A54A0[];
extern s32 D_800A5524[];
extern s32 D_800A55A8[];
extern s32 D_800A562C[];
extern s32 D_800A56B0[];
extern s32 D_800A5734[];
extern s32 D_800A57B8[];
extern s32 D_800A583C[];
extern s32 D_800A58C0[];
extern s32 D_800A5944[];
extern s32 D_800A5A48[];

StagePoint D_800A4FB0 = { 0x2E4, 1, 1, 0x340, 160, 1, NULL };
StagePoint D_800A4FC0 = { 0x2E6, 1, 1, 160, 0x150, 5, &D_800A4FB0 };
StagePoint D_800A4FD0 = { 0x21D, 0, 0, 0x328, 0x424, 0, &D_800A4FC0 };
StagePoints D_800A4FE0 = { 1, 1, &D_800A4FD0 };
StagePoint D_800A4FE8 = { 0x2E7, 1, 1, 0x250, 232, 1, NULL };
StagePoint D_800A4FF8 = { 0x2E4, 1, 1, 192, 0x180, 5, &D_800A4FE8 };
StagePoint D_800A5008 = { 0x234, 0, 0, 0x320, 0x1C8, 0, &D_800A4FF8 };
StagePoints D_800A5018 = { 1, 2, &D_800A5008 };
StagePoint D_800A5020 = { 0x2E2, 4, 1, 0x330, 248, 1, NULL };
StagePoint D_800A5030 = { 0x2E4, 4, 1, 192, 0x180, 5, &D_800A5020 };
StagePoint D_800A5040 = { 0x23B, 0, 0, 0x360, 0x12C, 0, &D_800A5030 };
StagePoints D_800A5050 = { 4, 1, &D_800A5040 };
StagePoint D_800A5058 = { 0x2E4, 11, 1, 0x340, 160, 1, NULL };
StagePoint D_800A5068 = { 0x2E6, 11, 1, 160, 0x150, 5, &D_800A5058 };
StagePoint D_800A5078 = { 0x28C, 0, 0, 0x328, 0x424, 0, &D_800A5068 };
StagePoints D_800A5088 = { 11, 1, &D_800A5078 };
StagePoint D_800A5090 = { 0x2E7, 11, 1, 0x250, 232, 1, NULL };
StagePoint D_800A50A0 = { 0x2E4, 11, 1, 192, 0x180, 5, &D_800A5090 };
StagePoint D_800A50B0 = { 0x2A2, 0, 0, 0x320, 0x1C8, 0, &D_800A50A0 };
StagePoints D_800A50C0 = { 11, 2, &D_800A50B0 };
StagePoint D_800A50C8 = { 0x2E2, 14, 1, 0x330, 248, 1, NULL };
StagePoint D_800A50D8 = { 0x2E4, 14, 1, 192, 0x180, 5, &D_800A50C8 };
StagePoint D_800A50E8 = { 0x2A8, 0, 0, 0x360, 0x12C, 0, &D_800A50D8 };
StagePoints D_800A50F8 = { 14, 1, &D_800A50E8 };
StagePoints D_800A5100 = { 0, 0, &D_800A4FD0 };
StagePoints *D_800A5108[] = {
    &D_800A4FE0, &D_800A5018, &D_800A5050, &D_800A5088,
    &D_800A50C0, &D_800A50F8, &D_800A5100, NULL,
};
s32 D_800A5128[] = {
    61, 11, 0x60080000,
};
s32 D_800A5134[] = {
    61, 11, 0x60080000,
};
s32 D_800A5140[] = {
    61, 11, 0x60080000,
};
s32 D_800A514C[] = {
    61, 11, 0x60080000,
};
s32 D_800A5158[] = {
    62, 11, 0x60080000,
};
s32 D_800A5164[] = {
    62, 11, 0x60080000,
};
s32 D_800A5170[] = {
    62, 11, 0x60080000,
};
s32 D_800A517C[] = {
    62, 11, 0x60080000,
};
s32 D_800A5188[] = {
    2, (s32)D_800A5128, (s32)D_800A5134, (s32)D_800A5140,
    (s32)D_800A514C, (s32)D_800A5158, (s32)D_800A5164, (s32)D_800A5170,
    (s32)D_800A517C,
};
s32 D_800A51AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A51B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A51D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A51DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A51E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A51F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5200[] = {
    0, 0, 0x60040000,
};
s32 D_800A520C[] = {
    0, (s32)D_800A51AC, (s32)D_800A51B8, (s32)D_800A51C4,
    (s32)D_800A51D0, (s32)D_800A51DC, (s32)D_800A51E8, (s32)D_800A51F4,
    (s32)D_800A5200,
};
s32 D_800A5230[] = {
    0, 0, 0x60040000,
};
s32 D_800A523C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5248[] = {
    0, 0, 0x60040000,
};
s32 D_800A5254[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5230, (s32)D_800A523C, (s32)D_800A5248,
    (s32)D_800A5254, (s32)D_800A5260, (s32)D_800A526C, (s32)D_800A5278,
    (s32)D_800A5284,
};
s32 D_800A52B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52D8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A52B4, (s32)D_800A52C0, (s32)D_800A52CC,
    (s32)D_800A52D8, (s32)D_800A52E4, (s32)D_800A52F0, (s32)D_800A52FC,
    (s32)D_800A5308,
};
s32 D_800A5338[] = {
    61, 11, 0x60080000,
};
s32 D_800A5344[] = {
    61, 11, 0x60080000,
};
s32 D_800A5350[] = {
    61, 11, 0x60080000,
};
s32 D_800A535C[] = {
    61, 11, 0x60080000,
};
s32 D_800A5368[] = {
    62, 11, 0x60080000,
};
s32 D_800A5374[] = {
    62, 11, 0x60080000,
};
s32 D_800A5380[] = {
    62, 11, 0x60080000,
};
s32 D_800A538C[] = {
    62, 11, 0x60080000,
};
s32 D_800A5398[] = {
    2, (s32)D_800A5338, (s32)D_800A5344, (s32)D_800A5350,
    (s32)D_800A535C, (s32)D_800A5368, (s32)D_800A5374, (s32)D_800A5380,
    (s32)D_800A538C,
};
s32 D_800A53BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A53E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5404[] = {
    0, 0, 0x60040000,
};
s32 D_800A5410[] = {
    0, 0, 0x60040000,
};
s32 D_800A541C[] = {
    0, (s32)D_800A53BC, (s32)D_800A53C8, (s32)D_800A53D4,
    (s32)D_800A53E0, (s32)D_800A53EC, (s32)D_800A53F8, (s32)D_800A5404,
    (s32)D_800A5410,
};
s32 D_800A5440[] = {
    0, 0, 0x60040000,
};
s32 D_800A544C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5458[] = {
    0, 0, 0x60040000,
};
s32 D_800A5464[] = {
    0, 0, 0x60040000,
};
s32 D_800A5470[] = {
    0, 0, 0x60040000,
};
s32 D_800A547C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5488[] = {
    0, 0, 0x60040000,
};
s32 D_800A5494[] = {
    0, 0, 0x60040000,
};
s32 D_800A54A0[] = {
    0, (s32)D_800A5440, (s32)D_800A544C, (s32)D_800A5458,
    (s32)D_800A5464, (s32)D_800A5470, (s32)D_800A547C, (s32)D_800A5488,
    (s32)D_800A5494,
};
s32 D_800A54C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A54D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A54E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A54F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5500[] = {
    0, 0, 0x60040000,
};
s32 D_800A550C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5518[] = {
    0, 0, 0x60040000,
};
s32 D_800A5524[] = {
    0, (s32)D_800A54C4, (s32)D_800A54D0, (s32)D_800A54DC,
    (s32)D_800A54E8, (s32)D_800A54F4, (s32)D_800A5500, (s32)D_800A550C,
    (s32)D_800A5518,
};
s32 D_800A5548[] = {
    103, 11, 0x60080000,
};
s32 D_800A5554[] = {
    103, 11, 0x60080000,
};
s32 D_800A5560[] = {
    103, 11, 0x60080000,
};
s32 D_800A556C[] = {
    103, 11, 0x60080000,
};
s32 D_800A5578[] = {
    103, 11, 0x60080000,
};
s32 D_800A5584[] = {
    103, 11, 0x60080000,
};
s32 D_800A5590[] = {
    103, 11, 0x60080000,
};
s32 D_800A559C[] = {
    103, 11, 0x60080000,
};
s32 D_800A55A8[] = {
    2, (s32)D_800A5548, (s32)D_800A5554, (s32)D_800A5560,
    (s32)D_800A556C, (s32)D_800A5578, (s32)D_800A5584, (s32)D_800A5590,
    (s32)D_800A559C,
};
s32 D_800A55CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A55D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A55E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A55F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A55FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5608[] = {
    0, 0, 0x60040000,
};
s32 D_800A5614[] = {
    0, 0, 0x60040000,
};
s32 D_800A5620[] = {
    0, 0, 0x60040000,
};
s32 D_800A562C[] = {
    0, (s32)D_800A55CC, (s32)D_800A55D8, (s32)D_800A55E4,
    (s32)D_800A55F0, (s32)D_800A55FC, (s32)D_800A5608, (s32)D_800A5614,
    (s32)D_800A5620,
};
s32 D_800A5650[] = {
    0, 0, 0x60040000,
};
s32 D_800A565C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5668[] = {
    0, 0, 0x60040000,
};
s32 D_800A5674[] = {
    0, 0, 0x60040000,
};
s32 D_800A5680[] = {
    0, 0, 0x60040000,
};
s32 D_800A568C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5698[] = {
    0, 0, 0x60040000,
};
s32 D_800A56A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A56B0[] = {
    0, (s32)D_800A5650, (s32)D_800A565C, (s32)D_800A5668,
    (s32)D_800A5674, (s32)D_800A5680, (s32)D_800A568C, (s32)D_800A5698,
    (s32)D_800A56A4,
};
s32 D_800A56D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A56E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A56EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A56F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5704[] = {
    0, 0, 0x60040000,
};
s32 D_800A5710[] = {
    0, 0, 0x60040000,
};
s32 D_800A571C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5728[] = {
    0, 0, 0x60040000,
};
s32 D_800A5734[] = {
    0, (s32)D_800A56D4, (s32)D_800A56E0, (s32)D_800A56EC,
    (s32)D_800A56F8, (s32)D_800A5704, (s32)D_800A5710, (s32)D_800A571C,
    (s32)D_800A5728,
};
s32 D_800A5758[] = {
    103, 11, 0x60080000,
};
s32 D_800A5764[] = {
    103, 11, 0x60080000,
};
s32 D_800A5770[] = {
    103, 11, 0x60080000,
};
s32 D_800A577C[] = {
    103, 11, 0x60080000,
};
s32 D_800A5788[] = {
    103, 11, 0x60080000,
};
s32 D_800A5794[] = {
    103, 11, 0x60080000,
};
s32 D_800A57A0[] = {
    103, 11, 0x60080000,
};
s32 D_800A57AC[] = {
    103, 11, 0x60080000,
};
s32 D_800A57B8[] = {
    2, (s32)D_800A5758, (s32)D_800A5764, (s32)D_800A5770,
    (s32)D_800A577C, (s32)D_800A5788, (s32)D_800A5794, (s32)D_800A57A0,
    (s32)D_800A57AC,
};
s32 D_800A57DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A57E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A57F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5800[] = {
    0, 0, 0x60040000,
};
s32 D_800A580C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5818[] = {
    0, 0, 0x60040000,
};
s32 D_800A5824[] = {
    0, 0, 0x60040000,
};
s32 D_800A5830[] = {
    0, 0, 0x60040000,
};
s32 D_800A583C[] = {
    0, (s32)D_800A57DC, (s32)D_800A57E8, (s32)D_800A57F4,
    (s32)D_800A5800, (s32)D_800A580C, (s32)D_800A5818, (s32)D_800A5824,
    (s32)D_800A5830,
};
s32 D_800A5860[] = {
    0, 0, 0x60040000,
};
s32 D_800A586C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5878[] = {
    0, 0, 0x60040000,
};
s32 D_800A5884[] = {
    0, 0, 0x60040000,
};
s32 D_800A5890[] = {
    0, 0, 0x60040000,
};
s32 D_800A589C[] = {
    0, 0, 0x60040000,
};
s32 D_800A58A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A58B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A58C0[] = {
    0, (s32)D_800A5860, (s32)D_800A586C, (s32)D_800A5878,
    (s32)D_800A5884, (s32)D_800A5890, (s32)D_800A589C, (s32)D_800A58A8,
    (s32)D_800A58B4,
};
s32 D_800A58E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A58F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A58FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5908[] = {
    0, 0, 0x60040000,
};
s32 D_800A5914[] = {
    0, 0, 0x60040000,
};
s32 D_800A5920[] = {
    0, 0, 0x60040000,
};
s32 D_800A592C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5938[] = {
    0, 0, 0x60040000,
};
s32 D_800A5944[] = {
    0, (s32)D_800A58E4, (s32)D_800A58F0, (s32)D_800A58FC,
    (s32)D_800A5908, (s32)D_800A5914, (s32)D_800A5920, (s32)D_800A592C,
    (s32)D_800A5938,
};
s32 D_800A5968[] = {
    175, 1, 0, (s32)D_800A5188,
    (s32)D_800A520C, (s32)D_800A5290, (s32)D_800A5314, 185,
    4, 0, (s32)D_800A5398, (s32)D_800A541C,
    (s32)D_800A54A0, (s32)D_800A5524, 203, 11,
    0, (s32)D_800A55A8, (s32)D_800A562C, (s32)D_800A56B0,
    (s32)D_800A5734, 213, 14, 0,
    (s32)D_800A57B8, (s32)D_800A583C, (s32)D_800A58C0, (s32)D_800A5944,
};
s32 D_800A59D8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1CF0170, 0xCF00C0, 0x1FF0160,
};
s32 D_800A5A48[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A5A5C[] = {
    (s32)D_800A5A48, 0,
};
s32 D_800A5A64[] = {
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
s32 D_800A5B84[] = {
    65535, 65535, 0x2E50001, 0x1200240,
    4, 0, 65535, 65535,
    0x2E50001, 0xD803B0, 5, 0,
    65535, 65535, 0x2E50001, 0x12000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5BE4[])(void) = {
    func_800A4E70,
};
