#ifndef STPLNMET_H
#define STPLNMET_H

/* STPLNMET.PRO: mode 0x500, the player's name entry. */

#include "game.h"

/* The files of the screen */
#if VERSION_US
#define FILE_PLNMET_SPRITES 0x27C
#define FILE_PLNMET_KEYBOARD 0x762
#define FILE_PLNMET_IMAGE 0x896
#elif VERSION_EU
#define FILE_PLNMET_SPRITES 0x28B
#define FILE_PLNMET_KEYBOARD 0x771
#define FILE_PLNMET_IMAGE 0x8A7
#endif

/* Opens or closes a window: value goes 0 -> 0x1000 */
typedef struct NameTween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s32 step;
    /* 0x8 */ s32 value;
    /* 0xC */ s32 active;
} NameTween;

/* The windows of the name entry */
typedef struct PlayerNameWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *name;
    /* 0x08 */ TextWindow *tabs[3];
    /* 0x14 */ TextWindow *unk14[3];
    /* 0x20 */ TextWindow *unk20;
    /* 0x24 */ TextWindow *unk24;
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *unk2C;
    /* 0x30 */ TextWindow *unk30;
} PlayerNameWindows;

/* The name entry (as STDGNAME's) */
typedef struct PlayerNameTask {
    TASK_HEADER(PlayerNameTask);
    /* 0x50 */ s32 mode;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 vramX;
    /* 0x60 */ s32 vramY;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ u16 name[12];
    /* 0x90 */ s32 cursor;
    /* 0x94 */ s32 maxLength;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s32 unkB4;
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ NameTween unkBC;
    /* 0xCC */ NameTween unkCC;
    /* 0xDC */ NameTween unkDC;
    /* 0xEC */ void (*getName)(struct PlayerNameTask *task, char *out);
    /* 0xF0 */ void (*unkF0)(struct PlayerNameTask *task, s32 arg);
    /* 0xF4 */ void (*unkF4)(struct PlayerNameTask *task);
} PlayerNameTask;

/* Two scrolling sprites (STPLNMET_createScroll), once their image is loaded */
typedef struct NameScroll {
    TASK_HEADER(NameScroll);
    /* 0x50 */ s32 vramX;
    /* 0x54 */ s32 vramY;
    /* 0x58 */ s32 loaded;
    /* 0x5C */ s32 layer;
    /* 0x60 */ s32 depth;
    /* 0x64 */ s32 times[2];
    /* 0x6C */ s32 pos[2][2];
    /* 0x7C */ void (*load)(struct NameScroll *task, s32 x, s32 y);
    /* 0x80 */ void (*setLayer)(struct NameScroll *task, s32 layer, s32 depth);
} NameScroll;

/* An animated sprite (func_80082B80, func_80082D88) */
typedef struct NameSparkle {
    TASK_HEADER(NameSparkle);
    /* 0x50 */ s32 unk50[4];
    /* 0x60 */ s32 frame;
    /* 0x64 */ s32 time;
} NameSparkle;

/* func_80082F0C's task */
typedef struct NameDialog {
    TASK_HEADER(NameDialog);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} NameDialog;

/* The main task of the screen (STPLNMET_createScreen) */
typedef struct PlayerNameScreen {
    TASK_HEADER(PlayerNameScreen);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 unk58[5];
} PlayerNameScreen;

#endif /* STPLNMET_H */
