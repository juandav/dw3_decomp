#ifndef STDGNAME_H
#define STDGNAME_H

#include "name_entry.h"

/* The screen's files: the discs number them differently */
#if VERSION_US
#define STDGNAME_FILE_SPRITES 0x279
#define STDGNAME_FILE_IMAGES 0x27A
#define STDGNAME_FILE_KEYBOARD 0x762
#define STDGNAME_FILE_KEY_SPRITES 0x761
#elif VERSION_EU
#define STDGNAME_FILE_SPRITES 0x288
#define STDGNAME_FILE_IMAGES 0x289
#define STDGNAME_FILE_KEYBOARD 0x771
#define STDGNAME_FILE_KEY_SPRITES 0x770
#endif
#define STDGNAME_SPRITES (STDGNAME_FILE_SPRITES << 16) /* sprite bank */
#define STDGNAME_KEY_SPRITES (STDGNAME_FILE_KEY_SPRITES << 16) /* the keyboard's and partners' sprites */

/* A full-screen fade */
typedef struct FadeTask {
    TASK_HEADER(FadeTask);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 fadeIn;
    /* 0x5C */ s32 level; /* 8.8 fixed point */
    /* 0x60 */ s32 delta; /* added to level each frame */
    /* 0x64 */ void (*start)(struct FadeTask *task, s32 fadeIn, s32 duration);
} FadeTask;

/* A linear tween of a scale, 0 to 0x1000 */
typedef struct Tween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s32 step;
    /* 0x8 */ s32 value;
    /* 0xC */ s32 active;
} Tween;

typedef struct NameWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *name;
    /* 0x08 */ TextWindow *tabs[3];
    /* 0x14 */ TextWindow *unk14[3];
    /* 0x20 */ TextWindow *unk20;
    /* 0x24 */ TextWindow *unk24;
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *unk2C;
    /* 0x30 */ TextWindow *unk30;
} NameWindows;

typedef struct NameTask {
    TASK_HEADER(NameTask);
    /* 0x50 */ s32 mode;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 vramX;
    /* 0x60 */ s32 vramY;
    /* 0x64 */ s32 partner;
    /* 0x68 */ s32 partnerFrame;
    /* 0x6C */ s32 partnerTime;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ u16 name[12];
    /* 0x90 */ s32 cursor;
    /* 0x94 */ s32 maxLength;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 column;
    /* 0xA0 */ s32 row;
    /* 0xA4 */ s32 keyFrame;
    /* 0xA8 */ s32 keyTime;
    /* 0xAC */ s32 active;
    /* 0xB0 */ s32 page;
    /* 0xB4 */ s32 arrowFrame;
    /* 0xB8 */ s32 arrowTime;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ Tween unkC0;
    /* 0xD0 */ Tween unkD0;
    /* 0xE0 */ Tween unkE0;
    /* 0xF0 */ void (*getName)(struct NameTask *task, char *out);
    /* 0xF4 */ void (*unkF4)(struct NameTask *task);
} NameTask;

/* Where a window of the partner menu goes, and its text */
typedef struct MenuWindow {
    /* 0x0 */ s32 text;
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
} MenuWindow;

struct ScreenTask;

/* A sprite of the partner menu, that opens by scaling */
typedef struct MenuSprite {
    /* 0x00 */ s32 sprite; /* -1 ends the list */
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ s32 pivotX;
    /* 0x14 */ s32 pivotY;
    /* 0x18 */ s32 vertical;
} MenuSprite;

typedef struct MenuSlot {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 pivotX;
    /* 0xC */ s32 pivotY;
} MenuSlot;

/* A partner's animation in the partner menu */
typedef struct MenuAnim {
    /* 0x0 */ s32 frame;
    /* 0x4 */ s32 time;
} MenuAnim;

/* The partner menu */
typedef struct MenuTask {
    TASK_HEADER(MenuTask);
    /* 0x50 */ struct ScreenTask *screen;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 cursorClut;
    /* 0x5C */ MenuAnim anims[3];
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 partyCount;
    /* 0x7C */ s32 titleClut;
    /* 0x80 */ Tween tweens[6];
} MenuTask;

typedef struct ScreenChildren {
    /* 0x0 */ MenuTask *menu;
    /* 0x4 */ NameTask *name;
    /* 0x8 */ FadeTask *fade;
    /* 0xC */ Task *unkC;
} ScreenChildren;

/* The screen's controller */
typedef struct ScreenTask {
    TASK_HEADER(ScreenTask);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 scroll;
    /* 0x5C */ s32 tick;
    /* 0x60 */ s32 choice;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ void (*fadeOut)(struct ScreenTask *task);
} ScreenTask;

typedef struct ScreenFuncs {
    /* 0x00 */ TextStyle *style;
    /* 0x04 */ s32 partner;
    /* 0x08 */ void (*loadFiles)(void);
    /* 0x0C */ s32 (*isLoading)(void);
    /* 0x10 */ void (*startTween)(Tween *tween, s32 open);
    /* 0x14 */ s32 (*tickTween)(Tween *tween);
} ScreenFuncs;

extern NameKeyboard STDGNAME_keyboard;
extern TextStyle STDGNAME_nameStyle;
extern s32 STDGNAME_nameAnims[];
extern BigKey STDGNAME_bigKeys[];
extern s32 STDGNAME_keyArrowCluts[];
extern KeyTabs STDGNAME_keyPages[];
extern KeyPage STDGNAME_keyChars[];
#if VERSION_EU
/* the keyboard of language 0, three pages */
extern KeyTabs STDGNAME_keyPagesJp[];
extern KeyPage STDGNAME_keyCharsJp[];
#endif
extern MenuSprite D_8008710C[];
extern MenuSlot D_800872B0[];
extern MenuWindow D_800872E0[];
extern s32 D_800873A0[][7];
extern ScreenFuncs STDGNAME_funcs;

void STDGNAME_updateScene(Task *task, void **children);
Task *STDGNAME_start(void);
void STDGNAME_startFader(FadeTask *task, s32 fadeIn, s32 duration);
void STDGNAME_drawFader(FadeTask *task);
void STDGNAME_updateFader(FadeTask *task);
FadeTask *STDGNAME_createFader(void);
void STDGNAME_startTween(Tween *tween, s32 open);
s32 STDGNAME_updateTween(Tween *tween);
void STDGNAME_createNameWindows(NameTask *task, NameWindows *windows);
void STDGNAME_showNameWindows(NameTask *task, NameWindows *windows, s32 show);
void STDGNAME_drawKeyboard(NameTask *task);
void STDGNAME_updateKeyboard(NameTask *task, NameWindows *windows);
void STDGNAME_updateNameEntry(NameTask *task, NameWindows *windows);
void STDGNAME_setNameVram(NameTask *task, s32 x, s32 y);
void STDGNAME_setName(NameTask *task, char *name);
void STDGNAME_getName(NameTask *task, char *out);
void STDGNAME_closeNameEntry(NameTask *task);
NameTask *STDGNAME_createNameEntry(char *name, s32 partner);
void func_80084998(MenuTask *task, TextWindow **window, s32 index, s32 show);
void func_80084B0C(MenuTask *task, TextWindow **windows);
s32 func_800850E0(MenuTask *task, TextWindow **windows);
void func_80085354(MenuTask *task, TextWindow **windows);
MenuTask *STDGNAME_createMenu(ScreenTask *screen);
void STDGNAME_stepScreen(ScreenTask *task, ScreenChildren *children);
void STDGNAME_drawBackground(ScreenTask *task);
void STDGNAME_updateScreen(ScreenTask *task, ScreenChildren *children);
void STDGNAME_fadeOutScreen(ScreenTask *task);
ScreenTask *STDGNAME_createScreen(void);
void STDGNAME_loadFiles(void);
s32 STDGNAME_filesLoading(void);
void STDGNAME_startFade(Tween *tween, s32 open);
s32 STDGNAME_updateFade(Tween *tween);

#endif /* STDGNAME_H */
