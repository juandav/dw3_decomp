#include "game.h"

/* Small variables, addressed through $gp (see the Makefile) */
static s32 GFX_STARTED;
static s32 FLIP_PENDING;
static CardDrawer *CARD_DRAWER;
static SpriteDrawer *SPRITE_DRAWER;
static TextTools *TEXT_TOOLS;
static TimLoader *TIM_LOADER;

void vsyncCallback(void) {
#if VERSION_US
    GFX.timeCounter += 0x100;
    GFX.frameTimeCounter += 0x100;
    GAME.playFrames += 0x100;
#elif VERSION_EU
    if (NTSC_MODE) {
        GFX.timeCounter += 0x100;
        GFX.frameTimeCounter += 0x100;
        GAME.playFrames += 0x100;
    } else {
        GFX.timeCounter += 0x133;
        GFX.frameTimeCounter += 0x133;
        GAME.playFrames += 0x133;
    }
#endif
    if (GFX.vsyncFunc != NULL) {
        GFX.vsyncFunc(GFX.vsyncArg);
    }
    if (FLIP_PENDING != 0) {
        GFX.dispBuffer = !GFX.dispBuffer;
        PutDispEnv(&GFX.disp[GFX.dispBuffer]);
    }
    SsSeqCalledTbyT();
    FLIP_PENDING = 0;
}

void startVSyncCallback(void) {
    VSyncCallback(vsyncCallback);
}

/*
 * Ends a frame: lets the layers run their draw callbacks, waits for the GPU
 * and for the vsync that shows the finished buffer, then sends every layer
 * of that buffer and clears the ones of the next.
 */
void drawFrame(s32 draw) {
    s32 i;
    Layer *layer;

    if (draw) {
        s32 j;

        for (j = 0; j < 30; j++) {
            layer = GFX.layers[j];
            if (layer != NULL) {
                if (layer->keepView != 0) {
                    layer->loadView(layer);
                }
                if (layer->keepLightMatrix != 0) {
                    layer->loadLightMatrix(layer);
                }
                layer->runCallbacks(layer);
            }
        }
    }
    DrawSync(0);
    FLIP_PENDING = 1;
    while (*(volatile s32 *)&FLIP_PENDING != 0) {
    }
    if (GFX.prim != 0) {
        for (i = 0; i < 30; i++) {
            if (GFX.layers[i] != NULL) {
                GFX.layers[i]->draw(GFX.layers[i]);
            }
        }
    }
    GFX.buffer = GFX.buffer == 0;
#if VERSION_US
    GFX.frameCounter += 0x100;
#elif VERSION_EU
    if (NTSC_MODE) {
        GFX.frameCounter += 0x100;
    } else {
        GFX.frameCounter += 0x133;
    }
#endif
    GFX.frameCount = GFX.frameCounter >> 8;
    GFX.time = GFX.timeCounter >> 8;
    GFX.frameTime = GFX.frameTimeCounter >> 8;
    GFX.frameTimeCounter &= 0xFF;
    GAME_FUNCS.updatePlayTime();
    GFX.prim = (s32)GFX.primBufs[GFX.buffer];
    for (i = 0; i < 30; i++) {
        if (GFX.layers[i] != NULL) {
            GFX.layers[i]->clearOt(GFX.layers[i]);
        }
    }
}

s32 getFrameCount(void) {
    return GFX.frameCount;
}

s32 getTime(void) {
    return GFX.time;
}

s32 getFrameTime(void) {
    return GFX.frameTime;
}

void resetGraphics(void) {
    s32 i;

    if (GFX_STARTED != 0) {
        for (i = 0; i < 30; i++) {
            if (GFX.layers[i] != NULL) {
                GFX.funcs.destroyLayer(GFX.layerIds[i]);
                i--;
            }
        }
        HEAP.zero(&GFX.prim, 0x18);
    } else {
        GFX.buffer = 1;
        GFX.dispBuffer = 0;
        GFX_STARTED = 1;
    }
}

void allocPrimBuffers(s32 size) {
    GFX.primBufSize = size;
    GFX.primBufs[0] = HEAP.allocHigh(size, 2);
    GFX.primBufs[1] = HEAP.allocHigh(size, 2);
    GFX.prim = (s32)GFX.primBufs[GFX.buffer];
}

s32 getPrim(void) {
    return GFX.prim;
}

void setPrim(s32 next) {
    GFX.prim = next;
}

void freePrimBuffers(void) {
    if (GFX.primBufs[0] != NULL) {
        HEAP.free(GFX.primBufs[0]);
    }
    if (GFX.primBufs[1] != NULL) {
        HEAP.free(GFX.primBufs[1]);
    }
    GFX.primBufs[0] = NULL;
    GFX.primBufs[1] = NULL;
}

void setDisplayMode(s32 w, s32 h, s32 hires, s32 interlace) {
    if (hires != 0) {
        if (interlace != 0) {
            SetDefDispEnv(&GFX.disp[0], 0, 0, 320, 480);
            GFX.disp[0].isinter = 1;
            GFX.disp[0].isrgb24 = 1;
            SetDefDispEnv(&GFX.disp[1], 480, 0, 320, 480);
            GFX.disp[1].isinter = 1;
            GFX.disp[1].isrgb24 = 1;
        } else {
            SetDefDispEnv(&GFX.disp[0], 0, 0, w, h);
            SetDefDispEnv(&GFX.disp[1], w, 0, w, h);
        }
    } else {
        SetDefDispEnv(&GFX.disp[0], 0, 0, w, h);
        SetDefDispEnv(&GFX.disp[1], 0, 256, w, h);
    }
#if VERSION_EU
    if (SHIFT_PAL_SCREEN) {
        GFX.disp[0].screen.y = 0x18;
        GFX.disp[1].screen.y = 0x18;
    }
#endif
    GsInit3D();
    SetGeomOffset(0, 0);
}

void setDisplayArea(s32 x, s32 y, s32 w, s32 h) {
    SetDefDispEnv(&GFX.disp[0], x, y, w, h);
    SetDefDispEnv(&GFX.disp[1], x, y, w, h);
}

Layer *getLayer(s32 id) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (GFX.layers[i] != NULL && GFX.layerIds[i] == id) {
            return GFX.layers[i];
        }
    }
    return NULL;
}

/* The slot of the layer with this id; id 0 finds a free slot */
s32 findLayerSlot(s32 id) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (id != 0) {
            if (GFX.layers[i] != NULL && GFX.layerIds[i] == id) {
                return i;
            }
        } else if (GFX.layers[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void removeLayerSlot(s32 index) {
    for (; index < 29; index++) {
        GFX.layers[index] = GFX.layers[index + 1];
        GFX.layerIds[index] = GFX.layerIds[index + 1];
    }
}

void insertLayerSlot(s32 index, Layer *layer, s32 id) {
    s32 i;

    for (i = 29; i != index; i--) {
        GFX.layers[i] = GFX.layers[i - 1];
        GFX.layerIds[i] = GFX.layerIds[i - 1];
    }
    GFX.layers[index] = layer;
    GFX.layerIds[index] = id;
}

Layer *createLayer(RECT *rect, s32 otShift, s32 id) {
    DRAWENV env;
    s32 index = findLayerSlot(0);

    if (index != -1) {
        SetDefDrawEnv(&env, rect->x, rect->y, rect->w, rect->h);
        GFX.layerIds[index] = id;
        return GFX.layers[index] = newLayer(&env, otShift);
    }
    return NULL;
}

s32 destroyLayer(s32 id) {
    s32 index = findLayerSlot(id);
    Layer *layer;

    if (index != -1) {
        layer = GFX.layers[index];
        layer->free(layer);
        HEAP.free(GFX.layers[index]);
        removeLayerSlot(index);
        return 1;
    }
    return 0;
}

/* Moves a layer to the position of another one (plus delta) in the draw order */
void moveLayer(s32 id, s32 targetId, s32 delta) {
    s32 from = findLayerSlot(id);
    s32 to = findLayerSlot(targetId);
    s32 pos;
    Layer *layer;
    s32 layerId;

    if (from != -1 && to != -1) {
        pos = to + delta;
        layer = GFX.layers[from];
        layerId = GFX.layerIds[from];
        if (pos <= 0) {
            pos = 0;
        }
        removeLayerSlot(from);
        insertLayerSlot(pos, layer, layerId);
    }
}

void layerClearOt(Layer *layer) {
    ClearOTagR(layer->ot[GFX.buffer], layer->otLen);
}

/* Links every run of empty OT entries past itself, so the GPU skips it */
void layerSkipEmptyOt(Layer *layer) {
    u_long mask = 0xFFFFFF;
    u_long *ot = layer->ot[GFX.buffer];
    u_long *p = ot + layer->otLen - 1;
    u_long *q;

    while (p != ot) {
        q = p - 1;
        if ((*p & mask) == ((u_long)q & mask)) {
            while ((*q & mask) == ((u_long)(q - 1) & mask)) {
                q--;
            }
            *p = (u_long)q & mask;
        }
        p = q;
    }
}

void layerDraw(Layer *layer) {
    DRAWENV env = layer->env;
    DR_ENV *dr;
    u_long *ot;
    u_long *tag;

    env.ofs[0] = layer->offsetX;
    env.ofs[1] = layer->offsetY;
    layerSkipEmptyOt(layer);
    dr = (DR_ENV *)GFX.prim;
    ot = layer->ot[GFX.buffer] + layer->otLen;
    tag = ot - 1;
    if (GFX.buffer != 0) {
        env.clip.y += 256;
        env.ofs[1] += 256;
    }
    SetDrawEnv(dr, &env);
    addPrim(ot - 1, dr);
    dr++;
    GFX.prim = (s32)dr;
    DrawOTag(tag);
}

u_long *layerGetOtEntry(Layer *layer, s32 depth) {
    return layer->ot[GFX.buffer] + depth;
}

u_long *layerGetOtEntryZ(Layer *layer, s32 z) {
    s32 i = z >> (16 - layer->otShift);

    return layer->ot[GFX.buffer] + i;
}

u_long *layerGetOt(Layer *layer) {
    return layer->ot[GFX.buffer];
}

s32 layerGetOtShift(LayerView *layer) {
    return layer->otShift;
}

void layerSetBgColor(LayerView *layer, u8 r, u8 g, u8 b) {
    layer->bgR = r;
    layer->bgB = b;
    layer->bgG = g;
    if (r | g | b) {
        layer->isbg = 1;
    } else {
        layer->isbg = 0;
    }
}

void layerSetOffset(LayerView *layer, s16 x, s16 y) {
    layer->offsetX = x;
    layer->offsetY = y;
}

void layerGetScroll(LayerView *layer, Vec2 *out) {
    out->x = layer->scrollX >> 8;
    out->y = layer->scrollY >> 8;
}

void layerSetScroll(LayerView *layer, s32 x, s32 y) {
    layer->scrollX = x;
    layer->scrollY = y;
}

void layerAddScroll(LayerView *layer, s32 dx, s32 dy) {
    layer->scrollX += dx;
    layer->scrollY += dy;
}

void layerSetClipPos(LayerView *layer, s16 x, s16 y) {
    layer->x = x;
    layer->y = y;
}

void layerSetClipSize(LayerView *layer, s16 w, s16 h) {
    layer->w = w;
    layer->h = h;
}

void layerGetViewRect(LayerView *layer, Rect16 *rect) {
    rect->x = layer->x - layer->offsetX + (layer->scrollX >> 8);
    rect->y = layer->y - layer->offsetY + (layer->scrollY >> 8);
    rect->w = layer->w;
    rect->h = layer->h;
}

void layerFree(Layer *layer) {
    DrawSync(0);
    HEAP.free(layer->ot[0]);
    HEAP.free(layer->ot[1]);
    if (layer->callbackCap != 0) {
        HEAP.free(layer->callbacks);
    }
}

void layerResetCallbacks(LayerView *layer) {
    layer->callbacks->priority = 0x7FFFFFFF;
    layer->callbacks->param = 0;
    layer->callbacks->func = NULL;
    layer->callbacks->arg = 0;
    layer->callbacks->next = NULL;
    layer->callbackCount = 1;
}

void layerAllocCallbacks(LayerView *layer, s32 count) {
    layer->callbacks = HEAP.alloc(count * sizeof(DrawCallback), 2);
    layer->callbackCap = count;
    layerResetCallbacks(layer);
}

void layerAddSortedCallback(Layer *layer, s32 func, s32 arg, s32 priority, s32 param) {
    DrawCallback *cur;
    DrawCallback *prev;
    DrawCallback *e;
    s32 i;
    s32 cap;

    if (layer->callbackCount < layer->callbackCap) {
        cur = layer->callbacks;
        e = &cur[layer->callbackCount];
        e->func = func;
        e->arg = arg;
        e->priority = priority;
        e->param = param;
        prev = NULL;
        if (layer->callbackCount != 0) {
            cap = layer->callbackCap;
            for (i = 0; i < cap; i++) {
                if (cur->priority < priority) {
                    cur = prev;
                    break;
                }
                prev = cur;
                if (cur->next == NULL) {
                    break;
                }
                cur = cur->next;
            }
            if (cur->next == NULL) {
                cur->next = e;
                e->next = NULL;
            } else {
                e->next = cur->next;
                cur->next = e;
            }
        } else {
            e->next = NULL;
        }
        layer->callbackCount++;
    }
}

void layerAddCallback(LayerView *layer, void (*func)(s32, void *, s32), s32 arg) {
    DrawCallback *cb;

    if (layer->callbackCount < layer->callbackCap) {
        cb = &layer->callbacks[layer->callbackCount];
        cb->func = func;
        cb->arg = arg;
        cb->priority = 0;
        cb->param = 0;
        cb->next = NULL;
        if (layer->callbackCount != 0) {
            cb[-1].next = cb;
        }
        layer->callbackCount++;
    }
}

void layerRunCallbacks(LayerView *layer) {
    DrawCallback *cb;

    if (layer->callbackCount) {
        cb = layer->callbacks;
        do {
            if (cb->func != NULL) {
                cb->func(cb->arg, layer, cb->param);
            }
            cb = cb->next;
        } while (cb != NULL);
        layerResetCallbacks(layer);
    }
}

void layerSetKeepView(Layer *layer, s32 enable, s32 projection) {
    layer->keepView = enable;
    if (enable) {
        layer->projection = projection;
        layer->view[GFX.buffer] = D_80080AF0;
    }
}

void layerLoadView(Layer *layer) {
    func_80029598(layer->projection);
    D_80080AF0 = layer->view[GFX.buffer];
}

void layerSetKeepLightMatrix(Layer *layer, s32 enable) {
    layer->keepLightMatrix = enable;
    if (enable) {
        layer->lightMatrix[GFX.buffer] = D_80080A90;
    }
}

void layerLoadLightMatrix(Layer *layer) {
    D_80080A90 = layer->lightMatrix[GFX.buffer];
}

Layer *newLayer(DRAWENV *env, s32 otShift) {
    Layer *layer = HEAP.allocZeroed(0x16C, 2);

    layer->env = *env;
    layer->otShift = otShift;
    layer->otLen = OT_LENGTHS[otShift - 1];
    layer->ot[0] = HEAP.alloc(layer->otLen << 2, 2);
    layer->ot[1] = HEAP.alloc(layer->otLen << 2, 2);
    ClearOTagR(layer->ot[0], layer->otLen);
    ClearOTagR(layer->ot[1], layer->otLen);
    layer->setBgColor = layerSetBgColor;
    layer->draw = (void *)layerDraw;
    layer->clearOt = (void *)layerClearOt;
    layer->getOtEntry = (void *)layerGetOtEntry;
    layer->getOtEntryZ = layerGetOtEntryZ;
    layer->free = (void *)layerFree;
    layer->setClipPos = layerSetClipPos;
    layer->setClipSize = layerSetClipSize;
    layer->setOffset = layerSetOffset;
    layer->setScroll = layerSetScroll;
    layer->addScroll = layerAddScroll;
    layer->getScroll = layerGetScroll;
    layer->getViewRect = layerGetViewRect;
    layer->getOt = layerGetOt;
    layer->getOtShift = layerGetOtShift;
    layer->allocCallbacks = layerAllocCallbacks;
    layer->addSortedCallback = layerAddSortedCallback;
    layer->addCallback = layerAddCallback;
    layer->runCallbacks = (void *)layerRunCallbacks;
    layer->setKeepView = layerSetKeepView;
    layer->loadView = (void *)layerLoadView;
    layer->setKeepLightMatrix = layerSetKeepLightMatrix;
    layer->loadLightMatrix = (void *)layerLoadLightMatrix;
    return layer;
}

void bindCardDrawer(CardDrawer *obj) {
    CARD_DRAWER = obj;
}

void cardDrawerSetCard(s32 id) {
    s32 n;
    s32 i;
    if (id > 0) {
        n = id - 1;
        i = n >> 6;
        CARD_DRAWER->card = FILE_CACHE_LOAD[0](CARD_IMAGE_FILES[i]) + (n & 0x3F) * 0x62C;
    } else {
        CARD_DRAWER->card = FILE_CACHE_LOAD[0](CARD_IMAGE_FILES[0]);
    }
}

void cardDrawerLoadImage(void) {
    TimLoader obj;

    initTimLoader(&obj);
    obj.setImagePos(CARD_DRAWER->imageX + CARD_DRAWER->cellX * 16, CARD_DRAWER->imageY + (CARD_DRAWER->cellY << 5));
    obj.setClutPos(CARD_DRAWER->clutX, CARD_DRAWER->clutY + CARD_DRAWER->cellX * CARD_DRAWER->clutStride + CARD_DRAWER->cellY);
    obj.load(CARD_DRAWER->card + 0xC);
}

void cardDrawerSetLayer(s32 id, s32 depth) {
    Layer *layer = GFX_FUNCS.getLayer(id);

    CARD_DRAWER->layer = layer;
    CARD_DRAWER->ot = layer->getOtEntry(layer, depth);
}

void cardDrawerSetImagePos(s32 x, s32 y) {
    CARD_DRAWER->imageX = x;
    CARD_DRAWER->imageY = y;
}

void cardDrawerSetClutPos(s32 x, s32 y) {
    CARD_DRAWER->clutX = x;
    CARD_DRAWER->clutY = y;
}

void cardDrawerSetCell(s32 x, s32 y) {
    CARD_DRAWER->cellX = x;
    CARD_DRAWER->cellY = y;
}

void cardDrawerSetClutStride(s32 stride) {
    CARD_DRAWER->clutStride = stride;
}

void cardDrawerSetSemiTrans(s32 on) {
    CARD_DRAWER->semiTrans = on;
}

void cardDrawerDraw(s32 x, s32 y) {
    SPRT *sprt = GFX.funcs.getPrim();
    SPRT *base = sprt;
    u8 *end;
    u16 tpage;
    u16 clut;

    clut = getClut(CARD_DRAWER->clutX, CARD_DRAWER->clutY + CARD_DRAWER->cellX * CARD_DRAWER->clutStride + CARD_DRAWER->cellY);
    tpage = (1 << 7) | (1 << 5) | ((CARD_DRAWER->imageY & 0x100) >> 4) | (((CARD_DRAWER->imageX + CARD_DRAWER->cellX * 16) & 0x3C0) >> 6) | ((CARD_DRAWER->imageY & 0x200) << 2);
    setSprt(sprt);
    if (CARD_DRAWER->semiTrans != 0) {
        setSemiTrans(sprt, 1);
    }
    setRGB0(sprt, 0x80, 0x80, 0x80);
    setXY0(sprt, x, y);
    setUV0(sprt, (CARD_DRAWER->cellX & 3) * 32, CARD_DRAWER->cellY * 32);
    setWH(sprt, 32, 32);
    sprt->clut = clut;
    addPrim(CARD_DRAWER->ot, sprt);
    sprt++;
    SetDrawTPage((DR_TPAGE *)sprt, 0, 1, tpage);
    end = (u8 *)base + 0x1C;
    /* addPrim, with the tag written through the start of the block */
    setaddr(base + 1, getaddr(CARD_DRAWER->ot));
    setaddr(CARD_DRAWER->ot, sprt);
    GFX.funcs.setPrim(end);
}

s32 cardDrawerGetKind(void) {
    return CARD_KINDS[CARD_DRAWER->card[3]];
}

void initCardDrawer(CardDrawer *obj) {
    HEAP.zero(obj, sizeof(CardDrawer));
    obj->setCard = cardDrawerSetCard;
    obj->loadImage = cardDrawerLoadImage;
    obj->setLayer = cardDrawerSetLayer;
    obj->setImagePos = cardDrawerSetImagePos;
    obj->setClutPos = cardDrawerSetClutPos;
    obj->setCell = cardDrawerSetCell;
    obj->setClutStride = cardDrawerSetClutStride;
    obj->setSemiTrans = cardDrawerSetSemiTrans;
    obj->draw = cardDrawerDraw;
    obj->getKind = cardDrawerGetKind;
    bindCardDrawer(obj);
    obj->clutStride = 8;
}

void bindSpriteDrawer(SpriteDrawer *obj) {
    SPRITE_DRAWER = obj;
}

void spriteDrawerSetTexture(s32 x, s32 y) {
    SPRITE_DRAWER->tpageX = x;
    SPRITE_DRAWER->tpageY = y;
    SPRITE_DRAWER->clutX = x;
    SPRITE_DRAWER->clutY = y;
}

void spriteDrawerSetAltClut(s32 x, s32 y) {
    SPRITE_DRAWER->altClutX = x;
    SPRITE_DRAWER->altClutY = y - 0x100;
}

void spriteDrawerSetClutRow(s32 row) {
    SPRITE_DRAWER->clutRow = row;
}

void spriteDrawerSetLayer(Layer *layer, s32 depth) {
    SPRITE_DRAWER->layer = layer;
    SPRITE_DRAWER->ot = layer->getOtEntry(layer, depth);
}

void spriteDrawerSetLayerId(s32 id, s32 depth) {
    spriteDrawerSetLayer(GFX_FUNCS.getLayer(id), depth);
}

/*
 * Draws frame `frame` of a sprite sheet (see SpritePart) at (x, y): as
 * sprites, changing the texture page between parts when needed, or as
 * textured quads when the drawer is scaled or rotated.
 */
void spriteDrawerDraw(s32 *sheet, s32 frame, s32 x, s32 y) {
    Vec2 scroll;
    SVECTOR out;
    SVECTOR in[4];
    SpritePart *parts;
    SpritePart *part;
    u8 *ids;
    s16 *p;
    void *prim;
    s32 transform;
    s32 count;
    s32 frameRow;
    s32 semi;
    s32 abr;
    s32 i;
    s32 k;
    u8 u;
    u8 v;

    transform = 0;
    ids = (u8 *)sheet + sheet[1];
    parts = (SpritePart *)((u8 *)sheet + sheet[0]);
    for (i = 0; ids[i] != frame; i++) {
    }
    p = (s16 *)((u8 *)sheet + sheet[i + 2]);
    /* rot.vx and rot.vy are tested as one word */
    if (SPRITE_DRAWER->scaleX != 0x1000 || SPRITE_DRAWER->scaleY != 0x1000 || SPRITE_DRAWER->scaleZ != 0x1000 ||
        *(s32 *)&SPRITE_DRAWER->rot.vx != 0 || SPRITE_DRAWER->rot.vz != 0) {
        transform = 1;
        if (SPRITE_DRAWER->transformDirty) {
            RotMatrixYXZ_gte(&SPRITE_DRAWER->rot, &SPRITE_DRAWER->matrix);
            ScaleMatrix(&SPRITE_DRAWER->matrix, (VECTOR *)&SPRITE_DRAWER->scaleX);
        }
    }
    count = *p++;
    frameRow = *p++;
    abr = *p++;
    if (abr == -1) {
        semi = 0;
        abr = 0;
    } else {
        semi = 1;
    }
    if (SPRITE_DRAWER->followScroll) {
        SPRITE_DRAWER->layer->getScroll(SPRITE_DRAWER->layer, &scroll);
    } else {
        scroll.x = 0;
        scroll.y = 0;
    }
    p += (count - 1) * 3;
    prim = GFX_FUNCS.getPrim();
    if (!transform) {
        u16 clut;
        u16 tpage;
        u16 prevTpage;

        tpage = 0;
        prevTpage = 0;
        for (i = 0; i < count; i++) {
            part = &parts[p[0]];
            clut = getClut((part->mode ? SPRITE_DRAWER->altClutX : SPRITE_DRAWER->clutX) + part->clutX,
                           (part->mode ? SPRITE_DRAWER->altClutY : SPRITE_DRAWER->clutY) + part->clutY + frameRow +
                               SPRITE_DRAWER->clutRow);
            tpage = getTPage(part->mode, abr, SPRITE_DRAWER->tpageX + (part->mode ? part->u / 2 : part->u / 4),
                             SPRITE_DRAWER->tpageY);
            if (i == 0) {
                prevTpage = tpage;
            }
            if (prevTpage != tpage) {
                SetDrawTPage(prim, 0, 1, prevTpage);
                addPrim(SPRITE_DRAWER->ot, prim);
                prim = (DR_TPAGE *)prim + 1;
                prevTpage = tpage;
            }
            *(CVECTOR *)&((SPRT *)prim)->r0 = SPRITE_DRAWER->color;
            setSprt((SPRT *)prim);
            if (semi) {
                setSemiTrans((SPRT *)prim, 1);
            }
            ((SPRT *)prim)->x0 = p[1] + x - scroll.x;
            ((SPRT *)prim)->y0 = p[2] + y - scroll.y;
            if (part->mode) {
                ((SPRT *)prim)->u0 = part->u & 0x7F;
            } else {
                ((SPRT *)prim)->u0 = part->u;
            }
            ((SPRT *)prim)->v0 = part->v;
            ((SPRT *)prim)->w = part->w;
            ((SPRT *)prim)->h = part->h;
            ((SPRT *)prim)->clut = clut;
            addPrim(SPRITE_DRAWER->ot, prim);
            prim = (SPRT *)prim + 1;
            p -= 3;
        }
        SetDrawTPage(prim, 0, 1, tpage);
        addPrim(SPRITE_DRAWER->ot, prim);
        prim = (DR_TPAGE *)prim + 1;
    } else {
        u16 clut;
        u16 tpage;

        for (i = 0; i < count; i++) {
            part = &parts[p[0]];
            clut = getClut((part->mode ? SPRITE_DRAWER->altClutX : SPRITE_DRAWER->clutX) + part->clutX,
                           (part->mode ? SPRITE_DRAWER->altClutY : SPRITE_DRAWER->clutY) + part->clutY + frameRow +
                               SPRITE_DRAWER->clutRow);
            tpage = getTPage(part->mode, abr, SPRITE_DRAWER->tpageX + (part->mode ? part->u / 2 : part->u / 4),
                             SPRITE_DRAWER->tpageY);
            *(CVECTOR *)&((POLY_FT4 *)prim)->r0 = SPRITE_DRAWER->color;
            setPolyFT4((POLY_FT4 *)prim);
            if (semi) {
                setSemiTrans((POLY_FT4 *)prim, 1);
            }
            in[0].vx = in[2].vx = p[1] + x - SPRITE_DRAWER->pivotX;
            in[1].vx = in[3].vx = in[0].vx + part->w;
            in[0].vy = in[1].vy = p[2] + y - SPRITE_DRAWER->pivotY;
            in[2].vy = in[3].vy = in[0].vy + part->h;
            in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
            for (k = 0; k < 4; k++) {
                ApplyMatrixSV(&SPRITE_DRAWER->matrix, &in[k], &out);
                (&((POLY_FT4 *)prim)->x0)[k * 4] = out.vx - scroll.x + SPRITE_DRAWER->pivotX;
                (&((POLY_FT4 *)prim)->y0)[k * 4] = out.vy - scroll.y + SPRITE_DRAWER->pivotY;
            }
            if (part->mode) {
                u = part->u & 0x7F;
            } else {
                u = part->u;
            }
            ((POLY_FT4 *)prim)->u0 = ((POLY_FT4 *)prim)->u2 = u;
            ((POLY_FT4 *)prim)->u1 = ((POLY_FT4 *)prim)->u3 = u + part->w - 1;
            v = part->v;
            ((POLY_FT4 *)prim)->v0 = ((POLY_FT4 *)prim)->v1 = v;
            ((POLY_FT4 *)prim)->v2 = ((POLY_FT4 *)prim)->v3 = v + part->h - 1;
            ((POLY_FT4 *)prim)->tpage = tpage;
            ((POLY_FT4 *)prim)->clut = clut;
            addPrim(SPRITE_DRAWER->ot, prim);
            prim = (POLY_FT4 *)prim + 1;
            p -= 3;
        }
    }
    GFX_FUNCS.setPrim(prim);
}

void spriteDrawerSetScale(s32 x, s32 y, s32 z) {
    SPRITE_DRAWER->scaleX = x;
    SPRITE_DRAWER->scaleY = y;
    SPRITE_DRAWER->scaleZ = z;
    SPRITE_DRAWER->transformDirty = 1;
}

void spriteDrawerSetRotation(s16 x, s16 y, s16 z) {
    SPRITE_DRAWER->rot.vx = x;
    SPRITE_DRAWER->rot.vy = y;
    SPRITE_DRAWER->rot.vz = z;
    SPRITE_DRAWER->transformDirty = 1;
}

void spriteDrawerSetPivot(s32 x, s32 y) {
    SPRITE_DRAWER->pivotX = x;
    SPRITE_DRAWER->pivotY = y;
}

void spriteDrawerSetFollowScroll(s32 on) {
    SPRITE_DRAWER->followScroll = on;
}

void spriteDrawerSetColor(CVECTOR *color) {
    SPRITE_DRAWER->color = *color;
}

void initSpriteDrawer(SpriteDrawer *obj) {
    HEAP.zero(obj, sizeof(SpriteDrawer));
    obj->scaleX = 0x1000;
    obj->scaleY = 0x1000;
    obj->scaleZ = 0x1000;
    obj->followScroll = 1;
    obj->color.b = 0x80;
    obj->color.g = 0x80;
    obj->color.r = 0x80;
    obj->setTexture = spriteDrawerSetTexture;
    obj->draw = spriteDrawerDraw;
    obj->setAltClut = spriteDrawerSetAltClut;
    obj->setLayerId = spriteDrawerSetLayerId;
    obj->setLayer = spriteDrawerSetLayer;
    obj->bind = bindSpriteDrawer;
    obj->setClutRow = spriteDrawerSetClutRow;
    obj->setScale = spriteDrawerSetScale;
    obj->setRotation = spriteDrawerSetRotation;
    obj->setPivot = spriteDrawerSetPivot;
    obj->setFollowScroll = spriteDrawerSetFollowScroll;
    obj->setColor = spriteDrawerSetColor;
    bindSpriteDrawer(obj);
}

void bindTextTools(TextTools *obj) {
    TEXT_TOOLS = obj;
}

s32 getString(s32 *table, s32 index) {
    s32 count = table[0];

    if (index < 0 || count < index) {
        return 0;
    }
    return (s32)table + table[index + 1];
}

s32 measureText(TextBuffer *text, TextStyle *style, s32 spacing) {
    s32 pos;
    s32 w;
    s32 max;
    s32 c;
    s32 op;
    s32 n;
    Glyph *g;
#if VERSION_US
    s32 len;
#endif

    if (text->data == NULL) {
        return 0;
    }
    pos = 0;
    w = 0;
    max = 0;
    while (pos < text->len) {
        c = ((s32 (*)())FONT.decode)(text->data + pos, (u8)text->sjis, style);
        switch (((u32)c >> 8) & 0xFF) {
        case 0:
            if ((s16)spacing != 0) {
                w += (s16)spacing;
            } else {
                w += ((Glyph *)style->glyphs)[(s16)c - 4].advance + ((Glyph *)style->glyphs)[(s16)c - 4].dx;
            }
            if (text->sjis != 0) {
                pos += 2;
            } else {
                pos += 1;
            }
            break;
        case 1:
            n = c & 0xFF;
            if (n <= style->iconCount && n > 0) {
                if ((s16)spacing != 0) {
                    w += (s16)spacing;
                } else {
                    w += ((Glyph *)style->icons)[n - 1].advance + ((Glyph *)style->icons)[n - 1].dx;
                }
            }
            pos += 2;
            break;
        case 2:
            op = text->data[pos + 1];
            switch (op) {
            case 1:
            case 3:
                if (max < w) {
                    max = w;
                }
                w = 0;
                break;
            case 5:
                w += measureText(&text[text->data[pos + 2]], style, (s16)spacing);
                break;
#if VERSION_US
            case 8:
                for (len = 0; (u8)GAME.name[len] != 0; len++) {
                }
                w += len * 11;
                break;
#endif
            }
            pos += FONT.codeLengths[op];
            break;
        case 3:
            if ((s16)spacing != 0) {
                w += (s16)spacing;
            } else {
                w += ((Glyph *)style->glyphs)->advance + ((Glyph *)style->glyphs)->dx;
            }
            if (text->sjis != 0) {
                pos += 2;
            } else {
                pos += 1;
            }
            break;
        case 4:
            if (max < w) {
                return w;
            }
            return max;
        }
    }
    if (max < w) {
        return w;
    }
    return max;
}

/* Swaps the bytes of a Shift-JIS code: the text has them big-endian */
#define SWAP16(x) ((((x) & 0xFF00) >> 8) | (((x) & 0xFF) << 8))

/*
 * Converts the string `text` to `buf`: mode 0 from font codes to Shift-JIS (a
 * code below 4 is followed by an icon's), mode 1 back. Not terminated.
 */
void convertText(void *buf, void *text, s32 mode) {
    u8 *dst = buf;
    u8 *src = text;
    s32 len;
    s32 i;
    s32 j;
    s32 n;
    s32 found;

    len = strlen(src);
    if (mode == 0) {
        n = 0;
        for (i = 0; i < len; i++) {
            if (src[i] >= 4) {
                for (j = 4; FONT_GLYPH_MAP[j].code != 0xFFFF; j++) {
                    if (FONT_GLYPH_MAP[j].index == src[i]) {
                        *(u16 *)&dst[n] = SWAP16(FONT_GLYPH_MAP[j].code);
                        n += 2;
                        break;
                    }
                }
            } else {
                for (j = 1; FONT_ICON_MAP[j].code != 0xFFFF; j++) {
                    if (FONT_ICON_MAP[j].index == src[i + 1]) {
                        *(u16 *)&dst[n] = SWAP16(FONT_ICON_MAP[j].code);
                        n += 2;
                        break;
                    }
                }
                i++;
            }
        }
    } else if (mode == 1) {
        len >>= 1;
        n = 0;
        for (i = 0; i < len; i++) {
            found = 0;
            for (j = 4; FONT_GLYPH_MAP[j].code != 0xFFFF; j++) {
                if (FONT_GLYPH_MAP[j].code == SWAP16(((s16 *)src)[i])) {
                    dst[n++] = FONT_GLYPH_MAP[j].index;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                for (j = 1; FONT_ICON_MAP[j].code != 0xFFFF; j++) {
                    if (FONT_ICON_MAP[j].code == SWAP16(((s16 *)src)[i])) {
                        dst[n++] = 1;
                        /* the glyph map's index, not the icon's */
                        dst[n++] = FONT_GLYPH_MAP[j].index;
                        break;
                    }
                }
            }
        }
    }
}

void initTextTools(TextTools *obj) {
    HEAP.zero(obj, sizeof(TextTools));
    obj->getString = getString;
    obj->measure = measureText;
    obj->convert = convertText;
    bindTextTools(obj);
}

void bindTimLoader(TimLoader *obj) {
    TIM_LOADER = obj;
}

void timLoaderSetImagePos(s32 x, s32 y) {
    TIM_LOADER->imageX = x;
    TIM_LOADER->imageY = y;
}

void timLoaderSetClutPos(s32 x, s32 y) {
    TIM_LOADER->clutX = x;
    TIM_LOADER->clutY = y;
}

void timLoaderLoad(u_long *tim) {
    RECT clut;
    RECT image;
    u_long *p = tim;
    s32 flag;
    s32 mode;
    s32 hasClut;

    p++;
    flag = *p++;
    hasClut = flag & 8;
    mode = flag & 7;
    if (hasClut) {
        switch (mode) {
        case 0:
        case 1:
            clut.x = TIM_LOADER->clutX;
            clut.y = TIM_LOADER->clutY;
            clut.w = ((u16 *)p)[4];
            clut.h = ((u16 *)p)[5];
            LoadImage(&clut, p + 3);
            break;
        }
        p = (u_long *)((u8 *)p + *p);
    }
    image.x = TIM_LOADER->imageX;
    image.y = TIM_LOADER->imageY;
    image.w = ((u16 *)p)[4];
    image.h = ((u16 *)p)[5];
    LoadImage(&image, p + 3);
    TIM_LOADER->w = image.w;
    TIM_LOADER->h = image.h;
}

void timLoaderLoadArchive(s32 archive) {
    u8 *buf = HEAP.alloc(TIM_LOADER->bufferSize, 2);
    s32 i;
    s32 compressed;
    u8 *data;
    u8 *src;
    u8 *dst;
    s32 c;
    s32 n;
    s32 k;

    for (i = 0;; i++) {
        data = FILE_CACHE.getArchiveEntry(i, archive);
        if (data == (u8 *)archive) {
            break;
        }
        src = data;
        compressed = *(u32 *)src == 0x4E454C52;
        dst = data;
        if (compressed) {
            dst = buf;
            src += 8;
            while ((c = *src) != 0) {
                if (c & 0x80) {
                    n = c & 0x7F;
                    src++;
                    for (k = 0; k < n; k++) {
                        *dst++ = *src;
                    }
                    src++;
                } else {
                    n = *src++;
                    for (k = 0; k < n; k++) {
                        *dst++ = *src++;
                    }
                }
            }
            dst = buf;
        }
        timLoaderLoad((u_long *)dst);
        DrawSync(0);
        TIM_LOADER->imageX += 0x40;
    }
    HEAP.free(buf);
}

void timLoaderSetBufferSize(s32 size) {
    TIM_LOADER->bufferSize = size;
}

void initTimLoader(TimLoader *obj) {
    HEAP.zero(obj, sizeof(TimLoader));
    obj->load = timLoaderLoad;
    obj->setClutPos = timLoaderSetClutPos;
    obj->setImagePos = timLoaderSetImagePos;
    obj->bind = bindTimLoader;
    obj->loadArchive = timLoaderLoadArchive;
    obj->setBufferSize = timLoaderSetBufferSize;
    bindTimLoader(obj);
    obj->bufferSize = 0xA800;
}
