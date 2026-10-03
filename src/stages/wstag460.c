#include "common.h"
#include "stage.h"
void func_800A5AF0();
void func_800A5368();
void func_800A4FDC();
extern void (*D_800A6594[])(void);
void func_800A5E70();
extern AnimFrame D_800A6298[];
extern AnimFrame D_800A62C4[];
extern u16 D_800A62F4[];
extern u16 D_800A62FC[];
s32 func_800A5804(s32 x, s32 y);
extern AnimFrame *D_800A6284[];
extern AnimFrame *D_800A628C[];
extern u8 D_800A6294[2][2];
void *func_800A521C(void);
void *func_800A567C(void);
void func_800A5DCC();
extern AnimFrame D_800A6128[];
extern AnimFrame D_800A6168[];
void *func_800A4E8C(s32 id);
void func_800A51D0(StageTileSolo *task, s32 arg1, s32 arg2);
void func_800A5630(StageTileDuo *task, s32 arg1, s32 arg2);
StageWanderer *func_800A5E18(s32 tileAnim, s32 speedIndex, s32 start);

/* Creates the tiles and the seven wanderers; in TASK_DONE makes them all hide and goes back to TASK_RUN */
void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A521C();
        children[1] = func_800A567C();
        children[2] = func_800A5E18(1, 0, 0);
        children[3] = func_800A5E18(2, 0, 0);
        children[4] = func_800A5E18(3, 0, 0);
        children[5] = func_800A5E18(4, 1, 0);
        children[6] = func_800A5E18(5, 1, 0);
        children[7] = func_800A5E18(6, 1, 0);
        children[8] = func_800A5E18(7, 1, 0);
        task->nextState(task);
        break;
    case TASK_RUN:
        break;
    case TASK_DONE:
        func_800A51D0(children[0], 0, 0);
        func_800A5630(children[1], 0, 0);
        func_800A5DCC(children[2], 0, 0);
        func_800A5DCC(children[3], 0, 0);
        func_800A5DCC(children[4], 0, 0);
        func_800A5DCC(children[5], 0, 0);
        func_800A5DCC(children[6], 0, 0);
        func_800A5DCC(children[7], 0, 0);
        func_800A5DCC(children[8], 0, 0);
        task->setState(task, TASK_RUN);
        break;
    case TASK_KILL:
        break;
    }
}

/* Sets the task to TASK_DONE when the id is 0x34C */
void func_800A4E54(Task *task, s32 id) {
    if (task != NULL && id == 0x34C) {
        task->setState(task, TASK_DONE);
    }
}

/* Creates the task of func_800A4CA4 with the given id */
void *func_800A4E8C(s32 id) {
    return createTaskWithId(func_800A4CA4, 0x50, 0x24, id);
}

s32 func_800A4EBC(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A4EBC(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Shows the record with animation 10 (animated) while mode isn't 0, and hides it by a one-shot animation wait frames after mode 2 */
void func_800A4FDC(StageTileSolo *task) {
    StageTile *rec;
    StageTile *tile;
    StageTile *fading;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tile.anim.index = 0;
        task->tile.anim.timer = D_800A6128[0].duration;
        task->tile.anim.index = 0;
        task->tile.anim.timer = D_800A6128[0].duration;
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 10) {
                task->tile.tile = rec;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        tile = task->tile.tile;
        if (task->mode != 0) {
            tile->visible = 1;
            tile->frame = 0x3C;
            tile->unk9 = func_800A4EBC(&task->tile, D_800A6128, 0, 0);
        } else {
            tile->visible = 0;
        }
        if (task->mode == 2) {
            if (--task->wait <= 0) {
                task->setState(task, TASK_DONE);
            }
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->tile.anim.index = 0;
            task->tile.anim.timer = D_800A6168[0].duration;
            task->setSubstate(task, 1);
        }
        fading = task->tile.tile;
        frame = func_800A4EBC(&task->tile, D_800A6168, 1, 0);
        switch (frame) {
        case 0x12C:
            fading->visible = 0;
            break;
        case 0xFF:
            fading->visible = 0;
            task->mode = 0;
            task->setState(task, TASK_RUN);
            break;
        default:
            fading->visible = 1;
            fading->frame = 0x3D;
            fading->unk9 = frame;
            break;
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Makes the StageTileSolo hide in 20 frames */
void func_800A51D0(StageTileSolo *task, s32 arg1, s32 arg2) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x14;
    }
}

void *func_800A51EC(s32 arg) {
    return createTaskWithId(func_800A4FDC, 0x5C, 0, arg);
}

void *func_800A521C(void) {
    return createTask(func_800A4FDC, 0x5C, 0);
}

s32 func_800A5248(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5248(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A5368(StageTileDuo *task) {
    StageTile *tile;
    StageTile *rec;
    StageTile *fading;
    s32 i;
    s32 j;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tiles[0].anim.index = 0;
        task->tiles[0].anim.timer = D_800A6284[0]->duration;
        task->tiles[1].anim.index = 0;
        task->tiles[1].anim.timer = D_800A6284[1]->duration;
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 8:
                task->tiles[0].tile = rec;
                break;
            case 9:
                task->tiles[1].tile = rec;
                break;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            tile = task->tiles[i].tile;
            if (task->mode != 0) {
                tile->visible = 1;
                tile->unk9 = func_800A5248(&task->tiles[i], D_800A6284[i], 0, 0);
                tile->frame = D_800A6294[0][i];
            } else {
                tile->visible = 0;
            }
        }
        if (task->mode == 2) {
            if (--task->wait <= 0) {
                task->setState(task, TASK_DONE);
            }
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->tiles[0].anim.index = 0;
            task->tiles[0].anim.timer = D_800A628C[0]->duration;
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A628C[1]->duration;
            task->setSubstate(task, 1);
        }
        for (j = 0; j < 2; j++) {
            fading = task->tiles[j].tile;
            frame = func_800A5248(&task->tiles[j], D_800A628C[j], 1, 0);
            switch (frame) {
            case 0x12C:
                fading->visible = 0;
                break;
            case 0xFF:
                fading->visible = 0;
                task->mode = 0;
                task->setState(task, TASK_RUN);
                break;
            default:
                fading->visible = 1;
                fading->frame = D_800A6294[1][j];
                fading->unk9 = frame;
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Makes the StageTileDuo hide in 150 frames */
void func_800A5630(StageTileDuo *task, s32 arg1, s32 arg2) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x96;
    }
}

void *func_800A564C(s32 arg) {
    return createTaskWithId(func_800A5368, 0x64, 0, arg);
}

void *func_800A567C(void) {
    return createTask(func_800A5368, 0x64, 0);
}

s32 func_800A56A8(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A56A8(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Whether the wanderer is more than dist from home (in x + y) */
s32 func_800A57C8(StageWanderer *task, s32 dist) {
    s32 dx = task->posX - task->homeX;
    s32 dy = task->posY - task->homeY;

    if (dx < 0) {
        dx = -dx;
    }
    if (dy < 0) {
        dy = -dy;
    }
    return dist < dx + dy;
}

/* The angle of (x, y), 0x100 a turn, from the table of tangents D_800A62FC */
s32 func_800A5804(s32 x, s32 y) {
    s32 result = 0;
    s32 ratio = 0;
    s32 base;
    s32 i;

    if (x <= 0 && y >= 0) {
        base = 0;
    } else if (x >= 0 && y >= 0) {
        base = 0x40;
    } else if (x >= 0 && y <= 0) {
        base = 0x80;
    } else if (x <= 0 && y <= 0) {
        base = 0xC0;
    } else {
        base = 0;
    }
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    if (x == y) {
        return base | 0x20;
    }
    if (y < x) {
        ratio = y * 0xFFFF / x;
    } else if (x < y) {
        ratio = x * 0xFFFF / y;
    }
    for (i = 0; i <= 0x20; i++) {
        if (D_800A62FC[i] <= ratio && ratio <= D_800A62FC[i + 1]) {
            switch (base) {
            case 0:
            case 0x80:
                if (y < x) {
                    result = i;
                } else if (x < y) {
                    result = 0x40 - i;
                }
                return result + base;
            case 0x40:
            case 0xC0:
                if (y < x) {
                    result = 0x40 - i;
                } else if (x < y) {
                    result = i;
                }
                return result + base;
            }
        }
    }
    return 0xFF;
}

/* Moves the wanderer, turning it every period frames */
void func_800A5974(StageWanderer *task) {
    s32 dx;
    s32 dy;

    task->timer += GFX_FUNCS.getFrameTime();
    if (task->period < task->timer) {
        if (func_800A57C8(task, 0x1E)) {
            task->angle = ((func_800A5804(task->homeX - task->posX, task->homeY - task->posY) - 0x40) << 4) & 0xFFF;
        } else {
            task->angle = (RANDOM.next() & 0xFF) << 4;
        }
        task->timer -= task->period;
        task->timer += (RANDOM.next() & 0xF) - 7;
    }
    dx = rsin(task->angle) * task->speed / 4096;
    dy = rcos(task->angle) * task->speed / 4096;
    task->x += dx;
    task->y += dy;
    task->posX = task->x >> 8;
    task->posY = task->y >> 8;
}

/* Wanders; when done, plays the animation of D_800A62C4 once and hides */
void func_800A5AF0(StageWanderer *task) {
    StageTile *tile;
    StageTile *rec;
    StageTile *fading;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tile.anim.index = task->start;
        task->tile.anim.timer = D_800A6298[0].duration;
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == task->tileAnim) {
                task->tile.tile = rec;
                task->homeX = rec->unkA;
                task->homeY = rec->unkC;
                task->x = rec->unkA << 8;
                task->y = rec->unkC << 8;
            }
        }
        task->period = 0x28;
        task->timer = task->start;
        task->speed = D_800A62F4[task->speedIndex];
        task->angle = (RANDOM.next() & 0xFF) << 4;
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->mode != 0) {
            func_800A5974(task);
        }
        tile = task->tile.tile;
        if (task->mode != 0) {
            tile->visible = 1;
            tile->unk9 = func_800A56A8(&task->tile, D_800A6298, 0, 0);
            tile->unkA = task->posX;
            tile->unkC = task->posY;
        } else {
            tile->visible = 0;
        }
        if (task->mode == 3) {
            task->speed -= 4;
            if (task->speed <= 0x10) {
                task->setState(task, TASK_DONE);
            }
        }
        if (task->mode == 2) {
            if (--task->wait <= 0) {
                task->mode = 3;
            }
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->tile.anim.index = 0;
            task->tile.anim.timer = D_800A62C4[0].duration;
            task->setSubstate(task, 1);
        }
        func_800A5974(task);
        fading = task->tile.tile;
        frame = func_800A56A8(&task->tile, D_800A62C4, 1, 0);
        switch (frame) {
        case 0x12C:
            fading->visible = 0;
            break;
        case 0xFF:
            fading->visible = 0;
            task->mode = 0;
            task->setState(task, TASK_RUN);
            break;
        default:
            fading->visible = 1;
            fading->unk9 = frame;
            fading->unkA = task->posX;
            fading->unkC = task->posY;
            break;
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Makes the wanderer wait 60 frames, then slow down and finish */
void func_800A5DCC(StageWanderer *task) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x3C;
    }
}

void *func_800A5DE8(s32 arg) {
    return createTaskWithId(func_800A5AF0, 0x80, 0, arg);
}

/* Creates a wanderer of the record with the given animation */
StageWanderer *func_800A5E18(s32 tileAnim, s32 speedIndex, s32 start) {
    StageWanderer *task = createTask(func_800A5AF0, sizeof(StageWanderer), 0);

    task->start = start;
    task->speedIndex = speedIndex;
    task->tileAnim = tileAnim;
    return task;
}

/* Creates the task of func_800A4CA4 (id 0x33E) before progress 15 */
void func_800A5E70(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (GAME_PROGRESS < 15) {
            children[0] = func_800A4E8C(0x33E);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5EE0(void *owner) {
    StageTask *task = createTask(func_800A5E70, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6594[0]();
    return task;
}

/* Sets the progress to 15 and applies flag action 0x8010 */
void func_800A5F3C(void) {
    GAME_PROGRESS = 15;
    FLAGS_00.applyAction(0x8010, 1);
}

extern s32 D_800A6414[];
extern s32 D_800A6534[];
extern s32 D_800A6340[];
extern s32 D_800A6408[];
extern s32 D_800A6598[];
#if VERSION_US
#define STAGE_TEXT 0xF7
#define STAGE_FILE 0x354
#define STAGE_ARCHIVE 0x44F
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xEF)
#define STAGE_FILE 0x363
#define STAGE_ARCHIVE 0x45F
#endif
void func_800A5F74(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A6414;
    D_800990B4.unk14 = D_800A6534;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0xC200, 0x1A500};
    D_800990B4.unk28 = D_800A6340;
    D_800990B4.unk3C = 0x10;
    D_800990B4.unk40 = 0x60400000;
    D_800990B4.unk4C = D_800A6408;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6598;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.unk50(0);
}

void func_800A5F74();
void func_800A5F3C();
extern AnimFrame D_800A619C[];
extern AnimFrame D_800A6210[];
extern AnimFrame D_800A61DC[];
extern AnimFrame D_800A6250[];
extern s32 D_800A63C0[];
extern s32 D_800A63D8[];
extern s32 D_800A63E0[];
extern s32 D_800A63F4[];
extern s32 D_800A6060[];

s32 D_800A6060[] = {
    1536, 0x1020002, 0x700002, 0x30188,
    0x820100, 0x16F0060, 0x820101, 0x70001,
    0x32D0101, 0x20337, 0x20302, 0x20101,
    0x30001, 0x1E0300, 0x3230101, 0x20325,
    0x3C0300, 0x3230101, 0x20326, 0x1E0300,
    512, 0x20001, 0x3010003, 0x1E0300,
    0x820100, 0, 0x820101, 0x70001,
    0x32D0101, 0x2034A, 0x1E0300, 512,
    0x20002, 0x3010003, 0x33E0101, 0x2034C,
    0xD20300, 512, 0x20003, 0x3010003,
    0x20101, 0x70001, 0x1E0300, 0x20102,
    0x1A800B0, 0x3000007, 0x304003C, 0x4700235,
    0x700E0, 0,
};
AnimFrame D_800A6128[] = {
    { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 },
    { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 11, 8 },
    { 12, 8 }, { 13, 8 }, { 14, 8 }, { 255, 0 },
};
AnimFrame D_800A6168[] = {
    { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 },
    { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 11, 8 },
    { 255, 0x3E7 },
};
AnimFrame D_800A619C[] = {
    { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 },
    { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 11, 8 },
    { 12, 8 }, { 13, 8 }, { 14, 8 }, { 255, 0 },
};
AnimFrame D_800A61DC[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 6, 6 }, { 7, 6 },
    { 8, 6 }, { 9, 6 }, { 10, 6 }, { 11, 6 },
    { 255, 0x3E7 },
};
AnimFrame D_800A6210[] = {
    { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 },
    { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 11, 8 },
    { 12, 8 }, { 13, 8 }, { 14, 8 }, { 255, 0 },
};
AnimFrame D_800A6250[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 6, 6 }, { 7, 6 },
    { 8, 6 }, { 9, 6 }, { 10, 6 }, { 11, 6 },
    { 255, 0x3E7 },
};
AnimFrame *D_800A6284[] = {
    D_800A619C, D_800A6210,
};
AnimFrame *D_800A628C[] = {
    D_800A61DC, D_800A6250,
};
u8 D_800A6294[2][2] = {
    { 62, 63 },
    { 64, 65 },
};
AnimFrame D_800A6298[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 4, 4 }, { 3, 4 },
    { 2, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A62C4[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 255, 0x3E7 },
};
u16 D_800A62F4[] = {
    96, 80, 72, 64,
};
u16 D_800A62FC[] = {
    0, 0x648, 0xC93, 0x12E2, 0x1936, 0x1F92, 0x259F, 0x2C6B,
    0x32EB, 0x39C7, 0x401F, 0x46D7, 0x4DA7, 0x5491, 0x5B98, 0x62BF,
    0x6A09, 0x7179, 0x7913, 0x80DB, 0x88B5, 0x9105, 0x9970, 0xA21B,
    0xAB0D, 0xB44A, 0xBDDC, 0xC7C8, 0xD217, 0xDCD2, 0xE805, 0xF3BA,
    0xFFFE, 0xFFFF,
};
s32 D_800A6340[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0, 0, 0, 0,
    0x1000140, 0x1D8017A, 0xD800E8, 0x1F10170,
};
s32 D_800A63C0[] = {
    0, 0, 826, 0,
    0, 0,
};
s32 D_800A63D8[] = {
    0x1600E, 65535,
};
s32 D_800A63E0[] = {
    0, (s32)D_800A63C0, 0x4003F, 0x6D00FA,
    1,
};
s32 D_800A63F4[] = {
    (s32)D_800A63D8, 0, 0x50082, 0x16F0060,
    7,
};
s32 D_800A6408[] = {
    (s32)D_800A63E0, (s32)D_800A63F4, 0,
};
s32 D_800A6414[] = {
    0x2FF0800, 62, 0x2E0000, 288,
    0x3000000, 0xD0240, 0, 0x1200034,
    0, 0x2400200, 13, 0x9A0000,
    262, 0x1000000, 0xD0240, 0,
    0x16700AE, 0, 0x2400700, 14,
    0x670000, 297, 0x5000000, 0xE0240,
    0, 0xEC0075, 0, 0x2400600,
    14, 0xD90000, 300, 0x10000,
    0x2320240, 0xC0100, 0x1200030, 0,
    0x2400001, 0x1000232, 0xA0000C, 280,
    0x10000, 0x2330240, 0xC0100, 0xF80068,
    0, 0x2400001, 0x1000233, 0xE9000C,
    263, 0x10000, 0x2330240, 0xC0100,
    0x14F00E9, 0, 0x6FF0A00, 60,
    0x320000, 239, 0x9000000, 0x3F06FF,
    0, 0x120002E, 0, 0x4400001,
    0, 0xF00000, 0x870048, 0,
    0, 0, 0, 0,
};
s32 D_800A6534[] = {
    0x1600E, 65535, 0x1720008, 0,
    0, 0, 65535, 65535,
    0xE0003, 0xA800EF, 0, 0,
    65535, 65535, 0xE0002, 0x19000DF,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A6594[])(void) = {
    func_800A5F74,
};
s32 D_800A6598[] = {
    370, (s32)D_800A6060,
#if VERSION_US
    0x12E0028,
#elif VERSION_EU
    0x1350028,
#endif
    0, (s32)func_800A5F3C, -1, 0,
    0, 0, 0,
};
