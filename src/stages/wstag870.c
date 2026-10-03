#include "common.h"
#include "stage.h"
extern void (*D_800A7A54[])(void);
void func_800A4DA4();
extern StagePoints *D_800A5494[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A5494, GAME.unk44, GAME.unk46);
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
    D_800A7A54[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag870", func_800A4E74);

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
extern s32 D_800A5518[];
extern s32 D_800A5524[];
extern s32 D_800A5530[];
extern s32 D_800A553C[];
extern s32 D_800A5548[];
extern s32 D_800A5554[];
extern s32 D_800A5560[];
extern s32 D_800A556C[];
extern s32 D_800A559C[];
extern s32 D_800A55A8[];
extern s32 D_800A55B4[];
extern s32 D_800A55C0[];
extern s32 D_800A55CC[];
extern s32 D_800A55D8[];
extern s32 D_800A55E4[];
extern s32 D_800A55F0[];
extern s32 D_800A5620[];
extern s32 D_800A562C[];
extern s32 D_800A5638[];
extern s32 D_800A5644[];
extern s32 D_800A5650[];
extern s32 D_800A565C[];
extern s32 D_800A5668[];
extern s32 D_800A5674[];
extern s32 D_800A56A4[];
extern s32 D_800A56B0[];
extern s32 D_800A56BC[];
extern s32 D_800A56C8[];
extern s32 D_800A56D4[];
extern s32 D_800A56E0[];
extern s32 D_800A56EC[];
extern s32 D_800A56F8[];
extern s32 D_800A5728[];
extern s32 D_800A5734[];
extern s32 D_800A5740[];
extern s32 D_800A574C[];
extern s32 D_800A5758[];
extern s32 D_800A5764[];
extern s32 D_800A5770[];
extern s32 D_800A577C[];
extern s32 D_800A57AC[];
extern s32 D_800A57B8[];
extern s32 D_800A57C4[];
extern s32 D_800A57D0[];
extern s32 D_800A57DC[];
extern s32 D_800A57E8[];
extern s32 D_800A57F4[];
extern s32 D_800A5800[];
extern s32 D_800A5830[];
extern s32 D_800A583C[];
extern s32 D_800A5848[];
extern s32 D_800A5854[];
extern s32 D_800A5860[];
extern s32 D_800A586C[];
extern s32 D_800A5878[];
extern s32 D_800A5884[];
extern s32 D_800A58B4[];
extern s32 D_800A58C0[];
extern s32 D_800A58CC[];
extern s32 D_800A58D8[];
extern s32 D_800A58E4[];
extern s32 D_800A58F0[];
extern s32 D_800A58FC[];
extern s32 D_800A5908[];
extern s32 D_800A5938[];
extern s32 D_800A5944[];
extern s32 D_800A5950[];
extern s32 D_800A595C[];
extern s32 D_800A5968[];
extern s32 D_800A5974[];
extern s32 D_800A5980[];
extern s32 D_800A598C[];
extern s32 D_800A59BC[];
extern s32 D_800A59C8[];
extern s32 D_800A59D4[];
extern s32 D_800A59E0[];
extern s32 D_800A59EC[];
extern s32 D_800A59F8[];
extern s32 D_800A5A04[];
extern s32 D_800A5A10[];
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
extern s32 D_800A5578[];
extern s32 D_800A55FC[];
extern s32 D_800A5680[];
extern s32 D_800A5704[];
extern s32 D_800A5788[];
extern s32 D_800A580C[];
extern s32 D_800A5890[];
extern s32 D_800A5914[];
extern s32 D_800A5998[];
extern s32 D_800A5A1C[];
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
extern s32 D_800A76FC[];
extern s32 D_800A766C[];
extern s32 D_800A7708[];
extern s32 D_800A7684[];
extern s32 D_800A7714[];
extern s32 D_800A769C[];
extern s32 D_800A7720[];
extern s32 D_800A76B4[];
extern s32 D_800A772C[];
extern s32 D_800A76CC[];
extern s32 D_800A7738[];
extern s32 D_800A76E4[];
extern s32 D_800A7744[];
extern s32 D_800A7750[];
extern s32 D_800A775C[];
extern s32 D_800A7768[];
extern s32 D_800A7774[];
extern s32 D_800A7780[];
extern s32 D_800A778C[];
extern s32 D_800A7798[];
extern s32 D_800A77A4[];
extern s32 D_800A77B0[];
extern s32 D_800A77BC[];
extern s32 D_800A77C8[];
extern s32 D_800A77D4[];
extern s32 D_800A77E0[];
extern s32 D_800A77EC[];
extern s32 D_800A7800[];
extern s32 D_800A7814[];
extern s32 D_800A7828[];
extern s32 D_800A783C[];
extern s32 D_800A7850[];
extern s32 D_800A7864[];
extern s32 D_800A7878[];
extern s32 D_800A788C[];
extern s32 D_800A78A0[];
extern s32 D_800A78B4[];
extern s32 D_800A78C8[];
extern s32 D_800A78DC[];
extern s32 D_800A78F0[];
extern s32 D_800A7904[];
extern s32 D_800A7918[];
extern s32 D_800A792C[];
extern s32 D_800A7940[];
extern s32 D_800A7954[];
extern s32 D_800A7968[];
extern s32 D_800A797C[];

StagePoint D_800A4F94 = { 0x2ED, 1, 2, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A4FA4 = { 0x229, 0, 0, 0x1F0, 0x360, 0, &D_800A4F94 };
StagePoints D_800A4FB4 = { 1, 1, &D_800A4FA4 };
StagePoint D_800A4FBC = { 0x2EE, 1, 1, 224, 0x240, 5, NULL };
StagePoint D_800A4FCC = { 0x23C, 0, 0, 0x410, 0x2F8, 0, &D_800A4FBC };
StagePoints D_800A4FDC = { 1, 2, &D_800A4FCC };
StagePoint D_800A4FE4 = { 0x2ED, 2, 1, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A4FF4 = { 0x22A, 0, 0, 0x440, 0x2F8, 0, &D_800A4FE4 };
StagePoints D_800A5004 = { 2, 1, &D_800A4FF4 };
StagePoint D_800A500C = { 0x2ED, 2, 2, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A501C = { 0x220, 0, 0, 0x450, 0x226, 0, &D_800A500C };
StagePoints D_800A502C = { 2, 2, &D_800A501C };
StagePoint D_800A5034 = { 0x2EE, 2, 2, 224, 0x240, 5, NULL };
StagePoint D_800A5044 = { 0x24A, 0, 0, 0x2B0, 0x100, 0, &D_800A5034 };
StagePoints D_800A5054 = { 2, 3, &D_800A5044 };
StagePoint D_800A505C = { 0x2EC, 3, 2, 240, 0x1D8, 5, NULL };
StagePoint D_800A506C = { 0x247, 0, 0, 0x3D0, 0x100, 0, &D_800A505C };
StagePoints D_800A507C = { 3, 1, &D_800A506C };
StagePoint D_800A5084 = { 0x2EE, 3, 3, 224, 0x240, 5, NULL };
StagePoint D_800A5094 = { 0x23A, 0, 0, 0x560, 0x188, 0, &D_800A5084 };
StagePoints D_800A50A4 = { 3, 2, &D_800A5094 };
StagePoint D_800A50AC = { 0x2EE, 3, 4, 224, 0x240, 5, NULL };
StagePoint D_800A50BC = { 0x299, 0, 0, 0x2D0, 0x590, 0, &D_800A50AC };
StagePoints D_800A50CC = { 3, 3, &D_800A50BC };
StagePoint D_800A50D4 = { 0x2EE, 3, 5, 224, 0x240, 5, NULL };
StagePoint D_800A50E4 = { 0x22A, 0, 0, 0x2D0, 0x590, 0, &D_800A50D4 };
StagePoints D_800A50F4 = { 3, 4, &D_800A50E4 };
StagePoint D_800A50FC = { 0x2ED, 4, 1, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A510C = { 0x24A, 0, 0, 0x5F0, 0x190, 0, &D_800A50FC };
StagePoints D_800A511C = { 4, 1, &D_800A510C };
StagePoint D_800A5124 = { 0x2ED, 4, 2, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A5134 = { 0x2B4, 0, 0, 0x5F0, 0x190, 0, &D_800A5124 };
StagePoints D_800A5144 = { 4, 2, &D_800A5134 };
StagePoint D_800A514C = { 0x2ED, 5, 2, 224, 192, 5, NULL };
StagePoint D_800A515C = { 0x265, 0, 0, 0x4C0, 200, 0, &D_800A514C };
StagePoints D_800A516C = { 5, 1, &D_800A515C };
StagePoint D_800A5174 = { 0x2EE, 5, 3, 224, 0x240, 5, NULL };
StagePoint D_800A5184 = { 0x261, 0, 0, 0x4B0, 0x13E, 0, &D_800A5174 };
StagePoints D_800A5194 = { 5, 2, &D_800A5184 };
StagePoint D_800A519C = { 0x2EE, 5, 4, 224, 0x240, 5, NULL };
StagePoint D_800A51AC = { 0x264, 0, 0, 192, 0x214, 0, &D_800A519C };
StagePoints D_800A51BC = { 5, 3, &D_800A51AC };
StagePoint D_800A51C4 = { 0x2EC, 5, 1, 240, 0x1D8, 5, NULL };
StagePoint D_800A51D4 = { 0x229, 0, 0, 0x560, 0x238, 0, &D_800A51C4 };
StagePoints D_800A51E4 = { 5, 4, &D_800A51D4 };
StagePoint D_800A51EC = { 0x2EE, 6, 1, 224, 0x240, 5, NULL };
StagePoint D_800A51FC = { 0x2B1, 0, 0, 0x190, 0x1C0, 0, &D_800A51EC };
StagePoints D_800A520C = { 6, 1, &D_800A51FC };
StagePoint D_800A5214 = { 0x2EE, 6, 3, 224, 0x240, 5, NULL };
StagePoint D_800A5224 = { 0x265, 0, 0, 0x1C0, 0x206, 0, &D_800A5214 };
StagePoints D_800A5234 = { 6, 2, &D_800A5224 };
StagePoint D_800A523C = { 0x2ED, 8, 1, 224, 192, 5, NULL };
StagePoint D_800A524C = { 0x24A, 0, 0, 0x3F0, 0x330, 0, &D_800A523C };
StagePoints D_800A525C = { 8, 1, &D_800A524C };
StagePoint D_800A5264 = { 0x2EE, 8, 1, 224, 0x240, 5, NULL };
StagePoint D_800A5274 = { 0x2A9, 0, 0, 0x410, 0x2F8, 0, &D_800A5264 };
StagePoints D_800A5284 = { 8, 2, &D_800A5274 };
StagePoint D_800A528C = { 0x2ED, 8, 2, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A529C = { 0x298, 0, 0, 0x1F0, 0x360, 0, &D_800A528C };
StagePoints D_800A52AC = { 8, 3, &D_800A529C };
StagePoint D_800A52B4 = { 0x2ED, 9, 1, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A52C4 = { 0x299, 0, 0, 0x440, 0x2F8, 0, &D_800A52B4 };
StagePoints D_800A52D4 = { 9, 1, &D_800A52C4 };
StagePoint D_800A52DC = { 0x2EE, 9, 2, 224, 0x240, 5, NULL };
StagePoint D_800A52EC = { 0x2B4, 0, 0, 0x2B0, 0x100, 0, &D_800A52DC };
StagePoints D_800A52FC = { 9, 2, &D_800A52EC };
StagePoint D_800A5304 = { 0x2ED, 9, 2, 0x350, 0x1F8, 5, NULL };
StagePoint D_800A5314 = { 0x28F, 0, 0, 0x450, 0x226, 0, &D_800A5304 };
StagePoints D_800A5324 = { 9, 3, &D_800A5314 };
StagePoint D_800A532C = { 0x2EE, 10, 1, 224, 0x240, 5, NULL };
StagePoint D_800A533C = { 0x247, 0, 0, 0x1B0, 0x2F0, 0, &D_800A532C };
StagePoints D_800A534C = { 10, 1, &D_800A533C };
StagePoint D_800A5354 = { 0x2EC, 10, 2, 240, 0x1D8, 5, NULL };
StagePoint D_800A5364 = { 0x24B, 0, 0, 0x2E0, 216, 0, &D_800A5354 };
StagePoints D_800A5374 = { 10, 2, &D_800A5364 };
StagePoint D_800A537C = { 0x2EE, 11, 1, 224, 0x240, 5, NULL };
StagePoint D_800A538C = { 0x2B1, 0, 0, 0x1B0, 0x2F0, 0, &D_800A537C };
StagePoints D_800A539C = { 11, 1, &D_800A538C };
StagePoint D_800A53A4 = { 0x2EC, 11, 2, 240, 0x1D8, 5, NULL };
StagePoint D_800A53B4 = { 0x2B5, 0, 0, 0x2E0, 216, 0, &D_800A53A4 };
StagePoints D_800A53C4 = { 11, 2, &D_800A53B4 };
StagePoint D_800A53CC = { 0x2EC, 12, 5, 240, 0x1D8, 5, NULL };
StagePoint D_800A53DC = { 0x264, 0, 0, 0x2E0, 196, 0, &D_800A53CC };
StagePoints D_800A53EC = { 12, 1, &D_800A53DC };
StagePoint D_800A53F4 = { 0x2EC, 13, 4, 240, 0x1D8, 5, NULL };
StagePoint D_800A5404 = { 0x2CC, 0, 0, 0x2E0, 196, 0, &D_800A53F4 };
StagePoints D_800A5414 = { 13, 1, &D_800A5404 };
StagePoint D_800A541C = { 0x2ED, 14, 2, 224, 192, 5, NULL };
StagePoint D_800A542C = { 0x23A, 0, 0, 0x1C1, 0x37A, 0, &D_800A541C };
StagePoints D_800A543C = { 14, 1, &D_800A542C };
StagePoint D_800A5444 = { 0x2ED, 27, 2, 224, 192, 5, NULL };
StagePoint D_800A5454 = { 0x248, 0, 0, 0x2A0, 0x138, 0, &D_800A5444 };
StagePoints D_800A5464 = { 27, 1, &D_800A5454 };
StagePoint D_800A546C = { 0x2EE, 30, 1, 224, 0x240, 5, NULL };
StagePoint D_800A547C = { 0x24A, 0, 0, 0x2C0, 0x2A8, 0, &D_800A546C };
StagePoints D_800A548C = { 30, 1, &D_800A547C };
StagePoints *D_800A5494[] = {
    &D_800A4FB4, &D_800A4FDC, &D_800A5004, &D_800A502C,
    &D_800A5054, &D_800A507C, &D_800A50A4, &D_800A50CC,
    &D_800A50F4, &D_800A511C, &D_800A5144, &D_800A516C,
    &D_800A5194, &D_800A51BC, &D_800A51E4, &D_800A520C,
    &D_800A5234, &D_800A525C, &D_800A5284, &D_800A52AC,
    &D_800A52D4, &D_800A52FC, &D_800A5324, &D_800A534C,
    &D_800A5374, &D_800A539C, &D_800A53C4, &D_800A53EC,
    &D_800A5414, &D_800A543C, &D_800A5464, &D_800A548C,
    NULL,
};
s32 D_800A5518[] = {
    174, 10, 0x60080000,
};
s32 D_800A5524[] = {
    174, 10, 0x60080000,
};
s32 D_800A5530[] = {
    170, 10, 0x60080000,
};
s32 D_800A553C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5548[] = {
    170, 10, 0x60080000,
};
s32 D_800A5554[] = {
    170, 10, 0x60080000,
};
s32 D_800A5560[] = {
    170, 10, 0x60080000,
};
s32 D_800A556C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5578[] = {
    1, (s32)D_800A5518, (s32)D_800A5524, (s32)D_800A5530,
    (s32)D_800A553C, (s32)D_800A5548, (s32)D_800A5554, (s32)D_800A5560,
    (s32)D_800A556C,
};
s32 D_800A559C[] = {
    0, 0, 0x60040000,
};
s32 D_800A55A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A55B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A55C0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A559C, (s32)D_800A55A8, (s32)D_800A55B4,
    (s32)D_800A55C0, (s32)D_800A55CC, (s32)D_800A55D8, (s32)D_800A55E4,
    (s32)D_800A55F0,
};
s32 D_800A5620[] = {
    0, 0, 0x60040000,
};
s32 D_800A562C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5638[] = {
    0, 0, 0x60040000,
};
s32 D_800A5644[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5620, (s32)D_800A562C, (s32)D_800A5638,
    (s32)D_800A5644, (s32)D_800A5650, (s32)D_800A565C, (s32)D_800A5668,
    (s32)D_800A5674,
};
s32 D_800A56A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A56B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A56BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A56C8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A56A4, (s32)D_800A56B0, (s32)D_800A56BC,
    (s32)D_800A56C8, (s32)D_800A56D4, (s32)D_800A56E0, (s32)D_800A56EC,
    (s32)D_800A56F8,
};
s32 D_800A5728[] = {
    174, 10, 0x60080000,
};
s32 D_800A5734[] = {
    174, 10, 0x60080000,
};
s32 D_800A5740[] = {
    170, 10, 0x60080000,
};
s32 D_800A574C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5758[] = {
    170, 10, 0x60080000,
};
s32 D_800A5764[] = {
    110, 10, 0x60080000,
};
s32 D_800A5770[] = {
    110, 10, 0x60080000,
};
s32 D_800A577C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5788[] = {
    1, (s32)D_800A5728, (s32)D_800A5734, (s32)D_800A5740,
    (s32)D_800A574C, (s32)D_800A5758, (s32)D_800A5764, (s32)D_800A5770,
    (s32)D_800A577C,
};
s32 D_800A57AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A57B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A57C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A57D0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A57AC, (s32)D_800A57B8, (s32)D_800A57C4,
    (s32)D_800A57D0, (s32)D_800A57DC, (s32)D_800A57E8, (s32)D_800A57F4,
    (s32)D_800A5800,
};
s32 D_800A5830[] = {
    0, 0, 0x60040000,
};
s32 D_800A583C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5848[] = {
    0, 0, 0x60040000,
};
s32 D_800A5854[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5830, (s32)D_800A583C, (s32)D_800A5848,
    (s32)D_800A5854, (s32)D_800A5860, (s32)D_800A586C, (s32)D_800A5878,
    (s32)D_800A5884,
};
s32 D_800A58B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A58C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A58CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A58D8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A58B4, (s32)D_800A58C0, (s32)D_800A58CC,
    (s32)D_800A58D8, (s32)D_800A58E4, (s32)D_800A58F0, (s32)D_800A58FC,
    (s32)D_800A5908,
};
s32 D_800A5938[] = {
    174, 10, 0x60080000,
};
s32 D_800A5944[] = {
    174, 10, 0x60080000,
};
s32 D_800A5950[] = {
    170, 10, 0x60080000,
};
s32 D_800A595C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5968[] = {
    182, 10, 0x60080000,
};
s32 D_800A5974[] = {
    182, 10, 0x60080000,
};
s32 D_800A5980[] = {
    71, 10, 0x60080000,
};
s32 D_800A598C[] = {
    71, 10, 0x60080000,
};
s32 D_800A5998[] = {
    1, (s32)D_800A5938, (s32)D_800A5944, (s32)D_800A5950,
    (s32)D_800A595C, (s32)D_800A5968, (s32)D_800A5974, (s32)D_800A5980,
    (s32)D_800A598C,
};
s32 D_800A59BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A59C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A59E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A59EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A59F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A04[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A10[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A1C[] = {
    0, (s32)D_800A59BC, (s32)D_800A59C8, (s32)D_800A59D4,
    (s32)D_800A59E0, (s32)D_800A59EC, (s32)D_800A59F8, (s32)D_800A5A04,
    (s32)D_800A5A10,
};
s32 D_800A5A40[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A58[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A64[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A70[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5AA0[] = {
    0, (s32)D_800A5A40, (s32)D_800A5A4C, (s32)D_800A5A58,
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
    174, 10, 0x60080000,
};
s32 D_800A5B54[] = {
    174, 10, 0x60080000,
};
s32 D_800A5B60[] = {
    170, 10, 0x60080000,
};
s32 D_800A5B6C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5B78[] = {
    182, 10, 0x60080000,
};
s32 D_800A5B84[] = {
    182, 10, 0x60080000,
};
s32 D_800A5B90[] = {
    71, 10, 0x60080000,
};
s32 D_800A5B9C[] = {
    71, 10, 0x60080000,
};
s32 D_800A5BA8[] = {
    1, (s32)D_800A5B48, (s32)D_800A5B54, (s32)D_800A5B60,
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
    0, 0, 0x60040000,
};
s32 D_800A5C5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C68[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C74[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C80[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C8C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C98[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CB0[] = {
    0, (s32)D_800A5C50, (s32)D_800A5C5C, (s32)D_800A5C68,
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
    174, 10, 0x60080000,
};
s32 D_800A5D64[] = {
    170, 10, 0x60080000,
};
s32 D_800A5D70[] = {
    110, 10, 0x60080000,
};
s32 D_800A5D7C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5D88[] = {
    182, 10, 0x60080000,
};
s32 D_800A5D94[] = {
    182, 10, 0x60080000,
};
s32 D_800A5DA0[] = {
    71, 10, 0x60080000,
};
s32 D_800A5DAC[] = {
    71, 10, 0x60080000,
};
s32 D_800A5DB8[] = {
    1, (s32)D_800A5D58, (s32)D_800A5D64, (s32)D_800A5D70,
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
    0, 0, 0x60040000,
};
s32 D_800A5E6C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E78[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5EC0[] = {
    0, (s32)D_800A5E60, (s32)D_800A5E6C, (s32)D_800A5E78,
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
    174, 10, 0x60080000,
};
s32 D_800A5F74[] = {
    170, 10, 0x60080000,
};
s32 D_800A5F80[] = {
    110, 10, 0x60080000,
};
s32 D_800A5F8C[] = {
    110, 10, 0x60080000,
};
s32 D_800A5F98[] = {
    182, 10, 0x60080000,
};
s32 D_800A5FA4[] = {
    182, 10, 0x60080000,
};
s32 D_800A5FB0[] = {
    71, 10, 0x60080000,
};
s32 D_800A5FBC[] = {
    71, 10, 0x60080000,
};
s32 D_800A5FC8[] = {
    1, (s32)D_800A5F68, (s32)D_800A5F74, (s32)D_800A5F80,
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
    0, 0, 0x60040000,
};
s32 D_800A607C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6088[] = {
    0, 0, 0x60040000,
};
s32 D_800A6094[] = {
    0, 0, 0x60040000,
};
s32 D_800A60A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A60AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A60B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A60C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A60D0[] = {
    0, (s32)D_800A6070, (s32)D_800A607C, (s32)D_800A6088,
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
    182, 10, 0x60080000,
};
s32 D_800A6184[] = {
    182, 10, 0x60080000,
};
s32 D_800A6190[] = {
    182, 10, 0x60080000,
};
s32 D_800A619C[] = {
    182, 10, 0x60080000,
};
s32 D_800A61A8[] = {
    71, 10, 0x60080000,
};
s32 D_800A61B4[] = {
    71, 10, 0x60080000,
};
s32 D_800A61C0[] = {
    71, 10, 0x60080000,
};
s32 D_800A61CC[] = {
    71, 10, 0x60080000,
};
s32 D_800A61D8[] = {
    1, (s32)D_800A6178, (s32)D_800A6184, (s32)D_800A6190,
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
    0, 0, 0x60040000,
};
s32 D_800A628C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6298[] = {
    0, 0, 0x60040000,
};
s32 D_800A62A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A62B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A62C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A62E0[] = {
    0, (s32)D_800A6280, (s32)D_800A628C, (s32)D_800A6298,
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
    182, 10, 0x60080000,
};
s32 D_800A6394[] = {
    182, 10, 0x60080000,
};
s32 D_800A63A0[] = {
    182, 10, 0x60080000,
};
s32 D_800A63AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A63B8[] = {
    71, 10, 0x60080000,
};
s32 D_800A63C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A63D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A63DC[] = {
    71, 10, 0x60080000,
};
s32 D_800A63E8[] = {
    1, (s32)D_800A6388, (s32)D_800A6394, (s32)D_800A63A0,
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
    0, 0, 0x60040000,
};
s32 D_800A649C[] = {
    0, 0, 0x60040000,
};
s32 D_800A64A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64F0[] = {
    0, (s32)D_800A6490, (s32)D_800A649C, (s32)D_800A64A8,
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
    174, 10, 0x60080000,
};
s32 D_800A65A4[] = {
    174, 10, 0x60080000,
};
s32 D_800A65B0[] = {
    170, 10, 0x60080000,
};
s32 D_800A65BC[] = {
    170, 10, 0x60080000,
};
s32 D_800A65C8[] = {
    170, 10, 0x60080000,
};
s32 D_800A65D4[] = {
    110, 10, 0x60080000,
};
s32 D_800A65E0[] = {
    110, 10, 0x60080000,
};
s32 D_800A65EC[] = {
    110, 10, 0x60080000,
};
s32 D_800A65F8[] = {
    2, (s32)D_800A6598, (s32)D_800A65A4, (s32)D_800A65B0,
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
    0, 0, 0x60040000,
};
s32 D_800A66AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A66D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A66F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6700[] = {
    0, (s32)D_800A66A0, (s32)D_800A66AC, (s32)D_800A66B8,
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
    182, 10, 0x60080000,
};
s32 D_800A67B4[] = {
    182, 10, 0x60080000,
};
s32 D_800A67C0[] = {
    182, 10, 0x60080000,
};
s32 D_800A67CC[] = {
    182, 10, 0x60080000,
};
s32 D_800A67D8[] = {
    71, 10, 0x60080000,
};
s32 D_800A67E4[] = {
    71, 10, 0x60080000,
};
s32 D_800A67F0[] = {
    71, 10, 0x60080000,
};
s32 D_800A67FC[] = {
    71, 10, 0x60080000,
};
s32 D_800A6808[] = {
    2, (s32)D_800A67A8, (s32)D_800A67B4, (s32)D_800A67C0,
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
    0, 0, 0x60040000,
};
s32 D_800A6910[] = {
    0, (s32)D_800A68B0, (s32)D_800A68BC, (s32)D_800A68C8,
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
    110, 10, 0x60080000,
};
s32 D_800A69C4[] = {
    110, 10, 0x60080000,
};
s32 D_800A69D0[] = {
    110, 10, 0x60080000,
};
s32 D_800A69DC[] = {
    110, 10, 0x60080000,
};
s32 D_800A69E8[] = {
    110, 10, 0x60080000,
};
s32 D_800A69F4[] = {
    110, 10, 0x60080000,
};
s32 D_800A6A00[] = {
    110, 10, 0x60080000,
};
s32 D_800A6A0C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6A18[] = {
    1, (s32)D_800A69B8, (s32)D_800A69C4, (s32)D_800A69D0,
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
    0, 0, 0x60040000,
};
s32 D_800A6B20[] = {
    0, (s32)D_800A6AC0, (s32)D_800A6ACC, (s32)D_800A6AD8,
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
    182, 10, 0x60080000,
};
s32 D_800A6BD4[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BE0[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BEC[] = {
    182, 10, 0x60080000,
};
s32 D_800A6BF8[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C04[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C10[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C1C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6C28[] = {
    1, (s32)D_800A6BC8, (s32)D_800A6BD4, (s32)D_800A6BE0,
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
    0, 0, 0x60040000,
};
s32 D_800A6D30[] = {
    0, (s32)D_800A6CD0, (s32)D_800A6CDC, (s32)D_800A6CE8,
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
    174, 10, 0x60080000,
};
s32 D_800A6DE4[] = {
    174, 10, 0x60080000,
};
s32 D_800A6DF0[] = {
    170, 10, 0x60080000,
};
s32 D_800A6DFC[] = {
    170, 10, 0x60080000,
};
s32 D_800A6E08[] = {
    170, 10, 0x60080000,
};
s32 D_800A6E14[] = {
    170, 10, 0x60080000,
};
s32 D_800A6E20[] = {
    170, 10, 0x60080000,
};
s32 D_800A6E2C[] = {
    170, 10, 0x60080000,
};
s32 D_800A6E38[] = {
    4, (s32)D_800A6DD8, (s32)D_800A6DE4, (s32)D_800A6DF0,
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
    0, 0, 0x60040000,
};
s32 D_800A6EEC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6EF8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F04[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F10[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F34[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F40[] = {
    0, (s32)D_800A6EE0, (s32)D_800A6EEC, (s32)D_800A6EF8,
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
    174, 10, 0x60080000,
};
s32 D_800A6FF4[] = {
    174, 10, 0x60080000,
};
s32 D_800A7000[] = {
    170, 10, 0x60080000,
};
s32 D_800A700C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7018[] = {
    170, 10, 0x60080000,
};
s32 D_800A7024[] = {
    170, 10, 0x60080000,
};
s32 D_800A7030[] = {
    170, 10, 0x60080000,
};
s32 D_800A703C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7048[] = {
    2, (s32)D_800A6FE8, (s32)D_800A6FF4, (s32)D_800A7000,
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
    0, 0, 0x60040000,
};
s32 D_800A70FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7108[] = {
    0, 0, 0x60040000,
};
s32 D_800A7114[] = {
    0, 0, 0x60040000,
};
s32 D_800A7120[] = {
    0, 0, 0x60040000,
};
s32 D_800A712C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7138[] = {
    0, 0, 0x60040000,
};
s32 D_800A7144[] = {
    0, 0, 0x60040000,
};
s32 D_800A7150[] = {
    0, (s32)D_800A70F0, (s32)D_800A70FC, (s32)D_800A7108,
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
    174, 10, 0x60080000,
};
s32 D_800A7204[] = {
    174, 10, 0x60080000,
};
s32 D_800A7210[] = {
    170, 10, 0x60080000,
};
s32 D_800A721C[] = {
    170, 10, 0x60080000,
};
s32 D_800A7228[] = {
    182, 10, 0x60080000,
};
s32 D_800A7234[] = {
    182, 10, 0x60080000,
};
s32 D_800A7240[] = {
    71, 10, 0x60080000,
};
s32 D_800A724C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7258[] = {
    1, (s32)D_800A71F8, (s32)D_800A7204, (s32)D_800A7210,
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
    0, 0, 0x60040000,
};
s32 D_800A730C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7318[] = {
    0, 0, 0x60040000,
};
s32 D_800A7324[] = {
    0, 0, 0x60040000,
};
s32 D_800A7330[] = {
    0, 0, 0x60040000,
};
s32 D_800A733C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7348[] = {
    0, 0, 0x60040000,
};
s32 D_800A7354[] = {
    0, 0, 0x60040000,
};
s32 D_800A7360[] = {
    0, (s32)D_800A7300, (s32)D_800A730C, (s32)D_800A7318,
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
    234, 1, 0, (s32)D_800A5578,
    (s32)D_800A55FC, (s32)D_800A5680, (s32)D_800A5704, 240,
    2, 0, (s32)D_800A5788, (s32)D_800A580C,
    (s32)D_800A5890, (s32)D_800A5914, 245, 3,
    0, (s32)D_800A5998, (s32)D_800A5A1C, (s32)D_800A5AA0,
    (s32)D_800A5B24, 250, 4, 0,
    (s32)D_800A5BA8, (s32)D_800A5C2C, (s32)D_800A5CB0, (s32)D_800A5D34,
    256, 5, 0, (s32)D_800A5DB8,
    (s32)D_800A5E3C, (s32)D_800A5EC0, (s32)D_800A5F44, 263,
    6, 0, (s32)D_800A5FC8, (s32)D_800A604C,
    (s32)D_800A60D0, (s32)D_800A6154, 271, 8,
    0, (s32)D_800A61D8, (s32)D_800A625C, (s32)D_800A62E0,
    (s32)D_800A6364, 278, 9, 0,
    (s32)D_800A63E8, (s32)D_800A646C, (s32)D_800A64F0, (s32)D_800A6574,
    283, 10, 0, (s32)D_800A65F8,
    (s32)D_800A667C, (s32)D_800A6700, (s32)D_800A6784, 288,
    11, 0, (s32)D_800A6808, (s32)D_800A688C,
    (s32)D_800A6910, (s32)D_800A6994, 294, 12,
    0, (s32)D_800A6A18, (s32)D_800A6A9C, (s32)D_800A6B20,
    (s32)D_800A6BA4, 300, 13, 0,
    (s32)D_800A6C28, (s32)D_800A6CAC, (s32)D_800A6D30, (s32)D_800A6DB4,
    304, 14, 0, (s32)D_800A6E38,
    (s32)D_800A6EBC, (s32)D_800A6F40, (s32)D_800A6FC4, 355,
    27, 0, (s32)D_800A7048, (s32)D_800A70CC,
    (s32)D_800A7150, (s32)D_800A71D4, 374, 30,
    0, (s32)D_800A7258, (s32)D_800A72DC, (s32)D_800A7360,
    (s32)D_800A73E4,
};
s32 D_800A75AC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000174, 208, 0x1FF0150,
    0x1000140, 0x1200174, 0x2000D0, 0x1FF0160,
    0x1000140, 0x1400160, 0x400080, 0x1FF0170,
    0x1000140, 0x140014C, 0x400030, 0x1FE0150,
    0x1000140, 0x100014C, 48, 0x1FE0160,
    0x1000140, 0x1000160, 128, 0x1FE0170,
};
s32 D_800A766C[] = {
    0, 0, 938, 0,
    0, 0,
};
s32 D_800A7684[] = {
    0, 0, 940, 0,
    0, 0,
};
s32 D_800A769C[] = {
    0, 0, 943, 0,
    0, 0,
};
s32 D_800A76B4[] = {
    0, 0, 939, 0,
    0, 0,
};
s32 D_800A76CC[] = {
    0, 0, 941, 0,
    0, 0,
};
s32 D_800A76E4[] = {
    0, 0, 942, 0,
    0, 0,
};
s32 D_800A76FC[] = {
    0x17E00, 0x17E1F, 65535,
};
s32 D_800A7708[] = {
    0x17E01, 0x17E20, 65535,
};
s32 D_800A7714[] = {
    0x17E08, 0x17E20, 65535,
};
s32 D_800A7720[] = {
    0x17E01, 0x17E1F, 65535,
};
s32 D_800A772C[] = {
    0x17E02, 0x17E1F, 65535,
};
s32 D_800A7738[] = {
    0x17E07, 0x17E1F, 65535,
};
s32 D_800A7744[] = {
    0x17E1F, 8, 65535,
};
s32 D_800A7750[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A775C[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A7768[] = {
    0x17E20, 9, 65535,
};
s32 D_800A7774[] = {
    0x17E01, 10, 65535,
};
s32 D_800A7780[] = {
    0x17E02, 10, 65535,
};
s32 D_800A778C[] = {
    0x17E04, 10, 65535,
};
s32 D_800A7798[] = {
    0x17E05, 10, 65535,
};
s32 D_800A77A4[] = {
    0x17E07, 10, 65535,
};
s32 D_800A77B0[] = {
    0x17E08, 10, 65535,
};
s32 D_800A77BC[] = {
    0x17E0A, 10, 65535,
};
s32 D_800A77C8[] = {
    0x17E0C, 10, 65535,
};
s32 D_800A77D4[] = {
    0x17E1A, 10, 65535,
};
s32 D_800A77E0[] = {
    0x17E1D, 10, 65535,
};
s32 D_800A77EC[] = {
    (s32)D_800A76FC, (s32)D_800A766C, 0x40042, 0x1100068,
    7,
};
s32 D_800A7800[] = {
    (s32)D_800A7708, (s32)D_800A7684, 0x40042, 0x1100068,
    7,
};
s32 D_800A7814[] = {
    (s32)D_800A7714, (s32)D_800A769C, 0x40042, 0x1100068,
    7,
};
s32 D_800A7828[] = {
    (s32)D_800A7720, (s32)D_800A76B4, 0x500B6, 0x1100068,
    7,
};
s32 D_800A783C[] = {
    (s32)D_800A772C, (s32)D_800A76CC, 0x500B6, 0x1100068,
    7,
};
s32 D_800A7850[] = {
    (s32)D_800A7738, (s32)D_800A76E4, 0x500B6, 0x1100068,
    7,
};
s32 D_800A7864[] = {
    0, 0, 0x60146, 0,
    0,
};
s32 D_800A7878[] = {
    (s32)D_800A7744, 0, 0x70148, 0x1880170,
    1,
};
s32 D_800A788C[] = {
    (s32)D_800A7750, 0, 0x8015F, 0x13801B0,
    1,
};
s32 D_800A78A0[] = {
    (s32)D_800A775C, 0, 0x8015F, 0x1580110,
    1,
};
s32 D_800A78B4[] = {
    (s32)D_800A7768, 0, 0x8015F, 0x1540178,
    1,
};
s32 D_800A78C8[] = {
    (s32)D_800A7774, 0, 0x90160, 0x1080210,
    1,
};
s32 D_800A78DC[] = {
    (s32)D_800A7780, 0, 0x90160, 0x12001E0,
    1,
};
s32 D_800A78F0[] = {
    (s32)D_800A778C, 0, 0x90160, 0x17001A0,
    1,
};
s32 D_800A7904[] = {
    (s32)D_800A7798, 0, 0x90160, 0x1080210,
    1,
};
s32 D_800A7918[] = {
    (s32)D_800A77A4, 0, 0x90160, 0x16C0138,
    1,
};
s32 D_800A792C[] = {
    (s32)D_800A77B0, 0, 0x90160, 0x14000E0,
    1,
};
s32 D_800A7940[] = {
    (s32)D_800A77BC, 0, 0x90160, 0x16C0138,
    1,
};
s32 D_800A7954[] = {
    (s32)D_800A77C8, 0, 0x90160, 0x1540178,
    1,
};
s32 D_800A7968[] = {
    (s32)D_800A77D4, 0, 0x90160, 0x1080210,
    1,
};
s32 D_800A797C[] = {
    (s32)D_800A77E0, 0, 0x90160, 0x14000E0,
    1,
};
s32 D_800A7990[] = {
    (s32)D_800A77EC, (s32)D_800A7800, (s32)D_800A7814, (s32)D_800A7828,
    (s32)D_800A783C, (s32)D_800A7850, (s32)D_800A7864, (s32)D_800A7878,
    (s32)D_800A788C, (s32)D_800A78A0, (s32)D_800A78B4, (s32)D_800A78C8,
    (s32)D_800A78DC, (s32)D_800A78F0, (s32)D_800A7904, (s32)D_800A7918,
    (s32)D_800A792C, (s32)D_800A7940, (s32)D_800A7954, (s32)D_800A7968,
    (s32)D_800A797C, 0,
};
s32 D_800A79E8[] = {
    0x4FF0001, 0x7000232, 0x980014, 0xFD008C,
    0, 0, 0, 0,
    0,
};
s32 D_800A7A0C[] = {
    65535, 65535, 0x2E90001, 0xF800B0,
    4, 0, 65535, 65535,
    0x2E90001, 0xF00240, 5, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A7A54[])(void) = {
    func_800A4E74,
};
