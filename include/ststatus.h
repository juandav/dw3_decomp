#ifndef STSTATUS_H
#define STSTATUS_H

/* STSTATUS.PRO: the field menu's screens. createFieldMenu (in main) lists
   the options; picking one switches to this mode, which opens the screen of
   FIELD_MENU_CHOICE (STSTATUS_screens) and goes back to the field menu when
   it closes. Its strings are in files 0xB1, 0x6B, 0x64, 0x4F, 0x48, 0xA3 and
   0x9C. */

#include "game.h"

/* The menu's sprite sheet; the next file is its texture archive */
#if VERSION_US
#define FILE_STATUS_SPRITES 0x3F4
#define FILE_STATUS_BG 0x78A /* +2 in the second half of the game */
#elif VERSION_EU
#define FILE_STATUS_SPRITES 0x404
#define FILE_STATUS_BG 0x799
#endif

/* The mode's main task (func_80098DE4) */
typedef struct FieldMenuScreen {
    TASK_HEADER(FieldMenuScreen);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 blinkPos;
    /* 0x58 */ s32 blinkSkip;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 lateGame; /* STSTATUS_area.isLateGame() */
    /* 0x64 */ s32 bgFile;
    /* 0x68 */ s32 bgFile2;
    /* 0x6C */ s32 bgArchive;
    /* 0x70 */ s32 bgArchive1;
    /* 0x74 */ s32 bgArchive2;
} FieldMenuScreen;

typedef struct FieldMenuScreenChildren {
    /* 0x0 */ Task *fieldMenu;
    /* 0x4 */ Task *screen;
} FieldMenuScreenChildren;

/* Moves a value towards a target in fixed point */
typedef struct StatusLerp {
    /* 0x00 */ s32 duration;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 fixed; /* value << 8 */
    /* 0x10 */ s32 target;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 active;
} StatusLerp;

/* The screens' helpers (STSTATUS_funcs) */
typedef struct StatusFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(StatusLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(StatusLerp *lerp);
    /* 0x18 */ s32 *(*getList)(s32 list, s32 index);
    /* 0x1C */ void (*func_80099298)(s32 arg0, s32 arg1);
    /* 0x20 */ s32 (*canEquip)(s32 partner, s32 slot, s32 item);
    /* 0x24 */ void (*equip)(s32 partner, s32 slot, s32 item);
} StatusFuncs;

/* Where the game is (D_8009AA00) */
typedef struct StatusAreaFuncs {
    /* 0x0 */ s32 (*isLateGame)(void); /* -1 outside of the field */
    /* 0x4 */ s32 (*getArea)(void);
    /* 0x8 */ void (*func_800999CC)(s32 *out);
} StatusAreaFuncs;

extern StatusFuncs STSTATUS_funcs;

#endif /* STSTATUS_H */
