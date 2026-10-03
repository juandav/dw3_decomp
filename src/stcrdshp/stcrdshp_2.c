#include "stcrdshp.h"

void func_800864BC(CardShopBuy *buy, CardShopBuyWindows *win);
void func_80085E44(CardShopBuy *buy);
void func_800870F4(CardShopBuy *buy, CardShopBuyWindows *win);

/* Creates the screen's windows and its cursor */
void STCRDSHP_createBuyWindows(CardShopBuy *buy, CardShopBuyWindows *win) {
    win->windows[0] = createTextWindow(buy->layer, 1, 0x88, 0x80);
    win->windows[1] = createTextWindow(buy->layer, 1, 0x115, 0x80);
    win->windows[2] = createTextWindow(buy->layer, 1, 0x126, 0x80);
    win->windows[3] = createTextWindow(buy->layer, 1, 0x115, 0xA6);
    win->windows[4] = createTextWindow(buy->layer, 1, 0x12C, 0xA6);
    win->windows[5] = createTextWindow(buy->layer, 1, 0x50, 0x97);
    win->windows[6] = createTextWindow(buy->layer, 1, 0xCE, 0x97);
    win->windows[7] = createTextWindow(buy->layer, 1, 0xF0, 0x97);
    win->windows[8] = createTextWindow(buy->layer, 1, 0xCE, 0xA4);
    win->windows[9] = createTextWindow(buy->layer, 1, 0xF0, 0xA4);
    win->windows[11] = createTextWindow(buy->layer, 3, 0x117, 0xC7);
    win->windows[10] = createTextWindow(buy->layer, 3, 0x11A, 0xC7);
    win->windows[12] = createTextWindow(buy->layer, 1, 0x12, 0x67);
    win->windows[13] = createTextWindow(buy->layer, 1, 0x121, 0x67);
    win->windows[13]->setDepth(win->windows[13], buy->depth);
    win->windows[14] = createTextWindow(buy->layer, 1, 0x9A, 0x39);
    win->windows[15] = createTextWindow(buy->layer, 1, 0xC5, 0x56);
    win->windows[16] = createTextWindow(buy->layer, 1, 0xC5, 0x66);
    win->cursor = createCursor(buy->layer, buy->depth - 3, 0xB8, 0x56);
    win->cursor->setVisible(win->cursor, 0);
}

INCLUDE_ASM("stcrdshp/nonmatchings/stcrdshp_2", func_800859A4);

INCLUDE_ASM("stcrdshp/nonmatchings/stcrdshp_2", func_80085E44);

INCLUDE_ASM("stcrdshp/nonmatchings/stcrdshp_2", func_800864BC);

INCLUDE_ASM("stcrdshp/nonmatchings/stcrdshp_2", func_800870F4);

/* Creates the screen to buy the cards of a shop */
CardShopBuy *STCRDSHP_createBuy(CardShop *shop, s32 shopId) {
    CardShopBuy *buy = createTask(func_800870F4, sizeof(CardShopBuy), sizeof(CardShopBuyWindows));

    buy->layer = 0x1000;
    buy->depth = 6;
    buy->shop = shop;
    buy->shopId = shopId;
    return buy;
}
