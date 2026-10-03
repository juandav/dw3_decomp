#include "common.h"
#include "stage.h"
extern void (*D_800A97C0[])(void);
void func_800A4DA4();
extern StagePoints *D_800A5670[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A5670, GAME.unk44, GAME.unk46);
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
    D_800A97C0[0]();
    return task;
}

extern s32 D_800A9754[];
extern s32 D_800A9778[];
extern s32 D_800A93F4[];
extern s32 D_800A9710[];
extern s32 D_800A90E4[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x6A0
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x6B0
#endif
void func_800A4E74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A9754;
    D_800990B4.unk14 = D_800A9778;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xF900, 0x14000};
    D_800990B4.unk28 = D_800A93F4;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A9710;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A90E4, GAME.unk44);
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4E74();
extern StagePoint D_800A4F90;
extern StagePoint D_800A4FA0;
extern StagePoint D_800A4FB8;
extern StagePoint D_800A4FC8;
extern StagePoint D_800A4FE0;
extern StagePoint D_800A4FF0;
extern StagePoint D_800A5008;
extern StagePoint D_800A5018;
extern StagePoint D_800A5030;
extern StagePoint D_800A5040;
extern StagePoint D_800A5058;
extern StagePoint D_800A5068;
extern StagePoint D_800A5080;
extern StagePoint D_800A5090;
extern StagePoint D_800A50A8;
extern StagePoint D_800A50B8;
extern StagePoint D_800A50D0;
extern StagePoint D_800A50E0;
extern StagePoint D_800A50F8;
extern StagePoint D_800A5108;
extern StagePoint D_800A5120;
extern StagePoint D_800A5130;
extern StagePoint D_800A5148;
extern StagePoint D_800A5158;
extern StagePoint D_800A5170;
extern StagePoint D_800A5180;
extern StagePoint D_800A5198;
extern StagePoint D_800A51A8;
extern StagePoint D_800A51C0;
extern StagePoint D_800A51D0;
extern StagePoint D_800A51E8;
extern StagePoint D_800A51F8;
extern StagePoint D_800A5210;
extern StagePoint D_800A5220;
extern StagePoint D_800A5238;
extern StagePoint D_800A5248;
extern StagePoint D_800A5260;
extern StagePoint D_800A5270;
extern StagePoint D_800A5288;
extern StagePoint D_800A5298;
extern StagePoint D_800A52B0;
extern StagePoint D_800A52C0;
extern StagePoint D_800A52D8;
extern StagePoint D_800A52E8;
extern StagePoint D_800A5300;
extern StagePoint D_800A5310;
extern StagePoint D_800A5328;
extern StagePoint D_800A5338;
extern StagePoint D_800A5350;
extern StagePoint D_800A5360;
extern StagePoint D_800A5378;
extern StagePoint D_800A5388;
extern StagePoint D_800A53A0;
extern StagePoint D_800A53B0;
extern StagePoint D_800A53C8;
extern StagePoint D_800A53D8;
extern StagePoint D_800A53F0;
extern StagePoint D_800A5400;
extern StagePoint D_800A5418;
extern StagePoint D_800A5428;
extern StagePoint D_800A5440;
extern StagePoint D_800A5450;
extern StagePoint D_800A5468;
extern StagePoint D_800A5478;
extern StagePoint D_800A5490;
extern StagePoint D_800A54A0;
extern StagePoint D_800A54B8;
extern StagePoint D_800A54C8;
extern StagePoint D_800A54E0;
extern StagePoint D_800A54F0;
extern StagePoint D_800A5508;
extern StagePoint D_800A5518;
extern StagePoint D_800A5530;
extern StagePoint D_800A5540;
extern StagePoint D_800A5558;
extern StagePoint D_800A5568;
extern StagePoint D_800A5580;
extern StagePoint D_800A5590;
extern StagePoint D_800A55A8;
extern StagePoint D_800A55B8;
extern StagePoint D_800A55D0;
extern StagePoint D_800A55E0;
extern StagePoint D_800A55F8;
extern StagePoint D_800A5608;
extern StagePoint D_800A5620;
extern StagePoint D_800A5630;
extern StagePoint D_800A5648;
extern StagePoint D_800A5658;
extern StagePoints D_800A4FB0;
extern StagePoints D_800A4FD8;
extern StagePoints D_800A5000;
extern StagePoints D_800A5028;
extern StagePoints D_800A5050;
extern StagePoints D_800A5078;
extern StagePoints D_800A50A0;
extern StagePoints D_800A50C8;
extern StagePoints D_800A50F0;
extern StagePoints D_800A5118;
extern StagePoints D_800A5140;
extern StagePoints D_800A5168;
extern StagePoints D_800A5190;
extern StagePoints D_800A51B8;
extern StagePoints D_800A51E0;
extern StagePoints D_800A5208;
extern StagePoints D_800A5230;
extern StagePoints D_800A5258;
extern StagePoints D_800A5280;
extern StagePoints D_800A52A8;
extern StagePoints D_800A52D0;
extern StagePoints D_800A52F8;
extern StagePoints D_800A5320;
extern StagePoints D_800A5348;
extern StagePoints D_800A5370;
extern StagePoints D_800A5398;
extern StagePoints D_800A53C0;
extern StagePoints D_800A53E8;
extern StagePoints D_800A5410;
extern StagePoints D_800A5438;
extern StagePoints D_800A5460;
extern StagePoints D_800A5488;
extern StagePoints D_800A54B0;
extern StagePoints D_800A54D8;
extern StagePoints D_800A5500;
extern StagePoints D_800A5528;
extern StagePoints D_800A5550;
extern StagePoints D_800A5578;
extern StagePoints D_800A55A0;
extern StagePoints D_800A55C8;
extern StagePoints D_800A55F0;
extern StagePoints D_800A5618;
extern StagePoints D_800A5640;
extern StagePoints D_800A5668;
extern s32 D_800A5724[];
extern s32 D_800A5730[];
extern s32 D_800A573C[];
extern s32 D_800A5748[];
extern s32 D_800A5754[];
extern s32 D_800A5760[];
extern s32 D_800A576C[];
extern s32 D_800A5778[];
extern s32 D_800A57A8[];
extern s32 D_800A57B4[];
extern s32 D_800A57C0[];
extern s32 D_800A57CC[];
extern s32 D_800A57D8[];
extern s32 D_800A57E4[];
extern s32 D_800A57F0[];
extern s32 D_800A57FC[];
extern s32 D_800A582C[];
extern s32 D_800A5838[];
extern s32 D_800A5844[];
extern s32 D_800A5850[];
extern s32 D_800A585C[];
extern s32 D_800A5868[];
extern s32 D_800A5874[];
extern s32 D_800A5880[];
extern s32 D_800A58B0[];
extern s32 D_800A58BC[];
extern s32 D_800A58C8[];
extern s32 D_800A58D4[];
extern s32 D_800A58E0[];
extern s32 D_800A58EC[];
extern s32 D_800A58F8[];
extern s32 D_800A5904[];
extern s32 D_800A5934[];
extern s32 D_800A5940[];
extern s32 D_800A594C[];
extern s32 D_800A5958[];
extern s32 D_800A5964[];
extern s32 D_800A5970[];
extern s32 D_800A597C[];
extern s32 D_800A5988[];
extern s32 D_800A59B8[];
extern s32 D_800A59C4[];
extern s32 D_800A59D0[];
extern s32 D_800A59DC[];
extern s32 D_800A59E8[];
extern s32 D_800A59F4[];
extern s32 D_800A5A00[];
extern s32 D_800A5A0C[];
extern s32 D_800A5A3C[];
extern s32 D_800A5A48[];
extern s32 D_800A5A54[];
extern s32 D_800A5A60[];
extern s32 D_800A5A6C[];
extern s32 D_800A5A78[];
extern s32 D_800A5A84[];
extern s32 D_800A5A90[];
extern s32 D_800A5AC0[];
extern s32 D_800A5ACC[];
extern s32 D_800A5AD8[];
extern s32 D_800A5AE4[];
extern s32 D_800A5AF0[];
extern s32 D_800A5AFC[];
extern s32 D_800A5B08[];
extern s32 D_800A5B14[];
extern s32 D_800A5B44[];
extern s32 D_800A5B50[];
extern s32 D_800A5B5C[];
extern s32 D_800A5B68[];
extern s32 D_800A5B74[];
extern s32 D_800A5B80[];
extern s32 D_800A5B8C[];
extern s32 D_800A5B98[];
extern s32 D_800A5BC8[];
extern s32 D_800A5BD4[];
extern s32 D_800A5BE0[];
extern s32 D_800A5BEC[];
extern s32 D_800A5BF8[];
extern s32 D_800A5C04[];
extern s32 D_800A5C10[];
extern s32 D_800A5C1C[];
extern s32 D_800A5C4C[];
extern s32 D_800A5C58[];
extern s32 D_800A5C64[];
extern s32 D_800A5C70[];
extern s32 D_800A5C7C[];
extern s32 D_800A5C88[];
extern s32 D_800A5C94[];
extern s32 D_800A5CA0[];
extern s32 D_800A5CD0[];
extern s32 D_800A5CDC[];
extern s32 D_800A5CE8[];
extern s32 D_800A5CF4[];
extern s32 D_800A5D00[];
extern s32 D_800A5D0C[];
extern s32 D_800A5D18[];
extern s32 D_800A5D24[];
extern s32 D_800A5D54[];
extern s32 D_800A5D60[];
extern s32 D_800A5D6C[];
extern s32 D_800A5D78[];
extern s32 D_800A5D84[];
extern s32 D_800A5D90[];
extern s32 D_800A5D9C[];
extern s32 D_800A5DA8[];
extern s32 D_800A5DD8[];
extern s32 D_800A5DE4[];
extern s32 D_800A5DF0[];
extern s32 D_800A5DFC[];
extern s32 D_800A5E08[];
extern s32 D_800A5E14[];
extern s32 D_800A5E20[];
extern s32 D_800A5E2C[];
extern s32 D_800A5E5C[];
extern s32 D_800A5E68[];
extern s32 D_800A5E74[];
extern s32 D_800A5E80[];
extern s32 D_800A5E8C[];
extern s32 D_800A5E98[];
extern s32 D_800A5EA4[];
extern s32 D_800A5EB0[];
extern s32 D_800A5EE0[];
extern s32 D_800A5EEC[];
extern s32 D_800A5EF8[];
extern s32 D_800A5F04[];
extern s32 D_800A5F10[];
extern s32 D_800A5F1C[];
extern s32 D_800A5F28[];
extern s32 D_800A5F34[];
extern s32 D_800A5F64[];
extern s32 D_800A5F70[];
extern s32 D_800A5F7C[];
extern s32 D_800A5F88[];
extern s32 D_800A5F94[];
extern s32 D_800A5FA0[];
extern s32 D_800A5FAC[];
extern s32 D_800A5FB8[];
extern s32 D_800A5FE8[];
extern s32 D_800A5FF4[];
extern s32 D_800A6000[];
extern s32 D_800A600C[];
extern s32 D_800A6018[];
extern s32 D_800A6024[];
extern s32 D_800A6030[];
extern s32 D_800A603C[];
extern s32 D_800A606C[];
extern s32 D_800A6078[];
extern s32 D_800A6084[];
extern s32 D_800A6090[];
extern s32 D_800A609C[];
extern s32 D_800A60A8[];
extern s32 D_800A60B4[];
extern s32 D_800A60C0[];
extern s32 D_800A60F0[];
extern s32 D_800A60FC[];
extern s32 D_800A6108[];
extern s32 D_800A6114[];
extern s32 D_800A6120[];
extern s32 D_800A612C[];
extern s32 D_800A6138[];
extern s32 D_800A6144[];
extern s32 D_800A6174[];
extern s32 D_800A6180[];
extern s32 D_800A618C[];
extern s32 D_800A6198[];
extern s32 D_800A61A4[];
extern s32 D_800A61B0[];
extern s32 D_800A61BC[];
extern s32 D_800A61C8[];
extern s32 D_800A61F8[];
extern s32 D_800A6204[];
extern s32 D_800A6210[];
extern s32 D_800A621C[];
extern s32 D_800A6228[];
extern s32 D_800A6234[];
extern s32 D_800A6240[];
extern s32 D_800A624C[];
extern s32 D_800A627C[];
extern s32 D_800A6288[];
extern s32 D_800A6294[];
extern s32 D_800A62A0[];
extern s32 D_800A62AC[];
extern s32 D_800A62B8[];
extern s32 D_800A62C4[];
extern s32 D_800A62D0[];
extern s32 D_800A6300[];
extern s32 D_800A630C[];
extern s32 D_800A6318[];
extern s32 D_800A6324[];
extern s32 D_800A6330[];
extern s32 D_800A633C[];
extern s32 D_800A6348[];
extern s32 D_800A6354[];
extern s32 D_800A6384[];
extern s32 D_800A6390[];
extern s32 D_800A639C[];
extern s32 D_800A63A8[];
extern s32 D_800A63B4[];
extern s32 D_800A63C0[];
extern s32 D_800A63CC[];
extern s32 D_800A63D8[];
extern s32 D_800A6408[];
extern s32 D_800A6414[];
extern s32 D_800A6420[];
extern s32 D_800A642C[];
extern s32 D_800A6438[];
extern s32 D_800A6444[];
extern s32 D_800A6450[];
extern s32 D_800A645C[];
extern s32 D_800A648C[];
extern s32 D_800A6498[];
extern s32 D_800A64A4[];
extern s32 D_800A64B0[];
extern s32 D_800A64BC[];
extern s32 D_800A64C8[];
extern s32 D_800A64D4[];
extern s32 D_800A64E0[];
extern s32 D_800A6510[];
extern s32 D_800A651C[];
extern s32 D_800A6528[];
extern s32 D_800A6534[];
extern s32 D_800A6540[];
extern s32 D_800A654C[];
extern s32 D_800A6558[];
extern s32 D_800A6564[];
extern s32 D_800A6594[];
extern s32 D_800A65A0[];
extern s32 D_800A65AC[];
extern s32 D_800A65B8[];
extern s32 D_800A65C4[];
extern s32 D_800A65D0[];
extern s32 D_800A65DC[];
extern s32 D_800A65E8[];
extern s32 D_800A6618[];
extern s32 D_800A6624[];
extern s32 D_800A6630[];
extern s32 D_800A663C[];
extern s32 D_800A6648[];
extern s32 D_800A6654[];
extern s32 D_800A6660[];
extern s32 D_800A666C[];
extern s32 D_800A669C[];
extern s32 D_800A66A8[];
extern s32 D_800A66B4[];
extern s32 D_800A66C0[];
extern s32 D_800A66CC[];
extern s32 D_800A66D8[];
extern s32 D_800A66E4[];
extern s32 D_800A66F0[];
extern s32 D_800A6720[];
extern s32 D_800A672C[];
extern s32 D_800A6738[];
extern s32 D_800A6744[];
extern s32 D_800A6750[];
extern s32 D_800A675C[];
extern s32 D_800A6768[];
extern s32 D_800A6774[];
extern s32 D_800A67A4[];
extern s32 D_800A67B0[];
extern s32 D_800A67BC[];
extern s32 D_800A67C8[];
extern s32 D_800A67D4[];
extern s32 D_800A67E0[];
extern s32 D_800A67EC[];
extern s32 D_800A67F8[];
extern s32 D_800A6828[];
extern s32 D_800A6834[];
extern s32 D_800A6840[];
extern s32 D_800A684C[];
extern s32 D_800A6858[];
extern s32 D_800A6864[];
extern s32 D_800A6870[];
extern s32 D_800A687C[];
extern s32 D_800A68AC[];
extern s32 D_800A68B8[];
extern s32 D_800A68C4[];
extern s32 D_800A68D0[];
extern s32 D_800A68DC[];
extern s32 D_800A68E8[];
extern s32 D_800A68F4[];
extern s32 D_800A6900[];
extern s32 D_800A6930[];
extern s32 D_800A693C[];
extern s32 D_800A6948[];
extern s32 D_800A6954[];
extern s32 D_800A6960[];
extern s32 D_800A696C[];
extern s32 D_800A6978[];
extern s32 D_800A6984[];
extern s32 D_800A69B4[];
extern s32 D_800A69C0[];
extern s32 D_800A69CC[];
extern s32 D_800A69D8[];
extern s32 D_800A69E4[];
extern s32 D_800A69F0[];
extern s32 D_800A69FC[];
extern s32 D_800A6A08[];
extern s32 D_800A6A38[];
extern s32 D_800A6A44[];
extern s32 D_800A6A50[];
extern s32 D_800A6A5C[];
extern s32 D_800A6A68[];
extern s32 D_800A6A74[];
extern s32 D_800A6A80[];
extern s32 D_800A6A8C[];
extern s32 D_800A6ABC[];
extern s32 D_800A6AC8[];
extern s32 D_800A6AD4[];
extern s32 D_800A6AE0[];
extern s32 D_800A6AEC[];
extern s32 D_800A6AF8[];
extern s32 D_800A6B04[];
extern s32 D_800A6B10[];
extern s32 D_800A6B40[];
extern s32 D_800A6B4C[];
extern s32 D_800A6B58[];
extern s32 D_800A6B64[];
extern s32 D_800A6B70[];
extern s32 D_800A6B7C[];
extern s32 D_800A6B88[];
extern s32 D_800A6B94[];
extern s32 D_800A6BC4[];
extern s32 D_800A6BD0[];
extern s32 D_800A6BDC[];
extern s32 D_800A6BE8[];
extern s32 D_800A6BF4[];
extern s32 D_800A6C00[];
extern s32 D_800A6C0C[];
extern s32 D_800A6C18[];
extern s32 D_800A6C48[];
extern s32 D_800A6C54[];
extern s32 D_800A6C60[];
extern s32 D_800A6C6C[];
extern s32 D_800A6C78[];
extern s32 D_800A6C84[];
extern s32 D_800A6C90[];
extern s32 D_800A6C9C[];
extern s32 D_800A6CCC[];
extern s32 D_800A6CD8[];
extern s32 D_800A6CE4[];
extern s32 D_800A6CF0[];
extern s32 D_800A6CFC[];
extern s32 D_800A6D08[];
extern s32 D_800A6D14[];
extern s32 D_800A6D20[];
extern s32 D_800A6D50[];
extern s32 D_800A6D5C[];
extern s32 D_800A6D68[];
extern s32 D_800A6D74[];
extern s32 D_800A6D80[];
extern s32 D_800A6D8C[];
extern s32 D_800A6D98[];
extern s32 D_800A6DA4[];
extern s32 D_800A6DD4[];
extern s32 D_800A6DE0[];
extern s32 D_800A6DEC[];
extern s32 D_800A6DF8[];
extern s32 D_800A6E04[];
extern s32 D_800A6E10[];
extern s32 D_800A6E1C[];
extern s32 D_800A6E28[];
extern s32 D_800A6E58[];
extern s32 D_800A6E64[];
extern s32 D_800A6E70[];
extern s32 D_800A6E7C[];
extern s32 D_800A6E88[];
extern s32 D_800A6E94[];
extern s32 D_800A6EA0[];
extern s32 D_800A6EAC[];
extern s32 D_800A6EDC[];
extern s32 D_800A6EE8[];
extern s32 D_800A6EF4[];
extern s32 D_800A6F00[];
extern s32 D_800A6F0C[];
extern s32 D_800A6F18[];
extern s32 D_800A6F24[];
extern s32 D_800A6F30[];
extern s32 D_800A6F60[];
extern s32 D_800A6F6C[];
extern s32 D_800A6F78[];
extern s32 D_800A6F84[];
extern s32 D_800A6F90[];
extern s32 D_800A6F9C[];
extern s32 D_800A6FA8[];
extern s32 D_800A6FB4[];
extern s32 D_800A6FE4[];
extern s32 D_800A6FF0[];
extern s32 D_800A6FFC[];
extern s32 D_800A7008[];
extern s32 D_800A7014[];
extern s32 D_800A7020[];
extern s32 D_800A702C[];
extern s32 D_800A7038[];
extern s32 D_800A7068[];
extern s32 D_800A7074[];
extern s32 D_800A7080[];
extern s32 D_800A708C[];
extern s32 D_800A7098[];
extern s32 D_800A70A4[];
extern s32 D_800A70B0[];
extern s32 D_800A70BC[];
extern s32 D_800A70EC[];
extern s32 D_800A70F8[];
extern s32 D_800A7104[];
extern s32 D_800A7110[];
extern s32 D_800A711C[];
extern s32 D_800A7128[];
extern s32 D_800A7134[];
extern s32 D_800A7140[];
extern s32 D_800A7170[];
extern s32 D_800A717C[];
extern s32 D_800A7188[];
extern s32 D_800A7194[];
extern s32 D_800A71A0[];
extern s32 D_800A71AC[];
extern s32 D_800A71B8[];
extern s32 D_800A71C4[];
extern s32 D_800A71F4[];
extern s32 D_800A7200[];
extern s32 D_800A720C[];
extern s32 D_800A7218[];
extern s32 D_800A7224[];
extern s32 D_800A7230[];
extern s32 D_800A723C[];
extern s32 D_800A7248[];
extern s32 D_800A7278[];
extern s32 D_800A7284[];
extern s32 D_800A7290[];
extern s32 D_800A729C[];
extern s32 D_800A72A8[];
extern s32 D_800A72B4[];
extern s32 D_800A72C0[];
extern s32 D_800A72CC[];
extern s32 D_800A72FC[];
extern s32 D_800A7308[];
extern s32 D_800A7314[];
extern s32 D_800A7320[];
extern s32 D_800A732C[];
extern s32 D_800A7338[];
extern s32 D_800A7344[];
extern s32 D_800A7350[];
extern s32 D_800A7380[];
extern s32 D_800A738C[];
extern s32 D_800A7398[];
extern s32 D_800A73A4[];
extern s32 D_800A73B0[];
extern s32 D_800A73BC[];
extern s32 D_800A73C8[];
extern s32 D_800A73D4[];
extern s32 D_800A7404[];
extern s32 D_800A7410[];
extern s32 D_800A741C[];
extern s32 D_800A7428[];
extern s32 D_800A7434[];
extern s32 D_800A7440[];
extern s32 D_800A744C[];
extern s32 D_800A7458[];
extern s32 D_800A7488[];
extern s32 D_800A7494[];
extern s32 D_800A74A0[];
extern s32 D_800A74AC[];
extern s32 D_800A74B8[];
extern s32 D_800A74C4[];
extern s32 D_800A74D0[];
extern s32 D_800A74DC[];
extern s32 D_800A750C[];
extern s32 D_800A7518[];
extern s32 D_800A7524[];
extern s32 D_800A7530[];
extern s32 D_800A753C[];
extern s32 D_800A7548[];
extern s32 D_800A7554[];
extern s32 D_800A7560[];
extern s32 D_800A7590[];
extern s32 D_800A759C[];
extern s32 D_800A75A8[];
extern s32 D_800A75B4[];
extern s32 D_800A75C0[];
extern s32 D_800A75CC[];
extern s32 D_800A75D8[];
extern s32 D_800A75E4[];
extern s32 D_800A7614[];
extern s32 D_800A7620[];
extern s32 D_800A762C[];
extern s32 D_800A7638[];
extern s32 D_800A7644[];
extern s32 D_800A7650[];
extern s32 D_800A765C[];
extern s32 D_800A7668[];
extern s32 D_800A7698[];
extern s32 D_800A76A4[];
extern s32 D_800A76B0[];
extern s32 D_800A76BC[];
extern s32 D_800A76C8[];
extern s32 D_800A76D4[];
extern s32 D_800A76E0[];
extern s32 D_800A76EC[];
extern s32 D_800A771C[];
extern s32 D_800A7728[];
extern s32 D_800A7734[];
extern s32 D_800A7740[];
extern s32 D_800A774C[];
extern s32 D_800A7758[];
extern s32 D_800A7764[];
extern s32 D_800A7770[];
extern s32 D_800A77A0[];
extern s32 D_800A77AC[];
extern s32 D_800A77B8[];
extern s32 D_800A77C4[];
extern s32 D_800A77D0[];
extern s32 D_800A77DC[];
extern s32 D_800A77E8[];
extern s32 D_800A77F4[];
extern s32 D_800A7824[];
extern s32 D_800A7830[];
extern s32 D_800A783C[];
extern s32 D_800A7848[];
extern s32 D_800A7854[];
extern s32 D_800A7860[];
extern s32 D_800A786C[];
extern s32 D_800A7878[];
extern s32 D_800A78A8[];
extern s32 D_800A78B4[];
extern s32 D_800A78C0[];
extern s32 D_800A78CC[];
extern s32 D_800A78D8[];
extern s32 D_800A78E4[];
extern s32 D_800A78F0[];
extern s32 D_800A78FC[];
extern s32 D_800A792C[];
extern s32 D_800A7938[];
extern s32 D_800A7944[];
extern s32 D_800A7950[];
extern s32 D_800A795C[];
extern s32 D_800A7968[];
extern s32 D_800A7974[];
extern s32 D_800A7980[];
extern s32 D_800A79B0[];
extern s32 D_800A79BC[];
extern s32 D_800A79C8[];
extern s32 D_800A79D4[];
extern s32 D_800A79E0[];
extern s32 D_800A79EC[];
extern s32 D_800A79F8[];
extern s32 D_800A7A04[];
extern s32 D_800A7A34[];
extern s32 D_800A7A40[];
extern s32 D_800A7A4C[];
extern s32 D_800A7A58[];
extern s32 D_800A7A64[];
extern s32 D_800A7A70[];
extern s32 D_800A7A7C[];
extern s32 D_800A7A88[];
extern s32 D_800A7AB8[];
extern s32 D_800A7AC4[];
extern s32 D_800A7AD0[];
extern s32 D_800A7ADC[];
extern s32 D_800A7AE8[];
extern s32 D_800A7AF4[];
extern s32 D_800A7B00[];
extern s32 D_800A7B0C[];
extern s32 D_800A7B3C[];
extern s32 D_800A7B48[];
extern s32 D_800A7B54[];
extern s32 D_800A7B60[];
extern s32 D_800A7B6C[];
extern s32 D_800A7B78[];
extern s32 D_800A7B84[];
extern s32 D_800A7B90[];
extern s32 D_800A7BC0[];
extern s32 D_800A7BCC[];
extern s32 D_800A7BD8[];
extern s32 D_800A7BE4[];
extern s32 D_800A7BF0[];
extern s32 D_800A7BFC[];
extern s32 D_800A7C08[];
extern s32 D_800A7C14[];
extern s32 D_800A7C44[];
extern s32 D_800A7C50[];
extern s32 D_800A7C5C[];
extern s32 D_800A7C68[];
extern s32 D_800A7C74[];
extern s32 D_800A7C80[];
extern s32 D_800A7C8C[];
extern s32 D_800A7C98[];
extern s32 D_800A7CC8[];
extern s32 D_800A7CD4[];
extern s32 D_800A7CE0[];
extern s32 D_800A7CEC[];
extern s32 D_800A7CF8[];
extern s32 D_800A7D04[];
extern s32 D_800A7D10[];
extern s32 D_800A7D1C[];
extern s32 D_800A7D4C[];
extern s32 D_800A7D58[];
extern s32 D_800A7D64[];
extern s32 D_800A7D70[];
extern s32 D_800A7D7C[];
extern s32 D_800A7D88[];
extern s32 D_800A7D94[];
extern s32 D_800A7DA0[];
extern s32 D_800A7DD0[];
extern s32 D_800A7DDC[];
extern s32 D_800A7DE8[];
extern s32 D_800A7DF4[];
extern s32 D_800A7E00[];
extern s32 D_800A7E0C[];
extern s32 D_800A7E18[];
extern s32 D_800A7E24[];
extern s32 D_800A7E54[];
extern s32 D_800A7E60[];
extern s32 D_800A7E6C[];
extern s32 D_800A7E78[];
extern s32 D_800A7E84[];
extern s32 D_800A7E90[];
extern s32 D_800A7E9C[];
extern s32 D_800A7EA8[];
extern s32 D_800A7ED8[];
extern s32 D_800A7EE4[];
extern s32 D_800A7EF0[];
extern s32 D_800A7EFC[];
extern s32 D_800A7F08[];
extern s32 D_800A7F14[];
extern s32 D_800A7F20[];
extern s32 D_800A7F2C[];
extern s32 D_800A7F5C[];
extern s32 D_800A7F68[];
extern s32 D_800A7F74[];
extern s32 D_800A7F80[];
extern s32 D_800A7F8C[];
extern s32 D_800A7F98[];
extern s32 D_800A7FA4[];
extern s32 D_800A7FB0[];
extern s32 D_800A7FE0[];
extern s32 D_800A7FEC[];
extern s32 D_800A7FF8[];
extern s32 D_800A8004[];
extern s32 D_800A8010[];
extern s32 D_800A801C[];
extern s32 D_800A8028[];
extern s32 D_800A8034[];
extern s32 D_800A8064[];
extern s32 D_800A8070[];
extern s32 D_800A807C[];
extern s32 D_800A8088[];
extern s32 D_800A8094[];
extern s32 D_800A80A0[];
extern s32 D_800A80AC[];
extern s32 D_800A80B8[];
extern s32 D_800A80E8[];
extern s32 D_800A80F4[];
extern s32 D_800A8100[];
extern s32 D_800A810C[];
extern s32 D_800A8118[];
extern s32 D_800A8124[];
extern s32 D_800A8130[];
extern s32 D_800A813C[];
extern s32 D_800A816C[];
extern s32 D_800A8178[];
extern s32 D_800A8184[];
extern s32 D_800A8190[];
extern s32 D_800A819C[];
extern s32 D_800A81A8[];
extern s32 D_800A81B4[];
extern s32 D_800A81C0[];
extern s32 D_800A81F0[];
extern s32 D_800A81FC[];
extern s32 D_800A8208[];
extern s32 D_800A8214[];
extern s32 D_800A8220[];
extern s32 D_800A822C[];
extern s32 D_800A8238[];
extern s32 D_800A8244[];
extern s32 D_800A8274[];
extern s32 D_800A8280[];
extern s32 D_800A828C[];
extern s32 D_800A8298[];
extern s32 D_800A82A4[];
extern s32 D_800A82B0[];
extern s32 D_800A82BC[];
extern s32 D_800A82C8[];
extern s32 D_800A82F8[];
extern s32 D_800A8304[];
extern s32 D_800A8310[];
extern s32 D_800A831C[];
extern s32 D_800A8328[];
extern s32 D_800A8334[];
extern s32 D_800A8340[];
extern s32 D_800A834C[];
extern s32 D_800A837C[];
extern s32 D_800A8388[];
extern s32 D_800A8394[];
extern s32 D_800A83A0[];
extern s32 D_800A83AC[];
extern s32 D_800A83B8[];
extern s32 D_800A83C4[];
extern s32 D_800A83D0[];
extern s32 D_800A8400[];
extern s32 D_800A840C[];
extern s32 D_800A8418[];
extern s32 D_800A8424[];
extern s32 D_800A8430[];
extern s32 D_800A843C[];
extern s32 D_800A8448[];
extern s32 D_800A8454[];
extern s32 D_800A8484[];
extern s32 D_800A8490[];
extern s32 D_800A849C[];
extern s32 D_800A84A8[];
extern s32 D_800A84B4[];
extern s32 D_800A84C0[];
extern s32 D_800A84CC[];
extern s32 D_800A84D8[];
extern s32 D_800A8508[];
extern s32 D_800A8514[];
extern s32 D_800A8520[];
extern s32 D_800A852C[];
extern s32 D_800A8538[];
extern s32 D_800A8544[];
extern s32 D_800A8550[];
extern s32 D_800A855C[];
extern s32 D_800A858C[];
extern s32 D_800A8598[];
extern s32 D_800A85A4[];
extern s32 D_800A85B0[];
extern s32 D_800A85BC[];
extern s32 D_800A85C8[];
extern s32 D_800A85D4[];
extern s32 D_800A85E0[];
extern s32 D_800A8610[];
extern s32 D_800A861C[];
extern s32 D_800A8628[];
extern s32 D_800A8634[];
extern s32 D_800A8640[];
extern s32 D_800A864C[];
extern s32 D_800A8658[];
extern s32 D_800A8664[];
extern s32 D_800A8694[];
extern s32 D_800A86A0[];
extern s32 D_800A86AC[];
extern s32 D_800A86B8[];
extern s32 D_800A86C4[];
extern s32 D_800A86D0[];
extern s32 D_800A86DC[];
extern s32 D_800A86E8[];
extern s32 D_800A8718[];
extern s32 D_800A8724[];
extern s32 D_800A8730[];
extern s32 D_800A873C[];
extern s32 D_800A8748[];
extern s32 D_800A8754[];
extern s32 D_800A8760[];
extern s32 D_800A876C[];
extern s32 D_800A879C[];
extern s32 D_800A87A8[];
extern s32 D_800A87B4[];
extern s32 D_800A87C0[];
extern s32 D_800A87CC[];
extern s32 D_800A87D8[];
extern s32 D_800A87E4[];
extern s32 D_800A87F0[];
extern s32 D_800A8820[];
extern s32 D_800A882C[];
extern s32 D_800A8838[];
extern s32 D_800A8844[];
extern s32 D_800A8850[];
extern s32 D_800A885C[];
extern s32 D_800A8868[];
extern s32 D_800A8874[];
extern s32 D_800A88A4[];
extern s32 D_800A88B0[];
extern s32 D_800A88BC[];
extern s32 D_800A88C8[];
extern s32 D_800A88D4[];
extern s32 D_800A88E0[];
extern s32 D_800A88EC[];
extern s32 D_800A88F8[];
extern s32 D_800A8928[];
extern s32 D_800A8934[];
extern s32 D_800A8940[];
extern s32 D_800A894C[];
extern s32 D_800A8958[];
extern s32 D_800A8964[];
extern s32 D_800A8970[];
extern s32 D_800A897C[];
extern s32 D_800A89AC[];
extern s32 D_800A89B8[];
extern s32 D_800A89C4[];
extern s32 D_800A89D0[];
extern s32 D_800A89DC[];
extern s32 D_800A89E8[];
extern s32 D_800A89F4[];
extern s32 D_800A8A00[];
extern s32 D_800A8A30[];
extern s32 D_800A8A3C[];
extern s32 D_800A8A48[];
extern s32 D_800A8A54[];
extern s32 D_800A8A60[];
extern s32 D_800A8A6C[];
extern s32 D_800A8A78[];
extern s32 D_800A8A84[];
extern s32 D_800A8AB4[];
extern s32 D_800A8AC0[];
extern s32 D_800A8ACC[];
extern s32 D_800A8AD8[];
extern s32 D_800A8AE4[];
extern s32 D_800A8AF0[];
extern s32 D_800A8AFC[];
extern s32 D_800A8B08[];
extern s32 D_800A8B38[];
extern s32 D_800A8B44[];
extern s32 D_800A8B50[];
extern s32 D_800A8B5C[];
extern s32 D_800A8B68[];
extern s32 D_800A8B74[];
extern s32 D_800A8B80[];
extern s32 D_800A8B8C[];
extern s32 D_800A8BBC[];
extern s32 D_800A8BC8[];
extern s32 D_800A8BD4[];
extern s32 D_800A8BE0[];
extern s32 D_800A8BEC[];
extern s32 D_800A8BF8[];
extern s32 D_800A8C04[];
extern s32 D_800A8C10[];
extern s32 D_800A8C40[];
extern s32 D_800A8C4C[];
extern s32 D_800A8C58[];
extern s32 D_800A8C64[];
extern s32 D_800A8C70[];
extern s32 D_800A8C7C[];
extern s32 D_800A8C88[];
extern s32 D_800A8C94[];
extern s32 D_800A8CC4[];
extern s32 D_800A8CD0[];
extern s32 D_800A8CDC[];
extern s32 D_800A8CE8[];
extern s32 D_800A8CF4[];
extern s32 D_800A8D00[];
extern s32 D_800A8D0C[];
extern s32 D_800A8D18[];
extern s32 D_800A8D48[];
extern s32 D_800A8D54[];
extern s32 D_800A8D60[];
extern s32 D_800A8D6C[];
extern s32 D_800A8D78[];
extern s32 D_800A8D84[];
extern s32 D_800A8D90[];
extern s32 D_800A8D9C[];
extern s32 D_800A8DCC[];
extern s32 D_800A8DD8[];
extern s32 D_800A8DE4[];
extern s32 D_800A8DF0[];
extern s32 D_800A8DFC[];
extern s32 D_800A8E08[];
extern s32 D_800A8E14[];
extern s32 D_800A8E20[];
extern s32 D_800A8E50[];
extern s32 D_800A8E5C[];
extern s32 D_800A8E68[];
extern s32 D_800A8E74[];
extern s32 D_800A8E80[];
extern s32 D_800A8E8C[];
extern s32 D_800A8E98[];
extern s32 D_800A8EA4[];
extern s32 D_800A8ED4[];
extern s32 D_800A8EE0[];
extern s32 D_800A8EEC[];
extern s32 D_800A8EF8[];
extern s32 D_800A8F04[];
extern s32 D_800A8F10[];
extern s32 D_800A8F1C[];
extern s32 D_800A8F28[];
extern s32 D_800A8F58[];
extern s32 D_800A8F64[];
extern s32 D_800A8F70[];
extern s32 D_800A8F7C[];
extern s32 D_800A8F88[];
extern s32 D_800A8F94[];
extern s32 D_800A8FA0[];
extern s32 D_800A8FAC[];
extern s32 D_800A8FDC[];
extern s32 D_800A8FE8[];
extern s32 D_800A8FF4[];
extern s32 D_800A9000[];
extern s32 D_800A900C[];
extern s32 D_800A9018[];
extern s32 D_800A9024[];
extern s32 D_800A9030[];
extern s32 D_800A9060[];
extern s32 D_800A906C[];
extern s32 D_800A9078[];
extern s32 D_800A9084[];
extern s32 D_800A9090[];
extern s32 D_800A909C[];
extern s32 D_800A90A8[];
extern s32 D_800A90B4[];
extern s32 D_800A5784[];
extern s32 D_800A5808[];
extern s32 D_800A588C[];
extern s32 D_800A5910[];
extern s32 D_800A5994[];
extern s32 D_800A5A18[];
extern s32 D_800A5A9C[];
extern s32 D_800A5B20[];
extern s32 D_800A5BA4[];
extern s32 D_800A5C28[];
extern s32 D_800A5CAC[];
extern s32 D_800A5D30[];
extern s32 D_800A5DB4[];
extern s32 D_800A5E38[];
extern s32 D_800A5EBC[];
extern s32 D_800A5F40[];
extern s32 D_800A5FC4[];
extern s32 D_800A6048[];
extern s32 D_800A60CC[];
extern s32 D_800A6150[];
extern s32 D_800A61D4[];
extern s32 D_800A6258[];
extern s32 D_800A62DC[];
extern s32 D_800A6360[];
extern s32 D_800A63E4[];
extern s32 D_800A6468[];
extern s32 D_800A64EC[];
extern s32 D_800A6570[];
extern s32 D_800A65F4[];
extern s32 D_800A6678[];
extern s32 D_800A66FC[];
extern s32 D_800A6780[];
extern s32 D_800A6804[];
extern s32 D_800A6888[];
extern s32 D_800A690C[];
extern s32 D_800A6990[];
extern s32 D_800A6A14[];
extern s32 D_800A6A98[];
extern s32 D_800A6B1C[];
extern s32 D_800A6BA0[];
extern s32 D_800A6C24[];
extern s32 D_800A6CA8[];
extern s32 D_800A6D2C[];
extern s32 D_800A6DB0[];
extern s32 D_800A6E34[];
extern s32 D_800A6EB8[];
extern s32 D_800A6F3C[];
extern s32 D_800A6FC0[];
extern s32 D_800A7044[];
extern s32 D_800A70C8[];
extern s32 D_800A714C[];
extern s32 D_800A71D0[];
extern s32 D_800A7254[];
extern s32 D_800A72D8[];
extern s32 D_800A735C[];
extern s32 D_800A73E0[];
extern s32 D_800A7464[];
extern s32 D_800A74E8[];
extern s32 D_800A756C[];
extern s32 D_800A75F0[];
extern s32 D_800A7674[];
extern s32 D_800A76F8[];
extern s32 D_800A777C[];
extern s32 D_800A7800[];
extern s32 D_800A7884[];
extern s32 D_800A7908[];
extern s32 D_800A798C[];
extern s32 D_800A7A10[];
extern s32 D_800A7A94[];
extern s32 D_800A7B18[];
extern s32 D_800A7B9C[];
extern s32 D_800A7C20[];
extern s32 D_800A7CA4[];
extern s32 D_800A7D28[];
extern s32 D_800A7DAC[];
extern s32 D_800A7E30[];
extern s32 D_800A7EB4[];
extern s32 D_800A7F38[];
extern s32 D_800A7FBC[];
extern s32 D_800A8040[];
extern s32 D_800A80C4[];
extern s32 D_800A8148[];
extern s32 D_800A81CC[];
extern s32 D_800A8250[];
extern s32 D_800A82D4[];
extern s32 D_800A8358[];
extern s32 D_800A83DC[];
extern s32 D_800A8460[];
extern s32 D_800A84E4[];
extern s32 D_800A8568[];
extern s32 D_800A85EC[];
extern s32 D_800A8670[];
extern s32 D_800A86F4[];
extern s32 D_800A8778[];
extern s32 D_800A87FC[];
extern s32 D_800A8880[];
extern s32 D_800A8904[];
extern s32 D_800A8988[];
extern s32 D_800A8A0C[];
extern s32 D_800A8A90[];
extern s32 D_800A8B14[];
extern s32 D_800A8B98[];
extern s32 D_800A8C1C[];
extern s32 D_800A8CA0[];
extern s32 D_800A8D24[];
extern s32 D_800A8DA8[];
extern s32 D_800A8E2C[];
extern s32 D_800A8EB0[];
extern s32 D_800A8F34[];
extern s32 D_800A8FB8[];
extern s32 D_800A903C[];
extern s32 D_800A90C0[];
extern s32 D_800A951C[];
extern s32 D_800A94A4[];
extern s32 D_800A9528[];
extern s32 D_800A94BC[];
extern s32 D_800A9534[];
extern s32 D_800A94D4[];
extern s32 D_800A9540[];
extern s32 D_800A94EC[];
extern s32 D_800A954C[];
extern s32 D_800A9504[];
extern s32 D_800A9558[];
extern s32 D_800A9564[];
extern s32 D_800A9570[];
extern s32 D_800A957C[];
extern s32 D_800A9588[];
extern s32 D_800A9594[];
extern s32 D_800A95A0[];
extern s32 D_800A95AC[];
extern s32 D_800A95B8[];
extern s32 D_800A95C4[];
extern s32 D_800A95D0[];
extern s32 D_800A95E4[];
extern s32 D_800A95F8[];
extern s32 D_800A960C[];
extern s32 D_800A9620[];
extern s32 D_800A9634[];
extern s32 D_800A9648[];
extern s32 D_800A965C[];
extern s32 D_800A9670[];
extern s32 D_800A9684[];
extern s32 D_800A9698[];
extern s32 D_800A96AC[];
extern s32 D_800A96C0[];
extern s32 D_800A96D4[];
extern s32 D_800A96E8[];
extern s32 D_800A96FC[];

StagePoint D_800A4F90 = { 0x2EC, 1, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A4FA0 = { 0x21D, 0, 0, 0x410, 0x400, 0, &D_800A4F90 };
StagePoints D_800A4FB0 = { 1, 1, &D_800A4FA0 };
StagePoint D_800A4FB8 = { 0x2ED, 1, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A4FC8 = { 0x248, 0, 0, 0x320, 0x518, 0, &D_800A4FB8 };
StagePoints D_800A4FD8 = { 1, 2, &D_800A4FC8 };
StagePoint D_800A4FE0 = { 0x2EC, 2, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A4FF0 = { 0x261, 0, 0, 176, 0x2EE, 0, &D_800A4FE0 };
StagePoints D_800A5000 = { 2, 1, &D_800A4FF0 };
StagePoint D_800A5008 = { 0x2EC, 3, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5018 = { 0x2CD, 0, 0, 0x1C0, 0x206, 0, &D_800A5008 };
StagePoints D_800A5028 = { 3, 1, &D_800A5018 };
StagePoint D_800A5030 = { 0x2ED, 3, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5040 = { 0x2A7, 0, 0, 0x560, 0x188, 0, &D_800A5030 };
StagePoints D_800A5050 = { 3, 2, &D_800A5040 };
StagePoint D_800A5058 = { 0x2EE, 3, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5068 = { 0x21D, 0, 0, 0x110, 0x290, 0, &D_800A5058 };
StagePoints D_800A5078 = { 3, 3, &D_800A5068 };
StagePoint D_800A5080 = { 0x2ED, 3, 4, 0x3A0, 128, 1, NULL };
StagePoint D_800A5090 = { 0x28C, 0, 0, 0x110, 0x290, 0, &D_800A5080 };
StagePoints D_800A50A0 = { 3, 4, &D_800A5090 };
StagePoint D_800A50A8 = { 0x2EE, 3, 5, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A50B8 = { 0x2B1, 0, 0, 0x3D0, 0x100, 0, &D_800A50A8 };
StagePoints D_800A50C8 = { 3, 5, &D_800A50B8 };
StagePoint D_800A50D0 = { 0x2EE, 4, 1, 0x130, 200, 1, NULL };
StagePoint D_800A50E0 = { 0x23C, 0, 0, 192, 224, 0, &D_800A50D0 };
StagePoints D_800A50F0 = { 4, 1, &D_800A50E0 };
StagePoint D_800A50F8 = { 0x2EE, 4, 2, 0x130, 200, 1, NULL };
StagePoint D_800A5108 = { 0x2A9, 0, 0, 192, 224, 0, &D_800A50F8 };
StagePoints D_800A5118 = { 4, 2, &D_800A5108 };
StagePoint D_800A5120 = { 0x2EE, 5, 1, 0x130, 200, 1, NULL };
StagePoint D_800A5130 = { 0x2CD, 0, 0, 0x4C0, 200, 0, &D_800A5120 };
StagePoints D_800A5140 = { 5, 1, &D_800A5130 };
StagePoint D_800A5148 = { 0x2EE, 5, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5158 = { 0x2C9, 0, 0, 0x4B0, 0x13E, 0, &D_800A5148 };
StagePoints D_800A5168 = { 5, 2, &D_800A5158 };
StagePoint D_800A5170 = { 0x2ED, 5, 4, 0x3A0, 128, 1, NULL };
StagePoint D_800A5180 = { 0x2CC, 0, 0, 192, 0x214, 0, &D_800A5170 };
StagePoints D_800A5190 = { 5, 3, &D_800A5180 };
StagePoint D_800A5198 = { 0x2ED, 6, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A51A8 = { 0x247, 0, 0, 0x190, 0x1C0, 0, &D_800A5198 };
StagePoints D_800A51B8 = { 6, 1, &D_800A51A8 };
StagePoint D_800A51C0 = { 0x2EC, 7, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A51D0 = { 0x2CA, 0, 0, 0x3BE, 0x2EE, 0, &D_800A51C0 };
StagePoints D_800A51E0 = { 7, 1, &D_800A51D0 };
StagePoint D_800A51E8 = { 0x2EC, 7, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A51F8 = { 0x262, 0, 0, 0x3BE, 0x2EE, 0, &D_800A51E8 };
StagePoints D_800A5208 = { 7, 2, &D_800A51F8 };
StagePoint D_800A5210 = { 0x2EE, 7, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5220 = { 0x298, 0, 0, 0x560, 0x238, 0, &D_800A5210 };
StagePoints D_800A5230 = { 7, 3, &D_800A5220 };
StagePoint D_800A5238 = { 0x2ED, 8, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5248 = { 0x2B2, 0, 0, 0x320, 0x518, 0, &D_800A5238 };
StagePoints D_800A5258 = { 8, 1, &D_800A5248 };
StagePoint D_800A5260 = { 0x2EC, 8, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5270 = { 0x28C, 0, 0, 0x410, 0x400, 0, &D_800A5260 };
StagePoints D_800A5280 = { 8, 2, &D_800A5270 };
StagePoint D_800A5288 = { 0x2EC, 9, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5298 = { 0x2C9, 0, 0, 176, 0x2EE, 0, &D_800A5288 };
StagePoints D_800A52A8 = { 9, 1, &D_800A5298 };
StagePoint D_800A52B0 = { 0x2EC, 10, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A52C0 = { 0x265, 0, 0, 0x4AE, 0x1EF, 0, &D_800A52B0 };
StagePoints D_800A52D0 = { 10, 1, &D_800A52C0 };
StagePoint D_800A52D8 = { 0x2ED, 10, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A52E8 = { 0x264, 0, 0, 0x100, 0x2A4, 0, &D_800A52D8 };
StagePoints D_800A52F8 = { 10, 2, &D_800A52E8 };
StagePoint D_800A5300 = { 0x2EC, 11, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5310 = { 0x2CD, 0, 0, 0x4AE, 0x1EF, 0, &D_800A5300 };
StagePoints D_800A5320 = { 11, 1, &D_800A5310 };
StagePoint D_800A5328 = { 0x2ED, 11, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5338 = { 0x2CC, 0, 0, 0x100, 0x2A4, 0, &D_800A5328 };
StagePoints D_800A5348 = { 11, 2, &D_800A5338 };
StagePoint D_800A5350 = { 0x2ED, 12, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5360 = { 0x261, 0, 0, 0x2F0, 0x30E, 0, &D_800A5350 };
StagePoints D_800A5370 = { 12, 1, &D_800A5360 };
StagePoint D_800A5378 = { 0x2EC, 13, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A5388 = { 0x2C9, 0, 0, 0x2F0, 0x30E, 0, &D_800A5378 };
StagePoints D_800A5398 = { 13, 1, &D_800A5388 };
StagePoint D_800A53A0 = { 0x2EB, 15, 1, 0x240, 160, 1, NULL };
StagePoint D_800A53B0 = { 0x220, 0, 0, 0x398, 0x270, 0, &D_800A53A0 };
StagePoints D_800A53C0 = { 15, 1, &D_800A53B0 };
StagePoint D_800A53C8 = { 0x2EE, 16, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A53D8 = { 0x24C, 0, 0, 0x200, 0x178, 0, &D_800A53C8 };
StagePoints D_800A53E8 = { 16, 1, &D_800A53D8 };
StagePoint D_800A53F0 = { 0x2EB, 17, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5400 = { 0x21D, 0, 0, 0x290, 0x200, 0, &D_800A53F0 };
StagePoints D_800A5410 = { 17, 1, &D_800A5400 };
StagePoint D_800A5418 = { 0x2EC, 18, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5428 = { 0x2B4, 0, 0, 0x3F0, 0x330, 0, &D_800A5418 };
StagePoints D_800A5438 = { 18, 1, &D_800A5428 };
StagePoint D_800A5440 = { 0x2EC, 19, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A5450 = { 0x262, 0, 0, 190, 166, 0, &D_800A5440 };
StagePoints D_800A5460 = { 19, 1, &D_800A5450 };
StagePoint D_800A5468 = { 0x2EE, 20, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5478 = { 0x2CA, 0, 0, 190, 166, 0, &D_800A5468 };
StagePoints D_800A5488 = { 20, 1, &D_800A5478 };
StagePoint D_800A5490 = { 0x2EE, 21, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A54A0 = { 0x264, 0, 0, 0x3A0, 180, 0, &D_800A5490 };
StagePoints D_800A54B0 = { 21, 1, &D_800A54A0 };
StagePoint D_800A54B8 = { 0x2EC, 22, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A54C8 = { 0x265, 0, 0, 0x23F, 0x317, 0, &D_800A54B8 };
StagePoints D_800A54D8 = { 22, 1, &D_800A54C8 };
StagePoint D_800A54E0 = { 0x2EC, 22, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A54F0 = { 0x261, 0, 0, 0x1A0, 0x166, 0, &D_800A54E0 };
StagePoints D_800A5500 = { 22, 2, &D_800A54F0 };
StagePoint D_800A5508 = { 0x2EC, 23, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5518 = { 0x2CD, 0, 0, 0x23F, 0x317, 0, &D_800A5508 };
StagePoints D_800A5528 = { 23, 1, &D_800A5518 };
StagePoint D_800A5530 = { 0x2EE, 23, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5540 = { 0x2C9, 0, 0, 0x1A0, 0x166, 0, &D_800A5530 };
StagePoints D_800A5550 = { 23, 2, &D_800A5540 };
StagePoint D_800A5558 = { 0x2EC, 24, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5568 = { 0x2CC, 0, 0, 0x3A0, 180, 0, &D_800A5558 };
StagePoints D_800A5578 = { 24, 1, &D_800A5568 };
StagePoint D_800A5580 = { 0x2EE, 25, 1, 0x130, 200, 1, NULL };
StagePoint D_800A5590 = { 0x2B6, 0, 0, 0x200, 0x178, 0, &D_800A5580 };
StagePoints D_800A55A0 = { 25, 1, &D_800A5590 };
StagePoint D_800A55A8 = { 0x2EB, 26, 1, 0x240, 160, 1, NULL };
StagePoint D_800A55B8 = { 0x2A7, 0, 0, 0x1C1, 0x37A, 0, &D_800A55A8 };
StagePoints D_800A55C8 = { 26, 1, &D_800A55B8 };
StagePoint D_800A55D0 = { 0x2ED, 28, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A55E0 = { 0x28C, 0, 0, 0x290, 0x200, 0, &D_800A55D0 };
StagePoints D_800A55F0 = { 28, 1, &D_800A55E0 };
StagePoint D_800A55F8 = { 0x2EC, 29, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A5608 = { 0x28F, 0, 0, 0x398, 0x270, 0, &D_800A55F8 };
StagePoints D_800A5618 = { 29, 1, &D_800A5608 };
StagePoint D_800A5620 = { 0x2ED, 30, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5630 = { 0x2B4, 0, 0, 0x2C0, 0x2A8, 0, &D_800A5620 };
StagePoints D_800A5640 = { 30, 1, &D_800A5630 };
StagePoint D_800A5648 = { 0x2ED, 30, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A5658 = { 0x2B2, 0, 0, 0x2A0, 0x138, 0, &D_800A5648 };
StagePoints D_800A5668 = { 30, 2, &D_800A5658 };
StagePoints *D_800A5670[] = {
    &D_800A4FB0, &D_800A4FD8, &D_800A5000, &D_800A5028,
    &D_800A5050, &D_800A5078, &D_800A50A0, &D_800A50C8,
    &D_800A50F0, &D_800A5118, &D_800A5140, &D_800A5168,
    &D_800A5190, &D_800A51B8, &D_800A51E0, &D_800A5208,
    &D_800A5230, &D_800A5258, &D_800A5280, &D_800A52A8,
    &D_800A52D0, &D_800A52F8, &D_800A5320, &D_800A5348,
    &D_800A5370, &D_800A5398, &D_800A53C0, &D_800A53E8,
    &D_800A5410, &D_800A5438, &D_800A5460, &D_800A5488,
    &D_800A54B0, &D_800A54D8, &D_800A5500, &D_800A5528,
    &D_800A5550, &D_800A5578, &D_800A55A0, &D_800A55C8,
    &D_800A55F0, &D_800A5618, &D_800A5640, &D_800A5668,
    NULL,
};
s32 D_800A5724[] = {
    174, 10, 0x60080000,
};
s32 D_800A5730[] = {
    174, 10, 0x60080000,
};
s32 D_800A573C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5748[] = {
    170, 10, 0x60080000,
};
s32 D_800A5754[] = {
    170, 10, 0x60080000,
};
s32 D_800A5760[] = {
    170, 10, 0x60080000,
};
s32 D_800A576C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5778[] = {
    170, 10, 0x60080000,
};
s32 D_800A5784[] = {
    1, (s32)D_800A5724, (s32)D_800A5730, (s32)D_800A573C,
    (s32)D_800A5748, (s32)D_800A5754, (s32)D_800A5760, (s32)D_800A576C,
    (s32)D_800A5778,
};
s32 D_800A57A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A57B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A57C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A57CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A57D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A57E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A57F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A57FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5808[] = {
    0, (s32)D_800A57A8, (s32)D_800A57B4, (s32)D_800A57C0,
    (s32)D_800A57CC, (s32)D_800A57D8, (s32)D_800A57E4, (s32)D_800A57F0,
    (s32)D_800A57FC,
};
s32 D_800A582C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5838[] = {
    0, 0, 0x60040000,
};
s32 D_800A5844[] = {
    0, 0, 0x60040000,
};
s32 D_800A5850[] = {
    0, 0, 0x60040000,
};
s32 D_800A585C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5868[] = {
    0, 0, 0x60040000,
};
s32 D_800A5874[] = {
    0, 0, 0x60040000,
};
s32 D_800A5880[] = {
    0, 0, 0x60040000,
};
s32 D_800A588C[] = {
    0, (s32)D_800A582C, (s32)D_800A5838, (s32)D_800A5844,
    (s32)D_800A5850, (s32)D_800A585C, (s32)D_800A5868, (s32)D_800A5874,
    (s32)D_800A5880,
};
s32 D_800A58B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A58BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A58C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A58D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A58E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A58EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A58F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5904[] = {
    0, 0, 0x60040000,
};
s32 D_800A5910[] = {
    0, (s32)D_800A58B0, (s32)D_800A58BC, (s32)D_800A58C8,
    (s32)D_800A58D4, (s32)D_800A58E0, (s32)D_800A58EC, (s32)D_800A58F8,
    (s32)D_800A5904,
};
s32 D_800A5934[] = {
    174, 10, 0x60080000,
};
s32 D_800A5940[] = {
    174, 10, 0x60080000,
};
s32 D_800A594C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5958[] = {
    170, 10, 0x60080000,
};
s32 D_800A5964[] = {
    170, 10, 0x60080000,
};
s32 D_800A5970[] = {
    110, 10, 0x60080000,
};
s32 D_800A597C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5988[] = {
    110, 10, 0x60080000,
};
s32 D_800A5994[] = {
    1, (s32)D_800A5934, (s32)D_800A5940, (s32)D_800A594C,
    (s32)D_800A5958, (s32)D_800A5964, (s32)D_800A5970, (s32)D_800A597C,
    (s32)D_800A5988,
};
s32 D_800A59B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A59D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A59DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A59E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A18[] = {
    0, (s32)D_800A59B8, (s32)D_800A59C4, (s32)D_800A59D0,
    (s32)D_800A59DC, (s32)D_800A59E8, (s32)D_800A59F4, (s32)D_800A5A00,
    (s32)D_800A5A0C,
};
s32 D_800A5A3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A60[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A9C[] = {
    0, (s32)D_800A5A3C, (s32)D_800A5A48, (s32)D_800A5A54,
    (s32)D_800A5A60, (s32)D_800A5A6C, (s32)D_800A5A78, (s32)D_800A5A84,
    (s32)D_800A5A90,
};
s32 D_800A5AC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5ACC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B20[] = {
    0, (s32)D_800A5AC0, (s32)D_800A5ACC, (s32)D_800A5AD8,
    (s32)D_800A5AE4, (s32)D_800A5AF0, (s32)D_800A5AFC, (s32)D_800A5B08,
    (s32)D_800A5B14,
};
s32 D_800A5B44[] = {
    174, 10, 0x60080000,
};
s32 D_800A5B50[] = {
    174, 10, 0x60080000,
};
s32 D_800A5B5C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5B68[] = {
    170, 10, 0x60080000,
};
s32 D_800A5B74[] = {
    182, 10, 0x60080000,
};
s32 D_800A5B80[] = {
    182, 10, 0x60080000,
};
s32 D_800A5B8C[] = {
    71, 10, 0x60080000,
};
s32 D_800A5B98[] = {
    71, 10, 0x60080000,
};
s32 D_800A5BA4[] = {
    1, (s32)D_800A5B44, (s32)D_800A5B50, (s32)D_800A5B5C,
    (s32)D_800A5B68, (s32)D_800A5B74, (s32)D_800A5B80, (s32)D_800A5B8C,
    (s32)D_800A5B98,
};
s32 D_800A5BC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C28[] = {
    0, (s32)D_800A5BC8, (s32)D_800A5BD4, (s32)D_800A5BE0,
    (s32)D_800A5BEC, (s32)D_800A5BF8, (s32)D_800A5C04, (s32)D_800A5C10,
    (s32)D_800A5C1C,
};
s32 D_800A5C4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C58[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CAC[] = {
    0, (s32)D_800A5C4C, (s32)D_800A5C58, (s32)D_800A5C64,
    (s32)D_800A5C70, (s32)D_800A5C7C, (s32)D_800A5C88, (s32)D_800A5C94,
    (s32)D_800A5CA0,
};
s32 D_800A5CD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D30[] = {
    0, (s32)D_800A5CD0, (s32)D_800A5CDC, (s32)D_800A5CE8,
    (s32)D_800A5CF4, (s32)D_800A5D00, (s32)D_800A5D0C, (s32)D_800A5D18,
    (s32)D_800A5D24,
};
s32 D_800A5D54[] = {
    174, 10, 0x60080000,
};
s32 D_800A5D60[] = {
    174, 10, 0x60080000,
};
s32 D_800A5D6C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5D78[] = {
    170, 10, 0x60080000,
};
s32 D_800A5D84[] = {
    182, 10, 0x60080000,
};
s32 D_800A5D90[] = {
    182, 10, 0x60080000,
};
s32 D_800A5D9C[] = {
    71, 10, 0x60080000,
};
s32 D_800A5DA8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5DB4[] = {
    1, (s32)D_800A5D54, (s32)D_800A5D60, (s32)D_800A5D6C,
    (s32)D_800A5D78, (s32)D_800A5D84, (s32)D_800A5D90, (s32)D_800A5D9C,
    (s32)D_800A5DA8,
};
s32 D_800A5DD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E38[] = {
    0, (s32)D_800A5DD8, (s32)D_800A5DE4, (s32)D_800A5DF0,
    (s32)D_800A5DFC, (s32)D_800A5E08, (s32)D_800A5E14, (s32)D_800A5E20,
    (s32)D_800A5E2C,
};
s32 D_800A5E5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E74[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E80[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E98[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EBC[] = {
    0, (s32)D_800A5E5C, (s32)D_800A5E68, (s32)D_800A5E74,
    (s32)D_800A5E80, (s32)D_800A5E8C, (s32)D_800A5E98, (s32)D_800A5EA4,
    (s32)D_800A5EB0,
};
s32 D_800A5EE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F28[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F34[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F40[] = {
    0, (s32)D_800A5EE0, (s32)D_800A5EEC, (s32)D_800A5EF8,
    (s32)D_800A5F04, (s32)D_800A5F10, (s32)D_800A5F1C, (s32)D_800A5F28,
    (s32)D_800A5F34,
};
s32 D_800A5F64[] = {
    174, 10, 0x60080000,
};
s32 D_800A5F70[] = {
    170, 10, 0x60080000,
};
s32 D_800A5F7C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5F88[] = {
    110, 10, 0x60080000,
};
s32 D_800A5F94[] = {
    182, 10, 0x60080000,
};
s32 D_800A5FA0[] = {
    182, 10, 0x60080000,
};
s32 D_800A5FAC[] = {
    71, 10, 0x60080000,
};
s32 D_800A5FB8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5FC4[] = {
    1, (s32)D_800A5F64, (s32)D_800A5F70, (s32)D_800A5F7C,
    (s32)D_800A5F88, (s32)D_800A5F94, (s32)D_800A5FA0, (s32)D_800A5FAC,
    (s32)D_800A5FB8,
};
s32 D_800A5FE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6000[] = {
    0, 0, 0x60040000,
};
s32 D_800A600C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6018[] = {
    0, 0, 0x60040000,
};
s32 D_800A6024[] = {
    0, 0, 0x60040000,
};
s32 D_800A6030[] = {
    0, 0, 0x60040000,
};
s32 D_800A603C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6048[] = {
    0, (s32)D_800A5FE8, (s32)D_800A5FF4, (s32)D_800A6000,
    (s32)D_800A600C, (s32)D_800A6018, (s32)D_800A6024, (s32)D_800A6030,
    (s32)D_800A603C,
};
s32 D_800A606C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6078[] = {
    0, 0, 0x60040000,
};
s32 D_800A6084[] = {
    0, 0, 0x60040000,
};
s32 D_800A6090[] = {
    0, 0, 0x60040000,
};
s32 D_800A609C[] = {
    0, 0, 0x60040000,
};
s32 D_800A60A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A60B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A60C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A60CC[] = {
    0, (s32)D_800A606C, (s32)D_800A6078, (s32)D_800A6084,
    (s32)D_800A6090, (s32)D_800A609C, (s32)D_800A60A8, (s32)D_800A60B4,
    (s32)D_800A60C0,
};
s32 D_800A60F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A60FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6108[] = {
    0, 0, 0x60040000,
};
s32 D_800A6114[] = {
    0, 0, 0x60040000,
};
s32 D_800A6120[] = {
    0, 0, 0x60040000,
};
s32 D_800A612C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6138[] = {
    0, 0, 0x60040000,
};
s32 D_800A6144[] = {
    0, 0, 0x60040000,
};
s32 D_800A6150[] = {
    0, (s32)D_800A60F0, (s32)D_800A60FC, (s32)D_800A6108,
    (s32)D_800A6114, (s32)D_800A6120, (s32)D_800A612C, (s32)D_800A6138,
    (s32)D_800A6144,
};
s32 D_800A6174[] = {
    174, 10, 0x60080000,
};
s32 D_800A6180[] = {
    170, 10, 0x60080000,
};
s32 D_800A618C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6198[] = {
    110, 10, 0x60080000,
};
s32 D_800A61A4[] = {
    182, 10, 0x60080000,
};
s32 D_800A61B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A61BC[] = {
    71, 10, 0x60080000,
};
s32 D_800A61C8[] = {
    71, 10, 0x60080000,
};
s32 D_800A61D4[] = {
    1, (s32)D_800A6174, (s32)D_800A6180, (s32)D_800A618C,
    (s32)D_800A6198, (s32)D_800A61A4, (s32)D_800A61B0, (s32)D_800A61BC,
    (s32)D_800A61C8,
};
s32 D_800A61F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6204[] = {
    0, 0, 0x60040000,
};
s32 D_800A6210[] = {
    0, 0, 0x60040000,
};
s32 D_800A621C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6228[] = {
    0, 0, 0x60040000,
};
s32 D_800A6234[] = {
    0, 0, 0x60040000,
};
s32 D_800A6240[] = {
    0, 0, 0x60040000,
};
s32 D_800A624C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6258[] = {
    0, (s32)D_800A61F8, (s32)D_800A6204, (s32)D_800A6210,
    (s32)D_800A621C, (s32)D_800A6228, (s32)D_800A6234, (s32)D_800A6240,
    (s32)D_800A624C,
};
s32 D_800A627C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6288[] = {
    0, 0, 0x60040000,
};
s32 D_800A6294[] = {
    0, 0, 0x60040000,
};
s32 D_800A62A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A62B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A62D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62DC[] = {
    0, (s32)D_800A627C, (s32)D_800A6288, (s32)D_800A6294,
    (s32)D_800A62A0, (s32)D_800A62AC, (s32)D_800A62B8, (s32)D_800A62C4,
    (s32)D_800A62D0,
};
s32 D_800A6300[] = {
    0, 0, 0x60040000,
};
s32 D_800A630C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6318[] = {
    0, 0, 0x60040000,
};
s32 D_800A6324[] = {
    0, 0, 0x60040000,
};
s32 D_800A6330[] = {
    0, 0, 0x60040000,
};
s32 D_800A633C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6348[] = {
    0, 0, 0x60040000,
};
s32 D_800A6354[] = {
    0, 0, 0x60040000,
};
s32 D_800A6360[] = {
    0, (s32)D_800A6300, (s32)D_800A630C, (s32)D_800A6318,
    (s32)D_800A6324, (s32)D_800A6330, (s32)D_800A633C, (s32)D_800A6348,
    (s32)D_800A6354,
};
s32 D_800A6384[] = {
    110, 10, 0x60080000,
};
s32 D_800A6390[] = {
    110, 10, 0x60080000,
};
s32 D_800A639C[] = {
    110, 10, 0x60080000,
};
s32 D_800A63A8[] = {
    110, 10, 0x60080000,
};
s32 D_800A63B4[] = {
    182, 10, 0x60080000,
};
s32 D_800A63C0[] = {
    182, 10, 0x60080000,
};
s32 D_800A63CC[] = {
    182, 10, 0x60080000,
};
s32 D_800A63D8[] = {
    182, 10, 0x60080000,
};
s32 D_800A63E4[] = {
    1, (s32)D_800A6384, (s32)D_800A6390, (s32)D_800A639C,
    (s32)D_800A63A8, (s32)D_800A63B4, (s32)D_800A63C0, (s32)D_800A63CC,
    (s32)D_800A63D8,
};
s32 D_800A6408[] = {
    0, 0, 0x60040000,
};
s32 D_800A6414[] = {
    0, 0, 0x60040000,
};
s32 D_800A6420[] = {
    0, 0, 0x60040000,
};
s32 D_800A642C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6438[] = {
    0, 0, 0x60040000,
};
s32 D_800A6444[] = {
    0, 0, 0x60040000,
};
s32 D_800A6450[] = {
    0, 0, 0x60040000,
};
s32 D_800A645C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6468[] = {
    0, (s32)D_800A6408, (s32)D_800A6414, (s32)D_800A6420,
    (s32)D_800A642C, (s32)D_800A6438, (s32)D_800A6444, (s32)D_800A6450,
    (s32)D_800A645C,
};
s32 D_800A648C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6498[] = {
    0, 0, 0x60040000,
};
s32 D_800A64A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64EC[] = {
    0, (s32)D_800A648C, (s32)D_800A6498, (s32)D_800A64A4,
    (s32)D_800A64B0, (s32)D_800A64BC, (s32)D_800A64C8, (s32)D_800A64D4,
    (s32)D_800A64E0,
};
s32 D_800A6510[] = {
    0, 0, 0x60040000,
};
s32 D_800A651C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6528[] = {
    0, 0, 0x60040000,
};
s32 D_800A6534[] = {
    0, 0, 0x60040000,
};
s32 D_800A6540[] = {
    0, 0, 0x60040000,
};
s32 D_800A654C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6558[] = {
    0, 0, 0x60040000,
};
s32 D_800A6564[] = {
    0, 0, 0x60040000,
};
s32 D_800A6570[] = {
    0, (s32)D_800A6510, (s32)D_800A651C, (s32)D_800A6528,
    (s32)D_800A6534, (s32)D_800A6540, (s32)D_800A654C, (s32)D_800A6558,
    (s32)D_800A6564,
};
s32 D_800A6594[] = {
    182, 10, 0x60080000,
};
s32 D_800A65A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A65AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A65B8[] = {
    182, 10, 0x60080000,
};
s32 D_800A65C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A65D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A65DC[] = {
    71, 10, 0x60080000,
};
s32 D_800A65E8[] = {
    71, 10, 0x60080000,
};
s32 D_800A65F4[] = {
    1, (s32)D_800A6594, (s32)D_800A65A0, (s32)D_800A65AC,
    (s32)D_800A65B8, (s32)D_800A65C4, (s32)D_800A65D0, (s32)D_800A65DC,
    (s32)D_800A65E8,
};
s32 D_800A6618[] = {
    0, 0, 0x60040000,
};
s32 D_800A6624[] = {
    0, 0, 0x60040000,
};
s32 D_800A6630[] = {
    0, 0, 0x60040000,
};
s32 D_800A663C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6648[] = {
    0, 0, 0x60040000,
};
s32 D_800A6654[] = {
    0, 0, 0x60040000,
};
s32 D_800A6660[] = {
    0, 0, 0x60040000,
};
s32 D_800A666C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6678[] = {
    0, (s32)D_800A6618, (s32)D_800A6624, (s32)D_800A6630,
    (s32)D_800A663C, (s32)D_800A6648, (s32)D_800A6654, (s32)D_800A6660,
    (s32)D_800A666C,
};
s32 D_800A669C[] = {
    0, 0, 0x60040000,
};
s32 D_800A66A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A66C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A66F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66FC[] = {
    0, (s32)D_800A669C, (s32)D_800A66A8, (s32)D_800A66B4,
    (s32)D_800A66C0, (s32)D_800A66CC, (s32)D_800A66D8, (s32)D_800A66E4,
    (s32)D_800A66F0,
};
s32 D_800A6720[] = {
    0, 0, 0x60040000,
};
s32 D_800A672C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6738[] = {
    0, 0, 0x60040000,
};
s32 D_800A6744[] = {
    0, 0, 0x60040000,
};
s32 D_800A6750[] = {
    0, 0, 0x60040000,
};
s32 D_800A675C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6768[] = {
    0, 0, 0x60040000,
};
s32 D_800A6774[] = {
    0, 0, 0x60040000,
};
s32 D_800A6780[] = {
    0, (s32)D_800A6720, (s32)D_800A672C, (s32)D_800A6738,
    (s32)D_800A6744, (s32)D_800A6750, (s32)D_800A675C, (s32)D_800A6768,
    (s32)D_800A6774,
};
s32 D_800A67A4[] = {
    182, 10, 0x60080000,
};
s32 D_800A67B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A67BC[] = {
    182, 10, 0x60080000,
};
s32 D_800A67C8[] = {
    182, 10, 0x60080000,
};
s32 D_800A67D4[] = {
    71, 10, 0x60080000,
};
s32 D_800A67E0[] = {
    71, 10, 0x60080000,
};
s32 D_800A67EC[] = {
    71, 10, 0x60080000,
};
s32 D_800A67F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A6804[] = {
    1, (s32)D_800A67A4, (s32)D_800A67B0, (s32)D_800A67BC,
    (s32)D_800A67C8, (s32)D_800A67D4, (s32)D_800A67E0, (s32)D_800A67EC,
    (s32)D_800A67F8,
};
s32 D_800A6828[] = {
    0, 0, 0x60040000,
};
s32 D_800A6834[] = {
    0, 0, 0x60040000,
};
s32 D_800A6840[] = {
    0, 0, 0x60040000,
};
s32 D_800A684C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6858[] = {
    0, 0, 0x60040000,
};
s32 D_800A6864[] = {
    0, 0, 0x60040000,
};
s32 D_800A6870[] = {
    0, 0, 0x60040000,
};
s32 D_800A687C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6888[] = {
    0, (s32)D_800A6828, (s32)D_800A6834, (s32)D_800A6840,
    (s32)D_800A684C, (s32)D_800A6858, (s32)D_800A6864, (s32)D_800A6870,
    (s32)D_800A687C,
};
s32 D_800A68AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6900[] = {
    0, 0, 0x60040000,
};
s32 D_800A690C[] = {
    0, (s32)D_800A68AC, (s32)D_800A68B8, (s32)D_800A68C4,
    (s32)D_800A68D0, (s32)D_800A68DC, (s32)D_800A68E8, (s32)D_800A68F4,
    (s32)D_800A6900,
};
s32 D_800A6930[] = {
    0, 0, 0x60040000,
};
s32 D_800A693C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6948[] = {
    0, 0, 0x60040000,
};
s32 D_800A6954[] = {
    0, 0, 0x60040000,
};
s32 D_800A6960[] = {
    0, 0, 0x60040000,
};
s32 D_800A696C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6978[] = {
    0, 0, 0x60040000,
};
s32 D_800A6984[] = {
    0, 0, 0x60040000,
};
s32 D_800A6990[] = {
    0, (s32)D_800A6930, (s32)D_800A693C, (s32)D_800A6948,
    (s32)D_800A6954, (s32)D_800A6960, (s32)D_800A696C, (s32)D_800A6978,
    (s32)D_800A6984,
};
s32 D_800A69B4[] = {
    174, 10, 0x60080000,
};
s32 D_800A69C0[] = {
    174, 10, 0x60080000,
};
s32 D_800A69CC[] = {
    170, 10, 0x60080000,
};
s32 D_800A69D8[] = {
    170, 10, 0x60080000,
};
s32 D_800A69E4[] = {
    170, 10, 0x60080000,
};
s32 D_800A69F0[] = {
    110, 10, 0x60080000,
};
s32 D_800A69FC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6A08[] = {
    110, 10, 0x60080000,
};
s32 D_800A6A14[] = {
    2, (s32)D_800A69B4, (s32)D_800A69C0, (s32)D_800A69CC,
    (s32)D_800A69D8, (s32)D_800A69E4, (s32)D_800A69F0, (s32)D_800A69FC,
    (s32)D_800A6A08,
};
s32 D_800A6A38[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A44[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A98[] = {
    0, (s32)D_800A6A38, (s32)D_800A6A44, (s32)D_800A6A50,
    (s32)D_800A6A5C, (s32)D_800A6A68, (s32)D_800A6A74, (s32)D_800A6A80,
    (s32)D_800A6A8C,
};
s32 D_800A6ABC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B04[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B1C[] = {
    0, (s32)D_800A6ABC, (s32)D_800A6AC8, (s32)D_800A6AD4,
    (s32)D_800A6AE0, (s32)D_800A6AEC, (s32)D_800A6AF8, (s32)D_800A6B04,
    (s32)D_800A6B10,
};
s32 D_800A6B40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BA0[] = {
    0, (s32)D_800A6B40, (s32)D_800A6B4C, (s32)D_800A6B58,
    (s32)D_800A6B64, (s32)D_800A6B70, (s32)D_800A6B7C, (s32)D_800A6B88,
    (s32)D_800A6B94,
};
s32 D_800A6BC4[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BD0[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BDC[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BE8[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BF4[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C00[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C0C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C18[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C24[] = {
    2, (s32)D_800A6BC4, (s32)D_800A6BD0, (s32)D_800A6BDC,
    (s32)D_800A6BE8, (s32)D_800A6BF4, (s32)D_800A6C00, (s32)D_800A6C0C,
    (s32)D_800A6C18,
};
s32 D_800A6C48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CA8[] = {
    0, (s32)D_800A6C48, (s32)D_800A6C54, (s32)D_800A6C60,
    (s32)D_800A6C6C, (s32)D_800A6C78, (s32)D_800A6C84, (s32)D_800A6C90,
    (s32)D_800A6C9C,
};
s32 D_800A6CCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D2C[] = {
    0, (s32)D_800A6CCC, (s32)D_800A6CD8, (s32)D_800A6CE4,
    (s32)D_800A6CF0, (s32)D_800A6CFC, (s32)D_800A6D08, (s32)D_800A6D14,
    (s32)D_800A6D20,
};
s32 D_800A6D50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D98[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DB0[] = {
    0, (s32)D_800A6D50, (s32)D_800A6D5C, (s32)D_800A6D68,
    (s32)D_800A6D74, (s32)D_800A6D80, (s32)D_800A6D8C, (s32)D_800A6D98,
    (s32)D_800A6DA4,
};
s32 D_800A6DD4[] = {
    110, 10, 0x60080000,
};
s32 D_800A6DE0[] = {
    110, 10, 0x60080000,
};
s32 D_800A6DEC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6DF8[] = {
    110, 10, 0x60080000,
};
s32 D_800A6E04[] = {
    110, 10, 0x60080000,
};
s32 D_800A6E10[] = {
    110, 10, 0x60080000,
};
s32 D_800A6E1C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6E28[] = {
    110, 10, 0x60080000,
};
s32 D_800A6E34[] = {
    1, (s32)D_800A6DD4, (s32)D_800A6DE0, (s32)D_800A6DEC,
    (s32)D_800A6DF8, (s32)D_800A6E04, (s32)D_800A6E10, (s32)D_800A6E1C,
    (s32)D_800A6E28,
};
s32 D_800A6E58[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EB8[] = {
    0, (s32)D_800A6E58, (s32)D_800A6E64, (s32)D_800A6E70,
    (s32)D_800A6E7C, (s32)D_800A6E88, (s32)D_800A6E94, (s32)D_800A6EA0,
    (s32)D_800A6EAC,
};
s32 D_800A6EDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F18[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F24[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F30[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F3C[] = {
    0, (s32)D_800A6EDC, (s32)D_800A6EE8, (s32)D_800A6EF4,
    (s32)D_800A6F00, (s32)D_800A6F0C, (s32)D_800A6F18, (s32)D_800A6F24,
    (s32)D_800A6F30,
};
s32 D_800A6F60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FC0[] = {
    0, (s32)D_800A6F60, (s32)D_800A6F6C, (s32)D_800A6F78,
    (s32)D_800A6F84, (s32)D_800A6F90, (s32)D_800A6F9C, (s32)D_800A6FA8,
    (s32)D_800A6FB4,
};
s32 D_800A6FE4[] = {
    182, 10, 0x60080000,
};
s32 D_800A6FF0[] = {
    182, 10, 0x60080000,
};
s32 D_800A6FFC[] = {
    182, 10, 0x60080000,
};
s32 D_800A7008[] = {
    182, 10, 0x60080000,
};
s32 D_800A7014[] = {
    71, 10, 0x60080000,
};
s32 D_800A7020[] = {
    71, 10, 0x60080000,
};
s32 D_800A702C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7038[] = {
    71, 10, 0x60080000,
};
s32 D_800A7044[] = {
    1, (s32)D_800A6FE4, (s32)D_800A6FF0, (s32)D_800A6FFC,
    (s32)D_800A7008, (s32)D_800A7014, (s32)D_800A7020, (s32)D_800A702C,
    (s32)D_800A7038,
};
s32 D_800A7068[] = {
    0, 0, 0x60040000,
};
s32 D_800A7074[] = {
    0, 0, 0x60040000,
};
s32 D_800A7080[] = {
    0, 0, 0x60040000,
};
s32 D_800A708C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7098[] = {
    0, 0, 0x60040000,
};
s32 D_800A70A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A70B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A70BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A70C8[] = {
    0, (s32)D_800A7068, (s32)D_800A7074, (s32)D_800A7080,
    (s32)D_800A708C, (s32)D_800A7098, (s32)D_800A70A4, (s32)D_800A70B0,
    (s32)D_800A70BC,
};
s32 D_800A70EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A70F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7104[] = {
    0, 0, 0x60040000,
};
s32 D_800A7110[] = {
    0, 0, 0x60040000,
};
s32 D_800A711C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7128[] = {
    0, 0, 0x60040000,
};
s32 D_800A7134[] = {
    0, 0, 0x60040000,
};
s32 D_800A7140[] = {
    0, 0, 0x60040000,
};
s32 D_800A714C[] = {
    0, (s32)D_800A70EC, (s32)D_800A70F8, (s32)D_800A7104,
    (s32)D_800A7110, (s32)D_800A711C, (s32)D_800A7128, (s32)D_800A7134,
    (s32)D_800A7140,
};
s32 D_800A7170[] = {
    0, 0, 0x60040000,
};
s32 D_800A717C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7188[] = {
    0, 0, 0x60040000,
};
s32 D_800A7194[] = {
    0, 0, 0x60040000,
};
s32 D_800A71A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A71AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A71B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A71C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A71D0[] = {
    0, (s32)D_800A7170, (s32)D_800A717C, (s32)D_800A7188,
    (s32)D_800A7194, (s32)D_800A71A0, (s32)D_800A71AC, (s32)D_800A71B8,
    (s32)D_800A71C4,
};
s32 D_800A71F4[] = {
    174, 10, 0x60080000,
};
s32 D_800A7200[] = {
    174, 10, 0x60080000,
};
s32 D_800A720C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7218[] = {
    170, 10, 0x60080000,
};
s32 D_800A7224[] = {
    170, 10, 0x60080000,
};
s32 D_800A7230[] = {
    170, 10, 0x60080000,
};
s32 D_800A723C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7248[] = {
    170, 10, 0x60080000,
};
s32 D_800A7254[] = {
    5, (s32)D_800A71F4, (s32)D_800A7200, (s32)D_800A720C,
    (s32)D_800A7218, (s32)D_800A7224, (s32)D_800A7230, (s32)D_800A723C,
    (s32)D_800A7248,
};
s32 D_800A7278[] = {
    0, 0, 0x60040000,
};
s32 D_800A7284[] = {
    0, 0, 0x60040000,
};
s32 D_800A7290[] = {
    0, 0, 0x60040000,
};
s32 D_800A729C[] = {
    0, 0, 0x60040000,
};
s32 D_800A72A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A72B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A72C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A72CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A72D8[] = {
    0, (s32)D_800A7278, (s32)D_800A7284, (s32)D_800A7290,
    (s32)D_800A729C, (s32)D_800A72A8, (s32)D_800A72B4, (s32)D_800A72C0,
    (s32)D_800A72CC,
};
s32 D_800A72FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7308[] = {
    0, 0, 0x60040000,
};
s32 D_800A7314[] = {
    0, 0, 0x60040000,
};
s32 D_800A7320[] = {
    0, 0, 0x60040000,
};
s32 D_800A732C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7338[] = {
    0, 0, 0x60040000,
};
s32 D_800A7344[] = {
    0, 0, 0x60040000,
};
s32 D_800A7350[] = {
    0, 0, 0x60040000,
};
s32 D_800A735C[] = {
    0, (s32)D_800A72FC, (s32)D_800A7308, (s32)D_800A7314,
    (s32)D_800A7320, (s32)D_800A732C, (s32)D_800A7338, (s32)D_800A7344,
    (s32)D_800A7350,
};
s32 D_800A7380[] = {
    0, 0, 0x60040000,
};
s32 D_800A738C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7398[] = {
    0, 0, 0x60040000,
};
s32 D_800A73A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A73B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A73BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A73C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A73D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A73E0[] = {
    0, (s32)D_800A7380, (s32)D_800A738C, (s32)D_800A7398,
    (s32)D_800A73A4, (s32)D_800A73B0, (s32)D_800A73BC, (s32)D_800A73C8,
    (s32)D_800A73D4,
};
s32 D_800A7404[] = {
    174, 10, 0x60080000,
};
s32 D_800A7410[] = {
    174, 10, 0x60080000,
};
s32 D_800A741C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7428[] = {
    170, 10, 0x60080000,
};
s32 D_800A7434[] = {
    170, 10, 0x60080000,
};
s32 D_800A7440[] = {
    170, 10, 0x60080000,
};
s32 D_800A744C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7458[] = {
    170, 10, 0x60080000,
};
s32 D_800A7464[] = {
    4, (s32)D_800A7404, (s32)D_800A7410, (s32)D_800A741C,
    (s32)D_800A7428, (s32)D_800A7434, (s32)D_800A7440, (s32)D_800A744C,
    (s32)D_800A7458,
};
s32 D_800A7488[] = {
    0, 0, 0x60040000,
};
s32 D_800A7494[] = {
    0, 0, 0x60040000,
};
s32 D_800A74A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A74B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A74D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A74E8[] = {
    0, (s32)D_800A7488, (s32)D_800A7494, (s32)D_800A74A0,
    (s32)D_800A74AC, (s32)D_800A74B8, (s32)D_800A74C4, (s32)D_800A74D0,
    (s32)D_800A74DC,
};
s32 D_800A750C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7518[] = {
    0, 0, 0x60040000,
};
s32 D_800A7524[] = {
    0, 0, 0x60040000,
};
s32 D_800A7530[] = {
    0, 0, 0x60040000,
};
s32 D_800A753C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7548[] = {
    0, 0, 0x60040000,
};
s32 D_800A7554[] = {
    0, 0, 0x60040000,
};
s32 D_800A7560[] = {
    0, 0, 0x60040000,
};
s32 D_800A756C[] = {
    0, (s32)D_800A750C, (s32)D_800A7518, (s32)D_800A7524,
    (s32)D_800A7530, (s32)D_800A753C, (s32)D_800A7548, (s32)D_800A7554,
    (s32)D_800A7560,
};
s32 D_800A7590[] = {
    0, 0, 0x60040000,
};
s32 D_800A759C[] = {
    0, 0, 0x60040000,
};
s32 D_800A75A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A75B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A75C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A75D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A75E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A75F0[] = {
    0, (s32)D_800A7590, (s32)D_800A759C, (s32)D_800A75A8,
    (s32)D_800A75B4, (s32)D_800A75C0, (s32)D_800A75CC, (s32)D_800A75D8,
    (s32)D_800A75E4,
};
s32 D_800A7614[] = {
    174, 10, 0x60080000,
};
s32 D_800A7620[] = {
    174, 10, 0x60080000,
};
s32 D_800A762C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7638[] = {
    170, 10, 0x60080000,
};
s32 D_800A7644[] = {
    170, 10, 0x60080000,
};
s32 D_800A7650[] = {
    170, 10, 0x60080000,
};
s32 D_800A765C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7668[] = {
    170, 10, 0x60080000,
};
s32 D_800A7674[] = {
    5, (s32)D_800A7614, (s32)D_800A7620, (s32)D_800A762C,
    (s32)D_800A7638, (s32)D_800A7644, (s32)D_800A7650, (s32)D_800A765C,
    (s32)D_800A7668,
};
s32 D_800A7698[] = {
    0, 0, 0x60040000,
};
s32 D_800A76A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A76B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A76BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A76C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A76D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A76E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A76EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A76F8[] = {
    0, (s32)D_800A7698, (s32)D_800A76A4, (s32)D_800A76B0,
    (s32)D_800A76BC, (s32)D_800A76C8, (s32)D_800A76D4, (s32)D_800A76E0,
    (s32)D_800A76EC,
};
s32 D_800A771C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7728[] = {
    0, 0, 0x60040000,
};
s32 D_800A7734[] = {
    0, 0, 0x60040000,
};
s32 D_800A7740[] = {
    0, 0, 0x60040000,
};
s32 D_800A774C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7758[] = {
    0, 0, 0x60040000,
};
s32 D_800A7764[] = {
    0, 0, 0x60040000,
};
s32 D_800A7770[] = {
    0, 0, 0x60040000,
};
s32 D_800A777C[] = {
    0, (s32)D_800A771C, (s32)D_800A7728, (s32)D_800A7734,
    (s32)D_800A7740, (s32)D_800A774C, (s32)D_800A7758, (s32)D_800A7764,
    (s32)D_800A7770,
};
s32 D_800A77A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A77B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A77C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A77D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A77E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A77F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7800[] = {
    0, (s32)D_800A77A0, (s32)D_800A77AC, (s32)D_800A77B8,
    (s32)D_800A77C4, (s32)D_800A77D0, (s32)D_800A77DC, (s32)D_800A77E8,
    (s32)D_800A77F4,
};
s32 D_800A7824[] = {
    182, 10, 0x60080000,
};
s32 D_800A7830[] = {
    182, 10, 0x60080000,
};
s32 D_800A783C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7848[] = {
    182, 10, 0x60080000,
};
s32 D_800A7854[] = {
    71, 10, 0x60080000,
};
s32 D_800A7860[] = {
    71, 10, 0x60080000,
};
s32 D_800A786C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7878[] = {
    71, 10, 0x60080000,
};
s32 D_800A7884[] = {
    5, (s32)D_800A7824, (s32)D_800A7830, (s32)D_800A783C,
    (s32)D_800A7848, (s32)D_800A7854, (s32)D_800A7860, (s32)D_800A786C,
    (s32)D_800A7878,
};
s32 D_800A78A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A78B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A78C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A78CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A78D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A78E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A78F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A78FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7908[] = {
    0, (s32)D_800A78A8, (s32)D_800A78B4, (s32)D_800A78C0,
    (s32)D_800A78CC, (s32)D_800A78D8, (s32)D_800A78E4, (s32)D_800A78F0,
    (s32)D_800A78FC,
};
s32 D_800A792C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7938[] = {
    0, 0, 0x60040000,
};
s32 D_800A7944[] = {
    0, 0, 0x60040000,
};
s32 D_800A7950[] = {
    0, 0, 0x60040000,
};
s32 D_800A795C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7968[] = {
    0, 0, 0x60040000,
};
s32 D_800A7974[] = {
    0, 0, 0x60040000,
};
s32 D_800A7980[] = {
    0, 0, 0x60040000,
};
s32 D_800A798C[] = {
    0, (s32)D_800A792C, (s32)D_800A7938, (s32)D_800A7944,
    (s32)D_800A7950, (s32)D_800A795C, (s32)D_800A7968, (s32)D_800A7974,
    (s32)D_800A7980,
};
s32 D_800A79B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A79C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A79D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A79E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A79F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A10[] = {
    0, (s32)D_800A79B0, (s32)D_800A79BC, (s32)D_800A79C8,
    (s32)D_800A79D4, (s32)D_800A79E0, (s32)D_800A79EC, (s32)D_800A79F8,
    (s32)D_800A7A04,
};
s32 D_800A7A34[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A40[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A4C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A58[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A64[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A70[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A7C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A88[] = {
    110, 10, 0x60080000,
};
s32 D_800A7A94[] = {
    1, (s32)D_800A7A34, (s32)D_800A7A40, (s32)D_800A7A4C,
    (s32)D_800A7A58, (s32)D_800A7A64, (s32)D_800A7A70, (s32)D_800A7A7C,
    (s32)D_800A7A88,
};
s32 D_800A7AB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7ADC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B00[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B18[] = {
    0, (s32)D_800A7AB8, (s32)D_800A7AC4, (s32)D_800A7AD0,
    (s32)D_800A7ADC, (s32)D_800A7AE8, (s32)D_800A7AF4, (s32)D_800A7B00,
    (s32)D_800A7B0C,
};
s32 D_800A7B3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B48[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B54[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B60[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B78[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B84[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B90[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B9C[] = {
    0, (s32)D_800A7B3C, (s32)D_800A7B48, (s32)D_800A7B54,
    (s32)D_800A7B60, (s32)D_800A7B6C, (s32)D_800A7B78, (s32)D_800A7B84,
    (s32)D_800A7B90,
};
s32 D_800A7BC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C08[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C14[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C20[] = {
    0, (s32)D_800A7BC0, (s32)D_800A7BCC, (s32)D_800A7BD8,
    (s32)D_800A7BE4, (s32)D_800A7BF0, (s32)D_800A7BFC, (s32)D_800A7C08,
    (s32)D_800A7C14,
};
s32 D_800A7C44[] = {
    182, 10, 0x60080000,
};
s32 D_800A7C50[] = {
    182, 10, 0x60080000,
};
s32 D_800A7C5C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7C68[] = {
    182, 10, 0x60080000,
};
s32 D_800A7C74[] = {
    71, 10, 0x60080000,
};
s32 D_800A7C80[] = {
    71, 10, 0x60080000,
};
s32 D_800A7C8C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7C98[] = {
    71, 10, 0x60080000,
};
s32 D_800A7CA4[] = {
    1, (s32)D_800A7C44, (s32)D_800A7C50, (s32)D_800A7C5C,
    (s32)D_800A7C68, (s32)D_800A7C74, (s32)D_800A7C80, (s32)D_800A7C8C,
    (s32)D_800A7C98,
};
s32 D_800A7CC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D10[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D28[] = {
    0, (s32)D_800A7CC8, (s32)D_800A7CD4, (s32)D_800A7CE0,
    (s32)D_800A7CEC, (s32)D_800A7CF8, (s32)D_800A7D04, (s32)D_800A7D10,
    (s32)D_800A7D1C,
};
s32 D_800A7D4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D58[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D64[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D88[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D94[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DAC[] = {
    0, (s32)D_800A7D4C, (s32)D_800A7D58, (s32)D_800A7D64,
    (s32)D_800A7D70, (s32)D_800A7D7C, (s32)D_800A7D88, (s32)D_800A7D94,
    (s32)D_800A7DA0,
};
s32 D_800A7DD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E00[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E18[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E24[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E30[] = {
    0, (s32)D_800A7DD0, (s32)D_800A7DDC, (s32)D_800A7DE8,
    (s32)D_800A7DF4, (s32)D_800A7E00, (s32)D_800A7E0C, (s32)D_800A7E18,
    (s32)D_800A7E24,
};
s32 D_800A7E54[] = {
    110, 10, 0x60080000,
};
s32 D_800A7E60[] = {
    110, 10, 0x60080000,
};
s32 D_800A7E6C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7E78[] = {
    110, 10, 0x60080000,
};
s32 D_800A7E84[] = {
    110, 10, 0x60080000,
};
s32 D_800A7E90[] = {
    110, 10, 0x60080000,
};
s32 D_800A7E9C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7EA8[] = {
    110, 10, 0x60080000,
};
s32 D_800A7EB4[] = {
    3, (s32)D_800A7E54, (s32)D_800A7E60, (s32)D_800A7E6C,
    (s32)D_800A7E78, (s32)D_800A7E84, (s32)D_800A7E90, (s32)D_800A7E9C,
    (s32)D_800A7EA8,
};
s32 D_800A7ED8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F08[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F14[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F20[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F38[] = {
    0, (s32)D_800A7ED8, (s32)D_800A7EE4, (s32)D_800A7EF0,
    (s32)D_800A7EFC, (s32)D_800A7F08, (s32)D_800A7F14, (s32)D_800A7F20,
    (s32)D_800A7F2C,
};
s32 D_800A7F5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F68[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F74[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F80[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F98[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FBC[] = {
    0, (s32)D_800A7F5C, (s32)D_800A7F68, (s32)D_800A7F74,
    (s32)D_800A7F80, (s32)D_800A7F8C, (s32)D_800A7F98, (s32)D_800A7FA4,
    (s32)D_800A7FB0,
};
s32 D_800A7FE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8004[] = {
    0, 0, 0x60040000,
};
s32 D_800A8010[] = {
    0, 0, 0x60040000,
};
s32 D_800A801C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8028[] = {
    0, 0, 0x60040000,
};
s32 D_800A8034[] = {
    0, 0, 0x60040000,
};
s32 D_800A8040[] = {
    0, (s32)D_800A7FE0, (s32)D_800A7FEC, (s32)D_800A7FF8,
    (s32)D_800A8004, (s32)D_800A8010, (s32)D_800A801C, (s32)D_800A8028,
    (s32)D_800A8034,
};
s32 D_800A8064[] = {
    110, 10, 0x60080000,
};
s32 D_800A8070[] = {
    110, 10, 0x60080000,
};
s32 D_800A807C[] = {
    110, 10, 0x60080000,
};
s32 D_800A8088[] = {
    110, 10, 0x60080000,
};
s32 D_800A8094[] = {
    110, 10, 0x60080000,
};
s32 D_800A80A0[] = {
    110, 10, 0x60080000,
};
s32 D_800A80AC[] = {
    110, 10, 0x60080000,
};
s32 D_800A80B8[] = {
    110, 10, 0x60080000,
};
s32 D_800A80C4[] = {
    3, (s32)D_800A8064, (s32)D_800A8070, (s32)D_800A807C,
    (s32)D_800A8088, (s32)D_800A8094, (s32)D_800A80A0, (s32)D_800A80AC,
    (s32)D_800A80B8,
};
s32 D_800A80E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A80F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8100[] = {
    0, 0, 0x60040000,
};
s32 D_800A810C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8118[] = {
    0, 0, 0x60040000,
};
s32 D_800A8124[] = {
    0, 0, 0x60040000,
};
s32 D_800A8130[] = {
    0, 0, 0x60040000,
};
s32 D_800A813C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8148[] = {
    0, (s32)D_800A80E8, (s32)D_800A80F4, (s32)D_800A8100,
    (s32)D_800A810C, (s32)D_800A8118, (s32)D_800A8124, (s32)D_800A8130,
    (s32)D_800A813C,
};
s32 D_800A816C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8178[] = {
    0, 0, 0x60040000,
};
s32 D_800A8184[] = {
    0, 0, 0x60040000,
};
s32 D_800A8190[] = {
    0, 0, 0x60040000,
};
s32 D_800A819C[] = {
    0, 0, 0x60040000,
};
s32 D_800A81A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A81B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A81C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A81CC[] = {
    0, (s32)D_800A816C, (s32)D_800A8178, (s32)D_800A8184,
    (s32)D_800A8190, (s32)D_800A819C, (s32)D_800A81A8, (s32)D_800A81B4,
    (s32)D_800A81C0,
};
s32 D_800A81F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A81FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8208[] = {
    0, 0, 0x60040000,
};
s32 D_800A8214[] = {
    0, 0, 0x60040000,
};
s32 D_800A8220[] = {
    0, 0, 0x60040000,
};
s32 D_800A822C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8238[] = {
    0, 0, 0x60040000,
};
s32 D_800A8244[] = {
    0, 0, 0x60040000,
};
s32 D_800A8250[] = {
    0, (s32)D_800A81F0, (s32)D_800A81FC, (s32)D_800A8208,
    (s32)D_800A8214, (s32)D_800A8220, (s32)D_800A822C, (s32)D_800A8238,
    (s32)D_800A8244,
};
s32 D_800A8274[] = {
    182, 10, 0x60080000,
};
s32 D_800A8280[] = {
    182, 10, 0x60080000,
};
s32 D_800A828C[] = {
    182, 10, 0x60080000,
};
s32 D_800A8298[] = {
    182, 10, 0x60080000,
};
s32 D_800A82A4[] = {
    71, 10, 0x60080000,
};
s32 D_800A82B0[] = {
    71, 10, 0x60080000,
};
s32 D_800A82BC[] = {
    71, 10, 0x60080000,
};
s32 D_800A82C8[] = {
    71, 10, 0x60080000,
};
s32 D_800A82D4[] = {
    2, (s32)D_800A8274, (s32)D_800A8280, (s32)D_800A828C,
    (s32)D_800A8298, (s32)D_800A82A4, (s32)D_800A82B0, (s32)D_800A82BC,
    (s32)D_800A82C8,
};
s32 D_800A82F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8304[] = {
    0, 0, 0x60040000,
};
s32 D_800A8310[] = {
    0, 0, 0x60040000,
};
s32 D_800A831C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8328[] = {
    0, 0, 0x60040000,
};
s32 D_800A8334[] = {
    0, 0, 0x60040000,
};
s32 D_800A8340[] = {
    0, 0, 0x60040000,
};
s32 D_800A834C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8358[] = {
    0, (s32)D_800A82F8, (s32)D_800A8304, (s32)D_800A8310,
    (s32)D_800A831C, (s32)D_800A8328, (s32)D_800A8334, (s32)D_800A8340,
    (s32)D_800A834C,
};
s32 D_800A837C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8388[] = {
    0, 0, 0x60040000,
};
s32 D_800A8394[] = {
    0, 0, 0x60040000,
};
s32 D_800A83A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A83AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A83B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A83C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A83D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A83DC[] = {
    0, (s32)D_800A837C, (s32)D_800A8388, (s32)D_800A8394,
    (s32)D_800A83A0, (s32)D_800A83AC, (s32)D_800A83B8, (s32)D_800A83C4,
    (s32)D_800A83D0,
};
s32 D_800A8400[] = {
    0, 0, 0x60040000,
};
s32 D_800A840C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8418[] = {
    0, 0, 0x60040000,
};
s32 D_800A8424[] = {
    0, 0, 0x60040000,
};
s32 D_800A8430[] = {
    0, 0, 0x60040000,
};
s32 D_800A843C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8448[] = {
    0, 0, 0x60040000,
};
s32 D_800A8454[] = {
    0, 0, 0x60040000,
};
s32 D_800A8460[] = {
    0, (s32)D_800A8400, (s32)D_800A840C, (s32)D_800A8418,
    (s32)D_800A8424, (s32)D_800A8430, (s32)D_800A843C, (s32)D_800A8448,
    (s32)D_800A8454,
};
s32 D_800A8484[] = {
    182, 10, 0x60080000,
};
s32 D_800A8490[] = {
    182, 10, 0x60080000,
};
s32 D_800A849C[] = {
    182, 10, 0x60080000,
};
s32 D_800A84A8[] = {
    182, 10, 0x60080000,
};
s32 D_800A84B4[] = {
    71, 10, 0x60080000,
};
s32 D_800A84C0[] = {
    71, 10, 0x60080000,
};
s32 D_800A84CC[] = {
    71, 10, 0x60080000,
};
s32 D_800A84D8[] = {
    71, 10, 0x60080000,
};
s32 D_800A84E4[] = {
    5, (s32)D_800A8484, (s32)D_800A8490, (s32)D_800A849C,
    (s32)D_800A84A8, (s32)D_800A84B4, (s32)D_800A84C0, (s32)D_800A84CC,
    (s32)D_800A84D8,
};
s32 D_800A8508[] = {
    0, 0, 0x60040000,
};
s32 D_800A8514[] = {
    0, 0, 0x60040000,
};
s32 D_800A8520[] = {
    0, 0, 0x60040000,
};
s32 D_800A852C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8538[] = {
    0, 0, 0x60040000,
};
s32 D_800A8544[] = {
    0, 0, 0x60040000,
};
s32 D_800A8550[] = {
    0, 0, 0x60040000,
};
s32 D_800A855C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8568[] = {
    0, (s32)D_800A8508, (s32)D_800A8514, (s32)D_800A8520,
    (s32)D_800A852C, (s32)D_800A8538, (s32)D_800A8544, (s32)D_800A8550,
    (s32)D_800A855C,
};
s32 D_800A858C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8598[] = {
    0, 0, 0x60040000,
};
s32 D_800A85A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A85B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A85BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A85C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A85D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A85E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A85EC[] = {
    0, (s32)D_800A858C, (s32)D_800A8598, (s32)D_800A85A4,
    (s32)D_800A85B0, (s32)D_800A85BC, (s32)D_800A85C8, (s32)D_800A85D4,
    (s32)D_800A85E0,
};
s32 D_800A8610[] = {
    0, 0, 0x60040000,
};
s32 D_800A861C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8628[] = {
    0, 0, 0x60040000,
};
s32 D_800A8634[] = {
    0, 0, 0x60040000,
};
s32 D_800A8640[] = {
    0, 0, 0x60040000,
};
s32 D_800A864C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8658[] = {
    0, 0, 0x60040000,
};
s32 D_800A8664[] = {
    0, 0, 0x60040000,
};
s32 D_800A8670[] = {
    0, (s32)D_800A8610, (s32)D_800A861C, (s32)D_800A8628,
    (s32)D_800A8634, (s32)D_800A8640, (s32)D_800A864C, (s32)D_800A8658,
    (s32)D_800A8664,
};
s32 D_800A8694[] = {
    182, 10, 0x60080000,
};
s32 D_800A86A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A86AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A86B8[] = {
    182, 10, 0x60080000,
};
s32 D_800A86C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A86D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A86DC[] = {
    71, 10, 0x60080000,
};
s32 D_800A86E8[] = {
    71, 10, 0x60080000,
};
s32 D_800A86F4[] = {
    4, (s32)D_800A8694, (s32)D_800A86A0, (s32)D_800A86AC,
    (s32)D_800A86B8, (s32)D_800A86C4, (s32)D_800A86D0, (s32)D_800A86DC,
    (s32)D_800A86E8,
};
s32 D_800A8718[] = {
    0, 0, 0x60040000,
};
s32 D_800A8724[] = {
    0, 0, 0x60040000,
};
s32 D_800A8730[] = {
    0, 0, 0x60040000,
};
s32 D_800A873C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8748[] = {
    0, 0, 0x60040000,
};
s32 D_800A8754[] = {
    0, 0, 0x60040000,
};
s32 D_800A8760[] = {
    0, 0, 0x60040000,
};
s32 D_800A876C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8778[] = {
    0, (s32)D_800A8718, (s32)D_800A8724, (s32)D_800A8730,
    (s32)D_800A873C, (s32)D_800A8748, (s32)D_800A8754, (s32)D_800A8760,
    (s32)D_800A876C,
};
s32 D_800A879C[] = {
    0, 0, 0x60040000,
};
s32 D_800A87A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A87B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A87C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A87CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A87D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A87E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A87F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A87FC[] = {
    0, (s32)D_800A879C, (s32)D_800A87A8, (s32)D_800A87B4,
    (s32)D_800A87C0, (s32)D_800A87CC, (s32)D_800A87D8, (s32)D_800A87E4,
    (s32)D_800A87F0,
};
s32 D_800A8820[] = {
    0, 0, 0x60040000,
};
s32 D_800A882C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8838[] = {
    0, 0, 0x60040000,
};
s32 D_800A8844[] = {
    0, 0, 0x60040000,
};
s32 D_800A8850[] = {
    0, 0, 0x60040000,
};
s32 D_800A885C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8868[] = {
    0, 0, 0x60040000,
};
s32 D_800A8874[] = {
    0, 0, 0x60040000,
};
s32 D_800A8880[] = {
    0, (s32)D_800A8820, (s32)D_800A882C, (s32)D_800A8838,
    (s32)D_800A8844, (s32)D_800A8850, (s32)D_800A885C, (s32)D_800A8868,
    (s32)D_800A8874,
};
s32 D_800A88A4[] = {
    182, 10, 0x60080000,
};
s32 D_800A88B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A88BC[] = {
    182, 10, 0x60080000,
};
s32 D_800A88C8[] = {
    182, 10, 0x60080000,
};
s32 D_800A88D4[] = {
    71, 10, 0x60080000,
};
s32 D_800A88E0[] = {
    71, 10, 0x60080000,
};
s32 D_800A88EC[] = {
    71, 10, 0x60080000,
};
s32 D_800A88F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A8904[] = {
    5, (s32)D_800A88A4, (s32)D_800A88B0, (s32)D_800A88BC,
    (s32)D_800A88C8, (s32)D_800A88D4, (s32)D_800A88E0, (s32)D_800A88EC,
    (s32)D_800A88F8,
};
s32 D_800A8928[] = {
    0, 0, 0x60040000,
};
s32 D_800A8934[] = {
    0, 0, 0x60040000,
};
s32 D_800A8940[] = {
    0, 0, 0x60040000,
};
s32 D_800A894C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8958[] = {
    0, 0, 0x60040000,
};
s32 D_800A8964[] = {
    0, 0, 0x60040000,
};
s32 D_800A8970[] = {
    0, 0, 0x60040000,
};
s32 D_800A897C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8988[] = {
    0, (s32)D_800A8928, (s32)D_800A8934, (s32)D_800A8940,
    (s32)D_800A894C, (s32)D_800A8958, (s32)D_800A8964, (s32)D_800A8970,
    (s32)D_800A897C,
};
s32 D_800A89AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A89B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A89C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A89D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A89DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A89E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A89F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A00[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A0C[] = {
    0, (s32)D_800A89AC, (s32)D_800A89B8, (s32)D_800A89C4,
    (s32)D_800A89D0, (s32)D_800A89DC, (s32)D_800A89E8, (s32)D_800A89F4,
    (s32)D_800A8A00,
};
s32 D_800A8A30[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A48[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A54[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A60[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A78[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A84[] = {
    0, 0, 0x60040000,
};
s32 D_800A8A90[] = {
    0, (s32)D_800A8A30, (s32)D_800A8A3C, (s32)D_800A8A48,
    (s32)D_800A8A54, (s32)D_800A8A60, (s32)D_800A8A6C, (s32)D_800A8A78,
    (s32)D_800A8A84,
};
s32 D_800A8AB4[] = {
    182, 10, 0x60080000,
};
s32 D_800A8AC0[] = {
    182, 10, 0x60080000,
};
s32 D_800A8ACC[] = {
    182, 10, 0x60080000,
};
s32 D_800A8AD8[] = {
    182, 10, 0x60080000,
};
s32 D_800A8AE4[] = {
    71, 10, 0x60080000,
};
s32 D_800A8AF0[] = {
    71, 10, 0x60080000,
};
s32 D_800A8AFC[] = {
    71, 10, 0x60080000,
};
s32 D_800A8B08[] = {
    71, 10, 0x60080000,
};
s32 D_800A8B14[] = {
    1, (s32)D_800A8AB4, (s32)D_800A8AC0, (s32)D_800A8ACC,
    (s32)D_800A8AD8, (s32)D_800A8AE4, (s32)D_800A8AF0, (s32)D_800A8AFC,
    (s32)D_800A8B08,
};
s32 D_800A8B38[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B44[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B50[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B68[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B74[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B80[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8B98[] = {
    0, (s32)D_800A8B38, (s32)D_800A8B44, (s32)D_800A8B50,
    (s32)D_800A8B5C, (s32)D_800A8B68, (s32)D_800A8B74, (s32)D_800A8B80,
    (s32)D_800A8B8C,
};
s32 D_800A8BBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8BC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8BD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8BE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A8BEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8BF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C04[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C10[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C1C[] = {
    0, (s32)D_800A8BBC, (s32)D_800A8BC8, (s32)D_800A8BD4,
    (s32)D_800A8BE0, (s32)D_800A8BEC, (s32)D_800A8BF8, (s32)D_800A8C04,
    (s32)D_800A8C10,
};
s32 D_800A8C40[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C58[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C64[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C70[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C88[] = {
    0, 0, 0x60040000,
};
s32 D_800A8C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A8CA0[] = {
    0, (s32)D_800A8C40, (s32)D_800A8C4C, (s32)D_800A8C58,
    (s32)D_800A8C64, (s32)D_800A8C70, (s32)D_800A8C7C, (s32)D_800A8C88,
    (s32)D_800A8C94,
};
s32 D_800A8CC4[] = {
    182, 10, 0x60080000,
};
s32 D_800A8CD0[] = {
    182, 10, 0x60080000,
};
s32 D_800A8CDC[] = {
    182, 10, 0x60080000,
};
s32 D_800A8CE8[] = {
    182, 10, 0x60080000,
};
s32 D_800A8CF4[] = {
    71, 10, 0x60080000,
};
s32 D_800A8D00[] = {
    71, 10, 0x60080000,
};
s32 D_800A8D0C[] = {
    71, 10, 0x60080000,
};
s32 D_800A8D18[] = {
    71, 10, 0x60080000,
};
s32 D_800A8D24[] = {
    1, (s32)D_800A8CC4, (s32)D_800A8CD0, (s32)D_800A8CDC,
    (s32)D_800A8CE8, (s32)D_800A8CF4, (s32)D_800A8D00, (s32)D_800A8D0C,
    (s32)D_800A8D18,
};
s32 D_800A8D48[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D60[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D78[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D84[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D90[] = {
    0, 0, 0x60040000,
};
s32 D_800A8D9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8DA8[] = {
    0, (s32)D_800A8D48, (s32)D_800A8D54, (s32)D_800A8D60,
    (s32)D_800A8D6C, (s32)D_800A8D78, (s32)D_800A8D84, (s32)D_800A8D90,
    (s32)D_800A8D9C,
};
s32 D_800A8DCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8DD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8DE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8DF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A8DFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E08[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E14[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E20[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E2C[] = {
    0, (s32)D_800A8DCC, (s32)D_800A8DD8, (s32)D_800A8DE4,
    (s32)D_800A8DF0, (s32)D_800A8DFC, (s32)D_800A8E08, (s32)D_800A8E14,
    (s32)D_800A8E20,
};
s32 D_800A8E50[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E68[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E74[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E80[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8E98[] = {
    0, 0, 0x60040000,
};
s32 D_800A8EA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8EB0[] = {
    0, (s32)D_800A8E50, (s32)D_800A8E5C, (s32)D_800A8E68,
    (s32)D_800A8E74, (s32)D_800A8E80, (s32)D_800A8E8C, (s32)D_800A8E98,
    (s32)D_800A8EA4,
};
s32 D_800A8ED4[] = {
    174, 10, 0x60080000,
};
s32 D_800A8EE0[] = {
    174, 10, 0x60080000,
};
s32 D_800A8EEC[] = {
    170, 10, 0x60080000,
};
s32 D_800A8EF8[] = {
    170, 10, 0x60080000,
};
s32 D_800A8F04[] = {
    182, 10, 0x60080000,
};
s32 D_800A8F10[] = {
    182, 10, 0x60080000,
};
s32 D_800A8F1C[] = {
    71, 10, 0x60080000,
};
s32 D_800A8F28[] = {
    71, 10, 0x60080000,
};
s32 D_800A8F34[] = {
    1, (s32)D_800A8ED4, (s32)D_800A8EE0, (s32)D_800A8EEC,
    (s32)D_800A8EF8, (s32)D_800A8F04, (s32)D_800A8F10, (s32)D_800A8F1C,
    (s32)D_800A8F28,
};
s32 D_800A8F58[] = {
    0, 0, 0x60040000,
};
s32 D_800A8F64[] = {
    0, 0, 0x60040000,
};
s32 D_800A8F70[] = {
    0, 0, 0x60040000,
};
s32 D_800A8F7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8F88[] = {
    0, 0, 0x60040000,
};
s32 D_800A8F94[] = {
    0, 0, 0x60040000,
};
s32 D_800A8FA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A8FAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8FB8[] = {
    0, (s32)D_800A8F58, (s32)D_800A8F64, (s32)D_800A8F70,
    (s32)D_800A8F7C, (s32)D_800A8F88, (s32)D_800A8F94, (s32)D_800A8FA0,
    (s32)D_800A8FAC,
};
s32 D_800A8FDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8FE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8FF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A9000[] = {
    0, 0, 0x60040000,
};
s32 D_800A900C[] = {
    0, 0, 0x60040000,
};
s32 D_800A9018[] = {
    0, 0, 0x60040000,
};
s32 D_800A9024[] = {
    0, 0, 0x60040000,
};
s32 D_800A9030[] = {
    0, 0, 0x60040000,
};
s32 D_800A903C[] = {
    0, (s32)D_800A8FDC, (s32)D_800A8FE8, (s32)D_800A8FF4,
    (s32)D_800A9000, (s32)D_800A900C, (s32)D_800A9018, (s32)D_800A9024,
    (s32)D_800A9030,
};
s32 D_800A9060[] = {
    0, 0, 0x60040000,
};
s32 D_800A906C[] = {
    0, 0, 0x60040000,
};
s32 D_800A9078[] = {
    0, 0, 0x60040000,
};
s32 D_800A9084[] = {
    0, 0, 0x60040000,
};
s32 D_800A9090[] = {
    0, 0, 0x60040000,
};
s32 D_800A909C[] = {
    0, 0, 0x60040000,
};
s32 D_800A90A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A90B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A90C0[] = {
    0, (s32)D_800A9060, (s32)D_800A906C, (s32)D_800A9078,
    (s32)D_800A9084, (s32)D_800A9090, (s32)D_800A909C, (s32)D_800A90A8,
    (s32)D_800A90B4,
};
s32 D_800A90E4[] = {
    229, 1, 0, (s32)D_800A5784,
    (s32)D_800A5808, (s32)D_800A588C, (s32)D_800A5910, 235,
    2, 0, (s32)D_800A5994, (s32)D_800A5A18,
    (s32)D_800A5A9C, (s32)D_800A5B20, 241, 3,
    0, (s32)D_800A5BA4, (s32)D_800A5C28, (s32)D_800A5CAC,
    (s32)D_800A5D30, 246, 4, 0,
    (s32)D_800A5DB4, (s32)D_800A5E38, (s32)D_800A5EBC, (s32)D_800A5F40,
    253, 5, 0, (s32)D_800A5FC4,
    (s32)D_800A6048, (s32)D_800A60CC, (s32)D_800A6150, 259,
    6, 0, (s32)D_800A61D4, (s32)D_800A6258,
    (s32)D_800A62DC, (s32)D_800A6360, 264, 7,
    0, (s32)D_800A63E4, (s32)D_800A6468, (s32)D_800A64EC,
    (s32)D_800A6570, 268, 8, 0,
    (s32)D_800A65F4, (s32)D_800A6678, (s32)D_800A66FC, (s32)D_800A6780,
    273, 9, 0, (s32)D_800A6804,
    (s32)D_800A6888, (s32)D_800A690C, (s32)D_800A6990, 279,
    10, 0, (s32)D_800A6A14, (s32)D_800A6A98,
    (s32)D_800A6B1C, (s32)D_800A6BA0, 284, 11,
    0, (s32)D_800A6C24, (s32)D_800A6CA8, (s32)D_800A6D2C,
    (s32)D_800A6DB0, 289, 12, 0,
    (s32)D_800A6E34, (s32)D_800A6EB8, (s32)D_800A6F3C, (s32)D_800A6FC0,
    297, 13, 0, (s32)D_800A7044,
    (s32)D_800A70C8, (s32)D_800A714C, (s32)D_800A71D0, 305,
    15, 0, (s32)D_800A7254, (s32)D_800A72D8,
    (s32)D_800A735C, (s32)D_800A73E0, 308, 16,
    0, (s32)D_800A7464, (s32)D_800A74E8, (s32)D_800A756C,
    (s32)D_800A75F0, 312, 17, 0,
    (s32)D_800A7674, (s32)D_800A76F8, (s32)D_800A777C, (s32)D_800A7800,
    314, 18, 0, (s32)D_800A7884,
    (s32)D_800A7908, (s32)D_800A798C, (s32)D_800A7A10, 319,
    19, 0, (s32)D_800A7A94, (s32)D_800A7B18,
    (s32)D_800A7B9C, (s32)D_800A7C20, 324, 20,
    0, (s32)D_800A7CA4, (s32)D_800A7D28, (s32)D_800A7DAC,
    (s32)D_800A7E30, 331, 21, 0,
    (s32)D_800A7EB4, (s32)D_800A7F38, (s32)D_800A7FBC, (s32)D_800A8040,
    334, 22, 0, (s32)D_800A80C4,
    (s32)D_800A8148, (s32)D_800A81CC, (s32)D_800A8250, 338,
    23, 0, (s32)D_800A82D4, (s32)D_800A8358,
    (s32)D_800A83DC, (s32)D_800A8460, 342, 24,
    0, (s32)D_800A84E4, (s32)D_800A8568, (s32)D_800A85EC,
    (s32)D_800A8670, 345, 25, 0,
    (s32)D_800A86F4, (s32)D_800A8778, (s32)D_800A87FC, (s32)D_800A8880,
    350, 26, 0, (s32)D_800A8904,
    (s32)D_800A8988, (s32)D_800A8A0C, (s32)D_800A8A90, 357,
    28, 0, (s32)D_800A8B14, (s32)D_800A8B98,
    (s32)D_800A8C1C, (s32)D_800A8CA0, 362, 29,
    0, (s32)D_800A8D24, (s32)D_800A8DA8, (s32)D_800A8E2C,
    (s32)D_800A8EB0, 368, 30, 0,
    (s32)D_800A8F34, (s32)D_800A8FB8, (s32)D_800A903C, (s32)D_800A90C0,
};
s32 D_800A93F4[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000174, 208, 0x1FF0150,
    0x1000140, 0x1200174, 0x2000D0, 0x1FF0160,
    0x1000140, 0x1400160, 0x400080, 0x1FF0170,
    0x1000140, 0x1000160, 128, 0x1FE0160,
    0x1000140, 0x140014C, 0x400030, 0x1FE0170,
};
s32 D_800A94A4[] = {
    0, 0, 934, 0,
    0, 0,
};
s32 D_800A94BC[] = {
    0, 0, 936, 0,
    0, 0,
};
s32 D_800A94D4[] = {
    0, 0, 933, 0,
    0, 0,
};
s32 D_800A94EC[] = {
    0, 0, 935, 0,
    0, 0,
};
s32 D_800A9504[] = {
    0, 0, 937, 0,
    0, 0,
};
s32 D_800A951C[] = {
    0x17E03, 0x17E1E, 65535,
};
s32 D_800A9528[] = {
    0x17E07, 0x17E1F, 65535,
};
s32 D_800A9534[] = {
    0x17E02, 0x17E1F, 65535,
};
s32 D_800A9540[] = {
    0x17E03, 0x17E1F, 65535,
};
s32 D_800A954C[] = {
    0x17E19, 0x17E1E, 65535,
};
s32 D_800A9558[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A9564[] = {
    0x17E20, 9, 65535,
};
s32 D_800A9570[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A957C[] = {
    0x17E00, 10, 65535,
};
s32 D_800A9588[] = {
    0x17E02, 10, 65535,
};
s32 D_800A9594[] = {
    0x17E04, 10, 65535,
};
s32 D_800A95A0[] = {
    0x17E07, 10, 65535,
};
s32 D_800A95AC[] = {
    0x17E09, 10, 65535,
};
s32 D_800A95B8[] = {
    0x17E0A, 10, 65535,
};
s32 D_800A95C4[] = {
    0x17E15, 10, 65535,
};
s32 D_800A95D0[] = {
    (s32)D_800A951C, (s32)D_800A94A4, 0x40042, 0xE80288,
    1,
};
s32 D_800A95E4[] = {
    (s32)D_800A9528, (s32)D_800A94BC, 0x40042, 0xE80288,
    1,
};
s32 D_800A95F8[] = {
    (s32)D_800A9534, (s32)D_800A94D4, 0x500B6, 0xE80288,
    1,
};
s32 D_800A960C[] = {
    (s32)D_800A9540, (s32)D_800A94EC, 0x500B6, 0xE80288,
    1,
};
s32 D_800A9620[] = {
    (s32)D_800A954C, (s32)D_800A9504, 0x500B6, 0xE80288,
    1,
};
s32 D_800A9634[] = {
    0, 0, 0x60146, 0,
    0,
};
s32 D_800A9648[] = {
    (s32)D_800A9558, 0, 0x7015F, 0x15000E0,
    1,
};
s32 D_800A965C[] = {
    (s32)D_800A9564, 0, 0x7015F, 0x1400140,
    1,
};
s32 D_800A9670[] = {
    (s32)D_800A9570, 0, 0x7015F, 0x13001E0,
    1,
};
s32 D_800A9684[] = {
    (s32)D_800A957C, 0, 0x80160, 0x14801B0,
    1,
};
s32 D_800A9698[] = {
    (s32)D_800A9588, 0, 0x80160, 0x1580170,
    1,
};
s32 D_800A96AC[] = {
    (s32)D_800A9594, 0, 0x80160, 0x1180210,
    1,
};
s32 D_800A96C0[] = {
    (s32)D_800A95A0, 0, 0x80160, 0x1180210,
    1,
};
s32 D_800A96D4[] = {
    (s32)D_800A95AC, 0, 0x80160, 0x1580170,
    1,
};
s32 D_800A96E8[] = {
    (s32)D_800A95B8, 0, 0x80160, 0x1380110,
    1,
};
s32 D_800A96FC[] = {
    (s32)D_800A95C4, 0, 0x80160, 0x1580170,
    1,
};
s32 D_800A9710[] = {
    (s32)D_800A95D0, (s32)D_800A95E4, (s32)D_800A95F8, (s32)D_800A960C,
    (s32)D_800A9620, (s32)D_800A9634, (s32)D_800A9648, (s32)D_800A965C,
    (s32)D_800A9670, (s32)D_800A9684, (s32)D_800A9698, (s32)D_800A96AC,
    (s32)D_800A96C0, (s32)D_800A96D4, (s32)D_800A96E8, (s32)D_800A96FC,
    0,
};
s32 D_800A9754[] = {
    0x4FF0001, 0x7000232, 0x2280014, 0xD50064,
    0, 0, 0, 0,
    0,
};
s32 D_800A9778[] = {
    65535, 65535, 0x2E80001, 0xD00240,
    4, 0, 65535, 65535,
    0x2E80001, 0x16800B0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A97C0[])(void) = {
    func_800A4E74,
};
