#include "common.h"
#include "stage.h"
extern void (*D_800A9450[])(void);
void func_800A4DA4();
extern StagePoints *D_800A58C4[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A58C4, GAME.unk44, GAME.unk46);
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
    D_800A9450[0]();
    return task;
}

extern s32 D_800A93DC[];
extern s32 D_800A93F0[];
extern s32 D_800A8B64[];
extern s32 D_800A9340[];
extern s32 D_800A88E0[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x689
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x699
#endif
void func_800A4E74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A93DC;
    D_800990B4.unk14 = D_800A93F0;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x13B00, 0x21000};
    D_800990B4.unk28 = D_800A8B64;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A9340;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A88E0, GAME.unk44);
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4E74();
extern StagePoint D_800A4F94;
extern StagePoint D_800A4FA4;
extern StagePoint D_800A4FB4;
extern StagePoint D_800A4FCC;
extern StagePoint D_800A4FDC;
extern StagePoint D_800A4FEC;
extern StagePoint D_800A5004;
extern StagePoint D_800A5014;
extern StagePoint D_800A5024;
extern StagePoint D_800A503C;
extern StagePoint D_800A504C;
extern StagePoint D_800A505C;
extern StagePoint D_800A5074;
extern StagePoint D_800A5084;
extern StagePoint D_800A5094;
extern StagePoint D_800A50AC;
extern StagePoint D_800A50BC;
extern StagePoint D_800A50CC;
extern StagePoint D_800A50E4;
extern StagePoint D_800A50F4;
extern StagePoint D_800A5104;
extern StagePoint D_800A511C;
extern StagePoint D_800A512C;
extern StagePoint D_800A513C;
extern StagePoint D_800A5154;
extern StagePoint D_800A5164;
extern StagePoint D_800A5174;
extern StagePoint D_800A518C;
extern StagePoint D_800A519C;
extern StagePoint D_800A51AC;
extern StagePoint D_800A51C4;
extern StagePoint D_800A51D4;
extern StagePoint D_800A51E4;
extern StagePoint D_800A51FC;
extern StagePoint D_800A520C;
extern StagePoint D_800A521C;
extern StagePoint D_800A5234;
extern StagePoint D_800A5244;
extern StagePoint D_800A5254;
extern StagePoint D_800A526C;
extern StagePoint D_800A527C;
extern StagePoint D_800A528C;
extern StagePoint D_800A52A4;
extern StagePoint D_800A52B4;
extern StagePoint D_800A52C4;
extern StagePoint D_800A52DC;
extern StagePoint D_800A52EC;
extern StagePoint D_800A52FC;
extern StagePoint D_800A5314;
extern StagePoint D_800A5324;
extern StagePoint D_800A5334;
extern StagePoint D_800A534C;
extern StagePoint D_800A535C;
extern StagePoint D_800A536C;
extern StagePoint D_800A5384;
extern StagePoint D_800A5394;
extern StagePoint D_800A53A4;
extern StagePoint D_800A53BC;
extern StagePoint D_800A53CC;
extern StagePoint D_800A53DC;
extern StagePoint D_800A53F4;
extern StagePoint D_800A5404;
extern StagePoint D_800A5414;
extern StagePoint D_800A542C;
extern StagePoint D_800A543C;
extern StagePoint D_800A544C;
extern StagePoint D_800A5464;
extern StagePoint D_800A5474;
extern StagePoint D_800A5484;
extern StagePoint D_800A549C;
extern StagePoint D_800A54AC;
extern StagePoint D_800A54BC;
extern StagePoint D_800A54D4;
extern StagePoint D_800A54E4;
extern StagePoint D_800A54F4;
extern StagePoint D_800A550C;
extern StagePoint D_800A551C;
extern StagePoint D_800A552C;
extern StagePoint D_800A5544;
extern StagePoint D_800A5554;
extern StagePoint D_800A5564;
extern StagePoint D_800A557C;
extern StagePoint D_800A558C;
extern StagePoint D_800A559C;
extern StagePoint D_800A55B4;
extern StagePoint D_800A55C4;
extern StagePoint D_800A55D4;
extern StagePoint D_800A55EC;
extern StagePoint D_800A55FC;
extern StagePoint D_800A560C;
extern StagePoint D_800A5624;
extern StagePoint D_800A5634;
extern StagePoint D_800A5644;
extern StagePoint D_800A565C;
extern StagePoint D_800A566C;
extern StagePoint D_800A567C;
extern StagePoint D_800A5694;
extern StagePoint D_800A56A4;
extern StagePoint D_800A56B4;
extern StagePoint D_800A56CC;
extern StagePoint D_800A56DC;
extern StagePoint D_800A56EC;
extern StagePoint D_800A5704;
extern StagePoint D_800A5714;
extern StagePoint D_800A5724;
extern StagePoint D_800A573C;
extern StagePoint D_800A574C;
extern StagePoint D_800A575C;
extern StagePoint D_800A5774;
extern StagePoint D_800A5784;
extern StagePoint D_800A5794;
extern StagePoint D_800A57AC;
extern StagePoint D_800A57BC;
extern StagePoint D_800A57CC;
extern StagePoint D_800A57E4;
extern StagePoint D_800A57F4;
extern StagePoint D_800A5804;
extern StagePoint D_800A581C;
extern StagePoint D_800A582C;
extern StagePoint D_800A583C;
extern StagePoint D_800A5854;
extern StagePoint D_800A5864;
extern StagePoint D_800A5874;
extern StagePoint D_800A588C;
extern StagePoint D_800A589C;
extern StagePoint D_800A58AC;
extern StagePoints D_800A4FC4;
extern StagePoints D_800A4FFC;
extern StagePoints D_800A5034;
extern StagePoints D_800A506C;
extern StagePoints D_800A50A4;
extern StagePoints D_800A50DC;
extern StagePoints D_800A5114;
extern StagePoints D_800A514C;
extern StagePoints D_800A5184;
extern StagePoints D_800A51BC;
extern StagePoints D_800A51F4;
extern StagePoints D_800A522C;
extern StagePoints D_800A5264;
extern StagePoints D_800A529C;
extern StagePoints D_800A52D4;
extern StagePoints D_800A530C;
extern StagePoints D_800A5344;
extern StagePoints D_800A537C;
extern StagePoints D_800A53B4;
extern StagePoints D_800A53EC;
extern StagePoints D_800A5424;
extern StagePoints D_800A545C;
extern StagePoints D_800A5494;
extern StagePoints D_800A54CC;
extern StagePoints D_800A5504;
extern StagePoints D_800A553C;
extern StagePoints D_800A5574;
extern StagePoints D_800A55AC;
extern StagePoints D_800A55E4;
extern StagePoints D_800A561C;
extern StagePoints D_800A5654;
extern StagePoints D_800A568C;
extern StagePoints D_800A56C4;
extern StagePoints D_800A56FC;
extern StagePoints D_800A5734;
extern StagePoints D_800A576C;
extern StagePoints D_800A57A4;
extern StagePoints D_800A57DC;
extern StagePoints D_800A5814;
extern StagePoints D_800A584C;
extern StagePoints D_800A5884;
extern StagePoints D_800A58BC;
extern s32 D_800A5970[];
extern s32 D_800A597C[];
extern s32 D_800A5988[];
extern s32 D_800A5994[];
extern s32 D_800A59A0[];
extern s32 D_800A59AC[];
extern s32 D_800A59B8[];
extern s32 D_800A59C4[];
extern s32 D_800A59F4[];
extern s32 D_800A5A00[];
extern s32 D_800A5A0C[];
extern s32 D_800A5A18[];
extern s32 D_800A5A24[];
extern s32 D_800A5A30[];
extern s32 D_800A5A3C[];
extern s32 D_800A5A48[];
extern s32 D_800A5A78[];
extern s32 D_800A5A84[];
extern s32 D_800A5A90[];
extern s32 D_800A5A9C[];
extern s32 D_800A5AA8[];
extern s32 D_800A5AB4[];
extern s32 D_800A5AC0[];
extern s32 D_800A5ACC[];
extern s32 D_800A5AFC[];
extern s32 D_800A5B08[];
extern s32 D_800A5B14[];
extern s32 D_800A5B20[];
extern s32 D_800A5B2C[];
extern s32 D_800A5B38[];
extern s32 D_800A5B44[];
extern s32 D_800A5B50[];
extern s32 D_800A5B80[];
extern s32 D_800A5B8C[];
extern s32 D_800A5B98[];
extern s32 D_800A5BA4[];
extern s32 D_800A5BB0[];
extern s32 D_800A5BBC[];
extern s32 D_800A5BC8[];
extern s32 D_800A5BD4[];
extern s32 D_800A5C04[];
extern s32 D_800A5C10[];
extern s32 D_800A5C1C[];
extern s32 D_800A5C28[];
extern s32 D_800A5C34[];
extern s32 D_800A5C40[];
extern s32 D_800A5C4C[];
extern s32 D_800A5C58[];
extern s32 D_800A5C88[];
extern s32 D_800A5C94[];
extern s32 D_800A5CA0[];
extern s32 D_800A5CAC[];
extern s32 D_800A5CB8[];
extern s32 D_800A5CC4[];
extern s32 D_800A5CD0[];
extern s32 D_800A5CDC[];
extern s32 D_800A5D0C[];
extern s32 D_800A5D18[];
extern s32 D_800A5D24[];
extern s32 D_800A5D30[];
extern s32 D_800A5D3C[];
extern s32 D_800A5D48[];
extern s32 D_800A5D54[];
extern s32 D_800A5D60[];
extern s32 D_800A5D90[];
extern s32 D_800A5D9C[];
extern s32 D_800A5DA8[];
extern s32 D_800A5DB4[];
extern s32 D_800A5DC0[];
extern s32 D_800A5DCC[];
extern s32 D_800A5DD8[];
extern s32 D_800A5DE4[];
extern s32 D_800A5E14[];
extern s32 D_800A5E20[];
extern s32 D_800A5E2C[];
extern s32 D_800A5E38[];
extern s32 D_800A5E44[];
extern s32 D_800A5E50[];
extern s32 D_800A5E5C[];
extern s32 D_800A5E68[];
extern s32 D_800A5E98[];
extern s32 D_800A5EA4[];
extern s32 D_800A5EB0[];
extern s32 D_800A5EBC[];
extern s32 D_800A5EC8[];
extern s32 D_800A5ED4[];
extern s32 D_800A5EE0[];
extern s32 D_800A5EEC[];
extern s32 D_800A5F1C[];
extern s32 D_800A5F28[];
extern s32 D_800A5F34[];
extern s32 D_800A5F40[];
extern s32 D_800A5F4C[];
extern s32 D_800A5F58[];
extern s32 D_800A5F64[];
extern s32 D_800A5F70[];
extern s32 D_800A5FA0[];
extern s32 D_800A5FAC[];
extern s32 D_800A5FB8[];
extern s32 D_800A5FC4[];
extern s32 D_800A5FD0[];
extern s32 D_800A5FDC[];
extern s32 D_800A5FE8[];
extern s32 D_800A5FF4[];
extern s32 D_800A6024[];
extern s32 D_800A6030[];
extern s32 D_800A603C[];
extern s32 D_800A6048[];
extern s32 D_800A6054[];
extern s32 D_800A6060[];
extern s32 D_800A606C[];
extern s32 D_800A6078[];
extern s32 D_800A60A8[];
extern s32 D_800A60B4[];
extern s32 D_800A60C0[];
extern s32 D_800A60CC[];
extern s32 D_800A60D8[];
extern s32 D_800A60E4[];
extern s32 D_800A60F0[];
extern s32 D_800A60FC[];
extern s32 D_800A612C[];
extern s32 D_800A6138[];
extern s32 D_800A6144[];
extern s32 D_800A6150[];
extern s32 D_800A615C[];
extern s32 D_800A6168[];
extern s32 D_800A6174[];
extern s32 D_800A6180[];
extern s32 D_800A61B0[];
extern s32 D_800A61BC[];
extern s32 D_800A61C8[];
extern s32 D_800A61D4[];
extern s32 D_800A61E0[];
extern s32 D_800A61EC[];
extern s32 D_800A61F8[];
extern s32 D_800A6204[];
extern s32 D_800A6234[];
extern s32 D_800A6240[];
extern s32 D_800A624C[];
extern s32 D_800A6258[];
extern s32 D_800A6264[];
extern s32 D_800A6270[];
extern s32 D_800A627C[];
extern s32 D_800A6288[];
extern s32 D_800A62B8[];
extern s32 D_800A62C4[];
extern s32 D_800A62D0[];
extern s32 D_800A62DC[];
extern s32 D_800A62E8[];
extern s32 D_800A62F4[];
extern s32 D_800A6300[];
extern s32 D_800A630C[];
extern s32 D_800A633C[];
extern s32 D_800A6348[];
extern s32 D_800A6354[];
extern s32 D_800A6360[];
extern s32 D_800A636C[];
extern s32 D_800A6378[];
extern s32 D_800A6384[];
extern s32 D_800A6390[];
extern s32 D_800A63C0[];
extern s32 D_800A63CC[];
extern s32 D_800A63D8[];
extern s32 D_800A63E4[];
extern s32 D_800A63F0[];
extern s32 D_800A63FC[];
extern s32 D_800A6408[];
extern s32 D_800A6414[];
extern s32 D_800A6444[];
extern s32 D_800A6450[];
extern s32 D_800A645C[];
extern s32 D_800A6468[];
extern s32 D_800A6474[];
extern s32 D_800A6480[];
extern s32 D_800A648C[];
extern s32 D_800A6498[];
extern s32 D_800A64C8[];
extern s32 D_800A64D4[];
extern s32 D_800A64E0[];
extern s32 D_800A64EC[];
extern s32 D_800A64F8[];
extern s32 D_800A6504[];
extern s32 D_800A6510[];
extern s32 D_800A651C[];
extern s32 D_800A654C[];
extern s32 D_800A6558[];
extern s32 D_800A6564[];
extern s32 D_800A6570[];
extern s32 D_800A657C[];
extern s32 D_800A6588[];
extern s32 D_800A6594[];
extern s32 D_800A65A0[];
extern s32 D_800A65D0[];
extern s32 D_800A65DC[];
extern s32 D_800A65E8[];
extern s32 D_800A65F4[];
extern s32 D_800A6600[];
extern s32 D_800A660C[];
extern s32 D_800A6618[];
extern s32 D_800A6624[];
extern s32 D_800A6654[];
extern s32 D_800A6660[];
extern s32 D_800A666C[];
extern s32 D_800A6678[];
extern s32 D_800A6684[];
extern s32 D_800A6690[];
extern s32 D_800A669C[];
extern s32 D_800A66A8[];
extern s32 D_800A66D8[];
extern s32 D_800A66E4[];
extern s32 D_800A66F0[];
extern s32 D_800A66FC[];
extern s32 D_800A6708[];
extern s32 D_800A6714[];
extern s32 D_800A6720[];
extern s32 D_800A672C[];
extern s32 D_800A675C[];
extern s32 D_800A6768[];
extern s32 D_800A6774[];
extern s32 D_800A6780[];
extern s32 D_800A678C[];
extern s32 D_800A6798[];
extern s32 D_800A67A4[];
extern s32 D_800A67B0[];
extern s32 D_800A67E0[];
extern s32 D_800A67EC[];
extern s32 D_800A67F8[];
extern s32 D_800A6804[];
extern s32 D_800A6810[];
extern s32 D_800A681C[];
extern s32 D_800A6828[];
extern s32 D_800A6834[];
extern s32 D_800A6864[];
extern s32 D_800A6870[];
extern s32 D_800A687C[];
extern s32 D_800A6888[];
extern s32 D_800A6894[];
extern s32 D_800A68A0[];
extern s32 D_800A68AC[];
extern s32 D_800A68B8[];
extern s32 D_800A68E8[];
extern s32 D_800A68F4[];
extern s32 D_800A6900[];
extern s32 D_800A690C[];
extern s32 D_800A6918[];
extern s32 D_800A6924[];
extern s32 D_800A6930[];
extern s32 D_800A693C[];
extern s32 D_800A696C[];
extern s32 D_800A6978[];
extern s32 D_800A6984[];
extern s32 D_800A6990[];
extern s32 D_800A699C[];
extern s32 D_800A69A8[];
extern s32 D_800A69B4[];
extern s32 D_800A69C0[];
extern s32 D_800A69F0[];
extern s32 D_800A69FC[];
extern s32 D_800A6A08[];
extern s32 D_800A6A14[];
extern s32 D_800A6A20[];
extern s32 D_800A6A2C[];
extern s32 D_800A6A38[];
extern s32 D_800A6A44[];
extern s32 D_800A6A74[];
extern s32 D_800A6A80[];
extern s32 D_800A6A8C[];
extern s32 D_800A6A98[];
extern s32 D_800A6AA4[];
extern s32 D_800A6AB0[];
extern s32 D_800A6ABC[];
extern s32 D_800A6AC8[];
extern s32 D_800A6AF8[];
extern s32 D_800A6B04[];
extern s32 D_800A6B10[];
extern s32 D_800A6B1C[];
extern s32 D_800A6B28[];
extern s32 D_800A6B34[];
extern s32 D_800A6B40[];
extern s32 D_800A6B4C[];
extern s32 D_800A6B7C[];
extern s32 D_800A6B88[];
extern s32 D_800A6B94[];
extern s32 D_800A6BA0[];
extern s32 D_800A6BAC[];
extern s32 D_800A6BB8[];
extern s32 D_800A6BC4[];
extern s32 D_800A6BD0[];
extern s32 D_800A6C00[];
extern s32 D_800A6C0C[];
extern s32 D_800A6C18[];
extern s32 D_800A6C24[];
extern s32 D_800A6C30[];
extern s32 D_800A6C3C[];
extern s32 D_800A6C48[];
extern s32 D_800A6C54[];
extern s32 D_800A6C84[];
extern s32 D_800A6C90[];
extern s32 D_800A6C9C[];
extern s32 D_800A6CA8[];
extern s32 D_800A6CB4[];
extern s32 D_800A6CC0[];
extern s32 D_800A6CCC[];
extern s32 D_800A6CD8[];
extern s32 D_800A6D08[];
extern s32 D_800A6D14[];
extern s32 D_800A6D20[];
extern s32 D_800A6D2C[];
extern s32 D_800A6D38[];
extern s32 D_800A6D44[];
extern s32 D_800A6D50[];
extern s32 D_800A6D5C[];
extern s32 D_800A6D8C[];
extern s32 D_800A6D98[];
extern s32 D_800A6DA4[];
extern s32 D_800A6DB0[];
extern s32 D_800A6DBC[];
extern s32 D_800A6DC8[];
extern s32 D_800A6DD4[];
extern s32 D_800A6DE0[];
extern s32 D_800A6E10[];
extern s32 D_800A6E1C[];
extern s32 D_800A6E28[];
extern s32 D_800A6E34[];
extern s32 D_800A6E40[];
extern s32 D_800A6E4C[];
extern s32 D_800A6E58[];
extern s32 D_800A6E64[];
extern s32 D_800A6E94[];
extern s32 D_800A6EA0[];
extern s32 D_800A6EAC[];
extern s32 D_800A6EB8[];
extern s32 D_800A6EC4[];
extern s32 D_800A6ED0[];
extern s32 D_800A6EDC[];
extern s32 D_800A6EE8[];
extern s32 D_800A6F18[];
extern s32 D_800A6F24[];
extern s32 D_800A6F30[];
extern s32 D_800A6F3C[];
extern s32 D_800A6F48[];
extern s32 D_800A6F54[];
extern s32 D_800A6F60[];
extern s32 D_800A6F6C[];
extern s32 D_800A6F9C[];
extern s32 D_800A6FA8[];
extern s32 D_800A6FB4[];
extern s32 D_800A6FC0[];
extern s32 D_800A6FCC[];
extern s32 D_800A6FD8[];
extern s32 D_800A6FE4[];
extern s32 D_800A6FF0[];
extern s32 D_800A7020[];
extern s32 D_800A702C[];
extern s32 D_800A7038[];
extern s32 D_800A7044[];
extern s32 D_800A7050[];
extern s32 D_800A705C[];
extern s32 D_800A7068[];
extern s32 D_800A7074[];
extern s32 D_800A70A4[];
extern s32 D_800A70B0[];
extern s32 D_800A70BC[];
extern s32 D_800A70C8[];
extern s32 D_800A70D4[];
extern s32 D_800A70E0[];
extern s32 D_800A70EC[];
extern s32 D_800A70F8[];
extern s32 D_800A7128[];
extern s32 D_800A7134[];
extern s32 D_800A7140[];
extern s32 D_800A714C[];
extern s32 D_800A7158[];
extern s32 D_800A7164[];
extern s32 D_800A7170[];
extern s32 D_800A717C[];
extern s32 D_800A71AC[];
extern s32 D_800A71B8[];
extern s32 D_800A71C4[];
extern s32 D_800A71D0[];
extern s32 D_800A71DC[];
extern s32 D_800A71E8[];
extern s32 D_800A71F4[];
extern s32 D_800A7200[];
extern s32 D_800A7230[];
extern s32 D_800A723C[];
extern s32 D_800A7248[];
extern s32 D_800A7254[];
extern s32 D_800A7260[];
extern s32 D_800A726C[];
extern s32 D_800A7278[];
extern s32 D_800A7284[];
extern s32 D_800A72B4[];
extern s32 D_800A72C0[];
extern s32 D_800A72CC[];
extern s32 D_800A72D8[];
extern s32 D_800A72E4[];
extern s32 D_800A72F0[];
extern s32 D_800A72FC[];
extern s32 D_800A7308[];
extern s32 D_800A7338[];
extern s32 D_800A7344[];
extern s32 D_800A7350[];
extern s32 D_800A735C[];
extern s32 D_800A7368[];
extern s32 D_800A7374[];
extern s32 D_800A7380[];
extern s32 D_800A738C[];
extern s32 D_800A73BC[];
extern s32 D_800A73C8[];
extern s32 D_800A73D4[];
extern s32 D_800A73E0[];
extern s32 D_800A73EC[];
extern s32 D_800A73F8[];
extern s32 D_800A7404[];
extern s32 D_800A7410[];
extern s32 D_800A7440[];
extern s32 D_800A744C[];
extern s32 D_800A7458[];
extern s32 D_800A7464[];
extern s32 D_800A7470[];
extern s32 D_800A747C[];
extern s32 D_800A7488[];
extern s32 D_800A7494[];
extern s32 D_800A74C4[];
extern s32 D_800A74D0[];
extern s32 D_800A74DC[];
extern s32 D_800A74E8[];
extern s32 D_800A74F4[];
extern s32 D_800A7500[];
extern s32 D_800A750C[];
extern s32 D_800A7518[];
extern s32 D_800A7548[];
extern s32 D_800A7554[];
extern s32 D_800A7560[];
extern s32 D_800A756C[];
extern s32 D_800A7578[];
extern s32 D_800A7584[];
extern s32 D_800A7590[];
extern s32 D_800A759C[];
extern s32 D_800A75CC[];
extern s32 D_800A75D8[];
extern s32 D_800A75E4[];
extern s32 D_800A75F0[];
extern s32 D_800A75FC[];
extern s32 D_800A7608[];
extern s32 D_800A7614[];
extern s32 D_800A7620[];
extern s32 D_800A7650[];
extern s32 D_800A765C[];
extern s32 D_800A7668[];
extern s32 D_800A7674[];
extern s32 D_800A7680[];
extern s32 D_800A768C[];
extern s32 D_800A7698[];
extern s32 D_800A76A4[];
extern s32 D_800A76D4[];
extern s32 D_800A76E0[];
extern s32 D_800A76EC[];
extern s32 D_800A76F8[];
extern s32 D_800A7704[];
extern s32 D_800A7710[];
extern s32 D_800A771C[];
extern s32 D_800A7728[];
extern s32 D_800A7758[];
extern s32 D_800A7764[];
extern s32 D_800A7770[];
extern s32 D_800A777C[];
extern s32 D_800A7788[];
extern s32 D_800A7794[];
extern s32 D_800A77A0[];
extern s32 D_800A77AC[];
extern s32 D_800A77DC[];
extern s32 D_800A77E8[];
extern s32 D_800A77F4[];
extern s32 D_800A7800[];
extern s32 D_800A780C[];
extern s32 D_800A7818[];
extern s32 D_800A7824[];
extern s32 D_800A7830[];
extern s32 D_800A7860[];
extern s32 D_800A786C[];
extern s32 D_800A7878[];
extern s32 D_800A7884[];
extern s32 D_800A7890[];
extern s32 D_800A789C[];
extern s32 D_800A78A8[];
extern s32 D_800A78B4[];
extern s32 D_800A78E4[];
extern s32 D_800A78F0[];
extern s32 D_800A78FC[];
extern s32 D_800A7908[];
extern s32 D_800A7914[];
extern s32 D_800A7920[];
extern s32 D_800A792C[];
extern s32 D_800A7938[];
extern s32 D_800A7968[];
extern s32 D_800A7974[];
extern s32 D_800A7980[];
extern s32 D_800A798C[];
extern s32 D_800A7998[];
extern s32 D_800A79A4[];
extern s32 D_800A79B0[];
extern s32 D_800A79BC[];
extern s32 D_800A79EC[];
extern s32 D_800A79F8[];
extern s32 D_800A7A04[];
extern s32 D_800A7A10[];
extern s32 D_800A7A1C[];
extern s32 D_800A7A28[];
extern s32 D_800A7A34[];
extern s32 D_800A7A40[];
extern s32 D_800A7A70[];
extern s32 D_800A7A7C[];
extern s32 D_800A7A88[];
extern s32 D_800A7A94[];
extern s32 D_800A7AA0[];
extern s32 D_800A7AAC[];
extern s32 D_800A7AB8[];
extern s32 D_800A7AC4[];
extern s32 D_800A7AF4[];
extern s32 D_800A7B00[];
extern s32 D_800A7B0C[];
extern s32 D_800A7B18[];
extern s32 D_800A7B24[];
extern s32 D_800A7B30[];
extern s32 D_800A7B3C[];
extern s32 D_800A7B48[];
extern s32 D_800A7B78[];
extern s32 D_800A7B84[];
extern s32 D_800A7B90[];
extern s32 D_800A7B9C[];
extern s32 D_800A7BA8[];
extern s32 D_800A7BB4[];
extern s32 D_800A7BC0[];
extern s32 D_800A7BCC[];
extern s32 D_800A7BFC[];
extern s32 D_800A7C08[];
extern s32 D_800A7C14[];
extern s32 D_800A7C20[];
extern s32 D_800A7C2C[];
extern s32 D_800A7C38[];
extern s32 D_800A7C44[];
extern s32 D_800A7C50[];
extern s32 D_800A7C80[];
extern s32 D_800A7C8C[];
extern s32 D_800A7C98[];
extern s32 D_800A7CA4[];
extern s32 D_800A7CB0[];
extern s32 D_800A7CBC[];
extern s32 D_800A7CC8[];
extern s32 D_800A7CD4[];
extern s32 D_800A7D04[];
extern s32 D_800A7D10[];
extern s32 D_800A7D1C[];
extern s32 D_800A7D28[];
extern s32 D_800A7D34[];
extern s32 D_800A7D40[];
extern s32 D_800A7D4C[];
extern s32 D_800A7D58[];
extern s32 D_800A7D88[];
extern s32 D_800A7D94[];
extern s32 D_800A7DA0[];
extern s32 D_800A7DAC[];
extern s32 D_800A7DB8[];
extern s32 D_800A7DC4[];
extern s32 D_800A7DD0[];
extern s32 D_800A7DDC[];
extern s32 D_800A7E0C[];
extern s32 D_800A7E18[];
extern s32 D_800A7E24[];
extern s32 D_800A7E30[];
extern s32 D_800A7E3C[];
extern s32 D_800A7E48[];
extern s32 D_800A7E54[];
extern s32 D_800A7E60[];
extern s32 D_800A7E90[];
extern s32 D_800A7E9C[];
extern s32 D_800A7EA8[];
extern s32 D_800A7EB4[];
extern s32 D_800A7EC0[];
extern s32 D_800A7ECC[];
extern s32 D_800A7ED8[];
extern s32 D_800A7EE4[];
extern s32 D_800A7F14[];
extern s32 D_800A7F20[];
extern s32 D_800A7F2C[];
extern s32 D_800A7F38[];
extern s32 D_800A7F44[];
extern s32 D_800A7F50[];
extern s32 D_800A7F5C[];
extern s32 D_800A7F68[];
extern s32 D_800A7F98[];
extern s32 D_800A7FA4[];
extern s32 D_800A7FB0[];
extern s32 D_800A7FBC[];
extern s32 D_800A7FC8[];
extern s32 D_800A7FD4[];
extern s32 D_800A7FE0[];
extern s32 D_800A7FEC[];
extern s32 D_800A801C[];
extern s32 D_800A8028[];
extern s32 D_800A8034[];
extern s32 D_800A8040[];
extern s32 D_800A804C[];
extern s32 D_800A8058[];
extern s32 D_800A8064[];
extern s32 D_800A8070[];
extern s32 D_800A80A0[];
extern s32 D_800A80AC[];
extern s32 D_800A80B8[];
extern s32 D_800A80C4[];
extern s32 D_800A80D0[];
extern s32 D_800A80DC[];
extern s32 D_800A80E8[];
extern s32 D_800A80F4[];
extern s32 D_800A8124[];
extern s32 D_800A8130[];
extern s32 D_800A813C[];
extern s32 D_800A8148[];
extern s32 D_800A8154[];
extern s32 D_800A8160[];
extern s32 D_800A816C[];
extern s32 D_800A8178[];
extern s32 D_800A81A8[];
extern s32 D_800A81B4[];
extern s32 D_800A81C0[];
extern s32 D_800A81CC[];
extern s32 D_800A81D8[];
extern s32 D_800A81E4[];
extern s32 D_800A81F0[];
extern s32 D_800A81FC[];
extern s32 D_800A822C[];
extern s32 D_800A8238[];
extern s32 D_800A8244[];
extern s32 D_800A8250[];
extern s32 D_800A825C[];
extern s32 D_800A8268[];
extern s32 D_800A8274[];
extern s32 D_800A8280[];
extern s32 D_800A82B0[];
extern s32 D_800A82BC[];
extern s32 D_800A82C8[];
extern s32 D_800A82D4[];
extern s32 D_800A82E0[];
extern s32 D_800A82EC[];
extern s32 D_800A82F8[];
extern s32 D_800A8304[];
extern s32 D_800A8334[];
extern s32 D_800A8340[];
extern s32 D_800A834C[];
extern s32 D_800A8358[];
extern s32 D_800A8364[];
extern s32 D_800A8370[];
extern s32 D_800A837C[];
extern s32 D_800A8388[];
extern s32 D_800A83B8[];
extern s32 D_800A83C4[];
extern s32 D_800A83D0[];
extern s32 D_800A83DC[];
extern s32 D_800A83E8[];
extern s32 D_800A83F4[];
extern s32 D_800A8400[];
extern s32 D_800A840C[];
extern s32 D_800A843C[];
extern s32 D_800A8448[];
extern s32 D_800A8454[];
extern s32 D_800A8460[];
extern s32 D_800A846C[];
extern s32 D_800A8478[];
extern s32 D_800A8484[];
extern s32 D_800A8490[];
extern s32 D_800A84C0[];
extern s32 D_800A84CC[];
extern s32 D_800A84D8[];
extern s32 D_800A84E4[];
extern s32 D_800A84F0[];
extern s32 D_800A84FC[];
extern s32 D_800A8508[];
extern s32 D_800A8514[];
extern s32 D_800A8544[];
extern s32 D_800A8550[];
extern s32 D_800A855C[];
extern s32 D_800A8568[];
extern s32 D_800A8574[];
extern s32 D_800A8580[];
extern s32 D_800A858C[];
extern s32 D_800A8598[];
extern s32 D_800A85C8[];
extern s32 D_800A85D4[];
extern s32 D_800A85E0[];
extern s32 D_800A85EC[];
extern s32 D_800A85F8[];
extern s32 D_800A8604[];
extern s32 D_800A8610[];
extern s32 D_800A861C[];
extern s32 D_800A864C[];
extern s32 D_800A8658[];
extern s32 D_800A8664[];
extern s32 D_800A8670[];
extern s32 D_800A867C[];
extern s32 D_800A8688[];
extern s32 D_800A8694[];
extern s32 D_800A86A0[];
extern s32 D_800A86D0[];
extern s32 D_800A86DC[];
extern s32 D_800A86E8[];
extern s32 D_800A86F4[];
extern s32 D_800A8700[];
extern s32 D_800A870C[];
extern s32 D_800A8718[];
extern s32 D_800A8724[];
extern s32 D_800A8754[];
extern s32 D_800A8760[];
extern s32 D_800A876C[];
extern s32 D_800A8778[];
extern s32 D_800A8784[];
extern s32 D_800A8790[];
extern s32 D_800A879C[];
extern s32 D_800A87A8[];
extern s32 D_800A87D8[];
extern s32 D_800A87E4[];
extern s32 D_800A87F0[];
extern s32 D_800A87FC[];
extern s32 D_800A8808[];
extern s32 D_800A8814[];
extern s32 D_800A8820[];
extern s32 D_800A882C[];
extern s32 D_800A885C[];
extern s32 D_800A8868[];
extern s32 D_800A8874[];
extern s32 D_800A8880[];
extern s32 D_800A888C[];
extern s32 D_800A8898[];
extern s32 D_800A88A4[];
extern s32 D_800A88B0[];
extern s32 D_800A59D0[];
extern s32 D_800A5A54[];
extern s32 D_800A5AD8[];
extern s32 D_800A5B5C[];
extern s32 D_800A5BE0[];
extern s32 D_800A5C64[];
extern s32 D_800A5CE8[];
extern s32 D_800A5D6C[];
extern s32 D_800A5DF0[];
extern s32 D_800A5E74[];
extern s32 D_800A5EF8[];
extern s32 D_800A5F7C[];
extern s32 D_800A6000[];
extern s32 D_800A6084[];
extern s32 D_800A6108[];
extern s32 D_800A618C[];
extern s32 D_800A6210[];
extern s32 D_800A6294[];
extern s32 D_800A6318[];
extern s32 D_800A639C[];
extern s32 D_800A6420[];
extern s32 D_800A64A4[];
extern s32 D_800A6528[];
extern s32 D_800A65AC[];
extern s32 D_800A6630[];
extern s32 D_800A66B4[];
extern s32 D_800A6738[];
extern s32 D_800A67BC[];
extern s32 D_800A6840[];
extern s32 D_800A68C4[];
extern s32 D_800A6948[];
extern s32 D_800A69CC[];
extern s32 D_800A6A50[];
extern s32 D_800A6AD4[];
extern s32 D_800A6B58[];
extern s32 D_800A6BDC[];
extern s32 D_800A6C60[];
extern s32 D_800A6CE4[];
extern s32 D_800A6D68[];
extern s32 D_800A6DEC[];
extern s32 D_800A6E70[];
extern s32 D_800A6EF4[];
extern s32 D_800A6F78[];
extern s32 D_800A6FFC[];
extern s32 D_800A7080[];
extern s32 D_800A7104[];
extern s32 D_800A7188[];
extern s32 D_800A720C[];
extern s32 D_800A7290[];
extern s32 D_800A7314[];
extern s32 D_800A7398[];
extern s32 D_800A741C[];
extern s32 D_800A74A0[];
extern s32 D_800A7524[];
extern s32 D_800A75A8[];
extern s32 D_800A762C[];
extern s32 D_800A76B0[];
extern s32 D_800A7734[];
extern s32 D_800A77B8[];
extern s32 D_800A783C[];
extern s32 D_800A78C0[];
extern s32 D_800A7944[];
extern s32 D_800A79C8[];
extern s32 D_800A7A4C[];
extern s32 D_800A7AD0[];
extern s32 D_800A7B54[];
extern s32 D_800A7BD8[];
extern s32 D_800A7C5C[];
extern s32 D_800A7CE0[];
extern s32 D_800A7D64[];
extern s32 D_800A7DE8[];
extern s32 D_800A7E6C[];
extern s32 D_800A7EF0[];
extern s32 D_800A7F74[];
extern s32 D_800A7FF8[];
extern s32 D_800A807C[];
extern s32 D_800A8100[];
extern s32 D_800A8184[];
extern s32 D_800A8208[];
extern s32 D_800A828C[];
extern s32 D_800A8310[];
extern s32 D_800A8394[];
extern s32 D_800A8418[];
extern s32 D_800A849C[];
extern s32 D_800A8520[];
extern s32 D_800A85A4[];
extern s32 D_800A8628[];
extern s32 D_800A86AC[];
extern s32 D_800A8730[];
extern s32 D_800A87B4[];
extern s32 D_800A8838[];
extern s32 D_800A88BC[];
extern s32 D_800A8E8C[];
extern s32 D_800A8C94[];
extern s32 D_800A8E98[];
extern s32 D_800A8CAC[];
extern s32 D_800A8EA4[];
extern s32 D_800A8CC4[];
extern s32 D_800A8EB0[];
extern s32 D_800A8CDC[];
extern s32 D_800A8EBC[];
extern s32 D_800A8CF4[];
extern s32 D_800A8EC8[];
extern s32 D_800A8D0C[];
extern s32 D_800A8ED4[];
extern s32 D_800A8D24[];
extern s32 D_800A8EE0[];
extern s32 D_800A8D3C[];
extern s32 D_800A8EEC[];
extern s32 D_800A8D54[];
extern s32 D_800A8EF8[];
extern s32 D_800A8D6C[];
extern s32 D_800A8F04[];
extern s32 D_800A8D84[];
extern s32 D_800A8F10[];
extern s32 D_800A8D9C[];
extern s32 D_800A8F1C[];
extern s32 D_800A8DB4[];
extern s32 D_800A8F28[];
extern s32 D_800A8DCC[];
extern s32 D_800A8F34[];
extern s32 D_800A8DE4[];
extern s32 D_800A8F40[];
extern s32 D_800A8DFC[];
extern s32 D_800A8F4C[];
extern s32 D_800A8E14[];
extern s32 D_800A8F58[];
extern s32 D_800A8E2C[];
extern s32 D_800A8F64[];
extern s32 D_800A8E44[];
extern s32 D_800A8F70[];
extern s32 D_800A8E5C[];
extern s32 D_800A8F7C[];
extern s32 D_800A8E74[];
extern s32 D_800A8F88[];
extern s32 D_800A8F94[];
extern s32 D_800A8FA0[];
extern s32 D_800A8FAC[];
extern s32 D_800A8FB8[];
extern s32 D_800A8FC4[];
extern s32 D_800A8FD0[];
extern s32 D_800A8FDC[];
extern s32 D_800A8FE8[];
extern s32 D_800A8FF4[];
extern s32 D_800A9000[];
extern s32 D_800A900C[];
extern s32 D_800A9018[];
extern s32 D_800A9024[];
extern s32 D_800A9030[];
extern s32 D_800A903C[];
extern s32 D_800A9048[];
extern s32 D_800A905C[];
extern s32 D_800A9070[];
extern s32 D_800A9084[];
extern s32 D_800A9098[];
extern s32 D_800A90AC[];
extern s32 D_800A90C0[];
extern s32 D_800A90D4[];
extern s32 D_800A90E8[];
extern s32 D_800A90FC[];
extern s32 D_800A9110[];
extern s32 D_800A9124[];
extern s32 D_800A9138[];
extern s32 D_800A914C[];
extern s32 D_800A9160[];
extern s32 D_800A9174[];
extern s32 D_800A9188[];
extern s32 D_800A919C[];
extern s32 D_800A91B0[];
extern s32 D_800A91C4[];
extern s32 D_800A91D8[];
extern s32 D_800A91EC[];
extern s32 D_800A9200[];
extern s32 D_800A9214[];
extern s32 D_800A9228[];
extern s32 D_800A923C[];
extern s32 D_800A9250[];
extern s32 D_800A9264[];
extern s32 D_800A9278[];
extern s32 D_800A928C[];
extern s32 D_800A92A0[];
extern s32 D_800A92B4[];
extern s32 D_800A92C8[];
extern s32 D_800A92DC[];
extern s32 D_800A92F0[];
extern s32 D_800A9304[];
extern s32 D_800A9318[];
extern s32 D_800A932C[];

StagePoint D_800A4F94 = { 0x2E9, 1, 2, 0x240, 240, 1, NULL };
StagePoint D_800A4FA4 = { 0x2ED, 1, 1, 0x350, 0x1F8, 5, &D_800A4F94 };
StagePoint D_800A4FB4 = { 0x2ED, 1, 2, 224, 192, 5, &D_800A4FA4 };
StagePoints D_800A4FC4 = { 1, 1, &D_800A4FB4 };
StagePoint D_800A4FCC = { 0x2ED, 2, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A4FDC = { 0x2EC, 2, 1, 240, 0x1D8, 5, &D_800A4FCC };
StagePoint D_800A4FEC = { 0x2ED, 2, 1, 224, 192, 5, &D_800A4FDC };
StagePoints D_800A4FFC = { 2, 1, &D_800A4FEC };
StagePoint D_800A5004 = { 0x2E9, 2, 3, 0x240, 240, 1, NULL };
StagePoint D_800A5014 = { 0x2EA, 2, 2, 224, 0x200, 5, &D_800A5004 };
StagePoint D_800A5024 = { 0x2ED, 2, 2, 224, 192, 5, &D_800A5014 };
StagePoints D_800A5034 = { 2, 2, &D_800A5024 };
StagePoint D_800A503C = { 0x2ED, 3, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A504C = { 0x2EC, 3, 1, 240, 0x1D8, 5, &D_800A503C };
StagePoint D_800A505C = { 0x2ED, 3, 1, 224, 192, 5, &D_800A504C };
StagePoints D_800A506C = { 3, 1, &D_800A505C };
StagePoint D_800A5074 = { 0x2ED, 3, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A5084 = { 0x2ED, 3, 1, 0x350, 0x1F8, 5, &D_800A5074 };
StagePoint D_800A5094 = { 0x2E8, 3, 3, 176, 0x168, 5, &D_800A5084 };
StagePoints D_800A50A4 = { 3, 2, &D_800A5094 };
StagePoint D_800A50AC = { 0x2E9, 3, 2, 0x240, 240, 1, NULL };
StagePoint D_800A50BC = { 0x2ED, 3, 2, 0x350, 0x1F8, 5, &D_800A50AC };
StagePoint D_800A50CC = { 0x2ED, 3, 3, 224, 192, 5, &D_800A50BC };
StagePoints D_800A50DC = { 3, 3, &D_800A50CC };
StagePoint D_800A50E4 = { 0x2E9, 3, 3, 0x240, 240, 1, NULL };
StagePoint D_800A50F4 = { 0x2ED, 3, 3, 0x350, 0x1F8, 5, &D_800A50E4 };
StagePoint D_800A5104 = { 0x2ED, 3, 4, 224, 192, 5, &D_800A50F4 };
StagePoints D_800A5114 = { 3, 4, &D_800A5104 };
StagePoint D_800A511C = { 0x2E9, 3, 4, 0x240, 240, 1, NULL };
StagePoint D_800A512C = { 0x2ED, 3, 4, 0x350, 0x1F8, 5, &D_800A511C };
StagePoint D_800A513C = { 0x2E8, 3, 5, 176, 0x168, 5, &D_800A512C };
StagePoints D_800A514C = { 3, 5, &D_800A513C };
StagePoint D_800A5154 = { 0x2ED, 4, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5164 = { 0x2E8, 4, 1, 176, 0x168, 5, &D_800A5154 };
StagePoint D_800A5174 = { 0x2EA, 4, 1, 224, 0x200, 5, &D_800A5164 };
StagePoints D_800A5184 = { 4, 1, &D_800A5174 };
StagePoint D_800A518C = { 0x2ED, 4, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A519C = { 0x2E8, 4, 2, 176, 0x168, 5, &D_800A518C };
StagePoint D_800A51AC = { 0x2ED, 4, 1, 224, 192, 5, &D_800A519C };
StagePoints D_800A51BC = { 4, 2, &D_800A51AC };
StagePoint D_800A51C4 = { 0x2ED, 5, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A51D4 = { 0x2E8, 5, 1, 176, 0x168, 5, &D_800A51C4 };
StagePoint D_800A51E4 = { 0x2ED, 5, 1, 224, 192, 5, &D_800A51D4 };
StagePoints D_800A51F4 = { 5, 1, &D_800A51E4 };
StagePoint D_800A51FC = { 0x2ED, 5, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A520C = { 0x2ED, 5, 1, 0x350, 0x1F8, 5, &D_800A51FC };
StagePoint D_800A521C = { 0x2E8, 5, 2, 176, 0x168, 5, &D_800A520C };
StagePoints D_800A522C = { 5, 2, &D_800A521C };
StagePoint D_800A5234 = { 0x2E9, 5, 2, 0x240, 240, 1, NULL };
StagePoint D_800A5244 = { 0x2ED, 5, 2, 0x350, 0x1F8, 5, &D_800A5234 };
StagePoint D_800A5254 = { 0x2ED, 5, 3, 224, 192, 5, &D_800A5244 };
StagePoints D_800A5264 = { 5, 3, &D_800A5254 };
StagePoint D_800A526C = { 0x2E9, 5, 3, 0x240, 240, 1, NULL };
StagePoint D_800A527C = { 0x2ED, 5, 3, 0x350, 0x1F8, 5, &D_800A526C };
StagePoint D_800A528C = { 0x2ED, 5, 4, 224, 192, 5, &D_800A527C };
StagePoints D_800A529C = { 5, 4, &D_800A528C };
StagePoint D_800A52A4 = { 0x2E9, 6, 1, 0x240, 240, 1, NULL };
StagePoint D_800A52B4 = { 0x2EC, 6, 1, 240, 0x1D8, 5, &D_800A52A4 };
StagePoint D_800A52C4 = { 0x2ED, 6, 1, 224, 192, 5, &D_800A52B4 };
StagePoints D_800A52D4 = { 6, 1, &D_800A52C4 };
StagePoint D_800A52DC = { 0x2EE, 6, 3, 0x130, 200, 1, NULL };
StagePoint D_800A52EC = { 0x2ED, 6, 1, 0x350, 0x1F8, 5, &D_800A52DC };
StagePoint D_800A52FC = { 0x2ED, 6, 2, 224, 192, 5, &D_800A52EC };
StagePoints D_800A530C = { 6, 2, &D_800A52FC };
StagePoint D_800A5314 = { 0x2E9, 6, 2, 0x240, 240, 1, NULL };
StagePoint D_800A5324 = { 0x2EE, 6, 2, 224, 0x240, 5, &D_800A5314 };
StagePoint D_800A5334 = { 0x2EC, 6, 2, 240, 0x1D8, 5, &D_800A5324 };
StagePoints D_800A5344 = { 6, 3, &D_800A5334 };
StagePoint D_800A534C = { 0x2EC, 7, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A535C = { 0x2EC, 7, 1, 240, 0x1D8, 5, &D_800A534C };
StagePoint D_800A536C = { 0x2EC, 7, 2, 240, 0x1D8, 5, &D_800A535C };
StagePoints D_800A537C = { 7, 1, &D_800A536C };
StagePoint D_800A5384 = { 0x2EB, 7, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5394 = { 0x2EC, 7, 3, 240, 0x1D8, 5, &D_800A5384 };
StagePoint D_800A53A4 = { 0x2E8, 7, 3, 176, 0x168, 5, &D_800A5394 };
StagePoints D_800A53B4 = { 7, 2, &D_800A53A4 };
StagePoint D_800A53BC = { 0x2E9, 8, 2, 0x240, 240, 1, NULL };
StagePoint D_800A53CC = { 0x2ED, 8, 1, 0x350, 0x1F8, 5, &D_800A53BC };
StagePoint D_800A53DC = { 0x2ED, 8, 2, 224, 192, 5, &D_800A53CC };
StagePoints D_800A53EC = { 8, 1, &D_800A53DC };
StagePoint D_800A53F4 = { 0x2ED, 9, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A5404 = { 0x2EC, 9, 1, 240, 0x1D8, 5, &D_800A53F4 };
StagePoint D_800A5414 = { 0x2ED, 9, 1, 224, 192, 5, &D_800A5404 };
StagePoints D_800A5424 = { 9, 1, &D_800A5414 };
StagePoint D_800A542C = { 0x2E9, 9, 2, 0x240, 240, 1, NULL };
StagePoint D_800A543C = { 0x2EA, 9, 2, 224, 0x200, 5, &D_800A542C };
StagePoint D_800A544C = { 0x2ED, 9, 2, 224, 192, 5, &D_800A543C };
StagePoints D_800A545C = { 9, 2, &D_800A544C };
StagePoint D_800A5464 = { 0x2E9, 10, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5474 = { 0x2EC, 10, 1, 240, 0x1D8, 5, &D_800A5464 };
StagePoint D_800A5484 = { 0x2ED, 10, 1, 224, 192, 5, &D_800A5474 };
StagePoints D_800A5494 = { 10, 1, &D_800A5484 };
StagePoint D_800A549C = { 0x2E9, 11, 1, 0x240, 240, 1, NULL };
StagePoint D_800A54AC = { 0x2EC, 11, 1, 240, 0x1D8, 5, &D_800A549C };
StagePoint D_800A54BC = { 0x2ED, 11, 1, 224, 192, 5, &D_800A54AC };
StagePoints D_800A54CC = { 11, 1, &D_800A54BC };
StagePoint D_800A54D4 = { 0x2EC, 12, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A54E4 = { 0x2ED, 12, 1, 0x350, 0x1F8, 5, &D_800A54D4 };
StagePoint D_800A54F4 = { 0x2ED, 12, 2, 224, 192, 5, &D_800A54E4 };
StagePoints D_800A5504 = { 12, 1, &D_800A54F4 };
StagePoint D_800A550C = { 0x2EC, 12, 5, 0x3B0, 120, 1, NULL };
StagePoint D_800A551C = { 0x2ED, 12, 2, 0x350, 0x1F8, 5, &D_800A550C };
StagePoint D_800A552C = { 0x2EC, 12, 2, 240, 0x1D8, 5, &D_800A551C };
StagePoints D_800A553C = { 12, 2, &D_800A552C };
StagePoint D_800A5544 = { 0x2EC, 13, 5, 0x3B0, 120, 1, NULL };
StagePoint D_800A5554 = { 0x2ED, 13, 1, 0x350, 0x1F8, 5, &D_800A5544 };
StagePoint D_800A5564 = { 0x2ED, 13, 2, 224, 192, 5, &D_800A5554 };
StagePoints D_800A5574 = { 13, 1, &D_800A5564 };
StagePoint D_800A557C = { 0x2EC, 13, 6, 0x3B0, 120, 1, NULL };
StagePoint D_800A558C = { 0x2ED, 13, 2, 0x350, 0x1F8, 5, &D_800A557C };
StagePoint D_800A559C = { 0x2EC, 13, 2, 240, 0x1D8, 5, &D_800A558C };
StagePoints D_800A55AC = { 13, 2, &D_800A559C };
StagePoint D_800A55B4 = { 0x2ED, 16, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A55C4 = { 0x2EA, 16, 1, 224, 0x200, 5, &D_800A55B4 };
StagePoint D_800A55D4 = { 0x2E8, 16, 1, 176, 0x168, 5, &D_800A55C4 };
StagePoints D_800A55E4 = { 16, 1, &D_800A55D4 };
StagePoint D_800A55EC = { 0x2EC, 19, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A55FC = { 0x2EA, 19, 2, 224, 0x200, 5, &D_800A55EC };
StagePoint D_800A560C = { 0x2EC, 19, 1, 240, 0x1D8, 5, &D_800A55FC };
StagePoints D_800A561C = { 19, 1, &D_800A560C };
StagePoint D_800A5624 = { 0x2ED, 19, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5634 = { 0x2EC, 19, 2, 240, 0x1D8, 5, &D_800A5624 };
StagePoint D_800A5644 = { 0x2EC, 19, 3, 240, 0x1D8, 5, &D_800A5634 };
StagePoints D_800A5654 = { 19, 2, &D_800A5644 };
StagePoint D_800A565C = { 0x2EC, 20, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A566C = { 0x2EA, 20, 1, 224, 0x200, 5, &D_800A565C };
StagePoint D_800A567C = { 0x2E8, 20, 1, 176, 0x168, 5, &D_800A566C };
StagePoints D_800A568C = { 20, 1, &D_800A567C };
StagePoint D_800A5694 = { 0x2ED, 20, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A56A4 = { 0x2EC, 20, 1, 240, 0x1D8, 5, &D_800A5694 };
StagePoint D_800A56B4 = { 0x2EC, 20, 2, 240, 0x1D8, 5, &D_800A56A4 };
StagePoints D_800A56C4 = { 20, 2, &D_800A56B4 };
StagePoint D_800A56CC = { 0x2EB, 21, 1, 0x240, 160, 1, NULL };
StagePoint D_800A56DC = { 0x2EC, 21, 2, 240, 0x1D8, 5, &D_800A56CC };
StagePoint D_800A56EC = { 0x2E8, 21, 1, 176, 0x168, 5, &D_800A56DC };
StagePoints D_800A56FC = { 21, 1, &D_800A56EC };
StagePoint D_800A5704 = { 0x2EC, 22, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A5714 = { 0x2EC, 22, 1, 240, 0x1D8, 5, &D_800A5704 };
StagePoint D_800A5724 = { 0x2EC, 22, 2, 240, 0x1D8, 5, &D_800A5714 };
StagePoints D_800A5734 = { 22, 1, &D_800A5724 };
StagePoint D_800A573C = { 0x2EB, 23, 1, 0x240, 160, 1, NULL };
StagePoint D_800A574C = { 0x2EC, 23, 3, 240, 0x1D8, 5, &D_800A573C };
StagePoint D_800A575C = { 0x2E8, 23, 2, 176, 0x168, 5, &D_800A574C };
StagePoints D_800A576C = { 23, 1, &D_800A575C };
StagePoint D_800A5774 = { 0x2ED, 25, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A5784 = { 0x2E8, 25, 1, 176, 0x168, 5, &D_800A5774 };
StagePoint D_800A5794 = { 0x2EA, 25, 1, 224, 0x200, 5, &D_800A5784 };
StagePoints D_800A57A4 = { 25, 1, &D_800A5794 };
StagePoint D_800A57AC = { 0x2EC, 28, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A57BC = { 0x2ED, 28, 1, 0x350, 0x1F8, 5, &D_800A57AC };
StagePoint D_800A57CC = { 0x2ED, 28, 2, 224, 192, 5, &D_800A57BC };
StagePoints D_800A57DC = { 28, 1, &D_800A57CC };
StagePoint D_800A57E4 = { 0x2EB, 28, 3, 0x240, 160, 1, NULL };
StagePoint D_800A57F4 = { 0x2ED, 28, 2, 0x350, 0x1F8, 5, &D_800A57E4 };
StagePoint D_800A5804 = { 0x2EC, 28, 2, 240, 0x1D8, 5, &D_800A57F4 };
StagePoints D_800A5814 = { 28, 2, &D_800A5804 };
StagePoint D_800A581C = { 0x2ED, 29, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A582C = { 0x2EC, 29, 1, 240, 0x1D8, 5, &D_800A581C };
StagePoint D_800A583C = { 0x2EC, 29, 2, 240, 0x1D8, 5, &D_800A582C };
StagePoints D_800A584C = { 29, 1, &D_800A583C };
StagePoint D_800A5854 = { 0x2E9, 30, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5864 = { 0x2ED, 30, 1, 0x350, 0x1F8, 5, &D_800A5854 };
StagePoint D_800A5874 = { 0x2ED, 30, 2, 224, 192, 5, &D_800A5864 };
StagePoints D_800A5884 = { 30, 1, &D_800A5874 };
StagePoint D_800A588C = { 0x2EB, 30, 2, 0x240, 160, 1, NULL };
StagePoint D_800A589C = { 0x2ED, 30, 2, 0x350, 0x1F8, 5, &D_800A588C };
StagePoint D_800A58AC = { 0x2EA, 30, 1, 224, 0x200, 5, &D_800A589C };
StagePoints D_800A58BC = { 30, 2, &D_800A58AC };
StagePoints *D_800A58C4[] = {
    &D_800A4FC4, &D_800A4FFC, &D_800A5034, &D_800A506C,
    &D_800A50A4, &D_800A50DC, &D_800A5114, &D_800A514C,
    &D_800A5184, &D_800A51BC, &D_800A51F4, &D_800A522C,
    &D_800A5264, &D_800A529C, &D_800A52D4, &D_800A530C,
    &D_800A5344, &D_800A537C, &D_800A53B4, &D_800A53EC,
    &D_800A5424, &D_800A545C, &D_800A5494, &D_800A54CC,
    &D_800A5504, &D_800A553C, &D_800A5574, &D_800A55AC,
    &D_800A55E4, &D_800A561C, &D_800A5654, &D_800A568C,
    &D_800A56C4, &D_800A56FC, &D_800A5734, &D_800A576C,
    &D_800A57A4, &D_800A57DC, &D_800A5814, &D_800A584C,
    &D_800A5884, &D_800A58BC, NULL,
};
s32 D_800A5970[] = {
    174, 10, 0x60080000,
};
s32 D_800A597C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5988[] = {
    170, 10, 0x60080000,
};
s32 D_800A5994[] = {
    170, 10, 0x60080000,
};
s32 D_800A59A0[] = {
    170, 10, 0x60080000,
};
s32 D_800A59AC[] = {
    170, 10, 0x60080000,
};
s32 D_800A59B8[] = {
    170, 10, 0x60080000,
};
s32 D_800A59C4[] = {
    170, 10, 0x60080000,
};
s32 D_800A59D0[] = {
    1, (s32)D_800A5970, (s32)D_800A597C, (s32)D_800A5988,
    (s32)D_800A5994, (s32)D_800A59A0, (s32)D_800A59AC, (s32)D_800A59B8,
    (s32)D_800A59C4,
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
    0, 0, 0x60040000,
};
s32 D_800A5A24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A54[] = {
    0, (s32)D_800A59F4, (s32)D_800A5A00, (s32)D_800A5A0C,
    (s32)D_800A5A18, (s32)D_800A5A24, (s32)D_800A5A30, (s32)D_800A5A3C,
    (s32)D_800A5A48,
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
    0, (s32)D_800A5A78, (s32)D_800A5A84, (s32)D_800A5A90,
    (s32)D_800A5A9C, (s32)D_800A5AA8, (s32)D_800A5AB4, (s32)D_800A5AC0,
    (s32)D_800A5ACC,
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
    0, (s32)D_800A5AFC, (s32)D_800A5B08, (s32)D_800A5B14,
    (s32)D_800A5B20, (s32)D_800A5B2C, (s32)D_800A5B38, (s32)D_800A5B44,
    (s32)D_800A5B50,
};
s32 D_800A5B80[] = {
    174, 10, 0x60080000,
};
s32 D_800A5B8C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5B98[] = {
    170, 10, 0x60080000,
};
s32 D_800A5BA4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5BB0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5BBC[] = {
    110, 10, 0x60080000,
};
s32 D_800A5BC8[] = {
    110, 10, 0x60080000,
};
s32 D_800A5BD4[] = {
    110, 10, 0x60080000,
};
s32 D_800A5BE0[] = {
    1, (s32)D_800A5B80, (s32)D_800A5B8C, (s32)D_800A5B98,
    (s32)D_800A5BA4, (s32)D_800A5BB0, (s32)D_800A5BBC, (s32)D_800A5BC8,
    (s32)D_800A5BD4,
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
    0, 0, 0x60040000,
};
s32 D_800A5C34[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C40[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C58[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C64[] = {
    0, (s32)D_800A5C04, (s32)D_800A5C10, (s32)D_800A5C1C,
    (s32)D_800A5C28, (s32)D_800A5C34, (s32)D_800A5C40, (s32)D_800A5C4C,
    (s32)D_800A5C58,
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
    0, (s32)D_800A5C88, (s32)D_800A5C94, (s32)D_800A5CA0,
    (s32)D_800A5CAC, (s32)D_800A5CB8, (s32)D_800A5CC4, (s32)D_800A5CD0,
    (s32)D_800A5CDC,
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
    0, (s32)D_800A5D0C, (s32)D_800A5D18, (s32)D_800A5D24,
    (s32)D_800A5D30, (s32)D_800A5D3C, (s32)D_800A5D48, (s32)D_800A5D54,
    (s32)D_800A5D60,
};
s32 D_800A5D90[] = {
    174, 10, 0x60080000,
};
s32 D_800A5D9C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5DA8[] = {
    170, 10, 0x60080000,
};
s32 D_800A5DB4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5DC0[] = {
    182, 10, 0x60080000,
};
s32 D_800A5DCC[] = {
    182, 10, 0x60080000,
};
s32 D_800A5DD8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5DE4[] = {
    71, 10, 0x60080000,
};
s32 D_800A5DF0[] = {
    1, (s32)D_800A5D90, (s32)D_800A5D9C, (s32)D_800A5DA8,
    (s32)D_800A5DB4, (s32)D_800A5DC0, (s32)D_800A5DCC, (s32)D_800A5DD8,
    (s32)D_800A5DE4,
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
    0, 0, 0x60040000,
};
s32 D_800A5E44[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E50[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E74[] = {
    0, (s32)D_800A5E14, (s32)D_800A5E20, (s32)D_800A5E2C,
    (s32)D_800A5E38, (s32)D_800A5E44, (s32)D_800A5E50, (s32)D_800A5E5C,
    (s32)D_800A5E68,
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
    0, (s32)D_800A5E98, (s32)D_800A5EA4, (s32)D_800A5EB0,
    (s32)D_800A5EBC, (s32)D_800A5EC8, (s32)D_800A5ED4, (s32)D_800A5EE0,
    (s32)D_800A5EEC,
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
    0, (s32)D_800A5F1C, (s32)D_800A5F28, (s32)D_800A5F34,
    (s32)D_800A5F40, (s32)D_800A5F4C, (s32)D_800A5F58, (s32)D_800A5F64,
    (s32)D_800A5F70,
};
s32 D_800A5FA0[] = {
    174, 10, 0x60080000,
};
s32 D_800A5FAC[] = {
    174, 10, 0x60080000,
};
s32 D_800A5FB8[] = {
    170, 10, 0x60080000,
};
s32 D_800A5FC4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5FD0[] = {
    182, 10, 0x60080000,
};
s32 D_800A5FDC[] = {
    182, 10, 0x60080000,
};
s32 D_800A5FE8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5FF4[] = {
    71, 10, 0x60080000,
};
s32 D_800A6000[] = {
    1, (s32)D_800A5FA0, (s32)D_800A5FAC, (s32)D_800A5FB8,
    (s32)D_800A5FC4, (s32)D_800A5FD0, (s32)D_800A5FDC, (s32)D_800A5FE8,
    (s32)D_800A5FF4,
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
    0, 0, 0x60040000,
};
s32 D_800A6054[] = {
    0, 0, 0x60040000,
};
s32 D_800A6060[] = {
    0, 0, 0x60040000,
};
s32 D_800A606C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6078[] = {
    0, 0, 0x60040000,
};
s32 D_800A6084[] = {
    0, (s32)D_800A6024, (s32)D_800A6030, (s32)D_800A603C,
    (s32)D_800A6048, (s32)D_800A6054, (s32)D_800A6060, (s32)D_800A606C,
    (s32)D_800A6078,
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
    0, (s32)D_800A60A8, (s32)D_800A60B4, (s32)D_800A60C0,
    (s32)D_800A60CC, (s32)D_800A60D8, (s32)D_800A60E4, (s32)D_800A60F0,
    (s32)D_800A60FC,
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
    0, (s32)D_800A612C, (s32)D_800A6138, (s32)D_800A6144,
    (s32)D_800A6150, (s32)D_800A615C, (s32)D_800A6168, (s32)D_800A6174,
    (s32)D_800A6180,
};
s32 D_800A61B0[] = {
    174, 10, 0x60080000,
};
s32 D_800A61BC[] = {
    170, 10, 0x60080000,
};
s32 D_800A61C8[] = {
    110, 10, 0x60080000,
};
s32 D_800A61D4[] = {
    110, 10, 0x60080000,
};
s32 D_800A61E0[] = {
    182, 10, 0x60080000,
};
s32 D_800A61EC[] = {
    182, 10, 0x60080000,
};
s32 D_800A61F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A6204[] = {
    71, 10, 0x60080000,
};
s32 D_800A6210[] = {
    1, (s32)D_800A61B0, (s32)D_800A61BC, (s32)D_800A61C8,
    (s32)D_800A61D4, (s32)D_800A61E0, (s32)D_800A61EC, (s32)D_800A61F8,
    (s32)D_800A6204,
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
    0, 0, 0x60040000,
};
s32 D_800A6264[] = {
    0, 0, 0x60040000,
};
s32 D_800A6270[] = {
    0, 0, 0x60040000,
};
s32 D_800A627C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6288[] = {
    0, 0, 0x60040000,
};
s32 D_800A6294[] = {
    0, (s32)D_800A6234, (s32)D_800A6240, (s32)D_800A624C,
    (s32)D_800A6258, (s32)D_800A6264, (s32)D_800A6270, (s32)D_800A627C,
    (s32)D_800A6288,
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
    0, (s32)D_800A62B8, (s32)D_800A62C4, (s32)D_800A62D0,
    (s32)D_800A62DC, (s32)D_800A62E8, (s32)D_800A62F4, (s32)D_800A6300,
    (s32)D_800A630C,
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
    0, (s32)D_800A633C, (s32)D_800A6348, (s32)D_800A6354,
    (s32)D_800A6360, (s32)D_800A636C, (s32)D_800A6378, (s32)D_800A6384,
    (s32)D_800A6390,
};
s32 D_800A63C0[] = {
    174, 10, 0x60080000,
};
s32 D_800A63CC[] = {
    170, 10, 0x60080000,
};
s32 D_800A63D8[] = {
    110, 10, 0x60080000,
};
s32 D_800A63E4[] = {
    110, 10, 0x60080000,
};
s32 D_800A63F0[] = {
    182, 10, 0x60080000,
};
s32 D_800A63FC[] = {
    182, 10, 0x60080000,
};
s32 D_800A6408[] = {
    71, 10, 0x60080000,
};
s32 D_800A6414[] = {
    71, 10, 0x60080000,
};
s32 D_800A6420[] = {
    1, (s32)D_800A63C0, (s32)D_800A63CC, (s32)D_800A63D8,
    (s32)D_800A63E4, (s32)D_800A63F0, (s32)D_800A63FC, (s32)D_800A6408,
    (s32)D_800A6414,
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
    0, 0, 0x60040000,
};
s32 D_800A6474[] = {
    0, 0, 0x60040000,
};
s32 D_800A6480[] = {
    0, 0, 0x60040000,
};
s32 D_800A648C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6498[] = {
    0, 0, 0x60040000,
};
s32 D_800A64A4[] = {
    0, (s32)D_800A6444, (s32)D_800A6450, (s32)D_800A645C,
    (s32)D_800A6468, (s32)D_800A6474, (s32)D_800A6480, (s32)D_800A648C,
    (s32)D_800A6498,
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
    0, (s32)D_800A64C8, (s32)D_800A64D4, (s32)D_800A64E0,
    (s32)D_800A64EC, (s32)D_800A64F8, (s32)D_800A6504, (s32)D_800A6510,
    (s32)D_800A651C,
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
    0, (s32)D_800A654C, (s32)D_800A6558, (s32)D_800A6564,
    (s32)D_800A6570, (s32)D_800A657C, (s32)D_800A6588, (s32)D_800A6594,
    (s32)D_800A65A0,
};
s32 D_800A65D0[] = {
    110, 10, 0x60080000,
};
s32 D_800A65DC[] = {
    110, 10, 0x60080000,
};
s32 D_800A65E8[] = {
    110, 10, 0x60080000,
};
s32 D_800A65F4[] = {
    110, 10, 0x60080000,
};
s32 D_800A6600[] = {
    182, 10, 0x60080000,
};
s32 D_800A660C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6618[] = {
    182, 10, 0x60080000,
};
s32 D_800A6624[] = {
    182, 10, 0x60080000,
};
s32 D_800A6630[] = {
    1, (s32)D_800A65D0, (s32)D_800A65DC, (s32)D_800A65E8,
    (s32)D_800A65F4, (s32)D_800A6600, (s32)D_800A660C, (s32)D_800A6618,
    (s32)D_800A6624,
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
    0, 0, 0x60040000,
};
s32 D_800A6684[] = {
    0, 0, 0x60040000,
};
s32 D_800A6690[] = {
    0, 0, 0x60040000,
};
s32 D_800A669C[] = {
    0, 0, 0x60040000,
};
s32 D_800A66A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66B4[] = {
    0, (s32)D_800A6654, (s32)D_800A6660, (s32)D_800A666C,
    (s32)D_800A6678, (s32)D_800A6684, (s32)D_800A6690, (s32)D_800A669C,
    (s32)D_800A66A8,
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
    0, (s32)D_800A66D8, (s32)D_800A66E4, (s32)D_800A66F0,
    (s32)D_800A66FC, (s32)D_800A6708, (s32)D_800A6714, (s32)D_800A6720,
    (s32)D_800A672C,
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
    0, (s32)D_800A675C, (s32)D_800A6768, (s32)D_800A6774,
    (s32)D_800A6780, (s32)D_800A678C, (s32)D_800A6798, (s32)D_800A67A4,
    (s32)D_800A67B0,
};
s32 D_800A67E0[] = {
    182, 10, 0x60080000,
};
s32 D_800A67EC[] = {
    182, 10, 0x60080000,
};
s32 D_800A67F8[] = {
    182, 10, 0x60080000,
};
s32 D_800A6804[] = {
    182, 10, 0x60080000,
};
s32 D_800A6810[] = {
    71, 10, 0x60080000,
};
s32 D_800A681C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6828[] = {
    71, 10, 0x60080000,
};
s32 D_800A6834[] = {
    71, 10, 0x60080000,
};
s32 D_800A6840[] = {
    1, (s32)D_800A67E0, (s32)D_800A67EC, (s32)D_800A67F8,
    (s32)D_800A6804, (s32)D_800A6810, (s32)D_800A681C, (s32)D_800A6828,
    (s32)D_800A6834,
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
    0, 0, 0x60040000,
};
s32 D_800A6894[] = {
    0, 0, 0x60040000,
};
s32 D_800A68A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68C4[] = {
    0, (s32)D_800A6864, (s32)D_800A6870, (s32)D_800A687C,
    (s32)D_800A6888, (s32)D_800A6894, (s32)D_800A68A0, (s32)D_800A68AC,
    (s32)D_800A68B8,
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
    0, (s32)D_800A68E8, (s32)D_800A68F4, (s32)D_800A6900,
    (s32)D_800A690C, (s32)D_800A6918, (s32)D_800A6924, (s32)D_800A6930,
    (s32)D_800A693C,
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
    0, (s32)D_800A696C, (s32)D_800A6978, (s32)D_800A6984,
    (s32)D_800A6990, (s32)D_800A699C, (s32)D_800A69A8, (s32)D_800A69B4,
    (s32)D_800A69C0,
};
s32 D_800A69F0[] = {
    182, 10, 0x60080000,
};
s32 D_800A69FC[] = {
    182, 10, 0x60080000,
};
s32 D_800A6A08[] = {
    182, 10, 0x60080000,
};
s32 D_800A6A14[] = {
    182, 10, 0x60080000,
};
s32 D_800A6A20[] = {
    71, 10, 0x60080000,
};
s32 D_800A6A2C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6A38[] = {
    71, 10, 0x60080000,
};
s32 D_800A6A44[] = {
    71, 10, 0x60080000,
};
s32 D_800A6A50[] = {
    1, (s32)D_800A69F0, (s32)D_800A69FC, (s32)D_800A6A08,
    (s32)D_800A6A14, (s32)D_800A6A20, (s32)D_800A6A2C, (s32)D_800A6A38,
    (s32)D_800A6A44,
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
    0, 0, 0x60040000,
};
s32 D_800A6AA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ABC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AD4[] = {
    0, (s32)D_800A6A74, (s32)D_800A6A80, (s32)D_800A6A8C,
    (s32)D_800A6A98, (s32)D_800A6AA4, (s32)D_800A6AB0, (s32)D_800A6ABC,
    (s32)D_800A6AC8,
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
    0, 0, 0x60040000,
};
s32 D_800A6B28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B34[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B40[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B58[] = {
    0, (s32)D_800A6AF8, (s32)D_800A6B04, (s32)D_800A6B10,
    (s32)D_800A6B1C, (s32)D_800A6B28, (s32)D_800A6B34, (s32)D_800A6B40,
    (s32)D_800A6B4C,
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
    0, 0, 0x60040000,
};
s32 D_800A6BAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BDC[] = {
    0, (s32)D_800A6B7C, (s32)D_800A6B88, (s32)D_800A6B94,
    (s32)D_800A6BA0, (s32)D_800A6BAC, (s32)D_800A6BB8, (s32)D_800A6BC4,
    (s32)D_800A6BD0,
};
s32 D_800A6C00[] = {
    174, 10, 0x60080000,
};
s32 D_800A6C0C[] = {
    174, 10, 0x60080000,
};
s32 D_800A6C18[] = {
    170, 10, 0x60080000,
};
s32 D_800A6C24[] = {
    170, 10, 0x60080000,
};
s32 D_800A6C30[] = {
    170, 10, 0x60080000,
};
s32 D_800A6C3C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6C48[] = {
    110, 10, 0x60080000,
};
s32 D_800A6C54[] = {
    110, 10, 0x60080000,
};
s32 D_800A6C60[] = {
    2, (s32)D_800A6C00, (s32)D_800A6C0C, (s32)D_800A6C18,
    (s32)D_800A6C24, (s32)D_800A6C30, (s32)D_800A6C3C, (s32)D_800A6C48,
    (s32)D_800A6C54,
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
    0, 0, 0x60040000,
};
s32 D_800A6CB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6CE4[] = {
    0, (s32)D_800A6C84, (s32)D_800A6C90, (s32)D_800A6C9C,
    (s32)D_800A6CA8, (s32)D_800A6CB4, (s32)D_800A6CC0, (s32)D_800A6CCC,
    (s32)D_800A6CD8,
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
    0, 0, 0x60040000,
};
s32 D_800A6D38[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D44[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D68[] = {
    0, (s32)D_800A6D08, (s32)D_800A6D14, (s32)D_800A6D20,
    (s32)D_800A6D2C, (s32)D_800A6D38, (s32)D_800A6D44, (s32)D_800A6D50,
    (s32)D_800A6D5C,
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
    0, 0, 0x60040000,
};
s32 D_800A6DBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DEC[] = {
    0, (s32)D_800A6D8C, (s32)D_800A6D98, (s32)D_800A6DA4,
    (s32)D_800A6DB0, (s32)D_800A6DBC, (s32)D_800A6DC8, (s32)D_800A6DD4,
    (s32)D_800A6DE0,
};
s32 D_800A6E10[] = {
    182, 10, 0x60080000,
};
s32 D_800A6E1C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6E28[] = {
    182, 10, 0x60080000,
};
s32 D_800A6E34[] = {
    182, 10, 0x60080000,
};
s32 D_800A6E40[] = {
    71, 10, 0x60080000,
};
s32 D_800A6E4C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6E58[] = {
    71, 10, 0x60080000,
};
s32 D_800A6E64[] = {
    71, 10, 0x60080000,
};
s32 D_800A6E70[] = {
    2, (s32)D_800A6E10, (s32)D_800A6E1C, (s32)D_800A6E28,
    (s32)D_800A6E34, (s32)D_800A6E40, (s32)D_800A6E4C, (s32)D_800A6E58,
    (s32)D_800A6E64,
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
    0, 0, 0x60040000,
};
s32 D_800A6EC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6ED0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EF4[] = {
    0, (s32)D_800A6E94, (s32)D_800A6EA0, (s32)D_800A6EAC,
    (s32)D_800A6EB8, (s32)D_800A6EC4, (s32)D_800A6ED0, (s32)D_800A6EDC,
    (s32)D_800A6EE8,
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
    0, 0, 0x60040000,
};
s32 D_800A6F48[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F78[] = {
    0, (s32)D_800A6F18, (s32)D_800A6F24, (s32)D_800A6F30,
    (s32)D_800A6F3C, (s32)D_800A6F48, (s32)D_800A6F54, (s32)D_800A6F60,
    (s32)D_800A6F6C,
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
    0, 0, 0x60040000,
};
s32 D_800A6FCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FFC[] = {
    0, (s32)D_800A6F9C, (s32)D_800A6FA8, (s32)D_800A6FB4,
    (s32)D_800A6FC0, (s32)D_800A6FCC, (s32)D_800A6FD8, (s32)D_800A6FE4,
    (s32)D_800A6FF0,
};
s32 D_800A7020[] = {
    110, 10, 0x60080000,
};
s32 D_800A702C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7038[] = {
    110, 10, 0x60080000,
};
s32 D_800A7044[] = {
    110, 10, 0x60080000,
};
s32 D_800A7050[] = {
    110, 10, 0x60080000,
};
s32 D_800A705C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7068[] = {
    110, 10, 0x60080000,
};
s32 D_800A7074[] = {
    110, 10, 0x60080000,
};
s32 D_800A7080[] = {
    1, (s32)D_800A7020, (s32)D_800A702C, (s32)D_800A7038,
    (s32)D_800A7044, (s32)D_800A7050, (s32)D_800A705C, (s32)D_800A7068,
    (s32)D_800A7074,
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
    0, 0, 0x60040000,
};
s32 D_800A70D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A70E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A70EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A70F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7104[] = {
    0, (s32)D_800A70A4, (s32)D_800A70B0, (s32)D_800A70BC,
    (s32)D_800A70C8, (s32)D_800A70D4, (s32)D_800A70E0, (s32)D_800A70EC,
    (s32)D_800A70F8,
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
    0, 0, 0x60040000,
};
s32 D_800A7158[] = {
    0, 0, 0x60040000,
};
s32 D_800A7164[] = {
    0, 0, 0x60040000,
};
s32 D_800A7170[] = {
    0, 0, 0x60040000,
};
s32 D_800A717C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7188[] = {
    0, (s32)D_800A7128, (s32)D_800A7134, (s32)D_800A7140,
    (s32)D_800A714C, (s32)D_800A7158, (s32)D_800A7164, (s32)D_800A7170,
    (s32)D_800A717C,
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
    0, 0, 0x60040000,
};
s32 D_800A71DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A71E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A71F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7200[] = {
    0, 0, 0x60040000,
};
s32 D_800A720C[] = {
    0, (s32)D_800A71AC, (s32)D_800A71B8, (s32)D_800A71C4,
    (s32)D_800A71D0, (s32)D_800A71DC, (s32)D_800A71E8, (s32)D_800A71F4,
    (s32)D_800A7200,
};
s32 D_800A7230[] = {
    182, 10, 0x60080000,
};
s32 D_800A723C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7248[] = {
    182, 10, 0x60080000,
};
s32 D_800A7254[] = {
    182, 10, 0x60080000,
};
s32 D_800A7260[] = {
    71, 10, 0x60080000,
};
s32 D_800A726C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7278[] = {
    71, 10, 0x60080000,
};
s32 D_800A7284[] = {
    71, 10, 0x60080000,
};
s32 D_800A7290[] = {
    1, (s32)D_800A7230, (s32)D_800A723C, (s32)D_800A7248,
    (s32)D_800A7254, (s32)D_800A7260, (s32)D_800A726C, (s32)D_800A7278,
    (s32)D_800A7284,
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
    0, 0, 0x60040000,
};
s32 D_800A72E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A72F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A72FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7308[] = {
    0, 0, 0x60040000,
};
s32 D_800A7314[] = {
    0, (s32)D_800A72B4, (s32)D_800A72C0, (s32)D_800A72CC,
    (s32)D_800A72D8, (s32)D_800A72E4, (s32)D_800A72F0, (s32)D_800A72FC,
    (s32)D_800A7308,
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
    0, 0, 0x60040000,
};
s32 D_800A7368[] = {
    0, 0, 0x60040000,
};
s32 D_800A7374[] = {
    0, 0, 0x60040000,
};
s32 D_800A7380[] = {
    0, 0, 0x60040000,
};
s32 D_800A738C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7398[] = {
    0, (s32)D_800A7338, (s32)D_800A7344, (s32)D_800A7350,
    (s32)D_800A735C, (s32)D_800A7368, (s32)D_800A7374, (s32)D_800A7380,
    (s32)D_800A738C,
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
    0, 0, 0x60040000,
};
s32 D_800A73EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A73F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7404[] = {
    0, 0, 0x60040000,
};
s32 D_800A7410[] = {
    0, 0, 0x60040000,
};
s32 D_800A741C[] = {
    0, (s32)D_800A73BC, (s32)D_800A73C8, (s32)D_800A73D4,
    (s32)D_800A73E0, (s32)D_800A73EC, (s32)D_800A73F8, (s32)D_800A7404,
    (s32)D_800A7410,
};
s32 D_800A7440[] = {
    174, 10, 0x60080000,
};
s32 D_800A744C[] = {
    174, 10, 0x60080000,
};
s32 D_800A7458[] = {
    170, 10, 0x60080000,
};
s32 D_800A7464[] = {
    170, 10, 0x60080000,
};
s32 D_800A7470[] = {
    170, 10, 0x60080000,
};
s32 D_800A747C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7488[] = {
    170, 10, 0x60080000,
};
s32 D_800A7494[] = {
    170, 10, 0x60080000,
};
s32 D_800A74A0[] = {
    4, (s32)D_800A7440, (s32)D_800A744C, (s32)D_800A7458,
    (s32)D_800A7464, (s32)D_800A7470, (s32)D_800A747C, (s32)D_800A7488,
    (s32)D_800A7494,
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
    0, 0, 0x60040000,
};
s32 D_800A74F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7500[] = {
    0, 0, 0x60040000,
};
s32 D_800A750C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7518[] = {
    0, 0, 0x60040000,
};
s32 D_800A7524[] = {
    0, (s32)D_800A74C4, (s32)D_800A74D0, (s32)D_800A74DC,
    (s32)D_800A74E8, (s32)D_800A74F4, (s32)D_800A7500, (s32)D_800A750C,
    (s32)D_800A7518,
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
    0, 0, 0x60040000,
};
s32 D_800A7578[] = {
    0, 0, 0x60040000,
};
s32 D_800A7584[] = {
    0, 0, 0x60040000,
};
s32 D_800A7590[] = {
    0, 0, 0x60040000,
};
s32 D_800A759C[] = {
    0, 0, 0x60040000,
};
s32 D_800A75A8[] = {
    0, (s32)D_800A7548, (s32)D_800A7554, (s32)D_800A7560,
    (s32)D_800A756C, (s32)D_800A7578, (s32)D_800A7584, (s32)D_800A7590,
    (s32)D_800A759C,
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
    0, 0, 0x60040000,
};
s32 D_800A75FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7608[] = {
    0, 0, 0x60040000,
};
s32 D_800A7614[] = {
    0, 0, 0x60040000,
};
s32 D_800A7620[] = {
    0, 0, 0x60040000,
};
s32 D_800A762C[] = {
    0, (s32)D_800A75CC, (s32)D_800A75D8, (s32)D_800A75E4,
    (s32)D_800A75F0, (s32)D_800A75FC, (s32)D_800A7608, (s32)D_800A7614,
    (s32)D_800A7620,
};
s32 D_800A7650[] = {
    110, 10, 0x60080000,
};
s32 D_800A765C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7668[] = {
    110, 10, 0x60080000,
};
s32 D_800A7674[] = {
    110, 10, 0x60080000,
};
s32 D_800A7680[] = {
    110, 10, 0x60080000,
};
s32 D_800A768C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7698[] = {
    110, 10, 0x60080000,
};
s32 D_800A76A4[] = {
    110, 10, 0x60080000,
};
s32 D_800A76B0[] = {
    1, (s32)D_800A7650, (s32)D_800A765C, (s32)D_800A7668,
    (s32)D_800A7674, (s32)D_800A7680, (s32)D_800A768C, (s32)D_800A7698,
    (s32)D_800A76A4,
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
    0, 0, 0x60040000,
};
s32 D_800A7704[] = {
    0, 0, 0x60040000,
};
s32 D_800A7710[] = {
    0, 0, 0x60040000,
};
s32 D_800A771C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7728[] = {
    0, 0, 0x60040000,
};
s32 D_800A7734[] = {
    0, (s32)D_800A76D4, (s32)D_800A76E0, (s32)D_800A76EC,
    (s32)D_800A76F8, (s32)D_800A7704, (s32)D_800A7710, (s32)D_800A771C,
    (s32)D_800A7728,
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
    0, 0, 0x60040000,
};
s32 D_800A7788[] = {
    0, 0, 0x60040000,
};
s32 D_800A7794[] = {
    0, 0, 0x60040000,
};
s32 D_800A77A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A77B8[] = {
    0, (s32)D_800A7758, (s32)D_800A7764, (s32)D_800A7770,
    (s32)D_800A777C, (s32)D_800A7788, (s32)D_800A7794, (s32)D_800A77A0,
    (s32)D_800A77AC,
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
    0, 0, 0x60040000,
};
s32 D_800A780C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7818[] = {
    0, 0, 0x60040000,
};
s32 D_800A7824[] = {
    0, 0, 0x60040000,
};
s32 D_800A7830[] = {
    0, 0, 0x60040000,
};
s32 D_800A783C[] = {
    0, (s32)D_800A77DC, (s32)D_800A77E8, (s32)D_800A77F4,
    (s32)D_800A7800, (s32)D_800A780C, (s32)D_800A7818, (s32)D_800A7824,
    (s32)D_800A7830,
};
s32 D_800A7860[] = {
    182, 10, 0x60080000,
};
s32 D_800A786C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7878[] = {
    182, 10, 0x60080000,
};
s32 D_800A7884[] = {
    182, 10, 0x60080000,
};
s32 D_800A7890[] = {
    71, 10, 0x60080000,
};
s32 D_800A789C[] = {
    71, 10, 0x60080000,
};
s32 D_800A78A8[] = {
    71, 10, 0x60080000,
};
s32 D_800A78B4[] = {
    71, 10, 0x60080000,
};
s32 D_800A78C0[] = {
    1, (s32)D_800A7860, (s32)D_800A786C, (s32)D_800A7878,
    (s32)D_800A7884, (s32)D_800A7890, (s32)D_800A789C, (s32)D_800A78A8,
    (s32)D_800A78B4,
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
    0, 0, 0x60040000,
};
s32 D_800A7914[] = {
    0, 0, 0x60040000,
};
s32 D_800A7920[] = {
    0, 0, 0x60040000,
};
s32 D_800A792C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7938[] = {
    0, 0, 0x60040000,
};
s32 D_800A7944[] = {
    0, (s32)D_800A78E4, (s32)D_800A78F0, (s32)D_800A78FC,
    (s32)D_800A7908, (s32)D_800A7914, (s32)D_800A7920, (s32)D_800A792C,
    (s32)D_800A7938,
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
    0, 0, 0x60040000,
};
s32 D_800A7998[] = {
    0, 0, 0x60040000,
};
s32 D_800A79A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A79B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A79C8[] = {
    0, (s32)D_800A7968, (s32)D_800A7974, (s32)D_800A7980,
    (s32)D_800A798C, (s32)D_800A7998, (s32)D_800A79A4, (s32)D_800A79B0,
    (s32)D_800A79BC,
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
    0, 0, 0x60040000,
};
s32 D_800A7A1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A28[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A34[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A40[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A4C[] = {
    0, (s32)D_800A79EC, (s32)D_800A79F8, (s32)D_800A7A04,
    (s32)D_800A7A10, (s32)D_800A7A1C, (s32)D_800A7A28, (s32)D_800A7A34,
    (s32)D_800A7A40,
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
    110, 10, 0x60080000,
};
s32 D_800A7AA0[] = {
    110, 10, 0x60080000,
};
s32 D_800A7AAC[] = {
    110, 10, 0x60080000,
};
s32 D_800A7AB8[] = {
    110, 10, 0x60080000,
};
s32 D_800A7AC4[] = {
    110, 10, 0x60080000,
};
s32 D_800A7AD0[] = {
    3, (s32)D_800A7A70, (s32)D_800A7A7C, (s32)D_800A7A88,
    (s32)D_800A7A94, (s32)D_800A7AA0, (s32)D_800A7AAC, (s32)D_800A7AB8,
    (s32)D_800A7AC4,
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
    0, 0, 0x60040000,
};
s32 D_800A7B24[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B30[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B48[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B54[] = {
    0, (s32)D_800A7AF4, (s32)D_800A7B00, (s32)D_800A7B0C,
    (s32)D_800A7B18, (s32)D_800A7B24, (s32)D_800A7B30, (s32)D_800A7B3C,
    (s32)D_800A7B48,
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
    0, 0, 0x60040000,
};
s32 D_800A7BA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BD8[] = {
    0, (s32)D_800A7B78, (s32)D_800A7B84, (s32)D_800A7B90,
    (s32)D_800A7B9C, (s32)D_800A7BA8, (s32)D_800A7BB4, (s32)D_800A7BC0,
    (s32)D_800A7BCC,
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
    0, 0, 0x60040000,
};
s32 D_800A7C2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C38[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C44[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C50[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C5C[] = {
    0, (s32)D_800A7BFC, (s32)D_800A7C08, (s32)D_800A7C14,
    (s32)D_800A7C20, (s32)D_800A7C2C, (s32)D_800A7C38, (s32)D_800A7C44,
    (s32)D_800A7C50,
};
s32 D_800A7C80[] = {
    110, 10, 0x60080000,
};
s32 D_800A7C8C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7C98[] = {
    110, 10, 0x60080000,
};
s32 D_800A7CA4[] = {
    110, 10, 0x60080000,
};
s32 D_800A7CB0[] = {
    110, 10, 0x60080000,
};
s32 D_800A7CBC[] = {
    110, 10, 0x60080000,
};
s32 D_800A7CC8[] = {
    110, 10, 0x60080000,
};
s32 D_800A7CD4[] = {
    110, 10, 0x60080000,
};
s32 D_800A7CE0[] = {
    3, (s32)D_800A7C80, (s32)D_800A7C8C, (s32)D_800A7C98,
    (s32)D_800A7CA4, (s32)D_800A7CB0, (s32)D_800A7CBC, (s32)D_800A7CC8,
    (s32)D_800A7CD4,
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
    0, 0, 0x60040000,
};
s32 D_800A7D34[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D40[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D58[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D64[] = {
    0, (s32)D_800A7D04, (s32)D_800A7D10, (s32)D_800A7D1C,
    (s32)D_800A7D28, (s32)D_800A7D34, (s32)D_800A7D40, (s32)D_800A7D4C,
    (s32)D_800A7D58,
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
    0, 0, 0x60040000,
};
s32 D_800A7DB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DE8[] = {
    0, (s32)D_800A7D88, (s32)D_800A7D94, (s32)D_800A7DA0,
    (s32)D_800A7DAC, (s32)D_800A7DB8, (s32)D_800A7DC4, (s32)D_800A7DD0,
    (s32)D_800A7DDC,
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
    0, 0, 0x60040000,
};
s32 D_800A7E3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E48[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E54[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E60[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E6C[] = {
    0, (s32)D_800A7E0C, (s32)D_800A7E18, (s32)D_800A7E24,
    (s32)D_800A7E30, (s32)D_800A7E3C, (s32)D_800A7E48, (s32)D_800A7E54,
    (s32)D_800A7E60,
};
s32 D_800A7E90[] = {
    182, 10, 0x60080000,
};
s32 D_800A7E9C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7EA8[] = {
    182, 10, 0x60080000,
};
s32 D_800A7EB4[] = {
    182, 10, 0x60080000,
};
s32 D_800A7EC0[] = {
    71, 10, 0x60080000,
};
s32 D_800A7ECC[] = {
    71, 10, 0x60080000,
};
s32 D_800A7ED8[] = {
    71, 10, 0x60080000,
};
s32 D_800A7EE4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7EF0[] = {
    2, (s32)D_800A7E90, (s32)D_800A7E9C, (s32)D_800A7EA8,
    (s32)D_800A7EB4, (s32)D_800A7EC0, (s32)D_800A7ECC, (s32)D_800A7ED8,
    (s32)D_800A7EE4,
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
    0, 0, 0x60040000,
};
s32 D_800A7F44[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F50[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F68[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F74[] = {
    0, (s32)D_800A7F14, (s32)D_800A7F20, (s32)D_800A7F2C,
    (s32)D_800A7F38, (s32)D_800A7F44, (s32)D_800A7F50, (s32)D_800A7F5C,
    (s32)D_800A7F68,
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
    0, 0, 0x60040000,
};
s32 D_800A7FC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FF8[] = {
    0, (s32)D_800A7F98, (s32)D_800A7FA4, (s32)D_800A7FB0,
    (s32)D_800A7FBC, (s32)D_800A7FC8, (s32)D_800A7FD4, (s32)D_800A7FE0,
    (s32)D_800A7FEC,
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
    0, 0, 0x60040000,
};
s32 D_800A804C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8058[] = {
    0, 0, 0x60040000,
};
s32 D_800A8064[] = {
    0, 0, 0x60040000,
};
s32 D_800A8070[] = {
    0, 0, 0x60040000,
};
s32 D_800A807C[] = {
    0, (s32)D_800A801C, (s32)D_800A8028, (s32)D_800A8034,
    (s32)D_800A8040, (s32)D_800A804C, (s32)D_800A8058, (s32)D_800A8064,
    (s32)D_800A8070,
};
s32 D_800A80A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A80AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A80B8[] = {
    182, 10, 0x60080000,
};
s32 D_800A80C4[] = {
    182, 10, 0x60080000,
};
s32 D_800A80D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A80DC[] = {
    71, 10, 0x60080000,
};
s32 D_800A80E8[] = {
    71, 10, 0x60080000,
};
s32 D_800A80F4[] = {
    71, 10, 0x60080000,
};
s32 D_800A8100[] = {
    4, (s32)D_800A80A0, (s32)D_800A80AC, (s32)D_800A80B8,
    (s32)D_800A80C4, (s32)D_800A80D0, (s32)D_800A80DC, (s32)D_800A80E8,
    (s32)D_800A80F4,
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
    0, 0, 0x60040000,
};
s32 D_800A8154[] = {
    0, 0, 0x60040000,
};
s32 D_800A8160[] = {
    0, 0, 0x60040000,
};
s32 D_800A816C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8178[] = {
    0, 0, 0x60040000,
};
s32 D_800A8184[] = {
    0, (s32)D_800A8124, (s32)D_800A8130, (s32)D_800A813C,
    (s32)D_800A8148, (s32)D_800A8154, (s32)D_800A8160, (s32)D_800A816C,
    (s32)D_800A8178,
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
    0, 0, 0x60040000,
};
s32 D_800A81D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A81E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A81F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A81FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8208[] = {
    0, (s32)D_800A81A8, (s32)D_800A81B4, (s32)D_800A81C0,
    (s32)D_800A81CC, (s32)D_800A81D8, (s32)D_800A81E4, (s32)D_800A81F0,
    (s32)D_800A81FC,
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
    0, 0, 0x60040000,
};
s32 D_800A825C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8268[] = {
    0, 0, 0x60040000,
};
s32 D_800A8274[] = {
    0, 0, 0x60040000,
};
s32 D_800A8280[] = {
    0, 0, 0x60040000,
};
s32 D_800A828C[] = {
    0, (s32)D_800A822C, (s32)D_800A8238, (s32)D_800A8244,
    (s32)D_800A8250, (s32)D_800A825C, (s32)D_800A8268, (s32)D_800A8274,
    (s32)D_800A8280,
};
s32 D_800A82B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A82BC[] = {
    182, 10, 0x60080000,
};
s32 D_800A82C8[] = {
    182, 10, 0x60080000,
};
s32 D_800A82D4[] = {
    182, 10, 0x60080000,
};
s32 D_800A82E0[] = {
    71, 10, 0x60080000,
};
s32 D_800A82EC[] = {
    71, 10, 0x60080000,
};
s32 D_800A82F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A8304[] = {
    71, 10, 0x60080000,
};
s32 D_800A8310[] = {
    1, (s32)D_800A82B0, (s32)D_800A82BC, (s32)D_800A82C8,
    (s32)D_800A82D4, (s32)D_800A82E0, (s32)D_800A82EC, (s32)D_800A82F8,
    (s32)D_800A8304,
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
    0, 0, 0x60040000,
};
s32 D_800A8364[] = {
    0, 0, 0x60040000,
};
s32 D_800A8370[] = {
    0, 0, 0x60040000,
};
s32 D_800A837C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8388[] = {
    0, 0, 0x60040000,
};
s32 D_800A8394[] = {
    0, (s32)D_800A8334, (s32)D_800A8340, (s32)D_800A834C,
    (s32)D_800A8358, (s32)D_800A8364, (s32)D_800A8370, (s32)D_800A837C,
    (s32)D_800A8388,
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
    0, 0, 0x60040000,
};
s32 D_800A83E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A83F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8400[] = {
    0, 0, 0x60040000,
};
s32 D_800A840C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8418[] = {
    0, (s32)D_800A83B8, (s32)D_800A83C4, (s32)D_800A83D0,
    (s32)D_800A83DC, (s32)D_800A83E8, (s32)D_800A83F4, (s32)D_800A8400,
    (s32)D_800A840C,
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
    0, 0, 0x60040000,
};
s32 D_800A846C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8478[] = {
    0, 0, 0x60040000,
};
s32 D_800A8484[] = {
    0, 0, 0x60040000,
};
s32 D_800A8490[] = {
    0, 0, 0x60040000,
};
s32 D_800A849C[] = {
    0, (s32)D_800A843C, (s32)D_800A8448, (s32)D_800A8454,
    (s32)D_800A8460, (s32)D_800A846C, (s32)D_800A8478, (s32)D_800A8484,
    (s32)D_800A8490,
};
s32 D_800A84C0[] = {
    182, 10, 0x60080000,
};
s32 D_800A84CC[] = {
    182, 10, 0x60080000,
};
s32 D_800A84D8[] = {
    182, 10, 0x60080000,
};
s32 D_800A84E4[] = {
    182, 10, 0x60080000,
};
s32 D_800A84F0[] = {
    71, 10, 0x60080000,
};
s32 D_800A84FC[] = {
    71, 10, 0x60080000,
};
s32 D_800A8508[] = {
    71, 10, 0x60080000,
};
s32 D_800A8514[] = {
    71, 10, 0x60080000,
};
s32 D_800A8520[] = {
    1, (s32)D_800A84C0, (s32)D_800A84CC, (s32)D_800A84D8,
    (s32)D_800A84E4, (s32)D_800A84F0, (s32)D_800A84FC, (s32)D_800A8508,
    (s32)D_800A8514,
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
    0, 0, 0x60040000,
};
s32 D_800A8574[] = {
    0, 0, 0x60040000,
};
s32 D_800A8580[] = {
    0, 0, 0x60040000,
};
s32 D_800A858C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8598[] = {
    0, 0, 0x60040000,
};
s32 D_800A85A4[] = {
    0, (s32)D_800A8544, (s32)D_800A8550, (s32)D_800A855C,
    (s32)D_800A8568, (s32)D_800A8574, (s32)D_800A8580, (s32)D_800A858C,
    (s32)D_800A8598,
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
    0, 0, 0x60040000,
};
s32 D_800A85F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8604[] = {
    0, 0, 0x60040000,
};
s32 D_800A8610[] = {
    0, 0, 0x60040000,
};
s32 D_800A861C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8628[] = {
    0, (s32)D_800A85C8, (s32)D_800A85D4, (s32)D_800A85E0,
    (s32)D_800A85EC, (s32)D_800A85F8, (s32)D_800A8604, (s32)D_800A8610,
    (s32)D_800A861C,
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
    0, 0, 0x60040000,
};
s32 D_800A867C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8688[] = {
    0, 0, 0x60040000,
};
s32 D_800A8694[] = {
    0, 0, 0x60040000,
};
s32 D_800A86A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A86AC[] = {
    0, (s32)D_800A864C, (s32)D_800A8658, (s32)D_800A8664,
    (s32)D_800A8670, (s32)D_800A867C, (s32)D_800A8688, (s32)D_800A8694,
    (s32)D_800A86A0,
};
s32 D_800A86D0[] = {
    174, 10, 0x60080000,
};
s32 D_800A86DC[] = {
    174, 10, 0x60080000,
};
s32 D_800A86E8[] = {
    170, 10, 0x60080000,
};
s32 D_800A86F4[] = {
    170, 10, 0x60080000,
};
s32 D_800A8700[] = {
    182, 10, 0x60080000,
};
s32 D_800A870C[] = {
    182, 10, 0x60080000,
};
s32 D_800A8718[] = {
    71, 10, 0x60080000,
};
s32 D_800A8724[] = {
    71, 10, 0x60080000,
};
s32 D_800A8730[] = {
    1, (s32)D_800A86D0, (s32)D_800A86DC, (s32)D_800A86E8,
    (s32)D_800A86F4, (s32)D_800A8700, (s32)D_800A870C, (s32)D_800A8718,
    (s32)D_800A8724,
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
    0, 0, 0x60040000,
};
s32 D_800A8784[] = {
    0, 0, 0x60040000,
};
s32 D_800A8790[] = {
    0, 0, 0x60040000,
};
s32 D_800A879C[] = {
    0, 0, 0x60040000,
};
s32 D_800A87A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A87B4[] = {
    0, (s32)D_800A8754, (s32)D_800A8760, (s32)D_800A876C,
    (s32)D_800A8778, (s32)D_800A8784, (s32)D_800A8790, (s32)D_800A879C,
    (s32)D_800A87A8,
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
    0, 0, 0x60040000,
};
s32 D_800A8808[] = {
    0, 0, 0x60040000,
};
s32 D_800A8814[] = {
    0, 0, 0x60040000,
};
s32 D_800A8820[] = {
    0, 0, 0x60040000,
};
s32 D_800A882C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8838[] = {
    0, (s32)D_800A87D8, (s32)D_800A87E4, (s32)D_800A87F0,
    (s32)D_800A87FC, (s32)D_800A8808, (s32)D_800A8814, (s32)D_800A8820,
    (s32)D_800A882C,
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
    0, 0, 0x60040000,
};
s32 D_800A888C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8898[] = {
    0, 0, 0x60040000,
};
s32 D_800A88A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A88B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A88BC[] = {
    0, (s32)D_800A885C, (s32)D_800A8868, (s32)D_800A8874,
    (s32)D_800A8880, (s32)D_800A888C, (s32)D_800A8898, (s32)D_800A88A4,
    (s32)D_800A88B0,
};
s32 D_800A88E0[] = {
    233, 1, 0, (s32)D_800A59D0,
    (s32)D_800A5A54, (s32)D_800A5AD8, (s32)D_800A5B5C, 239,
    2, 0, (s32)D_800A5BE0, (s32)D_800A5C64,
    (s32)D_800A5CE8, (s32)D_800A5D6C, 244, 3,
    0, (s32)D_800A5DF0, (s32)D_800A5E74, (s32)D_800A5EF8,
    (s32)D_800A5F7C, 248, 4, 0,
    (s32)D_800A6000, (s32)D_800A6084, (s32)D_800A6108, (s32)D_800A618C,
    255, 5, 0, (s32)D_800A6210,
    (s32)D_800A6294, (s32)D_800A6318, (s32)D_800A639C, 262,
    6, 0, (s32)D_800A6420, (s32)D_800A64A4,
    (s32)D_800A6528, (s32)D_800A65AC, 266, 7,
    0, (s32)D_800A6630, (s32)D_800A66B4, (s32)D_800A6738,
    (s32)D_800A67BC, 272, 8, 0,
    (s32)D_800A6840, (s32)D_800A68C4, (s32)D_800A6948, (s32)D_800A69CC,
    277, 9, 0, (s32)D_800A6A50,
    (s32)D_800A6AD4, (s32)D_800A6B58, (s32)D_800A6BDC, 282,
    10, 0, (s32)D_800A6C60, (s32)D_800A6CE4,
    (s32)D_800A6D68, (s32)D_800A6DEC, 287, 11,
    0, (s32)D_800A6E70, (s32)D_800A6EF4, (s32)D_800A6F78,
    (s32)D_800A6FFC, 292, 12, 0,
    (s32)D_800A7080, (s32)D_800A7104, (s32)D_800A7188, (s32)D_800A720C,
    299, 13, 0, (s32)D_800A7290,
    (s32)D_800A7314, (s32)D_800A7398, (s32)D_800A741C, 309,
    16, 0, (s32)D_800A74A0, (s32)D_800A7524,
    (s32)D_800A75A8, (s32)D_800A762C, 320, 19,
    0, (s32)D_800A76B0, (s32)D_800A7734, (s32)D_800A77B8,
    (s32)D_800A783C, 325, 20, 0,
    (s32)D_800A78C0, (s32)D_800A7944, (s32)D_800A79C8, (s32)D_800A7A4C,
    332, 21, 0, (s32)D_800A7AD0,
    (s32)D_800A7B54, (s32)D_800A7BD8, (s32)D_800A7C5C, 336,
    22, 0, (s32)D_800A7CE0, (s32)D_800A7D64,
    (s32)D_800A7DE8, (s32)D_800A7E6C, 340, 23,
    0, (s32)D_800A7EF0, (s32)D_800A7F74, (s32)D_800A7FF8,
    (s32)D_800A807C, 347, 25, 0,
    (s32)D_800A8100, (s32)D_800A8184, (s32)D_800A8208, (s32)D_800A828C,
    360, 28, 0, (s32)D_800A8310,
    (s32)D_800A8394, (s32)D_800A8418, (s32)D_800A849C, 365,
    29, 0, (s32)D_800A8520, (s32)D_800A85A4,
    (s32)D_800A8628, (s32)D_800A86AC, 372, 30,
    0, (s32)D_800A8730, (s32)D_800A87B4, (s32)D_800A8838,
    (s32)D_800A88BC,
};
s32 D_800A8B64[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140014C, 0x400030, 0x1FF0140,
    0x1000140, 0x1400154, 0x400050, 0x1FF0150,
    0x1000140, 0x140015C, 0x400070, 0x1FF0160,
    0x1000140, 0x1400164, 0x400090, 0x1FF0170,
    0x1000140, 0x140016C, 0x4000B0, 0x1FE0140,
    0x1000140, 0x1400174, 0x4000D0, 0x1FE0150,
    0x1000140, 0x160014C, 0x600030, 0x1FE0160,
    0x1000140, 0x1600154, 0x600050, 0x1FE0170,
    0x1000140, 0x160015C, 0x600070, 0x1FD0140,
    0x1000140, 0x1400140, 0x400000, 0x1FD0150,
    0x1000140, 0x1000168, 160, 0x1FD0160,
    0x1000140, 0x1000140, 0, 0x1FD0170,
    0x1000140, 0x1000154, 80, 0x1FC0140,
};
s32 D_800A8C94[] = {
    0, 0, 862, 0,
    0, 0,
};
s32 D_800A8CAC[] = {
    0, 0, 957, 0,
    0, 0,
};
s32 D_800A8CC4[] = {
    0, 0, 959, 0,
    0, 0,
};
s32 D_800A8CDC[] = {
    0, 0, 960, 0,
    0, 0,
};
s32 D_800A8CF4[] = {
    0, 0, 967, 0,
    0, 0,
};
s32 D_800A8D0C[] = {
    0, 0, 865, 0,
    0, 0,
};
s32 D_800A8D24[] = {
    0, 0, 963, 0,
    0, 0,
};
s32 D_800A8D3C[] = {
    0, 0, 964, 0,
    0, 0,
};
s32 D_800A8D54[] = {
    0, 0, 965, 0,
    0, 0,
};
s32 D_800A8D6C[] = {
    0, 0, 966, 0,
    0, 0,
};
s32 D_800A8D84[] = {
    0, 0, 868, 0,
    0, 0,
};
s32 D_800A8D9C[] = {
    0, 0, 958, 0,
    0, 0,
};
s32 D_800A8DB4[] = {
    0, 0, 961, 0,
    0, 0,
};
s32 D_800A8DCC[] = {
    0, 0, 962, 0,
    0, 0,
};
s32 D_800A8DE4[] = {
    0, 0, 968, 0,
    0, 0,
};
s32 D_800A8DFC[] = {
    0, 0, 863, 0,
    0, 0,
};
s32 D_800A8E14[] = {
    0, 0, 864, 0,
    0, 0,
};
s32 D_800A8E2C[] = {
    0, 0, 866, 0,
    0, 0,
};
s32 D_800A8E44[] = {
    0, 0, 867, 0,
    0, 0,
};
s32 D_800A8E5C[] = {
    0, 0, 869, 0,
    0, 0,
};
s32 D_800A8E74[] = {
    0, 0, 870, 0,
    0, 0,
};
s32 D_800A8E8C[] = {
    0x17E00, 0x17E1E, 65535,
};
s32 D_800A8E98[] = {
    0x17E01, 0x17E1E, 65535,
};
s32 D_800A8EA4[] = {
    0x17E02, 0x17E1F, 65535,
};
s32 D_800A8EB0[] = {
    0x17E03, 0x17E1E, 65535,
};
s32 D_800A8EBC[] = {
    0x17E1B, 0x17E1E, 65535,
};
s32 D_800A8EC8[] = {
    0x17E06, 0x17E1E, 65535,
};
s32 D_800A8ED4[] = {
    0x17E0B, 0x17E1F, 65535,
};
s32 D_800A8EE0[] = {
    0x17E0C, 0x17E1F, 65535,
};
s32 D_800A8EEC[] = {
    0x17E12, 0x17E1F, 65535,
};
s32 D_800A8EF8[] = {
    0x17E13, 0x17E1F, 65535,
};
s32 D_800A8F04[] = {
    0x17E07, 0x17E1E, 65535,
};
s32 D_800A8F10[] = {
    0x17E02, 0x17E1E, 65535,
};
s32 D_800A8F1C[] = {
    0x17E03, 0x17E1F, 65535,
};
s32 D_800A8F28[] = {
    0x17E08, 0x17E1E, 65535,
};
s32 D_800A8F34[] = {
    0x17E1C, 0x17E1E, 65535,
};
s32 D_800A8F40[] = {
    0x17E02, 0x17E20, 65535,
};
s32 D_800A8F4C[] = {
    0x17E16, 0x17E1E, 65535,
};
s32 D_800A8F58[] = {
    0x17E09, 0x17E1E, 65535,
};
s32 D_800A8F64[] = {
    0x17E1D, 0x17E1E, 65535,
};
s32 D_800A8F70[] = {
    0x17E0A, 0x17E1E, 65535,
};
s32 D_800A8F7C[] = {
    0x17E15, 0x17E1E, 65535,
};
s32 D_800A8F88[] = {
    0x17E03, 8, 65535,
};
s32 D_800A8F94[] = {
    0x17E05, 8, 65535,
};
s32 D_800A8FA0[] = {
    0x17E0B, 8, 65535,
};
s32 D_800A8FAC[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A8FB8[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A8FC4[] = {
    0x17E20, 9, 65535,
};
s32 D_800A8FD0[] = {
    0x17E02, 10, 65535,
};
s32 D_800A8FDC[] = {
    0x17E03, 10, 65535,
};
s32 D_800A8FE8[] = {
    0x17E04, 10, 65535,
};
s32 D_800A8FF4[] = {
    0x17E05, 10, 65535,
};
s32 D_800A9000[] = {
    0x17E08, 10, 65535,
};
s32 D_800A900C[] = {
    0x17E0B, 10, 65535,
};
s32 D_800A9018[] = {
    0x17E0C, 10, 65535,
};
s32 D_800A9024[] = {
    0x17E12, 10, 65535,
};
s32 D_800A9030[] = {
    0x17E13, 10, 65535,
};
s32 D_800A903C[] = {
    0x17E1D, 10, 65535,
};
s32 D_800A9048[] = {
    (s32)D_800A8E8C, (s32)D_800A8C94, 0x40022, 0x1A801C8,
    1,
};
s32 D_800A905C[] = {
    (s32)D_800A8E98, (s32)D_800A8CAC, 0x40022, 0x10000A8,
    5,
};
s32 D_800A9070[] = {
    (s32)D_800A8EA4, (s32)D_800A8CC4, 0x40022, 0x2080348,
    1,
};
s32 D_800A9084[] = {
    (s32)D_800A8EB0, (s32)D_800A8CDC, 0x40022, 0x10000A8,
    5,
};
s32 D_800A9098[] = {
    (s32)D_800A8EBC, (s32)D_800A8CF4, 0x40022, 0x1A801C8,
    1,
};
s32 D_800A90AC[] = {
    (s32)D_800A8EC8, (s32)D_800A8D0C, 0x50040, 0x1A801C8,
    1,
};
s32 D_800A90C0[] = {
    (s32)D_800A8ED4, (s32)D_800A8D24, 0x50040, 0x1A801C8,
    1,
};
s32 D_800A90D4[] = {
    (s32)D_800A8EE0, (s32)D_800A8D3C, 0x50040, 0x2080348,
    1,
};
s32 D_800A90E8[] = {
    (s32)D_800A8EEC, (s32)D_800A8D54, 0x50040, 0x10000A8,
    5,
};
s32 D_800A90FC[] = {
    (s32)D_800A8EF8, (s32)D_800A8D6C, 0x50040, 0x2080348,
    1,
};
s32 D_800A9110[] = {
    (s32)D_800A8F04, (s32)D_800A8D84, 0x600B4, 0x1A801C8,
    1,
};
s32 D_800A9124[] = {
    (s32)D_800A8F10, (s32)D_800A8D9C, 0x600B4, 0x2080348,
    1,
};
s32 D_800A9138[] = {
    (s32)D_800A8F1C, (s32)D_800A8DB4, 0x600B4, 0x2080348,
    1,
};
s32 D_800A914C[] = {
    (s32)D_800A8F28, (s32)D_800A8DCC, 0x600B4, 0x10000A8,
    5,
};
s32 D_800A9160[] = {
    (s32)D_800A8F34, (s32)D_800A8DE4, 0x600B4, 0x10000A8,
    5,
};
s32 D_800A9174[] = {
    (s32)D_800A8F40, (s32)D_800A8DFC, 0x700E2, 0x1A801C8,
    1,
};
s32 D_800A9188[] = {
    (s32)D_800A8F4C, (s32)D_800A8E14, 0x800E3, 0x1A801C8,
    1,
};
s32 D_800A919C[] = {
    (s32)D_800A8F58, (s32)D_800A8E2C, 0x900E7, 0x1A801C8,
    1,
};
s32 D_800A91B0[] = {
    (s32)D_800A8F64, (s32)D_800A8E44, 0xA00E8, 0x1A801C8,
    1,
};
s32 D_800A91C4[] = {
    (s32)D_800A8F70, (s32)D_800A8E5C, 0xB00F1, 0x1A801C8,
    1,
};
s32 D_800A91D8[] = {
    (s32)D_800A8F7C, (s32)D_800A8E74, 0xC00F2, 0x1A801C8,
    1,
};
s32 D_800A91EC[] = {
    0, 0, 0xD0146, 0,
    0,
};
s32 D_800A9200[] = {
    (s32)D_800A8F88, 0, 0xE0148, 0xE00100,
    1,
};
s32 D_800A9214[] = {
    (s32)D_800A8F94, 0, 0xE0148, 0x21001C0,
    1,
};
s32 D_800A9228[] = {
    (s32)D_800A8FA0, 0, 0xE0148, 0x1A002C0,
    1,
};
s32 D_800A923C[] = {
    (s32)D_800A8FAC, 0, 0xF015F, 0x1300270,
    1,
};
s32 D_800A9250[] = {
    (s32)D_800A8FB8, 0, 0xF015F, 0x22002D0,
    1,
};
s32 D_800A9264[] = {
    (s32)D_800A8FC4, 0, 0xF015F, 0x1E80310,
    1,
};
s32 D_800A9278[] = {
    (s32)D_800A8FD0, 0, 0x100160, 0x2000260,
    1,
};
s32 D_800A928C[] = {
    (s32)D_800A8FDC, 0, 0x100160, 0x1C00360,
    1,
};
s32 D_800A92A0[] = {
    (s32)D_800A8FE8, 0, 0x100160, 0x2200120,
    1,
};
s32 D_800A92B4[] = {
    (s32)D_800A8FF4, 0, 0x100160, 0x14401B8,
    1,
};
s32 D_800A92C8[] = {
    (s32)D_800A9000, 0, 0x100160, 0x2200120,
    1,
};
s32 D_800A92DC[] = {
    (s32)D_800A900C, 0, 0x100160, 0x12C0118,
    1,
};
s32 D_800A92F0[] = {
    (s32)D_800A9018, 0, 0x100160, 0x1C00360,
    1,
};
s32 D_800A9304[] = {
    (s32)D_800A9024, 0, 0x100160, 0x2000260,
    1,
};
s32 D_800A9318[] = {
    (s32)D_800A9030, 0, 0x100160, 0xE00100,
    1,
};
s32 D_800A932C[] = {
    (s32)D_800A903C, 0, 0x100160, 0x12C0118,
    1,
};
s32 D_800A9340[] = {
    (s32)D_800A9048, (s32)D_800A905C, (s32)D_800A9070, (s32)D_800A9084,
    (s32)D_800A9098, (s32)D_800A90AC, (s32)D_800A90C0, (s32)D_800A90D4,
    (s32)D_800A90E8, (s32)D_800A90FC, (s32)D_800A9110, (s32)D_800A9124,
    (s32)D_800A9138, (s32)D_800A914C, (s32)D_800A9160, (s32)D_800A9174,
    (s32)D_800A9188, (s32)D_800A919C, (s32)D_800A91B0, (s32)D_800A91C4,
    (s32)D_800A91D8, (s32)D_800A91EC, (s32)D_800A9200, (s32)D_800A9214,
    (s32)D_800A9228, (s32)D_800A923C, (s32)D_800A9250, (s32)D_800A9264,
    (s32)D_800A9278, (s32)D_800A928C, (s32)D_800A92A0, (s32)D_800A92B4,
    (s32)D_800A92C8, (s32)D_800A92DC, (s32)D_800A92F0, (s32)D_800A9304,
    (s32)D_800A9318, (s32)D_800A932C, 0,
};
s32 D_800A93DC[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A93F0[] = {
    65535, 65535, 0x2EE0001, 0x1A003A0,
    5, 0, 65535, 65535,
    0x2EE0001, 0xC80130, 5, 0,
    65535, 65535, 0x2EE0001, 0x24000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A9450[])(void) = {
    func_800A4E74,
};
