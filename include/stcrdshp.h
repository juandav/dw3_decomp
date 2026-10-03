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

/* The sprite sheet of the screen, the shop's textures and the card data
   (five files, as STCRDABM loads them) */
#if VERSION_US
#define FILE_CARDSHOP_SPRITES 0x62E
#define FILE_CARDSHOP_IMAGES 0x632
#define FILE_CARD_DATA 0x7E7
#elif VERSION_EU
#define FILE_CARDSHOP_SPRITES 0x63E
#define FILE_CARDSHOP_IMAGES 0x642
#define FILE_CARD_DATA 0x7F6
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

/* The cards a shop sells */
typedef struct CardShopStock {
    /* 0x0 */ s32 shop;
    /* 0x4 */ s32 count;
    /* 0x8 */ s16 *cards; /* 0-terminated */
} CardShopStock;

/* A card's price */
typedef struct CardPrice {
    /* 0x0 */ s16 card;
    /* 0x2 */ s16 price;
} CardPrice;

/* The shop's title for the field it is opened from */
typedef struct CardShopTitle {
    /* 0x0 */ s32 mode; /* GAME.fieldMode; 0 ends the list */
    /* 0x4 */ s32 title; /* string of file 0x95 */
} CardShopTitle;

/* The card shop's main task (STCRDSHP_createShop): buy cards, open packs
   or go to the item shop */
typedef struct CardShop {
    TASK_HEADER(CardShop);
    /* 0x050 */ s32 layer;
    /* 0x054 */ s32 depth;
    /* 0x058 */ s32 scroll; /* of the background */
    /* 0x05C */ s32 scrollWait; /* it moves every other frame */
    /* 0x060 */ s32 shop; /* the game mode's argument */
    /* 0x064 */ s32 title;
    /* 0x068 */ s32 toItemShop;
    /* 0x06C */ s32 cursor;
    /* 0x070 */ s16 items[0x194]; /* the bag's, to look for packs */
    /* 0x398 */ PanelAnim fades[3];
    /* 0x3C8 */ void (*showMoney)(struct CardShop *shop);
} CardShop;

/* The children of the shop */
typedef struct CardShopWindows {
    /* 0x00 */ TextWindow *title;
    /* 0x04 */ TextWindow *help;
    /* 0x08 */ TextWindow *message;
    /* 0x0C */ TextWindow *moneyLabel;
    /* 0x10 */ TextWindow *money;
    /* 0x14 */ TextWindow *options[3];
    /* 0x20 */ Cursor *cursor;
    /* 0x24 */ Task *dialog; /* buying cards or opening a pack */
    /* 0x28 */ ScreenFade *fade;
} CardShopWindows;

/* The screen to open a pack (STCRDSHP_createPackOpen): the bag's packs, eight
   a page */
typedef struct CardPackOpen {
    TASK_HEADER(CardPackOpen);
    /* 0x050 */ struct CardShop *shop;
    /* 0x054 */ s32 layer;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 unk5C[2];
    /* 0x064 */ s32 pages;
    /* 0x068 */ s32 unk68[12];
    /* 0x098 */ s16 packs[0x194]; /* the bag's card packs */
    /* 0x3C0 */ s32 packCount;
    /* 0x3C4 */ s16 items[0x194]; /* the bag's items */
    /* 0x6EC */ s32 unk6EC;
    /* 0x6F0 */ PanelAnim fades[4];
} CardPackOpen;

/* The screen to buy cards (STCRDSHP_createBuy): the shop's cards, six a page */
typedef struct CardShopBuy {
    TASK_HEADER(CardShopBuy);
    /* 0x50 */ struct CardShop *shop;
    /* 0x54 */ s32 layer;
    /* 0x58 */ s32 depth;
    /* 0x5C */ s32 column; /* the card under the cursor, on the page */
    /* 0x60 */ s32 cursorShown;
    /* 0x64 */ s32 cursorFrame;
    /* 0x68 */ s32 cursorTime;
    /* 0x6C */ s32 page;
    /* 0x70 */ s32 pages;
    /* 0x74 */ s32 cards[6]; /* the page's */
    /* 0x8C */ s32 arrowsShown;
    /* 0x90 */ s32 arrowsTime;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 shopId; /* the shop's game mode argument */
    /* 0xA4 */ s32 count;
    /* 0xA8 */ struct CardShopStock *stock;
    /* 0xAC */ PanelAnim fades[3];
} CardShopBuy;

typedef struct CardShopBuyWindows {
    /* 0x00 */ TextWindow *windows[17];
    /* 0x44 */ Cursor *cursor;
    /* 0x48 */ CardPackGrid *grid;
} CardShopBuyWindows;

/* The shop's helpers (STCRDSHP_funcs) */
typedef struct CardShopFuncs {
    /* 0x00 */ void (*loadFiles)(void);
    /* 0x04 */ s32 (*filesLoading)(void);
    /* 0x08 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x0C */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x10 */ void (*startLerp)(MenuLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x14 */ s32 (*updateLerp)(MenuLerp *lerp);
    /* 0x18 */ struct CardShopStock *(*getStock)(s32 shop);
    /* 0x1C */ s32 (*getPrice)(s32 card);
} CardShopFuncs;

extern CardShopTitle STCRDSHP_titles[];
extern CardShopFuncs STCRDSHP_funcs;
extern CardShopStock STCRDSHP_stocks[];
extern CardPrice STCRDSHP_prices[];

CardShopStock *STCRDSHP_getStock(s32 shop);
s32 STCRDSHP_getPrice(s32 card);
void STCRDSHP_loadFiles(void);
s32 STCRDSHP_filesLoading(void);
void STCRDSHP_startFade(PanelAnim *fade, s32 fadeIn);
s32 STCRDSHP_updateFade(PanelAnim *fade);
void STCRDSHP_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames);
s32 STCRDSHP_updateLerp(MenuLerp *lerp);
ScreenFade *STCRDSHP_createFader(void);
Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
CardShop *STCRDSHP_createShop(void);
CardPackOpen *STCRDSHP_createPackOpen(CardShop *shop); /* opens a pack */
CardShopBuy *STCRDSHP_createBuy(CardShop *shop, s32 shopId); /* buys cards */
CardPackGrid *STCRDSHP_createGrid(Task *owner, s32 *cards);

#endif
