#ifndef CNTY_SEL_H
#define CNTY_SEL_H

/*
 * CNTY_SEL.PRO: the country select screen.
 *
 * A background scrolls diagonally, three panels open one after the other and
 * a highlighted option blinks until Start is pressed. Then the option flashes,
 * the panels close, the screen fades to black and the game moves on to mode
 * 0xE01. The choice itself is not stored anywhere.
 */

#include "game.h"

/*
 * The screen's tasks use the engine states (task.h); the owner sets TASK_DONE
 * to make a task fade out, flash, or open/close its panel.
 */

/* Entries of file 0x892, read with FILE_CACHE_GET_ENTRY[0] */
#define CNTY_SEL_SPRITES 0x08920000 /* sprite bank */
#define CNTY_SEL_IMAGES 0x08920001  /* TIM archive for VRAM */

/* Sprites in the sprite bank */
#define SPRITE_BACKGROUND 0
#define SPRITE_RIGHT_PANEL 1
#define SPRITE_TOP_PANEL 2
#define SPRITE_LEFT_PANEL 3
#define SPRITE_OPTIONS 4 /* one per option */

/* Draw layer of the screen */
#define CNTY_SEL_LAYER 0x100

/* Sounds (SOUND_STATE.playSound) */
#define CNTY_SEL_SOUND_BANK 0x21
#define CNTY_SEL_MUSIC 0x60840002
#define SE_CURSOR 0x4001B
#define SE_START 0x4001C

/* Pad buttons, as bit numbers of the pad word */
#define BUTTON_START 3
#define BUTTON_UP 4
#define BUTTON_RIGHT 5
#define BUTTON_DOWN 6
#define BUTTON_LEFT 7

/* One frame of a sprite animation; frame 0xFF ends it */
typedef struct AnimFrame {
    /* 0x0 */ s16 frame;
    /* 0x2 */ s16 duration;
} AnimFrame;

typedef struct AnimState {
    /* 0x0 */ s16 index;
    /* 0x2 */ s16 timer;
} AnimState;

/* A linear tween of a panel's scale */
typedef struct PanelTween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s16 to;
    /* 0x6 */ s16 from;
} PanelTween;

typedef struct LeftPanelTween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s16 to;
    /* 0x6 */ s16 from;
    /* 0x8 */ s32 unk8;
} LeftPanelTween;

/* The scrolling background, which also fades the screen out */
typedef struct BackgroundTask {
    TASK_HEADER(BackgroundTask);
    /* 0x50 */ s16 scroll;
    /* 0x52 */ s16 fade;
} BackgroundTask;

/* The highlighted option */
typedef struct CursorTask {
    TASK_HEADER(CursorTask);
    /* 0x50 */ s32 blink;
    /* 0x54 */ s16 selection;
    /* 0x56 */ s16 frame;
    /* 0x58 */ AnimState anim;
    /* 0x5C */ void (*setSelection)(struct CursorTask *task, s16 selection);
} CursorTask;

/* A panel that opens and closes by scaling */
typedef struct PanelTask {
    TASK_HEADER(PanelTask);
    /* 0x50 */ s16 phase; /* 0: opening, 1: closing */
    /* 0x52 */ s16 time;
    /* 0x54 */ s16 scaleX;
    /* 0x56 */ s16 scaleY;
} PanelTask;

typedef struct MenuChildren {
    /* 0x00 */ CursorTask *cursor;
    /* 0x04 */ PanelTask *rightPanel;
    /* 0x08 */ PanelTask *topPanel;
    /* 0x0C */ PanelTask *leftPanel;
    /* 0x10 */ BackgroundTask *background;
} MenuChildren;

/* The screen's controller */
typedef struct MenuTask {
    TASK_HEADER(MenuTask);
    /* 0x50 */ s16 selection;
    /* 0x52 */ s16 timer;
} MenuTask;

/* MenuTask substates (Task.substate) in TASK_RUN */
enum MenuStep {
    MENU_OPEN_RIGHT_PANEL,
    MENU_WAIT_RIGHT_PANEL,
    MENU_OPEN_LEFT_PANEL,
    MENU_WAIT_LEFT_PANEL,
    MENU_OPEN_TOP_PANEL,
    MENU_WAIT_TOP_PANEL,
    MENU_SHOW_CURSOR,
    MENU_SELECT,
    MENU_WAIT_FLASH,
    MENU_CLOSE_PANELS,
    MENU_WAIT_PANELS,
    MENU_FADE_OUT,
    MENU_WAIT_FADE,
    MENU_EXIT,
};

extern RECT CNTY_SEL_screenRect;
extern RECT CNTY_SEL_vramRect;
extern RECT CNTY_SEL_fadeRect;
extern AnimFrame CNTY_SEL_cursorFlash[];
extern PanelTween CNTY_SEL_topPanelTweens[];
extern PanelTween CNTY_SEL_rightPanelTweens[];
extern LeftPanelTween CNTY_SEL_leftPanelTweens[];

void CNTY_SEL_tickScreen(Task *task, MenuTask **menu);
Task *CNTY_SEL_start(void);
void CNTY_SEL_drawBackground(BackgroundTask *task);
s32 CNTY_SEL_getFadeLevel(s32 time);
void CNTY_SEL_drawFade(s32 level);
void CNTY_SEL_tickBackground(BackgroundTask *task);
BackgroundTask *CNTY_SEL_startBackgroundTask(void);
s16 CNTY_SEL_stepAnimation(AnimState *anim, AnimFrame *frames, s32 depth);
void CNTY_SEL_drawCursor(CursorTask *task);
void CNTY_SEL_setCursorSelection(CursorTask *task, s16 selection);
void CNTY_SEL_tickCursor(CursorTask *task);
CursorTask *CNTY_SEL_startCursorTask(void);
s32 CNTY_SEL_getTopPanelScale(PanelTask *task, s32 phase);
void CNTY_SEL_drawTopPanel(PanelTask *task);
void CNTY_SEL_tickTopPanel(PanelTask *task);
PanelTask *CNTY_SEL_startTopPanelTask(void);
s32 CNTY_SEL_getRightPanelScale(PanelTask *task, s32 phase);
void CNTY_SEL_drawRightPanel(PanelTask *task);
void CNTY_SEL_tickRightPanel(PanelTask *task);
PanelTask *CNTY_SEL_startRightPanelTask(void);
s32 CNTY_SEL_getLeftPanelScale(PanelTask *task, s32 phase);
void CNTY_SEL_drawLeftPanel(PanelTask *task);
void CNTY_SEL_tickLeftPanel(PanelTask *task);
PanelTask *CNTY_SEL_startLeftPanelTask(void);
void CNTY_SEL_tickMenu(MenuTask *task, MenuChildren *children);
MenuTask *CNTY_SEL_startMenuTask(void);

#endif /* CNTY_SEL_H */
