#include "common.h"
#include "stage.h"
void func_800A4E08();
extern AnimFrame D_800A5C24[];
extern AnimFrame D_800A5C0C[];
extern StageEffectSpot D_800A5BD0[];
StageEffect *func_800A5604(s32 x, s32 y, s32 frame);
extern void (*D_800A6118[])(void);

/* The files of the background, which the versions number differently */
#if VERSION_US
#define BG_ARCHIVE 0x767
#define BG_FILE 0x766
#define BG_FILE2 0x887
#elif VERSION_EU
#define BG_ARCHIVE 0x776
#define BG_FILE 0x775
#define BG_FILE2 0x898
#endif

/* Draws the two background images (file BG_ARCHIVE) scrolled at 2/3 of the layer's scroll */
void func_800A4CA4(StageTask *task) {
    SpriteDrawer drawer;
    Vec2 scroll;
    Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getScroll(layer, &scroll);
    scroll.x = (scroll.x << 8) / 384;
    scroll.y = (scroll.y << 8) / 384;
    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1002, 7);
    drawer.setTexture(0x280, 0);
    drawer.setAltClut(0, 0xF0);
    drawer.draw(FILE_CACHE.getEntry(BG_ARCHIVE << 16 | 2), 0, scroll.x, scroll.y);
    drawer.setTexture(0x280, 0x100);
    drawer.setAltClut(0, 0x1F0);
    drawer.draw(FILE_CACHE.getEntry(BG_ARCHIVE << 16 | 3), 0, scroll.x, scroll.y + 0x100);
}

/* Loads the background images (files BG_FILE and BG_FILE2) to VRAM, then draws them every frame */
void func_800A4E08(StageTask *task) {
    TimLoader loader;

    switch (task->state) {
    case TASK_INIT:
    default:
        initTimLoader(&loader);
        loader.setImagePos(0x280, 0);
        loader.setClutPos(0, 0xF0);
        loader.loadArchive(FILE_CACHE.load(BG_FILE));
        loader.setImagePos(0x280, 0x100);
        loader.setClutPos(0, 0x1F0);
        loader.loadArchive(FILE_CACHE.load(BG_FILE2));
        task->nextState(task);
        break;
    case TASK_RUN:
        func_800A4CA4(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A4F10(void) {
    return createTask(func_800A4E08, 0x60, 0);
}

/* Creates an object, the stage's five effects and the event object of flags 0x4072/0x40A9 */
void func_800A4F3C(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        children[0] = func_800A4F10();
        for (i = 0; i < 5; i++) {
            if (D_800A5BD0[i].kind == 0) {
                children[i + 1] = func_800A5604(D_800A5BD0[i].x, D_800A5BD0[i].y, D_800A5BD0[i].frame);
            }
        }
        if (FLAGS_00.checkCondition(0x4072, 1) && FLAGS_00.checkCondition(0x40A9, 0)) {
            children[6] = func_80084B80(0x411);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the stage task (id 0x17) and calls the first function of its table */
StageTask *func_800A5048(void *owner) {
    StageTask *task = createTaskWithId(func_800A4F3C, sizeof(StageTask), 0x1C, 0x17);

    task->owner = owner;
    D_800A6118[0]();
    return task;
}

s32 func_800A50A8(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
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
        func_800A50A8(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A51C8(StageEffect *task, void *arg, s32 idx) {
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

s32 func_800A52B0(s32 x, s32 y, s32 w, s32 h) {
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

void func_800A5374(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A5C24[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A5C0C[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A50A8(&task->clutAnim, D_800A5C0C, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A52B0(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A51C8, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A5C24[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A5C0C[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A50A8(&task->clutAnim, D_800A5C0C, 0, 0);
        done = 0;
        frame = func_800A50A8(&task->anim, D_800A5C24, 1, 0);
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
        if (task->sprites[0].frame != 0 && func_800A52B0(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A51C8, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A52B0(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A51C8, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A5604(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A5374, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

void func_800A5660(void) {
    FLAGS_00.applyAction(0x4070, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A56AC(void) {
    FLAGS_00.applyAction(0x4071, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A56F8(void) {
    FLAGS_00.applyAction(0x4072, 1);
}

void func_800A5724(void) {
    FLAGS_00.applyAction(0x40A9, 1);
}

void func_800A5750(void) {
    FLAGS_00.applyAction(0x4073, 1);
    FLAGS_00.applyAction(0x7401, 1);
}

extern s32 D_800A5F74[];
extern s32 D_800A6028[];
extern s32 D_800A5EA8[];
extern s32 D_800A5F68[];
extern s32 D_800A5E8C[];
extern s32 D_800A611C[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x767
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x776
#endif
void func_800A579C(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A5F74;
    D_800990B4.unk14 = D_800A6028;
    D_800990B4.unk1C = STAGE_FILE - 2;
    D_800990B4.unk2C = (Vec2){0x3D400, 0x33B00};
    D_800990B4.unk28 = D_800A5EA8;
    D_800990B4.unk3C = 0x1C;
    D_800990B4.unk40 = 0x60700000;
    D_800990B4.unk4C = D_800A5F68;
    D_800990B4.unk34 = 0;
    D_800990B4.unk20 = D_800A5E8C;
    D_800990B4.events = D_800A611C;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.setFile(7, STAGE_FILE << 16 | 4);
    D_8009A70C.unk50(0);
}

void func_800A579C();
extern s32 D_800A5C7C[];
extern s32 D_800A5C88[];
extern s32 D_800A5C94[];
extern s32 D_800A5CA0[];
extern s32 D_800A5CAC[];
extern s32 D_800A5CB8[];
extern s32 D_800A5CC4[];
extern s32 D_800A5CD0[];
extern s32 D_800A5D00[];
extern s32 D_800A5D0C[];
extern s32 D_800A5D18[];
extern s32 D_800A5D24[];
extern s32 D_800A5D30[];
extern s32 D_800A5D3C[];
extern s32 D_800A5D48[];
extern s32 D_800A5D54[];
extern s32 D_800A5D84[];
extern s32 D_800A5D90[];
extern s32 D_800A5D9C[];
extern s32 D_800A5DA8[];
extern s32 D_800A5DB4[];
extern s32 D_800A5DC0[];
extern s32 D_800A5DCC[];
extern s32 D_800A5DD8[];
extern s32 D_800A5E08[];
extern s32 D_800A5E14[];
extern s32 D_800A5E20[];
extern s32 D_800A5E2C[];
extern s32 D_800A5E38[];
extern s32 D_800A5E44[];
extern s32 D_800A5E50[];
extern s32 D_800A5E5C[];
extern s32 D_800A5CDC[];
extern s32 D_800A5D60[];
extern s32 D_800A5DE4[];
extern s32 D_800A5E68[];
extern s32 D_800A5F28[];
extern s32 D_800A5F34[];
extern s32 D_800A5F40[];
extern s32 D_800A5F54[];
extern s32 D_800A5890[];
extern s32 D_800A590C[];
extern s32 D_800A5988[];
extern s32 D_800A5AB4[];
extern s32 D_800A5AF8[];

s32 D_800A5890[] = {
    0x20102, 0x2CB0160, 0x1010003, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000003,
    0x101001E, 0x3250323, 0x30000D0, 0x101005A,
    0x3260323, 0x30000D0, 0x200001E, 0x10000,
    0x200D0, 0x3000301, 0x200001E, 0x20000,
    0x10002, 0x20101, 0x30007, 0x1010301,
    0x10002, 0x3000003, 0x102001E, 0x1500002,
    0x302C4, 0x20302, 0,
};
s32 D_800A590C[] = {
    0x20102, 0x10303D0, 0x1010003, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000003,
    0x101001E, 0x3250323, 0x3000002, 0x101005A,
    0x3260323, 0x30000D1, 0x200001E, 0x10000,
    0x200D1, 0x3000301, 0x200001E, 0x20000,
    0x10002, 0x20101, 0x30007, 0x1010301,
    0x10002, 0x3000003, 0x102001E, 0x3C00002,
    0x300FB, 0x20302, 0,
};
s32 D_800A5988[] = {
    0x20102, 0x1F9027D, 0x1010003, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x1010003,
    0x372032D, 0x3000002, 0x101001E, 0x3250323,
    0x3000002, 0x101005A, 0x3260323, 0x3000002,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000002, 0x101001E, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000000,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000000, 0x101001E, 0x3250323,
    0x3000002, 0x10100B4, 0x3260323, 0x3000002,
    0x101001E, 0x10002, 0x1010001, 0x373032D,
    0x3000002, 0x200001E, 0x10000, 0x20002,
    0x20101, 0x10007, 0x1010301, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x1010002,
    0x372032D, 0x3000002, 0x101001E, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000000,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x1010000, 0x373032D, 0x3040002,
#if VERSION_US
    0x27D0E08,
#elif VERSION_EU
    0x27D0E09,
#endif
    0x101F9, 0,
};
s32 D_800A5AB4[] = {
    0x20100, 0x1F9027D, 0x20101, 1,
    0x780300, 512, 0x20001, 0x1010000,
    0x70002, 0x3010000, 0x20101, 1,
    0x1E0300, 0x20101, 0x30001, 0x1E0300,
    0,
};
s32 D_800A5AF8[] = {
    0x20102, 0x119017D, 0x1010003, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x1010003,
    0x372032D, 0x3000002, 0x101001E, 0x3250323,
    0x3000002, 0x101005A, 0x3260323, 0x3000002,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000002, 0x101001E, 0x10002,
    0x3000001, 0x101001E, 0x10002, 0x3000000,
    0x101001E, 0x10002, 0x3000001, 0x101001E,
    0x10002, 0x3000000, 0x101001E, 0x3250323,
    0x3000002, 0x10100B4, 0x3260323, 0x3000002,
    0x101001E, 0x10002, 0x3000003, 0x200001E,
    0x10000, 0x20002, 0x20101, 0x30007,
    0x32D0101, 0x20373, 0x1010301, 0x10002,
    0x3000003, 30,
};
StageEffectSpot D_800A5BD0[] = {
    { 60, 0, 0x318, 166 },
    { 60, 0, 0x3F8, 0x116 },
    { 60, 0, 168, 0x26E },
    { 60, 0, 0x188, 0x2DE },
    { 44, 0, 0x3F8, 0x2C6 },
};
AnimFrame D_800A5C0C[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A5C24[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A5C7C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C88[] = {
    0, 0, 0x60040000,
};
s32 D_800A5C94[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CA0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CAC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CB8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CC4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CD0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5CDC[] = {
    0, (s32)D_800A5C7C, (s32)D_800A5C88, (s32)D_800A5C94,
    (s32)D_800A5CA0, (s32)D_800A5CAC, (s32)D_800A5CB8, (s32)D_800A5CC4,
    (s32)D_800A5CD0,
};
s32 D_800A5D00[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D0C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D18[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D24[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D30[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D3C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D48[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D54[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D60[] = {
    0, (s32)D_800A5D00, (s32)D_800A5D0C, (s32)D_800A5D18,
    (s32)D_800A5D24, (s32)D_800A5D30, (s32)D_800A5D3C, (s32)D_800A5D48,
    (s32)D_800A5D54,
};
s32 D_800A5D84[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D90[] = {
    0, 0, 0x60040000,
};
s32 D_800A5D9C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DA8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DB4[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DC0[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DCC[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DD8[] = {
    0, 0, 0x60040000,
};
s32 D_800A5DE4[] = {
    0, (s32)D_800A5D84, (s32)D_800A5D90, (s32)D_800A5D9C,
    (s32)D_800A5DA8, (s32)D_800A5DB4, (s32)D_800A5DC0, (s32)D_800A5DCC,
    (s32)D_800A5DD8,
};
s32 D_800A5E08[] = {
    194, 17, 0x60080000,
};
s32 D_800A5E14[] = {
    144, 17, 0x60080000,
};
s32 D_800A5E20[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E2C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E38[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E44[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E50[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E5C[] = {
    0, 0, 0x60040000,
};
s32 D_800A5E68[] = {
    0, (s32)D_800A5E08, (s32)D_800A5E14, (s32)D_800A5E20,
    (s32)D_800A5E2C, (s32)D_800A5E38, (s32)D_800A5E44, (s32)D_800A5E50,
    (s32)D_800A5E5C,
};
s32 D_800A5E8C[] = {
    125, 0, 0, (s32)D_800A5CDC,
    (s32)D_800A5D60, (s32)D_800A5DE4, (s32)D_800A5E68,
};
s32 D_800A5EA8[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x10001C0, 0x18201CD, 0x820234, 0x1FC0160,
    0x10001C0, 0x15A01CD, 0x5A0234, 0x1FC0170,
};
s32 D_800A5F28[] = {
    16496, 0x16028, 65535,
};
s32 D_800A5F34[] = {
    0x16028, 16497, 65535,
};
s32 D_800A5F40[] = {
    (s32)D_800A5F28, 0, 0x400D0, 0x2B3012E,
    7,
};
s32 D_800A5F54[] = {
    (s32)D_800A5F34, 0, 0x500D1, 0xEB039F,
    7,
};
s32 D_800A5F68[] = {
    (s32)D_800A5F40, (s32)D_800A5F54, 0,
};
s32 D_800A5F74[] = {
    0x2FF0001, 0, 0, 0,
    0x10000, 0x306F9, 0, 0x2830355,
    643, 0x6FF0001, 4, 0x7C0000,
    99, 0x10000, 0x106D6, 0,
    0xC30155, 0, 0x6D60001, 1,
    0x1D50000, 307, 0x10000, 0x106D6,
    0, 0x1A30255, 0, 0x6D60001,
    1, 0x2D50000, 531, 0x10000,
    0x206FF, 0, 0x269009C, 617,
    0x6FF0001, 2, 0x30C0000, 0xA100A1,
    0, 0, 0, 0,
    0,
};
s32 D_800A6028[] = {
    65535, 65535, 0x2DF0001, 0x2280310,
    3, 0, 65535, 65535,
    0x2DD000E, 0x2960504, 5, 0,
    65535, 65535, 0x2DD000E, 0xF60344,
    5, 0, 65535, 65535,
    0x2DD000E, 0x1AA029C, 1, 0,
    65535, 65535, 0x2DD000E, 0x14603E4,
    5, 0, 16496, 65535,
    0x3FC0008, 0, 0, 0,
    16497, 65535, 0x4060008, 0,
    0, 0, 16498, 65535,
    0x4100008, 0, 0, 0,
    16499, 65535, 0x41A0008, 0,
    0, 0, 65535, 65535,
    0, 0, 0, 0,
};
void (*D_800A6118[])(void) = {
    func_800A579C,
};
s32 D_800A611C[] = {
    1020, (s32)D_800A5890,
#if VERSION_US
    0x14A0009,
#elif VERSION_EU
    0x1510009,
#endif
    0, (s32)func_800A5660, 1030, (s32)D_800A590C,
#if VERSION_US
    0x14A000A,
#elif VERSION_EU
    0x151000A,
#endif
    0, (s32)func_800A56AC, 1040, (s32)D_800A5988,
#if VERSION_US
    0x14A000C,
#elif VERSION_EU
    0x151000C,
#endif
    0, (s32)func_800A56F8, 1041, (s32)D_800A5AB4,
#if VERSION_US
    0x14A000D,
#elif VERSION_EU
    0x151000D,
#endif
    0, (s32)func_800A5724, 1050, (s32)D_800A5AF8,
#if VERSION_US
    0x14A000E,
#elif VERSION_EU
    0x151000E,
#endif
    0, (s32)func_800A5750, -1, 0,
    0, 0, 0,
};
