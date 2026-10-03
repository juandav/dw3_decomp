#include "common.h"
#include "stage.h"
void func_800A5EE0();
extern void (*D_800A7C10[])(void);
extern StagePoints *D_800A662C[];

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
        func_800A5DE0(D_800990B4.unk14, D_800A662C, GAME.unk44, GAME.unk46);
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
    D_800A7C10[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag972", func_800A5FB0);

void func_800A5FB0();
extern StagePoint D_800A60DC;
extern StagePoint D_800A60EC;
extern StagePoint D_800A6104;
extern StagePoint D_800A6114;
extern StagePoint D_800A612C;
extern StagePoint D_800A613C;
extern StagePoint D_800A6154;
extern StagePoint D_800A6164;
extern StagePoint D_800A617C;
extern StagePoint D_800A618C;
extern StagePoint D_800A61A4;
extern StagePoint D_800A61B4;
extern StagePoint D_800A61CC;
extern StagePoint D_800A61DC;
extern StagePoint D_800A61F4;
extern StagePoint D_800A6204;
extern StagePoint D_800A621C;
extern StagePoint D_800A622C;
extern StagePoint D_800A6244;
extern StagePoint D_800A6254;
extern StagePoint D_800A626C;
extern StagePoint D_800A627C;
extern StagePoint D_800A6294;
extern StagePoint D_800A62A4;
extern StagePoint D_800A62BC;
extern StagePoint D_800A62CC;
extern StagePoint D_800A62E4;
extern StagePoint D_800A62F4;
extern StagePoint D_800A630C;
extern StagePoint D_800A631C;
extern StagePoint D_800A6334;
extern StagePoint D_800A6344;
extern StagePoint D_800A635C;
extern StagePoint D_800A636C;
extern StagePoint D_800A6384;
extern StagePoint D_800A6394;
extern StagePoint D_800A63AC;
extern StagePoint D_800A63BC;
extern StagePoint D_800A63D4;
extern StagePoint D_800A63E4;
extern StagePoint D_800A63FC;
extern StagePoint D_800A640C;
extern StagePoint D_800A6424;
extern StagePoint D_800A6434;
extern StagePoint D_800A644C;
extern StagePoint D_800A645C;
extern StagePoint D_800A6474;
extern StagePoint D_800A6484;
extern StagePoint D_800A649C;
extern StagePoint D_800A64AC;
extern StagePoint D_800A64C4;
extern StagePoint D_800A64D4;
extern StagePoint D_800A64EC;
extern StagePoint D_800A64FC;
extern StagePoint D_800A6514;
extern StagePoint D_800A6524;
extern StagePoint D_800A653C;
extern StagePoint D_800A654C;
extern StagePoint D_800A6564;
extern StagePoint D_800A6574;
extern StagePoint D_800A658C;
extern StagePoint D_800A659C;
extern StagePoint D_800A65B4;
extern StagePoint D_800A65C4;
extern StagePoint D_800A65DC;
extern StagePoint D_800A65EC;
extern StagePoint D_800A6604;
extern StagePoint D_800A6614;
extern StagePoints D_800A60FC;
extern StagePoints D_800A6124;
extern StagePoints D_800A614C;
extern StagePoints D_800A6174;
extern StagePoints D_800A619C;
extern StagePoints D_800A61C4;
extern StagePoints D_800A61EC;
extern StagePoints D_800A6214;
extern StagePoints D_800A623C;
extern StagePoints D_800A6264;
extern StagePoints D_800A628C;
extern StagePoints D_800A62B4;
extern StagePoints D_800A62DC;
extern StagePoints D_800A6304;
extern StagePoints D_800A632C;
extern StagePoints D_800A6354;
extern StagePoints D_800A637C;
extern StagePoints D_800A63A4;
extern StagePoints D_800A63CC;
extern StagePoints D_800A63F4;
extern StagePoints D_800A641C;
extern StagePoints D_800A6444;
extern StagePoints D_800A646C;
extern StagePoints D_800A6494;
extern StagePoints D_800A64BC;
extern StagePoints D_800A64E4;
extern StagePoints D_800A650C;
extern StagePoints D_800A6534;
extern StagePoints D_800A655C;
extern StagePoints D_800A6584;
extern StagePoints D_800A65AC;
extern StagePoints D_800A65D4;
extern StagePoints D_800A65FC;
extern StagePoints D_800A6624;
extern s32 D_800A67C8[];
extern s32 D_800A67D4[];
extern s32 D_800A67E0[];
extern s32 D_800A67EC[];
extern s32 D_800A67F4[];
extern s32 D_800A6800[];
extern s32 D_800A6808[];
extern s32 D_800A6818[];
extern s32 D_800A6820[];
extern s32 D_800A6834[];
extern s32 D_800A6840[];
extern s32 D_800A6858[];
extern s32 D_800A686C[];
extern s32 D_800A6884[];
extern s32 D_800A6894[];
extern s32 D_800A689C[];
extern s32 D_800A68A8[];
extern s32 D_800A68B0[];
extern s32 D_800A68C0[];
extern s32 D_800A68C8[];
extern s32 D_800A68DC[];
extern s32 D_800A68E8[];
extern s32 D_800A6900[];
extern s32 D_800A6914[];
extern s32 D_800A692C[];
extern s32 D_800A693C[];
extern s32 D_800A6944[];
extern s32 D_800A6950[];
extern s32 D_800A6958[];
extern s32 D_800A6968[];
extern s32 D_800A6970[];
extern s32 D_800A6984[];
extern s32 D_800A6990[];
extern s32 D_800A69A8[];
extern s32 D_800A69BC[];
extern s32 D_800A69D4[];
extern s32 D_800A69E4[];
extern s32 D_800A69EC[];
extern s32 D_800A69F8[];
extern s32 D_800A6A00[];
extern s32 D_800A6A10[];
extern s32 D_800A6A18[];
extern s32 D_800A6A2C[];
extern s32 D_800A6A38[];
extern s32 D_800A6A50[];
extern s32 D_800A6A64[];
extern s32 D_800A6A7C[];
extern s32 D_800A6A8C[];
extern s32 D_800A6A94[];
extern s32 D_800A6AA0[];
extern s32 D_800A6AA8[];
extern s32 D_800A6AB8[];
extern s32 D_800A6AC0[];
extern s32 D_800A6AD4[];
extern s32 D_800A6AE0[];
extern s32 D_800A6AF8[];
extern s32 D_800A6B0C[];
extern s32 D_800A6B24[];
extern s32 D_800A6B34[];
extern s32 D_800A6B3C[];
extern s32 D_800A6B48[];
extern s32 D_800A6B50[];
extern s32 D_800A6B60[];
extern s32 D_800A6B68[];
extern s32 D_800A6B7C[];
extern s32 D_800A6B88[];
extern s32 D_800A6BA0[];
extern s32 D_800A6BB4[];
extern s32 D_800A6BCC[];
extern s32 D_800A6BDC[];
extern s32 D_800A6BE4[];
extern s32 D_800A6BF0[];
extern s32 D_800A6BF8[];
extern s32 D_800A6C08[];
extern s32 D_800A6C10[];
extern s32 D_800A6C24[];
extern s32 D_800A6C30[];
extern s32 D_800A6C48[];
extern s32 D_800A6C5C[];
extern s32 D_800A6C74[];
extern s32 D_800A6C84[];
extern s32 D_800A6C8C[];
extern s32 D_800A6C98[];
extern s32 D_800A6CA0[];
extern s32 D_800A6CB0[];
extern s32 D_800A6CB8[];
extern s32 D_800A6CCC[];
extern s32 D_800A6CD8[];
extern s32 D_800A6CF0[];
extern s32 D_800A6D04[];
extern s32 D_800A6D1C[];
extern s32 D_800A6D2C[];
extern s32 D_800A6D34[];
extern s32 D_800A6D40[];
extern s32 D_800A6D48[];
extern s32 D_800A6D58[];
extern s32 D_800A6D60[];
extern s32 D_800A6D74[];
extern s32 D_800A6D80[];
extern s32 D_800A6D98[];
extern s32 D_800A6DAC[];
extern s32 D_800A6DC4[];
extern s32 D_800A6DD4[];
extern s32 D_800A6DDC[];
extern s32 D_800A6DE8[];
extern s32 D_800A6DF0[];
extern s32 D_800A6E00[];
extern s32 D_800A6E08[];
extern s32 D_800A6E1C[];
extern s32 D_800A6E28[];
extern s32 D_800A6E40[];
extern s32 D_800A6E54[];
extern s32 D_800A6E6C[];
extern s32 D_800A6E7C[];
extern s32 D_800A6E84[];
extern s32 D_800A6E90[];
extern s32 D_800A6E98[];
extern s32 D_800A6EA8[];
extern s32 D_800A6EB0[];
extern s32 D_800A6EC4[];
extern s32 D_800A6ED0[];
extern s32 D_800A6EE8[];
extern s32 D_800A6EFC[];
extern s32 D_800A6F14[];
extern s32 D_800A6F24[];
extern s32 D_800A6F2C[];
extern s32 D_800A6F38[];
extern s32 D_800A6F40[];
extern s32 D_800A6F50[];
extern s32 D_800A6F58[];
extern s32 D_800A6F6C[];
extern s32 D_800A6F78[];
extern s32 D_800A6F90[];
extern s32 D_800A6FA4[];
extern s32 D_800A6FBC[];
extern s32 D_800A6FCC[];
extern s32 D_800A6FD4[];
extern s32 D_800A6FE0[];
extern s32 D_800A6FE8[];
extern s32 D_800A6FF8[];
extern s32 D_800A7000[];
extern s32 D_800A7014[];
extern s32 D_800A7020[];
extern s32 D_800A7038[];
extern s32 D_800A704C[];
extern s32 D_800A7064[];
extern s32 D_800A7074[];
extern s32 D_800A707C[];
extern s32 D_800A7088[];
extern s32 D_800A7090[];
extern s32 D_800A70A0[];
extern s32 D_800A70A8[];
extern s32 D_800A70BC[];
extern s32 D_800A70C8[];
extern s32 D_800A70E0[];
extern s32 D_800A70F4[];
extern s32 D_800A710C[];
extern s32 D_800A711C[];
extern s32 D_800A7124[];
extern s32 D_800A7130[];
extern s32 D_800A7138[];
extern s32 D_800A7148[];
extern s32 D_800A7150[];
extern s32 D_800A7164[];
extern s32 D_800A7170[];
extern s32 D_800A7188[];
extern s32 D_800A719C[];
extern s32 D_800A71B4[];
extern s32 D_800A71C4[];
extern s32 D_800A71CC[];
extern s32 D_800A71D4[];
extern s32 D_800A71DC[];
extern s32 D_800A71E8[];
extern s32 D_800A71F0[];
extern s32 D_800A71F8[];
extern s32 D_800A7200[];
extern s32 D_800A7788[];
extern s32 D_800A720C[];
extern s32 D_800A7798[];
extern s32 D_800A7224[];
extern s32 D_800A77B8[];
extern s32 D_800A723C[];
extern s32 D_800A77D8[];
extern s32 D_800A7254[];
extern s32 D_800A77E4[];
extern s32 D_800A72A8[];
extern s32 D_800A77F0[];
extern s32 D_800A72FC[];
extern s32 D_800A77FC[];
extern s32 D_800A7350[];
extern s32 D_800A7808[];
extern s32 D_800A73A4[];
extern s32 D_800A7814[];
extern s32 D_800A7820[];
extern s32 D_800A782C[];
extern s32 D_800A7838[];
extern s32 D_800A73F8[];
extern s32 D_800A7844[];
extern s32 D_800A744C[];
extern s32 D_800A7850[];
extern s32 D_800A74A0[];
extern s32 D_800A785C[];
extern s32 D_800A74F4[];
extern s32 D_800A7868[];
extern s32 D_800A7548[];
extern s32 D_800A7874[];
extern s32 D_800A759C[];
extern s32 D_800A7880[];
extern s32 D_800A75F0[];
extern s32 D_800A788C[];
extern s32 D_800A7644[];
extern s32 D_800A7898[];
extern s32 D_800A7698[];
extern s32 D_800A78A4[];
extern s32 D_800A76EC[];
extern s32 D_800A78B0[];
extern s32 D_800A78C0[];
extern s32 D_800A78D0[];
extern s32 D_800A78E0[];
extern s32 D_800A78F0[];
extern s32 D_800A7740[];
extern s32 D_800A7900[];
extern s32 D_800A7764[];
extern s32 D_800A7910[];
extern s32 D_800A7924[];
extern s32 D_800A7938[];
extern s32 D_800A794C[];
extern s32 D_800A7960[];
extern s32 D_800A7974[];
extern s32 D_800A7988[];
extern s32 D_800A799C[];
extern s32 D_800A79B0[];
extern s32 D_800A79C4[];
extern s32 D_800A79D8[];
extern s32 D_800A79EC[];
extern s32 D_800A7A00[];
extern s32 D_800A7A14[];
extern s32 D_800A7A28[];
extern s32 D_800A7A3C[];
extern s32 D_800A7A50[];
extern s32 D_800A7A64[];
extern s32 D_800A7A78[];
extern s32 D_800A7A8C[];
extern s32 D_800A7AA0[];
extern s32 D_800A7AB4[];
extern s32 D_800A7AC8[];
extern s32 D_800A7ADC[];
extern s32 D_800A7AF0[];
extern s32 D_800A7B04[];
extern s32 D_800A7B18[];
extern s32 D_800A7B2C[];
extern s32 D_800A7C14[];
extern s32 D_800A7C20[];
extern s32 D_800A7C2C[];
extern s32 D_800A7C38[];
extern s32 D_800A7C44[];
extern s32 D_800A7C50[];
extern s32 D_800A7C5C[];
extern s32 D_800A7C68[];
extern s32 D_800A7C98[];
extern s32 D_800A7CA4[];
extern s32 D_800A7CB0[];
extern s32 D_800A7CBC[];
extern s32 D_800A7CC8[];
extern s32 D_800A7CD4[];
extern s32 D_800A7CE0[];
extern s32 D_800A7CEC[];
extern s32 D_800A7D1C[];
extern s32 D_800A7D28[];
extern s32 D_800A7D34[];
extern s32 D_800A7D40[];
extern s32 D_800A7D4C[];
extern s32 D_800A7D58[];
extern s32 D_800A7D64[];
extern s32 D_800A7D70[];
extern s32 D_800A7DA0[];
extern s32 D_800A7DAC[];
extern s32 D_800A7DB8[];
extern s32 D_800A7DC4[];
extern s32 D_800A7DD0[];
extern s32 D_800A7DDC[];
extern s32 D_800A7DE8[];
extern s32 D_800A7DF4[];
extern s32 D_800A7E24[];
extern s32 D_800A7E30[];
extern s32 D_800A7E3C[];
extern s32 D_800A7E48[];
extern s32 D_800A7E54[];
extern s32 D_800A7E60[];
extern s32 D_800A7E6C[];
extern s32 D_800A7E78[];
extern s32 D_800A7EA8[];
extern s32 D_800A7EB4[];
extern s32 D_800A7EC0[];
extern s32 D_800A7ECC[];
extern s32 D_800A7ED8[];
extern s32 D_800A7EE4[];
extern s32 D_800A7EF0[];
extern s32 D_800A7EFC[];
extern s32 D_800A7F2C[];
extern s32 D_800A7F38[];
extern s32 D_800A7F44[];
extern s32 D_800A7F50[];
extern s32 D_800A7F5C[];
extern s32 D_800A7F68[];
extern s32 D_800A7F74[];
extern s32 D_800A7F80[];
extern s32 D_800A7FB0[];
extern s32 D_800A7FBC[];
extern s32 D_800A7FC8[];
extern s32 D_800A7FD4[];
extern s32 D_800A7FE0[];
extern s32 D_800A7FEC[];
extern s32 D_800A7FF8[];
extern s32 D_800A8004[];
extern s32 D_800A8034[];
extern s32 D_800A8040[];
extern s32 D_800A804C[];
extern s32 D_800A8058[];
extern s32 D_800A8064[];
extern s32 D_800A8070[];
extern s32 D_800A807C[];
extern s32 D_800A8088[];
extern s32 D_800A80B8[];
extern s32 D_800A80C4[];
extern s32 D_800A80D0[];
extern s32 D_800A80DC[];
extern s32 D_800A80E8[];
extern s32 D_800A80F4[];
extern s32 D_800A8100[];
extern s32 D_800A810C[];
extern s32 D_800A813C[];
extern s32 D_800A8148[];
extern s32 D_800A8154[];
extern s32 D_800A8160[];
extern s32 D_800A816C[];
extern s32 D_800A8178[];
extern s32 D_800A8184[];
extern s32 D_800A8190[];
extern s32 D_800A81C0[];
extern s32 D_800A81CC[];
extern s32 D_800A81D8[];
extern s32 D_800A81E4[];
extern s32 D_800A81F0[];
extern s32 D_800A81FC[];
extern s32 D_800A8208[];
extern s32 D_800A8214[];
extern s32 D_800A8244[];
extern s32 D_800A8250[];
extern s32 D_800A825C[];
extern s32 D_800A8268[];
extern s32 D_800A8274[];
extern s32 D_800A8280[];
extern s32 D_800A828C[];
extern s32 D_800A8298[];
extern s32 D_800A82C8[];
extern s32 D_800A82D4[];
extern s32 D_800A82E0[];
extern s32 D_800A82EC[];
extern s32 D_800A82F8[];
extern s32 D_800A8304[];
extern s32 D_800A8310[];
extern s32 D_800A831C[];
extern s32 D_800A834C[];
extern s32 D_800A8358[];
extern s32 D_800A8364[];
extern s32 D_800A8370[];
extern s32 D_800A837C[];
extern s32 D_800A8388[];
extern s32 D_800A8394[];
extern s32 D_800A83A0[];
extern s32 D_800A83D0[];
extern s32 D_800A83DC[];
extern s32 D_800A83E8[];
extern s32 D_800A83F4[];
extern s32 D_800A8400[];
extern s32 D_800A840C[];
extern s32 D_800A8418[];
extern s32 D_800A8424[];
extern s32 D_800A8454[];
extern s32 D_800A8460[];
extern s32 D_800A846C[];
extern s32 D_800A8478[];
extern s32 D_800A8484[];
extern s32 D_800A8490[];
extern s32 D_800A849C[];
extern s32 D_800A84A8[];
extern s32 D_800A84D8[];
extern s32 D_800A84E4[];
extern s32 D_800A84F0[];
extern s32 D_800A84FC[];
extern s32 D_800A8508[];
extern s32 D_800A8514[];
extern s32 D_800A8520[];
extern s32 D_800A852C[];
extern s32 D_800A855C[];
extern s32 D_800A8568[];
extern s32 D_800A8574[];
extern s32 D_800A8580[];
extern s32 D_800A858C[];
extern s32 D_800A8598[];
extern s32 D_800A85A4[];
extern s32 D_800A85B0[];
extern s32 D_800A85E0[];
extern s32 D_800A85EC[];
extern s32 D_800A85F8[];
extern s32 D_800A8604[];
extern s32 D_800A8610[];
extern s32 D_800A861C[];
extern s32 D_800A8628[];
extern s32 D_800A8634[];
extern s32 D_800A8664[];
extern s32 D_800A8670[];
extern s32 D_800A867C[];
extern s32 D_800A8688[];
extern s32 D_800A8694[];
extern s32 D_800A86A0[];
extern s32 D_800A86AC[];
extern s32 D_800A86B8[];
extern s32 D_800A86E8[];
extern s32 D_800A86F4[];
extern s32 D_800A8700[];
extern s32 D_800A870C[];
extern s32 D_800A8718[];
extern s32 D_800A8724[];
extern s32 D_800A8730[];
extern s32 D_800A873C[];
extern s32 D_800A876C[];
extern s32 D_800A8778[];
extern s32 D_800A8784[];
extern s32 D_800A8790[];
extern s32 D_800A879C[];
extern s32 D_800A87A8[];
extern s32 D_800A87B4[];
extern s32 D_800A87C0[];
extern s32 D_800A87F0[];
extern s32 D_800A87FC[];
extern s32 D_800A8808[];
extern s32 D_800A8814[];
extern s32 D_800A8820[];
extern s32 D_800A882C[];
extern s32 D_800A8838[];
extern s32 D_800A8844[];
extern s32 D_800A7C74[];
extern s32 D_800A7CF8[];
extern s32 D_800A7D7C[];
extern s32 D_800A7E00[];
extern s32 D_800A7E84[];
extern s32 D_800A7F08[];
extern s32 D_800A7F8C[];
extern s32 D_800A8010[];
extern s32 D_800A8094[];
extern s32 D_800A8118[];
extern s32 D_800A819C[];
extern s32 D_800A8220[];
extern s32 D_800A82A4[];
extern s32 D_800A8328[];
extern s32 D_800A83AC[];
extern s32 D_800A8430[];
extern s32 D_800A84B4[];
extern s32 D_800A8538[];
extern s32 D_800A85BC[];
extern s32 D_800A8640[];
extern s32 D_800A86C4[];
extern s32 D_800A8748[];
extern s32 D_800A87CC[];
extern s32 D_800A8850[];

StagePoint D_800A60DC = { 0x2ED, 1, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A60EC = { 0x2EC, 1, 2, 240, 0x1D8, 5, &D_800A60DC };
StagePoints D_800A60FC = { 1, 1, &D_800A60EC };
StagePoint D_800A6104 = { 0x2EC, 1, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A6114 = { 0x2ED, 1, 2, 0x350, 0x1F8, 5, &D_800A6104 };
StagePoints D_800A6124 = { 1, 2, &D_800A6114 };
StagePoint D_800A612C = { 0x2ED, 1, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A613C = { 0x2ED, 1, 3, 224, 192, 5, &D_800A612C };
StagePoints D_800A614C = { 1, 3, &D_800A613C };
StagePoint D_800A6154 = { 0x2EE, 1, 2, 0x130, 200, 1, NULL };
StagePoint D_800A6164 = { 0x2ED, 1, 3, 0x350, 0x1F8, 5, &D_800A6154 };
StagePoints D_800A6174 = { 1, 4, &D_800A6164 };
StagePoint D_800A617C = { 0x2EE, 1, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A618C = { 0x2ED, 1, 4, 224, 192, 5, &D_800A617C };
StagePoints D_800A619C = { 1, 5, &D_800A618C };
StagePoint D_800A61A4 = { 0x2ED, 1, 5, 0x3A0, 128, 1, NULL };
StagePoint D_800A61B4 = { 0x2EE, 1, 3, 224, 0x240, 5, &D_800A61A4 };
StagePoints D_800A61C4 = { 1, 6, &D_800A61B4 };
StagePoint D_800A61CC = { 0x2EE, 1, 4, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A61DC = { 0x2EC, 1, 8, 240, 0x1D8, 5, &D_800A61CC };
StagePoints D_800A61EC = { 1, 7, &D_800A61DC };
StagePoint D_800A61F4 = { 0x2EC, 1, 7, 0x3B0, 120, 1, NULL };
StagePoint D_800A6204 = { 0x2E8, 1, 2, 176, 0x168, 5, &D_800A61F4 };
StagePoints D_800A6214 = { 1, 8, &D_800A6204 };
StagePoint D_800A621C = { 0x2EE, 2, 6, 0x130, 200, 1, NULL };
StagePoint D_800A622C = { 0x2EE, 2, 3, 224, 0x240, 5, &D_800A621C };
StagePoints D_800A623C = { 2, 1, &D_800A622C };
StagePoint D_800A6244 = { 0x2EE, 2, 6, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6254 = { 0x2EE, 2, 4, 224, 0x240, 5, &D_800A6244 };
StagePoints D_800A6264 = { 2, 2, &D_800A6254 };
StagePoint D_800A626C = { 0x2ED, 3, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A627C = { 0x2EC, 4, 6, 240, 0x1D8, 5, &D_800A626C };
StagePoints D_800A628C = { 3, 1, &D_800A627C };
StagePoint D_800A6294 = { 0x2EE, 3, 1, 0x130, 200, 1, NULL };
StagePoint D_800A62A4 = { 0x2E8, 3, 1, 176, 0x168, 5, &D_800A6294 };
StagePoints D_800A62B4 = { 3, 2, &D_800A62A4 };
StagePoint D_800A62BC = { 0x2EE, 3, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A62CC = { 0x2ED, 3, 1, 224, 192, 5, &D_800A62BC };
StagePoints D_800A62DC = { 3, 3, &D_800A62CC };
StagePoint D_800A62E4 = { 0x2EE, 3, 2, 0x130, 200, 1, NULL };
StagePoint D_800A62F4 = { 0x2ED, 3, 2, 224, 192, 5, &D_800A62E4 };
StagePoints D_800A6304 = { 3, 4, &D_800A62F4 };
StagePoint D_800A630C = { 0x2EC, 3, 7, 0x3B0, 120, 1, NULL };
StagePoint D_800A631C = { 0x2EE, 3, 1, 224, 0x240, 5, &D_800A630C };
StagePoints D_800A632C = { 3, 5, &D_800A631C };
StagePoint D_800A6334 = { 0x2EE, 3, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6344 = { 0x2ED, 3, 3, 0x350, 0x1F8, 5, &D_800A6334 };
StagePoints D_800A6354 = { 3, 6, &D_800A6344 };
StagePoint D_800A635C = { 0x2EE, 3, 4, 0x130, 200, 1, NULL };
StagePoint D_800A636C = { 0x2EC, 3, 5, 240, 0x1D8, 5, &D_800A635C };
StagePoints D_800A637C = { 3, 7, &D_800A636C };
StagePoint D_800A6384 = { 0x2EE, 3, 5, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6394 = { 0x2EE, 3, 3, 224, 0x240, 5, &D_800A6384 };
StagePoints D_800A63A4 = { 3, 8, &D_800A6394 };
StagePoint D_800A63AC = { 0x2EE, 4, 1, 0x130, 200, 1, NULL };
StagePoint D_800A63BC = { 0x2E8, 4, 1, 176, 0x168, 5, &D_800A63AC };
StagePoints D_800A63CC = { 4, 1, &D_800A63BC };
StagePoint D_800A63D4 = { 0x2EE, 4, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A63E4 = { 0x2ED, 4, 1, 224, 192, 5, &D_800A63D4 };
StagePoints D_800A63F4 = { 4, 2, &D_800A63E4 };
StagePoint D_800A63FC = { 0x2ED, 4, 2, 0x3A0, 128, 1, NULL };
StagePoint D_800A640C = { 0x2ED, 4, 1, 0x350, 0x1F8, 5, &D_800A63FC };
StagePoints D_800A641C = { 4, 3, &D_800A640C };
StagePoint D_800A6424 = { 0x2EE, 4, 2, 0x130, 200, 1, NULL };
StagePoint D_800A6434 = { 0x2ED, 4, 2, 224, 192, 5, &D_800A6424 };
StagePoints D_800A6444 = { 4, 4, &D_800A6434 };
StagePoint D_800A644C = { 0x2EE, 4, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A645C = { 0x2ED, 4, 2, 0x350, 0x1F8, 5, &D_800A644C };
StagePoints D_800A646C = { 4, 5, &D_800A645C };
StagePoint D_800A6474 = { 0x2EC, 3, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A6484 = { 0x2ED, 4, 3, 224, 192, 5, &D_800A6474 };
StagePoints D_800A6494 = { 4, 6, &D_800A6484 };
StagePoint D_800A649C = { 0x2EE, 4, 3, 0x130, 200, 1, NULL };
StagePoint D_800A64AC = { 0x2ED, 4, 3, 0x350, 0x1F8, 5, &D_800A649C };
StagePoints D_800A64BC = { 4, 7, &D_800A64AC };
StagePoint D_800A64C4 = { 0x2ED, 5, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A64D4 = { 0x2ED, 5, 1, 224, 192, 5, &D_800A64C4 };
StagePoints D_800A64E4 = { 5, 1, &D_800A64D4 };
StagePoint D_800A64EC = { 0x2EE, 5, 1, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A64FC = { 0x2ED, 5, 2, 224, 192, 5, &D_800A64EC };
StagePoints D_800A650C = { 5, 2, &D_800A64FC };
StagePoint D_800A6514 = { 0x2ED, 5, 6, 0x3A0, 128, 1, NULL };
StagePoint D_800A6524 = { 0x2ED, 5, 4, 0x350, 0x1F8, 5, &D_800A6514 };
StagePoints D_800A6534 = { 5, 3, &D_800A6524 };
StagePoint D_800A653C = { 0x2EE, 5, 4, 0x130, 200, 1, NULL };
StagePoint D_800A654C = { 0x2EE, 5, 3, 224, 0x240, 5, &D_800A653C };
StagePoints D_800A655C = { 5, 4, &D_800A654C };
StagePoint D_800A6564 = { 0x2EE, 5, 5, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6574 = { 0x2EE, 5, 4, 224, 0x240, 5, &D_800A6564 };
StagePoints D_800A6584 = { 5, 5, &D_800A6574 };
StagePoint D_800A658C = { 0x2ED, 6, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A659C = { 0x2EE, 5, 2, 224, 0x240, 5, &D_800A658C };
StagePoints D_800A65AC = { 6, 1, &D_800A659C };
StagePoint D_800A65B4 = { 0x2ED, 6, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A65C4 = { 0x2ED, 6, 1, 224, 192, 5, &D_800A65B4 };
StagePoints D_800A65D4 = { 6, 2, &D_800A65C4 };
StagePoint D_800A65DC = { 0x2EE, 6, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A65EC = { 0x2ED, 6, 2, 0x350, 0x1F8, 5, &D_800A65DC };
StagePoints D_800A65FC = { 6, 3, &D_800A65EC };
StagePoint D_800A6604 = { 0x2EE, 6, 6, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6614 = { 0x2EE, 5, 5, 224, 0x240, 5, &D_800A6604 };
StagePoints D_800A6624 = { 6, 4, &D_800A6614 };
StagePoints *D_800A662C[] = {
    &D_800A60FC, &D_800A6124, &D_800A614C, &D_800A6174,
    &D_800A619C, &D_800A61C4, &D_800A61EC, &D_800A6214,
    &D_800A623C, &D_800A6264, &D_800A628C, &D_800A62B4,
    &D_800A62DC, &D_800A6304, &D_800A632C, &D_800A6354,
    &D_800A637C, &D_800A63A4, &D_800A63CC, &D_800A63F4,
    &D_800A641C, &D_800A6444, &D_800A646C, &D_800A6494,
    &D_800A64BC, &D_800A64E4, &D_800A650C, &D_800A6534,
    &D_800A655C, &D_800A6584, &D_800A65AC, &D_800A65D4,
    &D_800A65FC, &D_800A6624, NULL,
};
s32 D_800A66B8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1000178, 224, 0x1FF0140,
    0x1000140, 0x1200178, 0x2000E0, 0x1FF0150,
    0x1000140, 0x1400172, 0x4000C8, 0x1FF0160,
    0x1000140, 0x140015A, 0x400068, 0x1FF0170,
    0x1000140, 0x140014E, 0x400038, 0x1FE0140,
    0x1000140, 0x1000140, 0, 0x1FE0150,
    0x1000140, 0x1400162, 0x400088, 0x1FE0160,
    0x1000140, 0x140016A, 0x4000A8, 0x1FE0170,
    0x1000140, 0x1000154, 80, 0x1FD0140,
    0x1000140, 0x1000168, 160, 0x1FD0150,
    0x1000140, 0x1400140, 0x400000, 0x1FD0160,
};
s32 D_800A67C8[] = {
    0x10278, 0x18472, 65535,
};
s32 D_800A67D4[] = {
    0x1027B, 0x18666, 65535,
};
s32 D_800A67E0[] = {
    0x1027C, 0x1868D, 65535,
};
s32 D_800A67EC[] = {
    33170, 65535,
};
s32 D_800A67F4[] = {
    0, 0x18192, 65535,
};
s32 D_800A6800[] = {
    0x10000, 65535,
};
s32 D_800A6808[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6818[] = {
    0x17817, 65535,
};
s32 D_800A6820[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6834[] = {
    17, 0, 65535,
};
s32 D_800A6840[] = {
    37395, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6858[] = {
    0x19213, 16, 17, 0,
    65535,
};
s32 D_800A686C[] = {
    0x19213, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6884[] = {
    16, 17, 0, 65535,
};
s32 D_800A6894[] = {
    33170, 65535,
};
s32 D_800A689C[] = {
    0x18192, 1, 65535,
};
s32 D_800A68A8[] = {
    0x10001, 65535,
};
s32 D_800A68B0[] = {
    17, 0x10001, 0x18192, 65535,
};
s32 D_800A68C0[] = {
    0x1781A, 65535,
};
s32 D_800A68C8[] = {
    16, 0x10011, 0x10001, 0x18192,
    65535,
};
s32 D_800A68DC[] = {
    17, 1, 65535,
};
s32 D_800A68E8[] = {
    37377, 0x10010, 0x10011, 0x10001,
    0x18192, 65535,
};
s32 D_800A6900[] = {
    0x19201, 16, 17, 1,
    65535,
};
s32 D_800A6914[] = {
    0x19201, 0x10010, 0x10011, 0x10001,
    0x18192, 65535,
};
s32 D_800A692C[] = {
    16, 17, 1, 65535,
};
s32 D_800A693C[] = {
    33170, 65535,
};
s32 D_800A6944[] = {
    0, 0x18192, 65535,
};
s32 D_800A6950[] = {
    0x10000, 65535,
};
s32 D_800A6958[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6968[] = {
    0x17806, 65535,
};
s32 D_800A6970[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6984[] = {
    17, 0, 65535,
};
s32 D_800A6990[] = {
    37389, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A69A8[] = {
    0x1920D, 16, 17, 0,
    65535,
};
s32 D_800A69BC[] = {
    0x1920D, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A69D4[] = {
    16, 17, 0, 65535,
};
s32 D_800A69E4[] = {
    33170, 65535,
};
s32 D_800A69EC[] = {
    0, 0x18192, 65535,
};
s32 D_800A69F8[] = {
    0x10000, 65535,
};
s32 D_800A6A00[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6A10[] = {
    0x17821, 65535,
};
s32 D_800A6A18[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6A2C[] = {
    17, 0, 65535,
};
s32 D_800A6A38[] = {
    37401, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6A50[] = {
    0x19219, 16, 17, 0,
    65535,
};
s32 D_800A6A64[] = {
    0x19219, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6A7C[] = {
    16, 17, 0, 65535,
};
s32 D_800A6A8C[] = {
    33170, 65535,
};
s32 D_800A6A94[] = {
    0, 0x18192, 65535,
};
s32 D_800A6AA0[] = {
    0x10000, 65535,
};
s32 D_800A6AA8[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6AB8[] = {
    0x17811, 65535,
};
s32 D_800A6AC0[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6AD4[] = {
    17, 0, 65535,
};
s32 D_800A6AE0[] = {
    37383, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6AF8[] = {
    0x19207, 16, 17, 0,
    65535,
};
s32 D_800A6B0C[] = {
    0x19207, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6B24[] = {
    0, 16, 17, 65535,
};
s32 D_800A6B34[] = {
    33170, 65535,
};
s32 D_800A6B3C[] = {
    0, 0x18192, 65535,
};
s32 D_800A6B48[] = {
    0x10000, 65535,
};
s32 D_800A6B50[] = {
    0x10000, 17, 0x18192, 65535,
};
s32 D_800A6B60[] = {
    0x1764A, 65535,
};
s32 D_800A6B68[] = {
    0x10000, 0x10011, 16, 0x18192,
    65535,
};
s32 D_800A6B7C[] = {
    0, 17, 65535,
};
s32 D_800A6B88[] = {
    0x10000, 0x10011, 0x10010, 37409,
    0x18192, 65535,
};
s32 D_800A6BA0[] = {
    0, 17, 16, 0x19221,
    65535,
};
s32 D_800A6BB4[] = {
    0x10000, 0x10011, 0x10010, 0x19221,
    0x18192, 65535,
};
s32 D_800A6BCC[] = {
    0, 17, 16, 65535,
};
s32 D_800A6BDC[] = {
    33170, 65535,
};
s32 D_800A6BE4[] = {
    0, 0x18192, 65535,
};
s32 D_800A6BF0[] = {
    0x10000, 65535,
};
s32 D_800A6BF8[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6C08[] = {
    0x17648, 65535,
};
s32 D_800A6C10[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6C24[] = {
    17, 0, 65535,
};
s32 D_800A6C30[] = {
    37410, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6C48[] = {
    0x19222, 16, 17, 0,
    65535,
};
s32 D_800A6C5C[] = {
    0x19222, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6C74[] = {
    16, 17, 0, 65535,
};
s32 D_800A6C84[] = {
    33170, 65535,
};
s32 D_800A6C8C[] = {
    0, 0x18192, 65535,
};
s32 D_800A6C98[] = {
    0x10000, 65535,
};
s32 D_800A6CA0[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6CB0[] = {
    0x17649, 65535,
};
s32 D_800A6CB8[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6CCC[] = {
    17, 0, 65535,
};
s32 D_800A6CD8[] = {
    37411, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6CF0[] = {
    0x19223, 16, 17, 0,
    65535,
};
s32 D_800A6D04[] = {
    0x19223, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6D1C[] = {
    16, 17, 0, 65535,
};
s32 D_800A6D2C[] = {
    33170, 65535,
};
s32 D_800A6D34[] = {
    0, 0x18192, 65535,
};
s32 D_800A6D40[] = {
    0x10000, 65535,
};
s32 D_800A6D48[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6D58[] = {
    0x1764B, 65535,
};
s32 D_800A6D60[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6D74[] = {
    17, 0, 65535,
};
s32 D_800A6D80[] = {
    37407, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6D98[] = {
    0x1921F, 16, 17, 0,
    65535,
};
s32 D_800A6DAC[] = {
    0x1921F, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6DC4[] = {
    16, 17, 0, 65535,
};
s32 D_800A6DD4[] = {
    33170, 65535,
};
s32 D_800A6DDC[] = {
    0, 0x18192, 65535,
};
s32 D_800A6DE8[] = {
    0x10000, 65535,
};
s32 D_800A6DF0[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6E00[] = {
    0x17647, 65535,
};
s32 D_800A6E08[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6E1C[] = {
    17, 0, 65535,
};
s32 D_800A6E28[] = {
    37408, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6E40[] = {
    0x19220, 16, 17, 0,
    65535,
};
s32 D_800A6E54[] = {
    0x19220, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6E6C[] = {
    17, 0, 16, 65535,
};
s32 D_800A6E7C[] = {
    33170, 65535,
};
s32 D_800A6E84[] = {
    1, 0x18192, 65535,
};
s32 D_800A6E90[] = {
    0x10001, 65535,
};
s32 D_800A6E98[] = {
    17, 0x10001, 0x18192, 65535,
};
s32 D_800A6EA8[] = {
    0x1764F, 65535,
};
s32 D_800A6EB0[] = {
    0x10011, 0x10001, 0x18192, 16,
    65535,
};
s32 D_800A6EC4[] = {
    17, 1, 65535,
};
s32 D_800A6ED0[] = {
    37617, 0x10010, 0x10011, 0x10001,
    0x18192, 65535,
};
s32 D_800A6EE8[] = {
    0x192F1, 16, 17, 1,
    65535,
};
s32 D_800A6EFC[] = {
    0x192F1, 0x10010, 0x10011, 0x10001,
    0x18192, 65535,
};
s32 D_800A6F14[] = {
    17, 1, 16, 65535,
};
s32 D_800A6F24[] = {
    33170, 65535,
};
s32 D_800A6F2C[] = {
    0, 0x18192, 65535,
};
s32 D_800A6F38[] = {
    0x10000, 65535,
};
s32 D_800A6F40[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6F50[] = {
    0x1764E, 65535,
};
s32 D_800A6F58[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A6F6C[] = {
    17, 0, 65535,
};
s32 D_800A6F78[] = {
    0x10010, 0x10011, 0x10000, 0x18192,
    37445, 65535,
};
s32 D_800A6F90[] = {
    0x19245, 17, 16, 0,
    65535,
};
s32 D_800A6FA4[] = {
    0x19245, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A6FBC[] = {
    16, 17, 0, 65535,
};
s32 D_800A6FCC[] = {
    33170, 65535,
};
s32 D_800A6FD4[] = {
    0, 0x18192, 65535,
};
s32 D_800A6FE0[] = {
    0x10000, 65535,
};
s32 D_800A6FE8[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A6FF8[] = {
    0x1764D, 65535,
};
s32 D_800A7000[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A7014[] = {
    17, 0, 65535,
};
s32 D_800A7020[] = {
    37531, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A7038[] = {
    0x1929B, 16, 17, 0,
    65535,
};
s32 D_800A704C[] = {
    0x1929B, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A7064[] = {
    16, 17, 0, 65535,
};
s32 D_800A7074[] = {
    33170, 65535,
};
s32 D_800A707C[] = {
    0, 0x18192, 65535,
};
s32 D_800A7088[] = {
    0x10000, 65535,
};
s32 D_800A7090[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A70A0[] = {
    0x1764C, 65535,
};
s32 D_800A70A8[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A70BC[] = {
    17, 0, 65535,
};
s32 D_800A70C8[] = {
    37574, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A70E0[] = {
    0x192C6, 16, 17, 0,
    65535,
};
s32 D_800A70F4[] = {
    0x192C6, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A710C[] = {
    16, 17, 0, 65535,
};
s32 D_800A711C[] = {
    33170, 65535,
};
s32 D_800A7124[] = {
    0, 0x18192, 65535,
};
s32 D_800A7130[] = {
    0x10000, 65535,
};
s32 D_800A7138[] = {
    17, 0x10000, 0x18192, 65535,
};
s32 D_800A7148[] = {
    0x17650, 65535,
};
s32 D_800A7150[] = {
    16, 0x10011, 0x10000, 0x18192,
    65535,
};
s32 D_800A7164[] = {
    17, 0, 65535,
};
s32 D_800A7170[] = {
    37488, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A7188[] = {
    0x19270, 16, 17, 0,
    65535,
};
s32 D_800A719C[] = {
    0x19270, 0x10010, 0x10011, 0x10000,
    0x18192, 65535,
};
s32 D_800A71B4[] = {
    16, 17, 0, 65535,
};
s32 D_800A71C4[] = {
    0, 65535,
};
s32 D_800A71CC[] = {
    0x10000, 65535,
};
s32 D_800A71D4[] = {
    0x10000, 65535,
};
s32 D_800A71DC[] = {
    0x17400, 0x10A10, 65535,
};
s32 D_800A71E8[] = {
    0, 65535,
};
s32 D_800A71F0[] = {
    0x10000, 65535,
};
s32 D_800A71F8[] = {
    0x10000, 65535,
};
s32 D_800A7200[] = {
    0x10A13, 0x17401, 65535,
};
s32 D_800A720C[] = {
    0, (s32)D_800A67C8, 16, 0,
    0, 0,
};
s32 D_800A7224[] = {
    0, (s32)D_800A67D4, 19, 0,
    0, 0,
};
s32 D_800A723C[] = {
    0, (s32)D_800A67E0, 20, 0,
    0, 0,
};
s32 D_800A7254[] = {
    (s32)D_800A67EC, 0, 266, (s32)D_800A67F4,
    (s32)D_800A6800, 266, (s32)D_800A6808, (s32)D_800A6818,
    270, (s32)D_800A6820, (s32)D_800A6834, 273,
    (s32)D_800A6840, (s32)D_800A6858, 290, (s32)D_800A686C,
    (s32)D_800A6884, 276, 0, 0,
    0,
};
s32 D_800A72A8[] = {
    (s32)D_800A6894, 0, 263, (s32)D_800A689C,
    (s32)D_800A68A8, 263, (s32)D_800A68B0, (s32)D_800A68C0,
    270, (s32)D_800A68C8, (s32)D_800A68DC, 273,
    (s32)D_800A68E8, (s32)D_800A6900, 287, (s32)D_800A6914,
    (s32)D_800A692C, 276, 0, 0,
    0,
};
s32 D_800A72FC[] = {
    (s32)D_800A693C, 0, 265, (s32)D_800A6944,
    (s32)D_800A6950, 265, (s32)D_800A6958, (s32)D_800A6968,
    270, (s32)D_800A6970, (s32)D_800A6984, 273,
    (s32)D_800A6990, (s32)D_800A69A8, 289, (s32)D_800A69BC,
    (s32)D_800A69D4, 276, 0, 0,
    0,
};
s32 D_800A7350[] = {
    (s32)D_800A69E4, 0, 267, (s32)D_800A69EC,
    (s32)D_800A69F8, 267, (s32)D_800A6A00, (s32)D_800A6A10,
    270, (s32)D_800A6A18, (s32)D_800A6A2C, 273,
    (s32)D_800A6A38, (s32)D_800A6A50, 291, (s32)D_800A6A64,
    (s32)D_800A6A7C, 276, 0, 0,
    0,
};
s32 D_800A73A4[] = {
    (s32)D_800A6A8C, 0, 264, (s32)D_800A6A94,
    (s32)D_800A6AA0, 264, (s32)D_800A6AA8, (s32)D_800A6AB8,
    270, (s32)D_800A6AC0, (s32)D_800A6AD4, 273,
    (s32)D_800A6AE0, (s32)D_800A6AF8, 288, (s32)D_800A6B0C,
    (s32)D_800A6B24, 276, 0, 0,
    0,
};
s32 D_800A73F8[] = {
    (s32)D_800A6B34, 0, 255, (s32)D_800A6B3C,
    (s32)D_800A6B48, 255, (s32)D_800A6B50, (s32)D_800A6B60,
    268, (s32)D_800A6B68, (s32)D_800A6B7C, 271,
    (s32)D_800A6B88, (s32)D_800A6BA0, 279, (s32)D_800A6BB4,
    (s32)D_800A6BCC, 274, 0, 0,
    0,
};
s32 D_800A744C[] = {
    (s32)D_800A6BDC, 0, 256, (s32)D_800A6BE4,
    (s32)D_800A6BF0, 256, (s32)D_800A6BF8, (s32)D_800A6C08,
    268, (s32)D_800A6C10, (s32)D_800A6C24, 271,
    (s32)D_800A6C30, (s32)D_800A6C48, 280, (s32)D_800A6C5C,
    (s32)D_800A6C74, 274, 0, 0,
    0,
};
s32 D_800A74A0[] = {
    (s32)D_800A6C84, 0, 257, (s32)D_800A6C8C,
    (s32)D_800A6C98, 257, (s32)D_800A6CA0, (s32)D_800A6CB0,
    268, (s32)D_800A6CB8, (s32)D_800A6CCC, 271,
    (s32)D_800A6CD8, (s32)D_800A6CF0, 281, (s32)D_800A6D04,
    (s32)D_800A6D1C, 274, 0, 0,
    0,
};
s32 D_800A74F4[] = {
    (s32)D_800A6D2C, 0, 253, (s32)D_800A6D34,
    (s32)D_800A6D40, 253, (s32)D_800A6D48, (s32)D_800A6D58,
    268, (s32)D_800A6D60, (s32)D_800A6D74, 271,
    (s32)D_800A6D80, (s32)D_800A6D98, 277, (s32)D_800A6DAC,
    (s32)D_800A6DC4, 274, 0, 0,
    0,
};
s32 D_800A7548[] = {
    (s32)D_800A6DD4, 0, 254, (s32)D_800A6DDC,
    (s32)D_800A6DE8, 254, (s32)D_800A6DF0, (s32)D_800A6E00,
    268, (s32)D_800A6E08, (s32)D_800A6E1C, 271,
    (s32)D_800A6E28, (s32)D_800A6E40, 278, (s32)D_800A6E54,
    (s32)D_800A6E6C, 274, 0, 0,
    0,
};
s32 D_800A759C[] = {
    (s32)D_800A6E7C, 0, 262, (s32)D_800A6E84,
    (s32)D_800A6E90, 262, (s32)D_800A6E98, (s32)D_800A6EA8,
    269, (s32)D_800A6EB0, (s32)D_800A6EC4, 272,
    (s32)D_800A6ED0, (s32)D_800A6EE8, 286, (s32)D_800A6EFC,
    (s32)D_800A6F14, 275, 0, 0,
    0,
};
s32 D_800A75F0[] = {
    (s32)D_800A6F24, 0, 258, (s32)D_800A6F2C,
    (s32)D_800A6F38, 258, (s32)D_800A6F40, (s32)D_800A6F50,
    269, (s32)D_800A6F58, (s32)D_800A6F6C, 272,
    (s32)D_800A6F78, (s32)D_800A6F90, 282, (s32)D_800A6FA4,
    (s32)D_800A6FBC, 275, 0, 0,
    0,
};
s32 D_800A7644[] = {
    (s32)D_800A6FCC, 0, 260, (s32)D_800A6FD4,
    (s32)D_800A6FE0, 260, (s32)D_800A6FE8, (s32)D_800A6FF8,
    269, (s32)D_800A7000, (s32)D_800A7014, 272,
    (s32)D_800A7020, (s32)D_800A7038, 284, (s32)D_800A704C,
    (s32)D_800A7064, 275, 0, 0,
    0,
};
s32 D_800A7698[] = {
    (s32)D_800A7074, 0, 261, (s32)D_800A707C,
    (s32)D_800A7088, 261, (s32)D_800A7090, (s32)D_800A70A0,
    269, (s32)D_800A70A8, (s32)D_800A70BC, 272,
    (s32)D_800A70C8, (s32)D_800A70E0, 285, (s32)D_800A70F4,
    (s32)D_800A710C, 275, 0, 0,
    0,
};
s32 D_800A76EC[] = {
    (s32)D_800A711C, 0, 259, (s32)D_800A7124,
    (s32)D_800A7130, 259, (s32)D_800A7138, (s32)D_800A7148,
    269, (s32)D_800A7150, (s32)D_800A7164, 272,
    (s32)D_800A7170, (s32)D_800A7188, 283, (s32)D_800A719C,
    (s32)D_800A71B4, 275, 0, 0,
    0,
};
s32 D_800A7740[] = {
    (s32)D_800A71C4, (s32)D_800A71CC, 245, (s32)D_800A71D4,
    (s32)D_800A71DC, 246, 0, 0,
    0,
};
s32 D_800A7764[] = {
    (s32)D_800A71E8, (s32)D_800A71F0, 251, (s32)D_800A71F8,
    (s32)D_800A7200, 252, 0, 0,
    0,
};
s32 D_800A7788[] = {
    0x17E00, 0x17E25, 632, 65535,
};
s32 D_800A7798[] = {
    0x17E00, 0x17E25, 635, 34406,
    34407, 34408, 34409, 65535,
};
s32 D_800A77B8[] = {
    0x17E00, 0x17E25, 636, 34445,
    34446, 34447, 34448, 65535,
};
s32 D_800A77D8[] = {
    0x17E02, 0x17E20, 65535,
};
s32 D_800A77E4[] = {
    0x17E02, 0x17E24, 65535,
};
s32 D_800A77F0[] = {
    0x17E03, 0x17E1F, 65535,
};
s32 D_800A77FC[] = {
    0x17E03, 0x17E22, 65535,
};
s32 D_800A7808[] = {
    0x17E03, 0x17E24, 65535,
};
s32 D_800A7814[] = {
    0x17E00, 8, 65535,
};
s32 D_800A7820[] = {
    0x17E02, 8, 65535,
};
s32 D_800A782C[] = {
    0x17E04, 8, 65535,
};
s32 D_800A7838[] = {
    0x17E02, 0x17E1F, 65535,
};
s32 D_800A7844[] = {
    0x17E02, 0x17E25, 65535,
};
s32 D_800A7850[] = {
    0x17E03, 0x17E1E, 65535,
};
s32 D_800A785C[] = {
    0x17E03, 0x17E21, 65535,
};
s32 D_800A7868[] = {
    0x17E03, 0x17E23, 65535,
};
s32 D_800A7874[] = {
    0x17E02, 0x17E1E, 65535,
};
s32 D_800A7880[] = {
    0x17E02, 0x17E21, 65535,
};
s32 D_800A788C[] = {
    0x17E02, 0x17E22, 65535,
};
s32 D_800A7898[] = {
    0x17E02, 0x17E23, 65535,
};
s32 D_800A78A4[] = {
    0x17E03, 0x17E20, 65535,
};
s32 D_800A78B0[] = {
    32256, 0x17E1E, 9, 65535,
};
s32 D_800A78C0[] = {
    32256, 0x17E1F, 9, 65535,
};
s32 D_800A78D0[] = {
    32256, 0x17E20, 9, 65535,
};
s32 D_800A78E0[] = {
    32256, 0x17E21, 9, 65535,
};
s32 D_800A78F0[] = {
    0x17E00, 0x17E21, 2576, 65535,
};
s32 D_800A7900[] = {
    0x17E00, 0x17E25, 2579, 65535,
};
s32 D_800A7910[] = {
    (s32)D_800A7788, (s32)D_800A720C, 0x40021, 0x1580320,
    1,
};
s32 D_800A7924[] = {
    (s32)D_800A7798, (s32)D_800A7224, 0x5004D, 0x16002C0,
    1,
};
s32 D_800A7938[] = {
    (s32)D_800A77B8, (s32)D_800A723C, 0x6004E, 0x1100268,
    1,
};
s32 D_800A794C[] = {
    (s32)D_800A77D8, (s32)D_800A7254, 0x700C1, 0xC801C0,
    1,
};
s32 D_800A7960[] = {
    (s32)D_800A77E4, (s32)D_800A72A8, 0x700C1, 0xC801C0,
    1,
};
s32 D_800A7974[] = {
    (s32)D_800A77F0, (s32)D_800A72FC, 0x700C1, 0x1580320,
    1,
};
s32 D_800A7988[] = {
    (s32)D_800A77FC, (s32)D_800A7350, 0x700C1, 0xC801C0,
    1,
};
s32 D_800A799C[] = {
    (s32)D_800A7808, (s32)D_800A73A4, 0x700C1, 0x1CC0378,
    1,
};
s32 D_800A79B0[] = {
    0, 0, 0x80146, 0,
    0,
};
s32 D_800A79C4[] = {
    (s32)D_800A7814, 0, 0x90148, 0x1A002E0,
    1,
};
s32 D_800A79D8[] = {
    (s32)D_800A7820, 0, 0x90148, 0x1C00320,
    1,
};
s32 D_800A79EC[] = {
    (s32)D_800A782C, 0, 0x90148, 0x1A002E0,
    1,
};
s32 D_800A7A00[] = {
    (s32)D_800A7838, (s32)D_800A73F8, 0xA014D, 0xC801C0,
    1,
};
s32 D_800A7A14[] = {
    (s32)D_800A7844, (s32)D_800A744C, 0xA014D, 0x1CC0378,
    1,
};
s32 D_800A7A28[] = {
    (s32)D_800A7850, (s32)D_800A74A0, 0xA014D, 0x1CC0378,
    1,
};
s32 D_800A7A3C[] = {
    (s32)D_800A785C, (s32)D_800A74F4, 0xA014D, 0xC801C0,
    1,
};
s32 D_800A7A50[] = {
    (s32)D_800A7868, (s32)D_800A7548, 0xA014D, 0xC801C0,
    1,
};
s32 D_800A7A64[] = {
    (s32)D_800A7874, (s32)D_800A759C, 0xB0159, 0xC801C0,
    1,
};
s32 D_800A7A78[] = {
    (s32)D_800A7880, (s32)D_800A75F0, 0xB0159, 0xC801C0,
    1,
};
s32 D_800A7A8C[] = {
    (s32)D_800A788C, (s32)D_800A7644, 0xB0159, 0x1CC0378,
    1,
};
s32 D_800A7AA0[] = {
    (s32)D_800A7898, (s32)D_800A7698, 0xB0159, 0x1CC0378,
    1,
};
s32 D_800A7AB4[] = {
    (s32)D_800A78A4, (s32)D_800A76EC, 0xB0159, 0x1580320,
    1,
};
s32 D_800A7AC8[] = {
    (s32)D_800A78B0, 0, 0xC015F, 0xC80310,
    1,
};
s32 D_800A7ADC[] = {
    (s32)D_800A78C0, 0, 0xC015F, 0x1B80130,
    1,
};
s32 D_800A7AF0[] = {
    (s32)D_800A78D0, 0, 0xC015F, 0x980370,
    1,
};
s32 D_800A7B04[] = {
    (s32)D_800A78E0, 0, 0xC015F, 0x11002E0,
    1,
};
s32 D_800A7B18[] = {
    (s32)D_800A78F0, (s32)D_800A7740, 0xD018B, 0x1A801D0,
    7,
};
s32 D_800A7B2C[] = {
    (s32)D_800A7900, (s32)D_800A7764, 0xE018E, 0x1B80250,
    1,
};
s32 D_800A7B40[] = {
    (s32)D_800A7910, (s32)D_800A7924, (s32)D_800A7938, (s32)D_800A794C,
    (s32)D_800A7960, (s32)D_800A7974, (s32)D_800A7988, (s32)D_800A799C,
    (s32)D_800A79B0, (s32)D_800A79C4, (s32)D_800A79D8, (s32)D_800A79EC,
    (s32)D_800A7A00, (s32)D_800A7A14, (s32)D_800A7A28, (s32)D_800A7A3C,
    (s32)D_800A7A50, (s32)D_800A7A64, (s32)D_800A7A78, (s32)D_800A7A8C,
    (s32)D_800A7AA0, (s32)D_800A7AB4, (s32)D_800A7AC8, (s32)D_800A7ADC,
    (s32)D_800A7AF0, (s32)D_800A7B04, (s32)D_800A7B18, (s32)D_800A7B2C,
    0,
};
s32 D_800A7BB4[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A7BC8[] = {
    65535, 65535, 0x2EC0001, 0x7803B0,
    5, 0, 65535, 65535,
    0x2EC0001, 0x1D800F0, 1, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A7C10[])(void) = {
    func_800A5FB0,
};
s32 D_800A7C14[] = {
    38, 10, 0x60080000,
};
s32 D_800A7C20[] = {
    56, 10, 0x60080000,
};
s32 D_800A7C2C[] = {
    107, 10, 0x60080000,
};
s32 D_800A7C38[] = {
    155, 10, 0x60080000,
};
s32 D_800A7C44[] = {
    120, 10, 0x60080000,
};
s32 D_800A7C50[] = {
    181, 10, 0x60080000,
};
s32 D_800A7C5C[] = {
    142, 10, 0x60080000,
};
s32 D_800A7C68[] = {
    143, 10, 0x60080000,
};
s32 D_800A7C74[] = {
    3, (s32)D_800A7C14, (s32)D_800A7C20, (s32)D_800A7C2C,
    (s32)D_800A7C38, (s32)D_800A7C44, (s32)D_800A7C50, (s32)D_800A7C5C,
    (s32)D_800A7C68,
};
s32 D_800A7C98[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CBC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7C98, (s32)D_800A7CA4, (s32)D_800A7CB0,
    (s32)D_800A7CBC, (s32)D_800A7CC8, (s32)D_800A7CD4, (s32)D_800A7CE0,
    (s32)D_800A7CEC,
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
    0, 0, 0x60040000,
};
s32 D_800A7D70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D7C[] = {
    0, (s32)D_800A7D1C, (s32)D_800A7D28, (s32)D_800A7D34,
    (s32)D_800A7D40, (s32)D_800A7D4C, (s32)D_800A7D58, (s32)D_800A7D64,
    (s32)D_800A7D70,
};
s32 D_800A7DA0[] = {
    318, 19, 0x60880000,
};
s32 D_800A7DAC[] = {
    320, 19, 0x60880000,
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
    0, 0, 0x60040000,
};
s32 D_800A7DF4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7E00[] = {
    0, (s32)D_800A7DA0, (s32)D_800A7DAC, (s32)D_800A7DB8,
    (s32)D_800A7DC4, (s32)D_800A7DD0, (s32)D_800A7DDC, (s32)D_800A7DE8,
    (s32)D_800A7DF4,
};
s32 D_800A7E24[] = {
    81, 10, 0x60080000,
};
s32 D_800A7E30[] = {
    81, 10, 0x60080000,
};
s32 D_800A7E3C[] = {
    165, 10, 0x60080000,
};
s32 D_800A7E48[] = {
    165, 10, 0x60080000,
};
s32 D_800A7E54[] = {
    166, 10, 0x60080000,
};
s32 D_800A7E60[] = {
    166, 10, 0x60080000,
};
s32 D_800A7E6C[] = {
    169, 10, 0x60080000,
};
s32 D_800A7E78[] = {
    169, 10, 0x60080000,
};
s32 D_800A7E84[] = {
    3, (s32)D_800A7E24, (s32)D_800A7E30, (s32)D_800A7E3C,
    (s32)D_800A7E48, (s32)D_800A7E54, (s32)D_800A7E60, (s32)D_800A7E6C,
    (s32)D_800A7E78,
};
s32 D_800A7EA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7EC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7ECC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7EA8, (s32)D_800A7EB4, (s32)D_800A7EC0,
    (s32)D_800A7ECC, (s32)D_800A7ED8, (s32)D_800A7EE4, (s32)D_800A7EF0,
    (s32)D_800A7EFC,
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
    0, 0, 0x60040000,
};
s32 D_800A7F80[] = {
    0, 0, 0x60040000,
};
s32 D_800A7F8C[] = {
    0, (s32)D_800A7F2C, (s32)D_800A7F38, (s32)D_800A7F44,
    (s32)D_800A7F50, (s32)D_800A7F5C, (s32)D_800A7F68, (s32)D_800A7F74,
    (s32)D_800A7F80,
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
    0, 0, 0x60040000,
};
s32 D_800A8004[] = {
    0, 0, 0x60040000,
};
s32 D_800A8010[] = {
    0, (s32)D_800A7FB0, (s32)D_800A7FBC, (s32)D_800A7FC8,
    (s32)D_800A7FD4, (s32)D_800A7FE0, (s32)D_800A7FEC, (s32)D_800A7FF8,
    (s32)D_800A8004,
};
s32 D_800A8034[] = {
    136, 10, 0x60080000,
};
s32 D_800A8040[] = {
    136, 10, 0x60080000,
};
s32 D_800A804C[] = {
    137, 10, 0x60080000,
};
s32 D_800A8058[] = {
    137, 10, 0x60080000,
};
s32 D_800A8064[] = {
    183, 10, 0x60080000,
};
s32 D_800A8070[] = {
    183, 10, 0x60080000,
};
s32 D_800A807C[] = {
    118, 10, 0x60080000,
};
s32 D_800A8088[] = {
    118, 10, 0x60080000,
};
s32 D_800A8094[] = {
    3, (s32)D_800A8034, (s32)D_800A8040, (s32)D_800A804C,
    (s32)D_800A8058, (s32)D_800A8064, (s32)D_800A8070, (s32)D_800A807C,
    (s32)D_800A8088,
};
s32 D_800A80B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A80C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A80D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A80DC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A80B8, (s32)D_800A80C4, (s32)D_800A80D0,
    (s32)D_800A80DC, (s32)D_800A80E8, (s32)D_800A80F4, (s32)D_800A8100,
    (s32)D_800A810C,
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
    0, 0, 0x60040000,
};
s32 D_800A8190[] = {
    0, 0, 0x60040000,
};
s32 D_800A819C[] = {
    0, (s32)D_800A813C, (s32)D_800A8148, (s32)D_800A8154,
    (s32)D_800A8160, (s32)D_800A816C, (s32)D_800A8178, (s32)D_800A8184,
    (s32)D_800A8190,
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
    0, 0, 0x60040000,
};
s32 D_800A8214[] = {
    0, 0, 0x60040000,
};
s32 D_800A8220[] = {
    0, (s32)D_800A81C0, (s32)D_800A81CC, (s32)D_800A81D8,
    (s32)D_800A81E4, (s32)D_800A81F0, (s32)D_800A81FC, (s32)D_800A8208,
    (s32)D_800A8214,
};
s32 D_800A8244[] = {
    113, 10, 0x60080000,
};
s32 D_800A8250[] = {
    113, 10, 0x60080000,
};
s32 D_800A825C[] = {
    114, 10, 0x60080000,
};
s32 D_800A8268[] = {
    114, 10, 0x60080000,
};
s32 D_800A8274[] = {
    115, 10, 0x60080000,
};
s32 D_800A8280[] = {
    115, 10, 0x60080000,
};
s32 D_800A828C[] = {
    167, 10, 0x60080000,
};
s32 D_800A8298[] = {
    167, 10, 0x60080000,
};
s32 D_800A82A4[] = {
    3, (s32)D_800A8244, (s32)D_800A8250, (s32)D_800A825C,
    (s32)D_800A8268, (s32)D_800A8274, (s32)D_800A8280, (s32)D_800A828C,
    (s32)D_800A8298,
};
s32 D_800A82C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A82D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A82E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A82EC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A82C8, (s32)D_800A82D4, (s32)D_800A82E0,
    (s32)D_800A82EC, (s32)D_800A82F8, (s32)D_800A8304, (s32)D_800A8310,
    (s32)D_800A831C,
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
    0, 0, 0x60040000,
};
s32 D_800A83A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A83AC[] = {
    0, (s32)D_800A834C, (s32)D_800A8358, (s32)D_800A8364,
    (s32)D_800A8370, (s32)D_800A837C, (s32)D_800A8388, (s32)D_800A8394,
    (s32)D_800A83A0,
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
    0, 0, 0x60040000,
};
s32 D_800A8424[] = {
    0, 0, 0x60040000,
};
s32 D_800A8430[] = {
    0, (s32)D_800A83D0, (s32)D_800A83DC, (s32)D_800A83E8,
    (s32)D_800A83F4, (s32)D_800A8400, (s32)D_800A840C, (s32)D_800A8418,
    (s32)D_800A8424,
};
s32 D_800A8454[] = {
    74, 10, 0x60080000,
};
s32 D_800A8460[] = {
    77, 10, 0x60080000,
};
s32 D_800A846C[] = {
    78, 10, 0x60080000,
};
s32 D_800A8478[] = {
    79, 10, 0x60080000,
};
s32 D_800A8484[] = {
    80, 10, 0x60080000,
};
s32 D_800A8490[] = {
    75, 10, 0x60080000,
};
s32 D_800A849C[] = {
    76, 10, 0x60080000,
};
s32 D_800A84A8[] = {
    89, 10, 0x60080000,
};
s32 D_800A84B4[] = {
    3, (s32)D_800A8454, (s32)D_800A8460, (s32)D_800A846C,
    (s32)D_800A8478, (s32)D_800A8484, (s32)D_800A8490, (s32)D_800A849C,
    (s32)D_800A84A8,
};
s32 D_800A84D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A84E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A84F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A84FC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A84D8, (s32)D_800A84E4, (s32)D_800A84F0,
    (s32)D_800A84FC, (s32)D_800A8508, (s32)D_800A8514, (s32)D_800A8520,
    (s32)D_800A852C,
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
    0, 0, 0x60040000,
};
s32 D_800A85B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A85BC[] = {
    0, (s32)D_800A855C, (s32)D_800A8568, (s32)D_800A8574,
    (s32)D_800A8580, (s32)D_800A858C, (s32)D_800A8598, (s32)D_800A85A4,
    (s32)D_800A85B0,
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
    0, 0, 0x60040000,
};
s32 D_800A8634[] = {
    0, 0, 0x60040000,
};
s32 D_800A8640[] = {
    0, (s32)D_800A85E0, (s32)D_800A85EC, (s32)D_800A85F8,
    (s32)D_800A8604, (s32)D_800A8610, (s32)D_800A861C, (s32)D_800A8628,
    (s32)D_800A8634,
};
s32 D_800A8664[] = {
    162, 10, 0x60080000,
};
s32 D_800A8670[] = {
    162, 10, 0x60080000,
};
s32 D_800A867C[] = {
    162, 10, 0x60080000,
};
s32 D_800A8688[] = {
    162, 10, 0x60080000,
};
s32 D_800A8694[] = {
    135, 10, 0x60080000,
};
s32 D_800A86A0[] = {
    135, 10, 0x60080000,
};
s32 D_800A86AC[] = {
    135, 10, 0x60080000,
};
s32 D_800A86B8[] = {
    135, 10, 0x60080000,
};
s32 D_800A86C4[] = {
    3, (s32)D_800A8664, (s32)D_800A8670, (s32)D_800A867C,
    (s32)D_800A8688, (s32)D_800A8694, (s32)D_800A86A0, (s32)D_800A86AC,
    (s32)D_800A86B8,
};
s32 D_800A86E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A86F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A8700[] = {
    0, 0, 0x60040000,
};
s32 D_800A870C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A86E8, (s32)D_800A86F4, (s32)D_800A8700,
    (s32)D_800A870C, (s32)D_800A8718, (s32)D_800A8724, (s32)D_800A8730,
    (s32)D_800A873C,
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
    0, 0, 0x60040000,
};
s32 D_800A87C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A87CC[] = {
    0, (s32)D_800A876C, (s32)D_800A8778, (s32)D_800A8784,
    (s32)D_800A8790, (s32)D_800A879C, (s32)D_800A87A8, (s32)D_800A87B4,
    (s32)D_800A87C0,
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
    0, 0, 0x60040000,
};
s32 D_800A8844[] = {
    0, 0, 0x60040000,
};
s32 D_800A8850[] = {
    0, (s32)D_800A87F0, (s32)D_800A87FC, (s32)D_800A8808,
    (s32)D_800A8814, (s32)D_800A8820, (s32)D_800A882C, (s32)D_800A8838,
    (s32)D_800A8844,
};
s32 D_800A8874[] = {
    417, 1, 0, (s32)D_800A7C74,
    (s32)D_800A7CF8, (s32)D_800A7D7C, (s32)D_800A7E00, 422,
    2, 0, (s32)D_800A7E84, (s32)D_800A7F08,
    (s32)D_800A7F8C, (s32)D_800A8010, 428, 3,
    0, (s32)D_800A8094, (s32)D_800A8118, (s32)D_800A819C,
    (s32)D_800A8220, 434, 4, 0,
    (s32)D_800A82A4, (s32)D_800A8328, (s32)D_800A83AC, (s32)D_800A8430,
    440, 5, 0, (s32)D_800A84B4,
    (s32)D_800A8538, (s32)D_800A85BC, (s32)D_800A8640, 446,
    6, 0, (s32)D_800A86C4, (s32)D_800A8748,
    (s32)D_800A87CC, (s32)D_800A8850,
};
