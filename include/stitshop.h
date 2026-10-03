#ifndef STITSHOP_H
#define STITSHOP_H

/* STITSHOP.PRO: the item shop. The game mode's argument picks the shop
   (STITSHOP_shops, a list of the items it sells); the player buys items
   for the money, sells them, and equips what was bought on a partner.
   Its strings are in file 0x72. */

#include "game.h"

/* The main task of the shop (STITSHOP_createShop) */
typedef struct ItemShop {
    TASK_HEADER(ItemShop);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 shop; /* the game mode's argument */
    /* 0x64 */ s32 unk64;
    /* 0x68 */ PanelAnim panels[4];
    /* 0xA8 */ void (*showMoney)(struct ItemShop *shop);
} ItemShop;

/* The children of the shop */
typedef struct ItemShopWindows {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ TextWindow *money;
    /* 0x0C */ void *unkC[6];
} ItemShopWindows;

/* Moves a value towards a target in fixed point */
typedef struct ShopLerp {
    /* 0x00 */ s32 duration;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 fixed; /* value << 8 */
    /* 0x10 */ s32 target;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 active;
} ShopLerp;

/* A shop: the items it sells */
typedef struct ShopList {
    /* 0x0 */ s32 count;
    /* 0x4 */ s32 *items;
} ShopList;

#endif /* STITSHOP_H */
