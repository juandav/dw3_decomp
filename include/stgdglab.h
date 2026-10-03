#ifndef STGDGLAB_H
#define STGDGLAB_H

/* STGDGLAB.PRO: a lab that manages the partners. Its main menu
   (func_80089F20) opens one of three screens (D_8008ECDC); on the way in
   and out it packs the party (func_8008E4B4) so that the members come
   first. Its strings are in files 0x3A, 0x4F, 0x48, 0xA3 and 0x9C. */

#include "game.h"

/* The lab's sprite sheet; the next file is its texture archive */
#if VERSION_US
#define FILE_LAB_SPRITES 0x2B6
#elif VERSION_EU
#define FILE_LAB_SPRITES 0x2C5
#endif

/* The lab's main menu (func_80089F20), as the lab sees it */
typedef struct LabMenu {
    TASK_HEADER(LabMenu);
    /* 0x050 */ struct Lab *lab;
    /* 0x054 */ s32 picked;
    /* 0x058 */ s32 layer;
    /* 0x05C */ s32 depth;
    /* 0x060 */ s32 choice; /* into D_8008ECDC */
    /* 0x064 */ u8 unk64[0x114 - 0x64];
    /* 0x114 */ void (*open)(struct LabMenu *menu);
    /* 0x118 */ void (*close)(struct LabMenu *menu);
} LabMenu;

/* The mode's main task (func_8008E834) */
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

#endif /* STGDGLAB_H */
