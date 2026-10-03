#include "common.h"
#include "stage.h"
extern s32 D_800A6E54[];
extern s32 D_800A6984[];
extern s32 D_800A6B44[];
extern u8 D_800A69A0[];
extern u8 D_800A6D60[];
extern u8 D_800A6B54[];
void func_800A5E78();
void func_800A5800();
void func_800A53C0();
void func_800A503C();
extern void (*D_800A6E50[])(void);
void func_800A62B4();
void func_800A63B8();
s32 func_800A5B8C(s32 x, s32 y);
extern u16 D_800A6730[];
extern AnimFrame *D_800A6718[];
extern AnimFrame *D_800A6720[];
extern u16 D_800A6728[];
void *func_800A5274(void);
void *func_800A56B4(void);
void *func_800A5A04(void);
StageWanderPair *func_800A625C(s32 tileAnim, s32 speedIndex, s32 start);
void func_800A5228();
void func_800A5668();
void func_800A59B8();
void func_800A6210();
extern AnimFrame D_800A65A4[];
extern AnimFrame D_800A65B8[];
extern AnimFrame *D_800A663C[];
extern AnimFrame *D_800A6644[];
extern AnimFrame D_800A664C[];

/* Creates the stage's objects (three records and nine wandering pairs); in TASK_DONE tells them all to go away */
void func_800A4CA4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A5274();
        children[1] = func_800A56B4();
        children[2] = func_800A5A04();
        children[3] = func_800A625C(1, 0, 0);
        children[4] = func_800A625C(2, 0, 5);
        children[5] = func_800A625C(3, 1, 0);
        children[6] = func_800A625C(4, 1, 5);
        children[7] = func_800A625C(5, 1, 0);
        children[8] = func_800A625C(6, 2, 0);
        children[9] = func_800A625C(7, 2, 2);
        children[10] = func_800A625C(8, 3, 5);
        children[11] = func_800A625C(9, 3, 3);
        task->nextState(task);
        break;
    case TASK_RUN:
        break;
    case TASK_DONE:
        func_800A5228(children[0], 0, 0);
        func_800A5668(children[1], 0, 0);
        func_800A59B8(children[2], 0, 0);
        func_800A6210(children[3], 0, 0);
        func_800A6210(children[4], 0, 0);
        func_800A6210(children[5], 0, 0);
        func_800A6210(children[6], 0, 0);
        func_800A6210(children[7], 0, 0);
        func_800A6210(children[8], 0, 0);
        func_800A6210(children[9], 0, 0);
        func_800A6210(children[10], 0, 0);
        func_800A6210(children[11], 0, 0);
        task->setState(task, TASK_RUN);
        break;
    case TASK_KILL:
        break;
    }
}

/* Ends the task when map object 0x34B is triggered */
void func_800A4EB4(StageTask *task, s32 id) {
    if (task != NULL && id == 0x34B) {
        task->setState(task, TASK_DONE);
    }
}

/* Creates the task of func_800A4CA4 with an id */
void *func_800A4EEC(s32 arg) {
    return createTaskWithId(func_800A4CA4, 0x50, 0x30, arg);
}

s32 func_800A4F1C(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4F1C(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Animates the record of animation 0x15 (frame 2) while mode isn't 0; fades it out wait frames after mode 2 */
void func_800A503C(StageTileSolo *task) {
    StageTile *rec;
    StageTile *tile;
    StageTile *fading;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tile.anim.index = 0;
        task->tile.anim.timer = D_800A65A4[0].duration;
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 0x15) {
                task->tile.tile = rec;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        tile = task->tile.tile;
        if (task->mode != 0) {
            tile->visible = 1;
            tile->frame = 2;
            tile->unk9 = func_800A4F1C(&task->tile, D_800A65A4, 0, 0);
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
            task->tile.anim.timer = D_800A65B8[0].duration;
            task->setSubstate(task, 1);
        }
        fading = task->tile.tile;
        frame = func_800A4F1C(&task->tile, D_800A65B8, 1, 0);
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
            fading->frame = 2;
            fading->unk9 = frame;
            break;
        }
        break;
    case TASK_KILL:
        break;
    }
}

void func_800A5228(StageTileDuo *task, s32 arg1, s32 arg2) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x96;
    }
}

void *func_800A5244(s32 arg) {
    return createTaskWithId(func_800A503C, 0x5C, 0, arg);
}

void *func_800A5274(void) {
    return createTask(func_800A503C, 0x5C, 0);
}

s32 func_800A52A0(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A52A0(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Animates the records of animations 0x13 and 0x14 while mode isn't 0; fades them out wait frames after mode 2 */
void func_800A53C0(StageTileDuo *task) {
    StageTile *rec;
    StageTile *tile;
    StageTile *fading;
    s32 i;
    s32 j;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tiles[0].anim.index = 0;
        task->tiles[0].anim.timer = D_800A663C[0]->duration;
        task->tiles[1].anim.index = 0;
        task->tiles[1].anim.timer = D_800A663C[1]->duration;
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            switch (rec->anim) {
            case 0x13:
                task->tiles[0].tile = rec;
                break;
            case 0x14:
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
                tile->frame = func_800A52A0(&task->tiles[i], D_800A663C[i], 0, 0);
                tile->unk9 = 0;
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
            task->tiles[0].anim.timer = D_800A6644[0]->duration;
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A6644[1]->duration;
            task->setSubstate(task, 1);
        }
        for (j = 0; j < 2; j++) {
            fading = task->tiles[j].tile;
            frame = func_800A52A0(&task->tiles[j], D_800A6644[j], 1, 0);
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
                fading->frame = frame;
                fading->unk9 = 0;
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Tells the task to go away after 90 frames (mode 2) */
void func_800A5668(StageTileDuo *task) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x5A;
    }
}

void *func_800A5684(s32 arg) {
    return createTaskWithId(func_800A53C0, 0x64, 0, arg);
}

void *func_800A56B4(void) {
    return createTask(func_800A53C0, 0x64, 0);
}

s32 func_800A56E0(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A56E0(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Shows the record of animation 0x16 (frame 0x21) while mode isn't 0; fades it out wait frames after mode 2 */
void func_800A5800(StageTileSolo *task) {
    StageTile *rec;
    StageTile *tile;
    StageTile *fading;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 0x16) {
                task->tile.tile = rec;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        tile = task->tile.tile;
        if (task->mode != 0) {
            tile->visible = 1;
            tile->frame = 0x21;
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
            task->tile.anim.timer = D_800A664C[0].duration;
            task->setSubstate(task, 1);
        }
        fading = task->tile.tile;
        frame = func_800A56E0(&task->tile, D_800A664C, 1, 0);
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
            fading->frame = frame;
            fading->unk9 = 0;
            break;
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Tells the task to go away after 40 frames (mode 2) */
void func_800A59B8(StageTileDuo *task) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x28;
    }
}

void *func_800A59D4(s32 arg) {
    return createTaskWithId(func_800A5800, 0x5C, 0, arg);
}

void *func_800A5A04(void) {
    return createTask(func_800A5800, 0x5C, 0);
}

s32 func_800A5A30(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5A30(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

s32 func_800A5B50(StageWanderPair *task, s32 dist) {
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

s32 func_800A5B8C(s32 x, s32 y) {
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
        if (D_800A6730[i] <= ratio && ratio <= D_800A6730[i + 1]) {
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

void func_800A5CFC(StageWanderPair *task) {
    s32 dx;
    s32 dy;

    task->timer += GFX_FUNCS.getFrameTime();
    if (task->period < task->timer) {
        if (func_800A5B50(task, 0x1E)) {
            task->angle = ((func_800A5B8C(task->homeX - task->posX, task->homeY - task->posY) - 0x40) << 4) & 0xFFF;
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

void func_800A5E78(StageWanderPair *task) {
    StageTile *tile;
    StageTile *rec;
    StageTile *fading;
    s32 i;
    s32 j;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tiles[0].anim.index = task->start;
        task->tiles[0].anim.timer = D_800A6718[0]->duration;
        task->tiles[1].anim.index = task->start;
        task->tiles[1].anim.timer = D_800A6718[1]->duration;
        task->mode = 1;
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == task->tileAnim) {
                task->tiles[0].tile = rec;
                task->homeX = rec->unkA;
                task->homeY = rec->unkC;
                task->x = rec->unkA << 8;
                task->y = rec->unkC << 8;
            }
            if (rec->anim == task->tileAnim + 9) {
                task->tiles[1].tile = rec;
            }
        }
        task->period = 0x28;
        task->timer = task->start;
        task->speed = D_800A6728[task->speedIndex];
        task->angle = (RANDOM.next() & 0xFF) << 4;
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->mode != 0) {
            func_800A5CFC(task);
        }
        for (i = 0; i < 2; i++) {
            tile = task->tiles[i].tile;
            if (task->mode != 0) {
                tile->visible = 1;
                tile->unk9 = func_800A5A30(&task->tiles[i], D_800A6718[i], 0, 0);
                tile->unkA = task->posX;
                tile->unkC = task->posY;
            } else {
                tile->visible = 0;
            }
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
            task->tiles[0].anim.index = 0;
            task->tiles[0].anim.timer = D_800A6720[0]->duration;
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A6720[1]->duration;
            task->setSubstate(task, 1);
        }
        func_800A5CFC(task);
        for (j = 0; j < 2; j++) {
            fading = task->tiles[j].tile;
            frame = func_800A5A30(&task->tiles[j], D_800A6720[j], 1, 0);
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
        }
        break;
    case TASK_KILL:
        break;
    }
}

void func_800A6210(StageWanderer *task) {
    if (task != NULL) {
        task->mode = 2;
        task->wait = 0x3C;
    }
}

void *func_800A622C(s32 arg) {
    return createTaskWithId(func_800A5E78, 0x88, 0, arg);
}

/* Creates a pair of wandering records: tileAnim and tileAnim + 9 */
StageWanderPair *func_800A625C(s32 tileAnim, s32 speedIndex, s32 start) {
    StageWanderPair *task = createTask(func_800A5E78, sizeof(StageWanderPair), 0);

    task->start = start;
    task->speedIndex = speedIndex;
    task->tileAnim = tileAnim;
    return task;
}

/* The stage task: creates the object of map object 0x33D before progress 30 */
void func_800A62B4(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        if (GAME_PROGRESS < 0x1E) {
            children[0] = func_800A4EEC(0x33D);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A6324(void *owner) {
    StageTask *task = createTask(func_800A62B4, sizeof(StageTask), 4);

    task->owner = owner;
    D_800A6E50[0]();
    return task;
}

/* Event: sets the progress to 30 and applies action 0x8011 */
void func_800A6380(void) {
    GAME_PROGRESS = 0x1E;
    FLAGS_00.applyAction(0x8011, 1);
}

#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x6A8
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x6B8
#endif
void func_800A63B8(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A6B54;
    D_800990B4.unk14 = D_800A6D60;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x13D00, 0x38500};
    D_800990B4.unk28 = D_800A69A0;
    D_800990B4.unk3C = 0x37;
    D_800990B4.unk40 = 0x60DC0000;
    D_800990B4.unk4C = D_800A6B44;
    D_800990B4.unk20 = D_800A6984;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6E54;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 2);
    D_8009A70C.setFile(4, STAGE_FILE << 16 | 3);
    D_8009A70C.unk50(0);
}

void func_800A6380();
extern AnimFrame D_800A65D4[];
extern AnimFrame D_800A6608[];
extern AnimFrame D_800A65F0[];
extern AnimFrame D_800A6624[];
extern AnimFrame D_800A6660[];
extern AnimFrame D_800A66BC[];
extern AnimFrame D_800A668C[];
extern AnimFrame D_800A66E8[];
extern s32 D_800A6774[];
extern s32 D_800A6780[];
extern s32 D_800A678C[];
extern s32 D_800A6798[];
extern s32 D_800A67A4[];
extern s32 D_800A67B0[];
extern s32 D_800A67BC[];
extern s32 D_800A67C8[];
extern s32 D_800A67F8[];
extern s32 D_800A6804[];
extern s32 D_800A6810[];
extern s32 D_800A681C[];
extern s32 D_800A6828[];
extern s32 D_800A6834[];
extern s32 D_800A6840[];
extern s32 D_800A684C[];
extern s32 D_800A687C[];
extern s32 D_800A6888[];
extern s32 D_800A6894[];
extern s32 D_800A68A0[];
extern s32 D_800A68AC[];
extern s32 D_800A68B8[];
extern s32 D_800A68C4[];
extern s32 D_800A68D0[];
extern s32 D_800A6900[];
extern s32 D_800A690C[];
extern s32 D_800A6918[];
extern s32 D_800A6924[];
extern s32 D_800A6930[];
extern s32 D_800A693C[];
extern s32 D_800A6948[];
extern s32 D_800A6954[];
extern s32 D_800A67D4[];
extern s32 D_800A6858[];
extern s32 D_800A68DC[];
extern s32 D_800A6960[];
extern s32 D_800A6A30[];
extern s32 D_800A6A40[];
extern s32 D_800A6A48[];
extern s32 D_800A6A54[];
extern s32 D_800A6A5C[];
extern s32 D_800A6A6C[];
extern s32 D_800A6A7C[];
extern s32 D_800A6AE4[];
extern s32 D_800A6A90[];
extern s32 D_800A6AEC[];
extern s32 D_800A6AF4[];
extern s32 D_800A6AA8[];
extern s32 D_800A6B08[];
extern s32 D_800A6B1C[];
extern s32 D_800A6B30[];
extern s32 D_800A64CC[];

s32 D_800A64CC[] = {
    0x20102, 0xBE0098, 0x1000003, 0x800083,
    0x10100B2, 0x10083, 0x1010001, 0x337032D,
    0x3020002, 0x1020002, 0x900002, 0x300BA,
    0x20302, 0x20101, 0x30001, 0x1E0300,
    0x3230101, 0x20325, 0x3C0300, 0x3230101,
    0x20326, 0x1E0300, 512, 0x20001,
    0x3010003, 0x1E0300, 0x830100, 0,
    0x830101, 0x70001, 0x32D0101, 0x2034A,
    0x1E0300, 0x1E0300, 0x33D0101, 0x2034B,
    0xD20300, 512, 0x20002, 0x3010003,
    0x1E0300, 512, 0x20003, 0x3010003,
    0x1E0300, 0x20102, 0xBE0098, 0x3020007,
    0x1020002, 0xD00002, 0x70100, 0x2AB0304,
    0x1E8041E, 5,
};
AnimFrame D_800A65A4[] = {
    { 0, 12 }, { 1, 12 }, { 2, 12 }, { 1, 12 },
    { 255, 0 },
};
AnimFrame D_800A65B8[] = {
    { 0, 12 }, { 1, 12 }, { 2, 12 }, { 3, 12 },
    { 4, 12 }, { 5, 12 }, { 255, 0x3E7 },
};
AnimFrame D_800A65D4[] = {
    { 37, 12 }, { 38, 12 }, { 39, 12 }, { 40, 12 },
    { 41, 12 }, { 42, 12 }, { 255, 0 },
};
AnimFrame D_800A65F0[] = {
    { 3, 4 }, { 4, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A6608[] = {
    { 91, 12 }, { 92, 12 }, { 93, 12 }, { 94, 12 },
    { 95, 12 }, { 96, 12 }, { 255, 0 },
};
AnimFrame D_800A6624[] = {
    { 8, 4 }, { 9, 4 }, { 10, 4 }, { 11, 4 },
    { 12, 4 }, { 255, 0x3E7 },
};
AnimFrame *D_800A663C[] = {
    D_800A65D4, D_800A6608,
};
AnimFrame *D_800A6644[] = {
    D_800A65F0, D_800A6624,
};
AnimFrame D_800A664C[] = {
    { 33, 4 }, { 34, 4 }, { 35, 4 }, { 36, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A6660[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 4, 4 }, { 3, 4 },
    { 2, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A668C[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 255, 0x3E7 },
};
AnimFrame D_800A66BC[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 4, 4 }, { 3, 4 },
    { 2, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A66E8[] = {
    { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 },
    { 4, 4 }, { 5, 4 }, { 6, 8 }, { 7, 8 },
    { 8, 8 }, { 9, 8 }, { 10, 8 }, { 255, 0x3E7 },
};
AnimFrame *D_800A6718[] = {
    D_800A6660, D_800A66BC,
};
AnimFrame *D_800A6720[] = {
    D_800A668C, D_800A66E8,
};
u16 D_800A6728[] = {
    96, 80, 72, 64,
};
u16 D_800A6730[] = {
    0, 0x648, 0xC93, 0x12E2, 0x1936, 0x1F92, 0x259F, 0x2C6B,
    0x32EB, 0x39C7, 0x401F, 0x46D7, 0x4DA7, 0x5491, 0x5B98, 0x62BF,
    0x6A09, 0x7179, 0x7913, 0x80DB, 0x88B5, 0x9105, 0x9970, 0xA21B,
    0xAB0D, 0xB44A, 0xBDDC, 0xC7C8, 0xD217, 0xDCD2, 0xE805, 0xF3BA,
    0xFFFE, 0xFFFF,
};
s32 D_800A6774[] = {
    158, 27, 0x60080000,
};
s32 D_800A6780[] = {
    158, 27, 0x60080000,
};
s32 D_800A678C[] = {
    158, 27, 0x60080000,
};
s32 D_800A6798[] = {
    158, 27, 0x60080000,
};
s32 D_800A67A4[] = {
    158, 27, 0x60080000,
};
s32 D_800A67B0[] = {
    158, 27, 0x60080000,
};
s32 D_800A67BC[] = {
    158, 27, 0x60080000,
};
s32 D_800A67C8[] = {
    158, 27, 0x60080000,
};
s32 D_800A67D4[] = {
    3, (s32)D_800A6774, (s32)D_800A6780, (s32)D_800A678C,
    (s32)D_800A6798, (s32)D_800A67A4, (s32)D_800A67B0, (s32)D_800A67BC,
    (s32)D_800A67C8,
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
    0, (s32)D_800A67F8, (s32)D_800A6804, (s32)D_800A6810,
    (s32)D_800A681C, (s32)D_800A6828, (s32)D_800A6834, (s32)D_800A6840,
    (s32)D_800A684C,
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
    0, 0, 0x60040000,
};
s32 D_800A68AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A68B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A68C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A68D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A68DC[] = {
    0, (s32)D_800A687C, (s32)D_800A6888, (s32)D_800A6894,
    (s32)D_800A68A0, (s32)D_800A68AC, (s32)D_800A68B8, (s32)D_800A68C4,
    (s32)D_800A68D0,
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
    0, 0, 0x60040000,
};
s32 D_800A6930[] = {
    0, 0, 0x60040000,
};
s32 D_800A693C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6948[] = {
    0, 0, 0x60040000,
};
s32 D_800A6954[] = {
    0, 0, 0x60040000,
};
s32 D_800A6960[] = {
    0, (s32)D_800A6900, (s32)D_800A690C, (s32)D_800A6918,
    (s32)D_800A6924, (s32)D_800A6930, (s32)D_800A693C, (s32)D_800A6948,
    (s32)D_800A6954,
};
s32 D_800A6984[] = {
    78, 0, 0, (s32)D_800A67D4,
    (s32)D_800A6858, (s32)D_800A68DC, (s32)D_800A6960,
};
u8 D_800A69A0[] = {
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
    0x80, 0x01, 0x00, 0x01, 0xAE, 0x01, 0x18, 0x01,
    0xB8, 0x01, 0x18, 0x00, 0x70, 0x01, 0xF5, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x80, 0x01, 0x38, 0x01,
    0x00, 0x01, 0x38, 0x00, 0x40, 0x01, 0xF4, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x75, 0x01, 0x20, 0x01,
    0xD4, 0x00, 0x20, 0x00, 0x50, 0x01, 0xF4, 0x01,
};
s32 D_800A6A30[] = {
    0x1021F, 0x18494, 0x17013, 65535,
};
s32 D_800A6A40[] = {
    0x18681, 65535,
};
s32 D_800A6A48[] = {
    34433, 0, 65535,
};
s32 D_800A6A54[] = {
    0x10000, 65535,
};
s32 D_800A6A5C[] = {
    34433, 0x10000, 33917, 65535,
};
s32 D_800A6A6C[] = {
    34433, 0x10000, 0x1847D, 65535,
};
s32 D_800A6A7C[] = {
    0x18681, 34432, 33917, 0x17013,
    65535,
};
s32 D_800A6A90[] = {
    0, (s32)D_800A6A30, 383, 0,
    0, 0,
};
s32 D_800A6AA8[] = {
    (s32)D_800A6A40, 0, 738, (s32)D_800A6A48,
    (s32)D_800A6A54, 739, (s32)D_800A6A5C, 0,
    740, (s32)D_800A6A6C, (s32)D_800A6A7C, 741,
    0, 0, 0,
};
s32 D_800A6AE4[] = {
    543, 65535,
};
s32 D_800A6AEC[] = {
    0x1601D, 65535,
};
s32 D_800A6AF4[] = {
    0x17043, 0x1704B, 0x18680, 34433,
    65535,
};
s32 D_800A6B08[] = {
    (s32)D_800A6AE4, (s32)D_800A6A90, 0x40021, 0xB10221,
    1,
};
s32 D_800A6B1C[] = {
    (s32)D_800A6AEC, 0, 0x50083, 0xB20080,
    1,
};
s32 D_800A6B30[] = {
    (s32)D_800A6AF4, (s32)D_800A6AA8, 0x600AB, 0x1230281,
    1,
};
s32 D_800A6B44[] = {
    (s32)D_800A6B08, (s32)D_800A6B1C, (s32)D_800A6B30, 0,
};
u8 D_800A6B54[] = {
    0x00, 0x15, 0xFF, 0x02, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x13, 0xFF, 0x02, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xFF, 0x02,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0xFF, 0x02, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x50, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0xFF, 0x02, 0x0D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x58, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0xFF, 0x02, 0x0D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x48, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFF, 0x02,
    0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
    0xFF, 0x02, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x98, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x05, 0xFF, 0x02, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xA8, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0xFF, 0x02, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x70, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xFF, 0x02,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
    0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0xFF, 0x02, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xD0, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0xFF, 0x02, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x50, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0C, 0xFF, 0x02, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xFF, 0x02,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00,
    0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
    0xFF, 0x02, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0E, 0xFF, 0x02, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x98, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0D, 0xFF, 0x02, 0x11, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xFF, 0x02,
    0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00,
    0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
    0xFF, 0x02, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x70, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x12, 0xFF, 0x02, 0x12, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xD0, 0x00, 0x58, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x16, 0xFF, 0x06, 0x21, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x2C, 0x01, 0x2C, 0x3B, 0x0A, 0x00, 0x80, 0x00,
    0x5F, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x2C, 0x01, 0x2C, 0x3B, 0x0A, 0x00,
    0x80, 0x00, 0x8B, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x2C, 0x01, 0x2C, 0x3B,
    0x0A, 0x00, 0xA3, 0x02, 0xCA, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x3C, 0x01,
    0x3C, 0x46, 0x0A, 0x00, 0x1C, 0x01, 0x13, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x3C, 0x01, 0x3C, 0x46, 0x0A, 0x00, 0xC7, 0x02,
    0x2D, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x53, 0x01, 0x88, 0x01, 0x99, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A6D60[] = {
    0x93, 0x70, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0A, 0x00, 0xE0, 0x02, 0x40, 0x02, 0xD8, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x01, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x05, 0x00, 0x2F, 0x02, 0xC8, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x05, 0x00, 0x20, 0x02, 0x72, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x05, 0x00, 0x51, 0x02, 0xF7, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x05, 0x00, 0x60, 0x02, 0xA1, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x02, 0x00, 0x0A, 0x00, 0xC0, 0x01, 0x81, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x03, 0x00, 0x0A, 0x00, 0xD0, 0x01, 0xDA, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1D, 0x60, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x08, 0x00, 0xF8, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x93, 0x70, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0A, 0x00, 0xE0, 0x02, 0x40, 0x02, 0xD8, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x01, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A6E50[])(void) = {
    func_800A63B8,
};
s32 D_800A6E54[] = {
    760, (s32)D_800A64CC,
#if VERSION_US
    0x1350023,
#elif VERSION_EU
    0x13C0023,
#endif
    0, (s32)func_800A6380, -1, 0,
    0, 0, 0,
};
