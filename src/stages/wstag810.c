#include "common.h"
#include "stage.h"
extern void (*D_800A6E90[])(void);
void func_800A517C();
extern AnimFrame D_800A63B0[];
extern AnimFrame D_800A6398[];
extern AnimFrame D_800A6048[];
extern AnimFrame D_800A6058[];
extern AnimFrame D_800A6094[];
extern StageEffectSpot D_800A60B0[];
extern s32 D_800A6968[];
extern s32 D_800A6C68[];
StageEffect *func_800A5894(s32 x, s32 y, s32 frame);

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
void func_800A4DC4(StageTilePairN *task) {
    StageTile *tile;
    StageTile *rec;
    s32 i;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == task->anim) {
                task->anims[0].anim.index = 0;
                task->anims[0].anim.timer = (u8)D_800A6048[0].duration;
                task->anims[0].tile = rec;
            }
            if (rec->anim == task->anim + 1) {
                task->anims[1].anim.index = 0;
                task->anims[1].anim.timer = (u8)D_800A6094[0].duration;
                task->anims[1].tile = rec;
            }
        }
        task->playing = 0;
        if (task->done == 1) {
            task->playing = 1;
            task->anims[0].anim.index = 0;
            task->anims[0].anim.timer = (u8)D_800A6058[0].duration;
            task->setState(task, TASK_DONE);
        } else {
            task->nextState(task);
        }
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            tile = task->anims[i].tile;
            switch (i) {
            case 0:
                tile->visible = 1;
                tile->frame = 0x55;
                tile->unk9 = func_800A4CA4(&task->anims[0], D_800A6048, 0, 0);
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
                    frame = func_800A4CA4(&task->anims[0], D_800A6058, 1, 0);
                    if (frame == 0xFF) {
                        tile->frame = 0x54;
                        task->playing = 0;
                    } else {
                        tile->frame = frame;
                    }
                } else {
                    tile->frame = 0x54;
                }
                tile->unk9 = 0;
                break;
            case 1:
                tile->visible = 1;
                tile->frame = 0x46;
                tile->unk9 = func_800A4CA4(&task->anims[1], D_800A6094, 0, 0);
                break;
            }
        }
        break;
    case TASK_KILL:
        break;
    }
}

/* Plays the first record's one-shot animation when the event of map object 0x35B happens */
void func_800A503C(StageTilePairN *task, s32 id) {
    if (id == 0x35B) {
        task->playing = 1;
        task->anims[0].anim.index = 0;
        task->anims[0].anim.timer = (u8)D_800A6058[0].duration;
        task->setState(task, TASK_DONE);
    }
}

/* Creates the tile pair object of animations 1 and 2 */
void *func_800A5088(s32 arg) {
    StageTilePairN *task = createTaskWithId(func_800A4DC4, 0x68, 0, arg);

    task->anim = 1;
    task->done = 0;
    return task;
}

/* Creates the tile pair object of animations 3 and 4 */
void *func_800A50C4(s32 arg) {
    StageTilePairN *task = createTaskWithId(func_800A4DC4, 0x68, 0, arg);

    task->anim = 3;
    task->done = 0;
    return task;
}

/* Creates the tile pair object of animations 5 and 6 */
void *func_800A5100(s32 arg) {
    StageTilePairN *task = createTaskWithId(func_800A4DC4, 0x68, 0, arg);

    task->anim = 5;
    task->done = 0;
    return task;
}

/* Creates the tile pair object of animations anim and anim + 1, started in TASK_DONE */
void *func_800A513C(s32 anim) {
    StageTilePairN *task = createTask(func_800A4DC4, 0x68, 0);

    task->anim = anim;
    task->done = 1;
    return task;
}

/* Creates the stage's 62 effects and its three tile pairs, started by flags 0x406E, 0x406F and 0x406D */
void func_800A517C(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        for (i = 0; i < 62; i++) {
            if (D_800A60B0[i].kind == 0) {
                children[i] = func_800A5894(D_800A60B0[i].x, D_800A60B0[i].y, D_800A60B0[i].frame);
            }
        }
        if (FLAGS_00.checkCondition(0x406E, 0)) {
            children[62] = func_800A5088(0x34C);
        } else {
            children[62] = func_800A513C(1);
        }
        if (FLAGS_00.checkCondition(0x406F, 0)) {
            children[63] = func_800A50C4(0x34B);
        } else {
            children[63] = func_800A513C(3);
        }
        if (FLAGS_00.checkCondition(0x406D, 0)) {
            children[64] = func_800A5100(0x34A);
        } else {
            children[64] = func_800A513C(5);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A52DC(void *owner) {
    StageTask *task = createTask(func_800A517C, sizeof(StageTask), 0x104);

    task->owner = owner;
    D_800A6E90[0]();
    return task;
}

s32 func_800A5338(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A5338(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A5458(StageEffect *task, void *arg, s32 idx) {
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

s32 func_800A5540(s32 x, s32 y, s32 w, s32 h) {
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

void func_800A5604(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A63B0[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A6398[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5338(&task->clutAnim, D_800A6398, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A5540(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5458, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A63B0[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A6398[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5338(&task->clutAnim, D_800A6398, 0, 0);
        done = 0;
        frame = func_800A5338(&task->anim, D_800A63B0, 1, 0);
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
        if (task->sprites[0].frame != 0 && func_800A5540(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A5458, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A5540(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A5458, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A5894(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A5604, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag810", func_800A58F0);

INCLUDE_ASM("stages/nonmatchings/wstag810", func_800A5954);

void func_800A59BC(void) {
    FLAGS_00.applyAction(0x406D, 1);
    FLAGS_00.applyAction(0x1C3A, 1);
}

void func_800A5A08(void) {
    FLAGS_00.applyAction(0x406E, 1);
    FLAGS_00.applyAction(0x1C3B, 1);
}

void func_800A5A54(void) {
    FLAGS_00.applyAction(0x406F, 1);
    FLAGS_00.applyAction(0x1C3C, 1);
}

void func_800A5AA0(void) {
    GAME_PROGRESS = 41;
}

INCLUDE_ASM("stages/nonmatchings/wstag810", func_800A5AB0);

void func_800A5AB0();
void func_800A58F0();
void func_800A5954();
extern s32 D_800A6408[];
extern s32 D_800A6414[];
extern s32 D_800A6420[];
extern s32 D_800A642C[];
extern s32 D_800A6438[];
extern s32 D_800A6444[];
extern s32 D_800A6450[];
extern s32 D_800A645C[];
extern s32 D_800A648C[];
extern s32 D_800A6498[];
extern s32 D_800A64A4[];
extern s32 D_800A64B0[];
extern s32 D_800A64BC[];
extern s32 D_800A64C8[];
extern s32 D_800A64D4[];
extern s32 D_800A64E0[];
extern s32 D_800A6510[];
extern s32 D_800A651C[];
extern s32 D_800A6528[];
extern s32 D_800A6534[];
extern s32 D_800A6540[];
extern s32 D_800A654C[];
extern s32 D_800A6558[];
extern s32 D_800A6564[];
extern s32 D_800A6594[];
extern s32 D_800A65A0[];
extern s32 D_800A65AC[];
extern s32 D_800A65B8[];
extern s32 D_800A65C4[];
extern s32 D_800A65D0[];
extern s32 D_800A65DC[];
extern s32 D_800A65E8[];
extern s32 D_800A6468[];
extern s32 D_800A64EC[];
extern s32 D_800A6570[];
extern s32 D_800A65F4[];
extern s32 D_800A670C[];
extern s32 D_800A66C4[];
extern s32 D_800A6714[];
extern s32 D_800A66DC[];
extern s32 D_800A671C[];
extern s32 D_800A66F4[];
extern s32 D_800A6724[];
extern s32 D_800A6738[];
extern s32 D_800A674C[];
extern s32 D_800A5BE0[];
extern s32 D_800A5D18[];
extern s32 D_800A5E50[];
extern s32 D_800A5F88[];

s32 D_800A5BE0[] = {
    0x20102, 0x1400530, 0x1010005, 0x337032D,
    0x3020002, 0x3000002, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x10002, 0x3000004,
    0x101001E, 0x10002, 0x3000005, 0x101001E,
    0x10002, 0x3000006, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x3250323, 0x3000002,
    0x101005A, 0x3260323, 0x3000002, 0x200001E,
    0x10000, 2, 0x20101, 0x50007,
    0x1010301, 0x10002, 0x3000005, 0x101001E,
    0x377032D, 0x1010002, 0x35B034A, 0x3000002,
    0x300005A, 0x101001E, 0x10002, 0x1000001,
    384, 0x1010000, 0x10180, 0x1010001,
    0x374032D, 0x3000002, 0x101005A, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000002,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000000, 0x101001E, 0x10002,
    0x3000001, 0x200001E, 0x20000, 2,
    0x20101, 0x10007, 0x1010301, 0x10002,
    0x3000001, 0x102001E, 0x5100002, 0x10151,
    0x20302, 0,
};
s32 D_800A5D18[] = {
    0x20102, 0x900390, 0x1010005, 0x337032D,
    0x3020002, 0x3000002, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x10002, 0x3000004,
    0x101001E, 0x10002, 0x3000005, 0x101001E,
    0x10002, 0x3000006, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x3250323, 0x3000002,
    0x101005A, 0x3260323, 0x3000002, 0x200001E,
    0x10000, 2, 0x20101, 0x50007,
    0x1010301, 0x10002, 0x3000005, 0x101001E,
    0x377032D, 0x1010002, 0x35B034C, 0x3000002,
    0x300005A, 0x101001E, 0x10002, 0x1000001,
    385, 0x1010000, 0x10181, 0x1010001,
    0x374032D, 0x3000002, 0x101005A, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000002,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000000, 0x101001E, 0x10002,
    0x3000001, 0x200001E, 0x20000, 2,
    0x20101, 0x10007, 0x1010301, 0x10002,
    0x3000001, 0x102001E, 0x3700002, 0x100A0,
    0x20302, 0,
};
s32 D_800A5E50[] = {
    0x20102, 0x900510, 0x1010005, 0x337032D,
    0x3020002, 0x3000002, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x10002, 0x3000004,
    0x101001E, 0x10002, 0x3000005, 0x101001E,
    0x10002, 0x3000006, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x3250323, 0x3000002,
    0x101005A, 0x3260323, 0x3000002, 0x200001E,
    0x10000, 2, 0x20101, 0x50007,
    0x1010301, 0x10002, 0x3000005, 0x101001E,
    0x377032D, 0x1010002, 0x35B034B, 0x3000002,
    0x300005A, 0x101001E, 0x10002, 0x1000001,
    386, 0x1010000, 0x10182, 0x1010001,
    0x374032D, 0x3000002, 0x101005A, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000002,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000000, 0x101001E, 0x10002,
    0x3000001, 0x200001E, 0x20000, 2,
    0x20101, 0x10007, 0x1010301, 0x10002,
    0x3000001, 0x102001E, 0x50F0002, 0x10091,
    0x20302, 0,
};
s32 D_800A5F88[] = {
    0x20102, 0x2D900A0, 0x1010001, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000001,
    0x200001E, 0x10000, 0x40002, 0x3000301,
    0x101001E, 0x3250323, 0x3000002, 0x101005A,
    0x3260323, 0x3000002, 0x101001E, 0x10002,
    0x3000007, 0x101001E, 0x10002, 0x3000007,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000007, 0x101001E, 0x10002,
    0x3000005, 0x101001E, 0x10002, 0x3000007,
    0x200001E, 0x20000, 0x20002, 0x20101,
    0x70001, 0x1010301, 0x10002, 0x3000007,
    0x101001E, 0x10002, 0x3000001, 30,
};
AnimFrame D_800A6048[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 255, 0 },
};
AnimFrame D_800A6058[] = {
    { 71, 4 }, { 72, 4 }, { 73, 4 }, { 74, 4 },
    { 75, 4 }, { 76, 4 }, { 77, 4 }, { 78, 4 },
    { 79, 4 }, { 80, 4 }, { 81, 4 }, { 82, 4 },
    { 83, 4 }, { 84, 4 }, { 255, 0 },
};
AnimFrame D_800A6094[] = {
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 6 }, { 255, 0 },
};
StageEffectSpot D_800A60B0[] = {
    { 60, 0, 92, 181 },
    { 60, 0, 92, 245 },
    { 60, 0, 92, 0x195 },
    { 52, 0, 92, 0x1D5 },
    { 60, 0, 156, 213 },
    { 52, 0, 220, 245 },
    { 60, 0, 220, 0x135 },
    { 44, 0, 236, 0x2EC },
    { 44, 0, 252, 0x395 },
    { 60, 0, 0x11C, 149 },
    { 60, 0, 0x11C, 0x1D5 },
    { 44, 0, 0x11C, 0x324 },
    { 60, 0, 0x12C, 0x2CC },
    { 60, 0, 0x13C, 0x3B5 },
    { 60, 0, 0x15C, 181 },
    { 60, 0, 0x15C, 0x344 },
    { 60, 0, 0x17C, 133 },
    { 52, 0, 0x19C, 0x1D5 },
    { 60, 0, 0x1BC, 0x1A5 },
    { 60, 0, 0x1DC, 0x115 },
    { 60, 0, 0x1FC, 0x225 },
    { 52, 0, 0x21C, 0x1D5 },
    { 60, 0, 0x23C, 133 },
    { 60, 0, 0x23C, 0x245 },
    { 60, 0, 0x27C, 0x265 },
    { 60, 0, 0x29C, 0x195 },
    { 60, 0, 0x2BC, 133 },
    { 60, 0, 0x2BC, 0x285 },
    { 60, 0, 0x2DC, 0x175 },
    { 60, 0, 0x2EC, 0x41D },
    { 60, 0, 0x2FC, 0x2A5 },
    { 60, 0, 0x31C, 245 },
    { 60, 0, 0x33C, 0x225 },
    { 52, 0, 0x35C, 0x1B5 },
    { 60, 0, 0x36C, 0x2BD },
    { 52, 0, 0x36C, 0x2FD },
    { 60, 0, 0x36C, 0x33D },
    { 60, 0, 0x3AC, 0x35D },
    { 60, 0, 0x3BC, 0x145 },
    { 60, 0, 0x3BC, 0x1A5 },
    { 60, 0, 0x3CC, 0x38D },
    { 52, 0, 0x3EC, 0x33D },
    { 60, 0, 0x3EC, 0x3BD },
    { 60, 0, 0x3FC, 0x2A5 },
    { 52, 0, 0x42C, 0x39D },
    { 52, 0, 0x43C, 133 },
    { 52, 0, 0x43C, 0x245 },
    { 60, 0, 0x44C, 0x40D },
    { 60, 0, 0x45C, 0x1F5 },
    { 60, 0, 0x48C, 0x34D },
    { 60, 0, 0x49C, 0x1B5 },
    { 52, 0, 0x4DC, 245 },
    { 52, 0, 0x4DC, 0x1F5 },
    { 60, 0, 0x4DC, 0x295 },
    { 60, 0, 0x4EC, 0x35D },
    { 60, 0, 0x4EC, 0x41D },
    { 52, 0, 0x51C, 0x1B5 },
    { 60, 0, 0x51C, 0x235 },
    { 60, 0, 0x51C, 0x2B5 },
    { 60, 0, 0x51C, 0x2F5 },
    { 52, 0, 108, 0x2DC },
    { 44, 0, 204, 0x40D },
};
AnimFrame D_800A6398[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A63B0[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A6408[] = {
    185, 17, 0x60080000,
};
s32 D_800A6414[] = {
    185, 17, 0x60080000,
};
s32 D_800A6420[] = {
    185, 17, 0x60080000,
};
s32 D_800A642C[] = {
    135, 17, 0x60080000,
};
s32 D_800A6438[] = {
    135, 17, 0x60080000,
};
s32 D_800A6444[] = {
    135, 17, 0x60080000,
};
s32 D_800A6450[] = {
    140, 17, 0x60080000,
};
s32 D_800A645C[] = {
    140, 17, 0x60080000,
};
s32 D_800A6468[] = {
    4, (s32)D_800A6408, (s32)D_800A6414, (s32)D_800A6420,
    (s32)D_800A642C, (s32)D_800A6438, (s32)D_800A6444, (s32)D_800A6450,
    (s32)D_800A645C,
};
s32 D_800A648C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6498[] = {
    0, 0, 0x60040000,
};
s32 D_800A64A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64EC[] = {
    0, (s32)D_800A648C, (s32)D_800A6498, (s32)D_800A64A4,
    (s32)D_800A64B0, (s32)D_800A64BC, (s32)D_800A64C8, (s32)D_800A64D4,
    (s32)D_800A64E0,
};
s32 D_800A6510[] = {
    0, 0, 0x60040000,
};
s32 D_800A651C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6528[] = {
    0, 0, 0x60040000,
};
s32 D_800A6534[] = {
    0, 0, 0x60040000,
};
s32 D_800A6540[] = {
    0, 0, 0x60040000,
};
s32 D_800A654C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6558[] = {
    0, 0, 0x60040000,
};
s32 D_800A6564[] = {
    0, 0, 0x60040000,
};
s32 D_800A6570[] = {
    0, (s32)D_800A6510, (s32)D_800A651C, (s32)D_800A6528,
    (s32)D_800A6534, (s32)D_800A6540, (s32)D_800A654C, (s32)D_800A6558,
    (s32)D_800A6564,
};
s32 D_800A6594[] = {
    0, 0, 0x60040000,
};
s32 D_800A65A0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A65D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A65DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A65E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A65F4[] = {
    0, (s32)D_800A6594, (s32)D_800A65A0, (s32)D_800A65AC,
    (s32)D_800A65B8, (s32)D_800A65C4, (s32)D_800A65D0, (s32)D_800A65DC,
    (s32)D_800A65E8,
};
s32 D_800A6618[] = {
    124, 0, 0, (s32)D_800A6468,
    (s32)D_800A64EC, (s32)D_800A6570, (s32)D_800A65F4,
};
s32 D_800A6634[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1B10152, 0xB10048, 0x1F80170,
    0x1000140, 0x1B10162, 0xB10088, 0x1F70140,
    0x1000180, 0x1000180, 256, 0x1F70150,
};
s32 D_800A66C4[] = {
    0, 0, 840, 0,
    0, 0,
};
s32 D_800A66DC[] = {
    0, 0, 840, 0,
    0, 0,
};
s32 D_800A66F4[] = {
    0, 0, 840, 0,
    0, 0,
};
s32 D_800A670C[] = {
    7226, 65535,
};
s32 D_800A6714[] = {
    7227, 65535,
};
s32 D_800A671C[] = {
    7228, 65535,
};
s32 D_800A6724[] = {
    (s32)D_800A670C, (s32)D_800A66C4, 0x40180, 0x3900171,
    7,
};
s32 D_800A6738[] = {
    (s32)D_800A6714, (s32)D_800A66DC, 0x50181, 0x3200190,
    7,
};
s32 D_800A674C[] = {
    (s32)D_800A671C, (s32)D_800A66F4, 0x60182, 0x2C000D0,
    7,
};
s32 D_800A6760[] = {
    (s32)D_800A6724, (s32)D_800A6738, (s32)D_800A674C, 0,
};
s32 D_800A6770[] = {
    0x6640201, 70, 0x38E0000, 80,
    0x4010000, 0x460664, 0, 0x50050F,
    0, 0x6640601, 70, 0x52F0000,
    256, 0x1010000, 0x470664, 0,
    0x50038E, 0, 0x6640301, 71,
    0x50F0000, 80, 0x5010000, 0x470664,
    0, 0x100052F, 0, 0xAC80001,
    0, 0x1A0000, 975, 0x10000,
    2760, 0, 0x8A002F, 0,
    0xAC80001, 0, 0x7B0000, 576,
    0x10000, 2760, 0, 0x36D007D,
    0, 0xAC80001, 0, 0xC30000,
    656, 0x10000, 2760, 0,
    0x2000E7, 0, 0xAC80001, 0,
    0x1330000, 580, 0x10000, 2760,
    0, 0x36A01AF, 0, 0xAC80001,
    0, 0x1E60000, 102, 0x10000,
    2760, 0, 0x2DC0214, 0,
    0xAC80001, 0, 0x2250000, 1020,
    0x10000, 2760, 0, 0x3340253,
    0, 0xAC80001, 0, 0x2670000,
    349, 0x10000, 2760, 0,
    0x21029C, 0, 0xAC80001, 0,
    0x2C90000, 235, 0x10000, 2760,
    0, 0x34502E2, 0, 0xAC80001,
    0, 0x37A0000, 262, 0x10000,
    2760, 0, 0x2E040D, 0,
    0xAC80001, 0, 0x41E0000, 329,
    0x10000, 2760, 0, 0x1930454,
    0, 0xAC80001, 0, 0x54A0000,
    1060, 0, 0, 0,
    0, 0,
};
s32 D_800A6968[] = {
    65535, 65535, 0x2DD000D, 0x41E0314,
    5, 0, 65535, 65535,
    0x2DD000D, 0x3B6013C, 3, 0,
    65535, 65535, 0x2DD000D, 0x1960084,
    5, 0, 65535, 65535,
    0x2DD000D, 0x40E044C, 3, 0,
    65535, 65535, 0x2DD000D, 0x1B604C4,
    5, 0, 65535, 65535,
    0x2DD000D, 0x10A0084, 7, 0,
    65535, 65535, 0x2DD000D, 0x3A203CC,
    1, 0, 65535, 65535,
    0x2DD000D, 0x346015C, 3, 0,
    65535, 65535, 0x2DD000D, 0x23A033C,
    1, 0, 65535, 65535,
    0x2DD000D, 0x3D203EC, 1, 0,
    65535, 65535, 0x2DD000D, 0x2260224,
    5, 0, 65535, 65535,
    0x2DD000D, 0x37203AC, 1, 0,
    65535, 65535, 0x2DD000D, 0x28602E4,
    5, 0, 65535, 65535,
    0x2DD000D, 0x2460264, 5, 0,
    65535, 65535, 0x2DD000D, 0x1D6011C,
    3, 0, 65535, 65535,
    0x2DD000D, 0x2A60324, 5, 0,
    65535, 65535, 0x2DD000D, 0x24A051C,
    1, 0, 65535, 65535,
    0x2DD000D, 0x26602A4, 5, 0,
    65535, 65535, 0x2DE000E, 0x2DF0189,
    3, 0, 65535, 65535,
    0x2DE000E, 0x28300CE, 7, 0,
    65535, 65535, 0x2DD000D, 0x33E0394,
    5, 0, 65535, 65535,
    0x2DD000D, 0x2E2012C, 1, 0,
    65535, 65535, 0x2DE000E, 0x11703F8,
    3, 0, 65535, 65535,
    0x2DE000E, 0xBA033E, 7, 0,
    65535, 65535, 0x2DD000D, 0x3A00110,
    7, 0, 65535, 65535,
    0x2DD000D, 0x3300130, 7, 0,
    65535, 65535, 0x2DE000E, 0x2D2040C,
    1, 0, 16493, 65535,
    0x3DE0008, 0, 0, 0,
    16494, 65535, 0x3E80008, 0,
    0, 0, 16495, 65535,
    0x3F20008, 0, 0, 0,
    0x16028, 65535, 0x40B0008, 0,
    0, 0, 65535, 65535,
    0x23290008, 0, 0, 0,
};
s32 D_800A6C68[] = {
    65535, 65535, 0x2DD000D, 0xAA011C,
    1, 0, 65535, 65535,
    0x2DD000D, 0x2D20394, 7, 0,
    65535, 65535, 0x2DD000D, 0x34E048C,
    3, 0, 65535, 65535,
    0x2DD000D, 0x20A045C, 1, 0,
    65535, 65535, 0x2DD000D, 0x2A603FC,
    3, 0, 65535, 65535,
    0x2DD000D, 0xCA0184, 7, 0,
    65535, 65535, 0x2DD000D, 0x12A0204,
    7, 0, 65535, 65535,
    0x2DD000D, 0x14A0104, 7, 0,
    65535, 65535, 0x2DD000D, 0x2CA051C,
    1, 0, 65535, 65535,
    0x2DD000D, 0x1A601BC, 3, 0,
    65535, 65535, 0x2DD000D, 0x30A051C,
    1, 0, 65535, 65535,
    0x2DD000D, 0xB60084, 5, 0,
    65535, 65535, 0x2DD000D, 0x9A023C,
    1, 0, 65535, 65535,
    0x2DD000D, 0xD600C4, 5, 0,
    65535, 65535, 0x2DD000D, 0x1BA03E4,
    7, 0, 65535, 65535,
    0x2DD000D, 0x9A02BC, 1, 0,
    65535, 65535, 0x2DD000D, 0x37204EC,
    1, 0, 65535, 65535,
    0x2DD000D, 0x9A01A4, 7, 0,
    65535, 65535, 0x2DD000D, 0x41E04EC,
    3, 0, 65535, 65535,
    0x2DD000D, 0x18A0304, 7, 0,
    65535, 65535, 0x2DD000D, 0x2F80100,
    5, 0, 65535, 65535,
    0x23280008, 0, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A6E90[])(void) = {
    func_800A5AB0,
};
s32 D_800A6E94[] = {
    990, (s32)D_800A5BE0,
#if VERSION_US
    0x14A0006,
#elif VERSION_EU
    0x1510006,
#endif
    0, (s32)func_800A59BC, 1000, (s32)D_800A5D18,
#if VERSION_US
    0x14A0007,
#elif VERSION_EU
    0x1510007,
#endif
    0, (s32)func_800A5A08, 1010, (s32)D_800A5E50,
#if VERSION_US
    0x14A0008,
#elif VERSION_EU
    0x1510008,
#endif
    0, (s32)func_800A5A54, 1035, (s32)D_800A5F88,
#if VERSION_US
    0x14A000B,
#elif VERSION_EU
    0x151000B,
#endif
    0, (s32)func_800A5AA0, 9000, 0,
    0, (s32)func_800A58F0, 0, 9001,
    0, 0, (s32)func_800A5954, 0,
    -1, 0, 0, 0,
    0,
};
