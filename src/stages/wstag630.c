#include "common.h"
#include "stage.h"
extern s32 D_800A53A0[];
extern s32 D_800A5934[];
extern u8 D_800A53BC[];
extern u8 D_800A5A58[];
extern u8 D_800A5980[];
void func_800A4D98();
extern void (*D_800A5AA0[])(void);
void func_800A4F30();
void func_800A4FF0();
extern AnimFrame D_800A50F8[];
extern AnimFrame D_800A512C[];
extern AnimFrame D_800A5160[];

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
    s32 frames[3];
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A50F8[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A512C[0].duration;
        task->anims[2].index = 0;
        task->anims[2].timer = D_800A5160[0].duration;
        break;
    case TASK_RUN:
        tile = D_800990B4.unk10;
        frames[0] = func_800A4CA4(&task->anims[0], D_800A50F8, 0);
        frames[1] = func_800A4CA4(&task->anims[1], D_800A512C, 0);
        frames[2] = func_800A4CA4(&task->anims[2], D_800A5160, 0);
        for (; tile->unk2 != 0; tile++) {
            switch (tile->anim) {
            case 1:
                tile->frame = frames[0];
                break;
            case 2:
                tile->frame = frames[1];
                break;
            case 3:
                tile->frame = frames[2];
                break;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A4F04(void) {
    return createTask(func_800A4D98, 0x5C, 0);
}

void func_800A4F30(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4F04();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A4F94(void *owner) {
    StageTask *task = createTask(func_800A4F30, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5AA0[0]();
    return task;
}

#if VERSION_US
void func_800A4FF0(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x483;
    D_800990B4.unkC = 0x4840000;
    D_800990B4.unk10 = D_800A5980;
    D_800990B4.unk14 = D_800A5A58;
    D_800990B4.unk1C = 0x482;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1AF00;
    D_800990B4.unk30 = 0x11800;
    D_800990B4.unk28 = D_800A53BC;
    D_800990B4.unk3C = 56;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A5934;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A53A0;
    D_8009A70C.setFile(0, 0x4840001);
    D_8009A70C.setFile(7, 0x4840002);
    D_8009A70C.setFile(4, 0x4840003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag630", func_800A4FF0);
#endif

extern s32 D_800A5190[];
extern s32 D_800A519C[];
extern s32 D_800A51A8[];
extern s32 D_800A51B4[];
extern s32 D_800A51C0[];
extern s32 D_800A51CC[];
extern s32 D_800A51D8[];
extern s32 D_800A51E4[];
extern s32 D_800A5214[];
extern s32 D_800A5220[];
extern s32 D_800A522C[];
extern s32 D_800A5238[];
extern s32 D_800A5244[];
extern s32 D_800A5250[];
extern s32 D_800A525C[];
extern s32 D_800A5268[];
extern s32 D_800A5298[];
extern s32 D_800A52A4[];
extern s32 D_800A52B0[];
extern s32 D_800A52BC[];
extern s32 D_800A52C8[];
extern s32 D_800A52D4[];
extern s32 D_800A52E0[];
extern s32 D_800A52EC[];
extern s32 D_800A531C[];
extern s32 D_800A5328[];
extern s32 D_800A5334[];
extern s32 D_800A5340[];
extern s32 D_800A534C[];
extern s32 D_800A5358[];
extern s32 D_800A5364[];
extern s32 D_800A5370[];
extern s32 D_800A51F0[];
extern s32 D_800A5274[];
extern s32 D_800A52F8[];
extern s32 D_800A537C[];
extern s32 D_800A543C[];
extern s32 D_800A5444[];
extern s32 D_800A544C[];
extern s32 D_800A5454[];
extern s32 D_800A545C[];
extern s32 D_800A5464[];
extern s32 D_800A546C[];
extern s32 D_800A5474[];
extern s32 D_800A547C[];
extern s32 D_800A5484[];
extern s32 D_800A548C[];
extern s32 D_800A5494[];
extern s32 D_800A549C[];
extern s32 D_800A54A4[];
extern s32 D_800A54AC[];
extern s32 D_800A54B4[];
extern s32 D_800A54BC[];
extern s32 D_800A54C4[];
extern s32 D_800A54CC[];
extern s32 D_800A54D4[];
extern s32 D_800A54DC[];
extern s32 D_800A54E4[];
extern s32 D_800A54EC[];
extern s32 D_800A54F4[];
extern s32 D_800A54FC[];
extern s32 D_800A5504[];
extern s32 D_800A5728[];
extern s32 D_800A550C[];
extern s32 D_800A5730[];
extern s32 D_800A5524[];
extern s32 D_800A5738[];
extern s32 D_800A5548[];
extern s32 D_800A5740[];
extern s32 D_800A5560[];
extern s32 D_800A5748[];
extern s32 D_800A5578[];
extern s32 D_800A5750[];
extern s32 D_800A5590[];
extern s32 D_800A5758[];
extern s32 D_800A55A8[];
extern s32 D_800A5764[];
extern s32 D_800A55C0[];
extern s32 D_800A576C[];
extern s32 D_800A55D8[];
extern s32 D_800A577C[];
extern s32 D_800A55F0[];
extern s32 D_800A5784[];
extern s32 D_800A5614[];
extern s32 D_800A578C[];
extern s32 D_800A562C[];
extern s32 D_800A5794[];
extern s32 D_800A5650[];
extern s32 D_800A579C[];
extern s32 D_800A5674[];
extern s32 D_800A57A4[];
extern s32 D_800A5698[];
extern s32 D_800A57AC[];
extern s32 D_800A56BC[];
extern s32 D_800A57B4[];
extern s32 D_800A56E0[];
extern s32 D_800A57C4[];
extern s32 D_800A5704[];
extern s32 D_800A57CC[];
extern s32 D_800A57E0[];
extern s32 D_800A57F4[];
extern s32 D_800A5808[];
extern s32 D_800A581C[];
extern s32 D_800A5830[];
extern s32 D_800A5844[];
extern s32 D_800A5858[];
extern s32 D_800A586C[];
extern s32 D_800A5880[];
extern s32 D_800A5894[];
extern s32 D_800A58A8[];
extern s32 D_800A58BC[];
extern s32 D_800A58D0[];
extern s32 D_800A58E4[];
extern s32 D_800A58F8[];
extern s32 D_800A590C[];
extern s32 D_800A5920[];

AnimFrame D_800A50F8[] = {
    { 50, 8 }, { 51, 8 }, { 52, 8 }, { 53, 8 },
    { 54, 8 }, { 55, 8 }, { 56, 8 }, { 57, 8 },
    { 58, 8 }, { 59, 8 }, { 60, 8 }, { 82, 160 },
    { 255, 0 },
};
AnimFrame D_800A512C[] = {
    { 61, 8 }, { 62, 8 }, { 63, 8 }, { 64, 8 },
    { 65, 8 }, { 66, 8 }, { 67, 8 }, { 68, 8 },
    { 69, 8 }, { 70, 8 }, { 71, 8 }, { 82, 160 },
    { 255, 0 },
};
AnimFrame D_800A5160[] = {
    { 72, 8 }, { 73, 8 }, { 74, 8 }, { 75, 8 },
    { 76, 8 }, { 77, 8 }, { 78, 8 }, { 79, 8 },
    { 80, 8 }, { 81, 8 }, { 82, 160 }, { 255, 0 },
};
s32 D_800A5190[] = {
    156, 5, 0x60080000,
};
s32 D_800A519C[] = {
    156, 5, 0x60080000,
};
s32 D_800A51A8[] = {
    156, 5, 0x60080000,
};
s32 D_800A51B4[] = {
    156, 5, 0x60080000,
};
s32 D_800A51C0[] = {
    156, 5, 0x60080000,
};
s32 D_800A51CC[] = {
    156, 5, 0x60080000,
};
s32 D_800A51D8[] = {
    156, 5, 0x60080000,
};
s32 D_800A51E4[] = {
    156, 5, 0x60080000,
};
s32 D_800A51F0[] = {
    3, (s32)D_800A5190, (s32)D_800A519C, (s32)D_800A51A8,
    (s32)D_800A51B4, (s32)D_800A51C0, (s32)D_800A51CC, (s32)D_800A51D8,
    (s32)D_800A51E4,
};
s32 D_800A5214[] = {
    0, 0, 0x60040000,
};
s32 D_800A5220[] = {
    0, 0, 0x60040000,
};
s32 D_800A522C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5238[] = {
    0, 0, 0x60040000,
};
s32 D_800A5244[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5214, (s32)D_800A5220, (s32)D_800A522C,
    (s32)D_800A5238, (s32)D_800A5244, (s32)D_800A5250, (s32)D_800A525C,
    (s32)D_800A5268,
};
s32 D_800A5298[] = {
    0, 0, 0x60040000,
};
s32 D_800A52A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A52B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A52BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A52C8[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A5298, (s32)D_800A52A4, (s32)D_800A52B0,
    (s32)D_800A52BC, (s32)D_800A52C8, (s32)D_800A52D4, (s32)D_800A52E0,
    (s32)D_800A52EC,
};
s32 D_800A531C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5328[] = {
    0, 0, 0x60040000,
};
s32 D_800A5334[] = {
    0, 0, 0x60040000,
};
s32 D_800A5340[] = {
    0, 0, 0x60040000,
};
s32 D_800A534C[] = {
    0, 0, 0x60040000,
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
    0, (s32)D_800A531C, (s32)D_800A5328, (s32)D_800A5334,
    (s32)D_800A5340, (s32)D_800A534C, (s32)D_800A5358, (s32)D_800A5364,
    (s32)D_800A5370,
};
s32 D_800A53A0[] = {
    36, 0, 0, (s32)D_800A51F0,
    (s32)D_800A5274, (s32)D_800A52F8, (s32)D_800A537C,
};
u8 D_800A53BC[] = {
    0x00, 0x02, 0x00, 0x01, 0x1C, 0x02, 0xA6, 0x01,
    0x70, 0x00, 0xA6, 0x00, 0x30, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x16, 0x02, 0x38, 0x01,
    0x58, 0x00, 0x38, 0x00, 0x00, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x08, 0x02, 0xBC, 0x01,
    0x20, 0x00, 0xBC, 0x00, 0x10, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x10, 0x02, 0xBC, 0x01,
    0x40, 0x00, 0xBC, 0x00, 0x20, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0xBC, 0x01,
    0x00, 0x00, 0xBC, 0x00, 0x30, 0x02, 0xFD, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x88, 0x01, 0x00, 0x01,
    0x20, 0x01, 0x00, 0x00, 0x70, 0x01, 0xFF, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x90, 0x01, 0x00, 0x01,
    0x40, 0x01, 0x00, 0x00, 0x40, 0x01, 0xFE, 0x01,
};
s32 D_800A543C[] = {
    7196, 65535,
};
s32 D_800A5444[] = {
    0x11C1C, 65535,
};
s32 D_800A544C[] = {
    0, 65535,
};
s32 D_800A5454[] = {
    0x10000, 65535,
};
s32 D_800A545C[] = {
    0x10000, 65535,
};
s32 D_800A5464[] = {
    0, 65535,
};
s32 D_800A546C[] = {
    0x10000, 65535,
};
s32 D_800A5474[] = {
    0x10000, 65535,
};
s32 D_800A547C[] = {
    0, 65535,
};
s32 D_800A5484[] = {
    0x10000, 65535,
};
s32 D_800A548C[] = {
    0x10000, 65535,
};
s32 D_800A5494[] = {
    0, 65535,
};
s32 D_800A549C[] = {
    0x10000, 65535,
};
s32 D_800A54A4[] = {
    0x10000, 65535,
};
s32 D_800A54AC[] = {
    0, 65535,
};
s32 D_800A54B4[] = {
    0x10000, 65535,
};
s32 D_800A54BC[] = {
    0x10000, 65535,
};
s32 D_800A54C4[] = {
    0, 65535,
};
s32 D_800A54CC[] = {
    0x10000, 65535,
};
s32 D_800A54D4[] = {
    0x10000, 65535,
};
s32 D_800A54DC[] = {
    0, 65535,
};
s32 D_800A54E4[] = {
    0x10000, 65535,
};
s32 D_800A54EC[] = {
    0x10000, 65535,
};
s32 D_800A54F4[] = {
    0, 65535,
};
s32 D_800A54FC[] = {
    0x10000, 65535,
};
s32 D_800A5504[] = {
    0x10000, 65535,
};
s32 D_800A550C[] = {
    0, 0, 114, 0,
    0, 0,
};
s32 D_800A5524[] = {
    (s32)D_800A543C, 0, 441, (s32)D_800A5444,
    0, 74, 0, 0,
    0,
};
s32 D_800A5548[] = {
    0, 0, 445, 0,
    0, 0,
};
s32 D_800A5560[] = {
    0, 0, 444, 0,
    0, 0,
};
s32 D_800A5578[] = {
    0, 0, 443, 0,
    0, 0,
};
s32 D_800A5590[] = {
    0, 0, 442, 0,
    0, 0,
};
s32 D_800A55A8[] = {
    0, 0, 441, 0,
    0, 0,
};
s32 D_800A55C0[] = {
    0, 0, 115, 0,
    0, 0,
};
s32 D_800A55D8[] = {
    0, 0, 430, 0,
    0, 0,
};
s32 D_800A55F0[] = {
    (s32)D_800A544C, (s32)D_800A5454, 447, (s32)D_800A545C,
    0, 4, 0, 0,
    0,
};
s32 D_800A5614[] = {
    0, 0, 455, 0,
    0, 0,
};
s32 D_800A562C[] = {
    (s32)D_800A5464, (s32)D_800A546C, 454, (s32)D_800A5474,
    0, 4, 0, 0,
    0,
};
s32 D_800A5650[] = {
    (s32)D_800A547C, (s32)D_800A5484, 453, (s32)D_800A548C,
    0, 4, 0, 0,
    0,
};
s32 D_800A5674[] = {
    (s32)D_800A5494, (s32)D_800A549C, 452, (s32)D_800A54A4,
    0, 4, 0, 0,
    0,
};
s32 D_800A5698[] = {
    (s32)D_800A54AC, (s32)D_800A54B4, 451, (s32)D_800A54BC,
    0, 4, 0, 0,
    0,
};
s32 D_800A56BC[] = {
    (s32)D_800A54C4, (s32)D_800A54CC, 450, (s32)D_800A54D4,
    0, 4, 0, 0,
    0,
};
s32 D_800A56E0[] = {
    (s32)D_800A54DC, (s32)D_800A54E4, 449, (s32)D_800A54EC,
    0, 4, 0, 0,
    0,
};
s32 D_800A5704[] = {
    (s32)D_800A54F4, (s32)D_800A54FC, 448, (s32)D_800A5504,
    0, 4, 0, 0,
    0,
};
s32 D_800A5728[] = {
    0x1600F, 65535,
};
s32 D_800A5730[] = {
    0x16014, 65535,
};
s32 D_800A5738[] = {
    0x1701A, 65535,
};
s32 D_800A5740[] = {
    0x16026, 65535,
};
s32 D_800A5748[] = {
    0x17019, 65535,
};
s32 D_800A5750[] = {
    0x17018, 65535,
};
s32 D_800A5758[] = {
    0x17017, 24596, 65535,
};
s32 D_800A5764[] = {
    0x16010, 65535,
};
s32 D_800A576C[] = {
    0x17016, 24592, 24591, 65535,
};
s32 D_800A577C[] = {
    0x1600F, 65535,
};
s32 D_800A5784[] = {
    0x1602B, 65535,
};
s32 D_800A578C[] = {
    0x1701A, 65535,
};
s32 D_800A5794[] = {
    0x16026, 65535,
};
s32 D_800A579C[] = {
    0x17019, 65535,
};
s32 D_800A57A4[] = {
    0x17018, 65535,
};
s32 D_800A57AC[] = {
    0x17017, 65535,
};
s32 D_800A57B4[] = {
    24591, 24592, 0x17016, 65535,
};
s32 D_800A57C4[] = {
    0x16010, 65535,
};
s32 D_800A57CC[] = {
    (s32)D_800A5728, (s32)D_800A550C, 0x40022, 0x11801B1,
    7,
};
s32 D_800A57E0[] = {
    (s32)D_800A5730, (s32)D_800A5524, 0x40022, 0x11801B1,
    7,
};
s32 D_800A57F4[] = {
    (s32)D_800A5738, (s32)D_800A5548, 0x40022, 0x11801B1,
    7,
};
s32 D_800A5808[] = {
    (s32)D_800A5740, (s32)D_800A5560, 0x40022, 0x11801B1,
    7,
};
s32 D_800A581C[] = {
    (s32)D_800A5748, (s32)D_800A5578, 0x40022, 0x11801B1,
    7,
};
s32 D_800A5830[] = {
    (s32)D_800A5750, (s32)D_800A5590, 0x40022, 0x11801B1,
    7,
};
s32 D_800A5844[] = {
    (s32)D_800A5758, (s32)D_800A55A8, 0x40022, 0x11801B1,
    7,
};
s32 D_800A5858[] = {
    (s32)D_800A5764, (s32)D_800A55C0, 0x40022, 0x11801B1,
    7,
};
s32 D_800A586C[] = {
    (s32)D_800A576C, (s32)D_800A55D8, 0x40022, 0x11801B1,
    7,
};
s32 D_800A5880[] = {
    (s32)D_800A577C, (s32)D_800A55F0, 0x50040, 0x21901B1,
    1,
};
s32 D_800A5894[] = {
    (s32)D_800A5784, (s32)D_800A5614, 0x50040, 0x21901B1,
    1,
};
s32 D_800A58A8[] = {
    (s32)D_800A578C, (s32)D_800A562C, 0x50040, 0x21901B1,
    1,
};
s32 D_800A58BC[] = {
    (s32)D_800A5794, (s32)D_800A5650, 0x50040, 0x21901B1,
    1,
};
s32 D_800A58D0[] = {
    (s32)D_800A579C, (s32)D_800A5674, 0x50040, 0x21901B1,
    1,
};
s32 D_800A58E4[] = {
    (s32)D_800A57A4, (s32)D_800A5698, 0x50040, 0x21901B1,
    1,
};
s32 D_800A58F8[] = {
    (s32)D_800A57AC, (s32)D_800A56BC, 0x50040, 0x21901B1,
    1,
};
s32 D_800A590C[] = {
    (s32)D_800A57B4, (s32)D_800A56E0, 0x50040, 0x21901B1,
    1,
};
s32 D_800A5920[] = {
    (s32)D_800A57C4, (s32)D_800A5704, 0x50040, 0x21901B1,
    1,
};
s32 D_800A5934[] = {
    (s32)D_800A57CC, (s32)D_800A57E0, (s32)D_800A57F4, (s32)D_800A5808,
    (s32)D_800A581C, (s32)D_800A5830, (s32)D_800A5844, (s32)D_800A5858,
    (s32)D_800A586C, (s32)D_800A5880, (s32)D_800A5894, (s32)D_800A58A8,
    (s32)D_800A58BC, (s32)D_800A58D0, (s32)D_800A58E4, (s32)D_800A58F8,
    (s32)D_800A590C, (s32)D_800A5920, 0,
};
u8 D_800A5980[] = {
    0x01, 0x03, 0x40, 0x02, 0x48, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x2E, 0x01, 0x8C, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x40, 0x06, 0x3D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xCC, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x06,
    0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x01,
    0x78, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x40, 0x06, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x56, 0x01, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x40, 0x06, 0x32, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5C, 0x02, 0x9D, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x40, 0x06, 0x3D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xD6, 0x02, 0x3A, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x06,
    0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x02,
    0xAE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x40, 0x06, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x02, 0x40, 0x06, 0x3D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xB5, 0x03, 0x4D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1D, 0x02, 0x13, 0x01,
    0x46, 0x01, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x01,
    0xCB, 0x01, 0xFD, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5A58[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x48, 0x02, 0x90, 0x00, 0x40, 0x05,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x58, 0x02, 0x40, 0x03, 0xF0, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A5AA0[])(void) = {
    func_800A4FF0,
};
