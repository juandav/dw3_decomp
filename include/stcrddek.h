#ifndef STCRDDEK_H
#define STCRDDEK_H

/*
 * STCRDDEK: the deck editor, where the player builds the three decks from
 * the cards they own and renames them on the keyboard (name_entry.h).
 */

#include "name_entry.h"

#if VERSION_US
#define STCRDDEK_FILE_SPRITES 0x62E /* as the card shop's */
#define STCRDDEK_FILE_IMAGES 0x632
#define STCRDDEK_FILE_CARDS 0x7E7 /* the card images, the first of five */
#define STCRDDEK_FILE_KEYBOARD 0x762
#define STCRDDEK_FILE_KEY_SPRITES 0x761
#elif VERSION_EU
#define STCRDDEK_FILE_SPRITES 0x63E
#define STCRDDEK_FILE_IMAGES 0x642
#define STCRDDEK_FILE_CARDS 0x7F6
#define STCRDDEK_FILE_KEYBOARD 0x771
#define STCRDDEK_FILE_KEY_SPRITES 0x770
#endif
#define STCRDDEK_SPRITES (STCRDDEK_FILE_SPRITES << 16) /* sprite bank */
#define STCRDDEK_IMAGES (STCRDDEK_FILE_IMAGES << 16) /* TIM archive */
#define STCRDDEK_KEY_SPRITES (STCRDDEK_FILE_KEY_SPRITES << 16) /* the keyboard's and partners' sprites */

/* The screen's helpers */
typedef struct DeckFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(MenuLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(MenuLerp *lerp);
} DeckFuncs;

/* The deck being edited */
typedef struct DeckEditor {
    TASK_HEADER(DeckEditor);
    /* 0x050 */ struct DeckScreen *screen;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 deck; /* GAME.decks[] */
    /* 0x060 */ s32 column; /* of the deck's grid, 9 cards a row */
    /* 0x064 */ s32 row;
    /* 0x068 */ s32 cursorFrame;
    /* 0x06C */ s32 cursorTime;
    /* 0x070 */ s32 cursorShown;
    /* 0x074 */ s32 listCursor; /* in the list of the cards owned */
    /* 0x078 */ s32 listTop;
    /* 0x07C */ s32 listCount;
    /* 0x080 */ s32 arrowsShown;
    /* 0x084 */ s32 arrowTime;
    /* 0x088 */ s16 list[315]; /* the cards owned and not in the deck */
    /* 0x2FE */ s8 owned[315]; /* how many of each card are not in the deck */
    /* 0x43C */ s32 infoShown; /* the card's info panel */
    /* 0x440 */ s32 blinkTime;
    /* 0x444 */ PanelAnim panels[5];
} DeckEditor;

/* A line of the list of the cards owned */
typedef struct CardLine {
    /* 0x0 */ TextWindow *name;
    /* 0x4 */ TextWindow *label;
    /* 0x8 */ TextWindow *count;
} CardLine;

typedef struct DeckEditorChildren {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *unk4;
    /* 0x08 */ TextWindow *deckName;
    /* 0x0C */ TextWindow *kinds[6];
    /* 0x24 */ TextWindow *cardName;
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *unk2C;
    /* 0x30 */ TextWindow *unk30;
    /* 0x34 */ TextWindow *unk34;
    /* 0x38 */ TextWindow *unk38;
    /* 0x3C */ TextWindow *unk3C;
    /* 0x40 */ TextWindow *unk40;
    /* 0x44 */ TextWindow *listCardName;
    /* 0x48 */ TextWindow *unk48;
    /* 0x4C */ TextWindow *unk4C;
    /* 0x50 */ TextWindow *unk50;
    /* 0x54 */ TextWindow *unk54;
    /* 0x58 */ TextWindow *unk58;
    /* 0x5C */ TextWindow *unk5C;
    /* 0x60 */ TextWindow *unk60;
    /* 0x64 */ CardLine lines[8];
    /* 0xC4 */ Cursor *cursor;
    /* 0xC8 */ TextWindow *message;
    /* 0xCC */ struct DeckCards *cards;
    /* 0xD0 */ ScrollBar *scrollBar;
} DeckEditorChildren;

/* Draws the deck's cards, appearing one per frame */
typedef struct DeckCards {
    TASK_HEADER(DeckCards);
    /* 0x50 */ DeckEditor *editor;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 count; /* cards shown so far */
    /* 0x60 */ u8 unk60[0x10];
} DeckCards;

/* A task that waits for triangle; nothing creates it */
typedef struct DeckIdle {
    TASK_HEADER(DeckIdle);
    /* 0x50 */ void *parent;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ u8 unk5C[0x10];
} DeckIdle;

/* A deck's row on the screen: its name and how many cards of each kind it has */
typedef struct DeckRow {
    /* 0x00 */ TextWindow *name;
    /* 0x04 */ TextWindow *counts[6];
} DeckRow;

typedef struct DeckScreenChildren {
    /* 0x00 */ NameEntry *name; /* or the DeckEditor */
    /* 0x04 */ TextWindow *title;
    /* 0x08 */ DeckRow rows[3];
    /* 0x5C */ TextWindow *unk5C[2];
    /* 0x64 */ Cursor *cursor;
    /* 0x68 */ ScreenFade *fader;
} DeckScreenChildren;

/* The screen's controller: the three decks to choose from */
typedef struct DeckScreen {
    TASK_HEADER(DeckScreen);
    /* 0x050 */ s32 layer;
    /* 0x054 */ s32 depth;
    /* 0x058 */ s32 scroll; /* of the background */
    /* 0x05C */ s32 tick;
    /* 0x060 */ s32 deck; /* under the cursor */
    /* 0x064 */ s32 chosen;
    /* 0x068 */ s32 cursorFrame;
    /* 0x06C */ s32 cursorTime;
    /* 0x070 */ s32 renaming;
    /* 0x074 */ s32 kinds[3][6]; /* how many cards of each kind a deck has */
    /* 0x0BC */ PanelAnim panels[3];
    /* 0x0EC */ PanelAnim rowPanels[3];
    /* 0x11C */ void (*countKinds)(struct DeckScreen *task); /* STCRDDEK_countCardKinds */
} DeckScreen;

extern DeckFuncs STCRDDEK_funcs;

#endif /* STCRDDEK_H */
