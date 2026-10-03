#include "common.h"
#include "stage.h"
void func_800A5EE0();
extern void (*D_800A71D0[])(void);
extern StagePoints *D_800A6884[];

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
        func_800A5DE0(D_800990B4.unk14, D_800A6884, GAME.unk44, GAME.unk46);
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
    D_800A71D0[0]();
    return task;
}

extern s32 D_800A715C[];
extern s32 D_800A7170[];
extern s32 D_800A6914[];
extern s32 D_800A7100[];
extern s32 D_800A7E34[];
void func_800A5FB0(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x698;
    D_800990B4.unkC = 0x94B0004;
    D_800990B4.unk10 = D_800A715C;
    D_800990B4.unk14 = D_800A7170;
    D_800990B4.unk1C = 0x94A;
    D_800990B4.unk2C = (Vec2){0x13B00, 0x21000};
    D_800990B4.unk28 = D_800A6914;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A7100;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A7E34, GAME.unk44);
    D_8009A70C.setFile(0, 0x94B0006);
    D_8009A70C.setFile(7, 0x94B0007);
    D_8009A70C.setFile(4, 0x94B0005);
    D_8009A70C.unk50(0);
}

void func_800A5FB0();
extern StagePoint D_800A60DC;
extern StagePoint D_800A60EC;
extern StagePoint D_800A60FC;
extern StagePoint D_800A6114;
extern StagePoint D_800A6124;
extern StagePoint D_800A6134;
extern StagePoint D_800A614C;
extern StagePoint D_800A615C;
extern StagePoint D_800A616C;
extern StagePoint D_800A6184;
extern StagePoint D_800A6194;
extern StagePoint D_800A61A4;
extern StagePoint D_800A61BC;
extern StagePoint D_800A61CC;
extern StagePoint D_800A61DC;
extern StagePoint D_800A61F4;
extern StagePoint D_800A6204;
extern StagePoint D_800A6214;
extern StagePoint D_800A622C;
extern StagePoint D_800A623C;
extern StagePoint D_800A624C;
extern StagePoint D_800A6264;
extern StagePoint D_800A6274;
extern StagePoint D_800A6284;
extern StagePoint D_800A629C;
extern StagePoint D_800A62AC;
extern StagePoint D_800A62BC;
extern StagePoint D_800A62D4;
extern StagePoint D_800A62E4;
extern StagePoint D_800A62F4;
extern StagePoint D_800A630C;
extern StagePoint D_800A631C;
extern StagePoint D_800A632C;
extern StagePoint D_800A6344;
extern StagePoint D_800A6354;
extern StagePoint D_800A6364;
extern StagePoint D_800A637C;
extern StagePoint D_800A638C;
extern StagePoint D_800A639C;
extern StagePoint D_800A63B4;
extern StagePoint D_800A63C4;
extern StagePoint D_800A63D4;
extern StagePoint D_800A63EC;
extern StagePoint D_800A63FC;
extern StagePoint D_800A640C;
extern StagePoint D_800A6424;
extern StagePoint D_800A6434;
extern StagePoint D_800A6444;
extern StagePoint D_800A645C;
extern StagePoint D_800A646C;
extern StagePoint D_800A647C;
extern StagePoint D_800A6494;
extern StagePoint D_800A64A4;
extern StagePoint D_800A64B4;
extern StagePoint D_800A64CC;
extern StagePoint D_800A64DC;
extern StagePoint D_800A64EC;
extern StagePoint D_800A6504;
extern StagePoint D_800A6514;
extern StagePoint D_800A6524;
extern StagePoint D_800A653C;
extern StagePoint D_800A654C;
extern StagePoint D_800A655C;
extern StagePoint D_800A6574;
extern StagePoint D_800A6584;
extern StagePoint D_800A6594;
extern StagePoint D_800A65AC;
extern StagePoint D_800A65BC;
extern StagePoint D_800A65CC;
extern StagePoint D_800A65E4;
extern StagePoint D_800A65F4;
extern StagePoint D_800A6604;
extern StagePoint D_800A661C;
extern StagePoint D_800A662C;
extern StagePoint D_800A663C;
extern StagePoint D_800A6654;
extern StagePoint D_800A6664;
extern StagePoint D_800A6674;
extern StagePoint D_800A668C;
extern StagePoint D_800A669C;
extern StagePoint D_800A66AC;
extern StagePoint D_800A66C4;
extern StagePoint D_800A66D4;
extern StagePoint D_800A66E4;
extern StagePoint D_800A66FC;
extern StagePoint D_800A670C;
extern StagePoint D_800A671C;
extern StagePoint D_800A6734;
extern StagePoint D_800A6744;
extern StagePoint D_800A6754;
extern StagePoint D_800A676C;
extern StagePoint D_800A677C;
extern StagePoint D_800A678C;
extern StagePoint D_800A67A4;
extern StagePoint D_800A67B4;
extern StagePoint D_800A67C4;
extern StagePoint D_800A67DC;
extern StagePoint D_800A67EC;
extern StagePoint D_800A67FC;
extern StagePoint D_800A6814;
extern StagePoint D_800A6824;
extern StagePoint D_800A6834;
extern StagePoint D_800A684C;
extern StagePoint D_800A685C;
extern StagePoint D_800A686C;
extern StagePoints D_800A610C;
extern StagePoints D_800A6144;
extern StagePoints D_800A617C;
extern StagePoints D_800A61B4;
extern StagePoints D_800A61EC;
extern StagePoints D_800A6224;
extern StagePoints D_800A625C;
extern StagePoints D_800A6294;
extern StagePoints D_800A62CC;
extern StagePoints D_800A6304;
extern StagePoints D_800A633C;
extern StagePoints D_800A6374;
extern StagePoints D_800A63AC;
extern StagePoints D_800A63E4;
extern StagePoints D_800A641C;
extern StagePoints D_800A6454;
extern StagePoints D_800A648C;
extern StagePoints D_800A64C4;
extern StagePoints D_800A64FC;
extern StagePoints D_800A6534;
extern StagePoints D_800A656C;
extern StagePoints D_800A65A4;
extern StagePoints D_800A65DC;
extern StagePoints D_800A6614;
extern StagePoints D_800A664C;
extern StagePoints D_800A6684;
extern StagePoints D_800A66BC;
extern StagePoints D_800A66F4;
extern StagePoints D_800A672C;
extern StagePoints D_800A6764;
extern StagePoints D_800A679C;
extern StagePoints D_800A67D4;
extern StagePoints D_800A680C;
extern StagePoints D_800A6844;
extern StagePoints D_800A687C;
extern s32 D_800A6A04[];
extern s32 D_800A6A0C[];
extern s32 D_800A6A18[];
extern s32 D_800A6A20[];
extern s32 D_800A6A30[];
extern s32 D_800A6A40[];
extern s32 D_800A6A50[];
extern s32 D_800A6A58[];
extern s32 D_800A6A64[];
extern s32 D_800A6A6C[];
extern s32 D_800A6A7C[];
extern s32 D_800A6A8C[];
extern s32 D_800A6A9C[];
extern s32 D_800A6AA4[];
extern s32 D_800A6AB0[];
extern s32 D_800A6AB8[];
extern s32 D_800A6AC8[];
extern s32 D_800A6AD8[];
extern s32 D_800A6AE8[];
extern s32 D_800A6AF0[];
extern s32 D_800A6AFC[];
extern s32 D_800A6B04[];
extern s32 D_800A6B14[];
extern s32 D_800A6B24[];
extern s32 D_800A6B34[];
extern s32 D_800A6B3C[];
extern s32 D_800A6B48[];
extern s32 D_800A6B50[];
extern s32 D_800A6B60[];
extern s32 D_800A6B70[];
extern s32 D_800A6B80[];
extern s32 D_800A6B88[];
extern s32 D_800A6B94[];
extern s32 D_800A6B9C[];
extern s32 D_800A6BAC[];
extern s32 D_800A6BBC[];
extern s32 D_800A6BCC[];
extern s32 D_800A6BD4[];
extern s32 D_800A6BE0[];
extern s32 D_800A6BE8[];
extern s32 D_800A6BF8[];
extern s32 D_800A6C08[];
extern s32 D_800A6DBC[];
extern s32 D_800A6C18[];
extern s32 D_800A6DD8[];
extern s32 D_800A6C54[];
extern s32 D_800A6DF4[];
extern s32 D_800A6C90[];
extern s32 D_800A6E10[];
extern s32 D_800A6CCC[];
extern s32 D_800A6E2C[];
extern s32 D_800A6D08[];
extern s32 D_800A6E48[];
extern s32 D_800A6D44[];
extern s32 D_800A6E64[];
extern s32 D_800A6D80[];
extern s32 D_800A6E80[];
extern s32 D_800A6E8C[];
extern s32 D_800A6E98[];
extern s32 D_800A6EA4[];
extern s32 D_800A6EB0[];
extern s32 D_800A6EBC[];
extern s32 D_800A6EC8[];
extern s32 D_800A6ED8[];
extern s32 D_800A6EE8[];
extern s32 D_800A6EF8[];
extern s32 D_800A6F08[];
extern s32 D_800A6F18[];
extern s32 D_800A6F28[];
extern s32 D_800A6F38[];
extern s32 D_800A6F48[];
extern s32 D_800A6F5C[];
extern s32 D_800A6F70[];
extern s32 D_800A6F84[];
extern s32 D_800A6F98[];
extern s32 D_800A6FAC[];
extern s32 D_800A6FC0[];
extern s32 D_800A6FD4[];
extern s32 D_800A6FE8[];
extern s32 D_800A6FFC[];
extern s32 D_800A7010[];
extern s32 D_800A7024[];
extern s32 D_800A7038[];
extern s32 D_800A704C[];
extern s32 D_800A7060[];
extern s32 D_800A7074[];
extern s32 D_800A7088[];
extern s32 D_800A709C[];
extern s32 D_800A70B0[];
extern s32 D_800A70C4[];
extern s32 D_800A70D8[];
extern s32 D_800A70EC[];
extern s32 D_800A71D4[];
extern s32 D_800A71E0[];
extern s32 D_800A71EC[];
extern s32 D_800A71F8[];
extern s32 D_800A7204[];
extern s32 D_800A7210[];
extern s32 D_800A721C[];
extern s32 D_800A7228[];
extern s32 D_800A7258[];
extern s32 D_800A7264[];
extern s32 D_800A7270[];
extern s32 D_800A727C[];
extern s32 D_800A7288[];
extern s32 D_800A7294[];
extern s32 D_800A72A0[];
extern s32 D_800A72AC[];
extern s32 D_800A72DC[];
extern s32 D_800A72E8[];
extern s32 D_800A72F4[];
extern s32 D_800A7300[];
extern s32 D_800A730C[];
extern s32 D_800A7318[];
extern s32 D_800A7324[];
extern s32 D_800A7330[];
extern s32 D_800A7360[];
extern s32 D_800A736C[];
extern s32 D_800A7378[];
extern s32 D_800A7384[];
extern s32 D_800A7390[];
extern s32 D_800A739C[];
extern s32 D_800A73A8[];
extern s32 D_800A73B4[];
extern s32 D_800A73E4[];
extern s32 D_800A73F0[];
extern s32 D_800A73FC[];
extern s32 D_800A7408[];
extern s32 D_800A7414[];
extern s32 D_800A7420[];
extern s32 D_800A742C[];
extern s32 D_800A7438[];
extern s32 D_800A7468[];
extern s32 D_800A7474[];
extern s32 D_800A7480[];
extern s32 D_800A748C[];
extern s32 D_800A7498[];
extern s32 D_800A74A4[];
extern s32 D_800A74B0[];
extern s32 D_800A74BC[];
extern s32 D_800A74EC[];
extern s32 D_800A74F8[];
extern s32 D_800A7504[];
extern s32 D_800A7510[];
extern s32 D_800A751C[];
extern s32 D_800A7528[];
extern s32 D_800A7534[];
extern s32 D_800A7540[];
extern s32 D_800A7570[];
extern s32 D_800A757C[];
extern s32 D_800A7588[];
extern s32 D_800A7594[];
extern s32 D_800A75A0[];
extern s32 D_800A75AC[];
extern s32 D_800A75B8[];
extern s32 D_800A75C4[];
extern s32 D_800A75F4[];
extern s32 D_800A7600[];
extern s32 D_800A760C[];
extern s32 D_800A7618[];
extern s32 D_800A7624[];
extern s32 D_800A7630[];
extern s32 D_800A763C[];
extern s32 D_800A7648[];
extern s32 D_800A7678[];
extern s32 D_800A7684[];
extern s32 D_800A7690[];
extern s32 D_800A769C[];
extern s32 D_800A76A8[];
extern s32 D_800A76B4[];
extern s32 D_800A76C0[];
extern s32 D_800A76CC[];
extern s32 D_800A76FC[];
extern s32 D_800A7708[];
extern s32 D_800A7714[];
extern s32 D_800A7720[];
extern s32 D_800A772C[];
extern s32 D_800A7738[];
extern s32 D_800A7744[];
extern s32 D_800A7750[];
extern s32 D_800A7780[];
extern s32 D_800A778C[];
extern s32 D_800A7798[];
extern s32 D_800A77A4[];
extern s32 D_800A77B0[];
extern s32 D_800A77BC[];
extern s32 D_800A77C8[];
extern s32 D_800A77D4[];
extern s32 D_800A7804[];
extern s32 D_800A7810[];
extern s32 D_800A781C[];
extern s32 D_800A7828[];
extern s32 D_800A7834[];
extern s32 D_800A7840[];
extern s32 D_800A784C[];
extern s32 D_800A7858[];
extern s32 D_800A7888[];
extern s32 D_800A7894[];
extern s32 D_800A78A0[];
extern s32 D_800A78AC[];
extern s32 D_800A78B8[];
extern s32 D_800A78C4[];
extern s32 D_800A78D0[];
extern s32 D_800A78DC[];
extern s32 D_800A790C[];
extern s32 D_800A7918[];
extern s32 D_800A7924[];
extern s32 D_800A7930[];
extern s32 D_800A793C[];
extern s32 D_800A7948[];
extern s32 D_800A7954[];
extern s32 D_800A7960[];
extern s32 D_800A7990[];
extern s32 D_800A799C[];
extern s32 D_800A79A8[];
extern s32 D_800A79B4[];
extern s32 D_800A79C0[];
extern s32 D_800A79CC[];
extern s32 D_800A79D8[];
extern s32 D_800A79E4[];
extern s32 D_800A7A14[];
extern s32 D_800A7A20[];
extern s32 D_800A7A2C[];
extern s32 D_800A7A38[];
extern s32 D_800A7A44[];
extern s32 D_800A7A50[];
extern s32 D_800A7A5C[];
extern s32 D_800A7A68[];
extern s32 D_800A7A98[];
extern s32 D_800A7AA4[];
extern s32 D_800A7AB0[];
extern s32 D_800A7ABC[];
extern s32 D_800A7AC8[];
extern s32 D_800A7AD4[];
extern s32 D_800A7AE0[];
extern s32 D_800A7AEC[];
extern s32 D_800A7B1C[];
extern s32 D_800A7B28[];
extern s32 D_800A7B34[];
extern s32 D_800A7B40[];
extern s32 D_800A7B4C[];
extern s32 D_800A7B58[];
extern s32 D_800A7B64[];
extern s32 D_800A7B70[];
extern s32 D_800A7BA0[];
extern s32 D_800A7BAC[];
extern s32 D_800A7BB8[];
extern s32 D_800A7BC4[];
extern s32 D_800A7BD0[];
extern s32 D_800A7BDC[];
extern s32 D_800A7BE8[];
extern s32 D_800A7BF4[];
extern s32 D_800A7C24[];
extern s32 D_800A7C30[];
extern s32 D_800A7C3C[];
extern s32 D_800A7C48[];
extern s32 D_800A7C54[];
extern s32 D_800A7C60[];
extern s32 D_800A7C6C[];
extern s32 D_800A7C78[];
extern s32 D_800A7CA8[];
extern s32 D_800A7CB4[];
extern s32 D_800A7CC0[];
extern s32 D_800A7CCC[];
extern s32 D_800A7CD8[];
extern s32 D_800A7CE4[];
extern s32 D_800A7CF0[];
extern s32 D_800A7CFC[];
extern s32 D_800A7D2C[];
extern s32 D_800A7D38[];
extern s32 D_800A7D44[];
extern s32 D_800A7D50[];
extern s32 D_800A7D5C[];
extern s32 D_800A7D68[];
extern s32 D_800A7D74[];
extern s32 D_800A7D80[];
extern s32 D_800A7DB0[];
extern s32 D_800A7DBC[];
extern s32 D_800A7DC8[];
extern s32 D_800A7DD4[];
extern s32 D_800A7DE0[];
extern s32 D_800A7DEC[];
extern s32 D_800A7DF8[];
extern s32 D_800A7E04[];
extern s32 D_800A7234[];
extern s32 D_800A72B8[];
extern s32 D_800A733C[];
extern s32 D_800A73C0[];
extern s32 D_800A7444[];
extern s32 D_800A74C8[];
extern s32 D_800A754C[];
extern s32 D_800A75D0[];
extern s32 D_800A7654[];
extern s32 D_800A76D8[];
extern s32 D_800A775C[];
extern s32 D_800A77E0[];
extern s32 D_800A7864[];
extern s32 D_800A78E8[];
extern s32 D_800A796C[];
extern s32 D_800A79F0[];
extern s32 D_800A7A74[];
extern s32 D_800A7AF8[];
extern s32 D_800A7B7C[];
extern s32 D_800A7C00[];
extern s32 D_800A7C84[];
extern s32 D_800A7D08[];
extern s32 D_800A7D8C[];
extern s32 D_800A7E10[];

StagePoint D_800A60DC = { 0x2EB, 1, 1, 0x240, 160, 1, NULL };
StagePoint D_800A60EC = { 0x2ED, 1, 1, 0x350, 0x1F8, 5, &D_800A60DC };
StagePoint D_800A60FC = { 0x2E8, 1, 1, 176, 0x168, 5, &D_800A60EC };
StagePoints D_800A610C = { 1, 1, &D_800A60FC };
StagePoint D_800A6114 = { 0x2EB, 1, 4, 0x240, 160, 1, NULL };
StagePoint D_800A6124 = { 0x2EC, 1, 4, 240, 0x1D8, 5, &D_800A6114 };
StagePoint D_800A6134 = { 0x2EC, 1, 5, 240, 0x1D8, 5, &D_800A6124 };
StagePoints D_800A6144 = { 1, 2, &D_800A6134 };
StagePoint D_800A614C = { 0x2EC, 1, 6, 0x3B0, 120, 1, NULL };
StagePoint D_800A615C = { 0x2ED, 1, 4, 0x350, 0x1F8, 5, &D_800A614C };
StagePoint D_800A616C = { 0x2EA, 1, 3, 224, 0x200, 5, &D_800A615C };
StagePoints D_800A617C = { 1, 3, &D_800A616C };
StagePoint D_800A6184 = { 0x2EB, 1, 6, 0x240, 160, 1, NULL };
StagePoint D_800A6194 = { 0x2ED, 1, 5, 0x350, 0x1F8, 5, &D_800A6184 };
StagePoint D_800A61A4 = { 0x2EC, 1, 7, 240, 0x1D8, 5, &D_800A6194 };
StagePoints D_800A61B4 = { 1, 4, &D_800A61A4 };
StagePoint D_800A61BC = { 0x2ED, 2, 1, 0x3A0, 128, 1, NULL };
StagePoint D_800A61CC = { 0x2EA, 2, 1, 224, 0x200, 5, &D_800A61BC };
StagePoint D_800A61DC = { 0x2EA, 2, 2, 224, 0x200, 5, &D_800A61CC };
StagePoints D_800A61EC = { 2, 1, &D_800A61DC };
StagePoint D_800A61F4 = { 0x2ED, 2, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A6204 = { 0x2EA, 2, 4, 224, 0x200, 5, &D_800A61F4 };
StagePoint D_800A6214 = { 0x2ED, 2, 1, 224, 192, 5, &D_800A6204 };
StagePoints D_800A6224 = { 2, 2, &D_800A6214 };
StagePoint D_800A622C = { 0x2EC, 2, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A623C = { 0x2ED, 2, 1, 0x350, 0x1F8, 5, &D_800A622C };
StagePoint D_800A624C = { 0x2ED, 2, 2, 224, 192, 5, &D_800A623C };
StagePoints D_800A625C = { 2, 3, &D_800A624C };
StagePoint D_800A6264 = { 0x2EC, 2, 2, 0x3B0, 120, 1, NULL };
StagePoint D_800A6274 = { 0x2ED, 2, 2, 0x350, 0x1F8, 5, &D_800A6264 };
StagePoint D_800A6284 = { 0x2EA, 2, 5, 224, 0x200, 5, &D_800A6274 };
StagePoints D_800A6294 = { 2, 4, &D_800A6284 };
StagePoint D_800A629C = { 0x2EE, 2, 7, 0x130, 200, 1, NULL };
StagePoint D_800A62AC = { 0x2EA, 2, 6, 224, 0x200, 5, &D_800A629C };
StagePoint D_800A62BC = { 0x2ED, 2, 3, 224, 192, 5, &D_800A62AC };
StagePoints D_800A62CC = { 2, 5, &D_800A62BC };
StagePoint D_800A62D4 = { 0x2EE, 2, 8, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A62E4 = { 0x2EC, 2, 1, 240, 0x1D8, 5, &D_800A62D4 };
StagePoint D_800A62F4 = { 0x2EC, 2, 2, 240, 0x1D8, 5, &D_800A62E4 };
StagePoints D_800A6304 = { 2, 6, &D_800A62F4 };
StagePoint D_800A630C = { 0x2EE, 2, 9, 0x130, 200, 1, NULL };
StagePoint D_800A631C = { 0x2EE, 2, 5, 224, 0x240, 5, &D_800A630C };
StagePoint D_800A632C = { 0x2ED, 2, 4, 224, 192, 5, &D_800A631C };
StagePoints D_800A633C = { 2, 7, &D_800A632C };
StagePoint D_800A6344 = { 0x2EE, 2, 9, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6354 = { 0x2ED, 2, 4, 0x350, 0x1F8, 5, &D_800A6344 };
StagePoint D_800A6364 = { 0x2EE, 2, 6, 224, 0x240, 5, &D_800A6354 };
StagePoints D_800A6374 = { 2, 8, &D_800A6364 };
StagePoint D_800A637C = { 0x2E9, 2, 1, 0x240, 240, 1, NULL };
StagePoint D_800A638C = { 0x2EE, 2, 7, 224, 0x240, 5, &D_800A637C };
StagePoint D_800A639C = { 0x2EE, 2, 8, 224, 0x240, 5, &D_800A638C };
StagePoints D_800A63AC = { 2, 9, &D_800A639C };
StagePoint D_800A63B4 = { 0x2EC, 3, 5, 0x3B0, 120, 1, NULL };
StagePoint D_800A63C4 = { 0x2EC, 3, 2, 240, 0x1D8, 5, &D_800A63B4 };
StagePoint D_800A63D4 = { 0x2EC, 3, 3, 240, 0x1D8, 5, &D_800A63C4 };
StagePoints D_800A63E4 = { 3, 1, &D_800A63D4 };
StagePoint D_800A63EC = { 0x2EE, 3, 3, 0x130, 200, 1, NULL };
StagePoint D_800A63FC = { 0x2EC, 3, 4, 240, 0x1D8, 5, &D_800A63EC };
StagePoint D_800A640C = { 0x2ED, 3, 3, 224, 192, 5, &D_800A63FC };
StagePoints D_800A641C = { 3, 2, &D_800A640C };
StagePoint D_800A6424 = { 0x2EC, 3, 8, 0x3B0, 120, 1, NULL };
StagePoint D_800A6434 = { 0x2EE, 3, 2, 224, 0x240, 5, &D_800A6424 };
StagePoint D_800A6444 = { 0x2EC, 3, 6, 240, 0x1D8, 5, &D_800A6434 };
StagePoints D_800A6454 = { 3, 3, &D_800A6444 };
StagePoint D_800A645C = { 0x2EE, 3, 5, 0x130, 200, 1, NULL };
StagePoint D_800A646C = { 0x2EC, 3, 7, 240, 0x1D8, 5, &D_800A645C };
StagePoint D_800A647C = { 0x2EA, 3, 1, 224, 0x200, 5, &D_800A646C };
StagePoints D_800A648C = { 3, 4, &D_800A647C };
StagePoint D_800A6494 = { 0x2E9, 3, 1, 0x240, 240, 1, NULL };
StagePoint D_800A64A4 = { 0x2EE, 3, 4, 224, 0x240, 5, &D_800A6494 };
StagePoint D_800A64B4 = { 0x2EC, 3, 8, 240, 0x1D8, 5, &D_800A64A4 };
StagePoints D_800A64C4 = { 3, 5, &D_800A64B4 };
StagePoint D_800A64CC = { 0x2ED, 4, 3, 0x3A0, 128, 1, NULL };
StagePoint D_800A64DC = { 0x2EC, 4, 1, 240, 0x1D8, 5, &D_800A64CC };
StagePoint D_800A64EC = { 0x2EC, 4, 2, 240, 0x1D8, 5, &D_800A64DC };
StagePoints D_800A64FC = { 4, 1, &D_800A64EC };
StagePoint D_800A6504 = { 0x2EE, 4, 3, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6514 = { 0x2EC, 4, 4, 240, 0x1D8, 5, &D_800A6504 };
StagePoint D_800A6524 = { 0x2EC, 4, 5, 240, 0x1D8, 5, &D_800A6514 };
StagePoints D_800A6534 = { 4, 2, &D_800A6524 };
StagePoint D_800A653C = { 0x2E9, 4, 1, 0x240, 240, 1, NULL };
StagePoint D_800A654C = { 0x2EC, 4, 7, 240, 0x1D8, 5, &D_800A653C };
StagePoint D_800A655C = { 0x2EE, 4, 2, 224, 0x240, 5, &D_800A654C };
StagePoints D_800A656C = { 4, 3, &D_800A655C };
StagePoint D_800A6574 = { 0x2EE, 5, 2, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6584 = { 0x2ED, 5, 3, 0x350, 0x1F8, 5, &D_800A6574 };
StagePoint D_800A6594 = { 0x2EC, 5, 2, 240, 0x1D8, 5, &D_800A6584 };
StagePoints D_800A65A4 = { 5, 1, &D_800A6594 };
StagePoint D_800A65AC = { 0x2EC, 6, 1, 0x3B0, 120, 1, NULL };
StagePoint D_800A65BC = { 0x2ED, 5, 5, 0x350, 0x1F8, 5, &D_800A65AC };
StagePoint D_800A65CC = { 0x2EE, 5, 1, 224, 0x240, 5, &D_800A65BC };
StagePoints D_800A65DC = { 5, 2, &D_800A65CC };
StagePoint D_800A65E4 = { 0x2EC, 5, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A65F4 = { 0x2EA, 5, 1, 224, 0x200, 5, &D_800A65E4 };
StagePoint D_800A6604 = { 0x2ED, 5, 6, 224, 192, 5, &D_800A65F4 };
StagePoints D_800A6614 = { 5, 3, &D_800A6604 };
StagePoint D_800A661C = { 0x2EC, 5, 5, 0x3B0, 120, 1, NULL };
StagePoint D_800A662C = { 0x2EC, 5, 4, 240, 0x1D8, 5, &D_800A661C };
StagePoint D_800A663C = { 0x2EA, 5, 2, 224, 0x200, 5, &D_800A662C };
StagePoints D_800A664C = { 5, 4, &D_800A663C };
StagePoint D_800A6654 = { 0x2EC, 6, 4, 0x3B0, 120, 1, NULL };
StagePoint D_800A6664 = { 0x2EA, 5, 3, 224, 0x200, 5, &D_800A6654 };
StagePoint D_800A6674 = { 0x2EC, 5, 5, 240, 0x1D8, 5, &D_800A6664 };
StagePoints D_800A6684 = { 5, 5, &D_800A6674 };
StagePoint D_800A668C = { 0x2EE, 6, 2, 0x130, 200, 1, NULL };
StagePoint D_800A669C = { 0x2ED, 6, 1, 0x350, 0x1F8, 5, &D_800A668C };
StagePoint D_800A66AC = { 0x2ED, 6, 2, 224, 192, 5, &D_800A669C };
StagePoints D_800A66BC = { 6, 1, &D_800A66AC };
StagePoint D_800A66C4 = { 0x2ED, 6, 6, 0x3A0, 128, 1, NULL };
StagePoint D_800A66D4 = { 0x2EE, 6, 1, 224, 0x240, 5, &D_800A66C4 };
StagePoint D_800A66E4 = { 0x2EC, 6, 3, 240, 0x1D8, 5, &D_800A66D4 };
StagePoints D_800A66F4 = { 6, 2, &D_800A66E4 };
StagePoint D_800A66FC = { 0x2EE, 6, 5, 0x130, 200, 1, NULL };
StagePoint D_800A670C = { 0x2ED, 6, 4, 0x350, 0x1F8, 5, &D_800A66FC };
StagePoint D_800A671C = { 0x2ED, 6, 5, 224, 192, 5, &D_800A670C };
StagePoints D_800A672C = { 6, 3, &D_800A671C };
StagePoint D_800A6734 = { 0x2EE, 6, 5, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6744 = { 0x2ED, 6, 5, 0x350, 0x1F8, 5, &D_800A6734 };
StagePoint D_800A6754 = { 0x2ED, 6, 6, 224, 192, 5, &D_800A6744 };
StagePoints D_800A6764 = { 6, 4, &D_800A6754 };
StagePoint D_800A676C = { 0x2EE, 6, 7, 0x130, 200, 1, NULL };
StagePoint D_800A677C = { 0x2EE, 6, 3, 224, 0x240, 5, &D_800A676C };
StagePoint D_800A678C = { 0x2EE, 6, 4, 224, 0x240, 5, &D_800A677C };
StagePoints D_800A679C = { 6, 5, &D_800A678C };
StagePoint D_800A67A4 = { 0x2EE, 6, 8, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A67B4 = { 0x2ED, 6, 7, 0x350, 0x1F8, 5, &D_800A67A4 };
StagePoint D_800A67C4 = { 0x2EC, 6, 4, 240, 0x1D8, 5, &D_800A67B4 };
StagePoints D_800A67D4 = { 6, 6, &D_800A67C4 };
StagePoint D_800A67DC = { 0x2EE, 6, 9, 0x130, 200, 1, NULL };
StagePoint D_800A67EC = { 0x2EE, 6, 5, 224, 0x240, 5, &D_800A67DC };
StagePoint D_800A67FC = { 0x2ED, 6, 8, 224, 192, 5, &D_800A67EC };
StagePoints D_800A680C = { 6, 7, &D_800A67FC };
StagePoint D_800A6814 = { 0x2EE, 6, 9, 0x3A0, 0x1A0, 1, NULL };
StagePoint D_800A6824 = { 0x2ED, 6, 8, 0x350, 0x1F8, 5, &D_800A6814 };
StagePoint D_800A6834 = { 0x2EE, 6, 6, 224, 0x240, 5, &D_800A6824 };
StagePoints D_800A6844 = { 6, 8, &D_800A6834 };
StagePoint D_800A684C = { 0x2E9, 6, 1, 0x240, 240, 1, NULL };
StagePoint D_800A685C = { 0x2EE, 6, 7, 224, 0x240, 5, &D_800A684C };
StagePoint D_800A686C = { 0x2EE, 6, 8, 224, 0x240, 5, &D_800A685C };
StagePoints D_800A687C = { 6, 9, &D_800A686C };
StagePoints *D_800A6884[] = {
    &D_800A610C, &D_800A6144, &D_800A617C, &D_800A61B4,
    &D_800A61EC, &D_800A6224, &D_800A625C, &D_800A6294,
    &D_800A62CC, &D_800A6304, &D_800A633C, &D_800A6374,
    &D_800A63AC, &D_800A63E4, &D_800A641C, &D_800A6454,
    &D_800A648C, &D_800A64C4, &D_800A64FC, &D_800A6534,
    &D_800A656C, &D_800A65A4, &D_800A65DC, &D_800A6614,
    &D_800A664C, &D_800A6684, &D_800A66BC, &D_800A66F4,
    &D_800A672C, &D_800A6764, &D_800A679C, &D_800A67D4,
    &D_800A680C, &D_800A6844, &D_800A687C, NULL,
};
s32 D_800A6914[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140015E, 0x400078, 0x1FF0140,
    0x1000140, 0x140014C, 0x400030, 0x1FF0150,
    0x1000140, 0x1400166, 0x400098, 0x1FF0160,
    0x1000140, 0x140016E, 0x4000B8, 0x1FF0170,
    0x1000140, 0x1400156, 0x400058, 0x1FE0140,
    0x1000140, 0x1400140, 0x400000, 0x1FE0150,
    0x1000140, 0x1000140, 0, 0x1FE0160,
    0x1000140, 0x1000154, 80, 0x1FE0170,
    0x1000140, 0x1000168, 160, 0x1FD0140,
};
s32 D_800A6A04[] = {
    0x1868E, 65535,
};
s32 D_800A6A0C[] = {
    34446, 2, 65535,
};
s32 D_800A6A18[] = {
    0x10002, 65535,
};
s32 D_800A6A20[] = {
    34446, 0x10002, 33930, 65535,
};
s32 D_800A6A30[] = {
    34446, 0x10002, 0x1848A, 65535,
};
s32 D_800A6A40[] = {
    0x1868E, 34445, 33930, 65535,
};
s32 D_800A6A50[] = {
    0x1868F, 65535,
};
s32 D_800A6A58[] = {
    34447, 0, 65535,
};
s32 D_800A6A64[] = {
    0x10000, 65535,
};
s32 D_800A6A6C[] = {
    34447, 0x10000, 33931, 65535,
};
s32 D_800A6A7C[] = {
    34447, 0x10000, 0x1848B, 65535,
};
s32 D_800A6A8C[] = {
    0x1868F, 34446, 33931, 65535,
};
s32 D_800A6A9C[] = {
    0x18690, 65535,
};
s32 D_800A6AA4[] = {
    34448, 1, 65535,
};
s32 D_800A6AB0[] = {
    0x10001, 65535,
};
s32 D_800A6AB8[] = {
    34448, 0x10001, 33932, 65535,
};
s32 D_800A6AC8[] = {
    34448, 0x10001, 0x1848C, 65535,
};
s32 D_800A6AD8[] = {
    0x18690, 34447, 33932, 65535,
};
s32 D_800A6AE8[] = {
    0x18667, 65535,
};
s32 D_800A6AF0[] = {
    34407, 0, 65535,
};
s32 D_800A6AFC[] = {
    0x10000, 65535,
};
s32 D_800A6B04[] = {
    34407, 0x10000, 33891, 65535,
};
s32 D_800A6B14[] = {
    34407, 0x10000, 0x18463, 65535,
};
s32 D_800A6B24[] = {
    0x18667, 34406, 33891, 65535,
};
s32 D_800A6B34[] = {
    0x18681, 65535,
};
s32 D_800A6B3C[] = {
    34433, 0, 65535,
};
s32 D_800A6B48[] = {
    0x10000, 65535,
};
s32 D_800A6B50[] = {
    34433, 0x10000, 33917, 65535,
};
s32 D_800A6B60[] = {
    34433, 0x10000, 0x1847D, 65535,
};
s32 D_800A6B70[] = {
    0x18681, 34432, 33917, 65535,
};
s32 D_800A6B80[] = {
    0x18677, 65535,
};
s32 D_800A6B88[] = {
    34423, 0, 65535,
};
s32 D_800A6B94[] = {
    0x10000, 65535,
};
s32 D_800A6B9C[] = {
    34423, 0x10000, 33907, 65535,
};
s32 D_800A6BAC[] = {
    34423, 0x10000, 0x18473, 65535,
};
s32 D_800A6BBC[] = {
    0x18677, 34422, 33907, 65535,
};
s32 D_800A6BCC[] = {
    0x18675, 65535,
};
s32 D_800A6BD4[] = {
    34421, 0, 65535,
};
s32 D_800A6BE0[] = {
    0x10000, 65535,
};
s32 D_800A6BE8[] = {
    34421, 0x10000, 33905, 65535,
};
s32 D_800A6BF8[] = {
    34421, 0x10000, 0x18471, 65535,
};
s32 D_800A6C08[] = {
    33905, 0x18675, 34420, 65535,
};
s32 D_800A6C18[] = {
    (s32)D_800A6A04, 0, 165, (s32)D_800A6A0C,
    (s32)D_800A6A18, 166, (s32)D_800A6A20, 0,
    167, (s32)D_800A6A30, (s32)D_800A6A40, 168,
    0, 0, 0,
};
s32 D_800A6C54[] = {
    (s32)D_800A6A50, 0, 185, (s32)D_800A6A58,
    (s32)D_800A6A64, 186, (s32)D_800A6A6C, 0,
    187, (s32)D_800A6A7C, (s32)D_800A6A8C, 188,
    0, 0, 0,
};
s32 D_800A6C90[] = {
    (s32)D_800A6A9C, 0, 205, (s32)D_800A6AA4,
    (s32)D_800A6AB0, 206, (s32)D_800A6AB8, 0,
    207, (s32)D_800A6AC8, (s32)D_800A6AD8, 208,
    0, 0, 0,
};
s32 D_800A6CCC[] = {
    (s32)D_800A6AE8, 0, 149, (s32)D_800A6AF0,
    (s32)D_800A6AFC, 150, (s32)D_800A6B04, 0,
    151, (s32)D_800A6B14, (s32)D_800A6B24, 152,
    0, 0, 0,
};
s32 D_800A6D08[] = {
    (s32)D_800A6B34, 0, 153, (s32)D_800A6B3C,
    (s32)D_800A6B48, 154, (s32)D_800A6B50, 0,
    155, (s32)D_800A6B60, (s32)D_800A6B70, 156,
    0, 0, 0,
};
s32 D_800A6D44[] = {
    (s32)D_800A6B80, 0, 197, (s32)D_800A6B88,
    (s32)D_800A6B94, 198, (s32)D_800A6B9C, 0,
    199, (s32)D_800A6BAC, (s32)D_800A6BBC, 200,
    0, 0, 0,
};
s32 D_800A6D80[] = {
    (s32)D_800A6BCC, 0, 157, (s32)D_800A6BD4,
    (s32)D_800A6BE0, 158, (s32)D_800A6BE8, 0,
    159, (s32)D_800A6BF8, (s32)D_800A6C08, 160,
    0, 0, 0,
};
s32 D_800A6DBC[] = {
    0x17E01, 0x17E23, 0x17055, 0x17095,
    34446, 0x1868D, 65535,
};
s32 D_800A6DD8[] = {
    0x17E01, 0x17E21, 0x17055, 0x17095,
    0x1868E, 34447, 65535,
};
s32 D_800A6DF4[] = {
    0x17E01, 0x17E22, 0x17055, 0x17095,
    0x1868F, 34448, 65535,
};
s32 D_800A6E10[] = {
    0x17E01, 0x17E20, 0x17055, 0x17095,
    0x18666, 34407, 65535,
};
s32 D_800A6E2C[] = {
    0x17E01, 0x17E1E, 0x17055, 0x17095,
    0x18680, 34433, 65535,
};
s32 D_800A6E48[] = {
    0x17E01, 0x17E1F, 0x17055, 0x17095,
    0x18676, 34423, 65535,
};
s32 D_800A6E64[] = {
    0x17E01, 0x17E25, 0x17055, 0x17095,
    0x18674, 34421, 65535,
};
s32 D_800A6E80[] = {
    0x17E00, 8, 65535,
};
s32 D_800A6E8C[] = {
    0x17E01, 8, 65535,
};
s32 D_800A6E98[] = {
    0x17E02, 8, 65535,
};
s32 D_800A6EA4[] = {
    0x17E03, 8, 65535,
};
s32 D_800A6EB0[] = {
    0x17E04, 8, 65535,
};
s32 D_800A6EBC[] = {
    0x17E05, 8, 65535,
};
s32 D_800A6EC8[] = {
    0x17E00, 0x17E20, 9, 65535,
};
s32 D_800A6ED8[] = {
    0x17E00, 32288, 9, 65535,
};
s32 D_800A6EE8[] = {
    32256, 0x17E1E, 9, 65535,
};
s32 D_800A6EF8[] = {
    32256, 0x17E1F, 9, 65535,
};
s32 D_800A6F08[] = {
    32256, 0x17E20, 9, 65535,
};
s32 D_800A6F18[] = {
    32256, 0x17E21, 9, 65535,
};
s32 D_800A6F28[] = {
    0x17E00, 0x17E20, 10, 65535,
};
s32 D_800A6F38[] = {
    0x17E00, 32288, 10, 65535,
};
s32 D_800A6F48[] = {
    (s32)D_800A6DBC, (s32)D_800A6C18, 0x4001C, 0x1300270,
    1,
};
s32 D_800A6F5C[] = {
    (s32)D_800A6DD8, (s32)D_800A6C54, 0x5001F, 0x1300270,
    1,
};
s32 D_800A6F70[] = {
    (s32)D_800A6DF4, (s32)D_800A6C90, 0x5001F, 0x1300270,
    1,
};
s32 D_800A6F84[] = {
    (s32)D_800A6E10, (s32)D_800A6CCC, 0x600A6, 0x1300270,
    1,
};
s32 D_800A6F98[] = {
    (s32)D_800A6E2C, (s32)D_800A6D08, 0x700AB, 0x1300270,
    1,
};
s32 D_800A6FAC[] = {
    (s32)D_800A6E48, (s32)D_800A6D44, 0x800AD, 0x1300270,
    1,
};
s32 D_800A6FC0[] = {
    (s32)D_800A6E64, (s32)D_800A6D80, 0x800AD, 0x1300270,
    1,
};
s32 D_800A6FD4[] = {
    0, 0, 0x90146, 0,
    0,
};
s32 D_800A6FE8[] = {
    (s32)D_800A6E80, 0, 0xA0148, 0x21001C0,
    1,
};
s32 D_800A6FFC[] = {
    (s32)D_800A6E8C, 0, 0xA0148, 0x2000260,
    1,
};
s32 D_800A7010[] = {
    (s32)D_800A6E98, 0, 0xA0148, 0x1A002C0,
    1,
};
s32 D_800A7024[] = {
    (s32)D_800A6EA4, 0, 0xA0148, 0x22002D0,
    1,
};
s32 D_800A7038[] = {
    (s32)D_800A6EB0, 0, 0xA0148, 0x12C0118,
    1,
};
s32 D_800A704C[] = {
    (s32)D_800A6EBC, 0, 0xA0148, 0x14401B8,
    1,
};
s32 D_800A7060[] = {
    (s32)D_800A6EC8, 0, 0xB015F, 0x14401B8,
    1,
};
s32 D_800A7074[] = {
    (s32)D_800A6ED8, 0, 0xB015F, 0x2200120,
    1,
};
s32 D_800A7088[] = {
    (s32)D_800A6EE8, 0, 0xB015F, 0x21001C0,
    1,
};
s32 D_800A709C[] = {
    (s32)D_800A6EF8, 0, 0xB015F, 0x1C00360,
    1,
};
s32 D_800A70B0[] = {
    (s32)D_800A6F08, 0, 0xB015F, 0x2200120,
    1,
};
s32 D_800A70C4[] = {
    (s32)D_800A6F18, 0, 0xB015F, 0xE00100,
    1,
};
s32 D_800A70D8[] = {
    (s32)D_800A6F28, 0, 0xC0160, 0x1C00360,
    1,
};
s32 D_800A70EC[] = {
    (s32)D_800A6F38, 0, 0xC0160, 0x1E80310,
    1,
};
s32 D_800A7100[] = {
    (s32)D_800A6F48, (s32)D_800A6F5C, (s32)D_800A6F70, (s32)D_800A6F84,
    (s32)D_800A6F98, (s32)D_800A6FAC, (s32)D_800A6FC0, (s32)D_800A6FD4,
    (s32)D_800A6FE8, (s32)D_800A6FFC, (s32)D_800A7010, (s32)D_800A7024,
    (s32)D_800A7038, (s32)D_800A704C, (s32)D_800A7060, (s32)D_800A7074,
    (s32)D_800A7088, (s32)D_800A709C, (s32)D_800A70B0, (s32)D_800A70C4,
    (s32)D_800A70D8, (s32)D_800A70EC, 0,
};
s32 D_800A715C[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A7170[] = {
    65535, 65535, 0x2EE0001, 0x1A003A0,
    5, 0, 65535, 65535,
    0x2EE0001, 0xC80130, 5, 0,
    65535, 65535, 0x2EE0001, 0x24000E0,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A71D0[])(void) = {
    func_800A5FB0,
};
s32 D_800A71D4[] = {
    38, 10, 0x60080000,
};
s32 D_800A71E0[] = {
    56, 10, 0x60080000,
};
s32 D_800A71EC[] = {
    107, 10, 0x60080000,
};
s32 D_800A71F8[] = {
    155, 10, 0x60080000,
};
s32 D_800A7204[] = {
    120, 10, 0x60080000,
};
s32 D_800A7210[] = {
    181, 10, 0x60080000,
};
s32 D_800A721C[] = {
    142, 10, 0x60080000,
};
s32 D_800A7228[] = {
    143, 10, 0x60080000,
};
s32 D_800A7234[] = {
    3, (s32)D_800A71D4, (s32)D_800A71E0, (s32)D_800A71EC,
    (s32)D_800A71F8, (s32)D_800A7204, (s32)D_800A7210, (s32)D_800A721C,
    (s32)D_800A7228,
};
s32 D_800A7258[] = {
    0, 0, 0x60040000,
};
s32 D_800A7264[] = {
    0, 0, 0x60040000,
};
s32 D_800A7270[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7258, (s32)D_800A7264, (s32)D_800A7270,
    (s32)D_800A727C, (s32)D_800A7288, (s32)D_800A7294, (s32)D_800A72A0,
    (s32)D_800A72AC,
};
s32 D_800A72DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A72E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A72F4[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A72DC, (s32)D_800A72E8, (s32)D_800A72F4,
    (s32)D_800A7300, (s32)D_800A730C, (s32)D_800A7318, (s32)D_800A7324,
    (s32)D_800A7330,
};
s32 D_800A7360[] = {
    0, 0, 0x60040000,
};
s32 D_800A736C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7378[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7360, (s32)D_800A736C, (s32)D_800A7378,
    (s32)D_800A7384, (s32)D_800A7390, (s32)D_800A739C, (s32)D_800A73A8,
    (s32)D_800A73B4,
};
s32 D_800A73E4[] = {
    82, 10, 0x60080000,
};
s32 D_800A73F0[] = {
    82, 10, 0x60080000,
};
s32 D_800A73FC[] = {
    108, 10, 0x60080000,
};
s32 D_800A7408[] = {
    108, 10, 0x60080000,
};
s32 D_800A7414[] = {
    129, 10, 0x60080000,
};
s32 D_800A7420[] = {
    129, 10, 0x60080000,
};
s32 D_800A742C[] = {
    91, 10, 0x60080000,
};
s32 D_800A7438[] = {
    173, 10, 0x60080000,
};
s32 D_800A7444[] = {
    3, (s32)D_800A73E4, (s32)D_800A73F0, (s32)D_800A73FC,
    (s32)D_800A7408, (s32)D_800A7414, (s32)D_800A7420, (s32)D_800A742C,
    (s32)D_800A7438,
};
s32 D_800A7468[] = {
    0, 0, 0x60040000,
};
s32 D_800A7474[] = {
    0, 0, 0x60040000,
};
s32 D_800A7480[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7468, (s32)D_800A7474, (s32)D_800A7480,
    (s32)D_800A748C, (s32)D_800A7498, (s32)D_800A74A4, (s32)D_800A74B0,
    (s32)D_800A74BC,
};
s32 D_800A74EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A74F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7504[] = {
    0, 0, 0x60040000,
};
s32 D_800A7510[] = {
    0, 0, 0x60040000,
};
s32 D_800A751C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7528[] = {
    0, 0, 0x60040000,
};
s32 D_800A7534[] = {
    0, 0, 0x60040000,
};
s32 D_800A7540[] = {
    0, 0, 0x60040000,
};
s32 D_800A754C[] = {
    0, (s32)D_800A74EC, (s32)D_800A74F8, (s32)D_800A7504,
    (s32)D_800A7510, (s32)D_800A751C, (s32)D_800A7528, (s32)D_800A7534,
    (s32)D_800A7540,
};
s32 D_800A7570[] = {
    0, 0, 0x60040000,
};
s32 D_800A757C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7588[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7570, (s32)D_800A757C, (s32)D_800A7588,
    (s32)D_800A7594, (s32)D_800A75A0, (s32)D_800A75AC, (s32)D_800A75B8,
    (s32)D_800A75C4,
};
s32 D_800A75F4[] = {
    111, 10, 0x60080000,
};
s32 D_800A7600[] = {
    111, 10, 0x60080000,
};
s32 D_800A760C[] = {
    112, 10, 0x60080000,
};
s32 D_800A7618[] = {
    112, 10, 0x60080000,
};
s32 D_800A7624[] = {
    119, 10, 0x60080000,
};
s32 D_800A7630[] = {
    119, 10, 0x60080000,
};
s32 D_800A763C[] = {
    168, 10, 0x60080000,
};
s32 D_800A7648[] = {
    168, 10, 0x60080000,
};
s32 D_800A7654[] = {
    3, (s32)D_800A75F4, (s32)D_800A7600, (s32)D_800A760C,
    (s32)D_800A7618, (s32)D_800A7624, (s32)D_800A7630, (s32)D_800A763C,
    (s32)D_800A7648,
};
s32 D_800A7678[] = {
    0, 0, 0x60040000,
};
s32 D_800A7684[] = {
    0, 0, 0x60040000,
};
s32 D_800A7690[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7678, (s32)D_800A7684, (s32)D_800A7690,
    (s32)D_800A769C, (s32)D_800A76A8, (s32)D_800A76B4, (s32)D_800A76C0,
    (s32)D_800A76CC,
};
s32 D_800A76FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7708[] = {
    0, 0, 0x60040000,
};
s32 D_800A7714[] = {
    0, 0, 0x60040000,
};
s32 D_800A7720[] = {
    0, 0, 0x60040000,
};
s32 D_800A772C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7738[] = {
    0, 0, 0x60040000,
};
s32 D_800A7744[] = {
    0, 0, 0x60040000,
};
s32 D_800A7750[] = {
    0, 0, 0x60040000,
};
s32 D_800A775C[] = {
    0, (s32)D_800A76FC, (s32)D_800A7708, (s32)D_800A7714,
    (s32)D_800A7720, (s32)D_800A772C, (s32)D_800A7738, (s32)D_800A7744,
    (s32)D_800A7750,
};
s32 D_800A7780[] = {
    0, 0, 0x60040000,
};
s32 D_800A778C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7798[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7780, (s32)D_800A778C, (s32)D_800A7798,
    (s32)D_800A77A4, (s32)D_800A77B0, (s32)D_800A77BC, (s32)D_800A77C8,
    (s32)D_800A77D4,
};
s32 D_800A7804[] = {
    117, 10, 0x60080000,
};
s32 D_800A7810[] = {
    117, 10, 0x60080000,
};
s32 D_800A781C[] = {
    184, 10, 0x60080000,
};
s32 D_800A7828[] = {
    184, 10, 0x60080000,
};
s32 D_800A7834[] = {
    187, 10, 0x60080000,
};
s32 D_800A7840[] = {
    187, 10, 0x60080000,
};
s32 D_800A784C[] = {
    187, 10, 0x60080000,
};
s32 D_800A7858[] = {
    187, 10, 0x60080000,
};
s32 D_800A7864[] = {
    3, (s32)D_800A7804, (s32)D_800A7810, (s32)D_800A781C,
    (s32)D_800A7828, (s32)D_800A7834, (s32)D_800A7840, (s32)D_800A784C,
    (s32)D_800A7858,
};
s32 D_800A7888[] = {
    0, 0, 0x60040000,
};
s32 D_800A7894[] = {
    0, 0, 0x60040000,
};
s32 D_800A78A0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7888, (s32)D_800A7894, (s32)D_800A78A0,
    (s32)D_800A78AC, (s32)D_800A78B8, (s32)D_800A78C4, (s32)D_800A78D0,
    (s32)D_800A78DC,
};
s32 D_800A790C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7918[] = {
    0, 0, 0x60040000,
};
s32 D_800A7924[] = {
    0, 0, 0x60040000,
};
s32 D_800A7930[] = {
    0, 0, 0x60040000,
};
s32 D_800A793C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7948[] = {
    0, 0, 0x60040000,
};
s32 D_800A7954[] = {
    0, 0, 0x60040000,
};
s32 D_800A7960[] = {
    0, 0, 0x60040000,
};
s32 D_800A796C[] = {
    0, (s32)D_800A790C, (s32)D_800A7918, (s32)D_800A7924,
    (s32)D_800A7930, (s32)D_800A793C, (s32)D_800A7948, (s32)D_800A7954,
    (s32)D_800A7960,
};
s32 D_800A7990[] = {
    0, 0, 0x60040000,
};
s32 D_800A799C[] = {
    0, 0, 0x60040000,
};
s32 D_800A79A8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7990, (s32)D_800A799C, (s32)D_800A79A8,
    (s32)D_800A79B4, (s32)D_800A79C0, (s32)D_800A79CC, (s32)D_800A79D8,
    (s32)D_800A79E4,
};
s32 D_800A7A14[] = {
    171, 10, 0x60080000,
};
s32 D_800A7A20[] = {
    171, 10, 0x60080000,
};
s32 D_800A7A2C[] = {
    171, 10, 0x60080000,
};
s32 D_800A7A38[] = {
    172, 10, 0x60080000,
};
s32 D_800A7A44[] = {
    172, 10, 0x60080000,
};
s32 D_800A7A50[] = {
    87, 10, 0x60080000,
};
s32 D_800A7A5C[] = {
    87, 10, 0x60080000,
};
s32 D_800A7A68[] = {
    87, 10, 0x60080000,
};
s32 D_800A7A74[] = {
    3, (s32)D_800A7A14, (s32)D_800A7A20, (s32)D_800A7A2C,
    (s32)D_800A7A38, (s32)D_800A7A44, (s32)D_800A7A50, (s32)D_800A7A5C,
    (s32)D_800A7A68,
};
s32 D_800A7A98[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7AB0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7A98, (s32)D_800A7AA4, (s32)D_800A7AB0,
    (s32)D_800A7ABC, (s32)D_800A7AC8, (s32)D_800A7AD4, (s32)D_800A7AE0,
    (s32)D_800A7AEC,
};
s32 D_800A7B1C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B28[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B34[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B40[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B4C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B58[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B64[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B70[] = {
    0, 0, 0x60040000,
};
s32 D_800A7B7C[] = {
    0, (s32)D_800A7B1C, (s32)D_800A7B28, (s32)D_800A7B34,
    (s32)D_800A7B40, (s32)D_800A7B4C, (s32)D_800A7B58, (s32)D_800A7B64,
    (s32)D_800A7B70,
};
s32 D_800A7BA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7BB8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7BA0, (s32)D_800A7BAC, (s32)D_800A7BB8,
    (s32)D_800A7BC4, (s32)D_800A7BD0, (s32)D_800A7BDC, (s32)D_800A7BE8,
    (s32)D_800A7BF4,
};
s32 D_800A7C24[] = {
    73, 10, 0x60080000,
};
s32 D_800A7C30[] = {
    73, 10, 0x60080000,
};
s32 D_800A7C3C[] = {
    86, 10, 0x60080000,
};
s32 D_800A7C48[] = {
    86, 10, 0x60080000,
};
s32 D_800A7C54[] = {
    85, 10, 0x60080000,
};
s32 D_800A7C60[] = {
    170, 10, 0x60080000,
};
s32 D_800A7C6C[] = {
    92, 10, 0x60080000,
};
s32 D_800A7C78[] = {
    174, 10, 0x60080000,
};
s32 D_800A7C84[] = {
    3, (s32)D_800A7C24, (s32)D_800A7C30, (s32)D_800A7C3C,
    (s32)D_800A7C48, (s32)D_800A7C54, (s32)D_800A7C60, (s32)D_800A7C6C,
    (s32)D_800A7C78,
};
s32 D_800A7CA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7CC0[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7CA8, (s32)D_800A7CB4, (s32)D_800A7CC0,
    (s32)D_800A7CCC, (s32)D_800A7CD8, (s32)D_800A7CE4, (s32)D_800A7CF0,
    (s32)D_800A7CFC,
};
s32 D_800A7D2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D38[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D44[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D50[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D68[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D74[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D80[] = {
    0, 0, 0x60040000,
};
s32 D_800A7D8C[] = {
    0, (s32)D_800A7D2C, (s32)D_800A7D38, (s32)D_800A7D44,
    (s32)D_800A7D50, (s32)D_800A7D5C, (s32)D_800A7D68, (s32)D_800A7D74,
    (s32)D_800A7D80,
};
s32 D_800A7DB0[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DBC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7DC8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A7DB0, (s32)D_800A7DBC, (s32)D_800A7DC8,
    (s32)D_800A7DD4, (s32)D_800A7DE0, (s32)D_800A7DEC, (s32)D_800A7DF8,
    (s32)D_800A7E04,
};
s32 D_800A7E34[] = {
    419, 1, 0, (s32)D_800A7234,
    (s32)D_800A72B8, (s32)D_800A733C, (s32)D_800A73C0, 424,
    2, 0, (s32)D_800A7444, (s32)D_800A74C8,
    (s32)D_800A754C, (s32)D_800A75D0, 430, 3,
    0, (s32)D_800A7654, (s32)D_800A76D8, (s32)D_800A775C,
    (s32)D_800A77E0, 436, 4, 0,
    (s32)D_800A7864, (s32)D_800A78E8, (s32)D_800A796C, (s32)D_800A79F0,
    442, 5, 0, (s32)D_800A7A74,
    (s32)D_800A7AF8, (s32)D_800A7B7C, (s32)D_800A7C00, 448,
    6, 0, (s32)D_800A7C84, (s32)D_800A7D08,
    (s32)D_800A7D8C, (s32)D_800A7E10,
};
