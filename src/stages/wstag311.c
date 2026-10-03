#include "common.h"
#include "stage.h"
extern s32 D_800A79D8[];
extern s32 D_800A7554[];
extern s32 D_800A776C[];
extern u8 D_800A7570[];
extern u8 D_800A798C[];
extern u8 D_800A7794[];
void func_800A5644();
void func_800A5094();
void func_800A4DF8();
extern void (*D_800A79D4[])(void);
void func_800A5AD4();
void func_800A6464();
extern AnimFrame D_800A72EC[];
extern AnimFrame D_800A72D4[];
extern AnimFrame D_800A700C[];
extern AnimFrame D_800A7030[];
extern AnimFrame D_800A7050[];
extern AnimFrame D_800A706C[];
extern StageEffectSpot D_800A72B0[];
StageEffect *func_800A624C(s32 x, s32 y, s32 frame);
extern AnimFrame D_800A708C[];
extern AnimFrame D_800A70C0[];
extern AnimFrame D_800A7100[];
extern AnimFrame D_800A7170[];
extern AnimFrame D_800A70F4[];
extern AnimFrame D_800A71A4[];
extern AnimFrame D_800A71D8[];
extern AnimFrame D_800A720C[];
extern AnimFrame D_800A7218[];
extern AnimFrame D_800A727C[];

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

void func_800A4DF8(StageTileAnims *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->anims[0].index = 0;
        task->anims[0].timer = D_800A700C[0].duration;
        task->anims[1].index = 0;
        task->anims[1].timer = D_800A7030[0].duration;
        task->anims[2].index = 0;
        task->anims[2].timer = D_800A7050[0].duration;
        task->anims[3].index = 0;
        task->anims[3].timer = D_800A706C[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (tile = D_800990B4.unk10; tile->unk2 != 0; tile++) {
            switch (tile->anim) {
            case 1:
                tile->frame = func_800A4D04(&task->anims[0], D_800A700C, 0);
                break;
            case 2:
                tile->frame = func_800A4D04(&task->anims[1], D_800A7030, 0);
                break;
            case 3:
                tile->frame = func_800A4D04(&task->anims[2], D_800A7050, 0);
                break;
            case 4:
                tile->frame = func_800A4D04(&task->anims[3], D_800A706C, 0);
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

/* Animates the records with animations 5 to 10 by mode (0: hidden, 1 and 3: the first two once, then mode 2 or 0; 2: the other four) */
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
                    task->tiles[0].anim.timer = D_800A708C[0].duration;
                    break;
                case 6:
                    task->tiles[1].tile = rec;
                    task->tiles[1].anim.index = 0;
                    task->tiles[1].anim.timer = D_800A70C0[0].duration;
                    break;
                case 7:
                    task->tiles[2].tile = rec;
                    task->tiles[2].anim.index = 0;
                    task->tiles[2].anim.timer = D_800A70F4[0].duration;
                    break;
                case 8:
                    task->tiles[3].tile = rec;
                    task->tiles[3].anim.index = 0;
                    task->tiles[3].anim.timer = D_800A7100[0].duration;
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
        task->mode = 0;
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
                    frame = func_800A4F74(&task->tiles[0], D_800A708C, 1, 0);
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
                    frame = func_800A4F74(&task->tiles[1], D_800A70C0, 1, 0);
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
                    tile->unk9 = func_800A4F74(&task->tiles[i], D_800A70F4, 0, 0);
                    tile->visible = 1;
                    break;
                case 3:
                    tile->frame = 2;
                    tile->unk9 = func_800A4F74(&task->tiles[i], D_800A7100, 0, 0);
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
                    frame = func_800A4F74(&task->tiles[0], D_800A7170, 1, 0);
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
                    frame = func_800A4F74(&task->tiles[1], D_800A7170, 1, 0);
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

/* Restarts the first two records' animations for mode 1 (id 0) or 3 (id 1) */
void func_800A5458(StageTileSix *task, s32 id) {
    if (task != NULL) {
        switch (id) {
        case 0:
            task->tiles[0].anim.index = 0;
            task->tiles[0].anim.timer = D_800A708C[0].duration;
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A70C0[0].duration;
            task->mode = 1;
            break;
        case 1:
            task->tiles[0].anim.index = 0;
            task->tiles[0].anim.timer = D_800A7100[15].duration; /* the animation after D_800A7100's */
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A7170[0].duration;
            task->mode = 3;
            break;
        }
    }
}

void *func_800A54C8(s32 arg) {
    return createTaskWithId(func_800A5094, 0x84, 0, arg);
}

void *func_800A54F8(void) {
    return createTask(func_800A5094, 0x84, 0);
}

s32 func_800A5524(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5524(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Animates the records with animations 11 to 16 by mode (0: hidden, 1 and 3: the first two once, then mode 2 or 0; 2: the other four) */
void func_800A5644(StageTileSix *task) {
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
                    task->tiles[0].anim.timer = D_800A71A4[0].duration;
                    break;
                case 12:
                    task->tiles[1].tile = rec;
                    task->tiles[1].anim.index = 0;
                    task->tiles[1].anim.timer = D_800A71D8[0].duration;
                    break;
                case 13:
                    task->tiles[2].tile = rec;
                    task->tiles[2].anim.index = 0;
                    task->tiles[2].anim.timer = D_800A720C[0].duration;
                    break;
                case 14:
                    task->tiles[3].tile = rec;
                    task->tiles[3].anim.index = 0;
                    task->tiles[3].anim.timer = D_800A7218[0].duration;
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
        task->mode = 0;
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
                    frame = func_800A5524(&task->tiles[0], D_800A71A4, 1, 0);
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
                    frame = func_800A5524(&task->tiles[1], D_800A71D8, 1, 0);
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
                    tile->unk9 = func_800A5524(&task->tiles[i], D_800A720C, 0, 0);
                    tile->visible = 1;
                    break;
                case 3:
                    tile->frame = 0x11;
                    tile->unk9 = func_800A5524(&task->tiles[i], D_800A7218, 0, 0);
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
                    frame = func_800A5524(&task->tiles[0], D_800A727C, 1, 0);
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
                    frame = func_800A5524(&task->tiles[1], D_800A727C, 1, 0);
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

/* Restarts the first two records' animations for mode 1 (id 0) or 3 (id 1) */
void func_800A5A08(StageTileSix *task, s32 id) {
    if (task != NULL) {
        switch (id) {
        case 0:
            task->tiles[0].anim.index = 0;
            task->tiles[0].anim.timer = D_800A71A4[0].duration;
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A71D8[0].duration;
            task->mode = 1;
            break;
        case 1:
            task->tiles[0].anim.index = 0;
            task->tiles[0].anim.timer = D_800A7218[12].duration; /* the animation after D_800A7218's */
            task->tiles[1].anim.index = 0;
            task->tiles[1].anim.timer = D_800A727C[0].duration;
            task->mode = 3;
            break;
        }
    }
}

void *func_800A5A78(s32 arg) {
    return createTaskWithId(func_800A5644, 0x84, 0, arg);
}

void *func_800A5AA8(void) {
    return createTask(func_800A5644, 0x84, 0);
}

/* Creates the stage helper task, the sprite effects and the event object of the story so far */
void func_800A5AD4(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4F48();
        for (i = 0; i < 3; i++) {
            if (D_800A72B0[i].kind == 0 || (D_800A72B0[i].kind == 2 && GAME.progress >= 0x28)) {
                children[3 + i] = func_800A624C(D_800A72B0[i].x, D_800A72B0[i].y, D_800A72B0[i].frame);
            }
        }
        switch (GAME_PROGRESS) {
        case 0x25:
            if (FLAGS_00.checkCondition(0x405E, 0)) {
                children[6] = func_80084B80(0x3A3);
            } else if (FLAGS_00.checkCondition(0x4067, 0)) {
                children[6] = func_80084B80(0x3A4);
            } else if (FLAGS_00.checkCondition(0x405F, 0)) {
                children[6] = func_80084B80(0x3A5);
            } else if (FLAGS_00.checkCondition(0x4060, 0)) {
                children[6] = func_80084B80(0x3A6);
            }
            break;
        case 0x27:
            children[6] = func_80084B80(FLAGS_00.checkCondition(0x406C, 0) ? 0x3D5 : 0x3D6);
            break;
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5C94(void *owner) {
    StageTask *task = createTask(func_800A5AD4, sizeof(StageTask), 0x1C);

    task->owner = owner;
    D_800A79D4[0]();
    return task;
}

s32 func_800A5CF0(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5CF0(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A5E10(StageEffect *task, void *arg, s32 idx) {
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

s32 func_800A5EF8(s32 x, s32 y, s32 w, s32 h) {
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

void func_800A5FBC(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A72EC[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A72D4[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5CF0(&task->clutAnim, D_800A72D4, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A5EF8(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5E10, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A72EC[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A72D4[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5CF0(&task->clutAnim, D_800A72D4, 0, 0);
        done = 0;
        frame = func_800A5CF0(&task->anim, D_800A72EC, 1, 0);
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
        if (task->sprites[0].frame != 0 && func_800A5EF8(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5E10, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A5EF8(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A5E10, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A624C(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A5FBC, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

/* Creates the effect of frame 0x2A at (0x10F, 0x19B), playing, with a sound */
StageEffect *func_800A62A8(s32 id) {
    StageEffect *task = createTaskWithId(func_800A5FBC, sizeof(StageEffect), 0, id);

    task->x = 0x10F;
    task->y = 0x19B;
    SOUND.playSound(0x4001D);
    task->frame = 0x2A;
    task->setState(task, TASK_DONE);
    return task;
}

/* Sets flags 0x405E, 0xC33 and 0x7401 */
void func_800A6324(void) {
    FLAGS_00.applyAction(0x405E, 1);
    FLAGS_00.applyAction(0xC33, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

void func_800A6384(void) {
    FLAGS_00.applyAction(0x4067, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A63D0(void) {
    FLAGS_00.applyAction(0x405F, 1);
}

void func_800A63FC(void) {
    FLAGS_00.applyAction(0x4060, 1);
}

void func_800A6428(void) {
    FLAGS_00.applyAction(0x406C, 1);
}

void func_800A6454(void) {
    GAME_PROGRESS = 40;
}

#if VERSION_US
void func_800A6464(void) {
    D_800990B4.unk44 = 0xE2;
    D_800990B4.unk8 = 0x52C;
    D_800990B4.unkC = 0x52D0000;
    D_800990B4.unk10 = D_800A7794;
    D_800990B4.unk14 = D_800A798C;
    D_800990B4.unk1C = 0x52B;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x13500;
    D_800990B4.unk30 = 0x19D00;
    D_800990B4.unk28 = D_800A7570;
    D_800990B4.unk3C = 0x2A;
    D_800990B4.unk40 = 0x60A80000;
    D_800990B4.unk4C = D_800A776C;
    D_800990B4.unk20 = D_800A7554;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A79D8;
    D_8009A70C.unk40(0, 0x52D0001);
    D_8009A70C.unk40(7, 0x52D0002);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag311", func_800A6464);
#endif

void func_800A6324();
extern s32 D_800A7344[];
extern s32 D_800A7350[];
extern s32 D_800A735C[];
extern s32 D_800A7368[];
extern s32 D_800A7374[];
extern s32 D_800A7380[];
extern s32 D_800A738C[];
extern s32 D_800A7398[];
extern s32 D_800A73C8[];
extern s32 D_800A73D4[];
extern s32 D_800A73E0[];
extern s32 D_800A73EC[];
extern s32 D_800A73F8[];
extern s32 D_800A7404[];
extern s32 D_800A7410[];
extern s32 D_800A741C[];
extern s32 D_800A744C[];
extern s32 D_800A7458[];
extern s32 D_800A7464[];
extern s32 D_800A7470[];
extern s32 D_800A747C[];
extern s32 D_800A7488[];
extern s32 D_800A7494[];
extern s32 D_800A74A0[];
extern s32 D_800A74D0[];
extern s32 D_800A74DC[];
extern s32 D_800A74E8[];
extern s32 D_800A74F4[];
extern s32 D_800A7500[];
extern s32 D_800A750C[];
extern s32 D_800A7518[];
extern s32 D_800A7524[];
extern s32 D_800A73A4[];
extern s32 D_800A7428[];
extern s32 D_800A74AC[];
extern s32 D_800A7530[];
extern s32 D_800A7660[];
extern s32 D_800A7668[];
extern s32 D_800A7670[];
extern s32 D_800A7678[];
extern s32 D_800A7680[];
extern s32 D_800A768C[];
extern s32 D_800A7698[];
extern s32 D_800A76A4[];
extern s32 D_800A76AC[];
extern s32 D_800A76B8[];
extern s32 D_800A76CC[];
extern s32 D_800A76E0[];
extern s32 D_800A76F4[];
extern s32 D_800A7708[];
extern s32 D_800A771C[];
extern s32 D_800A7730[];
extern s32 D_800A7744[];
extern s32 D_800A7758[];
extern s32 D_800A6560[];
extern s32 D_800A664C[];
extern s32 D_800A6790[];
extern s32 D_800A6C20[];
extern s32 D_800A6E44[];
extern s32 D_800A6F44[];

s32 D_800A6560[] = {
    0x20100, 0x20C0058, 0x20101, 0x50001,
    0x780300, 0x3230101, 0x20325, 0x5A0300,
    0x3230101, 0x20326, 0x1E0300, 0x20102,
    0x1D000D0, 0x3020005, 0x1010002, 0x10002,
    0x3000005, 0x101001E, 0x100D2, 0x1010007,
    0x100D3, 0x3000003, 0x300001E, 0x200001E,
    0x10000, 0x200D4, 0x3000301, 0x101001E,
    0x10002, 0x3000005, 0x101001E, 0x10002,
    0x3000003, 0x101001E, 0x10002, 0x3000005,
    0x101001E, 0x10002, 0x3000007, 0x101001E,
    0x10002, 0x3000005, 0x200001E, 0x20000,
    2, 0x20101, 0x50007, 0x1010301,
    0x10002, 0x3000005, 0x200001E, 0x30000,
    211, 0x3000301, 0x200001E, 0x40000,
    0x200D2, 0x3000301, 30,
};
s32 D_800A664C[] = {
    0x20100, 0x1D000D0, 0x20101, 0x50001,
    0x1020100, 0x12001D0, 0x1020101, 0x10001,
    0x780300, 512, 0x20008, 0x3010000,
    0x1E0300, 0x20102, 0x1900150, 0x3020005,
    0x1010002, 0x10002, 0x1010005, 0x3250323,
    0x1010002, 0x369032D, 0x3000002, 0x101003C,
    0x3260323, 0x3000002, 0x601001E, 0x1700000,
    0x2000160, 0x10000, 0x10102, 0x3000301,
    0x600001E, 0x20000, 0x1020102, 0x13001B0,
    0x3020001, 0x1020102, 0x1700102, 0x10180,
    0x1020302, 0x1020101, 0x10001, 0x1E0300,
    512, 0x20002, 0x1010001, 0x70002,
    0x3010005, 0x20101, 0x50001, 0x1E0300,
    512, 0x1020003, 0x3010002, 0x1E0300,
    512, 0x20004, 0x1010001, 0x70002,
    0x3010005, 0x20101, 0x50001, 0x1E0300,
    512, 0x1020005, 0x3010002, 0x1E0300,
    512, 0x20006, 0x1010001, 0x70002,
    0x3010005, 0x20101, 0x50001, 0x1E0300,
    512, 0x1020007, 0x3010002, 0x1E0300,
    0,
};
s32 D_800A6790[] = {
    0x10601, 0x1A00150, 0x20100, 0x1900150,
    0x20101, 0x50001, 0x1020100, 0x1800170,
    0x1020101, 0x10001, 0x780300, 512,
    0x1020001, 0x3010000, 0x1E0300, 0x3230101,
    0x20325, 0x3C0300, 0x3230101, 0x20326,
    0x1E0300, 512, 0x20002, 0x3010003,
    0x670100, 0x1E800A0, 0x670101, 0x50001,
    0x1E0300, 0xC0100, 0x1E800A0, 0xC0101,
    0x50001, 0x670102, 0x1D800C0, 0x3020005,
    0x1020067, 0xC0000C, 0x501D8, 0x650100,
    0x1E800A0, 0x650101, 0x50001, 0x670102,
    0x1C800E0, 0x3020005, 0x1010067, 0x1000C,
    0x1010005, 0x3250323, 0x3000067, 0x101003C,
    0x3260323, 0x3000067, 0x200001E, 0x30000,
    0x20067, 0x1010301, 0x3250323, 0x3000002,
    0x101003C, 0x3260323, 0x3000002, 0x200001E,
    0xF0000, 0x30002, 0x20101, 0x10007,
    0x1010301, 0x10002, 0x1020001, 0x110000C,
    0x501B0, 0x650102, 0x1C000F0, 0x1020005,
    0x1300067, 0x501A0, 0x670302, 0xC0102,
    0x1A00130, 0x1020005, 0x1100065, 0x501B0,
    0x670102, 0x1900110, 0x3020003, 0x1020067,
    0x150000C, 0x701B0, 0x650102, 0x1A00130,
    0x1010005, 0x10067, 0x3020005, 0x1010065,
    0x10002, 0x1010005, 0x1000C, 0x1010005,
    0x10065, 0x3000005, 0x200001E, 0x110000,
    0x10065, 0x3000301, 0x200001E, 0x40000,
    258, 0x20101, 0x50001, 0x3000301,
    0x200001E, 0x50000, 0x10065, 0x3000301,
    0x200001E, 0x60000, 258, 0x1010301,
    0x3250323, 0x1010002, 0x3250324, 0x1010065,
    0x3250325, 0x101000C, 0x3250326, 0x3000067,
    0x101003C, 0x3260323, 0x1010002, 0x3260324,
    0x1010065, 0x3260325, 0x101000C, 0x3260326,
    0x3000067, 0x200001E, 0x70000, 0x10065,
    0x20101, 0x10001, 0xC0101, 0x30001,
    0x670101, 0x70001, 0x3000301, 0x200001E,
    0x120001, 0x3000C, 512, 0x670009,
    0x1010000, 0x7000C, 0x3010003, 0x20102,
    0x1840130, 0x1010003, 0x1000C, 0x3020003,
    0x1010002, 0x10002, 0x1020007, 0x1500102,
    0x10190, 0x1020302, 0x1020101, 0x10001,
    0x1E0300, 0x20101, 0x10001, 0xC0101,
    0x10001, 0x650102, 0x21A0040, 0x1010001,
    0x10067, 0x1020001, 0x400102, 0x1021A,
    0x5A0300, 1536, 0x1010002, 0x3250323,
    0x3000067, 0x101003C, 0x10002, 0x1010000,
    0x3260323, 0x3000067, 0x200001E, 0xC0000,
    0x20067, 0x670101, 0x70001, 0x1000301,
    101, 0x1010000, 0x10065, 0x1000000,
    258, 0x1010000, 0x10102, 0x3000000,
    0x200001E, 0x80000, 0x2000C, 0xC0101,
    0x30001, 0x1020301, 0x1300067, 0x701A0,
    0x670302, 0xC0102, 0x1A00130, 0x1020003,
    0x1500067, 0x50190, 0xC0302, 0x20101,
    0x70001, 0xC0102, 0x1900150, 0x1020005,
    0x1700067, 0x50180, 0xC0302, 0x20102,
    0x1900150, 0x1020005, 0x170000C, 0x50180,
    0x670102, 0x13001B0, 0x3020005, 0x2000002,
    0xA0000, 0x10002, 0x20101, 0x50007,
    0x1010301, 0x10002, 0x3000005, 0x200001E,
    0xB0000, 12, 0xC0101, 0x10007,
    0x1010301, 0x1000C, 0x1010001, 0x10067,
    0x3000001, 0x600001E, 0xC0000, 512,
    0x670010, 0x3010001, 0x1E0300, 0x3230101,
    0x20325, 0x3240101, 0xC0325, 0x3C0300,
    0x3230101, 0x20326, 0x3240101, 0xC0326,
    0x1E0300, 512, 0xC000D, 0x1010000,
    0x1000C, 0x3010005, 1536, 0x3000002,
    0x102001E, 0x1B0000C, 0x50130, 0x670102,
    0xFC0218, 0x3020005, 0x200000C, 0xE0000,
    0x20002, 0xC0102, 0xFC021A, 0x3010005,
    0x1E0300,
#if VERSION_US
    0xE060304,
#elif VERSION_EU
    0xE070304,
#endif
    0x1900150, 5,
};
s32 D_800A6C20[] = {
    0x10601, 0x1880140, 0x20100, 0x1900150,
    0x20101, 0x50001, 0xC0100, 0x11401EE,
    0xC0101, 0x10001, 0x670100, 0x11401EE,
    0x670101, 0x10001, 0x780300, 0xC0102,
    0x13001B0, 0x1010001, 0x3250323, 0x3000002,
    0x101003C, 0x3260323, 0x3000002, 0x200001E,
    0x10000, 0x1000C, 0xC0101, 0x10007,
    0x1010301, 0x1000C, 0x3000001, 0x102001E,
    0x170000C, 0x10180, 0xC0302, 512,
    0xC0008, 0x1010000, 0x7000C, 0x3010001,
    0xC0101, 0x10001, 0x1E0300, 512,
    0x20002, 0x1010003, 0x70002, 0x3010005,
    0x20101, 0x50001, 0x670102, 0x13001B0,
    0x3020001, 0x1020067, 0x1400002, 0x50188,
    0xC0102, 0x1900150, 0x1020001, 0x1700067,
    0x10180, 0xC0302, 0xC0102, 0x1980160,
    0x3020005, 0x200000C, 0x30000, 103,
    0x3000301, 0x101001E, 0x10002, 0x1010007,
    0x1000C, 0x1020003, 0x1500067, 0x10190,
    0x670302, 0x20101, 0x10001, 0xC0101,
    0x10001, 0x670102, 0x2000070, 0x3000001,
    0x200005A, 0x40000, 0x1000C, 0x20101,
    0x70001, 0xC0101, 0x30007, 0x1010301,
    0x1000C, 0x3000003, 0x200001E, 0x50000,
    0x20002, 0x20101, 0x70007, 0x1010301,
    0x10002, 0x3000007, 0x200001E, 0x60000,
    0x1000C, 0xC0101, 0x30007, 0x1010301,
    0x1000C, 0x3000003, 0x200001E, 0x70000,
    0x20002, 0x20101, 0x70007, 0x1010301,
    0x10002, 0x3000007, 0x102001E, 0x1500002,
    0x10190, 0x20302, 0x20102, 0x1A00130,
    0x1020001, 0x150000C, 0x10190, 0x20302,
    0x20102, 0x1F80080, 0x1020001, 0x80000C,
    0x101F8, 0x3C0300, 0x2760304, 0x1CC0058,
    5,
};
s32 D_800A6E44[] = {
    0x10100, 0x20C0058, 0x10101, 0x50001,
    0x1E0300, 0x10102, 0x1C300EA, 0x3020005,
    0x1010001, 0x10001, 0x3000003, 0x101001E,
    0x10001, 0x3000005, 0x101001E, 0x3A0001,
    0x3000007, 0x200003C, 0x10000, 0x10001,
    0x10101, 0x70001, 0x3000301, 0x101001E,
    0x10001, 0x3000005, 0x101001E, 0x3250323,
    0x1010001, 0x3350346, 0x3000346, 0x101003C,
    0x3260323, 0x3000001, 0x200001E, 0x50000,
    0x30001, 0x10101, 0x50007, 0xD50100,
    0x1A70122, 0xD50101, 0x10001, 0x1010301,
    0x10001, 0x3000005, 0x300001E, 0x200003C,
    0x20000, 0x400D5, 0x2000301, 0x30000,
    0x10001, 0x10101, 0x5000C, 0x3000301,
    0x200001E, 0x40000, 0x400D5, 0x3000301,
    0x304001E,
#if VERSION_US
    0xEA0E07,
#elif VERSION_EU
    0xEA0E08,
#endif
    0x501C3, 0,
};
s32 D_800A6F44[] = {
    0x10100, 0x1C300EA, 0x10101, 0x50001,
    0xD50100, 0x1A70122, 0xD50101, 0x10001,
    0x780300, 512, 0xD50001, 0x3010004,
    0x1E0300, 512, 0x10002, 0x1010001,
    0xC0001, 0x3010005, 0x1E0300, 512,
    0xD50003, 0x3010004, 0x1E0300, 512,
    0x10004, 0x3010001, 0x1E0300, 512,
    0xD50005, 0x3010004, 0x1E0300, 0x3460101,
    0x10335, 0x3C0300, 0xD50100, 0,
    0xD50101, 0x10001, 0x3C0300, 0x3C0300,
    512, 0x10006, 0x3010001, 0x10101,
    0x50001, 0x1E0300, 0x1E0300, 0x2880304,
    0x1C300EA, 5,
};
AnimFrame D_800A700C[] = {
    { 51, 8 }, { 52, 8 }, { 53, 8 }, { 54, 8 },
    { 55, 8 }, { 56, 8 }, { 57, 8 }, { 75, 40 },
    { 255, 0 },
};
AnimFrame D_800A7030[] = {
    { 58, 8 }, { 59, 8 }, { 60, 8 }, { 61, 8 },
    { 62, 8 }, { 63, 8 }, { 75, 40 }, { 255, 0 },
};
AnimFrame D_800A7050[] = {
    { 64, 8 }, { 65, 8 }, { 66, 8 }, { 67, 8 },
    { 68, 8 }, { 75, 40 }, { 255, 0 },
};
AnimFrame D_800A706C[] = {
    { 69, 8 }, { 70, 8 }, { 71, 8 }, { 72, 8 },
    { 73, 8 }, { 74, 8 }, { 75, 40 }, { 255, 0 },
};
AnimFrame D_800A708C[] = {
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 8, 4 },
    { 9, 4 }, { 10, 4 }, { 11, 4 }, { 12, 4 },
    { 13, 4 }, { 14, 4 }, { 15, 4 }, { 16, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A70C0[] = {
    { 28, 4 }, { 29, 4 }, { 30, 4 }, { 31, 4 },
    { 32, 4 }, { 33, 4 }, { 34, 4 }, { 35, 4 },
    { 36, 4 }, { 37, 4 }, { 38, 4 }, { 39, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A70F4[] = {
    { 0, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A7100[] = {
    { 0, 12 }, { 1, 12 }, { 2, 12 }, { 3, 12 },
    { 4, 12 }, { 5, 12 }, { 6, 12 }, { 7, 12 },
    { 8, 12 }, { 9, 12 }, { 10, 12 }, { 11, 12 },
    { 12, 12 }, { 13, 12 }, { 255, 0 }, { 16, 4 },
    { 15, 4 }, { 14, 4 }, { 13, 4 }, { 12, 4 },
    { 11, 4 }, { 10, 4 }, { 9, 4 }, { 8, 4 },
    { 7, 4 }, { 6, 4 }, { 5, 4 }, { 255, 0x3E7 },
};
AnimFrame D_800A7170[] = {
    { 39, 4 }, { 38, 4 }, { 37, 4 }, { 36, 4 },
    { 35, 4 }, { 34, 4 }, { 33, 4 }, { 32, 4 },
    { 31, 4 }, { 30, 4 }, { 29, 4 }, { 28, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A71A4[] = {
    { 76, 4 }, { 77, 4 }, { 78, 4 }, { 79, 4 },
    { 80, 4 }, { 81, 4 }, { 82, 4 }, { 83, 4 },
    { 84, 4 }, { 85, 4 }, { 86, 4 }, { 87, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A71D8[] = {
    { 88, 4 }, { 89, 4 }, { 90, 4 }, { 91, 4 },
    { 92, 4 }, { 93, 4 }, { 94, 4 }, { 95, 4 },
    { 96, 4 }, { 97, 4 }, { 98, 4 }, { 99, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A720C[] = {
    { 0, 4 }, { 1, 4 }, { 255, 0 },
};
AnimFrame D_800A7218[] = {
    { 0, 12 }, { 1, 12 }, { 2, 12 }, { 3, 12 },
    { 4, 12 }, { 5, 12 }, { 6, 12 }, { 7, 12 },
    { 8, 12 }, { 9, 12 }, { 10, 12 }, { 255, 0 },
    { 87, 4 }, { 86, 4 }, { 85, 4 }, { 84, 4 },
    { 83, 4 }, { 82, 4 }, { 81, 4 }, { 80, 4 },
    { 79, 4 }, { 78, 4 }, { 77, 4 }, { 76, 4 },
    { 255, 0x3E7 },
};
AnimFrame D_800A727C[] = {
    { 99, 4 }, { 98, 4 }, { 97, 4 }, { 96, 4 },
    { 95, 4 }, { 94, 4 }, { 93, 4 }, { 92, 4 },
    { 91, 4 }, { 90, 4 }, { 89, 4 }, { 88, 4 },
    { 255, 0x3E7 },
};
StageEffectSpot D_800A72B0[] = {
    { 20, 0, 492, 188 },
    { 20, 0, 620, 252 },
    { 42, 2, 271, 411 },
};
AnimFrame D_800A72D4[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A72EC[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A7344[] = {
    0, 0, 0x60040000,
};
s32 D_800A7350[] = {
    0, 0, 0x60040000,
};
s32 D_800A735C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7368[] = {
    0, 0, 0x60040000,
};
s32 D_800A7374[] = {
    0, 0, 0x60040000,
};
s32 D_800A7380[] = {
    0, 0, 0x60040000,
};
s32 D_800A738C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7398[] = {
    0, 0, 0x60040000,
};
s32 D_800A73A4[] = {
    0, (s32)D_800A7344, (s32)D_800A7350, (s32)D_800A735C,
    (s32)D_800A7368, (s32)D_800A7374, (s32)D_800A7380, (s32)D_800A738C,
    (s32)D_800A7398,
};
s32 D_800A73C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A73D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A73E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A73EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A73F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A7404[] = {
    0, 0, 0x60040000,
};
s32 D_800A7410[] = {
    0, 0, 0x60040000,
};
s32 D_800A741C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7428[] = {
    0, (s32)D_800A73C8, (s32)D_800A73D4, (s32)D_800A73E0,
    (s32)D_800A73EC, (s32)D_800A73F8, (s32)D_800A7404, (s32)D_800A7410,
    (s32)D_800A741C,
};
s32 D_800A744C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7458[] = {
    0, 0, 0x60040000,
};
s32 D_800A7464[] = {
    0, 0, 0x60040000,
};
s32 D_800A7470[] = {
    0, 0, 0x60040000,
};
s32 D_800A747C[] = {
    0, 0, 0x60040000,
};
s32 D_800A7488[] = {
    0, 0, 0x60040000,
};
s32 D_800A7494[] = {
    0, 0, 0x60040000,
};
s32 D_800A74A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A74AC[] = {
    0, (s32)D_800A744C, (s32)D_800A7458, (s32)D_800A7464,
    (s32)D_800A7470, (s32)D_800A747C, (s32)D_800A7488, (s32)D_800A7494,
    (s32)D_800A74A0,
};
s32 D_800A74D0[] = {
    32, 18, 0x608C0000,
};
s32 D_800A74DC[] = {
    198, 18, 0x60080000,
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
    0, 0, 0x60040000,
};
s32 D_800A7524[] = {
    0, 0, 0x60040000,
};
s32 D_800A7530[] = {
    0, (s32)D_800A74D0, (s32)D_800A74DC, (s32)D_800A74E8,
    (s32)D_800A74F4, (s32)D_800A7500, (s32)D_800A750C, (s32)D_800A7518,
    (s32)D_800A7524,
};
s32 D_800A7554[] = {
    148, 0, 0, (s32)D_800A73A4,
    (s32)D_800A7428, (s32)D_800A74AC, (s32)D_800A7530,
};
u8 D_800A7570[] = {
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
    0xC0, 0x01, 0x00, 0x01, 0xD2, 0x01, 0xD8, 0x01,
    0x48, 0x02, 0xD8, 0x00, 0x60, 0x01, 0xEE, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xDA, 0x01, 0xD8, 0x01,
    0x68, 0x02, 0xD8, 0x00, 0x70, 0x01, 0xEE, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x00, 0x01,
    0xD8, 0x00, 0x00, 0x00, 0x40, 0x01, 0xED, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x76, 0x01, 0x28, 0x01,
    0xD8, 0x00, 0x28, 0x00, 0x50, 0x01, 0xED, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xDE, 0x01, 0xA8, 0x01,
    0x78, 0x02, 0xA8, 0x00, 0x60, 0x01, 0xED, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xE8, 0x01, 0xA8, 0x01,
    0xA0, 0x02, 0xA8, 0x00, 0x70, 0x01, 0xED, 0x01,
    0xC0, 0x01, 0x00, 0x01, 0xF2, 0x01, 0xA8, 0x01,
    0xC8, 0x02, 0xA8, 0x00, 0x40, 0x01, 0xEC, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x9C, 0x01, 0x98, 0x01,
    0x70, 0x01, 0x98, 0x00, 0x50, 0x01, 0xEC, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA6, 0x01, 0xD0, 0x01,
    0x98, 0x01, 0xD0, 0x00, 0x60, 0x01, 0xEC, 0x01,
};
s32 D_800A7660[] = {
    0x16027, 65535,
};
s32 D_800A7668[] = {
    0x16025, 65535,
};
s32 D_800A7670[] = {
    0x16025, 65535,
};
s32 D_800A7678[] = {
    0x16025, 65535,
};
s32 D_800A7680[] = {
    0x16025, 3123, 65535,
};
s32 D_800A768C[] = {
    0x16025, 3123, 65535,
};
s32 D_800A7698[] = {
    0x16025, 3123, 65535,
};
s32 D_800A76A4[] = {
    0x16027, 65535,
};
s32 D_800A76AC[] = {
    0x16025, 16479, 65535,
};
s32 D_800A76B8[] = {
    (s32)D_800A7660, 0, 0x40001, 0,
    1,
};
s32 D_800A76CC[] = {
    (s32)D_800A7668, 0, 0x5000C, 0,
    1,
};
s32 D_800A76E0[] = {
    (s32)D_800A7670, 0, 0x60065, 0,
    1,
};
s32 D_800A76F4[] = {
    (s32)D_800A7678, 0, 0x70067, 0,
    1,
};
s32 D_800A7708[] = {
    (s32)D_800A7680, 0, 0x800D2, 0x1B900A1,
    1,
};
s32 D_800A771C[] = {
    (s32)D_800A768C, 0, 0x900D3, 0x1E900FF,
    1,
};
s32 D_800A7730[] = {
    (s32)D_800A7698, 0, 0xA00D4, 0x1C400EB,
    1,
};
s32 D_800A7744[] = {
    (s32)D_800A76A4, 0, 0xB00D5, 0,
    1,
};
s32 D_800A7758[] = {
    (s32)D_800A76AC, 0, 0xC0102, 0x12001D0,
    1,
};
s32 D_800A776C[] = {
    (s32)D_800A76B8, (s32)D_800A76CC, (s32)D_800A76E0, (s32)D_800A76F4,
    (s32)D_800A7708, (s32)D_800A771C, (s32)D_800A7730, (s32)D_800A7744,
    (s32)D_800A7758, 0,
};
u8 D_800A7794[] = {
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
    0x00, 0x00, 0x40, 0x06, 0x2A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0x01, 0x9B, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0x48, 0x00, 0xD0, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0xB2, 0x00,
    0x5E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x2F, 0x01, 0x0B, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x71, 0x01, 0xDB, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x01, 0x48, 0x01,
    0x82, 0x01, 0x00, 0x00, 0x01, 0x00, 0x40, 0x04,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02,
    0xF3, 0x00, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_800A798C[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0x87, 0x02, 0x78, 0x01, 0xFC, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x60, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0E, 0x00, 0xDD, 0x02, 0xE0, 0x00, 0x18, 0x04,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A79D4[])(void) = {
    func_800A6464,
};
s32 D_800A79D8[] = {
    931, (s32)D_800A6560,
#if VERSION_US
    0x1200010,
#elif VERSION_EU
    0x1270010,
#endif
    0, (s32)func_800A6324, 932, (s32)D_800A664C,
#if VERSION_US
    0x1200011,
#elif VERSION_EU
    0x1270011,
#endif
    0, (s32)func_800A6384, 933, (s32)D_800A6790,
#if VERSION_US
    0x1200012,
#elif VERSION_EU
    0x1270012,
#endif
    0, (s32)func_800A63D0, 934, (s32)D_800A6C20,
#if VERSION_US
    0x1200013,
#elif VERSION_EU
    0x1270013,
#endif
    0, (s32)func_800A63FC, 981, (s32)D_800A6E44,
#if VERSION_US
    0x1200018,
#elif VERSION_EU
    0x1270018,
#endif
    0, (s32)func_800A6428, 982, (s32)D_800A6F44,
#if VERSION_US
    0x1200019,
#elif VERSION_EU
    0x1270019,
#endif
    0, (s32)func_800A6454, -1, 0,
    0, 0, 0,
};
