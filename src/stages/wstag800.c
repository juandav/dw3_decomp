#include "common.h"
#include "stage.h"
#if VERSION_US
#define TIMER_SHEET 0x6EE
#elif VERSION_EU
#define TIMER_SHEET 0x6FE
#endif
extern s32 D_800A6D48[];
extern s32 D_800A686C[];
extern s32 D_800A6AD0[];
extern u8 D_800A6888[];
extern u8 D_800A6C6C[];
extern u8 D_800A6AF0[];
void func_800A554C();
void func_800A5208();
void func_800A4DC4();
extern AnimFrame D_800A64C0[];
extern AnimFrame D_800A64CC[];
extern AnimFrame D_800A64F8[];
extern void (*D_800A6D44[])(void);
void func_800A5748();
void func_800A5F88();
extern AnimFrame D_800A6604[];
extern AnimFrame D_800A65EC[];
extern StageEffectSpot D_800A65BC[];
void *func_800A50B4(void);
StageEffect *func_800A5E48(s32 x, s32 y, s32 frame);
extern AnimFrame *D_800A65AC[];
extern s16 D_800A65B4[];
extern AnimFrame D_800A6514[];
extern AnimFrame D_800A6560[];

s32 func_800A4CA4(StageTileAnim *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        obj->anim.timer += (u8)frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += (u8)frame->duration;
        }
        func_800A4CA4(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Shows the first record animated while running; when done, both */
void func_800A4DC4(StageTilePair16 *task) {
    StageTile *tile;
    StageTile *rec;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 1) {
                task->anims[0].anim.index = 0;
                task->anims[0].anim.timer = (u8)D_800A64C0[0].duration;
                task->anims[0].tile = rec;
            }
            if (rec->anim == 2) {
                task->anims[1].anim.index = 0;
                task->anims[1].anim.timer = (u8)D_800A64F8[0].duration;
                task->anims[1].tile = rec;
            }
        }
        task->playing = 0;
        if (task->done == 0) {
            task->nextState(task);
        } else {
            task->anims[0].anim.index = 0;
            task->anims[0].anim.timer = (u8)D_800A64CC[0].duration;
            task->setState(task, TASK_DONE);
        }
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                tile->frame = 0x46;
                tile->unk9 = func_800A4CA4(&task->anims[0], D_800A64C0, 0, 0);
                break;
            case 1:
                tile->visible = 0;
                break;
            }
        }
        break;
    case TASK_DONE:
        for (i = 0; i < 2; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                if (task->playing) {
                    frame = func_800A4CA4(&task->anims[0], D_800A64CC, 1, 0);
                    if (frame == 0xFF) {
                        tile->frame = 0x50;
                        task->playing = 0;
                    } else {
                        tile->frame = frame;
                    }
                } else {
                    tile->frame = 0x50;
                }
                tile->unk9 = 0;
                break;
            case 1:
                tile->visible = 1;
                tile->frame = 0x51;
                tile->unk9 = func_800A4CA4(&task->anims[1], D_800A64F8, 0, 0);
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Plays the first record's one-shot animation when the event of map object 0x35B happens */
void func_800A5038(StageTilePair16 *task, s32 id) {
    if (id == 0x35B) {
        task->playing = 1;
        task->anims[0].anim.index = 0;
        task->anims[0].anim.timer = (u8)D_800A64CC[0].duration;
        task->setState(task, TASK_DONE);
    }
}

void *func_800A5084(s32 arg) {
    return createTaskWithId(func_800A4DC4, 0x64, 0, arg);
}

/* Creates the tile pair object, started in TASK_DONE */
void *func_800A50B4(void) {
    StageTilePair16 *task = createTask(func_800A4DC4, sizeof(StageTilePair16), 0);

    task->done = 1;
    return task;
}

/* func_800A4CA4 for a StageTileAnimFlag */
s32 func_800A50E8(StageTileAnimFlag *obj, AnimFrame *frames, s32 once, s32 depth) {
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
        obj->anim.timer += (u8)frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += (u8)frame->duration;
        }
        func_800A50E8(obj, frames, once, depth + 1);
    }
    return frame->frame;
}

/* Plays the records with animations 3 and 4 once, then ends */
void func_800A5208(StageTileOnce *task) {
    StageTile *rec;
    StageTile *tile;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 3) {
                task->tiles[0].playing = 0;
                task->tiles[0].tile = rec;
            }
            if (rec->anim == 4) {
                task->tiles[1].playing = 0;
                task->tiles[1].tile = rec;
            }
        }
        task->tiles[0].playing = 1;
        task->tiles[0].anim.index = 0;
        task->tiles[0].anim.timer = (u8)D_800A6514[0].duration;
        task->tiles[1].playing = 1;
        task->tiles[1].anim.index = 0;
        task->tiles[1].anim.timer = (u8)D_800A6560[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            tile = task->tiles[i].tile;
            if (task->tiles[i].playing) {
                frame = func_800A50E8(&task->tiles[i], D_800A65AC[i], 1, 0);
                if (frame == 0xFF) {
                    task->tiles[i].playing = 0;
                    tile->visible = 0;
                } else {
                    tile->visible = 1;
                    if (i == 0) {
                        tile->frame = frame;
                        tile->unk9 = 0;
                    } else {
                        tile->frame = 0x33;
                        tile->unk9 = frame;
                    }
                }
            } else {
                tile->visible = 0;
            }
        }
        if (task->tiles[0].playing == 0 && task->tiles[1].playing == 0) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A53D4(s32 arg) {
    return createTaskWithId(func_800A5208, 0x6C, 0, arg);
}

/* Draws the timer: its frame and the three digits of GAME.countdown */
void func_800A5404(StageTask *task) {
    SpriteDrawer drawer;
    Vec2 scroll;
    s32 i;
    Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getScroll(layer, &scroll);
    initSpriteDrawer(&drawer);
    drawer.setLayer(layer, 0);
    drawer.setTexture(0x140, 0x100);
    drawer.setAltClut(0, 0x1F0);
    drawer.draw(FILE_CACHE.getEntry(TIMER_SHEET << 16), 1, scroll.x + 0xE0, scroll.y + 0x16);
    scroll.y += 0x19;
    for (i = 0; i < 3; i++) {
        drawer.draw(FILE_CACHE.getEntry(TIMER_SHEET << 16), GAME.countdown[i] + 2, scroll.x + D_800A65B4[i], scroll.y);
    }
}

/* The timer: counts GAME.countdown down while nothing stops it, then starts event 0x5E2 */
void func_800A554C(StageTask *task, void **children) {
    u8 *countdown;

    switch (task->state) {
    case TASK_RUN:
        if (FLAGS_00.checkCondition(0x4043, 0) || D_800990B4.unk58 != 0 || D_800990B4.unk5C != 0 ||
            D_800990B4.unk54 != 0 || D_800990B4.unk50 != 0 || D_800990B4.unk60 != 0) {
            break;
        }
        func_800A5404(task);
        countdown = GAME.countdown;
        if (countdown[0] != 0 || countdown[1] != 0 || countdown[2] != 0) {
            countdown[3] -= GFX_FUNCS.getFrameTime();
            if (countdown[3] > 60) {
                countdown[2]--;
                countdown[3] += 60;
                SOUND.playSound(0x800452C6);
            }
            COUNTDOWN_BORROW(countdown);
            break;
        }
        children[0] = func_80084B80(0x5E2);
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A571C(void) {
    return createTask(func_800A554C, 0x54, 0x4);
}

/* Creates the timer, the stage's four effects, the event object of flags 0x4044/0x4045 and one of two objects by flag 0x4061 */
void func_800A5748(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A571C();
        for (i = 0; i < 4; i++) {
            if (D_800A65BC[i].kind == 0) {
                children[i + 1] = func_800A5E48(D_800A65BC[i].x, D_800A65BC[i].y, D_800A65BC[i].frame);
            }
        }
        if (FLAGS_00.checkCondition(0x4044, 1) && FLAGS_00.checkCondition(0x4045, 0)) {
            children[7] = func_80084B80(0x367);
        }
        if (FLAGS_00.checkCondition(0x4061, 0)) {
            children[5] = func_800A5084(0x345);
        } else {
            children[5] = func_800A50B4();
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5890(void *owner) {
    StageTask *task = createTask(func_800A5748, sizeof(StageTask), 0x20);

    task->owner = owner;
    D_800A6D44[0]();
    return task;
}

s32 func_800A58EC(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A58EC(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A5A0C(StageEffect *task, void *arg, s32 idx) {
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

s32 func_800A5AF4(s32 x, s32 y, s32 w, s32 h) {
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

void func_800A5BB8(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A6604[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A65EC[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A58EC(&task->clutAnim, D_800A65EC, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A5AF4(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5A0C, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A6604[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A65EC[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A58EC(&task->clutAnim, D_800A65EC, 0, 0);
        done = 0;
        frame = func_800A58EC(&task->anim, D_800A6604, 1, 0);
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
        if (task->sprites[0].frame != 0 && func_800A5AF4(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5A0C, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A5AF4(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A5A0C, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A5E48(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A5BB8, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

void func_800A5EA4(void) {
    FLAGS_00.applyAction(0x1C0A, 1);
    FLAGS_00.applyAction(0x4061, 1);
}

void func_800A5EF0(void) {
    FLAGS_00.applyAction(0x4044, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5F3C(void) {
    FLAGS_00.applyAction(0x4045, 1);
    FLAGS_00.applyAction(0x84CB, 1);
}

#if VERSION_US
void func_800A5F88(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x715;
    D_800990B4.unkC = 0x6EE0000;
    D_800990B4.unk10 = D_800A6AF0;
    D_800990B4.unk14 = D_800A6C6C;
    D_800990B4.unk1C = 0x6EA;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x1E500;
    D_800990B4.unk30 = 0x38700;
    D_800990B4.unk28 = D_800A6888;
    D_800990B4.unk3C = 0xD;
    D_800990B4.unk40 = 0x60340000;
    D_800990B4.unk4C = D_800A6AD0;
    D_800990B4.unk20 = D_800A686C;
    D_800990B4.unk34 = 0;
    D_800990B4.events = D_800A6D48;
    D_8009A70C.setFile(0, 0x6EE0001);
    D_8009A70C.setFile(7, 0x6EE0002);
    D_8009A70C.setFile(4, 0x6EE0003);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag800", func_800A5F88);
#endif

extern s32 D_800A665C[];
extern s32 D_800A6668[];
extern s32 D_800A6674[];
extern s32 D_800A6680[];
extern s32 D_800A668C[];
extern s32 D_800A6698[];
extern s32 D_800A66A4[];
extern s32 D_800A66B0[];
extern s32 D_800A66E0[];
extern s32 D_800A66EC[];
extern s32 D_800A66F8[];
extern s32 D_800A6704[];
extern s32 D_800A6710[];
extern s32 D_800A671C[];
extern s32 D_800A6728[];
extern s32 D_800A6734[];
extern s32 D_800A6764[];
extern s32 D_800A6770[];
extern s32 D_800A677C[];
extern s32 D_800A6788[];
extern s32 D_800A6794[];
extern s32 D_800A67A0[];
extern s32 D_800A67AC[];
extern s32 D_800A67B8[];
extern s32 D_800A67E8[];
extern s32 D_800A67F4[];
extern s32 D_800A6800[];
extern s32 D_800A680C[];
extern s32 D_800A6818[];
extern s32 D_800A6824[];
extern s32 D_800A6830[];
extern s32 D_800A683C[];
extern s32 D_800A66BC[];
extern s32 D_800A6740[];
extern s32 D_800A67C4[];
extern s32 D_800A6848[];
extern s32 D_800A6958[];
extern s32 D_800A6964[];
extern s32 D_800A6970[];
extern s32 D_800A697C[];
extern s32 D_800A6984[];
extern s32 D_800A6A08[];
extern s32 D_800A6990[];
extern s32 D_800A6A10[];
extern s32 D_800A69A8[];
extern s32 D_800A6A18[];
extern s32 D_800A69C0[];
extern s32 D_800A6A20[];
extern s32 D_800A69D8[];
extern s32 D_800A6A28[];
extern s32 D_800A69F0[];
extern s32 D_800A6A30[];
extern s32 D_800A6A3C[];
extern s32 D_800A6A44[];
extern s32 D_800A6A58[];
extern s32 D_800A6A6C[];
extern s32 D_800A6A80[];
extern s32 D_800A6A94[];
extern s32 D_800A6AA8[];
extern s32 D_800A6ABC[];
extern s32 D_800A609C[];
extern s32 D_800A6184[];
extern s32 D_800A620C[];
extern s32 D_800A646C[];

s32 D_800A609C[] = {
    0x20102, 0x33703BC, 0x1010003, 0x337032D,
    0x3020002, 0x3000002, 0x101001E, 0x3250323,
    0x3000002, 0x101005A, 0x3260323, 0x3000002,
    0x200001E, 0x10000, 2, 0x20101,
    0x30001, 0x3000301, 0x101001E, 0x377032D,
    0x3000002, 0x101001E, 0x35B0345, 0x3000002,
    0x1010078, 0x10002, 0x3000003, 0x101001E,
    0x10002, 0x1010007, 0x37F032D, 0x3000002,
    0x101001E, 0x10002, 0x3000005, 0x101001E,
    0x10002, 0x3000007, 0x101001E, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000007,
    0x200001E, 0x20000, 2, 0x20101,
    0x70007, 0x3000301, 0x102001E, 0x3E00002,
    0x70348, 0x20302, 0x20101, 0x70001,
    0x1E0300, 0,
};
s32 D_800A6184[] = {
    0x20102, 0x1B00590, 0x1010005, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000005,
    0x200001E, 0x10000, 2, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x101001E, 0x3250323, 0x30000D0, 0x101005A,
    0x3260323, 0x30000D0, 0x101001E, 0x100D0,
    0x3000001, 0x200001E, 0x20000, 208,
    0x3000301, 0x102001E, 0x5A800D0, 0x101A4,
    0xD00302, 0,
};
s32 D_800A620C[] = {
    0x20100, 0x1B00590, 0x20101, 0x50001,
    0x13C0100, 0x1A405A8, 0x13C0101, 0x10001,
    0x780300, 512, 0x20001, 0x1010000,
    0x70002, 0x3010005, 0x20101, 0x50001,
    0x1E0300, 0x20101, 0x50001, 0x1E0300,
    0x3230101, 0x20325, 0x5A0300, 0x3230101,
    0x20326, 0x1E0300, 0x20102, 0x1AC0598,
    0x3020005, 0x3000002, 0x100001E, 316,
    0x1010000, 0x1013C, 0x3000000, 0x200001E,
    0x20000, 2, 0x20101, 0x50007,
    0x1010301, 0x10002, 0x3000005, 0x101001E,
    0x3250323, 0x3000002, 0x101005A, 0x3260323,
    0x3000002, 0x200001E, 0x30000, 2,
    0x20101, 0x50007, 0x1010301, 0x10002,
    0x3000005, 0x102001E, 0x5F70002, 0x5017C,
    0x20302, 0x20101, 0x50001, 0x1E0300,
    0x20101, 0x50001, 0x1E0300, 0x20101,
    0x40001, 0x1E0300, 0x20101, 0x50001,
    0x1E0300, 0x20101, 0x60001, 0x3C0300,
    0x20101, 0x60001, 0x3230101, 0x20325,
    0x3C0300, 0x3230101, 0x20326, 0x1E0300,
    0x20102, 0x1840607, 0x3020005, 0x1010002,
    0x10002, 0x3000005, 0x200001E, 0x40000,
    2, 0x20101, 0x50007, 0x1010301,
    0x10002, 0x3000005, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x10002, 0x3000006,
    0x101001E, 0x10002, 0x3000005, 0x101001E,
    0x10002, 0x3000004, 0x101001E, 0x10002,
    0x1010005, 0x377032D, 0x3000002, 0x101001E,
    0x10002, 0x1010005, 0x35B0347, 0x3000002,
    0x20000B4, 0x50000, 2, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x200001E, 0x60000, 0x40002, 0x3230101,
    0x20325, 0x32D0101, 0x2037D, 0x1010301,
    0x10002, 0x1010001, 0x3260323, 0x3000002,
    0x200001E, 0x70000, 2, 0x20101,
    0x10007, 0x1010301, 0x10002, 0x3000001,
    0x101001E, 0x10002, 0x3020001, 2,
};
s32 D_800A646C[] = {
    0x1E0300, 0x3230101, 0x20325, 0x5A0300,
    0x3230101, 0x20326, 0x1E0300, 0x20101,
    1, 0x1E0300, 512, 0x20001,
    0x1010002, 0x70002, 0x3010000, 0x20101,
    1, 0x1E0300, 0x26D0304, 0x10001,
    1,
};
AnimFrame D_800A64C0[] = {
    { 0, 8 }, { 1, 8 }, { 255, 0 },
};
AnimFrame D_800A64CC[] = {
    { 71, 4 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 75, 4 }, { 76, 4 }, { 77, 4 }, { 78, 4 },
    { 79, 4 }, { 80, 4 }, { 255, 0 },
};
AnimFrame D_800A64F8[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 255, 0 },
};
AnimFrame D_800A6514[] = {
    { 52, 6 }, { 53, 6 }, { 54, 6 }, { 55, 6 },
    { 56, 6 }, { 57, 6 }, { 58, 6 }, { 59, 6 },
    { 60, 6 }, { 61, 6 }, { 62, 6 }, { 63, 6 },
    { 64, 6 }, { 65, 6 }, { 66, 6 }, { 67, 6 },
    { 68, 6 }, { 69, 6 }, { 255, 0 },
};
AnimFrame D_800A6560[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 0, 6 }, { 1, 6 },
    { 2, 6 }, { 3, 6 }, { 4, 6 }, { 5, 6 },
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 255, 0 },
};
AnimFrame *D_800A65AC[] = {
    D_800A6514, D_800A6560,
};
s16 D_800A65B4[] = {
    226, 253, 0x118, 0,
};
StageEffectSpot D_800A65BC[] = {
    { 28, 0, 0x4BC, 0x273 },
    { 28, 0, 0x39C, 0x373 },
    { 20, 0, 0x2BC, 211 },
    { 20, 0, 0x43C, 0x323 },
};
AnimFrame D_800A65EC[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A6604[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A665C[] = {
    123, 16, 0x60080000,
};
s32 D_800A6668[] = {
    123, 16, 0x60080000,
};
s32 D_800A6674[] = {
    123, 16, 0x60080000,
};
s32 D_800A6680[] = {
    122, 16, 0x60080000,
};
s32 D_800A668C[] = {
    122, 16, 0x60080000,
};
s32 D_800A6698[] = {
    122, 16, 0x60080000,
};
s32 D_800A66A4[] = {
    102, 16, 0x60080000,
};
s32 D_800A66B0[] = {
    102, 16, 0x60080000,
};
s32 D_800A66BC[] = {
    3, (s32)D_800A665C, (s32)D_800A6668, (s32)D_800A6674,
    (s32)D_800A6680, (s32)D_800A668C, (s32)D_800A6698, (s32)D_800A66A4,
    (s32)D_800A66B0,
};
s32 D_800A66E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A66EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A66F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6704[] = {
    0, 0, 0x60040000,
};
s32 D_800A6710[] = {
    0, 0, 0x60040000,
};
s32 D_800A671C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6728[] = {
    0, 0, 0x60040000,
};
s32 D_800A6734[] = {
    0, 0, 0x60040000,
};
s32 D_800A6740[] = {
    0, (s32)D_800A66E0, (s32)D_800A66EC, (s32)D_800A66F8,
    (s32)D_800A6704, (s32)D_800A6710, (s32)D_800A671C, (s32)D_800A6728,
    (s32)D_800A6734,
};
s32 D_800A6764[] = {
    0, 0, 0x60040000,
};
s32 D_800A6770[] = {
    0, 0, 0x60040000,
};
s32 D_800A677C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6788[] = {
    0, 0, 0x60040000,
};
s32 D_800A6794[] = {
    0, 0, 0x60040000,
};
s32 D_800A67A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A67AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A67B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A67C4[] = {
    0, (s32)D_800A6764, (s32)D_800A6770, (s32)D_800A677C,
    (s32)D_800A6788, (s32)D_800A6794, (s32)D_800A67A0, (s32)D_800A67AC,
    (s32)D_800A67B8,
};
s32 D_800A67E8[] = {
    193, 16, 0x60080000,
};
s32 D_800A67F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6800[] = {
    0, 0, 0x60040000,
};
s32 D_800A680C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6818[] = {
    0, 0, 0x60040000,
};
s32 D_800A6824[] = {
    0, 0, 0x60040000,
};
s32 D_800A6830[] = {
    0, 0, 0x60040000,
};
s32 D_800A683C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6848[] = {
    0, (s32)D_800A67E8, (s32)D_800A67F4, (s32)D_800A6800,
    (s32)D_800A680C, (s32)D_800A6818, (s32)D_800A6824, (s32)D_800A6830,
    (s32)D_800A683C,
};
s32 D_800A686C[] = {
    91, 0, 0, (s32)D_800A66BC,
    (s32)D_800A6740, (s32)D_800A67C4, (s32)D_800A6848,
};
u8 D_800A6888[] = {
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
    0x80, 0x01, 0x00, 0x01, 0x9C, 0x01, 0x58, 0x01,
    0x70, 0x01, 0x58, 0x00, 0x70, 0x01, 0xD9, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA2, 0x01, 0x58, 0x01,
    0x88, 0x01, 0x58, 0x00, 0x70, 0x01, 0xD8, 0x01,
    0x80, 0x01, 0x00, 0x01, 0xA8, 0x01, 0x58, 0x01,
    0xA0, 0x01, 0x58, 0x00, 0x70, 0x01, 0xD7, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x8C, 0x01, 0x70, 0x01,
    0x30, 0x01, 0x70, 0x00, 0x70, 0x01, 0xD6, 0x01,
    0x80, 0x01, 0x00, 0x01, 0x92, 0x01, 0x70, 0x01,
    0x48, 0x01, 0x70, 0x00, 0x70, 0x01, 0xD5, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x6E, 0x01, 0xA8, 0x01,
    0xB8, 0x00, 0xA8, 0x00, 0x70, 0x01, 0xD4, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x7A, 0x01, 0xB0, 0x01,
    0xE8, 0x00, 0xB0, 0x00, 0x70, 0x01, 0xD3, 0x01,
};
s32 D_800A6958[] = {
    0x10245, 0x18AE0, 65535,
};
s32 D_800A6964[] = {
    0x10246, 0x18AEA, 65535,
};
s32 D_800A6970[] = {
    0x10247, 0x1822C, 65535,
};
s32 D_800A697C[] = {
    0x10248, 65535,
};
s32 D_800A6984[] = {
    0x10249, 0x18B11, 65535,
};
s32 D_800A6990[] = {
    0, (s32)D_800A6958, 539, 0,
    0, 0,
};
s32 D_800A69A8[] = {
    0, (s32)D_800A6964, 540, 0,
    0, 0,
};
s32 D_800A69C0[] = {
    0, (s32)D_800A6970, 381, 0,
    0, 0,
};
s32 D_800A69D8[] = {
    0, (s32)D_800A697C, 401, 0,
    0, 0,
};
s32 D_800A69F0[] = {
    0, (s32)D_800A6984, 543, 0,
    0, 0,
};
s32 D_800A6A08[] = {
    581, 65535,
};
s32 D_800A6A10[] = {
    582, 65535,
};
s32 D_800A6A18[] = {
    583, 65535,
};
s32 D_800A6A20[] = {
    584, 65535,
};
s32 D_800A6A28[] = {
    585, 65535,
};
s32 D_800A6A30[] = {
    0x16020, 16452, 65535,
};
s32 D_800A6A3C[] = {
    0x16020, 65535,
};
s32 D_800A6A44[] = {
    (s32)D_800A6A08, (s32)D_800A6990, 0x40021, 0xA80400,
    1,
};
s32 D_800A6A58[] = {
    (s32)D_800A6A10, (s32)D_800A69A8, 0x5004D, 0x3AA0280,
    1,
};
s32 D_800A6A6C[] = {
    (s32)D_800A6A18, (s32)D_800A69C0, 0x6004E, 0x14804C1,
    1,
};
s32 D_800A6A80[] = {
    (s32)D_800A6A20, (s32)D_800A69D8, 0x7004F, 0x11904E1,
    1,
};
s32 D_800A6A94[] = {
    (s32)D_800A6A28, (s32)D_800A69F0, 0x80050, 0x2B90160,
    1,
};
s32 D_800A6AA8[] = {
    (s32)D_800A6A30, 0, 0x900D0, 0x19905C1,
    5,
};
s32 D_800A6ABC[] = {
    (s32)D_800A6A3C, 0, 0xA013C, 0,
    1,
};
s32 D_800A6AD0[] = {
    (s32)D_800A6A44, (s32)D_800A6A58, (s32)D_800A6A6C, (s32)D_800A6A80,
    (s32)D_800A6A94, (s32)D_800A6AA8, (s32)D_800A6ABC, 0,
};
u8 D_800A6AF0[] = {
    0x01, 0x00, 0x40, 0x02, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0xD8, 0x02, 0xD4, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0xF8, 0x02, 0xC5, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0xB8, 0x03,
    0x74, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0xD8, 0x03, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x02, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x58, 0x04, 0x24, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x02, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0x78, 0x04, 0x14, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x02,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0xD8, 0x04,
    0x75, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x02, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0xF8, 0x04, 0x64, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x02, 0x64, 0x06, 0x51, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x82, 0x03, 0xFC, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x64, 0x06, 0x46, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x82, 0x03, 0xFC, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0x90, 0x02,
    0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0xB0, 0x02, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x70, 0x03, 0x50, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0x90, 0x03, 0x40, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x06,
    0x32, 0x02, 0x00, 0x05, 0x04, 0x00, 0x10, 0x04,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x40, 0x06, 0x32, 0x02, 0x00, 0x05, 0x04, 0x00,
    0x30, 0x04, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x40, 0x06, 0x32, 0x02, 0x00, 0x05,
    0x04, 0x00, 0x90, 0x04, 0x50, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x40, 0x06, 0x32, 0x02,
    0x00, 0x05, 0x04, 0x00, 0xB0, 0x04, 0x40, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x64, 0x06,
    0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x06,
    0x52, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x64, 0x06, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0E, 0x06, 0x52, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A6C6C[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDA, 0x02, 0xF2, 0x04, 0x50, 0x01,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDA, 0x02, 0x22, 0x05, 0xF6, 0x01,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDA, 0x02, 0x52, 0x05, 0x8E, 0x02,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDA, 0x02, 0x54, 0x05, 0x00, 0x04,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x60, 0x01, 0x00, 0x44, 0x40, 0x00, 0x00,
    0x08, 0x00, 0x66, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x1C, 0x01, 0x00, 0x61, 0x40, 0x00, 0x00,
    0x08, 0x00, 0x52, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x1C, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0D, 0x00, 0xDB, 0x02, 0x50, 0x04, 0x30, 0x03,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x1C, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0D, 0x00, 0xDB, 0x02, 0xD0, 0x02, 0xE0, 0x00,
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A6D44[])(void) = {
    func_800A5F88,
};
s32 D_800A6D48[] = {
    850, (s32)D_800A609C,
#if VERSION_US
    0x14A0000,
#elif VERSION_EU
    0x1510000,
#endif
    0, (s32)func_800A5EA4, 870, (s32)D_800A6184,
#if VERSION_US
    0x14A0001,
#elif VERSION_EU
    0x1510001,
#endif
    0, (s32)func_800A5EF0, 871, (s32)D_800A620C,
#if VERSION_US
    0x14A0002,
#elif VERSION_EU
    0x1510002,
#endif
    0, (s32)func_800A5F3C, 1506, (s32)D_800A646C,
#if VERSION_US
    0x14A0012,
#elif VERSION_EU
    0x1510012,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
