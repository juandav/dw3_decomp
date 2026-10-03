#include "stcrdshp.h"

void STCRDSHP_updateScene(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0xF000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)STCRDSHP_createShop();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STCRDSHP_start(void) {
    return createTask(STCRDSHP_updateScene, sizeof(Task), 4);
}

/* Creates the shop's windows and its cursor */
void STCRDSHP_createShopWindows(CardShop *shop, CardShopWindows *win) {
    TextWindow **windows;
    s32 i;
    s32 j;

    win->title = createTextWindow(shop->layer, 1, 0x1D, 0x16);
    win->help = createTextWindow(shop->layer, 1, 0xD3, 0xCC);
    win->money = createTextWindow(shop->layer, 3, 0x117, 0x1C);
    win->moneyLabel = createTextWindow(shop->layer, 3, 0x11A, 0x1C);
    for (i = 0; i < 3; i++) {
        win->options[i] = createTextWindow(shop->layer, 1, 0xA7, i * 14 + 0x35);
    }
    j = 0; /* the match depends on setting it here and on the loop's form */
    win->cursor = createCursor(shop->layer, shop->depth - 2, 0xA7, shop->cursor * 14 + 0x35);
    win->cursor->setVisible(win->cursor, 0);
    win->message = createTextWindow(shop->layer, 1, 0x9A, 0x71);
    windows = shop->children;
    while (j < shop->childCount - 3) {
        j++;
        (*windows)->setDepth(*windows, shop->depth - 2);
        windows++;
    }
}

/* Shows or hides the shop's title and the money */
void STCRDSHP_showTitle(CardShop *shop, CardShopWindows *win, s32 show) {
    if (show) {
        win->title->setString(win->title, FILE_CACHE.load(TEXT_FILE(0x95)), shop->title);
        win->moneyLabel->setString(win->moneyLabel, FILE_CACHE.load(TEXT_FILE(0x33)), 3);
        win->money->setNumber(win->money, 0, GAME.money);
        win->money->setRightAlign(win->money, 1);
    } else {
        win->title->setVisible(win->title, 0);
        win->moneyLabel->setVisible(win->moneyLabel, 0);
        win->money->setVisible(win->money, 0);
    }
}

/* Shows or hides the options (buy cards, open a pack, item shop) and the help */
void STCRDSHP_showOptions(CardShop *shop, CardShopWindows *win, s32 show) {
    s32 i;

    if (show) {
        for (i = 0; i < 3; i++) {
            win->options[i]->setString(win->options[i], FILE_CACHE.load(TEXT_FILE(0x33)), i + 5);
        }
        win->help->setString(win->help, FILE_CACHE.load(TEXT_FILE(0x33)), 4);
    } else {
        for (i = 0; i < 3; i++) {
            win->options[i]->setVisible(win->options[i], 0);
        }
        win->help->setVisible(win->help, 0);
    }
}

/* Draws the scrolling background and the panels as they open */
void STCRDSHP_drawShop(CardShop *shop) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(shop->layer, 7);
    sprite.setTexture(0x280, 0);
    if (shop->scrollWait != 0) {
        shop->scroll++;
        shop->scroll = shop->scroll < 0x60 ? shop->scroll : 0;
        shop->scrollWait = 0;
    } else {
        shop->scrollWait = 1;
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 8, shop->scroll, shop->scroll);
    sprite.setLayerId(shop->layer, shop->depth - 1);
    if (shop->fades[0].level != 0) {
        if (shop->fades[0].level != 0x1000) {
            sprite.setScale(shop->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x57, 0x1B);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x28, 0x16, 0x14);
        if (shop->fades[0].level != 0x1000) {
            sprite.setPivot(0x140, 0x1D);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x29, 0xD6, 0x15);
    }
    if (shop->fades[1].level != 0) {
        if (shop->fades[1].level != 0x1000) {
            sprite.setScale(shop->fades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x49);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x2F, 0x92, 0x2E);
        if (shop->fades[1].level != 0x1000) {
            sprite.setPivot(0x140, 0xD2);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0xF, 0xC6, 0xC4);
    }
    if (shop->fades[2].level != 0) {
        if (shop->fades[2].level != 0x1000) {
            sprite.setScale(shop->fades[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x77);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_CARDSHOP_SPRITES << 16), 0x2C, 0x7B, 0x6B);
    }
}

/* Opens the panels, moves the cursor and starts what was chosen */
void STCRDSHP_runShop(CardShop *shop, CardShopWindows *win) {
    s32 cursor;
    s32 count;
    s32 i;

    switch (shop->substate) {
    case 0:
    default:
        STCRDSHP_funcs.startFade(&shop->fades[0], 1);
        shop->substate++;
        break;
    case 1:
        if (STCRDSHP_funcs.updateFade(&shop->fades[0]) != 0) {
            STCRDSHP_showTitle(shop, win, 1);
            STCRDSHP_funcs.startFade(&shop->fades[1], 1);
            shop->substate++;
        }
        break;
    case 2:
        if (STCRDSHP_funcs.updateFade(&shop->fades[1]) != 0) {
            STCRDSHP_showOptions(shop, win, 1);
            win->cursor->setPos(win->cursor, 0x9A, shop->cursor * 14 + 0x35);
            win->cursor->setVisible(win->cursor, 1);
            shop->substate++;
        }
        break;
    case 3:
        cursor = shop->cursor;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            if (--shop->cursor < 0) {
                shop->cursor = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (++shop->cursor >= 3) {
                shop->cursor = 2;
            }
        }
        if (cursor != shop->cursor) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0x9A, shop->cursor * 14 + 0x35);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            shop->substate = 10;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            shop->setSubstate(shop, 50);
        }
        break;
    case 10:
        shop->step = 1;
        switch (shop->cursor) {
        case 0:
        default:
            win->dialog = (Task *)STCRDSHP_createBuy(shop, shop->shop);
            shop->substate = 50;
            break;
        case 1:
            count = ITEM_FUNCS->list(1, (u16 *)shop->items);
            for (i = 0; i < count; i++) {
                if (ITEM_FUNCS->getCategory(shop->items[i]) == 0x62) {
                    win->dialog = (Task *)STCRDSHP_createPackOpen(shop);
                    shop->substate = 50;
                    break;
                }
            }
            if (win->dialog == NULL) {
                shop->setSubstate(shop, 20);
            }
            break;
        case 2:
            shop->substate = 100;
            shop->toItemShop = 1;
            break;
        }
        break;
    case 11:
        if (win->dialog == NULL) {
            shop->substate = 1;
        }
        break;
    case 20:
        win->cursor->setStill(win->cursor, 1);
        win->cursor->setPalette(win->cursor, 7);
        STCRDSHP_funcs.startFade(&shop->fades[2], 1);
        shop->substate++;
        break;
    case 21:
        if (STCRDSHP_funcs.updateFade(&shop->fades[2]) != 0) {
            win->message->setString(win->message, FILE_CACHE.load(TEXT_FILE(0x33)), 0x15);
            shop->substate++;
        }
        break;
    case 22:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            win->message->setVisible(win->message, 0);
            STCRDSHP_funcs.startFade(&shop->fades[2], 0);
            shop->substate++;
        }
        break;
    case 23:
        if (STCRDSHP_funcs.updateFade(&shop->fades[2]) != 0) {
            win->cursor->setStill(win->cursor, 0);
            win->cursor->setPalette(win->cursor, 0);
            shop->substate = 3;
        }
        break;
    case 50:
        if (shop->step == 0) {
            win->fade = STCRDSHP_createFader();
            win->fade->start(win->fade, 0, 0x1E);
            win->fade->depth = 6;
        }
        STCRDSHP_showOptions(shop, win, 0);
        win->cursor->setVisible(win->cursor, 0);
        STCRDSHP_funcs.startFade(&shop->fades[1], 0);
        shop->substate++;
        break;
    case 51:
        if (STCRDSHP_funcs.updateFade(&shop->fades[1]) != 0) {
            if (shop->step == 0) {
                STCRDSHP_showTitle(shop, win, 0);
                STCRDSHP_funcs.startFade(&shop->fades[0], 0);
                shop->substate++;
            } else {
                shop->substate = 11;
            }
        }
        break;
    case 52:
        if (STCRDSHP_funcs.updateFade(&shop->fades[0]) != 0) {
            shop->substate = 101;
        }
        break;
    case 100:
        win->fade = STCRDSHP_createFader();
        win->fade->start(win->fade, 0, 10);
        shop->substate++;
        break;
    case 101:
        if (win->fade->state == 2) {
            shop->state = TASK_KILL;
        }
        break;
    }
}

/* Shows the money left (after buying) */
void STCRDSHP_showMoney(CardShop *shop) {
    CardShopWindows *win = shop->children;

    win->money->setNumber(win->money, 0, GAME.money);
    win->money->setRightAlign(win->money, 1);
}

/* The shop's update: loads its files, then runs it; leaves to the field or
   the item shop */
void STCRDSHP_updateShop(CardShop *shop, CardShopWindows *win) {
    switch (shop->state) {
    case TASK_INIT:
    default:
        switch (shop->substate) {
        case 0:
        default:
            STCRDSHP_funcs.loadFiles();
            shop->substate++;
            break;
        case 1:
            if (STCRDSHP_funcs.filesLoading() == 0) {
                STCRDSHP_createShopWindows(shop, win);
                shop->fades[0].duration = 10;
                shop->fades[1].duration = 10;
                shop->fades[2].duration = 10;
                shop->nextState(shop);
            }
            break;
        }
        break;
    case TASK_RUN:
        STCRDSHP_runShop(shop, win);
        STCRDSHP_drawShop(shop);
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        if (shop->toItemShop != 0) {
            GAME.funcs.requestMode(0x400, GAME.funcs.getModeArg());
        } else {
            GAME.funcs.requestMode(GAME.fieldMode, 0);
        }
        break;
    }
}

CardShop *STCRDSHP_createShop(void) {
    CardShop *shop = createTask(STCRDSHP_updateShop, sizeof(CardShop), sizeof(CardShopWindows));
    s32 mode;
    s32 i;

    shop->showMoney = STCRDSHP_showMoney;
    shop->layer = 0x1000;
    shop->depth = 7;
    shop->shop = GAME.funcs.getModeArg();
    mode = GAME.fieldMode;
    for (i = 0; STCRDSHP_titles[i].mode != 0; i++) {
        if (STCRDSHP_titles[i].mode == mode) {
            shop->title = STCRDSHP_titles[i].title;
        }
    }
    if (shop->title == 0) {
        shop->title = 0x1F;
    }
    if (GAME_FUNCS.getPrevMode() == 0x400) {
        shop->cursor = 2;
    }
    FILE_CACHE.request(FILE_CARD_DATA);
    FILE_CACHE.request(FILE_CARD_DATA + 1);
    FILE_CACHE.request(FILE_CARD_DATA + 2);
    FILE_CACHE.request(FILE_CARD_DATA + 3);
    FILE_CACHE.request(FILE_CARD_DATA + 4);
    FILE_CACHE.request(TEXT_FILE(0x17));
    FILE_CACHE.request(TEXT_FILE(0x1E));
    return shop;
}

/* Loads the shop's textures and requests its strings */
void STCRDSHP_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0);
    loader.loadArchive(FILE_CACHE.getEntry(FILE_CARDSHOP_IMAGES << 16));
    FILE_CACHE.request(TEXT_FILE(0x33));
    FILE_CACHE.request(TEXT_FILE(0x17));
    FILE_CACHE.request(TEXT_FILE(0x1E));
    FILE_CACHE.request(TEXT_FILE(0x95));
    FILE_CACHE.request(TEXT_FILE(0x6B));
}

/* Whether the shop's strings are still loading */
s32 STCRDSHP_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x33)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x17)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x1E)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x95)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x6B)) != 0;
}

void STCRDSHP_startFade(PanelAnim *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn != 0) {
        SOUND.playSound(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        SOUND.playSound(0x4001A);
        fade->level = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

s32 STCRDSHP_updateFade(PanelAnim *fade) {
    if (fade->active == 0) {
        return 1;
    }
    fade->level += fade->step;
    if (fade->step > 0) {
        if (fade->level > 0x1000) {
            fade->level = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->level < 0) {
        fade->level = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

void STCRDSHP_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STCRDSHP_updateLerp(MenuLerp *lerp) {
    if (lerp->active == 0) {
        return 1;
    }
    lerp->fixed += lerp->step;
    lerp->value = lerp->fixed >> 8;
    if (lerp->step > 0) {
        if (lerp->target < lerp->value) {
            lerp->value = lerp->target;
            lerp->active = 0;
            return 1;
        }
    } else if (lerp->value < lerp->target) {
        lerp->value = lerp->target;
        lerp->active = 0;
        return 1;
    }
    return 0;
}

/* The stock of a shop (the first one's if it has none), counting its cards */
CardShopStock *STCRDSHP_getStock(s32 shop) {
    s32 found = -1;
    s32 i;

    for (i = 0; STCRDSHP_stocks[i].shop != -1; i++) {
        if (STCRDSHP_stocks[i].shop == shop) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        found = 0;
    }
    STCRDSHP_stocks[found].count = 0;
    for (i = 0; STCRDSHP_stocks[found].cards[i] != 0; i++) {
        STCRDSHP_stocks[found].count++;
    }
    return &STCRDSHP_stocks[found];
}

/* The price of a card */
s32 STCRDSHP_getPrice(s32 card) {
    s32 i;

    for (i = 0; STCRDSHP_prices[i].card != 0; i++) {
        if (STCRDSHP_prices[i].card == card) {
            return STCRDSHP_prices[i].price;
        }
    }
    return 1;
}
