#include "common.h"
#include "stage.h"
extern void (*D_800A6870[])(void);
void func_800A5DFC();
extern s16 D_800A65B8[];

/* Moves the two records and the player 0x7F up or down when an event sets TASK_DONE */
void func_800A5DFC(StageTileLift *task) {
    StageTile *rec;
    StageTile *tile0;
    StageTile *tile1;
    StageActor *player;
    s32 d;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 2:
                task->tiles[1] = rec;
                task->homeY[1] = rec->unkC;
                if (task->down) {
                    rec->unkC -= 0x7F;
                }
                rec->visible = 0;
                break;
            case 3:
                task->tiles[0] = rec;
                task->homeY[0] = rec->unkC;
                if (task->down) {
                    rec->unkC -= 0x7F;
                }
                rec->visible = 1;
                break;
            }
        }
        task->down = 0;
        break;
    case TASK_RUN:
        break;
    case TASK_DONE:
        tile0 = task->tiles[0];
        tile1 = task->tiles[1];
        player = TASK_FUNCS.find(5, -1, 0);
        switch (task->substate) {
        case 0:
        default:
            tile1->visible = 1;
            task->timer = 0;
            task->y[0] = tile0->unkC;
            task->y[1] = tile1->unkC;
            task->playerY = player->y;
            SOUND.playSound(0x8004103C);
            task->nextSubstate(task);
            break;
        case 1:
            task->timer += GFX_FUNCS.getFrameTime();
            if (task->timer >= 0x1E) {
                task->shake = 0;
                task->nextSubstate(task);
                SOUND.playSound(0x1080001);
            }
            break;
        case 2:
        case 4:
            d = D_800A65B8[task->shake];
            if (d != 0x3E8) {
                tile0->unkC = task->y[0] + d;
                tile1->unkC = task->y[1] + d;
                player->y = task->playerY + d;
                task->shake++;
            } else {
                task->nextSubstate(task);
                task->shake = 0;
            }
            break;
        case 3:
            if (++task->shake >= 0xFE) {
                if (task->down) {
                    tile0->unkC = task->homeY[0];
                    tile1->unkC = task->homeY[1];
                    player->y = task->playerY + 0x7F00;
                } else {
                    tile0->unkC = task->homeY[0] - 0x7F;
                    tile1->unkC = task->homeY[1] - 0x7F;
                    player->y = task->playerY - 0x7F00;
                }
                task->y[0] = tile0->unkC;
                task->y[1] = tile1->unkC;
                task->playerY = player->y;
                task->nextSubstate(task);
                task->shake = 0;
            } else if (task->shake & 1) {
                if (task->down) {
                    tile0->unkC++;
                    tile1->unkC++;
                    player->y += 0x100;
                } else {
                    tile0->unkC--;
                    tile1->unkC--;
                    player->y -= 0x100;
                }
            }
            break;
        case 5:
            tile1->visible = 0;
            task->setState(task, TASK_RUN);
            task->down ^= 1;
            break;
        }
        break;
    case TASK_KILL:
        break;
    }
}

void func_800A6218(StageTileLift *task, s32 id) {
    if (task != NULL) {
        switch (id) {
        case 0x348:
            task->setState(task, TASK_DONE);
            task->down = 0;
            break;
        case 0x349:
            task->setState(task, TASK_DONE);
            task->down = 1;
            break;
        }
    }
}

StageTileLift *func_800A628C(s32 id) {
    StageTileLift *task = createTaskWithId(func_800A5DFC, sizeof(StageTileLift), 0, id);

    if (FLAGS_00.checkCondition(0x1C3D, 1)) {
        task->down = 1;
    } else {
        task->down = 0;
    }
    return task;
}

void func_800A62F4(StageTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the stage task (func_800A62F4) of the given owner */
StageTask *func_800A633C(void *owner) {
    StageTask *task = createTask(func_800A62F4, 0x58, 8);

    task->owner = owner;
    D_800A6870[0]();
    return task;
}

/* the color the setup copies to D_800990B4.unk38 */
const CVECTOR D_800A5DF8 = { 0x80, 0x80, 0x80, 0 };

extern s32 D_800A66FC[];
extern s32 D_800A67F8[];
extern s32 D_800A65CC[];
extern s32 D_800A66F0[];
void func_800A6398(void) {
    D_800990B4.unk44 = LANGUAGE + 0xFD;
    D_800990B4.unk8 = 0x1AC;
    D_800990B4.unkC = 0x8FB0000;
    D_800990B4.unk10 = D_800A66FC;
    D_800990B4.unk14 = D_800A67F8;
    D_800990B4.unk1C = 0x8FA;
    D_800990B4.unk2C = (Vec2){0x6700, 0x12300};
    D_800990B4.unk28 = D_800A65CC;
    D_800990B4.unk3C = 0x42;
    D_800990B4.unk34 = 0;
    D_800990B4.unk40 = 0x61080002;
    D_800990B4.unk4C = D_800A66F0;
    D_800990B4.unk38 = D_800A5DF8;
    D_8009A70C.setFile(0, 0x8FB0001);
    D_8009A70C.setFile(1, 0x8FB0002);
    D_8009A70C.setFile(7, 0x8FB0003);
    D_8009A70C.unk50(0);
}

void func_800A64B8(StageTween *tween, s32 up) {
    tween->active = 1;
    if (up) {
        SOUND.playSound(0x40019);
        tween->step = 0x1000 / tween->duration;
        tween->value = 0;
    } else {
        SOUND.playSound(0x4001A);
        tween->value = 0x1000;
        tween->step = -(0x1000 / tween->duration * 2);
    }
}

s32 func_800A654C(StageTween *tween) {
    if (tween->active == 0) {
        return 1;
    }
    tween->value += tween->step;
    if (tween->step > 0) {
        if (tween->value > 0x1000) {
            tween->value = 0x1000;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < 0) {
        tween->value = 0;
        tween->active = 0;
        return 1;
    }
    return 0;
}

void func_800A6398();
extern s32 D_800A664C[];
extern s32 D_800A6654[];
extern s32 D_800A665C[];
extern s32 D_800A6668[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A6698[];
extern s32 D_800A66C8[];
extern s32 D_800A66DC[];

s16 D_800A65B8[] = {
    1, 2, 1, 0, -1, -2, -1, 0,
    0x3E8, 5,
};
s32 D_800A65CC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000180, 0x1DD018C, 0xDD0130, 0x1FE0160,
    0x10001C0, 0x13C01EA, 0x3C02A8, 0x1FE0170,
};
s32 D_800A664C[] = {
    0, 65535,
};
s32 D_800A6654[] = {
    0x10000, 65535,
};
s32 D_800A665C[] = {
    0x10000, 33170, 65535,
};
s32 D_800A6668[] = {
    0x18192, 0x17013, 65535,
};
s32 D_800A6674[] = {
    0x10000, 0x18192, 65535,
};
s32 D_800A6680[] = {
    0, 0, 65, 0,
    0, 0,
};
s32 D_800A6698[] = {
    (s32)D_800A664C, (s32)D_800A6654, 62, (s32)D_800A665C,
    (s32)D_800A6668, 63, (s32)D_800A6674, 0,
    64, 0, 0, 0,
};
s32 D_800A66C8[] = {
    0, (s32)D_800A6680, 0x4002D, 0x169010F,
    5,
};
s32 D_800A66DC[] = {
    0, (s32)D_800A6698, 0x50067, 0x19000BF,
    3,
};
s32 D_800A66F0[] = {
    (s32)D_800A66C8, (s32)D_800A66DC, 0,
};
s32 D_800A66FC[] = {
    0x2440101, 0x1000252, 0x1380004, 282,
    0x2010000, 0x14A0240, 0x4514A, 0x1660087,
    0, 0x6400001, 0x433E013E, 0x1650004,
    161, 0x10000, 0x10640, 0,
    0x1A100C0, 0, 0x6400001, 0x7020102,
    0x1650004, 161, 0x3010000, 1741,
    0, 0x15200A0, 0, 0xA400001,
    0x49440144, 0x1650004, 241, 0x10000,
    0x1080A40, 0x40D08, 0xF10165, 0,
    0xA400001, 0x130F010F, 0x3E0004, 326,
    0x10000, 0x140A48, 0, 0xCA0080,
    0, 0xA490001, 21, 0xC80000,
    183, 0x10000, 0x1320440, 0x43732,
    0xA10165, 200, 0x8400001, 0x3D380138,
    0x1650004, 0x11800F1, 0, 0,
    0, 0, 0,
};
s32 D_800A67F8[] = {
    65535, 65535, 0x2710001, 0xF40368,
    1, 0, 65535, 65535,
    0x2810001, 0xA502FE, 1, 0,
    65535, 65535, 0x10006, 0,
    0, 0, 65535, 65535,
    0x80005, 0, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6870[])(void) = {
    func_800A6398,
};
s32 D_800A6874 = (s32)func_800A64B8;
s32 D_800A6878 = (s32)func_800A654C;
