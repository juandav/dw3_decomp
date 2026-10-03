#include "stitshop.h"

#define PAD_HELD(button) ((PAD.getHeld(0) >> PAD.getButtonBit(0, button)) & 1)

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
void func_800830DC(ShopBuy *buy, ShopBuyWindows *win);
void func_8008361C(ShopBuy *buy, ShopBuyWindows *win);
void func_80085254(ShopSell *sell, ShopSellWindows *win);
void func_80085684(ShopSell *sell, ShopSellWindows *win);
ShopItemList *STITSHOP_createItemList(Task *dialog, s32 type, s32 selling);
ShopInfo *STITSHOP_createInfo(s32 selling, s32 item);
void func_80086CE4(ShopItemList *list, ShopItemListWindows *win, s32 show);
void func_800875AC(ShopItemList *list, ShopItemListWindows *win);
void func_80087D5C(ShopItemList *list, s32 frozen);
void func_80087E00(ShopItemList *list, s32 visible);
void STITSHOP_listSellable(ShopItemList *list);
void func_80088960(ShopInfo *info, ShopInfoWindows *win, s32 show);
void func_800894EC(ShopInfo *info, ShopInfoWindows *win, s32 show);
void func_80089774(ShopInfo *info, ShopInfoWindows *win, s32 show);
void func_8008988C(ShopInfo *info, ShopInfoWindows *win, s32 show);
void func_8008A5E8(ShopInfo *info, ShopInfoWindows *win);
void func_80089104(ShopInfo *info, ShopInfoWindows *win);
void func_80089DE8(ShopInfo *info, ShopInfoWindows *win);
void func_80089AE0(ShopInfo *info, ShopInfoWindows *win);
void func_8008A46C(ShopInfo *info, ShopInfoWindows *win);
void func_800884A4(s16 *p, s32 stat, s32 delta);
void func_8008AF88(ItemShop *shop, ItemShopWindows *win);
extern s32 D_8008C0D4[];
extern s32 D_8008C114[];
extern Vec2 STITSHOP_changePos[];
extern s32 D_8008C148[];
extern s32 D_8008C16C[];
ItemShop *STITSHOP_createShop(void);
void STITSHOP_updateShop();
void STITSHOP_loadFiles(void);
s32 STITSHOP_filesLoading(void);
void STITSHOP_startFade(PanelAnim *fade, s32 fadeIn);
s32 STITSHOP_updateFade(PanelAnim *fade);
void STITSHOP_startLerp(ShopLerp *lerp, s32 from, s32 to, s32 frames);
s32 STITSHOP_updateLerp(ShopLerp *lerp);
s16 *STITSHOP_getShopItems(s32 shop);
s32 STITSHOP_canEquip(s32 partner, s32 item);
s32 STITSHOP_compareEquip(s32 partner, s32 item);
void STITSHOP_equip(s32 partner, s32 slot, s32 item, s32 fromBag);

void func_800829B4(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x14000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)STITSHOP_createShop();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_80082AB0(void) {
    return createTask(func_800829B4, sizeof(Task), 4);
}

void STITSHOP_startFader(ScreenFade *task, s32 fadeIn, s32 duration) {
    task->setState(task, TASK_RUN);
    task->substate = 1;
    task->fadeIn = fadeIn;
    if (fadeIn == 0) {
        task->level = 0;
        task->levelStep = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->levelStep = -(0xFF00 / duration);
    }
}

void STITSHOP_drawFader(ScreenFade *task) {
    Layer *layer = GFX.funcs.getLayer(task->layerId);
    u_long *ot = (u_long *)layer->getOtEntry(layer, task->depth);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->code = 0x2A;
    poly->r0 = poly->g0 = poly->b0 = task->level >> 8;
    poly->x0 = poly->x2 = 0;
    poly->x1 = poly->x3 = 320;
    poly->y0 = poly->y1 = 0;
    poly->y2 = poly->y3 = 256;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = 0xE1000245;
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void STITSHOP_updateFader(ScreenFade *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        if (task->substate == 0) {
            break;
        }
        task->level += task->levelStep;
        if (task->fadeIn == 0) {
            if (task->level > 0xFF00) {
                task->level = 0xFF00;
                task->state = 2;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = 2;
        }
        /* fallthrough */
    case 2:
        STITSHOP_drawFader(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *STITSHOP_createFader(void) {
    ScreenFade *task = createTask(STITSHOP_updateFader, sizeof(ScreenFade), 0);

    task->start = STITSHOP_startFader;
    task->layerId = 0x1000;
    task->depth = 6;
    return task;
}

void func_80082DA4(ShopBuy *buy, ShopBuyWindows *win) {
    win->quantityLabel = createTextWindow(buy->layer, 1, 0xB9, 0x3A);
    win->times = createTextWindow(buy->layer, 1, 0x103, 0x54);
    win->quantity = createTextWindow(buy->layer, 1, 0x11E, 0x54);
    win->total = createTextWindow(buy->layer, 1, 0x9A, 0x2C);
    win->yes = createTextWindow(buy->layer, 1, 0xC5, 0x49);
    win->no = createTextWindow(buy->layer, 1, 0xC5, 0x59);
    win->cursor = createCursor(buy->layer, buy->depth - 1, 0xB8, 0x49);
    win->cursor->setVisible(win->cursor, 0);
}

void func_80082E90(ShopBuy *buy, ShopBuyWindows *win, s32 show) {
    if (show) {
        win->quantityLabel->setString(win->quantityLabel, FILE_CACHE.load(TEXT_FILE(0x72)), 0x11);
        win->times->setString(win->times, FILE_CACHE.load(TEXT_FILE(0x72)), 8);
        win->quantity->setNumber(win->quantity, 0, buy->quantity);
        win->quantity->setRightAlign(win->quantity, 1);
    } else {
        win->quantityLabel->setVisible(win->quantityLabel, 0);
        win->times->setVisible(win->times, 0);
        win->quantity->setVisible(win->quantity, 0);
    }
}

void func_80082F94(ShopBuy *buy, ShopBuyWindows *win, s32 show) {
    if (show) {
        win->total->setString(win->total, FILE_CACHE.load(TEXT_FILE(0x72)), 0x12);
        win->total->setNumber(win->total, 1, GET_ITEM[0](buy->item)->price * buy->quantity);
        win->yes->setString(win->yes, FILE_CACHE.load(TEXT_FILE(0x72)), 0x13);
        win->no->setString(win->no, FILE_CACHE.load(TEXT_FILE(0x72)), 0x14);
    } else {
        win->total->setVisible(win->total, 0);
        win->yes->setVisible(win->yes, 0);
        win->no->setVisible(win->no, 0);
    }
}

/* Draws the buying screen's frames, the quantity's blinking arrows and the
   marker over a partner */
void func_800830DC(ShopBuy *buy, ShopBuyWindows *win) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(buy->layer, buy->depth);
    sprite.setTexture(0x280, 0x100);
    if (buy->panels[0].level != 0) {
        sprite.setScale(buy->panels[0].level, 0x1000, 0x1000);
        if (buy->panels[0].level != 0x1000) {
            sprite.setPivot(0x140, 0x42);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xA, 0x9A, 0x34);
        if (buy->panels[0].level != 0x1000) {
            sprite.setPivot(0x140, 0x59);
        } else {
            if (GFX.funcs.getTime() - buy->blinkTime >= 9) {
                buy->blinkTime = GFX.funcs.getTime();
                buy->blink = 1 - buy->blink;
            }
            if (buy->blink) {
                if (buy->quantity < buy->max) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x12, 0x122, 0x51);
                }
                if (buy->quantity >= 2) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x13, 0x122, 0x5B);
                }
            }
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xB, 0xF6, 0x4F);
    }
    if (buy->panels[1].level != 0) {
        if (buy->panels[1].level != 0x1000) {
            sprite.setScale(buy->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x32);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x15, 0x7B, 0x26);
        if (buy->panels[1].level != 0x1000) {
            sprite.setPivot(0x140, 0x57);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xC, 0xAF, 0x43);
    }
    if (buy->panels[2].level != 0) {
        sprite.setLayerId(buy->layer, buy->depth - 2);
        if (buy->panels[2].level != 0x1000) {
            sprite.setScale(buy->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x32);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x15, 0x7B, 0x26);
    }
    if (buy->panels[3].level != 0) {
        sprite.setLayerId(buy->layer, buy->depth - 2);
        if (buy->panels[3].level != 0x1000) {
            sprite.setScale(buy->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x32);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x15, 0x7B, 0x26);
    }
    if (buy->markerShown) {
        if (GFX.funcs.getTime() - buy->markerTime >= 9) {
            buy->markerTime = GFX.funcs.getTime();
            if (++buy->markerFrame >= 8) {
                buy->markerFrame = 0;
            }
        }
        sprite.setLayerId(buy->layer, buy->depth - 2);
        sprite.setScale(0x1000, 0x1000, 0x1000);
        sprite.setClutRow(buy->markerFrame);
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xF, buy->partner * 0x63 + 0x10, 0x9C);
    }
}

/* The buying dialog: pick the item in the list, how many, confirm, then
   (equipment) whether to equip it and on which partner */
void func_8008361C(ShopBuy *buy, ShopBuyWindows *win) {
    s32 i;
    s32 n;
    s32 old;
    u16 price;
    s32 partner;

    switch (buy->substate) {
    case 0:
    default:
        if (win->list == NULL) {
            win->list = STITSHOP_createItemList((Task *)buy, buy->shop->shop, 0);
        }
        buy->substate++;
        break;
    case 1:
        if (win->list->state == TASK_DONE) {
            if (win->info == NULL) {
                win->info = STITSHOP_createInfo(0, win->list->getSelected(win->list));
            }
            buy->substate++;
        }
        break;
    case 2:
        if (win->info->substate == 3) {
            win->list->showCursor(win->list, 1);
            buy->substate++;
        }
        break;
    case 3:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            buy->item = win->list->getSelected(win->list);
            if (GAME.items[buy->item] == 99) {
                win->total->setString(win->total, FILE_CACHE_LOAD[0](TEXT_FILE(0x72)), 0x1C);
                win->total->setVisible(win->total, 0);
                buy->substate = 45;
            } else if (GAME.money < GET_ITEM[0](buy->item)->price) {
                win->total->setString(win->total, FILE_CACHE_LOAD[0](TEXT_FILE(0x72)), 0x1B);
                win->total->setVisible(win->total, 0);
                buy->substate = 45;
            } else {
                win->list->showCursor(win->list, 0);
                buy->substate = 5;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            win->list->close(win->list);
            win->info->close(win->info);
            buy->substate = 50;
        } else if (PAD_PRESSED(PAD_CIRCLE)) {
            if (win->info->substate == 3) {
                win->info->turnPage(win->info);
                win->list->freezeCursor(win->list, 1);
                buy->substate = 4;
            }
        }
        break;
    case 4:
        if (win->info->substate == 3) {
            win->list->freezeCursor(win->list, 0);
            buy->substate = 3;
        }
        break;
    case 5:
        win->list->close(win->list);
        price = GET_ITEM[0](buy->item)->price;
        if (price == 0) {
            price = 1;
        }
        buy->max = GAME.money / price;
        if (buy->max + GAME.items[buy->item] >= 100) {
            buy->max = 99 - GAME.items[buy->item];
        }
        buy->substate++;
        break;
    case 6:
        if (win->list->state == TASK_DONE) {
            STITSHOP_funcs.startFade(&buy->panels[0], 1);
            buy->substate++;
        }
        break;
    case 7:
        if (STITSHOP_funcs.updateFade(&buy->panels[0]) != 0) {
            func_80082E90(buy, win, 1);
            buy->substate++;
        }
        break;
    case 8:
        old = buy->quantity;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            buy->quantity++;
            if (buy->quantity > buy->max) {
                buy->quantity = buy->max;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (--buy->quantity <= 0) {
                buy->quantity = 1;
            }
        } else if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            buy->quantity -= 10;
            if (buy->quantity < 10) {
                buy->quantity = 1;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            buy->quantity += 10;
            if (buy->quantity > buy->max) {
                buy->quantity = buy->max;
            }
        }
        if (old != buy->quantity) {
            price = GET_ITEM[0](buy->item)->price;
            if (GAME.money < price * buy->quantity) {
                buy->quantity = GAME.money / price;
            }
            func_80082E90(buy, win, 1);
            win->info->showItem(win->info, buy->item, buy->quantity);
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            buy->nextSubstate(buy);
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            buy->nextSubstate(buy);
            buy->step = 1;
            buy->quantity = 1;
            win->info->showItem(win->info, buy->item, 1);
        } else if (PAD_PRESSED(PAD_CIRCLE)) {
            if (win->info->substate == 3) {
                win->info->turnPage(win->info);
                buy->substate = 12;
            }
        }
        break;
    case 9:
        func_80082E90(buy, win, 0);
        STITSHOP_funcs.startFade(&buy->panels[0], 0);
        buy->substate++;
        break;
    case 10:
        if (STITSHOP_funcs.updateFade(&buy->panels[0]) != 0) {
            if (buy->step != 0) {
                win->list->start(win->list);
                buy->nextSubstate(buy);
            } else {
                buy->substate = 15;
            }
        }
        break;
    case 11:
        if (win->list->state == TASK_DONE) {
            win->list->showCursor(win->list, 1);
            buy->substate = 2;
        }
        break;
    case 12:
        if (win->info->substate == 3) {
            buy->substate = 8;
        }
        break;
    case 15:
        STITSHOP_funcs.startFade(&buy->panels[1], 1);
        buy->substate++;
        break;
    case 16:
        if (STITSHOP_funcs.updateFade(&buy->panels[1]) != 0) {
            func_80082F94(buy, win, 1);
            buy->choice = 0;
            win->cursor->setPos(win->cursor, 0xB8, 0x49);
            win->cursor->setVisible(win->cursor, 1);
            buy->substate++;
        }
        break;
    case 17:
        old = buy->choice;
        if (PAD_PRESSED(PAD_UP)) {
            buy->choice = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            buy->choice = 1;
        }
        if (old != buy->choice) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0xB8, buy->choice * 0x10 + 0x49);
        } else if (win->info->shown && PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            buy->setSubstate(buy, 20);
            if (buy->choice == 0) {
                if (ITEM_FUNCS->isKind(buy->item, 3) || ITEM_FUNCS->isKind(buy->item, 4) ||
                    ITEM_FUNCS->isKind(buy->item, 5)) {
                    buy->step = 1;
                }
                if (GAME.items[buy->item] + buy->quantity >= 100) {
                    GAME.items[buy->item] = 99;
                } else {
                    GAME.items[buy->item] += buy->quantity;
                }                win->info->showItem(win->info, buy->item, buy->quantity);
                GAME.money -= GET_ITEM[0](buy->item)->price * buy->quantity;
                buy->shop->showMoney(buy->shop);
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            buy->setSubstate(buy, 20);
        } else if (PAD_PRESSED(PAD_CIRCLE)) {
            if (win->info->substate == 3) {
                win->info->turnPage(win->info);
                buy->substate = 18;
            }
        }
        break;
    case 18:
        if (win->info->substate == 3) {
            buy->substate = 17;
        }
        break;
    case 20:
        buy->quantity = 1;
        win->info->showItem(win->info, buy->item, 1);
        func_80082F94(buy, win, 0);
        win->cursor->setVisible(win->cursor, 0);
        STITSHOP_funcs.startFade(&buy->panels[1], 0);
        buy->substate++;
        break;
    case 21:
        if (STITSHOP_funcs.updateFade(&buy->panels[1]) != 0) {
            if (buy->step != 0) {
                for (i = 0, n = 0; i < 3; i++) {
                    if (STITSHOP_funcs.canEquip(GAME.funcs.getPartyMember(i), buy->item)) {
                        n++;
                    }
                }
                if (n != 0) {
                    buy->setSubstate(buy, 25);
                } else {
                    buy->substate = 10;
                    buy->step = 1;
                }
            } else {
                buy->substate = 10;
                buy->step = 1;
            }
        }
        break;
    case 25:
        if (win->info->shown) {
            win->info->nextSubstate(win->info);
            STITSHOP_funcs.startFade(&buy->panels[1], 1);
            STITSHOP_funcs.startFade(&buy->panels[2], 1);
            buy->substate++;
        }
        break;
    case 26:
        STITSHOP_funcs.updateFade(&buy->panels[1]);
        if (STITSHOP_funcs.updateFade(&buy->panels[2]) != 0) {
            win->total->setString(win->total, FILE_CACHE.load(TEXT_FILE(0x72)), 0x15);
            win->yes->setString(win->yes, FILE_CACHE.load(TEXT_FILE(0x72)), 0x16);
            win->no->setString(win->no, FILE_CACHE.load(TEXT_FILE(0x72)), 0x17);
            buy->choice = 0;
            win->cursor->setPos(win->cursor, 0xB8, 0x49);
            win->cursor->setVisible(win->cursor, 1);
            buy->substate++;
        }
        break;
    case 27:
        old = buy->choice;
        if (PAD_PRESSED(PAD_UP)) {
            buy->choice = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            buy->choice = 1;
        }
        if (old != buy->choice) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0xB8, buy->choice * 0x10 + 0x49);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            buy->nextSubstate(buy);
            if (buy->choice == 0) {
                buy->step = 1;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            buy->nextSubstate(buy);
        }
        break;
    case 28:
        win->total->setVisible(win->total, 0);
        win->yes->setVisible(win->yes, 0);
        win->no->setVisible(win->no, 0);
        win->cursor->setVisible(win->cursor, 0);
        STITSHOP_funcs.startFade(&buy->panels[1], 0);
        if (buy->step == 0) {
            STITSHOP_funcs.startFade(&buy->panels[2], 0);
        }
        buy->substate++;
        break;
    case 29:
        if (buy->step == 0) {
            STITSHOP_funcs.updateFade(&buy->panels[2]);
        }
        if (STITSHOP_funcs.updateFade(&buy->panels[1]) != 0) {
            if (buy->step != 0) {
                buy->setSubstate(buy, 30);
            } else {
                buy->substate = 10;
                buy->step = 1;
                win->info->nextSubstate(win->info);
            }
        }
        break;
    case 30:
        STITSHOP_funcs.startFade(&buy->panels[2], 1);
        buy->substate++;
        break;
    case 31:
        if (STITSHOP_funcs.updateFade(&buy->panels[2]) != 0) {
            if (buy->step == 0) {
                for (buy->partner = 0; buy->partner < 3; buy->partner++) {
                    if (STITSHOP_funcs.canEquip(GAME.funcs.getPartyMember(buy->partner), buy->item)) {
                        break;
                    }
                }
            }
            buy->markerShown = 1;
            win->total->setString(win->total, FILE_CACHE_LOAD[0](TEXT_FILE(0x72)), 0x10);
            buy->substate++;
        }
        break;
    case 32:
        old = buy->partner;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            do {
                if (--buy->partner < 0) {
                    buy->partner = 0;
                    break;
                }
            } while (!STITSHOP_funcs.canEquip(GAME_FUNCS.getPartyMember(buy->partner), buy->item));
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            do {
                if (++buy->partner > win->info->unk60 - 1) {
                    buy->partner = win->info->unk60 - 1;
                    break;
                }
            } while (!STITSHOP_funcs.canEquip(GAME_FUNCS.getPartyMember(buy->partner), buy->item));
        }
        if (old != buy->partner) {
            if (STITSHOP_funcs.canEquip(GAME_FUNCS.getPartyMember(buy->partner), buy->item)) {
                SOUND.playSound(0x4001B);
            } else {
                buy->partner = old;
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            partner = GAME_FUNCS.getPartyMember(buy->partner);
            STITSHOP_funcs.equip(partner, STITSHOP_funcs.compareEquip(partner, buy->item), buy->item, 1);
            win->info->func_8008AAB0(win->info, buy->partner);
            buy->substate = 36;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            buy->substate++;
        }
        break;
    case 33:
        STITSHOP_funcs.startFade(&buy->panels[2], 0);
        win->total->setVisible(win->total, 0);
        buy->substate++;
        break;
    case 34:
        if (STITSHOP_funcs.updateFade(&buy->panels[2]) != 0) {
            buy->substate++;
        }
        break;
    case 35:
        buy->substate = 10;
        buy->step = 1;
        win->info->nextSubstate(win->info);
        buy->markerShown = 0;
        break;
    case 36:
        buy->markerShown = 0;
        STITSHOP_funcs.startFade(&buy->panels[2], 0);
        win->total->setVisible(win->total, 0);
        buy->substate++;
        break;
    case 37:
        if (STITSHOP_funcs.updateFade(&buy->panels[2]) != 0) {
            STITSHOP_funcs.startFade(&buy->panels[3], 1);
            buy->substate++;
        }
        break;
    case 38:
        if (STITSHOP_funcs.updateFade(&buy->panels[3]) != 0) {
            win->total->setString(win->total, FILE_CACHE_LOAD[0](TEXT_FILE(0x72)), 9);
            buy->substate++;
        }
        break;
    case 39:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            STITSHOP_funcs.startFade(&buy->panels[3], 0);
            win->total->setVisible(win->total, 0);
            buy->substate++;
        }
        break;
    case 40:
        if (STITSHOP_funcs.updateFade(&buy->panels[3]) != 0) {
            if (GAME.items[buy->item] <= 0) {
                buy->substate = 35;
            } else {
                buy->substate = 30;
                buy->step = 1;
            }
        }
        break;
    case 45:
        STITSHOP_funcs.startFade(&buy->panels[2], 1);
        win->list->freezeCursor(win->list, 1);
        buy->substate++;
        break;
    case 46:
        if (STITSHOP_funcs.updateFade(&buy->panels[2]) != 0) {
            win->total->setVisible(win->total, 1);
            buy->substate++;
        }
        break;
    case 47:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x4001C);
            win->total->setVisible(win->total, 0);
            STITSHOP_funcs.startFade(&buy->panels[2], 0);
            buy->substate++;
        }
        break;
    case 48:
        if (STITSHOP_funcs.updateFade(&buy->panels[2]) != 0) {
            win->list->freezeCursor(win->list, 0);
            buy->substate = 3;
        }
        break;
    case 50:
        if (win->info == NULL) {
            buy->state = TASK_KILL;
        }
        break;
    }
}

void STITSHOP_updateBuy(ShopBuy *buy, ShopBuyWindows *win) {
    switch (buy->state) {
    case TASK_INIT:
    default:
        buy->nextState(buy);
        func_80082DA4(buy, win);
        buy->panels[0].duration = 10;
        buy->panels[1].duration = 10;
        buy->panels[2].duration = 10;
        buy->panels[3].duration = 10;
        buy->quantity = 1;
        break;
    case TASK_RUN:
        func_8008361C(buy, win);
        func_800830DC(buy, win);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_80085070(ShopBuy *buy, s32 item, s32 arg) {
    ShopBuyWindows *win = buy->children;

    win->info->showItem(win->info, item, arg);
}

ShopBuy *STITSHOP_createBuy(ItemShop *shop) {
    ShopBuy *buy = createTask(STITSHOP_updateBuy, sizeof(ShopBuy), sizeof(ShopBuyWindows));

    buy->showItem = func_80085070;
    buy->layer = 0x1000;
    buy->depth = 4;
    buy->shop = shop;
    return buy;
}

void func_800850FC(ShopSell *sell, ShopSellWindows *win) {
    s32 i;

    win->cursor = createCursor(sell->layer, sell->depth - 1, 0, 0xB0);
    win->cursor->setVisible(win->cursor, 0);
    for (i = 0; i < 4; i++) {
        win->types[i] = createTextWindow(sell->layer, 1, 0xBE, i * 0xE + 0x2F);
    }
    win->quantityLabel = createTextWindow(sell->layer, 1, 0xB9, 0x3A);
    win->times = createTextWindow(sell->layer, 1, 0x103, 0x54);
    win->quantity = createTextWindow(sell->layer, 1, 0x11E, 0x54);
    win->unk28 = createTextWindow(sell->layer, 1, 0x9A, 0x2C);
    win->total = createTextWindow(sell->layer, 1, 0xC5, 0x49);
    win->unk30 = createTextWindow(sell->layer, 1, 0xC5, 0x59);
    win->unk34 = createTextWindow(sell->layer, 1, 0x9A, 0x8A);
}

/* Draws the selling screen's frames, and the quantity's blinking arrows */
void func_80085254(ShopSell *sell, ShopSellWindows *win) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    if (sell->panels[3].level != 0) {
        sprite.setLayerId(sell->layer, 1);
        if (sell->panels[3].level != 0x1000) {
            sprite.setScale(sell->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x41);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xD, 0xA0, 0x24);
    }
    sprite.setLayerId(sell->layer, sell->depth);
    if (sell->panels[0].level != 0) {
        if (sell->panels[0].level != 0x1000) {
            sprite.setScale(sell->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x4F);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 4, 0xA9, 0x26);
    }
    if (sell->panels[1].level != 0) {
        if (sell->panels[1].level != 0x1000) {
            sprite.setScale(sell->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x42);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xA, 0x9A, 0x34);
        if (sell->panels[1].level != 0x1000) {
            sprite.setPivot(0x140, 0x59);
        } else {
            if (GFX.funcs.getTime() - sell->blinkTime >= 9) {
                sell->blinkTime = GFX.funcs.getTime();
                sell->blink = 1 - sell->blink;
            }
            if (sell->blink) {
                if (sell->quantity < sell->max) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x12, 0x122, 0x51);
                }
                if (sell->quantity >= 2) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x13, 0x122, 0x5B);
                }
            }
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xB, 0xF6, 0x4F);
    }
    if (sell->panels[2].level != 0) {
        if (sell->panels[2].level != 0x1000) {
            sprite.setScale(sell->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x32);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x15, 0x7B, 0x26);
        if (sell->panels[2].level != 0x1000) {
            sprite.setPivot(0x140, 0x57);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xC, 0xAF, 0x43);
    }
    if (sell->panels[4].level != 0) {
        if (sell->panels[4].level != 0x1000) {
            sprite.setScale(sell->panels[4].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x8F);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x15, 0x7B, 0x84);
    }
}

/* The selling dialog: pick the kind of item, then the item in the list, how
   many, and confirm */
void func_80085684(ShopSell *sell, ShopSellWindows *win) {
    s32 i;
    s32 old;
    s32 j;

    switch (sell->substate) {
    case 0:
    default:
        STITSHOP_funcs.startFade(&sell->panels[0], 1);
        sell->substate++;
        break;
    case 1:
        if (STITSHOP_funcs.updateFade(&sell->panels[0]) != 0) {
            for (i = 0; i < 4; i++) {
                win->types[i]->setString(win->types[i], FILE_CACHE.load(TEXT_FILE(0x72)), i + 0x1D);
            }
            win->cursor->setPos(win->cursor, 0xB0, sell->type * 0xE + 0x2F);
            win->cursor->setVisible(win->cursor, 1);
            sell->substate++;
        }
        break;
    case 2:
        old = sell->type;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            if (--sell->type < 0) {
                sell->type = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (++sell->type >= 4) {
                sell->type = 3;
            }
        }
        if (old != sell->type) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0xB0, sell->type * 0xE + 0x2F);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            win->cursor->setVisible(win->cursor, 0);
            if (win->list != NULL) {
                win->list->state = TASK_KILL;
            }
            sell->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            sell->setSubstate(sell, 50);
        }
        break;
    case 3:
        if (win->list == NULL) {
            win->list = STITSHOP_createItemList((Task *)sell, D_8008C0D4[sell->type], 1);
            sell->substate++;
        } else {
            win->list->state = TASK_KILL;
        }
        break;
    case 4:
        if (win->list->substate == 100) {
            if (win->list->count > 0) {
                sell->setSubstate(sell, 50);
                sell->step = 1;
            } else {
                sell->substate = 200;
            }
        }
        break;
    case 100:
        win->list->substate = 1;
        sell->substate = 101;
        break;
    case 101:
        if (win->list->state == TASK_DONE) {
            if (win->info == NULL) {
                win->info = STITSHOP_createInfo(1, win->list->getSelected(win->list));
            }
            sell->substate = 5;
        }
        break;
    case 5:
        if (win->info->substate == 3) {
            win->list->showCursor(win->list, 1);
            sell->substate++;
        }
        break;
    case 6:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            sell->substate = 20;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            win->list->close(win->list);
            win->info->close(win->info);
            sell->substate = 40;
        }
        break;
    case 20:
        win->list->close(win->list);
        sell->substate++;
        break;
    case 21:
        if (win->list->state == TASK_DONE) {
            STITSHOP_funcs.startFade(&sell->panels[1], 1);
            sell->substate++;
        }
        break;
    case 22:
        if (STITSHOP_funcs.updateFade(&sell->panels[1]) != 0) {
            win->quantityLabel->setString(win->quantityLabel, FILE_CACHE.load(TEXT_FILE(0x72)), 0x21);
            win->times->setString(win->times, FILE_CACHE.load(TEXT_FILE(0x72)), 8);
            win->quantity->setNumber(win->quantity, 0, sell->quantity);
            win->quantity->setRightAlign(win->quantity, 1);
            sell->unk64 = win->list->getSelected(win->list);
            sell->max = GAME.items[sell->unk64];
            sell->substate++;
        }
        break;
    case 23:
        old = sell->quantity;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            sell->quantity++;
            if (sell->quantity > sell->max) {
                sell->quantity = sell->max;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (--sell->quantity <= 0) {
                sell->quantity = 1;
            }
        } else if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            sell->quantity -= 10;
            if (sell->quantity < 10) {
                sell->quantity = 1;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            sell->quantity += 10;
            if (sell->quantity > sell->max) {
                sell->quantity = sell->max;
            }
        }
        if (old != sell->quantity) {
            GET_ITEM[0](sell->unk64); /* its result is unused */
            win->quantity->setNumber(win->quantity, 0, sell->quantity);
            win->quantity->setRightAlign(win->quantity, 1);
            win->info->showItem(win->info, sell->unk64, sell->quantity);
            SOUND.playSound(0x4001B);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            sell->step = 0;
            sell->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            sell->quantity = 1;
            win->info->showItem(win->info, sell->unk64, 1);
            sell->step = 1;
            sell->substate++;
        }
        break;
    case 24:
        STITSHOP_funcs.startFade(&sell->panels[1], 0);
        win->quantityLabel->setVisible(win->quantityLabel, 0);
        win->times->setVisible(win->times, 0);
        win->quantity->setVisible(win->quantity, 0);
        if (sell->step != 0) {
            win->list->start(win->list);
            sell->substate++;
        } else {
            sell->setSubstate(sell, 30);
        }
        break;
    case 25:
        if (win->list->substate == 100) {
            win->list->substate = 1;
        }
        if (STITSHOP_funcs.updateFade(&sell->panels[1]) != 0) {
            sell->substate++;
        }
        break;
    case 26:
        if (win->list->state == TASK_DONE) {
            win->list->showCursor(win->list, 1);
            sell->substate = 6;
        }
        break;
    case 30:
        if (STITSHOP_funcs.updateFade(&sell->panels[1]) != 0) {
            STITSHOP_funcs.startFade(&sell->panels[2], 1);
            sell->substate++;
        }
        break;
    case 31:
        if (STITSHOP_funcs.updateFade(&sell->panels[2]) != 0) {
            win->unk28->setString(win->unk28, FILE_CACHE.load(TEXT_FILE(0x72)), 0x12);
            win->unk28->setNumber(win->unk28, 1, GET_ITEM[0](sell->unk64)->sellPrice * sell->quantity);
            win->total->setString(win->total, FILE_CACHE.load(TEXT_FILE(0x72)), 0x22);
            win->unk30->setString(win->unk30, FILE_CACHE.load(TEXT_FILE(0x72)), 0x14);
            sell->unk78 = 0;
            win->cursor->setPos(win->cursor, 0xB8, 0x49);
            win->cursor->setVisible(win->cursor, 1);
            sell->substate++;
        }
        break;
    case 32:
        old = sell->unk78;
        if (PAD_PRESSED(PAD_UP)) {
            sell->unk78 = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            sell->unk78 = 1;
        }
        if (old != sell->unk78) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0xB8, sell->unk78 * 0x10 + 0x49);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (sell->unk78 == 0) {
                GAME.money += GET_ITEM[0](sell->unk64)->sellPrice * sell->quantity;
                if (GAME.money > 9999999) {
                    GAME.money = 9999999;
                }
                GAME.items[sell->unk64] -= sell->quantity;
                if (GAME.items[sell->unk64] < 0) {
                    GAME.items[sell->unk64] = 0;
                }
                sell->shop->showMoney(sell->shop);
            }
            win->list->listBag(win->list);
            sell->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            sell->substate++;
        }
        break;
    case 33:
        STITSHOP_funcs.startFade(&sell->panels[2], 0);
        win->unk28->setVisible(win->unk28, 0);
        win->total->setVisible(win->total, 0);
        win->unk30->setVisible(win->unk30, 0);
        win->cursor->setVisible(win->cursor, 0);
        if (win->list->count <= 0 && GAME.items[sell->unk64] == 0) {
            sell->quantity = 1;
            win->list->state = TASK_KILL;
            win->info->close(win->info);
            sell->substate = 39;
        } else {
            win->list->start(win->list);
            sell->substate++;
        }
        break;
    case 34:
        if (win->list == NULL) {
            win->list = STITSHOP_createItemList((Task *)sell, D_8008C0D4[sell->type], 1);
        } else if (win->list->substate == 100) {
            win->list->substate = 1;
            if (win->list->selection > win->list->count - 1) {
                win->list->selection--;
            }
            if (win->list->page > win->list->pages - 1) {
                win->list->page--;
            }
            sell->unk64 = win->list->getSelected(win->list);
            sell->quantity = 1;
            win->info->showItem(win->info, sell->unk64, 1);
        }
        if (STITSHOP_funcs.updateFade(&sell->panels[2]) != 0) {
            sell->substate = 26;
        }
        break;
    case 39:
        if (STITSHOP_funcs.updateFade(&sell->panels[2]) != 0) {
            sell->substate = 40;
        }
        break;
    case 40:
        if (win->info == NULL) {
            sell->substate++;
        }
        break;
    case 41:
        sell->substate = 0;
        break;
    case 200:
        STITSHOP_funcs.startFade(&sell->panels[4], 1);
        sell->substate++;
        break;
    case 201:
        if (STITSHOP_funcs.updateFade(&sell->panels[4]) != 0) {
            win->unk34->setString(win->unk34, FILE_CACHE.load(TEXT_FILE(0x72)), 1);
            win->unk34->setSubString(win->unk34, FILE_CACHE.load(TEXT_FILE(0x72)), sell->type + 0x1D, 1);
            sell->substate++;
        }
        break;
    case 202:
        if (PAD_PRESSED(PAD_CROSS) || PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x4001C);
            win->unk34->setVisible(win->unk34, 0);
            STITSHOP_funcs.startFade(&sell->panels[4], 0);
            sell->substate++;
        }
        break;
    case 203:
        if (STITSHOP_funcs.updateFade(&sell->panels[4]) != 0) {
            win->cursor->setVisible(win->cursor, 1);
            sell->substate = 2;
        }
        break;
    case 50:
        win->cursor->setVisible(win->cursor, 0);
        for (j = 0; j < 4; j++) {
            win->types[j]->setVisible(win->types[j], 0);
        }
        STITSHOP_funcs.startFade(&sell->panels[0], 0);
        sell->substate++;
        break;
    case 51:
        if (STITSHOP_funcs.updateFade(&sell->panels[0]) != 0) {
            if (sell->step != 0) {
                sell->setSubstate(sell, 100);
            } else {
                sell->state = TASK_KILL;
            }
        }
        break;
    }
}

void STITSHOP_updateSell(ShopSell *sell, ShopSellWindows *win) {
    switch (sell->state) {
    case TASK_INIT:
    default:
        sell->nextState(sell);
        func_800850FC(sell, win);
        sell->panels[0].duration = 10;
        sell->panels[1].duration = 10;
        sell->panels[2].duration = 10;
        sell->panels[3].duration = 10;
        sell->panels[4].duration = 10;
        sell->quantity = 1;
        break;
    case TASK_RUN:
        func_80085684(sell, win);
        func_80085254(sell, win);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_80086AA0(ShopSell *sell, s32 item, s32 arg) {
    ShopSellWindows *win = sell->children;

    win->info->showItem(win->info, item, arg);
}

ShopSell *STITSHOP_createSell(ItemShop *shop) {
    ShopSell *sell = createTask(STITSHOP_updateSell, sizeof(ShopSell), sizeof(ShopSellWindows));

    sell->showItem = func_80086AA0;
    sell->layer = 0x1000;
    sell->depth = 4;
    sell->shop = shop;
    return sell;
}

void func_80086B2C(ShopItemList *list, ShopItemListWindows *win) {
    s32 i;
    s32 y = list->selling * 0x28;

    for (i = 0; i < 14; i++) {
        win->items[i] = createTextWindow(list->layer, 1, (i % 2) * 0x83 + 0x37, (i / 2) * 0xE + 0x24);
        win->items[i]->setDepth(win->items[i], list->depth - 1);
    }
    win->unk38 = createTextWindow(list->layer, 1, 0x9B, y + 0x60);
    win->unk3C = createTextWindow(list->layer, 1, 0x9C, y + 0x60);
    win->unk40 = createTextWindow(list->layer, 1, 0xB0, y + 0x60);
    win->unk44 = createTextWindow(list->layer, 1, 0x2D, y + 0x5C + list->selling * 2);
    win->unk48 = createTextWindow(list->layer, 1, 0x102, y + 0x5C + list->selling * 2);
    win->cursor = createCursor(list->layer, list->depth - 1, 0x1D, 0x24);
    win->cursor->setVisible(win->cursor, 0);
}

/* Shows the page of items, the page number and the arrows' labels; or hides
   them */
void func_80086CE4(ShopItemList *list, ShopItemListWindows *win, s32 show) {
    s32 index;
    s32 item;
    s32 i;

    if (show) {
        for (i = 0; i < list->pageSize; i++) {
            index = list->page * list->pageSize + i;
            if (list->selling == 0) {
                item = list->shopItems[index];
            } else {
                item = list->items[index];
            }
            if (index < list->count && item != 0) {
                win->items[i]->setString(win->items[i], FILE_CACHE.load(TEXT_FILE(0x6B)), item);
            } else {
                win->items[i]->setVisible(win->items[i], 0);
            }
        }
        win->unk38->setNumber(win->unk38, 0, list->page + 1);
        win->unk38->setRightAlign(win->unk38, 1);
        win->unk3C->setString(win->unk3C, FILE_CACHE.load(TEXT_FILE(0x72)), 0x18);
        win->unk40->setNumber(win->unk40, 0, list->pages);
        win->unk40->setRightAlign(win->unk40, 1);
        if (list->pages >= 2) {
            if (list->page != 0) {
                win->unk44->setString(win->unk44, FILE_CACHE.load(TEXT_FILE(0x72)), 0x19);
            } else {
                win->unk44->setVisible(win->unk44, 0);
            }
            if (list->page < list->pages - 1) {
                win->unk48->setString(win->unk48, FILE_CACHE.load(TEXT_FILE(0x72)), 0x1A);
                return;
            }
            win->unk48->setVisible(win->unk48, 0);
        }
    } else {
        for (i = 0; i < list->pageSize; i++) {
            win->items[i]->setVisible(win->items[i], 0);
        }
        win->unk38->setVisible(win->unk38, 0);
        win->unk3C->setVisible(win->unk3C, 0);
        win->unk40->setVisible(win->unk40, 0);
        win->unk44->setVisible(win->unk44, 0);
        win->unk48->setVisible(win->unk48, 0);
    }
}

/* Draws the list's frame, the items' icons and the blinking page arrows */
void func_8008700C(ShopItemList *list) {
    SpriteDrawer sprite;
    s32 index;
    s32 item;
    s32 x;
    s32 y;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(list->layer, list->depth);
    sprite.setTexture(0x280, 0x100);
    if (list->panel.level != 0) {
        if (list->panel.level != 0x1000) {
            sprite.setScale(0x1000, list->panel.level, 0x1000);
            sprite.setPivot(0xA0, 0x47);
        } else {
            for (i = 0; i < list->pageSize; i++) {
                index = list->page * list->pageSize + i;
                if (list->selling == 0) {
                    item = list->shopItems[index];
                } else {
                    item = list->items[index];
                }
                if (index >= list->count || item == 0) {
                    break;
                }
                x = (i % 2) * 0x83 + 0x28;
                y = (i % list->pageSize) / 2 * 0xE + 0x24;
                sprite.setTexture(0x140, 0);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(item), x, y);
                sprite.setTexture(0x280, 0x100);
                sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x31, x, y);
            }
            if (list->pages >= 2) {
                if (GFX.funcs.getTime() - list->blinkTime >= 11) {
                    list->blinkTime = GFX.funcs.getTime();
                    if (++list->clutRow >= 4) {
                        list->clutRow = 0;
                    }
                }
                sprite.setTexture(0x280, 0x100);
                sprite.setClutRow(list->clutRow);
                if (list->page != 0) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x10, 0x1E, list->selling * 0x2A + 0x5F);
                }
                if (list->page < list->pages - 1) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x11, 0xFD, list->selling * 0x2A + 0x5F);
                }
                sprite.setClutRow(0);
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), list->selling + 6, 0, 0x1D);
    }
}

/* The list's states: lists the shop's items or the bag's, fades in, then
   fades out when closed */
void func_800873E8(ShopItemList *list, ShopItemListWindows *win) {
    switch (list->substate) {
    case 0:
    default:
        if (list->selling == 0) {
            list->shopItems = STITSHOP_funcs.getShopItems(list->type);
            list->count = STITSHOP_funcs.count;
            list->pageSize = 8;
            list->substate++;
        } else {
            STITSHOP_listSellable(list);
            list->pageSize = 14;
            list->substate = 100;
        }
        list->pages = list->count / list->pageSize + (list->count % list->pageSize != 0);
        break;
    case 1:
        STITSHOP_funcs.startFade(&list->panel, 1);
        list->substate++;
        break;
    case 2:
        if (STITSHOP_funcs.updateFade(&list->panel)) {
            func_80086CE4(list, win, 1);
            list->setState(list, TASK_DONE);
        }
        break;
    case 50:
        STITSHOP_funcs.startFade(&list->panel, 0);
        func_80086CE4(list, win, 0);
        list->substate++;
        break;
    case 51:
        if (STITSHOP_funcs.updateFade(&list->panel)) {
            list->setState(list, TASK_DONE);
        }
        break;
    case 100:
        break;
    }
}

/* The item list: L1 and R1 turn its pages, the d-pad moves in the page, and
   the dialog shows the selected item */
void func_800875AC(ShopItemList *list, ShopItemListWindows *win) {
    s32 page;
    s32 first;
    s32 last;
    s32 old;
    s32 item;

    switch (list->state) {
    case TASK_INIT:
    default:
        list->nextState(list);
        func_80086B2C(list, win);
        list->panel.duration = 10;
        break;
    case TASK_RUN:
        func_800873E8(list, win);
        func_8008700C(list);
        break;
    case TASK_DONE:
        if (list->active) {
            page = list->page;
            if ((!PAD_HELD(PAD_R1) && PAD_PRESSED(PAD_L1)) || (!PAD_HELD(PAD_R1) && PAD_REPEATED(PAD_L1))) {
                if (--list->page < 0) {
                    list->page = 0;
                }
            } else if ((!PAD_HELD(PAD_L1) && PAD_PRESSED(PAD_R1)) || (!PAD_HELD(PAD_L1) && PAD_REPEATED(PAD_R1))) {
                if (++list->page > list->pages - 1) {
                    list->page = list->pages - 1;
                }
            }
            if (page != list->page) {
                SOUND.playSound(0x8004513E);
                list->selection = list->page * list->pageSize;
                if (list->selling == 0) {
                    item = list->shopItems[list->selection];
                } else {
                    item = list->items[list->selection];
                }
                ((ShopBuy *)list->dialog)->showItem((ShopBuy *)list->dialog, item, 1);
                func_80086CE4(list, win, 1);
                win->cursor->setPos(win->cursor, (list->selection % 2) * 0x83 + 0x1D,
                                    (list->selection % list->pageSize) / 2 * 0xE + 0x24);
            } else {
                first = page * list->pageSize;
                old = list->selection;
                last = (page + 1) * list->pageSize - 1;
                if (last > list->count - 1) {
                    last = list->count - 1;
                }
                if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                    list->selection -= 2;
                    if (list->selection < first) {
                        list->selection = first;
                    }
                } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                    list->selection += 2;
                    if (list->selection > last) {
                        list->selection = last;
                    }
                }
                if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
                    if (!PAD_HELD(PAD_DOWN)) {
                        if (--list->selection < first) {
                            list->selection = first;
                        }
                    }
                } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
                    if (!PAD_HELD(PAD_UP)) {
                        if (++list->selection > last) {
                            list->selection = last;
                        }
                    }
                }
                if (old != list->selection) {
                    if (list->selling == 0) {
                        item = list->shopItems[list->selection];
                    } else {
                        item = list->items[list->selection];
                    }
                    ((ShopBuy *)list->dialog)->showItem((ShopBuy *)list->dialog, item, 1);
                        win->cursor->setPos(win->cursor, (list->selection % 2) * 0x83 + 0x1D,
                                    (list->selection % list->pageSize) / 2 * 0xE + 0x24);
                    SOUND.playSound(0x8004513E);
                }
            }
        }
        func_8008700C(list);
        break;
    case TASK_KILL:
        break;
    }
}

void func_80087D5C(ShopItemList *list, s32 frozen) {
    ShopItemListWindows *win = list->children;

    if (frozen) {
        win->cursor->setPalette(win->cursor, 7);
        win->cursor->setStill(win->cursor, 1);
        list->active = 0;
    } else {
        win->cursor->setPalette(win->cursor, 0);
        win->cursor->setStill(win->cursor, 0);
        list->active = 1;
    }
}

void func_80087E00(ShopItemList *list, s32 visible) {
    ShopItemListWindows *win = list->children;
    s32 row;

    list->active = visible;
    row = (list->selection % list->pageSize) / 2;
    win->cursor->setPos(win->cursor, (list->selection % 2) * 0x83 + 0x1D, row * 0xE + 0x24);
    win->cursor->setVisible(win->cursor, visible);
}

void func_80087EB0(ShopItemList *list) {
    list->setState(list, TASK_RUN);
}

void func_80087ED8(ShopItemList *list) {
    list->setState(list, TASK_RUN);
    list->substate = 0x32;
    func_80087E00(list, 0);
}

s32 STITSHOP_getSelectedItem(ShopItemList *list) {
    if (!list->selling) {
        return list->shopItems[list->selection];
    }
    return list->items[list->selection];
}

void func_80087F64(ShopItemList *list) {
    void *win = list->children;

    STITSHOP_listSellable(list);
    func_80086CE4(list, win, 1);
    ((ShopBuy *)list->dialog)->showItem((ShopBuy *)list->dialog, list->items[list->selection], 1);
}

void STITSHOP_listSellable(ShopItemList *list) {
    s32 i;
    s32 n;

    list->count = 0;
    n = ITEM_FUNCS->list(list->type, list->bag);
    for (i = 0; i < n; i++) {
        if (ITEM_FUNCS->get(list->bag[i])->sellPrice != 0) {
            list->items[list->count++] = list->bag[i];
        }
    }
}

ShopItemList *STITSHOP_createItemList(Task *dialog, s32 type, s32 selling) {
    ShopItemList *list = createTask(func_800875AC, sizeof(ShopItemList), 0x50);

    list->start = func_80087EB0;
    list->close = func_80087ED8;
    list->getSelected = STITSHOP_getSelectedItem;
    list->showCursor = func_80087E00;
    list->freezeCursor = func_80087D5C;
    list->refresh = func_80087F64;
    list->listBag = STITSHOP_listSellable;
    list->layer = 0x1000;
    list->depth = 4;
    list->dialog = dialog;
    list->selling = selling;
    list->type = type;
    return list;
}

void func_80088150(s32 partner, s16 *out) {
    s16 *equip;
    s32 i;
    s32 j;
    ItemInfo *info;
    ShopItemData *data;
    u8 type;
    u8 stat;
    s32 amount;

    GameState *save = &GAME;
    PartnerStats *d;

    *(ShopStatBlock *)out = *(ShopStatBlock *)&save->partners[partner].level;
    d = &PARTNER_STATS[partner];
    equip = d->equip;
    for (i = 0; i < 6; i++) {
        if (equip[i] > 0) {
            info = GET_ITEM[0](equip[i]);
            type = info->type;
            data = (ShopItemData *)info->data;
            if ((u8)(type - 2) < 13) {
                out[6] += data->weapon.atk;
                if (out[6] >= 1000) {
                    out[6] = 999;
                }
                for (j = 0; j < 2; j++) {
                    stat = *(j + data->weapon.stats);
                    amount = data->weapon.amounts[j];
                    if (stat != 0) {
                        func_800884A4(out, stat, (s16)amount);
                    }
                }
            } else if ((u8)(type - 15) < 6) {
                out[7] += data->armor.def;
                if (out[7] >= 1000) {
                    out[7] = 999;
                }
                for (j = 0; j < 2; j++) {
                    stat = *(j + data->armor.stats);
                    amount = data->armor.amounts[j];
                    if (stat != 0) {
                        func_800884A4(out, stat, (s16)amount);
                    }
                }
            } else if ((u8)(type - 21) < 4) {
                stat = data->acc.stat;
                amount = data->acc.amount;
                if (stat != 0) {
                    func_800884A4(out, stat, (s16)amount);
                }
            } else {
                continue;
            }
            out[11] += data->weapon.unk0;
            if (out[11] >= 1000) {
                out[11] = 999;
            }
        }
    }
    out[6] -= out[19];
    if (out[6] < 0) {
        out[6] = 0;
    }
    out[7] -= out[20];
    if (out[7] < 0) {
        out[7] = 0;
    }
    out[10] -= out[21];
    if (out[10] < 0) {
        out[10] = 0;
    }
}

void func_800884A4(s16 *p, s32 stat, s32 delta) {
    s32 i;
    s16 value;

    if (stat == 7) {
        for (i = 0; i < 6; i++) {
            value = p[i + 6] + delta;
            p[i + 6] = value;
            if (value >= 1000) {
                p[i + 6] = 999;
            }
        }
    } else if (stat - 1 < 6U) {
        value = p[stat + 5] + delta;
        p[stat + 5] = value;
        if (value >= 1000) {
            p[stat + 5] = 999;
        }
    } else if (stat - 8 < 7U) {
        value = p[stat + 4] + delta;
        p[stat + 4] = value;
        if (value >= 1000) {
            p[stat + 4] = 999;
        }
    }
}

void func_80088578(ShopInfo *info, TextWindow *win, ShopStatRow *row) {
    ShopPartnerInfo *p = &info->partners[row->partner];
    s16 value;

    if (row->compare == 0) {
        value = *(D_8008C114[row->stat] + p->stats);
    } else {
        value = *(D_8008C114[row->stat] + p->newStats);
    }
    win->setNumber(win, 0, value);
    win->setRightAlign(win, 1);
}

void func_80088638(ShopInfo *info, TextWindow *win, ShopStatRow *row) {
    ShopPartnerInfo *p = &info->partners[row->partner];
    s32 penalty;
    s16 v[2];

    if (row->stat == 0) {
        penalty = 0;
    } else if (row->stat == 1) {
        penalty = 1;
    } else if (row->stat == 4) {
        penalty = 2;
    } else {
        penalty = -1;
    }
    v[0] = *(D_8008C114[row->stat] + p->stats);
    if (row->compare == 0) {
        if (penalty >= 0 && p->penalties[penalty] != 0) {
            win->setPalette(win, 6);
        } else {
            win->setPalette(win, 0);
        }
    } else {
        v[1] = *(D_8008C114[row->stat] + p->newStats);
        if (v[0] == v[1]) {
            if (penalty >= 0 && p->penalties[penalty] != 0) {
                win->setPalette(win, 6);
            } else {
                win->setPalette(win, 0);
            }
        } else if (v[0] < v[1]) {
            win->setPalette(win, 1);
        } else {
            win->setPalette(win, 5);
        }
    }
}

void func_8008879C(ShopInfo *info, TextWindow **win, ShopStatRow *row) {
    ShopPartnerInfo *p = &info->partners[row->partner];
    s32 i;
    s32 n = 0;
    s16 v[2];

    for (i = 0; i < 13; i++) {
        if (i != row->skip && (row->skip2 < 0 || i != row->skip2)) {
            v[0] = *(D_8008C114[i] + p->stats);
            v[1] = *(D_8008C114[i] + p->newStats);
            if (v[0] != v[1]) {
                p->rows[n + 2] = i + 1;
                win[n]->setNumber(win[n], 0, v[1]);
                win[n]->setRightAlign(win[n], 1);
                if (v[0] < v[1]) {
                    win[n]->setPalette(win[n], 1);
                } else {
                    win[n]->setPalette(win[n], 5);
                }
                n++;
            }
        }
    }
    p->changes += n;
    for (i = n; i < 4; i++) {
        win[i]->setVisible(win[i], 0);
    }
}

/* Fills a partner's rows of the details panel's second page: the stats of
   the slot the item goes in, then the others it would change. The item is
   equipped to compute them and the partner's equipment put back */
void func_80088960(ShopInfo *info, ShopInfoWindows *win, s32 show) {
    ShopEquipSet equip;
    ShopStatRow row;
    s32 partner = GAME.funcs.getPartyMember(show);
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(partner);
    ShopPartnerInfo *p = &info->partners[show];
    ShopItemData *data;

    equip = *(ShopEquipSet *)stats->equip;
    func_80088150(partner, p->stats);
    p->unk58 = STITSHOP_funcs.compareEquip(partner, info->item);
    STITSHOP_funcs.equip(partner, p->unk58, info->item, 0);
    func_80088150(partner, p->newStats);
    *(ShopEquipSet *)stats->equip = equip;
    p->changes = 2;
    switch (p->unk58) {
    case 0:
    case 2:
    case 3:
    default:
        if (GET_ITEM[0](info->item)->type - 2U < 13) {
            p->rows[0] = 1;
            row.partner = show;
            row.stat = 0;
            row.compare = 0;
            func_80088578(info, win->partners[show].changes[0], &row);
            func_80088638(info, win->partners[show].changes[0], &row);
            row.compare = 1;
            func_80088578(info, win->partners[show].changes[2], &row);
            func_80088638(info, win->partners[show].changes[2], &row);
            p->rows[1] = 6;
            row.partner = show;
            row.stat = 5;
            row.compare = 0;
            func_80088578(info, win->partners[show].changes[1], &row);
            func_80088638(info, win->partners[show].changes[1], &row);
            row.compare = 1;
            func_80088578(info, win->partners[show].changes[3], &row);
            func_80088638(info, win->partners[show].changes[3], &row);
            row.skip = 0;
            row.skip2 = 5;
            func_8008879C(info, &win->partners[show].changes[4], &row);
        } else {
            p->rows[0] = 2;
            row.partner = show;
            row.stat = 1;
            row.compare = 0;
            func_80088578(info, win->partners[show].changes[0], &row);
            func_80088638(info, win->partners[show].changes[0], &row);
            row.compare = 1;
            func_80088578(info, win->partners[show].changes[2], &row);
            func_80088638(info, win->partners[show].changes[2], &row);
            p->rows[1] = 6;
            row.partner = show;
            row.stat = 5;
            row.compare = 0;
            func_80088578(info, win->partners[show].changes[1], &row);
            func_80088638(info, win->partners[show].changes[1], &row);
            row.compare = 1;
            func_80088578(info, win->partners[show].changes[3], &row);
            func_80088638(info, win->partners[show].changes[3], &row);
            row.skip = 1;
            row.skip2 = 5;
            func_8008879C(info, &win->partners[show].changes[4], &row);
        }
        win->partners[show].stats[0]->setString(win->partners[show].stats[0], FILE_CACHE.load(TEXT_FILE(0x72)), 0xC);
        win->partners[show].stats[1]->setString(win->partners[show].stats[1], FILE_CACHE.load(TEXT_FILE(0x72)), 0xC);
        break;
    case 1:
        p->rows[0] = 2;
        row.partner = show;
        row.stat = 1;
        row.compare = 0;
        func_80088578(info, win->partners[show].changes[0], &row);
        func_80088638(info, win->partners[show].changes[0], &row);
        row.compare = 1;
        func_80088578(info, win->partners[show].changes[2], &row);
        func_80088638(info, win->partners[show].changes[2], &row);
        p->rows[1] = 6;
        row.partner = show;
        row.stat = 5;
        row.compare = 0;
        func_80088578(info, win->partners[show].changes[1], &row);
        func_80088638(info, win->partners[show].changes[1], &row);
        row.compare = 1;
        func_80088578(info, win->partners[show].changes[3], &row);
        func_80088638(info, win->partners[show].changes[3], &row);
        row.skip = 1;
        row.skip2 = 5;
        func_8008879C(info, &win->partners[show].changes[4], &row);
        win->partners[show].stats[0]->setString(win->partners[show].stats[0], FILE_CACHE.load(TEXT_FILE(0x72)), 0xC);
        win->partners[show].stats[1]->setString(win->partners[show].stats[1], FILE_CACHE.load(TEXT_FILE(0x72)), 0xC);
        break;
    case 4:
    case 5:
        p->rows[0] = 6;
        row.partner = show;
        row.stat = 5;
        row.compare = 0;
        func_80088578(info, win->partners[show].changes[0], &row);
        func_80088638(info, win->partners[show].changes[0], &row);
        row.compare = 1;
        func_80088578(info, win->partners[show].changes[2], &row);
        func_80088638(info, win->partners[show].changes[2], &row);
        row.skip = 5;
        data = (ShopItemData *)GET_ITEM[0](info->item)->data;
        /* the row of the stat the accessory raises (7 raises them all and has
           none). The match depends on the range tests being written out: the
           inner one isn't merged with the outer one before cse */
        if ((data->acc.stat >= 1 && data->acc.stat <= 5) || (data->acc.stat >= 8 && data->acc.stat <= 14)) {
            if (data->acc.stat >= 1 && data->acc.stat <= 5) {
                p->rows[1] = data->acc.stat;
            } else {
                p->rows[1] = data->acc.stat - 1;
            }            row.partner = show;
            row.stat = p->rows[1] - 1;
            row.compare = 0;            func_80088578(info, win->partners[show].changes[1], &row);
            func_80088638(info, win->partners[show].changes[1], &row);
            row.compare = 1;
            func_80088578(info, win->partners[show].changes[3], &row);
            func_80088638(info, win->partners[show].changes[3], &row);
            win->partners[show].stats[0]->setString(win->partners[show].stats[0], FILE_CACHE.load(TEXT_FILE(0x72)), 0xC);
            win->partners[show].stats[1]->setString(win->partners[show].stats[1], FILE_CACHE.load(TEXT_FILE(0x72)), 0xC);
            row.skip2 = row.stat;
        } else {
            win->partners[show].changes[1]->setVisible(win->partners[show].changes[1], 0);
            win->partners[show].changes[3]->setVisible(win->partners[show].changes[3], 0);
            row.skip2 = -1;
            p->rows[1] = 0;
            win->partners[show].stats[0]->setString(win->partners[show].stats[0], FILE_CACHE_LOAD[0](TEXT_FILE(0x72)), 0xC);
            win->partners[show].stats[1]->setVisible(win->partners[show].stats[1], 0);
        }
        func_8008879C(info, &win->partners[show].changes[4], &row);
        break;
    }
}

/* The y of a line of the details panel, two lower when selling. The match
   depends on this being a function: its sum isn't folded into the offset */
static inline s32 STITSHOP_lineY(ShopInfo *info, s32 y) {
    return info->selling * 2 + y;
}

/* Creates the details panel's windows: the item's rows, then, when buying,
   each partner's name, stats and stat changes */
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089104);

/* Shows the item's name, how many are equipped and in the bag, and its
   price; or hides them */
void func_800894EC(ShopInfo *info, ShopInfoWindows *win, s32 show) {
    if (show) {
        win->name->setString(win->name, FILE_CACHE.load(TEXT_FILE(0x6B)), info->item);
        win->equippedLabel->setString(win->equippedLabel, FILE_CACHE.load(TEXT_FILE(0x72)), 6);
        win->equipped->setNumber(win->equipped, 0, GAME.equippedItems[info->item]);
        win->equipped->setRightAlign(win->equipped, 1);
        win->ownedLabel->setString(win->ownedLabel, FILE_CACHE.load(TEXT_FILE(0x72)), 7);
        win->owned->setNumber(win->owned, 0, GAME.items[info->item]);
        win->owned->setRightAlign(win->owned, 1);
        win->priceLabel->setString(win->priceLabel, FILE_CACHE.load(TEXT_FILE(0x72)), 2);
        if (info->selling == 0) {
            win->price->setNumber(win->price, 0, GET_ITEM[0](info->item)->price * info->unk1E8);
        } else {
            win->price->setNumber(win->price, 0, GET_ITEM[0](info->item)->sellPrice * info->unk1E8);
        }
        win->price->setRightAlign(win->price, 1);
    } else {
        win->name->setVisible(win->name, 0);
        win->equippedLabel->setVisible(win->equippedLabel, 0);
        win->equipped->setVisible(win->equipped, 0);
        win->ownedLabel->setVisible(win->ownedLabel, 0);
        win->owned->setVisible(win->owned, 0);
        win->priceLabel->setVisible(win->priceLabel, 0);
        win->price->setVisible(win->price, 0);
    }
}

/* Shows the item's description and, for a weapon, its kind; or hides them */
void func_80089774(ShopInfo *info, ShopInfoWindows *win, s32 show) {
    ItemInfo *item;
    u8 *data;

    if (show) {
        win->desc->setString(win->desc, FILE_CACHE.load(TEXT_FILE(0x64)), info->item);
        item = GET_ITEM[0](info->item);
        if (item->type >= 2 && item->type < 14) {
            data = item->data;
            win->kind->setString(win->kind, FILE_CACHE.load(TEXT_FILE(0x72)), D_8008C148[data[2]]);
            return;
        }
    } else {
        win->desc->setVisible(win->desc, 0);
    }
    win->kind->setVisible(win->kind, 0);
}

/* Shows the party's names and, for those who can equip the item, the stats
   it changes; or hides them */
void func_8008988C(ShopInfo *info, ShopInfoWindows *win, s32 show) {
    s32 partner;
    s32 i;
    s32 j;

    if (show) {
        for (i = 0; i < info->unk60; i++) {
            partner = GAME.funcs.getPartyMember(i);
            win->partners[i].name->setString(win->partners[i].name, GAME.funcs.getPartnerStats(partner), -1);
            if (STITSHOP_funcs.canEquip(partner, info->item)) {
                func_80088960(info, win, i);
                win->partners[i].name->setPalette(win->partners[i].name, 0);
            } else {
                win->partners[i].name->setPalette(win->partners[i].name, 7);
                for (j = 0; j < 2; j++) {
                    win->partners[i].stats[j]->setVisible(win->partners[i].stats[j], 0);
                }
                for (j = 0; j < 8; j++) {
                    win->partners[i].changes[j]->setVisible(win->partners[i].changes[j], 0);
                }
            }
        }
    } else {
        for (i = 0; i < info->unk60; i++) {
            win->partners[i].name->setVisible(win->partners[i].name, 0);
            for (j = 0; j < 2; j++) {
                win->partners[i].stats[j]->setVisible(win->partners[i].stats[j], 0);
            }
            for (j = 0; j < 8; j++) {
                win->partners[i].changes[j]->setVisible(win->partners[i].changes[j], 0);
            }
        }
    }
}

/* Draws the second page's frames: the panel, then for each partner its frame
   and either the icons of the stats the item changes or a cross */
void func_80089AE0(ShopInfo *info, ShopInfoWindows *win) {
    SpriteDrawer sprite;
    s32 i;
    s32 j;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(info->layer, info->depth);
    sprite.setTexture(0x280, 0x100);
    if (info->panels[1].level != 0) {
        if (info->panels[1].level != 0x1000) {
            sprite.setScale(info->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x8C);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 9, 0, 0x81);
    }
    if (info->panels[3].level != 0) {
        sprite.setScale(0x1000, info->panels[3].level, 0x1000);
        for (i = 0; i < info->unk60; i++) {
            if (info->panels[3].level != 0x1000) {
                sprite.setPivot(i * 0x64 + 0x3C, 0xC0);
            } else if (STITSHOP_funcs.canEquip(GAME_FUNCS.getPartyMember(i), info->item)) {
                sprite.setTexture(0x140, 0);
                for (j = 0; j < info->partners[i].changes; j++) {
                    if (info->partners[i].rows[j] > 0) {
                        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), info->partners[i].rows[j] + 0x24,
                                    STITSHOP_changePos[j].x + i * 0x63, STITSHOP_changePos[j].y);
                    }
                }
            } else {
                sprite.setTexture(0x280, 0x100);
                sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x16, i * 0x63 + 0x19, 0xAD);
            }
            sprite.setTexture(0x280, 0x100);
            sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 8, i * 0x63 + 0xB, 0x9C);
        }
    }
}

/* The details panel's states when buying: fades in its first page, turns
   between the pages (10-16), and fades out when closed (50) */
void func_80089DE8(ShopInfo *info, ShopInfoWindows *win) {
    switch (info->substate) {
    case 0:
    default:
        STITSHOP_funcs.startFade(&info->panels[0], 1);
        if (info->unk1EC) {
            STITSHOP_funcs.startFade(&info->panels[1], 1);
        }
        info->substate++;
        break;
    case 1:
        if (info->unk1EC) {
            STITSHOP_funcs.updateFade(&info->panels[1]);
        }
        if (STITSHOP_funcs.updateFade(&info->panels[0])) {
            func_800894EC(info, win, 1);
            if (info->unk1EC) {
                win->unkA8->setString(win->unkA8, FILE_CACHE.load(TEXT_FILE(0x72)), info->page + 10);
            }
            STITSHOP_funcs.startFade(&info->panels[2], 1);
            info->substate++;
        }
        break;
    case 2:
        if (STITSHOP_funcs.updateFade(&info->panels[2])) {
            func_80089774(info, win, 1);
            info->substate++;
        }
        break;
    case 3:
        break;
    case 4:
        info->shown = 0;
        win->unkA8->setVisible(win->unkA8, 0);
        STITSHOP_funcs.startFade(&info->panels[1], 0);
        if (info->page == 0) {
            STITSHOP_funcs.startFade(&info->panels[2], 0);
            func_80089774(info, win, 0);
        }
        info->substate++;
        break;
    case 5:
        STITSHOP_funcs.updateFade(&info->panels[2]);
        if (STITSHOP_funcs.updateFade(&info->panels[1])) {
            if (info->page == 0) {
                STITSHOP_funcs.startFade(&info->panels[3], 1);
            }
            info->substate++;
        }
        break;
    case 6:
        if (STITSHOP_funcs.updateFade(&info->panels[3])) {
            func_8008988C(info, win, 1);
            info->substate++;
        }
        break;
    case 7:
        break;
    case 8:
        if (info->page == 0) {
            func_8008988C(info, win, 0);
            STITSHOP_funcs.startFade(&info->panels[3], 0);
        }
        STITSHOP_funcs.startFade(&info->panels[1], 1);
        info->substate++;
        break;
    case 9:
        STITSHOP_funcs.updateFade(&info->panels[3]);
        if (STITSHOP_funcs.updateFade(&info->panels[1])) {
            win->unkA8->setVisible(win->unkA8, 1);
            if (info->page == 0) {
                STITSHOP_funcs.startFade(&info->panels[2], 1);
            }
            info->substate = 1000;
        }
        break;
    case 1000:
        if (STITSHOP_funcs.updateFade(&info->panels[2])) {
            if (info->page == 0) {
                func_80089774(info, win, 1);
            }
            info->substate = 3;
            info->shown = 1;
        }
        break;
    case 10:
        win->unkA8->setString(win->unkA8, FILE_CACHE.load(TEXT_FILE(0x72)), info->page + 10);
        if (info->page == 0) {
            STITSHOP_funcs.startFade(&info->panels[3], 0);
            func_8008988C(info, win, 0);
            info->substate = 15;
        } else {
            STITSHOP_funcs.startFade(&info->panels[2], 0);
            func_80089774(info, win, 0);
            info->substate = 11;
        }
        break;
    case 11:
        if (STITSHOP_funcs.updateFade(&info->panels[2])) {
            STITSHOP_funcs.startFade(&info->panels[3], 1);
            info->substate++;
        }
        break;
    case 12:
        if (STITSHOP_funcs.updateFade(&info->panels[3])) {
            func_8008988C(info, win, 1);
            info->substate = 3;
            info->shown = 1;
        }
        break;
    case 15:
        if (STITSHOP_funcs.updateFade(&info->panels[3])) {
            STITSHOP_funcs.startFade(&info->panels[2], 1);
            info->substate++;
        }
        break;
    case 16:
        if (STITSHOP_funcs.updateFade(&info->panels[2])) {
            func_80089774(info, win, 1);
            info->substate = 3;
            info->shown = 1;
        }
        break;
    case 50:
        func_800894EC(info, win, 0);
        win->unkA8->setVisible(win->unkA8, 0);
        STITSHOP_funcs.startFade(&info->panels[0], 0);
        if (info->unk1EC) {
            STITSHOP_funcs.startFade(&info->panels[1], 0);
        }
        if (info->page == 0) {
            func_80089774(info, win, 0);
            STITSHOP_funcs.startFade(&info->panels[2], 0);
        } else {
            func_8008988C(info, win, 0);
            STITSHOP_funcs.startFade(&info->panels[3], 0);
        }
        info->substate++;
        break;
    case 51:
        if (info->page == 0) {
            STITSHOP_funcs.updateFade(&info->panels[2]);
        } else {
            STITSHOP_funcs.updateFade(&info->panels[3]);
        }
        if (info->unk1EC) {
            STITSHOP_funcs.updateFade(&info->panels[1]);
        }
        if (STITSHOP_funcs.updateFade(&info->panels[0])) {
            info->state = TASK_KILL;
        }
        break;
    }
}

/* The details panel's first page: fades in, shows the item, then fades out
   when closed */
void func_8008A46C(ShopInfo *info, ShopInfoWindows *win) {
    switch (info->substate) {
    case 0:
    default:
        STITSHOP_funcs.startFade(&info->panels[0], 1);
        info->substate++;
        break;
    case 1:
        if (STITSHOP_funcs.updateFade(&info->panels[0])) {
            func_800894EC(info, win, 1);
            STITSHOP_funcs.startFade(&info->panels[2], 1);
            info->substate++;
        }
        break;
    case 2:
        if (STITSHOP_funcs.updateFade(&info->panels[2])) {
            func_80089774(info, win, 1);
            info->substate++;
        }
        break;
    case 3:
        break;
    case 50:
        func_800894EC(info, win, 0);
        func_80089774(info, win, 0);
        STITSHOP_funcs.startFade(&info->panels[0], 0);
        STITSHOP_funcs.startFade(&info->panels[2], 0);
        info->substate++;
        break;
    case 51:
        STITSHOP_funcs.updateFade(&info->panels[0]);
        if (STITSHOP_funcs.updateFade(&info->panels[2])) {
            info->state = TASK_KILL;
        }
        break;
    }
}

/* The details panel: counts the party, then runs the pages and draws the
   item's icon and frames */
void func_8008A5E8(ShopInfo *info, ShopInfoWindows *win) {
    SpriteDrawer sprite;
    s32 offset;
    s32 i;

    switch (info->state) {
    case TASK_INIT:
    default:
        info->nextState(info);
        for (i = 0; i < 3; i++) {
            if (GAME.funcs.getPartyMember(i) >= 0) {
                info->unk60++;
            }
        }
        func_80089104(info, win);
        info->panels[0].duration = 10;
        info->panels[1].duration = 10;
        info->panels[2].duration = 10;
        info->panels[3].duration = 10;
        if (info->selling == 0 &&
            (ITEM_FUNCS->isKind(info->item, 3) || ITEM_FUNCS->isKind(info->item, 4) ||
             ITEM_FUNCS->isKind(info->item, 5))) {
            info->unk1EC = 1;
        }
        break;
    case TASK_RUN:
        if (info->selling == 0) {
            func_80089DE8(info, win);
            func_80089AE0(info, win);
        } else {
            func_8008A46C(info, win);
        }
        offset = info->selling * 0x28;
        initSpriteDrawer(&sprite);
        sprite.setLayerId(info->layer, info->depth - 1);
        sprite.setTexture(0x280, 0x100);
        if (info->panels[0].level != 0) {
            if (info->panels[0].level != 0x1000) {
                sprite.setScale(info->panels[0].level, 0x1000, 0x1000);
                sprite.setPivot(0x140, offset + 0x81);
            } else {
                sprite.setTexture(0x140, 0);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(info->item), 0x16,
                            offset + STITSHOP_lineY(info, 0x73));
            }
            sprite.setTexture(0x280, 0x100);
            sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0xE, 0xF, offset + STITSHOP_lineY(info, 0x6C));
        }
        if (info->panels[2].level != 0) {
            if (info->panels[2].level != 0x1000) {
                sprite.setScale(0x1000, info->panels[2].level, 0x1000);
                sprite.setPivot(0xA0, offset + 0xAE);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 3, 0, offset + 0x9C);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_8008A91C(ShopInfo *info, s32 item, s32 arg) {
    void *win = info->children;

    info->item = item;
    info->unk1E8 = arg;
    if (info->shown != 0) {
        func_800894EC(info, win, 1);
        if (info->page == 0) {
            func_80089774(info, win, 1);
        } else {
            func_80089774(info, win, 0);
            func_8008988C(info, win, 1);
        }
    }
}

void func_8008A9A4(ShopInfo *info) {
    if (info->substate == 3) {
        info->substate = 0x32;
    }
}

void func_8008A9C0(ShopInfo *info, s32 visible) {
    TextWindow **win = info->children;

    win[8]->setVisible(win[8], visible);
}

void func_8008A9F8(ShopInfo *info) {
    if (ITEM_FUNCS->isKind(info->item, 3) != 0 || ITEM_FUNCS->isKind(info->item, 4) != 0 ||
        ITEM_FUNCS->isKind(info->item, 5) != 0) {
        SOUND.playSound(0x4001B);
        info->substate = 10;
        info->shown = 0;
        info->page = 1 - info->page;
    }
}

void func_8008AAB0(ShopInfo *info, s32 arg) {
    void *win = info->children;

    func_800894EC(info, win, 1);
    func_80088960(info, win, arg);
}

ShopInfo *STITSHOP_createInfo(s32 selling, s32 item) {
    ShopInfo *info = createTask(func_8008A5E8, sizeof(ShopInfo), 0xAC);

    info->showItem = func_8008A91C;
    info->close = func_8008A9A4;
    info->setArrowVisible = func_8008A9C0;
    info->turnPage = func_8008A9F8;
    info->func_8008AAB0 = func_8008AAB0;
    info->layer = 0x1000;
    info->depth = 6;
    info->selling = selling;
    info->item = item;
    info->unk1E8 = 1;
    info->shown = 1;
    return info;
}

void func_8008ABA4(ItemShop *shop, ItemShopWindows *win) {
    win->help = createTextWindow(shop->layer, 1, 0xD3, 0xCC);
    win->title = createTextWindow(shop->layer, 1, 0x1D, 0x14);
    win->money = createTextWindow(shop->layer, 3, 0x117, 0x17);
    win->moneyLabel = createTextWindow(shop->layer, 3, 0x11A, 0x17);
    win->buy = createTextWindow(shop->layer, 1, 0xBE, 0x2F);
    win->sell = createTextWindow(shop->layer, 1, 0xBE, 0x3D);
    win->cursor = createCursor(shop->layer, 0, 0xB0, 0x2F);
    win->cursor->setVisible(win->cursor, 0);
}

void func_8008AC8C(ItemShop *shop, ItemShopWindows *win) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(shop->layer, 1);
    sprite.setTexture(0x280, 0x100);
    if (shop->panels[0].level != 0) {
        if (shop->panels[0].level != 0x1000) {
            sprite.setScale(shop->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x57, 0x19);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 1, 0x16, 0x12);
    }
    if (shop->panels[1].level != 0) {
        if (shop->panels[1].level != 0x1000) {
            sprite.setScale(shop->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x18);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 2, 0xD6, 0xF);
    }
    if (shop->panels[2].level != 0) {
        if (shop->panels[2].level != 0x1000) {
            sprite.setScale(shop->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x3B);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 5, 0xA9, 0x26);
    }
    if (shop->panels[3].level != 0) {
        if (shop->panels[3].level != 0x1000) {
            sprite.setScale(shop->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xD2);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0, 0xC6, 0xC4);
    }
    sprite.setLayerId(shop->layer, 7);
    if (shop->unk5C != 0) {
        shop->unk58++;
        shop->unk58 = shop->unk58 < 0x60 ? shop->unk58 : 0;
        shop->unk5C = 0;
    } else {
        shop->unk5C = 1;
    }
    sprite.setScale(0x1000, 0x1000, 0x1000);
    sprite.draw(FILE_CACHE.getEntry(FILE_SHOP_SPRITES << 16), 0x14, shop->unk58, shop->unk58);
}

void func_8008AF88(ItemShop *shop, ItemShopWindows *win) {
    s32 choice;

    switch (shop->substate) {
    case 0:
    default:
        STITSHOP_funcs.startFade(&shop->panels[0], 1);
        STITSHOP_funcs.startFade(&shop->panels[1], 1);
        shop->substate++;
        break;
    case 1:
        STITSHOP_funcs.updateFade(&shop->panels[0]);
        if (STITSHOP_funcs.updateFade(&shop->panels[1]) != 0) {
            STITSHOP_funcs.startFade(&shop->panels[2], 1);
            STITSHOP_funcs.startFade(&shop->panels[3], 1);
            win->title->setString(win->title, FILE_CACHE.load(TEXT_FILE(0x95)), D_8008C16C[shop->shop]);
            win->moneyLabel->setString(win->moneyLabel, FILE_CACHE.load(TEXT_FILE(0x72)), 2);
            win->money->setNumber(win->money, 0, GAME.money);
            win->money->setRightAlign(win->money, 1);
            shop->substate++;
        }
        break;
    case 2:
        STITSHOP_funcs.updateFade(&shop->panels[2]);
        if (STITSHOP_funcs.updateFade(&shop->panels[3]) != 0) {
            win->buy->setString(win->buy, FILE_CACHE.load(TEXT_FILE(0x72)), 3);
            win->sell->setString(win->sell, FILE_CACHE.load(TEXT_FILE(0x72)), 4);
            win->cursor->setVisible(win->cursor, 1);
            win->help->setString(win->help, FILE_CACHE.load(TEXT_FILE(0x72)), 5);
            shop->substate++;
        }
        break;
    case 3:
        choice = shop->unk64;
        if (PAD_PRESSED(PAD_UP)) {
            shop->unk64 = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            shop->unk64 = 1;
        }
        if (choice != shop->unk64) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0xB0, shop->unk64 * 0xE + 0x2F);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            shop->substate = 20;
            shop->step = 1;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            shop->setSubstate(shop, 20);
        }
        break;
    case 10:
        if (shop->unk64 == 0) {
            win->dialog = (Task *)STITSHOP_createBuy(shop);
        } else {
            win->dialog = (Task *)STITSHOP_createSell(shop);
        }
        shop->substate++;
        break;
    case 11:
        if (win->dialog == NULL) {
            STITSHOP_funcs.startFade(&shop->panels[2], 1);
            STITSHOP_funcs.startFade(&shop->panels[3], 1);
            shop->substate = 2;
        }
        break;
    case 20:
        if (shop->step == 0) {
            win->fade = STITSHOP_createFader();
            win->fade->start(win->fade, 0, 0x1E);
        }
        STITSHOP_funcs.startFade(&shop->panels[2], 0);
        STITSHOP_funcs.startFade(&shop->panels[3], 0);
        win->help->setVisible(win->help, 0);
        win->buy->setVisible(win->buy, 0);
        win->sell->setVisible(win->sell, 0);
        win->cursor->setVisible(win->cursor, 0);
        shop->substate++;
        break;
    case 21:
        STITSHOP_funcs.updateFade(&shop->panels[2]);
        if (STITSHOP_funcs.updateFade(&shop->panels[3]) != 0) {
            if (shop->step != 0) {
                shop->setSubstate(shop, 10);
            } else {
                STITSHOP_funcs.startFade(&shop->panels[0], 0);
                STITSHOP_funcs.startFade(&shop->panels[1], 0);
                win->title->setVisible(win->title, 0);
                win->moneyLabel->setVisible(win->moneyLabel, 0);
                win->money->setVisible(win->money, 0);
                shop->substate++;
            }
        }
        break;
    case 22:
        STITSHOP_funcs.updateFade(&shop->panels[0]);
        if (STITSHOP_funcs.updateFade(&shop->panels[1]) != 0) {
            shop->substate++;
        }
        break;
    case 23:
        if (win->fade->state == 2) {
            shop->state = TASK_KILL;
        }
        break;
    }
}

void STITSHOP_updateShop(ItemShop *shop, ItemShopWindows *win) {
    switch (shop->state) {
    case TASK_INIT:
    default:
        switch (shop->substate) {
        case 0:
        default:
            STITSHOP_funcs.loadFiles();
            shop->substate++;
            break;
        case 1:
            if (STITSHOP_funcs.filesLoading() == 0) {
                func_8008ABA4(shop, win);
                shop->panels[0].duration = 10;
                shop->panels[1].duration = 10;
                shop->panels[2].duration = 10;
                shop->panels[3].duration = 10;
                shop->nextState(shop);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_8008AF88(shop, win);
        func_8008AC8C(shop, win);
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        GAME.funcs.requestMode(GAME.fieldMode, 0);
        break;
    }
}

void func_8008B728(ItemShop *shop) {
    ItemShopWindows *win = shop->children;

    win->money->setNumber(win->money, 0, GAME.money);
    win->money->setRightAlign(win->money, 1);
}

ItemShop *STITSHOP_createShop(void) {
    ItemShop *shop = createTask(STITSHOP_updateShop, sizeof(ItemShop), sizeof(ItemShopWindows));

    shop->showMoney = func_8008B728;
    shop->layer = 0x1000;
    shop->shop = GAME_FUNCS.getModeArg();
    return shop;
}

void STITSHOP_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry((FILE_SHOP_SPRITES + 1) << 16));
    FILE_CACHE.request(TEXT_FILE(0x72));
    FILE_CACHE.request(TEXT_FILE(0x6B));
    FILE_CACHE.request(TEXT_FILE(0x64));
    FILE_CACHE.request(TEXT_FILE(0x95));
}

s32 STITSHOP_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x72)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x6B)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x64)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x95)) != 0;
}

void STITSHOP_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STITSHOP_updateFade(PanelAnim *fade) {
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

void STITSHOP_startLerp(ShopLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STITSHOP_updateLerp(ShopLerp *lerp) {
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

s16 *STITSHOP_getShopItems(s32 shop) {
    if (shop < 0 || STITSHOP_shops[shop].items == NULL) {
        return NULL;
    }
    STITSHOP_funcs.count = STITSHOP_shops[shop].count;
    return STITSHOP_shops[shop].items;
}

s32 STITSHOP_canEquip(s32 partner, s32 item) {
    return (GET_ITEM[0](item)->data[4] >> partner) & 1;
}

/* Which equipment slot a bought item would go in: 2 or 3 for the weapons (the
   one with the weaker item when both are taken), 4 or 5 for the accessories
   (the one with the same group, else the weaker one); -1 when it can't */
s32 STITSHOP_compareEquip(s32 partner, s32 item) {
    u8 *data = GET_ITEM[0](item)->data;
    PartnerStats *stats;
    ItemInfo *info;
    u8 *first;
    u8 *second;
    s32 equipped[2];
    u8 *datas[2];
    s32 i;

    switch (data[2]) {
    case 3:
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(partner);
        if (stats->equip[2] > 0) {
            equipped[0] = stats->equip[2];
            if (stats->equip[3] > 0) {
                equipped[1] = stats->equip[3];
                first = GET_ITEM[0](equipped[0])->data;
                info = GET_ITEM[0](equipped[1]);
                second = info->data;
                if (first[2] == 7 || info->type == 0x14) {
                    return 2;
                }
                for (i = 0; i < 2; i++) {
                    info = GET_ITEM[0](equipped[i]);
                    if (info->type < 2 || info->type > 14) {
                        return -1;
                    }
                }
                if (*(u16 *)(first + 0xA) < *(u16 *)(second + 0xA)) {
                    return 2;
                }
            }
            return 3;
        }
        return 2;
    case 2:
        return 3;
    case 4:
        return 0;
    case 5:
        return 1;
    case 6:
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(partner);
        if (stats->equip[4] > 0) {
            equipped[0] = stats->equip[4];
            if (stats->equip[5] > 0) {
                equipped[1] = stats->equip[5];
                datas[0] = GET_ITEM[0](equipped[0])->data;
                datas[1] = GET_ITEM[0](equipped[1])->data;
                if (*(s16 *)(datas[0] + 6) < *(s16 *)(datas[1] + 6)) {
                    return 4;
                }
            }
            return 5;
        }
        return 4;
    case 1:
    case 7:
        return 2;
    case 8:
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(partner);
        if (stats->equip[4] > 0) {
            equipped[0] = stats->equip[4];
            if (stats->equip[5] <= 0) {
                return 5;
            }
            equipped[1] = stats->equip[5];
            datas[0] = GET_ITEM[0](equipped[0])->data;
            if (datas[0][2] == 8 && datas[0][3] == data[3]) {
                return 4;
            }
            datas[1] = GET_ITEM[0](equipped[1])->data;
            if (datas[1][2] == 8 && datas[1][3] == data[3]) {
                return 5;
            }
            break;
        }
        return 4;
    case 0:
    default:
        return -1;
    }
    if (*(s16 *)(datas[0] + 6) < *(s16 *)(datas[1] + 6)) {
        return 4;
    }
    return 5;
}

/* Puts an item in a partner's equipment slot like STSTATUS_equip, moving the
   counts between GAME.items and GAME.equippedItems only when fromBag is set */
void STITSHOP_equip(s32 partner, s32 slot, s32 item, s32 fromBag) {
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(partner);
    s16 *equip;
    s16 *pair;
    u8 *data;
    s32 group;
    s32 old;
    s32 i;
    s32 id = item; /* the match depends on this copy, as in STSTATUS_equip */

    old = *(stats->equip + slot);
    if (old != 0) {
        if (fromBag) {
            GAME.equippedItems[old]--;
            GAME.items[old]++;
        }
        data = GET_ITEM[0](old)->data;
        if (data[2] == 7) {
            stats->equip[2] = 0;
            stats->equip[3] = 0;
        } else {
            *(stats->equip + slot) = 0;
        }
    }
    if (id > 0) {
        data = GET_ITEM[0](id)->data;
        if (data[2] == 7) {
            pair = &stats->equip[2];
            if (stats->equip[2] == 0) {
                pair = NULL;
                if (stats->equip[3] != 0) {
                    pair = &stats->equip[3];
                }
            }
            if (pair != NULL) {
                if (fromBag) {
                    GAME.equippedItems[*pair]--;
                    GAME.items[*pair]++;
                }
                *pair = 0;
            }
        } else if (data[2] == 8) {
            group = data[3];
            for (i = 0; i < 2; i++) {
                equip = &stats->equip[i + 4];
                if (*equip != 0) {
                    data = GET_ITEM[0](*equip)->data;
                    if (data[3] == group) {
                        if (fromBag) {
                            GAME.equippedItems[*equip]--;
                            GAME.items[*equip]++;
                        }
                        *equip = 0;
                    }
                }
            }
        }
        if (fromBag) {
            GAME.equippedItems[id]++;
            GAME.items[id]--;
        }
        data = GET_ITEM[0](id)->data;
        if (data[2] == 7) {
            stats->equip[2] = id;
            stats->equip[3] = id;
        } else {
            *(stats->equip + slot) = id;
        }
    }
}


s32 D_8008C0D4[] = {
    1, 2, 3, 4,
};
/* Where the stat change arrows go in a partner's column */
Vec2 STITSHOP_changePos[] = {
    { 23, 172 }, { 23, 186 }, { 23, 200 }, { 65, 200 }, { 23, 214 }, { 65, 214 },
};
s32 D_8008C114[] = {
    6, 7, 8, 9,
    10, 11, 12, 13,
    14, 15, 16, 17,
    18,
};
s32 D_8008C148[] = {
    0, 35, 36, 37,
    38, 39, 40, 41,
    42,
};
s32 D_8008C16C[] = {
    17, 1, 5, 18,
    6, 25, 13, 24,
    4, 12, 29, 30,
    16, 21, 9, 19,
    2, 7, 20, 8,
    26, 14, 23, 3,
    11, 27, 28, 15,
    22, 10,
};
s16 D_8008C1E4[] = {
    0x05C, 0x06A, 0x09D, 0x0A7, 0x0BE, 0x0D7, 0x0E2, 0x0EC,
    0x0F9, 0x106, 0x113, 0x000,
};
s16 D_8008C1FC[] = {
    0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
s16 D_8008C224[] = {
    0x02B, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048, 0x049,
    0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050, 0x051,
    0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C24C[] = {
    0x060, 0x06E, 0x07A, 0x086, 0x093, 0x0A1, 0x0AB, 0x0B2,
    0x0B9, 0x0C2, 0x0C9, 0x0D1, 0x0DB, 0x0E6, 0x0F0, 0x0FD,
    0x10A, 0x117, 0x000,
};
s16 D_8008C274[] = {
    0x02B, 0x02C, 0x000,
};
s16 D_8008C27C[] = {
    0x05D, 0x06B, 0x09E, 0x0A8, 0x0BF, 0x0D8, 0x0E3, 0x0ED,
    0x0FA, 0x107, 0x114, 0x000,
};
s16 D_8008C294[] = {
    0x02B, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048, 0x049,
    0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050, 0x051,
    0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C2BC[] = {
    0x05E, 0x06C, 0x09F, 0x0A9, 0x0C0, 0x0D9, 0x0E4, 0x0EE,
    0x0FB, 0x108, 0x115, 0x000,
};
s16 D_8008C2D4[] = {
    0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
s16 D_8008C2FC[] = {
    0x02B, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048, 0x049,
    0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050, 0x051,
    0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C324[] = {
    0x05F, 0x06D, 0x078, 0x084, 0x091, 0x0A0, 0x0AA, 0x0B0,
    0x0B7, 0x0C1, 0x0C7, 0x0CF, 0x0DA, 0x0E5, 0x0EF, 0x0FC,
    0x109, 0x116, 0x000,
};
s16 D_8008C34C[] = {
    0x05F, 0x06D, 0x078, 0x084, 0x091, 0x0A0, 0x0AA, 0x0B0,
    0x0B7, 0x0C1, 0x0C7, 0x0CF, 0x0DA, 0x0E5, 0x0EF, 0x0FC,
    0x109, 0x116, 0x000,
};
s16 D_8008C374[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C3A0[] = {
    0x061, 0x06F, 0x07B, 0x087, 0x094, 0x0A2, 0x0AC, 0x0B3,
    0x0BA, 0x0C3, 0x0CA, 0x0D2, 0x0DC, 0x0E7, 0x0F1, 0x0FE,
    0x10B, 0x118, 0x000,
};
s16 D_8008C3C8[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C3F4[] = {
    0x065, 0x073, 0x07F, 0x08C, 0x098, 0x0A6, 0x0AF, 0x0B6,
    0x0BD, 0x0C6, 0x0CE, 0x0D6, 0x0E1, 0x0EB, 0x0F8, 0x105,
    0x112, 0x123, 0x000,
};
s16 D_8008C41C[] = {
    0x125, 0x127, 0x129, 0x12B, 0x12D, 0x12F, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
s16 D_8008C444[] = {
    0x02B, 0x02C, 0x02D, 0x042, 0x043, 0x045, 0x046, 0x047,
    0x048, 0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F,
    0x050, 0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C470[] = {
    0x062, 0x070, 0x07C, 0x088, 0x089, 0x095, 0x0A3, 0x0CB,
    0x0D3, 0x0DD, 0x0DE, 0x0E8, 0x0F2, 0x0F3, 0x0F4, 0x0F5,
    0x0FF, 0x100, 0x101, 0x102, 0x10C, 0x10D, 0x10E, 0x10F,
    0x119, 0x11A, 0x11B, 0x11C, 0x11D, 0x11E, 0x11F, 0x120,
    0x000,
};
s16 D_8008C4B4[] = {
    0x02F, 0x030, 0x031, 0x032, 0x033, 0x034, 0x035, 0x036,
    0x037, 0x038, 0x039, 0x03A, 0x03B, 0x03C, 0x03D, 0x000,
};
s16 D_8008C4D4[] = {
    0x060, 0x06E, 0x07A, 0x086, 0x093, 0x0A1, 0x0AB, 0x0B2,
    0x0B9, 0x0C2, 0x0C9, 0x0D1, 0x0DB, 0x0E6, 0x0F0, 0x0FD,
    0x10A, 0x117, 0x000,
};
s16 D_8008C4FC[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C528[] = {
    0x061, 0x06F, 0x07B, 0x087, 0x094, 0x0A2, 0x0AC, 0x0B3,
    0x0BA, 0x0C3, 0x0CA, 0x0D2, 0x0DC, 0x0E7, 0x0F1, 0x0FE,
    0x10B, 0x118, 0x000,
};
s16 D_8008C550[] = {
    0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
s16 D_8008C578[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C5A4[] = {
    0x063, 0x071, 0x07D, 0x08A, 0x096, 0x0A4, 0x0AD, 0x0B4,
    0x0BB, 0x0C4, 0x0CC, 0x0D4, 0x0DF, 0x0E9, 0x0F6, 0x103,
    0x110, 0x121, 0x000,
};
s16 D_8008C5CC[] = {
    0x064, 0x072, 0x07E, 0x08B, 0x097, 0x0A5, 0x0AE, 0x0B5,
    0x0BC, 0x0C5, 0x0CD, 0x0D5, 0x0E0, 0x0EA, 0x0F7, 0x104,
    0x111, 0x122, 0x000,
};
s16 D_8008C5F4[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C620[] = {
    0x064, 0x072, 0x07E, 0x08B, 0x097, 0x0A5, 0x0AE, 0x0B5,
    0x0BC, 0x0C5, 0x0CD, 0x0D5, 0x0E0, 0x0EA, 0x0F7, 0x104,
    0x111, 0x122, 0x000,
};
s16 D_8008C648[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
s16 D_8008C674[] = {
    0x001, 0x002, 0x003, 0x004, 0x005, 0x006, 0x007, 0x008,
    0x009, 0x00A, 0x00B, 0x00C, 0x00D, 0x00E, 0x00F, 0x010,
    0x011, 0x012, 0x013, 0x014, 0x015, 0x016, 0x017, 0x018,
    0x019, 0x01A, 0x01B, 0x01C, 0x01D, 0x01E, 0x01F, 0x020,
    0x021, 0x022, 0x023, 0x024, 0x025, 0x026, 0x027, 0x028,
    0x029, 0x02A, 0x168, 0x18A, 0x18B, 0x18C, 0x18D, 0x18E,
    0x18F, 0x190, 0x191, 0x192, 0x000,
};
ShopList STITSHOP_shops[31] = {
    { 11, D_8008C1E4 },
    { 18, D_8008C1FC },
    { 19, D_8008C224 },
    { 18, D_8008C24C },
    { 2, D_8008C274 },
    { 11, D_8008C27C },
    { 19, D_8008C294 },
    { 11, D_8008C2BC },
    { 18, D_8008C2D4 },
    { 19, D_8008C2FC },
    { 18, D_8008C324 },
    { 18, D_8008C34C },
    { 20, D_8008C374 },
    { 18, D_8008C3A0 },
    { 20, D_8008C3C8 },
    { 18, D_8008C3F4 },
    { 18, D_8008C41C },
    { 21, D_8008C444 },
    { 32, D_8008C470 },
    { 15, D_8008C4B4 },
    { 18, D_8008C4D4 },
    { 20, D_8008C4FC },
    { 18, D_8008C528 },
    { 18, D_8008C550 },
    { 20, D_8008C578 },
    { 18, D_8008C5A4 },
    { 18, D_8008C5CC },
    { 20, D_8008C5F4 },
    { 18, D_8008C620 },
    { 20, D_8008C648 },
    { 52, D_8008C674 },
};
ItemShopFuncs STITSHOP_funcs = {
    0,
    STITSHOP_loadFiles,
    STITSHOP_filesLoading,
    STITSHOP_startFade,
    STITSHOP_updateFade,
    STITSHOP_startLerp,
    STITSHOP_updateLerp,
    STITSHOP_getShopItems,
    STITSHOP_canEquip,
    STITSHOP_compareEquip,
    STITSHOP_equip,
};
