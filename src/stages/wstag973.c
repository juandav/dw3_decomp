#include "common.h"
#include "stage.h"
void func_800A5EE0();
extern void (*D_800A6E08[])(void);
extern StagePoints *D_800A6730[];

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
        func_800A5DE0(D_800990B4.unk14, D_800A6730, GAME.unk44, GAME.unk46);
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
    D_800A6E08[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag973", func_800A5FB0);

void func_800A5FB0();
extern StagePoint D_800A60D8;
extern StagePoint D_800A60E8;
extern StagePoint D_800A60F8;
extern StagePoint D_800A6110;
extern StagePoint D_800A6120;
extern StagePoint D_800A6130;
extern StagePoint D_800A6148;
extern StagePoint D_800A6158;
extern StagePoint D_800A6168;
extern StagePoint D_800A6180;
extern StagePoint D_800A6190;
extern StagePoint D_800A61A0;
extern StagePoint D_800A61B8;
extern StagePoint D_800A61C8;
extern StagePoint D_800A61D8;
extern StagePoint D_800A61F0;
extern StagePoint D_800A6200;
extern StagePoint D_800A6210;
extern StagePoint D_800A6228;
extern StagePoint D_800A6238;
extern StagePoint D_800A6248;
extern StagePoint D_800A6260;
extern StagePoint D_800A6270;
extern StagePoint D_800A6280;
extern StagePoint D_800A6298;
extern StagePoint D_800A62A8;
extern StagePoint D_800A62B8;
extern StagePoint D_800A62D0;
extern StagePoint D_800A62E0;
extern StagePoint D_800A62F0;
extern StagePoint D_800A6308;
extern StagePoint D_800A6318;
extern StagePoint D_800A6328;
extern StagePoint D_800A6340;
extern StagePoint D_800A6350;
extern StagePoint D_800A6360;
extern StagePoint D_800A6378;
extern StagePoint D_800A6388;
extern StagePoint D_800A6398;
extern StagePoint D_800A63B0;
extern StagePoint D_800A63C0;
extern StagePoint D_800A63D0;
extern StagePoint D_800A63E8;
extern StagePoint D_800A63F8;
extern StagePoint D_800A6408;
extern StagePoint D_800A6420;
extern StagePoint D_800A6430;
extern StagePoint D_800A6440;
extern StagePoint D_800A6458;
extern StagePoint D_800A6468;
extern StagePoint D_800A6478;
extern StagePoint D_800A6490;
extern StagePoint D_800A64A0;
extern StagePoint D_800A64B0;
extern StagePoint D_800A64C8;
extern StagePoint D_800A64D8;
extern StagePoint D_800A64E8;
extern StagePoint D_800A6500;
extern StagePoint D_800A6510;
extern StagePoint D_800A6520;
extern StagePoint D_800A6538;
extern StagePoint D_800A6548;
extern StagePoint D_800A6558;
extern StagePoint D_800A6570;
extern StagePoint D_800A6580;
extern StagePoint D_800A6590;
extern StagePoint D_800A65A8;
extern StagePoint D_800A65B8;
extern StagePoint D_800A65C8;
extern StagePoint D_800A65E0;
extern StagePoint D_800A65F0;
extern StagePoint D_800A6600;
extern StagePoint D_800A6618;
extern StagePoint D_800A6628;
extern StagePoint D_800A6638;
extern StagePoint D_800A6650;
extern StagePoint D_800A6660;
extern StagePoint D_800A6670;
extern StagePoint D_800A6688;
extern StagePoint D_800A6698;
extern StagePoint D_800A66A8;
extern StagePoint D_800A66C0;
extern StagePoint D_800A66D0;
extern StagePoint D_800A66E0;
extern StagePoint D_800A66F8;
extern StagePoint D_800A6708;
extern StagePoint D_800A6718;
extern StagePoints D_800A6108;
extern StagePoints D_800A6140;
extern StagePoints D_800A6178;
extern StagePoints D_800A61B0;
extern StagePoints D_800A61E8;
extern StagePoints D_800A6220;
extern StagePoints D_800A6258;
extern StagePoints D_800A6290;
extern StagePoints D_800A62C8;
extern StagePoints D_800A6300;
extern StagePoints D_800A6338;
extern StagePoints D_800A6370;
extern StagePoints D_800A63A8;
extern StagePoints D_800A63E0;
extern StagePoints D_800A6418;
extern StagePoints D_800A6450;
extern StagePoints D_800A6488;
extern StagePoints D_800A64C0;
extern StagePoints D_800A64F8;
extern StagePoints D_800A6530;
extern StagePoints D_800A6568;
extern StagePoints D_800A65A0;
extern StagePoints D_800A65D8;
extern StagePoints D_800A6610;
extern StagePoints D_800A6648;
extern StagePoints D_800A6680;
extern StagePoints D_800A66B8;
extern StagePoints D_800A66F0;
extern StagePoints D_800A6728;
extern s32 D_800A6888[];
extern s32 D_800A6894[];
extern s32 D_800A68A0[];
extern s32 D_800A68AC[];
extern s32 D_800A68B8[];
extern s32 D_800A68C0[];
extern s32 D_800A68C8[];
extern s32 D_800A68D0[];
extern s32 D_800A68DC[];
extern s32 D_800A68E4[];
extern s32 D_800A68EC[];
extern s32 D_800A68F4[];
extern s32 D_800A6900[];
extern s32 D_800A6908[];
extern s32 D_800A6910[];
extern s32 D_800A6918[];
extern s32 D_800A6924[];
extern s32 D_800A692C[];
extern s32 D_800A6934[];
extern s32 D_800A693C[];
extern s32 D_800A6A38[];
extern s32 D_800A6948[];
extern s32 D_800A6A48[];
extern s32 D_800A6960[];
extern s32 D_800A6A58[];
extern s32 D_800A6978[];
extern s32 D_800A6A68[];
extern s32 D_800A6990[];
extern s32 D_800A6A7C[];
extern s32 D_800A6A8C[];
extern s32 D_800A6A9C[];
extern s32 D_800A6AAC[];
extern s32 D_800A6ABC[];
extern s32 D_800A6ACC[];
extern s32 D_800A6AD8[];
extern s32 D_800A6AE4[];
extern s32 D_800A6AF0[];
extern s32 D_800A6B00[];
extern s32 D_800A6B10[];
extern s32 D_800A6B20[];
extern s32 D_800A6B30[];
extern s32 D_800A6B40[];
extern s32 D_800A69A8[];
extern s32 D_800A6B50[];
extern s32 D_800A69CC[];
extern s32 D_800A6B60[];
extern s32 D_800A69F0[];
extern s32 D_800A6B70[];
extern s32 D_800A6A14[];
extern s32 D_800A6B80[];
extern s32 D_800A6B94[];
extern s32 D_800A6BA8[];
extern s32 D_800A6BBC[];
extern s32 D_800A6BD0[];
extern s32 D_800A6BE4[];
extern s32 D_800A6BF8[];
extern s32 D_800A6C0C[];
extern s32 D_800A6C20[];
extern s32 D_800A6C34[];
extern s32 D_800A6C48[];
extern s32 D_800A6C5C[];
extern s32 D_800A6C70[];
extern s32 D_800A6C84[];
extern s32 D_800A6C98[];
extern s32 D_800A6CAC[];
extern s32 D_800A6CC0[];
extern s32 D_800A6CD4[];
extern s32 D_800A6CE8[];
extern s32 D_800A6CFC[];
extern s32 D_800A6D10[];
extern s32 D_800A6D24[];
extern s32 D_800A6E0C[];
extern s32 D_800A6E18[];
extern s32 D_800A6E24[];
extern s32 D_800A6E30[];
extern s32 D_800A6E3C[];
extern s32 D_800A6E48[];
extern s32 D_800A6E54[];
extern s32 D_800A6E60[];
extern s32 D_800A6E90[];
extern s32 D_800A6E9C[];
extern s32 D_800A6EA8[];
extern s32 D_800A6EB4[];
extern s32 D_800A6EC0[];
extern s32 D_800A6ECC[];
extern s32 D_800A6ED8[];
extern s32 D_800A6EE4[];
extern s32 D_800A6F14[];
extern s32 D_800A6F20[];
extern s32 D_800A6F2C[];
extern s32 D_800A6F38[];
extern s32 D_800A6F44[];
extern s32 D_800A6F50[];
extern s32 D_800A6F5C[];
extern s32 D_800A6F68[];
extern s32 D_800A6F98[];
extern s32 D_800A6FA4[];
extern s32 D_800A6FB0[];
extern s32 D_800A6FBC[];
extern s32 D_800A6FC8[];
extern s32 D_800A6FD4[];
extern s32 D_800A6FE0[];
extern s32 D_800A6FEC[];
extern s32 D_800A701C[];
extern s32 D_800A7028[];
extern s32 D_800A7034[];
extern s32 D_800A7040[];
extern s32 D_800A704C[];
extern s32 D_800A7058[];
extern s32 D_800A7064[];
extern s32 D_800A7070[];
extern s32 D_800A70A0[];
extern s32 D_800A70AC[];
extern s32 D_800A70B8[];
extern s32 D_800A70C4[];
extern s32 D_800A70D0[];
extern s32 D_800A70DC[];
extern s32 D_800A70E8[];
extern s32 D_800A70F4[];
extern s32 D_800A7124[];
extern s32 D_800A7130[];
extern s32 D_800A713C[];
extern s32 D_800A7148[];
extern s32 D_800A7154[];
extern s32 D_800A7160[];
extern s32 D_800A716C[];
extern s32 D_800A7178[];
extern s32 D_800A71A8[];
extern s32 D_800A71B4[];
extern s32 D_800A71C0[];
extern s32 D_800A71CC[];
extern s32 D_800A71D8[];
extern s32 D_800A71E4[];
extern s32 D_800A71F0[];
extern s32 D_800A71FC[];
extern s32 D_800A722C[];
extern s32 D_800A7238[];
extern s32 D_800A7244[];
extern s32 D_800A7250[];
extern s32 D_800A725C[];
extern s32 D_800A7268[];
extern s32 D_800A7274[];
extern s32 D_800A7280[];
extern s32 D_800A72B0[];
extern s32 D_800A72BC[];
extern s32 D_800A72C8[];
extern s32 D_800A72D4[];
extern s32 D_800A72E0[];
extern s32 D_800A72EC[];
extern s32 D_800A72F8[];
extern s32 D_800A7304[];
extern s32 D_800A7334[];
extern s32 D_800A7340[];
extern s32 D_800A734C[];
extern s32 D_800A7358[];
extern s32 D_800A7364[];
extern s32 D_800A7370[];
extern s32 D_800A737C[];
extern s32 D_800A7388[];
extern s32 D_800A73B8[];
extern s32 D_800A73C4[];
extern s32 D_800A73D0[];
extern s32 D_800A73DC[];
extern s32 D_800A73E8[];
extern s32 D_800A73F4[];
extern s32 D_800A7400[];
extern s32 D_800A740C[];
extern s32 D_800A743C[];
extern s32 D_800A7448[];
extern s32 D_800A7454[];
extern s32 D_800A7460[];
extern s32 D_800A746C[];
extern s32 D_800A7478[];
extern s32 D_800A7484[];
extern s32 D_800A7490[];
extern s32 D_800A74C0[];
extern s32 D_800A74CC[];
extern s32 D_800A74D8[];
extern s32 D_800A74E4[];
extern s32 D_800A74F0[];
extern s32 D_800A74FC[];
extern s32 D_800A7508[];
extern s32 D_800A7514[];
extern s32 D_800A7544[];
extern s32 D_800A7550[];
extern s32 D_800A755C[];
extern s32 D_800A7568[];
extern s32 D_800A7574[];
extern s32 D_800A7580[];
extern s32 D_800A758C[];
extern s32 D_800A7598[];
extern s32 D_800A75C8[];
extern s32 D_800A75D4[];
extern s32 D_800A75E0[];
extern s32 D_800A75EC[];
extern s32 D_800A75F8[];
extern s32 D_800A7604[];
extern s32 D_800A7610[];
extern s32 D_800A761C[];
extern s32 D_800A764C[];
extern s32 D_800A7658[];
extern s32 D_800A7664[];
extern s32 D_800A7670[];
extern s32 D_800A767C[];
extern s32 D_800A7688[];
extern s32 D_800A7694[];
extern s32 D_800A76A0[];
extern s32 D_800A76D0[];
extern s32 D_800A76DC[];
extern s32 D_800A76E8[];
extern s32 D_800A76F4[];
extern s32 D_800A7700[];
extern s32 D_800A770C[];
extern s32 D_800A7718[];
extern s32 D_800A7724[];
extern s32 D_800A7754[];
extern s32 D_800A7760[];
extern s32 D_800A776C[];
extern s32 D_800A7778[];
extern s32 D_800A7784[];
extern s32 D_800A7790[];
extern s32 D_800A779C[];
extern s32 D_800A77A8[];
extern s32 D_800A77D8[];
extern s32 D_800A77E4[];
extern s32 D_800A77F0[];
extern s32 D_800A77FC[];
extern s32 D_800A7808[];
extern s32 D_800A7814[];
extern s32 D_800A7820[];
extern s32 D_800A782C[];
extern s32 D_800A785C[];
extern s32 D_800A7868[];
extern s32 D_800A7874[];
extern s32 D_800A7880[];
extern s32 D_800A788C[];
extern s32 D_800A7898[];
extern s32 D_800A78A4[];
extern s32 D_800A78B0[];
extern s32 D_800A78E0[];
extern s32 D_800A78EC[];
extern s32 D_800A78F8[];
extern s32 D_800A7904[];
extern s32 D_800A7910[];
extern s32 D_800A791C[];
extern s32 D_800A7928[];
extern s32 D_800A7934[];
extern s32 D_800A7964[];
extern s32 D_800A7970[];
extern s32 D_800A797C[];
extern s32 D_800A7988[];
extern s32 D_800A7994[];
extern s32 D_800A79A0[];
extern s32 D_800A79AC[];
extern s32 D_800A79B8[];
extern s32 D_800A79E8[];
extern s32 D_800A79F4[];
extern s32 D_800A7A00[];
extern s32 D_800A7A0C[];
extern s32 D_800A7A18[];
extern s32 D_800A7A24[];
extern s32 D_800A7A30[];
extern s32 D_800A7A3C[];
extern s32 D_800A6E6C[];
extern s32 D_800A6EF0[];
extern s32 D_800A6F74[];
extern s32 D_800A6FF8[];
extern s32 D_800A707C[];
extern s32 D_800A7100[];
extern s32 D_800A7184[];
extern s32 D_800A7208[];
extern s32 D_800A728C[];
extern s32 D_800A7310[];
extern s32 D_800A7394[];
extern s32 D_800A7418[];
extern s32 D_800A749C[];
extern s32 D_800A7520[];
extern s32 D_800A75A4[];
extern s32 D_800A7628[];
extern s32 D_800A76AC[];
extern s32 D_800A7730[];
extern s32 D_800A77B4[];
extern s32 D_800A7838[];
extern s32 D_800A78BC[];
extern s32 D_800A7940[];
extern s32 D_800A79C4[];
extern s32 D_800A7A48[];

StagePoint D_800A60D8 = { 0x2EB, 1, 2, 0x240, 160, 1, NULL };
StagePoint D_800A60E8 = { 0x2EE, 1, 1, 0x130, 200, 1, &D_800A60D8 };
StagePoint D_800A60F8 = { 0x2EC, 1, 1, 240, 0x1D8, 5, &D_800A60E8 };
StagePoints D_800A6108 = { 1, 1, &D_800A60F8 };
StagePoint D_800A6110 = { 0x2EB, 1, 3, 0x240, 160, 1, NULL };
StagePoint D_800A6120 = { 0x2EC, 1, 2, 0x3B0, 120, 1, &D_800A6110 };
StagePoint D_800A6130 = { 0x2EC, 1, 3, 240, 0x1D8, 5, &D_800A6120 };
StagePoints D_800A6140 = { 1, 2, &D_800A6130 };
StagePoint D_800A6148 = { 0x2EC, 1, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A6158 = { 0x2EC, 1, 4, 0x3B0, 120, 1, &D_800A6148 };
StagePoint D_800A6168 = { 0x2EA, 1, 1, 224, 0x200, 5, &D_800A6158 };
StagePoints D_800A6178 = { 1, 3, &D_800A6168 };
StagePoint D_800A6180 = { 0x2EC, 1, 5, 0x3B0, 120, 1, NULL };
StagePoint D_800A6190 = { 0x2EE, 1, 3, 0x130, 200, 1, &D_800A6180 };
StagePoint D_800A61A0 = { 0x2EA, 1, 2, 224, 0x200, 5, &D_800A6190 };
StagePoints D_800A61B0 = { 1, 4, &D_800A61A0 };
StagePoint D_800A61B8 = { 0x2EB, 1, 5, 0x240, 160, 1, NULL };
StagePoint D_800A61C8 = { 0x2EE, 1, 4, 0x130, 200, 1, &D_800A61B8 };
StagePoint D_800A61D8 = { 0x2EC, 1, 6, 240, 0x1D8, 5, &D_800A61C8 };
StagePoints D_800A61E8 = { 1, 5, &D_800A61D8 };
StagePoint D_800A61F0 = { 0x2EE, 2, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6200 = { 0x2EE, 2, 3, 0x130, 200, 1, &D_800A61F0 };
StagePoint D_800A6210 = { 0x2EE, 2, 1, 224, 0x240, 5, &D_800A6200 };
StagePoints D_800A6220 = { 2, 1, &D_800A6210 };
StagePoint D_800A6228 = { 0x2EE, 2, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6238 = { 0x2EE, 2, 4, 0x130, 200, 1, &D_800A6228 };
StagePoint D_800A6248 = { 0x2EA, 2, 3, 224, 0x200, 5, &D_800A6238 };
StagePoints D_800A6258 = { 2, 2, &D_800A6248 };
StagePoint D_800A6260 = { 0x2EE, 2, 5, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6270 = { 0x2ED, 2, 4, 0x3A0, 128, 1, &D_800A6260 };
StagePoint D_800A6280 = { 0x2EE, 2, 2, 224, 0x240, 5, &D_800A6270 };
StagePoints D_800A6290 = { 2, 3, &D_800A6280 };
StagePoint D_800A6298 = { 0x2EE, 2, 7, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A62A8 = { 0x2EE, 2, 8, 0x130, 200, 1, &D_800A6298 };
StagePoint D_800A62B8 = { 0x2ED, 2, 3, 0x350, 0x1F8, 5, &D_800A62A8 };
StagePoints D_800A62C8 = { 2, 4, &D_800A62B8 };
StagePoint D_800A62D0 = { 0x2EC, 3, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A62E0 = { 0x2ED, 3, 2, 0x3A0, 128, 1, &D_800A62D0 };
StagePoint D_800A62F0 = { 0x2EC, 3, 1, 240, 0x1D8, 5, &D_800A62E0 };
StagePoints D_800A6300 = { 3, 1, &D_800A62F0 };
StagePoint D_800A6308 = { 0x2EC, 3, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A6318 = { 0x2ED, 3, 3, 0x3A0, 128, 1, &D_800A6308 };
StagePoint D_800A6328 = { 0x2ED, 3, 1, 0x350, 0x1F8, 5, &D_800A6318 };
StagePoints D_800A6338 = { 3, 2, &D_800A6328 };
StagePoint D_800A6340 = { 0x2EE, 3, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6350 = { 0x2EC, 3, 6, 0x3B0, 120, 1, &D_800A6340 };
StagePoint D_800A6360 = { 0x2ED, 3, 2, 0x350, 0x1F8, 5, &D_800A6350 };
StagePoints D_800A6370 = { 3, 3, &D_800A6360 };
StagePoint D_800A6378 = { 0x2EC, 4, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A6388 = { 0x2EC, 4, 3, 0x3B0, 120, 1, &D_800A6378 };
StagePoint D_800A6398 = { 0x2EA, 4, 1, 224, 0x200, 5, &D_800A6388 };
StagePoints D_800A63A8 = { 4, 1, &D_800A6398 };
StagePoint D_800A63B0 = { 0x2EC, 4, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A63C0 = { 0x2EC, 4, 5, 0x3B0, 120, 1, &D_800A63B0 };
StagePoint D_800A63D0 = { 0x2EC, 4, 3, 240, 0x1D8, 5, &D_800A63C0 };
StagePoints D_800A63E0 = { 4, 2, &D_800A63D0 };
StagePoint D_800A63E8 = { 0x2EC, 4, 6, 0x3B0, 120, 1, NULL };
StagePoint D_800A63F8 = { 0x2EC, 4, 7, 0x3B0, 120, 1, &D_800A63E8 };
StagePoint D_800A6408 = { 0x2EE, 4, 1, 224, 0x240, 5, &D_800A63F8 };
StagePoints D_800A6418 = { 4, 3, &D_800A6408 };
StagePoint D_800A6420 = { 0x2EC, 5, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A6430 = { 0x2ED, 5, 2, 0x3A0, 128, 1, &D_800A6420 };
StagePoint D_800A6440 = { 0x2E8, 5, 1, 176, 0x168, 5, &D_800A6430 };
StagePoints D_800A6450 = { 5, 1, &D_800A6440 };
StagePoint D_800A6458 = { 0x2EC, 5, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A6468 = { 0x2ED, 5, 4, 0x3A0, 128, 1, &D_800A6458 };
StagePoint D_800A6478 = { 0x2ED, 5, 1, 0x350, 0x1F8, 5, &D_800A6468 };
StagePoints D_800A6488 = { 5, 2, &D_800A6478 };
StagePoint D_800A6490 = { 0x2ED, 5, 5, 0x3A0, 128, 1, NULL };
StagePoint D_800A64A0 = { 0x2EE, 5, 1, 0x130, 200, 1, &D_800A6490 };
StagePoint D_800A64B0 = { 0x2EC, 5, 1, 240, 0x1D8, 5, &D_800A64A0 };
StagePoints D_800A64C0 = { 5, 3, &D_800A64B0 };
StagePoint D_800A64C8 = { 0x2EB, 5, 1, 0x240, 160, 1, NULL };
StagePoint D_800A64D8 = { 0x2EC, 5, 3, 0x3B0, 120, 1, &D_800A64C8 };
StagePoint D_800A64E8 = { 0x2ED, 5, 2, 0x350, 0x1F8, 5, &D_800A64D8 };
StagePoints D_800A64F8 = { 5, 4, &D_800A64E8 };
StagePoint D_800A6500 = { 0x2EB, 5, 2, 0x240, 160, 1, NULL };
StagePoint D_800A6510 = { 0x2EE, 5, 2, 0x130, 200, 1, &D_800A6500 };
StagePoint D_800A6520 = { 0x2ED, 5, 3, 224, 192, 5, &D_800A6510 };
StagePoints D_800A6530 = { 5, 5, &D_800A6520 };
StagePoint D_800A6538 = { 0x2EE, 5, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6548 = { 0x2EB, 5, 3, 0x240, 160, 1, &D_800A6538 };
StagePoint D_800A6558 = { 0x2EC, 5, 3, 240, 0x1D8, 5, &D_800A6548 };
StagePoints D_800A6568 = { 5, 6, &D_800A6558 };
StagePoint D_800A6570 = { 0x2EC, 6, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A6580 = { 0x2EE, 6, 1, 0x130, 200, 1, &D_800A6570 };
StagePoint D_800A6590 = { 0x2EC, 6, 1, 240, 0x1D8, 5, &D_800A6580 };
StagePoints D_800A65A0 = { 6, 1, &D_800A6590 };
StagePoint D_800A65A8 = { 0x2EE, 6, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A65B8 = { 0x2EC, 6, 3, 0x3B0, 120, 1, &D_800A65A8 };
StagePoint D_800A65C8 = { 0x2EA, 6, 1, 224, 0x200, 5, &D_800A65B8 };
StagePoints D_800A65D8 = { 6, 2, &D_800A65C8 };
StagePoint D_800A65E0 = { 0x2ED, 6, 4, 0x3A0, 128, 1, NULL };
StagePoint D_800A65F0 = { 0x2ED, 6, 5, 0x3A0, 128, 1, &D_800A65E0 };
StagePoint D_800A6600 = { 0x2EC, 6, 2, 240, 0x1D8, 5, &D_800A65F0 };
StagePoints D_800A6610 = { 6, 3, &D_800A6600 };
StagePoint D_800A6618 = { 0x2EB, 6, 1, 0x240, 160, 1, NULL };
StagePoint D_800A6628 = { 0x2EE, 6, 3, 0x130, 200, 1, &D_800A6618 };
StagePoint D_800A6638 = { 0x2ED, 6, 3, 224, 192, 5, &D_800A6628 };
StagePoints D_800A6648 = { 6, 4, &D_800A6638 };
StagePoint D_800A6650 = { 0x2EE, 6, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6660 = { 0x2EE, 6, 4, 0x130, 200, 1, &D_800A6650 };
StagePoint D_800A6670 = { 0x2ED, 6, 3, 0x350, 0x1F8, 5, &D_800A6660 };
StagePoints D_800A6680 = { 6, 5, &D_800A6670 };
StagePoint D_800A6688 = { 0x2EE, 6, 4, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6698 = { 0x2ED, 6, 7, 0x3A0, 128, 1, &D_800A6688 };
StagePoint D_800A66A8 = { 0x2EE, 6, 2, 224, 0x240, 5, &D_800A6698 };
StagePoints D_800A66B8 = { 6, 6, &D_800A66A8 };
StagePoint D_800A66C0 = { 0x2ED, 6, 8, 0x3A0, 128, 1, NULL };
StagePoint D_800A66D0 = { 0x2EE, 6, 6, 0x130, 200, 1, &D_800A66C0 };
StagePoint D_800A66E0 = { 0x2ED, 6, 6, 0x350, 0x1F8, 5, &D_800A66D0 };
StagePoints D_800A66F0 = { 6, 7, &D_800A66E0 };
StagePoint D_800A66F8 = { 0x2EE, 6, 7, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6708 = { 0x2EE, 6, 8, 0x130, 200, 1, &D_800A66F8 };
StagePoint D_800A6718 = { 0x2ED, 6, 7, 224, 192, 5, &D_800A6708 };
StagePoints D_800A6728 = { 6, 8, &D_800A6718 };
StagePoints *D_800A6730[] = {
    &D_800A6108, &D_800A6140, &D_800A6178, &D_800A61B0,
    &D_800A61E8, &D_800A6220, &D_800A6258, &D_800A6290,
    &D_800A62C8, &D_800A6300, &D_800A6338, &D_800A6370,
    &D_800A63A8, &D_800A63E0, &D_800A6418, &D_800A6450,
    &D_800A6488, &D_800A64C0, &D_800A64F8, &D_800A6530,
    &D_800A6568, &D_800A65A0, &D_800A65D8, &D_800A6610,
    &D_800A6648, &D_800A6680, &D_800A66B8, &D_800A66F0,
    &D_800A6728, NULL,
};
s32 D_800A67A8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x170016E, 0x7000B8, 0x1FF0140,
    0x1000140, 0x140016E, 0x4000B8, 0x1FF0150,
    0x1000140, 0x1000140, 0, 0x1FF0160,
    0x1000140, 0x1000154, 80, 0x1FF0170,
    0x1000140, 0x1400152, 0x400048, 0x1FE0140,
    0x1000140, 0x1000168, 160, 0x1FE0150,
    0x1000140, 0x1400140, 0x400000, 0x1FE0160,
    0x1000140, 0x1400160, 0x400080, 0x1FE0170,
};
s32 D_800A6888[] = {
    0x10276, 0x1848B, 65535,
};
s32 D_800A6894[] = {
    0x10275, 0x1847E, 65535,
};
s32 D_800A68A0[] = {
    0x10274, 0x18497, 65535,
};
s32 D_800A68AC[] = {
    0x10279, 0x18029, 65535,
};
s32 D_800A68B8[] = {
    0, 65535,
};
s32 D_800A68C0[] = {
    0x10000, 65535,
};
s32 D_800A68C8[] = {
    0x10000, 65535,
};
s32 D_800A68D0[] = {
    0x17400, 0x10A0E, 65535,
};
s32 D_800A68DC[] = {
    0, 65535,
};
s32 D_800A68E4[] = {
    0x10000, 65535,
};
s32 D_800A68EC[] = {
    0x10000, 65535,
};
s32 D_800A68F4[] = {
    0x17401, 0x10A0F, 65535,
};
s32 D_800A6900[] = {
    0, 65535,
};
s32 D_800A6908[] = {
    0x10000, 65535,
};
s32 D_800A6910[] = {
    0x10000, 65535,
};
s32 D_800A6918[] = {
    0x10A11, 0x17402, 65535,
};
s32 D_800A6924[] = {
    0, 65535,
};
s32 D_800A692C[] = {
    0x10000, 65535,
};
s32 D_800A6934[] = {
    0x10000, 65535,
};
s32 D_800A693C[] = {
    0x17403, 0x10A12, 65535,
};
s32 D_800A6948[] = {
    0, (s32)D_800A6888, 14, 0,
    0, 0,
};
s32 D_800A6960[] = {
    0, (s32)D_800A6894, 13, 0,
    0, 0,
};
s32 D_800A6978[] = {
    0, (s32)D_800A68A0, 12, 0,
    0, 0,
};
s32 D_800A6990[] = {
    0, (s32)D_800A68AC, 17, 0,
    0, 0,
};
s32 D_800A69A8[] = {
    (s32)D_800A68B8, (s32)D_800A68C0, 241, (s32)D_800A68C8,
    (s32)D_800A68D0, 242, 0, 0,
    0,
};
s32 D_800A69CC[] = {
    (s32)D_800A68DC, (s32)D_800A68E4, 243, (s32)D_800A68EC,
    (s32)D_800A68F4, 244, 0, 0,
    0,
};
s32 D_800A69F0[] = {
    (s32)D_800A6900, (s32)D_800A6908, 247, (s32)D_800A6910,
    (s32)D_800A6918, 248, 0, 0,
    0,
};
s32 D_800A6A14[] = {
    (s32)D_800A6924, (s32)D_800A692C, 249, (s32)D_800A6934,
    (s32)D_800A693C, 250, 0, 0,
    0,
};
s32 D_800A6A38[] = {
    0x17E04, 0x17E22, 630, 65535,
};
s32 D_800A6A48[] = {
    0x17E04, 0x17E23, 629, 65535,
};
s32 D_800A6A58[] = {
    0x17E05, 0x17E20, 628, 65535,
};
s32 D_800A6A68[] = {
    0x17E05, 0x17E23, 633, 32809,
    65535,
};
s32 D_800A6A7C[] = {
    0x17E00, 0x17E1E, 8, 65535,
};
s32 D_800A6A8C[] = {
    0x17E00, 0x17E1F, 8, 65535,
};
s32 D_800A6A9C[] = {
    0x17E00, 0x17E20, 8, 65535,
};
s32 D_800A6AAC[] = {
    0x17E00, 0x17E21, 8, 65535,
};
s32 D_800A6ABC[] = {
    0x17E00, 0x17E22, 8, 65535,
};
s32 D_800A6ACC[] = {
    0x17E01, 8, 65535,
};
s32 D_800A6AD8[] = {
    0x17E04, 8, 65535,
};
s32 D_800A6AE4[] = {
    0x17E05, 8, 65535,
};
s32 D_800A6AF0[] = {
    32256, 0x17E1E, 9, 65535,
};
s32 D_800A6B00[] = {
    32256, 0x17E1F, 9, 65535,
};
s32 D_800A6B10[] = {
    32256, 0x17E20, 9, 65535,
};
s32 D_800A6B20[] = {
    32256, 0x17E21, 9, 65535,
};
s32 D_800A6B30[] = {
    32256, 0x17E22, 9, 65535,
};
s32 D_800A6B40[] = {
    0x17E00, 0x17E1E, 2574, 65535,
};
s32 D_800A6B50[] = {
    0x17E00, 0x17E1F, 2575, 65535,
};
s32 D_800A6B60[] = {
    0x17E00, 0x17E21, 2577, 65535,
};
s32 D_800A6B70[] = {
    0x17E00, 0x17E22, 2578, 65535,
};
s32 D_800A6B80[] = {
    (s32)D_800A6A38, (s32)D_800A6948, 0x40021, 0xD802A0,
    1,
};
s32 D_800A6B94[] = {
    (s32)D_800A6A48, (s32)D_800A6960, 0x40021, 0xD802A0,
    1,
};
s32 D_800A6BA8[] = {
    (s32)D_800A6A58, (s32)D_800A6978, 0x40021, 0xD802A0,
    1,
};
s32 D_800A6BBC[] = {
    (s32)D_800A6A68, (s32)D_800A6990, 0x40021, 0xD802A0,
    1,
};
s32 D_800A6BD0[] = {
    0, 0, 0x50146, 0,
    0,
};
s32 D_800A6BE4[] = {
    (s32)D_800A6A7C, 0, 0x60148, 0xA401E8,
    1,
};
s32 D_800A6BF8[] = {
    (s32)D_800A6A8C, 0, 0x60148, 0xA401E8,
    1,
};
s32 D_800A6C0C[] = {
    (s32)D_800A6A9C, 0, 0x60148, 0xC80310,
    1,
};
s32 D_800A6C20[] = {
    (s32)D_800A6AAC, 0, 0x60148, 0xC80310,
    1,
};
s32 D_800A6C34[] = {
    (s32)D_800A6ABC, 0, 0x60148, 0xA401E8,
    1,
};
s32 D_800A6C48[] = {
    (s32)D_800A6ACC, 0, 0x60148, 0x1600300,
    1,
};
s32 D_800A6C5C[] = {
    (s32)D_800A6AD8, 0, 0x60148, 0xA401E8,
    1,
};
s32 D_800A6C70[] = {
    (s32)D_800A6AE4, 0, 0x60148, 0x15401C8,
    1,
};
s32 D_800A6C84[] = {
    (s32)D_800A6AF0, 0, 0x7015F, 0x18001C0,
    1,
};
s32 D_800A6C98[] = {
    (s32)D_800A6B00, 0, 0x7015F, 0x1980370,
    1,
};
s32 D_800A6CAC[] = {
    (s32)D_800A6B10, 0, 0x7015F, 0x980370,
    1,
};
s32 D_800A6CC0[] = {
    (s32)D_800A6B20, 0, 0x7015F, 0xC80310,
    1,
};
s32 D_800A6CD4[] = {
    (s32)D_800A6B30, 0, 0x7015F, 0xA80110,
    1,
};
s32 D_800A6CE8[] = {
    (s32)D_800A6B40, (s32)D_800A69A8, 0x80189, 0x10001E0,
    1,
};
s32 D_800A6CFC[] = {
    (s32)D_800A6B50, (s32)D_800A69CC, 0x9018A, 0x10001E0,
    1,
};
s32 D_800A6D10[] = {
    (s32)D_800A6B60, (s32)D_800A69F0, 0xA018C, 0x1A00280,
    1,
};
s32 D_800A6D24[] = {
    (s32)D_800A6B70, (s32)D_800A6A14, 0xB018D, 0x1A00280,
    1,
};
s32 D_800A6D38[] = {
    (s32)D_800A6B80, (s32)D_800A6B94, (s32)D_800A6BA8, (s32)D_800A6BBC,
    (s32)D_800A6BD0, (s32)D_800A6BE4, (s32)D_800A6BF8, (s32)D_800A6C0C,
    (s32)D_800A6C20, (s32)D_800A6C34, (s32)D_800A6C48, (s32)D_800A6C5C,
    (s32)D_800A6C70, (s32)D_800A6C84, (s32)D_800A6C98, (s32)D_800A6CAC,
    (s32)D_800A6CC0, (s32)D_800A6CD4, (s32)D_800A6CE8, (s32)D_800A6CFC,
    (s32)D_800A6D10, (s32)D_800A6D24, 0,
};
s32 D_800A6D94[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A6DA8[] = {
    65535, 65535, 0x2ED0001, 0x8003A0,
    5, 0, 65535, 65535,
    0x2ED0001, 0x1F80350, 1, 0,
    65535, 65535, 0x2ED0001, 0xC000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A6E08[])(void) = {
    func_800A5FB0,
};
s32 D_800A6E0C[] = {
    38, 10, 0x60080000,
};
s32 D_800A6E18[] = {
    56, 10, 0x60080000,
};
s32 D_800A6E24[] = {
    107, 10, 0x60080000,
};
s32 D_800A6E30[] = {
    155, 10, 0x60080000,
};
s32 D_800A6E3C[] = {
    120, 10, 0x60080000,
};
s32 D_800A6E48[] = {
    181, 10, 0x60080000,
};
s32 D_800A6E54[] = {
    142, 10, 0x60080000,
};
s32 D_800A6E60[] = {
    143, 10, 0x60080000,
};
s32 D_800A6E6C[] = {
    3, (s32)D_800A6E0C, (s32)D_800A6E18, (s32)D_800A6E24,
    (s32)D_800A6E30, (s32)D_800A6E3C, (s32)D_800A6E48, (s32)D_800A6E54,
    (s32)D_800A6E60,
};
s32 D_800A6E90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ECC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ED8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EF0[] = {
    0, (s32)D_800A6E90, (s32)D_800A6E9C, (s32)D_800A6EA8,
    (s32)D_800A6EB4, (s32)D_800A6EC0, (s32)D_800A6ECC, (s32)D_800A6ED8,
    (s32)D_800A6EE4,
};
s32 D_800A6F14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F38[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F44[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F74[] = {
    0, (s32)D_800A6F14, (s32)D_800A6F20, (s32)D_800A6F2C,
    (s32)D_800A6F38, (s32)D_800A6F44, (s32)D_800A6F50, (s32)D_800A6F5C,
    (s32)D_800A6F68,
};
s32 D_800A6F98[] = {
    316, 19, 0x60880000,
};
s32 D_800A6FA4[] = {
    317, 19, 0x60880000,
};
s32 D_800A6FB0[] = {
    319, 19, 0x60880000,
};
s32 D_800A6FBC[] = {
    321, 19, 0x60880000,
};
s32 D_800A6FC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FF8[] = {
    0, (s32)D_800A6F98, (s32)D_800A6FA4, (s32)D_800A6FB0,
    (s32)D_800A6FBC, (s32)D_800A6FC8, (s32)D_800A6FD4, (s32)D_800A6FE0,
    (s32)D_800A6FEC,
};
s32 D_800A701C[] = {
    81, 10, 0x60080000,
};
s32 D_800A7028[] = {
    81, 10, 0x60080000,
};
s32 D_800A7034[] = {
    165, 10, 0x60080000,
};
s32 D_800A7040[] = {
    165, 10, 0x60080000,
};
s32 D_800A704C[] = {
    166, 10, 0x60080000,
};
s32 D_800A7058[] = {
    166, 10, 0x60080000,
};
s32 D_800A7064[] = {
    169, 10, 0x60080000,
};
s32 D_800A7070[] = {
    169, 10, 0x60080000,
};
s32 D_800A707C[] = {
    3, (s32)D_800A701C, (s32)D_800A7028, (s32)D_800A7034,
    (s32)D_800A7040, (s32)D_800A704C, (s32)D_800A7058, (s32)D_800A7064,
    (s32)D_800A7070,
};
s32 D_800A70A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A70AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A70B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A70C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A70D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A70DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A70E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A70F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7100[] = {
    0, (s32)D_800A70A0, (s32)D_800A70AC, (s32)D_800A70B8,
    (s32)D_800A70C4, (s32)D_800A70D0, (s32)D_800A70DC, (s32)D_800A70E8,
    (s32)D_800A70F4,
};
s32 D_800A7124[] = {
    0, 0, 0x60040000,
};
s32 D_800A7130[] = {
    0, 0, 0x60040000,
};
s32 D_800A713C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7148[] = {
    0, 0, 0x60040000,
};
s32 D_800A7154[] = {
    0, 0, 0x60040000,
};
s32 D_800A7160[] = {
    0, 0, 0x60040000,
};
s32 D_800A716C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7178[] = {
    0, 0, 0x60040000,
};
s32 D_800A7184[] = {
    0, (s32)D_800A7124, (s32)D_800A7130, (s32)D_800A713C,
    (s32)D_800A7148, (s32)D_800A7154, (s32)D_800A7160, (s32)D_800A716C,
    (s32)D_800A7178,
};
s32 D_800A71A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A71B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A71C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A71CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A71D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A71E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A71F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A71FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7208[] = {
    0, (s32)D_800A71A8, (s32)D_800A71B4, (s32)D_800A71C0,
    (s32)D_800A71CC, (s32)D_800A71D8, (s32)D_800A71E4, (s32)D_800A71F0,
    (s32)D_800A71FC,
};
s32 D_800A722C[] = {
    136, 10, 0x60080000,
};
s32 D_800A7238[] = {
    136, 10, 0x60080000,
};
s32 D_800A7244[] = {
    137, 10, 0x60080000,
};
s32 D_800A7250[] = {
    137, 10, 0x60080000,
};
s32 D_800A725C[] = {
    183, 10, 0x60080000,
};
s32 D_800A7268[] = {
    183, 10, 0x60080000,
};
s32 D_800A7274[] = {
    118, 10, 0x60080000,
};
s32 D_800A7280[] = {
    118, 10, 0x60080000,
};
s32 D_800A728C[] = {
    3, (s32)D_800A722C, (s32)D_800A7238, (s32)D_800A7244,
    (s32)D_800A7250, (s32)D_800A725C, (s32)D_800A7268, (s32)D_800A7274,
    (s32)D_800A7280,
};
s32 D_800A72B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A72BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A72C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A72D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A72E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A72EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A72F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7304[] = {
    0, 0, 0x60040000,
};
s32 D_800A7310[] = {
    0, (s32)D_800A72B0, (s32)D_800A72BC, (s32)D_800A72C8,
    (s32)D_800A72D4, (s32)D_800A72E0, (s32)D_800A72EC, (s32)D_800A72F8,
    (s32)D_800A7304,
};
s32 D_800A7334[] = {
    0, 0, 0x60040000,
};
s32 D_800A7340[] = {
    0, 0, 0x60040000,
};
s32 D_800A734C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7358[] = {
    0, 0, 0x60040000,
};
s32 D_800A7364[] = {
    0, 0, 0x60040000,
};
s32 D_800A7370[] = {
    0, 0, 0x60040000,
};
s32 D_800A737C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7388[] = {
    0, 0, 0x60040000,
};
s32 D_800A7394[] = {
    0, (s32)D_800A7334, (s32)D_800A7340, (s32)D_800A734C,
    (s32)D_800A7358, (s32)D_800A7364, (s32)D_800A7370, (s32)D_800A737C,
    (s32)D_800A7388,
};
s32 D_800A73B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A73C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A73D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A73DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A73E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A73F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7400[] = {
    0, 0, 0x60040000,
};
s32 D_800A740C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7418[] = {
    0, (s32)D_800A73B8, (s32)D_800A73C4, (s32)D_800A73D0,
    (s32)D_800A73DC, (s32)D_800A73E8, (s32)D_800A73F4, (s32)D_800A7400,
    (s32)D_800A740C,
};
s32 D_800A743C[] = {
    117, 10, 0x60080000,
};
s32 D_800A7448[] = {
    117, 10, 0x60080000,
};
s32 D_800A7454[] = {
    184, 10, 0x60080000,
};
s32 D_800A7460[] = {
    184, 10, 0x60080000,
};
s32 D_800A746C[] = {
    187, 10, 0x60080000,
};
s32 D_800A7478[] = {
    187, 10, 0x60080000,
};
s32 D_800A7484[] = {
    187, 10, 0x60080000,
};
s32 D_800A7490[] = {
    187, 10, 0x60080000,
};
s32 D_800A749C[] = {
    3, (s32)D_800A743C, (s32)D_800A7448, (s32)D_800A7454,
    (s32)D_800A7460, (s32)D_800A746C, (s32)D_800A7478, (s32)D_800A7484,
    (s32)D_800A7490,
};
s32 D_800A74C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A74D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A74F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7508[] = {
    0, 0, 0x60040000,
};
s32 D_800A7514[] = {
    0, 0, 0x60040000,
};
s32 D_800A7520[] = {
    0, (s32)D_800A74C0, (s32)D_800A74CC, (s32)D_800A74D8,
    (s32)D_800A74E4, (s32)D_800A74F0, (s32)D_800A74FC, (s32)D_800A7508,
    (s32)D_800A7514,
};
s32 D_800A7544[] = {
    0, 0, 0x60040000,
};
s32 D_800A7550[] = {
    0, 0, 0x60040000,
};
s32 D_800A755C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7568[] = {
    0, 0, 0x60040000,
};
s32 D_800A7574[] = {
    0, 0, 0x60040000,
};
s32 D_800A7580[] = {
    0, 0, 0x60040000,
};
s32 D_800A758C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7598[] = {
    0, 0, 0x60040000,
};
s32 D_800A75A4[] = {
    0, (s32)D_800A7544, (s32)D_800A7550, (s32)D_800A755C,
    (s32)D_800A7568, (s32)D_800A7574, (s32)D_800A7580, (s32)D_800A758C,
    (s32)D_800A7598,
};
s32 D_800A75C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A75D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A75E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A75F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7604[] = {
    0, 0, 0x60040000,
};
s32 D_800A7610[] = {
    0, 0, 0x60040000,
};
s32 D_800A761C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7628[] = {
    0, (s32)D_800A75C8, (s32)D_800A75D4, (s32)D_800A75E0,
    (s32)D_800A75EC, (s32)D_800A75F8, (s32)D_800A7604, (s32)D_800A7610,
    (s32)D_800A761C,
};
s32 D_800A764C[] = {
    74, 10, 0x60080000,
};
s32 D_800A7658[] = {
    77, 10, 0x60080000,
};
s32 D_800A7664[] = {
    78, 10, 0x60080000,
};
s32 D_800A7670[] = {
    79, 10, 0x60080000,
};
s32 D_800A767C[] = {
    80, 10, 0x60080000,
};
s32 D_800A7688[] = {
    75, 10, 0x60080000,
};
s32 D_800A7694[] = {
    76, 10, 0x60080000,
};
s32 D_800A76A0[] = {
    89, 10, 0x60080000,
};
s32 D_800A76AC[] = {
    3, (s32)D_800A764C, (s32)D_800A7658, (s32)D_800A7664,
    (s32)D_800A7670, (s32)D_800A767C, (s32)D_800A7688, (s32)D_800A7694,
    (s32)D_800A76A0,
};
s32 D_800A76D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A76DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A76E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A76F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7700[] = {
    0, 0, 0x60040000,
};
s32 D_800A770C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7718[] = {
    0, 0, 0x60040000,
};
s32 D_800A7724[] = {
    0, 0, 0x60040000,
};
s32 D_800A7730[] = {
    0, (s32)D_800A76D0, (s32)D_800A76DC, (s32)D_800A76E8,
    (s32)D_800A76F4, (s32)D_800A7700, (s32)D_800A770C, (s32)D_800A7718,
    (s32)D_800A7724,
};
s32 D_800A7754[] = {
    0, 0, 0x60040000,
};
s32 D_800A7760[] = {
    0, 0, 0x60040000,
};
s32 D_800A776C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7778[] = {
    0, 0, 0x60040000,
};
s32 D_800A7784[] = {
    0, 0, 0x60040000,
};
s32 D_800A7790[] = {
    0, 0, 0x60040000,
};
s32 D_800A779C[] = {
    0, 0, 0x60040000,
};
s32 D_800A77A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A77B4[] = {
    0, (s32)D_800A7754, (s32)D_800A7760, (s32)D_800A776C,
    (s32)D_800A7778, (s32)D_800A7784, (s32)D_800A7790, (s32)D_800A779C,
    (s32)D_800A77A8,
};
s32 D_800A77D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A77E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A77F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7808[] = {
    0, 0, 0x60040000,
};
s32 D_800A7814[] = {
    0, 0, 0x60040000,
};
s32 D_800A7820[] = {
    0, 0, 0x60040000,
};
s32 D_800A782C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7838[] = {
    0, (s32)D_800A77D8, (s32)D_800A77E4, (s32)D_800A77F0,
    (s32)D_800A77FC, (s32)D_800A7808, (s32)D_800A7814, (s32)D_800A7820,
    (s32)D_800A782C,
};
s32 D_800A785C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7868[] = {
    110, 10, 0x60080000,
};
s32 D_800A7874[] = {
    71, 10, 0x60080000,
};
s32 D_800A7880[] = {
    71, 10, 0x60080000,
};
s32 D_800A788C[] = {
    121, 10, 0x60080000,
};
s32 D_800A7898[] = {
    121, 10, 0x60080000,
};
s32 D_800A78A4[] = {
    182, 10, 0x60080000,
};
s32 D_800A78B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A78BC[] = {
    3, (s32)D_800A785C, (s32)D_800A7868, (s32)D_800A7874,
    (s32)D_800A7880, (s32)D_800A788C, (s32)D_800A7898, (s32)D_800A78A4,
    (s32)D_800A78B0,
};
s32 D_800A78E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A78EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A78F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7904[] = {
    0, 0, 0x60040000,
};
s32 D_800A7910[] = {
    0, 0, 0x60040000,
};
s32 D_800A791C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7928[] = {
    0, 0, 0x60040000,
};
s32 D_800A7934[] = {
    0, 0, 0x60040000,
};
s32 D_800A7940[] = {
    0, (s32)D_800A78E0, (s32)D_800A78EC, (s32)D_800A78F8,
    (s32)D_800A7904, (s32)D_800A7910, (s32)D_800A791C, (s32)D_800A7928,
    (s32)D_800A7934,
};
s32 D_800A7964[] = {
    0, 0, 0x60040000,
};
s32 D_800A7970[] = {
    0, 0, 0x60040000,
};
s32 D_800A797C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7988[] = {
    0, 0, 0x60040000,
};
s32 D_800A7994[] = {
    0, 0, 0x60040000,
};
s32 D_800A79A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A79B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A79C4[] = {
    0, (s32)D_800A7964, (s32)D_800A7970, (s32)D_800A797C,
    (s32)D_800A7988, (s32)D_800A7994, (s32)D_800A79A0, (s32)D_800A79AC,
    (s32)D_800A79B8,
};
s32 D_800A79E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A79F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A00[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A18[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A24[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A30[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A48[] = {
    0, (s32)D_800A79E8, (s32)D_800A79F4, (s32)D_800A7A00,
    (s32)D_800A7A0C, (s32)D_800A7A18, (s32)D_800A7A24, (s32)D_800A7A30,
    (s32)D_800A7A3C,
};
s32 D_800A7A6C[] = {
    418, 1, 0, (s32)D_800A6E6C,
    (s32)D_800A6EF0, (s32)D_800A6F74, (s32)D_800A6FF8, 423,
    2, 0, (s32)D_800A707C, (s32)D_800A7100,
    (s32)D_800A7184, (s32)D_800A7208, 429, 3,
    0, (s32)D_800A728C, (s32)D_800A7310, (s32)D_800A7394,
    (s32)D_800A7418, 435, 4, 0,
    (s32)D_800A749C, (s32)D_800A7520, (s32)D_800A75A4, (s32)D_800A7628,
    441, 5, 0, (s32)D_800A76AC,
    (s32)D_800A7730, (s32)D_800A77B4, (s32)D_800A7838, 447,
    6, 0, (s32)D_800A78BC, (s32)D_800A7940,
    (s32)D_800A79C4, (s32)D_800A7A48,
};
