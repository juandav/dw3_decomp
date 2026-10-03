#include "common.h"
#include "stage.h"
extern s32 D_800A76C8[];
extern s32 D_800A7BA4[];
extern s32 D_800A7954[];
extern u8 D_800A76E4[];
extern u8 D_800A7B70[];
extern u8 D_800A7988[];
void func_800A561C();
void func_800A5094();
void func_800A4DF8();
extern void (*D_800A7BA0[])(void);
void func_800A5A80();
void func_800A6898();
extern AnimFrame D_800A711C[];
extern AnimFrame D_800A7140[];
extern AnimFrame D_800A7160[];
extern AnimFrame D_800A717C[];
extern AnimFrame D_800A73D8[];
extern AnimFrame D_800A73F0[];
extern AnimFrame D_800A7448[];
extern AnimFrame D_800A7460[];
extern StageEffectSpot D_800A73C0[];
void *func_800A5498(s32 id);
void *func_800A5A1C(s32 id);
StageEffect *func_800A6758(s32 x, s32 y, s32 frame);
extern AnimFrame D_800A7210[];
extern AnimFrame D_800A7280[];
extern AnimFrame D_800A7328[];
extern AnimFrame D_800A738C[];
extern AnimFrame D_800A719C[];
extern AnimFrame D_800A71D0[];
extern AnimFrame D_800A7204[];
extern AnimFrame D_800A72B4[];
extern AnimFrame D_800A72E8[];
extern AnimFrame D_800A731C[];

s32 func_800A4D04(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        func_800A4D04(anim, frames, depth + 1);
    }
    return frame->frame;
}

/* Sets the frame of the records of StageInfo.unk10 from four animations, which run once per record */
void func_800A4DF8(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A711C[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A7140[0].duration;
        task->anims[2].index = 0;
        task->anims[2].timer = D_800A7160[0].duration;
        task->anims[3].index = 0;
        task->anims[3].timer = D_800A717C[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            switch (tile->anim) {
            case 1:
                tile->frame = func_800A4D04(&task->anims[0], D_800A711C, 0);
                break;
            case 2:
                tile->frame = func_800A4D04(&task->anims[1], D_800A7140, 0);
                break;
            case 3:
                tile->frame = func_800A4D04(&task->anims[2], D_800A7160, 0);
                break;
            case 4:
                tile->frame = func_800A4D04(&task->anims[3], D_800A717C, 0);
                break;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A4F48(void) {
    return createTask(func_800A4DF8, 0x60, 0);
}

s32 func_800A4F74(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A4F74(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Animates the records with animations 5 to 10 by mode (0: hidden, 1 and 3: the first two once, then mode 2 or 0; 2, the first: the other four) */
void func_800A5094(StageTileSix *task) {
    StageTile *rec;
    StageTile *tile;
    s32 done;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim >= 5 && rec->anim <= 10) {
                switch (rec->anim) {
                case 5:
                    task->tiles[0].tile = rec;
                    task->tiles[0].anim.index = 0;
                    task->tiles[0].anim.timer = D_800A719C[0].duration;
                    break;
                case 6:
                    task->tiles[1].tile = rec;
                    task->tiles[1].anim.index = 0;
                    task->tiles[1].anim.timer = D_800A71D0[0].duration;
                    break;
                case 7:
                    task->tiles[2].tile = rec;
                    task->tiles[2].anim.index = 0;
                    task->tiles[2].anim.timer = D_800A7204[0].duration;
                    break;
                case 8:
                    task->tiles[3].tile = rec;
                    task->tiles[3].anim.index = 0;
                    task->tiles[3].anim.timer = D_800A7210[0].duration;
                    break;
                case 9:
                    task->tiles[4].tile = rec;
                    task->tiles[4].anim.index = 0;
                    task->tiles[4].anim.timer = 0;
                    break;
                case 10:
                    task->tiles[5].tile = rec;
                    task->tiles[5].anim.index = 0;
                    task->tiles[5].anim.timer = 0;
                    break;
                }
            }
        }
        task->mode = 2;
        task->nextState(task);
        break;
    case TASK_RUN:
        done = 0;
        for (i = 0; i < 6; i++) {
            tile = task->tiles[i].tile;
            switch (task->mode) {
            case 0:
                tile->visible = 0;
                break;
            case 1:
                switch (i) {
                case 0:
                    frame = func_800A4F74(&task->tiles[0], D_800A719C, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 1:
                    frame = func_800A4F74(&task->tiles[1], D_800A71D0, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    tile->visible = 0;
                    break;
                }
                break;
            case 2:
                switch (i) {
                case 0:
                case 1:
                    tile->visible = 0;
                    break;
                case 2:
                    tile->frame = 0x28;
                    tile->unk9 = func_800A4F74(&task->tiles[i], D_800A7204, 0, 0);
                    tile->visible = 1;
                    break;
                case 3:
                    tile->frame = 2;
                    tile->unk9 = func_800A4F74(&task->tiles[i], D_800A7210, 0, 0);
                    tile->visible = 1;
                    break;
                case 4:
                    tile->visible = 1;
                    tile->frame = 3;
                    tile->unk9 = 0;
                    break;
                case 5:
                    tile->visible = 1;
                    tile->frame = 4;
                    tile->unk9 = 0;
                    break;
                }
                break;
            case 3:
                switch (i) {
                case 0:
                    frame = func_800A4F74(&task->tiles[0], D_800A7280, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 1:
                    frame = func_800A4F74(&task->tiles[1], D_800A7280, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    tile->visible = 0;
                    break;
                }
                break;
            }
        }
        if (done >= 2) {
            switch (task->mode) {
            case 1:
                task->mode = 2;
                break;
            case 3:
                task->mode = 0;
                break;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Plays the first two records backwards (mode 3) for map 0x359 */
void func_800A545C(StageTileSix *task, s32 id) {
    if (task != NULL && id == 0x359) {
        task->tiles[0].anim.index = 0;
        task->tiles[0].anim.timer = D_800A7210[15].duration;
        task->tiles[1].anim.index = 0;
        task->tiles[1].anim.timer = D_800A7280[0].duration;
        task->mode = 3;
    }
}

/* Creates the task of the six records with id ID, in mode 2 */
void *func_800A5498(s32 id) {
    StageTileSix *task = createTaskWithId(func_800A5094, 0x84, 0, id);

    task->mode = 2;
    return task;
}

void *func_800A54D0(void) {
    return createTask(func_800A5094, 0x84, 0);
}

s32 func_800A54FC(StageTileAnimFlag *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A54FC(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Animates the records with animations 11 to 16 by mode (0: hidden, 1 and 3: the first two once, then mode 2 or 0; 2, the first: the other four) */
void func_800A561C(StageTileSixW *task) {
    StageTile *rec;
    StageTile *tile;
    s32 done;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim >= 11 && rec->anim <= 16) {
                switch (rec->anim) {
                case 11:
                    task->tiles[0].tile = rec;
                    task->tiles[0].anim.index = 0;
                    task->tiles[0].anim.timer = D_800A72B4[0].duration;
                    break;
                case 12:
                    task->tiles[1].tile = rec;
                    task->tiles[1].anim.index = 0;
                    task->tiles[1].anim.timer = D_800A72E8[0].duration;
                    break;
                case 13:
                    task->tiles[2].tile = rec;
                    task->tiles[2].anim.index = 0;
                    task->tiles[2].anim.timer = D_800A731C[0].duration;
                    break;
                case 14:
                    task->tiles[3].tile = rec;
                    task->tiles[3].anim.index = 0;
                    task->tiles[3].anim.timer = D_800A7328[0].duration;
                    break;
                case 15:
                    task->tiles[4].tile = rec;
                    task->tiles[4].anim.index = 0;
                    task->tiles[4].anim.timer = 0;
                    break;
                case 16:
                    task->tiles[5].tile = rec;
                    task->tiles[5].anim.index = 0;
                    task->tiles[5].anim.timer = 0;
                    break;
                }
            }
        }
        task->mode = 2;
        task->nextState(task);
        break;
    case TASK_RUN:
        done = 0;
        for (i = 0; i < 6; i++) {
            tile = task->tiles[i].tile;
            switch (task->mode) {
            case 0:
                tile->visible = 0;
                break;
            case 1:
                switch (i) {
                case 0:
                    frame = func_800A54FC(&task->tiles[0], D_800A72B4, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 1:
                    frame = func_800A54FC(&task->tiles[1], D_800A72E8, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    tile->visible = 0;
                    break;
                }
                break;
            case 2:
                switch (i) {
                case 0:
                case 1:
                    tile->visible = 0;
                    break;
                case 2:
                    tile->frame = 0x29;
                    tile->unk9 = func_800A54FC(&task->tiles[i], D_800A731C, 0, 0);
                    tile->visible = 1;
                    break;
                case 3:
                    tile->frame = 0x11;
                    tile->unk9 = func_800A54FC(&task->tiles[i], D_800A7328, 0, 0);
                    tile->visible = 1;
                    break;
                case 4:
                    tile->visible = 1;
                    tile->frame = 0x12;
                    tile->unk9 = 0;
                    break;
                case 5:
                    tile->visible = 1;
                    tile->frame = 0x13;
                    tile->unk9 = 0;
                    break;
                }
                break;
            case 3:
                switch (i) {
                case 0:
                    frame = func_800A54FC(&task->tiles[0], D_800A738C, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 1:
                    frame = func_800A54FC(&task->tiles[1], D_800A738C, 1, 0);
                    if (frame != 0xFF) {
                        tile->frame = frame;
                        tile->visible = 1;
                    } else {
                        done++;
                        tile->frame = 0;
                        tile->visible = 0;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    tile->visible = 0;
                    break;
                }
                break;
            }
        }
        if (done >= 2) {
            switch (task->mode) {
            case 1:
                task->mode = 2;
                break;
            case 3:
                task->mode = 0;
                break;
            }
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Plays the first two records backwards (mode 3) for map 0x359 */
void func_800A59E0(StageTileSixW *task, s32 id) {
    if (task != NULL && id == 0x359) {
        task->tiles[0].anim.index = 0;
        task->tiles[0].anim.timer = D_800A7328[12].duration;
        task->tiles[1].anim.index = 0;
        task->tiles[1].anim.timer = D_800A738C[0].duration;
        task->mode = 3;
    }
}

/* Creates the task of the six records with id ID, in mode 2 */
void *func_800A5A1C(s32 id) {
    StageTileSixW *task = createTaskWithId(func_800A561C, 0x9C, 0, id);

    task->mode = 2;
    return task;
}

void *func_800A5A54(void) {
    return createTask(func_800A561C, 0x9C, 0);
}

/* Creates the stage tasks, the sprite effects and the event object of the story so far */
void func_800A5A80(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4F48();
        for (i = 0; i < 2; i++) {
            if (D_800A73C0[i].kind == 0) {
                children[3 + i] = func_800A6758(D_800A73C0[i].x, D_800A73C0[i].y, D_800A73C0[i].frame);
            }
        }
        do {
            if (GAME.progress == 0x17 && FLAGS_00.checkCondition(0x404E, 0)) {
                children[5] = func_80084B80(0x2A8);
                break;
            }
            if (GAME.progress == 0x17 && FLAGS_00.checkCondition(0x404E, 1) && FLAGS_00.checkCondition(0x404F, 0)) {
                children[5] = func_80084B80(0x2A9);
                children[1] = func_800A5498(0x33F);
                children[2] = func_800A5A1C(0x340);
                break;
            }
            if (GAME.progress == 0x17 && FLAGS_00.checkCondition(0x404F, 1)) {
                children[5] = func_80084B80(0x2AA);
                break;
            }
            if (GAME.progress == 0x26) {
                children[5] = func_80084B80(0x3C1);
                break;
            }
        } while (0);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5C40(void *owner) {
    StageTask *task = createTask(func_800A5A80, sizeof(StageTask), 0x18);

    task->owner = owner;
    D_800A7BA0[0]();
    return task;
}

s32 func_800A5C9C(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A5C9C(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Draws sprite IDX of the effect while it plays (a draw callback) */
void func_800A5DBC(StageEffect *task, void *arg, s32 idx) {
    SpriteDrawer drawer;
    Layer *layer = arg;
    StageSprite *sprite;
    s32 y;
    s32 x;
    s32 depth;

    if (task->state == TASK_RUN) {
        sprite = &task->sprites[idx];
        y = task->y;
        x = task->x;
        if (idx == 1) {
            y -= 0x20;
            depth = 4;
        } else {
            depth = 6;
        }
        initSpriteDrawer(&drawer);
        drawer.setTexture(0x140, 0x100);
        drawer.setLayer(layer, depth);
        drawer.setClutRow(sprite->clutRow);
        drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), sprite->frame, x, y);
    }
}

/* Whether the rectangle (x, y, w, h) is in the view of layer 0x1002 */
s32 func_800A5EAC(s32 x, s32 y, s32 w, s32 h) {
    RECT rect;
    struct Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getViewRect(layer, &rect);
    if (x + w < rect.x) {
        return 0;
    }
    if (rect.x + rect.w < x) {
        return 0;
    }
    if (y + h < rect.y) {
        return 0;
    }
    return rect.y + rect.h >= y;
}

/* An effect that plays its animation once and ends */
void func_800A5F70(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A73F0[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A73D8[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A73F0[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A73D8[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5C9C(&task->clutAnim, D_800A73D8, 0, 0);
        done = 0;
        frame = func_800A5C9C(&task->anim, D_800A73F0, 1, 0);
        switch (frame) {
        case 0xFF:
            task->sprites[1].frame = 0;
            done = 1;
            break;
        case 0x12C:
            task->sprites[1].frame = 0;
            break;
        default:
            task->sprites[1].frame = task->frame + frame;
            break;
        }
        if (done) {
            task->setState(task, TASK_KILL);
        }
        if (task->sprites[0].frame != 0 && func_800A5EAC(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5DBC, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A5EAC(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A5DBC, task, task->y + 0x12, 1);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A6190(s32 id) {
    StageEffect *task = createTaskWithId(func_800A5F70, sizeof(StageEffect), 0, id);

    task->x = 0x26C;
    task->y = 0xFC;
    SOUND.playSound(0x4001D);
    task->frame = 0x14;
    return task;
}

s32 func_800A61FC(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A61FC(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Draws sprite IDX of the effect (a draw callback) */
void func_800A631C(StageEffect *task, void *arg, s32 idx) {
    SpriteDrawer drawer;
    Layer *layer = arg;
    StageSprite *sprite = &task->sprites[idx];
    s32 y = task->y;
    s32 x = task->x;
    s32 depth;

    if (idx == 1) {
        y -= 0x20;
        depth = 4;
    } else {
        depth = 6;
    }
    initSpriteDrawer(&drawer);
    drawer.setTexture(0x140, 0x100);
    drawer.setLayer(layer, depth);
    drawer.setClutRow(sprite->clutRow);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), sprite->frame, x, y);
}

s32 func_800A6404(s32 x, s32 y, s32 w, s32 h) {
    RECT rect;
    struct Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getViewRect(layer, &rect);
    if (x + w < rect.x) {
        return 0;
    }
    if (rect.x + rect.w < x) {
        return 0;
    }
    if (y + h < rect.y) {
        return 0;
    }
    return rect.y + rect.h >= y;
}

/* An effect that plays its animation each time it is set to TASK_DONE */
void func_800A64C8(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A7460[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A7448[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A61FC(&task->clutAnim, D_800A7448, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A6404(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A631C, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A7460[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A7448[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A61FC(&task->clutAnim, D_800A7448, 0, 0);
        done = 0;
        frame = func_800A61FC(&task->anim, D_800A7460, 1, 0);
        switch (frame) {
        case 0xFF:
            task->sprites[1].frame = 0;
            done = 1;
            break;
        case 0x12C:
            task->sprites[1].frame = 0;
            break;
        default:
            task->sprites[1].frame = task->frame + frame;
            break;
        }
        if (done) {
            task->setState(task, TASK_RUN);
        }
        if (task->sprites[0].frame != 0 && func_800A6404(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A631C, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A6404(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A631C, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A6758(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTask(func_800A64C8, sizeof(StageEffect), 0);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

/* Sets flags 0xC13, 0x7401 and 0x404E */
void func_800A67B0(void) {
    FLAGS_00.applyAction(0xC13, 1);
    FLAGS_00.applyAction(0x7401, 1);
    FLAGS_00.applyAction(0x404E, 1);
}

void func_800A6810(void) {
    FLAGS_00.applyAction(0x404F, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A685C(void) {
    FLAGS_00.applyAction(0x4050, 1);
}

void func_800A6888(void) {
    GAME_PROGRESS = 39;
}

#if VERSION_US
void func_800A6898(void) {
    D_800990B4.unk44 = 0xF0;
    D_800990B4.unk8 = 0x333;
    D_800990B4.unkC = 0x3340000;
    D_800990B4.unk10 = D_800A7988;
    D_800990B4.unk14 = D_800A7B70;
    D_800990B4.unk1C = 0x332;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13E00;
    D_800990B4.unk30 = 0x19800;
    D_800990B4.unk28 = D_800A76E4;
    D_800990B4.unk3C = 0x2A;
    D_800990B4.unk40 = 0x60A80000;
    D_800990B4.unk4C = D_800A7954;
    D_800990B4.events = D_800A7BA4;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A76C8;
    D_8009A70C.setFile(0, 0x3340001);
    D_8009A70C.setFile(7, 0x3340002);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag310", func_800A6898);
#endif

void func_800A67B0();
extern s32 D_800A74B8[];
extern s32 D_800A74C4[];
extern s32 D_800A74D0[];
extern s32 D_800A74DC[];
extern s32 D_800A74E8[];
extern s32 D_800A74F4[];
extern s32 D_800A7500[];
extern s32 D_800A750C[];
extern s32 D_800A753C[];
extern s32 D_800A7548[];
extern s32 D_800A7554[];
extern s32 D_800A7560[];
extern s32 D_800A756C[];
extern s32 D_800A7578[];
extern s32 D_800A7584[];
extern s32 D_800A7590[];
extern s32 D_800A75C0[];
extern s32 D_800A75CC[];
extern s32 D_800A75D8[];
extern s32 D_800A75E4[];
extern s32 D_800A75F0[];
extern s32 D_800A75FC[];
extern s32 D_800A7608[];
extern s32 D_800A7614[];
extern s32 D_800A7644[];
extern s32 D_800A7650[];
extern s32 D_800A765C[];
extern s32 D_800A7668[];
extern s32 D_800A7674[];
extern s32 D_800A7680[];
extern s32 D_800A768C[];
extern s32 D_800A7698[];
extern s32 D_800A7518[];
extern s32 D_800A759C[];
extern s32 D_800A7620[];
extern s32 D_800A76A4[];
extern s32 D_800A77F4[];
extern s32 D_800A77FC[];
extern s32 D_800A7804[];
extern s32 D_800A780C[];
extern s32 D_800A7814[];
extern s32 D_800A781C[];
extern s32 D_800A7828[];
extern s32 D_800A7834[];
extern s32 D_800A7840[];
extern s32 D_800A784C[];
extern s32 D_800A7854[];
extern s32 D_800A785C[];
extern s32 D_800A7864[];
extern s32 D_800A7878[];
extern s32 D_800A788C[];
extern s32 D_800A78A0[];
extern s32 D_800A78B4[];
extern s32 D_800A78C8[];
extern s32 D_800A78DC[];
extern s32 D_800A78F0[];
extern s32 D_800A7904[];
extern s32 D_800A7918[];
extern s32 D_800A792C[];
extern s32 D_800A7940[];
extern s32 D_800A6994[];
extern s32 D_800A6B2C[];
extern s32 D_800A6CD0[];
extern s32 D_800A6EF8[];

s32 D_800A6994[] = {
    0x20100, 0x20C0058, 0x20101, 0x50001,
    0x6C0100, 0xEB023B, 0x6C0101, 0x10001,
    0x6D0100, 0x1B900A1, 0x6D0101, 0x10001,
    0x6E0100, 0x1E900FF, 0x6E0101, 0x10001,
    0x770100, 0x1C400EB, 0x770101, 0x10001,
    0x1100100, 0x1090280, 0x1100101, 0x10001,
    0x1E0300, 0x20102, 0x1FC0078, 0x3020005,
    0x1010002, 0x10002, 0x3000005, 0x200001E,
    0x10000, 2, 0x3000301, 0x101001E,
    0x3250323, 0x3000002, 0x101003C, 0x3260323,
    0x3000002, 0x200001E, 0x20000, 2,
    0x3000301, 0x600001E, 0x6C0000, 0x780300,
    0x1E0300, 1536, 0x3000002, 0x2000078,
    0x30000, 0x20002, 0x3000301, 0x102001E,
    0xB00002, 0x501E0, 0x20302, 0x20101,
    0x50001, 0x3230101, 0x6D0325, 0x3240101,
    0x6E0325, 0x3250101, 0x770325, 0x3C0300,
    0x3230101, 0x6D0326, 0x3240101, 0x6E0326,
    0x3250101, 0x770326, 0x1E0300, 0x6D0102,
    0x1C400B8, 0x1020000, 0xE7006E, 0x201DC,
    0x770102, 0x1D000D0, 0x3020001, 0x2000077,
    0x40000, 0x2006D, 0x6D0101, 1,
    0x6E0101, 0x20001, 0x770101, 0x10001,
    0x3000301, 0x200001E, 0x50000, 0x3006E,
    0x3000301, 0x200001E, 0x60000, 0x20077,
    0x3000301, 30,
};
s32 D_800A6B2C[] = {
    0x20100, 0x1E000B0, 0x20101, 0x50001,
    0x6C0100, 0xEB023B, 0x6C0101, 0x10001,
    0x1100100, 0x1090280, 0x1100101, 0x10001,
    0x780300, 512, 0x2000A, 0x3010000,
    0x1E0300, 0x20102, 0x1800170, 0x3020005,
    0x1020002, 0x1B00002, 0x50130, 0x6C0101,
    0x50001, 0x20302, 0x20101, 0x50001,
    0x3230101, 0x20325, 0x32D0101, 0x20369,
    0x3C0300, 0x3230101, 0x20326, 0x1E0300,
    1536, 0x300006C, 0x200003C, 0x10000,
    0x40002, 0x3000301, 0x200001E, 0x20000,
    0x1006C, 0x3000301, 0x200001E, 0x30000,
    0x40002, 0x3000301, 0x200001E, 0x40000,
    0x1006C, 0x3000301, 0x200001E, 0x50000,
    0x40002, 0x3000301, 0x101001E, 0x3350354,
    0x3000002, 0x100003C, 272, 0x1010000,
    0x10110, 0x3000000, 0x300001E, 0x600001E,
    0x20000, 0x20102, 0x102020C, 0x3020005,
    0x1010002, 0x10002, 0x3000005, 0x200001E,
    0x60000, 0x10002, 0x1010301, 0x3250323,
    0x300006C, 0x101003C, 0x3260323, 0x3000002,
    0x101001E, 0x359033F, 0x3000002, 0x1010012,
    0x3590340, 0x3000002, 0x2000048, 0x70000,
    108, 0x6C0101, 0x10001, 0x3000301,
    0x200001E, 0x80000, 0x10002, 0x3000301,
    0x200001E, 0x90000, 108, 0x3000301,
    30,
};
s32 D_800A6CD0[] = {
    0x10601, 0x108020C, 0x20100, 0x102020C,
    0x20101, 0x50001, 0x650100, 0x1900150,
    0x650101, 0x50001, 0x6C0100, 0xEB023B,
    0x6C0101, 0x10001, 0x780300, 512,
    0x6C0001, 0x3010000, 0x1E0300, 0xC0100,
    0x1900150, 0xC0101, 0x50001, 0x650102,
    0x1800170, 0x3020005, 0x1020065, 0x170000C,
    0x50180, 0x650102, 0x16A0182, 0x1000005,
    0x1500067, 0x1010190, 0x10067, 0x3020005,
    0x1020065, 0x19E000C, 0x50146, 0x650102,
    0x13001B0, 0x3020005, 0x1020065, 0x1B0000C,
    0x50130, 0x650102, 0x12001D0, 0x3020005,
    0x102000C, 0x1D0000C, 0x50120, 0x650102,
    0x11001F0, 0x3020005, 0x1020065, 0x1F0000C,
    0x50110, 0x650102, 0x1180200, 0x3020005,
    0x102000C, 0x1E0000C, 0x50108, 0x650101,
    0x50001, 0xC0302, 512, 0x650002,
    0x1010001, 0x1000C, 0x1010005, 0x10065,
    0x3010004, 0x3230101, 0x20325, 0x3C0300,
    0x20101, 0x10001, 0x3230101, 0x20326,
    0x1E0300, 512, 0xC0003, 0x1010002,
    0x1000C, 0x3010006, 0x1E0300, 0x670102,
    0x1800170, 0x3020005, 0x1020067, 0x1B00067,
    0x50130, 0x670302, 0xC0101, 0x10001,
    0x650101, 0x10001, 0x670102, 0x12001D0,
    0x3020005, 0x2000067, 0x40000, 0x30067,
    0x1010301, 0x3250323, 0x3000002, 0x101003C,
    0x3260323, 0x3000002, 0x200001E, 0x50000,
    0x20002, 0x3000301, 0x200001E, 0x60000,
    0x30067, 0x3000301, 0x200001E, 0x70000,
    0x30065, 0x650101, 0x40001, 0x3000301,
    0x200001E, 0x80000, 0x30065, 0x20101,
    0x50001, 0xC0101, 0x50001, 0x650101,
    0x50001, 0x3000301, 0x304001E, 0x640218,
    100, 0,
};
s32 D_800A6EF8[] = {
    0x1E0300, 0x10102, 0x1A50128, 0x3020005,
    0x1010001, 0x10001, 0x3000005, 0x200001E,
    0x10000, 1, 0x10101, 0x50007,
    0x1010301, 0x10001, 0x3000005, 0x101001E,
    0x10001, 0x3000001, 0x101001E, 0x3A0001,
    0x3000001, 0x1010078, 0x10001, 0x3000001,
    0x100001E, 0x400110, 0x1010218, 0x10110,
    0x1000005, 0x280111, 0x1010224, 0x10111,
    0x1000005, 0x10112, 0x1010238, 0x10112,
    0x1010005, 0x3250323, 0x3000001, 0x601001E,
    0x600001, 0x3000208, 0x102005A, 0x100112,
    0x50230, 0x3230101, 0x10326, 0x1120302,
    0x1100101, 0x40001, 0x1110101, 0x60001,
    0x1120101, 0x40001, 0x1E0300, 0x1100101,
    0x50001, 0x1110101, 0x50001, 0x1120101,
    0x50001, 0x1E0300, 0x1100101, 0x60001,
    0x1110101, 0x40001, 0x1120101, 0x60001,
    0x1E0300, 0x1100101, 0x50001, 0x1110101,
    0x50001, 0x1120101, 0x50001, 0x1E0300,
    0x3230101, 0x1100325, 0x3240101, 0x1110325,
    0x3250101, 0x1120325, 0x5A0300, 0x3230101,
    0x1100326, 0x3240101, 0x1110326, 0x3250101,
    0x1120326, 0x1E0300, 0x1100101, 0x10001,
    0x1110101, 0x10001, 0x1120101, 0x10001,
    0x120300, 0x1120102, 0x2380001, 0x3020001,
    0x1020112, 0x10111, 0x10238, 0x1120100,
    0, 0x1120101, 0x10001, 0x1110302,
    0x1100102, 0x2380001, 0x1000001, 273,
    0x1010000, 0x10111, 0x3020001, 0x6000110,
    0x10001, 0x1100100, 0, 0x1100101,
    0x10001, 0x5A0300, 512, 0x10003,
    0x1010000, 0x70001, 0x3010001, 0x10101,
    0x10001, 0x1E0300, 0x10102, 0x2000070,
    0x3000001, 0x304001E, 0x1780218, 0x100FC,
    0,
};
AnimFrame D_800A711C[] = {
    { 51, 8 }, { 52, 8 }, { 53, 8 }, { 54, 8 },
    { 55, 8 }, { 56, 8 }, { 57, 8 }, { 75, 40 },
    { 255, 0 },
};
AnimFrame D_800A7140[] = {
    { 58, 8 }, { 59, 8 }, { 60, 8 }, { 61, 8 },
    { 62, 8 }, { 63, 8 }, { 75, 40 }, { 255, 0 },
};
AnimFrame D_800A7160[] = {
    { 64, 8 }, { 65, 8 }, { 66, 8 }, { 67, 8 },
    { 68, 8 }, { 75, 40 }, { 255, 0 },
};
AnimFrame D_800A717C[] = {
    { 69, 8 }, { 70, 8 }, { 71, 8 }, { 72, 8 },
    { 73, 8 }, { 74, 8 }, { 75, 40 }, { 255, 0 },
};
AnimFrame D_800A719C[] = {
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 8, 4 },
    { 9, 4 }, { 10, 4 }, { 11, 4 }, { 12, 4 },
    { 13, 4 }, { 14, 4 }, { 15, 4 }, { 16, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A71D0[] = {
    { 28, 4 }, { 29, 4 }, { 30, 4 }, { 31, 4 },
    { 32, 4 }, { 33, 4 }, { 34, 4 }, { 35, 4 },
    { 36, 4 }, { 37, 4 }, { 38, 4 }, { 39, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A7204[] = {
    { 0, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A7210[] = {
    { 0, 12 }, { 1, 12 }, { 2, 12 }, { 3, 12 },
    { 4, 12 }, { 5, 12 }, { 6, 12 }, { 7, 12 },
    { 8, 12 }, { 9, 12 }, { 10, 12 }, { 11, 12 },
    { 12, 12 }, { 13, 12 }, { 255, 0 }, { 16, 4 },
    { 15, 4 }, { 14, 4 }, { 13, 4 }, { 12, 4 },
    { 11, 4 }, { 10, 4 }, { 9, 4 }, { 8, 4 },
    { 7, 4 }, { 6, 4 }, { 5, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A7280[] = {
    { 39, 4 }, { 38, 4 }, { 37, 4 }, { 36, 4 },
    { 35, 4 }, { 34, 4 }, { 33, 4 }, { 32, 4 },
    { 31, 4 }, { 30, 4 }, { 29, 4 }, { 28, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A72B4[] = {
    { 76, 4 }, { 77, 4 }, { 78, 4 }, { 79, 4 },
    { 80, 4 }, { 81, 4 }, { 82, 4 }, { 83, 4 },
    { 84, 4 }, { 85, 4 }, { 86, 4 }, { 87, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A72E8[] = {
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 91, 4 },
    { 92, 4 }, { 93, 4 }, { 94, 4 }, { 95, 4 },
    { 96, 4 }, { 97, 4 }, { 98, 4 }, { 99, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A731C[] = {
    { 0, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A7328[] = {
    { 0, 12 }, { 1, 12 }, { 2, 12 }, { 3, 12 },
    { 4, 12 }, { 5, 12 }, { 6, 12 }, { 7, 12 },
    { 8, 12 }, { 9, 12 }, { 10, 12 }, { 255, 0 },
    { 87, 4 }, { 86, 4 }, { 85, 4 }, { 84, 4 },
    { 83, 4 }, { 82, 4 }, { 81, 4 }, { 80, 4 },
    { 79, 4 }, { 78, 4 }, { 77, 4 }, { 76, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A738C[] = {
    { 99, 4 }, { 98, 4 }, { 97, 4 }, { 96, 4 },
    { 95, 4 }, { 94, 4 }, { 93, 4 }, { 92, 4 },
    { 91, 4 }, { 90, 4 }, { 89, 4 }, { 88, 4 },
    { 255, 0x3E7 },
};
StageEffectSpot D_800A73C0[] = {
    { 20, 0, 492, 188 },
    { 20, 0, 620, 252 },
};
AnimFrame D_800A73D8[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A73F0[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A7448[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A7460[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A74B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A74D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A74E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A74F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A7500[] = {
    0, 0, 0x60040000,
};
s32 D_800A750C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7518[] = {
    0, (s32)D_800A74B8, (s32)D_800A74C4, (s32)D_800A74D0,
    (s32)D_800A74DC, (s32)D_800A74E8, (s32)D_800A74F4, (s32)D_800A7500,
    (s32)D_800A750C,
};
s32 D_800A753C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7548[] = {
    0, 0, 0x60040000,
};
s32 D_800A7554[] = {
    0, 0, 0x60040000,
};
s32 D_800A7560[] = {
    0, 0, 0x60040000,
};
s32 D_800A756C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7578[] = {
    0, 0, 0x60040000,
};
s32 D_800A7584[] = {
    0, 0, 0x60040000,
};
s32 D_800A7590[] = {
    0, 0, 0x60040000,
};
s32 D_800A759C[] = {
    0, (s32)D_800A753C, (s32)D_800A7548, (s32)D_800A7554,
    (s32)D_800A7560, (s32)D_800A756C, (s32)D_800A7578, (s32)D_800A7584,
    (s32)D_800A7590,
};
s32 D_800A75C0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75CC[] = {
    0, 0, 0x60040000,
};
s32 D_800A75D8[] = {
    0, 0, 0x60040000,
};
s32 D_800A75E4[] = {
    0, 0, 0x60040000,
};
s32 D_800A75F0[] = {
    0, 0, 0x60040000,
};
s32 D_800A75FC[] = {
    0, 0, 0x60040000,
};
s32 D_800A7608[] = {
    0, 0, 0x60040000,
};
s32 D_800A7614[] = {
    0, 0, 0x60040000,
};
s32 D_800A7620[] = {
    0, (s32)D_800A75C0, (s32)D_800A75CC, (s32)D_800A75D8,
    (s32)D_800A75E4, (s32)D_800A75F0, (s32)D_800A75FC, (s32)D_800A7608,
    (s32)D_800A7614,
};
s32 D_800A7644[] = {
    10, 18, 0x608C0000,
};
s32 D_800A7650[] = {
    191, 18, 0x60080000,
};
s32 D_800A765C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7668[] = {
    0, 0, 0x60040000,
};
s32 D_800A7674[] = {
    0, 0, 0x60040000,
};
s32 D_800A7680[] = {
    0, 0, 0x60040000,
};
s32 D_800A768C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7698[] = {
    0, 0, 0x60040000,
};
s32 D_800A76A4[] = {
    0, (s32)D_800A7644, (s32)D_800A7650, (s32)D_800A765C,
    (s32)D_800A7668, (s32)D_800A7674, (s32)D_800A7680, (s32)D_800A768C,
    (s32)D_800A7698,
};
s32 D_800A76C8[] = {
    137, 0, 0, (s32)D_800A7518,
    (s32)D_800A759C, (s32)D_800A7620, (s32)D_800A76A4,
};
u8 D_800A76E4[] = {
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
    0xC0, 0x01, 0x00, 0x01, 0xF6, 0x01, 0x00, 0x01,
    0xD8, 0x02, 0x00, 0x00, 0x60, 0x01, 0xF0, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xF6, 0x01, 0x20, 0x01,
    0xD8, 0x02, 0x20, 0x00, 0x40, 0x01, 0xEF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x00, 0x01,
    0xD8, 0x00, 0x00, 0x00, 0x50, 0x01, 0xEF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x28, 0x01,
    0xD8, 0x00, 0x28, 0x00, 0x60, 0x01, 0xEF, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xF6, 0x01, 0x40, 0x01,
    0xD8, 0x02, 0x40, 0x00, 0x70, 0x01, 0xEF, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x50, 0x01,
    0xD8, 0x00, 0x50, 0x00, 0x40, 0x01, 0xEE, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x78, 0x01,
    0xD8, 0x00, 0x78, 0x00, 0x50, 0x01, 0xEE, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0xA0, 0x01,
    0xD8, 0x00, 0xA0, 0x00, 0x70, 0x01, 0xEE, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xE2, 0x01, 0x78, 0x01,
    0x88, 0x02, 0x78, 0x00, 0x40, 0x01, 0xED, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xEA, 0x01, 0x78, 0x01,
    0xA8, 0x02, 0x78, 0x00, 0x50, 0x01, 0xED, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xCA, 0x01, 0x80, 0x01,
    0x28, 0x02, 0x80, 0x00, 0x60, 0x01, 0xED, 0x01,
};
s32 D_800A77F4[] = {
    0x16026, 65535,
};
s32 D_800A77FC[] = {
    0x16017, 65535,
};
s32 D_800A7804[] = {
    0x16017, 65535,
};
s32 D_800A780C[] = {
    0x16017, 65535,
};
s32 D_800A7814[] = {
    0x16017, 65535,
};
s32 D_800A781C[] = {
    16462, 0x16017, 65535,
};
s32 D_800A7828[] = {
    16462, 0x16017, 65535,
};
s32 D_800A7834[] = {
    16462, 0x16017, 65535,
};
s32 D_800A7840[] = {
    16463, 0x16017, 65535,
};
s32 D_800A784C[] = {
    0x16026, 65535,
};
s32 D_800A7854[] = {
    0x16026, 65535,
};
s32 D_800A785C[] = {
    0x16026, 65535,
};
s32 D_800A7864[] = {
    (s32)D_800A77F4, 0, 0x40001, 0,
    1,
};
s32 D_800A7878[] = {
    (s32)D_800A77FC, 0, 0x5000C, 0,
    1,
};
s32 D_800A788C[] = {
    (s32)D_800A7804, 0, 0x60065, 0,
    1,
};
s32 D_800A78A0[] = {
    (s32)D_800A780C, 0, 0x70067, 0,
    1,
};
s32 D_800A78B4[] = {
    (s32)D_800A7814, 0, 0x8006C, 0xEB023B,
    1,
};
s32 D_800A78C8[] = {
    (s32)D_800A781C, 0, 0x9006D, 0x1B900A1,
    1,
};
s32 D_800A78DC[] = {
    (s32)D_800A7828, 0, 0xA006E, 0x1E900FF,
    1,
};
s32 D_800A78F0[] = {
    (s32)D_800A7834, 0, 0xB0077, 0x1C400EB,
    1,
};
s32 D_800A7904[] = {
    (s32)D_800A7840, 0, 0xC0110, 0x1090280,
    1,
};
s32 D_800A7918[] = {
    (s32)D_800A784C, 0, 0xC0110, 0,
    1,
};
s32 D_800A792C[] = {
    (s32)D_800A7854, 0, 0xD0111, 0,
    1,
};
s32 D_800A7940[] = {
    (s32)D_800A785C, 0, 0xE0112, 0,
    1,
};
s32 D_800A7954[] = {
    (s32)D_800A7864, (s32)D_800A7878, (s32)D_800A788C, (s32)D_800A78A0,
    (s32)D_800A78B4, (s32)D_800A78C8, (s32)D_800A78DC, (s32)D_800A78F0,
    (s32)D_800A7904, (s32)D_800A7918, (s32)D_800A792C, (s32)D_800A7940,
    0,
};
u8 D_800A7988[] = {
    0x01, 0x01, 0x40, 0x02, 0x33, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x48, 0x02, 0x7D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x40, 0x02, 0x3A, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x50, 0x02, 0x90, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x40, 0x02,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x02,
    0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04,
    0x40, 0x02, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x62, 0x02, 0xA7, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0xA0, 0x00, 0xFD, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0x88, 0x01, 0xC9, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0xC0, 0x01,
    0x53, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x21, 0x02, 0x33, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x06, 0x80, 0x02, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x26, 0x02, 0x74, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0C, 0xFF, 0x02, 0x58, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xAE, 0x01, 0x67, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x02,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x02,
    0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09,
    0x80, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x26, 0x02, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0x80, 0x02, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x26, 0x02, 0x74, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x05, 0x80, 0x02, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x26, 0x02, 0x74, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x02,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x02,
    0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E,
    0xFF, 0x02, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAE, 0x01, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0xFF, 0x02, 0x12, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xAE, 0x01, 0x67, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0xFF, 0x02, 0x13, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xAE, 0x01, 0x67, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xFF, 0x02,
    0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x01,
    0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D,
    0xFF, 0x02, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAA, 0x01, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x48, 0x00, 0xD0, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0xB2, 0x00, 0x5E, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0x2F, 0x01,
    0x0B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x71, 0x01, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x88, 0x01, 0x48, 0x01, 0x82, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x02, 0xF3, 0x00,
    0x0A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A7B70[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x18, 0x02, 0x78, 0x01, 0xFC, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A7BA0[])(void) = {
    func_800A6898,
};
s32 D_800A7BA4[] = {
    680, (s32)D_800A6994,
#if VERSION_US
    0x120000A,
#elif VERSION_EU
    0x127000A,
#endif
    0, (s32)func_800A67B0, 681, (s32)D_800A6B2C,
#if VERSION_US
    0x120000B,
#elif VERSION_EU
    0x127000B,
#endif
    0, (s32)func_800A6810, 682, (s32)D_800A6CD0,
#if VERSION_US
    0x120000C,
#elif VERSION_EU
    0x127000C,
#endif
    0, (s32)func_800A685C, 961, (s32)D_800A6EF8,
#if VERSION_US
    0x1200014,
#elif VERSION_EU
    0x1270014,
#endif
    0, (s32)func_800A6888, -1, 0,
    0, 0, 0,
};
