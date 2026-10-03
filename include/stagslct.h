#ifndef STAGSLCT_H
#define STAGSLCT_H

/* STAGSLCT.PRO: the debug stage select (scene 0x1500), a menu of every
   scene of the game with some debug settings on the second controller */

#include "game.h"

/* One line of the menu; the list ends with scene -1 and scene 0 lines are
   separators the cursor skips */
typedef struct StageSelectEntry {
    /* 0x0 */ char *name;
    /* 0x4 */ char *title;
    /* 0x8 */ s32 scene;
    /* 0xC */ s32 arg; /* bit 15: go through GAME.funcs.requestMode */
} StageSelectEntry;

typedef struct StageSelect {
    TASK_HEADER(StageSelect);
    /* 0x50 */ s32 cursor; /* line on screen */
    /* 0x54 */ s32 top;    /* first entry shown */
    /* 0x58 */ s32 lines;  /* lines on screen */
    /* 0x5C */ s32 count;  /* entries */
    /* 0x60 */ s32 biosShown;
    /* 0x64 */ s32 fading;
    /* 0x68 */ s32 fade;
    /* 0x6C */ s32 fadeStep;
} StageSelect;

typedef struct StageSelectWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *cursor;
    /* 0x08 */ TextWindow *names[14];
    /* 0x40 */ TextWindow *titles[14];
    /* 0x78 */ TextWindow *bios;
    /* 0x7C */ TextWindow *unk7C;
    /* 0x80 */ TextWindow *region;
    /* 0x84 */ TextWindow *unk84; /* GAME_PROGRESS */
    /* 0x88 */ TextWindow *unk88; /* D_80042728.unk0 */
    /* 0x8C */ TextWindow *unk8C; /* party member 0: unk32 */
    /* 0x90 */ TextWindow *unk90; /* party member 0: level */
    /* 0x94 */ TextWindow *unk94; /* D_80042728.unk4 */
    /* 0x98 */ TextWindow *unk98; /* D_80042728.unk8 */
} StageSelectWindows;

#endif /* STAGSLCT_H */
