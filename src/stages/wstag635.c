#include "common.h"
#include "stage.h"
extern s32 D_800A5734[];
extern s32 D_800A5C78[];
extern u8 D_800A5750[];
extern u8 D_800A5DF8[];
extern u8 D_800A5CA0[];
void func_800A4D98();
extern void (*D_800A5E70[])(void);
void func_800A5030();
void func_800A5114();
extern AnimFrame D_800A521C[];
extern StagePoints *D_800A54FC[];
extern AnimFrame D_800A5250[];
extern AnimFrame D_800A5284[];

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
        task->anims[0].timer = D_800A521C[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A5250[0].duration;
        task->anims[2].index = 0;
        task->anims[2].timer = D_800A5284[0].duration;
        break;
    case TASK_RUN:
        tile = D_800990B4.unk10;
        frames[0] = func_800A4CA4(&task->anims[0], D_800A521C, 0);
        frames[1] = func_800A4CA4(&task->anims[1], D_800A5250, 0);
        frames[2] = func_800A4CA4(&task->anims[2], D_800A5284, 0);
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

/* Copies the points of the place (id0, id1) in LIST to SLOTS */
void func_800A4F30(StageSlot *slots, StagePoints **list, s32 id0, s32 id1) {
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

void func_800A5030(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4F04();
        func_800A4F30(D_800990B4.unk14, D_800A54FC, GAME.unk44, GAME.unk46);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A50B8(void *owner) {
    StageTask *task = createTask(func_800A5030, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A5E70[0]();
    return task;
}

#if VERSION_US
void func_800A5114(void) {
    D_800990B4.unk44 = 0xDB;
    D_800990B4.unk8 = 0x48B;
    D_800990B4.unkC = 0x48C0000;
    D_800990B4.unk10 = D_800A5CA0;
    D_800990B4.unk14 = D_800A5DF8;
    D_800990B4.unk1C = 0x48A;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x20900;
    D_800990B4.unk30 = 0x31B00;
    D_800990B4.unk28 = D_800A5750;
    D_800990B4.unk3C = 56;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk4C = D_800A5C78;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5734;
    D_8009A70C.unk40(0, 0x48C0001);
    D_8009A70C.unk40(7, 0x48C0002);
    D_8009A70C.unk40(4, 0x48C0003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag635", func_800A5114);
#endif

extern StagePoint D_800A52B4;
extern StagePoint D_800A52C4;
extern StagePoint D_800A52D4;
extern StagePoint D_800A52E4;
extern StagePoint D_800A52FC;
extern StagePoint D_800A530C;
extern StagePoint D_800A531C;
extern StagePoint D_800A532C;
extern StagePoint D_800A5344;
extern StagePoint D_800A5354;
extern StagePoint D_800A5364;
extern StagePoint D_800A5374;
extern StagePoint D_800A538C;
extern StagePoint D_800A539C;
extern StagePoint D_800A53AC;
extern StagePoint D_800A53BC;
extern StagePoint D_800A53D4;
extern StagePoint D_800A53E4;
extern StagePoint D_800A53F4;
extern StagePoint D_800A5404;
extern StagePoint D_800A541C;
extern StagePoint D_800A542C;
extern StagePoint D_800A543C;
extern StagePoint D_800A544C;
extern StagePoint D_800A5464;
extern StagePoint D_800A5474;
extern StagePoint D_800A5484;
extern StagePoint D_800A5494;
extern StagePoint D_800A54AC;
extern StagePoint D_800A54BC;
extern StagePoint D_800A54CC;
extern StagePoint D_800A54DC;
extern StagePoints D_800A52F4;
extern StagePoints D_800A533C;
extern StagePoints D_800A5384;
extern StagePoints D_800A53CC;
extern StagePoints D_800A5414;
extern StagePoints D_800A545C;
extern StagePoints D_800A54A4;
extern StagePoints D_800A54EC;
extern StagePoints D_800A54F4;
extern s32 D_800A5524[];
extern s32 D_800A5530[];
extern s32 D_800A553C[];
extern s32 D_800A5548[];
extern s32 D_800A5554[];
extern s32 D_800A5560[];
extern s32 D_800A556C[];
extern s32 D_800A5578[];
extern s32 D_800A55A8[];
extern s32 D_800A55B4[];
extern s32 D_800A55C0[];
extern s32 D_800A55CC[];
extern s32 D_800A55D8[];
extern s32 D_800A55E4[];
extern s32 D_800A55F0[];
extern s32 D_800A55FC[];
extern s32 D_800A562C[];
extern s32 D_800A5638[];
extern s32 D_800A5644[];
extern s32 D_800A5650[];
extern s32 D_800A565C[];
extern s32 D_800A5668[];
extern s32 D_800A5674[];
extern s32 D_800A5680[];
extern s32 D_800A56B0[];
extern s32 D_800A56BC[];
extern s32 D_800A56C8[];
extern s32 D_800A56D4[];
extern s32 D_800A56E0[];
extern s32 D_800A56EC[];
extern s32 D_800A56F8[];
extern s32 D_800A5704[];
extern s32 D_800A5584[];
extern s32 D_800A5608[];
extern s32 D_800A568C[];
extern s32 D_800A5710[];
extern s32 D_800A5810[];
extern s32 D_800A5818[];
extern s32 D_800A5820[];
extern s32 D_800A582C[];
extern s32 D_800A583C[];
extern s32 D_800A5850[];
extern s32 D_800A5858[];
extern s32 D_800A586C[];
extern s32 D_800A5874[];
extern s32 D_800A5880[];
extern s32 D_800A5888[];
extern s32 D_800A5890[];
extern s32 D_800A5898[];
extern s32 D_800A58A4[];
extern s32 D_800A58B4[];
extern s32 D_800A58C8[];
extern s32 D_800A58D0[];
extern s32 D_800A58E4[];
extern s32 D_800A58EC[];
extern s32 D_800A58F8[];
extern s32 D_800A5900[];
extern s32 D_800A5908[];
extern s32 D_800A5910[];
extern s32 D_800A591C[];
extern s32 D_800A592C[];
extern s32 D_800A5940[];
extern s32 D_800A5948[];
extern s32 D_800A595C[];
extern s32 D_800A5964[];
extern s32 D_800A5970[];
extern s32 D_800A5B04[];
extern s32 D_800A5978[];
extern s32 D_800A5B1C[];
extern s32 D_800A59C0[];
extern s32 D_800A5B34[];
extern s32 D_800A59E4[];
extern s32 D_800A5B4C[];
extern s32 D_800A5A2C[];
extern s32 D_800A5B64[];
extern s32 D_800A5A50[];
extern s32 D_800A5B74[];
extern s32 D_800A5A68[];
extern s32 D_800A5B84[];
extern s32 D_800A5A80[];
extern s32 D_800A5B94[];
extern s32 D_800A5A98[];
extern s32 D_800A5BAC[];
extern s32 D_800A5AE0[];
extern s32 D_800A5BC4[];
extern s32 D_800A5BD8[];
extern s32 D_800A5BEC[];
extern s32 D_800A5C00[];
extern s32 D_800A5C14[];
extern s32 D_800A5C28[];
extern s32 D_800A5C3C[];
extern s32 D_800A5C50[];
extern s32 D_800A5C64[];

AnimFrame D_800A521C[] = {
    { 50, 8 }, { 51, 8 }, { 52, 8 }, { 53, 8 },
    { 54, 8 }, { 55, 8 }, { 56, 8 }, { 57, 8 },
    { 58, 8 }, { 59, 8 }, { 60, 8 }, { 82, 160 },
    { 255, 0 },
};
AnimFrame D_800A5250[] = {
    { 61, 8 }, { 62, 8 }, { 63, 8 }, { 64, 8 },
    { 65, 8 }, { 66, 8 }, { 67, 8 }, { 68, 8 },
    { 69, 8 }, { 70, 8 }, { 71, 8 }, { 82, 160 },
    { 255, 0 },
};
AnimFrame D_800A5284[] = {
    { 72, 8 }, { 73, 8 }, { 74, 8 }, { 75, 8 },
    { 76, 8 }, { 77, 8 }, { 78, 8 }, { 79, 8 },
    { 80, 8 }, { 81, 8 }, { 82, 160 }, { 255, 0 },
};
StagePoint D_800A52B4 = { 0x259, 1, 2, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A52C4 = { 0x259, 1, 3, 0x358, 252, 1, &D_800A52B4 };
StagePoint D_800A52D4 = { 0x259, 1, 1, 0x120, 0x100, 7, &D_800A52C4 };
StagePoint D_800A52E4 = { 0x257, 0, 0, 0x100, 0x278, 5, &D_800A52D4 };
StagePoints D_800A52F4 = { 1, 1, &D_800A52E4 };
StagePoint D_800A52FC = { 0x259, 1, 1, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A530C = { 0x259, 1, 4, 0x358, 252, 1, &D_800A52FC };
StagePoint D_800A531C = { 0x259, 1, 2, 0x120, 0x100, 7, &D_800A530C };
StagePoint D_800A532C = { 0x257, 0, 0, 0x100, 0x278, 5, &D_800A531C };
StagePoints D_800A533C = { 1, 2, &D_800A532C };
StagePoint D_800A5344 = { 0x259, 1, 3, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A5354 = { 0x259, 1, 5, 0x358, 252, 1, &D_800A5344 };
StagePoint D_800A5364 = { 0x259, 1, 4, 0x120, 0x100, 7, &D_800A5354 };
StagePoint D_800A5374 = { 0x259, 1, 1, 0x118, 0x2EC, 5, &D_800A5364 };
StagePoints D_800A5384 = { 1, 3, &D_800A5374 };
StagePoint D_800A538C = { 0x259, 1, 4, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A539C = { 0x259, 1, 6, 0x358, 252, 1, &D_800A538C };
StagePoint D_800A53AC = { 0x259, 1, 3, 0x120, 0x100, 7, &D_800A539C };
StagePoint D_800A53BC = { 0x259, 1, 2, 0x118, 0x2EC, 5, &D_800A53AC };
StagePoints D_800A53CC = { 1, 4, &D_800A53BC };
StagePoint D_800A53D4 = { 0x259, 1, 6, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A53E4 = { 0x259, 1, 7, 0x358, 252, 1, &D_800A53D4 };
StagePoint D_800A53F4 = { 0x259, 1, 5, 0x120, 0x100, 7, &D_800A53E4 };
StagePoint D_800A5404 = { 0x259, 1, 3, 0x118, 0x2EC, 5, &D_800A53F4 };
StagePoints D_800A5414 = { 1, 5, &D_800A5404 };
StagePoint D_800A541C = { 0x25A, 0, 0, 0x2F8, 0x244, 3, NULL };
StagePoint D_800A542C = { 0x259, 1, 8, 0x358, 252, 1, &D_800A541C };
StagePoint D_800A543C = { 0x259, 1, 6, 0x120, 0x100, 7, &D_800A542C };
StagePoint D_800A544C = { 0x259, 1, 4, 0x118, 0x2EC, 5, &D_800A543C };
StagePoints D_800A545C = { 1, 6, &D_800A544C };
StagePoint D_800A5464 = { 0x259, 1, 7, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A5474 = { 0x259, 1, 1, 0x358, 252, 1, &D_800A5464 };
StagePoint D_800A5484 = { 0x259, 1, 8, 0x120, 0x100, 7, &D_800A5474 };
StagePoint D_800A5494 = { 0x259, 1, 5, 0x118, 0x2EC, 5, &D_800A5484 };
StagePoints D_800A54A4 = { 1, 7, &D_800A5494 };
StagePoint D_800A54AC = { 0x259, 1, 8, 0x350, 0x2F8, 3, NULL };
StagePoint D_800A54BC = { 0x259, 1, 2, 0x358, 252, 1, &D_800A54AC };
StagePoint D_800A54CC = { 0x259, 1, 7, 0x120, 0x100, 7, &D_800A54BC };
StagePoint D_800A54DC = { 0x259, 1, 6, 0x118, 0x2EC, 5, &D_800A54CC };
StagePoints D_800A54EC = { 1, 8, &D_800A54DC };
StagePoints D_800A54F4 = { 0, 0, &D_800A52E4 };
StagePoints *D_800A54FC[] = {
    &D_800A52F4, &D_800A533C, &D_800A5384, &D_800A53CC,
    &D_800A5414, &D_800A545C, &D_800A54A4, &D_800A54EC,
    &D_800A54F4, NULL,
};
s32 D_800A5524[] = {
    73, 5, 0x60080000,
};
s32 D_800A5530[] = {
    73, 5, 0x60080000,
};
s32 D_800A553C[] = {
    73, 5, 0x60080000,
};
s32 D_800A5548[] = {
    74, 5, 0x60080000,
};
s32 D_800A5554[] = {
    74, 5, 0x60080000,
};
s32 D_800A5560[] = {
    74, 5, 0x60080000,
};
s32 D_800A556C[] = {
    156, 5, 0x60080000,
};
s32 D_800A5578[] = {
    156, 5, 0x60080000,
};
s32 D_800A5584[] = {
    3, (s32)D_800A5524, (s32)D_800A5530, (s32)D_800A553C,
    (s32)D_800A5548, (s32)D_800A5554, (s32)D_800A5560, (s32)D_800A556C,
    (s32)D_800A5578,
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
    0, 0, 0x60040000,
};
s32 D_800A5608[] = {
    0, (s32)D_800A55A8, (s32)D_800A55B4, (s32)D_800A55C0,
    (s32)D_800A55CC, (s32)D_800A55D8, (s32)D_800A55E4, (s32)D_800A55F0,
    (s32)D_800A55FC,
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
    0, 0, 0x60040000,
};
s32 D_800A568C[] = {
    0, (s32)D_800A562C, (s32)D_800A5638, (s32)D_800A5644,
    (s32)D_800A5650, (s32)D_800A565C, (s32)D_800A5668, (s32)D_800A5674,
    (s32)D_800A5680,
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
    0, 0, 0x60040000,
};
s32 D_800A5710[] = {
    0, (s32)D_800A56B0, (s32)D_800A56BC, (s32)D_800A56C8,
    (s32)D_800A56D4, (s32)D_800A56E0, (s32)D_800A56EC, (s32)D_800A56F8,
    (s32)D_800A5704,
};
s32 D_800A5734[] = {
    37, 0, 0, (s32)D_800A5584,
    (s32)D_800A5608, (s32)D_800A568C, (s32)D_800A5710,
};
u8 D_800A5750[] = {
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
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x60, 0x01,
    0xD8, 0x00, 0x60, 0x00, 0x70, 0x01, 0xFF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x88, 0x01,
    0xD8, 0x00, 0x88, 0x00, 0x40, 0x01, 0xFE, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xB0, 0x01, 0x88, 0x01,
    0xC0, 0x01, 0x88, 0x00, 0x50, 0x01, 0xFE, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x88, 0x01, 0x94, 0x01,
    0x20, 0x01, 0x94, 0x00, 0x60, 0x01, 0xFE, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x80, 0x01, 0x9C, 0x01,
    0x00, 0x01, 0x9C, 0x00, 0x70, 0x01, 0xFE, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xB6, 0x01, 0x00, 0x01,
    0xD8, 0x01, 0x00, 0x00, 0x40, 0x01, 0xFD, 0x01,
};
s32 D_800A5810[] = {
    6703, 65535,
};
s32 D_800A5818[] = {
    0x11A2F, 65535,
};
s32 D_800A5820[] = {
    0x11A2F, 28718, 65535,
};
s32 D_800A582C[] = {
    0x11A2F, 0x1702E, 28711, 65535,
};
s32 D_800A583C[] = {
    0x11A2F, 0x1702E, 0x17027, 28713,
    65535,
};
s32 D_800A5850[] = {
    0x10604, 65535,
};
s32 D_800A5858[] = {
    0x11A2F, 0x1702E, 0x17027, 0x17029,
    65535,
};
s32 D_800A586C[] = {
    28688, 65535,
};
s32 D_800A5874[] = {
    0x17037, 0x17013, 65535,
};
s32 D_800A5880[] = {
    0x17010, 65535,
};
s32 D_800A5888[] = {
    6704, 65535,
};
s32 D_800A5890[] = {
    0x11A30, 65535,
};
s32 D_800A5898[] = {
    0x11A30, 28720, 65535,
};
s32 D_800A58A4[] = {
    0x11A30, 0x17030, 28711, 65535,
};
s32 D_800A58B4[] = {
    0x11A30, 0x17030, 0x17027, 28713,
    65535,
};
s32 D_800A58C8[] = {
    0x10605, 65535,
};
s32 D_800A58D0[] = {
    0x11A30, 0x17030, 0x17027, 0x17029,
    65535,
};
s32 D_800A58E4[] = {
    28690, 65535,
};
s32 D_800A58EC[] = {
    0x17039, 0x17013, 65535,
};
s32 D_800A58F8[] = {
    0x17012, 65535,
};
s32 D_800A5900[] = {
    6705, 65535,
};
s32 D_800A5908[] = {
    0x11A31, 65535,
};
s32 D_800A5910[] = {
    0x11A31, 28719, 65535,
};
s32 D_800A591C[] = {
    0x11A31, 0x1702F, 28711, 65535,
};
s32 D_800A592C[] = {
    0x11A31, 0x1702F, 0x17027, 28713,
    65535,
};
s32 D_800A5940[] = {
    0x10606, 65535,
};
s32 D_800A5948[] = {
    0x11A31, 0x1702F, 0x17027, 0x17029,
    65535,
};
s32 D_800A595C[] = {
    28689, 65535,
};
s32 D_800A5964[] = {
    0x17038, 0x17013, 65535,
};
s32 D_800A5970[] = {
    0x17011, 65535,
};
s32 D_800A5978[] = {
    (s32)D_800A5810, (s32)D_800A5818, 829, (s32)D_800A5820,
    0, 835, (s32)D_800A582C, 0,
    830, (s32)D_800A583C, (s32)D_800A5850, 831,
    (s32)D_800A5858, 0, 836, 0,
    0, 0,
};
s32 D_800A59C0[] = {
    (s32)D_800A586C, (s32)D_800A5874, 832, (s32)D_800A5880,
    0, 834, 0, 0,
    0,
};
s32 D_800A59E4[] = {
    (s32)D_800A5888, (s32)D_800A5890, 837, (s32)D_800A5898,
    0, 843, (s32)D_800A58A4, 0,
    838, (s32)D_800A58B4, (s32)D_800A58C8, 839,
    (s32)D_800A58D0, 0, 844, 0,
    0, 0,
};
s32 D_800A5A2C[] = {
    (s32)D_800A58E4, (s32)D_800A58EC, 840, (s32)D_800A58F8,
    0, 842, 0, 0,
    0,
};
s32 D_800A5A50[] = {
    0, 0, 833, 0,
    0, 0,
};
s32 D_800A5A68[] = {
    0, 0, 841, 0,
    0, 0,
};
s32 D_800A5A80[] = {
    0, 0, 849, 0,
    0, 0,
};
s32 D_800A5A98[] = {
    (s32)D_800A5900, (s32)D_800A5908, 845, (s32)D_800A5910,
    0, 851, (s32)D_800A591C, 0,
    846, (s32)D_800A592C, (s32)D_800A5940, 847,
    (s32)D_800A5948, 0, 852, 0,
    0, 0,
};
s32 D_800A5AE0[] = {
    (s32)D_800A595C, (s32)D_800A5964, 848, (s32)D_800A5970,
    0, 850, 0, 0,
    0,
};
s32 D_800A5B04[] = {
    0x17093, 28698, 32787, 0x17E00,
    0x17E1E, 65535,
};
s32 D_800A5B1C[] = {
    0x17093, 28698, 0x18013, 0x17E1E,
    0x17E00, 65535,
};
s32 D_800A5B34[] = {
    0x17093, 28698, 33163, 0x17E21,
    0x17E00, 65535,
};
s32 D_800A5B4C[] = {
    0x17093, 28698, 0x1818B, 0x17E21,
    0x17E00, 65535,
};
s32 D_800A5B64[] = {
    0x1701A, 0x17E1E, 0x17E00, 65535,
};
s32 D_800A5B74[] = {
    0x1701A, 0x17E21, 0x17E00, 65535,
};
s32 D_800A5B84[] = {
    0x1701A, 0x17E00, 0x17E24, 65535,
};
s32 D_800A5B94[] = {
    0x17093, 28698, 33128, 0x17E24,
    0x17E00, 65535,
};
s32 D_800A5BAC[] = {
    0x17093, 28698, 0x18168, 0x17E24,
    0x17E00, 65535,
};
s32 D_800A5BC4[] = {
    (s32)D_800A5B04, (s32)D_800A5978, 0x4002B, 0x2B801E0,
    7,
};
s32 D_800A5BD8[] = {
    (s32)D_800A5B1C, (s32)D_800A59C0, 0x4002B, 0x2B801E0,
    7,
};
s32 D_800A5BEC[] = {
    (s32)D_800A5B34, (s32)D_800A59E4, 0x5002C, 0x2080320,
    1,
};
s32 D_800A5C00[] = {
    (s32)D_800A5B4C, (s32)D_800A5A2C, 0x5002C, 0x2080320,
    1,
};
s32 D_800A5C14[] = {
    (s32)D_800A5B64, (s32)D_800A5A50, 0x6009D, 0x2B801E0,
    7,
};
s32 D_800A5C28[] = {
    (s32)D_800A5B74, (s32)D_800A5A68, 0x7009E, 0x2080320,
    1,
};
s32 D_800A5C3C[] = {
    (s32)D_800A5B84, (s32)D_800A5A80, 0x8009F, 0x16C0198,
    7,
};
s32 D_800A5C50[] = {
    (s32)D_800A5B94, (s32)D_800A5A98, 0x900A3, 0x16C0198,
    7,
};
s32 D_800A5C64[] = {
    (s32)D_800A5BAC, (s32)D_800A5AE0, 0x900A3, 0x16C0198,
    7,
};
s32 D_800A5C78[] = {
    (s32)D_800A5BC4, (s32)D_800A5BD8, (s32)D_800A5BEC, (s32)D_800A5C00,
    (s32)D_800A5C14, (s32)D_800A5C28, (s32)D_800A5C3C, (s32)D_800A5C50,
    (s32)D_800A5C64, 0,
};
u8 D_800A5CA0[] = {
    0x01, 0x03, 0xC8, 0x02, 0x48, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x32, 0x00, 0x80, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x03, 0xC8, 0x02, 0x48, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x5C, 0x01, 0x67, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0xC8, 0x02,
    0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x01,
    0x53, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x07, 0x01, 0x07, 0x0C, 0x04, 0x00,
    0x3A, 0x02, 0x8D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x07, 0x01, 0x07, 0x0C,
    0x04, 0x00, 0x8A, 0x03, 0xF3, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x40, 0x06, 0x3D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xBD, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x40, 0x06,
    0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x00,
    0xE8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x40, 0x06, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x71, 0x00, 0x90, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x02, 0x40, 0x06, 0x3D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x54, 0x01, 0x2C, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x40, 0x06, 0x3D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7B, 0x03, 0x22, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x06,
    0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x04,
    0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA1, 0x01, 0x16, 0x01, 0x49, 0x01, 0x00, 0x00,
    0x01, 0x00, 0x48, 0x04, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5C, 0x01, 0x16, 0x01, 0x56, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x4A, 0x04, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x11, 0x02, 0x63, 0x02,
    0xA8, 0x02, 0x00, 0x00, 0x01, 0x00, 0x5A, 0x04,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA6, 0x01,
    0x3A, 0x02, 0x90, 0x02, 0x00, 0x00, 0x01, 0x00,
    0x58, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x01, 0x7B, 0x02, 0xCF, 0x02, 0x00, 0x00,
    0x01, 0x00, 0x60, 0x04, 0x05, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x97, 0x03, 0x07, 0x02, 0x60, 0x02,
    0x00, 0x00, 0x01, 0x00, 0x5E, 0x04, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x47, 0x02, 0x9F, 0x00,
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5DF8[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x58, 0x02, 0x40, 0x03, 0xF0, 0x00,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x58, 0x02, 0x68, 0x03, 0xEC, 0x02,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x58, 0x02, 0x28, 0x01, 0xF4, 0x02,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x58, 0x02, 0x10, 0x01, 0x08, 0x01,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A5E70[])(void) = {
    func_800A5114,
};
