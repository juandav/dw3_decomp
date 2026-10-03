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

#endif
