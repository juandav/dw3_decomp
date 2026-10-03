#include "stcrdshp.h"

#define PAD_HELD(button) ((PAD.getHeld(0) >> PAD.getButtonBit(0, button)) & 1)

void func_800864BC(CardShopBuy *buy, CardShopBuyWindows *win);
void func_80085E44(CardShopBuy *buy);
void func_800870F4(CardShopBuy *buy, CardShopBuyWindows *win);
void initCardDrawer(CardDrawer *obj);

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

/* Shows (or hides) the card under the cursor's name, price, how many the
   player has and its text or numbers */
void func_800859A4(CardShopBuy *buy, CardShopBuyWindows *win, s32 show) {
    CardDrawer drawer;
    s32 card;

    card = buy->stock->cards[buy->page * 6 + buy->column];
    if (show) {
        initCardDrawer(&drawer);
        drawer.setCard(card);
        win->windows[0]->setString(win->windows[0], FILE_CACHE.load(TEXT_FILE(0x17)), card);
        win->windows[10]->setString(win->windows[10], FILE_CACHE.load(TEXT_FILE(0x33)), 3);
        win->windows[11]->setNumber(win->windows[11], 0, STCRDSHP_funcs.getPrice(card));
        win->windows[11]->setRightAlign(win->windows[11], 1);
        win->windows[3]->setString(win->windows[3], FILE_CACHE.load(TEXT_FILE(0x33)), 8);
        win->windows[4]->setNumber(win->windows[4], 0, GAME.cards[card]);
        win->windows[4]->setRightAlign(win->windows[4], 1);
        if (drawer.getKind() != 0) {
            win->windows[1]->setVisible(win->windows[1], 0);
            win->windows[2]->setVisible(win->windows[2], 0);
            win->windows[5]->setString(win->windows[5], FILE_CACHE.load(TEXT_FILE(0x1E)), card);
            win->windows[6]->setVisible(win->windows[6], 0);
            win->windows[7]->setVisible(win->windows[7], 0);
            win->windows[8]->setVisible(win->windows[8], 0);
            win->windows[9]->setVisible(win->windows[9], 0);
        } else {
            win->windows[1]->setString(win->windows[1], FILE_CACHE.load(TEXT_FILE(0x33)), 8);
            win->windows[2]->setNumber(win->windows[2], 0, drawer.card[5]);
            win->windows[2]->setRightAlign(win->windows[2], 1);
            if (card == 0x45 || card == 0x70 || card == 0x9B || card == 0xC6 || card == 0xF1) {
                win->windows[5]->setString(win->windows[5], FILE_CACHE.load(TEXT_FILE(0x1E)), card);
                win->windows[6]->setVisible(win->windows[6], 0);
                win->windows[7]->setVisible(win->windows[7], 0);
                win->windows[8]->setVisible(win->windows[8], 0);
                win->windows[9]->setVisible(win->windows[9], 0);
            } else {
                win->windows[5]->setVisible(win->windows[5], 0);
                win->windows[6]->setString(win->windows[6], FILE_CACHE.load(TEXT_FILE(0x33)), 0x11);
                win->windows[7]->setNumber(win->windows[7], 0, drawer.card[1]);
                win->windows[7]->setRightAlign(win->windows[7], 1);
                win->windows[8]->setString(win->windows[8], FILE_CACHE.load(TEXT_FILE(0x33)), 0x12);
                win->windows[9]->setNumber(win->windows[9], 0, drawer.card[2]);
                win->windows[9]->setRightAlign(win->windows[9], 1);
            }
        }
    } else {
        win->windows[0]->setVisible(win->windows[0], 0);
        win->windows[10]->setVisible(win->windows[10], 0);
        win->windows[11]->setVisible(win->windows[11], 0);
        win->windows[3]->setVisible(win->windows[3], 0);
        win->windows[4]->setVisible(win->windows[4], 0);
        win->windows[1]->setVisible(win->windows[1], 0);
        win->windows[2]->setVisible(win->windows[2], 0);
        win->windows[5]->setVisible(win->windows[5], 0);
        win->windows[6]->setVisible(win->windows[6], 0);
        win->windows[7]->setVisible(win->windows[7], 0);
        win->windows[8]->setVisible(win->windows[8], 0);
        win->windows[9]->setVisible(win->windows[9], 0);
    }
}

extern s32 D_8008C15C[];

/* Draws the screen: the card under the cursor's frames, the cursor, the
   arrows and the title */
void func_80085E44(CardShopBuy *buy) {
    SpriteDrawer sprite;
    CardDrawer drawer;
    s32 card;
    s32 kind;
    s32 frame;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0);
    sprite.setLayerId(buy->layer, buy->depth);
    card = buy->stock->cards[buy->page * 6 + buy->column];
    if (buy->fades[0].level != 0) {
        initCardDrawer(&drawer);
        drawer.setCard(card);
        if (buy->fades[0].level != 0x1000) {
            sprite.setScale(buy->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x87);
        }
        kind = drawer.getKind();
        if (kind == 1) {
            frame = 0x12;
        } else if (kind == 2) {
            frame = 0x13;
        } else {
            frame = drawer.card[0] + 0x13;
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), frame, 0x103, 0x7E);
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xD, 0xFC, 0x7C);
        if (buy->fades[0].level != 0x1000) {
            sprite.setPivot(0x140, 0x87);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xA, 0x82, 0x7C);
        if (buy->fades[0].level != 0x1000) {
            sprite.setPivot(0x140, 0xAF);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x10, 0x103, 0xA4);
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xD, 0xFC, 0xA2);
        if (buy->fades[0].level != 0x1000) {
            sprite.setPivot(0x140, 0xA5);
        }
        if (kind != 0) {
            sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xB, 0x4A, 0x92);
        } else if (card == 0x45 || card == 0x70 || card == 0x9B || card == 0xC6 || card == 0xF1) {
            sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xB, 0x4A, 0x92);
        } else {
            sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xC, 0xC7, 0x92);
        }
        if (buy->fades[1].level != 0x1000) {
            sprite.setPivot(0x140, 0xC8);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x29, 0xD6, 0xBF);
    }
    if (buy->cursorShown != 0) {
        if (GFX.funcs.getTime() - buy->cursorTime >= 4) {
            buy->cursorTime = GFX.funcs.getTime();
            if (++buy->cursorFrame >= 6) {
                buy->cursorFrame = 0;
            }
        }
        sprite.setClutRow(D_8008C15C[buy->cursorFrame]);
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 7, buy->column * 0x2A + 0x24, 0x44);
        sprite.setClutRow(0);
        if (buy->pages >= 2) {
            if (GFX.funcs.getTime() - buy->arrowsTime >= 0x11) {
                buy->arrowsTime = GFX.funcs.getTime();
                buy->arrowsShown = 1 - buy->arrowsShown;
            }
            if (buy->fades[0].level == 0x1000 && buy->arrowsShown != 0) {
                if (buy->page > 0) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x1A, 0xE, 0x55);
                }
                if (buy->page < buy->pages - 1) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x1B, 0x121, 0x55);
                }
            }
        }
    }
    if (buy->fades[1].level != 0) {
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x280, 0);
        sprite.setLayerId(buy->layer, buy->depth - 2);
        if (buy->fades[1].level != 0x1000) {
            sprite.setScale(buy->fades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x3F);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x2C, 0x7B, 0x33);
        if (buy->fades[2].level != 0) {
            if (buy->fades[2].level != 0x1000) {
                sprite.setScale(buy->fades[2].level, 0x1000, 0x1000);
                sprite.setPivot(0x140, 0x64);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x2D, 0xAF, 0x50);
        }
    }
}

/* The states of the screen to buy cards: picking a card (left/right, L1/R1
   for the pages), the yes/no to buy it and the messages when the player
   can't */
void func_800864BC(CardShopBuy *buy, CardShopBuyWindows *win) {
    CardDrawer drawer;
    s32 old;
    s32 i;

    if (win->grid->state != 1) {
        return;
    }
    switch (buy->substate) {
    case 0:
    default:
        STCRDSHP_funcs.startFade(&buy->fades[0], 1);
        buy->substate++;
        break;
    case 1:
        if (STCRDSHP_funcs.updateFade(&buy->fades[0])) {
            buy->cursorShown = 1;
            func_800859A4(buy, win, 1);
            if (buy->pages >= 2) {
                if (buy->page < buy->pages - 1) {
                    win->windows[13]->setString(win->windows[13], FILE_CACHE.load(TEXT_FILE(0x33)), 0xB);
                } else {
                    win->windows[13]->setVisible(win->windows[13], 0);
                }
            }
            buy->substate++;
        }
        break;
    case 2:
        old = buy->column;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            buy->column--;
            if (buy->column < 0) {
                buy->column = 0;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            buy->column++;
            if (buy->column >= 6) {
                buy->column = 5;
            }
        }
        if (old != buy->column) {
            if (buy->stock->cards[buy->page * 6 + buy->column] != 0) {
                SOUND.playSound(0x4001B);
                func_800859A4(buy, win, 1);
            } else {
                buy->column = old;
            }
        }
        old = buy->page;
        if (!PAD_HELD(PAD_R1) && PAD_PRESSED(PAD_L1)) {
            buy->page--;
            if (buy->page < 0) {
                buy->page = 0;
            }
        } else if (!PAD_HELD(PAD_L1) && PAD_PRESSED(PAD_R1)) {
            buy->page++;
            if (buy->page > buy->pages - 1) {
                buy->page = buy->pages - 1;
            }
        }
        if (old != buy->page) {
            SOUND.playSound(0x4001B);
            buy->cursorShown = 0;
            buy->column = 0;
            for (i = 0; i < 6; i++) {
                buy->cards[i] = buy->stock->cards[buy->page * 6 + i];
            }
            win->grid->setCards(win->grid, buy->cards);
            if (buy->pages >= 2) {
                if (buy->page > 0) {
                    win->windows[12]->setString(win->windows[12], FILE_CACHE.load(TEXT_FILE(0x33)), 0xA);
                } else {
                    win->windows[12]->setVisible(win->windows[12], 0);
                }
                if (buy->page < buy->pages - 1) {
                    win->windows[13]->setString(win->windows[13], FILE_CACHE.load(TEXT_FILE(0x33)), 0xB);
                } else {
                    win->windows[13]->setVisible(win->windows[13], 0);
                }
            }
            buy->substate = 1;
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            initCardDrawer(&drawer);
            buy->unk98 = buy->stock->cards[buy->page * 6 + buy->column];
            drawer.setCard(buy->unk98);
            buy->unk9C = STCRDSHP_funcs.getPrice(buy->unk98);
            SOUND.playSound(0x4001C);
            if (GAME.money < buy->unk9C) {
                buy->substate = 10;
                buy->step = 0x13;
            } else if (GAME.cards[buy->unk98] == 9) {
                buy->substate = 10;
                buy->step = 0x14;
            } else {
                buy->substate = 5;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            buy->substate = 50;
        }
        break;
    case 5:
        STCRDSHP_funcs.startFade(&buy->fades[1], 1);
        STCRDSHP_funcs.startFade(&buy->fades[2], 1);
        buy->substate++;
        break;
    case 6:
        STCRDSHP_funcs.updateFade(&buy->fades[2]);
        if (STCRDSHP_funcs.updateFade(&buy->fades[1])) {
            win->windows[14]->setString(win->windows[14], FILE_CACHE.load(TEXT_FILE(0x33)), 0xC);
            win->windows[14]->setNumber(win->windows[14], 1, buy->unk9C);
            win->windows[15]->setString(win->windows[15], FILE_CACHE.load(TEXT_FILE(0x33)), 0xD);
            win->windows[16]->setString(win->windows[16], FILE_CACHE.load(TEXT_FILE(0x33)), 0xE);
            win->cursor->setPos(win->cursor, 0xB8, buy->unk94 * 0x10 + 0x56);
            win->cursor->setVisible(win->cursor, 1);
            buy->substate++;
        }
        break;
    case 7:
        old = buy->unk94;
        if (PAD_PRESSED(PAD_UP)) {
            buy->unk94 = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            buy->unk94 = 1;
        }
        if (old != buy->unk94) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0xB8, buy->unk94 * 0x10 + 0x56);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (buy->unk94 == 0) {
                GAME.funcs.addCards(buy->unk98, 1);
                GAME.money -= buy->unk9C;
                buy->shop->showMoney(buy->shop);
            }
            buy->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            buy->substate++;
        }
        break;
    case 8:
        win->windows[14]->setVisible(win->windows[14], 0);
        win->windows[15]->setVisible(win->windows[15], 0);
        win->windows[16]->setVisible(win->windows[16], 0);
        win->cursor->setVisible(win->cursor, 0);
        buy->unk94 = 0;
        STCRDSHP_funcs.startFade(&buy->fades[1], 0);
        buy->substate++;
        break;
    case 10:
        STCRDSHP_funcs.startFade(&buy->fades[1], 1);
        buy->fades[2].level = 0;
        buy->substate++;
        break;
    case 11:
        if (STCRDSHP_funcs.updateFade(&buy->fades[1])) {
            win->windows[14]->setString(win->windows[14], FILE_CACHE.load(TEXT_FILE(0x33)), buy->step);
            buy->substate++;
        }
        break;
    case 12:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x4001C);
            win->windows[14]->setVisible(win->windows[14], 0);
            STCRDSHP_funcs.startFade(&buy->fades[1], 0);
            buy->substate++;
        }
        break;
    case 9:
    case 13:
        if (STCRDSHP_funcs.updateFade(&buy->fades[1])) {
            buy->substate = 1;
        }
        break;
    case 50:
        buy->cursorShown = 0;
        win->windows[12]->setVisible(win->windows[12], 0);
        win->windows[13]->setVisible(win->windows[13], 0);
        func_800859A4(buy, win, 0);
        STCRDSHP_funcs.startFade(&buy->fades[0], 0);
        buy->substate++;
        break;
    case 51:
        if (STCRDSHP_funcs.updateFade(&buy->fades[0])) {
            win->grid->hide(win->grid);
            buy->state = TASK_DONE;
        }
        break;
    }
}

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
