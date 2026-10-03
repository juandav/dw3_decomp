#ifndef CARDGAME_H
#define CARDGAME_H

/* CARDGAME.PRO: the card battle (mode 0x700) */

#include "game.h"

/* CARDGAME's own pictures, a TIM archive */
#if VERSION_US
#define FILE_CARDGAME_TIMS 0x24E
#elif VERSION_EU
#define FILE_CARDGAME_TIMS 0x25D
#endif

/* The card battle (CARDGAME_createBattle) */
typedef struct CardBattle {
    TASK_HEADER(CardBattle);
    /* 0x050 */ u8 unk50[0x2B3];
    /* 0x303 */ u8 result; /* 2 once the battle is over */
} CardBattle;

/* A file CARDGAME_tickPreloader reads; a text file is in each language */
typedef struct CardFileEntry {
    /* 0x0 */ s16 file; /* -2: the files before are enough to start, -1: the end */
    /* 0x2 */ s16 isText;
} CardFileEntry;

/* Reads CARDGAME's files into the file cache, one at a time */
typedef struct CardPreloader {
    TASK_HEADER(CardPreloader);
    /* 0x50 */ s32 ready; /* the files before the first -2 are in */
    /* 0x54 */ s16 index;
    /* 0x56 */ s16 file;
} CardPreloader;

/* Fades the screen to a colour: a POLY_F4 over it, blended (blend is the
   semi-transparency rate) */
typedef struct CardFader {
    TASK_HEADER(CardFader);
    /* 0x50 */ s32 mode; /* 0 idle, 1 fading, 2 done: the task ends */
    /* 0x54 */ s32 time; /* left */
    /* 0x58 */ s32 duration;
    /* 0x5C */ u8 blend;
    /* 0x5D */ u8 killWhenDone;
    /* 0x5E */ u8 target[3];
    /* 0x61 */ u8 from[3];
    /* 0x64 */ u8 color[3];
    /* 0x68 */ void (*setColor)(struct CardFader *fader, u8 r, u8 g, u8 b);
    /* 0x6C */ void (*start)(struct CardFader *fader, u8 r, u8 g, u8 b, s32 frames, s32 killWhenDone);
    /* 0x70 */ s32 (*isDone)(struct CardFader *fader);
    /* 0x74 */ void (*kill)(struct CardFader *fader);
} CardFader;

/* A blinking marker that opens and closes by scaling (CARDGAME_createMarker):
   frame 0x47 of the TIM archive's sprite sheet */
typedef struct CardMarker {
    TASK_HEADER(CardMarker);
    /* 0x50 */ s32 time; /* the blink */
    /* 0x54 */ s16 x;
    /* 0x56 */ s16 y;
    /* 0x58 */ s16 scaleX;
    /* 0x5A */ s16 scaleY;
    /* 0x5C */ u8 unk5C[6];
    /* 0x62 */ u8 phase; /* 0 opening, 1 open, 2 closing */
    /* 0x63 */ u8 fast; /* the blink's palette cycle */
    /* 0x64 */ s16 scaleTime;
    /* 0x66 */ s16 scaleDuration;
    /* 0x68 */ void (*setPos)(struct CardMarker *marker, s16 x, s16 y);
    /* 0x6C */ void (*close)(struct CardMarker *marker);
    /* 0x70 */ void (*setFast)(struct CardMarker *marker);
} CardMarker;

/* An offset from a window's corner */
typedef struct CardOffset {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
} CardOffset;

/* A deck's window (CARDGAME_createDeckWindow): its name and how many cards
   of each of the six colours it has. It opens and closes by scaling. */
typedef struct CardDeckWindow {
    TASK_HEADER(CardDeckWindow);
    /* 0x50 */ s32 deck; /* in GAME.decks */
    /* 0x54 */ s32 time; /* the blink */
    /* 0x58 */ s16 x;
    /* 0x5A */ s16 y;
    /* 0x5C */ s16 scaleX;
    /* 0x5E */ s16 scaleY;
    /* 0x60 */ u8 counts[6];
    /* 0x66 */ u8 phase; /* 0 opening, 1 open, 2 closing */
    /* 0x67 */ u8 blink;
    /* 0x68 */ s16 scaleTime;
    /* 0x6A */ s16 scaleDuration;
    /* 0x6C */ void (*setBlink)(struct CardDeckWindow *window);
    /* 0x70 */ void (*close)(struct CardDeckWindow *window);
} CardDeckWindow;

/* A number drawn with the TIM archive's digits (CARDGAME_drawNumber) */
typedef struct CardNumber {
    /* 0x00 */ s16 value;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 scaleX;
    /* 0x08 */ s16 scaleY;
    /* 0x0A */ s16 pivotX;
    /* 0x0C */ s16 pivotY;
    /* 0x0E */ u8 digits;
    /* 0x0F */ u8 leadingZeros;
    /* 0x10 */ u8 depth;
} CardNumber;

/* The battle screen's task items */
typedef struct CardScreenItems {
    /* 0x00 */ Cursor *cursor;
    /* 0x04 */ TextWindow *texts[13];
} CardScreenItems;

/* One side's panel on the battle screen (CardScreen.panels): 0 is the
   player's, 1 the opponent's */
typedef struct CardPanel {
    /* 0x00 */ s16 time;
    /* 0x02 */ s16 duration;
    /* 0x04 */ s16 state;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ s16 x;
    /* 0x0E */ s16 y;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14[4];
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ u8 flags[10];
    /* 0x3A */ u8 unk3A[2];
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ u8 unk40[8];
    /* 0x48 */ s16 scale;
    /* 0x4A */ u8 unk4A[2];
    /* 0x4C */ s16 scaleTime;
    /* 0x4E */ s16 scaleDuration;
    /* 0x50 */ u8 scaleState;
    /* 0x51 */ u8 unk51[3];
} CardPanel;

/* A card on the battle screen (CardScreen.sprites) */
typedef struct CardSprite {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 targetX;
    /* 0x0C */ s32 targetY;
    /* 0x10 */ s32 startX;
    /* 0x14 */ s32 startY;
    /* 0x18 */ s16 scaleX;
    /* 0x1A */ s16 scaleY;
    /* 0x1C */ s16 targetScaleX;
    /* 0x1E */ s16 targetScaleY;
    /* 0x20 */ s16 startScaleX;
    /* 0x22 */ s16 startScaleY;
    /* 0x24 */ s16 slot;
    /* 0x26 */ s16 moving;
    /* 0x28 */ s32 time;
    /* 0x2C */ s32 duration;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ u8 unk34[4];
    /* 0x38 */ s16 color; /* the card's colour, from 0 */
    /* 0x3A */ s16 index; /* in the battle's card list */
    /* 0x3C */ s16 isKind16;
    /* 0x3E */ u8 unk3E[3];
    /* 0x41 */ u8 unk41;
    /* 0x42 */ u8 state;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 visible;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A[2];
} CardSprite;

typedef struct CardScreenCE8 {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 startX;
    /* 0x06 */ s16 startY;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 state;
    /* 0x11 */ u8 unk11;
} CardScreenCE8;

/* A value that goes from `from` to `to` (0x1000 is 1) over `duration` frames */
typedef struct CardScreenDC0 {
    /* 0x00 */ s16 from;
    /* 0x02 */ s16 to;
    /* 0x04 */ s16 time;
    /* 0x06 */ s16 duration;
    /* 0x08 */ s16 state;
    /* 0x0A */ s16 value;
} CardScreenDC0;

/* A window that opens (its scale goes from `from` to `to`) */
typedef struct CardScreenE0C {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 from;
    /* 0x06 */ s16 to;
    /* 0x08 */ s16 time;
    /* 0x0A */ s16 duration;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[3];
    /* 0x17 */ u8 state;
} CardScreenE0C;

/* The battle screen (created by CARDGAME_createScreen): the two panels, the cards on
   the table and the windows. Its 14 task items are a cursor and 13 text
   windows. */
typedef struct CardScreen {
    TASK_HEADER(CardScreen);
    /* 0x050 */ s16 *cards; /* the battle's card list */
    /* 0x054 */ s32 unk54;
    /* 0x058 */ u32 time;
    /* 0x05C */ u8 unk5C[4];
    /* 0x060 */ CardPanel panels[2];
    /* 0x108 */ CardSprite sprites[40];
    /* 0xCE8 */ CardScreenCE8 unkCE8[12];
    /* 0xDC0 */ CardScreenDC0 unkDC0[3];
    /* 0xDE4 */ s32 unkDE4;
    /* 0xDE8 */ s32 unkDE8;
    /* 0xDEC */ s32 unkDEC;
    /* 0xDF0 */ s16 unkDF0; /* time */
    /* 0xDF2 */ s16 unkDF2; /* duration */
    /* 0xDF4 */ s16 unkDF4;
    /* 0xDF6 */ s16 unkDF6;
    /* 0xDF8 */ s16 unkDF8;
    /* 0xDFA */ u8 unkDFA; /* state */
    /* 0xDFB */ u8 unkDFB;
    /* 0xDFC */ u8 unkDFC[4];
    /* 0xE00 */ s16 unkE00; /* time */
    /* 0xE02 */ s16 unkE02; /* duration */
    /* 0xE04 */ s16 unkE04;
    /* 0xE06 */ u8 unkE06[4];
    /* 0xE0A */ s16 unkE0A; /* state */
    /* 0xE0C */ CardScreenE0C unkE0C[6];
    /* 0xE9C */ u8 unkE9C;
    /* 0xE9D */ u8 unkE9D;
    /* 0xE9E */ u8 unkE9E;
    /* 0xE9F */ u8 unkE9F;
    /* 0xEA0 */ void (*setPanelValue)(struct CardScreen *screen, s32 side, u32 which, s32 value);
    /* 0xEA4 */ void (*unkEA4)(struct CardScreen *screen, s32 index, s16 value);
    /* 0xEA8 */ void (*unkEA8)(struct CardScreen *screen, s32 index);
    /* 0xEAC */ void (*unkEAC)(struct CardScreen *screen, s32 index, s16 arg2, s32 arg3, s32 x, s32 y);
    /* 0xEB0 */ void (*unkEB0)(struct CardScreen *screen, s32 index);
    /* 0xEB4 */ void (*clearPanelFlags)(struct CardScreen *screen);
    /* 0xEB8 */ void (*setPanelFlags)(struct CardScreen *screen, s32 bits);
    /* 0xEBC */ void (*unkEBC)(struct CardScreen *screen, s32 side);
    /* 0xEC0 */ void (*unkEC0)(struct CardScreen *screen, s32 side);
    /* 0xEC4 */ void (*unkEC4)(struct CardScreen *screen);
    /* 0xEC8 */ void (*unkEC8)(struct CardScreen *screen);
    /* 0xECC */ void (*unkECC)(struct CardScreen *screen);
    /* 0xED0 */ void (*unkED0)(struct CardScreen *screen, s32 side);
    /* 0xED4 */ void (*unkED4)(struct CardScreen *screen, s32 side);
    /* 0xED8 */ s32 (*getHandOffset)(s32 count, s32 index);
    /* 0xEDC */ s32 (*unkEDC)(struct CardScreen *screen, s32 index, s16 x, s16 y);
    /* 0xEE0 */ s32 (*unkEE0)(struct CardScreen *screen, s32 index, u8 arg2, s16 arg3, s32 arg4);
    /* 0xEE4 */ void (*unkEE4)(struct CardScreen *screen, s32 arg1, u8 arg2, s16 arg3, s32 arg4);
    /* 0xEE8 */ void (*unkEE8)(struct CardScreen *screen);
    /* 0xEEC */ void (*unkEEC)(struct CardScreen *screen);
    /* 0xEF0 */ void (*unkEF0)(struct CardScreen *screen, s16 value);
    /* 0xEF4 */ void (*unkEF4)(struct CardScreen *screen, s16 value);
    /* 0xEF8 */ void (*unkEF8)(struct CardScreen *screen);
    /* 0xEFC */ void (*unkEFC)(struct CardScreen *screen);
    /* 0xF00 */ void (*unkF00)(struct CardScreen *screen, s16 value);
    /* 0xF04 */ void (*dealSprites)(struct CardScreen *screen, s16 duration, s16 count, s32 x, s32 y);
    /* 0xF08 */ void (*unkF08)(struct CardScreen *screen, s32 index, s32 duration, s32 x, s32 y);
    /* 0xF0C */ void (*unkF0C)(struct CardScreen *screen, s32 index, s32 duration, s32 x, s32 y);
    /* 0xF10 */ s32 (*unkF10)(struct CardScreen *screen, s32 index, s32 duration, s32 x, s32 y);
    /* 0xF14 */ s32 (*addSprite)(struct CardScreen *screen, s32 index, s32 x, s32 y);
    /* 0xF18 */ s32 (*removeSprite)(struct CardScreen *screen, s32 index);
    /* 0xF1C */ s32 (*unkF1C)(struct CardScreen *screen, s32 index);
    /* 0xF20 */ void (*setSpriteScale)(struct CardScreen *screen, s32 index, s32 scaleX, s32 scaleY);
    /* 0xF24 */ void (*scaleSprite)(struct CardScreen *screen, s32 index, s32 duration, s32 scaleX, s32 scaleY);
    /* 0xF28 */ s32 (*unkF28)(struct CardScreen *screen, s32 index);
    /* 0xF2C */ s32 (*unkF2C)(struct CardScreen *screen, s32 index);
    /* 0xF30 */ s32 (*unkF30)(struct CardScreen *screen, s32 index);
    /* 0xF34 */ s32 (*unkF34)(struct CardScreen *screen, s32 index);
    /* 0xF38 */ s32 (*unkF38)(struct CardScreen *screen, s32 index, s32 arg2);
    /* 0xF3C */ void (*setSpriteCard)(struct CardScreen *screen, s32 sprite, s32 index);
    /* 0xF40 */ u8 (*getCardColor)(struct CardScreen *screen, s32 index);
    /* 0xF44 */ s32 (*loadCardImages)(s16 *dst, s16 *player, s16 *opponent);
} CardScreen;

#endif /* CARDGAME_H */
