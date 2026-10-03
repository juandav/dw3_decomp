#ifndef STCRDABM_H
#define STCRDABM_H

/* STCRDABM.PRO: the card album (scene 0x1200). 27 pages of 12 cards, the
   cards the player has are shown with their icon and numbers, the others
   as empty slots. */

#include "game.h"

#define CARD_COUNT 315
#define ALBUM_PAGE_CARDS 12

/* The album's files: the discs number them differently */
#if VERSION_US
#define STCRDABM_FILE_SPRITES 0x5F5
#define STCRDABM_FILE_IMAGES 0x5F6
#define STCRDABM_FILE_DATA 0x7E7 /* the first of five */
#elif VERSION_EU
#define STCRDABM_FILE_SPRITES 0x605
#define STCRDABM_FILE_IMAGES 0x606
#define STCRDABM_FILE_DATA 0x7F6
#endif
#define STCRDABM_SPRITES (STCRDABM_FILE_SPRITES << 16) /* sprite bank */
#define STCRDABM_IMAGES (STCRDABM_FILE_IMAGES << 16)   /* TIM archive */

/* Fades the screen to or from black with a subtractive rectangle */
typedef struct CardAlbumFader {
    TASK_HEADER(CardAlbumFader);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 fadeIn;
    /* 0x5C */ s32 level; /* 0..0xFF00 */
    /* 0x60 */ s32 levelStep;
    /* 0x64 */ void (*start)(struct CardAlbumFader *fader, s32 fadeIn, s32 frames);
} CardAlbumFader;

/* Draws the cards of a page and animates the page turns */
typedef struct CardAlbumGrid {
    TASK_HEADER(CardAlbumGrid);
    /* 0x50 */ struct CardAlbum *album;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 first;     /* first card of the page */
    /* 0x60 */ s32 prevFirst; /* the page being turned */
    /* 0x64 */ s32 shown;     /* cards drawn */
    /* 0x68 */ s32 turned;    /* slots turned so far */
    /* 0x6C */ s32 time;
    /* 0x70 */ s32 frame;
    /* 0x74 */ u8 unk74[0x10];
    /* 0x84 */ void (*setPage)(struct CardAlbumGrid *grid, s32 first);
    /* 0x88 */ void (*hide)(struct CardAlbumGrid *grid);
} CardAlbumGrid;

typedef struct CardAlbum {
    TASK_HEADER(CardAlbum);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 frame;
    /* 0x5C */ s32 frameToggle;
    /* 0x60 */ s32 page;
    /* 0x64 */ s32 pageCount;
    /* 0x68 */ s32 active;
    /* 0x6C */ s32 blink;
    /* 0x70 */ s32 blinkTime;
    /* 0x74 */ s32 slot;
    /* 0x78 */ s32 card;
    /* 0x7C */ s32 pageHasCards;
    /* 0x80 */ s32 slotHasCard[ALBUM_PAGE_CARDS];
    /* 0xB0 */ s32 cursorFrame;
    /* 0xB4 */ s32 cursorTime;
    /* 0xB8 */ PanelAnim fade;     /* the album */
    /* 0xC8 */ PanelAnim infoFade; /* the card's details */
} CardAlbum;

typedef struct CardAlbumWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *help;
    /* 0x08 */ TextWindow *page;
    /* 0x0C */ TextWindow *pageSlash;
    /* 0x10 */ TextWindow *pageCount;
    /* 0x14 */ TextWindow *prev;
    /* 0x18 */ TextWindow *next;
    /* 0x1C */ TextWindow *name;
    /* 0x20 */ TextWindow *levelLabel;
    /* 0x24 */ TextWindow *level;      /* card data [5] */
    /* 0x28 */ TextWindow *countLabel;
    /* 0x2C */ TextWindow *count;      /* copies the player has */
    /* 0x30 */ TextWindow *text;
    /* 0x34 */ TextWindow *stat1Label;
    /* 0x38 */ TextWindow *stat1;      /* card data [1] */
    /* 0x3C */ TextWindow *stat2Label;
    /* 0x40 */ TextWindow *stat2;      /* card data [2] */
    /* 0x44 */ CardAlbumGrid *grid;
    /* 0x48 */ CardAlbumFader *fader;
} CardAlbumWindows;

/* Moves a value towards a target in fixed point */
typedef struct CardAlbumLerp {
    /* 0x00 */ s32 duration;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 fixed; /* value << 8 */
    /* 0x10 */ s32 target;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 active;
} CardAlbumLerp;

typedef struct CardAlbumFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(CardAlbumLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(CardAlbumLerp *lerp);
} CardAlbumFuncs;

#endif /* STCRDABM_H */
