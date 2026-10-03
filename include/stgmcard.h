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
