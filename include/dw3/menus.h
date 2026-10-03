#ifndef DW3_MENUS_H
#define DW3_MENUS_H

/* The inn, the screen fade and the field menu (inn.c, system.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "dw3/task.h"
#include "dw3/graphics.h"
#include "dw3/text.h"

/*
 * Opens or closes a menu panel: level goes 0 -> 0x1000 in `duration` frames
 * (or back at twice the speed), and the panel is drawn scaled by it.
 */
typedef struct PanelAnim {
    s32 duration;
    s32 step;
    s32 level;
    s32 active;
} PanelAnim;

/* Fades the whole screen to black and back with a subtractive rectangle */
typedef struct ScreenFade {
    TASK_HEADER(ScreenFade);
    /* 0x50 */ s32 layerId;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 fadeIn; /* 0: to black */
    /* 0x5C */ s32 level; /* 0-0xFF00 */
    /* 0x60 */ s32 levelStep;
    /* 0x64 */ void (*start)(); /* (fade, fadeIn, frames); state 2 when done */
} ScreenFade;

/* A vertical scroll bar, as the menu overlays (STSTATUS, STGDGLAB) draw one */
typedef struct ScrollBar {
    TASK_HEADER(ScrollBar);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 x;
    /* 0x5C */ s32 y;
    /* 0x60 */ s32 width;
    /* 0x64 */ s32 size; /* of the thumb, in fixed point */
    /* 0x68 */ s32 hasCount;
    /* 0x6C */ s32 pageSize;
    /* 0x70 */ s32 count;
    /* 0x74 */ s32 pos;
    /* 0x78 */ s32 hasRange;
    /* 0x7C */ s32 top;
    /* 0x80 */ s32 bottom;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 posStep; /* fixed point */
    /* 0x8C */ void (*setX)(struct ScrollBar *bar, s32 x, s32 width);
    /* 0x90 */ void (*setRange)(struct ScrollBar *bar, s32 top, s32 bottom);
    /* 0x94 */ void (*setCount)(struct ScrollBar *bar, s32 pageSize, s32 count);
    /* 0x98 */ void (*setPos)(struct ScrollBar *bar, s32 pos);
} ScrollBar;

/*
 * The inn: pay INNS[inn].price per party member to restore HP, MP and
 * status, with a fade to black and a jingle. `step` is set when the money
 * is not enough.
 */
typedef struct Inn {
    TASK_HEADER(Inn);
    /* 0x50 */ s32 layerId;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 inn;
    /* 0x5C */ s32 choice; /* 0 yes, 1 no */
    /* 0x60 */ s32 count; /* party members */
    /* 0x64 */ s32 music;
    /* 0x68 */ s32 time;
    /* 0x6C */ PanelAnim panels[3];
} Inn;

typedef struct InnChildren {
    /* 0x00 */ struct ScreenFade *fade;
    /* 0x04 */ TextWindow *windows[6];
    /* 0x1C */ Cursor *cursor;
} InnChildren;

/* One party member in the field menu: name and five stats */
typedef struct PartnerPage {
    /* 0x00 */ TextWindow *name;
    /* 0x04 */ TextWindow *labels[5];
    /* 0x18 */ TextWindow *values[5];
} PartnerPage;

/* The children of the field menu */
typedef struct FieldMenuWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *moneyLabel;
    /* 0x08 */ TextWindow *money;
    /* 0x0C */ TextWindow *options[6];
    /* 0x24 */ struct Cursor *cursor;
    /* 0x28 */ PartnerPage pages[3];
} FieldMenuWindows;

/* Where a window goes, and the string it shows */
typedef struct WindowPos {
    /* 0x0 */ s32 string;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 y;
    /* 0xA */ s16 unkA;
} WindowPos;

void updateInn(struct Inn *task, struct InnChildren *data);
void screenFadeStart(ScreenFade *task, s32 fadeIn, s32 duration);
void drawScreenFade(struct ScreenFade *task);
void updateScreenFade(struct ScreenFade *task);
void updateFieldMenu();

#endif /* DW3_MENUS_H */
