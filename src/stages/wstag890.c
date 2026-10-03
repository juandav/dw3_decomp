#include "common.h"
#include "stage.h"
extern void (*D_800A902C[])(void);
void func_800A4DA4();
extern StagePoints *D_800A59D8[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A59D8, GAME.unk44, GAME.unk46);
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
    D_800A902C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag890", func_800A4E74);

void func_800A4E74();
extern StagePoint D_800A4F90;
extern StagePoint D_800A4FA0;
extern StagePoint D_800A4FB0;
extern StagePoint D_800A4FC8;
extern StagePoint D_800A4FD8;
extern StagePoint D_800A4FE8;
extern StagePoint D_800A5000;
extern StagePoint D_800A5010;
extern StagePoint D_800A5020;
extern StagePoint D_800A5038;
extern StagePoint D_800A5048;
extern StagePoint D_800A5058;
extern StagePoint D_800A5070;
extern StagePoint D_800A5080;
extern StagePoint D_800A5090;
extern StagePoint D_800A50A8;
extern StagePoint D_800A50B8;
extern StagePoint D_800A50C8;
extern StagePoint D_800A50E0;
extern StagePoint D_800A50F0;
extern StagePoint D_800A5100;
extern StagePoint D_800A5118;
extern StagePoint D_800A5128;
extern StagePoint D_800A5138;
extern StagePoint D_800A5150;
extern StagePoint D_800A5160;
extern StagePoint D_800A5170;
extern StagePoint D_800A5188;
extern StagePoint D_800A5198;
extern StagePoint D_800A51A8;
extern StagePoint D_800A51C0;
extern StagePoint D_800A51D0;
extern StagePoint D_800A51E0;
extern StagePoint D_800A51F8;
extern StagePoint D_800A5208;
extern StagePoint D_800A5218;
extern StagePoint D_800A5230;
extern StagePoint D_800A5240;
extern StagePoint D_800A5250;
extern StagePoint D_800A5268;
extern StagePoint D_800A5278;
extern StagePoint D_800A5288;
extern StagePoint D_800A52A0;
extern StagePoint D_800A52B0;
extern StagePoint D_800A52C0;
extern StagePoint D_800A52D8;
extern StagePoint D_800A52E8;
extern StagePoint D_800A52F8;
extern StagePoint D_800A5310;
extern StagePoint D_800A5320;
extern StagePoint D_800A5330;
extern StagePoint D_800A5348;
extern StagePoint D_800A5358;
extern StagePoint D_800A5368;
extern StagePoint D_800A5380;
extern StagePoint D_800A5390;
extern StagePoint D_800A53A0;
extern StagePoint D_800A53B8;
extern StagePoint D_800A53C8;
extern StagePoint D_800A53D8;
extern StagePoint D_800A53F0;
extern StagePoint D_800A5400;
extern StagePoint D_800A5410;
extern StagePoint D_800A5428;
extern StagePoint D_800A5438;
extern StagePoint D_800A5448;
extern StagePoint D_800A5460;
extern StagePoint D_800A5470;
extern StagePoint D_800A5480;
extern StagePoint D_800A5498;
extern StagePoint D_800A54A8;
extern StagePoint D_800A54B8;
extern StagePoint D_800A54D0;
extern StagePoint D_800A54E0;
extern StagePoint D_800A54F0;
extern StagePoint D_800A5508;
extern StagePoint D_800A5518;
extern StagePoint D_800A5528;
extern StagePoint D_800A5540;
extern StagePoint D_800A5550;
extern StagePoint D_800A5560;
extern StagePoint D_800A5578;
extern StagePoint D_800A5588;
extern StagePoint D_800A5598;
extern StagePoint D_800A55B0;
extern StagePoint D_800A55C0;
extern StagePoint D_800A55D0;
extern StagePoint D_800A55E8;
extern StagePoint D_800A55F8;
extern StagePoint D_800A5608;
extern StagePoint D_800A5620;
extern StagePoint D_800A5630;
extern StagePoint D_800A5640;
extern StagePoint D_800A5658;
extern StagePoint D_800A5668;
extern StagePoint D_800A5678;
extern StagePoint D_800A5690;
extern StagePoint D_800A56A0;
extern StagePoint D_800A56B0;
extern StagePoint D_800A56C8;
extern StagePoint D_800A56D8;
extern StagePoint D_800A56E8;
extern StagePoint D_800A5700;
extern StagePoint D_800A5710;
extern StagePoint D_800A5720;
extern StagePoint D_800A5738;
extern StagePoint D_800A5748;
extern StagePoint D_800A5758;
extern StagePoint D_800A5770;
extern StagePoint D_800A5780;
extern StagePoint D_800A5790;
extern StagePoint D_800A57A8;
extern StagePoint D_800A57B8;
extern StagePoint D_800A57C8;
extern StagePoint D_800A57E0;
extern StagePoint D_800A57F0;
extern StagePoint D_800A5800;
extern StagePoint D_800A5818;
extern StagePoint D_800A5828;
extern StagePoint D_800A5838;
extern StagePoint D_800A5850;
extern StagePoint D_800A5860;
extern StagePoint D_800A5870;
extern StagePoint D_800A5888;
extern StagePoint D_800A5898;
extern StagePoint D_800A58A8;
extern StagePoint D_800A58C0;
extern StagePoint D_800A58D0;
extern StagePoint D_800A58E0;
extern StagePoint D_800A58F8;
extern StagePoint D_800A5908;
extern StagePoint D_800A5918;
extern StagePoint D_800A5930;
extern StagePoint D_800A5940;
extern StagePoint D_800A5950;
extern StagePoint D_800A5968;
extern StagePoint D_800A5978;
extern StagePoint D_800A5988;
extern StagePoint D_800A59A0;
extern StagePoint D_800A59B0;
extern StagePoint D_800A59C0;
extern StagePoints D_800A4FC0;
extern StagePoints D_800A4FF8;
extern StagePoints D_800A5030;
extern StagePoints D_800A5068;
extern StagePoints D_800A50A0;
extern StagePoints D_800A50D8;
extern StagePoints D_800A5110;
extern StagePoints D_800A5148;
extern StagePoints D_800A5180;
extern StagePoints D_800A51B8;
extern StagePoints D_800A51F0;
extern StagePoints D_800A5228;
extern StagePoints D_800A5260;
extern StagePoints D_800A5298;
extern StagePoints D_800A52D0;
extern StagePoints D_800A5308;
extern StagePoints D_800A5340;
extern StagePoints D_800A5378;
extern StagePoints D_800A53B0;
extern StagePoints D_800A53E8;
extern StagePoints D_800A5420;
extern StagePoints D_800A5458;
extern StagePoints D_800A5490;
extern StagePoints D_800A54C8;
extern StagePoints D_800A5500;
extern StagePoints D_800A5538;
extern StagePoints D_800A5570;
extern StagePoints D_800A55A8;
extern StagePoints D_800A55E0;
extern StagePoints D_800A5618;
extern StagePoints D_800A5650;
extern StagePoints D_800A5688;
extern StagePoints D_800A56C0;
extern StagePoints D_800A56F8;
extern StagePoints D_800A5730;
extern StagePoints D_800A5768;
extern StagePoints D_800A57A0;
extern StagePoints D_800A57D8;
extern StagePoints D_800A5810;
extern StagePoints D_800A5848;
extern StagePoints D_800A5880;
extern StagePoints D_800A58B8;
extern StagePoints D_800A58F0;
extern StagePoints D_800A5928;
extern StagePoints D_800A5960;
extern StagePoints D_800A5998;
extern StagePoints D_800A59D0;
extern s32 D_800A5A98[];
extern s32 D_800A5AA4[];
extern s32 D_800A5AB0[];
extern s32 D_800A5ABC[];
extern s32 D_800A5AC8[];
extern s32 D_800A5AD4[];
extern s32 D_800A5AE0[];
extern s32 D_800A5AEC[];
extern s32 D_800A5B1C[];
extern s32 D_800A5B28[];
extern s32 D_800A5B34[];
extern s32 D_800A5B40[];
extern s32 D_800A5B4C[];
extern s32 D_800A5B58[];
extern s32 D_800A5B64[];
extern s32 D_800A5B70[];
extern s32 D_800A5BA0[];
extern s32 D_800A5BAC[];
extern s32 D_800A5BB8[];
extern s32 D_800A5BC4[];
extern s32 D_800A5BD0[];
extern s32 D_800A5BDC[];
extern s32 D_800A5BE8[];
extern s32 D_800A5BF4[];
extern s32 D_800A5C24[];
extern s32 D_800A5C30[];
extern s32 D_800A5C3C[];
extern s32 D_800A5C48[];
extern s32 D_800A5C54[];
extern s32 D_800A5C60[];
extern s32 D_800A5C6C[];
extern s32 D_800A5C78[];
extern s32 D_800A5CA8[];
extern s32 D_800A5CB4[];
extern s32 D_800A5CC0[];
extern s32 D_800A5CCC[];
extern s32 D_800A5CD8[];
extern s32 D_800A5CE4[];
extern s32 D_800A5CF0[];
extern s32 D_800A5CFC[];
extern s32 D_800A5D2C[];
extern s32 D_800A5D38[];
extern s32 D_800A5D44[];
extern s32 D_800A5D50[];
extern s32 D_800A5D5C[];
extern s32 D_800A5D68[];
extern s32 D_800A5D74[];
extern s32 D_800A5D80[];
extern s32 D_800A5DB0[];
extern s32 D_800A5DBC[];
extern s32 D_800A5DC8[];
extern s32 D_800A5DD4[];
extern s32 D_800A5DE0[];
extern s32 D_800A5DEC[];
extern s32 D_800A5DF8[];
extern s32 D_800A5E04[];
extern s32 D_800A5E34[];
extern s32 D_800A5E40[];
extern s32 D_800A5E4C[];
extern s32 D_800A5E58[];
extern s32 D_800A5E64[];
extern s32 D_800A5E70[];
extern s32 D_800A5E7C[];
extern s32 D_800A5E88[];
extern s32 D_800A5EB8[];
extern s32 D_800A5EC4[];
extern s32 D_800A5ED0[];
extern s32 D_800A5EDC[];
extern s32 D_800A5EE8[];
extern s32 D_800A5EF4[];
extern s32 D_800A5F00[];
extern s32 D_800A5F0C[];
extern s32 D_800A5F3C[];
extern s32 D_800A5F48[];
extern s32 D_800A5F54[];
extern s32 D_800A5F60[];
extern s32 D_800A5F6C[];
extern s32 D_800A5F78[];
extern s32 D_800A5F84[];
extern s32 D_800A5F90[];
extern s32 D_800A5FC0[];
extern s32 D_800A5FCC[];
extern s32 D_800A5FD8[];
extern s32 D_800A5FE4[];
extern s32 D_800A5FF0[];
extern s32 D_800A5FFC[];
extern s32 D_800A6008[];
extern s32 D_800A6014[];
extern s32 D_800A6044[];
extern s32 D_800A6050[];
extern s32 D_800A605C[];
extern s32 D_800A6068[];
extern s32 D_800A6074[];
extern s32 D_800A6080[];
extern s32 D_800A608C[];
extern s32 D_800A6098[];
extern s32 D_800A60C8[];
extern s32 D_800A60D4[];
extern s32 D_800A60E0[];
extern s32 D_800A60EC[];
extern s32 D_800A60F8[];
extern s32 D_800A6104[];
extern s32 D_800A6110[];
extern s32 D_800A611C[];
extern s32 D_800A614C[];
extern s32 D_800A6158[];
extern s32 D_800A6164[];
extern s32 D_800A6170[];
extern s32 D_800A617C[];
extern s32 D_800A6188[];
extern s32 D_800A6194[];
extern s32 D_800A61A0[];
extern s32 D_800A61D0[];
extern s32 D_800A61DC[];
extern s32 D_800A61E8[];
extern s32 D_800A61F4[];
extern s32 D_800A6200[];
extern s32 D_800A620C[];
extern s32 D_800A6218[];
extern s32 D_800A6224[];
extern s32 D_800A6254[];
extern s32 D_800A6260[];
extern s32 D_800A626C[];
extern s32 D_800A6278[];
extern s32 D_800A6284[];
extern s32 D_800A6290[];
extern s32 D_800A629C[];
extern s32 D_800A62A8[];
extern s32 D_800A62D8[];
extern s32 D_800A62E4[];
extern s32 D_800A62F0[];
extern s32 D_800A62FC[];
extern s32 D_800A6308[];
extern s32 D_800A6314[];
extern s32 D_800A6320[];
extern s32 D_800A632C[];
extern s32 D_800A635C[];
extern s32 D_800A6368[];
extern s32 D_800A6374[];
extern s32 D_800A6380[];
extern s32 D_800A638C[];
extern s32 D_800A6398[];
extern s32 D_800A63A4[];
extern s32 D_800A63B0[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6404[];
extern s32 D_800A6410[];
extern s32 D_800A641C[];
extern s32 D_800A6428[];
extern s32 D_800A6434[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A6488[];
extern s32 D_800A6494[];
extern s32 D_800A64A0[];
extern s32 D_800A64AC[];
extern s32 D_800A64B8[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A650C[];
extern s32 D_800A6518[];
extern s32 D_800A6524[];
extern s32 D_800A6530[];
extern s32 D_800A653C[];
extern s32 D_800A656C[];
extern s32 D_800A6578[];
extern s32 D_800A6584[];
extern s32 D_800A6590[];
extern s32 D_800A659C[];
extern s32 D_800A65A8[];
extern s32 D_800A65B4[];
extern s32 D_800A65C0[];
extern s32 D_800A65F0[];
extern s32 D_800A65FC[];
extern s32 D_800A6608[];
extern s32 D_800A6614[];
extern s32 D_800A6620[];
extern s32 D_800A662C[];
extern s32 D_800A6638[];
extern s32 D_800A6644[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A668C[];
extern s32 D_800A6698[];
extern s32 D_800A66A4[];
extern s32 D_800A66B0[];
extern s32 D_800A66BC[];
extern s32 D_800A66C8[];
extern s32 D_800A66F8[];
extern s32 D_800A6704[];
extern s32 D_800A6710[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A6740[];
extern s32 D_800A674C[];
extern s32 D_800A677C[];
extern s32 D_800A6788[];
extern s32 D_800A6794[];
extern s32 D_800A67A0[];
extern s32 D_800A67AC[];
extern s32 D_800A67B8[];
extern s32 D_800A67C4[];
extern s32 D_800A67D0[];
extern s32 D_800A6800[];
extern s32 D_800A680C[];
extern s32 D_800A6818[];
extern s32 D_800A6824[];
extern s32 D_800A6830[];
extern s32 D_800A683C[];
extern s32 D_800A6848[];
extern s32 D_800A6854[];
extern s32 D_800A6884[];
extern s32 D_800A6890[];
extern s32 D_800A689C[];
extern s32 D_800A68A8[];
extern s32 D_800A68B4[];
extern s32 D_800A68C0[];
extern s32 D_800A68CC[];
extern s32 D_800A68D8[];
extern s32 D_800A6908[];
extern s32 D_800A6914[];
extern s32 D_800A6920[];
extern s32 D_800A692C[];
extern s32 D_800A6938[];
extern s32 D_800A6944[];
extern s32 D_800A6950[];
extern s32 D_800A695C[];
extern s32 D_800A698C[];
extern s32 D_800A6998[];
extern s32 D_800A69A4[];
extern s32 D_800A69B0[];
extern s32 D_800A69BC[];
extern s32 D_800A69C8[];
extern s32 D_800A69D4[];
extern s32 D_800A69E0[];
extern s32 D_800A6A10[];
extern s32 D_800A6A1C[];
extern s32 D_800A6A28[];
extern s32 D_800A6A34[];
extern s32 D_800A6A40[];
extern s32 D_800A6A4C[];
extern s32 D_800A6A58[];
extern s32 D_800A6A64[];
extern s32 D_800A6A94[];
extern s32 D_800A6AA0[];
extern s32 D_800A6AAC[];
extern s32 D_800A6AB8[];
extern s32 D_800A6AC4[];
extern s32 D_800A6AD0[];
extern s32 D_800A6ADC[];
extern s32 D_800A6AE8[];
extern s32 D_800A6B18[];
extern s32 D_800A6B24[];
extern s32 D_800A6B30[];
extern s32 D_800A6B3C[];
extern s32 D_800A6B48[];
extern s32 D_800A6B54[];
extern s32 D_800A6B60[];
extern s32 D_800A6B6C[];
extern s32 D_800A6B9C[];
extern s32 D_800A6BA8[];
extern s32 D_800A6BB4[];
extern s32 D_800A6BC0[];
extern s32 D_800A6BCC[];
extern s32 D_800A6BD8[];
extern s32 D_800A6BE4[];
extern s32 D_800A6BF0[];
extern s32 D_800A6C20[];
extern s32 D_800A6C2C[];
extern s32 D_800A6C38[];
extern s32 D_800A6C44[];
extern s32 D_800A6C50[];
extern s32 D_800A6C5C[];
extern s32 D_800A6C68[];
extern s32 D_800A6C74[];
extern s32 D_800A6CA4[];
extern s32 D_800A6CB0[];
extern s32 D_800A6CBC[];
extern s32 D_800A6CC8[];
extern s32 D_800A6CD4[];
extern s32 D_800A6CE0[];
extern s32 D_800A6CEC[];
extern s32 D_800A6CF8[];
extern s32 D_800A6D28[];
extern s32 D_800A6D34[];
extern s32 D_800A6D40[];
extern s32 D_800A6D4C[];
extern s32 D_800A6D58[];
extern s32 D_800A6D64[];
extern s32 D_800A6D70[];
extern s32 D_800A6D7C[];
extern s32 D_800A6DAC[];
extern s32 D_800A6DB8[];
extern s32 D_800A6DC4[];
extern s32 D_800A6DD0[];
extern s32 D_800A6DDC[];
extern s32 D_800A6DE8[];
extern s32 D_800A6DF4[];
extern s32 D_800A6E00[];
extern s32 D_800A6E30[];
extern s32 D_800A6E3C[];
extern s32 D_800A6E48[];
extern s32 D_800A6E54[];
extern s32 D_800A6E60[];
extern s32 D_800A6E6C[];
extern s32 D_800A6E78[];
extern s32 D_800A6E84[];
extern s32 D_800A6EB4[];
extern s32 D_800A6EC0[];
extern s32 D_800A6ECC[];
extern s32 D_800A6ED8[];
extern s32 D_800A6EE4[];
extern s32 D_800A6EF0[];
extern s32 D_800A6EFC[];
extern s32 D_800A6F08[];
extern s32 D_800A6F38[];
extern s32 D_800A6F44[];
extern s32 D_800A6F50[];
extern s32 D_800A6F5C[];
extern s32 D_800A6F68[];
extern s32 D_800A6F74[];
extern s32 D_800A6F80[];
extern s32 D_800A6F8C[];
extern s32 D_800A6FBC[];
extern s32 D_800A6FC8[];
extern s32 D_800A6FD4[];
extern s32 D_800A6FE0[];
extern s32 D_800A6FEC[];
extern s32 D_800A6FF8[];
extern s32 D_800A7004[];
extern s32 D_800A7010[];
extern s32 D_800A7040[];
extern s32 D_800A704C[];
extern s32 D_800A7058[];
extern s32 D_800A7064[];
extern s32 D_800A7070[];
extern s32 D_800A707C[];
extern s32 D_800A7088[];
extern s32 D_800A7094[];
extern s32 D_800A70C4[];
extern s32 D_800A70D0[];
extern s32 D_800A70DC[];
extern s32 D_800A70E8[];
extern s32 D_800A70F4[];
extern s32 D_800A7100[];
extern s32 D_800A710C[];
extern s32 D_800A7118[];
extern s32 D_800A7148[];
extern s32 D_800A7154[];
extern s32 D_800A7160[];
extern s32 D_800A716C[];
extern s32 D_800A7178[];
extern s32 D_800A7184[];
extern s32 D_800A7190[];
extern s32 D_800A719C[];
extern s32 D_800A71CC[];
extern s32 D_800A71D8[];
extern s32 D_800A71E4[];
extern s32 D_800A71F0[];
extern s32 D_800A71FC[];
extern s32 D_800A7208[];
extern s32 D_800A7214[];
extern s32 D_800A7220[];
extern s32 D_800A7250[];
extern s32 D_800A725C[];
extern s32 D_800A7268[];
extern s32 D_800A7274[];
extern s32 D_800A7280[];
extern s32 D_800A728C[];
extern s32 D_800A7298[];
extern s32 D_800A72A4[];
extern s32 D_800A72D4[];
extern s32 D_800A72E0[];
extern s32 D_800A72EC[];
extern s32 D_800A72F8[];
extern s32 D_800A7304[];
extern s32 D_800A7310[];
extern s32 D_800A731C[];
extern s32 D_800A7328[];
extern s32 D_800A7358[];
extern s32 D_800A7364[];
extern s32 D_800A7370[];
extern s32 D_800A737C[];
extern s32 D_800A7388[];
extern s32 D_800A7394[];
extern s32 D_800A73A0[];
extern s32 D_800A73AC[];
extern s32 D_800A73DC[];
extern s32 D_800A73E8[];
extern s32 D_800A73F4[];
extern s32 D_800A7400[];
extern s32 D_800A740C[];
extern s32 D_800A7418[];
extern s32 D_800A7424[];
extern s32 D_800A7430[];
extern s32 D_800A7460[];
extern s32 D_800A746C[];
extern s32 D_800A7478[];
extern s32 D_800A7484[];
extern s32 D_800A7490[];
extern s32 D_800A749C[];
extern s32 D_800A74A8[];
extern s32 D_800A74B4[];
extern s32 D_800A74E4[];
extern s32 D_800A74F0[];
extern s32 D_800A74FC[];
extern s32 D_800A7508[];
extern s32 D_800A7514[];
extern s32 D_800A7520[];
extern s32 D_800A752C[];
extern s32 D_800A7538[];
extern s32 D_800A7568[];
extern s32 D_800A7574[];
extern s32 D_800A7580[];
extern s32 D_800A758C[];
extern s32 D_800A7598[];
extern s32 D_800A75A4[];
extern s32 D_800A75B0[];
extern s32 D_800A75BC[];
extern s32 D_800A75EC[];
extern s32 D_800A75F8[];
extern s32 D_800A7604[];
extern s32 D_800A7610[];
extern s32 D_800A761C[];
extern s32 D_800A7628[];
extern s32 D_800A7634[];
extern s32 D_800A7640[];
extern s32 D_800A7670[];
extern s32 D_800A767C[];
extern s32 D_800A7688[];
extern s32 D_800A7694[];
extern s32 D_800A76A0[];
extern s32 D_800A76AC[];
extern s32 D_800A76B8[];
extern s32 D_800A76C4[];
extern s32 D_800A76F4[];
extern s32 D_800A7700[];
extern s32 D_800A770C[];
extern s32 D_800A7718[];
extern s32 D_800A7724[];
extern s32 D_800A7730[];
extern s32 D_800A773C[];
extern s32 D_800A7748[];
extern s32 D_800A7778[];
extern s32 D_800A7784[];
extern s32 D_800A7790[];
extern s32 D_800A779C[];
extern s32 D_800A77A8[];
extern s32 D_800A77B4[];
extern s32 D_800A77C0[];
extern s32 D_800A77CC[];
extern s32 D_800A77FC[];
extern s32 D_800A7808[];
extern s32 D_800A7814[];
extern s32 D_800A7820[];
extern s32 D_800A782C[];
extern s32 D_800A7838[];
extern s32 D_800A7844[];
extern s32 D_800A7850[];
extern s32 D_800A7880[];
extern s32 D_800A788C[];
extern s32 D_800A7898[];
extern s32 D_800A78A4[];
extern s32 D_800A78B0[];
extern s32 D_800A78BC[];
extern s32 D_800A78C8[];
extern s32 D_800A78D4[];
extern s32 D_800A7904[];
extern s32 D_800A7910[];
extern s32 D_800A791C[];
extern s32 D_800A7928[];
extern s32 D_800A7934[];
extern s32 D_800A7940[];
extern s32 D_800A794C[];
extern s32 D_800A7958[];
extern s32 D_800A7988[];
extern s32 D_800A7994[];
extern s32 D_800A79A0[];
extern s32 D_800A79AC[];
extern s32 D_800A79B8[];
extern s32 D_800A79C4[];
extern s32 D_800A79D0[];
extern s32 D_800A79DC[];
extern s32 D_800A7A0C[];
extern s32 D_800A7A18[];
extern s32 D_800A7A24[];
extern s32 D_800A7A30[];
extern s32 D_800A7A3C[];
extern s32 D_800A7A48[];
extern s32 D_800A7A54[];
extern s32 D_800A7A60[];
extern s32 D_800A7A90[];
extern s32 D_800A7A9C[];
extern s32 D_800A7AA8[];
extern s32 D_800A7AB4[];
extern s32 D_800A7AC0[];
extern s32 D_800A7ACC[];
extern s32 D_800A7AD8[];
extern s32 D_800A7AE4[];
extern s32 D_800A7B14[];
extern s32 D_800A7B20[];
extern s32 D_800A7B2C[];
extern s32 D_800A7B38[];
extern s32 D_800A7B44[];
extern s32 D_800A7B50[];
extern s32 D_800A7B5C[];
extern s32 D_800A7B68[];
extern s32 D_800A7B98[];
extern s32 D_800A7BA4[];
extern s32 D_800A7BB0[];
extern s32 D_800A7BBC[];
extern s32 D_800A7BC8[];
extern s32 D_800A7BD4[];
extern s32 D_800A7BE0[];
extern s32 D_800A7BEC[];
extern s32 D_800A7C1C[];
extern s32 D_800A7C28[];
extern s32 D_800A7C34[];
extern s32 D_800A7C40[];
extern s32 D_800A7C4C[];
extern s32 D_800A7C58[];
extern s32 D_800A7C64[];
extern s32 D_800A7C70[];
extern s32 D_800A7CA0[];
extern s32 D_800A7CAC[];
extern s32 D_800A7CB8[];
extern s32 D_800A7CC4[];
extern s32 D_800A7CD0[];
extern s32 D_800A7CDC[];
extern s32 D_800A7CE8[];
extern s32 D_800A7CF4[];
extern s32 D_800A7D24[];
extern s32 D_800A7D30[];
extern s32 D_800A7D3C[];
extern s32 D_800A7D48[];
extern s32 D_800A7D54[];
extern s32 D_800A7D60[];
extern s32 D_800A7D6C[];
extern s32 D_800A7D78[];
extern s32 D_800A7DA8[];
extern s32 D_800A7DB4[];
extern s32 D_800A7DC0[];
extern s32 D_800A7DCC[];
extern s32 D_800A7DD8[];
extern s32 D_800A7DE4[];
extern s32 D_800A7DF0[];
extern s32 D_800A7DFC[];
extern s32 D_800A7E2C[];
extern s32 D_800A7E38[];
extern s32 D_800A7E44[];
extern s32 D_800A7E50[];
extern s32 D_800A7E5C[];
extern s32 D_800A7E68[];
extern s32 D_800A7E74[];
extern s32 D_800A7E80[];
extern s32 D_800A7EB0[];
extern s32 D_800A7EBC[];
extern s32 D_800A7EC8[];
extern s32 D_800A7ED4[];
extern s32 D_800A7EE0[];
extern s32 D_800A7EEC[];
extern s32 D_800A7EF8[];
extern s32 D_800A7F04[];
extern s32 D_800A7F34[];
extern s32 D_800A7F40[];
extern s32 D_800A7F4C[];
extern s32 D_800A7F58[];
extern s32 D_800A7F64[];
extern s32 D_800A7F70[];
extern s32 D_800A7F7C[];
extern s32 D_800A7F88[];
extern s32 D_800A7FB8[];
extern s32 D_800A7FC4[];
extern s32 D_800A7FD0[];
extern s32 D_800A7FDC[];
extern s32 D_800A7FE8[];
extern s32 D_800A7FF4[];
extern s32 D_800A8000[];
extern s32 D_800A800C[];
extern s32 D_800A803C[];
extern s32 D_800A8048[];
extern s32 D_800A8054[];
extern s32 D_800A8060[];
extern s32 D_800A806C[];
extern s32 D_800A8078[];
extern s32 D_800A8084[];
extern s32 D_800A8090[];
extern s32 D_800A80C0[];
extern s32 D_800A80CC[];
extern s32 D_800A80D8[];
extern s32 D_800A80E4[];
extern s32 D_800A80F0[];
extern s32 D_800A80FC[];
extern s32 D_800A8108[];
extern s32 D_800A8114[];
extern s32 D_800A8144[];
extern s32 D_800A8150[];
extern s32 D_800A815C[];
extern s32 D_800A8168[];
extern s32 D_800A8174[];
extern s32 D_800A8180[];
extern s32 D_800A818C[];
extern s32 D_800A8198[];
extern s32 D_800A81C8[];
extern s32 D_800A81D4[];
extern s32 D_800A81E0[];
extern s32 D_800A81EC[];
extern s32 D_800A81F8[];
extern s32 D_800A8204[];
extern s32 D_800A8210[];
extern s32 D_800A821C[];
extern s32 D_800A824C[];
extern s32 D_800A8258[];
extern s32 D_800A8264[];
extern s32 D_800A8270[];
extern s32 D_800A827C[];
extern s32 D_800A8288[];
extern s32 D_800A8294[];
extern s32 D_800A82A0[];
extern s32 D_800A82D0[];
extern s32 D_800A82DC[];
extern s32 D_800A82E8[];
extern s32 D_800A82F4[];
extern s32 D_800A8300[];
extern s32 D_800A830C[];
extern s32 D_800A8318[];
extern s32 D_800A8324[];
extern s32 D_800A8354[];
extern s32 D_800A8360[];
extern s32 D_800A836C[];
extern s32 D_800A8378[];
extern s32 D_800A8384[];
extern s32 D_800A8390[];
extern s32 D_800A839C[];
extern s32 D_800A83A8[];
extern s32 D_800A83D8[];
extern s32 D_800A83E4[];
extern s32 D_800A83F0[];
extern s32 D_800A83FC[];
extern s32 D_800A8408[];
extern s32 D_800A8414[];
extern s32 D_800A8420[];
extern s32 D_800A842C[];
extern s32 D_800A845C[];
extern s32 D_800A8468[];
extern s32 D_800A8474[];
extern s32 D_800A8480[];
extern s32 D_800A848C[];
extern s32 D_800A8498[];
extern s32 D_800A84A4[];
extern s32 D_800A84B0[];
extern s32 D_800A84E0[];
extern s32 D_800A84EC[];
extern s32 D_800A84F8[];
extern s32 D_800A8504[];
extern s32 D_800A8510[];
extern s32 D_800A851C[];
extern s32 D_800A8528[];
extern s32 D_800A8534[];
extern s32 D_800A8564[];
extern s32 D_800A8570[];
extern s32 D_800A857C[];
extern s32 D_800A8588[];
extern s32 D_800A8594[];
extern s32 D_800A85A0[];
extern s32 D_800A85AC[];
extern s32 D_800A85B8[];
extern s32 D_800A5AF8[];
extern s32 D_800A5B7C[];
extern s32 D_800A5C00[];
extern s32 D_800A5C84[];
extern s32 D_800A5D08[];
extern s32 D_800A5D8C[];
extern s32 D_800A5E10[];
extern s32 D_800A5E94[];
extern s32 D_800A5F18[];
extern s32 D_800A5F9C[];
extern s32 D_800A6020[];
extern s32 D_800A60A4[];
extern s32 D_800A6128[];
extern s32 D_800A61AC[];
extern s32 D_800A6230[];
extern s32 D_800A62B4[];
extern s32 D_800A6338[];
extern s32 D_800A63BC[];
extern s32 D_800A6440[];
extern s32 D_800A64C4[];
extern s32 D_800A6548[];
extern s32 D_800A65CC[];
extern s32 D_800A6650[];
extern s32 D_800A66D4[];
extern s32 D_800A6758[];
extern s32 D_800A67DC[];
extern s32 D_800A6860[];
extern s32 D_800A68E4[];
extern s32 D_800A6968[];
extern s32 D_800A69EC[];
extern s32 D_800A6A70[];
extern s32 D_800A6AF4[];
extern s32 D_800A6B78[];
extern s32 D_800A6BFC[];
extern s32 D_800A6C80[];
extern s32 D_800A6D04[];
extern s32 D_800A6D88[];
extern s32 D_800A6E0C[];
extern s32 D_800A6E90[];
extern s32 D_800A6F14[];
extern s32 D_800A6F98[];
extern s32 D_800A701C[];
extern s32 D_800A70A0[];
extern s32 D_800A7124[];
extern s32 D_800A71A8[];
extern s32 D_800A722C[];
extern s32 D_800A72B0[];
extern s32 D_800A7334[];
extern s32 D_800A73B8[];
extern s32 D_800A743C[];
extern s32 D_800A74C0[];
extern s32 D_800A7544[];
extern s32 D_800A75C8[];
extern s32 D_800A764C[];
extern s32 D_800A76D0[];
extern s32 D_800A7754[];
extern s32 D_800A77D8[];
extern s32 D_800A785C[];
extern s32 D_800A78E0[];
extern s32 D_800A7964[];
extern s32 D_800A79E8[];
extern s32 D_800A7A6C[];
extern s32 D_800A7AF0[];
extern s32 D_800A7B74[];
extern s32 D_800A7BF8[];
extern s32 D_800A7C7C[];
extern s32 D_800A7D00[];
extern s32 D_800A7D84[];
extern s32 D_800A7E08[];
extern s32 D_800A7E8C[];
extern s32 D_800A7F10[];
extern s32 D_800A7F94[];
extern s32 D_800A8018[];
extern s32 D_800A809C[];
extern s32 D_800A8120[];
extern s32 D_800A81A4[];
extern s32 D_800A8228[];
extern s32 D_800A82AC[];
extern s32 D_800A8330[];
extern s32 D_800A83B4[];
extern s32 D_800A8438[];
extern s32 D_800A84BC[];
extern s32 D_800A8540[];
extern s32 D_800A85C4[];
extern s32 D_800A8B1C[];
extern s32 D_800A8954[];
extern s32 D_800A8B28[];
extern s32 D_800A896C[];
extern s32 D_800A8B34[];
extern s32 D_800A8984[];
extern s32 D_800A8B40[];
extern s32 D_800A899C[];
extern s32 D_800A8B4C[];
extern s32 D_800A89B4[];
extern s32 D_800A8B58[];
extern s32 D_800A89CC[];
extern s32 D_800A8B64[];
extern s32 D_800A89E4[];
extern s32 D_800A8B70[];
extern s32 D_800A89FC[];
extern s32 D_800A8B7C[];
extern s32 D_800A8A14[];
extern s32 D_800A8B88[];
extern s32 D_800A8A2C[];
extern s32 D_800A8B94[];
extern s32 D_800A8A44[];
extern s32 D_800A8BA0[];
extern s32 D_800A8A5C[];
extern s32 D_800A8BAC[];
extern s32 D_800A8A74[];
extern s32 D_800A8BB8[];
extern s32 D_800A8A8C[];
extern s32 D_800A8BC4[];
extern s32 D_800A8AA4[];
extern s32 D_800A8BD0[];
extern s32 D_800A8ABC[];
extern s32 D_800A8BDC[];
extern s32 D_800A8AD4[];
extern s32 D_800A8BE8[];
extern s32 D_800A8AEC[];
extern s32 D_800A8BF4[];
extern s32 D_800A8B04[];
extern s32 D_800A8C00[];
extern s32 D_800A8C0C[];
extern s32 D_800A8C18[];
extern s32 D_800A8C24[];
extern s32 D_800A8C30[];
extern s32 D_800A8C3C[];
extern s32 D_800A8C48[];
extern s32 D_800A8C54[];
extern s32 D_800A8C60[];
extern s32 D_800A8C6C[];
extern s32 D_800A8C78[];
extern s32 D_800A8C84[];
extern s32 D_800A8C90[];
extern s32 D_800A8C9C[];
extern s32 D_800A8CB0[];
extern s32 D_800A8CC4[];
extern s32 D_800A8CD8[];
extern s32 D_800A8CEC[];
extern s32 D_800A8D00[];
extern s32 D_800A8D14[];
extern s32 D_800A8D28[];
extern s32 D_800A8D3C[];
extern s32 D_800A8D50[];
extern s32 D_800A8D64[];
extern s32 D_800A8D78[];
extern s32 D_800A8D8C[];
extern s32 D_800A8DA0[];
extern s32 D_800A8DB4[];
extern s32 D_800A8DC8[];
extern s32 D_800A8DDC[];
extern s32 D_800A8DF0[];
extern s32 D_800A8E04[];
extern s32 D_800A8E18[];
extern s32 D_800A8E2C[];
extern s32 D_800A8E40[];
extern s32 D_800A8E54[];
extern s32 D_800A8E68[];
extern s32 D_800A8E7C[];
extern s32 D_800A8E90[];
extern s32 D_800A8EA4[];
extern s32 D_800A8EB8[];
extern s32 D_800A8ECC[];
extern s32 D_800A8EE0[];
extern s32 D_800A8EF4[];
extern s32 D_800A8F08[];
extern s32 D_800A8F1C[];

StagePoint D_800A4F90 = { 0x2EB, 1, 1, 0x240, 160, 1, NULL };
StagePoint D_800A4FA0 = { 0x2EE, 1, 1, 0x130, 200, 1, &D_800A4F90 };
StagePoint D_800A4FB0 = { 0x2E8, 1, 2, 176, 0x168, 5, &D_800A4FA0 };
StagePoints D_800A4FC0 = { 1, 1, &D_800A4FB0 };
StagePoint D_800A4FC8 = { 0x2EE, 1, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A4FD8 = { 0x2E9, 1, 1, 0x240, 240, 1, &D_800A4FC8 };
StagePoint D_800A4FE8 = { 0x2EC, 1, 1, 240, 0x1D8, 5, &D_800A4FD8 };
StagePoints D_800A4FF8 = { 1, 2, &D_800A4FE8 };
StagePoint D_800A5000 = { 0x2EE, 2, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5010 = { 0x2E9, 2, 1, 0x240, 240, 1, &D_800A5000 };
StagePoint D_800A5020 = { 0x2EA, 2, 1, 224, 0x200, 5, &D_800A5010 };
StagePoints D_800A5030 = { 2, 1, &D_800A5020 };
StagePoint D_800A5038 = { 0x2EE, 2, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5048 = { 0x2E9, 2, 2, 0x240, 240, 1, &D_800A5038 };
StagePoint D_800A5058 = { 0x2EE, 2, 1, 224, 0x240, 5, &D_800A5048 };
StagePoints D_800A5068 = { 2, 2, &D_800A5058 };
StagePoint D_800A5070 = { 0x2EE, 3, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5080 = { 0x2EE, 3, 2, 0x130, 200, 1, &D_800A5070 };
StagePoint D_800A5090 = { 0x2E8, 3, 2, 176, 0x168, 5, &D_800A5080 };
StagePoints D_800A50A0 = { 3, 1, &D_800A5090 };
StagePoint D_800A50A8 = { 0x2EC, 3, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A50B8 = { 0x2EE, 3, 3, 0x130, 200, 1, &D_800A50A8 };
StagePoint D_800A50C8 = { 0x2EE, 3, 1, 224, 0x240, 5, &D_800A50B8 };
StagePoints D_800A50D8 = { 3, 2, &D_800A50C8 };
StagePoint D_800A50E0 = { 0x2EE, 3, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A50F0 = { 0x2EE, 3, 4, 0x130, 200, 1, &D_800A50E0 };
StagePoint D_800A5100 = { 0x2EE, 3, 2, 224, 0x240, 5, &D_800A50F0 };
StagePoints D_800A5110 = { 3, 3, &D_800A5100 };
StagePoint D_800A5118 = { 0x2EE, 3, 4, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5128 = { 0x2EE, 3, 5, 0x130, 200, 1, &D_800A5118 };
StagePoint D_800A5138 = { 0x2E8, 3, 4, 176, 0x168, 5, &D_800A5128 };
StagePoints D_800A5148 = { 3, 4, &D_800A5138 };
StagePoint D_800A5150 = { 0x2EE, 4, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5160 = { 0x2E9, 4, 1, 0x240, 240, 1, &D_800A5150 };
StagePoint D_800A5170 = { 0x2EE, 4, 1, 224, 0x240, 5, &D_800A5160 };
StagePoints D_800A5180 = { 4, 1, &D_800A5170 };
StagePoint D_800A5188 = { 0x2EB, 4, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5198 = { 0x2E9, 4, 2, 0x240, 240, 1, &D_800A5188 };
StagePoint D_800A51A8 = { 0x2EE, 4, 2, 224, 0x240, 5, &D_800A5198 };
StagePoints D_800A51B8 = { 4, 2, &D_800A51A8 };
StagePoint D_800A51C0 = { 0x2EE, 5, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A51D0 = { 0x2EE, 5, 2, 0x130, 200, 1, &D_800A51C0 };
StagePoint D_800A51E0 = { 0x2EA, 5, 1, 224, 0x200, 5, &D_800A51D0 };
StagePoints D_800A51F0 = { 5, 1, &D_800A51E0 };
StagePoint D_800A51F8 = { 0x2E9, 5, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5208 = { 0x2EE, 5, 3, 0x130, 200, 1, &D_800A51F8 };
StagePoint D_800A5218 = { 0x2EE, 5, 1, 224, 0x240, 5, &D_800A5208 };
StagePoints D_800A5228 = { 5, 2, &D_800A5218 };
StagePoint D_800A5230 = { 0x2EE, 5, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5240 = { 0x2EE, 5, 4, 0x130, 200, 1, &D_800A5230 };
StagePoint D_800A5250 = { 0x2EE, 5, 2, 224, 0x240, 5, &D_800A5240 };
StagePoints D_800A5260 = { 5, 3, &D_800A5250 };
StagePoint D_800A5268 = { 0x2EE, 5, 4, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5278 = { 0x2EC, 5, 1, 0x3B0, 120, 1, &D_800A5268 };
StagePoint D_800A5288 = { 0x2E8, 5, 3, 176, 0x168, 5, &D_800A5278 };
StagePoints D_800A5298 = { 5, 4, &D_800A5288 };
StagePoint D_800A52A0 = { 0x2EE, 6, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A52B0 = { 0x2EE, 6, 2, 0x130, 200, 1, &D_800A52A0 };
StagePoint D_800A52C0 = { 0x2E8, 6, 1, 176, 0x168, 5, &D_800A52B0 };
StagePoints D_800A52D0 = { 6, 1, &D_800A52C0 };
StagePoint D_800A52D8 = { 0x2EE, 6, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A52E8 = { 0x2EC, 6, 2, 0x3B0, 120, 1, &D_800A52D8 };
StagePoint D_800A52F8 = { 0x2EA, 6, 2, 224, 0x200, 5, &D_800A52E8 };
StagePoints D_800A5308 = { 6, 2, &D_800A52F8 };
StagePoint D_800A5310 = { 0x2E9, 8, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5320 = { 0x2EE, 8, 1, 0x130, 200, 1, &D_800A5310 };
StagePoint D_800A5330 = { 0x2E8, 8, 1, 176, 0x168, 5, &D_800A5320 };
StagePoints D_800A5340 = { 8, 1, &D_800A5330 };
StagePoint D_800A5348 = { 0x2EE, 8, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5358 = { 0x2E9, 8, 3, 0x240, 240, 1, &D_800A5348 };
StagePoint D_800A5368 = { 0x2EC, 8, 1, 240, 0x1D8, 5, &D_800A5358 };
StagePoints D_800A5378 = { 8, 2, &D_800A5368 };
StagePoint D_800A5380 = { 0x2EE, 9, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5390 = { 0x2E9, 9, 1, 0x240, 240, 1, &D_800A5380 };
StagePoint D_800A53A0 = { 0x2EA, 9, 1, 224, 0x200, 5, &D_800A5390 };
StagePoints D_800A53B0 = { 9, 1, &D_800A53A0 };
StagePoint D_800A53B8 = { 0x2EE, 9, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A53C8 = { 0x2E9, 9, 3, 0x240, 240, 1, &D_800A53B8 };
StagePoint D_800A53D8 = { 0x2EE, 9, 1, 224, 0x240, 5, &D_800A53C8 };
StagePoints D_800A53E8 = { 9, 2, &D_800A53D8 };
StagePoint D_800A53F0 = { 0x2EE, 10, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5400 = { 0x2EC, 10, 2, 0x3B0, 120, 1, &D_800A53F0 };
StagePoint D_800A5410 = { 0x2E8, 10, 2, 176, 0x168, 5, &D_800A5400 };
StagePoints D_800A5420 = { 10, 1, &D_800A5410 };
StagePoint D_800A5428 = { 0x2EE, 11, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5438 = { 0x2EC, 11, 2, 0x3B0, 120, 1, &D_800A5428 };
StagePoint D_800A5448 = { 0x2E8, 11, 2, 176, 0x168, 5, &D_800A5438 };
StagePoints D_800A5458 = { 11, 1, &D_800A5448 };
StagePoint D_800A5460 = { 0x2EC, 12, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A5470 = { 0x2EE, 12, 1, 0x130, 200, 1, &D_800A5460 };
StagePoint D_800A5480 = { 0x2E8, 12, 1, 176, 0x168, 5, &D_800A5470 };
StagePoints D_800A5490 = { 12, 1, &D_800A5480 };
StagePoint D_800A5498 = { 0x2EE, 12, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A54A8 = { 0x2EE, 12, 2, 0x130, 200, 1, &D_800A5498 };
StagePoint D_800A54B8 = { 0x2EC, 12, 1, 240, 0x1D8, 5, &D_800A54A8 };
StagePoints D_800A54C8 = { 12, 2, &D_800A54B8 };
StagePoint D_800A54D0 = { 0x2EC, 13, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A54E0 = { 0x2EE, 13, 1, 0x130, 200, 1, &D_800A54D0 };
StagePoint D_800A54F0 = { 0x2EA, 13, 2, 224, 0x200, 5, &D_800A54E0 };
StagePoints D_800A5500 = { 13, 1, &D_800A54F0 };
StagePoint D_800A5508 = { 0x2EE, 13, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5518 = { 0x2EE, 13, 2, 0x130, 200, 1, &D_800A5508 };
StagePoint D_800A5528 = { 0x2EC, 13, 1, 240, 0x1D8, 5, &D_800A5518 };
StagePoints D_800A5538 = { 13, 2, &D_800A5528 };
StagePoint D_800A5540 = { 0x2EB, 14, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5550 = { 0x2ED, 14, 2, 0x3A0, 128, 1, &D_800A5540 };
StagePoint D_800A5560 = { 0x2EA, 14, 1, 224, 0x200, 5, &D_800A5550 };
StagePoints D_800A5570 = { 14, 1, &D_800A5560 };
StagePoint D_800A5578 = { 0x2E9, 14, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5588 = { 0x2EB, 14, 2, 0x240, 160, 1, &D_800A5578 };
StagePoint D_800A5598 = { 0x2ED, 14, 1, 0x350, 0x1F8, 5, &D_800A5588 };
StagePoints D_800A55A8 = { 14, 2, &D_800A5598 };
StagePoint D_800A55B0 = { 0x2EB, 16, 1, 0x240, 160, 1, NULL };
StagePoint D_800A55C0 = { 0x2EB, 16, 2, 0x240, 160, 1, &D_800A55B0 };
StagePoint D_800A55D0 = { 0x2EE, 16, 1, 224, 0x240, 5, &D_800A55C0 };
StagePoints D_800A55E0 = { 16, 1, &D_800A55D0 };
StagePoint D_800A55E8 = { 0x2EC, 19, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A55F8 = { 0x2ED, 19, 2, 0x3A0, 128, 1, &D_800A55E8 };
StagePoint D_800A5608 = { 0x2EE, 19, 2, 224, 0x240, 5, &D_800A55F8 };
StagePoints D_800A5618 = { 19, 1, &D_800A5608 };
StagePoint D_800A5620 = { 0x2EB, 19, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5630 = { 0x2EB, 19, 2, 0x240, 160, 1, &D_800A5620 };
StagePoint D_800A5640 = { 0x2ED, 19, 1, 0x350, 0x1F8, 5, &D_800A5630 };
StagePoints D_800A5650 = { 19, 2, &D_800A5640 };
StagePoint D_800A5658 = { 0x2EB, 19, 3, 0x240, 160, 1, NULL };
StagePoint D_800A5668 = { 0x2EC, 19, 5, 0x3B0, 120, 1, &D_800A5658 };
StagePoint D_800A5678 = { 0x2EC, 19, 4, 240, 0x1D8, 5, &D_800A5668 };
StagePoints D_800A5688 = { 19, 3, &D_800A5678 };
StagePoint D_800A5690 = { 0x2EC, 20, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A56A0 = { 0x2ED, 20, 2, 0x3A0, 128, 1, &D_800A5690 };
StagePoint D_800A56B0 = { 0x2EE, 20, 2, 224, 0x240, 5, &D_800A56A0 };
StagePoints D_800A56C0 = { 20, 1, &D_800A56B0 };
StagePoint D_800A56C8 = { 0x2EB, 20, 1, 0x240, 160, 1, NULL };
StagePoint D_800A56D8 = { 0x2EC, 20, 4, 0x3B0, 120, 1, &D_800A56C8 };
StagePoint D_800A56E8 = { 0x2ED, 20, 1, 0x350, 0x1F8, 5, &D_800A56D8 };
StagePoints D_800A56F8 = { 20, 2, &D_800A56E8 };
StagePoint D_800A5700 = { 0x2EB, 20, 2, 0x240, 160, 1, NULL };
StagePoint D_800A5710 = { 0x2EC, 20, 5, 0x3B0, 120, 1, &D_800A5700 };
StagePoint D_800A5720 = { 0x2EC, 20, 3, 240, 0x1D8, 5, &D_800A5710 };
StagePoints D_800A5730 = { 20, 3, &D_800A5720 };
StagePoint D_800A5738 = { 0x2EB, 20, 3, 0x240, 160, 1, NULL };
StagePoint D_800A5748 = { 0x2EC, 20, 6, 0x3B0, 120, 1, &D_800A5738 };
StagePoint D_800A5758 = { 0x2EC, 20, 4, 240, 0x1D8, 5, &D_800A5748 };
StagePoints D_800A5768 = { 20, 4, &D_800A5758 };
StagePoint D_800A5770 = { 0x2EC, 20, 7, 0x3B0, 120, 1, NULL };
StagePoint D_800A5780 = { 0x2EC, 20, 8, 0x3B0, 120, 1, &D_800A5770 };
StagePoint D_800A5790 = { 0x2EC, 20, 5, 240, 0x1D8, 5, &D_800A5780 };
StagePoints D_800A57A0 = { 20, 5, &D_800A5790 };
StagePoint D_800A57A8 = { 0x2EC, 20, 9, 0x3B0, 120, 1, NULL };
StagePoint D_800A57B8 = { 0x2EB, 20, 7, 0x240, 160, 1, &D_800A57A8 };
StagePoint D_800A57C8 = { 0x2EC, 20, 7, 240, 0x1D8, 5, &D_800A57B8 };
StagePoints D_800A57D8 = { 20, 6, &D_800A57C8 };
StagePoint D_800A57E0 = { 0x2EB, 25, 1, 0x240, 160, 1, NULL };
StagePoint D_800A57F0 = { 0x2EB, 25, 2, 0x240, 160, 1, &D_800A57E0 };
StagePoint D_800A5800 = { 0x2EE, 25, 1, 224, 0x240, 5, &D_800A57F0 };
StagePoints D_800A5810 = { 25, 1, &D_800A5800 };
StagePoint D_800A5818 = { 0x2EB, 27, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5828 = { 0x2ED, 27, 2, 0x3A0, 128, 1, &D_800A5818 };
StagePoint D_800A5838 = { 0x2EA, 27, 1, 224, 0x200, 5, &D_800A5828 };
StagePoints D_800A5848 = { 27, 1, &D_800A5838 };
StagePoint D_800A5850 = { 0x2E9, 27, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5860 = { 0x2EB, 27, 2, 0x240, 160, 1, &D_800A5850 };
StagePoint D_800A5870 = { 0x2ED, 27, 1, 0x350, 0x1F8, 5, &D_800A5860 };
StagePoints D_800A5880 = { 27, 2, &D_800A5870 };
StagePoint D_800A5888 = { 0x2EC, 28, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A5898 = { 0x2EE, 28, 1, 0x130, 200, 1, &D_800A5888 };
StagePoint D_800A58A8 = { 0x2E8, 28, 1, 176, 0x168, 5, &D_800A5898 };
StagePoints D_800A58B8 = { 28, 1, &D_800A58A8 };
StagePoint D_800A58C0 = { 0x2EE, 28, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A58D0 = { 0x2EE, 28, 2, 0x130, 200, 1, &D_800A58C0 };
StagePoint D_800A58E0 = { 0x2EC, 28, 1, 240, 0x1D8, 5, &D_800A58D0 };
StagePoints D_800A58F0 = { 28, 2, &D_800A58E0 };
StagePoint D_800A58F8 = { 0x2EB, 29, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5908 = { 0x2ED, 29, 2, 0x3A0, 128, 1, &D_800A58F8 };
StagePoint D_800A5918 = { 0x2EE, 29, 1, 224, 0x240, 5, &D_800A5908 };
StagePoints D_800A5928 = { 29, 1, &D_800A5918 };
StagePoint D_800A5930 = { 0x2EB, 29, 2, 0x240, 160, 1, NULL };
StagePoint D_800A5940 = { 0x2EB, 29, 3, 0x240, 160, 1, &D_800A5930 };
StagePoint D_800A5950 = { 0x2ED, 29, 1, 0x350, 0x1F8, 5, &D_800A5940 };
StagePoints D_800A5960 = { 29, 2, &D_800A5950 };
StagePoint D_800A5968 = { 0x2EC, 30, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5978 = { 0x2EE, 30, 1, 0x130, 200, 1, &D_800A5968 };
StagePoint D_800A5988 = { 0x2E8, 30, 1, 176, 0x168, 5, &D_800A5978 };
StagePoints D_800A5998 = { 30, 1, &D_800A5988 };
StagePoint D_800A59A0 = { 0x2EE, 30, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A59B0 = { 0x2EE, 30, 2, 0x130, 200, 1, &D_800A59A0 };
StagePoint D_800A59C0 = { 0x2E8, 30, 2, 176, 0x168, 5, &D_800A59B0 };
StagePoints D_800A59D0 = { 30, 2, &D_800A59C0 };
StagePoints *D_800A59D8[] = {
    &D_800A4FC0, &D_800A4FF8, &D_800A5030, &D_800A5068,
    &D_800A50A0, &D_800A50D8, &D_800A5110, &D_800A5148,
    &D_800A5180, &D_800A51B8, &D_800A51F0, &D_800A5228,
    &D_800A5260, &D_800A5298, &D_800A52D0, &D_800A5308,
    &D_800A5340, &D_800A5378, &D_800A53B0, &D_800A53E8,
    &D_800A5420, &D_800A5458, &D_800A5490, &D_800A54C8,
    &D_800A5500, &D_800A5538, &D_800A5570, &D_800A55A8,
    &D_800A55E0, &D_800A5618, &D_800A5650, &D_800A5688,
    &D_800A56C0, &D_800A56F8, &D_800A5730, &D_800A5768,
    &D_800A57A0, &D_800A57D8, &D_800A5810, &D_800A5848,
    &D_800A5880, &D_800A58B8, &D_800A58F0, &D_800A5928,
    &D_800A5960, &D_800A5998, &D_800A59D0, NULL,
};
s32 D_800A5A98[] = {
    174, 10, 0x60080000,
};
s32 D_800A5AA4[] = {
    174, 10, 0x60080000,
};
s32 D_800A5AB0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5ABC[] = {
    170, 10, 0x60080000,
};
s32 D_800A5AC8[] = {
    170, 10, 0x60080000,
};
s32 D_800A5AD4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5AE0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5AEC[] = {
    170, 10, 0x60080000,
};
s32 D_800A5AF8[] = {
    1, (s32)D_800A5A98, (s32)D_800A5AA4, (s32)D_800A5AB0,
    (s32)D_800A5ABC, (s32)D_800A5AC8, (s32)D_800A5AD4, (s32)D_800A5AE0,
    (s32)D_800A5AEC,
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
    0, 0, 0x60040000,
};
s32 D_800A5B4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B58[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B7C[] = {
    0, (s32)D_800A5B1C, (s32)D_800A5B28, (s32)D_800A5B34,
    (s32)D_800A5B40, (s32)D_800A5B4C, (s32)D_800A5B58, (s32)D_800A5B64,
    (s32)D_800A5B70,
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
    0, 0, 0x60040000,
};
s32 D_800A5BD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C00[] = {
    0, (s32)D_800A5BA0, (s32)D_800A5BAC, (s32)D_800A5BB8,
    (s32)D_800A5BC4, (s32)D_800A5BD0, (s32)D_800A5BDC, (s32)D_800A5BE8,
    (s32)D_800A5BF4,
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
    0, 0, 0x60040000,
};
s32 D_800A5C54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C60[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C84[] = {
    0, (s32)D_800A5C24, (s32)D_800A5C30, (s32)D_800A5C3C,
    (s32)D_800A5C48, (s32)D_800A5C54, (s32)D_800A5C60, (s32)D_800A5C6C,
    (s32)D_800A5C78,
};
s32 D_800A5CA8[] = {
    174, 10, 0x60080000,
};
s32 D_800A5CB4[] = {
    174, 10, 0x60080000,
};
s32 D_800A5CC0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5CCC[] = {
    170, 10, 0x60080000,
};
s32 D_800A5CD8[] = {
    170, 10, 0x60080000,
};
s32 D_800A5CE4[] = {
    110, 10, 0x60080000,
};
s32 D_800A5CF0[] = {
    110, 10, 0x60080000,
};
s32 D_800A5CFC[] = {
    110, 10, 0x60080000,
};
s32 D_800A5D08[] = {
    1, (s32)D_800A5CA8, (s32)D_800A5CB4, (s32)D_800A5CC0,
    (s32)D_800A5CCC, (s32)D_800A5CD8, (s32)D_800A5CE4, (s32)D_800A5CF0,
    (s32)D_800A5CFC,
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
    0, 0, 0x60040000,
};
s32 D_800A5D5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D74[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D80[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D8C[] = {
    0, (s32)D_800A5D2C, (s32)D_800A5D38, (s32)D_800A5D44,
    (s32)D_800A5D50, (s32)D_800A5D5C, (s32)D_800A5D68, (s32)D_800A5D74,
    (s32)D_800A5D80,
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
    0, 0, 0x60040000,
};
s32 D_800A5DE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E10[] = {
    0, (s32)D_800A5DB0, (s32)D_800A5DBC, (s32)D_800A5DC8,
    (s32)D_800A5DD4, (s32)D_800A5DE0, (s32)D_800A5DEC, (s32)D_800A5DF8,
    (s32)D_800A5E04,
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
    0, 0, 0x60040000,
};
s32 D_800A5E64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E94[] = {
    0, (s32)D_800A5E34, (s32)D_800A5E40, (s32)D_800A5E4C,
    (s32)D_800A5E58, (s32)D_800A5E64, (s32)D_800A5E70, (s32)D_800A5E7C,
    (s32)D_800A5E88,
};
s32 D_800A5EB8[] = {
    174, 10, 0x60080000,
};
s32 D_800A5EC4[] = {
    174, 10, 0x60080000,
};
s32 D_800A5ED0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EDC[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EE8[] = {
    182, 10, 0x60080000,
};
s32 D_800A5EF4[] = {
    182, 10, 0x60080000,
};
s32 D_800A5F00[] = {
    71, 10, 0x60080000,
};
s32 D_800A5F0C[] = {
    71, 10, 0x60080000,
};
s32 D_800A5F18[] = {
    1, (s32)D_800A5EB8, (s32)D_800A5EC4, (s32)D_800A5ED0,
    (s32)D_800A5EDC, (s32)D_800A5EE8, (s32)D_800A5EF4, (s32)D_800A5F00,
    (s32)D_800A5F0C,
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
    0, 0, 0x60040000,
};
s32 D_800A5F6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F9C[] = {
    0, (s32)D_800A5F3C, (s32)D_800A5F48, (s32)D_800A5F54,
    (s32)D_800A5F60, (s32)D_800A5F6C, (s32)D_800A5F78, (s32)D_800A5F84,
    (s32)D_800A5F90,
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
    0, 0, 0x60040000,
};
s32 D_800A5FF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6008[] = {
    0, 0, 0x60040000,
};
s32 D_800A6014[] = {
    0, 0, 0x60040000,
};
s32 D_800A6020[] = {
    0, (s32)D_800A5FC0, (s32)D_800A5FCC, (s32)D_800A5FD8,
    (s32)D_800A5FE4, (s32)D_800A5FF0, (s32)D_800A5FFC, (s32)D_800A6008,
    (s32)D_800A6014,
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
    0, 0, 0x60040000,
};
s32 D_800A6074[] = {
    0, 0, 0x60040000,
};
s32 D_800A6080[] = {
    0, 0, 0x60040000,
};
s32 D_800A608C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6098[] = {
    0, 0, 0x60040000,
};
s32 D_800A60A4[] = {
    0, (s32)D_800A6044, (s32)D_800A6050, (s32)D_800A605C,
    (s32)D_800A6068, (s32)D_800A6074, (s32)D_800A6080, (s32)D_800A608C,
    (s32)D_800A6098,
};
s32 D_800A60C8[] = {
    174, 10, 0x60080000,
};
s32 D_800A60D4[] = {
    174, 10, 0x60080000,
};
s32 D_800A60E0[] = {
    170, 10, 0x60080000,
};
s32 D_800A60EC[] = {
    170, 10, 0x60080000,
};
s32 D_800A60F8[] = {
    182, 10, 0x60080000,
};
s32 D_800A6104[] = {
    182, 10, 0x60080000,
};
s32 D_800A6110[] = {
    71, 10, 0x60080000,
};
s32 D_800A611C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6128[] = {
    1, (s32)D_800A60C8, (s32)D_800A60D4, (s32)D_800A60E0,
    (s32)D_800A60EC, (s32)D_800A60F8, (s32)D_800A6104, (s32)D_800A6110,
    (s32)D_800A611C,
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
    0, 0, 0x60040000,
};
s32 D_800A617C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6188[] = {
    0, 0, 0x60040000,
};
s32 D_800A6194[] = {
    0, 0, 0x60040000,
};
s32 D_800A61A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61AC[] = {
    0, (s32)D_800A614C, (s32)D_800A6158, (s32)D_800A6164,
    (s32)D_800A6170, (s32)D_800A617C, (s32)D_800A6188, (s32)D_800A6194,
    (s32)D_800A61A0,
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
    0, 0, 0x60040000,
};
s32 D_800A6200[] = {
    0, 0, 0x60040000,
};
s32 D_800A620C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6218[] = {
    0, 0, 0x60040000,
};
s32 D_800A6224[] = {
    0, 0, 0x60040000,
};
s32 D_800A6230[] = {
    0, (s32)D_800A61D0, (s32)D_800A61DC, (s32)D_800A61E8,
    (s32)D_800A61F4, (s32)D_800A6200, (s32)D_800A620C, (s32)D_800A6218,
    (s32)D_800A6224,
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
    0, 0, 0x60040000,
};
s32 D_800A6284[] = {
    0, 0, 0x60040000,
};
s32 D_800A6290[] = {
    0, 0, 0x60040000,
};
s32 D_800A629C[] = {
    0, 0, 0x60040000,
};
s32 D_800A62A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62B4[] = {
    0, (s32)D_800A6254, (s32)D_800A6260, (s32)D_800A626C,
    (s32)D_800A6278, (s32)D_800A6284, (s32)D_800A6290, (s32)D_800A629C,
    (s32)D_800A62A8,
};
s32 D_800A62D8[] = {
    174, 10, 0x60080000,
};
s32 D_800A62E4[] = {
    170, 10, 0x60080000,
};
s32 D_800A62F0[] = {
    110, 10, 0x60080000,
};
s32 D_800A62FC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6308[] = {
    182, 10, 0x60080000,
};
s32 D_800A6314[] = {
    182, 10, 0x60080000,
};
s32 D_800A6320[] = {
    71, 10, 0x60080000,
};
s32 D_800A632C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6338[] = {
    1, (s32)D_800A62D8, (s32)D_800A62E4, (s32)D_800A62F0,
    (s32)D_800A62FC, (s32)D_800A6308, (s32)D_800A6314, (s32)D_800A6320,
    (s32)D_800A632C,
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
    0, 0, 0x60040000,
};
s32 D_800A638C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6398[] = {
    0, 0, 0x60040000,
};
s32 D_800A63A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63BC[] = {
    0, (s32)D_800A635C, (s32)D_800A6368, (s32)D_800A6374,
    (s32)D_800A6380, (s32)D_800A638C, (s32)D_800A6398, (s32)D_800A63A4,
    (s32)D_800A63B0,
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
    0, 0, 0x60040000,
};
s32 D_800A6440[] = {
    0, (s32)D_800A63E0, (s32)D_800A63EC, (s32)D_800A63F8,
    (s32)D_800A6404, (s32)D_800A6410, (s32)D_800A641C, (s32)D_800A6428,
    (s32)D_800A6434,
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
    0, 0, 0x60040000,
};
s32 D_800A64C4[] = {
    0, (s32)D_800A6464, (s32)D_800A6470, (s32)D_800A647C,
    (s32)D_800A6488, (s32)D_800A6494, (s32)D_800A64A0, (s32)D_800A64AC,
    (s32)D_800A64B8,
};
s32 D_800A64E8[] = {
    174, 10, 0x60080000,
};
s32 D_800A64F4[] = {
    170, 10, 0x60080000,
};
s32 D_800A6500[] = {
    110, 10, 0x60080000,
};
s32 D_800A650C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6518[] = {
    182, 10, 0x60080000,
};
s32 D_800A6524[] = {
    182, 10, 0x60080000,
};
s32 D_800A6530[] = {
    71, 10, 0x60080000,
};
s32 D_800A653C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6548[] = {
    1, (s32)D_800A64E8, (s32)D_800A64F4, (s32)D_800A6500,
    (s32)D_800A650C, (s32)D_800A6518, (s32)D_800A6524, (s32)D_800A6530,
    (s32)D_800A653C,
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
    0, 0, 0x60040000,
};
s32 D_800A659C[] = {
    0, 0, 0x60040000,
};
s32 D_800A65A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65CC[] = {
    0, (s32)D_800A656C, (s32)D_800A6578, (s32)D_800A6584,
    (s32)D_800A6590, (s32)D_800A659C, (s32)D_800A65A8, (s32)D_800A65B4,
    (s32)D_800A65C0,
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
    0, 0, 0x60040000,
};
s32 D_800A6620[] = {
    0, 0, 0x60040000,
};
s32 D_800A662C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6638[] = {
    0, 0, 0x60040000,
};
s32 D_800A6644[] = {
    0, 0, 0x60040000,
};
s32 D_800A6650[] = {
    0, (s32)D_800A65F0, (s32)D_800A65FC, (s32)D_800A6608,
    (s32)D_800A6614, (s32)D_800A6620, (s32)D_800A662C, (s32)D_800A6638,
    (s32)D_800A6644,
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
    0, 0, 0x60040000,
};
s32 D_800A66A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A66B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66D4[] = {
    0, (s32)D_800A6674, (s32)D_800A6680, (s32)D_800A668C,
    (s32)D_800A6698, (s32)D_800A66A4, (s32)D_800A66B0, (s32)D_800A66BC,
    (s32)D_800A66C8,
};
s32 D_800A66F8[] = {
    182, 10, 0x60080000,
};
s32 D_800A6704[] = {
    182, 10, 0x60080000,
};
s32 D_800A6710[] = {
    182, 10, 0x60080000,
};
s32 D_800A671C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6728[] = {
    71, 10, 0x60080000,
};
s32 D_800A6734[] = {
    71, 10, 0x60080000,
};
s32 D_800A6740[] = {
    71, 10, 0x60080000,
};
s32 D_800A674C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6758[] = {
    1, (s32)D_800A66F8, (s32)D_800A6704, (s32)D_800A6710,
    (s32)D_800A671C, (s32)D_800A6728, (s32)D_800A6734, (s32)D_800A6740,
    (s32)D_800A674C,
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
    0, 0, 0x60040000,
};
s32 D_800A67AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67DC[] = {
    0, (s32)D_800A677C, (s32)D_800A6788, (s32)D_800A6794,
    (s32)D_800A67A0, (s32)D_800A67AC, (s32)D_800A67B8, (s32)D_800A67C4,
    (s32)D_800A67D0,
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
    0, 0, 0x60040000,
};
s32 D_800A6830[] = {
    0, 0, 0x60040000,
};
s32 D_800A683C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6848[] = {
    0, 0, 0x60040000,
};
s32 D_800A6854[] = {
    0, 0, 0x60040000,
};
s32 D_800A6860[] = {
    0, (s32)D_800A6800, (s32)D_800A680C, (s32)D_800A6818,
    (s32)D_800A6824, (s32)D_800A6830, (s32)D_800A683C, (s32)D_800A6848,
    (s32)D_800A6854,
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
    0, 0, 0x60040000,
};
s32 D_800A68B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68E4[] = {
    0, (s32)D_800A6884, (s32)D_800A6890, (s32)D_800A689C,
    (s32)D_800A68A8, (s32)D_800A68B4, (s32)D_800A68C0, (s32)D_800A68CC,
    (s32)D_800A68D8,
};
s32 D_800A6908[] = {
    182, 10, 0x60080000,
};
s32 D_800A6914[] = {
    182, 10, 0x60080000,
};
s32 D_800A6920[] = {
    182, 10, 0x60080000,
};
s32 D_800A692C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6938[] = {
    71, 10, 0x60080000,
};
s32 D_800A6944[] = {
    71, 10, 0x60080000,
};
s32 D_800A6950[] = {
    71, 10, 0x60080000,
};
s32 D_800A695C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6968[] = {
    1, (s32)D_800A6908, (s32)D_800A6914, (s32)D_800A6920,
    (s32)D_800A692C, (s32)D_800A6938, (s32)D_800A6944, (s32)D_800A6950,
    (s32)D_800A695C,
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
    0, 0, 0x60040000,
};
s32 D_800A69BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69EC[] = {
    0, (s32)D_800A698C, (s32)D_800A6998, (s32)D_800A69A4,
    (s32)D_800A69B0, (s32)D_800A69BC, (s32)D_800A69C8, (s32)D_800A69D4,
    (s32)D_800A69E0,
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
    0, 0, 0x60040000,
};
s32 D_800A6A40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A70[] = {
    0, (s32)D_800A6A10, (s32)D_800A6A1C, (s32)D_800A6A28,
    (s32)D_800A6A34, (s32)D_800A6A40, (s32)D_800A6A4C, (s32)D_800A6A58,
    (s32)D_800A6A64,
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
    0, 0, 0x60040000,
};
s32 D_800A6AC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ADC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AF4[] = {
    0, (s32)D_800A6A94, (s32)D_800A6AA0, (s32)D_800A6AAC,
    (s32)D_800A6AB8, (s32)D_800A6AC4, (s32)D_800A6AD0, (s32)D_800A6ADC,
    (s32)D_800A6AE8,
};
s32 D_800A6B18[] = {
    174, 10, 0x60080000,
};
s32 D_800A6B24[] = {
    174, 10, 0x60080000,
};
s32 D_800A6B30[] = {
    170, 10, 0x60080000,
};
s32 D_800A6B3C[] = {
    170, 10, 0x60080000,
};
s32 D_800A6B48[] = {
    170, 10, 0x60080000,
};
s32 D_800A6B54[] = {
    110, 10, 0x60080000,
};
s32 D_800A6B60[] = {
    110, 10, 0x60080000,
};
s32 D_800A6B6C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6B78[] = {
    2, (s32)D_800A6B18, (s32)D_800A6B24, (s32)D_800A6B30,
    (s32)D_800A6B3C, (s32)D_800A6B48, (s32)D_800A6B54, (s32)D_800A6B60,
    (s32)D_800A6B6C,
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
    0, 0, 0x60040000,
};
s32 D_800A6BCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BFC[] = {
    0, (s32)D_800A6B9C, (s32)D_800A6BA8, (s32)D_800A6BB4,
    (s32)D_800A6BC0, (s32)D_800A6BCC, (s32)D_800A6BD8, (s32)D_800A6BE4,
    (s32)D_800A6BF0,
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
    0, 0, 0x60040000,
};
s32 D_800A6C50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C80[] = {
    0, (s32)D_800A6C20, (s32)D_800A6C2C, (s32)D_800A6C38,
    (s32)D_800A6C44, (s32)D_800A6C50, (s32)D_800A6C5C, (s32)D_800A6C68,
    (s32)D_800A6C74,
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
    0, 0, 0x60040000,
};
s32 D_800A6CD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D04[] = {
    0, (s32)D_800A6CA4, (s32)D_800A6CB0, (s32)D_800A6CBC,
    (s32)D_800A6CC8, (s32)D_800A6CD4, (s32)D_800A6CE0, (s32)D_800A6CEC,
    (s32)D_800A6CF8,
};
s32 D_800A6D28[] = {
    182, 10, 0x60080000,
};
s32 D_800A6D34[] = {
    182, 10, 0x60080000,
};
s32 D_800A6D40[] = {
    182, 10, 0x60080000,
};
s32 D_800A6D4C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6D58[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D64[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D70[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D7C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D88[] = {
    2, (s32)D_800A6D28, (s32)D_800A6D34, (s32)D_800A6D40,
    (s32)D_800A6D4C, (s32)D_800A6D58, (s32)D_800A6D64, (s32)D_800A6D70,
    (s32)D_800A6D7C,
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
    0, 0, 0x60040000,
};
s32 D_800A6DDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E0C[] = {
    0, (s32)D_800A6DAC, (s32)D_800A6DB8, (s32)D_800A6DC4,
    (s32)D_800A6DD0, (s32)D_800A6DDC, (s32)D_800A6DE8, (s32)D_800A6DF4,
    (s32)D_800A6E00,
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
    0, 0, 0x60040000,
};
s32 D_800A6E60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E90[] = {
    0, (s32)D_800A6E30, (s32)D_800A6E3C, (s32)D_800A6E48,
    (s32)D_800A6E54, (s32)D_800A6E60, (s32)D_800A6E6C, (s32)D_800A6E78,
    (s32)D_800A6E84,
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
    0, 0, 0x60040000,
};
s32 D_800A6EFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F14[] = {
    0, (s32)D_800A6EB4, (s32)D_800A6EC0, (s32)D_800A6ECC,
    (s32)D_800A6ED8, (s32)D_800A6EE4, (s32)D_800A6EF0, (s32)D_800A6EFC,
    (s32)D_800A6F08,
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
    110, 10, 0x60080000,
};
s32 D_800A6F68[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F74[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F80[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F8C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F98[] = {
    1, (s32)D_800A6F38, (s32)D_800A6F44, (s32)D_800A6F50,
    (s32)D_800A6F5C, (s32)D_800A6F68, (s32)D_800A6F74, (s32)D_800A6F80,
    (s32)D_800A6F8C,
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
    0, 0, 0x60040000,
};
s32 D_800A6FEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7004[] = {
    0, 0, 0x60040000,
};
s32 D_800A7010[] = {
    0, 0, 0x60040000,
};
s32 D_800A701C[] = {
    0, (s32)D_800A6FBC, (s32)D_800A6FC8, (s32)D_800A6FD4,
    (s32)D_800A6FE0, (s32)D_800A6FEC, (s32)D_800A6FF8, (s32)D_800A7004,
    (s32)D_800A7010,
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
    0, 0, 0x60040000,
};
s32 D_800A7070[] = {
    0, 0, 0x60040000,
};
s32 D_800A707C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7088[] = {
    0, 0, 0x60040000,
};
s32 D_800A7094[] = {
    0, 0, 0x60040000,
};
s32 D_800A70A0[] = {
    0, (s32)D_800A7040, (s32)D_800A704C, (s32)D_800A7058,
    (s32)D_800A7064, (s32)D_800A7070, (s32)D_800A707C, (s32)D_800A7088,
    (s32)D_800A7094,
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
    0, 0, 0x60040000,
};
s32 D_800A710C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7118[] = {
    0, 0, 0x60040000,
};
s32 D_800A7124[] = {
    0, (s32)D_800A70C4, (s32)D_800A70D0, (s32)D_800A70DC,
    (s32)D_800A70E8, (s32)D_800A70F4, (s32)D_800A7100, (s32)D_800A710C,
    (s32)D_800A7118,
};
s32 D_800A7148[] = {
    182, 10, 0x60080000,
};
s32 D_800A7154[] = {
    182, 10, 0x60080000,
};
s32 D_800A7160[] = {
    182, 10, 0x60080000,
};
s32 D_800A716C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7178[] = {
    71, 10, 0x60080000,
};
s32 D_800A7184[] = {
    71, 10, 0x60080000,
};
s32 D_800A7190[] = {
    71, 10, 0x60080000,
};
s32 D_800A719C[] = {
    71, 10, 0x60080000,
};
s32 D_800A71A8[] = {
    1, (s32)D_800A7148, (s32)D_800A7154, (s32)D_800A7160,
    (s32)D_800A716C, (s32)D_800A7178, (s32)D_800A7184, (s32)D_800A7190,
    (s32)D_800A719C,
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
    0, 0, 0x60040000,
};
s32 D_800A7214[] = {
    0, 0, 0x60040000,
};
s32 D_800A7220[] = {
    0, 0, 0x60040000,
};
s32 D_800A722C[] = {
    0, (s32)D_800A71CC, (s32)D_800A71D8, (s32)D_800A71E4,
    (s32)D_800A71F0, (s32)D_800A71FC, (s32)D_800A7208, (s32)D_800A7214,
    (s32)D_800A7220,
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
    0, 0, 0x60040000,
};
s32 D_800A7280[] = {
    0, 0, 0x60040000,
};
s32 D_800A728C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7298[] = {
    0, 0, 0x60040000,
};
s32 D_800A72A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A72B0[] = {
    0, (s32)D_800A7250, (s32)D_800A725C, (s32)D_800A7268,
    (s32)D_800A7274, (s32)D_800A7280, (s32)D_800A728C, (s32)D_800A7298,
    (s32)D_800A72A4,
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
    0, 0, 0x60040000,
};
s32 D_800A731C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7328[] = {
    0, 0, 0x60040000,
};
s32 D_800A7334[] = {
    0, (s32)D_800A72D4, (s32)D_800A72E0, (s32)D_800A72EC,
    (s32)D_800A72F8, (s32)D_800A7304, (s32)D_800A7310, (s32)D_800A731C,
    (s32)D_800A7328,
};
s32 D_800A7358[] = {
    174, 10, 0x60080000,
};
s32 D_800A7364[] = {
    174, 10, 0x60080000,
};
s32 D_800A7370[] = {
    170, 10, 0x60080000,
};
s32 D_800A737C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7388[] = {
    170, 10, 0x60080000,
};
s32 D_800A7394[] = {
    170, 10, 0x60080000,
};
s32 D_800A73A0[] = {
    170, 10, 0x60080000,
};
s32 D_800A73AC[] = {
    170, 10, 0x60080000,
};
s32 D_800A73B8[] = {
    4, (s32)D_800A7358, (s32)D_800A7364, (s32)D_800A7370,
    (s32)D_800A737C, (s32)D_800A7388, (s32)D_800A7394, (s32)D_800A73A0,
    (s32)D_800A73AC,
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
    0, 0, 0x60040000,
};
s32 D_800A7424[] = {
    0, 0, 0x60040000,
};
s32 D_800A7430[] = {
    0, 0, 0x60040000,
};
s32 D_800A743C[] = {
    0, (s32)D_800A73DC, (s32)D_800A73E8, (s32)D_800A73F4,
    (s32)D_800A7400, (s32)D_800A740C, (s32)D_800A7418, (s32)D_800A7424,
    (s32)D_800A7430,
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
    0, 0, 0x60040000,
};
s32 D_800A7490[] = {
    0, 0, 0x60040000,
};
s32 D_800A749C[] = {
    0, 0, 0x60040000,
};
s32 D_800A74A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A74C0[] = {
    0, (s32)D_800A7460, (s32)D_800A746C, (s32)D_800A7478,
    (s32)D_800A7484, (s32)D_800A7490, (s32)D_800A749C, (s32)D_800A74A8,
    (s32)D_800A74B4,
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
    0, 0, 0x60040000,
};
s32 D_800A752C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7538[] = {
    0, 0, 0x60040000,
};
s32 D_800A7544[] = {
    0, (s32)D_800A74E4, (s32)D_800A74F0, (s32)D_800A74FC,
    (s32)D_800A7508, (s32)D_800A7514, (s32)D_800A7520, (s32)D_800A752C,
    (s32)D_800A7538,
};
s32 D_800A7568[] = {
    174, 10, 0x60080000,
};
s32 D_800A7574[] = {
    174, 10, 0x60080000,
};
s32 D_800A7580[] = {
    170, 10, 0x60080000,
};
s32 D_800A758C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7598[] = {
    170, 10, 0x60080000,
};
s32 D_800A75A4[] = {
    170, 10, 0x60080000,
};
s32 D_800A75B0[] = {
    170, 10, 0x60080000,
};
s32 D_800A75BC[] = {
    170, 10, 0x60080000,
};
s32 D_800A75C8[] = {
    4, (s32)D_800A7568, (s32)D_800A7574, (s32)D_800A7580,
    (s32)D_800A758C, (s32)D_800A7598, (s32)D_800A75A4, (s32)D_800A75B0,
    (s32)D_800A75BC,
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
    0, 0, 0x60040000,
};
s32 D_800A7634[] = {
    0, 0, 0x60040000,
};
s32 D_800A7640[] = {
    0, 0, 0x60040000,
};
s32 D_800A764C[] = {
    0, (s32)D_800A75EC, (s32)D_800A75F8, (s32)D_800A7604,
    (s32)D_800A7610, (s32)D_800A761C, (s32)D_800A7628, (s32)D_800A7634,
    (s32)D_800A7640,
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
    0, 0, 0x60040000,
};
s32 D_800A76A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A76AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A76B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A76C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A76D0[] = {
    0, (s32)D_800A7670, (s32)D_800A767C, (s32)D_800A7688,
    (s32)D_800A7694, (s32)D_800A76A0, (s32)D_800A76AC, (s32)D_800A76B8,
    (s32)D_800A76C4,
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
    0, 0, 0x60040000,
};
s32 D_800A773C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7748[] = {
    0, 0, 0x60040000,
};
s32 D_800A7754[] = {
    0, (s32)D_800A76F4, (s32)D_800A7700, (s32)D_800A770C,
    (s32)D_800A7718, (s32)D_800A7724, (s32)D_800A7730, (s32)D_800A773C,
    (s32)D_800A7748,
};
s32 D_800A7778[] = {
    110, 10, 0x60080000,
};
s32 D_800A7784[] = {
    110, 10, 0x60080000,
};
s32 D_800A7790[] = {
    110, 10, 0x60080000,
};
s32 D_800A779C[] = {
    110, 10, 0x60080000,
};
s32 D_800A77A8[] = {
    110, 10, 0x60080000,
};
s32 D_800A77B4[] = {
    110, 10, 0x60080000,
};
s32 D_800A77C0[] = {
    110, 10, 0x60080000,
};
s32 D_800A77CC[] = {
    110, 10, 0x60080000,
};
s32 D_800A77D8[] = {
    1, (s32)D_800A7778, (s32)D_800A7784, (s32)D_800A7790,
    (s32)D_800A779C, (s32)D_800A77A8, (s32)D_800A77B4, (s32)D_800A77C0,
    (s32)D_800A77CC,
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
    0, 0, 0x60040000,
};
s32 D_800A7844[] = {
    0, 0, 0x60040000,
};
s32 D_800A7850[] = {
    0, 0, 0x60040000,
};
s32 D_800A785C[] = {
    0, (s32)D_800A77FC, (s32)D_800A7808, (s32)D_800A7814,
    (s32)D_800A7820, (s32)D_800A782C, (s32)D_800A7838, (s32)D_800A7844,
    (s32)D_800A7850,
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
    0, 0, 0x60040000,
};
s32 D_800A78B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A78BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A78C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A78D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A78E0[] = {
    0, (s32)D_800A7880, (s32)D_800A788C, (s32)D_800A7898,
    (s32)D_800A78A4, (s32)D_800A78B0, (s32)D_800A78BC, (s32)D_800A78C8,
    (s32)D_800A78D4,
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
    0, 0, 0x60040000,
};
s32 D_800A794C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7958[] = {
    0, 0, 0x60040000,
};
s32 D_800A7964[] = {
    0, (s32)D_800A7904, (s32)D_800A7910, (s32)D_800A791C,
    (s32)D_800A7928, (s32)D_800A7934, (s32)D_800A7940, (s32)D_800A794C,
    (s32)D_800A7958,
};
s32 D_800A7988[] = {
    182, 10, 0x60080000,
};
s32 D_800A7994[] = {
    182, 10, 0x60080000,
};
s32 D_800A79A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A79AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A79B8[] = {
    71, 10, 0x60080000,
};
s32 D_800A79C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A79D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A79DC[] = {
    71, 10, 0x60080000,
};
s32 D_800A79E8[] = {
    1, (s32)D_800A7988, (s32)D_800A7994, (s32)D_800A79A0,
    (s32)D_800A79AC, (s32)D_800A79B8, (s32)D_800A79C4, (s32)D_800A79D0,
    (s32)D_800A79DC,
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
    0, 0, 0x60040000,
};
s32 D_800A7A54[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A60[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A6C[] = {
    0, (s32)D_800A7A0C, (s32)D_800A7A18, (s32)D_800A7A24,
    (s32)D_800A7A30, (s32)D_800A7A3C, (s32)D_800A7A48, (s32)D_800A7A54,
    (s32)D_800A7A60,
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
    0, 0, 0x60040000,
};
s32 D_800A7AC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7ACC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AF0[] = {
    0, (s32)D_800A7A90, (s32)D_800A7A9C, (s32)D_800A7AA8,
    (s32)D_800A7AB4, (s32)D_800A7AC0, (s32)D_800A7ACC, (s32)D_800A7AD8,
    (s32)D_800A7AE4,
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
    0, 0, 0x60040000,
};
s32 D_800A7B44[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B50[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B68[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B74[] = {
    0, (s32)D_800A7B14, (s32)D_800A7B20, (s32)D_800A7B2C,
    (s32)D_800A7B38, (s32)D_800A7B44, (s32)D_800A7B50, (s32)D_800A7B5C,
    (s32)D_800A7B68,
};
s32 D_800A7B98[] = {
    182, 10, 0x60080000,
};
s32 D_800A7BA4[] = {
    182, 10, 0x60080000,
};
s32 D_800A7BB0[] = {
    182, 10, 0x60080000,
};
s32 D_800A7BBC[] = {
    182, 10, 0x60080000,
};
s32 D_800A7BC8[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BD4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BE0[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BEC[] = {
    71, 10, 0x60080000,
};
s32 D_800A7BF8[] = {
    4, (s32)D_800A7B98, (s32)D_800A7BA4, (s32)D_800A7BB0,
    (s32)D_800A7BBC, (s32)D_800A7BC8, (s32)D_800A7BD4, (s32)D_800A7BE0,
    (s32)D_800A7BEC,
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
    0, 0, 0x60040000,
};
s32 D_800A7C4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C58[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C64[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C7C[] = {
    0, (s32)D_800A7C1C, (s32)D_800A7C28, (s32)D_800A7C34,
    (s32)D_800A7C40, (s32)D_800A7C4C, (s32)D_800A7C58, (s32)D_800A7C64,
    (s32)D_800A7C70,
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
    0, 0, 0x60040000,
};
s32 D_800A7CD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D00[] = {
    0, (s32)D_800A7CA0, (s32)D_800A7CAC, (s32)D_800A7CB8,
    (s32)D_800A7CC4, (s32)D_800A7CD0, (s32)D_800A7CDC, (s32)D_800A7CE8,
    (s32)D_800A7CF4,
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
    0, 0, 0x60040000,
};
s32 D_800A7D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D60[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D78[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D84[] = {
    0, (s32)D_800A7D24, (s32)D_800A7D30, (s32)D_800A7D3C,
    (s32)D_800A7D48, (s32)D_800A7D54, (s32)D_800A7D60, (s32)D_800A7D6C,
    (s32)D_800A7D78,
};
s32 D_800A7DA8[] = {
    174, 10, 0x60080000,
};
s32 D_800A7DB4[] = {
    174, 10, 0x60080000,
};
s32 D_800A7DC0[] = {
    170, 10, 0x60080000,
};
s32 D_800A7DCC[] = {
    170, 10, 0x60080000,
};
s32 D_800A7DD8[] = {
    170, 10, 0x60080000,
};
s32 D_800A7DE4[] = {
    170, 10, 0x60080000,
};
s32 D_800A7DF0[] = {
    170, 10, 0x60080000,
};
s32 D_800A7DFC[] = {
    170, 10, 0x60080000,
};
s32 D_800A7E08[] = {
    2, (s32)D_800A7DA8, (s32)D_800A7DB4, (s32)D_800A7DC0,
    (s32)D_800A7DCC, (s32)D_800A7DD8, (s32)D_800A7DE4, (s32)D_800A7DF0,
    (s32)D_800A7DFC,
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
    0, 0, 0x60040000,
};
s32 D_800A7E5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E68[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E74[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E80[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E8C[] = {
    0, (s32)D_800A7E2C, (s32)D_800A7E38, (s32)D_800A7E44,
    (s32)D_800A7E50, (s32)D_800A7E5C, (s32)D_800A7E68, (s32)D_800A7E74,
    (s32)D_800A7E80,
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
    0, 0, 0x60040000,
};
s32 D_800A7EE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F10[] = {
    0, (s32)D_800A7EB0, (s32)D_800A7EBC, (s32)D_800A7EC8,
    (s32)D_800A7ED4, (s32)D_800A7EE0, (s32)D_800A7EEC, (s32)D_800A7EF8,
    (s32)D_800A7F04,
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
    0, 0, 0x60040000,
};
s32 D_800A7F64[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F88[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F94[] = {
    0, (s32)D_800A7F34, (s32)D_800A7F40, (s32)D_800A7F4C,
    (s32)D_800A7F58, (s32)D_800A7F64, (s32)D_800A7F70, (s32)D_800A7F7C,
    (s32)D_800A7F88,
};
s32 D_800A7FB8[] = {
    182, 10, 0x60080000,
};
s32 D_800A7FC4[] = {
    182, 10, 0x60080000,
};
s32 D_800A7FD0[] = {
    182, 10, 0x60080000,
};
s32 D_800A7FDC[] = {
    182, 10, 0x60080000,
};
s32 D_800A7FE8[] = {
    71, 10, 0x60080000,
};
s32 D_800A7FF4[] = {
    71, 10, 0x60080000,
};
s32 D_800A8000[] = {
    71, 10, 0x60080000,
};
s32 D_800A800C[] = {
    71, 10, 0x60080000,
};
s32 D_800A8018[] = {
    1, (s32)D_800A7FB8, (s32)D_800A7FC4, (s32)D_800A7FD0,
    (s32)D_800A7FDC, (s32)D_800A7FE8, (s32)D_800A7FF4, (s32)D_800A8000,
    (s32)D_800A800C,
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
    0, 0, 0x60040000,
};
s32 D_800A806C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8078[] = {
    0, 0, 0x60040000,
};
s32 D_800A8084[] = {
    0, 0, 0x60040000,
};
s32 D_800A8090[] = {
    0, 0, 0x60040000,
};
s32 D_800A809C[] = {
    0, (s32)D_800A803C, (s32)D_800A8048, (s32)D_800A8054,
    (s32)D_800A8060, (s32)D_800A806C, (s32)D_800A8078, (s32)D_800A8084,
    (s32)D_800A8090,
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
    0, 0, 0x60040000,
};
s32 D_800A80F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A80FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8108[] = {
    0, 0, 0x60040000,
};
s32 D_800A8114[] = {
    0, 0, 0x60040000,
};
s32 D_800A8120[] = {
    0, (s32)D_800A80C0, (s32)D_800A80CC, (s32)D_800A80D8,
    (s32)D_800A80E4, (s32)D_800A80F0, (s32)D_800A80FC, (s32)D_800A8108,
    (s32)D_800A8114,
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
    0, 0, 0x60040000,
};
s32 D_800A8174[] = {
    0, 0, 0x60040000,
};
s32 D_800A8180[] = {
    0, 0, 0x60040000,
};
s32 D_800A818C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8198[] = {
    0, 0, 0x60040000,
};
s32 D_800A81A4[] = {
    0, (s32)D_800A8144, (s32)D_800A8150, (s32)D_800A815C,
    (s32)D_800A8168, (s32)D_800A8174, (s32)D_800A8180, (s32)D_800A818C,
    (s32)D_800A8198,
};
s32 D_800A81C8[] = {
    182, 10, 0x60080000,
};
s32 D_800A81D4[] = {
    182, 10, 0x60080000,
};
s32 D_800A81E0[] = {
    182, 10, 0x60080000,
};
s32 D_800A81EC[] = {
    182, 10, 0x60080000,
};
s32 D_800A81F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A8204[] = {
    71, 10, 0x60080000,
};
s32 D_800A8210[] = {
    71, 10, 0x60080000,
};
s32 D_800A821C[] = {
    71, 10, 0x60080000,
};
s32 D_800A8228[] = {
    1, (s32)D_800A81C8, (s32)D_800A81D4, (s32)D_800A81E0,
    (s32)D_800A81EC, (s32)D_800A81F8, (s32)D_800A8204, (s32)D_800A8210,
    (s32)D_800A821C,
};
s32 D_800A824C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8258[] = {
    0, 0, 0x60040000,
};
s32 D_800A8264[] = {
    0, 0, 0x60040000,
};
s32 D_800A8270[] = {
    0, 0, 0x60040000,
};
s32 D_800A827C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8288[] = {
    0, 0, 0x60040000,
};
s32 D_800A8294[] = {
    0, 0, 0x60040000,
};
s32 D_800A82A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A82AC[] = {
    0, (s32)D_800A824C, (s32)D_800A8258, (s32)D_800A8264,
    (s32)D_800A8270, (s32)D_800A827C, (s32)D_800A8288, (s32)D_800A8294,
    (s32)D_800A82A0,
};
s32 D_800A82D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A82DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A82E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A82F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8300[] = {
    0, 0, 0x60040000,
};
s32 D_800A830C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8318[] = {
    0, 0, 0x60040000,
};
s32 D_800A8324[] = {
    0, 0, 0x60040000,
};
s32 D_800A8330[] = {
    0, (s32)D_800A82D0, (s32)D_800A82DC, (s32)D_800A82E8,
    (s32)D_800A82F4, (s32)D_800A8300, (s32)D_800A830C, (s32)D_800A8318,
    (s32)D_800A8324,
};
s32 D_800A8354[] = {
    0, 0, 0x60040000,
};
s32 D_800A8360[] = {
    0, 0, 0x60040000,
};
s32 D_800A836C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8378[] = {
    0, 0, 0x60040000,
};
s32 D_800A8384[] = {
    0, 0, 0x60040000,
};
s32 D_800A8390[] = {
    0, 0, 0x60040000,
};
s32 D_800A839C[] = {
    0, 0, 0x60040000,
};
s32 D_800A83A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A83B4[] = {
    0, (s32)D_800A8354, (s32)D_800A8360, (s32)D_800A836C,
    (s32)D_800A8378, (s32)D_800A8384, (s32)D_800A8390, (s32)D_800A839C,
    (s32)D_800A83A8,
};
s32 D_800A83D8[] = {
    174, 10, 0x60080000,
};
s32 D_800A83E4[] = {
    174, 10, 0x60080000,
};
s32 D_800A83F0[] = {
    170, 10, 0x60080000,
};
s32 D_800A83FC[] = {
    170, 10, 0x60080000,
};
s32 D_800A8408[] = {
    182, 10, 0x60080000,
};
s32 D_800A8414[] = {
    182, 10, 0x60080000,
};
s32 D_800A8420[] = {
    71, 10, 0x60080000,
};
s32 D_800A842C[] = {
    71, 10, 0x60080000,
};
s32 D_800A8438[] = {
    1, (s32)D_800A83D8, (s32)D_800A83E4, (s32)D_800A83F0,
    (s32)D_800A83FC, (s32)D_800A8408, (s32)D_800A8414, (s32)D_800A8420,
    (s32)D_800A842C,
};
s32 D_800A845C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8468[] = {
    0, 0, 0x60040000,
};
s32 D_800A8474[] = {
    0, 0, 0x60040000,
};
s32 D_800A8480[] = {
    0, 0, 0x60040000,
};
s32 D_800A848C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8498[] = {
    0, 0, 0x60040000,
};
s32 D_800A84A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A84B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A84BC[] = {
    0, (s32)D_800A845C, (s32)D_800A8468, (s32)D_800A8474,
    (s32)D_800A8480, (s32)D_800A848C, (s32)D_800A8498, (s32)D_800A84A4,
    (s32)D_800A84B0,
};
s32 D_800A84E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A84EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A84F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8504[] = {
    0, 0, 0x60040000,
};
s32 D_800A8510[] = {
    0, 0, 0x60040000,
};
s32 D_800A851C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8528[] = {
    0, 0, 0x60040000,
};
s32 D_800A8534[] = {
    0, 0, 0x60040000,
};
s32 D_800A8540[] = {
    0, (s32)D_800A84E0, (s32)D_800A84EC, (s32)D_800A84F8,
    (s32)D_800A8504, (s32)D_800A8510, (s32)D_800A851C, (s32)D_800A8528,
    (s32)D_800A8534,
};
s32 D_800A8564[] = {
    0, 0, 0x60040000,
};
s32 D_800A8570[] = {
    0, 0, 0x60040000,
};
s32 D_800A857C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8588[] = {
    0, 0, 0x60040000,
};
s32 D_800A8594[] = {
    0, 0, 0x60040000,
};
s32 D_800A85A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A85AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A85B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A85C4[] = {
    0, (s32)D_800A8564, (s32)D_800A8570, (s32)D_800A857C,
    (s32)D_800A8588, (s32)D_800A8594, (s32)D_800A85A0, (s32)D_800A85AC,
    (s32)D_800A85B8,
};
s32 D_800A85E8[] = {
    231, 1, 0, (s32)D_800A5AF8,
    (s32)D_800A5B7C, (s32)D_800A5C00, (s32)D_800A5C84, 238,
    2, 0, (s32)D_800A5D08, (s32)D_800A5D8C,
    (s32)D_800A5E10, (s32)D_800A5E94, 243, 3,
    0, (s32)D_800A5F18, (s32)D_800A5F9C, (s32)D_800A6020,
    (s32)D_800A60A4, 249, 4, 0,
    (s32)D_800A6128, (s32)D_800A61AC, (s32)D_800A6230, (s32)D_800A62B4,
    254, 5, 0, (s32)D_800A6338,
    (s32)D_800A63BC, (s32)D_800A6440, (s32)D_800A64C4, 261,
    6, 0, (s32)D_800A6548, (s32)D_800A65CC,
    (s32)D_800A6650, (s32)D_800A66D4, 270, 8,
    0, (s32)D_800A6758, (s32)D_800A67DC, (s32)D_800A6860,
    (s32)D_800A68E4, 276, 9, 0,
    (s32)D_800A6968, (s32)D_800A69EC, (s32)D_800A6A70, (s32)D_800A6AF4,
    281, 10, 0, (s32)D_800A6B78,
    (s32)D_800A6BFC, (s32)D_800A6C80, (s32)D_800A6D04, 286,
    11, 0, (s32)D_800A6D88, (s32)D_800A6E0C,
    (s32)D_800A6E90, (s32)D_800A6F14, 291, 12,
    0, (s32)D_800A6F98, (s32)D_800A701C, (s32)D_800A70A0,
    (s32)D_800A7124, 298, 13, 0,
    (s32)D_800A71A8, (s32)D_800A722C, (s32)D_800A72B0, (s32)D_800A7334,
    302, 14, 0, (s32)D_800A73B8,
    (s32)D_800A743C, (s32)D_800A74C0, (s32)D_800A7544, 310,
    16, 0, (s32)D_800A75C8, (s32)D_800A764C,
    (s32)D_800A76D0, (s32)D_800A7754, 321, 19,
    0, (s32)D_800A77D8, (s32)D_800A785C, (s32)D_800A78E0,
    (s32)D_800A7964, 327, 20, 0,
    (s32)D_800A79E8, (s32)D_800A7A6C, (s32)D_800A7AF0, (s32)D_800A7B74,
    348, 25, 0, (s32)D_800A7BF8,
    (s32)D_800A7C7C, (s32)D_800A7D00, (s32)D_800A7D84, 353,
    27, 0, (s32)D_800A7E08, (s32)D_800A7E8C,
    (s32)D_800A7F10, (s32)D_800A7F94, 359, 28,
    0, (s32)D_800A8018, (s32)D_800A809C, (s32)D_800A8120,
    (s32)D_800A81A4, 366, 29, 0,
    (s32)D_800A8228, (s32)D_800A82AC, (s32)D_800A8330, (s32)D_800A83B4,
    369, 30, 0, (s32)D_800A8438,
    (s32)D_800A84BC, (s32)D_800A8540, (s32)D_800A85C4,
};
s32 D_800A8834[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000174, 208, 0x1FF0140,
    0x1000140, 0x1400170, 0x4000C0, 0x1FF0150,
    0x1000140, 0x1400168, 0x4000A0, 0x1FF0160,
    0x1000140, 0x1400140, 0x400000, 0x1FF0170,
    0x1000140, 0x1400148, 0x400020, 0x1FE0140,
    0x1000140, 0x1400150, 0x400040, 0x1FE0150,
    0x1000140, 0x1400158, 0x400060, 0x1FE0160,
    0x1000140, 0x1400160, 0x400080, 0x1FE0170,
    0x1000140, 0x1200174, 0x2000D0, 0x1FD0140,
    0x1000140, 0x1000168, 160, 0x1FD0150,
    0x1000140, 0x1000140, 0, 0x1FD0160,
    0x1000140, 0x1000154, 80, 0x1FD0170,
};
s32 D_800A8954[] = {
    0, 0, 946, 0,
    0, 0,
};
s32 D_800A896C[] = {
    0, 0, 947, 0,
    0, 0,
};
s32 D_800A8984[] = {
    0, 0, 954, 0,
    0, 0,
};
s32 D_800A899C[] = {
    0, 0, 857, 0,
    0, 0,
};
s32 D_800A89B4[] = {
    0, 0, 950, 0,
    0, 0,
};
s32 D_800A89CC[] = {
    0, 0, 951, 0,
    0, 0,
};
s32 D_800A89E4[] = {
    0, 0, 953, 0,
    0, 0,
};
s32 D_800A89FC[] = {
    0, 0, 853, 0,
    0, 0,
};
s32 D_800A8A14[] = {
    0, 0, 952, 0,
    0, 0,
};
s32 D_800A8A2C[] = {
    0, 0, 955, 0,
    0, 0,
};
s32 D_800A8A44[] = {
    0, 0, 860, 0,
    0, 0,
};
s32 D_800A8A5C[] = {
    0, 0, 858, 0,
    0, 0,
};
s32 D_800A8A74[] = {
    0, 0, 948, 0,
    0, 0,
};
s32 D_800A8A8C[] = {
    0, 0, 956, 0,
    0, 0,
};
s32 D_800A8AA4[] = {
    0, 0, 855, 0,
    0, 0,
};
s32 D_800A8ABC[] = {
    0, 0, 854, 0,
    0, 0,
};
s32 D_800A8AD4[] = {
    0, 0, 861, 0,
    0, 0,
};
s32 D_800A8AEC[] = {
    0, 0, 856, 0,
    0, 0,
};
s32 D_800A8B04[] = {
    0, 0, 859, 0,
    0, 0,
};
s32 D_800A8B1C[] = {
    0x17E00, 0x17E1F, 65535,
};
s32 D_800A8B28[] = {
    0x17E03, 0x17E1E, 65535,
};
s32 D_800A8B34[] = {
    0x17E21, 0x17E13, 65535,
};
s32 D_800A8B40[] = {
    0x17E04, 0x17E1F, 65535,
};
s32 D_800A8B4C[] = {
    0x17E0B, 0x17E1E, 65535,
};
s32 D_800A8B58[] = {
    0x17E0C, 0x17E1E, 65535,
};
s32 D_800A8B64[] = {
    0x17E12, 0x17E20, 65535,
};
s32 D_800A8B70[] = {
    0x17E02, 0x17E1E, 65535,
};
s32 D_800A8B7C[] = {
    0x17E0D, 0x17E1F, 65535,
};
s32 D_800A8B88[] = {
    0x17E13, 0x17E22, 65535,
};
s32 D_800A8B94[] = {
    0x17E01, 0x17E1F, 65535,
};
s32 D_800A8BA0[] = {
    0x17E02, 0x17E21, 65535,
};
s32 D_800A8BAC[] = {
    0x17E07, 0x17E1F, 65535,
};
s32 D_800A8BB8[] = {
    0x17E1B, 0x17E1F, 65535,
};
s32 D_800A8BC4[] = {
    0x17E04, 0x17E20, 65535,
};
s32 D_800A8BD0[] = {
    0x17E08, 0x17E1F, 65535,
};
s32 D_800A8BDC[] = {
    0x17E13, 0x17E1E, 65535,
};
s32 D_800A8BE8[] = {
    0x17E04, 0x17E21, 65535,
};
s32 D_800A8BF4[] = {
    0x17E05, 0x17E1E, 65535,
};
s32 D_800A8C00[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A8C0C[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A8C18[] = {
    0x17E20, 9, 65535,
};
s32 D_800A8C24[] = {
    0x17E0B, 10, 65535,
};
s32 D_800A8C30[] = {
    0x17E12, 10, 65535,
};
s32 D_800A8C3C[] = {
    0x17E13, 10, 65535,
};
s32 D_800A8C48[] = {
    0x17E1A, 10, 65535,
};
s32 D_800A8C54[] = {
    0x17E1B, 10, 65535,
};
s32 D_800A8C60[] = {
    0x17E00, 10, 65535,
};
s32 D_800A8C6C[] = {
    0x17E02, 10, 65535,
};
s32 D_800A8C78[] = {
    0x17E03, 10, 65535,
};
s32 D_800A8C84[] = {
    0x17E04, 10, 65535,
};
s32 D_800A8C90[] = {
    0x17E07, 10, 65535,
};
s32 D_800A8C9C[] = {
    (s32)D_800A8B1C, (s32)D_800A8954, 0x40023, 0x1C003D8,
    1,
};
s32 D_800A8CB0[] = {
    (s32)D_800A8B28, (s32)D_800A896C, 0x40023, 0x1C003D8,
    1,
};
s32 D_800A8CC4[] = {
    (s32)D_800A8B34, (s32)D_800A8984, 0x40023, 0xD802A0,
    7,
};
s32 D_800A8CD8[] = {
    (s32)D_800A8B40, (s32)D_800A899C, 0x40023, 0xD802A0,
    7,
};
s32 D_800A8CEC[] = {
    (s32)D_800A8B4C, (s32)D_800A89B4, 0x50040, 0xD802A0,
    7,
};
s32 D_800A8D00[] = {
    (s32)D_800A8B58, (s32)D_800A89CC, 0x50040, 0x640180,
    1,
};
s32 D_800A8D14[] = {
    (s32)D_800A8B64, (s32)D_800A89E4, 0x50040, 0xD802A0,
    7,
};
s32 D_800A8D28[] = {
    (s32)D_800A8B70, (s32)D_800A89FC, 0x50040, 0xD802A0,
    7,
};
s32 D_800A8D3C[] = {
    (s32)D_800A8B7C, (s32)D_800A8A14, 0x60041, 0xD802A0,
    7,
};
s32 D_800A8D50[] = {
    (s32)D_800A8B88, (s32)D_800A8A2C, 0x60041, 0xD802A0,
    7,
};
s32 D_800A8D64[] = {
    (s32)D_800A8B94, (s32)D_800A8A44, 0x60041, 0xD802A0,
    7,
};
s32 D_800A8D78[] = {
    (s32)D_800A8BA0, (s32)D_800A8A5C, 0x700B4, 0xD802A0,
    7,
};
s32 D_800A8D8C[] = {
    (s32)D_800A8BAC, (s32)D_800A8A74, 0x800B5, 0x1C003D8,
    1,
};
s32 D_800A8DA0[] = {
    (s32)D_800A8BB8, (s32)D_800A8A8C, 0x800B5, 0x640180,
    1,
};
s32 D_800A8DB4[] = {
    (s32)D_800A8BC4, (s32)D_800A8AA4, 0x800B5, 0xD802A0,
    7,
};
s32 D_800A8DC8[] = {
    (s32)D_800A8BD0, (s32)D_800A8ABC, 0x900E7, 0xD802A0,
    7,
};
s32 D_800A8DDC[] = {
    (s32)D_800A8BDC, (s32)D_800A8AD4, 0xA00EB, 0xD802A0,
    7,
};
s32 D_800A8DF0[] = {
    (s32)D_800A8BE8, (s32)D_800A8AEC, 0xB00EF, 0xD802A0,
    7,
};
s32 D_800A8E04[] = {
    (s32)D_800A8BF4, (s32)D_800A8B04, 0xC00F1, 0xD802A0,
    7,
};
s32 D_800A8E18[] = {
    0, 0, 0xD0146, 0,
    0,
};
s32 D_800A8E2C[] = {
    (s32)D_800A8C00, 0, 0xE015F, 0x1600300,
    1,
};
s32 D_800A8E40[] = {
    (s32)D_800A8C0C, 0, 0xE015F, 0x15401C8,
    1,
};
s32 D_800A8E54[] = {
    (s32)D_800A8C18, 0, 0xE015F, 0x18001C0,
    1,
};
s32 D_800A8E68[] = {
    (s32)D_800A8C24, 0, 0xF0160, 0xA80110,
    1,
};
s32 D_800A8E7C[] = {
    (s32)D_800A8C30, 0, 0xF0160, 0x980370,
    1,
};
s32 D_800A8E90[] = {
    (s32)D_800A8C3C, 0, 0xF0160, 0x10001E0,
    1,
};
s32 D_800A8EA4[] = {
    (s32)D_800A8C48, 0, 0xF0160, 0x1A00280,
    1,
};
s32 D_800A8EB8[] = {
    (s32)D_800A8C54, 0, 0xF0160, 0xC80310,
    1,
};
s32 D_800A8ECC[] = {
    (s32)D_800A8C60, 0, 0xF0160, 0xC80310,
    1,
};
s32 D_800A8EE0[] = {
    (s32)D_800A8C6C, 0, 0xF0160, 0xA401E8,
    1,
};
s32 D_800A8EF4[] = {
    (s32)D_800A8C78, 0, 0xF0160, 0xC80310,
    1,
};
s32 D_800A8F08[] = {
    (s32)D_800A8C84, 0, 0xF0160, 0x1980370,
    1,
};
s32 D_800A8F1C[] = {
    (s32)D_800A8C90, 0, 0xF0160, 0x10001E0,
    1,
};
s32 D_800A8F30[] = {
    (s32)D_800A8C9C, (s32)D_800A8CB0, (s32)D_800A8CC4, (s32)D_800A8CD8,
    (s32)D_800A8CEC, (s32)D_800A8D00, (s32)D_800A8D14, (s32)D_800A8D28,
    (s32)D_800A8D3C, (s32)D_800A8D50, (s32)D_800A8D64, (s32)D_800A8D78,
    (s32)D_800A8D8C, (s32)D_800A8DA0, (s32)D_800A8DB4, (s32)D_800A8DC8,
    (s32)D_800A8DDC, (s32)D_800A8DF0, (s32)D_800A8E04, (s32)D_800A8E18,
    (s32)D_800A8E2C, (s32)D_800A8E40, (s32)D_800A8E54, (s32)D_800A8E68,
    (s32)D_800A8E7C, (s32)D_800A8E90, (s32)D_800A8EA4, (s32)D_800A8EB8,
    (s32)D_800A8ECC, (s32)D_800A8EE0, (s32)D_800A8EF4, (s32)D_800A8F08,
    (s32)D_800A8F1C, 0,
};
s32 D_800A8FB8[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A8FCC[] = {
    65535, 65535, 0x2ED0001, 0x8003A0,
    5, 0, 65535, 65535,
    0x2ED0001, 0x1F80350, 1, 0,
    65535, 65535, 0x2ED0001, 0xC000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A902C[])(void) = {
    func_800A4E74,
};
