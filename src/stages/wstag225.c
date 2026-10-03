#include "common.h"
#include "stage.h"
void func_800A4DB4();
extern void (*D_800A59F8[])(void);
void func_800A5100();
extern AnimFrame *D_800A54E8[];
extern s8 D_800A54F4[];
extern s8 D_800A54F8[];
extern s16 D_800A54FC[][2];

s32 func_800A4CA4(Anim4 *obj, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            return 0xFF;
        }
        func_800A4CA4(obj, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A4D7C(StageTileEffect *task) {
    s32 i;

    for (i = 0; i < 3; i++) {
        task->anims[i].anim.index = 0;
        task->anims[i].anim.timer = D_800A54E8[i][0].duration;
    }
}

/* Once the substate is set to 1, moves the records of animations 1-3 to (x, y), plays a sound and animates them once */
void func_800A4DB4(StageTileEffect *task) {
    StageTile *tile;
    StageTile *t;
    s32 i;
    s32 n;
    s32 j;
    s32 frame;
    s32 done;

    switch (task->state) {
    case TASK_INIT:
    default:
        func_800A4D7C(task);
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            switch (task->step) {
            case 0:
                n = 0;
                for (t = D_800990B4.unk10; t->unk2 != 0; t++) {
                    if (t->anim >= 1 && t->anim <= 3) {
                        task->anims[n].tile = t;
                        t->unkA = task->x;
                        t->unkC = task->y + D_800A54F8[n];
                        t->unkE = task->y + D_800A54F4[n];
                        n++;
                    }
                }
                SOUND.playSound(0xCC0001);
                task->nextStep(task);
            case 1:
                done = 0;
                for (i = 0; i < 3; i++) {
                    tile = task->anims[i].tile;
                    frame = func_800A4CA4((Anim4 *)&task->anims[i], D_800A54E8[i], 0);
                    switch (frame) {
                    case 0xFF:
                        done++;
                        tile->visible = 0;
                        tile->frame = 0;
                        break;
                    case 0x12C:
                        tile->visible = 0;
                        tile->frame = 0;
                        break;
                    default:
                        tile->visible = 1;
                        tile->frame = frame;
                        break;
                    }
                }
                if (done < 3) {
                    break;
                }
                task->nextStep(task);
            case 2:
                for (j = 0; j < 3; j++) {
                    task->anims[j].tile->visible = 0;
                }
                func_800A4D7C(task);
                task->setSubstate(task, 0);
                break;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Starts the effect at the place of map object 0x346 or 0x347 */
void func_800A5038(StageTileEffect *task, s32 id) {
    s32 i;

    if (task != NULL) {
        i = 0;
        switch (id) {
        case 0x347:
            i = 1;
        case 0x346:
            task->x = D_800A54FC[i][0];
            task->y = D_800A54FC[i][1];
            task->setSubstate(task, 1);
            break;
        }
    }
}

void *func_800A50A4(s32 arg) {
    return createTaskWithId(func_800A4DB4, 0x70, 0, arg);
}

void *func_800A50D4(void) {
    return createTask(func_800A4DB4, 0x70, 0);
}

/* Creates the event object of progress 1 */
void func_800A5100(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (GAME_PROGRESS == 1) {
            children[0] = func_80084B80(5);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5178(void *owner) {
    StageTask *task = createTask(func_800A5100, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A59F8[0]();
    return task;
}

void func_800A51D4(void) {
    GAME_PROGRESS = 2;
}

extern s32 D_800A58F0[];
extern s32 D_800A59C8[];
extern s32 D_800A5504[];
extern s32 D_800A58AC[];
extern s32 D_800A59FC[];
#if VERSION_US
#define STAGE_TEXT 0xF0
#define STAGE_FILE 0x191
#define STAGE_ARCHIVE 0x3BD
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xE8)
#define STAGE_FILE 0x19F
#define STAGE_ARCHIVE 0x3CD
#endif
void func_800A51E4(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A58F0;
    D_800990B4.unk14 = D_800A59C8;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0xFD00, 0x17700};
    D_800990B4.unk28 = D_800A5504;
    D_800990B4.unk3C = 0x33;
    D_800990B4.unk40 = 0x60CC0000;
    D_800990B4.unk4C = D_800A58AC;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A59FC;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
    if (GAME_PROGRESS >= 0x14 && GAME_PROGRESS < 0x18) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
    if (GAME_PROGRESS >= 0x27 && GAME_PROGRESS < 0x29) {
        D_800990B4.unk3C = 0x1F;
        D_800990B4.unk40 = 0x607C0000;
    }
}

void func_800A51E4();
extern AnimFrame D_800A5444[];
extern AnimFrame D_800A54A8[];
extern AnimFrame D_800A5458[];
extern s32 D_800A56EC[];
extern s32 D_800A56F4[];
extern s32 D_800A56FC[];
extern s32 D_800A55B4[];
extern s32 D_800A5704[];
extern s32 D_800A55CC[];
extern s32 D_800A570C[];
extern s32 D_800A55E4[];
extern s32 D_800A5714[];
extern s32 D_800A55FC[];
extern s32 D_800A571C[];
extern s32 D_800A5614[];
extern s32 D_800A5724[];
extern s32 D_800A562C[];
extern s32 D_800A572C[];
extern s32 D_800A5644[];
extern s32 D_800A5734[];
extern s32 D_800A565C[];
extern s32 D_800A573C[];
extern s32 D_800A5674[];
extern s32 D_800A5744[];
extern s32 D_800A568C[];
extern s32 D_800A574C[];
extern s32 D_800A56A4[];
extern s32 D_800A5754[];
extern s32 D_800A56BC[];
extern s32 D_800A575C[];
extern s32 D_800A5764[];
extern s32 D_800A56D4[];
extern s32 D_800A576C[];
extern s32 D_800A5780[];
extern s32 D_800A5794[];
extern s32 D_800A57A8[];
extern s32 D_800A57BC[];
extern s32 D_800A57D0[];
extern s32 D_800A57E4[];
extern s32 D_800A57F8[];
extern s32 D_800A580C[];
extern s32 D_800A5820[];
extern s32 D_800A5834[];
extern s32 D_800A5848[];
extern s32 D_800A585C[];
extern s32 D_800A5870[];
extern s32 D_800A5884[];
extern s32 D_800A5898[];
extern s32 D_800A531C[];

s32 D_800A531C[] = {
    0x10601, 0x127011E, 0x10100, 0,
    0x10101, 1, 0xD0100, 0x191010F,
    0xD0101, 0x30001, 0x32F0101, 0x10345,
    0x780300, 0x1E0300, 0x32F0101, 0x10346,
    0x5A0300, 0x5A0300, 0x10100, 0x11F0170,
    0x10101, 0x10001, 0xB40300, 0x1E0300,
    0x10102, 0x1300150, 0x3020001, 0x1010001,
    0x3A0001, 0x3000001, 0x20000B4, 0x10000,
    1, 0x10101, 0x10001, 0x3000301,
    0x102001E, 0x1300001, 0x10160, 0x10302,
    1536, 0x1020001, 0xF00001, 0x10180,
    0x10302, 0x10101, 0x70001, 0x1E0300,
    512, 0xD0002, 0x1010002, 0x7000D,
    0x3010003, 0xD0101, 0x30001, 0x1E0300,
    512, 0x10003, 0x1010001, 0x70001,
    0x3010007, 0x10101, 0x70001, 0x1E0300,
    0xD0101, 0x10001, 0x10302, 0x10102,
    0x1D00050, 0x3000007, 0x3040006, 0x2DA0203,
    0x1017E,
#if VERSION_US
    0x8FB00000,
#elif VERSION_EU
    0,
#endif
};
AnimFrame D_800A5444[] = {
    { 70, 4 }, { 71, 4 }, { 70, 4 }, { 71, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A5458[] = {
    { 0x12C, 56 }, { 85, 6 }, { 86, 6 }, { 87, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 88, 4 },
    { 89, 4 }, { 90, 4 }, { 88, 4 }, { 89, 4 },
    { 90, 4 }, { 88, 4 }, { 89, 4 }, { 90, 4 },
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A54A8[] = {
    { 0x12C, 16 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 73, 4 }, { 75, 6 }, { 76, 6 }, { 77, 14 },
    { 78, 114 }, { 79, 6 }, { 80, 6 }, { 81, 6 },
    { 82, 6 }, { 83, 6 }, { 84, 8 }, { 255, 0x3E7 },
};
AnimFrame *D_800A54E8[] = {
    D_800A5444, D_800A54A8, D_800A5458,
};
s8 D_800A54F4[] = {
    30, 30, 30, 0,
};
s8 D_800A54F8[] = {
    0, -0x2F, -0x2F, 0,
};
s16 D_800A54FC[][2] = {
    { 0x150, 0x112 }, { 112, 0x112 },
};
s32 D_800A5504[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1D00152, 0xD00048, 0x1FE0170,
    0x1000140, 0x1B00170, 0xB000C0, 0x1FD0160,
    0x1000140, 0x1B8014A, 0xB80028, 0x1FD0170,
    0x1000140, 0x1D00162, 0xD00088, 0x1FC0150,
    0x1000140, 0x1D0015A, 0xD00068, 0x1FC0160,
};
s32 D_800A55B4[] = {
    0, 0, 28, 0,
    0, 0,
};
s32 D_800A55CC[] = {
    0, 0, 410, 0,
    0, 0,
};
s32 D_800A55E4[] = {
    0, 0, 411, 0,
    0, 0,
};
s32 D_800A55FC[] = {
    0, 0, 413, 0,
    0, 0,
};
s32 D_800A5614[] = {
    0, 0, 417, 0,
    0, 0,
};
s32 D_800A562C[] = {
    0, 0, 418, 0,
    0, 0,
};
s32 D_800A5644[] = {
    0, 0, 412, 0,
    0, 0,
};
s32 D_800A565C[] = {
    0, 0, 414, 0,
    0, 0,
};
s32 D_800A5674[] = {
    0, 0, 415, 0,
    0, 0,
};
s32 D_800A568C[] = {
    0, 0, 419, 0,
    0, 0,
};
s32 D_800A56A4[] = {
    0, 0, 433, 0,
    0, 0,
};
s32 D_800A56BC[] = {
    0, 0, 416, 0,
    0, 0,
};
s32 D_800A56D4[] = {
    0, 0, 432, 0,
    0, 0,
};
s32 D_800A56EC[] = {
    0x16001, 65535,
};
s32 D_800A56F4[] = {
    0x16001, 65535,
};
s32 D_800A56FC[] = {
    0x16002, 65535,
};
s32 D_800A5704[] = {
    0x16004, 65535,
};
s32 D_800A570C[] = {
    0x17015, 65535,
};
s32 D_800A5714[] = {
    0x1600D, 65535,
};
s32 D_800A571C[] = {
    0x17018, 65535,
};
s32 D_800A5724[] = {
    0x17019, 65535,
};
s32 D_800A572C[] = {
    0x1600C, 65535,
};
s32 D_800A5734[] = {
    0x1600E, 65535,
};
s32 D_800A573C[] = {
    0x17016, 65535,
};
s32 D_800A5744[] = {
    0x16026, 65535,
};
s32 D_800A574C[] = {
    0x1602B, 65535,
};
s32 D_800A5754[] = {
    0x16016, 65535,
};
s32 D_800A575C[] = {
    0x1600D, 65535,
};
s32 D_800A5764[] = {
    0x1701A, 65535,
};
s32 D_800A576C[] = {
    (s32)D_800A56EC, 0, 0x40001, 0,
    1,
};
s32 D_800A5780[] = {
    (s32)D_800A56F4, 0, 0x5000D, 0,
    3,
};
s32 D_800A5794[] = {
    (s32)D_800A56FC, (s32)D_800A55B4, 0x60020, 0x18D0109,
    3,
};
s32 D_800A57A8[] = {
    (s32)D_800A5704, (s32)D_800A55CC, 0x60020, 0x18D0109,
    3,
};
s32 D_800A57BC[] = {
    (s32)D_800A570C, (s32)D_800A55E4, 0x60020, 0x18D0109,
    3,
};
s32 D_800A57D0[] = {
    (s32)D_800A5714, (s32)D_800A55FC, 0x60020, 0x18D0109,
    3,
};
s32 D_800A57E4[] = {
    (s32)D_800A571C, (s32)D_800A5614, 0x60020, 0x18D0109,
    3,
};
s32 D_800A57F8[] = {
    (s32)D_800A5724, (s32)D_800A562C, 0x60020, 0x18D0109,
    3,
};
s32 D_800A580C[] = {
    (s32)D_800A572C, (s32)D_800A5644, 0x60020, 0x18D0109,
    3,
};
s32 D_800A5820[] = {
    (s32)D_800A5734, (s32)D_800A565C, 0x60020, 0x18D0109,
    3,
};
s32 D_800A5834[] = {
    (s32)D_800A573C, (s32)D_800A5674, 0x60020, 0x18D0109,
    3,
};
s32 D_800A5848[] = {
    (s32)D_800A5744, (s32)D_800A568C, 0x60020, 0x18D0109,
    3,
};
s32 D_800A585C[] = {
    (s32)D_800A574C, (s32)D_800A56A4, 0x60020, 0x18D0109,
    3,
};
s32 D_800A5870[] = {
    (s32)D_800A5754, (s32)D_800A56BC, 0x60020, 0x18D0109,
    3,
};
s32 D_800A5884[] = {
    (s32)D_800A575C, 0, 0x7006A, 0,
    1,
};
s32 D_800A5898[] = {
    (s32)D_800A5764, (s32)D_800A56D4, 0x8009D, 0x18D0109,
    3,
};
s32 D_800A58AC[] = {
    (s32)D_800A576C, (s32)D_800A5780, (s32)D_800A5794, (s32)D_800A57A8,
    (s32)D_800A57BC, (s32)D_800A57D0, (s32)D_800A57E4, (s32)D_800A57F8,
    (s32)D_800A580C, (s32)D_800A5820, (s32)D_800A5834, (s32)D_800A5848,
    (s32)D_800A585C, (s32)D_800A5870, (s32)D_800A5884, (s32)D_800A5898,
    0,
};
s32 D_800A58F0[] = {
    0x6500100, 70, 0x700000, 274,
    0x10000, 0x13F0640, 0x6423F, 0x1020074,
    0, 0x6400001, 0x423F013F, 0xE40006,
    282, 0x10000, 0x13F0640, 0x6423F,
    0x1020154, 0, 0x6400001, 0x423F013F,
    0x1630006, 346, 0x2000000, 0x480450,
    0, 0xE30070, 301, 0x4500300,
    85, 0x700000, 0x12600E3, 0x10000,
    0x13B0440, 0x63E3B, 0x1120074, 300,
    0x4400001, 0x3E3B013B, 0xE40006, 0x144012A,
    0x10000, 0x13B0440, 0x63E3B, 0x1120154,
    300, 0x4400001, 0x3E3B013B, 0x1630006,
    0x184016A, 0, 0, 0,
    0, 0,
};
s32 D_800A59C8[] = {
    65535, 65535, 0x2030001, 0x17E02DA,
    1, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A59F8[])(void) = {
    func_800A51E4,
};
s32 D_800A59FC[] = {
    5, (s32)D_800A531C,
#if VERSION_US
    0x10B0000,
#elif VERSION_EU
    0x1120000,
#endif
    0, (s32)func_800A51D4, -1, 0,
    0, 0, 0,
};
