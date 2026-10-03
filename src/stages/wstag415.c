#include "common.h"
#include "stage.h"
void func_800A541C();
void func_800A4E6C();
extern void (*D_800A6694[])(void);
void func_800A5DC0();
Task *func_800A5D84(s32 kind);
extern StageFallParams D_800A620C[];
void func_800A4DAC(StageFaller *task, Layer *layer);
void func_800A5B50();
extern AnimFrame D_800A62AC[];
extern AnimFrame D_800A62D4[];
extern AnimFrame D_800A62E4[];

/* The files of the background, which the versions number differently */
#if VERSION_US
#define BG_ARCHIVE 0x74E
#define BG_FILE 0x759
#elif VERSION_EU
#define BG_ARCHIVE 0x75E
#define BG_FILE 0x769
#endif

/* Steps the looping animation of a StageFallBody, returning its frame */
s32 func_800A4CB8(StageFallBody *body, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[body->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        body->anim.timer -= dt;
    }
    if (body->anim.timer <= 0) {
        frame++;
        body->anim.index++;
        body->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            frame = frames;
            body->anim.index = 0;
            body->anim.timer += frame->duration;
        }
        func_800A4CB8(body, frames, depth + 1);
    }
    return frame->frame;
}

/* Draws a StageFaller (a layer callback) */
void func_800A4DAC(StageFaller *task, Layer *layer) {
    SpriteDrawer drawer;

    if (task->state == TASK_RUN) {
        initSpriteDrawer(&drawer);
        drawer.setTexture(0x140, 0x100);
        drawer.setLayer(layer, 4);
        drawer.setClutRow(0);
        drawer.setAltClut(0, 0x1F0);
        drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), task->frame, task->x, task->y);
    }
}

/* Updates a StageFaller */
void func_800A4E6C(StageFaller *task) {
    Layer *layer = GFX.funcs.getLayer(0x1002);
    s32 dv;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->body.x = D_800A620C[task->key1].x << 8;
        task->body.y = D_800A620C[task->key1].y << 8;
        task->body.bounced = 0;
        task->body.vy = 0;
        task->body.vx = D_800A620C[task->key1].vx;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->frame = func_800A4CB8(&task->body, D_800A620C[task->key1].frames, 0);
        dv = D_800A620C[task->key1].gravity * GFX.funcs.getFrameTime();
        task->body.x += task->body.vx;
        task->body.vy += dv;
        task->x = task->body.x >> 8;
        task->body.y += task->body.vy;
        task->y = task->body.y >> 8;
        if (D_800A620C[task->key1].bounce != 0 && task->body.bounced == 0 && task->y >= D_800A620C[task->key1].floorY) {
            task->body.y = D_800A620C[task->key1].floorY << 8;
            task->y = D_800A620C[task->key1].floorY;
            task->body.vy = -(task->body.vy / D_800A620C[task->key1].bounce);
            task->body.vx = D_800A620C[task->key1].vx * 3;
            task->body.bounced = 1;
            SOUND.playSound(0x40012);
        }
        if (task->frame != 0) {
            layer->addSortedCallback(layer, func_800A4DAC, task, task->y, 0);
        }
        if (task->y > 0x244) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the task of func_800A4E6C with the given id, kind 0 */
Task *func_800A50F4(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 0;
    return task;
}

Task *func_800A5128(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 1;
    return task;
}

Task *func_800A5160(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 2;
    return task;
}

Task *func_800A5198(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 3;
    return task;
}

Task *func_800A51D0(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 4;
    return task;
}

Task *func_800A5208(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 5;
    return task;
}

Task *func_800A5240(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 6;
    return task;
}

Task *func_800A5278(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 7;
    return task;
}

Task *func_800A52B0(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 8;
    return task;
}

Task *func_800A52E8(s32 id) {
    Task *task = createTaskWithId(func_800A4E6C, 0x74, 0, id);

    task->key1 = 9;
    return task;
}

/* Steps the animation of a StageMoverBody, holding its last frame, and returns the frame */
s32 func_800A5320(StageMoverBody *body, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[body->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        body->anim.timer -= dt;
    }
    if (body->anim.timer <= 0) {
        frame++;
        body->anim.index++;
        body->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            frame--;
            body->anim.index--;
            body->anim.timer += frame->duration;
        }
        func_800A5320(body, frames, depth + 1);
    }
    return frame->frame;
}

/* Updates a StageMover: falls in mode 1 and plays an animation in modes 2 to 4 */
void func_800A541C(StageMover *task) {
    StageTile *tile;
    StageTile *rec;

    switch (task->state) {
    case TASK_INIT:
    default:
        if (task->key1 == 0) {
            task->body.x = 0x9600;
            task->body.y = 0xE600;
            task->body.mode = 0;
            task->body.vy = 0;
            task->body.vx = 0;
            task->body.timer = 0;
        } else {
            task->body.x = 0x9600;
            task->body.y = 0x1AE00;
            task->body.timer = 0;
            task->body.mode = 0;
            task->x = task->body.x >> 8;
            task->y = task->body.y >> 8;
        }
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 1) {
                task->tile = rec;
                rec->unkA = task->x;
                rec->unkA = task->y; /* unkA again */
                break;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->body.mode) {
        case 0:
            task->frame = 0x32;
            break;
        case 1:
            task->frame = 0x32;
            task->body.vy += GFX_FUNCS.getFrameTime() * 0x30;
            task->body.x += task->body.vx;
            task->body.y += task->body.vy;
            task->x = task->body.x >> 8;
            task->y = task->body.y >> 8;
            if (task->y >= 0x1AE) {
                task->body.y = 0x1AE00;
                task->y = 0x1AE;
                if (task->body.vy > 0x200) {
                    SOUND.playSound(0x8004474A);
                }
                task->body.vy = -(task->body.vy / 6);
            }
            task->body.timer++;
            break;
        case 2:
            task->frame = func_800A5320(&task->body, D_800A62AC, 0);
            if (task->frame == 0x35 && task->substate == 0) {
                SOUND.playSound(0x80044648);
                task->substate++;
            }
            if (task->frame == 0x3B && task->substate == 1) {
                SOUND.playSound(0x340001);
                task->substate++;
            }
            break;
        case 3:
            task->frame = func_800A5320(&task->body, D_800A62D4, 0);
            break;
        case 4:
            task->frame = func_800A5320(&task->body, D_800A62E4, 0);
            if (task->frame == 2 && task->substate == 0) {
                SOUND.playSound(0x340002);
                task->substate++;
            }
            if (task->frame == 0x20 && task->substate == 1) {
                SOUND.playSound(0x40012);
                task->substate++;
            }
            if (task->frame == 0x2A && task->substate == 2) {
                SOUND.playSound(0x40012);
                task->step = 0;
                task->substate++;
            }
            if (task->substate == 3 || task->substate == 4) {
                if ((++task->step & 0x1F) == 0) {
                    SOUND.playSound(0x40012);
                    task->step = 0;
                    task->substate++;
                }
            }
            break;
        }
        tile = task->tile;
        tile->frame = task->frame;
        tile->unkA = task->x;
        tile->unkC = task->y;
        tile->visible = 1;
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Handles the events 0x331 to 0x334 sent to a StageMover */
void func_800A5850(StageMover *task, s32 id) {
    if (task != NULL) {
        switch (id) {
        case 0x331:
            task->body.x = 0x9600;
            task->body.y = 0xE600;
            task->body.mode = 1;
            task->body.vy = 0;
            task->body.vx = 0;
            task->body.timer = 0;
            break;
        case 0x332:
            SOUND.playSound(0x800442C1);
            task->body.anim.index = 0;
            task->body.anim.timer = D_800A62AC[0].duration;
            task->body.mode = 2;
            task->substate = 0;
            break;
        case 0x333:
            SOUND.playSound(0x80044648);
            task->body.anim.index = 0;
            task->body.anim.timer = D_800A62D4[0].duration;
            task->body.mode = 3;
            break;
        case 0x334:
            task->body.mode = 4;
            task->body.anim.index = 0;
            task->body.anim.timer = D_800A62E4[0].duration;
            task->substate = 0;
            break;
        }
    }
}

/* Creates the task of func_800A541C with the given id, kind 0 */
Task *func_800A595C(s32 id) {
    Task *task = createTaskWithId(func_800A541C, 0x78, 0, id);

    task->key1 = 0;
    return task;
}

Task *func_800A5990(s32 id) {
    Task *task = createTaskWithId(func_800A541C, 0x78, 0, id);

    task->key1 = 1;
    return task;
}

/* Draws a StageScroller: each image twice, the second 0x200 left and 0x100 down */
void func_800A59C8(StageScroller *task) {
    SpriteDrawer drawer;
    s32 pos[2];

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1002, 7);
    drawer.setTexture(0x280, 0);
    drawer.setAltClut(0, 0xF0);
    pos[0] = task->x >> 8;
    pos[1] = (task->y >> 8) + 0x100;
    drawer.draw(FILE_CACHE.getEntry(BG_ARCHIVE << 16 | 2), 0, pos[0], pos[1]);
    drawer.draw(FILE_CACHE.getEntry(BG_ARCHIVE << 16 | 2), 0, pos[0] - 0x200, pos[1] + 0x100);
    drawer.setTexture(0x280, 0x100);
    drawer.setAltClut(0, 0xF8);
    pos[0] = (task->x >> 8) + 0x100;
    drawer.draw(FILE_CACHE.getEntry(BG_ARCHIVE << 16 | 4), 0, pos[0], pos[1]);
    drawer.draw(FILE_CACHE.getEntry(BG_ARCHIVE << 16 | 4), 0, pos[0] - 0x200, pos[1] + 0x100);
}

/* Loads the images of a StageScroller and scrolls it, slowing down to a stop in substate 1 */
void func_800A5B50(StageScroller *task) {
    TimLoader loader;

    switch (task->state) {
    case TASK_INIT:
    default:
        initTimLoader(&loader);
        loader.setImagePos(0x280, 0);
        loader.setClutPos(0, 0xF0);
        loader.loadArchive(FILE_CACHE.load(BG_FILE));
        loader.setImagePos(0x280, 0x100);
        loader.setClutPos(0, 0xF8);
        loader.loadArchive(FILE_CACHE.load(BG_FILE + 1));
        task->nextState(task);
        if (task->key1 != 0) {
            task->nextSubstate(task);
        }
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            task->vx = 0x800;
            task->vy = 0x400;
            break;
        case 1:
            if (task->vx == 0x800) {
                SOUND.playSound(0x340003);
            }
            if (task->vx != 0) {
                task->vx -= 0x10;
                task->vy = task->vx / 2;
                if (task->vx < 0) {
                    task->vx = 0;
                    task->vy = 0;
                }
            }
            break;
        }
        task->x += task->vx;
        task->y -= task->vy;
        if (task->x > 0x1FFFF) {
            task->x -= 0x20000;
            task->y += 0x10000;
        }
        func_800A59C8(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Sets the substate of the task to 1 when the id is 0x336 */
void func_800A5D4C(Task *task, s32 id) {
    if (task != NULL && id == 0x336) {
        task->setSubstate(task, 1);
    }
}

/* Creates the task of func_800A5B50 (id 0x32C) of the given kind */
Task *func_800A5D84(s32 kind) {
    Task *task = createTaskWithId(func_800A5B50, 0x60, 0, 0x32C);

    task->key1 = kind;
    return task;
}

/* Creates the event objects of progress 6, which depend on flag 0x4018 */
void func_800A5DC0(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        if (GAME_PROGRESS == 6) {
            if (FLAGS_00.checkCondition(0x4018, 0)) {
                children[0] = func_800A5D84(0);
                children[1] = func_80084B80(0x96);
            } else {
                children[0] = func_800A5D84(1);
                children[2] = func_800A5990(0x32B);
                children[1] = func_80084B80(0x97);
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5E84(void *owner) {
    StageTask *task = createTask(func_800A5DC0, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A6694[0]();
    return task;
}

void func_800A5EE0(void) {
    FLAGS_00.applyAction(0x4018, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

INCLUDE_ASM("stages/nonmatchings/wstag415", func_800A5F2C);

void func_800A5F2C();
extern AnimFrame D_800A61E4[];
extern AnimFrame D_800A61F8[];
extern s32 D_800A63A4[];
extern s32 D_800A63B0[];
extern s32 D_800A63BC[];
extern s32 D_800A63C8[];
extern s32 D_800A63D4[];
extern s32 D_800A63E0[];
extern s32 D_800A63EC[];
extern s32 D_800A63F8[];
extern s32 D_800A6428[];
extern s32 D_800A6434[];
extern s32 D_800A6440[];
extern s32 D_800A644C[];
extern s32 D_800A6458[];
extern s32 D_800A6464[];
extern s32 D_800A6470[];
extern s32 D_800A647C[];
extern s32 D_800A64AC[];
extern s32 D_800A64B8[];
extern s32 D_800A64C4[];
extern s32 D_800A64D0[];
extern s32 D_800A64DC[];
extern s32 D_800A64E8[];
extern s32 D_800A64F4[];
extern s32 D_800A6500[];
extern s32 D_800A6530[];
extern s32 D_800A653C[];
extern s32 D_800A6548[];
extern s32 D_800A6554[];
extern s32 D_800A6560[];
extern s32 D_800A656C[];
extern s32 D_800A6578[];
extern s32 D_800A6584[];
extern s32 D_800A6404[];
extern s32 D_800A6488[];
extern s32 D_800A650C[];
extern s32 D_800A6590[];
extern s32 D_800A6640[];
extern s32 D_800A5FE0[];
extern s32 D_800A615C[];

s32 D_800A5FE0[] = {
    0x10600, 0x1000001, 0x1140001, 0x1010157,
    0x10001, 0x1010001, 0x330032B, 0x3000001,
    0x10100B4, 0x336032C, 0x303032C, 0x300032C,
    0x101001E, 0x3250323, 0x3000001, 0x101003C,
    0x3260323, 0x3000001, 0x300001E, 0x101003C,
    0x3A0001, 0x3000001, 0x200003C, 0x10000,
    1, 0x1010301, 0x10001, 0x3000001,
    0x200001E, 0x20000, 0x40001, 0x32D0101,
    0x1037D, 0x1010301, 0x372032D, 0x3000001,
    0x200003C, 0x30000, 1, 0x10101,
    0x10033, 0x1010301, 0x10001, 0x3000001,
    0x601003C, 0xD80000, 0x3000175, 0x101003C,
    0x3350330, 0x3000330, 0x101005A, 0x3350331,
    0x1010331, 0x3350337, 0x3000337, 0x101003C,
    0x3350332, 0x1010332, 0x3350334, 0x1010334,
    0x3350336, 0x3000336, 0x101003C, 0x3350333,
    0x1010333, 0x3350339, 0x3000339, 0x101003C,
    0x3350335, 0x1010335, 0x3350338, 0x3000333,
    0x101003C, 0x331032B, 0x300032B, 0x3000078,
    0x101001E, 0x373032D, 0x3000001, 0x200000C,
    0x40000, 1, 0x10101, 0x10033,
    0x1010301, 0x10001, 0x3000001, 0x101001E,
    0x332032B, 0x300032B, 0x3000078, 0x1010078,
    0x333032B, 0x300032B, 12,
};
s32 D_800A615C[] = {
    0x10601, 0x17500D8, 0x10100, 0x1570114,
    0x10101, 0x10001, 0x32C0101, 0x10336,
    0x60300, 0x540300, 0x32B0101, 0x10334,
    0x9C0300, 1536, 0x3000001, 0x200001E,
    0x20000, 0x20001, 0x3000301, 0x2000078,
    0x10000, 0x40001, 0x32D0101, 0x1037D,
    0x1010301, 0x3250323, 0x3000001, 0x101003C,
    0x3260323, 0x3000001, 0x304003C, 0x1EF0232,
    0x100B9, 0,
};
AnimFrame D_800A61E4[] = {
    { 70, 8 }, { 71, 8 }, { 72, 8 }, { 73, 8 },
    { 255, 0 },
};
AnimFrame D_800A61F8[] = {
    { 74, 8 }, { 75, 8 }, { 76, 8 }, { 77, 8 },
    { 255, 0 },
};
StageFallParams D_800A620C[] = {
    { D_800A61E4, -0x20, 230, 0, 0x180, 88, 0 },
    { D_800A61F8, 0, 230, 0x1C2, 0x200, 72, 4 },
    { D_800A61E4, 32, 230, 0x19A, 0x180, 88, 8 },
    { D_800A61F8, 64, 230, 0, 0x200, 72, 0 },
    { D_800A61F8, 80, 230, 0, 0x200, 72, 0 },
    { D_800A61E4, 16, 230, 0, 96, 88, 0 },
    { D_800A61F8, 48, 230, 0x1CC, 128, 72, 4 },
    { D_800A61E4, 80, 230, 0x1A4, 96, 88, 8 },
    { D_800A61F8, 112, 230, 0, 128, 72, 0 },
    { D_800A61F8, 140, 230, 0, 128, 72, 0 },
};
AnimFrame D_800A62AC[] = {
    { 50, 5 }, { 52, 5 }, { 53, 5 }, { 54, 40 },
    { 55, 8 }, { 56, 8 }, { 57, 10 }, { 58, 12 },
    { 59, 180 }, { 255, 0 },
};
AnimFrame D_800A62D4[] = {
    { 60, 4 }, { 61, 4 }, { 62, 0x3E7 }, { 255, 0 },
};
AnimFrame D_800A62E4[] = {
    { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 8, 4 },
    { 9, 4 }, { 10, 4 }, { 11, 4 }, { 12, 4 },
    { 13, 4 }, { 14, 4 }, { 15, 4 }, { 16, 4 },
    { 17, 4 }, { 18, 4 }, { 19, 4 }, { 20, 4 },
    { 21, 4 }, { 22, 4 }, { 23, 4 }, { 24, 4 },
    { 25, 4 }, { 26, 4 }, { 27, 4 }, { 28, 4 },
    { 29, 4 }, { 30, 4 }, { 31, 4 }, { 32, 4 },
    { 33, 4 }, { 34, 4 }, { 35, 4 }, { 36, 4 },
    { 37, 4 }, { 38, 4 }, { 39, 4 }, { 40, 4 },
    { 41, 4 }, { 42, 4 }, { 43, 4 }, { 44, 4 },
    { 45, 4 }, { 46, 4 }, { 47, 4 }, { 255, 0x3E7 },
};
s32 D_800A63A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A63D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A63E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A63EC[] = {
    0, 0, 0x60040000,
};
s32 D_800A63F8[] = {
    0, 0, 0x60040000,
};
s32 D_800A6404[] = {
    0, (s32)D_800A63A4, (s32)D_800A63B0, (s32)D_800A63BC,
    (s32)D_800A63C8, (s32)D_800A63D4, (s32)D_800A63E0, (s32)D_800A63EC,
    (s32)D_800A63F8,
};
s32 D_800A6428[] = {
    0, 0, 0x60040000,
};
s32 D_800A6434[] = {
    0, 0, 0x60040000,
};
s32 D_800A6440[] = {
    0, 0, 0x60040000,
};
s32 D_800A644C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6458[] = {
    0, 0, 0x60040000,
};
s32 D_800A6464[] = {
    0, 0, 0x60040000,
};
s32 D_800A6470[] = {
    0, 0, 0x60040000,
};
s32 D_800A647C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6488[] = {
    0, (s32)D_800A6428, (s32)D_800A6434, (s32)D_800A6440,
    (s32)D_800A644C, (s32)D_800A6458, (s32)D_800A6464, (s32)D_800A6470,
    (s32)D_800A647C,
};
s32 D_800A64AC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64B8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A64D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A64DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A64E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A64F4[] = {
    0, 0, 0x60040000,
};
s32 D_800A6500[] = {
    0, 0, 0x60040000,
};
s32 D_800A650C[] = {
    0, (s32)D_800A64AC, (s32)D_800A64B8, (s32)D_800A64C4,
    (s32)D_800A64D0, (s32)D_800A64DC, (s32)D_800A64E8, (s32)D_800A64F4,
    (s32)D_800A6500,
};
s32 D_800A6530[] = {
    323, 10, 0x60880000,
};
s32 D_800A653C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6548[] = {
    0, 0, 0x60040000,
};
s32 D_800A6554[] = {
    0, 0, 0x60040000,
};
s32 D_800A6560[] = {
    0, 0, 0x60040000,
};
s32 D_800A656C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6578[] = {
    0, 0, 0x60040000,
};
s32 D_800A6584[] = {
    0, 0, 0x60040000,
};
s32 D_800A6590[] = {
    0, (s32)D_800A6530, (s32)D_800A653C, (s32)D_800A6548,
    (s32)D_800A6554, (s32)D_800A6560, (s32)D_800A656C, (s32)D_800A6578,
    (s32)D_800A6584,
};
s32 D_800A65B4[] = {
    128, 0, 0, (s32)D_800A6404,
    (s32)D_800A6488, (s32)D_800A650C, (s32)D_800A6590,
};
s32 D_800A65D0[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x10001C0, 0x15001CC, 0x500230, 0x1FF0160,
};
s32 D_800A6640[] = {
    0, 0, 0x40001, 0,
    7,
};
s32 D_800A6654[] = {
    (s32)D_800A6640, 0,
};
s32 D_800A665C[] = {
    0x66E0001, 0, 0xE10000, 318,
    0x1010000, 0x320494, 0, 0xFFCE0000,
    0, 0, 0, 0,
    0, 0,
};
void (*D_800A6694[])(void) = {
    func_800A5F2C,
};
s32 D_800A6698[] = {
    150, (s32)D_800A5FE0,
#if VERSION_US
    0x12E0004,
#elif VERSION_EU
    0x1350004,
#endif
    0, (s32)func_800A5EE0, 151, (s32)D_800A615C,
#if VERSION_US
    0x12E0005,
#elif VERSION_EU
    0x1350005,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
