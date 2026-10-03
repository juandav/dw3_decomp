#include "common.h"
#include "stage.h"
void func_800A5DE4();
void func_800A5F64();
extern void (*D_800A664C[])(void);
extern s32 D_800A6174[][2];

/* Draws the 36 sprites of file 0x919 at their places, scrolling at 1/8 of the layer */
void func_800A5DE4(StageTask *task) {
    SpriteDrawer drawer;
    s32 pos[2];
    s32 scroll[2];
    Layer *layer;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        initSpriteDrawer(&drawer);
        drawer.setLayerId(0x1002, 0xC);
        drawer.setTexture(0x140, 0x100);
        drawer.setAltClut(0, 0x1F0);
        layer = GFX_FUNCS.getLayer(0x1002);
        layer->getScroll(layer, scroll);
        pos[0] = (scroll[0] - 0x2C0) >> 3;
        pos[1] = (scroll[1] - 0x280) >> 3;
        for (i = 0; i < 0x24; i++) {
            drawer.draw(FILE_CACHE.getEntry(0x9190000), 0, D_800A6174[i][0] + pos[0], D_800A6174[i][1] + pos[1]);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5F38(void) {
    return createTask(func_800A5DE4, 0x50, 0);
}

void func_800A5F64(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A5F38();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5FC8(void *owner) {
    StageTask *task = createTask(func_800A5F64, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A664C[0]();
    return task;
}

extern s32 D_800A6548[];
extern s32 D_800A655C[];
extern s32 D_800A6294[];
extern s32 D_800A6530[];
extern CVECTOR D_800A5DE0;
extern s32 D_800A6650[];
extern s32 D_800A6888[];
void func_800A6024(void) {
    D_800990B4.unk44 = LANGUAGE + 0x104;
    D_800990B4.unk8 = 0x1BE;
    D_800990B4.unkC = 0x9190000;
    D_800990B4.unk10 = D_800A6548;
    D_800990B4.unk14 = D_800A655C;
    D_800990B4.unk1C = 0x918;
    D_800990B4.unk2C = (Vec2){0x1AF00, 0x3B400};
    D_800990B4.unk28 = D_800A6294;
    D_800990B4.unk3C = 0xB;
    D_800990B4.unk40 = 0x602C0000;
    D_800990B4.unk4C = D_800A6530;
    D_800990B4.unk34 = 0;
    D_800990B4.unk38 = D_800A5DE0;
    D_800990B4.events = D_800A6650;
    D_800990B4.unk20 = D_800A6888;
    D_8009A70C.setFile(0, 0x9190002);
    D_8009A70C.setFile(1, 0x9190003);
    D_8009A70C.setFile(7, 0x9190004);
    D_8009A70C.setFile(4, 0x9190001);
    D_8009A70C.unk50(0);
}

void func_800A6024();
extern s32 D_800A6334[];
extern s32 D_800A6340[];
extern s32 D_800A634C[];
extern s32 D_800A6358[];
extern s32 D_800A6368[];
extern s32 D_800A6374[];
extern s32 D_800A637C[];
extern s32 D_800A6388[];
extern s32 D_800A6390[];
extern s32 D_800A6398[];
extern s32 D_800A63A0[];
extern s32 D_800A63AC[];
extern s32 D_800A63B8[];
extern s32 D_800A63C4[];
extern s32 D_800A63CC[];
extern s32 D_800A63D8[];
extern s32 D_800A63E4[];
extern s32 D_800A64BC[];
extern s32 D_800A63F0[];
extern s32 D_800A64C4[];
extern s32 D_800A6408[];
extern s32 D_800A6444[];
extern s32 D_800A645C[];
extern s32 D_800A648C[];
extern s32 D_800A64CC[];
extern s32 D_800A64E0[];
extern s32 D_800A64F4[];
extern s32 D_800A6508[];
extern s32 D_800A651C[];
extern s32 D_800A6678[];
extern s32 D_800A6684[];
extern s32 D_800A6690[];
extern s32 D_800A669C[];
extern s32 D_800A66A8[];
extern s32 D_800A66B4[];
extern s32 D_800A66C0[];
extern s32 D_800A66CC[];
extern s32 D_800A66FC[];
extern s32 D_800A6708[];
extern s32 D_800A6714[];
extern s32 D_800A6720[];
extern s32 D_800A672C[];
extern s32 D_800A6738[];
extern s32 D_800A6744[];
extern s32 D_800A6750[];
extern s32 D_800A6780[];
extern s32 D_800A678C[];
extern s32 D_800A6798[];
extern s32 D_800A67A4[];
extern s32 D_800A67B0[];
extern s32 D_800A67BC[];
extern s32 D_800A67C8[];
extern s32 D_800A67D4[];
extern s32 D_800A6804[];
extern s32 D_800A6810[];
extern s32 D_800A681C[];
extern s32 D_800A6828[];
extern s32 D_800A6834[];
extern s32 D_800A6840[];
extern s32 D_800A684C[];
extern s32 D_800A6858[];
extern s32 D_800A66D8[];
extern s32 D_800A675C[];
extern s32 D_800A67E0[];
extern s32 D_800A6864[];

s32 D_800A6174[][2] = {
    596, 399, 809, 564,
    820, 832, 1143, 1009,
    738, 1035, 416, 1055,
    36, 28, 140, 0,
    178, 159, 218, 202,
    186, 242, 299, 93,
    418, 16, 440, 329,
    476, 369, 725, 82,
    1137, 24, 1213, 103,
    1281, 147, 1349, 48,
    669, 632, 491, 796,
    661, 889, 624, 926,
    998, 634, 1026, 648,
    890, 940, 915, 959,
    826, 1119, 1028, 1089,
    1227, 1002, 1306, 861,
    498, 1190, 146, 569,
    187, 590, 394, 616,
};
s32 D_800A6294[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x100016A, 168, 0x1FF0140,
    0x1000140, 0x100015A, 104, 0x1FF0150,
    0x1000140, 0x1000150, 64, 0x1FF0160,
    0x1000140, 0x1000162, 136, 0x1FF0170,
};
s32 D_800A6334[] = {
    0x10011, 16, 65535,
};
s32 D_800A6340[] = {
    17, 0, 65535,
};
s32 D_800A634C[] = {
    0x10011, 0x10010, 65535,
};
s32 D_800A6358[] = {
    17, 16, 0, 65535,
};
s32 D_800A6368[] = {
    17, 0, 65535,
};
s32 D_800A6374[] = {
    0x10000, 65535,
};
s32 D_800A637C[] = {
    17, 0x10000, 65535,
};
s32 D_800A6388[] = {
    0x17842, 65535,
};
s32 D_800A6390[] = {
    0x17C01, 65535,
};
s32 D_800A6398[] = {
    28822, 65535,
};
s32 D_800A63A0[] = {
    0x17096, 4110, 65535,
};
s32 D_800A63AC[] = {
    0x17400, 0x1100E, 65535,
};
s32 D_800A63B8[] = {
    0x17096, 0x1100E, 65535,
};
s32 D_800A63C4[] = {
    28822, 65535,
};
s32 D_800A63CC[] = {
    0x17096, 4111, 65535,
};
s32 D_800A63D8[] = {
    0x1100F, 0x17401, 65535,
};
s32 D_800A63E4[] = {
    0x17096, 0x1100F, 65535,
};
s32 D_800A63F0[] = {
    0, 0, 57, 0,
    0, 0,
};
s32 D_800A6408[] = {
    (s32)D_800A6334, (s32)D_800A6340, 59, (s32)D_800A634C,
    (s32)D_800A6358, 60, (s32)D_800A6368, (s32)D_800A6374,
    57, (s32)D_800A637C, (s32)D_800A6388, 58,
    0, 0, 0,
};
s32 D_800A6444[] = {
    0, (s32)D_800A6390, 135, 0,
    0, 0,
};
s32 D_800A645C[] = {
    (s32)D_800A6398, 0, 129, (s32)D_800A63A0,
    (s32)D_800A63AC, 130, (s32)D_800A63B8, 0,
    131, 0, 0, 0,
};
s32 D_800A648C[] = {
    (s32)D_800A63C4, 0, 132, (s32)D_800A63CC,
    (s32)D_800A63D8, 133, (s32)D_800A63E4, 0,
    134, 0, 0, 0,
};
s32 D_800A64BC[] = {
    33170, 65535,
};
s32 D_800A64C4[] = {
    0x18192, 65535,
};
s32 D_800A64CC[] = {
    (s32)D_800A64BC, (s32)D_800A63F0, 0x40039, 0x1580140,
    7,
};
s32 D_800A64E0[] = {
    (s32)D_800A64C4, (s32)D_800A6408, 0x40039, 0x1580140,
    7,
};
s32 D_800A64F4[] = {
    0, (s32)D_800A6444, 0x5003D, 0xF20061,
    1,
};
s32 D_800A6508[] = {
    0, (s32)D_800A645C, 0x60090, 0x910431,
    1,
};
s32 D_800A651C[] = {
    0, (s32)D_800A648C, 0x70091, 0xDC0208,
    7,
};
s32 D_800A6530[] = {
    (s32)D_800A64CC, (s32)D_800A64E0, (s32)D_800A64F4, (s32)D_800A6508,
    (s32)D_800A651C, 0,
};
s32 D_800A6548[] = {
    0, 0, 0, 0,
    0,
};
s32 D_800A655C[] = {
    65535, 65535, 0x2940001, 0x880510,
    1, 0, 65535, 65535,
    0x80005, 0, 0, 0,
    65535, 65535, 0x40005, 0,
    0, 0, 65535, 65535,
    0x10006, 0, 0, 0,
    65535, 65535, 6, 0,
    0, 0, 65535, 65535,
    0x60004, 0, 0, 0,
    65535, 65535, 0x50004, 0,
    0, 0, 65535, 65535,
    0x90002, 0x1AF007E, 0, 0,
    65535, 65535, 0x90003, 0x117006D,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A664C[])(void) = {
    func_800A6024,
};
s32 D_800A6650[] = {
    9000, 0, 0, (s32)func_8008B258,
    0, -1, 0, 0,
    0, 0,
};
s32 D_800A6678[] = {
    46, 7, 0x60080000,
};
s32 D_800A6684[] = {
    46, 7, 0x60080000,
};
s32 D_800A6690[] = {
    150, 7, 0x60080000,
};
s32 D_800A669C[] = {
    150, 7, 0x60080000,
};
s32 D_800A66A8[] = {
    96, 7, 0x60080000,
};
s32 D_800A66B4[] = {
    96, 7, 0x60080000,
};
s32 D_800A66C0[] = {
    97, 7, 0x60080000,
};
s32 D_800A66CC[] = {
    97, 7, 0x60080000,
};
s32 D_800A66D8[] = {
    3, (s32)D_800A6678, (s32)D_800A6684, (s32)D_800A6690,
    (s32)D_800A669C, (s32)D_800A66A8, (s32)D_800A66B4, (s32)D_800A66C0,
    (s32)D_800A66CC,
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
    0, 0, 0x60040000,
};
s32 D_800A675C[] = {
    0, (s32)D_800A66FC, (s32)D_800A6708, (s32)D_800A6714,
    (s32)D_800A6720, (s32)D_800A672C, (s32)D_800A6738, (s32)D_800A6744,
    (s32)D_800A6750,
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
    0, 0, 0x60040000,
};
s32 D_800A67E0[] = {
    0, (s32)D_800A6780, (s32)D_800A678C, (s32)D_800A6798,
    (s32)D_800A67A4, (s32)D_800A67B0, (s32)D_800A67BC, (s32)D_800A67C8,
    (s32)D_800A67D4,
};
s32 D_800A6804[] = {
    306, 18, 0x608C0000,
};
s32 D_800A6810[] = {
    307, 18, 0x608C0000,
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
    0, 0, 0x60040000,
};
s32 D_800A6864[] = {
    0, (s32)D_800A6804, (s32)D_800A6810, (s32)D_800A681C,
    (s32)D_800A6828, (s32)D_800A6834, (s32)D_800A6840, (s32)D_800A684C,
    (s32)D_800A6858,
};
s32 D_800A6888[] = {
    387, 0, 0, (s32)D_800A66D8,
    (s32)D_800A675C, (s32)D_800A67E0, (s32)D_800A6864,
};
