#ifndef STGMCARD_H
#define STGMCARD_H

/* STGMCARD.PRO: mode 0xC00, the memory card screen. */

#include "game.h"

/* The sprite archive of the screen */
#if VERSION_US
#define FILE_GMCARD_SPRITES 0x28F
#elif VERSION_EU
#define FILE_GMCARD_SPRITES 0x29E
#endif

/* The root task of the overlay (STGMCARD_start) */
typedef struct MemCardScene {
    TASK_HEADER(MemCardScene);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
} MemCardScene;

/* The main task of the screen (func_80087174) */
typedef struct MemCardScreen {
    TASK_HEADER(MemCardScreen);
    /* 0x50 */ s32 saving; /* the game mode's argument is not negative */
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
} MemCardScreen;

struct MemCardMenu;
struct MemCardPanel;
struct MemCardInfo;

/* The children of the save list */
typedef struct MemCardSavesWindows {
    /* 0x00 */ Task *unk0;
    /* 0x04 */ TextWindow *windows[5];
    /* 0x18 */ Cursor *cursor;
    /* 0x1C */ struct MemCardPanel *panel;
    /* 0x20 */ struct MemCardMenu *menu;
    /* 0x24 */ struct MemCardInfo *info;
} MemCardSavesWindows;

/* The saves of a memory card (func_80086BA0) */
typedef struct MemCardSaves {
    TASK_HEADER(MemCardSaves);
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 layer;
    /* 0x0058 */ s32 unk58[3];
    /* 0x0064 */ s32 port;
    /* 0x0068 */ s32 count;
    /* 0x006C */ s32 unk6C[2];
#if VERSION_US
    /* 0x0074 */ u8 unk74[0x2788];
#elif VERSION_EU
    /* 0x0074 */ u8 unk74[0x2790];
#endif
    /* 0x27FC */ s32 unk27FC; /* 0x2804 in the European version */
    /* 0x2800 */ u8 unk2800[0x4C];
    /* 0x284C */ void (*refresh)(struct MemCardSaves *saves);
    /* 0x2850 */ void (*hide)(struct MemCardSaves *saves);
} MemCardSaves;

/* The window with the selected save's details (func_80082E28) */
typedef struct MemCardInfo {
    TASK_HEADER(MemCardInfo);
    /* 0x50 */ MemCardSaves *saves;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 shown;
    /* 0x64 */ u8 unk64[0x20];
    /* 0x84 */ void (*show)(struct MemCardInfo *info);
    /* 0x88 */ void (*hide)(struct MemCardInfo *info);
    /* 0x8C */ void (*refresh)(struct MemCardInfo *info);
} MemCardInfo;

/* func_80083B10's task */
typedef struct MemCardMenu {
    TASK_HEADER(MemCardMenu);
    /* 0x50 */ MemCardSaves *saves;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ MenuLerp lerps[4];
    /* 0xCC */ s32 unkCC;
    /* 0xD0 */ s32 unkD0;
    /* 0xD4 */ s32 unkD4;
    /* 0xD8 */ s32 unkD8;
    /* 0xDC */ void (*reset)(struct MemCardMenu *menu);
    /* 0xE0 */ void (*unkE0)(struct MemCardMenu *menu);
    /* 0xE4 */ void (*unkE4)(struct MemCardMenu *menu, s32 arg);
    /* 0xE8 */ void (*unkE8)(struct MemCardMenu *menu);
    /* 0xEC */ void (*unkEC)(struct MemCardMenu *menu);
    /* 0xF0 */ void (*unkF0)(struct MemCardMenu *menu);
} MemCardMenu;

/* A gradient panel that opens by scaling (func_800833A0) */
typedef struct MemCardPanel {
    TASK_HEADER(MemCardPanel);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 x;
    /* 0x5C */ s32 y;
    /* 0x60 */ s32 w;
    /* 0x64 */ s32 h;
    /* 0x68 */ s32 done;
    /* 0x6C */ CVECTOR top;
    /* 0x70 */ CVECTOR bottom;
    /* 0x74 */ s32 duration;
    /* 0x78 */ s32 rate; /* 0x1000 / duration */
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 pivotX;
    /* 0x88 */ s32 pivotY;
    /* 0x8C */ VECTOR scale;
    /* 0x9C */ SVECTOR rot;
    /* 0xA4 */ MATRIX matrix;
    /* 0xC4 */ void (*reset)(struct MemCardPanel *panel);
    /* 0xC8 */ void (*start)(struct MemCardPanel *panel, s32 substate, s32 duration);
    /* 0xCC */ void (*setTopColor)(struct MemCardPanel *panel, u8 r, u8 g, u8 b);
    /* 0xD0 */ void (*setBottomColor)(struct MemCardPanel *panel, u8 r, u8 g, u8 b);
    /* 0xD4 */ void (*setPos)(struct MemCardPanel *panel, s32 x, s32 y);
} MemCardPanel;

/* The save's icon for the memory card's directory */
typedef struct SaveIcon {
    /* 0x0 */ CardClut *clut;
    /* 0x4 */ s32 frames[3];
} SaveIcon;

/* The overlay's buffers and helpers (STGMCARD_funcs) */
typedef struct MemCardScreenFuncs {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 *infoBuf;
    /* 0x10 */ u8 *dataBuf;
    /* 0x14 */ s32 infoSize;
    /* 0x18 */ s32 dataSize;
    /* 0x1C */ void (*loadFiles)(void);
    /* 0x20 */ s32 (*filesLoading)(void);
    /* 0x24 */ void (*freeBuffers)(void);
    /* 0x28 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x2C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x30 */ void (*startLerp)(MenuLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x34 */ s32 (*updateLerp)(MenuLerp *lerp);
} MemCardScreenFuncs;

#endif /* STGMCARD_H */
