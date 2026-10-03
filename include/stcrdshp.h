#ifndef STCRDSHP_H
#define STCRDSHP_H

/* STCRDSHP.PRO: the card packs (mode 0x1300). Opening a pack, an item, uses
   it up and draws six cards, one from each of its slots' lists
   (STCRDSHP_packs), which are then added to the player's cards. */

#include "game.h"

/* A card pack: the item and the six lists of 16 cards its slots draw from */
typedef struct CardPack {
    /* 0x00 */ s32 item;
    /* 0x04 */ s32 *slots[6];
} CardPack;

extern CardPack STCRDSHP_packs[];

/* The cards are drawn from 315 ids (1-314) */
#define CARD_PACK_IDS 315

/* The sprite sheet of the screen */
#if VERSION_US
#define FILE_CARDSHOP_SPRITES 0x62E
#elif VERSION_EU
#define FILE_CARDSHOP_SPRITES 0x63E
#endif

/* Draws the six cards drawn from a pack, and turns them over */
typedef struct CardPackGrid {
    TASK_HEADER(CardPackGrid);
    /* 0x50 */ Task *owner;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 shown;  /* cards drawn */
    /* 0x68 */ s32 turned; /* slots turned so far */
    /* 0x6C */ s32 time;
    /* 0x70 */ s32 frame;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 cards[6];
    /* 0x94 */ s32 prevCards[6]; /* the cards being turned */
    /* 0xAC */ u8 unkAC[0x10];
    /* 0xBC */ void (*setCards)(struct CardPackGrid *grid, s32 *cards);
    /* 0xC0 */ void (*hide)(struct CardPackGrid *grid);
} CardPackGrid;

#endif
