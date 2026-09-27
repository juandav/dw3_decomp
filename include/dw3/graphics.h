#ifndef DW3_GRAPHICS_H
#define DW3_GRAPHICS_H

/* Display, drawing layers and the drawing helpers (graphics.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct Layer Layer;
typedef struct DrawCallback DrawCallback;

/* The graphics methods (GFX.funcs) */
typedef struct GfxFuncs {
    /* 0x00 */ void (*reset)(void);
    /* 0x04 */ void (*allocPrimBuffers)(s32 size);
    /* 0x08 */ void *(*getPrim)(void);
    /* 0x0C */ void (*setPrim)(void *next);
    /* 0x10 */ void (*freePrimBuffers)(void);
    /* 0x14 */ void (*startVSync)(void);
    /* 0x18 */ void (*drawFrame)();
    /* 0x1C */ struct Layer *(*createLayer)(RECT *rect, s32 otShift, s32 id);
    /* 0x20 */ s32 (*destroyLayer)(s32 id);
    /* 0x24 */ void (*setDisplayMode)(s32 w, s32 h, s32 hires, s32 interlace);
    /* 0x28 */ void (*setDisplayArea)();
    /* 0x2C */ struct Layer *(*getLayer)(s32 id);
    /* 0x30 */ void (*moveLayer)();
    /* 0x34 */ void (*getFrameCount)();
    /* 0x38 */ s32 (*getTime)(void);
    /* 0x3C */ s32 (*getFrameTime)(void);
} GfxFuncs;

/*
 * The graphics state: double-buffered display, the GPU packet buffers that
 * primitives are written to (getPrim/setPrim), and up to 30 drawing layers,
 * each with its own ordering table, drawn in order by drawFrame.
 * Times are in vsyncs; the counters keep 8 fractional bits.
 */
typedef struct GfxState {
    /* 0x00 */ void (*vsyncFunc)(s32 arg);
    /* 0x04 */ s32 vsyncArg;
    /* 0x08 */ s32 frameCount;
    /* 0x0C */ s32 frameCounter;
    /* 0x10 */ s32 time; /* vsyncs since boot */
    /* 0x14 */ s32 timeCounter;
    /* 0x18 */ s32 frameTime; /* vsyncs that the last frame took */
    /* 0x1C */ s32 frameTimeCounter;
    /* 0x20 */ s32 prim; /* next free byte of the packet buffer */
    /* 0x24 */ void *primBufs[2];
    /* 0x2C */ s32 primBufSize;
    /* 0x30 */ s32 dispBuffer;
    /* 0x34 */ s32 buffer; /* the one being drawn */
    /* 0x38 */ DISPENV disp[2];
    /* 0x60 */ struct Layer *layers[30];
    /* 0xD8 */ s32 layerIds[30];
    /* 0x150 */ GfxFuncs funcs; /* GFX_FUNCS */
} GfxState;

/* Layer as its clip/scroll methods see it: the clip rect as unsigned */
typedef struct LayerView {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u8 unk8[0x10];
    /* 0x18 */ u8 isbg;
    /* 0x19 */ u8 bgR;
    /* 0x1A */ u8 bgG;
    /* 0x1B */ u8 bgB;
    /* 0x1C */ u8 unk1C[0x4C];
    /* 0x68 */ s32 otShift;
    /* 0x6C */ s16 offsetX;
    /* 0x6E */ s16 offsetY;
    /* 0x70 */ s32 scrollX;
    /* 0x74 */ s32 scrollY;
    /* 0x78 */ s32 callbackCap;
    /* 0x7C */ s32 callbackCount;
    /* 0x80 */ DrawCallback *callbacks;
} LayerView;

typedef struct Rect16 {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
} Rect16;

/* A function that a layer calls when it is drawn (Layer.addDrawCallback) */
struct DrawCallback {
    /* 0x00 */ s32 priority;
    /* 0x04 */ s32 param;
    /* 0x08 */ void (*func)(s32 arg, void *layer, s32 param);
    /* 0x0C */ s32 arg;
    /* 0x10 */ struct DrawCallback *next;
};

/*
 * A drawing layer (GFX.funcs.createLayer): a DRAWENV with a pair of ordering
 * tables, one per buffer, a scroll position and a list of draw callbacks.
 */
struct Layer {
    /* 0x00 */ DRAWENV env;
    /* 0x5C */ u_long *ot[2];
    /* 0x64 */ s32 otLen;
    /* 0x68 */ s32 otShift;
    /* 0x6C */ s16 offsetX;
    /* 0x6E */ s16 offsetY;
    /* 0x70 */ s32 scrollX;
    /* 0x74 */ s32 scrollY;
    /* 0x78 */ s32 callbackCap;
    /* 0x7C */ s32 callbackCount;
    /* 0x80 */ DrawCallback *callbacks;
    /* 0x84 */ s32 keepView;
    /* 0x88 */ s32 projection;
    /* 0x8C */ MATRIX view[2];
    /* 0xCC */ s32 keepLightMatrix;
    /* 0xD0 */ MATRIX lightMatrix[2];
    /* 0x110 */ void (*setClipPos)();
    /* 0x114 */ void (*setClipSize)();
    /* 0x118 */ void (*setOffset)();
    /* 0x11C */ void (*getScroll)();
    /* 0x120 */ void (*setScroll)();
    /* 0x124 */ void (*addScroll)();
    /* 0x128 */ void (*getViewRect)();
    /* 0x12C */ void (*setBgColor)();
    /* 0x130 */ void (*draw)(struct Layer *);
    /* 0x134 */ void (*clearOt)(struct Layer *);
    /* 0x138 */ s32 (*getOtEntry)(struct Layer *, s32 depth);
    /* 0x13C */ void (*getOtEntryZ)();
    /* 0x140 */ void (*getOt)();
    /* 0x144 */ void (*getOtShift)();
    /* 0x148 */ void (*allocCallbacks)();
    /* 0x14C */ void (*addSortedCallback)();
    /* 0x150 */ void (*addCallback)();
    /* 0x154 */ void (*runCallbacks)(struct Layer *);
    /* 0x158 */ void (*loadView)(struct Layer *);
    /* 0x15C */ void (*setKeepView)();
    /* 0x160 */ void (*loadLightMatrix)(struct Layer *);
    /* 0x164 */ void (*setKeepLightMatrix)();
    /* 0x168 */ void (*free)(struct Layer *);
};

/*
 * Draws 32x32 8-bit images from files 0x7E7-0x7EB (64 per file, 0x62C bytes
 * each: a 12-byte header and a TIM). There are 320 of them, so they are
 * probably the cards (the save has counts for 317). The methods act on the
 * drawer that was set up last (CARD_DRAWER).
 */
typedef struct CardDrawer {
    /* 0x00 */ u8 *card;
    /* 0x04 */ s32 imageX; /* VRAM position of the image grid */
    /* 0x08 */ s32 imageY;
    /* 0x0C */ s32 clutX;
    /* 0x10 */ s32 clutY;
    /* 0x14 */ s32 cellX; /* grid cell: 32x32 pixels, one CLUT row each */
    /* 0x18 */ s32 cellY;
    /* 0x1C */ s32 clutStride;
    /* 0x20 */ s32 semiTrans;
    /* 0x24 */ Layer *layer;
    /* 0x28 */ s32 ot;
    /* 0x2C */ void (*setCard)(); /* (id) */
    /* 0x30 */ void (*loadImage)();
    /* 0x34 */ void (*draw)(); /* (x, y) */
    /* 0x38 */ void (*setLayer)(); /* (id, depth) */
    /* 0x3C */ void (*setImagePos)(); /* (x, y) */
    /* 0x40 */ void (*setClutPos)(); /* (x, y) */
    /* 0x44 */ void (*setCell)(); /* (x, y) */
    /* 0x48 */ void (*setClutStride)(); /* (stride) */
    /* 0x4C */ void (*setSemiTrans)(); /* (on) */
    /* 0x50 */ s32 (*getKind)(void);
} CardDrawer;

/*
 * Draws sprites from a sprite sheet (such as file 0x277, the menu graphics):
 * a sheet has a table of frames, each made of textured parts, and can be
 * scaled, rotated and tinted. Set up on the stack with initSpriteDrawer; its
 * methods act on the drawer that was set up last (SPRITE_DRAWER).
 */
typedef struct SpriteDrawer {
    /* 0x00 */ Layer *layer;
    /* 0x04 */ s32 ot;
    /* 0x08 */ s32 tpageX; /* VRAM position of the sheet's texture */
    /* 0x0C */ s32 tpageY;
    /* 0x10 */ s32 clutX;
    /* 0x14 */ s32 clutY;
    /* 0x18 */ s32 altClutX; /* for the parts that are flagged */
    /* 0x1C */ s32 altClutY;
    /* 0x20 */ s32 clutRow; /* added to the CLUT y: palette animations */
    /* 0x24 */ s32 followScroll; /* offset by the layer's scroll */
    /* 0x28 */ CVECTOR color;
    /* 0x2C */ s32 transformDirty;
    /* 0x30 */ s32 pivotX;
    /* 0x34 */ s32 pivotY;
    /* 0x38 */ s32 scaleX;
    /* 0x3C */ s32 scaleY;
    /* 0x40 */ s32 scaleZ;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s16 rotX;
    /* 0x4A */ s16 rotY;
    /* 0x4C */ s16 rotZ;
    /* 0x4E */ u8 unk4E[2];
    /* 0x50 */ MATRIX matrix;
    /* 0x70 */ void (*bind)(); /* (drawer) */
    /* 0x74 */ void (*setTexture)(); /* (x, y) */
    /* 0x78 */ void (*setAltClut)(); /* (x, y) */
    /* 0x7C */ void (*setLayerId)(); /* (id, depth) */
    /* 0x80 */ void (*setLayer)(); /* (layer, depth) */
    /* 0x84 */ void (*draw)(); /* (sheet, frame, x, y) */
    /* 0x88 */ void (*setClutRow)(); /* (row) */
    /* 0x8C */ void (*setScale)(); /* (x, y, z), 0x1000 = 1.0 */
    /* 0x90 */ void (*setRotation)(); /* (x, y, z) */
    /* 0x94 */ void (*setPivot)(); /* (x, y) */
    /* 0x98 */ void (*setFollowScroll)(); /* (on) */
    /* 0x9C */ void (*setColor)(); /* (CVECTOR *) */
} SpriteDrawer;

/* Text helpers (initTextTools) */
typedef struct TextTools {
    /* 0x0 */ char *(*getString)(); /* (table, index) */
    /* 0x4 */ s32 (*measure)(); /* (TextBuffer *, style, spacing) */
    /* 0x8 */ void (*convert)(); /* (dst, src, mode): font codes <-> Shift-JIS */
} TextTools;

/* Uploads TIM images to VRAM (initTimLoader); acts on TIM_LOADER */
typedef struct TimLoader {
    /* 0x00 */ u16 w; /* size of the last image */
    /* 0x02 */ u16 h;
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ s32 imageX;
    /* 0x0C */ s32 imageY;
    /* 0x10 */ s32 clutX;
    /* 0x14 */ s32 clutY;
    /* 0x18 */ s32 bufferSize; /* for the RLE-compressed images */
    /* 0x1C */ void (*bind)(); /* (loader) */
    /* 0x20 */ void (*load)(); /* (TIM) */
    /* 0x24 */ void (*setImagePos)(); /* (x, y) */
    /* 0x28 */ void (*setClutPos)(); /* (x, y) */
    /* 0x2C */ void (*loadArchive)(); /* (archive): each image 64 halfwords to the right */
    /* 0x30 */ void (*setBufferSize)(); /* (size) */
} TimLoader;

typedef struct Vec2 {
    s32 x;
    s32 y;
} Vec2;

u_long *layerGetOtEntryZ(Layer *layer, s32 z);
void layerSkipEmptyOt(Layer *layer);
Layer *newLayer(DRAWENV *env, s32 otShift);
s32 findLayerSlot(s32 id);
void removeLayerSlot(s32 index);
void initTimLoader(TimLoader *obj);
void vsyncCallback(void);
void bindCardDrawer(CardDrawer *obj);
void cardDrawerSetCard();
void cardDrawerLoadImage();
void cardDrawerSetLayer();
void cardDrawerSetImagePos();
void cardDrawerSetClutPos();
void cardDrawerSetCell();
void cardDrawerSetClutStride();
void cardDrawerSetSemiTrans();
void cardDrawerDraw();
s32 cardDrawerGetKind(void);
void bindSpriteDrawer(SpriteDrawer *obj);
void spriteDrawerSetTexture();
void spriteDrawerSetAltClut();
void spriteDrawerSetClutRow();
void spriteDrawerSetLayer(Layer *layer, s32 arg1);
void spriteDrawerDraw();
void spriteDrawerSetScale();
void spriteDrawerSetRotation(s16 x, s16 y, s16 z);
void spriteDrawerSetPivot();
void spriteDrawerSetFollowScroll();
void spriteDrawerSetColor(CVECTOR *color);
void bindTextTools(TextTools *obj);
s32 getString(s32 *table, s32 index);
s32 measureText();
void initTextTools(TextTools *obj);
void convertText();
void bindTimLoader(TimLoader *obj);
void timLoaderSetImagePos();
void timLoaderSetClutPos();
void timLoaderLoad();
void timLoaderLoadArchive();
void timLoaderSetBufferSize();
void initSpriteDrawer(struct SpriteDrawer *obj);

extern GfxFuncs GFX_FUNCS;
extern s16 OT_LENGTHS[];
extern s32 CARD_IMAGE_FILES[];
extern GfxState GFX;
extern s32 CARD_KINDS[];
/* libgs globals: the light matrix and GsWSMATRIX */
extern MATRIX D_80080A90;
extern MATRIX D_80080AF0;

#endif /* DW3_GRAPHICS_H */
