#ifndef STPLNMET_H
#define STPLNMET_H

/* STPLNMET.PRO: mode 0x500, the player's name entry. */

#include "game.h"

/* The files of the screen */
#if VERSION_US
#define FILE_PLNMET_SPRITES 0x27C
#define FILE_PLNMET_KEYBOARD 0x762
#define FILE_PLNMET_IMAGE 0x896
#define FILE_PLNMET_MENU 0x27B
#define FILE_PLNMET_BANK 0x761
#define FILE_PLNMET_SCROLL 0x2B5
#elif VERSION_EU
#define FILE_PLNMET_SPRITES 0x28B
#define FILE_PLNMET_KEYBOARD 0x771
#define FILE_PLNMET_IMAGE 0x8A7
#define FILE_PLNMET_MENU 0x28A
#define FILE_PLNMET_BANK 0x770
#define FILE_PLNMET_SCROLL 0x2C4
#endif
#define PLNMET_MENU (FILE_PLNMET_MENU << 16) /* sprite bank */
#define PLNMET_BANK (FILE_PLNMET_BANK << 16) /* the keyboard's and partners' sprites */
#define PLNMET_SCROLL (FILE_PLNMET_SCROLL << 16)

/*
 * The Japanese keyboard (three pages) is for language 0 of the European
 * version; the USA version keeps the code that handles it, never run.
 */
#if VERSION_US
#define PLNMET_JAPANESE 0
#elif VERSION_EU
#define PLNMET_JAPANESE (LANGUAGE == 0)
#endif

/* A sprite of the bank drawn per language, one after the other (USA: the first) */
#if VERSION_US
#define PLNMET_TEXT_SPRITE(sprite) ((sprite) + 1)
#elif VERSION_EU
#define PLNMET_TEXT_SPRITE(sprite) (LANGUAGE + (sprite))
#endif

/* A key of the keyboard bigger than one cell: its sprite and where it goes */
typedef struct BigKey {
    /* 0x0 */ s32 sprite;
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
} BigKey;

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

/* A keyboard cell: 1 starts a key, 0 is empty and negative cells belong to a wide key */
typedef struct NameKey {
    /* 0x0 */ s8 kind;
    /* 0x1 */ u8 code;
} NameKey;

/* A page of the keyboard: 7 rows of 15 cells */
typedef struct KeyPage {
    /* 0x0 */ NameKey cells[7][15];
} KeyPage;

/* The texts of a keyboard page's three tabs */
typedef struct KeyTabs {
    /* 0x0 */ s32 texts[3];
} KeyTabs;

/* The character pages of the keyboard (as STDGNAME's) */
typedef struct NameKeyboard {
    /* 0x0 */ s32 pageCount;
    /* 0x4 */ KeyTabs *tabTexts; /* one per page */
    /* 0x8 */ KeyPage *pages;
} NameKeyboard;

/* The name entry (as STDGNAME's) */
typedef struct PlayerNameTask {
    TASK_HEADER(PlayerNameTask);
    /* 0x50 */ s32 mode;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 vramX;
    /* 0x60 */ s32 vramY;
    /* 0x64 */ s32 partner;
    /* 0x68 */ s32 partnerFrame;
    /* 0x6C */ s32 partnerTime;
    /* 0x70 */ s32 clutRow;
    /* 0x74 */ s32 clutTime;
    /* 0x78 */ u16 name[12];
    /* 0x90 */ s32 cursor;
    /* 0x94 */ s32 maxLength;
    /* 0x98 */ s32 column;
    /* 0x9C */ s32 row;
    /* 0xA0 */ s32 keyFrame;
    /* 0xA4 */ s32 keyTime;
    /* 0xA8 */ s32 active;
    /* 0xAC */ s32 page;
    /* 0xB0 */ s32 arrowFrame;
    /* 0xB4 */ s32 arrowTime;
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

/* A frame of func_80082D88's animation: 0 ends */
typedef struct SparkleFrame {
    /* 0x0 */ s32 delay;
    /* 0x4 */ s32 sprite;
} SparkleFrame;

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
    /* 0x54 */ s32 clutRow;
    /* 0x58 */ s32 unk58;
} NameDialog;

typedef struct NameDialogWindows {
    /* 0x0 */ TextWindow *text;
    /* 0x4 */ TextWindow *arrow; /* follows the text, blinks while it waits */
} NameDialogWindows;

/* The main task of the screen (STPLNMET_createScreen) */
typedef struct PlayerNameScreen {
    TASK_HEADER(PlayerNameScreen);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 page; /* 0 the name, 1 the partners, 2 the confirmation */
    /* 0x5C */ PanelAnim fade;
} PlayerNameScreen;

typedef struct PlayerNameScreenChildren {
    /* 0x00 */ struct NameDialog *dialog;
    /* 0x04 */ PlayerNameTask *name;
    /* 0x08 */ struct PartnerChoice *partners;
    /* 0x0C */ struct NameConfirm *confirm;
    /* 0x10 */ NameScroll *scroll;
    /* 0x14 */ NameSparkle *sparkleA;
    /* 0x18 */ NameSparkle *sparkleB;
    /* 0x1C */ TextWindow *tabs[3];
} PlayerNameScreenChildren;

/* The confirmation of the name and the partners (func_800863E8) */
typedef struct NameConfirm {
    TASK_HEADER(NameConfirm);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 choice; /* STPLNMET_funcs.choices */
    /* 0x60 */ s32 cursor; /* 0 yes, 1 no */
    /* 0x64 */ s32 clutRow;
    /* 0x68 */ s32 clutTime;
    /* 0x6C */ u16 *name;
    /* 0x70 */ s32 frames[3];
    /* 0x7C */ s32 frameTime;
    /* 0x80 */ s32 progress; /* 0-100 */
    /* 0x84 */ VECTOR scale;
    /* 0x94 */ SVECTOR rot;
    /* 0x9C */ MATRIX matrix;
    /* 0xBC */ PanelAnim tweenA;
    /* 0xCC */ PanelAnim tweenB;
    /* 0xDC */ void (*hide)(struct NameConfirm *task, s32 hide);
    /* 0xE0 */ void (*unkE0)(struct NameConfirm *task);
} NameConfirm;

typedef struct NameConfirmWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *name;
    /* 0x08 */ TextWindow *unk8;
    /* 0x0C */ TextWindow *unkC;
    /* 0x10 */ TextWindow *unk10;
    /* 0x14 */ TextWindow *yes;
    /* 0x18 */ TextWindow *no;
    /* 0x1C */ Cursor *cursor;
} NameConfirmWindows;

/* The choice of the partners (func_80086F30) */
typedef struct PartnerChoice {
    TASK_HEADER(PartnerChoice);
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 frames[3];
    /* 0x68 */ s32 frameTime;
    /* 0x6C */ s32 choice; /* STPLNMET_funcs.choices */
    /* 0x70 */ s32 arrowFrame;
    /* 0x74 */ s32 arrowTime;
    /* 0x78 */ u8 unk78[0x88 - 0x78];
    /* 0x88 */ void (*hide)(struct PartnerChoice *task, s32 hide);
} PartnerChoice;

typedef struct PartnerChoiceWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *labels[3];
    /* 0x10 */ TextWindow *name;
    /* 0x14 */ TextWindow *text;
    /* 0x18 */ struct {
        TextWindow *name;
        TextWindow *text;
    } partners[3];
} PartnerChoiceWindows;

/* A partner's animation: its frames, -1 ends */
typedef struct PartnerAnim {
    /* 0x0 */ s32 frames[7];
} PartnerAnim;

/* The screen's helpers (STPLNMET_funcs) */
typedef struct PlayerNameFuncs {
    /* 0x00 */ PartnerAnim *anims;
    /* 0x04 */ s32 (*choices)[3]; /* three partners each */
    /* 0x08 */ void (*loadFiles)(void);
    /* 0x0C */ s32 (*filesLoading)(void);
    /* 0x10 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x14 */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x18 */ void (*startLerp)(MenuLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x1C */ s32 (*updateLerp)(MenuLerp *lerp);
} PlayerNameFuncs;

extern PlayerNameFuncs STPLNMET_funcs;

#endif /* STPLNMET_H */
