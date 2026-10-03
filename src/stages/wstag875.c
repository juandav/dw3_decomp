#include "common.h"
#include "stage.h"
extern void (*D_800A802C[])(void);
void func_800A4DA4();
extern StagePoints *D_800A51E4[];

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
        func_800A4CA4(D_800990B4.unk14, D_800A51E4, GAME.unk44, GAME.unk46);
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
    D_800A802C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag875", func_800A4E74);

void func_800A4E74();
extern StagePoint D_800A4F8C;
extern StagePoint D_800A4FA4;
extern StagePoint D_800A4FBC;
extern StagePoint D_800A4FD4;
extern StagePoint D_800A4FEC;
extern StagePoint D_800A5004;
extern StagePoint D_800A501C;
extern StagePoint D_800A5034;
extern StagePoint D_800A504C;
extern StagePoint D_800A5064;
extern StagePoint D_800A507C;
extern StagePoint D_800A5094;
extern StagePoint D_800A50AC;
extern StagePoint D_800A50C4;
extern StagePoint D_800A50DC;
extern StagePoint D_800A50F4;
extern StagePoint D_800A510C;
extern StagePoint D_800A5124;
extern StagePoint D_800A513C;
extern StagePoint D_800A5154;
extern StagePoint D_800A516C;
extern StagePoint D_800A5184;
extern StagePoint D_800A519C;
extern StagePoint D_800A51B4;
extern StagePoint D_800A51CC;
extern StagePoints D_800A4F9C;
extern StagePoints D_800A4FB4;
extern StagePoints D_800A4FCC;
extern StagePoints D_800A4FE4;
extern StagePoints D_800A4FFC;
extern StagePoints D_800A5014;
extern StagePoints D_800A502C;
extern StagePoints D_800A5044;
extern StagePoints D_800A505C;
extern StagePoints D_800A5074;
extern StagePoints D_800A508C;
extern StagePoints D_800A50A4;
extern StagePoints D_800A50BC;
extern StagePoints D_800A50D4;
extern StagePoints D_800A50EC;
extern StagePoints D_800A5104;
extern StagePoints D_800A511C;
extern StagePoints D_800A5134;
extern StagePoints D_800A514C;
extern StagePoints D_800A5164;
extern StagePoints D_800A517C;
extern StagePoints D_800A5194;
extern StagePoints D_800A51AC;
extern StagePoints D_800A51C4;
extern StagePoints D_800A51DC;
extern s32 D_800A524C[];
extern s32 D_800A5258[];
extern s32 D_800A5264[];
extern s32 D_800A5270[];
extern s32 D_800A527C[];
extern s32 D_800A5288[];
extern s32 D_800A5294[];
extern s32 D_800A52A0[];
extern s32 D_800A52D0[];
extern s32 D_800A52DC[];
extern s32 D_800A52E8[];
extern s32 D_800A52F4[];
extern s32 D_800A5300[];
extern s32 D_800A530C[];
extern s32 D_800A5318[];
extern s32 D_800A5324[];
extern s32 D_800A5354[];
extern s32 D_800A5360[];
extern s32 D_800A536C[];
extern s32 D_800A5378[];
extern s32 D_800A5384[];
extern s32 D_800A5390[];
extern s32 D_800A539C[];
extern s32 D_800A53A8[];
extern s32 D_800A53D8[];
extern s32 D_800A53E4[];
extern s32 D_800A53F0[];
extern s32 D_800A53FC[];
extern s32 D_800A5408[];
extern s32 D_800A5414[];
extern s32 D_800A5420[];
extern s32 D_800A542C[];
extern s32 D_800A545C[];
extern s32 D_800A5468[];
extern s32 D_800A5474[];
extern s32 D_800A5480[];
extern s32 D_800A548C[];
extern s32 D_800A5498[];
extern s32 D_800A54A4[];
extern s32 D_800A54B0[];
extern s32 D_800A54E0[];
extern s32 D_800A54EC[];
extern s32 D_800A54F8[];
extern s32 D_800A5504[];
extern s32 D_800A5510[];
extern s32 D_800A551C[];
extern s32 D_800A5528[];
extern s32 D_800A5534[];
extern s32 D_800A5564[];
extern s32 D_800A5570[];
extern s32 D_800A557C[];
extern s32 D_800A5588[];
extern s32 D_800A5594[];
extern s32 D_800A55A0[];
extern s32 D_800A55AC[];
extern s32 D_800A55B8[];
extern s32 D_800A55E8[];
extern s32 D_800A55F4[];
extern s32 D_800A5600[];
extern s32 D_800A560C[];
extern s32 D_800A5618[];
extern s32 D_800A5624[];
extern s32 D_800A5630[];
extern s32 D_800A563C[];
extern s32 D_800A566C[];
extern s32 D_800A5678[];
extern s32 D_800A5684[];
extern s32 D_800A5690[];
extern s32 D_800A569C[];
extern s32 D_800A56A8[];
extern s32 D_800A56B4[];
extern s32 D_800A56C0[];
extern s32 D_800A56F0[];
extern s32 D_800A56FC[];
extern s32 D_800A5708[];
extern s32 D_800A5714[];
extern s32 D_800A5720[];
extern s32 D_800A572C[];
extern s32 D_800A5738[];
extern s32 D_800A5744[];
extern s32 D_800A5774[];
extern s32 D_800A5780[];
extern s32 D_800A578C[];
extern s32 D_800A5798[];
extern s32 D_800A57A4[];
extern s32 D_800A57B0[];
extern s32 D_800A57BC[];
extern s32 D_800A57C8[];
extern s32 D_800A57F8[];
extern s32 D_800A5804[];
extern s32 D_800A5810[];
extern s32 D_800A581C[];
extern s32 D_800A5828[];
extern s32 D_800A5834[];
extern s32 D_800A5840[];
extern s32 D_800A584C[];
extern s32 D_800A587C[];
extern s32 D_800A5888[];
extern s32 D_800A5894[];
extern s32 D_800A58A0[];
extern s32 D_800A58AC[];
extern s32 D_800A58B8[];
extern s32 D_800A58C4[];
extern s32 D_800A58D0[];
extern s32 D_800A5900[];
extern s32 D_800A590C[];
extern s32 D_800A5918[];
extern s32 D_800A5924[];
extern s32 D_800A5930[];
extern s32 D_800A593C[];
extern s32 D_800A5948[];
extern s32 D_800A5954[];
extern s32 D_800A5984[];
extern s32 D_800A5990[];
extern s32 D_800A599C[];
extern s32 D_800A59A8[];
extern s32 D_800A59B4[];
extern s32 D_800A59C0[];
extern s32 D_800A59CC[];
extern s32 D_800A59D8[];
extern s32 D_800A5A08[];
extern s32 D_800A5A14[];
extern s32 D_800A5A20[];
extern s32 D_800A5A2C[];
extern s32 D_800A5A38[];
extern s32 D_800A5A44[];
extern s32 D_800A5A50[];
extern s32 D_800A5A5C[];
extern s32 D_800A5A8C[];
extern s32 D_800A5A98[];
extern s32 D_800A5AA4[];
extern s32 D_800A5AB0[];
extern s32 D_800A5ABC[];
extern s32 D_800A5AC8[];
extern s32 D_800A5AD4[];
extern s32 D_800A5AE0[];
extern s32 D_800A5B10[];
extern s32 D_800A5B1C[];
extern s32 D_800A5B28[];
extern s32 D_800A5B34[];
extern s32 D_800A5B40[];
extern s32 D_800A5B4C[];
extern s32 D_800A5B58[];
extern s32 D_800A5B64[];
extern s32 D_800A5B94[];
extern s32 D_800A5BA0[];
extern s32 D_800A5BAC[];
extern s32 D_800A5BB8[];
extern s32 D_800A5BC4[];
extern s32 D_800A5BD0[];
extern s32 D_800A5BDC[];
extern s32 D_800A5BE8[];
extern s32 D_800A5C18[];
extern s32 D_800A5C24[];
extern s32 D_800A5C30[];
extern s32 D_800A5C3C[];
extern s32 D_800A5C48[];
extern s32 D_800A5C54[];
extern s32 D_800A5C60[];
extern s32 D_800A5C6C[];
extern s32 D_800A5C9C[];
extern s32 D_800A5CA8[];
extern s32 D_800A5CB4[];
extern s32 D_800A5CC0[];
extern s32 D_800A5CCC[];
extern s32 D_800A5CD8[];
extern s32 D_800A5CE4[];
extern s32 D_800A5CF0[];
extern s32 D_800A5D20[];
extern s32 D_800A5D2C[];
extern s32 D_800A5D38[];
extern s32 D_800A5D44[];
extern s32 D_800A5D50[];
extern s32 D_800A5D5C[];
extern s32 D_800A5D68[];
extern s32 D_800A5D74[];
extern s32 D_800A5DA4[];
extern s32 D_800A5DB0[];
extern s32 D_800A5DBC[];
extern s32 D_800A5DC8[];
extern s32 D_800A5DD4[];
extern s32 D_800A5DE0[];
extern s32 D_800A5DEC[];
extern s32 D_800A5DF8[];
extern s32 D_800A5E28[];
extern s32 D_800A5E34[];
extern s32 D_800A5E40[];
extern s32 D_800A5E4C[];
extern s32 D_800A5E58[];
extern s32 D_800A5E64[];
extern s32 D_800A5E70[];
extern s32 D_800A5E7C[];
extern s32 D_800A5EAC[];
extern s32 D_800A5EB8[];
extern s32 D_800A5EC4[];
extern s32 D_800A5ED0[];
extern s32 D_800A5EDC[];
extern s32 D_800A5EE8[];
extern s32 D_800A5EF4[];
extern s32 D_800A5F00[];
extern s32 D_800A5F30[];
extern s32 D_800A5F3C[];
extern s32 D_800A5F48[];
extern s32 D_800A5F54[];
extern s32 D_800A5F60[];
extern s32 D_800A5F6C[];
extern s32 D_800A5F78[];
extern s32 D_800A5F84[];
extern s32 D_800A5FB4[];
extern s32 D_800A5FC0[];
extern s32 D_800A5FCC[];
extern s32 D_800A5FD8[];
extern s32 D_800A5FE4[];
extern s32 D_800A5FF0[];
extern s32 D_800A5FFC[];
extern s32 D_800A6008[];
extern s32 D_800A6038[];
extern s32 D_800A6044[];
extern s32 D_800A6050[];
extern s32 D_800A605C[];
extern s32 D_800A6068[];
extern s32 D_800A6074[];
extern s32 D_800A6080[];
extern s32 D_800A608C[];
extern s32 D_800A60BC[];
extern s32 D_800A60C8[];
extern s32 D_800A60D4[];
extern s32 D_800A60E0[];
extern s32 D_800A60EC[];
extern s32 D_800A60F8[];
extern s32 D_800A6104[];
extern s32 D_800A6110[];
extern s32 D_800A6140[];
extern s32 D_800A614C[];
extern s32 D_800A6158[];
extern s32 D_800A6164[];
extern s32 D_800A6170[];
extern s32 D_800A617C[];
extern s32 D_800A6188[];
extern s32 D_800A6194[];
extern s32 D_800A61C4[];
extern s32 D_800A61D0[];
extern s32 D_800A61DC[];
extern s32 D_800A61E8[];
extern s32 D_800A61F4[];
extern s32 D_800A6200[];
extern s32 D_800A620C[];
extern s32 D_800A6218[];
extern s32 D_800A6248[];
extern s32 D_800A6254[];
extern s32 D_800A6260[];
extern s32 D_800A626C[];
extern s32 D_800A6278[];
extern s32 D_800A6284[];
extern s32 D_800A6290[];
extern s32 D_800A629C[];
extern s32 D_800A62CC[];
extern s32 D_800A62D8[];
extern s32 D_800A62E4[];
extern s32 D_800A62F0[];
extern s32 D_800A62FC[];
extern s32 D_800A6308[];
extern s32 D_800A6314[];
extern s32 D_800A6320[];
extern s32 D_800A6350[];
extern s32 D_800A635C[];
extern s32 D_800A6368[];
extern s32 D_800A6374[];
extern s32 D_800A6380[];
extern s32 D_800A638C[];
extern s32 D_800A6398[];
extern s32 D_800A63A4[];
extern s32 D_800A63D4[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6404[];
extern s32 D_800A6410[];
extern s32 D_800A641C[];
extern s32 D_800A6428[];
extern s32 D_800A6458[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A6488[];
extern s32 D_800A6494[];
extern s32 D_800A64A0[];
extern s32 D_800A64AC[];
extern s32 D_800A64DC[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A650C[];
extern s32 D_800A6518[];
extern s32 D_800A6524[];
extern s32 D_800A6530[];
extern s32 D_800A6560[];
extern s32 D_800A656C[];
extern s32 D_800A6578[];
extern s32 D_800A6584[];
extern s32 D_800A6590[];
extern s32 D_800A659C[];
extern s32 D_800A65A8[];
extern s32 D_800A65B4[];
extern s32 D_800A65E4[];
extern s32 D_800A65F0[];
extern s32 D_800A65FC[];
extern s32 D_800A6608[];
extern s32 D_800A6614[];
extern s32 D_800A6620[];
extern s32 D_800A662C[];
extern s32 D_800A6638[];
extern s32 D_800A6668[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A668C[];
extern s32 D_800A6698[];
extern s32 D_800A66A4[];
extern s32 D_800A66B0[];
extern s32 D_800A66BC[];
extern s32 D_800A66EC[];
extern s32 D_800A66F8[];
extern s32 D_800A6704[];
extern s32 D_800A6710[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A6740[];
extern s32 D_800A6770[];
extern s32 D_800A677C[];
extern s32 D_800A6788[];
extern s32 D_800A6794[];
extern s32 D_800A67A0[];
extern s32 D_800A67AC[];
extern s32 D_800A67B8[];
extern s32 D_800A67C4[];
extern s32 D_800A67F4[];
extern s32 D_800A6800[];
extern s32 D_800A680C[];
extern s32 D_800A6818[];
extern s32 D_800A6824[];
extern s32 D_800A6830[];
extern s32 D_800A683C[];
extern s32 D_800A6848[];
extern s32 D_800A6878[];
extern s32 D_800A6884[];
extern s32 D_800A6890[];
extern s32 D_800A689C[];
extern s32 D_800A68A8[];
extern s32 D_800A68B4[];
extern s32 D_800A68C0[];
extern s32 D_800A68CC[];
extern s32 D_800A68FC[];
extern s32 D_800A6908[];
extern s32 D_800A6914[];
extern s32 D_800A6920[];
extern s32 D_800A692C[];
extern s32 D_800A6938[];
extern s32 D_800A6944[];
extern s32 D_800A6950[];
extern s32 D_800A6980[];
extern s32 D_800A698C[];
extern s32 D_800A6998[];
extern s32 D_800A69A4[];
extern s32 D_800A69B0[];
extern s32 D_800A69BC[];
extern s32 D_800A69C8[];
extern s32 D_800A69D4[];
extern s32 D_800A6A04[];
extern s32 D_800A6A10[];
extern s32 D_800A6A1C[];
extern s32 D_800A6A28[];
extern s32 D_800A6A34[];
extern s32 D_800A6A40[];
extern s32 D_800A6A4C[];
extern s32 D_800A6A58[];
extern s32 D_800A6A88[];
extern s32 D_800A6A94[];
extern s32 D_800A6AA0[];
extern s32 D_800A6AAC[];
extern s32 D_800A6AB8[];
extern s32 D_800A6AC4[];
extern s32 D_800A6AD0[];
extern s32 D_800A6ADC[];
extern s32 D_800A6B0C[];
extern s32 D_800A6B18[];
extern s32 D_800A6B24[];
extern s32 D_800A6B30[];
extern s32 D_800A6B3C[];
extern s32 D_800A6B48[];
extern s32 D_800A6B54[];
extern s32 D_800A6B60[];
extern s32 D_800A6B90[];
extern s32 D_800A6B9C[];
extern s32 D_800A6BA8[];
extern s32 D_800A6BB4[];
extern s32 D_800A6BC0[];
extern s32 D_800A6BCC[];
extern s32 D_800A6BD8[];
extern s32 D_800A6BE4[];
extern s32 D_800A6C14[];
extern s32 D_800A6C20[];
extern s32 D_800A6C2C[];
extern s32 D_800A6C38[];
extern s32 D_800A6C44[];
extern s32 D_800A6C50[];
extern s32 D_800A6C5C[];
extern s32 D_800A6C68[];
extern s32 D_800A6C98[];
extern s32 D_800A6CA4[];
extern s32 D_800A6CB0[];
extern s32 D_800A6CBC[];
extern s32 D_800A6CC8[];
extern s32 D_800A6CD4[];
extern s32 D_800A6CE0[];
extern s32 D_800A6CEC[];
extern s32 D_800A6D1C[];
extern s32 D_800A6D28[];
extern s32 D_800A6D34[];
extern s32 D_800A6D40[];
extern s32 D_800A6D4C[];
extern s32 D_800A6D58[];
extern s32 D_800A6D64[];
extern s32 D_800A6D70[];
extern s32 D_800A6DA0[];
extern s32 D_800A6DAC[];
extern s32 D_800A6DB8[];
extern s32 D_800A6DC4[];
extern s32 D_800A6DD0[];
extern s32 D_800A6DDC[];
extern s32 D_800A6DE8[];
extern s32 D_800A6DF4[];
extern s32 D_800A6E24[];
extern s32 D_800A6E30[];
extern s32 D_800A6E3C[];
extern s32 D_800A6E48[];
extern s32 D_800A6E54[];
extern s32 D_800A6E60[];
extern s32 D_800A6E6C[];
extern s32 D_800A6E78[];
extern s32 D_800A6EA8[];
extern s32 D_800A6EB4[];
extern s32 D_800A6EC0[];
extern s32 D_800A6ECC[];
extern s32 D_800A6ED8[];
extern s32 D_800A6EE4[];
extern s32 D_800A6EF0[];
extern s32 D_800A6EFC[];
extern s32 D_800A6F2C[];
extern s32 D_800A6F38[];
extern s32 D_800A6F44[];
extern s32 D_800A6F50[];
extern s32 D_800A6F5C[];
extern s32 D_800A6F68[];
extern s32 D_800A6F74[];
extern s32 D_800A6F80[];
extern s32 D_800A6FB0[];
extern s32 D_800A6FBC[];
extern s32 D_800A6FC8[];
extern s32 D_800A6FD4[];
extern s32 D_800A6FE0[];
extern s32 D_800A6FEC[];
extern s32 D_800A6FF8[];
extern s32 D_800A7004[];
extern s32 D_800A7034[];
extern s32 D_800A7040[];
extern s32 D_800A704C[];
extern s32 D_800A7058[];
extern s32 D_800A7064[];
extern s32 D_800A7070[];
extern s32 D_800A707C[];
extern s32 D_800A7088[];
extern s32 D_800A70B8[];
extern s32 D_800A70C4[];
extern s32 D_800A70D0[];
extern s32 D_800A70DC[];
extern s32 D_800A70E8[];
extern s32 D_800A70F4[];
extern s32 D_800A7100[];
extern s32 D_800A710C[];
extern s32 D_800A713C[];
extern s32 D_800A7148[];
extern s32 D_800A7154[];
extern s32 D_800A7160[];
extern s32 D_800A716C[];
extern s32 D_800A7178[];
extern s32 D_800A7184[];
extern s32 D_800A7190[];
extern s32 D_800A71C0[];
extern s32 D_800A71CC[];
extern s32 D_800A71D8[];
extern s32 D_800A71E4[];
extern s32 D_800A71F0[];
extern s32 D_800A71FC[];
extern s32 D_800A7208[];
extern s32 D_800A7214[];
extern s32 D_800A7244[];
extern s32 D_800A7250[];
extern s32 D_800A725C[];
extern s32 D_800A7268[];
extern s32 D_800A7274[];
extern s32 D_800A7280[];
extern s32 D_800A728C[];
extern s32 D_800A7298[];
extern s32 D_800A72C8[];
extern s32 D_800A72D4[];
extern s32 D_800A72E0[];
extern s32 D_800A72EC[];
extern s32 D_800A72F8[];
extern s32 D_800A7304[];
extern s32 D_800A7310[];
extern s32 D_800A731C[];
extern s32 D_800A734C[];
extern s32 D_800A7358[];
extern s32 D_800A7364[];
extern s32 D_800A7370[];
extern s32 D_800A737C[];
extern s32 D_800A7388[];
extern s32 D_800A7394[];
extern s32 D_800A73A0[];
extern s32 D_800A73D0[];
extern s32 D_800A73DC[];
extern s32 D_800A73E8[];
extern s32 D_800A73F4[];
extern s32 D_800A7400[];
extern s32 D_800A740C[];
extern s32 D_800A7418[];
extern s32 D_800A7424[];
extern s32 D_800A7454[];
extern s32 D_800A7460[];
extern s32 D_800A746C[];
extern s32 D_800A7478[];
extern s32 D_800A7484[];
extern s32 D_800A7490[];
extern s32 D_800A749C[];
extern s32 D_800A74A8[];
extern s32 D_800A74D8[];
extern s32 D_800A74E4[];
extern s32 D_800A74F0[];
extern s32 D_800A74FC[];
extern s32 D_800A7508[];
extern s32 D_800A7514[];
extern s32 D_800A7520[];
extern s32 D_800A752C[];
extern s32 D_800A52AC[];
extern s32 D_800A5330[];
extern s32 D_800A53B4[];
extern s32 D_800A5438[];
extern s32 D_800A54BC[];
extern s32 D_800A5540[];
extern s32 D_800A55C4[];
extern s32 D_800A5648[];
extern s32 D_800A56CC[];
extern s32 D_800A5750[];
extern s32 D_800A57D4[];
extern s32 D_800A5858[];
extern s32 D_800A58DC[];
extern s32 D_800A5960[];
extern s32 D_800A59E4[];
extern s32 D_800A5A68[];
extern s32 D_800A5AEC[];
extern s32 D_800A5B70[];
extern s32 D_800A5BF4[];
extern s32 D_800A5C78[];
extern s32 D_800A5CFC[];
extern s32 D_800A5D80[];
extern s32 D_800A5E04[];
extern s32 D_800A5E88[];
extern s32 D_800A5F0C[];
extern s32 D_800A5F90[];
extern s32 D_800A6014[];
extern s32 D_800A6098[];
extern s32 D_800A611C[];
extern s32 D_800A61A0[];
extern s32 D_800A6224[];
extern s32 D_800A62A8[];
extern s32 D_800A632C[];
extern s32 D_800A63B0[];
extern s32 D_800A6434[];
extern s32 D_800A64B8[];
extern s32 D_800A653C[];
extern s32 D_800A65C0[];
extern s32 D_800A6644[];
extern s32 D_800A66C8[];
extern s32 D_800A674C[];
extern s32 D_800A67D0[];
extern s32 D_800A6854[];
extern s32 D_800A68D8[];
extern s32 D_800A695C[];
extern s32 D_800A69E0[];
extern s32 D_800A6A64[];
extern s32 D_800A6AE8[];
extern s32 D_800A6B6C[];
extern s32 D_800A6BF0[];
extern s32 D_800A6C74[];
extern s32 D_800A6CF8[];
extern s32 D_800A6D7C[];
extern s32 D_800A6E00[];
extern s32 D_800A6E84[];
extern s32 D_800A6F08[];
extern s32 D_800A6F8C[];
extern s32 D_800A7010[];
extern s32 D_800A7094[];
extern s32 D_800A7118[];
extern s32 D_800A719C[];
extern s32 D_800A7220[];
extern s32 D_800A72A4[];
extern s32 D_800A7328[];
extern s32 D_800A73AC[];
extern s32 D_800A7430[];
extern s32 D_800A74B4[];
extern s32 D_800A7538[];
extern s32 D_800A7858[];
extern s32 D_800A7864[];
extern s32 D_800A786C[];
extern s32 D_800A7878[];
extern s32 D_800A7884[];
extern s32 D_800A788C[];
extern s32 D_800A7898[];
extern s32 D_800A78A8[];
extern s32 D_800A78B4[];
extern s32 D_800A78BC[];
extern s32 D_800A78C8[];
extern s32 D_800A78D4[];
extern s32 D_800A78DC[];
extern s32 D_800A78E8[];
extern s32 D_800A78FC[];
extern s32 D_800A7908[];
extern s32 D_800A7910[];
extern s32 D_800A791C[];
extern s32 D_800A7928[];
extern s32 D_800A7930[];
extern s32 D_800A793C[];
extern s32 D_800A794C[];
extern s32 D_800A7958[];
extern s32 D_800A7960[];
extern s32 D_800A796C[];
extern s32 D_800A7978[];
extern s32 D_800A7980[];
extern s32 D_800A798C[];
extern s32 D_800A799C[];
extern s32 D_800A79A8[];
extern s32 D_800A79B0[];
extern s32 D_800A79BC[];
extern s32 D_800A79C8[];
extern s32 D_800A79D0[];
extern s32 D_800A79DC[];
extern s32 D_800A79EC[];
extern s32 D_800A79F8[];
extern s32 D_800A7A00[];
extern s32 D_800A7A0C[];
extern s32 D_800A7A18[];
extern s32 D_800A7A20[];
extern s32 D_800A7A2C[];
extern s32 D_800A7A3C[];
extern s32 D_800A7A48[];
extern s32 D_800A7A50[];
extern s32 D_800A7A5C[];
extern s32 D_800A7A68[];
extern s32 D_800A7A70[];
extern s32 D_800A7A7C[];
extern s32 D_800A7A8C[];
extern s32 D_800A7A98[];
extern s32 D_800A7AA0[];
extern s32 D_800A7AAC[];
extern s32 D_800A7AB8[];
extern s32 D_800A7AC0[];
extern s32 D_800A7ACC[];
extern s32 D_800A7CBC[];
extern s32 D_800A7CC8[];
extern s32 D_800A7ADC[];
extern s32 D_800A7CDC[];
extern s32 D_800A7B18[];
extern s32 D_800A7CF0[];
extern s32 D_800A7B54[];
extern s32 D_800A7D04[];
extern s32 D_800A7B90[];
extern s32 D_800A7D18[];
extern s32 D_800A7BCC[];
extern s32 D_800A7D2C[];
extern s32 D_800A7C08[];
extern s32 D_800A7D40[];
extern s32 D_800A7C44[];
extern s32 D_800A7D54[];
extern s32 D_800A7C80[];
extern s32 D_800A7D68[];
extern s32 D_800A7D74[];
extern s32 D_800A7D80[];
extern s32 D_800A7D8C[];
extern s32 D_800A7D98[];
extern s32 D_800A7DA4[];
extern s32 D_800A7DB0[];
extern s32 D_800A7DBC[];
extern s32 D_800A7DC8[];
extern s32 D_800A7DD4[];
extern s32 D_800A7DE0[];
extern s32 D_800A7DEC[];
extern s32 D_800A7E00[];
extern s32 D_800A7E14[];
extern s32 D_800A7E28[];
extern s32 D_800A7E3C[];
extern s32 D_800A7E50[];
extern s32 D_800A7E64[];
extern s32 D_800A7E78[];
extern s32 D_800A7E8C[];
extern s32 D_800A7EA0[];
extern s32 D_800A7EB4[];
extern s32 D_800A7EC8[];
extern s32 D_800A7EDC[];
extern s32 D_800A7EF0[];
extern s32 D_800A7F04[];
extern s32 D_800A7F18[];
extern s32 D_800A7F2C[];
extern s32 D_800A7F40[];
extern s32 D_800A7F54[];
extern s32 D_800A7F68[];
extern s32 D_800A7F7C[];

StagePoint D_800A4F8C = { 0x2ED, 2, 1, 0x3A0, 128, 1, NULL };
StagePoints D_800A4F9C = { 2, 1, &D_800A4F8C };
StagePoint D_800A4FA4 = { 0x2EE, 2, 2, 0x130, 200, 1, NULL };
StagePoints D_800A4FB4 = { 2, 2, &D_800A4FA4 };
StagePoint D_800A4FBC = { 0x2EE, 4, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoints D_800A4FCC = { 4, 1, &D_800A4FBC };
StagePoint D_800A4FD4 = { 0x2ED, 5, 1, 0x3A0, 128, 1, NULL };
StagePoints D_800A4FE4 = { 5, 1, &D_800A4FD4 };
StagePoint D_800A4FEC = { 0x2EC, 6, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A4FFC = { 6, 1, &D_800A4FEC };
StagePoint D_800A5004 = { 0x2ED, 6, 2, 0x3A0, 128, 1, NULL };
StagePoints D_800A5014 = { 6, 2, &D_800A5004 };
StagePoint D_800A501C = { 0x2ED, 9, 1, 0x3A0, 128, 1, NULL };
StagePoints D_800A502C = { 9, 1, &D_800A501C };
StagePoint D_800A5034 = { 0x2EE, 9, 2, 0x130, 200, 1, NULL };
StagePoints D_800A5044 = { 9, 2, &D_800A5034 };
StagePoint D_800A504C = { 0x2EC, 12, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A505C = { 12, 1, &D_800A504C };
StagePoint D_800A5064 = { 0x2EC, 12, 2, 0x3B0, 120, 1, NULL };
StagePoints D_800A5074 = { 12, 2, &D_800A5064 };
StagePoint D_800A507C = { 0x2EC, 13, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A508C = { 13, 1, &D_800A507C };
StagePoint D_800A5094 = { 0x2ED, 13, 1, 0x3A0, 128, 1, NULL };
StagePoints D_800A50A4 = { 13, 2, &D_800A5094 };
StagePoint D_800A50AC = { 0x2ED, 14, 1, 0x3A0, 128, 1, NULL };
StagePoints D_800A50BC = { 14, 1, &D_800A50AC };
StagePoint D_800A50C4 = { 0x2EE, 16, 1, 0x130, 200, 1, NULL };
StagePoints D_800A50D4 = { 16, 1, &D_800A50C4 };
StagePoint D_800A50DC = { 0x2EC, 19, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A50EC = { 19, 1, &D_800A50DC };
StagePoint D_800A50F4 = { 0x2EE, 19, 1, 0x130, 200, 1, NULL };
StagePoints D_800A5104 = { 19, 2, &D_800A50F4 };
StagePoint D_800A510C = { 0x2EE, 20, 1, 0x130, 200, 1, NULL };
StagePoints D_800A511C = { 20, 1, &D_800A510C };
StagePoint D_800A5124 = { 0x2EC, 20, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A5134 = { 20, 2, &D_800A5124 };
StagePoint D_800A513C = { 0x2EC, 21, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A514C = { 21, 1, &D_800A513C };
StagePoint D_800A5154 = { 0x2EE, 25, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoints D_800A5164 = { 25, 1, &D_800A5154 };
StagePoint D_800A516C = { 0x2ED, 27, 1, 0x3A0, 128, 1, NULL };
StagePoints D_800A517C = { 27, 1, &D_800A516C };
StagePoint D_800A5184 = { 0x2EC, 28, 1, 0x3B0, 120, 1, NULL };
StagePoints D_800A5194 = { 28, 1, &D_800A5184 };
StagePoint D_800A519C = { 0x2EC, 28, 2, 0x3B0, 120, 1, NULL };
StagePoints D_800A51AC = { 28, 2, &D_800A519C };
StagePoint D_800A51B4 = { 0x2EC, 29, 2, 0x3B0, 120, 1, NULL };
StagePoints D_800A51C4 = { 29, 1, &D_800A51B4 };
StagePoint D_800A51CC = { 0x2EE, 30, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoints D_800A51DC = { 30, 1, &D_800A51CC };
StagePoints *D_800A51E4[] = {
    &D_800A4F9C, &D_800A4FB4, &D_800A4FCC, &D_800A4FE4,
    &D_800A4FFC, &D_800A5014, &D_800A502C, &D_800A5044,
    &D_800A505C, &D_800A5074, &D_800A508C, &D_800A50A4,
    &D_800A50BC, &D_800A50D4, &D_800A50EC, &D_800A5104,
    &D_800A511C, &D_800A5134, &D_800A514C, &D_800A5164,
    &D_800A517C, &D_800A5194, &D_800A51AC, &D_800A51C4,
    &D_800A51DC, NULL,
};
s32 D_800A524C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5258[] = {
    174, 10, 0x60080000,
};
s32 D_800A5264[] = {
    170, 10, 0x60080000,
};
s32 D_800A5270[] = {
    170, 10, 0x60080000,
};
s32 D_800A527C[] = {
    170, 10, 0x60080000,
};
s32 D_800A5288[] = {
    110, 10, 0x60080000,
};
s32 D_800A5294[] = {
    110, 10, 0x60080000,
};
s32 D_800A52A0[] = {
    110, 10, 0x60080000,
};
s32 D_800A52AC[] = {
    1, (s32)D_800A524C, (s32)D_800A5258, (s32)D_800A5264,
    (s32)D_800A5270, (s32)D_800A527C, (s32)D_800A5288, (s32)D_800A5294,
    (s32)D_800A52A0,
};
s32 D_800A52D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A52F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5300[] = {
    0, 0, 0x60040000,
};
s32 D_800A530C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5318[] = {
    0, 0, 0x60040000,
};
s32 D_800A5324[] = {
    0, 0, 0x60040000,
};
s32 D_800A5330[] = {
    0, (s32)D_800A52D0, (s32)D_800A52DC, (s32)D_800A52E8,
    (s32)D_800A52F4, (s32)D_800A5300, (s32)D_800A530C, (s32)D_800A5318,
    (s32)D_800A5324,
};
s32 D_800A5354[] = {
    0, 0, 0x60040000,
};
s32 D_800A5360[] = {
    0, 0, 0x60040000,
};
s32 D_800A536C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5378[] = {
    0, 0, 0x60040000,
};
s32 D_800A5384[] = {
    0, 0, 0x60040000,
};
s32 D_800A5390[] = {
    0, 0, 0x60040000,
};
s32 D_800A539C[] = {
    0, 0, 0x60040000,
};
s32 D_800A53A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53B4[] = {
    0, (s32)D_800A5354, (s32)D_800A5360, (s32)D_800A536C,
    (s32)D_800A5378, (s32)D_800A5384, (s32)D_800A5390, (s32)D_800A539C,
    (s32)D_800A53A8,
};
s32 D_800A53D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A53E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A53F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A53FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5408[] = {
    0, 0, 0x60040000,
};
s32 D_800A5414[] = {
    0, 0, 0x60040000,
};
s32 D_800A5420[] = {
    0, 0, 0x60040000,
};
s32 D_800A542C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5438[] = {
    0, (s32)D_800A53D8, (s32)D_800A53E4, (s32)D_800A53F0,
    (s32)D_800A53FC, (s32)D_800A5408, (s32)D_800A5414, (s32)D_800A5420,
    (s32)D_800A542C,
};
s32 D_800A545C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5468[] = {
    174, 10, 0x60080000,
};
s32 D_800A5474[] = {
    170, 10, 0x60080000,
};
s32 D_800A5480[] = {
    170, 10, 0x60080000,
};
s32 D_800A548C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5498[] = {
    182, 10, 0x60080000,
};
s32 D_800A54A4[] = {
    71, 10, 0x60080000,
};
s32 D_800A54B0[] = {
    71, 10, 0x60080000,
};
s32 D_800A54BC[] = {
    1, (s32)D_800A545C, (s32)D_800A5468, (s32)D_800A5474,
    (s32)D_800A5480, (s32)D_800A548C, (s32)D_800A5498, (s32)D_800A54A4,
    (s32)D_800A54B0,
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
    0, 0, 0x60040000,
};
s32 D_800A551C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5528[] = {
    0, 0, 0x60040000,
};
s32 D_800A5534[] = {
    0, 0, 0x60040000,
};
s32 D_800A5540[] = {
    0, (s32)D_800A54E0, (s32)D_800A54EC, (s32)D_800A54F8,
    (s32)D_800A5504, (s32)D_800A5510, (s32)D_800A551C, (s32)D_800A5528,
    (s32)D_800A5534,
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
    0, 0, 0x60040000,
};
s32 D_800A55A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A55AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A55B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A55C4[] = {
    0, (s32)D_800A5564, (s32)D_800A5570, (s32)D_800A557C,
    (s32)D_800A5588, (s32)D_800A5594, (s32)D_800A55A0, (s32)D_800A55AC,
    (s32)D_800A55B8,
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
    0, 0, 0x60040000,
};
s32 D_800A5624[] = {
    0, 0, 0x60040000,
};
s32 D_800A5630[] = {
    0, 0, 0x60040000,
};
s32 D_800A563C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5648[] = {
    0, (s32)D_800A55E8, (s32)D_800A55F4, (s32)D_800A5600,
    (s32)D_800A560C, (s32)D_800A5618, (s32)D_800A5624, (s32)D_800A5630,
    (s32)D_800A563C,
};
s32 D_800A566C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5678[] = {
    170, 10, 0x60080000,
};
s32 D_800A5684[] = {
    110, 10, 0x60080000,
};
s32 D_800A5690[] = {
    110, 10, 0x60080000,
};
s32 D_800A569C[] = {
    182, 10, 0x60080000,
};
s32 D_800A56A8[] = {
    182, 10, 0x60080000,
};
s32 D_800A56B4[] = {
    71, 10, 0x60080000,
};
s32 D_800A56C0[] = {
    71, 10, 0x60080000,
};
s32 D_800A56CC[] = {
    1, (s32)D_800A566C, (s32)D_800A5678, (s32)D_800A5684,
    (s32)D_800A5690, (s32)D_800A569C, (s32)D_800A56A8, (s32)D_800A56B4,
    (s32)D_800A56C0,
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
    0, 0, 0x60040000,
};
s32 D_800A572C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5738[] = {
    0, 0, 0x60040000,
};
s32 D_800A5744[] = {
    0, 0, 0x60040000,
};
s32 D_800A5750[] = {
    0, (s32)D_800A56F0, (s32)D_800A56FC, (s32)D_800A5708,
    (s32)D_800A5714, (s32)D_800A5720, (s32)D_800A572C, (s32)D_800A5738,
    (s32)D_800A5744,
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
    0, 0, 0x60040000,
};
s32 D_800A57B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A57BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A57C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A57D4[] = {
    0, (s32)D_800A5774, (s32)D_800A5780, (s32)D_800A578C,
    (s32)D_800A5798, (s32)D_800A57A4, (s32)D_800A57B0, (s32)D_800A57BC,
    (s32)D_800A57C8,
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
    0, 0, 0x60040000,
};
s32 D_800A5834[] = {
    0, 0, 0x60040000,
};
s32 D_800A5840[] = {
    0, 0, 0x60040000,
};
s32 D_800A584C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5858[] = {
    0, (s32)D_800A57F8, (s32)D_800A5804, (s32)D_800A5810,
    (s32)D_800A581C, (s32)D_800A5828, (s32)D_800A5834, (s32)D_800A5840,
    (s32)D_800A584C,
};
s32 D_800A587C[] = {
    174, 10, 0x60080000,
};
s32 D_800A5888[] = {
    170, 10, 0x60080000,
};
s32 D_800A5894[] = {
    110, 10, 0x60080000,
};
s32 D_800A58A0[] = {
    110, 10, 0x60080000,
};
s32 D_800A58AC[] = {
    182, 10, 0x60080000,
};
s32 D_800A58B8[] = {
    182, 10, 0x60080000,
};
s32 D_800A58C4[] = {
    71, 10, 0x60080000,
};
s32 D_800A58D0[] = {
    71, 10, 0x60080000,
};
s32 D_800A58DC[] = {
    1, (s32)D_800A587C, (s32)D_800A5888, (s32)D_800A5894,
    (s32)D_800A58A0, (s32)D_800A58AC, (s32)D_800A58B8, (s32)D_800A58C4,
    (s32)D_800A58D0,
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
    0, 0, 0x60040000,
};
s32 D_800A593C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5948[] = {
    0, 0, 0x60040000,
};
s32 D_800A5954[] = {
    0, 0, 0x60040000,
};
s32 D_800A5960[] = {
    0, (s32)D_800A5900, (s32)D_800A590C, (s32)D_800A5918,
    (s32)D_800A5924, (s32)D_800A5930, (s32)D_800A593C, (s32)D_800A5948,
    (s32)D_800A5954,
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
    0, 0, 0x60040000,
};
s32 D_800A59C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A59CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A59D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A59E4[] = {
    0, (s32)D_800A5984, (s32)D_800A5990, (s32)D_800A599C,
    (s32)D_800A59A8, (s32)D_800A59B4, (s32)D_800A59C0, (s32)D_800A59CC,
    (s32)D_800A59D8,
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
    0, 0, 0x60040000,
};
s32 D_800A5A44[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A50[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5A68[] = {
    0, (s32)D_800A5A08, (s32)D_800A5A14, (s32)D_800A5A20,
    (s32)D_800A5A2C, (s32)D_800A5A38, (s32)D_800A5A44, (s32)D_800A5A50,
    (s32)D_800A5A5C,
};
s32 D_800A5A8C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5A98[] = {
    182, 10, 0x60080000,
};
s32 D_800A5AA4[] = {
    182, 10, 0x60080000,
};
s32 D_800A5AB0[] = {
    182, 10, 0x60080000,
};
s32 D_800A5ABC[] = {
    71, 10, 0x60080000,
};
s32 D_800A5AC8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5AD4[] = {
    71, 10, 0x60080000,
};
s32 D_800A5AE0[] = {
    71, 10, 0x60080000,
};
s32 D_800A5AEC[] = {
    1, (s32)D_800A5A8C, (s32)D_800A5A98, (s32)D_800A5AA4,
    (s32)D_800A5AB0, (s32)D_800A5ABC, (s32)D_800A5AC8, (s32)D_800A5AD4,
    (s32)D_800A5AE0,
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
    0, (s32)D_800A5B10, (s32)D_800A5B1C, (s32)D_800A5B28,
    (s32)D_800A5B34, (s32)D_800A5B40, (s32)D_800A5B4C, (s32)D_800A5B58,
    (s32)D_800A5B64,
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
    0, (s32)D_800A5B94, (s32)D_800A5BA0, (s32)D_800A5BAC,
    (s32)D_800A5BB8, (s32)D_800A5BC4, (s32)D_800A5BD0, (s32)D_800A5BDC,
    (s32)D_800A5BE8,
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
    0, (s32)D_800A5C18, (s32)D_800A5C24, (s32)D_800A5C30,
    (s32)D_800A5C3C, (s32)D_800A5C48, (s32)D_800A5C54, (s32)D_800A5C60,
    (s32)D_800A5C6C,
};
s32 D_800A5C9C[] = {
    182, 10, 0x60080000,
};
s32 D_800A5CA8[] = {
    182, 10, 0x60080000,
};
s32 D_800A5CB4[] = {
    182, 10, 0x60080000,
};
s32 D_800A5CC0[] = {
    182, 10, 0x60080000,
};
s32 D_800A5CCC[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CD8[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CE4[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CF0[] = {
    71, 10, 0x60080000,
};
s32 D_800A5CFC[] = {
    1, (s32)D_800A5C9C, (s32)D_800A5CA8, (s32)D_800A5CB4,
    (s32)D_800A5CC0, (s32)D_800A5CCC, (s32)D_800A5CD8, (s32)D_800A5CE4,
    (s32)D_800A5CF0,
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
    0, (s32)D_800A5D20, (s32)D_800A5D2C, (s32)D_800A5D38,
    (s32)D_800A5D44, (s32)D_800A5D50, (s32)D_800A5D5C, (s32)D_800A5D68,
    (s32)D_800A5D74,
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
    0, (s32)D_800A5DA4, (s32)D_800A5DB0, (s32)D_800A5DBC,
    (s32)D_800A5DC8, (s32)D_800A5DD4, (s32)D_800A5DE0, (s32)D_800A5DEC,
    (s32)D_800A5DF8,
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
    0, (s32)D_800A5E28, (s32)D_800A5E34, (s32)D_800A5E40,
    (s32)D_800A5E4C, (s32)D_800A5E58, (s32)D_800A5E64, (s32)D_800A5E70,
    (s32)D_800A5E7C,
};
s32 D_800A5EAC[] = {
    174, 10, 0x60080000,
};
s32 D_800A5EB8[] = {
    174, 10, 0x60080000,
};
s32 D_800A5EC4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5ED0[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EDC[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EE8[] = {
    170, 10, 0x60080000,
};
s32 D_800A5EF4[] = {
    170, 10, 0x60080000,
};
s32 D_800A5F00[] = {
    170, 10, 0x60080000,
};
s32 D_800A5F0C[] = {
    4, (s32)D_800A5EAC, (s32)D_800A5EB8, (s32)D_800A5EC4,
    (s32)D_800A5ED0, (s32)D_800A5EDC, (s32)D_800A5EE8, (s32)D_800A5EF4,
    (s32)D_800A5F00,
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
    0, (s32)D_800A5F30, (s32)D_800A5F3C, (s32)D_800A5F48,
    (s32)D_800A5F54, (s32)D_800A5F60, (s32)D_800A5F6C, (s32)D_800A5F78,
    (s32)D_800A5F84,
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
    0, (s32)D_800A5FB4, (s32)D_800A5FC0, (s32)D_800A5FCC,
    (s32)D_800A5FD8, (s32)D_800A5FE4, (s32)D_800A5FF0, (s32)D_800A5FFC,
    (s32)D_800A6008,
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
    0, (s32)D_800A6038, (s32)D_800A6044, (s32)D_800A6050,
    (s32)D_800A605C, (s32)D_800A6068, (s32)D_800A6074, (s32)D_800A6080,
    (s32)D_800A608C,
};
s32 D_800A60BC[] = {
    110, 10, 0x60080000,
};
s32 D_800A60C8[] = {
    110, 10, 0x60080000,
};
s32 D_800A60D4[] = {
    110, 10, 0x60080000,
};
s32 D_800A60E0[] = {
    110, 10, 0x60080000,
};
s32 D_800A60EC[] = {
    110, 10, 0x60080000,
};
s32 D_800A60F8[] = {
    110, 10, 0x60080000,
};
s32 D_800A6104[] = {
    110, 10, 0x60080000,
};
s32 D_800A6110[] = {
    110, 10, 0x60080000,
};
s32 D_800A611C[] = {
    1, (s32)D_800A60BC, (s32)D_800A60C8, (s32)D_800A60D4,
    (s32)D_800A60E0, (s32)D_800A60EC, (s32)D_800A60F8, (s32)D_800A6104,
    (s32)D_800A6110,
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
    0, (s32)D_800A6140, (s32)D_800A614C, (s32)D_800A6158,
    (s32)D_800A6164, (s32)D_800A6170, (s32)D_800A617C, (s32)D_800A6188,
    (s32)D_800A6194,
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
    0, (s32)D_800A61C4, (s32)D_800A61D0, (s32)D_800A61DC,
    (s32)D_800A61E8, (s32)D_800A61F4, (s32)D_800A6200, (s32)D_800A620C,
    (s32)D_800A6218,
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
    0, (s32)D_800A6248, (s32)D_800A6254, (s32)D_800A6260,
    (s32)D_800A626C, (s32)D_800A6278, (s32)D_800A6284, (s32)D_800A6290,
    (s32)D_800A629C,
};
s32 D_800A62CC[] = {
    182, 10, 0x60080000,
};
s32 D_800A62D8[] = {
    182, 10, 0x60080000,
};
s32 D_800A62E4[] = {
    182, 10, 0x60080000,
};
s32 D_800A62F0[] = {
    182, 10, 0x60080000,
};
s32 D_800A62FC[] = {
    71, 10, 0x60080000,
};
s32 D_800A6308[] = {
    71, 10, 0x60080000,
};
s32 D_800A6314[] = {
    71, 10, 0x60080000,
};
s32 D_800A6320[] = {
    71, 10, 0x60080000,
};
s32 D_800A632C[] = {
    5, (s32)D_800A62CC, (s32)D_800A62D8, (s32)D_800A62E4,
    (s32)D_800A62F0, (s32)D_800A62FC, (s32)D_800A6308, (s32)D_800A6314,
    (s32)D_800A6320,
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
    0, (s32)D_800A6350, (s32)D_800A635C, (s32)D_800A6368,
    (s32)D_800A6374, (s32)D_800A6380, (s32)D_800A638C, (s32)D_800A6398,
    (s32)D_800A63A4,
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
    0, (s32)D_800A63D4, (s32)D_800A63E0, (s32)D_800A63EC,
    (s32)D_800A63F8, (s32)D_800A6404, (s32)D_800A6410, (s32)D_800A641C,
    (s32)D_800A6428,
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
    0, (s32)D_800A6458, (s32)D_800A6464, (s32)D_800A6470,
    (s32)D_800A647C, (s32)D_800A6488, (s32)D_800A6494, (s32)D_800A64A0,
    (s32)D_800A64AC,
};
s32 D_800A64DC[] = {
    110, 10, 0x60080000,
};
s32 D_800A64E8[] = {
    110, 10, 0x60080000,
};
s32 D_800A64F4[] = {
    110, 10, 0x60080000,
};
s32 D_800A6500[] = {
    110, 10, 0x60080000,
};
s32 D_800A650C[] = {
    110, 10, 0x60080000,
};
s32 D_800A6518[] = {
    110, 10, 0x60080000,
};
s32 D_800A6524[] = {
    110, 10, 0x60080000,
};
s32 D_800A6530[] = {
    110, 10, 0x60080000,
};
s32 D_800A653C[] = {
    3, (s32)D_800A64DC, (s32)D_800A64E8, (s32)D_800A64F4,
    (s32)D_800A6500, (s32)D_800A650C, (s32)D_800A6518, (s32)D_800A6524,
    (s32)D_800A6530,
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
    0, (s32)D_800A6560, (s32)D_800A656C, (s32)D_800A6578,
    (s32)D_800A6584, (s32)D_800A6590, (s32)D_800A659C, (s32)D_800A65A8,
    (s32)D_800A65B4,
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
    0, (s32)D_800A65E4, (s32)D_800A65F0, (s32)D_800A65FC,
    (s32)D_800A6608, (s32)D_800A6614, (s32)D_800A6620, (s32)D_800A662C,
    (s32)D_800A6638,
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
    0, (s32)D_800A6668, (s32)D_800A6674, (s32)D_800A6680,
    (s32)D_800A668C, (s32)D_800A6698, (s32)D_800A66A4, (s32)D_800A66B0,
    (s32)D_800A66BC,
};
s32 D_800A66EC[] = {
    182, 10, 0x60080000,
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
    71, 10, 0x60080000,
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
    4, (s32)D_800A66EC, (s32)D_800A66F8, (s32)D_800A6704,
    (s32)D_800A6710, (s32)D_800A671C, (s32)D_800A6728, (s32)D_800A6734,
    (s32)D_800A6740,
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
    0, (s32)D_800A6770, (s32)D_800A677C, (s32)D_800A6788,
    (s32)D_800A6794, (s32)D_800A67A0, (s32)D_800A67AC, (s32)D_800A67B8,
    (s32)D_800A67C4,
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
    0, (s32)D_800A67F4, (s32)D_800A6800, (s32)D_800A680C,
    (s32)D_800A6818, (s32)D_800A6824, (s32)D_800A6830, (s32)D_800A683C,
    (s32)D_800A6848,
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
    0, (s32)D_800A6878, (s32)D_800A6884, (s32)D_800A6890,
    (s32)D_800A689C, (s32)D_800A68A8, (s32)D_800A68B4, (s32)D_800A68C0,
    (s32)D_800A68CC,
};
s32 D_800A68FC[] = {
    174, 10, 0x60080000,
};
s32 D_800A6908[] = {
    174, 10, 0x60080000,
};
s32 D_800A6914[] = {
    170, 10, 0x60080000,
};
s32 D_800A6920[] = {
    170, 10, 0x60080000,
};
s32 D_800A692C[] = {
    170, 10, 0x60080000,
};
s32 D_800A6938[] = {
    170, 10, 0x60080000,
};
s32 D_800A6944[] = {
    170, 10, 0x60080000,
};
s32 D_800A6950[] = {
    170, 10, 0x60080000,
};
s32 D_800A695C[] = {
    2, (s32)D_800A68FC, (s32)D_800A6908, (s32)D_800A6914,
    (s32)D_800A6920, (s32)D_800A692C, (s32)D_800A6938, (s32)D_800A6944,
    (s32)D_800A6950,
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
    0, (s32)D_800A6980, (s32)D_800A698C, (s32)D_800A6998,
    (s32)D_800A69A4, (s32)D_800A69B0, (s32)D_800A69BC, (s32)D_800A69C8,
    (s32)D_800A69D4,
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
    0, (s32)D_800A6A04, (s32)D_800A6A10, (s32)D_800A6A1C,
    (s32)D_800A6A28, (s32)D_800A6A34, (s32)D_800A6A40, (s32)D_800A6A4C,
    (s32)D_800A6A58,
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
    0, (s32)D_800A6A88, (s32)D_800A6A94, (s32)D_800A6AA0,
    (s32)D_800A6AAC, (s32)D_800A6AB8, (s32)D_800A6AC4, (s32)D_800A6AD0,
    (s32)D_800A6ADC,
};
s32 D_800A6B0C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6B18[] = {
    182, 10, 0x60080000,
};
s32 D_800A6B24[] = {
    182, 10, 0x60080000,
};
s32 D_800A6B30[] = {
    182, 10, 0x60080000,
};
s32 D_800A6B3C[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B48[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B54[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B60[] = {
    71, 10, 0x60080000,
};
s32 D_800A6B6C[] = {
    1, (s32)D_800A6B0C, (s32)D_800A6B18, (s32)D_800A6B24,
    (s32)D_800A6B30, (s32)D_800A6B3C, (s32)D_800A6B48, (s32)D_800A6B54,
    (s32)D_800A6B60,
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
    0, (s32)D_800A6B90, (s32)D_800A6B9C, (s32)D_800A6BA8,
    (s32)D_800A6BB4, (s32)D_800A6BC0, (s32)D_800A6BCC, (s32)D_800A6BD8,
    (s32)D_800A6BE4,
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
    0, (s32)D_800A6C14, (s32)D_800A6C20, (s32)D_800A6C2C,
    (s32)D_800A6C38, (s32)D_800A6C44, (s32)D_800A6C50, (s32)D_800A6C5C,
    (s32)D_800A6C68,
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
    0, (s32)D_800A6C98, (s32)D_800A6CA4, (s32)D_800A6CB0,
    (s32)D_800A6CBC, (s32)D_800A6CC8, (s32)D_800A6CD4, (s32)D_800A6CE0,
    (s32)D_800A6CEC,
};
s32 D_800A6D1C[] = {
    182, 10, 0x60080000,
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
    71, 10, 0x60080000,
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
    1, (s32)D_800A6D1C, (s32)D_800A6D28, (s32)D_800A6D34,
    (s32)D_800A6D40, (s32)D_800A6D4C, (s32)D_800A6D58, (s32)D_800A6D64,
    (s32)D_800A6D70,
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
    0, (s32)D_800A6DA0, (s32)D_800A6DAC, (s32)D_800A6DB8,
    (s32)D_800A6DC4, (s32)D_800A6DD0, (s32)D_800A6DDC, (s32)D_800A6DE8,
    (s32)D_800A6DF4,
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
    0, (s32)D_800A6E24, (s32)D_800A6E30, (s32)D_800A6E3C,
    (s32)D_800A6E48, (s32)D_800A6E54, (s32)D_800A6E60, (s32)D_800A6E6C,
    (s32)D_800A6E78,
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
    0, 0, 0x60040000,
};
s32 D_800A6EFC[] = {
    0, 0, 0x60040000,
};
s32 D_800A6F08[] = {
    0, (s32)D_800A6EA8, (s32)D_800A6EB4, (s32)D_800A6EC0,
    (s32)D_800A6ECC, (s32)D_800A6ED8, (s32)D_800A6EE4, (s32)D_800A6EF0,
    (s32)D_800A6EFC,
};
s32 D_800A6F2C[] = {
    174, 10, 0x60080000,
};
s32 D_800A6F38[] = {
    174, 10, 0x60080000,
};
s32 D_800A6F44[] = {
    170, 10, 0x60080000,
};
s32 D_800A6F50[] = {
    170, 10, 0x60080000,
};
s32 D_800A6F5C[] = {
    182, 10, 0x60080000,
};
s32 D_800A6F68[] = {
    182, 10, 0x60080000,
};
s32 D_800A6F74[] = {
    71, 10, 0x60080000,
};
s32 D_800A6F80[] = {
    71, 10, 0x60080000,
};
s32 D_800A6F8C[] = {
    1, (s32)D_800A6F2C, (s32)D_800A6F38, (s32)D_800A6F44,
    (s32)D_800A6F50, (s32)D_800A6F5C, (s32)D_800A6F68, (s32)D_800A6F74,
    (s32)D_800A6F80,
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
    0, (s32)D_800A6FB0, (s32)D_800A6FBC, (s32)D_800A6FC8,
    (s32)D_800A6FD4, (s32)D_800A6FE0, (s32)D_800A6FEC, (s32)D_800A6FF8,
    (s32)D_800A7004,
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
    0, (s32)D_800A7034, (s32)D_800A7040, (s32)D_800A704C,
    (s32)D_800A7058, (s32)D_800A7064, (s32)D_800A7070, (s32)D_800A707C,
    (s32)D_800A7088,
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
    0, 0, 0x60040000,
};
s32 D_800A710C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7118[] = {
    0, (s32)D_800A70B8, (s32)D_800A70C4, (s32)D_800A70D0,
    (s32)D_800A70DC, (s32)D_800A70E8, (s32)D_800A70F4, (s32)D_800A7100,
    (s32)D_800A710C,
};
s32 D_800A713C[] = {
    182, 10, 0x60080000,
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
    71, 10, 0x60080000,
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
    1, (s32)D_800A713C, (s32)D_800A7148, (s32)D_800A7154,
    (s32)D_800A7160, (s32)D_800A716C, (s32)D_800A7178, (s32)D_800A7184,
    (s32)D_800A7190,
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
    0, 0, 0x60040000,
};
s32 D_800A7214[] = {
    0, 0, 0x60040000,
};
s32 D_800A7220[] = {
    0, (s32)D_800A71C0, (s32)D_800A71CC, (s32)D_800A71D8,
    (s32)D_800A71E4, (s32)D_800A71F0, (s32)D_800A71FC, (s32)D_800A7208,
    (s32)D_800A7214,
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
    0, (s32)D_800A7244, (s32)D_800A7250, (s32)D_800A725C,
    (s32)D_800A7268, (s32)D_800A7274, (s32)D_800A7280, (s32)D_800A728C,
    (s32)D_800A7298,
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
    0, 0, 0x60040000,
};
s32 D_800A731C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7328[] = {
    0, (s32)D_800A72C8, (s32)D_800A72D4, (s32)D_800A72E0,
    (s32)D_800A72EC, (s32)D_800A72F8, (s32)D_800A7304, (s32)D_800A7310,
    (s32)D_800A731C,
};
s32 D_800A734C[] = {
    182, 10, 0x60080000,
};
s32 D_800A7358[] = {
    182, 10, 0x60080000,
};
s32 D_800A7364[] = {
    182, 10, 0x60080000,
};
s32 D_800A7370[] = {
    182, 10, 0x60080000,
};
s32 D_800A737C[] = {
    71, 10, 0x60080000,
};
s32 D_800A7388[] = {
    71, 10, 0x60080000,
};
s32 D_800A7394[] = {
    71, 10, 0x60080000,
};
s32 D_800A73A0[] = {
    71, 10, 0x60080000,
};
s32 D_800A73AC[] = {
    1, (s32)D_800A734C, (s32)D_800A7358, (s32)D_800A7364,
    (s32)D_800A7370, (s32)D_800A737C, (s32)D_800A7388, (s32)D_800A7394,
    (s32)D_800A73A0,
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
    0, 0, 0x60040000,
};
s32 D_800A7424[] = {
    0, 0, 0x60040000,
};
s32 D_800A7430[] = {
    0, (s32)D_800A73D0, (s32)D_800A73DC, (s32)D_800A73E8,
    (s32)D_800A73F4, (s32)D_800A7400, (s32)D_800A740C, (s32)D_800A7418,
    (s32)D_800A7424,
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
    0, (s32)D_800A7454, (s32)D_800A7460, (s32)D_800A746C,
    (s32)D_800A7478, (s32)D_800A7484, (s32)D_800A7490, (s32)D_800A749C,
    (s32)D_800A74A8,
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
    0, 0, 0x60040000,
};
s32 D_800A752C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7538[] = {
    0, (s32)D_800A74D8, (s32)D_800A74E4, (s32)D_800A74F0,
    (s32)D_800A74FC, (s32)D_800A7508, (s32)D_800A7514, (s32)D_800A7520,
    (s32)D_800A752C,
};
s32 D_800A755C[] = {
    236, 2, 0, (s32)D_800A52AC,
    (s32)D_800A5330, (s32)D_800A53B4, (s32)D_800A5438, 247,
    4, 0, (s32)D_800A54BC, (s32)D_800A5540,
    (s32)D_800A55C4, (s32)D_800A5648, 252, 5,
    0, (s32)D_800A56CC, (s32)D_800A5750, (s32)D_800A57D4,
    (s32)D_800A5858, 258, 6, 0,
    (s32)D_800A58DC, (s32)D_800A5960, (s32)D_800A59E4, (s32)D_800A5A68,
    274, 9, 0, (s32)D_800A5AEC,
    (s32)D_800A5B70, (s32)D_800A5BF4, (s32)D_800A5C78, 295,
    13, 0, (s32)D_800A5CFC, (s32)D_800A5D80,
    (s32)D_800A5E04, (s32)D_800A5E88, 307, 16,
    0, (s32)D_800A5F0C, (s32)D_800A5F90, (s32)D_800A6014,
    (s32)D_800A6098, 317, 19, 0,
    (s32)D_800A611C, (s32)D_800A61A0, (s32)D_800A6224, (s32)D_800A62A8,
    323, 20, 0, (s32)D_800A632C,
    (s32)D_800A63B0, (s32)D_800A6434, (s32)D_800A64B8, 329,
    21, 0, (s32)D_800A653C, (s32)D_800A65C0,
    (s32)D_800A6644, (s32)D_800A66C8, 346, 25,
    0, (s32)D_800A674C, (s32)D_800A67D0, (s32)D_800A6854,
    (s32)D_800A68D8, 352, 27, 0,
    (s32)D_800A695C, (s32)D_800A69E0, (s32)D_800A6A64, (s32)D_800A6AE8,
    356, 28, 0, (s32)D_800A6B6C,
    (s32)D_800A6BF0, (s32)D_800A6C74, (s32)D_800A6CF8, 363,
    29, 0, (s32)D_800A6D7C, (s32)D_800A6E00,
    (s32)D_800A6E84, (s32)D_800A6F08, 370, 30,
    0, (s32)D_800A6F8C, (s32)D_800A7010, (s32)D_800A7094,
    (s32)D_800A7118, 377, 12, 0,
    (s32)D_800A719C, (s32)D_800A7220, (s32)D_800A72A4, (s32)D_800A7328,
    378, 14, 0, (s32)D_800A73AC,
    (s32)D_800A7430, (s32)D_800A74B4, (s32)D_800A7538,
};
s32 D_800A7738[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1400140, 0x400000, 0x1FF0140,
    0x1000140, 0x1000168, 160, 0x1FF0150,
    0x1000140, 0x140014C, 0x400030, 0x1FF0160,
    0x1000140, 0x1400154, 0x400050, 0x1FF0170,
    0x1000140, 0x140015C, 0x400070, 0x1FE0140,
    0x1000140, 0x1400164, 0x400090, 0x1FE0150,
    0x1000140, 0x140016C, 0x4000B0, 0x1FE0160,
    0x1000140, 0x1400174, 0x4000D0, 0x1FE0170,
    0x1000140, 0x160014C, 0x600030, 0x1FD0140,
    0x1000140, 0x1600154, 0x600050, 0x1FD0150,
    0x1000140, 0x1000140, 0, 0x1FD0160,
    0x1000140, 0x1000154, 80, 0x1FD0170,
};
s32 D_800A7858[] = {
    17, 7231, 65535,
};
s32 D_800A7864[] = {
    0x17645, 65535,
};
s32 D_800A786C[] = {
    17, 0x11C3F, 65535,
};
s32 D_800A7878[] = {
    0x10011, 16, 65535,
};
s32 D_800A7884[] = {
    17, 65535,
};
s32 D_800A788C[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A7898[] = {
    17, 16, 0x11C3F, 65535,
};
s32 D_800A78A8[] = {
    7232, 17, 65535,
};
s32 D_800A78B4[] = {
    0x17646, 65535,
};
s32 D_800A78BC[] = {
    0x11C40, 17, 65535,
};
s32 D_800A78C8[] = {
    0x10011, 16, 65535,
};
s32 D_800A78D4[] = {
    17, 65535,
};
s32 D_800A78DC[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A78E8[] = {
    17, 16, 0x11C40, 0x1818D,
    65535,
};
s32 D_800A78FC[] = {
    17, 37408, 65535,
};
s32 D_800A7908[] = {
    0x17647, 65535,
};
s32 D_800A7910[] = {
    17, 0x19220, 65535,
};
s32 D_800A791C[] = {
    0x10011, 16, 65535,
};
s32 D_800A7928[] = {
    17, 65535,
};
s32 D_800A7930[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A793C[] = {
    17, 16, 0x19220, 65535,
};
s32 D_800A794C[] = {
    37410, 17, 65535,
};
s32 D_800A7958[] = {
    0x17648, 65535,
};
s32 D_800A7960[] = {
    17, 0x19222, 65535,
};
s32 D_800A796C[] = {
    0x10011, 16, 65535,
};
s32 D_800A7978[] = {
    17, 65535,
};
s32 D_800A7980[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A798C[] = {
    17, 16, 0x19222, 65535,
};
s32 D_800A799C[] = {
    17, 37407, 65535,
};
s32 D_800A79A8[] = {
    0x1764B, 65535,
};
s32 D_800A79B0[] = {
    17, 0x1921F, 65535,
};
s32 D_800A79BC[] = {
    0x10011, 16, 65535,
};
s32 D_800A79C8[] = {
    17, 65535,
};
s32 D_800A79D0[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A79DC[] = {
    17, 16, 0x1921F, 65535,
};
s32 D_800A79EC[] = {
    17, 37445, 65535,
};
s32 D_800A79F8[] = {
    0x1764E, 65535,
};
s32 D_800A7A00[] = {
    17, 0x19245, 65535,
};
s32 D_800A7A0C[] = {
    0x10011, 16, 65535,
};
s32 D_800A7A18[] = {
    17, 65535,
};
s32 D_800A7A20[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A7A2C[] = {
    17, 16, 0x19245, 65535,
};
s32 D_800A7A3C[] = {
    17, 37617, 65535,
};
s32 D_800A7A48[] = {
    0x1764F, 65535,
};
s32 D_800A7A50[] = {
    17, 0x192F1, 65535,
};
s32 D_800A7A5C[] = {
    0x10011, 16, 65535,
};
s32 D_800A7A68[] = {
    17, 65535,
};
s32 D_800A7A70[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A7A7C[] = {
    17, 16, 0x192F1, 65535,
};
s32 D_800A7A8C[] = {
    17, 37488, 65535,
};
s32 D_800A7A98[] = {
    0x17650, 65535,
};
s32 D_800A7AA0[] = {
    17, 0x19270, 65535,
};
s32 D_800A7AAC[] = {
    0x10011, 16, 65535,
};
s32 D_800A7AB8[] = {
    17, 65535,
};
s32 D_800A7AC0[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A7ACC[] = {
    17, 16, 0x19270, 65535,
};
s32 D_800A7ADC[] = {
    (s32)D_800A7858, (s32)D_800A7864, 895, (s32)D_800A786C,
    0, 896, (s32)D_800A7878, (s32)D_800A7884,
    897, (s32)D_800A788C, (s32)D_800A7898, 898,
    0, 0, 0,
};
s32 D_800A7B18[] = {
    (s32)D_800A78A8, (s32)D_800A78B4, 899, (s32)D_800A78BC,
    0, 900, (s32)D_800A78C8, (s32)D_800A78D4,
    901, (s32)D_800A78DC, (s32)D_800A78E8, 902,
    0, 0, 0,
};
s32 D_800A7B54[] = {
    (s32)D_800A78FC, (s32)D_800A7908, 871, (s32)D_800A7910,
    0, 872, (s32)D_800A791C, (s32)D_800A7928,
    873, (s32)D_800A7930, (s32)D_800A793C, 874,
    0, 0, 0,
};
s32 D_800A7B90[] = {
    (s32)D_800A794C, (s32)D_800A7958, 871, (s32)D_800A7960,
    0, 872, (s32)D_800A796C, (s32)D_800A7978,
    873, (s32)D_800A7980, (s32)D_800A798C, 875,
    0, 0, 0,
};
s32 D_800A7BCC[] = {
    (s32)D_800A799C, (s32)D_800A79A8, 871, (s32)D_800A79B0,
    0, 872, (s32)D_800A79BC, (s32)D_800A79C8,
    873, (s32)D_800A79D0, (s32)D_800A79DC, 878,
    0, 0, 0,
};
s32 D_800A7C08[] = {
    (s32)D_800A79EC, (s32)D_800A79F8, 887, (s32)D_800A7A00,
    0, 888, (s32)D_800A7A0C, (s32)D_800A7A18,
    889, (s32)D_800A7A20, (s32)D_800A7A2C, 892,
    0, 0, 0,
};
s32 D_800A7C44[] = {
    (s32)D_800A7A3C, (s32)D_800A7A48, 887, (s32)D_800A7A50,
    0, 888, (s32)D_800A7A5C, (s32)D_800A7A68,
    889, (s32)D_800A7A70, (s32)D_800A7A7C, 893,
    0, 0, 0,
};
s32 D_800A7C80[] = {
    (s32)D_800A7A8C, (s32)D_800A7A98, 887, (s32)D_800A7AA0,
    0, 888, (s32)D_800A7AAC, (s32)D_800A7AB8,
    889, (s32)D_800A7AC0, (s32)D_800A7ACC, 894,
    0, 0, 0,
};
s32 D_800A7CBC[] = {
    0x17E08, 8, 65535,
};
s32 D_800A7CC8[] = {
    0x17E0D, 0x17E1E, 0x11C42, 7231,
    65535,
};
s32 D_800A7CDC[] = {
    0x17E1B, 0x17E1F, 0x11C3F, 7232,
    65535,
};
s32 D_800A7CF0[] = {
    0x18014, 37408, 0x17E1A, 0x17E1E,
    65535,
};
s32 D_800A7D04[] = {
    0x17E05, 0x17E1F, 0x18014, 37410,
    65535,
};
s32 D_800A7D18[] = {
    0x17E1C, 0x17E1E, 0x18014, 37407,
    65535,
};
s32 D_800A7D2C[] = {
    0x17E14, 0x17E1E, 0x18014, 37445,
    65535,
};
s32 D_800A7D40[] = {
    0x17E12, 0x17E1E, 0x18014, 37617,
    65535,
};
s32 D_800A7D54[] = {
    0x17E08, 0x17E1F, 0x18014, 37488,
    65535,
};
s32 D_800A7D68[] = {
    0x17E1E, 9, 65535,
};
s32 D_800A7D74[] = {
    0x17E1F, 9, 65535,
};
s32 D_800A7D80[] = {
    0x17E01, 10, 65535,
};
s32 D_800A7D8C[] = {
    0x17E05, 10, 65535,
};
s32 D_800A7D98[] = {
    0x17E08, 10, 65535,
};
s32 D_800A7DA4[] = {
    0x17E0C, 10, 65535,
};
s32 D_800A7DB0[] = {
    0x17E0D, 10, 65535,
};
s32 D_800A7DBC[] = {
    0x17E12, 10, 65535,
};
s32 D_800A7DC8[] = {
    0x17E13, 10, 65535,
};
s32 D_800A7DD4[] = {
    0x17E14, 10, 65535,
};
s32 D_800A7DE0[] = {
    0x17E1B, 10, 65535,
};
s32 D_800A7DEC[] = {
    0, 0, 0x40146, 0,
    0,
};
s32 D_800A7E00[] = {
    (s32)D_800A7CBC, 0, 0x50148, 0x1B80170,
    1,
};
s32 D_800A7E14[] = {
    (s32)D_800A7CC8, (s32)D_800A7ADC, 0x6014D, 0x9001B0,
    7,
};
s32 D_800A7E28[] = {
    (s32)D_800A7CDC, (s32)D_800A7B18, 0x7014E, 0x9001B0,
    7,
};
s32 D_800A7E3C[] = {
    (s32)D_800A7CF0, (s32)D_800A7B54, 0x8014F, 0x9001B0,
    7,
};
s32 D_800A7E50[] = {
    (s32)D_800A7D04, (s32)D_800A7B90, 0x90150, 0x9001B0,
    7,
};
s32 D_800A7E64[] = {
    (s32)D_800A7D18, (s32)D_800A7BCC, 0xA0153, 0x9001B0,
    7,
};
s32 D_800A7E78[] = {
    (s32)D_800A7D2C, (s32)D_800A7C08, 0xB015C, 0x9001B0,
    7,
};
s32 D_800A7E8C[] = {
    (s32)D_800A7D40, (s32)D_800A7C44, 0xC015D, 0x9001B0,
    7,
};
s32 D_800A7EA0[] = {
    (s32)D_800A7D54, (s32)D_800A7C80, 0xD015E, 0x9001B0,
    7,
};
s32 D_800A7EB4[] = {
    (s32)D_800A7D68, 0, 0xE015F, 0x1500180,
    1,
};
s32 D_800A7EC8[] = {
    (s32)D_800A7D74, 0, 0xE015F, 0x1E80110,
    1,
};
s32 D_800A7EDC[] = {
    (s32)D_800A7D80, 0, 0xF0160, 0x17C0188,
    1,
};
s32 D_800A7EF0[] = {
    (s32)D_800A7D8C, 0, 0xF0160, 0x1700140,
    1,
};
s32 D_800A7F04[] = {
    (s32)D_800A7D98, 0, 0xF0160, 0xB00220,
    1,
};
s32 D_800A7F18[] = {
    (s32)D_800A7DA4, 0, 0xF0160, 0x1080210,
    1,
};
s32 D_800A7F2C[] = {
    (s32)D_800A7DB0, 0, 0xF0160, 0xDC0208,
    1,
};
s32 D_800A7F40[] = {
    (s32)D_800A7DBC, 0, 0xF0160, 0xF801D0,
    1,
};
s32 D_800A7F54[] = {
    (s32)D_800A7DC8, 0, 0xF0160, 0x12C01C8,
    1,
};
s32 D_800A7F68[] = {
    (s32)D_800A7DD4, 0, 0xF0160, 0xC001E0,
    1,
};
s32 D_800A7F7C[] = {
    (s32)D_800A7DE0, 0, 0xF0160, 0xDC0208,
    1,
};
s32 D_800A7F90[] = {
    (s32)D_800A7DEC, (s32)D_800A7E00, (s32)D_800A7E14, (s32)D_800A7E28,
    (s32)D_800A7E3C, (s32)D_800A7E50, (s32)D_800A7E64, (s32)D_800A7E78,
    (s32)D_800A7E8C, (s32)D_800A7EA0, (s32)D_800A7EB4, (s32)D_800A7EC8,
    (s32)D_800A7EDC, (s32)D_800A7EF0, (s32)D_800A7F04, (s32)D_800A7F18,
    (s32)D_800A7F2C, (s32)D_800A7F40, (s32)D_800A7F54, (s32)D_800A7F68,
    (s32)D_800A7F7C, 0,
};
s32 D_800A7FE8[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A7FFC[] = {
    65535, 65535, 0x2EA0001, 0x20000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A802C[])(void) = {
    func_800A4E74,
};
