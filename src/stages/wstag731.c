#include "common.h"
#include "stage.h"
void func_800A4D98();
extern void (*D_800A5834[])(void);
void func_800A4E84();
extern AnimFrame D_800A50A0[];

s32 func_800A4CA4(AnimState *anim, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        anim->timer -= dt;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A4CA4(anim, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A4D98(StageTileAnims *task) {
    StageTile *tile;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A50A0[0].duration;
        break;
    case TASK_RUN:
        tile = D_800990B4.unk10;
        frame = func_800A4CA4(&task->anims[0], D_800A50A0, 0);
        for (; tile->unk2 != 0; tile++) {
            if (tile->anim == 1) {
                tile->frame = frame;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A4E58(void) {
    return createTask(func_800A4D98, 0x54, 0);
}

void func_800A4E84(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4E58();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4EE8(void *owner) {
    StageTask *task = createTask(func_800A4E84, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5834[0]();
    return task;
}

extern s32 D_800A56AC[];
extern s32 D_800A5804[];
extern s32 D_800A50BC[];
extern s32 D_800A5678[];
extern s32 D_800A5838[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x6B8
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x6C7
#endif
void func_800A4F44(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A56AC;
    D_800990B4.unk14 = D_800A5804;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0xCE00, 0xDD00};
    D_800990B4.unk28 = D_800A50BC;
    D_800990B4.unk3C = 8;
    D_800990B4.unk40 = 0x60200000;
    D_800990B4.unk4C = D_800A5678;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A5838;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A4F44();
extern s32 D_800A513C[];
extern s32 D_800A5144[];
extern s32 D_800A514C[];
extern s32 D_800A5158[];
extern s32 D_800A5160[];
extern s32 D_800A5170[];
extern s32 D_800A5180[];
extern s32 D_800A5194[];
extern s32 D_800A519C[];
extern s32 D_800A51A8[];
extern s32 D_800A51B0[];
extern s32 D_800A51C0[];
extern s32 D_800A51D0[];
extern s32 D_800A51E4[];
extern s32 D_800A51EC[];
extern s32 D_800A51F8[];
extern s32 D_800A5200[];
extern s32 D_800A5210[];
extern s32 D_800A5220[];
extern s32 D_800A5234[];
extern s32 D_800A523C[];
extern s32 D_800A5248[];
extern s32 D_800A5250[];
extern s32 D_800A5260[];
extern s32 D_800A5270[];
extern s32 D_800A5284[];
extern s32 D_800A528C[];
extern s32 D_800A5298[];
extern s32 D_800A52A0[];
extern s32 D_800A52B0[];
extern s32 D_800A52C0[];
extern s32 D_800A52D4[];
extern s32 D_800A54A8[];
extern s32 D_800A52EC[];
extern s32 D_800A54B4[];
extern s32 D_800A5304[];
extern s32 D_800A54C0[];
extern s32 D_800A5340[];
extern s32 D_800A54D0[];
extern s32 D_800A5358[];
extern s32 D_800A54E0[];
extern s32 D_800A5394[];
extern s32 D_800A54F4[];
extern s32 D_800A53AC[];
extern s32 D_800A5508[];
extern s32 D_800A53E8[];
extern s32 D_800A5520[];
extern s32 D_800A5400[];
extern s32 D_800A5538[];
extern s32 D_800A543C[];
extern s32 D_800A5554[];
extern s32 D_800A5454[];
extern s32 D_800A5570[];
extern s32 D_800A5490[];
extern s32 D_800A5588[];
extern s32 D_800A559C[];
extern s32 D_800A55B0[];
extern s32 D_800A55C4[];
extern s32 D_800A55D8[];
extern s32 D_800A55EC[];
extern s32 D_800A5600[];
extern s32 D_800A5614[];
extern s32 D_800A5628[];
extern s32 D_800A563C[];
extern s32 D_800A5650[];
extern s32 D_800A5664[];
extern s32 D_800A502C[];

s32 D_800A502C[] = {
    0x20102, 0xCE01AD, 0x1000005, 0x1CD0015,
    0x10100BE, 0x10015, 0x1010001, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000005,
    0x3000006, 0x200001E, 0x10000, 0x20015,
    0x3000301, 0x101001E, 0x360015, 0x1010003,
    0x375032D, 0x3030002, 0x1010015, 0x370015,
    0x3000003, 0x304005A, 3088, 0,
#if VERSION_US
    0x3500000,
#elif VERSION_EU
    0,
#endif
};
AnimFrame D_800A50A0[] = {
    { 53, 8 }, { 54, 8 }, { 55, 8 }, { 56, 4 },
    { 57, 40 }, { 58, 8 }, { 255, 0 },
};
s32 D_800A50BC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x13C0172, 0x3C00C8, 0x1FC0170,
    0x1000140, 0x1D40160, 0xD40080, 0x1FB0150,
};
s32 D_800A513C[] = {
    0x19016, 65535,
};
s32 D_800A5144[] = {
    0x1869C, 65535,
};
s32 D_800A514C[] = {
    34460, 0, 65535,
};
s32 D_800A5158[] = {
    0x10000, 65535,
};
s32 D_800A5160[] = {
    34460, 0x10000, 33944, 65535,
};
s32 D_800A5170[] = {
    34460, 0x10000, 0x18498, 65535,
};
s32 D_800A5180[] = {
    0x1869C, 34459, 33944, 0x17013,
    65535,
};
s32 D_800A5194[] = {
    0x18690, 65535,
};
s32 D_800A519C[] = {
    34448, 1, 65535,
};
s32 D_800A51A8[] = {
    0x10001, 65535,
};
s32 D_800A51B0[] = {
    34448, 0x10001, 33932, 65535,
};
s32 D_800A51C0[] = {
    34448, 0x10001, 0x1848C, 65535,
};
s32 D_800A51D0[] = {
    0x18690, 34447, 33932, 0x17013,
    65535,
};
s32 D_800A51E4[] = {
    0x18677, 65535,
};
s32 D_800A51EC[] = {
    34423, 2, 65535,
};
s32 D_800A51F8[] = {
    0x10002, 65535,
};
s32 D_800A5200[] = {
    34423, 0x10002, 33907, 65535,
};
s32 D_800A5210[] = {
    34423, 0x10002, 0x18473, 65535,
};
s32 D_800A5220[] = {
    0x18677, 34422, 33907, 0x17013,
    65535,
};
s32 D_800A5234[] = {
    0x18683, 65535,
};
s32 D_800A523C[] = {
    34435, 3, 65535,
};
s32 D_800A5248[] = {
    0x10003, 65535,
};
s32 D_800A5250[] = {
    34435, 0x10003, 33919, 65535,
};
s32 D_800A5260[] = {
    34435, 0x10003, 0x1847F, 65535,
};
s32 D_800A5270[] = {
    0x18683, 34434, 33919, 0x17013,
    65535,
};
s32 D_800A5284[] = {
    0x18669, 65535,
};
s32 D_800A528C[] = {
    34409, 4, 65535,
};
s32 D_800A5298[] = {
    0x10004, 65535,
};
s32 D_800A52A0[] = {
    34409, 0x10004, 33893, 65535,
};
s32 D_800A52B0[] = {
    34409, 0x10004, 0x18465, 65535,
};
s32 D_800A52C0[] = {
    0x18669, 34408, 33893, 0x17013,
    65535,
};
s32 D_800A52D4[] = {
    0, (s32)D_800A513C, 719, 0,
    0, 0,
};
s32 D_800A52EC[] = {
    0, 0, 721, 0,
    0, 0,
};
s32 D_800A5304[] = {
    (s32)D_800A5144, 0, 778, (s32)D_800A514C,
    (s32)D_800A5158, 779, (s32)D_800A5160, 0,
    780, (s32)D_800A5170, (s32)D_800A5180, 781,
    0, 0, 0,
};
s32 D_800A5340[] = {
    0, 0, 790, 0,
    0, 0,
};
s32 D_800A5358[] = {
    (s32)D_800A5194, 0, 782, (s32)D_800A519C,
    (s32)D_800A51A8, 783, (s32)D_800A51B0, 0,
    784, (s32)D_800A51C0, (s32)D_800A51D0, 785,
    0, 0, 0,
};
s32 D_800A5394[] = {
    0, 0, 791, 0,
    0, 0,
};
s32 D_800A53AC[] = {
    (s32)D_800A51E4, 0, 786, (s32)D_800A51EC,
    (s32)D_800A51F8, 787, (s32)D_800A5200, 0,
    788, (s32)D_800A5210, (s32)D_800A5220, 789,
    0, 0, 0,
};
s32 D_800A53E8[] = {
    0, 0, 792, 0,
    0, 0,
};
s32 D_800A5400[] = {
    (s32)D_800A5234, 0, 793, (s32)D_800A523C,
    (s32)D_800A5248, 794, (s32)D_800A5250, 0,
    795, (s32)D_800A5260, (s32)D_800A5270, 796,
    0, 0, 0,
};
s32 D_800A543C[] = {
    0, 0, 797, 0,
    0, 0,
};
s32 D_800A5454[] = {
    (s32)D_800A5284, 0, 799, (s32)D_800A528C,
    (s32)D_800A5298, 800, (s32)D_800A52A0, 0,
    801, (s32)D_800A52B0, (s32)D_800A52C0, 802,
    0, 0, 0,
};
s32 D_800A5490[] = {
    0, 0, 798, 0,
    0, 0,
};
s32 D_800A54A8[] = {
    34459, 34460, 65535,
};
s32 D_800A54B4[] = {
    0x1869B, 34460, 65535,
};
s32 D_800A54C0[] = {
    34447, 0x1869C, 34448, 65535,
};
s32 D_800A54D0[] = {
    0x1869C, 0x1868F, 34448, 65535,
};
s32 D_800A54E0[] = {
    0x1869C, 0x18690, 34422, 34423,
    65535,
};
s32 D_800A54F4[] = {
    0x1869C, 0x18690, 0x18676, 34423,
    65535,
};
s32 D_800A5508[] = {
    0x1869C, 0x18690, 0x18677, 34434,
    34435, 65535,
};
s32 D_800A5520[] = {
    0x1869C, 0x18690, 0x18677, 0x18682,
    34435, 65535,
};
s32 D_800A5538[] = {
    34408, 0x1869C, 0x18690, 0x18677,
    0x18683, 34409, 65535,
};
s32 D_800A5554[] = {
    0x1869C, 0x18690, 0x18677, 0x18683,
    0x18668, 34409, 65535,
};
s32 D_800A5570[] = {
    0x1869C, 0x18690, 0x18677, 0x18683,
    0x18669, 65535,
};
s32 D_800A5588[] = {
    0, (s32)D_800A52D4, 0x40015, 0xBE01CD,
    1,
};
s32 D_800A559C[] = {
    (s32)D_800A54A8, (s32)D_800A52EC, 0x500C1, 0xB00130,
    1,
};
s32 D_800A55B0[] = {
    (s32)D_800A54B4, (s32)D_800A5304, 0x500C1, 0xB00130,
    1,
};
s32 D_800A55C4[] = {
    (s32)D_800A54C0, (s32)D_800A5340, 0x500C1, 0xB00130,
    1,
};
s32 D_800A55D8[] = {
    (s32)D_800A54D0, (s32)D_800A5358, 0x500C1, 0xB00130,
    1,
};
s32 D_800A55EC[] = {
    (s32)D_800A54E0, (s32)D_800A5394, 0x500C1, 0xB00130,
    1,
};
s32 D_800A5600[] = {
    (s32)D_800A54F4, (s32)D_800A53AC, 0x500C1, 0xB00130,
    1,
};
s32 D_800A5614[] = {
    (s32)D_800A5508, (s32)D_800A53E8, 0x500C1, 0xB00130,
    1,
};
s32 D_800A5628[] = {
    (s32)D_800A5520, (s32)D_800A5400, 0x500C1, 0xB00130,
    1,
};
s32 D_800A563C[] = {
    (s32)D_800A5538, (s32)D_800A543C, 0x500C1, 0xB00130,
    1,
};
s32 D_800A5650[] = {
    (s32)D_800A5554, (s32)D_800A5454, 0x500C1, 0xB00130,
    1,
};
s32 D_800A5664[] = {
    (s32)D_800A5570, (s32)D_800A5490, 0x500C1, 0xB00130,
    1,
};
s32 D_800A5678[] = {
    (s32)D_800A5588, (s32)D_800A559C, (s32)D_800A55B0, (s32)D_800A55C4,
    (s32)D_800A55D8, (s32)D_800A55EC, (s32)D_800A5600, (s32)D_800A5614,
    (s32)D_800A5628, (s32)D_800A563C, (s32)D_800A5650, (s32)D_800A5664,
    0,
};
s32 D_800A56AC[] = {
    0x2400001, 0x5000234, 0x7C0006, 112,
    0x10000, 0x2340240, 0x60500, 0x5300BB,
    0, 0x2400001, 0x3000241, 0x1D60006,
    34, 0x10000, 0x10256, 0,
    0x3C014F, 0, 0x6800101, 53,
    0x2060000, 136, 0x10000, 0x2330640,
    0x60300, 0x1C011C, 0, 0x6400001,
    0x3000233, 0x11E0006, 62, 0x10000,
    0x2330640, 0x60300, 0x2B0139, 0,
    0x6400001, 0x3000233, 0x13B0006, 77,
    0x10000, 0x2330640, 0x60300, 0x390156,
    0, 0x6400001, 0x3000233, 0x1590006,
    92, 0x10000, 0x320640, 0,
    0x1A0121, 0, 0x6400001, 50,
    0x1230000, 60, 0x10000, 0x320640,
    0, 0x28013D, 0, 0x6400001,
    50, 0x13F0000, 74, 0x10000,
    0x320640, 0, 0x36015A, 0,
    0x6400001, 50, 0x15C0000, 89,
    0x10000, 1088, 0, 0x900138,
    195, 0, 0, 0,
    0, 0,
};
s32 D_800A5804[] = {
    65535, 65535, 0x2D00001, 0xAC0318,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A5834[])(void) = {
    func_800A4F44,
};
s32 D_800A5838[] = {
    1236, (s32)D_800A502C,
#if VERSION_US
    0x1430005,
#elif VERSION_EU
    0x14A0005,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
