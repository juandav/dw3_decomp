#include "common.h"
#include "stage.h"
extern void (*D_800A916C[])(void);
void func_800A4DA4();
extern StagePoints *D_800A5944[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A5944, GAME.unk44, GAME.unk46);
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
    D_800A916C[0]();
    return task;
}

extern s32 D_800A9110[];
extern s32 D_800A9124[];
extern s32 D_800A8A08[];
extern s32 D_800A90AC[];
extern s32 D_800A87A0[];
#if VERSION_US
#define STAGE_TEXT 0xE9
#define STAGE_FILE 0x683
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE1)
#define STAGE_FILE 0x693
#endif
void func_800A4E74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A9110;
    D_800990B4.unk14 = D_800A9124;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x37200, 0x1CE00};
    D_800990B4.unk28 = D_800A8A08;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A90AC;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A87A0, GAME.unk44);
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A4E74();
extern StagePoint D_800A4F94;
extern StagePoint D_800A4FA4;
extern StagePoint D_800A4FBC;
extern StagePoint D_800A4FCC;
extern StagePoint D_800A4FE4;
extern StagePoint D_800A4FF4;
extern StagePoint D_800A500C;
extern StagePoint D_800A501C;
extern StagePoint D_800A5034;
extern StagePoint D_800A5044;
extern StagePoint D_800A505C;
extern StagePoint D_800A506C;
extern StagePoint D_800A5084;
extern StagePoint D_800A5094;
extern StagePoint D_800A50AC;
extern StagePoint D_800A50BC;
extern StagePoint D_800A50D4;
extern StagePoint D_800A50E4;
extern StagePoint D_800A50FC;
extern StagePoint D_800A510C;
extern StagePoint D_800A5124;
extern StagePoint D_800A5134;
extern StagePoint D_800A514C;
extern StagePoint D_800A515C;
extern StagePoint D_800A5174;
extern StagePoint D_800A5184;
extern StagePoint D_800A519C;
extern StagePoint D_800A51AC;
extern StagePoint D_800A51C4;
extern StagePoint D_800A51D4;
extern StagePoint D_800A51EC;
extern StagePoint D_800A51FC;
extern StagePoint D_800A5214;
extern StagePoint D_800A5224;
extern StagePoint D_800A523C;
extern StagePoint D_800A524C;
extern StagePoint D_800A5264;
extern StagePoint D_800A5274;
extern StagePoint D_800A528C;
extern StagePoint D_800A529C;
extern StagePoint D_800A52B4;
extern StagePoint D_800A52C4;
extern StagePoint D_800A52DC;
extern StagePoint D_800A52EC;
extern StagePoint D_800A5304;
extern StagePoint D_800A5314;
extern StagePoint D_800A532C;
extern StagePoint D_800A533C;
extern StagePoint D_800A5354;
extern StagePoint D_800A5364;
extern StagePoint D_800A537C;
extern StagePoint D_800A538C;
extern StagePoint D_800A53A4;
extern StagePoint D_800A53B4;
extern StagePoint D_800A53CC;
extern StagePoint D_800A53DC;
extern StagePoint D_800A53F4;
extern StagePoint D_800A5404;
extern StagePoint D_800A541C;
extern StagePoint D_800A542C;
extern StagePoint D_800A5444;
extern StagePoint D_800A5454;
extern StagePoint D_800A546C;
extern StagePoint D_800A547C;
extern StagePoint D_800A5494;
extern StagePoint D_800A54A4;
extern StagePoint D_800A54BC;
extern StagePoint D_800A54CC;
extern StagePoint D_800A54E4;
extern StagePoint D_800A54F4;
extern StagePoint D_800A550C;
extern StagePoint D_800A551C;
extern StagePoint D_800A5534;
extern StagePoint D_800A5544;
extern StagePoint D_800A555C;
extern StagePoint D_800A556C;
extern StagePoint D_800A5584;
extern StagePoint D_800A5594;
extern StagePoint D_800A55AC;
extern StagePoint D_800A55BC;
extern StagePoint D_800A55D4;
extern StagePoint D_800A55E4;
extern StagePoint D_800A55FC;
extern StagePoint D_800A560C;
extern StagePoint D_800A5624;
extern StagePoint D_800A5634;
extern StagePoint D_800A564C;
extern StagePoint D_800A565C;
extern StagePoint D_800A5674;
extern StagePoint D_800A5684;
extern StagePoint D_800A569C;
extern StagePoint D_800A56AC;
extern StagePoint D_800A56C4;
extern StagePoint D_800A56D4;
extern StagePoint D_800A56EC;
extern StagePoint D_800A56FC;
extern StagePoint D_800A5714;
extern StagePoint D_800A5724;
extern StagePoint D_800A573C;
extern StagePoint D_800A574C;
extern StagePoint D_800A5764;
extern StagePoint D_800A5774;
extern StagePoint D_800A578C;
extern StagePoint D_800A579C;
extern StagePoint D_800A57B4;
extern StagePoint D_800A57C4;
extern StagePoint D_800A57DC;
extern StagePoint D_800A57EC;
extern StagePoint D_800A5804;
extern StagePoint D_800A5814;
extern StagePoint D_800A582C;
extern StagePoint D_800A583C;
extern StagePoint D_800A5854;
extern StagePoint D_800A5864;
extern StagePoint D_800A587C;
extern StagePoint D_800A588C;
extern StagePoint D_800A58A4;
extern StagePoint D_800A58B4;
extern StagePoint D_800A58CC;
extern StagePoint D_800A58DC;
extern StagePoint D_800A58F4;
extern StagePoint D_800A5904;
extern StagePoint D_800A591C;
extern StagePoint D_800A592C;
extern StagePoints D_800A4FB4;
extern StagePoints D_800A4FDC;
extern StagePoints D_800A5004;
extern StagePoints D_800A502C;
extern StagePoints D_800A5054;
extern StagePoints D_800A507C;
extern StagePoints D_800A50A4;
extern StagePoints D_800A50CC;
extern StagePoints D_800A50F4;
extern StagePoints D_800A511C;
extern StagePoints D_800A5144;
extern StagePoints D_800A516C;
extern StagePoints D_800A5194;
extern StagePoints D_800A51BC;
extern StagePoints D_800A51E4;
extern StagePoints D_800A520C;
extern StagePoints D_800A5234;
extern StagePoints D_800A525C;
extern StagePoints D_800A5284;
extern StagePoints D_800A52AC;
extern StagePoints D_800A52D4;
extern StagePoints D_800A52FC;
extern StagePoints D_800A5324;
extern StagePoints D_800A534C;
extern StagePoints D_800A5374;
extern StagePoints D_800A539C;
extern StagePoints D_800A53C4;
extern StagePoints D_800A53EC;
extern StagePoints D_800A5414;
extern StagePoints D_800A543C;
extern StagePoints D_800A5464;
extern StagePoints D_800A548C;
extern StagePoints D_800A54B4;
extern StagePoints D_800A54DC;
extern StagePoints D_800A5504;
extern StagePoints D_800A552C;
extern StagePoints D_800A5554;
extern StagePoints D_800A557C;
extern StagePoints D_800A55A4;
extern StagePoints D_800A55CC;
extern StagePoints D_800A55F4;
extern StagePoints D_800A561C;
extern StagePoints D_800A5644;
extern StagePoints D_800A566C;
extern StagePoints D_800A5694;
extern StagePoints D_800A56BC;
extern StagePoints D_800A56E4;
extern StagePoints D_800A570C;
extern StagePoints D_800A5734;
extern StagePoints D_800A575C;
extern StagePoints D_800A5784;
extern StagePoints D_800A57AC;
extern StagePoints D_800A57D4;
extern StagePoints D_800A57FC;
extern StagePoints D_800A5824;
extern StagePoints D_800A584C;
extern StagePoints D_800A5874;
extern StagePoints D_800A589C;
extern StagePoints D_800A58C4;
extern StagePoints D_800A58EC;
extern StagePoints D_800A5914;
extern StagePoints D_800A593C;
extern s32 D_800A5A40[];
extern s32 D_800A5A4C[];
extern s32 D_800A5A58[];
extern s32 D_800A5A64[];
extern s32 D_800A5A70[];
extern s32 D_800A5A7C[];
extern s32 D_800A5A88[];
extern s32 D_800A5A94[];
extern s32 D_800A5AC4[];
extern s32 D_800A5AD0[];
extern s32 D_800A5ADC[];
extern s32 D_800A5AE8[];
extern s32 D_800A5AF4[];
extern s32 D_800A5B00[];
extern s32 D_800A5B0C[];
extern s32 D_800A5B18[];
extern s32 D_800A5B48[];
extern s32 D_800A5B54[];
extern s32 D_800A5B60[];
extern s32 D_800A5B6C[];
extern s32 D_800A5B78[];
extern s32 D_800A5B84[];
extern s32 D_800A5B90[];
extern s32 D_800A5B9C[];
extern s32 D_800A5BCC[];
extern s32 D_800A5BD8[];
extern s32 D_800A5BE4[];
extern s32 D_800A5BF0[];
extern s32 D_800A5BFC[];
extern s32 D_800A5C08[];
extern s32 D_800A5C14[];
extern s32 D_800A5C20[];
extern s32 D_800A5C50[];
extern s32 D_800A5C5C[];
extern s32 D_800A5C68[];
extern s32 D_800A5C74[];
extern s32 D_800A5C80[];
extern s32 D_800A5C8C[];
extern s32 D_800A5C98[];
extern s32 D_800A5CA4[];
extern s32 D_800A5CD4[];
extern s32 D_800A5CE0[];
extern s32 D_800A5CEC[];
extern s32 D_800A5CF8[];
extern s32 D_800A5D04[];
extern s32 D_800A5D10[];
extern s32 D_800A5D1C[];
extern s32 D_800A5D28[];
extern s32 D_800A5D58[];
extern s32 D_800A5D64[];
extern s32 D_800A5D70[];
extern s32 D_800A5D7C[];
extern s32 D_800A5D88[];
extern s32 D_800A5D94[];
extern s32 D_800A5DA0[];
extern s32 D_800A5DAC[];
extern s32 D_800A5DDC[];
extern s32 D_800A5DE8[];
extern s32 D_800A5DF4[];
extern s32 D_800A5E00[];
extern s32 D_800A5E0C[];
extern s32 D_800A5E18[];
extern s32 D_800A5E24[];
extern s32 D_800A5E30[];
extern s32 D_800A5E60[];
extern s32 D_800A5E6C[];
extern s32 D_800A5E78[];
extern s32 D_800A5E84[];
extern s32 D_800A5E90[];
extern s32 D_800A5E9C[];
extern s32 D_800A5EA8[];
extern s32 D_800A5EB4[];
extern s32 D_800A5EE4[];
extern s32 D_800A5EF0[];
extern s32 D_800A5EFC[];
extern s32 D_800A5F08[];
extern s32 D_800A5F14[];
extern s32 D_800A5F20[];
extern s32 D_800A5F2C[];
extern s32 D_800A5F38[];
extern s32 D_800A5F68[];
extern s32 D_800A5F74[];
extern s32 D_800A5F80[];
extern s32 D_800A5F8C[];
extern s32 D_800A5F98[];
extern s32 D_800A5FA4[];
extern s32 D_800A5FB0[];
extern s32 D_800A5FBC[];
extern s32 D_800A5FEC[];
extern s32 D_800A5FF8[];
extern s32 D_800A6004[];
extern s32 D_800A6010[];
extern s32 D_800A601C[];
extern s32 D_800A6028[];
extern s32 D_800A6034[];
extern s32 D_800A6040[];
extern s32 D_800A6070[];
extern s32 D_800A607C[];
extern s32 D_800A6088[];
extern s32 D_800A6094[];
extern s32 D_800A60A0[];
extern s32 D_800A60AC[];
extern s32 D_800A60B8[];
extern s32 D_800A60C4[];
extern s32 D_800A60F4[];
extern s32 D_800A6100[];
extern s32 D_800A610C[];
extern s32 D_800A6118[];
extern s32 D_800A6124[];
extern s32 D_800A6130[];
extern s32 D_800A613C[];
extern s32 D_800A6148[];
extern s32 D_800A6178[];
extern s32 D_800A6184[];
extern s32 D_800A6190[];
extern s32 D_800A619C[];
extern s32 D_800A61A8[];
extern s32 D_800A61B4[];
extern s32 D_800A61C0[];
extern s32 D_800A61CC[];
extern s32 D_800A61FC[];
extern s32 D_800A6208[];
extern s32 D_800A6214[];
extern s32 D_800A6220[];
extern s32 D_800A622C[];
extern s32 D_800A6238[];
extern s32 D_800A6244[];
extern s32 D_800A6250[];
extern s32 D_800A6280[];
extern s32 D_800A628C[];
extern s32 D_800A6298[];
extern s32 D_800A62A4[];
extern s32 D_800A62B0[];
extern s32 D_800A62BC[];
extern s32 D_800A62C8[];
extern s32 D_800A62D4[];
extern s32 D_800A6304[];
extern s32 D_800A6310[];
extern s32 D_800A631C[];
extern s32 D_800A6328[];
extern s32 D_800A6334[];
extern s32 D_800A6340[];
extern s32 D_800A634C[];
extern s32 D_800A6358[];
extern s32 D_800A6388[];
extern s32 D_800A6394[];
extern s32 D_800A63A0[];
extern s32 D_800A63AC[];
extern s32 D_800A63B8[];
extern s32 D_800A63C4[];
extern s32 D_800A63D0[];
extern s32 D_800A63DC[];
extern s32 D_800A640C[];
extern s32 D_800A6418[];
extern s32 D_800A6424[];
extern s32 D_800A6430[];
extern s32 D_800A643C[];
extern s32 D_800A6448[];
extern s32 D_800A6454[];
extern s32 D_800A6460[];
extern s32 D_800A6490[];
extern s32 D_800A649C[];
extern s32 D_800A64A8[];
extern s32 D_800A64B4[];
extern s32 D_800A64C0[];
extern s32 D_800A64CC[];
extern s32 D_800A64D8[];
extern s32 D_800A64E4[];
extern s32 D_800A6514[];
extern s32 D_800A6520[];
extern s32 D_800A652C[];
extern s32 D_800A6538[];
extern s32 D_800A6544[];
extern s32 D_800A6550[];
extern s32 D_800A655C[];
extern s32 D_800A6568[];
extern s32 D_800A6598[];
extern s32 D_800A65A4[];
extern s32 D_800A65B0[];
extern s32 D_800A65BC[];
extern s32 D_800A65C8[];
extern s32 D_800A65D4[];
extern s32 D_800A65E0[];
extern s32 D_800A65EC[];
extern s32 D_800A661C[];
extern s32 D_800A6628[];
extern s32 D_800A6634[];
extern s32 D_800A6640[];
extern s32 D_800A664C[];
extern s32 D_800A6658[];
extern s32 D_800A6664[];
extern s32 D_800A6670[];
extern s32 D_800A66A0[];
extern s32 D_800A66AC[];
extern s32 D_800A66B8[];
extern s32 D_800A66C4[];
extern s32 D_800A66D0[];
extern s32 D_800A66DC[];
extern s32 D_800A66E8[];
extern s32 D_800A66F4[];
extern s32 D_800A6724[];
extern s32 D_800A6730[];
extern s32 D_800A673C[];
extern s32 D_800A6748[];
extern s32 D_800A6754[];
extern s32 D_800A6760[];
extern s32 D_800A676C[];
extern s32 D_800A6778[];
extern s32 D_800A67A8[];
extern s32 D_800A67B4[];
extern s32 D_800A67C0[];
extern s32 D_800A67CC[];
extern s32 D_800A67D8[];
extern s32 D_800A67E4[];
extern s32 D_800A67F0[];
extern s32 D_800A67FC[];
extern s32 D_800A682C[];
extern s32 D_800A6838[];
extern s32 D_800A6844[];
extern s32 D_800A6850[];
extern s32 D_800A685C[];
extern s32 D_800A6868[];
extern s32 D_800A6874[];
extern s32 D_800A6880[];
extern s32 D_800A68B0[];
extern s32 D_800A68BC[];
extern s32 D_800A68C8[];
extern s32 D_800A68D4[];
extern s32 D_800A68E0[];
extern s32 D_800A68EC[];
extern s32 D_800A68F8[];
extern s32 D_800A6904[];
extern s32 D_800A6934[];
extern s32 D_800A6940[];
extern s32 D_800A694C[];
extern s32 D_800A6958[];
extern s32 D_800A6964[];
extern s32 D_800A6970[];
extern s32 D_800A697C[];
extern s32 D_800A6988[];
extern s32 D_800A69B8[];
extern s32 D_800A69C4[];
extern s32 D_800A69D0[];
extern s32 D_800A69DC[];
extern s32 D_800A69E8[];
extern s32 D_800A69F4[];
extern s32 D_800A6A00[];
extern s32 D_800A6A0C[];
extern s32 D_800A6A3C[];
extern s32 D_800A6A48[];
extern s32 D_800A6A54[];
extern s32 D_800A6A60[];
extern s32 D_800A6A6C[];
extern s32 D_800A6A78[];
extern s32 D_800A6A84[];
extern s32 D_800A6A90[];
extern s32 D_800A6AC0[];
extern s32 D_800A6ACC[];
extern s32 D_800A6AD8[];
extern s32 D_800A6AE4[];
extern s32 D_800A6AF0[];
extern s32 D_800A6AFC[];
extern s32 D_800A6B08[];
extern s32 D_800A6B14[];
extern s32 D_800A6B44[];
extern s32 D_800A6B50[];
extern s32 D_800A6B5C[];
extern s32 D_800A6B68[];
extern s32 D_800A6B74[];
extern s32 D_800A6B80[];
extern s32 D_800A6B8C[];
extern s32 D_800A6B98[];
extern s32 D_800A6BC8[];
extern s32 D_800A6BD4[];
extern s32 D_800A6BE0[];
extern s32 D_800A6BEC[];
extern s32 D_800A6BF8[];
extern s32 D_800A6C04[];
extern s32 D_800A6C10[];
extern s32 D_800A6C1C[];
extern s32 D_800A6C4C[];
extern s32 D_800A6C58[];
extern s32 D_800A6C64[];
extern s32 D_800A6C70[];
extern s32 D_800A6C7C[];
extern s32 D_800A6C88[];
extern s32 D_800A6C94[];
extern s32 D_800A6CA0[];
extern s32 D_800A6CD0[];
extern s32 D_800A6CDC[];
extern s32 D_800A6CE8[];
extern s32 D_800A6CF4[];
extern s32 D_800A6D00[];
extern s32 D_800A6D0C[];
extern s32 D_800A6D18[];
extern s32 D_800A6D24[];
extern s32 D_800A6D54[];
extern s32 D_800A6D60[];
extern s32 D_800A6D6C[];
extern s32 D_800A6D78[];
extern s32 D_800A6D84[];
extern s32 D_800A6D90[];
extern s32 D_800A6D9C[];
extern s32 D_800A6DA8[];
extern s32 D_800A6DD8[];
extern s32 D_800A6DE4[];
extern s32 D_800A6DF0[];
extern s32 D_800A6DFC[];
extern s32 D_800A6E08[];
extern s32 D_800A6E14[];
extern s32 D_800A6E20[];
extern s32 D_800A6E2C[];
extern s32 D_800A6E5C[];
extern s32 D_800A6E68[];
extern s32 D_800A6E74[];
extern s32 D_800A6E80[];
extern s32 D_800A6E8C[];
extern s32 D_800A6E98[];
extern s32 D_800A6EA4[];
extern s32 D_800A6EB0[];
extern s32 D_800A6EE0[];
extern s32 D_800A6EEC[];
extern s32 D_800A6EF8[];
extern s32 D_800A6F04[];
extern s32 D_800A6F10[];
extern s32 D_800A6F1C[];
extern s32 D_800A6F28[];
extern s32 D_800A6F34[];
extern s32 D_800A6F64[];
extern s32 D_800A6F70[];
extern s32 D_800A6F7C[];
extern s32 D_800A6F88[];
extern s32 D_800A6F94[];
extern s32 D_800A6FA0[];
extern s32 D_800A6FAC[];
extern s32 D_800A6FB8[];
extern s32 D_800A6FE8[];
extern s32 D_800A6FF4[];
extern s32 D_800A7000[];
extern s32 D_800A700C[];
extern s32 D_800A7018[];
extern s32 D_800A7024[];
extern s32 D_800A7030[];
extern s32 D_800A703C[];
extern s32 D_800A706C[];
extern s32 D_800A7078[];
extern s32 D_800A7084[];
extern s32 D_800A7090[];
extern s32 D_800A709C[];
extern s32 D_800A70A8[];
extern s32 D_800A70B4[];
extern s32 D_800A70C0[];
extern s32 D_800A70F0[];
extern s32 D_800A70FC[];
extern s32 D_800A7108[];
extern s32 D_800A7114[];
extern s32 D_800A7120[];
extern s32 D_800A712C[];
extern s32 D_800A7138[];
extern s32 D_800A7144[];
extern s32 D_800A7174[];
extern s32 D_800A7180[];
extern s32 D_800A718C[];
extern s32 D_800A7198[];
extern s32 D_800A71A4[];
extern s32 D_800A71B0[];
extern s32 D_800A71BC[];
extern s32 D_800A71C8[];
extern s32 D_800A71F8[];
extern s32 D_800A7204[];
extern s32 D_800A7210[];
extern s32 D_800A721C[];
extern s32 D_800A7228[];
extern s32 D_800A7234[];
extern s32 D_800A7240[];
extern s32 D_800A724C[];
extern s32 D_800A727C[];
extern s32 D_800A7288[];
extern s32 D_800A7294[];
extern s32 D_800A72A0[];
extern s32 D_800A72AC[];
extern s32 D_800A72B8[];
extern s32 D_800A72C4[];
extern s32 D_800A72D0[];
extern s32 D_800A7300[];
extern s32 D_800A730C[];
extern s32 D_800A7318[];
extern s32 D_800A7324[];
extern s32 D_800A7330[];
extern s32 D_800A733C[];
extern s32 D_800A7348[];
extern s32 D_800A7354[];
extern s32 D_800A7384[];
extern s32 D_800A7390[];
extern s32 D_800A739C[];
extern s32 D_800A73A8[];
extern s32 D_800A73B4[];
extern s32 D_800A73C0[];
extern s32 D_800A73CC[];
extern s32 D_800A73D8[];
extern s32 D_800A7408[];
extern s32 D_800A7414[];
extern s32 D_800A7420[];
extern s32 D_800A742C[];
extern s32 D_800A7438[];
extern s32 D_800A7444[];
extern s32 D_800A7450[];
extern s32 D_800A745C[];
extern s32 D_800A748C[];
extern s32 D_800A7498[];
extern s32 D_800A74A4[];
extern s32 D_800A74B0[];
extern s32 D_800A74BC[];
extern s32 D_800A74C8[];
extern s32 D_800A74D4[];
extern s32 D_800A74E0[];
extern s32 D_800A7510[];
extern s32 D_800A751C[];
extern s32 D_800A7528[];
extern s32 D_800A7534[];
extern s32 D_800A7540[];
extern s32 D_800A754C[];
extern s32 D_800A7558[];
extern s32 D_800A7564[];
extern s32 D_800A7594[];
extern s32 D_800A75A0[];
extern s32 D_800A75AC[];
extern s32 D_800A75B8[];
extern s32 D_800A75C4[];
extern s32 D_800A75D0[];
extern s32 D_800A75DC[];
extern s32 D_800A75E8[];
extern s32 D_800A7618[];
extern s32 D_800A7624[];
extern s32 D_800A7630[];
extern s32 D_800A763C[];
extern s32 D_800A7648[];
extern s32 D_800A7654[];
extern s32 D_800A7660[];
extern s32 D_800A766C[];
extern s32 D_800A769C[];
extern s32 D_800A76A8[];
extern s32 D_800A76B4[];
extern s32 D_800A76C0[];
extern s32 D_800A76CC[];
extern s32 D_800A76D8[];
extern s32 D_800A76E4[];
extern s32 D_800A76F0[];
extern s32 D_800A7720[];
extern s32 D_800A772C[];
extern s32 D_800A7738[];
extern s32 D_800A7744[];
extern s32 D_800A7750[];
extern s32 D_800A775C[];
extern s32 D_800A7768[];
extern s32 D_800A7774[];
extern s32 D_800A77A4[];
extern s32 D_800A77B0[];
extern s32 D_800A77BC[];
extern s32 D_800A77C8[];
extern s32 D_800A77D4[];
extern s32 D_800A77E0[];
extern s32 D_800A77EC[];
extern s32 D_800A77F8[];
extern s32 D_800A7828[];
extern s32 D_800A7834[];
extern s32 D_800A7840[];
extern s32 D_800A784C[];
extern s32 D_800A7858[];
extern s32 D_800A7864[];
extern s32 D_800A7870[];
extern s32 D_800A787C[];
extern s32 D_800A78AC[];
extern s32 D_800A78B8[];
extern s32 D_800A78C4[];
extern s32 D_800A78D0[];
extern s32 D_800A78DC[];
extern s32 D_800A78E8[];
extern s32 D_800A78F4[];
extern s32 D_800A7900[];
extern s32 D_800A7930[];
extern s32 D_800A793C[];
extern s32 D_800A7948[];
extern s32 D_800A7954[];
extern s32 D_800A7960[];
extern s32 D_800A796C[];
extern s32 D_800A7978[];
extern s32 D_800A7984[];
extern s32 D_800A79B4[];
extern s32 D_800A79C0[];
extern s32 D_800A79CC[];
extern s32 D_800A79D8[];
extern s32 D_800A79E4[];
extern s32 D_800A79F0[];
extern s32 D_800A79FC[];
extern s32 D_800A7A08[];
extern s32 D_800A7A38[];
extern s32 D_800A7A44[];
extern s32 D_800A7A50[];
extern s32 D_800A7A5C[];
extern s32 D_800A7A68[];
extern s32 D_800A7A74[];
extern s32 D_800A7A80[];
extern s32 D_800A7A8C[];
extern s32 D_800A7ABC[];
extern s32 D_800A7AC8[];
extern s32 D_800A7AD4[];
extern s32 D_800A7AE0[];
extern s32 D_800A7AEC[];
extern s32 D_800A7AF8[];
extern s32 D_800A7B04[];
extern s32 D_800A7B10[];
extern s32 D_800A7B40[];
extern s32 D_800A7B4C[];
extern s32 D_800A7B58[];
extern s32 D_800A7B64[];
extern s32 D_800A7B70[];
extern s32 D_800A7B7C[];
extern s32 D_800A7B88[];
extern s32 D_800A7B94[];
extern s32 D_800A7BC4[];
extern s32 D_800A7BD0[];
extern s32 D_800A7BDC[];
extern s32 D_800A7BE8[];
extern s32 D_800A7BF4[];
extern s32 D_800A7C00[];
extern s32 D_800A7C0C[];
extern s32 D_800A7C18[];
extern s32 D_800A7C48[];
extern s32 D_800A7C54[];
extern s32 D_800A7C60[];
extern s32 D_800A7C6C[];
extern s32 D_800A7C78[];
extern s32 D_800A7C84[];
extern s32 D_800A7C90[];
extern s32 D_800A7C9C[];
extern s32 D_800A7CCC[];
extern s32 D_800A7CD8[];
extern s32 D_800A7CE4[];
extern s32 D_800A7CF0[];
extern s32 D_800A7CFC[];
extern s32 D_800A7D08[];
extern s32 D_800A7D14[];
extern s32 D_800A7D20[];
extern s32 D_800A7D50[];
extern s32 D_800A7D5C[];
extern s32 D_800A7D68[];
extern s32 D_800A7D74[];
extern s32 D_800A7D80[];
extern s32 D_800A7D8C[];
extern s32 D_800A7D98[];
extern s32 D_800A7DA4[];
extern s32 D_800A7DD4[];
extern s32 D_800A7DE0[];
extern s32 D_800A7DEC[];
extern s32 D_800A7DF8[];
extern s32 D_800A7E04[];
extern s32 D_800A7E10[];
extern s32 D_800A7E1C[];
extern s32 D_800A7E28[];
extern s32 D_800A7E58[];
extern s32 D_800A7E64[];
extern s32 D_800A7E70[];
extern s32 D_800A7E7C[];
extern s32 D_800A7E88[];
extern s32 D_800A7E94[];
extern s32 D_800A7EA0[];
extern s32 D_800A7EAC[];
extern s32 D_800A7EDC[];
extern s32 D_800A7EE8[];
extern s32 D_800A7EF4[];
extern s32 D_800A7F00[];
extern s32 D_800A7F0C[];
extern s32 D_800A7F18[];
extern s32 D_800A7F24[];
extern s32 D_800A7F30[];
extern s32 D_800A7F60[];
extern s32 D_800A7F6C[];
extern s32 D_800A7F78[];
extern s32 D_800A7F84[];
extern s32 D_800A7F90[];
extern s32 D_800A7F9C[];
extern s32 D_800A7FA8[];
extern s32 D_800A7FB4[];
extern s32 D_800A7FE4[];
extern s32 D_800A7FF0[];
extern s32 D_800A7FFC[];
extern s32 D_800A8008[];
extern s32 D_800A8014[];
extern s32 D_800A8020[];
extern s32 D_800A802C[];
extern s32 D_800A8038[];
extern s32 D_800A8068[];
extern s32 D_800A8074[];
extern s32 D_800A8080[];
extern s32 D_800A808C[];
extern s32 D_800A8098[];
extern s32 D_800A80A4[];
extern s32 D_800A80B0[];
extern s32 D_800A80BC[];
extern s32 D_800A80EC[];
extern s32 D_800A80F8[];
extern s32 D_800A8104[];
extern s32 D_800A8110[];
extern s32 D_800A811C[];
extern s32 D_800A8128[];
extern s32 D_800A8134[];
extern s32 D_800A8140[];
extern s32 D_800A8170[];
extern s32 D_800A817C[];
extern s32 D_800A8188[];
extern s32 D_800A8194[];
extern s32 D_800A81A0[];
extern s32 D_800A81AC[];
extern s32 D_800A81B8[];
extern s32 D_800A81C4[];
extern s32 D_800A81F4[];
extern s32 D_800A8200[];
extern s32 D_800A820C[];
extern s32 D_800A8218[];
extern s32 D_800A8224[];
extern s32 D_800A8230[];
extern s32 D_800A823C[];
extern s32 D_800A8248[];
extern s32 D_800A8278[];
extern s32 D_800A8284[];
extern s32 D_800A8290[];
extern s32 D_800A829C[];
extern s32 D_800A82A8[];
extern s32 D_800A82B4[];
extern s32 D_800A82C0[];
extern s32 D_800A82CC[];
extern s32 D_800A82FC[];
extern s32 D_800A8308[];
extern s32 D_800A8314[];
extern s32 D_800A8320[];
extern s32 D_800A832C[];
extern s32 D_800A8338[];
extern s32 D_800A8344[];
extern s32 D_800A8350[];
extern s32 D_800A8380[];
extern s32 D_800A838C[];
extern s32 D_800A8398[];
extern s32 D_800A83A4[];
extern s32 D_800A83B0[];
extern s32 D_800A83BC[];
extern s32 D_800A83C8[];
extern s32 D_800A83D4[];
extern s32 D_800A8404[];
extern s32 D_800A8410[];
extern s32 D_800A841C[];
extern s32 D_800A8428[];
extern s32 D_800A8434[];
extern s32 D_800A8440[];
extern s32 D_800A844C[];
extern s32 D_800A8458[];
extern s32 D_800A8488[];
extern s32 D_800A8494[];
extern s32 D_800A84A0[];
extern s32 D_800A84AC[];
extern s32 D_800A84B8[];
extern s32 D_800A84C4[];
extern s32 D_800A84D0[];
extern s32 D_800A84DC[];
extern s32 D_800A850C[];
extern s32 D_800A8518[];
extern s32 D_800A8524[];
extern s32 D_800A8530[];
extern s32 D_800A853C[];
extern s32 D_800A8548[];
extern s32 D_800A8554[];
extern s32 D_800A8560[];
extern s32 D_800A8590[];
extern s32 D_800A859C[];
extern s32 D_800A85A8[];
extern s32 D_800A85B4[];
extern s32 D_800A85C0[];
extern s32 D_800A85CC[];
extern s32 D_800A85D8[];
extern s32 D_800A85E4[];
extern s32 D_800A8614[];
extern s32 D_800A8620[];
extern s32 D_800A862C[];
extern s32 D_800A8638[];
extern s32 D_800A8644[];
extern s32 D_800A8650[];
extern s32 D_800A865C[];
extern s32 D_800A8668[];
extern s32 D_800A8698[];
extern s32 D_800A86A4[];
extern s32 D_800A86B0[];
extern s32 D_800A86BC[];
extern s32 D_800A86C8[];
extern s32 D_800A86D4[];
extern s32 D_800A86E0[];
extern s32 D_800A86EC[];
extern s32 D_800A871C[];
extern s32 D_800A8728[];
extern s32 D_800A8734[];
extern s32 D_800A8740[];
extern s32 D_800A874C[];
extern s32 D_800A8758[];
extern s32 D_800A8764[];
extern s32 D_800A8770[];
extern s32 D_800A5AA0[];
extern s32 D_800A5B24[];
extern s32 D_800A5BA8[];
extern s32 D_800A5C2C[];
extern s32 D_800A5CB0[];
extern s32 D_800A5D34[];
extern s32 D_800A5DB8[];
extern s32 D_800A5E3C[];
extern s32 D_800A5EC0[];
extern s32 D_800A5F44[];
extern s32 D_800A5FC8[];
extern s32 D_800A604C[];
extern s32 D_800A60D0[];
extern s32 D_800A6154[];
extern s32 D_800A61D8[];
extern s32 D_800A625C[];
extern s32 D_800A62E0[];
extern s32 D_800A6364[];
extern s32 D_800A63E8[];
extern s32 D_800A646C[];
extern s32 D_800A64F0[];
extern s32 D_800A6574[];
extern s32 D_800A65F8[];
extern s32 D_800A667C[];
extern s32 D_800A6700[];
extern s32 D_800A6784[];
extern s32 D_800A6808[];
extern s32 D_800A688C[];
extern s32 D_800A6910[];
extern s32 D_800A6994[];
extern s32 D_800A6A18[];
extern s32 D_800A6A9C[];
extern s32 D_800A6B20[];
extern s32 D_800A6BA4[];
extern s32 D_800A6C28[];
extern s32 D_800A6CAC[];
extern s32 D_800A6D30[];
extern s32 D_800A6DB4[];
extern s32 D_800A6E38[];
extern s32 D_800A6EBC[];
extern s32 D_800A6F40[];
extern s32 D_800A6FC4[];
extern s32 D_800A7048[];
extern s32 D_800A70CC[];
extern s32 D_800A7150[];
extern s32 D_800A71D4[];
extern s32 D_800A7258[];
extern s32 D_800A72DC[];
extern s32 D_800A7360[];
extern s32 D_800A73E4[];
extern s32 D_800A7468[];
extern s32 D_800A74EC[];
extern s32 D_800A7570[];
extern s32 D_800A75F4[];
extern s32 D_800A7678[];
extern s32 D_800A76FC[];
extern s32 D_800A7780[];
extern s32 D_800A7804[];
extern s32 D_800A7888[];
extern s32 D_800A790C[];
extern s32 D_800A7990[];
extern s32 D_800A7A14[];
extern s32 D_800A7A98[];
extern s32 D_800A7B1C[];
extern s32 D_800A7BA0[];
extern s32 D_800A7C24[];
extern s32 D_800A7CA8[];
extern s32 D_800A7D2C[];
extern s32 D_800A7DB0[];
extern s32 D_800A7E34[];
extern s32 D_800A7EB8[];
extern s32 D_800A7F3C[];
extern s32 D_800A7FC0[];
extern s32 D_800A8044[];
extern s32 D_800A80C8[];
extern s32 D_800A814C[];
extern s32 D_800A81D0[];
extern s32 D_800A8254[];
extern s32 D_800A82D8[];
extern s32 D_800A835C[];
extern s32 D_800A83E0[];
extern s32 D_800A8464[];
extern s32 D_800A84E8[];
extern s32 D_800A856C[];
extern s32 D_800A85F0[];
extern s32 D_800A8674[];
extern s32 D_800A86F8[];
extern s32 D_800A877C[];
extern s32 D_800A8B08[];
extern s32 D_800A8B14[];
extern s32 D_800A8B1C[];
extern s32 D_800A8B28[];
extern s32 D_800A8B34[];
extern s32 D_800A8B3C[];
extern s32 D_800A8B48[];
extern s32 D_800A8B58[];
extern s32 D_800A8B64[];
extern s32 D_800A8B6C[];
extern s32 D_800A8B78[];
extern s32 D_800A8B84[];
extern s32 D_800A8B8C[];
extern s32 D_800A8B98[];
extern s32 D_800A8BA8[];
extern s32 D_800A8BB4[];
extern s32 D_800A8BBC[];
extern s32 D_800A8BC8[];
extern s32 D_800A8BD4[];
extern s32 D_800A8BDC[];
extern s32 D_800A8BE8[];
extern s32 D_800A8BF8[];
extern s32 D_800A8C04[];
extern s32 D_800A8C0C[];
extern s32 D_800A8C18[];
extern s32 D_800A8C24[];
extern s32 D_800A8C2C[];
extern s32 D_800A8C38[];
extern s32 D_800A8D98[];
extern s32 D_800A8C48[];
extern s32 D_800A8DA4[];
extern s32 D_800A8C60[];
extern s32 D_800A8DB0[];
extern s32 D_800A8C78[];
extern s32 D_800A8DBC[];
extern s32 D_800A8C90[];
extern s32 D_800A8DC8[];
extern s32 D_800A8DD4[];
extern s32 D_800A8CA8[];
extern s32 D_800A8DE8[];
extern s32 D_800A8CE4[];
extern s32 D_800A8DFC[];
extern s32 D_800A8D20[];
extern s32 D_800A8E10[];
extern s32 D_800A8D5C[];
extern s32 D_800A8E24[];
extern s32 D_800A8E30[];
extern s32 D_800A8E3C[];
extern s32 D_800A8E48[];
extern s32 D_800A8E54[];
extern s32 D_800A8E60[];
extern s32 D_800A8E6C[];
extern s32 D_800A8E78[];
extern s32 D_800A8E84[];
extern s32 D_800A8E90[];
extern s32 D_800A8E9C[];
extern s32 D_800A8EA8[];
extern s32 D_800A8EB4[];
extern s32 D_800A8EC0[];
extern s32 D_800A8ECC[];
extern s32 D_800A8EE0[];
extern s32 D_800A8EF4[];
extern s32 D_800A8F08[];
extern s32 D_800A8F1C[];
extern s32 D_800A8F30[];
extern s32 D_800A8F44[];
extern s32 D_800A8F58[];
extern s32 D_800A8F6C[];
extern s32 D_800A8F80[];
extern s32 D_800A8F94[];
extern s32 D_800A8FA8[];
extern s32 D_800A8FBC[];
extern s32 D_800A8FD0[];
extern s32 D_800A8FE4[];
extern s32 D_800A8FF8[];
extern s32 D_800A900C[];
extern s32 D_800A9020[];
extern s32 D_800A9034[];
extern s32 D_800A9048[];
extern s32 D_800A905C[];
extern s32 D_800A9070[];
extern s32 D_800A9084[];
extern s32 D_800A9098[];

StagePoint D_800A4F94 = { 0x2ED, 1, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A4FA4 = { 0x2E8, 1, 1, 176, 0x168, 5, &D_800A4F94 };
StagePoints D_800A4FB4 = { 1, 1, &D_800A4FA4 };
StagePoint D_800A4FBC = { 0x2EE, 2, 1, 0x130, 200, 1, NULL };
StagePoint D_800A4FCC = { 0x2E8, 2, 1, 176, 0x168, 5, &D_800A4FBC };
StagePoints D_800A4FDC = { 2, 1, &D_800A4FCC };
StagePoint D_800A4FE4 = { 0x2EE, 3, 1, 0x130, 200, 1, NULL };
StagePoint D_800A4FF4 = { 0x2E8, 3, 1, 176, 0x168, 5, &D_800A4FE4 };
StagePoints D_800A5004 = { 3, 1, &D_800A4FF4 };
StagePoint D_800A500C = { 0x2E9, 3, 1, 0x240, 240, 1, NULL };
StagePoint D_800A501C = { 0x2ED, 3, 2, 224, 192, 5, &D_800A500C };
StagePoints D_800A502C = { 3, 2, &D_800A501C };
StagePoint D_800A5034 = { 0x2E9, 5, 4, 0x240, 240, 1, NULL };
StagePoint D_800A5044 = { 0x2ED, 5, 4, 0x350, 0x1F8, 5, &D_800A5034 };
StagePoints D_800A5054 = { 5, 1, &D_800A5044 };
StagePoint D_800A505C = { 0x2EE, 6, 1, 0x130, 200, 1, NULL };
StagePoint D_800A506C = { 0x2EA, 6, 1, 224, 0x200, 5, &D_800A505C };
StagePoints D_800A507C = { 6, 1, &D_800A506C };
StagePoint D_800A5084 = { 0x2EE, 6, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5094 = { 0x2ED, 6, 2, 0x350, 0x1F8, 5, &D_800A5084 };
StagePoints D_800A50A4 = { 6, 2, &D_800A5094 };
StagePoint D_800A50AC = { 0x2EE, 7, 1, 0x130, 200, 1, NULL };
StagePoint D_800A50BC = { 0x2E8, 7, 1, 176, 0x168, 5, &D_800A50AC };
StagePoints D_800A50CC = { 7, 1, &D_800A50BC };
StagePoint D_800A50D4 = { 0x2EE, 7, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A50E4 = { 0x2E8, 7, 2, 176, 0x168, 5, &D_800A50D4 };
StagePoints D_800A50F4 = { 7, 2, &D_800A50E4 };
StagePoint D_800A50FC = { 0x2EE, 7, 2, 0x130, 200, 1, NULL };
StagePoint D_800A510C = { 0x2EE, 7, 1, 224, 0x240, 5, &D_800A50FC };
StagePoints D_800A511C = { 7, 3, &D_800A510C };
StagePoint D_800A5124 = { 0x2ED, 8, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A5134 = { 0x2E8, 8, 2, 176, 0x168, 5, &D_800A5124 };
StagePoints D_800A5144 = { 8, 1, &D_800A5134 };
StagePoint D_800A514C = { 0x2EE, 9, 1, 0x130, 200, 1, NULL };
StagePoint D_800A515C = { 0x2E8, 9, 1, 176, 0x168, 5, &D_800A514C };
StagePoints D_800A516C = { 9, 1, &D_800A515C };
StagePoint D_800A5174 = { 0x2EE, 10, 1, 0x130, 200, 1, NULL };
StagePoint D_800A5184 = { 0x2E8, 10, 1, 176, 0x168, 5, &D_800A5174 };
StagePoints D_800A5194 = { 10, 1, &D_800A5184 };
StagePoint D_800A519C = { 0x2E9, 10, 2, 0x240, 240, 1, NULL };
StagePoint D_800A51AC = { 0x2ED, 10, 1, 0x350, 0x1F8, 5, &D_800A519C };
StagePoints D_800A51BC = { 10, 2, &D_800A51AC };
StagePoint D_800A51C4 = { 0x2EE, 11, 1, 0x130, 200, 1, NULL };
StagePoint D_800A51D4 = { 0x2E8, 11, 1, 176, 0x168, 5, &D_800A51C4 };
StagePoints D_800A51E4 = { 11, 1, &D_800A51D4 };
StagePoint D_800A51EC = { 0x2E9, 11, 2, 0x240, 240, 1, NULL };
StagePoint D_800A51FC = { 0x2ED, 11, 1, 0x350, 0x1F8, 5, &D_800A51EC };
StagePoints D_800A520C = { 11, 2, &D_800A51FC };
StagePoint D_800A5214 = { 0x2ED, 12, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A5224 = { 0x2EA, 12, 1, 224, 0x200, 5, &D_800A5214 };
StagePoints D_800A5234 = { 12, 1, &D_800A5224 };
StagePoint D_800A523C = { 0x2EE, 12, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A524C = { 0x2EA, 12, 2, 224, 0x200, 5, &D_800A523C };
StagePoints D_800A525C = { 12, 2, &D_800A524C };
StagePoint D_800A5264 = { 0x2EB, 12, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5274 = { 0x2ED, 12, 1, 224, 192, 5, &D_800A5264 };
StagePoints D_800A5284 = { 12, 3, &D_800A5274 };
StagePoint D_800A528C = { 0x2EB, 12, 2, 0x240, 160, 1, NULL };
StagePoint D_800A529C = { 0x2EE, 12, 1, 224, 0x240, 5, &D_800A528C };
StagePoints D_800A52AC = { 12, 4, &D_800A529C };
StagePoint D_800A52B4 = { 0x2E9, 12, 1, 0x240, 240, 1, NULL };
StagePoint D_800A52C4 = { 0x2EE, 12, 2, 224, 0x240, 5, &D_800A52B4 };
StagePoints D_800A52D4 = { 12, 5, &D_800A52C4 };
StagePoint D_800A52DC = { 0x2ED, 13, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A52EC = { 0x2EA, 13, 1, 224, 0x200, 5, &D_800A52DC };
StagePoints D_800A52FC = { 13, 1, &D_800A52EC };
StagePoint D_800A5304 = { 0x2EE, 13, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5314 = { 0x2E8, 13, 1, 176, 0x168, 5, &D_800A5304 };
StagePoints D_800A5324 = { 13, 2, &D_800A5314 };
StagePoint D_800A532C = { 0x2EC, 13, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A533C = { 0x2ED, 13, 1, 224, 192, 5, &D_800A532C };
StagePoints D_800A534C = { 13, 3, &D_800A533C };
StagePoint D_800A5354 = { 0x2E9, 13, 1, 0x240, 240, 1, NULL };
StagePoint D_800A5364 = { 0x2EC, 13, 3, 240, 0x1D8, 5, &D_800A5354 };
StagePoints D_800A5374 = { 13, 4, &D_800A5364 };
StagePoint D_800A537C = { 0x2EB, 13, 1, 0x240, 160, 1, NULL };
StagePoint D_800A538C = { 0x2EE, 13, 1, 224, 0x240, 5, &D_800A537C };
StagePoints D_800A539C = { 13, 5, &D_800A538C };
StagePoint D_800A53A4 = { 0x2EB, 13, 2, 0x240, 160, 1, NULL };
StagePoint D_800A53B4 = { 0x2EE, 13, 2, 224, 0x240, 5, &D_800A53A4 };
StagePoints D_800A53C4 = { 13, 6, &D_800A53B4 };
StagePoint D_800A53CC = { 0x2EB, 18, 1, 0x240, 160, 1, NULL };
StagePoint D_800A53DC = { 0x2E8, 18, 1, 176, 0x168, 5, &D_800A53CC };
StagePoints D_800A53EC = { 18, 1, &D_800A53DC };
StagePoint D_800A53F4 = { 0x2EE, 19, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5404 = { 0x2EA, 19, 1, 224, 0x200, 5, &D_800A53F4 };
StagePoints D_800A5414 = { 19, 1, &D_800A5404 };
StagePoint D_800A541C = { 0x2EE, 19, 2, 0x130, 200, 1, NULL };
StagePoint D_800A542C = { 0x2E8, 19, 1, 176, 0x168, 5, &D_800A541C };
StagePoints D_800A543C = { 19, 2, &D_800A542C };
StagePoint D_800A5444 = { 0x2EE, 19, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5454 = { 0x2EE, 19, 1, 224, 0x240, 5, &D_800A5444 };
StagePoints D_800A5464 = { 19, 3, &D_800A5454 };
StagePoint D_800A546C = { 0x2ED, 19, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A547C = { 0x2ED, 19, 1, 224, 192, 5, &D_800A546C };
StagePoints D_800A548C = { 19, 4, &D_800A547C };
StagePoint D_800A5494 = { 0x2EB, 19, 4, 0x240, 160, 1, NULL };
StagePoint D_800A54A4 = { 0x2ED, 19, 3, 0x350, 0x1F8, 5, &D_800A5494 };
StagePoints D_800A54B4 = { 19, 5, &D_800A54A4 };
StagePoint D_800A54BC = { 0x2EE, 20, 2, 0x130, 200, 1, NULL };
StagePoint D_800A54CC = { 0x2EA, 20, 2, 224, 0x200, 5, &D_800A54BC };
StagePoints D_800A54DC = { 20, 1, &D_800A54CC };
StagePoint D_800A54E4 = { 0x2EE, 20, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A54F4 = { 0x2EE, 20, 1, 224, 0x240, 5, &D_800A54E4 };
StagePoints D_800A5504 = { 20, 2, &D_800A54F4 };
StagePoint D_800A550C = { 0x2ED, 20, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A551C = { 0x2ED, 20, 1, 224, 192, 5, &D_800A550C };
StagePoints D_800A552C = { 20, 3, &D_800A551C };
StagePoint D_800A5534 = { 0x2ED, 20, 4, 0x3A0, 128, 1, NULL };
StagePoint D_800A5544 = { 0x2ED, 20, 2, 0x350, 0x1F8, 5, &D_800A5534 };
StagePoints D_800A5554 = { 20, 4, &D_800A5544 };
StagePoint D_800A555C = { 0x2ED, 20, 5, 0x3A0, 128, 1, NULL };
StagePoint D_800A556C = { 0x2ED, 20, 3, 0x350, 0x1F8, 5, &D_800A555C };
StagePoints D_800A557C = { 20, 5, &D_800A556C };
StagePoint D_800A5584 = { 0x2EB, 20, 4, 0x240, 160, 1, NULL };
StagePoint D_800A5594 = { 0x2ED, 20, 4, 0x350, 0x1F8, 5, &D_800A5584 };
StagePoints D_800A55A4 = { 20, 6, &D_800A5594 };
StagePoint D_800A55AC = { 0x2ED, 20, 6, 0x3A0, 128, 1, NULL };
StagePoint D_800A55BC = { 0x2ED, 20, 5, 224, 192, 5, &D_800A55AC };
StagePoints D_800A55CC = { 20, 7, &D_800A55BC };
StagePoint D_800A55D4 = { 0x2EB, 20, 5, 0x240, 160, 1, NULL };
StagePoint D_800A55E4 = { 0x2ED, 20, 5, 0x350, 0x1F8, 5, &D_800A55D4 };
StagePoints D_800A55F4 = { 20, 8, &D_800A55E4 };
StagePoint D_800A55FC = { 0x2EB, 20, 6, 0x240, 160, 1, NULL };
StagePoint D_800A560C = { 0x2ED, 20, 6, 224, 192, 5, &D_800A55FC };
StagePoints D_800A561C = { 20, 9, &D_800A560C };
StagePoint D_800A5624 = { 0x2EC, 21, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A5634 = { 0x2EA, 21, 1, 224, 0x200, 5, &D_800A5624 };
StagePoints D_800A5644 = { 21, 1, &D_800A5634 };
StagePoint D_800A564C = { 0x2EE, 21, 1, 0x130, 200, 1, NULL };
StagePoint D_800A565C = { 0x2EC, 21, 1, 240, 0x1D8, 5, &D_800A564C };
StagePoints D_800A566C = { 21, 2, &D_800A565C };
StagePoint D_800A5674 = { 0x2EE, 22, 1, 0x130, 200, 1, NULL };
StagePoint D_800A5684 = { 0x2E8, 22, 1, 176, 0x168, 5, &D_800A5674 };
StagePoints D_800A5694 = { 22, 1, &D_800A5684 };
StagePoint D_800A569C = { 0x2EE, 22, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A56AC = { 0x2E8, 22, 2, 176, 0x168, 5, &D_800A569C };
StagePoints D_800A56BC = { 22, 2, &D_800A56AC };
StagePoint D_800A56C4 = { 0x2EB, 22, 1, 0x240, 160, 1, NULL };
StagePoint D_800A56D4 = { 0x2EE, 22, 1, 224, 0x240, 5, &D_800A56C4 };
StagePoints D_800A56E4 = { 22, 3, &D_800A56D4 };
StagePoint D_800A56EC = { 0x2EC, 23, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A56FC = { 0x2E8, 23, 1, 176, 0x168, 5, &D_800A56EC };
StagePoints D_800A570C = { 23, 1, &D_800A56FC };
StagePoint D_800A5714 = { 0x2EC, 23, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A5724 = { 0x2EC, 23, 1, 240, 0x1D8, 5, &D_800A5714 };
StagePoints D_800A5734 = { 23, 2, &D_800A5724 };
StagePoint D_800A573C = { 0x2EE, 23, 1, 0x130, 200, 1, NULL };
StagePoint D_800A574C = { 0x2EC, 23, 2, 240, 0x1D8, 5, &D_800A573C };
StagePoints D_800A575C = { 23, 3, &D_800A574C };
StagePoint D_800A5764 = { 0x2EC, 24, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A5774 = { 0x2E8, 24, 1, 176, 0x168, 5, &D_800A5764 };
StagePoints D_800A5784 = { 24, 1, &D_800A5774 };
StagePoint D_800A578C = { 0x2EC, 24, 3, 0x3B0, 120, 1, NULL };
StagePoint D_800A579C = { 0x2EC, 24, 1, 240, 0x1D8, 5, &D_800A578C };
StagePoints D_800A57AC = { 24, 2, &D_800A579C };
StagePoint D_800A57B4 = { 0x2EC, 24, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A57C4 = { 0x2EC, 24, 2, 240, 0x1D8, 5, &D_800A57B4 };
StagePoints D_800A57D4 = { 24, 3, &D_800A57C4 };
StagePoint D_800A57DC = { 0x2EC, 24, 5, 0x3B0, 120, 1, NULL };
StagePoint D_800A57EC = { 0x2EC, 24, 3, 240, 0x1D8, 5, &D_800A57DC };
StagePoints D_800A57FC = { 24, 4, &D_800A57EC };
StagePoint D_800A5804 = { 0x2EB, 24, 1, 0x240, 160, 1, NULL };
StagePoint D_800A5814 = { 0x2EC, 24, 4, 240, 0x1D8, 5, &D_800A5804 };
StagePoints D_800A5824 = { 24, 5, &D_800A5814 };
StagePoint D_800A582C = { 0x2ED, 28, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A583C = { 0x2EA, 28, 1, 224, 0x200, 5, &D_800A582C };
StagePoints D_800A584C = { 28, 1, &D_800A583C };
StagePoint D_800A5854 = { 0x2EE, 28, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5864 = { 0x2EA, 28, 2, 224, 0x200, 5, &D_800A5854 };
StagePoints D_800A5874 = { 28, 2, &D_800A5864 };
StagePoint D_800A587C = { 0x2EB, 28, 1, 0x240, 160, 1, NULL };
StagePoint D_800A588C = { 0x2ED, 28, 1, 224, 192, 5, &D_800A587C };
StagePoints D_800A589C = { 28, 3, &D_800A588C };
StagePoint D_800A58A4 = { 0x2EB, 28, 2, 0x240, 160, 1, NULL };
StagePoint D_800A58B4 = { 0x2EE, 28, 1, 224, 0x240, 5, &D_800A58A4 };
StagePoints D_800A58C4 = { 28, 4, &D_800A58B4 };
StagePoint D_800A58CC = { 0x2EE, 29, 1, 0x130, 200, 1, NULL };
StagePoint D_800A58DC = { 0x2E8, 29, 1, 176, 0x168, 5, &D_800A58CC };
StagePoints D_800A58EC = { 29, 1, &D_800A58DC };
StagePoint D_800A58F4 = { 0x2EE, 29, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A5904 = { 0x2EA, 29, 1, 224, 0x200, 5, &D_800A58F4 };
StagePoints D_800A5914 = { 29, 2, &D_800A5904 };
StagePoint D_800A591C = { 0x2EB, 30, 1, 0x240, 160, 1, NULL };
StagePoint D_800A592C = { 0x2ED, 30, 1, 224, 192, 5, &D_800A591C };
StagePoints D_800A593C = { 30, 1, &D_800A592C };
StagePoints *D_800A5944[] = {
    &D_800A4FB4, &D_800A4FDC, &D_800A5004, &D_800A502C,
    &D_800A5054, &D_800A507C, &D_800A50A4, &D_800A50CC,
    &D_800A50F4, &D_800A511C, &D_800A5144, &D_800A516C,
    &D_800A5194, &D_800A51BC, &D_800A51E4, &D_800A520C,
    &D_800A5234, &D_800A525C, &D_800A5284, &D_800A52AC,
    &D_800A52D4, &D_800A52FC, &D_800A5324, &D_800A534C,
    &D_800A5374, &D_800A539C, &D_800A53C4, &D_800A53EC,
    &D_800A5414, &D_800A543C, &D_800A5464, &D_800A548C,
    &D_800A54B4, &D_800A54DC, &D_800A5504, &D_800A552C,
    &D_800A5554, &D_800A557C, &D_800A55A4, &D_800A55CC,
    &D_800A55F4, &D_800A561C, &D_800A5644, &D_800A566C,
    &D_800A5694, &D_800A56BC, &D_800A56E4, &D_800A570C,
    &D_800A5734, &D_800A575C, &D_800A5784, &D_800A57AC,
    &D_800A57D4, &D_800A57FC, &D_800A5824, &D_800A584C,
    &D_800A5874, &D_800A589C, &D_800A58C4, &D_800A58EC,
    &D_800A5914, &D_800A593C, NULL,
};
s32 D_800A5A40[] = {
    174, 10, 0x60080000,
};
s32 D_800A5A4C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5A58[] = {
    170, 10, 0x60080000,
};
s32 D_800A5A64[] = {
    170, 10, 0x60080000,
};
s32 D_800A5A70[] = {
    170, 10, 0x60080000,
};
s32 D_800A5A7C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5A88[] = {
    170, 10, 0x60080000,
};
s32 D_800A5A94[] = {
    170, 10, 0x60080000,
};
s32 D_800A5AA0[] = {
    1, (s32)D_800A5A40, (s32)D_800A5A4C, (s32)D_800A5A58,
    (s32)D_800A5A64, (s32)D_800A5A70, (s32)D_800A5A7C, (s32)D_800A5A88,
    (s32)D_800A5A94,
};
s32 D_800A5AC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5ADC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B24[] = {
    0, (s32)D_800A5AC4, (s32)D_800A5AD0, (s32)D_800A5ADC,
    (s32)D_800A5AE8, (s32)D_800A5AF4, (s32)D_800A5B00, (s32)D_800A5B0C,
    (s32)D_800A5B18,
};
s32 D_800A5B48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B60[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5B9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BA8[] = {
    0, (s32)D_800A5B48, (s32)D_800A5B54, (s32)D_800A5B60,
    (s32)D_800A5B6C, (s32)D_800A5B78, (s32)D_800A5B84, (s32)D_800A5B90,
    (s32)D_800A5B9C,
};
s32 D_800A5BCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5BFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C2C[] = {
    0, (s32)D_800A5BCC, (s32)D_800A5BD8, (s32)D_800A5BE4,
    (s32)D_800A5BF0, (s32)D_800A5BFC, (s32)D_800A5C08, (s32)D_800A5C14,
    (s32)D_800A5C20,
};
s32 D_800A5C50[] = {
    174, 10, 0x60080000,
};
s32 D_800A5C5C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5C68[] = {
    170, 10, 0x60080000,
};
s32 D_800A5C74[] = {
    170, 10, 0x60080000,
};
s32 D_800A5C80[] = {
    170, 10, 0x60080000,
};
s32 D_800A5C8C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5C98[] = {
    110, 10, 0x60080000,
};
s32 D_800A5CA4[] = {
    110, 10, 0x60080000,
};
s32 D_800A5CB0[] = {
    1, (s32)D_800A5C50, (s32)D_800A5C5C, (s32)D_800A5C68,
    (s32)D_800A5C74, (s32)D_800A5C80, (s32)D_800A5C8C, (s32)D_800A5C98,
    (s32)D_800A5CA4,
};
s32 D_800A5CD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D28[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D34[] = {
    0, (s32)D_800A5CD4, (s32)D_800A5CE0, (s32)D_800A5CEC,
    (s32)D_800A5CF8, (s32)D_800A5D04, (s32)D_800A5D10, (s32)D_800A5D1C,
    (s32)D_800A5D28,
};
s32 D_800A5D58[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DB8[] = {
    0, (s32)D_800A5D58, (s32)D_800A5D64, (s32)D_800A5D70,
    (s32)D_800A5D7C, (s32)D_800A5D88, (s32)D_800A5D94, (s32)D_800A5DA0,
    (s32)D_800A5DAC,
};
s32 D_800A5DDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E3C[] = {
    0, (s32)D_800A5DDC, (s32)D_800A5DE8, (s32)D_800A5DF4,
    (s32)D_800A5E00, (s32)D_800A5E0C, (s32)D_800A5E18, (s32)D_800A5E24,
    (s32)D_800A5E30,
};
s32 D_800A5E60[] = {
    174, 10, 0x60080000,
};
s32 D_800A5E6C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5E78[] = {
    170, 10, 0x60080000,
};
s32 D_800A5E84[] = {
    170, 10, 0x60080000,
};
s32 D_800A5E90[] = {
    182, 10, 0x60080000,
};
s32 D_800A5E9C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5EA8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5EB4[] = {
    71, 10, 0x60080000,
};
s32 D_800A5EC0[] = {
    1, (s32)D_800A5E60, (s32)D_800A5E6C, (s32)D_800A5E78,
    (s32)D_800A5E84, (s32)D_800A5E90, (s32)D_800A5E9C, (s32)D_800A5EA8,
    (s32)D_800A5EB4,
};
s32 D_800A5EE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F08[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F14[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F38[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F44[] = {
    0, (s32)D_800A5EE4, (s32)D_800A5EF0, (s32)D_800A5EFC,
    (s32)D_800A5F08, (s32)D_800A5F14, (s32)D_800A5F20, (s32)D_800A5F2C,
    (s32)D_800A5F38,
};
s32 D_800A5F68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F74[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F80[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5F98[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FC8[] = {
    0, (s32)D_800A5F68, (s32)D_800A5F74, (s32)D_800A5F80,
    (s32)D_800A5F8C, (s32)D_800A5F98, (s32)D_800A5FA4, (s32)D_800A5FB0,
    (s32)D_800A5FBC,
};
s32 D_800A5FEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5FF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6004[] = {
    0, 0, 0x60040000,
};
s32 D_800A6010[] = {
    0, 0, 0x60040000,
};
s32 D_800A601C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6028[] = {
    0, 0, 0x60040000,
};
s32 D_800A6034[] = {
    0, 0, 0x60040000,
};
s32 D_800A6040[] = {
    0, 0, 0x60040000,
};
s32 D_800A604C[] = {
    0, (s32)D_800A5FEC, (s32)D_800A5FF8, (s32)D_800A6004,
    (s32)D_800A6010, (s32)D_800A601C, (s32)D_800A6028, (s32)D_800A6034,
    (s32)D_800A6040,
};
s32 D_800A6070[] = {
    174, 10, 0x60080000,
};
s32 D_800A607C[] = {
    170, 10, 0x60080000,
};
s32 D_800A6088[] = {
    110, 10, 0x60080000,
};
s32 D_800A6094[] = {
    110, 10, 0x60080000,
};
s32 D_800A60A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A60AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A60B8[] = {
    71, 10, 0x60080000,
};
s32 D_800A60C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A60D0[] = {
    1, (s32)D_800A6070, (s32)D_800A607C, (s32)D_800A6088,
    (s32)D_800A6094, (s32)D_800A60A0, (s32)D_800A60AC, (s32)D_800A60B8,
    (s32)D_800A60C4,
};
s32 D_800A60F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6100[] = {
    0, 0, 0x60040000,
};
s32 D_800A610C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6118[] = {
    0, 0, 0x60040000,
};
s32 D_800A6124[] = {
    0, 0, 0x60040000,
};
s32 D_800A6130[] = {
    0, 0, 0x60040000,
};
s32 D_800A613C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6148[] = {
    0, 0, 0x60040000,
};
s32 D_800A6154[] = {
    0, (s32)D_800A60F4, (s32)D_800A6100, (s32)D_800A610C,
    (s32)D_800A6118, (s32)D_800A6124, (s32)D_800A6130, (s32)D_800A613C,
    (s32)D_800A6148,
};
s32 D_800A6178[] = {
    0, 0, 0x60040000,
};
s32 D_800A6184[] = {
    0, 0, 0x60040000,
};
s32 D_800A6190[] = {
    0, 0, 0x60040000,
};
s32 D_800A619C[] = {
    0, 0, 0x60040000,
};
s32 D_800A61A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A61B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A61C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A61D8[] = {
    0, (s32)D_800A6178, (s32)D_800A6184, (s32)D_800A6190,
    (s32)D_800A619C, (s32)D_800A61A8, (s32)D_800A61B4, (s32)D_800A61C0,
    (s32)D_800A61CC,
};
s32 D_800A61FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6208[] = {
    0, 0, 0x60040000,
};
s32 D_800A6214[] = {
    0, 0, 0x60040000,
};
s32 D_800A6220[] = {
    0, 0, 0x60040000,
};
s32 D_800A622C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6238[] = {
    0, 0, 0x60040000,
};
s32 D_800A6244[] = {
    0, 0, 0x60040000,
};
s32 D_800A6250[] = {
    0, 0, 0x60040000,
};
s32 D_800A625C[] = {
    0, (s32)D_800A61FC, (s32)D_800A6208, (s32)D_800A6214,
    (s32)D_800A6220, (s32)D_800A622C, (s32)D_800A6238, (s32)D_800A6244,
    (s32)D_800A6250,
};
s32 D_800A6280[] = {
    174, 10, 0x60080000,
};
s32 D_800A628C[] = {
    170, 10, 0x60080000,
};
s32 D_800A6298[] = {
    110, 10, 0x60080000,
};
s32 D_800A62A4[] = {
    110, 10, 0x60080000,
};
s32 D_800A62B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A62BC[] = {
    182, 10, 0x60080000,
};
s32 D_800A62C8[] = {
    71, 10, 0x60080000,
};
s32 D_800A62D4[] = {
    71, 10, 0x60080000,
};
s32 D_800A62E0[] = {
    1, (s32)D_800A6280, (s32)D_800A628C, (s32)D_800A6298,
    (s32)D_800A62A4, (s32)D_800A62B0, (s32)D_800A62BC, (s32)D_800A62C8,
    (s32)D_800A62D4,
};
s32 D_800A6304[] = {
    0, 0, 0x60040000,
};
s32 D_800A6310[] = {
    0, 0, 0x60040000,
};
s32 D_800A631C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6328[] = {
    0, 0, 0x60040000,
};
s32 D_800A6334[] = {
    0, 0, 0x60040000,
};
s32 D_800A6340[] = {
    0, 0, 0x60040000,
};
s32 D_800A634C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6358[] = {
    0, 0, 0x60040000,
};
s32 D_800A6364[] = {
    0, (s32)D_800A6304, (s32)D_800A6310, (s32)D_800A631C,
    (s32)D_800A6328, (s32)D_800A6334, (s32)D_800A6340, (s32)D_800A634C,
    (s32)D_800A6358,
};
s32 D_800A6388[] = {
    0, 0, 0x60040000,
};
s32 D_800A6394[] = {
    0, 0, 0x60040000,
};
s32 D_800A63A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63E8[] = {
    0, (s32)D_800A6388, (s32)D_800A6394, (s32)D_800A63A0,
    (s32)D_800A63AC, (s32)D_800A63B8, (s32)D_800A63C4, (s32)D_800A63D0,
    (s32)D_800A63DC,
};
s32 D_800A640C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6418[] = {
    0, 0, 0x60040000,
};
s32 D_800A6424[] = {
    0, 0, 0x60040000,
};
s32 D_800A6430[] = {
    0, 0, 0x60040000,
};
s32 D_800A643C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6448[] = {
    0, 0, 0x60040000,
};
s32 D_800A6454[] = {
    0, 0, 0x60040000,
};
s32 D_800A6460[] = {
    0, 0, 0x60040000,
};
s32 D_800A646C[] = {
    0, (s32)D_800A640C, (s32)D_800A6418, (s32)D_800A6424,
    (s32)D_800A6430, (s32)D_800A643C, (s32)D_800A6448, (s32)D_800A6454,
    (s32)D_800A6460,
};
s32 D_800A6490[] = {
    110, 10, 0x60080000,
};
s32 D_800A649C[] = {
    110, 10, 0x60080000,
};
s32 D_800A64A8[] = {
    110, 10, 0x60080000,
};
s32 D_800A64B4[] = {
    110, 10, 0x60080000,
};
s32 D_800A64C0[] = {
    182, 10, 0x60080000,
};
s32 D_800A64CC[] = {
    182, 10, 0x60080000,
};
s32 D_800A64D8[] = {
    182, 10, 0x60080000,
};
s32 D_800A64E4[] = {
    182, 10, 0x60080000,
};
s32 D_800A64F0[] = {
    1, (s32)D_800A6490, (s32)D_800A649C, (s32)D_800A64A8,
    (s32)D_800A64B4, (s32)D_800A64C0, (s32)D_800A64CC, (s32)D_800A64D8,
    (s32)D_800A64E4,
};
s32 D_800A6514[] = {
    0, 0, 0x60040000,
};
s32 D_800A6520[] = {
    0, 0, 0x60040000,
};
s32 D_800A652C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6538[] = {
    0, 0, 0x60040000,
};
s32 D_800A6544[] = {
    0, 0, 0x60040000,
};
s32 D_800A6550[] = {
    0, 0, 0x60040000,
};
s32 D_800A655C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6568[] = {
    0, 0, 0x60040000,
};
s32 D_800A6574[] = {
    0, (s32)D_800A6514, (s32)D_800A6520, (s32)D_800A652C,
    (s32)D_800A6538, (s32)D_800A6544, (s32)D_800A6550, (s32)D_800A655C,
    (s32)D_800A6568,
};
s32 D_800A6598[] = {
    0, 0, 0x60040000,
};
s32 D_800A65A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65F8[] = {
    0, (s32)D_800A6598, (s32)D_800A65A4, (s32)D_800A65B0,
    (s32)D_800A65BC, (s32)D_800A65C8, (s32)D_800A65D4, (s32)D_800A65E0,
    (s32)D_800A65EC,
};
s32 D_800A661C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6628[] = {
    0, 0, 0x60040000,
};
s32 D_800A6634[] = {
    0, 0, 0x60040000,
};
s32 D_800A6640[] = {
    0, 0, 0x60040000,
};
s32 D_800A664C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6658[] = {
    0, 0, 0x60040000,
};
s32 D_800A6664[] = {
    0, 0, 0x60040000,
};
s32 D_800A6670[] = {
    0, 0, 0x60040000,
};
s32 D_800A667C[] = {
    0, (s32)D_800A661C, (s32)D_800A6628, (s32)D_800A6634,
    (s32)D_800A6640, (s32)D_800A664C, (s32)D_800A6658, (s32)D_800A6664,
    (s32)D_800A6670,
};
s32 D_800A66A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A66AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A66B8[] = {
    182, 10, 0x60080000,
};
s32 D_800A66C4[] = {
    182, 10, 0x60080000,
};
s32 D_800A66D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A66DC[] = {
    71, 10, 0x60080000,
};
s32 D_800A66E8[] = {
    71, 10, 0x60080000,
};
s32 D_800A66F4[] = {
    71, 10, 0x60080000,
};
s32 D_800A6700[] = {
    1, (s32)D_800A66A0, (s32)D_800A66AC, (s32)D_800A66B8,
    (s32)D_800A66C4, (s32)D_800A66D0, (s32)D_800A66DC, (s32)D_800A66E8,
    (s32)D_800A66F4,
};
s32 D_800A6724[] = {
    0, 0, 0x60040000,
};
s32 D_800A6730[] = {
    0, 0, 0x60040000,
};
s32 D_800A673C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6748[] = {
    0, 0, 0x60040000,
};
s32 D_800A6754[] = {
    0, 0, 0x60040000,
};
s32 D_800A6760[] = {
    0, 0, 0x60040000,
};
s32 D_800A676C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6778[] = {
    0, 0, 0x60040000,
};
s32 D_800A6784[] = {
    0, (s32)D_800A6724, (s32)D_800A6730, (s32)D_800A673C,
    (s32)D_800A6748, (s32)D_800A6754, (s32)D_800A6760, (s32)D_800A676C,
    (s32)D_800A6778,
};
s32 D_800A67A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6808[] = {
    0, (s32)D_800A67A8, (s32)D_800A67B4, (s32)D_800A67C0,
    (s32)D_800A67CC, (s32)D_800A67D8, (s32)D_800A67E4, (s32)D_800A67F0,
    (s32)D_800A67FC,
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
    0, 0, 0x60040000,
};
s32 D_800A688C[] = {
    0, (s32)D_800A682C, (s32)D_800A6838, (s32)D_800A6844,
    (s32)D_800A6850, (s32)D_800A685C, (s32)D_800A6868, (s32)D_800A6874,
    (s32)D_800A6880,
};
s32 D_800A68B0[] = {
    182, 10, 0x60080000,
};
s32 D_800A68BC[] = {
    182, 10, 0x60080000,
};
s32 D_800A68C8[] = {
    182, 10, 0x60080000,
};
s32 D_800A68D4[] = {
    182, 10, 0x60080000,
};
s32 D_800A68E0[] = {
    71, 10, 0x60080000,
};
s32 D_800A68EC[] = {
    71, 10, 0x60080000,
};
s32 D_800A68F8[] = {
    71, 10, 0x60080000,
};
s32 D_800A6904[] = {
    71, 10, 0x60080000,
};
s32 D_800A6910[] = {
    1, (s32)D_800A68B0, (s32)D_800A68BC, (s32)D_800A68C8,
    (s32)D_800A68D4, (s32)D_800A68E0, (s32)D_800A68EC, (s32)D_800A68F8,
    (s32)D_800A6904,
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
    0, 0, 0x60040000,
};
s32 D_800A6994[] = {
    0, (s32)D_800A6934, (s32)D_800A6940, (s32)D_800A694C,
    (s32)D_800A6958, (s32)D_800A6964, (s32)D_800A6970, (s32)D_800A697C,
    (s32)D_800A6988,
};
s32 D_800A69B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A00[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6A18[] = {
    0, (s32)D_800A69B8, (s32)D_800A69C4, (s32)D_800A69D0,
    (s32)D_800A69DC, (s32)D_800A69E8, (s32)D_800A69F4, (s32)D_800A6A00,
    (s32)D_800A6A0C,
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
    0, 0, 0x60040000,
};
s32 D_800A6A9C[] = {
    0, (s32)D_800A6A3C, (s32)D_800A6A48, (s32)D_800A6A54,
    (s32)D_800A6A60, (s32)D_800A6A6C, (s32)D_800A6A78, (s32)D_800A6A84,
    (s32)D_800A6A90,
};
s32 D_800A6AC0[] = {
    174, 10, 0x60080000,
};
s32 D_800A6ACC[] = {
    174, 10, 0x60080000,
};
s32 D_800A6AD8[] = {
    170, 10, 0x60080000,
};
s32 D_800A6AE4[] = {
    170, 10, 0x60080000,
};
s32 D_800A6AF0[] = {
    170, 10, 0x60080000,
};
s32 D_800A6AFC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6B08[] = {
    110, 10, 0x60080000,
};
s32 D_800A6B14[] = {
    110, 10, 0x60080000,
};
s32 D_800A6B20[] = {
    2, (s32)D_800A6AC0, (s32)D_800A6ACC, (s32)D_800A6AD8,
    (s32)D_800A6AE4, (s32)D_800A6AF0, (s32)D_800A6AFC, (s32)D_800A6B08,
    (s32)D_800A6B14,
};
s32 D_800A6B44[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B50[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B5C[] = {
    0, 0, 0x60040000,
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
    0, 0, 0x60040000,
};
s32 D_800A6BA4[] = {
    0, (s32)D_800A6B44, (s32)D_800A6B50, (s32)D_800A6B5C,
    (s32)D_800A6B68, (s32)D_800A6B74, (s32)D_800A6B80, (s32)D_800A6B8C,
    (s32)D_800A6B98,
};
s32 D_800A6BC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6BF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C04[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6C28[] = {
    0, (s32)D_800A6BC8, (s32)D_800A6BD4, (s32)D_800A6BE0,
    (s32)D_800A6BEC, (s32)D_800A6BF8, (s32)D_800A6C04, (s32)D_800A6C10,
    (s32)D_800A6C1C,
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
    0, 0, 0x60040000,
};
s32 D_800A6CAC[] = {
    0, (s32)D_800A6C4C, (s32)D_800A6C58, (s32)D_800A6C64,
    (s32)D_800A6C70, (s32)D_800A6C7C, (s32)D_800A6C88, (s32)D_800A6C94,
    (s32)D_800A6CA0,
};
s32 D_800A6CD0[] = {
    182, 10, 0x60080000,
};
s32 D_800A6CDC[] = {
    182, 10, 0x60080000,
};
s32 D_800A6CE8[] = {
    182, 10, 0x60080000,
};
s32 D_800A6CF4[] = {
    182, 10, 0x60080000,
};
s32 D_800A6D00[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D0C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D18[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D24[] = {
    71, 10, 0x60080000,
};
s32 D_800A6D30[] = {
    2, (s32)D_800A6CD0, (s32)D_800A6CDC, (s32)D_800A6CE8,
    (s32)D_800A6CF4, (s32)D_800A6D00, (s32)D_800A6D0C, (s32)D_800A6D18,
    (s32)D_800A6D24,
};
s32 D_800A6D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D60[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D78[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D84[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D90[] = {
    0, 0, 0x60040000,
};
s32 D_800A6D9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DB4[] = {
    0, (s32)D_800A6D54, (s32)D_800A6D60, (s32)D_800A6D6C,
    (s32)D_800A6D78, (s32)D_800A6D84, (s32)D_800A6D90, (s32)D_800A6D9C,
    (s32)D_800A6DA8,
};
s32 D_800A6DD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6DFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E08[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E14[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E20[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E38[] = {
    0, (s32)D_800A6DD8, (s32)D_800A6DE4, (s32)D_800A6DF0,
    (s32)D_800A6DFC, (s32)D_800A6E08, (s32)D_800A6E14, (s32)D_800A6E20,
    (s32)D_800A6E2C,
};
s32 D_800A6E5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E68[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E74[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E80[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6E98[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EBC[] = {
    0, (s32)D_800A6E5C, (s32)D_800A6E68, (s32)D_800A6E74,
    (s32)D_800A6E80, (s32)D_800A6E8C, (s32)D_800A6E98, (s32)D_800A6EA4,
    (s32)D_800A6EB0,
};
s32 D_800A6EE0[] = {
    110, 10, 0x60080000,
};
s32 D_800A6EEC[] = {
    110, 10, 0x60080000,
};
s32 D_800A6EF8[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F04[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F10[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F1C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F28[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F34[] = {
    110, 10, 0x60080000,
};
s32 D_800A6F40[] = {
    1, (s32)D_800A6EE0, (s32)D_800A6EEC, (s32)D_800A6EF8,
    (s32)D_800A6F04, (s32)D_800A6F10, (s32)D_800A6F1C, (s32)D_800A6F28,
    (s32)D_800A6F34,
};
s32 D_800A6F64[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F70[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F88[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F94[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FC4[] = {
    0, (s32)D_800A6F64, (s32)D_800A6F70, (s32)D_800A6F7C,
    (s32)D_800A6F88, (s32)D_800A6F94, (s32)D_800A6FA0, (s32)D_800A6FAC,
    (s32)D_800A6FB8,
};
s32 D_800A6FE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6FF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7000[] = {
    0, 0, 0x60040000,
};
s32 D_800A700C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7018[] = {
    0, 0, 0x60040000,
};
s32 D_800A7024[] = {
    0, 0, 0x60040000,
};
s32 D_800A7030[] = {
    0, 0, 0x60040000,
};
s32 D_800A703C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7048[] = {
    0, (s32)D_800A6FE8, (s32)D_800A6FF4, (s32)D_800A7000,
    (s32)D_800A700C, (s32)D_800A7018, (s32)D_800A7024, (s32)D_800A7030,
    (s32)D_800A703C,
};
s32 D_800A706C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7078[] = {
    0, 0, 0x60040000,
};
s32 D_800A7084[] = {
    0, 0, 0x60040000,
};
s32 D_800A7090[] = {
    0, 0, 0x60040000,
};
s32 D_800A709C[] = {
    0, 0, 0x60040000,
};
s32 D_800A70A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A70B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A70C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A70CC[] = {
    0, (s32)D_800A706C, (s32)D_800A7078, (s32)D_800A7084,
    (s32)D_800A7090, (s32)D_800A709C, (s32)D_800A70A8, (s32)D_800A70B4,
    (s32)D_800A70C0,
};
s32 D_800A70F0[] = {
    182, 10, 0x60080000,
};
s32 D_800A70FC[] = {
    182, 10, 0x60080000,
};
s32 D_800A7108[] = {
    182, 10, 0x60080000,
};
s32 D_800A7114[] = {
    182, 10, 0x60080000,
};
s32 D_800A7120[] = {
    71, 10, 0x60080000,
};
s32 D_800A712C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7138[] = {
    71, 10, 0x60080000,
};
s32 D_800A7144[] = {
    71, 10, 0x60080000,
};
s32 D_800A7150[] = {
    1, (s32)D_800A70F0, (s32)D_800A70FC, (s32)D_800A7108,
    (s32)D_800A7114, (s32)D_800A7120, (s32)D_800A712C, (s32)D_800A7138,
    (s32)D_800A7144,
};
s32 D_800A7174[] = {
    0, 0, 0x60040000,
};
s32 D_800A7180[] = {
    0, 0, 0x60040000,
};
s32 D_800A718C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7198[] = {
    0, 0, 0x60040000,
};
s32 D_800A71A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A71B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A71BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A71C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A71D4[] = {
    0, (s32)D_800A7174, (s32)D_800A7180, (s32)D_800A718C,
    (s32)D_800A7198, (s32)D_800A71A4, (s32)D_800A71B0, (s32)D_800A71BC,
    (s32)D_800A71C8,
};
s32 D_800A71F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7204[] = {
    0, 0, 0x60040000,
};
s32 D_800A7210[] = {
    0, 0, 0x60040000,
};
s32 D_800A721C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7228[] = {
    0, 0, 0x60040000,
};
s32 D_800A7234[] = {
    0, 0, 0x60040000,
};
s32 D_800A7240[] = {
    0, 0, 0x60040000,
};
s32 D_800A724C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7258[] = {
    0, (s32)D_800A71F8, (s32)D_800A7204, (s32)D_800A7210,
    (s32)D_800A721C, (s32)D_800A7228, (s32)D_800A7234, (s32)D_800A7240,
    (s32)D_800A724C,
};
s32 D_800A727C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7288[] = {
    0, 0, 0x60040000,
};
s32 D_800A7294[] = {
    0, 0, 0x60040000,
};
s32 D_800A72A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A72AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A72B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A72C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A72D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A72DC[] = {
    0, (s32)D_800A727C, (s32)D_800A7288, (s32)D_800A7294,
    (s32)D_800A72A0, (s32)D_800A72AC, (s32)D_800A72B8, (s32)D_800A72C4,
    (s32)D_800A72D0,
};
s32 D_800A7300[] = {
    182, 10, 0x60080000,
};
s32 D_800A730C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7318[] = {
    182, 10, 0x60080000,
};
s32 D_800A7324[] = {
    182, 10, 0x60080000,
};
s32 D_800A7330[] = {
    71, 10, 0x60080000,
};
s32 D_800A733C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7348[] = {
    71, 10, 0x60080000,
};
s32 D_800A7354[] = {
    71, 10, 0x60080000,
};
s32 D_800A7360[] = {
    5, (s32)D_800A7300, (s32)D_800A730C, (s32)D_800A7318,
    (s32)D_800A7324, (s32)D_800A7330, (s32)D_800A733C, (s32)D_800A7348,
    (s32)D_800A7354,
};
s32 D_800A7384[] = {
    0, 0, 0x60040000,
};
s32 D_800A7390[] = {
    0, 0, 0x60040000,
};
s32 D_800A739C[] = {
    0, 0, 0x60040000,
};
s32 D_800A73A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A73B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A73C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A73CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A73D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A73E4[] = {
    0, (s32)D_800A7384, (s32)D_800A7390, (s32)D_800A739C,
    (s32)D_800A73A8, (s32)D_800A73B4, (s32)D_800A73C0, (s32)D_800A73CC,
    (s32)D_800A73D8,
};
s32 D_800A7408[] = {
    0, 0, 0x60040000,
};
s32 D_800A7414[] = {
    0, 0, 0x60040000,
};
s32 D_800A7420[] = {
    0, 0, 0x60040000,
};
s32 D_800A742C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7438[] = {
    0, 0, 0x60040000,
};
s32 D_800A7444[] = {
    0, 0, 0x60040000,
};
s32 D_800A7450[] = {
    0, 0, 0x60040000,
};
s32 D_800A745C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7468[] = {
    0, (s32)D_800A7408, (s32)D_800A7414, (s32)D_800A7420,
    (s32)D_800A742C, (s32)D_800A7438, (s32)D_800A7444, (s32)D_800A7450,
    (s32)D_800A745C,
};
s32 D_800A748C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7498[] = {
    0, 0, 0x60040000,
};
s32 D_800A74A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A74B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A74C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A74E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74EC[] = {
    0, (s32)D_800A748C, (s32)D_800A7498, (s32)D_800A74A4,
    (s32)D_800A74B0, (s32)D_800A74BC, (s32)D_800A74C8, (s32)D_800A74D4,
    (s32)D_800A74E0,
};
s32 D_800A7510[] = {
    110, 10, 0x60080000,
};
s32 D_800A751C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7528[] = {
    110, 10, 0x60080000,
};
s32 D_800A7534[] = {
    110, 10, 0x60080000,
};
s32 D_800A7540[] = {
    110, 10, 0x60080000,
};
s32 D_800A754C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7558[] = {
    110, 10, 0x60080000,
};
s32 D_800A7564[] = {
    110, 10, 0x60080000,
};
s32 D_800A7570[] = {
    1, (s32)D_800A7510, (s32)D_800A751C, (s32)D_800A7528,
    (s32)D_800A7534, (s32)D_800A7540, (s32)D_800A754C, (s32)D_800A7558,
    (s32)D_800A7564,
};
s32 D_800A7594[] = {
    0, 0, 0x60040000,
};
s32 D_800A75A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A75B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A75C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A75D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A75E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A75F4[] = {
    0, (s32)D_800A7594, (s32)D_800A75A0, (s32)D_800A75AC,
    (s32)D_800A75B8, (s32)D_800A75C4, (s32)D_800A75D0, (s32)D_800A75DC,
    (s32)D_800A75E8,
};
s32 D_800A7618[] = {
    0, 0, 0x60040000,
};
s32 D_800A7624[] = {
    0, 0, 0x60040000,
};
s32 D_800A7630[] = {
    0, 0, 0x60040000,
};
s32 D_800A763C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7648[] = {
    0, 0, 0x60040000,
};
s32 D_800A7654[] = {
    0, 0, 0x60040000,
};
s32 D_800A7660[] = {
    0, 0, 0x60040000,
};
s32 D_800A766C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7678[] = {
    0, (s32)D_800A7618, (s32)D_800A7624, (s32)D_800A7630,
    (s32)D_800A763C, (s32)D_800A7648, (s32)D_800A7654, (s32)D_800A7660,
    (s32)D_800A766C,
};
s32 D_800A769C[] = {
    0, 0, 0x60040000,
};
s32 D_800A76A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A76B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A76C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A76CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A76D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A76E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A76F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A76FC[] = {
    0, (s32)D_800A769C, (s32)D_800A76A8, (s32)D_800A76B4,
    (s32)D_800A76C0, (s32)D_800A76CC, (s32)D_800A76D8, (s32)D_800A76E4,
    (s32)D_800A76F0,
};
s32 D_800A7720[] = {
    182, 10, 0x60080000,
};
s32 D_800A772C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7738[] = {
    182, 10, 0x60080000,
};
s32 D_800A7744[] = {
    182, 10, 0x60080000,
};
s32 D_800A7750[] = {
    71, 10, 0x60080000,
};
s32 D_800A775C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7768[] = {
    71, 10, 0x60080000,
};
s32 D_800A7774[] = {
    71, 10, 0x60080000,
};
s32 D_800A7780[] = {
    1, (s32)D_800A7720, (s32)D_800A772C, (s32)D_800A7738,
    (s32)D_800A7744, (s32)D_800A7750, (s32)D_800A775C, (s32)D_800A7768,
    (s32)D_800A7774,
};
s32 D_800A77A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A77B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A77C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A77D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A77E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A77EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A77F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7804[] = {
    0, (s32)D_800A77A4, (s32)D_800A77B0, (s32)D_800A77BC,
    (s32)D_800A77C8, (s32)D_800A77D4, (s32)D_800A77E0, (s32)D_800A77EC,
    (s32)D_800A77F8,
};
s32 D_800A7828[] = {
    0, 0, 0x60040000,
};
s32 D_800A7834[] = {
    0, 0, 0x60040000,
};
s32 D_800A7840[] = {
    0, 0, 0x60040000,
};
s32 D_800A784C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7858[] = {
    0, 0, 0x60040000,
};
s32 D_800A7864[] = {
    0, 0, 0x60040000,
};
s32 D_800A7870[] = {
    0, 0, 0x60040000,
};
s32 D_800A787C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7888[] = {
    0, (s32)D_800A7828, (s32)D_800A7834, (s32)D_800A7840,
    (s32)D_800A784C, (s32)D_800A7858, (s32)D_800A7864, (s32)D_800A7870,
    (s32)D_800A787C,
};
s32 D_800A78AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A78B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A78C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A78D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A78DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A78E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A78F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7900[] = {
    0, 0, 0x60040000,
};
s32 D_800A790C[] = {
    0, (s32)D_800A78AC, (s32)D_800A78B8, (s32)D_800A78C4,
    (s32)D_800A78D0, (s32)D_800A78DC, (s32)D_800A78E8, (s32)D_800A78F4,
    (s32)D_800A7900,
};
s32 D_800A7930[] = {
    110, 10, 0x60080000,
};
s32 D_800A793C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7948[] = {
    110, 10, 0x60080000,
};
s32 D_800A7954[] = {
    110, 10, 0x60080000,
};
s32 D_800A7960[] = {
    110, 10, 0x60080000,
};
s32 D_800A796C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7978[] = {
    110, 10, 0x60080000,
};
s32 D_800A7984[] = {
    110, 10, 0x60080000,
};
s32 D_800A7990[] = {
    3, (s32)D_800A7930, (s32)D_800A793C, (s32)D_800A7948,
    (s32)D_800A7954, (s32)D_800A7960, (s32)D_800A796C, (s32)D_800A7978,
    (s32)D_800A7984,
};
s32 D_800A79B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A79C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A79D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A79E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A79F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A79FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A08[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A14[] = {
    0, (s32)D_800A79B4, (s32)D_800A79C0, (s32)D_800A79CC,
    (s32)D_800A79D8, (s32)D_800A79E4, (s32)D_800A79F0, (s32)D_800A79FC,
    (s32)D_800A7A08,
};
s32 D_800A7A38[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A44[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A50[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A68[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A74[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A80[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7A98[] = {
    0, (s32)D_800A7A38, (s32)D_800A7A44, (s32)D_800A7A50,
    (s32)D_800A7A5C, (s32)D_800A7A68, (s32)D_800A7A74, (s32)D_800A7A80,
    (s32)D_800A7A8C,
};
s32 D_800A7ABC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AC8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B10[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B1C[] = {
    0, (s32)D_800A7ABC, (s32)D_800A7AC8, (s32)D_800A7AD4,
    (s32)D_800A7AE0, (s32)D_800A7AEC, (s32)D_800A7AF8, (s32)D_800A7B04,
    (s32)D_800A7B10,
};
s32 D_800A7B40[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B4C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B58[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B64[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B70[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B7C[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B88[] = {
    110, 10, 0x60080000,
};
s32 D_800A7B94[] = {
    110, 10, 0x60080000,
};
s32 D_800A7BA0[] = {
    3, (s32)D_800A7B40, (s32)D_800A7B4C, (s32)D_800A7B58,
    (s32)D_800A7B64, (s32)D_800A7B70, (s32)D_800A7B7C, (s32)D_800A7B88,
    (s32)D_800A7B94,
};
s32 D_800A7BC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C00[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C18[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C24[] = {
    0, (s32)D_800A7BC4, (s32)D_800A7BD0, (s32)D_800A7BDC,
    (s32)D_800A7BE8, (s32)D_800A7BF4, (s32)D_800A7C00, (s32)D_800A7C0C,
    (s32)D_800A7C18,
};
s32 D_800A7C48[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C54[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C60[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C78[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C84[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C90[] = {
    0, 0, 0x60040000,
};
s32 D_800A7C9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CA8[] = {
    0, (s32)D_800A7C48, (s32)D_800A7C54, (s32)D_800A7C60,
    (s32)D_800A7C6C, (s32)D_800A7C78, (s32)D_800A7C84, (s32)D_800A7C90,
    (s32)D_800A7C9C,
};
s32 D_800A7CCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D08[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D14[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D20[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D2C[] = {
    0, (s32)D_800A7CCC, (s32)D_800A7CD8, (s32)D_800A7CE4,
    (s32)D_800A7CF0, (s32)D_800A7CFC, (s32)D_800A7D08, (s32)D_800A7D14,
    (s32)D_800A7D20,
};
s32 D_800A7D50[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D5C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D68[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D74[] = {
    182, 10, 0x60080000,
};
s32 D_800A7D80[] = {
    71, 10, 0x60080000,
};
s32 D_800A7D8C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7D98[] = {
    71, 10, 0x60080000,
};
s32 D_800A7DA4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7DB0[] = {
    2, (s32)D_800A7D50, (s32)D_800A7D5C, (s32)D_800A7D68,
    (s32)D_800A7D74, (s32)D_800A7D80, (s32)D_800A7D8C, (s32)D_800A7D98,
    (s32)D_800A7DA4,
};
s32 D_800A7DD4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DE0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E04[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E10[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E28[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E34[] = {
    0, (s32)D_800A7DD4, (s32)D_800A7DE0, (s32)D_800A7DEC,
    (s32)D_800A7DF8, (s32)D_800A7E04, (s32)D_800A7E10, (s32)D_800A7E1C,
    (s32)D_800A7E28,
};
s32 D_800A7E58[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E64[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E88[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E94[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EB8[] = {
    0, (s32)D_800A7E58, (s32)D_800A7E64, (s32)D_800A7E70,
    (s32)D_800A7E7C, (s32)D_800A7E88, (s32)D_800A7E94, (s32)D_800A7EA0,
    (s32)D_800A7EAC,
};
s32 D_800A7EDC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EE8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F00[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F18[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F24[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F30[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F3C[] = {
    0, (s32)D_800A7EDC, (s32)D_800A7EE8, (s32)D_800A7EF4,
    (s32)D_800A7F00, (s32)D_800A7F0C, (s32)D_800A7F18, (s32)D_800A7F24,
    (s32)D_800A7F30,
};
s32 D_800A7F60[] = {
    182, 10, 0x60080000,
};
s32 D_800A7F6C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7F78[] = {
    182, 10, 0x60080000,
};
s32 D_800A7F84[] = {
    182, 10, 0x60080000,
};
s32 D_800A7F90[] = {
    71, 10, 0x60080000,
};
s32 D_800A7F9C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7FA8[] = {
    71, 10, 0x60080000,
};
s32 D_800A7FB4[] = {
    71, 10, 0x60080000,
};
s32 D_800A7FC0[] = {
    5, (s32)D_800A7F60, (s32)D_800A7F6C, (s32)D_800A7F78,
    (s32)D_800A7F84, (s32)D_800A7F90, (s32)D_800A7F9C, (s32)D_800A7FA8,
    (s32)D_800A7FB4,
};
s32 D_800A7FE4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FF0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7FFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8008[] = {
    0, 0, 0x60040000,
};
s32 D_800A8014[] = {
    0, 0, 0x60040000,
};
s32 D_800A8020[] = {
    0, 0, 0x60040000,
};
s32 D_800A802C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8038[] = {
    0, 0, 0x60040000,
};
s32 D_800A8044[] = {
    0, (s32)D_800A7FE4, (s32)D_800A7FF0, (s32)D_800A7FFC,
    (s32)D_800A8008, (s32)D_800A8014, (s32)D_800A8020, (s32)D_800A802C,
    (s32)D_800A8038,
};
s32 D_800A8068[] = {
    0, 0, 0x60040000,
};
s32 D_800A8074[] = {
    0, 0, 0x60040000,
};
s32 D_800A8080[] = {
    0, 0, 0x60040000,
};
s32 D_800A808C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8098[] = {
    0, 0, 0x60040000,
};
s32 D_800A80A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A80B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A80BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A80C8[] = {
    0, (s32)D_800A8068, (s32)D_800A8074, (s32)D_800A8080,
    (s32)D_800A808C, (s32)D_800A8098, (s32)D_800A80A4, (s32)D_800A80B0,
    (s32)D_800A80BC,
};
s32 D_800A80EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A80F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A8104[] = {
    0, 0, 0x60040000,
};
s32 D_800A8110[] = {
    0, 0, 0x60040000,
};
s32 D_800A811C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8128[] = {
    0, 0, 0x60040000,
};
s32 D_800A8134[] = {
    0, 0, 0x60040000,
};
s32 D_800A8140[] = {
    0, 0, 0x60040000,
};
s32 D_800A814C[] = {
    0, (s32)D_800A80EC, (s32)D_800A80F8, (s32)D_800A8104,
    (s32)D_800A8110, (s32)D_800A811C, (s32)D_800A8128, (s32)D_800A8134,
    (s32)D_800A8140,
};
s32 D_800A8170[] = {
    182, 10, 0x60080000,
};
s32 D_800A817C[] = {
    182, 10, 0x60080000,
};
s32 D_800A8188[] = {
    182, 10, 0x60080000,
};
s32 D_800A8194[] = {
    182, 10, 0x60080000,
};
s32 D_800A81A0[] = {
    71, 10, 0x60080000,
};
s32 D_800A81AC[] = {
    71, 10, 0x60080000,
};
s32 D_800A81B8[] = {
    71, 10, 0x60080000,
};
s32 D_800A81C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A81D0[] = {
    1, (s32)D_800A8170, (s32)D_800A817C, (s32)D_800A8188,
    (s32)D_800A8194, (s32)D_800A81A0, (s32)D_800A81AC, (s32)D_800A81B8,
    (s32)D_800A81C4,
};
s32 D_800A81F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8200[] = {
    0, 0, 0x60040000,
};
s32 D_800A820C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8218[] = {
    0, 0, 0x60040000,
};
s32 D_800A8224[] = {
    0, 0, 0x60040000,
};
s32 D_800A8230[] = {
    0, 0, 0x60040000,
};
s32 D_800A823C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8248[] = {
    0, 0, 0x60040000,
};
s32 D_800A8254[] = {
    0, (s32)D_800A81F4, (s32)D_800A8200, (s32)D_800A820C,
    (s32)D_800A8218, (s32)D_800A8224, (s32)D_800A8230, (s32)D_800A823C,
    (s32)D_800A8248,
};
s32 D_800A8278[] = {
    0, 0, 0x60040000,
};
s32 D_800A8284[] = {
    0, 0, 0x60040000,
};
s32 D_800A8290[] = {
    0, 0, 0x60040000,
};
s32 D_800A829C[] = {
    0, 0, 0x60040000,
};
s32 D_800A82A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A82B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A82C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A82CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A82D8[] = {
    0, (s32)D_800A8278, (s32)D_800A8284, (s32)D_800A8290,
    (s32)D_800A829C, (s32)D_800A82A8, (s32)D_800A82B4, (s32)D_800A82C0,
    (s32)D_800A82CC,
};
s32 D_800A82FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A8308[] = {
    0, 0, 0x60040000,
};
s32 D_800A8314[] = {
    0, 0, 0x60040000,
};
s32 D_800A8320[] = {
    0, 0, 0x60040000,
};
s32 D_800A832C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8338[] = {
    0, 0, 0x60040000,
};
s32 D_800A8344[] = {
    0, 0, 0x60040000,
};
s32 D_800A8350[] = {
    0, 0, 0x60040000,
};
s32 D_800A835C[] = {
    0, (s32)D_800A82FC, (s32)D_800A8308, (s32)D_800A8314,
    (s32)D_800A8320, (s32)D_800A832C, (s32)D_800A8338, (s32)D_800A8344,
    (s32)D_800A8350,
};
s32 D_800A8380[] = {
    182, 10, 0x60080000,
};
s32 D_800A838C[] = {
    182, 10, 0x60080000,
};
s32 D_800A8398[] = {
    182, 10, 0x60080000,
};
s32 D_800A83A4[] = {
    182, 10, 0x60080000,
};
s32 D_800A83B0[] = {
    71, 10, 0x60080000,
};
s32 D_800A83BC[] = {
    71, 10, 0x60080000,
};
s32 D_800A83C8[] = {
    71, 10, 0x60080000,
};
s32 D_800A83D4[] = {
    71, 10, 0x60080000,
};
s32 D_800A83E0[] = {
    1, (s32)D_800A8380, (s32)D_800A838C, (s32)D_800A8398,
    (s32)D_800A83A4, (s32)D_800A83B0, (s32)D_800A83BC, (s32)D_800A83C8,
    (s32)D_800A83D4,
};
s32 D_800A8404[] = {
    0, 0, 0x60040000,
};
s32 D_800A8410[] = {
    0, 0, 0x60040000,
};
s32 D_800A841C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8428[] = {
    0, 0, 0x60040000,
};
s32 D_800A8434[] = {
    0, 0, 0x60040000,
};
s32 D_800A8440[] = {
    0, 0, 0x60040000,
};
s32 D_800A844C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8458[] = {
    0, 0, 0x60040000,
};
s32 D_800A8464[] = {
    0, (s32)D_800A8404, (s32)D_800A8410, (s32)D_800A841C,
    (s32)D_800A8428, (s32)D_800A8434, (s32)D_800A8440, (s32)D_800A844C,
    (s32)D_800A8458,
};
s32 D_800A8488[] = {
    0, 0, 0x60040000,
};
s32 D_800A8494[] = {
    0, 0, 0x60040000,
};
s32 D_800A84A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A84AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A84B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A84C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A84D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A84DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A84E8[] = {
    0, (s32)D_800A8488, (s32)D_800A8494, (s32)D_800A84A0,
    (s32)D_800A84AC, (s32)D_800A84B8, (s32)D_800A84C4, (s32)D_800A84D0,
    (s32)D_800A84DC,
};
s32 D_800A850C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8518[] = {
    0, 0, 0x60040000,
};
s32 D_800A8524[] = {
    0, 0, 0x60040000,
};
s32 D_800A8530[] = {
    0, 0, 0x60040000,
};
s32 D_800A853C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8548[] = {
    0, 0, 0x60040000,
};
s32 D_800A8554[] = {
    0, 0, 0x60040000,
};
s32 D_800A8560[] = {
    0, 0, 0x60040000,
};
s32 D_800A856C[] = {
    0, (s32)D_800A850C, (s32)D_800A8518, (s32)D_800A8524,
    (s32)D_800A8530, (s32)D_800A853C, (s32)D_800A8548, (s32)D_800A8554,
    (s32)D_800A8560,
};
s32 D_800A8590[] = {
    174, 10, 0x60080000,
};
s32 D_800A859C[] = {
    174, 10, 0x60080000,
};
s32 D_800A85A8[] = {
    170, 10, 0x60080000,
};
s32 D_800A85B4[] = {
    170, 10, 0x60080000,
};
s32 D_800A85C0[] = {
    182, 10, 0x60080000,
};
s32 D_800A85CC[] = {
    182, 10, 0x60080000,
};
s32 D_800A85D8[] = {
    71, 10, 0x60080000,
};
s32 D_800A85E4[] = {
    71, 10, 0x60080000,
};
s32 D_800A85F0[] = {
    1, (s32)D_800A8590, (s32)D_800A859C, (s32)D_800A85A8,
    (s32)D_800A85B4, (s32)D_800A85C0, (s32)D_800A85CC, (s32)D_800A85D8,
    (s32)D_800A85E4,
};
s32 D_800A8614[] = {
    0, 0, 0x60040000,
};
s32 D_800A8620[] = {
    0, 0, 0x60040000,
};
s32 D_800A862C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8638[] = {
    0, 0, 0x60040000,
};
s32 D_800A8644[] = {
    0, 0, 0x60040000,
};
s32 D_800A8650[] = {
    0, 0, 0x60040000,
};
s32 D_800A865C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8668[] = {
    0, 0, 0x60040000,
};
s32 D_800A8674[] = {
    0, (s32)D_800A8614, (s32)D_800A8620, (s32)D_800A862C,
    (s32)D_800A8638, (s32)D_800A8644, (s32)D_800A8650, (s32)D_800A865C,
    (s32)D_800A8668,
};
s32 D_800A8698[] = {
    0, 0, 0x60040000,
};
s32 D_800A86A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A86B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A86BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A86C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A86D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A86E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A86EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A86F8[] = {
    0, (s32)D_800A8698, (s32)D_800A86A4, (s32)D_800A86B0,
    (s32)D_800A86BC, (s32)D_800A86C8, (s32)D_800A86D4, (s32)D_800A86E0,
    (s32)D_800A86EC,
};
s32 D_800A871C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8728[] = {
    0, 0, 0x60040000,
};
s32 D_800A8734[] = {
    0, 0, 0x60040000,
};
s32 D_800A8740[] = {
    0, 0, 0x60040000,
};
s32 D_800A874C[] = {
    0, 0, 0x60040000,
};
s32 D_800A8758[] = {
    0, 0, 0x60040000,
};
s32 D_800A8764[] = {
    0, 0, 0x60040000,
};
s32 D_800A8770[] = {
    0, 0, 0x60040000,
};
s32 D_800A877C[] = {
    0, (s32)D_800A871C, (s32)D_800A8728, (s32)D_800A8734,
    (s32)D_800A8740, (s32)D_800A874C, (s32)D_800A8758, (s32)D_800A8764,
    (s32)D_800A8770,
};
s32 D_800A87A0[] = {
    230, 1, 0, (s32)D_800A5AA0,
    (s32)D_800A5B24, (s32)D_800A5BA8, (s32)D_800A5C2C, 237,
    2, 0, (s32)D_800A5CB0, (s32)D_800A5D34,
    (s32)D_800A5DB8, (s32)D_800A5E3C, 242, 3,
    0, (s32)D_800A5EC0, (s32)D_800A5F44, (s32)D_800A5FC8,
    (s32)D_800A604C, 257, 5, 0,
    (s32)D_800A60D0, (s32)D_800A6154, (s32)D_800A61D8, (s32)D_800A625C,
    260, 6, 0, (s32)D_800A62E0,
    (s32)D_800A6364, (s32)D_800A63E8, (s32)D_800A646C, 265,
    7, 0, (s32)D_800A64F0, (s32)D_800A6574,
    (s32)D_800A65F8, (s32)D_800A667C, 269, 8,
    0, (s32)D_800A6700, (s32)D_800A6784, (s32)D_800A6808,
    (s32)D_800A688C, 275, 9, 0,
    (s32)D_800A6910, (s32)D_800A6994, (s32)D_800A6A18, (s32)D_800A6A9C,
    280, 10, 0, (s32)D_800A6B20,
    (s32)D_800A6BA4, (s32)D_800A6C28, (s32)D_800A6CAC, 285,
    11, 0, (s32)D_800A6D30, (s32)D_800A6DB4,
    (s32)D_800A6E38, (s32)D_800A6EBC, 290, 12,
    0, (s32)D_800A6F40, (s32)D_800A6FC4, (s32)D_800A7048,
    (s32)D_800A70CC, 296, 13, 0,
    (s32)D_800A7150, (s32)D_800A71D4, (s32)D_800A7258, (s32)D_800A72DC,
    315, 18, 0, (s32)D_800A7360,
    (s32)D_800A73E4, (s32)D_800A7468, (s32)D_800A74EC, 318,
    19, 0, (s32)D_800A7570, (s32)D_800A75F4,
    (s32)D_800A7678, (s32)D_800A76FC, 326, 20,
    0, (s32)D_800A7780, (s32)D_800A7804, (s32)D_800A7888,
    (s32)D_800A790C, 330, 21, 0,
    (s32)D_800A7990, (s32)D_800A7A14, (s32)D_800A7A98, (s32)D_800A7B1C,
    335, 22, 0, (s32)D_800A7BA0,
    (s32)D_800A7C24, (s32)D_800A7CA8, (s32)D_800A7D2C, 339,
    23, 0, (s32)D_800A7DB0, (s32)D_800A7E34,
    (s32)D_800A7EB8, (s32)D_800A7F3C, 343, 24,
    0, (s32)D_800A7FC0, (s32)D_800A8044, (s32)D_800A80C8,
    (s32)D_800A814C, 358, 28, 0,
    (s32)D_800A81D0, (s32)D_800A8254, (s32)D_800A82D8, (s32)D_800A835C,
    364, 29, 0, (s32)D_800A83E0,
    (s32)D_800A8464, (s32)D_800A84E8, (s32)D_800A856C, 371,
    30, 0, (s32)D_800A85F0, (s32)D_800A8674,
    (s32)D_800A86F8, (s32)D_800A877C,
};
s32 D_800A8A08[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140014C, 0x400030, 0x1FF0140,
    0x1000140, 0x1400174, 0x4000D0, 0x1FF0150,
    0x1000140, 0x1400140, 0x400000, 0x1FF0160,
    0x1000140, 0x1000168, 160, 0x1FF0170,
    0x1000140, 0x1400154, 0x400050, 0x1FE0140,
    0x1000140, 0x140015C, 0x400070, 0x1FE0150,
    0x1000140, 0x1400164, 0x400090, 0x1FE0160,
    0x1000140, 0x140016C, 0x4000B0, 0x1FE0170,
    0x1000140, 0x1000140, 0, 0x1FD0140,
    0x1000140, 0x1000154, 80, 0x1FD0150,
};
s32 D_800A8B08[] = {
    17, 37411, 65535,
};
s32 D_800A8B14[] = {
    0x17649, 65535,
};
s32 D_800A8B1C[] = {
    17, 0x19223, 65535,
};
s32 D_800A8B28[] = {
    0x10011, 16, 65535,
};
s32 D_800A8B34[] = {
    17, 65535,
};
s32 D_800A8B3C[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A8B48[] = {
    17, 16, 0x19223, 65535,
};
s32 D_800A8B58[] = {
    17, 37409, 65535,
};
s32 D_800A8B64[] = {
    0x1764A, 65535,
};
s32 D_800A8B6C[] = {
    17, 0x19221, 65535,
};
s32 D_800A8B78[] = {
    0x10011, 16, 65535,
};
s32 D_800A8B84[] = {
    17, 65535,
};
s32 D_800A8B8C[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A8B98[] = {
    17, 16, 0x19221, 65535,
};
s32 D_800A8BA8[] = {
    17, 37574, 65535,
};
s32 D_800A8BB4[] = {
    0x1764C, 65535,
};
s32 D_800A8BBC[] = {
    17, 0x192C6, 65535,
};
s32 D_800A8BC8[] = {
    0x10011, 16, 65535,
};
s32 D_800A8BD4[] = {
    17, 65535,
};
s32 D_800A8BDC[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A8BE8[] = {
    17, 16, 0x192C6, 65535,
};
s32 D_800A8BF8[] = {
    37531, 17, 65535,
};
s32 D_800A8C04[] = {
    0x1764D, 65535,
};
s32 D_800A8C0C[] = {
    17, 0x1929B, 65535,
};
s32 D_800A8C18[] = {
    0x10011, 16, 65535,
};
s32 D_800A8C24[] = {
    17, 65535,
};
s32 D_800A8C2C[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A8C38[] = {
    17, 16, 0x1929B, 65535,
};
s32 D_800A8C48[] = {
    0, 0, 852, 0,
    0, 0,
};
s32 D_800A8C60[] = {
    0, 0, 944, 0,
    0, 0,
};
s32 D_800A8C78[] = {
    0, 0, 945, 0,
    0, 0,
};
s32 D_800A8C90[] = {
    0, 0, 949, 0,
    0, 0,
};
s32 D_800A8CA8[] = {
    (s32)D_800A8B08, (s32)D_800A8B14, 871, (s32)D_800A8B1C,
    0, 872, (s32)D_800A8B28, (s32)D_800A8B34,
    873, (s32)D_800A8B3C, (s32)D_800A8B48, 876,
    0, 0, 0,
};
s32 D_800A8CE4[] = {
    (s32)D_800A8B58, (s32)D_800A8B64, 871, (s32)D_800A8B6C,
    0, 872, (s32)D_800A8B78, (s32)D_800A8B84,
    873, (s32)D_800A8B8C, (s32)D_800A8B98, 877,
    0, 0, 0,
};
s32 D_800A8D20[] = {
    (s32)D_800A8BA8, (s32)D_800A8BB4, 887, (s32)D_800A8BBC,
    0, 888, (s32)D_800A8BC8, (s32)D_800A8BD4,
    889, (s32)D_800A8BDC, (s32)D_800A8BE8, 890,
    0, 0, 0,
};
s32 D_800A8D5C[] = {
    (s32)D_800A8BF8, (s32)D_800A8C04, 887, (s32)D_800A8C0C,
    0, 888, (s32)D_800A8C18, (s32)D_800A8C24,
    889, (s32)D_800A8C2C, (s32)D_800A8C38, 891,
    0, 0, 0,
};
s32 D_800A8D98[] = {
    0x17E17, 0x17E1F, 65535,
};
s32 D_800A8DA4[] = {
    0x17E00, 0x17E1E, 65535,
};
s32 D_800A8DB0[] = {
    0x17E07, 0x17E1E, 65535,
};
s32 D_800A8DBC[] = {
    0x17E08, 0x17E1E, 65535,
};
s32 D_800A8DC8[] = {
    0x17E13, 8, 65535,
};
s32 D_800A8DD4[] = {
    37411, 0x17E0B, 0x17E1E, 0x18014,
    65535,
};
s32 D_800A8DE8[] = {
    0x17E0C, 0x17E1E, 0x18014, 37409,
    65535,
};
s32 D_800A8DFC[] = {
    0x17E17, 0x17E20, 0x18014, 37574,
    65535,
};
s32 D_800A8E10[] = {
    0x17E16, 0x17E1F, 0x18014, 37531,
    65535,
};
s32 D_800A8E24[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A8E30[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A8E3C[] = {
    0x17E20, 9, 65535,
};
s32 D_800A8E48[] = {
    0x17E05, 10, 65535,
};
s32 D_800A8E54[] = {
    0x17E06, 10, 65535,
};
s32 D_800A8E60[] = {
    0x17E0B, 10, 65535,
};
s32 D_800A8E6C[] = {
    0x17E0C, 10, 65535,
};
s32 D_800A8E78[] = {
    0x17E12, 10, 65535,
};
s32 D_800A8E84[] = {
    0x17E13, 10, 65535,
};
s32 D_800A8E90[] = {
    0x17E15, 10, 65535,
};
s32 D_800A8E9C[] = {
    0x17E16, 10, 65535,
};
s32 D_800A8EA8[] = {
    0x17E17, 10, 65535,
};
s32 D_800A8EB4[] = {
    0x17E1B, 10, 65535,
};
s32 D_800A8EC0[] = {
    0x17E1C, 10, 65535,
};
s32 D_800A8ECC[] = {
    (s32)D_800A8D98, (s32)D_800A8C48, 0x40023, 0x1580320,
    1,
};
s32 D_800A8EE0[] = {
    (s32)D_800A8DA4, (s32)D_800A8C60, 0x40023, 0x1100268,
    7,
};
s32 D_800A8EF4[] = {
    (s32)D_800A8DB0, (s32)D_800A8C78, 0x40023, 0x1580320,
    1,
};
s32 D_800A8F08[] = {
    (s32)D_800A8DBC, (s32)D_800A8C90, 0x50041, 0x1100268,
    7,
};
s32 D_800A8F1C[] = {
    0, 0, 0x60146, 0,
    0,
};
s32 D_800A8F30[] = {
    (s32)D_800A8DC8, 0, 0x70148, 0xF80190,
    1,
};
s32 D_800A8F44[] = {
    (s32)D_800A8DD4, (s32)D_800A8CA8, 0x80151, 0x1580320,
    1,
};
s32 D_800A8F58[] = {
    (s32)D_800A8DE8, (s32)D_800A8CE4, 0x90152, 0x1CC0378,
    1,
};
s32 D_800A8F6C[] = {
    (s32)D_800A8DFC, (s32)D_800A8D20, 0xA0159, 0xC801C0,
    1,
};
s32 D_800A8F80[] = {
    (s32)D_800A8E10, (s32)D_800A8D5C, 0xB015A, 0x1CC0378,
    1,
};
s32 D_800A8F94[] = {
    (s32)D_800A8E24, 0, 0xC015F, 0x1A801D0,
    1,
};
s32 D_800A8FA8[] = {
    (s32)D_800A8E30, 0, 0xC015F, 0x16002C0,
    1,
};
s32 D_800A8FBC[] = {
    (s32)D_800A8E3C, 0, 0xC015F, 0x11002E0,
    1,
};
s32 D_800A8FD0[] = {
    (s32)D_800A8E48, 0, 0xD0160, 0x980370,
    1,
};
s32 D_800A8FE4[] = {
    (s32)D_800A8E54, 0, 0xD0160, 0x1B80130,
    1,
};
s32 D_800A8FF8[] = {
    (s32)D_800A8E60, 0, 0xD0160, 0x1A002E0,
    1,
};
s32 D_800A900C[] = {
    (s32)D_800A8E6C, 0, 0xD0160, 0xF80190,
    1,
};
s32 D_800A9020[] = {
    (s32)D_800A8E78, 0, 0xD0160, 0x1B80250,
    1,
};
s32 D_800A9034[] = {
    (s32)D_800A8E84, 0, 0xD0160, 0x1C00320,
    1,
};
s32 D_800A9048[] = {
    (s32)D_800A8E90, 0, 0xD0160, 0xC80310,
    1,
};
s32 D_800A905C[] = {
    (s32)D_800A8E9C, 0, 0xD0160, 0x1200140,
    1,
};
s32 D_800A9070[] = {
    (s32)D_800A8EA8, 0, 0xD0160, 0x1C00320,
    1,
};
s32 D_800A9084[] = {
    (s32)D_800A8EB4, 0, 0xD0160, 0x980370,
    1,
};
s32 D_800A9098[] = {
    (s32)D_800A8EC0, 0, 0xD0160, 0x1A002E0,
    1,
};
s32 D_800A90AC[] = {
    (s32)D_800A8ECC, (s32)D_800A8EE0, (s32)D_800A8EF4, (s32)D_800A8F08,
    (s32)D_800A8F1C, (s32)D_800A8F30, (s32)D_800A8F44, (s32)D_800A8F58,
    (s32)D_800A8F6C, (s32)D_800A8F80, (s32)D_800A8F94, (s32)D_800A8FA8,
    (s32)D_800A8FBC, (s32)D_800A8FD0, (s32)D_800A8FE4, (s32)D_800A8FF8,
    (s32)D_800A900C, (s32)D_800A9020, (s32)D_800A9034, (s32)D_800A9048,
    (s32)D_800A905C, (s32)D_800A9070, (s32)D_800A9084, (s32)D_800A9098,
    0,
};
s32 D_800A9110[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A9124[] = {
    65535, 65535, 0x2EC0001, 0x7803B0,
    5, 0, 65535, 65535,
    0x2EC0001, 0x1D800F0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A916C[])(void) = {
    func_800A4E74,
};
