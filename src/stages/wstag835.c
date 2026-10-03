#include "common.h"
#include "stage.h"
extern void (*D_800A6DE4[])(void);
void func_800A4DA8();
extern StagePoints *D_800A5194[];

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
        func_800A4CA8(D_800990B4.unk14, D_800A5194, GAME.unk44, GAME.unk46);
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
    D_800A6DE4[0]();
    return task;
}

extern s32 D_800A6C68[];
extern s32 D_800A6D9C[];
extern s32 D_800A6BDC[];
extern s32 D_800A6C60[];
extern CVECTOR D_800A4CA4;
extern s32 D_800A6A8C[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x6D6
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x6E5
#endif
void func_800A4E70(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A6C68;
    D_800990B4.unk14 = D_800A6D9C;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xC700, 0x16D00};
    D_800990B4.unk28 = D_800A6BDC;
    D_800990B4.unk3C = 0x1D;
    D_800990B4.unk40 = 0x60740000;
    D_800990B4.unk4C = D_800A6C60;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A4CA4;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A6A8C, GAME.unk44);
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4E70();
extern StagePoint D_800A4FAC;
extern StagePoint D_800A4FBC;
extern StagePoint D_800A4FD4;
extern StagePoint D_800A4FE4;
extern StagePoint D_800A4FFC;
extern StagePoint D_800A500C;
extern StagePoint D_800A5024;
extern StagePoint D_800A5034;
extern StagePoint D_800A504C;
extern StagePoint D_800A505C;
extern StagePoint D_800A5074;
extern StagePoint D_800A5084;
extern StagePoint D_800A509C;
extern StagePoint D_800A50AC;
extern StagePoint D_800A50C4;
extern StagePoint D_800A50D4;
extern StagePoint D_800A50EC;
extern StagePoint D_800A50FC;
extern StagePoint D_800A5114;
extern StagePoint D_800A5124;
extern StagePoint D_800A513C;
extern StagePoint D_800A514C;
extern StagePoint D_800A5164;
extern StagePoint D_800A5174;
extern StagePoints D_800A4FCC;
extern StagePoints D_800A4FF4;
extern StagePoints D_800A501C;
extern StagePoints D_800A5044;
extern StagePoints D_800A506C;
extern StagePoints D_800A5094;
extern StagePoints D_800A50BC;
extern StagePoints D_800A50E4;
extern StagePoints D_800A510C;
extern StagePoints D_800A5134;
extern StagePoints D_800A515C;
extern StagePoints D_800A5184;
extern StagePoints D_800A518C;
extern s32 D_800A51CC[];
extern s32 D_800A51D8[];
extern s32 D_800A51E4[];
extern s32 D_800A51F0[];
extern s32 D_800A51FC[];
extern s32 D_800A5208[];
extern s32 D_800A5214[];
extern s32 D_800A5220[];
extern s32 D_800A5250[];
extern s32 D_800A525C[];
extern s32 D_800A5268[];
extern s32 D_800A5274[];
extern s32 D_800A5280[];
extern s32 D_800A528C[];
extern s32 D_800A5298[];
extern s32 D_800A52A4[];
extern s32 D_800A52D4[];
extern s32 D_800A52E0[];
extern s32 D_800A52EC[];
extern s32 D_800A52F8[];
extern s32 D_800A5304[];
extern s32 D_800A5310[];
extern s32 D_800A531C[];
extern s32 D_800A5328[];
extern s32 D_800A5358[];
extern s32 D_800A5364[];
extern s32 D_800A5370[];
extern s32 D_800A537C[];
extern s32 D_800A5388[];
extern s32 D_800A5394[];
extern s32 D_800A53A0[];
extern s32 D_800A53AC[];
extern s32 D_800A53DC[];
extern s32 D_800A53E8[];
extern s32 D_800A53F4[];
extern s32 D_800A5400[];
extern s32 D_800A540C[];
extern s32 D_800A5418[];
extern s32 D_800A5424[];
extern s32 D_800A5430[];
extern s32 D_800A5460[];
extern s32 D_800A546C[];
extern s32 D_800A5478[];
extern s32 D_800A5484[];
extern s32 D_800A5490[];
extern s32 D_800A549C[];
extern s32 D_800A54A8[];
extern s32 D_800A54B4[];
extern s32 D_800A54E4[];
extern s32 D_800A54F0[];
extern s32 D_800A54FC[];
extern s32 D_800A5508[];
extern s32 D_800A5514[];
extern s32 D_800A5520[];
extern s32 D_800A552C[];
extern s32 D_800A5538[];
extern s32 D_800A5568[];
extern s32 D_800A5574[];
extern s32 D_800A5580[];
extern s32 D_800A558C[];
extern s32 D_800A5598[];
extern s32 D_800A55A4[];
extern s32 D_800A55B0[];
extern s32 D_800A55BC[];
extern s32 D_800A55EC[];
extern s32 D_800A55F8[];
extern s32 D_800A5604[];
extern s32 D_800A5610[];
extern s32 D_800A561C[];
extern s32 D_800A5628[];
extern s32 D_800A5634[];
extern s32 D_800A5640[];
extern s32 D_800A5670[];
extern s32 D_800A567C[];
extern s32 D_800A5688[];
extern s32 D_800A5694[];
extern s32 D_800A56A0[];
extern s32 D_800A56AC[];
extern s32 D_800A56B8[];
extern s32 D_800A56C4[];
extern s32 D_800A56F4[];
extern s32 D_800A5700[];
extern s32 D_800A570C[];
extern s32 D_800A5718[];
extern s32 D_800A5724[];
extern s32 D_800A5730[];
extern s32 D_800A573C[];
extern s32 D_800A5748[];
extern s32 D_800A5778[];
extern s32 D_800A5784[];
extern s32 D_800A5790[];
extern s32 D_800A579C[];
extern s32 D_800A57A8[];
extern s32 D_800A57B4[];
extern s32 D_800A57C0[];
extern s32 D_800A57CC[];
extern s32 D_800A57FC[];
extern s32 D_800A5808[];
extern s32 D_800A5814[];
extern s32 D_800A5820[];
extern s32 D_800A582C[];
extern s32 D_800A5838[];
extern s32 D_800A5844[];
extern s32 D_800A5850[];
extern s32 D_800A5880[];
extern s32 D_800A588C[];
extern s32 D_800A5898[];
extern s32 D_800A58A4[];
extern s32 D_800A58B0[];
extern s32 D_800A58BC[];
extern s32 D_800A58C8[];
extern s32 D_800A58D4[];
extern s32 D_800A5904[];
extern s32 D_800A5910[];
extern s32 D_800A591C[];
extern s32 D_800A5928[];
extern s32 D_800A5934[];
extern s32 D_800A5940[];
extern s32 D_800A594C[];
extern s32 D_800A5958[];
extern s32 D_800A5988[];
extern s32 D_800A5994[];
extern s32 D_800A59A0[];
extern s32 D_800A59AC[];
extern s32 D_800A59B8[];
extern s32 D_800A59C4[];
extern s32 D_800A59D0[];
extern s32 D_800A59DC[];
extern s32 D_800A5A0C[];
extern s32 D_800A5A18[];
extern s32 D_800A5A24[];
extern s32 D_800A5A30[];
extern s32 D_800A5A3C[];
extern s32 D_800A5A48[];
extern s32 D_800A5A54[];
extern s32 D_800A5A60[];
extern s32 D_800A5A90[];
extern s32 D_800A5A9C[];
extern s32 D_800A5AA8[];
extern s32 D_800A5AB4[];
extern s32 D_800A5AC0[];
extern s32 D_800A5ACC[];
extern s32 D_800A5AD8[];
extern s32 D_800A5AE4[];
extern s32 D_800A5B14[];
extern s32 D_800A5B20[];
extern s32 D_800A5B2C[];
extern s32 D_800A5B38[];
extern s32 D_800A5B44[];
extern s32 D_800A5B50[];
extern s32 D_800A5B5C[];
extern s32 D_800A5B68[];
extern s32 D_800A5B98[];
extern s32 D_800A5BA4[];
extern s32 D_800A5BB0[];
extern s32 D_800A5BBC[];
extern s32 D_800A5BC8[];
extern s32 D_800A5BD4[];
extern s32 D_800A5BE0[];
extern s32 D_800A5BEC[];
extern s32 D_800A5C1C[];
extern s32 D_800A5C28[];
extern s32 D_800A5C34[];
extern s32 D_800A5C40[];
extern s32 D_800A5C4C[];
extern s32 D_800A5C58[];
extern s32 D_800A5C64[];
extern s32 D_800A5C70[];
extern s32 D_800A5CA0[];
extern s32 D_800A5CAC[];
extern s32 D_800A5CB8[];
extern s32 D_800A5CC4[];
extern s32 D_800A5CD0[];
extern s32 D_800A5CDC[];
extern s32 D_800A5CE8[];
extern s32 D_800A5CF4[];
extern s32 D_800A5D24[];
extern s32 D_800A5D30[];
extern s32 D_800A5D3C[];
extern s32 D_800A5D48[];
extern s32 D_800A5D54[];
extern s32 D_800A5D60[];
extern s32 D_800A5D6C[];
extern s32 D_800A5D78[];
extern s32 D_800A5DA8[];
extern s32 D_800A5DB4[];
extern s32 D_800A5DC0[];
extern s32 D_800A5DCC[];
extern s32 D_800A5DD8[];
extern s32 D_800A5DE4[];
extern s32 D_800A5DF0[];
extern s32 D_800A5DFC[];
extern s32 D_800A5E2C[];
extern s32 D_800A5E38[];
extern s32 D_800A5E44[];
extern s32 D_800A5E50[];
extern s32 D_800A5E5C[];
extern s32 D_800A5E68[];
extern s32 D_800A5E74[];
extern s32 D_800A5E80[];
extern s32 D_800A5EB0[];
extern s32 D_800A5EBC[];
extern s32 D_800A5EC8[];
extern s32 D_800A5ED4[];
extern s32 D_800A5EE0[];
extern s32 D_800A5EEC[];
extern s32 D_800A5EF8[];
extern s32 D_800A5F04[];
extern s32 D_800A5F34[];
extern s32 D_800A5F40[];
extern s32 D_800A5F4C[];
extern s32 D_800A5F58[];
extern s32 D_800A5F64[];
extern s32 D_800A5F70[];
extern s32 D_800A5F7C[];
extern s32 D_800A5F88[];
extern s32 D_800A5FB8[];
extern s32 D_800A5FC4[];
extern s32 D_800A5FD0[];
extern s32 D_800A5FDC[];
extern s32 D_800A5FE8[];
extern s32 D_800A5FF4[];
extern s32 D_800A6000[];
extern s32 D_800A600C[];
extern s32 D_800A603C[];
extern s32 D_800A6048[];
extern s32 D_800A6054[];
extern s32 D_800A6060[];
extern s32 D_800A606C[];
extern s32 D_800A6078[];
extern s32 D_800A6084[];
extern s32 D_800A6090[];
extern s32 D_800A60C0[];
extern s32 D_800A60CC[];
extern s32 D_800A60D8[];
extern s32 D_800A60E4[];
extern s32 D_800A60F0[];
extern s32 D_800A60FC[];
extern s32 D_800A6108[];
extern s32 D_800A6114[];
extern s32 D_800A6144[];
extern s32 D_800A6150[];
extern s32 D_800A615C[];
extern s32 D_800A6168[];
extern s32 D_800A6174[];
extern s32 D_800A6180[];
extern s32 D_800A618C[];
extern s32 D_800A6198[];
extern s32 D_800A61C8[];
extern s32 D_800A61D4[];
extern s32 D_800A61E0[];
extern s32 D_800A61EC[];
extern s32 D_800A61F8[];
extern s32 D_800A6204[];
extern s32 D_800A6210[];
extern s32 D_800A621C[];
extern s32 D_800A624C[];
extern s32 D_800A6258[];
extern s32 D_800A6264[];
extern s32 D_800A6270[];
extern s32 D_800A627C[];
extern s32 D_800A6288[];
extern s32 D_800A6294[];
extern s32 D_800A62A0[];
extern s32 D_800A62D0[];
extern s32 D_800A62DC[];
extern s32 D_800A62E8[];
extern s32 D_800A62F4[];
extern s32 D_800A6300[];
extern s32 D_800A630C[];
extern s32 D_800A6318[];
extern s32 D_800A6324[];
extern s32 D_800A6354[];
extern s32 D_800A6360[];
extern s32 D_800A636C[];
extern s32 D_800A6378[];
extern s32 D_800A6384[];
extern s32 D_800A6390[];
extern s32 D_800A639C[];
extern s32 D_800A63A8[];
extern s32 D_800A63D8[];
extern s32 D_800A63E4[];
extern s32 D_800A63F0[];
extern s32 D_800A63FC[];
extern s32 D_800A6408[];
extern s32 D_800A6414[];
extern s32 D_800A6420[];
extern s32 D_800A642C[];
extern s32 D_800A645C[];
extern s32 D_800A6468[];
extern s32 D_800A6474[];
extern s32 D_800A6480[];
extern s32 D_800A648C[];
extern s32 D_800A6498[];
extern s32 D_800A64A4[];
extern s32 D_800A64B0[];
extern s32 D_800A64E0[];
extern s32 D_800A64EC[];
extern s32 D_800A64F8[];
extern s32 D_800A6504[];
extern s32 D_800A6510[];
extern s32 D_800A651C[];
extern s32 D_800A6528[];
extern s32 D_800A6534[];
extern s32 D_800A6564[];
extern s32 D_800A6570[];
extern s32 D_800A657C[];
extern s32 D_800A6588[];
extern s32 D_800A6594[];
extern s32 D_800A65A0[];
extern s32 D_800A65AC[];
extern s32 D_800A65B8[];
extern s32 D_800A65E8[];
extern s32 D_800A65F4[];
extern s32 D_800A6600[];
extern s32 D_800A660C[];
extern s32 D_800A6618[];
extern s32 D_800A6624[];
extern s32 D_800A6630[];
extern s32 D_800A663C[];
extern s32 D_800A666C[];
extern s32 D_800A6678[];
extern s32 D_800A6684[];
extern s32 D_800A6690[];
extern s32 D_800A669C[];
extern s32 D_800A66A8[];
extern s32 D_800A66B4[];
extern s32 D_800A66C0[];
extern s32 D_800A66F0[];
extern s32 D_800A66FC[];
extern s32 D_800A6708[];
extern s32 D_800A6714[];
extern s32 D_800A6720[];
extern s32 D_800A672C[];
extern s32 D_800A6738[];
extern s32 D_800A6744[];
extern s32 D_800A6774[];
extern s32 D_800A6780[];
extern s32 D_800A678C[];
extern s32 D_800A6798[];
extern s32 D_800A67A4[];
extern s32 D_800A67B0[];
extern s32 D_800A67BC[];
extern s32 D_800A67C8[];
extern s32 D_800A67F8[];
extern s32 D_800A6804[];
extern s32 D_800A6810[];
extern s32 D_800A681C[];
extern s32 D_800A6828[];
extern s32 D_800A6834[];
extern s32 D_800A6840[];
extern s32 D_800A684C[];
extern s32 D_800A687C[];
extern s32 D_800A6888[];
extern s32 D_800A6894[];
extern s32 D_800A68A0[];
extern s32 D_800A68AC[];
extern s32 D_800A68B8[];
extern s32 D_800A68C4[];
extern s32 D_800A68D0[];
extern s32 D_800A6900[];
extern s32 D_800A690C[];
extern s32 D_800A6918[];
extern s32 D_800A6924[];
extern s32 D_800A6930[];
extern s32 D_800A693C[];
extern s32 D_800A6948[];
extern s32 D_800A6954[];
extern s32 D_800A6984[];
extern s32 D_800A6990[];
extern s32 D_800A699C[];
extern s32 D_800A69A8[];
extern s32 D_800A69B4[];
extern s32 D_800A69C0[];
extern s32 D_800A69CC[];
extern s32 D_800A69D8[];
extern s32 D_800A6A08[];
extern s32 D_800A6A14[];
extern s32 D_800A6A20[];
extern s32 D_800A6A2C[];
extern s32 D_800A6A38[];
extern s32 D_800A6A44[];
extern s32 D_800A6A50[];
extern s32 D_800A6A5C[];
extern s32 D_800A522C[];
extern s32 D_800A52B0[];
extern s32 D_800A5334[];
extern s32 D_800A53B8[];
extern s32 D_800A543C[];
extern s32 D_800A54C0[];
extern s32 D_800A5544[];
extern s32 D_800A55C8[];
extern s32 D_800A564C[];
extern s32 D_800A56D0[];
extern s32 D_800A5754[];
extern s32 D_800A57D8[];
extern s32 D_800A585C[];
extern s32 D_800A58E0[];
extern s32 D_800A5964[];
extern s32 D_800A59E8[];
extern s32 D_800A5A6C[];
extern s32 D_800A5AF0[];
extern s32 D_800A5B74[];
extern s32 D_800A5BF8[];
extern s32 D_800A5C7C[];
extern s32 D_800A5D00[];
extern s32 D_800A5D84[];
extern s32 D_800A5E08[];
extern s32 D_800A5E8C[];
extern s32 D_800A5F10[];
extern s32 D_800A5F94[];
extern s32 D_800A6018[];
extern s32 D_800A609C[];
extern s32 D_800A6120[];
extern s32 D_800A61A4[];
extern s32 D_800A6228[];
extern s32 D_800A62AC[];
extern s32 D_800A6330[];
extern s32 D_800A63B4[];
extern s32 D_800A6438[];
extern s32 D_800A64BC[];
extern s32 D_800A6540[];
extern s32 D_800A65C4[];
extern s32 D_800A6648[];
extern s32 D_800A66CC[];
extern s32 D_800A6750[];
extern s32 D_800A67D4[];
extern s32 D_800A6858[];
extern s32 D_800A68DC[];
extern s32 D_800A6960[];
extern s32 D_800A69E4[];
extern s32 D_800A6A68[];
extern s32 D_800A6C4C[];

StagePoint D_800A4FAC = { 0x2E6, 3, 1, 160, 0x150, 5, NULL };
StagePoint D_800A4FBC = { 0x24B, 0, 0, 0x2D0, 0x320, 0, &D_800A4FAC };
StagePoints D_800A4FCC = { 3, 1, &D_800A4FBC };
StagePoint D_800A4FD4 = { 0x2E5, 4, 1, 224, 0x120, 5, NULL };
StagePoint D_800A4FE4 = { 0x23C, 0, 0, 160, 0x3E8, 0, &D_800A4FD4 };
StagePoints D_800A4FF4 = { 4, 1, &D_800A4FE4 };
StagePoint D_800A4FFC = { 0x2E6, 5, 1, 160, 0x150, 5, NULL };
StagePoint D_800A500C = { 0x249, 0, 0, 208, 0x200, 0, &D_800A4FFC };
StagePoints D_800A501C = { 5, 1, &D_800A500C };
StagePoint D_800A5024 = { 0x2E0, 7, 1, 176, 0x178, 5, NULL };
StagePoint D_800A5034 = { 0x23E, 0, 0, 0x420, 0x1E8, 0, &D_800A5024 };
StagePoints D_800A5044 = { 7, 1, &D_800A5034 };
StagePoint D_800A504C = { 0x2E0, 8, 1, 176, 0x178, 5, NULL };
StagePoint D_800A505C = { 0x227, 0, 0, 0x240, 0x200, 0, &D_800A504C };
StagePoints D_800A506C = { 8, 1, &D_800A505C };
StagePoint D_800A5074 = { 0x2E6, 9, 1, 160, 0x150, 5, NULL };
StagePoint D_800A5084 = { 0x247, 0, 0, 0x350, 0x3F0, 0, &D_800A5074 };
StagePoints D_800A5094 = { 9, 1, &D_800A5084 };
StagePoint D_800A509C = { 0x2E6, 13, 1, 160, 0x150, 5, NULL };
StagePoint D_800A50AC = { 0x2B5, 0, 0, 0x2D0, 0x320, 0, &D_800A509C };
StagePoints D_800A50BC = { 13, 1, &D_800A50AC };
StagePoint D_800A50C4 = { 0x2E5, 14, 1, 224, 0x120, 5, NULL };
StagePoint D_800A50D4 = { 0x2A9, 0, 0, 160, 0x3E8, 0, &D_800A50C4 };
StagePoints D_800A50E4 = { 14, 1, &D_800A50D4 };
StagePoint D_800A50EC = { 0x2E6, 15, 1, 160, 0x150, 5, NULL };
StagePoint D_800A50FC = { 0x2B3, 0, 0, 208, 0x200, 0, &D_800A50EC };
StagePoints D_800A510C = { 15, 1, &D_800A50FC };
StagePoint D_800A5114 = { 0x2E0, 17, 1, 176, 0x178, 5, NULL };
StagePoint D_800A5124 = { 0x2AB, 0, 0, 0x420, 0x1E8, 0, &D_800A5114 };
StagePoints D_800A5134 = { 17, 1, &D_800A5124 };
StagePoint D_800A513C = { 0x2E0, 18, 1, 176, 0x178, 5, NULL };
StagePoint D_800A514C = { 0x296, 0, 0, 0x240, 0x200, 0, &D_800A513C };
StagePoints D_800A515C = { 18, 1, &D_800A514C };
StagePoint D_800A5164 = { 0x2E6, 19, 1, 160, 0x150, 5, NULL };
StagePoint D_800A5174 = { 0x2B1, 0, 0, 0x350, 0x3F0, 0, &D_800A5164 };
StagePoints D_800A5184 = { 19, 1, &D_800A5174 };
StagePoints D_800A518C = { 0, 0, &D_800A4FBC };
StagePoints *D_800A5194[] = {
    &D_800A4FCC, &D_800A4FF4, &D_800A501C, &D_800A5044,
    &D_800A506C, &D_800A5094, &D_800A50BC, &D_800A50E4,
    &D_800A510C, &D_800A5134, &D_800A515C, &D_800A5184,
    &D_800A518C, NULL,
};
s32 D_800A51CC[] = {
    61, 11, 0x60080000,
};
s32 D_800A51D8[] = {
    61, 11, 0x60080000,
};
s32 D_800A51E4[] = {
    61, 11, 0x60080000,
};
s32 D_800A51F0[] = {
    61, 11, 0x60080000,
};
s32 D_800A51FC[] = {
    61, 11, 0x60080000,
};
s32 D_800A5208[] = {
    61, 11, 0x60080000,
};
s32 D_800A5214[] = {
    61, 11, 0x60080000,
};
s32 D_800A5220[] = {
    61, 11, 0x60080000,
};
s32 D_800A522C[] = {
    3, (s32)D_800A51CC, (s32)D_800A51D8, (s32)D_800A51E4,
    (s32)D_800A51F0, (s32)D_800A51FC, (s32)D_800A5208, (s32)D_800A5214,
    (s32)D_800A5220,
};
s32 D_800A5250[] = {
    0, 0, 0x60040000,
};
s32 D_800A525C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5268[] = {
    0, 0, 0x60040000,
};
s32 D_800A5274[] = {
    0, 0, 0x60040000,
};
s32 D_800A5280[] = {
    0, 0, 0x60040000,
};
s32 D_800A528C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5298[] = {
    0, 0, 0x60040000,
};
s32 D_800A52A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52B0[] = {
    0, (s32)D_800A5250, (s32)D_800A525C, (s32)D_800A5268,
    (s32)D_800A5274, (s32)D_800A5280, (s32)D_800A528C, (s32)D_800A5298,
    (s32)D_800A52A4,
};
s32 D_800A52D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5304[] = {
    0, 0, 0x60040000,
};
s32 D_800A5310[] = {
    0, 0, 0x60040000,
};
s32 D_800A531C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5328[] = {
    0, 0, 0x60040000,
};
s32 D_800A5334[] = {
    0, (s32)D_800A52D4, (s32)D_800A52E0, (s32)D_800A52EC,
    (s32)D_800A52F8, (s32)D_800A5304, (s32)D_800A5310, (s32)D_800A531C,
    (s32)D_800A5328,
};
s32 D_800A5358[] = {
    0, 0, 0x60040000,
};
s32 D_800A5364[] = {
    0, 0, 0x60040000,
};
s32 D_800A5370[] = {
    0, 0, 0x60040000,
};
s32 D_800A537C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5388[] = {
    0, 0, 0x60040000,
};
s32 D_800A5394[] = {
    0, 0, 0x60040000,
};
s32 D_800A53A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A53B8[] = {
    0, (s32)D_800A5358, (s32)D_800A5364, (s32)D_800A5370,
    (s32)D_800A537C, (s32)D_800A5388, (s32)D_800A5394, (s32)D_800A53A0,
    (s32)D_800A53AC,
};
s32 D_800A53DC[] = {
    61, 11, 0x60080000,
};
s32 D_800A53E8[] = {
    61, 11, 0x60080000,
};
s32 D_800A53F4[] = {
    61, 11, 0x60080000,
};
s32 D_800A5400[] = {
    61, 11, 0x60080000,
};
s32 D_800A540C[] = {
    62, 11, 0x60080000,
};
s32 D_800A5418[] = {
    62, 11, 0x60080000,
};
s32 D_800A5424[] = {
    62, 11, 0x60080000,
};
s32 D_800A5430[] = {
    62, 11, 0x60080000,
};
s32 D_800A543C[] = {
    2, (s32)D_800A53DC, (s32)D_800A53E8, (s32)D_800A53F4,
    (s32)D_800A5400, (s32)D_800A540C, (s32)D_800A5418, (s32)D_800A5424,
    (s32)D_800A5430,
};
s32 D_800A5460[] = {
    0, 0, 0x60040000,
};
s32 D_800A546C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5478[] = {
    0, 0, 0x60040000,
};
s32 D_800A5484[] = {
    0, 0, 0x60040000,
};
s32 D_800A5490[] = {
    0, 0, 0x60040000,
};
s32 D_800A549C[] = {
    0, 0, 0x60040000,
};
s32 D_800A54A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A54B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A54C0[] = {
    0, (s32)D_800A5460, (s32)D_800A546C, (s32)D_800A5478,
    (s32)D_800A5484, (s32)D_800A5490, (s32)D_800A549C, (s32)D_800A54A8,
    (s32)D_800A54B4,
};
s32 D_800A54E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A54F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A54FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5508[] = {
    0, 0, 0x60040000,
};
s32 D_800A5514[] = {
    0, 0, 0x60040000,
};
s32 D_800A5520[] = {
    0, 0, 0x60040000,
};
s32 D_800A552C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5538[] = {
    0, 0, 0x60040000,
};
s32 D_800A5544[] = {
    0, (s32)D_800A54E4, (s32)D_800A54F0, (s32)D_800A54FC,
    (s32)D_800A5508, (s32)D_800A5514, (s32)D_800A5520, (s32)D_800A552C,
    (s32)D_800A5538,
};
s32 D_800A5568[] = {
    0, 0, 0x60040000,
};
s32 D_800A5574[] = {
    0, 0, 0x60040000,
};
s32 D_800A5580[] = {
    0, 0, 0x60040000,
};
s32 D_800A558C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5598[] = {
    0, 0, 0x60040000,
};
s32 D_800A55A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A55B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A55BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A55C8[] = {
    0, (s32)D_800A5568, (s32)D_800A5574, (s32)D_800A5580,
    (s32)D_800A558C, (s32)D_800A5598, (s32)D_800A55A4, (s32)D_800A55B0,
    (s32)D_800A55BC,
};
s32 D_800A55EC[] = {
    63, 11, 0x60080000,
};
s32 D_800A55F8[] = {
    63, 11, 0x60080000,
};
s32 D_800A5604[] = {
    63, 11, 0x60080000,
};
s32 D_800A5610[] = {
    63, 11, 0x60080000,
};
s32 D_800A561C[] = {
    63, 11, 0x60080000,
};
s32 D_800A5628[] = {
    63, 11, 0x60080000,
};
s32 D_800A5634[] = {
    63, 11, 0x60080000,
};
s32 D_800A5640[] = {
    63, 11, 0x60080000,
};
s32 D_800A564C[] = {
    3, (s32)D_800A55EC, (s32)D_800A55F8, (s32)D_800A5604,
    (s32)D_800A5610, (s32)D_800A561C, (s32)D_800A5628, (s32)D_800A5634,
    (s32)D_800A5640,
};
s32 D_800A5670[] = {
    0, 0, 0x60040000,
};
s32 D_800A567C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5688[] = {
    0, 0, 0x60040000,
};
s32 D_800A5694[] = {
    0, 0, 0x60040000,
};
s32 D_800A56A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A56AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A56B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A56C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A56D0[] = {
    0, (s32)D_800A5670, (s32)D_800A567C, (s32)D_800A5688,
    (s32)D_800A5694, (s32)D_800A56A0, (s32)D_800A56AC, (s32)D_800A56B8,
    (s32)D_800A56C4,
};
s32 D_800A56F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5700[] = {
    0, 0, 0x60040000,
};
s32 D_800A570C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5718[] = {
    0, 0, 0x60040000,
};
s32 D_800A5724[] = {
    0, 0, 0x60040000,
};
s32 D_800A5730[] = {
    0, 0, 0x60040000,
};
s32 D_800A573C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5748[] = {
    0, 0, 0x60040000,
};
s32 D_800A5754[] = {
    0, (s32)D_800A56F4, (s32)D_800A5700, (s32)D_800A570C,
    (s32)D_800A5718, (s32)D_800A5724, (s32)D_800A5730, (s32)D_800A573C,
    (s32)D_800A5748,
};
s32 D_800A5778[] = {
    0, 0, 0x60040000,
};
s32 D_800A5784[] = {
    0, 0, 0x60040000,
};
s32 D_800A5790[] = {
    0, 0, 0x60040000,
};
s32 D_800A579C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5778, (s32)D_800A5784, (s32)D_800A5790,
    (s32)D_800A579C, (s32)D_800A57A8, (s32)D_800A57B4, (s32)D_800A57C0,
    (s32)D_800A57CC,
};
s32 D_800A57FC[] = {
    61, 11, 0x60080000,
};
s32 D_800A5808[] = {
    61, 11, 0x60080000,
};
s32 D_800A5814[] = {
    61, 11, 0x60080000,
};
s32 D_800A5820[] = {
    61, 11, 0x60080000,
};
s32 D_800A582C[] = {
    61, 11, 0x60080000,
};
s32 D_800A5838[] = {
    61, 11, 0x60080000,
};
s32 D_800A5844[] = {
    61, 11, 0x60080000,
};
s32 D_800A5850[] = {
    61, 11, 0x60080000,
};
s32 D_800A585C[] = {
    4, (s32)D_800A57FC, (s32)D_800A5808, (s32)D_800A5814,
    (s32)D_800A5820, (s32)D_800A582C, (s32)D_800A5838, (s32)D_800A5844,
    (s32)D_800A5850,
};
s32 D_800A5880[] = {
    0, 0, 0x60040000,
};
s32 D_800A588C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5898[] = {
    0, 0, 0x60040000,
};
s32 D_800A58A4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5880, (s32)D_800A588C, (s32)D_800A5898,
    (s32)D_800A58A4, (s32)D_800A58B0, (s32)D_800A58BC, (s32)D_800A58C8,
    (s32)D_800A58D4,
};
s32 D_800A5904[] = {
    0, 0, 0x60040000,
};
s32 D_800A5910[] = {
    0, 0, 0x60040000,
};
s32 D_800A591C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5928[] = {
    0, 0, 0x60040000,
};
s32 D_800A5934[] = {
    0, 0, 0x60040000,
};
s32 D_800A5940[] = {
    0, 0, 0x60040000,
};
s32 D_800A594C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5958[] = {
    0, 0, 0x60040000,
};
s32 D_800A5964[] = {
    0, (s32)D_800A5904, (s32)D_800A5910, (s32)D_800A591C,
    (s32)D_800A5928, (s32)D_800A5934, (s32)D_800A5940, (s32)D_800A594C,
    (s32)D_800A5958,
};
s32 D_800A5988[] = {
    0, 0, 0x60040000,
};
s32 D_800A5994[] = {
    0, 0, 0x60040000,
};
s32 D_800A59A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A59AC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5988, (s32)D_800A5994, (s32)D_800A59A0,
    (s32)D_800A59AC, (s32)D_800A59B8, (s32)D_800A59C4, (s32)D_800A59D0,
    (s32)D_800A59DC,
};
s32 D_800A5A0C[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A18[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A24[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A30[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A3C[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A48[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A54[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A60[] = {
    64, 11, 0x60080000,
};
s32 D_800A5A6C[] = {
    4, (s32)D_800A5A0C, (s32)D_800A5A18, (s32)D_800A5A24,
    (s32)D_800A5A30, (s32)D_800A5A3C, (s32)D_800A5A48, (s32)D_800A5A54,
    (s32)D_800A5A60,
};
s32 D_800A5A90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AB4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5A90, (s32)D_800A5A9C, (s32)D_800A5AA8,
    (s32)D_800A5AB4, (s32)D_800A5AC0, (s32)D_800A5ACC, (s32)D_800A5AD8,
    (s32)D_800A5AE4,
};
s32 D_800A5B14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B38[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B44[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B50[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B74[] = {
    0, (s32)D_800A5B14, (s32)D_800A5B20, (s32)D_800A5B2C,
    (s32)D_800A5B38, (s32)D_800A5B44, (s32)D_800A5B50, (s32)D_800A5B5C,
    (s32)D_800A5B68,
};
s32 D_800A5B98[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BBC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5B98, (s32)D_800A5BA4, (s32)D_800A5BB0,
    (s32)D_800A5BBC, (s32)D_800A5BC8, (s32)D_800A5BD4, (s32)D_800A5BE0,
    (s32)D_800A5BEC,
};
s32 D_800A5C1C[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C28[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C34[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C40[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C4C[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C58[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C64[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C70[] = {
    61, 11, 0x60080000,
};
s32 D_800A5C7C[] = {
    3, (s32)D_800A5C1C, (s32)D_800A5C28, (s32)D_800A5C34,
    (s32)D_800A5C40, (s32)D_800A5C4C, (s32)D_800A5C58, (s32)D_800A5C64,
    (s32)D_800A5C70,
};
s32 D_800A5CA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CC4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5CA0, (s32)D_800A5CAC, (s32)D_800A5CB8,
    (s32)D_800A5CC4, (s32)D_800A5CD0, (s32)D_800A5CDC, (s32)D_800A5CE8,
    (s32)D_800A5CF4,
};
s32 D_800A5D24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D60[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D84[] = {
    0, (s32)D_800A5D24, (s32)D_800A5D30, (s32)D_800A5D3C,
    (s32)D_800A5D48, (s32)D_800A5D54, (s32)D_800A5D60, (s32)D_800A5D6C,
    (s32)D_800A5D78,
};
s32 D_800A5DA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DCC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5DA8, (s32)D_800A5DB4, (s32)D_800A5DC0,
    (s32)D_800A5DCC, (s32)D_800A5DD8, (s32)D_800A5DE4, (s32)D_800A5DF0,
    (s32)D_800A5DFC,
};
s32 D_800A5E2C[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E38[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E44[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E50[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E5C[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E68[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E74[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E80[] = {
    104, 11, 0x60080000,
};
s32 D_800A5E8C[] = {
    3, (s32)D_800A5E2C, (s32)D_800A5E38, (s32)D_800A5E44,
    (s32)D_800A5E50, (s32)D_800A5E5C, (s32)D_800A5E68, (s32)D_800A5E74,
    (s32)D_800A5E80,
};
s32 D_800A5EB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5ED4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5EB0, (s32)D_800A5EBC, (s32)D_800A5EC8,
    (s32)D_800A5ED4, (s32)D_800A5EE0, (s32)D_800A5EEC, (s32)D_800A5EF8,
    (s32)D_800A5F04,
};
s32 D_800A5F34[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F40[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F58[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F94[] = {
    0, (s32)D_800A5F34, (s32)D_800A5F40, (s32)D_800A5F4C,
    (s32)D_800A5F58, (s32)D_800A5F64, (s32)D_800A5F70, (s32)D_800A5F7C,
    (s32)D_800A5F88,
};
s32 D_800A5FB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FDC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5FB8, (s32)D_800A5FC4, (s32)D_800A5FD0,
    (s32)D_800A5FDC, (s32)D_800A5FE8, (s32)D_800A5FF4, (s32)D_800A6000,
    (s32)D_800A600C,
};
s32 D_800A603C[] = {
    103, 11, 0x60080000,
};
s32 D_800A6048[] = {
    103, 11, 0x60080000,
};
s32 D_800A6054[] = {
    103, 11, 0x60080000,
};
s32 D_800A6060[] = {
    103, 11, 0x60080000,
};
s32 D_800A606C[] = {
    103, 11, 0x60080000,
};
s32 D_800A6078[] = {
    103, 11, 0x60080000,
};
s32 D_800A6084[] = {
    103, 11, 0x60080000,
};
s32 D_800A6090[] = {
    103, 11, 0x60080000,
};
s32 D_800A609C[] = {
    2, (s32)D_800A603C, (s32)D_800A6048, (s32)D_800A6054,
    (s32)D_800A6060, (s32)D_800A606C, (s32)D_800A6078, (s32)D_800A6084,
    (s32)D_800A6090,
};
s32 D_800A60C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A60CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A60D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A60E4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A60C0, (s32)D_800A60CC, (s32)D_800A60D8,
    (s32)D_800A60E4, (s32)D_800A60F0, (s32)D_800A60FC, (s32)D_800A6108,
    (s32)D_800A6114,
};
s32 D_800A6144[] = {
    0, 0, 0x60040000,
};
s32 D_800A6150[] = {
    0, 0, 0x60040000,
};
s32 D_800A615C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6168[] = {
    0, 0, 0x60040000,
};
s32 D_800A6174[] = {
    0, 0, 0x60040000,
};
s32 D_800A6180[] = {
    0, 0, 0x60040000,
};
s32 D_800A618C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6198[] = {
    0, 0, 0x60040000,
};
s32 D_800A61A4[] = {
    0, (s32)D_800A6144, (s32)D_800A6150, (s32)D_800A615C,
    (s32)D_800A6168, (s32)D_800A6174, (s32)D_800A6180, (s32)D_800A618C,
    (s32)D_800A6198,
};
s32 D_800A61C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A61D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A61E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61EC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A61C8, (s32)D_800A61D4, (s32)D_800A61E0,
    (s32)D_800A61EC, (s32)D_800A61F8, (s32)D_800A6204, (s32)D_800A6210,
    (s32)D_800A621C,
};
s32 D_800A624C[] = {
    178, 11, 0x60080000,
};
s32 D_800A6258[] = {
    178, 11, 0x60080000,
};
s32 D_800A6264[] = {
    178, 11, 0x60080000,
};
s32 D_800A6270[] = {
    178, 11, 0x60080000,
};
s32 D_800A627C[] = {
    178, 11, 0x60080000,
};
s32 D_800A6288[] = {
    178, 11, 0x60080000,
};
s32 D_800A6294[] = {
    178, 11, 0x60080000,
};
s32 D_800A62A0[] = {
    178, 11, 0x60080000,
};
s32 D_800A62AC[] = {
    3, (s32)D_800A624C, (s32)D_800A6258, (s32)D_800A6264,
    (s32)D_800A6270, (s32)D_800A627C, (s32)D_800A6288, (s32)D_800A6294,
    (s32)D_800A62A0,
};
s32 D_800A62D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A62E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62F4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A62D0, (s32)D_800A62DC, (s32)D_800A62E8,
    (s32)D_800A62F4, (s32)D_800A6300, (s32)D_800A630C, (s32)D_800A6318,
    (s32)D_800A6324,
};
s32 D_800A6354[] = {
    0, 0, 0x60040000,
};
s32 D_800A6360[] = {
    0, 0, 0x60040000,
};
s32 D_800A636C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6378[] = {
    0, 0, 0x60040000,
};
s32 D_800A6384[] = {
    0, 0, 0x60040000,
};
s32 D_800A6390[] = {
    0, 0, 0x60040000,
};
s32 D_800A639C[] = {
    0, 0, 0x60040000,
};
s32 D_800A63A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B4[] = {
    0, (s32)D_800A6354, (s32)D_800A6360, (s32)D_800A636C,
    (s32)D_800A6378, (s32)D_800A6384, (s32)D_800A6390, (s32)D_800A639C,
    (s32)D_800A63A8,
};
s32 D_800A63D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63FC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A63D8, (s32)D_800A63E4, (s32)D_800A63F0,
    (s32)D_800A63FC, (s32)D_800A6408, (s32)D_800A6414, (s32)D_800A6420,
    (s32)D_800A642C,
};
s32 D_800A645C[] = {
    103, 11, 0x60080000,
};
s32 D_800A6468[] = {
    103, 11, 0x60080000,
};
s32 D_800A6474[] = {
    103, 11, 0x60080000,
};
s32 D_800A6480[] = {
    103, 11, 0x60080000,
};
s32 D_800A648C[] = {
    103, 11, 0x60080000,
};
s32 D_800A6498[] = {
    103, 11, 0x60080000,
};
s32 D_800A64A4[] = {
    103, 11, 0x60080000,
};
s32 D_800A64B0[] = {
    103, 11, 0x60080000,
};
s32 D_800A64BC[] = {
    2, (s32)D_800A645C, (s32)D_800A6468, (s32)D_800A6474,
    (s32)D_800A6480, (s32)D_800A648C, (s32)D_800A6498, (s32)D_800A64A4,
    (s32)D_800A64B0,
};
s32 D_800A64E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6504[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A64E0, (s32)D_800A64EC, (s32)D_800A64F8,
    (s32)D_800A6504, (s32)D_800A6510, (s32)D_800A651C, (s32)D_800A6528,
    (s32)D_800A6534,
};
s32 D_800A6564[] = {
    0, 0, 0x60040000,
};
s32 D_800A6570[] = {
    0, 0, 0x60040000,
};
s32 D_800A657C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6588[] = {
    0, 0, 0x60040000,
};
s32 D_800A6594[] = {
    0, 0, 0x60040000,
};
s32 D_800A65A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C4[] = {
    0, (s32)D_800A6564, (s32)D_800A6570, (s32)D_800A657C,
    (s32)D_800A6588, (s32)D_800A6594, (s32)D_800A65A0, (s32)D_800A65AC,
    (s32)D_800A65B8,
};
s32 D_800A65E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6600[] = {
    0, 0, 0x60040000,
};
s32 D_800A660C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A65E8, (s32)D_800A65F4, (s32)D_800A6600,
    (s32)D_800A660C, (s32)D_800A6618, (s32)D_800A6624, (s32)D_800A6630,
    (s32)D_800A663C,
};
s32 D_800A666C[] = {
    64, 11, 0x60080000,
};
s32 D_800A6678[] = {
    64, 11, 0x60080000,
};
s32 D_800A6684[] = {
    64, 11, 0x60080000,
};
s32 D_800A6690[] = {
    64, 11, 0x60080000,
};
s32 D_800A669C[] = {
    64, 11, 0x60080000,
};
s32 D_800A66A8[] = {
    64, 11, 0x60080000,
};
s32 D_800A66B4[] = {
    64, 11, 0x60080000,
};
s32 D_800A66C0[] = {
    64, 11, 0x60080000,
};
s32 D_800A66CC[] = {
    4, (s32)D_800A666C, (s32)D_800A6678, (s32)D_800A6684,
    (s32)D_800A6690, (s32)D_800A669C, (s32)D_800A66A8, (s32)D_800A66B4,
    (s32)D_800A66C0,
};
s32 D_800A66F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6708[] = {
    0, 0, 0x60040000,
};
s32 D_800A6714[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A66F0, (s32)D_800A66FC, (s32)D_800A6708,
    (s32)D_800A6714, (s32)D_800A6720, (s32)D_800A672C, (s32)D_800A6738,
    (s32)D_800A6744,
};
s32 D_800A6774[] = {
    0, 0, 0x60040000,
};
s32 D_800A6780[] = {
    0, 0, 0x60040000,
};
s32 D_800A678C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6798[] = {
    0, 0, 0x60040000,
};
s32 D_800A67A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D4[] = {
    0, (s32)D_800A6774, (s32)D_800A6780, (s32)D_800A678C,
    (s32)D_800A6798, (s32)D_800A67A4, (s32)D_800A67B0, (s32)D_800A67BC,
    (s32)D_800A67C8,
};
s32 D_800A67F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6804[] = {
    0, 0, 0x60040000,
};
s32 D_800A6810[] = {
    0, 0, 0x60040000,
};
s32 D_800A681C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A67F8, (s32)D_800A6804, (s32)D_800A6810,
    (s32)D_800A681C, (s32)D_800A6828, (s32)D_800A6834, (s32)D_800A6840,
    (s32)D_800A684C,
};
s32 D_800A687C[] = {
    104, 11, 0x60080000,
};
s32 D_800A6888[] = {
    104, 11, 0x60080000,
};
s32 D_800A6894[] = {
    104, 11, 0x60080000,
};
s32 D_800A68A0[] = {
    104, 11, 0x60080000,
};
s32 D_800A68AC[] = {
    104, 11, 0x60080000,
};
s32 D_800A68B8[] = {
    104, 11, 0x60080000,
};
s32 D_800A68C4[] = {
    104, 11, 0x60080000,
};
s32 D_800A68D0[] = {
    104, 11, 0x60080000,
};
s32 D_800A68DC[] = {
    3, (s32)D_800A687C, (s32)D_800A6888, (s32)D_800A6894,
    (s32)D_800A68A0, (s32)D_800A68AC, (s32)D_800A68B8, (s32)D_800A68C4,
    (s32)D_800A68D0,
};
s32 D_800A6900[] = {
    0, 0, 0x60040000,
};
s32 D_800A690C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6918[] = {
    0, 0, 0x60040000,
};
s32 D_800A6924[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6900, (s32)D_800A690C, (s32)D_800A6918,
    (s32)D_800A6924, (s32)D_800A6930, (s32)D_800A693C, (s32)D_800A6948,
    (s32)D_800A6954,
};
s32 D_800A6984[] = {
    0, 0, 0x60040000,
};
s32 D_800A6990[] = {
    0, 0, 0x60040000,
};
s32 D_800A699C[] = {
    0, 0, 0x60040000,
};
s32 D_800A69A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E4[] = {
    0, (s32)D_800A6984, (s32)D_800A6990, (s32)D_800A699C,
    (s32)D_800A69A8, (s32)D_800A69B4, (s32)D_800A69C0, (s32)D_800A69CC,
    (s32)D_800A69D8,
};
s32 D_800A6A08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A2C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A6A08, (s32)D_800A6A14, (s32)D_800A6A20,
    (s32)D_800A6A2C, (s32)D_800A6A38, (s32)D_800A6A44, (s32)D_800A6A50,
    (s32)D_800A6A5C,
};
s32 D_800A6A8C[] = {
    182, 3, 0, (s32)D_800A522C,
    (s32)D_800A52B0, (s32)D_800A5334, (s32)D_800A53B8, 186,
    4, 0, (s32)D_800A543C, (s32)D_800A54C0,
    (s32)D_800A5544, (s32)D_800A55C8, 190, 5,
    0, (s32)D_800A564C, (s32)D_800A56D0, (s32)D_800A5754,
    (s32)D_800A57D8, 195, 7, 0,
    (s32)D_800A585C, (s32)D_800A58E0, (s32)D_800A5964, (s32)D_800A59E8,
    197, 8, 0, (s32)D_800A5A6C,
    (s32)D_800A5AF0, (s32)D_800A5B74, (s32)D_800A5BF8, 200,
    9, 0, (s32)D_800A5C7C, (s32)D_800A5D00,
    (s32)D_800A5D84, (s32)D_800A5E08, 210, 13,
    0, (s32)D_800A5E8C, (s32)D_800A5F10, (s32)D_800A5F94,
    (s32)D_800A6018, 214, 14, 0,
    (s32)D_800A609C, (s32)D_800A6120, (s32)D_800A61A4, (s32)D_800A6228,
    218, 15, 0, (s32)D_800A62AC,
    (s32)D_800A6330, (s32)D_800A63B4, (s32)D_800A6438, 223,
    17, 0, (s32)D_800A64BC, (s32)D_800A6540,
    (s32)D_800A65C4, (s32)D_800A6648, 225, 18,
    0, (s32)D_800A66CC, (s32)D_800A6750, (s32)D_800A67D4,
    (s32)D_800A6858, 228, 19, 0,
    (s32)D_800A68DC, (s32)D_800A6960, (s32)D_800A69E4, (s32)D_800A6A68,
};
s32 D_800A6BDC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1980152, 0x980048, 0x1FF0160,
};
s32 D_800A6C4C[] = {
    0, 0, 0x40147, 0,
    0,
};
s32 D_800A6C60[] = {
    (s32)D_800A6C4C, 0,
};
s32 D_800A6C68[] = {
    0x28F0001, 0x4B370137, 0xFE000A, 275,
    0x10000, 0x137028F, 0xA4B37, 0xF4026D,
    0, 0x28F0001, 0x4B370137, 0x354000A,
    128, 0x10000, 0x14C02B6, 0xA624C,
    0xAB0180, 0, 0x2B60001, 0x624C014C,
    0x2B1000A, 166, 0x10000, 0x23302FF,
    0x180700, 0xFFDC008C, 0, 0x2980001,
    5, 0x1B00000, 254, 0x10000,
    0x6028A, 0, 0x10C0198, 0,
    0x68F0001, 0x4B370137, 0x1DB000A, 113,
    0x10000, 0x1340668, 0xA3634, 0xCE00A9,
    0, 0x6680001, 0x36340134, 0x2EE000A,
    142, 0x10000, 0x23204FF, 0x180700,
    0x5C008C, 336, 0x4920001, 1,
    0x2300000, 0x13F00B3, 0x10000, 0x20479,
    0, 0xC60210, 335, 0x4880001,
    3, 0x1F00000, 0x15F00D8, 0x10000,
    0x40486, 0, 0xE801D0, 368,
    0, 0, 0, 0,
    0,
};
s32 D_800A6D9C[] = {
    65535, 65535, 0x2E20001, 0x14800B0,
    4, 0, 65535, 65535,
    0x2E20001, 0xF80330, 5, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6DE4[])(void) = {
    func_800A4E70,
};
