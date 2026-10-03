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

/* A card a player has out (CARDGAME_setSlot) */
typedef struct CardSlot {
    /* 0x0 */ s16 card; /* the index in the battle's card list */
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6; /* the card's byte 1 */
    /* 0x8 */ s16 unk8; /* the card's byte 2 */
    /* 0xA */ u8 side;
    /* 0xB */ u8 owner;
    /* 0xC */ u8 order; /* CardBattle.slotCount when it was added */
} CardSlot;

/* One of the two players of a card battle */
typedef struct CardPlayer {
    /* 0x00 */ u8 slotCount;
    /* 0x02 */ CardSlot slots[8];
} CardPlayer;

/* An entry of CardBattle560.unk20 */
typedef struct CardSideEntry {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} CardSideEntry;

typedef struct CardBattle35C {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
} CardBattle35C;

/* A message of the card battle (D_800A4C20) */
typedef struct CardBattleMessage {
    /* 0x0 */ u16 text; /* for CardBattle.unk421 */
    /* 0x2 */ u16 unk2;
} CardBattleMessage;

/* An entry of CardBattle.unk30A */
typedef struct CardBattle30A {
    /* 0x0 */ s8 unk0;
    /* 0x1 */ u8 unk1;
} CardBattle30A;

/* A player's cards in a card battle (CardSide.pile) */
typedef struct CardPile {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; /* the cards in unk64 */
    /* 0x0C */ u8 unkC[5]; /* one per card colour */
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ s16 unk14[40];
    /* 0x64 */ s16 unk64[10]; /* unkA in use */
    /* 0x78 */ s16 unk78[10]; /* unk6 in use */
} CardPile;

/* The card battle's record of the cards played (CardBattle.unk560) */
typedef struct CardBattle560 {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ s8 unk15; /* the entries of unk20 in use */
    /* 0x16 */ u8 unk16[6];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ CardSideEntry unk20[3];
    /* 0x38 */ u8 unk38[4];
} CardBattle560;

/* Each player's side of a card battle (CardBattle.sides) */
typedef struct CardSide {
    /* 0x00 */ CardPile pile;
    /* 0x8C */ u8 unk8C[0x3C];
} CardSide;

/* CardBattle.unk498 */
typedef struct CardBattle498 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5; /* 1 or 2: set unk6 to 0 or 1 */
    /* 0x06 */ u8 unk6[40];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
} CardBattle498;

/* The card battle (CARDGAME_createBattle). Its seven task items: the battle
   screen is the last one (CardBattleItems). */
typedef struct CardBattle {
    TASK_HEADER(CardBattle);
    /* 0x050 */ s16 cards[80]; /* card ids, minus one */
    /* 0x0F0 */ u8 unkF0[0x1F8];
    /* 0x2E8 */ u8 arg; /* the mode argument */
    /* 0x2E9 */ u8 unk2E9;
    /* 0x2EA */ s16 unk2EA;
    /* 0x2EC */ s32 unk2EC;
    /* 0x2F0 */ s32 unk2F0;
    /* 0x2F4 */ u8 unk2F4;
    /* 0x2F5 */ u8 unk2F5;
    /* 0x2F6 */ u8 unk2F6;
    /* 0x2F7 */ u8 unk2F7;
    /* 0x2F8 */ u8 unk2F8;
    /* 0x2F9 */ u8 unk2F9;
    /* 0x2FA */ u8 unk2FA[2];
    /* 0x2FC */ s32 unk2FC;
    /* 0x300 */ u8 unk300;
    /* 0x301 */ u8 unk301;
    /* 0x302 */ u8 unk302;
    /* 0x303 */ u8 result; /* 2 once the battle is over */
    /* 0x304 */ u8 unk304;
    /* 0x305 */ u8 unk305;
    /* 0x306 */ u8 unk306;
    /* 0x307 */ u8 unk307;
    /* 0x308 */ u8 slotCount; /* the slots added so far */
    /* 0x309 */ u8 unk309;
    /* 0x30A */ CardBattle30A unk30A[40];
    /* 0x35A */ u8 unk35A[2];
    /* 0x35C */ CardBattle35C unk35C[40]; /* one per card of side 1 (40-79) */
    /* 0x3FC */ u8 unk3FC[0x1F];
    /* 0x41B */ u8 unk41B;
    /* 0x41C */ u8 unk41C;
    /* 0x41D */ u8 unk41D[3];
    /* 0x420 */ u8 unk420;
    /* 0x421 */ u8 unk421;
    /* 0x422 */ u8 stepState; /* 1 when a step starts */
    /* 0x423 */ u8 unk423;
    /* 0x424 */ s32 unk424;
    /* 0x428 */ s32 unk428;
    /* 0x42C */ s32 unk42C;
    /* 0x430 */ s32 unk430;
    /* 0x434 */ s32 unk434;
    /* 0x438 */ s32 unk438;
    /* 0x43C */ s32 unk43C;
    /* 0x440 */ s32 unk440;
    /* 0x444 */ u8 unk444;
    /* 0x445 */ u8 unk445;
    /* 0x446 */ s8 unk446[0x29];
    /* 0x46F */ s8 unk46F[40];
    /* 0x497 */ u8 unk497;
    /* 0x498 */ CardBattle498 unk498;
    /* 0x4DC */ u8 unk4DC;
    /* 0x4DD */ u8 unk4DD;
    /* 0x4DE */ u8 unk4DE;
    /* 0x4E0 */ s16 unk4E0; /* a score the computer player adds up */
    /* 0x4E2 */ s16 unk4E2;
    /* 0x4E4 */ s16 unk4E4;
    /* 0x4E8 */ s32 unk4E8;
    /* 0x4EC */ s32 unk4EC;
    /* 0x4F0 */ u8 unk4F0[0x70];
    /* 0x560 */ CardBattle560 unk560;
    /* 0x59C */ CardSide sides[2];
    /* 0x72C */ CardPlayer players[2];
    /* 0x810 */ void (*unk810)();
    /* 0x814 */ void (*unk814)(struct CardBattle *battle, void *arg1, s32 arg2, s32 arg3);
    /* 0x818 */ void (*unk818)();
    /* 0x81C */ void (*addCard)(struct CardBattle *battle, s32 side, s32 card);
    /* 0x820 */ s32 (*unk820)();
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

/* A fade colour and blend mode (CardBattle.unk306 - 1 picks one) */
typedef struct CardFadeColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 blend;
} CardFadeColor;

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

/* How each of the six CardScreenE0C windows is drawn */
typedef struct CardWindowLayout {
    /* 0x0 */ s16 x; /* its pivot, from the window's corner */
    /* 0x2 */ s16 y;
    /* 0x4 */ u8 sprite;
    /* 0x5 */ u8 kind; /* 2: a sprite of the fourth TIM, else of the third */
} CardWindowLayout;

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

/* The card battle's task items */
typedef struct CardBattleItems {
    /* 0x00 */ void *unk0[6];
    /* 0x18 */ CardScreen *screen;
} CardBattleItems;

#endif /* CARDGAME_H */
