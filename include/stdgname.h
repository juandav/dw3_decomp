#ifndef STDGNAME_H
#define STDGNAME_H

#include "game.h"

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

/* The character pages of the keyboard */
typedef struct Keyboard {
    /* 0x0 */ s32 pageCount;
    /* 0x4 */ s32 *tabTexts; /* three per page */
    /* 0x8 */ s8 (*keys)[7][15][2];
} Keyboard;

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

/* The partner menu */
typedef struct MenuTask {
    TASK_HEADER(MenuTask);
    /* 0x50 */ struct ScreenTask *screen;
    /* 0x54 */ s32 layer;
    /* 0x58 */ u8 unk58[0x20];
    /* 0x78 */ s32 partyCount;
    /* 0x7C */ s32 unk7C;
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

extern Keyboard D_8008837C;
extern TextStyle D_80086FC0;
extern s32 D_80086EE0[];
extern s8 D_80086EEC[][7][15][2];
extern MenuWindow D_800872E0[];
extern ScreenFuncs D_80087480;

void func_80082724(Task *task, void **children);
Task *func_8008281C(void);
void func_80082848(FadeTask *task, s32 fadeIn, s32 duration);
void func_800828D0(FadeTask *task);
void func_80082A14(FadeTask *task);
FadeTask *func_80082AC8(void);
void func_80082B10(Tween *tween, s32 open);
s32 func_80082BA4(Tween *tween);
void func_80082C10(NameTask *task, NameWindows *windows);
void func_80082E00(NameTask *task, NameWindows *windows, s32 show);
void func_80083104(NameTask *task);
void func_80083A30(NameTask *task, NameWindows *windows);
void func_80084640(NameTask *task, NameWindows *windows);
void func_80084744(NameTask *task, s32 x, s32 y);
void func_80084750(NameTask *task, char *name);
void func_800847E4(NameTask *task, char *out);
void func_800848E4(NameTask *task);
NameTask *func_800848F0(char *name, s32 partner);
void func_80084998(MenuTask *task, TextWindow **window, s32 index, s32 show);
void func_80084B0C(MenuTask *task, TextWindow **windows);
s32 func_800850E0(MenuTask *task, TextWindow **windows);
void func_80085354(MenuTask *task, TextWindow **windows);
MenuTask *func_800856B4(ScreenTask *screen);
void func_800856F4(ScreenTask *task, ScreenChildren *children);
void func_800858D8(ScreenTask *task);
void func_800859CC(ScreenTask *task, ScreenChildren *children);
void func_80085ADC(ScreenTask *task);
ScreenTask *func_80085B20(void);
void func_80085B60(void);
s32 func_80085C08(void);
void func_80085C78(Tween *tween, s32 open);
s32 func_80085D0C(Tween *tween);

#endif /* STDGNAME_H */
