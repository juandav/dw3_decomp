#ifndef STITSHOP_H
#define STITSHOP_H

/* STITSHOP.PRO: the item shop. The game mode's argument picks the shop
   (STITSHOP_shops, a list of the items it sells); the player buys items
   for the money, sells them, and equips what was bought on a partner.
   Its strings are in file 0x72. */

#include "game.h"

/* The shop's sprite sheet; the next file is its texture archive */
#if VERSION_US
#define FILE_SHOP_SPRITES 0x3F2
#elif VERSION_EU
#define FILE_SHOP_SPRITES 0x402
#endif

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
    /* 0x00 */ TextWindow *title; /* the shop's name */
    /* 0x04 */ TextWindow *help;
    /* 0x08 */ TextWindow *money;
    /* 0x0C */ TextWindow *moneyLabel;
    /* 0x10 */ TextWindow *buy;
    /* 0x14 */ TextWindow *sell;
    /* 0x18 */ Cursor *cursor;
    /* 0x1C */ Task *dialog; /* ShopBuy or ShopSell */
    /* 0x20 */ ScreenFade *fade;
} ItemShopWindows;

/* What the details panel shows of a partner */
typedef struct ShopPartnerInfo {
    /* 0x00 */ s16 stats[19]; /* as computeStats gives them */
    /* 0x26 */ s16 penalties[3]; /* subtracted from stats 6, 7 and 10 */
    /* 0x2C */ s16 newStats[22]; /* with the item equipped */
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 changes; /* how many of the stats would change */
    /* 0x60 */ s32 rows[8]; /* from 2: the stats that change (from 1) */
} ShopPartnerInfo;

/* A row of the details panel's stats */
typedef struct ShopStatRow {
    /* 0x00 */ s32 partner;
    /* 0x04 */ s32 stat; /* into D_8008C114 */
    /* 0x08 */ s32 compare; /* show the stat with the item equipped */
    /* 0x0C */ s32 skip;
    /* 0x10 */ s32 skip2; /* -1: none */
} ShopStatRow;

/* The panel with the selected item's details (func_8008AB04) */
typedef struct ShopInfo {
    TASK_HEADER(ShopInfo);
    /* 0x050 */ s32 layer;
    /* 0x054 */ s32 depth;
    /* 0x058 */ s32 selling;
    /* 0x05C */ s32 page; /* 0: the description, 1: the partners' stats */
    /* 0x060 */ s32 unk60;
    /* 0x064 */ ShopPartnerInfo partners[3];
    /* 0x1E4 */ s32 item;
    /* 0x1E8 */ s32 unk1E8;
    /* 0x1EC */ s32 unk1EC;
    /* 0x1F0 */ s32 shown;
    /* 0x1F4 */ PanelAnim panels[4];
    /* 0x234 */ void (*showItem)(struct ShopInfo *info, s32 item, s32 arg);
    /* 0x238 */ void (*close)(struct ShopInfo *info);
    /* 0x23C */ void (*setArrowVisible)(struct ShopInfo *info, s32 visible);
    /* 0x240 */ void (*turnPage)(struct ShopInfo *info);
    /* 0x244 */ void (*func_8008AAB0)(struct ShopInfo *info, s32 arg);
} ShopInfo;

/* The list of the items to buy or sell (func_80088094) */
typedef struct ShopItemList {
    TASK_HEADER(ShopItemList);
    /* 0x050 */ struct Task *dialog; /* ShopBuy or ShopSell */
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 selling; /* 0: the shop's items, 1: the bag's */
    /* 0x060 */ s32 type; /* the shop, or the item type to sell */
    /* 0x064 */ s16 items[0x194]; /* the bag's items that can be sold */
    /* 0x38C */ s16 bag[0x194];
    /* 0x6B4 */ u16 *shopItems;
    /* 0x6B8 */ s32 cursorStill;
    /* 0x6BC */ s32 selection;
    /* 0x6C0 */ s32 count;
    /* 0x6C4 */ s32 unk6C4[4];
    /* 0x6D4 */ s32 pageSize;
    /* 0x6D8 */ s32 unk6D8[4];
    /* 0x6E8 */ void (*start)(struct ShopItemList *list);
    /* 0x6EC */ void (*close)(struct ShopItemList *list);
    /* 0x6F0 */ s16 (*getSelected)(struct ShopItemList *list);
    /* 0x6F4 */ void (*showCursor)(struct ShopItemList *list, s32 visible);
    /* 0x6F8 */ void (*freezeCursor)(struct ShopItemList *list, s32 frozen);
    /* 0x6FC */ void (*refresh)(struct ShopItemList *list);
    /* 0x700 */ void (*listBag)(struct ShopItemList *list);
} ShopItemList;

/* The dialog to buy an item (func_800850A8) */
typedef struct ShopBuy {
    TASK_HEADER(ShopBuy);
    /* 0x50 */ void (*showItem)(struct ShopBuy *buy, s32 item, s32 arg);
    /* 0x54 */ struct ItemShop *shop;
    /* 0x58 */ s32 layer;
    /* 0x5C */ s32 depth;
    /* 0x60 */ s32 item;
    /* 0x64 */ s32 quantity;
    /* 0x68 */ s32 max;
    /* 0x6C */ s32 blink;
    /* 0x70 */ s32 blinkTime;
    /* 0x74 */ s32 choice;
    /* 0x78 */ s32 unk78[4];
    /* 0x88 */ PanelAnim panels[4];
} ShopBuy;

typedef struct ShopBuyWindows {
    /* 0x00 */ ShopItemList *list;
    /* 0x04 */ ShopInfo *info;
    /* 0x08 */ TextWindow *quantityLabel;
    /* 0x0C */ TextWindow *times;
    /* 0x10 */ TextWindow *quantity;
    /* 0x14 */ TextWindow *total;
    /* 0x18 */ TextWindow *yes;
    /* 0x1C */ TextWindow *no;
    /* 0x20 */ Cursor *cursor;
} ShopBuyWindows;

/* The dialog to sell an item (func_80086AD8) */
typedef struct ShopSell {
    TASK_HEADER(ShopSell);
    /* 0x50 */ void (*showItem)(struct ShopSell *sell, s32 item, s32 arg);
    /* 0x54 */ struct ItemShop *shop;
    /* 0x58 */ s32 layer;
    /* 0x5C */ s32 depth;
    /* 0x60 */ s32 type;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 quantity;
    /* 0x6C */ s32 unk6C[4];
    /* 0x7C */ PanelAnim panels[5];
} ShopSell;

typedef struct ShopSellWindows {
    /* 0x00 */ ShopItemList *list;
    /* 0x04 */ ShopInfo *info;
    /* 0x08 */ Cursor *cursor;
    /* 0x0C */ TextWindow *types[4];
    /* 0x1C */ TextWindow *quantityLabel;
    /* 0x20 */ TextWindow *times;
    /* 0x24 */ TextWindow *quantity;
    /* 0x28 */ TextWindow *unk28;
    /* 0x2C */ TextWindow *total;
    /* 0x30 */ TextWindow *unk30;
    /* 0x34 */ TextWindow *unk34;
} ShopSellWindows;

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
    /* 0x4 */ u16 *items;
} ShopList;

/* The shop's helpers (STITSHOP_funcs) */
typedef struct ItemShopFuncs {
    /* 0x00 */ s32 count; /* the items of the shop getShopItems returned */
    /* 0x04 */ void (*loadFiles)(void);
    /* 0x08 */ s32 (*filesLoading)(void);
    /* 0x0C */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x10 */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x14 */ void (*startLerp)(ShopLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x18 */ s32 (*updateLerp)(ShopLerp *lerp);
    /* 0x1C */ u16 *(*getShopItems)(s32 shop);
    /* 0x20 */ s32 (*canEquip)(s32 partner, s32 item);
    /* 0x24 */ s32 (*compareEquip)(s32 partner, s32 item);
    /* 0x28 */ void (*equip)(s32 partner, s32 slot, s32 item, s32 fromBag);
} ItemShopFuncs;

/* A partner's stats, copied whole (as main's computeStats does) */
typedef struct ShopStatBlock {
    s16 v[22];
} ShopStatBlock;

typedef union ShopItemData {
    struct {
        /* 0x0 */ s16 unk0;
        /* 0x2 */ s16 unk2[2];
        /* 0x6 */ u16 amounts[2];
        /* 0xA */ s16 atk;
        /* 0xC */ u8 stats[2];
    } weapon;
    struct {
        /* 0x0 */ s16 unk0;
        /* 0x2 */ s16 unk2[2];
        /* 0x6 */ u16 amounts[2];
        /* 0xA */ u8 stats[2];
        /* 0xC */ s16 def;
    } armor;
    struct {
        /* 0x0 */ s16 unk0;
        /* 0x2 */ s16 unk2[2];
        /* 0x6 */ u16 amount;
        /* 0x8 */ u8 stat;
    } acc;
} ShopItemData;

extern ShopList STITSHOP_shops[31];
extern ItemShopFuncs STITSHOP_funcs;

#endif /* STITSHOP_H */
