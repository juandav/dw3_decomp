#include "common.h"
#include "stage.h"
void func_800A5EE0();
extern void (*D_800A6314[])(void);
extern StagePoints *D_800A617C[];

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
        func_800A5DE0(D_800990B4.unk14, D_800A617C, GAME.unk44, GAME.unk46);
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
    D_800A6314[0]();
    return task;
}

extern s32 D_800A62A8[];
extern s32 D_800A62CC[];
extern s32 D_800A6190[];
extern s32 D_800A6294[];
extern s32 D_800A6B58[];
void func_800A5FB0(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x6B3;
    D_800990B4.unkC = 0x9410004;
    D_800990B4.unk10 = D_800A62A8;
    D_800990B4.unk14 = D_800A62CC;
    D_800990B4.unk1C = 0x940;
    D_800990B4.unk2C = (Vec2){0x17900, 0x17300};
    D_800990B4.unk28 = D_800A6190;
    D_800990B4.unk3C = 0x1E;
    D_800990B4.unk40 = 0x60780000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk4C = D_800A6294;
    D_800990B4.unk20 = D_800990B4.unk7C(D_800A6B58, GAME.unk44);
    D_8009A70C.setFile(0, 0x9410006);
    D_8009A70C.setFile(7, 0x9410007);
    D_8009A70C.setFile(4, 0x9410005);
    D_8009A70C.unk50(0);
}

void func_800A5FB0();
extern StagePoint D_800A60DC;
extern StagePoint D_800A60EC;
extern StagePoint D_800A6104;
extern StagePoint D_800A6114;
extern StagePoint D_800A612C;
extern StagePoint D_800A613C;
extern StagePoint D_800A6154;
extern StagePoint D_800A6164;
extern StagePoints D_800A60FC;
extern StagePoints D_800A6124;
extern StagePoints D_800A614C;
extern StagePoints D_800A6174;
extern s32 D_800A6220[];
extern s32 D_800A622C[];
extern s32 D_800A6238[];
extern s32 D_800A6244[];
extern s32 D_800A6258[];
extern s32 D_800A626C[];
extern s32 D_800A6280[];
extern s32 D_800A6318[];
extern s32 D_800A6324[];
extern s32 D_800A6330[];
extern s32 D_800A633C[];
extern s32 D_800A6348[];
extern s32 D_800A6354[];
extern s32 D_800A6360[];
extern s32 D_800A636C[];
extern s32 D_800A639C[];
extern s32 D_800A63A8[];
extern s32 D_800A63B4[];
extern s32 D_800A63C0[];
extern s32 D_800A63CC[];
extern s32 D_800A63D8[];
extern s32 D_800A63E4[];
extern s32 D_800A63F0[];
extern s32 D_800A6420[];
extern s32 D_800A642C[];
extern s32 D_800A6438[];
extern s32 D_800A6444[];
extern s32 D_800A6450[];
extern s32 D_800A645C[];
extern s32 D_800A6468[];
extern s32 D_800A6474[];
extern s32 D_800A64A4[];
extern s32 D_800A64B0[];
extern s32 D_800A64BC[];
extern s32 D_800A64C8[];
extern s32 D_800A64D4[];
extern s32 D_800A64E0[];
extern s32 D_800A64EC[];
extern s32 D_800A64F8[];
extern s32 D_800A6528[];
extern s32 D_800A6534[];
extern s32 D_800A6540[];
extern s32 D_800A654C[];
extern s32 D_800A6558[];
extern s32 D_800A6564[];
extern s32 D_800A6570[];
extern s32 D_800A657C[];
extern s32 D_800A65AC[];
extern s32 D_800A65B8[];
extern s32 D_800A65C4[];
extern s32 D_800A65D0[];
extern s32 D_800A65DC[];
extern s32 D_800A65E8[];
extern s32 D_800A65F4[];
extern s32 D_800A6600[];
extern s32 D_800A6630[];
extern s32 D_800A663C[];
extern s32 D_800A6648[];
extern s32 D_800A6654[];
extern s32 D_800A6660[];
extern s32 D_800A666C[];
extern s32 D_800A6678[];
extern s32 D_800A6684[];
extern s32 D_800A66B4[];
extern s32 D_800A66C0[];
extern s32 D_800A66CC[];
extern s32 D_800A66D8[];
extern s32 D_800A66E4[];
extern s32 D_800A66F0[];
extern s32 D_800A66FC[];
extern s32 D_800A6708[];
extern s32 D_800A6738[];
extern s32 D_800A6744[];
extern s32 D_800A6750[];
extern s32 D_800A675C[];
extern s32 D_800A6768[];
extern s32 D_800A6774[];
extern s32 D_800A6780[];
extern s32 D_800A678C[];
extern s32 D_800A67BC[];
extern s32 D_800A67C8[];
extern s32 D_800A67D4[];
extern s32 D_800A67E0[];
extern s32 D_800A67EC[];
extern s32 D_800A67F8[];
extern s32 D_800A6804[];
extern s32 D_800A6810[];
extern s32 D_800A6840[];
extern s32 D_800A684C[];
extern s32 D_800A6858[];
extern s32 D_800A6864[];
extern s32 D_800A6870[];
extern s32 D_800A687C[];
extern s32 D_800A6888[];
extern s32 D_800A6894[];
extern s32 D_800A68C4[];
extern s32 D_800A68D0[];
extern s32 D_800A68DC[];
extern s32 D_800A68E8[];
extern s32 D_800A68F4[];
extern s32 D_800A6900[];
extern s32 D_800A690C[];
extern s32 D_800A6918[];
extern s32 D_800A6948[];
extern s32 D_800A6954[];
extern s32 D_800A6960[];
extern s32 D_800A696C[];
extern s32 D_800A6978[];
extern s32 D_800A6984[];
extern s32 D_800A6990[];
extern s32 D_800A699C[];
extern s32 D_800A69CC[];
extern s32 D_800A69D8[];
extern s32 D_800A69E4[];
extern s32 D_800A69F0[];
extern s32 D_800A69FC[];
extern s32 D_800A6A08[];
extern s32 D_800A6A14[];
extern s32 D_800A6A20[];
extern s32 D_800A6A50[];
extern s32 D_800A6A5C[];
extern s32 D_800A6A68[];
extern s32 D_800A6A74[];
extern s32 D_800A6A80[];
extern s32 D_800A6A8C[];
extern s32 D_800A6A98[];
extern s32 D_800A6AA4[];
extern s32 D_800A6AD4[];
extern s32 D_800A6AE0[];
extern s32 D_800A6AEC[];
extern s32 D_800A6AF8[];
extern s32 D_800A6B04[];
extern s32 D_800A6B10[];
extern s32 D_800A6B1C[];
extern s32 D_800A6B28[];
extern s32 D_800A6378[];
extern s32 D_800A63FC[];
extern s32 D_800A6480[];
extern s32 D_800A6504[];
extern s32 D_800A6588[];
extern s32 D_800A660C[];
extern s32 D_800A6690[];
extern s32 D_800A6714[];
extern s32 D_800A6798[];
extern s32 D_800A681C[];
extern s32 D_800A68A0[];
extern s32 D_800A6924[];
extern s32 D_800A69A8[];
extern s32 D_800A6A2C[];
extern s32 D_800A6AB0[];
extern s32 D_800A6B34[];

StagePoint D_800A60DC = { 0x2EE, 2, 9, 224, 0x240, 5, NULL };
StagePoint D_800A60EC = { 0x28C, 0, 0, 0x410, 0x400, 0, &D_800A60DC };
StagePoints D_800A60FC = { 2, 1, &D_800A60EC };
StagePoint D_800A6104 = { 0x2EE, 3, 5, 224, 0x240, 5, NULL };
StagePoint D_800A6114 = { 0x28C, 0, 0, 0x110, 0x290, 0, &D_800A6104 };
StagePoints D_800A6124 = { 3, 1, &D_800A6114 };
StagePoint D_800A612C = { 0x2EE, 4, 3, 224, 0x240, 5, NULL };
StagePoint D_800A613C = { 0x299, 0, 0, 0x440, 0x2F8, 0, &D_800A612C };
StagePoints D_800A614C = { 4, 1, &D_800A613C };
StagePoint D_800A6154 = { 0x2EE, 6, 9, 224, 0x240, 5, NULL };
StagePoint D_800A6164 = { 0x299, 0, 0, 0x2D0, 0x590, 0, &D_800A6154 };
StagePoints D_800A6174 = { 6, 1, &D_800A6164 };
StagePoints *D_800A617C[] = {
    &D_800A60FC, &D_800A6124, &D_800A614C, &D_800A6174,
    NULL,
};
s32 D_800A6190[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x140014C, 0x400030, 0x1FF0150,
    0x1000140, 0x100014C, 48, 0x1FF0160,
    0x1000140, 0x1000160, 128, 0x1FF0170,
};
s32 D_800A6220[] = {
    32257, 8, 65535,
};
s32 D_800A622C[] = {
    32258, 9, 65535,
};
s32 D_800A6238[] = {
    0x17E02, 9, 65535,
};
s32 D_800A6244[] = {
    0, 0, 0x40146, 0,
    0,
};
s32 D_800A6258[] = {
    (s32)D_800A6220, 0, 0x50148, 0x1580110,
    1,
};
s32 D_800A626C[] = {
    (s32)D_800A622C, 0, 0x6015F, 0x13801B0,
    1,
};
s32 D_800A6280[] = {
    (s32)D_800A6238, 0, 0x6015F, 0x14000E0,
    1,
};
s32 D_800A6294[] = {
    (s32)D_800A6244, (s32)D_800A6258, (s32)D_800A626C, (s32)D_800A6280,
    0,
};
s32 D_800A62A8[] = {
    0x4FF0001, 0x7000232, 0x980014, 0xFD008C,
    0, 0, 0, 0,
    0,
};
s32 D_800A62CC[] = {
    65535, 65535, 0x2E90001, 0xF800B0,
    4, 0, 65535, 65535,
    0x2E90001, 0xF00240, 5, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6314[])(void) = {
    func_800A5FB0,
};
s32 D_800A6318[] = {
    55, 10, 0x60080000,
};
s32 D_800A6324[] = {
    55, 10, 0x60080000,
};
s32 D_800A6330[] = {
    55, 10, 0x60080000,
};
s32 D_800A633C[] = {
    55, 10, 0x60080000,
};
s32 D_800A6348[] = {
    55, 10, 0x60080000,
};
s32 D_800A6354[] = {
    55, 10, 0x60080000,
};
s32 D_800A6360[] = {
    55, 10, 0x60080000,
};
s32 D_800A636C[] = {
    55, 10, 0x60080000,
};
s32 D_800A6378[] = {
    3, (s32)D_800A6318, (s32)D_800A6324, (s32)D_800A6330,
    (s32)D_800A633C, (s32)D_800A6348, (s32)D_800A6354, (s32)D_800A6360,
    (s32)D_800A636C,
};
s32 D_800A639C[] = {
    0, 0, 0x60040000,
};
s32 D_800A63A8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63CC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A639C, (s32)D_800A63A8, (s32)D_800A63B4,
    (s32)D_800A63C0, (s32)D_800A63CC, (s32)D_800A63D8, (s32)D_800A63E4,
    (s32)D_800A63F0,
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
    0, 0, 0x60040000,
};
s32 D_800A6474[] = {
    0, 0, 0x60040000,
};
s32 D_800A6480[] = {
    0, (s32)D_800A6420, (s32)D_800A642C, (s32)D_800A6438,
    (s32)D_800A6444, (s32)D_800A6450, (s32)D_800A645C, (s32)D_800A6468,
    (s32)D_800A6474,
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
    0, 0, 0x60040000,
};
s32 D_800A64F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6504[] = {
    0, (s32)D_800A64A4, (s32)D_800A64B0, (s32)D_800A64BC,
    (s32)D_800A64C8, (s32)D_800A64D4, (s32)D_800A64E0, (s32)D_800A64EC,
    (s32)D_800A64F8,
};
s32 D_800A6528[] = {
    111, 10, 0x60080000,
};
s32 D_800A6534[] = {
    111, 10, 0x60080000,
};
s32 D_800A6540[] = {
    112, 10, 0x60080000,
};
s32 D_800A654C[] = {
    112, 10, 0x60080000,
};
s32 D_800A6558[] = {
    119, 10, 0x60080000,
};
s32 D_800A6564[] = {
    119, 10, 0x60080000,
};
s32 D_800A6570[] = {
    168, 10, 0x60080000,
};
s32 D_800A657C[] = {
    168, 10, 0x60080000,
};
s32 D_800A6588[] = {
    3, (s32)D_800A6528, (s32)D_800A6534, (s32)D_800A6540,
    (s32)D_800A654C, (s32)D_800A6558, (s32)D_800A6564, (s32)D_800A6570,
    (s32)D_800A657C,
};
s32 D_800A65AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65DC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A65AC, (s32)D_800A65B8, (s32)D_800A65C4,
    (s32)D_800A65D0, (s32)D_800A65DC, (s32)D_800A65E8, (s32)D_800A65F4,
    (s32)D_800A6600,
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
    0, 0, 0x60040000,
};
s32 D_800A6684[] = {
    0, 0, 0x60040000,
};
s32 D_800A6690[] = {
    0, (s32)D_800A6630, (s32)D_800A663C, (s32)D_800A6648,
    (s32)D_800A6654, (s32)D_800A6660, (s32)D_800A666C, (s32)D_800A6678,
    (s32)D_800A6684,
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
    0, 0, 0x60040000,
};
s32 D_800A6708[] = {
    0, 0, 0x60040000,
};
s32 D_800A6714[] = {
    0, (s32)D_800A66B4, (s32)D_800A66C0, (s32)D_800A66CC,
    (s32)D_800A66D8, (s32)D_800A66E4, (s32)D_800A66F0, (s32)D_800A66FC,
    (s32)D_800A6708,
};
s32 D_800A6738[] = {
    113, 10, 0x60080000,
};
s32 D_800A6744[] = {
    113, 10, 0x60080000,
};
s32 D_800A6750[] = {
    114, 10, 0x60080000,
};
s32 D_800A675C[] = {
    114, 10, 0x60080000,
};
s32 D_800A6768[] = {
    115, 10, 0x60080000,
};
s32 D_800A6774[] = {
    115, 10, 0x60080000,
};
s32 D_800A6780[] = {
    167, 10, 0x60080000,
};
s32 D_800A678C[] = {
    167, 10, 0x60080000,
};
s32 D_800A6798[] = {
    3, (s32)D_800A6738, (s32)D_800A6744, (s32)D_800A6750,
    (s32)D_800A675C, (s32)D_800A6768, (s32)D_800A6774, (s32)D_800A6780,
    (s32)D_800A678C,
};
s32 D_800A67BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A67E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67EC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A67BC, (s32)D_800A67C8, (s32)D_800A67D4,
    (s32)D_800A67E0, (s32)D_800A67EC, (s32)D_800A67F8, (s32)D_800A6804,
    (s32)D_800A6810,
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
    0, 0, 0x60040000,
};
s32 D_800A6894[] = {
    0, 0, 0x60040000,
};
s32 D_800A68A0[] = {
    0, (s32)D_800A6840, (s32)D_800A684C, (s32)D_800A6858,
    (s32)D_800A6864, (s32)D_800A6870, (s32)D_800A687C, (s32)D_800A6888,
    (s32)D_800A6894,
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
    0, 0, 0x60040000,
};
s32 D_800A6918[] = {
    0, 0, 0x60040000,
};
s32 D_800A6924[] = {
    0, (s32)D_800A68C4, (s32)D_800A68D0, (s32)D_800A68DC,
    (s32)D_800A68E8, (s32)D_800A68F4, (s32)D_800A6900, (s32)D_800A690C,
    (s32)D_800A6918,
};
s32 D_800A6948[] = {
    73, 10, 0x60080000,
};
s32 D_800A6954[] = {
    73, 10, 0x60080000,
};
s32 D_800A6960[] = {
    86, 10, 0x60080000,
};
s32 D_800A696C[] = {
    86, 10, 0x60080000,
};
s32 D_800A6978[] = {
    85, 10, 0x60080000,
};
s32 D_800A6984[] = {
    170, 10, 0x60080000,
};
s32 D_800A6990[] = {
    92, 10, 0x60080000,
};
s32 D_800A699C[] = {
    174, 10, 0x60080000,
};
s32 D_800A69A8[] = {
    3, (s32)D_800A6948, (s32)D_800A6954, (s32)D_800A6960,
    (s32)D_800A696C, (s32)D_800A6978, (s32)D_800A6984, (s32)D_800A6990,
    (s32)D_800A699C,
};
s32 D_800A69CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A69D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A69E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A69F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A69FC[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A69CC, (s32)D_800A69D8, (s32)D_800A69E4,
    (s32)D_800A69F0, (s32)D_800A69FC, (s32)D_800A6A08, (s32)D_800A6A14,
    (s32)D_800A6A20,
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
    0, 0, 0x60040000,
};
s32 D_800A6AA4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6AB0[] = {
    0, (s32)D_800A6A50, (s32)D_800A6A5C, (s32)D_800A6A68,
    (s32)D_800A6A74, (s32)D_800A6A80, (s32)D_800A6A8C, (s32)D_800A6A98,
    (s32)D_800A6AA4,
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
    0, 0, 0x60040000,
};
s32 D_800A6B28[] = {
    0, 0, 0x60040000,
};
s32 D_800A6B34[] = {
    0, (s32)D_800A6AD4, (s32)D_800A6AE0, (s32)D_800A6AEC,
    (s32)D_800A6AF8, (s32)D_800A6B04, (s32)D_800A6B10, (s32)D_800A6B1C,
    (s32)D_800A6B28,
};
s32 D_800A6B58[] = {
    420, 2, 0, (s32)D_800A6378,
    (s32)D_800A63FC, (s32)D_800A6480, (s32)D_800A6504, 426,
    3, 0, (s32)D_800A6588, (s32)D_800A660C,
    (s32)D_800A6690, (s32)D_800A6714, 432, 4,
    0, (s32)D_800A6798, (s32)D_800A681C, (s32)D_800A68A0,
    (s32)D_800A6924, 443, 6, 0,
    (s32)D_800A69A8, (s32)D_800A6A2C, (s32)D_800A6AB0, (s32)D_800A6B34,
};
