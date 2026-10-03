#include "common.h"
#include "stage.h"
void func_800A5804();
void func_800A6174();
void func_800A508C();
void func_800A5668();
extern void (*D_800A80B4[])(void);
void func_800A6390();
extern u8 D_800A726C[];
extern s32 D_800A7274[2][2][2][2];
extern StageAnimSpot D_800A72CC[];
extern AnimFrame *D_800A73C4[];
void func_800A5A10(StageFlyerGate *task);
extern StageQuadTexture D_800A73CC[];
extern StageQuad D_800A78FC[];
extern u8 *D_800A7CC0[];

/* The file of the stage's sprites, which the versions number differently */
#if VERSION_US
#define SPRITES 0x1B7
#elif VERSION_EU
#define SPRITES 0x1C5
#endif

/* Draws the sprite at (x, y), flipped when it goes right */
void func_800A4CA4(StageFlyer *task) {
    SpriteDrawer drawer;
    s32 pos[2];

    initSpriteDrawer(&drawer);
    pos[0] = task->x >> 8;
    pos[1] = task->y >> 8;
    drawer.setLayerId(0x1002, 2);
    drawer.setTexture(0x140, 0x100);
    drawer.setAltClut(0, 0x1F0);
    drawer.setPivot(pos[0], pos[1]);
    if (task->right) {
        drawer.setScale(-0x1000, 0x1000, 0x1000);
    }
    drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), task->frame, pos[0], pos[1]);
}

/* Moves the sprite diagonally unless it is still, animates it and ends it off screen */
void func_800A4D84(StageFlyer *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        if (!task->still) {
            if (task->right) {
                task->x += 0x500;
            } else {
                task->x -= 0x500;
            }
            if (task->up) {
                task->y -= 0x280;
            } else {
                task->y += 0x280;
            }
        }
        task->timer += GFX_FUNCS.getFrameTime();
        if (task->timer >= 8) {
            task->timer = 0;
        }
        if (task->anim != 0 && task->still) {
            task->frame = 0x3B;
        } else {
            task->frame = D_800A726C[(task->timer >> 2) + task->up * 2 + task->anim * 4];
        }
        if (task->right) {
            if (task->x >= 0x28000) {
                task->setState(task, TASK_KILL);
            }
        } else if (task->x <= 0) {
            task->setState(task, TASK_KILL);
        }
        func_800A4CA4(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates a flyer at the start the direction and stillness pick */
void *func_800A4F20(s32 up, s32 right, s32 still, s32 anim) {
    StageFlyer *task = createTask(func_800A4D84, 0x70, 0);

    task->up = up;
    task->right = right;
    task->still = still;
    task->anim = anim;
    task->x = D_800A7274[up][right][still][0] << 8;
    task->y = D_800A7274[up][right][still][1] << 8;
    if (still && anim) {
        task->x += 0x3200;
        task->y -= 0x1900;
    }
    return task;
}

/* Draws the picture of file SPRITES with the frame of the level */
void func_800A4FF4(StageGlow *task) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1002, 7);
    drawer.setTexture(0x140, 0x100);
    drawer.setAltClut(0, 0x1F0);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), task->level >> 2, 0xDA, 0x47);
}

/* Raises the level with a sound, waits, lowers it and ends, drawing it */
void func_800A508C(StageGlow *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->level = 12;
        if (GAME_PROGRESS == 0x27) {
            SOUND.playSound(0x80A4203C);
        } else {
            SOUND.playSound(0xA40004);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            task->level += GFX_FUNCS.getFrameTime();
            if (task->level >= 0x1C) {
                task->level = 0x1C;
                task->nextSubstate(task);
            }
            break;
        case 1:
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step >= 0x8C) {
                task->nextSubstate(task);
            }
            break;
        case 2:
            task->level -= GFX_FUNCS.getFrameTime();
            if (task->level < 0xD) {
                task->level = 12;
                task->setState(task, TASK_KILL);
            }
            break;
        }
        func_800A4FF4(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A5220(s32 arg) {
    return createTaskWithId(func_800A508C, 0x54, 0, arg);
}

s32 func_800A5250(AnimState *anim, AnimFrame *frames, s32 depth) {
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
        func_800A5250(anim, frames, depth + 1);
    }
    return frame->frame;
}

/* Draws the sprite of the effect at (x, y) at depth 4 of LAYER while it runs */
void func_800A5344(StageEffect *task, void *arg) {
    SpriteDrawer drawer;
    Layer *layer = arg;

    if (task->state == TASK_RUN) {
        initSpriteDrawer(&drawer);
        drawer.setTexture(0x140, 0x100);
        drawer.setLayer(layer, 4);
        drawer.setClutRow(0);
        drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), task->frame, task->x, task->y);
    }
}

/* A looping sprite animation at the place key1 picks, started at a random point */
void func_800A53F0(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);

    switch (task->state) {
    case TASK_INIT:
    default:
        task->x = D_800A72CC[task->key1].x;
        task->y = D_800A72CC[task->key1].y;
        task->anim.index = RANDOM.next() & 1;
        task->anim.timer = RANDOM.next() % 3 + 2;
        task->frame = 0;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->frame = func_800A5250(&task->anim, D_800A72CC[task->key1].frames, 0);
        if (task->frame != 0) {
            layer->addSortedCallback(layer, func_800A5344, task, task->y, 0);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the task of func_800A53F0 with KEY as its key1 */
void *func_800A553C(s32 key) {
    Task *task = createTask(func_800A53F0, 0x60, 0);

    task->key1 = key;
    return task;
}

s32 func_800A5574(Anim4 *obj, AnimFrame *frames, s32 depth) {
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
            frame = frames;
            obj->anim.index = 0;
            obj->anim.timer += frame->duration;
        }
        func_800A5574(obj, frames, depth + 1);
    }
    return frame->frame;
}

/* Shows and loops the animations of the records with animations 1 and 2 */
void func_800A5668(StageTileLoop2 *task) {
    StageTile *t;
    StageTile *tile;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->tiles[0].anim.index = 0;
        task->tiles[0].anim.timer = D_800A73C4[0][0].duration;
        task->tiles[1].anim.index = 0;
        task->tiles[1].anim.timer = D_800A73C4[1][0].duration;
        for (t = D_800990B4.unk10; t->unk2 != 0; t++) {
            switch (t->anim) {
            case 1:
                task->tiles[0].tile = t;
                break;
            case 2:
                task->tiles[1].tile = t;
                break;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            tile = task->tiles[i].tile;
            tile->visible = 1;
            tile->frame = func_800A5574((Anim4 *)&task->tiles[i], D_800A73C4[i], 0);
            tile->unk9 = 0;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A57D8(void) {
    return createTask(func_800A5668, 0x60, 0);
}

/* Creates the six objects of func_800A53F0 (keys 0-5) and the object of func_800A5668 */
void func_800A5804(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (i = 0; i < 6; i++) {
            children[i] = func_800A553C(i);
        }
        children[6] = func_800A57D8();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void *func_800A589C(void) {
    return createTask(func_800A5804, 0x50, 0x1C);
}

/* Lets out the flyers of the sets that are on, where their children are free */
void func_800A58C8(StageFlyerGate *task, void **children) {
    s32 animA;
    s32 animB;

    if (task->spawnA) {
        animA = RANDOM.next() & 1;
        if (children[0] == NULL) {
            children[0] = func_800A4F20(0, 0, 0, animA);
        }
        if (children[3] == NULL) {
            children[3] = func_800A4F20(1, 1, 0, 0);
        }
    }
    if (task->spawnB) {
        animB = RANDOM.next() & 1;
        if (children[0] == NULL) {
            children[0] = func_800A4F20(0, 0, 1, 0);
        }
        if (children[3] == NULL) {
            children[3] = func_800A4F20(0, 0, 1, 1);
        }
        if (children[1] == NULL) {
            children[1] = func_800A4F20(1, 0, 0, 0);
        }
        if (children[2] == NULL) {
            children[2] = func_800A4F20(0, 1, 0, animB);
        }
    }
}

/* Draws the three pictures of the gate */
void func_800A5A10(StageFlyerGate *task) {
    SpriteDrawer drawer;

    initSpriteDrawer(&drawer);
    drawer.setLayerId(0x1002, 2);
    drawer.setTexture(0x140, 0x100);
    drawer.setAltClut(0, 0x1F0);
    drawer.setClutRow((GFX_FUNCS.getTime() >> 1) & 1);
    switch (task->left) {
    case 0:
    default:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x44, 0xC6, 0xB3);
        break;
    case 1:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x45, 0xC6, 0xBC);
        break;
    case 2:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x46, 0xC6, 0xC4);
        break;
    }
    switch (task->left) {
    case 0:
    default:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x44, 0x156, 0xFB);
        break;
    case 1:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x45, 0x156, 0x104);
        break;
    case 2:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x46, 0x156, 0x10C);
        break;
    }
    switch (task->right) {
    case 0:
    default:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x41, 0xEA, 0xB3);
        break;
    case 1:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x42, 0xEA, 0xBC);
        break;
    case 2:
        drawer.draw(FILE_CACHE_GET_ENTRY[0](SPRITES << 16), 0x43, 0xEA, 0xC4);
        break;
    }
}

/* Swaps the pictures every 0x79 frames, letting out the flyers */
void func_800A5C88(StageFlyerGate *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            task->left = 2;
            task->right = 0;
            task->spawnA = 1;
            task->spawnB = 0;
            break;
        case 1:
            if (task->left == 2) {
                task->left = 1;
            }
            if (task->right == 2) {
                task->right = 1;
            }
            task->step += GFX_FUNCS.getFrameTime();
            if (task->step >= 0x79) {
                if (task->left == 0) {
                    task->left = 2;
                }
                if (task->left == 1) {
                    task->left = 0;
                }
                if (task->right == 0) {
                    task->right = 2;
                }
                if (task->right == 1) {
                    task->right = 0;
                }
                task->nextSubstate(task);
            }
            task->spawnA = 0;
            task->spawnB = 0;
            break;
        case 2:
            task->spawnA = 0;
            task->spawnB = 1;
            break;
        }
        func_800A5A10(task);
        func_800A58C8(task, children);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Stops the object (substate 0) for map 0x324, starts it (substate 1) for 0x320 */
void func_800A5E04(Task *task, s32 id) {
    if (task != NULL) {
        switch (id) {
        case 0x324:
            task->setSubstate(task, 0);
            break;
        case 0x320:
            task->setSubstate(task, 1);
            break;
        }
    }
}

/* Creates the task of func_800A5C88 with id ARG */
void *func_800A5E50(s32 arg) {
    return createTaskWithId(func_800A5C88, 0x60, 0x10, arg);
}

/* Draws the 40 quads, those of kind 0 and 1 with the frames of the animations */
void func_800A5E80(StageByteAnims *task) {
    Layer *layer = GFX.funcs.getLayer(0x1002);
    u_long *ot = (u_long *)layer->getOtEntry(layer, 2);
    s32 scroll[2];
    POLY_FT4 *poly;
    StageQuadTexture *tex;
    StageQuad *quad;
    s32 size;
    s32 i;

    layer->getScroll(layer, scroll);
    poly = GFX.funcs.getPrim();
    for (i = 0; i < 40; i++) {
        quad = &D_800A78FC[i];
        switch (quad->kind) {
        case 0:
        case 1:
            tex = &D_800A73CC[task->anims[quad->kind].frame];
            break;
        default:
            tex = &D_800A73CC[quad->kind];
            break;
        }
        size = 0x28;
        if (quad->kind == 1) {
            size = 0x14;
        }
        setPolyFT4(poly);
        if (quad->kind >= 9) {
            setSemiTrans(poly, 1);
        }
        setRGB0(poly, 0x80, 0x80, 0x80);
        poly->x0 = quad->x0 - scroll[0];
        poly->x1 = quad->x1 - scroll[0];
        poly->x2 = quad->x2 - scroll[0];
        poly->x3 = quad->x3 - scroll[0];
        poly->y0 = quad->y0 - scroll[1];
        poly->y1 = quad->y1 - scroll[1];
        poly->y2 = quad->y2 - scroll[1];
        poly->y3 = quad->y3 - scroll[1];
        poly->u0 = tex->u;
        poly->u1 = tex->u + size;
        poly->u2 = tex->u;
        poly->u3 = tex->u + size;
        poly->v0 = tex->v;
        poly->v1 = tex->v;
        poly->v2 = tex->v + size;
        poly->v3 = tex->v + size;
        poly->tpage = getTPage(0, 0, tex->tpageX, tex->tpageY);
        poly->clut = getClut(tex->clutX, tex->clutY);
        addPrim(ot, poly);
        poly++;
    }
    GFX_FUNCS.setPrim(poly);
}

/* Plays its two byte-pair animations, restarting one when its animation changes, and draws */
void func_800A6174(StageByteAnims *task) {
    StageByteAnim *a;
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->anims[0].anim = 1;
        task->anims[0].cur = -1;
        task->anims[1].anim = 4;
        task->anims[1].cur = -1;
        break;
    case TASK_RUN:
        for (i = 0; i < 2; i++) {
            a = &task->anims[i];
            if (a->anim != a->cur) {
                a->cur = a->anim;
                a->index = 0;
                a->frame = 0;
                a->timer = 0;
            }
            a->timer -= GFX.funcs.getFrameTime();
            if (a->timer <= 0) {
                a->index++;
                if (D_800A7CC0[a->anim][a->index * 2 + 1] == 0) {
                    a->index = D_800A7CC0[a->anim][a->index * 2];
                }
                a->frame = D_800A7CC0[a->anim][a->index * 2];
                a->timer = D_800A7CC0[a->anim][a->index * 2 + 1];
            }
        }
        func_800A5E80(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Switches the animations to 2 and 5 with a sound for map 0x322 */
void func_800A6314(StageByteAnims *task, s32 id) {
    if (id == 0x322) {
        task->anims[0].anim = 2;
        task->anims[1].anim = 5;
        SOUND.playSound(0xA40006);
    }
}

void *func_800A6360(s32 arg) {
    return createTaskWithId(func_800A6174, 0x78, 0, arg);
}

/* Creates an object and the event object of the story progress */
void func_800A6390(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[1] = func_800A6360(0x321);
        do {
            if (GAME_PROGRESS == 0) {
                children[0] = func_80084B80(0);
                break;
            }
            if (GAME_PROGRESS == 0x17) {
                children[0] = func_80084B80(0x2AC);
                break;
            }
            if (GAME_PROGRESS == 0x1B) {
                children[0] = func_80084B80(0x2E6);
                children[2] = func_800A589C();
                break;
            }
            if (GAME_PROGRESS == 0x20) {
                children[0] = func_80084B80(0x375);
                break;
            }
            if (GAME_PROGRESS == 0x27) {
                children[0] = func_80084B80(0x3CB);
                break;
            }
            if (GAME_PROGRESS == 0x2B) {
                children[0] = func_80084B80(0x5DC);
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

StageTask *func_800A6474(void *owner) {
    StageTask *task = createTask(func_800A6390, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A80B4[0]();
    return task;
}

/* Sets the story progress to 0 */
void func_800A64D0(void) {
    GAME_PROGRESS = 0;
}

void func_800A64DC(void) {
    FLAGS_00.applyAction(0x4066, 1);
}

#if VERSION_EU
void func_800A7644(void) {
    GAME_PROGRESS = 45;
}
#endif

extern s32 D_800A8034[];
extern s32 D_800A7CDC[];
extern s32 D_800A7FEC[];
extern s32 D_800A80B8[];
#if VERSION_US
#define STAGE_TEXT 0xFE
#define STAGE_FILE 0x1B7
#define STAGE_ARCHIVE 0x311
#elif VERSION_EU
#define STAGE_TEXT (LANGUAGE + 0xF6)
#define STAGE_FILE 0x1C5
#define STAGE_ARCHIVE 0x320
#endif
void func_800A6508(void) {
    D_800990B4.unk44 = STAGE_TEXT;
    D_800990B4.unk8 = STAGE_FILE - 1;
    D_800990B4.unkC = STAGE_FILE << 16;
    D_800990B4.unk10 = D_800A8034;
    D_800990B4.unk1C = STAGE_ARCHIVE;
    D_800990B4.unk2C = (Vec2){0x1C700, 0x12C00};
    D_800990B4.unk28 = D_800A7CDC;
    D_800990B4.unk34 = 0;
    D_800990B4.unk3C = 0x29;
    D_800990B4.unk40 = 0x60A40000;
    D_800990B4.unk4C = D_800A7FEC;
    D_800990B4.events = D_800A80B8;
    D_8009A70C.setFile(0, STAGE_FILE << 16 | 1);
    D_8009A70C.unk50(0);
    switch (GAME_PROGRESS) {
    case 0x1B:
        D_800990B4.unk3C = 0x29;
        D_800990B4.unk40 = 0x60A40001;
        break;
    case 0x20:
        D_800990B4.unk3C = 0x29;
        D_800990B4.unk40 = 0x60A40002;
        break;
    case 0x27:
        D_800990B4.unk3C = 0x29;
        D_800990B4.unk40 = 0x60A40003;
        break;
    }
}

void func_800A6508();
void func_800A64D0();
extern AnimFrame D_800A72C0[];
extern AnimFrame D_800A72B4[];
extern AnimFrame D_800A731C[];
extern AnimFrame D_800A7374[];
extern u8 D_800A7BCC[];
extern u8 D_800A7BE8[];
extern u8 D_800A7BF8[];
extern u8 D_800A7C38[];
extern u8 D_800A7C54[];
extern u8 D_800A7C64[];
extern s32 D_800A7E40[];
extern s32 D_800A7E48[];
extern s32 D_800A7E50[];
extern s32 D_800A7E58[];
extern s32 D_800A7E60[];
extern s32 D_800A7E68[];
extern s32 D_800A7E1C[];
extern s32 D_800A7E70[];
extern s32 D_800A7E78[];
extern s32 D_800A7E80[];
extern s32 D_800A7E88[];
extern s32 D_800A7E90[];
extern s32 D_800A7E98[];
extern s32 D_800A7EAC[];
extern s32 D_800A7EC0[];
extern s32 D_800A7ED4[];
extern s32 D_800A7EE8[];
extern s32 D_800A7EFC[];
extern s32 D_800A7F10[];
extern s32 D_800A7F24[];
extern s32 D_800A7F38[];
extern s32 D_800A7F4C[];
extern s32 D_800A7F60[];
extern s32 D_800A7F74[];
extern s32 D_800A7F88[];
extern s32 D_800A7F9C[];
extern s32 D_800A7FB0[];
extern s32 D_800A7FC4[];
extern s32 D_800A7FD8[];
extern s32 D_800A6644[];
extern s32 D_800A69F8[];
extern s32 D_800A6B20[];
extern s32 D_800A6C58[];
extern s32 D_800A6CB0[];
extern s32 D_800A6EC0[];

s32 D_800A6644[] = {
    0x10600, 0x1000001, 0xB00001, 0x1010098,
    0x10001, 0x1000005, 0x1300010, 0x10100B0,
    0x10010, 0x1010007, 0x3240320, 0x1010001,
    0x3210321, 0x3000001, 0x1010078, 0x2A0001,
    0x3000005, 0x101003C, 0x2B0001, 0x3030005,
    0x1010001, 0x2A0001, 0x3000005, 0x200003C,
    0x10000, 0x20001, 0x10101, 0x5002A,
    0x1020301, 0xC00001, 0x10090, 0x10302,
    0x10101, 0x1002A, 0x780300, 512,
    0x10002, 0x3010000, 0x10101, 0x10039,
    0x3200101, 0x10320, 0x10303, 0x10101,
    0x1002A, 0x780300, 0x10101, 0x1002A,
    0x100102, 0x1E00280, 0x3000007, 0x1020168,
    0xD00001, 0x50088, 0x100100, 0,
    0x100101, 0x10001, 0x10302, 0x10101,
    0x5002E, 0x3210101, 0x10322, 0x10303,
    0x10101, 0x50001, 0x1E0300, 0x10101,
    0x60001, 0x1E0300, 0x10102, 0x980100,
    0x3020005, 0x2000001, 0x30000, 0x40001,
    0x10101, 0x50001, 0x1010301, 0x290001,
    0x1010001, 0x3210321, 0x3000001, 0x101003C,
    0x300001, 0x3030001, 0x1010001, 0x290001,
    0x3000001, 0x200003C, 0x40000, 0x20001,
    0x10101, 0x10029, 0x1010301, 0x300001,
    0x1010001, 0x3230322, 0x3000001, 0x101003C,
    0x290001, 0x1000001, 0xF0000B, 0x1020078,
    0xC0000B, 0x10090, 0xB0302, 0xB0101,
    0x60001, 0xC0100, 0x7800F0, 0xC0102,
    0x8400DA, 0x3020007, 0x101000C, 0x300001,
    0x1010001, 0x1000B, 0x1010006, 0x1000C,
    0x3000007, 0x200001E, 0x60001, 0x2000C,
    512, 0xB0005, 0x1010003, 0x10001,
    0x1010001, 0x7000B, 0x1010006, 0x7000C,
    0x3010007, 0x10101, 0x30001, 0xB0101,
    0x60001, 0xC0101, 0x70001, 0x1E0300,
    0x10101, 0x3000C, 0x3C0300, 512,
    0x10007, 0x1010002, 0xC0001, 0x3010003,
    0x10101, 0x30031, 0x10303, 0x10101,
    0x3000C, 0x3C0300, 512, 0x10008,
    0x1010002, 0xC0001, 0x3010002, 0x10101,
    0x20001, 0xB0102, 0x9800E0, 0x3020006,
    0x101000B, 0x10001, 0x1010002, 0x1000B,
    0x3000006, 0x200001E, 0x90000, 0x2000B,
    0xB0101, 0x60007, 0x1010301, 0xC0001,
    0x1010002, 0xC000B, 0x1010006, 0x34000C,
    0x3000000, 0x1010078, 0x35000C, 0x3000000,
    0x1010078, 0x1000C, 0x3000000, 0x101003C,
    0x9000C, 0x3030000, 0x101000C, 0x1000C,
    0x3000000, 0x102001E, 0xB0000C, 0x60098,
    0xC0302, 0xC0101, 0x60001, 0x1E0300,
    512, 0xC000A, 0x1010002, 0x7000C,
    0x3010006, 0x10101, 0x20001, 0xB0101,
    0x60001, 0xC0101, 0x60001, 0x3C0300,
    0x10101, 0x20009, 0xB0101, 0x60009,
    0xB0303, 0x10101, 0x20001, 0xB0101,
    0x60001, 0x1E0300, 0x10102, 0x1380250,
    0x1010007, 0x1000B, 0x3000007, 0x102001E,
    0x250000B, 0x70138, 0xC0102, 0x1380250,
    0x3000007, 0x304003C, 0x28002D8, 0x10100,
    0,
};
s32 D_800A69F8[] = {
    0x10601, 0x9000C0, 0x20100, 0,
    0x20101, 0x10001, 0x100100,
#if VERSION_US
    0xC00090,
#elif VERSION_EU
    0xC1012F,
#endif
    0x100101,
#if VERSION_US
    0x10001,
#elif VERSION_EU
    0x70001,
#endif
    0x2D0100, 0x8000D0, 0x2D0101, 0x30001,
    0x2F0100, 0x9800A0, 0x2F0101, 0x40001,
    0x310100, 0x990100, 0x310101, 0x50001,
    0x350100, 0x9400D8, 0x350101, 0x30001,
    0x380100,
#if VERSION_US
    0xB00070,
#elif VERSION_EU
    0xB00150,
#endif
    0x380101,
#if VERSION_US
    0x10001,
#elif VERSION_EU
    0x70001,
#endif
    0x3200101,
#if VERSION_US
    0x20320,
#elif VERSION_EU
    0x20324,
#endif
    0x3210101, 0x3210321, 0x780300, 0x3210101,
    0x20322, 0x1E0300, 512, 0x20001,
    0x3010004, 0x5A0300, 0x3210101, 0x3210321,
    0x3230101, 0x350325, 0x3240101, 0x2F0325,
    0x3250101, 0x2D0325, 0x5A0300, 0x3230101,
    0x2D0326, 0x3240101, 0x2F0326, 0x3250101,
    0x350326, 0x1E0300, 512, 0x2D0002,
    0x3010002, 0x120300, 512, 0x2F0003,
    0x3010000, 0x120300, 512, 0x350004,
    0x3010002, 0x120300, 0x120300, 0x2030304,
    0xC4014A, 1,
};
s32 D_800A6B20[] = {
    0x10601, 0xB000E0, 0x20100, 0,
    0x20101, 0x10001, 0x100100, 0xA000F0,
    0x100101, 0x70001, 0x2D0100, 0xC800B0,
    0x2D0101, 1, 0x2F0100, 0xAC0089,
    0x2F0101, 0x10001, 0x350100, 0x8800BF,
    0x350101, 1, 0x380100, 0xC0010F,
    0x380101, 0x70001, 0x3210101, 0x20321,
    0x780300, 0x3230101, 0x2D0325, 0x3240101,
    0x100325, 0x3250101, 0x380325, 0x5A0300,
    0x3230101, 0x2D0326, 0x3240101, 0x100326,
    0x3250101, 0x380326, 0x1E0300, 512,
    0x2D0001, 0x3010002, 0x120300, 512,
    0x100002, 0x3010000, 0x120300, 512,
    0x380003, 0x3010000, 0x120300, 0x380101,
    0x70001, 0x180300, 0x380101, 1,
    0x180300, 0x380101, 0x70001, 0x180300,
    0x380101, 0x60001, 0x180300, 0x380101,
    0x70001, 0x180300, 512, 0x380004,
    0x3010000, 0xC0300, 0x60300, 0x29C0304,
    0xDA0180, 1,
};
s32 D_800A6C58[] = {
    0x10601, 0xA000E0, 0x20100, 0,
    0x20101, 0x10001, 0x3210101, 0x3210321,
    0x780300, 0x1E0300, 0x3210101, 0x3210322,
    0x5A0300, 0x120300, 512, 0x20001,
    0x3010004, 0x120300, 0x120300, 0x26D0304,
    0xCA015E, 7,
};
s32 D_800A6CB0[] = {
    0x10601, 0xB000E0, 0x20100, 0,
    0x20101, 0x10001, 0x1100100, 0x1000010,
    0x1100101, 0x50001, 0x1110100, 0x800010,
    0x1110101, 0x70001, 0x1120100, 0x10001D0,
    0x1120101, 0x30001, 0x3210101, 0x3210321,
    0x780300, 0x1100102, 0xA800C0, 0x3020005,
    0x1010110, 0x10110, 0x1020000, 0xB00111,
    0x100D0, 0x1120102, 0x980100, 0x3020003,
    0x3000112, 0x1010012, 0x10110, 0x1010000,
    0x10111, 0x1010001, 0x10112, 0x3000007,
    0x1010012, 0x10110, 0x1010001, 0x10111,
    0x1010000, 0x10112, 0x3000000, 0x1010012,
    0x10110, 0x1010000, 0x10111, 0x1010001,
    0x10112, 0x3000007, 0x1010012, 0x10110,
    0x1010007, 0x10111, 0x1010002, 0x10112,
    0x3000006, 0x1010012, 0x10110, 0x1010000,
    0x10111, 0x1010001, 0x10112, 0x3000007,
    0x1010012, 0x3230322, 0x3000001, 0x100003C,
    0xF0009D, 0x1010078, 0x1009D, 0x3000001,
    0x102000C, 0xE7009D, 0x1007C, 0xC0300,
    0x3230101, 0x9D0325, 0x5A0300, 0x3230101,
    0x9D0326, 0x120300, 512, 0x9D0001,
    0x3010001, 0x9D0101, 0x50001, 0x120300,
    0x9D0102, 0x7800F0, 0x1010005, 0x3230322,
    0x3020002, 0x100009D, 157, 0x1010000,
    0x1009D, 0x1010001, 0x3250323, 0x1010110,
    0x3250324, 0x1010111, 0x3250325, 0x3000112,
    0x101005A, 0x10110, 0x1010001, 0x10111,
    0x1010001, 0x10112, 0x1010001, 0x3260323,
    0x1010110, 0x3260324, 0x1010111, 0x3260325,
    0x3000112, 0x1010012, 0x10110, 0x1010005,
    0x10111, 0x1010005, 0x10112, 0x3000003,
    0x3040012, 0x1000272, 0x501E0, 0,
};
s32 D_800A6EC0[] = {
    0x10600, 0x1000001, 0xB00001, 0x1010098,
    0x10001, 0x1000005, 0x1300010, 0x10100B0,
    0x10010, 0x1010007, 0x3240320, 0x1010001,
    0x3210321, 0x3000001, 0x1010078, 0x2A0001,
    0x3000005, 0x101003C, 0x2B0001, 0x3030005,
    0x1010001, 0x2A0001, 0x3000005, 0x200003C,
    0x10000, 0x20001, 0x10101, 0x5002A,
    0x1020301, 0xC00001, 0x10090, 0x10302,
    0x10101, 0x1002A, 0x780300, 512,
    0x10002, 0x3010000, 0x10101, 0x10039,
    0x3200101, 0x10320, 0x10303, 0x10101,
    0x10029, 0x780300, 0x10101, 0x1002A,
    0x100102, 0x1E00280, 0x3000000, 0x1020168,
    0xD00001, 0x50088, 0x100101, 0x10001,
    0x10302, 0x10101, 0x5002E, 0x3210101,
    0x10322, 0x10303, 0x10101, 0x50001,
    0x1E0300, 0x10101, 0x60001, 0x1E0300,
    0x10102, 0x980100, 0x3020005, 0x2000001,
    0x30000, 0x40001, 0x10101, 0x50001,
    0x1010301, 0x290001, 0x1010001, 0x3210321,
    0x3000001, 0x101003C, 0x300001, 0x3030001,
    0x1010001, 0x290001, 0x3000001, 0x200003C,
    0x40000, 0x20001, 0x10101, 0x10029,
    0x1010301, 0x300001, 0x1010001, 0x3230322,
    0x3000001, 0x101003C, 0x290001, 0x1000001,
    0xF0000B, 0x1020078, 0xC0000B, 0x10090,
    0xB0302, 0xB0101, 0x60001, 0xC0100,
    0x7800F0, 0xC0102, 0x8400DA, 0x3020007,
    0x101000C, 0x300001, 0x1010001, 0x1000B,
    0x1010006, 0x1000C, 0x3000007, 0x200001E,
    0x60001, 0x2000C, 512, 0xB0005,
    0x1010003, 0x10001, 0x1010001, 0x7000B,
    0x1010006, 0x7000C, 0x3010007, 0x10101,
    0x30001, 0xB0101, 0x60001, 0xC0101,
    0x70001, 0x1E0300, 0x10101, 0x3000C,
    0x3C0300, 512, 0x10007, 0x1010002,
    0xC0001, 0x3010003, 0x10101, 0x30031,
    0x10303, 0x10101, 0x3000C, 0x3C0300,
    512, 0x10008, 0x1010002, 0xC0001,
    0x3010002, 0x10101, 0x20001, 0xB0102,
    0x9800E0, 0x3020006, 0x101000B, 0x10001,
    0x1010002, 0x1000B, 0x3000006, 0x200001E,
    0x90000, 0x2000B, 0xB0101, 0x60007,
    0x1010301, 0xC0001, 0x1010002, 0xC000B,
    0x1010006, 0x34000C, 0x3000000, 0x1010078,
    0x35000C, 0x3000000, 0x1010078, 0x1000C,
    0x3000000, 0x101003C, 0x9000C, 0x3030000,
    0x101000C, 0x1000C, 0x3000000, 0x102001E,
    0xB0000C, 0x60098, 0xC0302, 0xC0101,
    0x60001, 0x1E0300, 512, 0xC000A,
    0x1010002, 0x7000C, 0x3010006, 0x10101,
    0x20001, 0xB0101, 0x60001, 0xC0101,
    0x60001, 0x3C0300, 0x10101, 0x20009,
    0xB0101, 0x60009, 0xB0303, 0x10101,
    0x20001, 0xB0101, 0x60001, 0x1E0300,
    0x10102, 0x1380250, 0x1010007, 0x1000B,
    0x3000007, 0x102001E, 0x250000B, 0x70138,
    0xC0102, 0x1380250, 0x3000007, 0x304003C,
#if VERSION_US
    3596,
#elif VERSION_EU
    3587,
#endif
#if VERSION_US
    0,
#elif VERSION_EU
    0x10000,
#endif
    0,
};
u8 D_800A726C[] = {
    50, 52, 53, 55, 56, 57, 56, 57,
};
s32 D_800A7274[2][2][2][2] = {
    { { { 640, 72 }, { 432, 176 } }, { { 0, 224 }, { 0, 0 } } },
    { { { 448, 392 }, { 0, 0 } }, { { 112, 392 }, { 0, 0 } } },
};
AnimFrame D_800A72B4[] = {
    { 50, 4 }, { 51, 4 }, { 255, 0 },
};
AnimFrame D_800A72C0[] = {
    { 53, 4 }, { 54, 4 }, { 255, 0 },
};
StageAnimSpot D_800A72CC[] = {
    { D_800A72C0, 20, 130 },
    { D_800A72C0, 80, 180 },
    { D_800A72C0, 120, 230 },
    { D_800A72C0, 170, 0x118 },
    { D_800A72B4, 0x15E, 210 },
    { D_800A72B4, 0x12C, 240 },
    { NULL, 0, 0 },
    { NULL, 0, 0 },
    { NULL, 0, 0 },
    { NULL, 0, 0 },
};
AnimFrame D_800A731C[] = {
    { 10, 12 }, { 11, 12 }, { 12, 12 }, { 13, 12 },
    { 14, 12 }, { 15, 20 }, { 16, 4 }, { 17, 4 },
    { 15, 4 }, { 13, 4 }, { 18, 4 }, { 11, 4 },
    { 13, 4 }, { 15, 4 }, { 13, 4 }, { 16, 4 },
    { 16, 4 }, { 15, 4 }, { 18, 4 }, { 17, 4 },
    { 11, 4 }, { 255, 0 },
};
AnimFrame D_800A7374[] = {
    { 18, 12 }, { 19, 12 }, { 20, 12 }, { 21, 12 },
    { 22, 12 }, { 23, 20 }, { 24, 4 }, { 25, 4 },
    { 22, 4 }, { 19, 4 }, { 21, 4 }, { 18, 4 },
    { 23, 4 }, { 20, 4 }, { 19, 4 }, { 25, 4 },
    { 22, 4 }, { 19, 4 }, { 18, 4 }, { 255, 0 },
};
AnimFrame *D_800A73C4[] = {
    D_800A731C, D_800A7374,
};
StageQuadTexture D_800A73CC[] = {
    { 0x180, 0x100, 0x1B2, 0x130, 0x1C8, 48, 0x170, 0x1DE },
    { 0x180, 0x100, 0x180, 0x14C, 0x100, 76, 0x170, 0x1DE },
    { 0x180, 0x100, 0x18A, 0x14C, 0x128, 76, 0x170, 0x1DE },
    { 0x180, 0x100, 0x194, 0x158, 0x150, 88, 0x170, 0x1DE },
    { 0x180, 0x100, 0x19E, 0x158, 0x178, 88, 0x170, 0x1DE },
    { 0x180, 0x100, 0x1A8, 0x158, 0x1A0, 88, 0x170, 0x1DE },
    { 0x180, 0x100, 0x1B2, 0x158, 0x1C8, 88, 0x170, 0x1DE },
    { 0x180, 0x100, 0x180, 0x174, 0x100, 116, 0x170, 0x1DE },
    { 0x180, 0x100, 0x18A, 0x174, 0x128, 116, 0x170, 0x1DE },
    { 0x180, 0x100, 0x194, 0x180, 0x150, 128, 0x170, 0x1DE },
    { 0x180, 0x100, 0x19E, 0x180, 0x178, 128, 0x170, 0x1DE },
    { 0x180, 0x100, 0x1A8, 0x180, 0x1A0, 128, 0x170, 0x1DE },
    { 0x180, 0x100, 0x1B2, 0x180, 0x1C8, 128, 0x170, 0x1DD },
    { 0x180, 0x100, 0x180, 0x19C, 0x100, 156, 0x170, 0x1DD },
    { 0x180, 0x100, 0x18A, 0x19C, 0x128, 156, 0x170, 0x1DD },
    { 0x180, 0x100, 0x194, 0x1A8, 0x150, 168, 0x170, 0x1DD },
    { 0x180, 0x100, 0x19E, 0x1A8, 0x178, 168, 0x170, 0x1DD },
    { 0x180, 0x100, 0x1A8, 0x1A8, 0x1A0, 168, 0x170, 0x1DD },
    { 0x180, 0x100, 0x1B2, 0x1A8, 0x1C8, 168, 0x170, 0x1DD },
    { 0x180, 0x100, 0x180, 0x1C4, 0x100, 196, 0x170, 0x1DD },
    { 0x180, 0x100, 0x18A, 0x1C4, 0x128, 196, 0x170, 0x1DD },
    { 0x180, 0x100, 0x194, 0x1D0, 0x150, 208, 0x170, 0x1DD },
    { 0x180, 0x100, 0x19E, 0x1D0, 0x178, 208, 0x170, 0x1DD },
    { 0x180, 0x100, 0x1A8, 0x1D0, 0x1A0, 208, 0x170, 0x1DD },
    { 0x180, 0x100, 0x1B2, 0x1D0, 0x1C8, 208, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1C0, 0x100, 0x200, 0, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1CA, 0x100, 0x228, 0, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1D4, 0x100, 0x250, 0, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1DE, 0x100, 0x278, 0, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1E8, 0x100, 0x2A0, 0, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1F2, 0x100, 0x2C8, 0, 0x170, 0x1DB },
    { 0x1C0, 0x100, 0x1C0, 0x128, 0x200, 40, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1CA, 0x128, 0x228, 40, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1D4, 0x128, 0x250, 40, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1DE, 0x128, 0x278, 40, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1E8, 0x128, 0x2A0, 40, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1F2, 0x128, 0x2C8, 40, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1C0, 0x150, 0x200, 80, 0x170, 0x1DA },
    { 0x140, 0x100, 0x16A, 0x1D8, 168, 216, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1FA, 0x150, 0x2E8, 80, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1FA, 0x164, 0x2E8, 100, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1DE, 0x178, 0x278, 120, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1E3, 0x178, 0x28C, 120, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1FA, 0x178, 0x2E8, 120, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1DE, 0x18C, 0x278, 140, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1E3, 0x18C, 0x28C, 140, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1FA, 0x18C, 0x2E8, 140, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1E8, 0x190, 0x2A0, 144, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1ED, 0x190, 0x2B4, 144, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1F2, 0x190, 0x2C8, 144, 0x170, 0x1DE },
    { 0x1C0, 0x100, 0x1D0, 0x194, 0x240, 148, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1D5, 0x194, 0x254, 148, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1C0, 0x198, 0x200, 152, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1C5, 0x198, 0x214, 152, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1CA, 0x198, 0x228, 152, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1DA, 0x1A0, 0x268, 160, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1DF, 0x1A0, 0x27C, 160, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1F7, 0x1A0, 0x2DC, 160, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1E4, 0x1A4, 0x290, 164, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1E9, 0x1A4, 0x2A4, 164, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1EE, 0x1A4, 0x2B8, 164, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1CF, 0x1A8, 0x23C, 168, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1D4, 0x1A8, 0x250, 168, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1C0, 0x1AC, 0x200, 172, 0x170, 0x1DD },
    { 0x1C0, 0x100, 0x1C5, 0x1AC, 0x214, 172, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1CA, 0x1AC, 0x228, 172, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1D9, 0x1B4, 0x264, 180, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1DE, 0x1B4, 0x278, 180, 0x170, 0x1DC },
    { 0x1C0, 0x100, 0x1F3, 0x1B4, 0x2CC, 180, 0x170, 0x1DB },
    { 0x1C0, 0x100, 0x1F8, 0x1B4, 0x2E0, 180, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1E3, 0x1B8, 0x28C, 184, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1E8, 0x1B8, 0x2A0, 184, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1ED, 0x1B8, 0x2B4, 184, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1CF, 0x1BC, 0x23C, 188, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1D4, 0x1BC, 0x250, 188, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1C0, 0x1C0, 0x200, 192, 0x170, 0x1DA },
    { 0x1C0, 0x100, 0x1C5, 0x1C0, 0x214, 192, 0x170, 0x1D9 },
    { 0x1C0, 0x100, 0x1CA, 0x1C0, 0x228, 192, 0x170, 0x1D9 },
    { 0x1C0, 0x100, 0x1D9, 0x1C8, 0x264, 200, 0x170, 0x1D9 },
    { 0x1C0, 0x100, 0x1DE, 0x1C8, 0x278, 200, 0x170, 0x1D9 },
    { 0x180, 0x100, 0x1A0, 0x100, 0x180, 0, 0x170, 0x1F6 },
    { 0x180, 0x100, 0x194, 0x100, 0x150, 0, 0x170, 0x1F6 },
    { 0x1C0, 0x100, 0x1D7, 0x178, 0x25C, 120, 0x170, 0x1F4 },
};
StageQuad D_800A78FC[] = {
    { 121, 76, 168, 53, 121, 123, 168, 100, 80 },
    { 121, 77, 160, 58, 121, 116, 160, 97, 0 },
#if VERSION_US
    { 0x111, 94, 0x130, 109, 0x111, 125, 0x130, 140, 81 },
#elif VERSION_EU
    { 0x110, 92, 0x131, 108, 0x110, 123, 0x131, 139, 81 },
#endif
    { 0x115, 96, 0x130, 109, 0x115, 122, 0x130, 135, 0 },
#if VERSION_US
    { 27, 56, 54, 69, 27, 83, 54, 96, 81 },
#elif VERSION_EU
    { 29, 53, 56, 66, 29, 81, 56, 94, 81 },
#endif
    { 33, 59, 54, 69, 33, 81, 54, 91, 0 },
#if VERSION_US
    { 58, 72, 85, 85, 58, 99, 85, 112, 81 },
#elif VERSION_EU
    { 60, 68, 87, 81, 60, 97, 87, 110, 81 },
#endif
    { 64, 74, 85, 84, 64, 96, 85, 106, 0 },
#if VERSION_US
    { 58, 103, 85, 116, 58, 130, 85, 143, 81 },
#elif VERSION_EU
    { 60, 99, 87, 112, 60, 128, 87, 141, 81 },
#endif
    { 64, 105, 85, 115, 64, 127, 85, 137, 0 },
#if VERSION_US
    { 27, 87, 54, 100, 27, 114, 54, 127, 81 },
#elif VERSION_EU
    { 29, 84, 56, 97, 29, 112, 56, 125, 81 },
#endif
    { 33, 90, 54, 100, 33, 112, 54, 122, 0 },
    { 0x14F, 109, 0x15F, 101, 0x14F, 123, 0x15F, 115, 82 },
    { 0x14F, 109, 0x15B, 103, 0x14F, 119, 0x15B, 113, 1 },
    { 0x15F, 101, 0x16F, 93, 0x15F, 115, 0x16F, 107, 82 },
    { 0x15F, 101, 0x16B, 95, 0x15F, 111, 0x16B, 105, 1 },
    { 0x16F, 93, 0x17F, 85, 0x16F, 107, 0x17F, 99, 82 },
    { 0x16F, 93, 0x17B, 87, 0x16F, 103, 0x17B, 97, 1 },
    { 0x17F, 85, 0x18F, 77, 0x17F, 99, 0x18F, 91, 82 },
    { 0x17F, 85, 0x18B, 79, 0x17F, 95, 0x18B, 89, 1 },
    { 0x14F, 125, 0x15F, 117, 0x14F, 139, 0x15F, 131, 82 },
    { 0x14F, 125, 0x15B, 119, 0x14F, 135, 0x15B, 129, 1 },
    { 0x15F, 117, 0x16F, 109, 0x15F, 131, 0x16F, 123, 82 },
    { 0x15F, 117, 0x16B, 111, 0x15F, 127, 0x16B, 121, 1 },
    { 0x16F, 109, 0x17F, 101, 0x16F, 123, 0x17F, 115, 82 },
    { 0x16F, 109, 0x17B, 103, 0x16F, 119, 0x17B, 113, 1 },
    { 0x17F, 101, 0x18F, 93, 0x17F, 115, 0x18F, 107, 82 },
    { 0x17F, 101, 0x18B, 95, 0x17F, 111, 0x18B, 105, 1 },
    { 148, 91, 164, 83, 148, 105, 164, 97, 82 },
    { 148, 91, 160, 85, 148, 101, 160, 95, 1 },
    { 164, 83, 180, 75, 164, 97, 180, 89, 82 },
    { 164, 83, 176, 77, 164, 93, 176, 87, 1 },
    { 180, 75, 196, 67, 180, 89, 196, 81, 82 },
    { 180, 75, 192, 69, 180, 85, 192, 79, 1 },
    { 148, 107, 164, 99, 148, 121, 164, 113, 82 },
    { 148, 107, 160, 101, 148, 117, 160, 111, 1 },
    { 164, 99, 180, 91, 164, 113, 180, 105, 82 },
    { 164, 99, 176, 93, 164, 109, 176, 103, 1 },
    { 180, 91, 196, 83, 180, 105, 196, 97, 82 },
    { 180, 91, 192, 85, 180, 101, 192, 95, 1 },
};
u8 D_800A7BCC[] = {
    0, 4, 1, 4, 2, 4, 3, 4,
    4, 4, 5, 4, 6, 4, 7, 4,
    8, 4, 9, 4, 10, 4, 11, 4,
    0, 0, 0, 0,
};
u8 D_800A7BE8[] = {
    31, 8, 32, 8, 33, 8, 34, 8,
    35, 8, 36, 8, 37, 8, 0, 0,
};
u8 D_800A7BF8[] = {
    12, 10, 13, 4, 14, 4, 15, 4,
    16, 4, 17, 4, 18, 4, 19, 8,
    20, 8, 19, 8, 20, 8, 19, 8,
    20, 8, 19, 4, 21, 8, 22, 4,
    23, 4, 24, 4, 25, 4, 26, 26,
    26, 26, 27, 26, 26, 12, 28, 12,
    29, 12, 29, 12, 30, 12, 29, 12,
    28, 12, 26, 12, 19, 0, 0, 0,
};
u8 D_800A7C38[] = {
    38, 4, 39, 4, 40, 4, 41, 4,
    42, 4, 43, 4, 44, 4, 45, 4,
    46, 4, 47, 4, 48, 4, 49, 4,
    0, 0, 0, 0,
};
u8 D_800A7C54[] = {
    69, 4, 70, 4, 71, 4, 72, 4,
    73, 4, 74, 4, 75, 4, 0, 0,
};
u8 D_800A7C64[] = {
    50, 10, 51, 4, 52, 4, 53, 4,
    54, 4, 55, 4, 56, 4, 57, 8,
    58, 8, 57, 8, 58, 8, 57, 8,
    58, 8, 57, 4, 59, 8, 60, 4,
    61, 4, 62, 4, 63, 4, 64, 26,
    64, 26, 65, 26, 64, 12, 66, 12,
    67, 12, 67, 12, 68, 12, 67, 12,
    66, 12, 64, 12, 76, 120, 77, 120,
    64, 26, 64, 26, 65, 26, 64, 12,
    66, 12, 67, 12, 67, 12, 68, 12,
    67, 12, 66, 12, 64, 12, 78, 120,
    79, 120, 19, 0,
};
u8 *D_800A7CC0[] = {
    D_800A7BCC,
    D_800A7BE8,
    D_800A7BF8,
    D_800A7C38,
    D_800A7C54,
    D_800A7C64,
    NULL,
};
s32 D_800A7CDC[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1B40176, 0xB400D8, 0x1EC0170,
    0x1000140, 0x1D80162, 0xD80088, 0x1EB0170,
    0x10001C0, 0x15001EA, 0x5002A8, 0x1EA0170,
    0x1000180, 0x10001B6, 472, 0x1E90170,
    0x1000140, 0x18A014E, 0x8A0038, 0x1E80170,
    0x10001C0, 0x15001CA, 0x500228, 0x1E70170,
    0x10001C0, 0x15001D2, 0x500248, 0x1E60170,
    0x10001C0, 0x15001DA, 0x500268, 0x1E50170,
    0x10001C0, 0x15001E2, 0x500288, 0x1E40170,
    0x10001C0, 0x15001F2, 0x5002C8, 0x1E30170,
    0x10001C0, 0x17001EA, 0x7002A8, 0x1E20170,
    0x10001C0, 0x17001F2, 0x7002C8, 0x1E10170,
    0x10001C0, 0x17801C0, 0x780200, 0x1E00170,
    0x10001C0, 0x17801C8, 0x780220, 0x1DF0170,
};
s32 D_800A7E1C[] = {
    0, 0, 1, 0,
    0, 1, 0, 0,
    0,
};
s32 D_800A7E40[] = {
    0x16000, 65535,
};
s32 D_800A7E48[] = {
    0x1602B, 65535,
};
s32 D_800A7E50[] = {
    0x16000, 65535,
};
s32 D_800A7E58[] = {
    0x1602B, 65535,
};
s32 D_800A7E60[] = {
    0x16000, 65535,
};
s32 D_800A7E68[] = {
    0x1602B, 65535,
};
s32 D_800A7E70[] = {
    0x16027, 65535,
};
s32 D_800A7E78[] = {
    0x16027, 65535,
};
s32 D_800A7E80[] = {
    0x16027, 65535,
};
s32 D_800A7E88[] = {
    0x16027, 65535,
};
s32 D_800A7E90[] = {
    0x16027, 65535,
};
s32 D_800A7E98[] = {
    (s32)D_800A7E40, 0, 0x40001, 0,
    1,
};
s32 D_800A7EAC[] = {
    (s32)D_800A7E48, 0, 0x40001, 0,
    1,
};
s32 D_800A7EC0[] = {
    (s32)D_800A7E50, 0, 0x5000B, 0,
    1,
};
s32 D_800A7ED4[] = {
    (s32)D_800A7E58, 0, 0x5000B, 0,
    1,
};
s32 D_800A7EE8[] = {
    (s32)D_800A7E60, 0, 0x6000C, 0,
    1,
};
s32 D_800A7EFC[] = {
    (s32)D_800A7E68, 0, 0x6000C, 0,
    1,
};
s32 D_800A7F10[] = {
    0, (s32)D_800A7E1C, 0x70010, 0,
    1,
};
s32 D_800A7F24[] = {
    0, 0, 0x8002D, 0,
    1,
};
s32 D_800A7F38[] = {
    0, 0, 0x9002F, 0,
    1,
};
s32 D_800A7F4C[] = {
    0, 0, 0xA0031, 0,
    1,
};
s32 D_800A7F60[] = {
    0, 0, 0xB0035, 0,
    1,
};
s32 D_800A7F74[] = {
    0, 0, 0xC0038, 0,
    1,
};
s32 D_800A7F88[] = {
    (s32)D_800A7E70, 0, 0xD009D, 0,
    1,
};
s32 D_800A7F9C[] = {
    (s32)D_800A7E78, 0, 0xE009E, 0,
    1,
};
s32 D_800A7FB0[] = {
    (s32)D_800A7E80, 0, 0xF0110, 0,
    1,
};
s32 D_800A7FC4[] = {
    (s32)D_800A7E88, 0, 0x100111, 0,
    1,
};
s32 D_800A7FD8[] = {
    (s32)D_800A7E90, 0, 0x110112, 0,
    1,
};
s32 D_800A7FEC[] = {
    (s32)D_800A7E98, (s32)D_800A7EAC, (s32)D_800A7EC0, (s32)D_800A7ED4,
    (s32)D_800A7EE8, (s32)D_800A7EFC, (s32)D_800A7F10, (s32)D_800A7F24,
    (s32)D_800A7F38, (s32)D_800A7F4C, (s32)D_800A7F60, (s32)D_800A7F74,
    (s32)D_800A7F88, (s32)D_800A7F9C, (s32)D_800A7FB0, (s32)D_800A7FC4,
    (s32)D_800A7FD8, 0,
};
s32 D_800A8034[] = {
    0x2400100, 10, 0xC60000, 179,
    0x2000000, 0x120240, 0, 0xFB0156,
    0, 0x6800000, 50, 0x16B0000,
    206, 0, 0x350680, 0,
    0xEB0088, 0, 0x4400001, 1,
    0xBE0000, 0xE7009C, 0x10000, 0x20440,
    0, 0xE5015A, 303, 0,
    0, 0, 0, 0,
};
void (*D_800A80B4[])(void) = {
    func_800A6508,
};
s32 D_800A80B8[] = {
    0, (s32)D_800A6644,
#if VERSION_US
    0x1430000,
#elif VERSION_EU
    0x14A0000,
#endif
    0, (s32)func_800A64D0, 684, (s32)D_800A69F8,
#if VERSION_US
    0x1430020,
#elif VERSION_EU
    0x14A0020,
#endif
    0, 0, 742, (s32)D_800A6B20,
#if VERSION_US
    0x1430021,
#elif VERSION_EU
    0x14A0021,
#endif
    0, 0, 885, (s32)D_800A6C58,
#if VERSION_US
    0x1430022,
#elif VERSION_EU
    0x14A0022,
#endif
    0, (s32)func_800A64DC, 971, (s32)D_800A6CB0,
#if VERSION_US
    0x1430023,
#elif VERSION_EU
    0x14A0023,
#endif
    0, 0, 1500, (s32)D_800A6EC0,
#if VERSION_US
    0x1430024,
#elif VERSION_EU
    0x14A0024,
#endif
    0,
#if VERSION_US
    0,
#elif VERSION_EU
    (s32)func_800A7644,
#endif
    -1, 0, 0, 0,
    0,
};
