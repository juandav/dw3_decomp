#include "common.h"
#include "stage.h"
extern s32 D_800A5728[];
extern u8 D_800A5744[];
extern u8 D_800A5978[];
extern u8 D_800A57A4[];
void func_800A4D98();
extern void (*D_800A59F0[])(void);
void func_800A5030();
void func_800A5114();
extern AnimFrame D_800A5210[];
extern AnimFrame D_800A5244[];
extern AnimFrame D_800A5278[];
extern StagePoints *D_800A54F0[];

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
        task->anims[0].timer = D_800A5210[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A5244[0].duration;
        task->anims[2].index = 0;
        task->anims[2].timer = D_800A5278[0].duration;
        break;
    case TASK_RUN:
        tile = D_800990B4.unk10;
        frames[0] = func_800A4CA4(&task->anims[0], D_800A5210, 0);
        frames[1] = func_800A4CA4(&task->anims[1], D_800A5244, 0);
        frames[2] = func_800A4CA4(&task->anims[2], D_800A5278, 0);
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
        func_800A4F30(D_800990B4.unk14, D_800A54F0, GAME.unk44, GAME.unk46);
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
    D_800A59F0[0]();
    return task;
}

#if VERSION_US
#define STAGE_TEXT 0xF7
#define STAGE_FILE 0x490
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xEF)
#define STAGE_FILE 0x4A0
#endif
void func_800A5114(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A57A4;
    D_800990B4.unk14 = D_800A5978;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x1F400, 0x32000};
    D_800990B4.unk28 = D_800A5744;
    D_800990B4.unk3C = 0x38;
    D_800990B4.unk40 = 0x60E00000;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5728;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

extern StagePoint D_800A52A8;
extern StagePoint D_800A52B8;
extern StagePoint D_800A52C8;
extern StagePoint D_800A52D8;
extern StagePoint D_800A52F0;
extern StagePoint D_800A5300;
extern StagePoint D_800A5310;
extern StagePoint D_800A5320;
extern StagePoint D_800A5338;
extern StagePoint D_800A5348;
extern StagePoint D_800A5358;
extern StagePoint D_800A5368;
extern StagePoint D_800A5380;
extern StagePoint D_800A5390;
extern StagePoint D_800A53A0;
extern StagePoint D_800A53B0;
extern StagePoint D_800A53C8;
extern StagePoint D_800A53D8;
extern StagePoint D_800A53E8;
extern StagePoint D_800A53F8;
extern StagePoint D_800A5410;
extern StagePoint D_800A5420;
extern StagePoint D_800A5430;
extern StagePoint D_800A5440;
extern StagePoint D_800A5458;
extern StagePoint D_800A5468;
extern StagePoint D_800A5478;
extern StagePoint D_800A5488;
extern StagePoint D_800A54A0;
extern StagePoint D_800A54B0;
extern StagePoint D_800A54C0;
extern StagePoint D_800A54D0;
extern StagePoints D_800A52E8;
extern StagePoints D_800A5330;
extern StagePoints D_800A5378;
extern StagePoints D_800A53C0;
extern StagePoints D_800A5408;
extern StagePoints D_800A5450;
extern StagePoints D_800A5498;
extern StagePoints D_800A54E0;
extern StagePoints D_800A54E8;
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
extern s32 D_800A5578[];
extern s32 D_800A55FC[];
extern s32 D_800A5680[];
extern s32 D_800A5704[];

AnimFrame D_800A5210[] = {
    { 50, 8 }, { 51, 8 }, { 52, 8 }, { 53, 8 },
    { 54, 8 }, { 55, 8 }, { 56, 8 }, { 57, 8 },
    { 58, 8 }, { 59, 8 }, { 60, 8 }, { 82, 160 },
    { 255, 0 },
};
AnimFrame D_800A5244[] = {
    { 61, 8 }, { 62, 8 }, { 63, 8 }, { 64, 8 },
    { 65, 8 }, { 66, 8 }, { 67, 8 }, { 68, 8 },
    { 69, 8 }, { 70, 8 }, { 71, 8 }, { 82, 160 },
    { 255, 0 },
};
AnimFrame D_800A5278[] = {
    { 72, 8 }, { 73, 8 }, { 74, 8 }, { 75, 8 },
    { 76, 8 }, { 77, 8 }, { 78, 8 }, { 79, 8 },
    { 80, 8 }, { 81, 8 }, { 82, 160 }, { 255, 0 },
};
StagePoint D_800A52A8 = { 0x258, 1, 1, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A52B8 = { 0x258, 1, 3, 0x340, 240, 1, &D_800A52A8 };
StagePoint D_800A52C8 = { 0x258, 1, 2, 0x110, 0x108, 7, &D_800A52B8 };
StagePoint D_800A52D8 = { 0x257, 0, 0, 0x100, 0x278, 5, &D_800A52C8 };
StagePoints D_800A52E8 = { 1, 1, &D_800A52D8 };
StagePoint D_800A52F0 = { 0x258, 1, 2, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5300 = { 0x258, 1, 4, 0x340, 240, 1, &D_800A52F0 };
StagePoint D_800A5310 = { 0x258, 1, 1, 0x110, 0x108, 7, &D_800A5300 };
StagePoint D_800A5320 = { 0x257, 0, 0, 0x100, 0x278, 5, &D_800A5310 };
StagePoints D_800A5330 = { 1, 2, &D_800A5320 };
StagePoint D_800A5338 = { 0x258, 1, 4, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5348 = { 0x258, 1, 5, 0x340, 240, 1, &D_800A5338 };
StagePoint D_800A5358 = { 0x258, 1, 3, 0x110, 0x108, 7, &D_800A5348 };
StagePoint D_800A5368 = { 0x258, 1, 1, 0x128, 0x2F4, 5, &D_800A5358 };
StagePoints D_800A5378 = { 1, 3, &D_800A5368 };
StagePoint D_800A5380 = { 0x258, 1, 3, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5390 = { 0x258, 1, 6, 0x340, 240, 1, &D_800A5380 };
StagePoint D_800A53A0 = { 0x258, 1, 4, 0x110, 0x108, 7, &D_800A5390 };
StagePoint D_800A53B0 = { 0x258, 1, 2, 0x128, 0x2F4, 5, &D_800A53A0 };
StagePoints D_800A53C0 = { 1, 4, &D_800A53B0 };
StagePoint D_800A53C8 = { 0x258, 1, 5, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A53D8 = { 0x258, 1, 7, 0x340, 240, 1, &D_800A53C8 };
StagePoint D_800A53E8 = { 0x258, 1, 6, 0x110, 0x108, 7, &D_800A53D8 };
StagePoint D_800A53F8 = { 0x258, 1, 3, 0x128, 0x2F4, 5, &D_800A53E8 };
StagePoints D_800A5408 = { 1, 5, &D_800A53F8 };
StagePoint D_800A5410 = { 0x258, 1, 6, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5420 = { 0x258, 1, 8, 0x340, 240, 1, &D_800A5410 };
StagePoint D_800A5430 = { 0x258, 1, 5, 0x110, 0x108, 7, &D_800A5420 };
StagePoint D_800A5440 = { 0x258, 1, 4, 0x128, 0x2F4, 5, &D_800A5430 };
StagePoints D_800A5450 = { 1, 6, &D_800A5440 };
StagePoint D_800A5458 = { 0x258, 1, 8, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A5468 = { 0x258, 1, 1, 0x340, 240, 1, &D_800A5458 };
StagePoint D_800A5478 = { 0x258, 1, 7, 0x110, 0x108, 7, &D_800A5468 };
StagePoint D_800A5488 = { 0x258, 1, 5, 0x128, 0x2F4, 5, &D_800A5478 };
StagePoints D_800A5498 = { 1, 7, &D_800A5488 };
StagePoint D_800A54A0 = { 0x258, 1, 7, 0x368, 0x2EC, 3, NULL };
StagePoint D_800A54B0 = { 0x258, 1, 2, 0x340, 240, 1, &D_800A54A0 };
StagePoint D_800A54C0 = { 0x258, 1, 8, 0x110, 0x108, 7, &D_800A54B0 };
StagePoint D_800A54D0 = { 0x258, 1, 6, 0x128, 0x2F4, 5, &D_800A54C0 };
StagePoints D_800A54E0 = { 1, 8, &D_800A54D0 };
StagePoints D_800A54E8 = { 0, 0, &D_800A52D8 };
StagePoints *D_800A54F0[] = {
    &D_800A52E8, &D_800A5330, &D_800A5378, &D_800A53C0,
    &D_800A5408, &D_800A5450, &D_800A5498, &D_800A54E0,
    &D_800A54E8, NULL,
};
s32 D_800A5518[] = {
    73, 5, 0x60080000,
};
s32 D_800A5524[] = {
    73, 5, 0x60080000,
};
s32 D_800A5530[] = {
    73, 5, 0x60080000,
};
s32 D_800A553C[] = {
    74, 5, 0x60080000,
};
s32 D_800A5548[] = {
    74, 5, 0x60080000,
};
s32 D_800A5554[] = {
    74, 5, 0x60080000,
};
s32 D_800A5560[] = {
    156, 5, 0x60080000,
};
s32 D_800A556C[] = {
    156, 5, 0x60080000,
};
s32 D_800A5578[] = {
    3, (s32)D_800A5518, (s32)D_800A5524, (s32)D_800A5530,
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
    38, 0, 0, (s32)D_800A5578,
    (s32)D_800A55FC, (s32)D_800A5680, (s32)D_800A5704,
};
u8 D_800A5744[] = {
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
};
u8 D_800A57A4[] = {
    0x01, 0x03, 0xC8, 0x02, 0x48, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x01, 0x61, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x03, 0xC8, 0x02, 0x48, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x67, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0xC8, 0x02,
    0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0x03,
    0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x08, 0x01, 0x08, 0x0D, 0x04, 0x00,
    0x48, 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x08, 0x01, 0x08, 0x0D,
    0x04, 0x00, 0x77, 0x01, 0xDC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x08, 0x01,
    0x08, 0x0D, 0x04, 0x00, 0x07, 0x02, 0x94, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x08, 0x01, 0x08, 0x0D, 0x04, 0x00, 0x18, 0x02,
    0x1B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x08, 0x01, 0x08, 0x0D, 0x04, 0x00,
    0x47, 0x02, 0xC6, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x08, 0x01, 0x08, 0x0D,
    0x04, 0x00, 0xC7, 0x02, 0x64, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x08, 0x01,
    0x08, 0x0D, 0x04, 0x00, 0xD8, 0x02, 0x0B, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x08, 0x01, 0x08, 0x0D, 0x04, 0x00, 0x17, 0x03,
    0xCC, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x40, 0x06, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA6, 0x00, 0xA9, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x40, 0x06, 0x32, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xAB, 0x00, 0xE9, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x40, 0x06, 0x32, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xB8, 0x00, 0x6B, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x06,
    0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F, 0x01,
    0x21, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x40, 0x06, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA5, 0x03, 0x28, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x02, 0x40, 0x06, 0x3D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC8, 0x03, 0xF2, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x60, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xD4, 0x02, 0x77, 0x02,
    0xD1, 0x02, 0x00, 0x00, 0x01, 0x00, 0x60, 0x04,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x02,
    0xA7, 0x02, 0x01, 0x03, 0x00, 0x00, 0x01, 0x00,
    0x60, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x54, 0x01, 0x27, 0x02, 0x81, 0x02, 0x00, 0x00,
    0x01, 0x00, 0x60, 0x04, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x03, 0xDF, 0x01, 0x39, 0x02,
    0x00, 0x00, 0x01, 0x00, 0x60, 0x04, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x54, 0x02, 0xD7, 0x01,
    0x32, 0x02, 0x00, 0x00, 0x01, 0x00, 0x60, 0x04,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE4, 0x02,
    0x1F, 0x01, 0x7A, 0x01, 0x00, 0x00, 0x01, 0x00,
    0x60, 0x04, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x02, 0x2F, 0x01, 0x89, 0x01, 0x00, 0x00,
    0x01, 0x00, 0x60, 0x04, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x84, 0x01, 0xEF, 0x00, 0x49, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A5978[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x59, 0x02, 0x58, 0x03, 0xFC, 0x00,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x59, 0x02, 0x50, 0x03, 0xF8, 0x02,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x59, 0x02, 0x18, 0x01, 0xEC, 0x02,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x59, 0x02, 0x20, 0x01, 0x00, 0x01,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A59F0[])(void) = {
    func_800A5114,
};
