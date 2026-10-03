#ifndef STGMCARD_H
#define STGMCARD_H

/* STGMCARD.PRO: mode 0xC00, the memory card screen. */

#include "game.h"

/* The sprite archive of the screen */
#if VERSION_US
#define FILE_GMCARD_SPRITES 0x28F
#define FILE_GMCARD_SHEET 0x28E /* the sprite sheet of its images */
#elif VERSION_EU
#define FILE_GMCARD_SPRITES 0x29E
#define FILE_GMCARD_SHEET 0x29D
#endif

/* The root task of the overlay (STGMCARD_start) */
typedef struct MemCardScene {
    TASK_HEADER(MemCardScene);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
} MemCardScene;

/* A mode (or stage) the screen can be opened from, and the value the screen
   takes from it (D_800879D8, which ends with a zero mode) */
typedef struct MemCardModeEntry {
    /* 0x0 */ u8 value;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 mode;
} MemCardModeEntry;

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
struct MemCardSaves;

/* The children of the main task */
typedef struct MemCardScreenTasks {
    /* 0x0 */ struct MemCardSaves *saves;
    /* 0x4 */ ScreenFade *fade;
} MemCardScreenTasks;

/* The children of the save list */
typedef struct MemCardSavesWindows {
    /* 0x00 */ TextWindow *unk0;
    /* 0x04 */ TextWindow *windows[5];
    /* 0x18 */ Cursor *cursor;
    /* 0x1C */ struct MemCardPanel *panel;
    /* 0x20 */ struct MemCardMenu *menu;
    /* 0x24 */ struct MemCardInfo *info;
} MemCardSavesWindows;

/* The play time, as GameState keeps it from playFrames */
typedef struct PlayTime {
    /* 0x0 */ s32 frames;
    /* 0x4 */ s16 hours;
    /* 0x6 */ s16 minutes;
    /* 0x8 */ s16 seconds;
    /* 0xA */ s16 maxed;
} PlayTime;

/* A save of the memory card, as the list shows it */
typedef struct MemCardSave {
    /* 0x00 */ u8 name[0x18]; /* empty for a free slot */
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 money;
    /* 0x24 */ PlayTime time;
    /* 0x30 */ s32 partners[3]; /* 3 and up: a partner, whose animation the
                                   details show */
    /* 0x3C */ s16 levels[3];
    /* 0x42 */ s16 unk42;
} MemCardSave;

/* The memory card's info section: the three slots' saves, as the list shows
   them (STGMCARD_funcs.infoBuf, and the list's copy) */
typedef struct MemCardFile {
    /* 0x00 */ u8 checksum; /* of the rest, from magic */
    /* 0x01 */ u8 last; /* the slot last saved to */
    /* 0x02 */ u8 version; /* MEMCARD_SAVE_VERSION */
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s32 magic; /* "DMW3" */
    /* 0x08 */ MemCardSave saves[3];
} MemCardFile;

#define MEMCARD_FILE_MAGIC 0x33574D44

/* The saved part of the game state, GAME's first bytes: a save's data
   section. Its bytes 0 and 2 hold the checksum of the rest, from byte 4, and
   MEMCARD_SAVE_VERSION. */
#if VERSION_US
#define GAME_SAVE_SIZE 0x26BC
#define MEMCARD_SAVE_VERSION 3
#elif VERSION_EU
#define GAME_SAVE_SIZE 0x26C4
#define MEMCARD_SAVE_VERSION 4
#endif

/* The durations of the panels shown while loading and saving */
#if VERSION_US
#define MEMCARD_LOAD_FRAMES 1239
#define MEMCARD_SAVE_FRAMES 1266
#elif VERSION_EU
#define MEMCARD_LOAD_FRAMES 1240
#define MEMCARD_SAVE_FRAMES 1267
#endif

typedef struct GameSave {
    /* 0x0000 */ s32 data[GAME_SAVE_SIZE / 4];
} GameSave;

/* MEMCARD followed by MEMCARD_FUNCS, as func_800844DC reaches the functions:
   through MEMCARD's address */
typedef struct MemCardSystem {
    /* 0x000 */ MemCard card;
    /* 0x328 */ MemCardFuncs funcs;
} MemCardSystem;

#define MEMCARD_SYSTEM (*(MemCardSystem *)&MEMCARD)

/* A text window of the details (D_800876BC) */
typedef struct MemCardWindowSpec {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 type;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ s32 unk10;
} MemCardWindowSpec;

/* The saves of a memory card (func_80086BA0) */
typedef struct MemCardSaves {
    TASK_HEADER(MemCardSaves);
    /* 0x0050 */ MemCardScreen *screen;
    /* 0x0054 */ s32 layer;
    /* 0x0058 */ s32 unk58[3];
    /* 0x0064 */ s32 port;
    /* 0x0068 */ s32 count;
    /* 0x006C */ MemCardFile file; /* the card's */
    /* 0x0140 */ u8 unk140[GAME_SAVE_SIZE];
    /* 0x27FC */ s32 choice; /* of a yes/no question, 0 for yes; 0x2804 in the
                                European version, as all below */
    /* 0x2800 */ MenuLerp slide[2]; /* the list's x and y offsets */
    /* 0x2838 */ s32 unk2838;
    /* 0x283C */ s32 blinkTime;
    /* 0x2840 */ s32 blinkFrame;
    /* 0x2844 */ s32 unk2844;
    /* 0x2848 */ s32 unk2848;
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
    /* 0x64 */ s32 time;
    /* 0x68 */ s32 frames[3]; /* of the three partners' animations */
    /* 0x74 */ PanelAnim fade;
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
    /* 0xD0 */ s32 blinkTime;
    /* 0xD4 */ s32 blinkFrame;
    /* 0xD8 */ s32 blinkDown; /* the frame counts down */
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
    /* 0x04 */ s32 slot; /* the selected one */
    /* 0x08 */ s32 unk8;
    /* 0x0C */ MemCardFile *infoBuf;
    /* 0x10 */ GameState *dataBuf; /* the saved part of the game state */
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
