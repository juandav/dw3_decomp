#include "common.h"
#include "stage.h"
extern void (*D_800A8E3C[])(void);
void func_800A4DA4();
extern StagePoints *D_800A5380[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A5380, GAME.unk44, GAME.unk46);
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
    D_800A8E3C[0]();
    return task;
}

extern s32 D_800A8DF8[];
extern s32 D_800A8E0C[];
extern s32 D_800A83F4[];
extern s32 D_800A8D58[];
extern s32 D_800A818C[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x680
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x690
#endif
void func_800A4E74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A8DF8;
    D_800990B4.unk14 = D_800A8E0C;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xEB00, 0x1F500};
    D_800990B4.unk28 = D_800A83F4;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A8D58;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A818C, GAME.unk44);
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4E74();
extern StagePoint D_800A4F90;
extern StagePoint D_800A4FA8;
extern StagePoint D_800A4FC0;
extern StagePoint D_800A4FD8;
extern StagePoint D_800A4FF0;
extern StagePoint D_800A5008;
extern StagePoint D_800A5020;
extern StagePoint D_800A5038;
extern StagePoint D_800A5050;
extern StagePoint D_800A5068;
extern StagePoint D_800A5080;
extern StagePoint D_800A5098;
extern StagePoint D_800A50B0;
extern StagePoint D_800A50C8;
extern StagePoint D_800A50E0;
extern StagePoint D_800A50F8;
extern StagePoint D_800A5110;
extern StagePoint D_800A5128;
extern StagePoint D_800A5140;
extern StagePoint D_800A5158;
extern StagePoint D_800A5170;
extern StagePoint D_800A5188;
extern StagePoint D_800A51A0;
extern StagePoint D_800A51B8;
extern StagePoint D_800A51D0;
extern StagePoint D_800A51E8;
extern StagePoint D_800A5200;
extern StagePoint D_800A5218;
extern StagePoint D_800A5230;
extern StagePoint D_800A5248;
extern StagePoint D_800A5260;
extern StagePoint D_800A5278;
extern StagePoint D_800A5290;
extern StagePoint D_800A52A8;
extern StagePoint D_800A52C0;
extern StagePoint D_800A52D8;
extern StagePoint D_800A52F0;
extern StagePoint D_800A5308;
extern StagePoint D_800A5320;
extern StagePoint D_800A5338;
extern StagePoint D_800A5350;
extern StagePoint D_800A5368;
extern StagePoints D_800A4FA0;
extern StagePoints D_800A4FB8;
extern StagePoints D_800A4FD0;
extern StagePoints D_800A4FE8;
extern StagePoints D_800A5000;
extern StagePoints D_800A5018;
extern StagePoints D_800A5030;
extern StagePoints D_800A5048;
extern StagePoints D_800A5060;
extern StagePoints D_800A5078;
extern StagePoints D_800A5090;
extern StagePoints D_800A50A8;
extern StagePoints D_800A50C0;
extern StagePoints D_800A50D8;
extern StagePoints D_800A50F0;
extern StagePoints D_800A5108;
extern StagePoints D_800A5120;
extern StagePoints D_800A5138;
extern StagePoints D_800A5150;
extern StagePoints D_800A5168;
extern StagePoints D_800A5180;
extern StagePoints D_800A5198;
extern StagePoints D_800A51B0;
extern StagePoints D_800A51C8;
extern StagePoints D_800A51E0;
extern StagePoints D_800A51F8;
extern StagePoints D_800A5210;
extern StagePoints D_800A5228;
extern StagePoints D_800A5240;
extern StagePoints D_800A5258;
extern StagePoints D_800A5270;
extern StagePoints D_800A5288;
extern StagePoints D_800A52A0;
extern StagePoints D_800A52B8;
extern StagePoints D_800A52D0;
extern StagePoints D_800A52E8;
extern StagePoints D_800A5300;
extern StagePoints D_800A5318;
extern StagePoints D_800A5330;
extern StagePoints D_800A5348;
extern StagePoints D_800A5360;
extern StagePoints D_800A5378;
extern s32 D_800A542C[];
extern s32 D_800A5438[];
extern s32 D_800A5444[];
extern s32 D_800A5450[];
extern s32 D_800A545C[];
extern s32 D_800A5468[];
extern s32 D_800A5474[];
extern s32 D_800A5480[];
extern s32 D_800A54B0[];
extern s32 D_800A54BC[];
extern s32 D_800A54C8[];
extern s32 D_800A54D4[];
extern s32 D_800A54E0[];
extern s32 D_800A54EC[];
extern s32 D_800A54F8[];
extern s32 D_800A5504[];
extern s32 D_800A5534[];
extern s32 D_800A5540[];
extern s32 D_800A554C[];
extern s32 D_800A5558[];
extern s32 D_800A5564[];
extern s32 D_800A5570[];
extern s32 D_800A557C[];
extern s32 D_800A5588[];
extern s32 D_800A55B8[];
extern s32 D_800A55C4[];
extern s32 D_800A55D0[];
extern s32 D_800A55DC[];
extern s32 D_800A55E8[];
extern s32 D_800A55F4[];
extern s32 D_800A5600[];
extern s32 D_800A560C[];
extern s32 D_800A563C[];
extern s32 D_800A5648[];
extern s32 D_800A5654[];
extern s32 D_800A5660[];
extern s32 D_800A566C[];
extern s32 D_800A5678[];
extern s32 D_800A5684[];
extern s32 D_800A5690[];
extern s32 D_800A56C0[];
extern s32 D_800A56CC[];
extern s32 D_800A56D8[];
extern s32 D_800A56E4[];
extern s32 D_800A56F0[];
extern s32 D_800A56FC[];
extern s32 D_800A5708[];
extern s32 D_800A5714[];
extern s32 D_800A5744[];
extern s32 D_800A5750[];
extern s32 D_800A575C[];
extern s32 D_800A5768[];
extern s32 D_800A5774[];
extern s32 D_800A5780[];
extern s32 D_800A578C[];
extern s32 D_800A5798[];
extern s32 D_800A57C8[];
extern s32 D_800A57D4[];
extern s32 D_800A57E0[];
extern s32 D_800A57EC[];
extern s32 D_800A57F8[];
extern s32 D_800A5804[];
extern s32 D_800A5810[];
extern s32 D_800A581C[];
extern s32 D_800A584C[];
extern s32 D_800A5858[];
extern s32 D_800A5864[];
extern s32 D_800A5870[];
extern s32 D_800A587C[];
extern s32 D_800A5888[];
extern s32 D_800A5894[];
extern s32 D_800A58A0[];
extern s32 D_800A58D0[];
extern s32 D_800A58DC[];
extern s32 D_800A58E8[];
extern s32 D_800A58F4[];
extern s32 D_800A5900[];
extern s32 D_800A590C[];
extern s32 D_800A5918[];
extern s32 D_800A5924[];
extern s32 D_800A5954[];
extern s32 D_800A5960[];
extern s32 D_800A596C[];
extern s32 D_800A5978[];
extern s32 D_800A5984[];
extern s32 D_800A5990[];
extern s32 D_800A599C[];
extern s32 D_800A59A8[];
extern s32 D_800A59D8[];
extern s32 D_800A59E4[];
extern s32 D_800A59F0[];
extern s32 D_800A59FC[];
extern s32 D_800A5A08[];
extern s32 D_800A5A14[];
extern s32 D_800A5A20[];
extern s32 D_800A5A2C[];
extern s32 D_800A5A5C[];
extern s32 D_800A5A68[];
extern s32 D_800A5A74[];
extern s32 D_800A5A80[];
extern s32 D_800A5A8C[];
extern s32 D_800A5A98[];
extern s32 D_800A5AA4[];
extern s32 D_800A5AB0[];
extern s32 D_800A5AE0[];
extern s32 D_800A5AEC[];
extern s32 D_800A5AF8[];
extern s32 D_800A5B04[];
extern s32 D_800A5B10[];
extern s32 D_800A5B1C[];
extern s32 D_800A5B28[];
extern s32 D_800A5B34[];
extern s32 D_800A5B64[];
extern s32 D_800A5B70[];
extern s32 D_800A5B7C[];
extern s32 D_800A5B88[];
extern s32 D_800A5B94[];
extern s32 D_800A5BA0[];
extern s32 D_800A5BAC[];
extern s32 D_800A5BB8[];
extern s32 D_800A5BE8[];
extern s32 D_800A5BF4[];
extern s32 D_800A5C00[];
extern s32 D_800A5C0C[];
extern s32 D_800A5C18[];
extern s32 D_800A5C24[];
extern s32 D_800A5C30[];
extern s32 D_800A5C3C[];
extern s32 D_800A5C6C[];
extern s32 D_800A5C78[];
extern s32 D_800A5C84[];
extern s32 D_800A5C90[];
extern s32 D_800A5C9C[];
extern s32 D_800A5CA8[];
extern s32 D_800A5CB4[];
extern s32 D_800A5CC0[];
extern s32 D_800A5CF0[];
extern s32 D_800A5CFC[];
extern s32 D_800A5D08[];
extern s32 D_800A5D14[];
extern s32 D_800A5D20[];
extern s32 D_800A5D2C[];
extern s32 D_800A5D38[];
extern s32 D_800A5D44[];
extern s32 D_800A5D74[];
extern s32 D_800A5D80[];
extern s32 D_800A5D8C[];
extern s32 D_800A5D98[];
extern s32 D_800A5DA4[];
extern s32 D_800A5DB0[];
extern s32 D_800A5DBC[];
extern s32 D_800A5DC8[];
extern s32 D_800A5DF8[];
extern s32 D_800A5E04[];
extern s32 D_800A5E10[];
extern s32 D_800A5E1C[];
extern s32 D_800A5E28[];
extern s32 D_800A5E34[];
extern s32 D_800A5E40[];
extern s32 D_800A5E4C[];
extern s32 D_800A5E7C[];
extern s32 D_800A5E88[];
extern s32 D_800A5E94[];
extern s32 D_800A5EA0[];
extern s32 D_800A5EAC[];
extern s32 D_800A5EB8[];
extern s32 D_800A5EC4[];
extern s32 D_800A5ED0[];
extern s32 D_800A5F00[];
extern s32 D_800A5F0C[];
extern s32 D_800A5F18[];
extern s32 D_800A5F24[];
extern s32 D_800A5F30[];
extern s32 D_800A5F3C[];
extern s32 D_800A5F48[];
extern s32 D_800A5F54[];
extern s32 D_800A5F84[];
extern s32 D_800A5F90[];
extern s32 D_800A5F9C[];
extern s32 D_800A5FA8[];
extern s32 D_800A5FB4[];
extern s32 D_800A5FC0[];
extern s32 D_800A5FCC[];
extern s32 D_800A5FD8[];
extern s32 D_800A6008[];
extern s32 D_800A6014[];
extern s32 D_800A6020[];
extern s32 D_800A602C[];
extern s32 D_800A6038[];
extern s32 D_800A6044[];
extern s32 D_800A6050[];
extern s32 D_800A605C[];
extern s32 D_800A608C[];
extern s32 D_800A6098[];
extern s32 D_800A60A4[];
extern s32 D_800A60B0[];
extern s32 D_800A60BC[];
extern s32 D_800A60C8[];
extern s32 D_800A60D4[];
extern s32 D_800A60E0[];
extern s32 D_800A6110[];
extern s32 D_800A611C[];
extern s32 D_800A6128[];
extern s32 D_800A6134[];
extern s32 D_800A6140[];
extern s32 D_800A614C[];
extern s32 D_800A6158[];
extern s32 D_800A6164[];
extern s32 D_800A6194[];
extern s32 D_800A61A0[];
extern s32 D_800A61AC[];
extern s32 D_800A61B8[];
extern s32 D_800A61C4[];
extern s32 D_800A61D0[];
extern s32 D_800A61DC[];
extern s32 D_800A61E8[];
extern s32 D_800A6218[];
extern s32 D_800A6224[];
extern s32 D_800A6230[];
extern s32 D_800A623C[];
extern s32 D_800A6248[];
extern s32 D_800A6254[];
extern s32 D_800A6260[];
extern s32 D_800A626C[];
extern s32 D_800A629C[];
extern s32 D_800A62A8[];
extern s32 D_800A62B4[];
extern s32 D_800A62C0[];
extern s32 D_800A62CC[];
extern s32 D_800A62D8[];
extern s32 D_800A62E4[];
extern s32 D_800A62F0[];
extern s32 D_800A6320[];
extern s32 D_800A632C[];
extern s32 D_800A6338[];
extern s32 D_800A6344[];
extern s32 D_800A6350[];
extern s32 D_800A635C[];
extern s32 D_800A6368[];
extern s32 D_800A6374[];
extern s32 D_800A63A4[];
extern s32 D_800A63B0[];
extern s32 D_800A63BC[];
extern s32 D_800A63C8[];
extern s32 D_800A63D4[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6428[];
extern s32 D_800A6434[];
extern s32 D_800A6440[];
extern s32 D_800A644C[];
extern s32 D_800A6458[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A64AC[];
extern s32 D_800A64B8[];
extern s32 D_800A64C4[];
extern s32 D_800A64D0[];
extern s32 D_800A64DC[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A6530[];
extern s32 D_800A653C[];
extern s32 D_800A6548[];
extern s32 D_800A6554[];
extern s32 D_800A6560[];
extern s32 D_800A656C[];
extern s32 D_800A6578[];
extern s32 D_800A6584[];
extern s32 D_800A65B4[];
extern s32 D_800A65C0[];
extern s32 D_800A65CC[];
extern s32 D_800A65D8[];
extern s32 D_800A65E4[];
extern s32 D_800A65F0[];
extern s32 D_800A65FC[];
extern s32 D_800A6608[];
extern s32 D_800A6638[];
extern s32 D_800A6644[];
extern s32 D_800A6650[];
extern s32 D_800A665C[];
extern s32 D_800A6668[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A668C[];
extern s32 D_800A66BC[];
extern s32 D_800A66C8[];
extern s32 D_800A66D4[];
extern s32 D_800A66E0[];
extern s32 D_800A66EC[];
extern s32 D_800A66F8[];
extern s32 D_800A6704[];
extern s32 D_800A6710[];
extern s32 D_800A6740[];
extern s32 D_800A674C[];
extern s32 D_800A6758[];
extern s32 D_800A6764[];
extern s32 D_800A6770[];
extern s32 D_800A677C[];
extern s32 D_800A6788[];
extern s32 D_800A6794[];
extern s32 D_800A67C4[];
extern s32 D_800A67D0[];
extern s32 D_800A67DC[];
extern s32 D_800A67E8[];
extern s32 D_800A67F4[];
extern s32 D_800A6800[];
extern s32 D_800A680C[];
extern s32 D_800A6818[];
extern s32 D_800A6848[];
extern s32 D_800A6854[];
extern s32 D_800A6860[];
extern s32 D_800A686C[];
extern s32 D_800A6878[];
extern s32 D_800A6884[];
extern s32 D_800A6890[];
extern s32 D_800A689C[];
extern s32 D_800A68CC[];
extern s32 D_800A68D8[];
extern s32 D_800A68E4[];
extern s32 D_800A68F0[];
extern s32 D_800A68FC[];
extern s32 D_800A6908[];
extern s32 D_800A6914[];
extern s32 D_800A6920[];
extern s32 D_800A6950[];
extern s32 D_800A695C[];
extern s32 D_800A6968[];
extern s32 D_800A6974[];
extern s32 D_800A6980[];
extern s32 D_800A698C[];
extern s32 D_800A6998[];
extern s32 D_800A69A4[];
extern s32 D_800A69D4[];
extern s32 D_800A69E0[];
extern s32 D_800A69EC[];
extern s32 D_800A69F8[];
extern s32 D_800A6A04[];
extern s32 D_800A6A10[];
extern s32 D_800A6A1C[];
extern s32 D_800A6A28[];
extern s32 D_800A6A58[];
extern s32 D_800A6A64[];
extern s32 D_800A6A70[];
extern s32 D_800A6A7C[];
extern s32 D_800A6A88[];
extern s32 D_800A6A94[];
extern s32 D_800A6AA0[];
extern s32 D_800A6AAC[];
extern s32 D_800A6ADC[];
extern s32 D_800A6AE8[];
extern s32 D_800A6AF4[];
extern s32 D_800A6B00[];
extern s32 D_800A6B0C[];
extern s32 D_800A6B18[];
extern s32 D_800A6B24[];
extern s32 D_800A6B30[];
extern s32 D_800A6B60[];
extern s32 D_800A6B6C[];
extern s32 D_800A6B78[];
extern s32 D_800A6B84[];
extern s32 D_800A6B90[];
extern s32 D_800A6B9C[];
extern s32 D_800A6BA8[];
extern s32 D_800A6BB4[];
extern s32 D_800A6BE4[];
extern s32 D_800A6BF0[];
extern s32 D_800A6BFC[];
extern s32 D_800A6C08[];
extern s32 D_800A6C14[];
extern s32 D_800A6C20[];
extern s32 D_800A6C2C[];
extern s32 D_800A6C38[];
extern s32 D_800A6C68[];
extern s32 D_800A6C74[];
extern s32 D_800A6C80[];
extern s32 D_800A6C8C[];
extern s32 D_800A6C98[];
extern s32 D_800A6CA4[];
extern s32 D_800A6CB0[];
extern s32 D_800A6CBC[];
extern s32 D_800A6CEC[];
extern s32 D_800A6CF8[];
extern s32 D_800A6D04[];
extern s32 D_800A6D10[];
extern s32 D_800A6D1C[];
extern s32 D_800A6D28[];
extern s32 D_800A6D34[];
extern s32 D_800A6D40[];
extern s32 D_800A6D70[];
extern s32 D_800A6D7C[];
extern s32 D_800A6D88[];
extern s32 D_800A6D94[];
extern s32 D_800A6DA0[];
extern s32 D_800A6DAC[];
extern s32 D_800A6DB8[];
extern s32 D_800A6DC4[];
extern s32 D_800A6DF4[];
extern s32 D_800A6E00[];
extern s32 D_800A6E0C[];
extern s32 D_800A6E18[];
extern s32 D_800A6E24[];
extern s32 D_800A6E30[];
extern s32 D_800A6E3C[];
extern s32 D_800A6E48[];
extern s32 D_800A6E78[];
extern s32 D_800A6E84[];
extern s32 D_800A6E90[];
extern s32 D_800A6E9C[];
extern s32 D_800A6EA8[];
extern s32 D_800A6EB4[];
extern s32 D_800A6EC0[];
extern s32 D_800A6ECC[];
extern s32 D_800A6EFC[];
extern s32 D_800A6F08[];
extern s32 D_800A6F14[];
extern s32 D_800A6F20[];
extern s32 D_800A6F2C[];
extern s32 D_800A6F38[];
extern s32 D_800A6F44[];
extern s32 D_800A6F50[];
extern s32 D_800A6F80[];
extern s32 D_800A6F8C[];
extern s32 D_800A6F98[];
extern s32 D_800A6FA4[];
extern s32 D_800A6FB0[];
extern s32 D_800A6FBC[];
extern s32 D_800A6FC8[];
extern s32 D_800A6FD4[];
extern s32 D_800A7004[];
extern s32 D_800A7010[];
extern s32 D_800A701C[];
extern s32 D_800A7028[];
extern s32 D_800A7034[];
extern s32 D_800A7040[];
extern s32 D_800A704C[];
extern s32 D_800A7058[];
extern s32 D_800A7088[];
extern s32 D_800A7094[];
extern s32 D_800A70A0[];
extern s32 D_800A70AC[];
extern s32 D_800A70B8[];
extern s32 D_800A70C4[];
extern s32 D_800A70D0[];
extern s32 D_800A70DC[];
extern s32 D_800A710C[];
extern s32 D_800A7118[];
extern s32 D_800A7124[];
extern s32 D_800A7130[];
extern s32 D_800A713C[];
extern s32 D_800A7148[];
extern s32 D_800A7154[];
extern s32 D_800A7160[];
extern s32 D_800A7190[];
extern s32 D_800A719C[];
extern s32 D_800A71A8[];
extern s32 D_800A71B4[];
extern s32 D_800A71C0[];
extern s32 D_800A71CC[];
extern s32 D_800A71D8[];
extern s32 D_800A71E4[];
extern s32 D_800A7214[];
extern s32 D_800A7220[];
extern s32 D_800A722C[];
extern s32 D_800A7238[];
extern s32 D_800A7244[];
extern s32 D_800A7250[];
extern s32 D_800A725C[];
extern s32 D_800A7268[];
extern s32 D_800A7298[];
extern s32 D_800A72A4[];
extern s32 D_800A72B0[];
extern s32 D_800A72BC[];
extern s32 D_800A72C8[];
extern s32 D_800A72D4[];
extern s32 D_800A72E0[];
extern s32 D_800A72EC[];
extern s32 D_800A731C[];
extern s32 D_800A7328[];
extern s32 D_800A7334[];
extern s32 D_800A7340[];
extern s32 D_800A734C[];
extern s32 D_800A7358[];
extern s32 D_800A7364[];
extern s32 D_800A7370[];
extern s32 D_800A73A0[];
extern s32 D_800A73AC[];
extern s32 D_800A73B8[];
extern s32 D_800A73C4[];
extern s32 D_800A73D0[];
extern s32 D_800A73DC[];
extern s32 D_800A73E8[];
extern s32 D_800A73F4[];
extern s32 D_800A7424[];
extern s32 D_800A7430[];
extern s32 D_800A743C[];
extern s32 D_800A7448[];
extern s32 D_800A7454[];
extern s32 D_800A7460[];
extern s32 D_800A746C[];
extern s32 D_800A7478[];
extern s32 D_800A74A8[];
extern s32 D_800A74B4[];
extern s32 D_800A74C0[];
extern s32 D_800A74CC[];
extern s32 D_800A74D8[];
extern s32 D_800A74E4[];
extern s32 D_800A74F0[];
extern s32 D_800A74FC[];
extern s32 D_800A752C[];
extern s32 D_800A7538[];
extern s32 D_800A7544[];
extern s32 D_800A7550[];
extern s32 D_800A755C[];
extern s32 D_800A7568[];
extern s32 D_800A7574[];
extern s32 D_800A7580[];
extern s32 D_800A75B0[];
extern s32 D_800A75BC[];
extern s32 D_800A75C8[];
extern s32 D_800A75D4[];
extern s32 D_800A75E0[];
extern s32 D_800A75EC[];
extern s32 D_800A75F8[];
extern s32 D_800A7604[];
extern s32 D_800A7634[];
extern s32 D_800A7640[];
extern s32 D_800A764C[];
extern s32 D_800A7658[];
extern s32 D_800A7664[];
extern s32 D_800A7670[];
extern s32 D_800A767C[];
extern s32 D_800A7688[];
extern s32 D_800A76B8[];
extern s32 D_800A76C4[];
extern s32 D_800A76D0[];
extern s32 D_800A76DC[];
extern s32 D_800A76E8[];
extern s32 D_800A76F4[];
extern s32 D_800A7700[];
extern s32 D_800A770C[];
extern s32 D_800A773C[];
extern s32 D_800A7748[];
extern s32 D_800A7754[];
extern s32 D_800A7760[];
extern s32 D_800A776C[];
extern s32 D_800A7778[];
extern s32 D_800A7784[];
extern s32 D_800A7790[];
extern s32 D_800A77C0[];
extern s32 D_800A77CC[];
extern s32 D_800A77D8[];
extern s32 D_800A77E4[];
extern s32 D_800A77F0[];
extern s32 D_800A77FC[];
extern s32 D_800A7808[];
extern s32 D_800A7814[];
extern s32 D_800A7844[];
extern s32 D_800A7850[];
extern s32 D_800A785C[];
extern s32 D_800A7868[];
extern s32 D_800A7874[];
extern s32 D_800A7880[];
extern s32 D_800A788C[];
extern s32 D_800A7898[];
extern s32 D_800A78C8[];
extern s32 D_800A78D4[];
extern s32 D_800A78E0[];
extern s32 D_800A78EC[];
extern s32 D_800A78F8[];
extern s32 D_800A7904[];
extern s32 D_800A7910[];
extern s32 D_800A791C[];
extern s32 D_800A794C[];
extern s32 D_800A7958[];
extern s32 D_800A7964[];
extern s32 D_800A7970[];
extern s32 D_800A797C[];
extern s32 D_800A7988[];
extern s32 D_800A7994[];
extern s32 D_800A79A0[];
extern s32 D_800A79D0[];
extern s32 D_800A79DC[];
extern s32 D_800A79E8[];
extern s32 D_800A79F4[];
extern s32 D_800A7A00[];
extern s32 D_800A7A0C[];
extern s32 D_800A7A18[];
extern s32 D_800A7A24[];
extern s32 D_800A7A54[];
extern s32 D_800A7A60[];
extern s32 D_800A7A6C[];
extern s32 D_800A7A78[];
extern s32 D_800A7A84[];
extern s32 D_800A7A90[];
extern s32 D_800A7A9C[];
extern s32 D_800A7AA8[];
extern s32 D_800A7AD8[];
extern s32 D_800A7AE4[];
extern s32 D_800A7AF0[];
extern s32 D_800A7AFC[];
extern s32 D_800A7B08[];
extern s32 D_800A7B14[];
extern s32 D_800A7B20[];
extern s32 D_800A7B2C[];
extern s32 D_800A7B5C[];
extern s32 D_800A7B68[];
extern s32 D_800A7B74[];
extern s32 D_800A7B80[];
extern s32 D_800A7B8C[];
extern s32 D_800A7B98[];
extern s32 D_800A7BA4[];
extern s32 D_800A7BB0[];
extern s32 D_800A7BE0[];
extern s32 D_800A7BEC[];
extern s32 D_800A7BF8[];
extern s32 D_800A7C04[];
extern s32 D_800A7C10[];
extern s32 D_800A7C1C[];
extern s32 D_800A7C28[];
extern s32 D_800A7C34[];
extern s32 D_800A7C64[];
extern s32 D_800A7C70[];
extern s32 D_800A7C7C[];
extern s32 D_800A7C88[];
extern s32 D_800A7C94[];
extern s32 D_800A7CA0[];
extern s32 D_800A7CAC[];
extern s32 D_800A7CB8[];
extern s32 D_800A7CE8[];
extern s32 D_800A7CF4[];
extern s32 D_800A7D00[];
extern s32 D_800A7D0C[];
extern s32 D_800A7D18[];
extern s32 D_800A7D24[];
extern s32 D_800A7D30[];
extern s32 D_800A7D3C[];
extern s32 D_800A7D6C[];
extern s32 D_800A7D78[];
extern s32 D_800A7D84[];
extern s32 D_800A7D90[];
extern s32 D_800A7D9C[];
extern s32 D_800A7DA8[];
extern s32 D_800A7DB4[];
extern s32 D_800A7DC0[];
extern s32 D_800A7DF0[];
extern s32 D_800A7DFC[];
extern s32 D_800A7E08[];
extern s32 D_800A7E14[];
extern s32 D_800A7E20[];
extern s32 D_800A7E2C[];
extern s32 D_800A7E38[];
extern s32 D_800A7E44[];
extern s32 D_800A7E74[];
extern s32 D_800A7E80[];
extern s32 D_800A7E8C[];
extern s32 D_800A7E98[];
extern s32 D_800A7EA4[];
extern s32 D_800A7EB0[];
extern s32 D_800A7EBC[];
extern s32 D_800A7EC8[];
extern s32 D_800A7EF8[];
extern s32 D_800A7F04[];
extern s32 D_800A7F10[];
extern s32 D_800A7F1C[];
extern s32 D_800A7F28[];
extern s32 D_800A7F34[];
extern s32 D_800A7F40[];
extern s32 D_800A7F4C[];
extern s32 D_800A7F7C[];
extern s32 D_800A7F88[];
extern s32 D_800A7F94[];
extern s32 D_800A7FA0[];
extern s32 D_800A7FAC[];
extern s32 D_800A7FB8[];
extern s32 D_800A7FC4[];
extern s32 D_800A7FD0[];
extern s32 D_800A8000[];
extern s32 D_800A800C[];
extern s32 D_800A8018[];
extern s32 D_800A8024[];
extern s32 D_800A8030[];
extern s32 D_800A803C[];
extern s32 D_800A8048[];
extern s32 D_800A8054[];
extern s32 D_800A8084[];
extern s32 D_800A8090[];
extern s32 D_800A809C[];
extern s32 D_800A80A8[];
extern s32 D_800A80B4[];
extern s32 D_800A80C0[];
extern s32 D_800A80CC[];
extern s32 D_800A80D8[];
extern s32 D_800A8108[];
extern s32 D_800A8114[];
extern s32 D_800A8120[];
extern s32 D_800A812C[];
extern s32 D_800A8138[];
extern s32 D_800A8144[];
extern s32 D_800A8150[];
extern s32 D_800A815C[];
extern s32 D_800A548C[];
extern s32 D_800A5510[];
extern s32 D_800A5594[];
extern s32 D_800A5618[];
extern s32 D_800A569C[];
extern s32 D_800A5720[];
extern s32 D_800A57A4[];
extern s32 D_800A5828[];
extern s32 D_800A58AC[];
extern s32 D_800A5930[];
extern s32 D_800A59B4[];
extern s32 D_800A5A38[];
extern s32 D_800A5ABC[];
extern s32 D_800A5B40[];
extern s32 D_800A5BC4[];
extern s32 D_800A5C48[];
extern s32 D_800A5CCC[];
extern s32 D_800A5D50[];
extern s32 D_800A5DD4[];
extern s32 D_800A5E58[];
extern s32 D_800A5EDC[];
extern s32 D_800A5F60[];
extern s32 D_800A5FE4[];
extern s32 D_800A6068[];
extern s32 D_800A60EC[];
extern s32 D_800A6170[];
extern s32 D_800A61F4[];
extern s32 D_800A6278[];
extern s32 D_800A62FC[];
extern s32 D_800A6380[];
extern s32 D_800A6404[];
extern s32 D_800A6488[];
extern s32 D_800A650C[];
extern s32 D_800A6590[];
extern s32 D_800A6614[];
extern s32 D_800A6698[];
extern s32 D_800A671C[];
extern s32 D_800A67A0[];
extern s32 D_800A6824[];
extern s32 D_800A68A8[];
extern s32 D_800A692C[];
extern s32 D_800A69B0[];
extern s32 D_800A6A34[];
extern s32 D_800A6AB8[];
extern s32 D_800A6B3C[];
extern s32 D_800A6BC0[];
extern s32 D_800A6C44[];
extern s32 D_800A6CC8[];
extern s32 D_800A6D4C[];
extern s32 D_800A6DD0[];
extern s32 D_800A6E54[];
extern s32 D_800A6ED8[];
extern s32 D_800A6F5C[];
extern s32 D_800A6FE0[];
extern s32 D_800A7064[];
extern s32 D_800A70E8[];
extern s32 D_800A716C[];
extern s32 D_800A71F0[];
extern s32 D_800A7274[];
extern s32 D_800A72F8[];
extern s32 D_800A737C[];
extern s32 D_800A7400[];
extern s32 D_800A7484[];
extern s32 D_800A7508[];
extern s32 D_800A758C[];
extern s32 D_800A7610[];
extern s32 D_800A7694[];
extern s32 D_800A7718[];
extern s32 D_800A779C[];
extern s32 D_800A7820[];
extern s32 D_800A78A4[];
extern s32 D_800A7928[];
extern s32 D_800A79AC[];
extern s32 D_800A7A30[];
extern s32 D_800A7AB4[];
extern s32 D_800A7B38[];
extern s32 D_800A7BBC[];
extern s32 D_800A7C40[];
extern s32 D_800A7CC4[];
extern s32 D_800A7D48[];
extern s32 D_800A7DCC[];
extern s32 D_800A7E50[];
extern s32 D_800A7ED4[];
extern s32 D_800A7F58[];
extern s32 D_800A7FDC[];
extern s32 D_800A8060[];
extern s32 D_800A80E4[];
extern s32 D_800A8168[];
extern s32 D_800A85B4[];
extern s32 D_800A85C0[];
extern s32 D_800A85CC[];
extern s32 D_800A85D8[];
extern s32 D_800A85E4[];
extern s32 D_800A85F0[];
extern s32 D_800A85FC[];
extern s32 D_800A8608[];
extern s32 D_800A8614[];
extern s32 D_800A8620[];
extern s32 D_800A862C[];
extern s32 D_800A8638[];
extern s32 D_800A8644[];
extern s32 D_800A8650[];
extern s32 D_800A865C[];
extern s32 D_800A8668[];
extern s32 D_800A8674[];
extern s32 D_800A8680[];
extern s32 D_800A883C[];
extern s32 D_800A868C[];
extern s32 D_800A884C[];
extern s32 D_800A86A4[];
extern s32 D_800A885C[];
extern s32 D_800A86BC[];
extern s32 D_800A886C[];
extern s32 D_800A86D4[];
extern s32 D_800A887C[];
extern s32 D_800A86EC[];
extern s32 D_800A888C[];
extern s32 D_800A8704[];
extern s32 D_800A889C[];
extern s32 D_800A871C[];
extern s32 D_800A88AC[];
extern s32 D_800A8734[];
extern s32 D_800A88BC[];
extern s32 D_800A874C[];
extern s32 D_800A88CC[];
extern s32 D_800A8764[];
extern s32 D_800A88DC[];
extern s32 D_800A877C[];
extern s32 D_800A88EC[];
extern s32 D_800A8794[];
extern s32 D_800A88FC[];
extern s32 D_800A8908[];
extern s32 D_800A8914[];
extern s32 D_800A87AC[];
extern s32 D_800A8924[];
extern s32 D_800A87C4[];
extern s32 D_800A8934[];
extern s32 D_800A87DC[];
extern s32 D_800A8944[];
extern s32 D_800A87F4[];
extern s32 D_800A8954[];
extern s32 D_800A880C[];
extern s32 D_800A8964[];
extern s32 D_800A8824[];
extern s32 D_800A8974[];
extern s32 D_800A8980[];
extern s32 D_800A898C[];
extern s32 D_800A8998[];
extern s32 D_800A89A4[];
extern s32 D_800A89B0[];
extern s32 D_800A89BC[];
extern s32 D_800A89C8[];
extern s32 D_800A89D4[];
extern s32 D_800A89E0[];
extern s32 D_800A89EC[];
extern s32 D_800A89F8[];
extern s32 D_800A8A04[];
extern s32 D_800A8A10[];
extern s32 D_800A8A1C[];
extern s32 D_800A8A28[];
extern s32 D_800A8A34[];
extern s32 D_800A8A40[];
extern s32 D_800A8A4C[];
extern s32 D_800A8A60[];
extern s32 D_800A8A74[];
extern s32 D_800A8A88[];
extern s32 D_800A8A9C[];
extern s32 D_800A8AB0[];
extern s32 D_800A8AC4[];
extern s32 D_800A8AD8[];
extern s32 D_800A8AEC[];
extern s32 D_800A8B00[];
extern s32 D_800A8B14[];
extern s32 D_800A8B28[];
extern s32 D_800A8B3C[];
extern s32 D_800A8B50[];
extern s32 D_800A8B64[];
extern s32 D_800A8B78[];
extern s32 D_800A8B8C[];
extern s32 D_800A8BA0[];
extern s32 D_800A8BB4[];
extern s32 D_800A8BC8[];
extern s32 D_800A8BDC[];
extern s32 D_800A8BF0[];
extern s32 D_800A8C04[];
extern s32 D_800A8C18[];
extern s32 D_800A8C2C[];
extern s32 D_800A8C40[];
extern s32 D_800A8C54[];
extern s32 D_800A8C68[];
extern s32 D_800A8C7C[];
extern s32 D_800A8C90[];
extern s32 D_800A8CA4[];
extern s32 D_800A8CB8[];
extern s32 D_800A8CCC[];
extern s32 D_800A8CE0[];
extern s32 D_800A8CF4[];
extern s32 D_800A8D08[];
extern s32 D_800A8D1C[];
extern s32 D_800A8D30[];
extern s32 D_800A8D44[];

StagePoint D_800A4F90 = { 0x2ED, 1, 1, 224, 192, 5, NULL };
StagePoints D_800A4FA0 = { 1, 1, &D_800A4F90 };
StagePoint D_800A4FA8 = { 0x2ED, 4, 2, 224, 192, 5, NULL };
StagePoints D_800A4FB8 = { 4, 1, &D_800A4FA8 };
StagePoint D_800A4FC0 = { 0x2EE, 7, 2, 224, 0x240, 5, NULL };
StagePoints D_800A4FD0 = { 7, 1, &D_800A4FC0 };
StagePoint D_800A4FD8 = { 0x2EC, 12, 3, 240, 0x1D8, 5, NULL };
StagePoints D_800A4FE8 = { 12, 1, &D_800A4FD8 };
StagePoint D_800A4FF0 = { 0x2EC, 12, 4, 240, 0x1D8, 5, NULL };
StagePoints D_800A5000 = { 12, 2, &D_800A4FF0 };
StagePoint D_800A5008 = { 0x2EC, 13, 5, 240, 0x1D8, 5, NULL };
StagePoints D_800A5018 = { 13, 1, &D_800A5008 };
StagePoint D_800A5020 = { 0x2EC, 13, 6, 240, 0x1D8, 5, NULL };
StagePoints D_800A5030 = { 13, 2, &D_800A5020 };
StagePoint D_800A5038 = { 0x2ED, 14, 1, 224, 192, 5, NULL };
StagePoints D_800A5048 = { 14, 1, &D_800A5038 };
StagePoint D_800A5050 = { 0x2ED, 14, 2, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A5060 = { 14, 2, &D_800A5050 };
StagePoint D_800A5068 = { 0x2E8, 15, 1, 176, 0x168, 5, NULL };
StagePoints D_800A5078 = { 15, 1, &D_800A5068 };
StagePoint D_800A5080 = { 0x2ED, 16, 1, 224, 192, 5, NULL };
StagePoints D_800A5090 = { 16, 1, &D_800A5080 };
StagePoint D_800A5098 = { 0x2ED, 16, 1, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A50A8 = { 16, 2, &D_800A5098 };
StagePoint D_800A50B0 = { 0x2E8, 17, 1, 176, 0x168, 5, NULL };
StagePoints D_800A50C0 = { 17, 1, &D_800A50B0 };
StagePoint D_800A50C8 = { 0x2EC, 18, 1, 240, 0x1D8, 5, NULL };
StagePoints D_800A50D8 = { 18, 1, &D_800A50C8 };
StagePoint D_800A50E0 = { 0x2ED, 19, 2, 224, 192, 5, NULL };
StagePoints D_800A50F0 = { 19, 1, &D_800A50E0 };
StagePoint D_800A50F8 = { 0x2ED, 19, 2, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A5108 = { 19, 2, &D_800A50F8 };
StagePoint D_800A5110 = { 0x2ED, 19, 3, 224, 192, 5, NULL };
StagePoints D_800A5120 = { 19, 3, &D_800A5110 };
StagePoint D_800A5128 = { 0x2EC, 19, 5, 240, 0x1D8, 5, NULL };
StagePoints D_800A5138 = { 19, 4, &D_800A5128 };
StagePoint D_800A5140 = { 0x2ED, 20, 2, 224, 192, 5, NULL };
StagePoints D_800A5150 = { 20, 1, &D_800A5140 };
StagePoint D_800A5158 = { 0x2ED, 20, 3, 224, 192, 5, NULL };
StagePoints D_800A5168 = { 20, 2, &D_800A5158 };
StagePoint D_800A5170 = { 0x2ED, 20, 4, 224, 192, 5, NULL };
StagePoints D_800A5180 = { 20, 3, &D_800A5170 };
StagePoint D_800A5188 = { 0x2EC, 20, 6, 240, 0x1D8, 5, NULL };
StagePoints D_800A5198 = { 20, 4, &D_800A5188 };
StagePoint D_800A51A0 = { 0x2EC, 20, 8, 240, 0x1D8, 5, NULL };
StagePoints D_800A51B0 = { 20, 5, &D_800A51A0 };
StagePoint D_800A51B8 = { 0x2EC, 20, 9, 240, 0x1D8, 5, NULL };
StagePoints D_800A51C8 = { 20, 6, &D_800A51B8 };
StagePoint D_800A51D0 = { 0x2ED, 20, 6, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A51E0 = { 20, 7, &D_800A51D0 };
StagePoint D_800A51E8 = { 0x2EE, 21, 1, 224, 0x240, 5, NULL };
StagePoints D_800A51F8 = { 21, 1, &D_800A51E8 };
StagePoint D_800A5200 = { 0x2EC, 22, 3, 240, 0x1D8, 5, NULL };
StagePoints D_800A5210 = { 22, 1, &D_800A5200 };
StagePoint D_800A5218 = { 0x2EE, 23, 1, 224, 0x240, 5, NULL };
StagePoints D_800A5228 = { 23, 1, &D_800A5218 };
StagePoint D_800A5230 = { 0x2EC, 24, 5, 240, 0x1D8, 5, NULL };
StagePoints D_800A5240 = { 24, 1, &D_800A5230 };
StagePoint D_800A5248 = { 0x2ED, 25, 1, 224, 192, 5, NULL };
StagePoints D_800A5258 = { 25, 1, &D_800A5248 };
StagePoint D_800A5260 = { 0x2ED, 25, 1, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A5270 = { 25, 2, &D_800A5260 };
StagePoint D_800A5278 = { 0x2E8, 26, 1, 176, 0x168, 5, NULL };
StagePoints D_800A5288 = { 26, 1, &D_800A5278 };
StagePoint D_800A5290 = { 0x2ED, 27, 1, 224, 192, 5, NULL };
StagePoints D_800A52A0 = { 27, 1, &D_800A5290 };
StagePoint D_800A52A8 = { 0x2ED, 27, 2, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A52B8 = { 27, 2, &D_800A52A8 };
StagePoint D_800A52C0 = { 0x2EC, 28, 3, 240, 0x1D8, 5, NULL };
StagePoints D_800A52D0 = { 28, 1, &D_800A52C0 };
StagePoint D_800A52D8 = { 0x2EC, 28, 4, 240, 0x1D8, 5, NULL };
StagePoints D_800A52E8 = { 28, 2, &D_800A52D8 };
StagePoint D_800A52F0 = { 0x2EE, 28, 2, 224, 0x240, 5, NULL };
StagePoints D_800A5300 = { 28, 3, &D_800A52F0 };
StagePoint D_800A5308 = { 0x2ED, 29, 1, 224, 192, 5, NULL };
StagePoints D_800A5318 = { 29, 1, &D_800A5308 };
StagePoint D_800A5320 = { 0x2ED, 29, 2, 224, 192, 5, NULL };
StagePoints D_800A5330 = { 29, 2, &D_800A5320 };
StagePoint D_800A5338 = { 0x2ED, 29, 2, 0x350, 0x1F8, 5, NULL };
StagePoints D_800A5348 = { 29, 3, &D_800A5338 };
StagePoint D_800A5350 = { 0x2EC, 30, 1, 240, 0x1D8, 5, NULL };
StagePoints D_800A5360 = { 30, 1, &D_800A5350 };
StagePoint D_800A5368 = { 0x2EE, 30, 2, 224, 0x240, 5, NULL };
StagePoints D_800A5378 = { 30, 2, &D_800A5368 };
StagePoints *D_800A5380[] = {
    &D_800A4FA0, &D_800A4FB8, &D_800A4FD0, &D_800A4FE8,
    &D_800A5000, &D_800A5018, &D_800A5030, &D_800A5048,
    &D_800A5060, &D_800A5078, &D_800A5090, &D_800A50A8,
    &D_800A50C0, &D_800A50D8, &D_800A50F0, &D_800A5108,
    &D_800A5120, &D_800A5138, &D_800A5150, &D_800A5168,
    &D_800A5180, &D_800A5198, &D_800A51B0, &D_800A51C8,
    &D_800A51E0, &D_800A51F8, &D_800A5210, &D_800A5228,
    &D_800A5240, &D_800A5258, &D_800A5270, &D_800A5288,
    &D_800A52A0, &D_800A52B8, &D_800A52D0, &D_800A52E8,
    &D_800A5300, &D_800A5318, &D_800A5330, &D_800A5348,
    &D_800A5360, &D_800A5378, NULL,
};
s32 D_800A542C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5438[] = {
    174, 10, 0x60080000,
};
s32 D_800A5444[] = {
    170, 10, 0x60080000,
};
s32 D_800A5450[] = {
    170, 10, 0x60080000,
};
s32 D_800A545C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5468[] = {
    170, 10, 0x60080000,
};
s32 D_800A5474[] = {
    170, 10, 0x60080000,
};
s32 D_800A5480[] = {
    170, 10, 0x60080000,
};
s32 D_800A548C[] = {
    1, (s32)D_800A542C, (s32)D_800A5438, (s32)D_800A5444,
    (s32)D_800A5450, (s32)D_800A545C, (s32)D_800A5468, (s32)D_800A5474,
    (s32)D_800A5480,
};
s32 D_800A54B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A54C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A54D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A54E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A54F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5504[] = {
    0, 0, 0x60040000,
};
s32 D_800A5510[] = {
    0, (s32)D_800A54B0, (s32)D_800A54BC, (s32)D_800A54C8,
    (s32)D_800A54D4, (s32)D_800A54E0, (s32)D_800A54EC, (s32)D_800A54F8,
    (s32)D_800A5504,
};
s32 D_800A5534[] = {
    0, 0, 0x60040000,
};
s32 D_800A5540[] = {
    0, 0, 0x60040000,
};
s32 D_800A554C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5558[] = {
    0, 0, 0x60040000,
};
s32 D_800A5564[] = {
    0, 0, 0x60040000,
};
s32 D_800A5570[] = {
    0, 0, 0x60040000,
};
s32 D_800A557C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5588[] = {
    0, 0, 0x60040000,
};
s32 D_800A5594[] = {
    0, (s32)D_800A5534, (s32)D_800A5540, (s32)D_800A554C,
    (s32)D_800A5558, (s32)D_800A5564, (s32)D_800A5570, (s32)D_800A557C,
    (s32)D_800A5588,
};
s32 D_800A55B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A55C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A55D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A55DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A55E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A55F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5600[] = {
    0, 0, 0x60040000,
};
s32 D_800A560C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5618[] = {
    0, (s32)D_800A55B8, (s32)D_800A55C4, (s32)D_800A55D0,
    (s32)D_800A55DC, (s32)D_800A55E8, (s32)D_800A55F4, (s32)D_800A5600,
    (s32)D_800A560C,
};
s32 D_800A563C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5648[] = {
    174, 10, 0x60080000,
};
s32 D_800A5654[] = {
    170, 10, 0x60080000,
};
s32 D_800A5660[] = {
    170, 10, 0x60080000,
};
s32 D_800A566C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5678[] = {
    182, 10, 0x60080000,
};
s32 D_800A5684[] = {
    71, 10, 0x60080000,
};
s32 D_800A5690[] = {
    71, 10, 0x60080000,
};
s32 D_800A569C[] = {
    1, (s32)D_800A563C, (s32)D_800A5648, (s32)D_800A5654,
    (s32)D_800A5660, (s32)D_800A566C, (s32)D_800A5678, (s32)D_800A5684,
    (s32)D_800A5690,
};
s32 D_800A56C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A56CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A56D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A56E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A56F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A56FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5708[] = {
    0, 0, 0x60040000,
};
s32 D_800A5714[] = {
    0, 0, 0x60040000,
};
s32 D_800A5720[] = {
    0, (s32)D_800A56C0, (s32)D_800A56CC, (s32)D_800A56D8,
    (s32)D_800A56E4, (s32)D_800A56F0, (s32)D_800A56FC, (s32)D_800A5708,
    (s32)D_800A5714,
};
s32 D_800A5744[] = {
    0, 0, 0x60040000,
};
s32 D_800A5750[] = {
    0, 0, 0x60040000,
};
s32 D_800A575C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5768[] = {
    0, 0, 0x60040000,
};
s32 D_800A5774[] = {
    0, 0, 0x60040000,
};
s32 D_800A5780[] = {
    0, 0, 0x60040000,
};
s32 D_800A578C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5798[] = {
    0, 0, 0x60040000,
};
s32 D_800A57A4[] = {
    0, (s32)D_800A5744, (s32)D_800A5750, (s32)D_800A575C,
    (s32)D_800A5768, (s32)D_800A5774, (s32)D_800A5780, (s32)D_800A578C,
    (s32)D_800A5798,
};
s32 D_800A57C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A57D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A57E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A57EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A57F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5804[] = {
    0, 0, 0x60040000,
};
s32 D_800A5810[] = {
    0, 0, 0x60040000,
};
s32 D_800A581C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5828[] = {
    0, (s32)D_800A57C8, (s32)D_800A57D4, (s32)D_800A57E0,
    (s32)D_800A57EC, (s32)D_800A57F8, (s32)D_800A5804, (s32)D_800A5810,
    (s32)D_800A581C,
};
s32 D_800A584C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5858[] = {
    110, 10, 0x60080000,
};
s32 D_800A5864[] = {
    110, 10, 0x60080000,
};
s32 D_800A5870[] = {
    110, 10, 0x60080000,
};
s32 D_800A587C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5888[] = {
    182, 10, 0x60080000,
};
s32 D_800A5894[] = {
    182, 10, 0x60080000,
};
s32 D_800A58A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A58AC[] = {
    1, (s32)D_800A584C, (s32)D_800A5858, (s32)D_800A5864,
    (s32)D_800A5870, (s32)D_800A587C, (s32)D_800A5888, (s32)D_800A5894,
    (s32)D_800A58A0,
};
s32 D_800A58D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A58DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A58E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A58F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5900[] = {
    0, 0, 0x60040000,
};
s32 D_800A590C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5918[] = {
    0, 0, 0x60040000,
};
s32 D_800A5924[] = {
    0, 0, 0x60040000,
};
s32 D_800A5930[] = {
    0, (s32)D_800A58D0, (s32)D_800A58DC, (s32)D_800A58E8,
    (s32)D_800A58F4, (s32)D_800A5900, (s32)D_800A590C, (s32)D_800A5918,
    (s32)D_800A5924,
};
s32 D_800A5954[] = {
    0, 0, 0x60040000,
};
s32 D_800A5960[] = {
    0, 0, 0x60040000,
};
s32 D_800A596C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5978[] = {
    0, 0, 0x60040000,
};
s32 D_800A5984[] = {
    0, 0, 0x60040000,
};
s32 D_800A5990[] = {
    0, 0, 0x60040000,
};
s32 D_800A599C[] = {
    0, 0, 0x60040000,
};
s32 D_800A59A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59B4[] = {
    0, (s32)D_800A5954, (s32)D_800A5960, (s32)D_800A596C,
    (s32)D_800A5978, (s32)D_800A5984, (s32)D_800A5990, (s32)D_800A599C,
    (s32)D_800A59A8,
};
s32 D_800A59D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A59F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A59FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A38[] = {
    0, (s32)D_800A59D8, (s32)D_800A59E4, (s32)D_800A59F0,
    (s32)D_800A59FC, (s32)D_800A5A08, (s32)D_800A5A14, (s32)D_800A5A20,
    (s32)D_800A5A2C,
};
s32 D_800A5A5C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5A68[] = {
    110, 10, 0x60080000,
};
s32 D_800A5A74[] = {
    110, 10, 0x60080000,
};
s32 D_800A5A80[] = {
    110, 10, 0x60080000,
};
s32 D_800A5A8C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5A98[] = {
    110, 10, 0x60080000,
};
s32 D_800A5AA4[] = {
    110, 10, 0x60080000,
};
s32 D_800A5AB0[] = {
    110, 10, 0x60080000,
};
s32 D_800A5ABC[] = {
    1, (s32)D_800A5A5C, (s32)D_800A5A68, (s32)D_800A5A74,
    (s32)D_800A5A80, (s32)D_800A5A8C, (s32)D_800A5A98, (s32)D_800A5AA4,
    (s32)D_800A5AB0,
};
s32 D_800A5AE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B28[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B34[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B40[] = {
    0, (s32)D_800A5AE0, (s32)D_800A5AEC, (s32)D_800A5AF8,
    (s32)D_800A5B04, (s32)D_800A5B10, (s32)D_800A5B1C, (s32)D_800A5B28,
    (s32)D_800A5B34,
};
s32 D_800A5B64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BC4[] = {
    0, (s32)D_800A5B64, (s32)D_800A5B70, (s32)D_800A5B7C,
    (s32)D_800A5B88, (s32)D_800A5B94, (s32)D_800A5BA0, (s32)D_800A5BAC,
    (s32)D_800A5BB8,
};
s32 D_800A5BE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C48[] = {
    0, (s32)D_800A5BE8, (s32)D_800A5BF4, (s32)D_800A5C00,
    (s32)D_800A5C0C, (s32)D_800A5C18, (s32)D_800A5C24, (s32)D_800A5C30,
    (s32)D_800A5C3C,
};
s32 D_800A5C6C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5C78[] = {
    182, 10, 0x60080000,
};
s32 D_800A5C84[] = {
    182, 10, 0x60080000,
};
s32 D_800A5C90[] = {
    182, 10, 0x60080000,
};
s32 D_800A5C9C[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CA8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CB4[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CC0[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CCC[] = {
    1, (s32)D_800A5C6C, (s32)D_800A5C78, (s32)D_800A5C84,
    (s32)D_800A5C90, (s32)D_800A5C9C, (s32)D_800A5CA8, (s32)D_800A5CB4,
    (s32)D_800A5CC0,
};
s32 D_800A5CF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D38[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D44[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D50[] = {
    0, (s32)D_800A5CF0, (s32)D_800A5CFC, (s32)D_800A5D08,
    (s32)D_800A5D14, (s32)D_800A5D20, (s32)D_800A5D2C, (s32)D_800A5D38,
    (s32)D_800A5D44,
};
s32 D_800A5D74[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D80[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D98[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DD4[] = {
    0, (s32)D_800A5D74, (s32)D_800A5D80, (s32)D_800A5D8C,
    (s32)D_800A5D98, (s32)D_800A5DA4, (s32)D_800A5DB0, (s32)D_800A5DBC,
    (s32)D_800A5DC8,
};
s32 D_800A5DF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E28[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E34[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E40[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E58[] = {
    0, (s32)D_800A5DF8, (s32)D_800A5E04, (s32)D_800A5E10,
    (s32)D_800A5E1C, (s32)D_800A5E28, (s32)D_800A5E34, (s32)D_800A5E40,
    (s32)D_800A5E4C,
};
s32 D_800A5E7C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5E88[] = {
    174, 10, 0x60080000,
};
s32 D_800A5E94[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EA0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EAC[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EB8[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EC4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5ED0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EDC[] = {
    4, (s32)D_800A5E7C, (s32)D_800A5E88, (s32)D_800A5E94,
    (s32)D_800A5EA0, (s32)D_800A5EAC, (s32)D_800A5EB8, (s32)D_800A5EC4,
    (s32)D_800A5ED0,
};
s32 D_800A5F00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F60[] = {
    0, (s32)D_800A5F00, (s32)D_800A5F0C, (s32)D_800A5F18,
    (s32)D_800A5F24, (s32)D_800A5F30, (s32)D_800A5F3C, (s32)D_800A5F48,
    (s32)D_800A5F54,
};
s32 D_800A5F84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FE4[] = {
    0, (s32)D_800A5F84, (s32)D_800A5F90, (s32)D_800A5F9C,
    (s32)D_800A5FA8, (s32)D_800A5FB4, (s32)D_800A5FC0, (s32)D_800A5FCC,
    (s32)D_800A5FD8,
};
s32 D_800A6008[] = {
    0, 0, 0x60040000,
};
s32 D_800A6014[] = {
    0, 0, 0x60040000,
};
s32 D_800A6020[] = {
    0, 0, 0x60040000,
};
s32 D_800A602C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6038[] = {
    0, 0, 0x60040000,
};
s32 D_800A6044[] = {
    0, 0, 0x60040000,
};
s32 D_800A6050[] = {
    0, 0, 0x60040000,
};
s32 D_800A605C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6068[] = {
    0, (s32)D_800A6008, (s32)D_800A6014, (s32)D_800A6020,
    (s32)D_800A602C, (s32)D_800A6038, (s32)D_800A6044, (s32)D_800A6050,
    (s32)D_800A605C,
};
s32 D_800A608C[] = {
    174, 10, 0x60080000,
};
s32 D_800A6098[] = {
    174, 10, 0x60080000,
};
s32 D_800A60A4[] = {
    170, 10, 0x60080000,
};
s32 D_800A60B0[] = {
    170, 10, 0x60080000,
};
s32 D_800A60BC[] = {
    170, 10, 0x60080000,
};
s32 D_800A60C8[] = {
    170, 10, 0x60080000,
};
s32 D_800A60D4[] = {
    170, 10, 0x60080000,
};
s32 D_800A60E0[] = {
    170, 10, 0x60080000,
};
s32 D_800A60EC[] = {
    5, (s32)D_800A608C, (s32)D_800A6098, (s32)D_800A60A4,
    (s32)D_800A60B0, (s32)D_800A60BC, (s32)D_800A60C8, (s32)D_800A60D4,
    (s32)D_800A60E0,
};
s32 D_800A6110[] = {
    0, 0, 0x60040000,
};
s32 D_800A611C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6128[] = {
    0, 0, 0x60040000,
};
s32 D_800A6134[] = {
    0, 0, 0x60040000,
};
s32 D_800A6140[] = {
    0, 0, 0x60040000,
};
s32 D_800A614C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6158[] = {
    0, 0, 0x60040000,
};
s32 D_800A6164[] = {
    0, 0, 0x60040000,
};
s32 D_800A6170[] = {
    0, (s32)D_800A6110, (s32)D_800A611C, (s32)D_800A6128,
    (s32)D_800A6134, (s32)D_800A6140, (s32)D_800A614C, (s32)D_800A6158,
    (s32)D_800A6164,
};
s32 D_800A6194[] = {
    0, 0, 0x60040000,
};
s32 D_800A61A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A61B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A61C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A61D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A61E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A61F4[] = {
    0, (s32)D_800A6194, (s32)D_800A61A0, (s32)D_800A61AC,
    (s32)D_800A61B8, (s32)D_800A61C4, (s32)D_800A61D0, (s32)D_800A61DC,
    (s32)D_800A61E8,
};
s32 D_800A6218[] = {
    0, 0, 0x60040000,
};
s32 D_800A6224[] = {
    0, 0, 0x60040000,
};
s32 D_800A6230[] = {
    0, 0, 0x60040000,
};
s32 D_800A623C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6248[] = {
    0, 0, 0x60040000,
};
s32 D_800A6254[] = {
    0, 0, 0x60040000,
};
s32 D_800A6260[] = {
    0, 0, 0x60040000,
};
s32 D_800A626C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6278[] = {
    0, (s32)D_800A6218, (s32)D_800A6224, (s32)D_800A6230,
    (s32)D_800A623C, (s32)D_800A6248, (s32)D_800A6254, (s32)D_800A6260,
    (s32)D_800A626C,
};
s32 D_800A629C[] = {
    174, 10, 0x60080000,
};
s32 D_800A62A8[] = {
    174, 10, 0x60080000,
};
s32 D_800A62B4[] = {
    170, 10, 0x60080000,
};
s32 D_800A62C0[] = {
    170, 10, 0x60080000,
};
s32 D_800A62CC[] = {
    170, 10, 0x60080000,
};
s32 D_800A62D8[] = {
    170, 10, 0x60080000,
};
s32 D_800A62E4[] = {
    170, 10, 0x60080000,
};
s32 D_800A62F0[] = {
    170, 10, 0x60080000,
};
s32 D_800A62FC[] = {
    4, (s32)D_800A629C, (s32)D_800A62A8, (s32)D_800A62B4,
    (s32)D_800A62C0, (s32)D_800A62CC, (s32)D_800A62D8, (s32)D_800A62E4,
    (s32)D_800A62F0,
};
s32 D_800A6320[] = {
    0, 0, 0x60040000,
};
s32 D_800A632C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6338[] = {
    0, 0, 0x60040000,
};
s32 D_800A6344[] = {
    0, 0, 0x60040000,
};
s32 D_800A6350[] = {
    0, 0, 0x60040000,
};
s32 D_800A635C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6368[] = {
    0, 0, 0x60040000,
};
s32 D_800A6374[] = {
    0, 0, 0x60040000,
};
s32 D_800A6380[] = {
    0, (s32)D_800A6320, (s32)D_800A632C, (s32)D_800A6338,
    (s32)D_800A6344, (s32)D_800A6350, (s32)D_800A635C, (s32)D_800A6368,
    (s32)D_800A6374,
};
s32 D_800A63A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A63A4, (s32)D_800A63B0, (s32)D_800A63BC,
    (s32)D_800A63C8, (s32)D_800A63D4, (s32)D_800A63E0, (s32)D_800A63EC,
    (s32)D_800A63F8,
};
s32 D_800A6428[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6428, (s32)D_800A6434, (s32)D_800A6440,
    (s32)D_800A644C, (s32)D_800A6458, (s32)D_800A6464, (s32)D_800A6470,
    (s32)D_800A647C,
};
s32 D_800A64AC[] = {
    174, 10, 0x60080000,
};
s32 D_800A64B8[] = {
    174, 10, 0x60080000,
};
s32 D_800A64C4[] = {
    170, 10, 0x60080000,
};
s32 D_800A64D0[] = {
    170, 10, 0x60080000,
};
s32 D_800A64DC[] = {
    170, 10, 0x60080000,
};
s32 D_800A64E8[] = {
    170, 10, 0x60080000,
};
s32 D_800A64F4[] = {
    170, 10, 0x60080000,
};
s32 D_800A6500[] = {
    170, 10, 0x60080000,
};
s32 D_800A650C[] = {
    5, (s32)D_800A64AC, (s32)D_800A64B8, (s32)D_800A64C4,
    (s32)D_800A64D0, (s32)D_800A64DC, (s32)D_800A64E8, (s32)D_800A64F4,
    (s32)D_800A6500,
};
s32 D_800A6530[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6530, (s32)D_800A653C, (s32)D_800A6548,
    (s32)D_800A6554, (s32)D_800A6560, (s32)D_800A656C, (s32)D_800A6578,
    (s32)D_800A6584,
};
s32 D_800A65B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6608[] = {
    0, 0, 0x60040000,
};
s32 D_800A6614[] = {
    0, (s32)D_800A65B4, (s32)D_800A65C0, (s32)D_800A65CC,
    (s32)D_800A65D8, (s32)D_800A65E4, (s32)D_800A65F0, (s32)D_800A65FC,
    (s32)D_800A6608,
};
s32 D_800A6638[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6638, (s32)D_800A6644, (s32)D_800A6650,
    (s32)D_800A665C, (s32)D_800A6668, (s32)D_800A6674, (s32)D_800A6680,
    (s32)D_800A668C,
};
s32 D_800A66BC[] = {
    182, 10, 0x60080000,
};
s32 D_800A66C8[] = {
    182, 10, 0x60080000,
};
s32 D_800A66D4[] = {
    182, 10, 0x60080000,
};
s32 D_800A66E0[] = {
    182, 10, 0x60080000,
};
s32 D_800A66EC[] = {
    71, 10, 0x60080000,
};
s32 D_800A66F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A6704[] = {
    71, 10, 0x60080000,
};
s32 D_800A6710[] = {
    71, 10, 0x60080000,
};
s32 D_800A671C[] = {
    5, (s32)D_800A66BC, (s32)D_800A66C8, (s32)D_800A66D4,
    (s32)D_800A66E0, (s32)D_800A66EC, (s32)D_800A66F8, (s32)D_800A6704,
    (s32)D_800A6710,
};
s32 D_800A6740[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6740, (s32)D_800A674C, (s32)D_800A6758,
    (s32)D_800A6764, (s32)D_800A6770, (s32)D_800A677C, (s32)D_800A6788,
    (s32)D_800A6794,
};
s32 D_800A67C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6800[] = {
    0, 0, 0x60040000,
};
s32 D_800A680C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6818[] = {
    0, 0, 0x60040000,
};
s32 D_800A6824[] = {
    0, (s32)D_800A67C4, (s32)D_800A67D0, (s32)D_800A67DC,
    (s32)D_800A67E8, (s32)D_800A67F4, (s32)D_800A6800, (s32)D_800A680C,
    (s32)D_800A6818,
};
s32 D_800A6848[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6848, (s32)D_800A6854, (s32)D_800A6860,
    (s32)D_800A686C, (s32)D_800A6878, (s32)D_800A6884, (s32)D_800A6890,
    (s32)D_800A689C,
};
s32 D_800A68CC[] = {
    110, 10, 0x60080000,
};
s32 D_800A68D8[] = {
    110, 10, 0x60080000,
};
s32 D_800A68E4[] = {
    110, 10, 0x60080000,
};
s32 D_800A68F0[] = {
    110, 10, 0x60080000,
};
s32 D_800A68FC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6908[] = {
    110, 10, 0x60080000,
};
s32 D_800A6914[] = {
    110, 10, 0x60080000,
};
s32 D_800A6920[] = {
    110, 10, 0x60080000,
};
s32 D_800A692C[] = {
    1, (s32)D_800A68CC, (s32)D_800A68D8, (s32)D_800A68E4,
    (s32)D_800A68F0, (s32)D_800A68FC, (s32)D_800A6908, (s32)D_800A6914,
    (s32)D_800A6920,
};
s32 D_800A6950[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6950, (s32)D_800A695C, (s32)D_800A6968,
    (s32)D_800A6974, (s32)D_800A6980, (s32)D_800A698C, (s32)D_800A6998,
    (s32)D_800A69A4,
};
s32 D_800A69D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A04[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A34[] = {
    0, (s32)D_800A69D4, (s32)D_800A69E0, (s32)D_800A69EC,
    (s32)D_800A69F8, (s32)D_800A6A04, (s32)D_800A6A10, (s32)D_800A6A1C,
    (s32)D_800A6A28,
};
s32 D_800A6A58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AB8[] = {
    0, (s32)D_800A6A58, (s32)D_800A6A64, (s32)D_800A6A70,
    (s32)D_800A6A7C, (s32)D_800A6A88, (s32)D_800A6A94, (s32)D_800A6AA0,
    (s32)D_800A6AAC,
};
s32 D_800A6ADC[] = {
    182, 10, 0x60080000,
};
s32 D_800A6AE8[] = {
    182, 10, 0x60080000,
};
s32 D_800A6AF4[] = {
    182, 10, 0x60080000,
};
s32 D_800A6B00[] = {
    182, 10, 0x60080000,
};
s32 D_800A6B0C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B18[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B24[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B30[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B3C[] = {
    1, (s32)D_800A6ADC, (s32)D_800A6AE8, (s32)D_800A6AF4,
    (s32)D_800A6B00, (s32)D_800A6B0C, (s32)D_800A6B18, (s32)D_800A6B24,
    (s32)D_800A6B30,
};
s32 D_800A6B60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BC0[] = {
    0, (s32)D_800A6B60, (s32)D_800A6B6C, (s32)D_800A6B78,
    (s32)D_800A6B84, (s32)D_800A6B90, (s32)D_800A6B9C, (s32)D_800A6BA8,
    (s32)D_800A6BB4,
};
s32 D_800A6BE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C38[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C44[] = {
    0, (s32)D_800A6BE4, (s32)D_800A6BF0, (s32)D_800A6BFC,
    (s32)D_800A6C08, (s32)D_800A6C14, (s32)D_800A6C20, (s32)D_800A6C2C,
    (s32)D_800A6C38,
};
s32 D_800A6C68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C98[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CC8[] = {
    0, (s32)D_800A6C68, (s32)D_800A6C74, (s32)D_800A6C80,
    (s32)D_800A6C8C, (s32)D_800A6C98, (s32)D_800A6CA4, (s32)D_800A6CB0,
    (s32)D_800A6CBC,
};
s32 D_800A6CEC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6CF8[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D04[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D10[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D1C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D28[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D34[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D40[] = {
    110, 10, 0x60080000,
};
s32 D_800A6D4C[] = {
    3, (s32)D_800A6CEC, (s32)D_800A6CF8, (s32)D_800A6D04,
    (s32)D_800A6D10, (s32)D_800A6D1C, (s32)D_800A6D28, (s32)D_800A6D34,
    (s32)D_800A6D40,
};
s32 D_800A6D70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DD0[] = {
    0, (s32)D_800A6D70, (s32)D_800A6D7C, (s32)D_800A6D88,
    (s32)D_800A6D94, (s32)D_800A6DA0, (s32)D_800A6DAC, (s32)D_800A6DB8,
    (s32)D_800A6DC4,
};
s32 D_800A6DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E24[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E30[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E54[] = {
    0, (s32)D_800A6DF4, (s32)D_800A6E00, (s32)D_800A6E0C,
    (s32)D_800A6E18, (s32)D_800A6E24, (s32)D_800A6E30, (s32)D_800A6E3C,
    (s32)D_800A6E48,
};
s32 D_800A6E78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E84[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6E78, (s32)D_800A6E84, (s32)D_800A6E90,
    (s32)D_800A6E9C, (s32)D_800A6EA8, (s32)D_800A6EB4, (s32)D_800A6EC0,
    (s32)D_800A6ECC,
};
s32 D_800A6EFC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F08[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F14[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F20[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F2C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F38[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F44[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F50[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F5C[] = {
    3, (s32)D_800A6EFC, (s32)D_800A6F08, (s32)D_800A6F14,
    (s32)D_800A6F20, (s32)D_800A6F2C, (s32)D_800A6F38, (s32)D_800A6F44,
    (s32)D_800A6F50,
};
s32 D_800A6F80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F98[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FE0[] = {
    0, (s32)D_800A6F80, (s32)D_800A6F8C, (s32)D_800A6F98,
    (s32)D_800A6FA4, (s32)D_800A6FB0, (s32)D_800A6FBC, (s32)D_800A6FC8,
    (s32)D_800A6FD4,
};
s32 D_800A7004[] = {
    0, 0, 0x60040000,
};
s32 D_800A7010[] = {
    0, 0, 0x60040000,
};
s32 D_800A701C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7028[] = {
    0, 0, 0x60040000,
};
s32 D_800A7034[] = {
    0, 0, 0x60040000,
};
s32 D_800A7040[] = {
    0, 0, 0x60040000,
};
s32 D_800A704C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7058[] = {
    0, 0, 0x60040000,
};
s32 D_800A7064[] = {
    0, (s32)D_800A7004, (s32)D_800A7010, (s32)D_800A701C,
    (s32)D_800A7028, (s32)D_800A7034, (s32)D_800A7040, (s32)D_800A704C,
    (s32)D_800A7058,
};
s32 D_800A7088[] = {
    0, 0, 0x60040000,
};
s32 D_800A7094[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7088, (s32)D_800A7094, (s32)D_800A70A0,
    (s32)D_800A70AC, (s32)D_800A70B8, (s32)D_800A70C4, (s32)D_800A70D0,
    (s32)D_800A70DC,
};
s32 D_800A710C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7118[] = {
    182, 10, 0x60080000,
};
s32 D_800A7124[] = {
    182, 10, 0x60080000,
};
s32 D_800A7130[] = {
    182, 10, 0x60080000,
};
s32 D_800A713C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7148[] = {
    71, 10, 0x60080000,
};
s32 D_800A7154[] = {
    71, 10, 0x60080000,
};
s32 D_800A7160[] = {
    71, 10, 0x60080000,
};
s32 D_800A716C[] = {
    2, (s32)D_800A710C, (s32)D_800A7118, (s32)D_800A7124,
    (s32)D_800A7130, (s32)D_800A713C, (s32)D_800A7148, (s32)D_800A7154,
    (s32)D_800A7160,
};
s32 D_800A7190[] = {
    0, 0, 0x60040000,
};
s32 D_800A719C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7190, (s32)D_800A719C, (s32)D_800A71A8,
    (s32)D_800A71B4, (s32)D_800A71C0, (s32)D_800A71CC, (s32)D_800A71D8,
    (s32)D_800A71E4,
};
s32 D_800A7214[] = {
    0, 0, 0x60040000,
};
s32 D_800A7220[] = {
    0, 0, 0x60040000,
};
s32 D_800A722C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7238[] = {
    0, 0, 0x60040000,
};
s32 D_800A7244[] = {
    0, 0, 0x60040000,
};
s32 D_800A7250[] = {
    0, 0, 0x60040000,
};
s32 D_800A725C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7268[] = {
    0, 0, 0x60040000,
};
s32 D_800A7274[] = {
    0, (s32)D_800A7214, (s32)D_800A7220, (s32)D_800A722C,
    (s32)D_800A7238, (s32)D_800A7244, (s32)D_800A7250, (s32)D_800A725C,
    (s32)D_800A7268,
};
s32 D_800A7298[] = {
    0, 0, 0x60040000,
};
s32 D_800A72A4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7298, (s32)D_800A72A4, (s32)D_800A72B0,
    (s32)D_800A72BC, (s32)D_800A72C8, (s32)D_800A72D4, (s32)D_800A72E0,
    (s32)D_800A72EC,
};
s32 D_800A731C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7328[] = {
    182, 10, 0x60080000,
};
s32 D_800A7334[] = {
    182, 10, 0x60080000,
};
s32 D_800A7340[] = {
    182, 10, 0x60080000,
};
s32 D_800A734C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7358[] = {
    71, 10, 0x60080000,
};
s32 D_800A7364[] = {
    71, 10, 0x60080000,
};
s32 D_800A7370[] = {
    71, 10, 0x60080000,
};
s32 D_800A737C[] = {
    5, (s32)D_800A731C, (s32)D_800A7328, (s32)D_800A7334,
    (s32)D_800A7340, (s32)D_800A734C, (s32)D_800A7358, (s32)D_800A7364,
    (s32)D_800A7370,
};
s32 D_800A73A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A73AC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A73A0, (s32)D_800A73AC, (s32)D_800A73B8,
    (s32)D_800A73C4, (s32)D_800A73D0, (s32)D_800A73DC, (s32)D_800A73E8,
    (s32)D_800A73F4,
};
s32 D_800A7424[] = {
    0, 0, 0x60040000,
};
s32 D_800A7430[] = {
    0, 0, 0x60040000,
};
s32 D_800A743C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7448[] = {
    0, 0, 0x60040000,
};
s32 D_800A7454[] = {
    0, 0, 0x60040000,
};
s32 D_800A7460[] = {
    0, 0, 0x60040000,
};
s32 D_800A746C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7478[] = {
    0, 0, 0x60040000,
};
s32 D_800A7484[] = {
    0, (s32)D_800A7424, (s32)D_800A7430, (s32)D_800A743C,
    (s32)D_800A7448, (s32)D_800A7454, (s32)D_800A7460, (s32)D_800A746C,
    (s32)D_800A7478,
};
s32 D_800A74A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74B4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A74A8, (s32)D_800A74B4, (s32)D_800A74C0,
    (s32)D_800A74CC, (s32)D_800A74D8, (s32)D_800A74E4, (s32)D_800A74F0,
    (s32)D_800A74FC,
};
s32 D_800A752C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7538[] = {
    182, 10, 0x60080000,
};
s32 D_800A7544[] = {
    182, 10, 0x60080000,
};
s32 D_800A7550[] = {
    182, 10, 0x60080000,
};
s32 D_800A755C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7568[] = {
    71, 10, 0x60080000,
};
s32 D_800A7574[] = {
    71, 10, 0x60080000,
};
s32 D_800A7580[] = {
    71, 10, 0x60080000,
};
s32 D_800A758C[] = {
    4, (s32)D_800A752C, (s32)D_800A7538, (s32)D_800A7544,
    (s32)D_800A7550, (s32)D_800A755C, (s32)D_800A7568, (s32)D_800A7574,
    (s32)D_800A7580,
};
s32 D_800A75B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75BC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A75B0, (s32)D_800A75BC, (s32)D_800A75C8,
    (s32)D_800A75D4, (s32)D_800A75E0, (s32)D_800A75EC, (s32)D_800A75F8,
    (s32)D_800A7604,
};
s32 D_800A7634[] = {
    0, 0, 0x60040000,
};
s32 D_800A7640[] = {
    0, 0, 0x60040000,
};
s32 D_800A764C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7658[] = {
    0, 0, 0x60040000,
};
s32 D_800A7664[] = {
    0, 0, 0x60040000,
};
s32 D_800A7670[] = {
    0, 0, 0x60040000,
};
s32 D_800A767C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7688[] = {
    0, 0, 0x60040000,
};
s32 D_800A7694[] = {
    0, (s32)D_800A7634, (s32)D_800A7640, (s32)D_800A764C,
    (s32)D_800A7658, (s32)D_800A7664, (s32)D_800A7670, (s32)D_800A767C,
    (s32)D_800A7688,
};
s32 D_800A76B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A76C4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A76B8, (s32)D_800A76C4, (s32)D_800A76D0,
    (s32)D_800A76DC, (s32)D_800A76E8, (s32)D_800A76F4, (s32)D_800A7700,
    (s32)D_800A770C,
};
s32 D_800A773C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7748[] = {
    182, 10, 0x60080000,
};
s32 D_800A7754[] = {
    182, 10, 0x60080000,
};
s32 D_800A7760[] = {
    182, 10, 0x60080000,
};
s32 D_800A776C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7778[] = {
    71, 10, 0x60080000,
};
s32 D_800A7784[] = {
    71, 10, 0x60080000,
};
s32 D_800A7790[] = {
    71, 10, 0x60080000,
};
s32 D_800A779C[] = {
    5, (s32)D_800A773C, (s32)D_800A7748, (s32)D_800A7754,
    (s32)D_800A7760, (s32)D_800A776C, (s32)D_800A7778, (s32)D_800A7784,
    (s32)D_800A7790,
};
s32 D_800A77C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77CC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A77C0, (s32)D_800A77CC, (s32)D_800A77D8,
    (s32)D_800A77E4, (s32)D_800A77F0, (s32)D_800A77FC, (s32)D_800A7808,
    (s32)D_800A7814,
};
s32 D_800A7844[] = {
    0, 0, 0x60040000,
};
s32 D_800A7850[] = {
    0, 0, 0x60040000,
};
s32 D_800A785C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7868[] = {
    0, 0, 0x60040000,
};
s32 D_800A7874[] = {
    0, 0, 0x60040000,
};
s32 D_800A7880[] = {
    0, 0, 0x60040000,
};
s32 D_800A788C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7898[] = {
    0, 0, 0x60040000,
};
s32 D_800A78A4[] = {
    0, (s32)D_800A7844, (s32)D_800A7850, (s32)D_800A785C,
    (s32)D_800A7868, (s32)D_800A7874, (s32)D_800A7880, (s32)D_800A788C,
    (s32)D_800A7898,
};
s32 D_800A78C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A78D4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A78C8, (s32)D_800A78D4, (s32)D_800A78E0,
    (s32)D_800A78EC, (s32)D_800A78F8, (s32)D_800A7904, (s32)D_800A7910,
    (s32)D_800A791C,
};
s32 D_800A794C[] = {
    174, 10, 0x60080000,
};
s32 D_800A7958[] = {
    174, 10, 0x60080000,
};
s32 D_800A7964[] = {
    170, 10, 0x60080000,
};
s32 D_800A7970[] = {
    170, 10, 0x60080000,
};
s32 D_800A797C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7988[] = {
    170, 10, 0x60080000,
};
s32 D_800A7994[] = {
    170, 10, 0x60080000,
};
s32 D_800A79A0[] = {
    170, 10, 0x60080000,
};
s32 D_800A79AC[] = {
    2, (s32)D_800A794C, (s32)D_800A7958, (s32)D_800A7964,
    (s32)D_800A7970, (s32)D_800A797C, (s32)D_800A7988, (s32)D_800A7994,
    (s32)D_800A79A0,
};
s32 D_800A79D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79DC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A79D0, (s32)D_800A79DC, (s32)D_800A79E8,
    (s32)D_800A79F4, (s32)D_800A7A00, (s32)D_800A7A0C, (s32)D_800A7A18,
    (s32)D_800A7A24,
};
s32 D_800A7A54[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A60[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A78[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A84[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A90[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AB4[] = {
    0, (s32)D_800A7A54, (s32)D_800A7A60, (s32)D_800A7A6C,
    (s32)D_800A7A78, (s32)D_800A7A84, (s32)D_800A7A90, (s32)D_800A7A9C,
    (s32)D_800A7AA8,
};
s32 D_800A7AD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B08[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B14[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B20[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B38[] = {
    0, (s32)D_800A7AD8, (s32)D_800A7AE4, (s32)D_800A7AF0,
    (s32)D_800A7AFC, (s32)D_800A7B08, (s32)D_800A7B14, (s32)D_800A7B20,
    (s32)D_800A7B2C,
};
s32 D_800A7B5C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7B68[] = {
    182, 10, 0x60080000,
};
s32 D_800A7B74[] = {
    182, 10, 0x60080000,
};
s32 D_800A7B80[] = {
    182, 10, 0x60080000,
};
s32 D_800A7B8C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7B98[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BA4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BB0[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BBC[] = {
    1, (s32)D_800A7B5C, (s32)D_800A7B68, (s32)D_800A7B74,
    (s32)D_800A7B80, (s32)D_800A7B8C, (s32)D_800A7B98, (s32)D_800A7BA4,
    (s32)D_800A7BB0,
};
s32 D_800A7BE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C10[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C28[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C34[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C40[] = {
    0, (s32)D_800A7BE0, (s32)D_800A7BEC, (s32)D_800A7BF8,
    (s32)D_800A7C04, (s32)D_800A7C10, (s32)D_800A7C1C, (s32)D_800A7C28,
    (s32)D_800A7C34,
};
s32 D_800A7C64[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C88[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CC4[] = {
    0, (s32)D_800A7C64, (s32)D_800A7C70, (s32)D_800A7C7C,
    (s32)D_800A7C88, (s32)D_800A7C94, (s32)D_800A7CA0, (s32)D_800A7CAC,
    (s32)D_800A7CB8,
};
s32 D_800A7CE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D00[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D18[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D24[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D30[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D48[] = {
    0, (s32)D_800A7CE8, (s32)D_800A7CF4, (s32)D_800A7D00,
    (s32)D_800A7D0C, (s32)D_800A7D18, (s32)D_800A7D24, (s32)D_800A7D30,
    (s32)D_800A7D3C,
};
s32 D_800A7D6C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D78[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D84[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D90[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D9C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7DA8[] = {
    71, 10, 0x60080000,
};
s32 D_800A7DB4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7DC0[] = {
    71, 10, 0x60080000,
};
s32 D_800A7DCC[] = {
    1, (s32)D_800A7D6C, (s32)D_800A7D78, (s32)D_800A7D84,
    (s32)D_800A7D90, (s32)D_800A7D9C, (s32)D_800A7DA8, (s32)D_800A7DB4,
    (s32)D_800A7DC0,
};
s32 D_800A7DF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E08[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E14[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E20[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E38[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E44[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E50[] = {
    0, (s32)D_800A7DF0, (s32)D_800A7DFC, (s32)D_800A7E08,
    (s32)D_800A7E14, (s32)D_800A7E20, (s32)D_800A7E2C, (s32)D_800A7E38,
    (s32)D_800A7E44,
};
s32 D_800A7E74[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E80[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E98[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7ED4[] = {
    0, (s32)D_800A7E74, (s32)D_800A7E80, (s32)D_800A7E8C,
    (s32)D_800A7E98, (s32)D_800A7EA4, (s32)D_800A7EB0, (s32)D_800A7EBC,
    (s32)D_800A7EC8,
};
s32 D_800A7EF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F10[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F28[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F34[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F40[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F58[] = {
    0, (s32)D_800A7EF8, (s32)D_800A7F04, (s32)D_800A7F10,
    (s32)D_800A7F1C, (s32)D_800A7F28, (s32)D_800A7F34, (s32)D_800A7F40,
    (s32)D_800A7F4C,
};
s32 D_800A7F7C[] = {
    174, 10, 0x60080000,
};
s32 D_800A7F88[] = {
    174, 10, 0x60080000,
};
s32 D_800A7F94[] = {
    170, 10, 0x60080000,
};
s32 D_800A7FA0[] = {
    170, 10, 0x60080000,
};
s32 D_800A7FAC[] = {
    182, 10, 0x60080000,
};
s32 D_800A7FB8[] = {
    182, 10, 0x60080000,
};
s32 D_800A7FC4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7FD0[] = {
    71, 10, 0x60080000,
};
s32 D_800A7FDC[] = {
    1, (s32)D_800A7F7C, (s32)D_800A7F88, (s32)D_800A7F94,
    (s32)D_800A7FA0, (s32)D_800A7FAC, (s32)D_800A7FB8, (s32)D_800A7FC4,
    (s32)D_800A7FD0,
};
s32 D_800A8000[] = {
    0, 0, 0x60040000,
};
s32 D_800A800C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8018[] = {
    0, 0, 0x60040000,
};
s32 D_800A8024[] = {
    0, 0, 0x60040000,
};
s32 D_800A8030[] = {
    0, 0, 0x60040000,
};
s32 D_800A803C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8048[] = {
    0, 0, 0x60040000,
};
s32 D_800A8054[] = {
    0, 0, 0x60040000,
};
s32 D_800A8060[] = {
    0, (s32)D_800A8000, (s32)D_800A800C, (s32)D_800A8018,
    (s32)D_800A8024, (s32)D_800A8030, (s32)D_800A803C, (s32)D_800A8048,
    (s32)D_800A8054,
};
s32 D_800A8084[] = {
    0, 0, 0x60040000,
};
s32 D_800A8090[] = {
    0, 0, 0x60040000,
};
s32 D_800A809C[] = {
    0, 0, 0x60040000,
};
s32 D_800A80A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A80B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A80C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A80CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A80D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A80E4[] = {
    0, (s32)D_800A8084, (s32)D_800A8090, (s32)D_800A809C,
    (s32)D_800A80A8, (s32)D_800A80B4, (s32)D_800A80C0, (s32)D_800A80CC,
    (s32)D_800A80D8,
};
s32 D_800A8108[] = {
    0, 0, 0x60040000,
};
s32 D_800A8114[] = {
    0, 0, 0x60040000,
};
s32 D_800A8120[] = {
    0, 0, 0x60040000,
};
s32 D_800A812C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8138[] = {
    0, 0, 0x60040000,
};
s32 D_800A8144[] = {
    0, 0, 0x60040000,
};
s32 D_800A8150[] = {
    0, 0, 0x60040000,
};
s32 D_800A815C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8168[] = {
    0, (s32)D_800A8108, (s32)D_800A8114, (s32)D_800A8120,
    (s32)D_800A812C, (s32)D_800A8138, (s32)D_800A8144, (s32)D_800A8150,
    (s32)D_800A815C,
};
s32 D_800A818C[] = {
    232, 1, 0, (s32)D_800A548C,
    (s32)D_800A5510, (s32)D_800A5594, (s32)D_800A5618, 251,
    4, 0, (s32)D_800A569C, (s32)D_800A5720,
    (s32)D_800A57A4, (s32)D_800A5828, 267, 7,
    0, (s32)D_800A58AC, (s32)D_800A5930, (s32)D_800A59B4,
    (s32)D_800A5A38, 293, 12, 0,
    (s32)D_800A5ABC, (s32)D_800A5B40, (s32)D_800A5BC4, (s32)D_800A5C48,
    301, 13, 0, (s32)D_800A5CCC,
    (s32)D_800A5D50, (s32)D_800A5DD4, (s32)D_800A5E58, 303,
    14, 0, (s32)D_800A5EDC, (s32)D_800A5F60,
    (s32)D_800A5FE4, (s32)D_800A6068, 306, 15,
    0, (s32)D_800A60EC, (s32)D_800A6170, (s32)D_800A61F4,
    (s32)D_800A6278, 311, 16, 0,
    (s32)D_800A62FC, (s32)D_800A6380, (s32)D_800A6404, (s32)D_800A6488,
    313, 17, 0, (s32)D_800A650C,
    (s32)D_800A6590, (s32)D_800A6614, (s32)D_800A6698, 316,
    18, 0, (s32)D_800A671C, (s32)D_800A67A0,
    (s32)D_800A6824, (s32)D_800A68A8, 322, 19,
    0, (s32)D_800A692C, (s32)D_800A69B0, (s32)D_800A6A34,
    (s32)D_800A6AB8, 328, 20, 0,
    (s32)D_800A6B3C, (s32)D_800A6BC0, (s32)D_800A6C44, (s32)D_800A6CC8,
    333, 21, 0, (s32)D_800A6D4C,
    (s32)D_800A6DD0, (s32)D_800A6E54, (s32)D_800A6ED8, 337,
    22, 0, (s32)D_800A6F5C, (s32)D_800A6FE0,
    (s32)D_800A7064, (s32)D_800A70E8, 341, 23,
    0, (s32)D_800A716C, (s32)D_800A71F0, (s32)D_800A7274,
    (s32)D_800A72F8, 344, 24, 0,
    (s32)D_800A737C, (s32)D_800A7400, (s32)D_800A7484, (s32)D_800A7508,
    349, 25, 0, (s32)D_800A758C,
    (s32)D_800A7610, (s32)D_800A7694, (s32)D_800A7718, 351,
    26, 0, (s32)D_800A779C, (s32)D_800A7820,
    (s32)D_800A78A4, (s32)D_800A7928, 354, 27,
    0, (s32)D_800A79AC, (s32)D_800A7A30, (s32)D_800A7AB4,
    (s32)D_800A7B38, 361, 28, 0,
    (s32)D_800A7BBC, (s32)D_800A7C40, (s32)D_800A7CC4, (s32)D_800A7D48,
    367, 29, 0, (s32)D_800A7DCC,
    (s32)D_800A7E50, (s32)D_800A7ED4, (s32)D_800A7F58, 373,
    30, 0, (s32)D_800A7FDC, (s32)D_800A8060,
    (s32)D_800A80E4, (s32)D_800A8168,
};
s32 D_800A83F4[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140014C, 0x400030, 0x1FF0140,
    0x1000140, 0x1400152, 0x400048, 0x1FF0150,
    0x1000140, 0x1400158, 0x400060, 0x1FF0160,
    0x1000140, 0x140015E, 0x400078, 0x1FF0170,
    0x1000140, 0x1400164, 0x400090, 0x1FE0140,
    0x1000140, 0x140016A, 0x4000A8, 0x1FE0150,
    0x1000140, 0x1400170, 0x4000C0, 0x1FE0160,
    0x1000140, 0x1400176, 0x4000D8, 0x1FE0170,
    0x1000140, 0x160014C, 0x600030, 0x1FD0140,
    0x1000140, 0x1600152, 0x600048, 0x1FD0150,
    0x1000140, 0x1600158, 0x600060, 0x1FD0160,
    0x1000140, 0x160015E, 0x600078, 0x1FD0170,
    0x1000140, 0x1400140, 0x400000, 0x1FC0140,
    0x1000140, 0x1000168, 160, 0x1FC0150,
    0x1000140, 0x1600164, 0x600090, 0x1FC0160,
    0x1000140, 0x160016A, 0x6000A8, 0x1FC0170,
    0x1000140, 0x1600170, 0x6000C0, 0x1FB0140,
    0x1000140, 0x1600176, 0x6000D8, 0x1FB0150,
    0x1000140, 0x1700140, 0x700000, 0x1FB0160,
    0x1000140, 0x1700146, 0x700018, 0x1FB0170,
    0x1000140, 0x1000140, 0, 0x1FA0140,
    0x1000140, 0x1000154, 80, 0x1FA0150,
};
s32 D_800A85B4[] = {
    0x1022D, 0x1822F, 65535,
};
s32 D_800A85C0[] = {
    0x1022E, 0x18230, 65535,
};
s32 D_800A85CC[] = {
    0x1022F, 0x18231, 65535,
};
s32 D_800A85D8[] = {
    0x10230, 0x18232, 65535,
};
s32 D_800A85E4[] = {
    0x10231, 0x18233, 65535,
};
s32 D_800A85F0[] = {
    0x10232, 0x18234, 65535,
};
s32 D_800A85FC[] = {
    0x10233, 0x18235, 65535,
};
s32 D_800A8608[] = {
    0x10234, 0x18237, 65535,
};
s32 D_800A8614[] = {
    0x10235, 0x18238, 65535,
};
s32 D_800A8620[] = {
    0x10236, 0x18239, 65535,
};
s32 D_800A862C[] = {
    0x10237, 0x1823A, 65535,
};
s32 D_800A8638[] = {
    0x10256, 0x1823B, 65535,
};
s32 D_800A8644[] = {
    0x10257, 0x1823C, 65535,
};
s32 D_800A8650[] = {
    0x10258, 0x1823D, 65535,
};
s32 D_800A865C[] = {
    0x10259, 0x18470, 65535,
};
s32 D_800A8668[] = {
    0x1025A, 0x18B1B, 65535,
};
s32 D_800A8674[] = {
    0x1025B, 0x18B1C, 65535,
};
s32 D_800A8680[] = {
    0x1025C, 0x18AFF, 65535,
};
s32 D_800A868C[] = {
    0, (s32)D_800A85B4, 910, 0,
    0, 0,
};
s32 D_800A86A4[] = {
    0, (s32)D_800A85C0, 904, 0,
    0, 0,
};
s32 D_800A86BC[] = {
    0, (s32)D_800A85CC, 905, 0,
    0, 0,
};
s32 D_800A86D4[] = {
    0, (s32)D_800A85D8, 906, 0,
    0, 0,
};
s32 D_800A86EC[] = {
    0, (s32)D_800A85E4, 907, 0,
    0, 0,
};
s32 D_800A8704[] = {
    0, (s32)D_800A85F0, 908, 0,
    0, 0,
};
s32 D_800A871C[] = {
    0, (s32)D_800A85FC, 909, 0,
    0, 0,
};
s32 D_800A8734[] = {
    0, (s32)D_800A8608, 911, 0,
    0, 0,
};
s32 D_800A874C[] = {
    0, (s32)D_800A8614, 912, 0,
    0, 0,
};
s32 D_800A8764[] = {
    0, (s32)D_800A8620, 913, 0,
    0, 0,
};
s32 D_800A877C[] = {
    0, (s32)D_800A862C, 914, 0,
    0, 0,
};
s32 D_800A8794[] = {
    0, (s32)D_800A8638, 915, 0,
    0, 0,
};
s32 D_800A87AC[] = {
    0, (s32)D_800A8644, 916, 0,
    0, 0,
};
s32 D_800A87C4[] = {
    0, (s32)D_800A8650, 917, 0,
    0, 0,
};
s32 D_800A87DC[] = {
    0, (s32)D_800A865C, 918, 0,
    0, 0,
};
s32 D_800A87F4[] = {
    0, (s32)D_800A8668, 919, 0,
    0, 0,
};
s32 D_800A880C[] = {
    0, (s32)D_800A8674, 920, 0,
    0, 0,
};
s32 D_800A8824[] = {
    0, (s32)D_800A8680, 921, 0,
    0, 0,
};
s32 D_800A883C[] = {
    0x17E15, 0x17E1E, 557, 65535,
};
s32 D_800A884C[] = {
    0x17E12, 0x17E21, 558, 65535,
};
s32 D_800A885C[] = {
    0x17E00, 0x17E1E, 559, 65535,
};
s32 D_800A886C[] = {
    0x17E18, 0x17E1F, 560, 65535,
};
s32 D_800A887C[] = {
    0x17E0E, 0x17E1E, 561, 65535,
};
s32 D_800A888C[] = {
    0x17E03, 0x17E1E, 562, 65535,
};
s32 D_800A889C[] = {
    0x17E11, 0x17E1E, 563, 65535,
};
s32 D_800A88AC[] = {
    0x17E0F, 0x17E1E, 564, 65535,
};
s32 D_800A88BC[] = {
    0x17E1C, 0x17E1F, 565, 65535,
};
s32 D_800A88CC[] = {
    0x17E0D, 0x17E1E, 566, 65535,
};
s32 D_800A88DC[] = {
    0x17E10, 0x17E1E, 567, 65535,
};
s32 D_800A88EC[] = {
    598, 0x17E0C, 0x17E1E, 65535,
};
s32 D_800A88FC[] = {
    0x17E18, 8, 65535,
};
s32 D_800A8908[] = {
    0x17E1B, 8, 65535,
};
s32 D_800A8914[] = {
    0x17E06, 0x17E1E, 599, 65535,
};
s32 D_800A8924[] = {
    0x17E13, 0x17E20, 600, 65535,
};
s32 D_800A8934[] = {
    0x17E13, 0x17E23, 601, 65535,
};
s32 D_800A8944[] = {
    0x17E19, 0x17E1E, 602, 65535,
};
s32 D_800A8954[] = {
    0x17E17, 0x17E1E, 603, 65535,
};
s32 D_800A8964[] = {
    0x17E1B, 0x17E1F, 604, 65535,
};
s32 D_800A8974[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A8980[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A898C[] = {
    0x17E20, 9, 65535,
};
s32 D_800A8998[] = {
    0x17E21, 9, 65535,
};
s32 D_800A89A4[] = {
    0x17E00, 10, 65535,
};
s32 D_800A89B0[] = {
    0x17E0B, 10, 65535,
};
s32 D_800A89BC[] = {
    0x17E0C, 10, 65535,
};
s32 D_800A89C8[] = {
    0x17E0D, 10, 65535,
};
s32 D_800A89D4[] = {
    0x17E0F, 10, 65535,
};
s32 D_800A89E0[] = {
    0x17E10, 10, 65535,
};
s32 D_800A89EC[] = {
    0x17E12, 10, 65535,
};
s32 D_800A89F8[] = {
    0x17E13, 10, 65535,
};
s32 D_800A8A04[] = {
    0x17E17, 10, 65535,
};
s32 D_800A8A10[] = {
    0x17E18, 10, 65535,
};
s32 D_800A8A1C[] = {
    0x17E1A, 10, 65535,
};
s32 D_800A8A28[] = {
    0x17E1B, 10, 65535,
};
s32 D_800A8A34[] = {
    0x17E1C, 10, 65535,
};
s32 D_800A8A40[] = {
    0x17E1D, 10, 65535,
};
s32 D_800A8A4C[] = {
    (s32)D_800A883C, (s32)D_800A868C, 0x40021, 0x25800F0,
    1,
};
s32 D_800A8A60[] = {
    (s32)D_800A884C, (s32)D_800A86A4, 0x5004D, 0x25800F0,
    1,
};
s32 D_800A8A74[] = {
    (s32)D_800A885C, (s32)D_800A86BC, 0x6004E, 0x25800F0,
    1,
};
s32 D_800A8A88[] = {
    (s32)D_800A886C, (s32)D_800A86D4, 0x7004F, 0x25800F0,
    1,
};
s32 D_800A8A9C[] = {
    (s32)D_800A887C, (s32)D_800A86EC, 0x80050, 0x25800F0,
    1,
};
s32 D_800A8AB0[] = {
    (s32)D_800A888C, (s32)D_800A8704, 0x90051, 0x2580104,
    1,
};
s32 D_800A8AC4[] = {
    (s32)D_800A889C, (s32)D_800A871C, 0xA0052, 0x25800F0,
    1,
};
s32 D_800A8AD8[] = {
    (s32)D_800A88AC, (s32)D_800A8734, 0xB0053, 0x25800F0,
    1,
};
s32 D_800A8AEC[] = {
    (s32)D_800A88BC, (s32)D_800A874C, 0xC0054, 0x25800F0,
    1,
};
s32 D_800A8B00[] = {
    (s32)D_800A88CC, (s32)D_800A8764, 0xD0055, 0x25800F0,
    1,
};
s32 D_800A8B14[] = {
    (s32)D_800A88DC, (s32)D_800A877C, 0xE0056, 0x25800F0,
    1,
};
s32 D_800A8B28[] = {
    (s32)D_800A88EC, (s32)D_800A8794, 0xF0057, 0x25800F0,
    1,
};
s32 D_800A8B3C[] = {
    0, 0, 0x100146, 0,
    0,
};
s32 D_800A8B50[] = {
    (s32)D_800A88FC, 0, 0x110148, 0x1380150,
    1,
};
s32 D_800A8B64[] = {
    (s32)D_800A8908, 0, 0x110148, 0x1580190,
    1,
};
s32 D_800A8B78[] = {
    (s32)D_800A8914, (s32)D_800A87AC, 0x120154, 0x25800F0,
    1,
};
s32 D_800A8B8C[] = {
    (s32)D_800A8924, (s32)D_800A87C4, 0x130155, 0x25800F0,
    1,
};
s32 D_800A8BA0[] = {
    (s32)D_800A8934, (s32)D_800A87DC, 0x140156, 0x25800F0,
    1,
};
s32 D_800A8BB4[] = {
    (s32)D_800A8944, (s32)D_800A87F4, 0x150157, 0x25800F0,
    1,
};
s32 D_800A8BC8[] = {
    (s32)D_800A8954, (s32)D_800A880C, 0x160158, 0x25800F0,
    1,
};
s32 D_800A8BDC[] = {
    (s32)D_800A8964, (s32)D_800A8824, 0x17015B, 0x25800F0,
    1,
};
s32 D_800A8BF0[] = {
    (s32)D_800A8974, 0, 0x18015F, 0x1900120,
    1,
};
s32 D_800A8C04[] = {
    (s32)D_800A8980, 0, 0x18015F, 0x1B800D0,
    1,
};
s32 D_800A8C18[] = {
    (s32)D_800A898C, 0, 0x18015F, 0x1D000A0,
    1,
};
s32 D_800A8C2C[] = {
    (s32)D_800A8998, 0, 0x18015F, 0xD001E0,
    1,
};
s32 D_800A8C40[] = {
    (s32)D_800A89A4, 0, 0x190160, 0x22000C0,
    1,
};
s32 D_800A8C54[] = {
    (s32)D_800A89B0, 0, 0x190160, 0xD001E0,
    1,
};
s32 D_800A8C68[] = {
    (s32)D_800A89BC, 0, 0x190160, 0x1100160,
    1,
};
s32 D_800A8C7C[] = {
    (s32)D_800A89C8, 0, 0x190160, 0x1380150,
    1,
};
s32 D_800A8C90[] = {
    (s32)D_800A89D4, 0, 0x190160, 0x1E800F0,
    1,
};
s32 D_800A8CA4[] = {
    (s32)D_800A89E0, 0, 0x190160, 0x1780150,
    1,
};
s32 D_800A8CB8[] = {
    (s32)D_800A89EC, 0, 0x190160, 0x1100160,
    1,
};
s32 D_800A8CCC[] = {
    (s32)D_800A89F8, 0, 0x190160, 0x1580190,
    1,
};
s32 D_800A8CE0[] = {
    (s32)D_800A8A04, 0, 0x190160, 0x1100160,
    1,
};
s32 D_800A8CF4[] = {
    (s32)D_800A8A10, 0, 0x190160, 0x22000C0,
    1,
};
s32 D_800A8D08[] = {
    (s32)D_800A8A1C, 0, 0x190160, 0x1E800F0,
    1,
};
s32 D_800A8D1C[] = {
    (s32)D_800A8A28, 0, 0x190160, 0xD001E0,
    1,
};
s32 D_800A8D30[] = {
    (s32)D_800A8A34, 0, 0x190160, 0x1100160,
    1,
};
s32 D_800A8D44[] = {
    (s32)D_800A8A40, 0, 0x190160, 0x1780150,
    1,
};
s32 D_800A8D58[] = {
    (s32)D_800A8A4C, (s32)D_800A8A60, (s32)D_800A8A74, (s32)D_800A8A88,
    (s32)D_800A8A9C, (s32)D_800A8AB0, (s32)D_800A8AC4, (s32)D_800A8AD8,
    (s32)D_800A8AEC, (s32)D_800A8B00, (s32)D_800A8B14, (s32)D_800A8B28,
    (s32)D_800A8B3C, (s32)D_800A8B50, (s32)D_800A8B64, (s32)D_800A8B78,
    (s32)D_800A8B8C, (s32)D_800A8BA0, (s32)D_800A8BB4, (s32)D_800A8BC8,
    (s32)D_800A8BDC, (s32)D_800A8BF0, (s32)D_800A8C04, (s32)D_800A8C18,
    (s32)D_800A8C2C, (s32)D_800A8C40, (s32)D_800A8C54, (s32)D_800A8C68,
    (s32)D_800A8C7C, (s32)D_800A8C90, (s32)D_800A8CA4, (s32)D_800A8CB8,
    (s32)D_800A8CCC, (s32)D_800A8CE0, (s32)D_800A8CF4, (s32)D_800A8D08,
    (s32)D_800A8D1C, (s32)D_800A8D30, (s32)D_800A8D44, 0,
};
s32 D_800A8DF8[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A8E0C[] = {
    65535, 65535, 0x2EB0001, 0xA00240,
    5, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A8E3C[])(void) = {
    func_800A4E74,
};
