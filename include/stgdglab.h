#ifndef STGDGLAB_H
#define STGDGLAB_H

/* STGDGLAB.PRO: the partners' digivolutions, it seems. Its main menu
   (STGDGLAB_createMenu) opens one of three screens (STGDGLAB_screens): the
   third checks the recipes of STGDGLAB_tables (how many of a few ids are
   needed) against the entries a partner has (listPartnerEntries), and the
   second sets a partner's three slots (setPartnerSlots). On the way in it
   packs the party (STGDGLAB_packParty) so that the members come first. Its
   strings are in files 0x3A, 0x4F, 0x48, 0xA3 and 0x9C. */

#include "game.h"

/* The lab's sprite sheet; the next file is its texture archive */
#if VERSION_US
#define FILE_LAB_SPRITES 0x2B6
#elif VERSION_EU
#define FILE_LAB_SPRITES 0x2C5
#endif

/* The lab's main menu (STGDGLAB_createMenu) */
typedef struct LabMenu {
    TASK_HEADER(LabMenu);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 picked;
    /* 0x058 */ s32 layer;
    /* 0x05C */ s32 depth;
    /* 0x060 */ s32 choice; /* into STGDGLAB_screens */
    /* 0x064 */ PanelAnim panels[9];
    /* 0x0F4 */ s32 unkF4;
    /* 0x0F8 */ s32 unkF8;
    /* 0x0FC */ s32 unkFC[5];
    /* 0x110 */ s32 unk110;
    /* 0x114 */ void (*open)(struct LabMenu *menu);
    /* 0x118 */ void (*close)(struct LabMenu *menu);
} LabMenu;

typedef struct LabMenuWindows {
    /* 0x00 */ TextWindow *unk0[5];
    /* 0x14 */ TextWindow *unk14[5];
    /* 0x28 */ TextWindow *unk28[5];
    /* 0x3C */ TextWindow *unk3C;
    /* 0x40 */ Task *unk40[3];
} LabMenuWindows;

/* A recipe of STGDGLAB_tables's tables: how many of the ids are needed, then up
   to five ids (0: none) */
typedef s16 LabRecipe[6];

typedef struct LabTables {
    /* 0x00 */ s32 *anim; /* D_8008ECE8 */
    /* 0x04 */ s32 *pos; /* D_8008EDC8 */
    /* 0x08 */ LabRecipe *recipes[8]; /* [row * 4 + col] */
} LabTables;

/* The main menu's first screen (func_8008BB30) */
typedef struct LabScreen1 {
    TASK_HEADER(LabScreen1);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ u8 unk5C[0x108 - 0x5C];
} LabScreen1;

/* The main menu's second screen (func_80087FF0) */
typedef struct LabScreen2 {
    TASK_HEADER(LabScreen2);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ PanelAnim panels[6];
    /* 0x0B4 */ s32 layer;
    /* 0x0B8 */ s32 depth;
    /* 0x0BC */ u8 unkBC[0x130 - 0xBC];
} LabScreen2;

/* The main menu's third screen (func_80084CF4) */
typedef struct LabScreen3 {
    TASK_HEADER(LabScreen3);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ s16 owned[44];
    /* 0x0B8 */ s32 ownedCount;
    /* 0x0BC */ s32 table; /* into STGDGLAB_tables.recipes */
    /* 0x0C0 */ s32 row;
    /* 0x0C4 */ s32 unkC4[3];
    /* 0x0D0 */ s32 found[4][4][5]; /* the owned ids of each recipe */
    /* 0x210 */ s32 complete[4]; /* 0: a recipe of the row lacks ids */
    /* 0x220 */ s32 foundCount[4];
    /* 0x230 */ u8 unk230[0x290 - 0x230];
    /* 0x290 */ s32 col;
    /* 0x294 */ s32 slot;
    /* 0x298 */ s32 unk298;
} LabScreen3;

/* A panel of the second screen (func_800869A4) */
typedef struct LabPanel1 {
    TASK_HEADER(LabPanel1);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60[0x100 - 0x60];
} LabPanel1;

/* A panel of the second screen (func_8008D014) */
typedef struct LabPanel2 {
    TASK_HEADER(LabPanel2);
    /* 0x50 */ u8 unk50[0x70 - 0x50];
    /* 0x70 */ s32 layer;
    /* 0x74 */ s32 depth;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ u8 unk80[0xAC - 0x80];
} LabPanel2;

/* A panel of the main menu (func_8008E320) */
typedef struct LabPanel3 {
    TASK_HEADER(LabPanel3);
    /* 0x050 */ s32 unk50;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 layer;
    /* 0x05C */ s32 depth;
    /* 0x060 */ u8 unk60[0x80 - 0x60];
    /* 0x080 */ PanelAnim fade;
    /* 0x090 */ u8 unk90[0x16C - 0x90];
    /* 0x16C */ s32 unk16C;
    /* 0x170 */ void (*close)(struct LabPanel3 *panel);
} LabPanel3;

typedef struct LabPanel3Windows {
    /* 0x00 */ u8 unk0[0x68];
    /* 0x68 */ Cursor *cursor;
    /* 0x6C */ Task *unk6C;
} LabPanel3Windows;

/* The mode's main task (STGDGLAB_createLab) */
typedef struct Lab {
    TASK_HEADER(Lab);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 blinkPos;
    /* 0x58 */ s32 blinkSkip;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 partyCount;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 (*openMenu)(struct Lab *lab);
    /* 0x6C */ s32 (*closeMenu)(struct Lab *lab);
    /* 0x70 */ s32 (*menuOpen)(struct Lab *lab);
    /* 0x74 */ void (*packParty)(struct Lab *lab);
    /* 0x78 */ void (*fadeOut)(struct Lab *lab);
} Lab;

typedef struct LabChildren {
    /* 0x0 */ LabMenu *menu;
    /* 0x4 */ Task *screen;
    /* 0x8 */ ScreenFade *fade;
} LabChildren;

/* Moves a value towards a target in fixed point */
typedef struct LabLerp {
    /* 0x00 */ s32 duration;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 fixed; /* value << 8 */
    /* 0x10 */ s32 target;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 active;
} LabLerp;

/* An entry of D_8008EE4C */
typedef struct LabEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 a;
    /* 0x4 */ s16 b;
} LabEntry;

/* The lab's helpers (STGDGLAB_funcs) */
typedef struct LabFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(LabLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(LabLerp *lerp);
    /* 0x18 */ s16 (*getA)(s32 id);
    /* 0x1C */ s16 (*getB)(s32 id);
} LabFuncs;

extern LabFuncs STGDGLAB_funcs;
extern LabTables STGDGLAB_tables;

#endif /* STGDGLAB_H */
