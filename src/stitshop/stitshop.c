#include "stitshop.h"

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
void func_800830DC(ShopBuy *buy, ShopBuyWindows *win);
void func_8008361C(ShopBuy *buy, ShopBuyWindows *win);
void func_80085254(ShopSell *sell, ShopSellWindows *win);
void func_80085684(ShopSell *sell, ShopSellWindows *win);
void func_80086CE4(ShopItemList *list, void *win, s32 arg);
void func_800875AC();
void func_80087D5C(ShopItemList *list, s32 frozen);
void func_80087E00(ShopItemList *list, s32 visible);
void func_80087FD0(ShopItemList *list);
void func_80088960(ShopInfo *info, void *win, s32 arg);
void func_800894EC(ShopInfo *info, void *win, s32 arg);
void func_80089774(ShopInfo *info, void *win, s32 arg);
void func_8008988C(ShopInfo *info, void *win, s32 arg);
void func_8008A5E8();
ItemShop *func_8008B77C(void);
void func_8008B614();
void func_8008B7E0(void);
s32 func_8008B880(void);
void func_8008B908(PanelAnim *fade, s32 fadeIn);
s32 func_8008B99C(PanelAnim *fade);
void func_8008BA08(ShopLerp *lerp, s32 from, s32 to, s32 frames);
s32 func_8008BA48(ShopLerp *lerp);
u16 *func_8008BAB4(s32 shop);
s32 func_8008BAF8(s32 partner, s32 item);
s32 func_8008BB3C(s32 partner, s32 item);
void func_8008BE2C(s32 partner, s32 slot, s32 item, s32 fromBag);

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
        children[0] = (Task *)func_8008B77C();
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

void func_80082ADC(ScreenFade *task, s32 fadeIn, s32 duration) {
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

void func_80082B64(ScreenFade *task) {
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

void func_80082CA8(ScreenFade *task) {
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
        func_80082B64(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *func_80082D5C(void) {
    ScreenFade *task = createTask(func_80082CA8, sizeof(ScreenFade), 0);

    task->start = func_80082ADC;
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

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800830DC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008361C);

void func_80084FCC(ShopBuy *buy, ShopBuyWindows *win) {
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

ShopBuy *func_800850A8(ItemShop *shop) {
    ShopBuy *buy = createTask(func_80084FCC, sizeof(ShopBuy), sizeof(ShopBuyWindows));

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

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80085254);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80085684);

void func_800869F8(ShopSell *sell, ShopSellWindows *win) {
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

ShopSell *func_80086AD8(ItemShop *shop) {
    ShopSell *sell = createTask(func_800869F8, sizeof(ShopSell), sizeof(ShopSellWindows));

    sell->showItem = func_80086AA0;
    sell->layer = 0x1000;
    sell->depth = 4;
    sell->shop = shop;
    return sell;
}

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80086B2C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80086CE4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008700C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800873E8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800875AC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087D5C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80087E00);

void func_80087EB0(ShopItemList *list) {
    list->setState(list, TASK_RUN);
}

void func_80087ED8(ShopItemList *list) {
    list->setState(list, TASK_RUN);
    list->substate = 0x32;
    func_80087E00(list, 0);
}

s16 func_80087F1C(ShopItemList *list) {
    if (!list->selling) {
        return list->shopItems[list->selection];
    }
    return list->items[list->selection];
}

void func_80087F64(ShopItemList *list) {
    void *win = list->children;

    func_80087FD0(list);
    func_80086CE4(list, win, 1);
    ((ShopBuy *)list->dialog)->showItem((ShopBuy *)list->dialog, list->items[list->selection], 1);
}

void func_80087FD0(ShopItemList *list) {
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

ShopItemList *func_80088094(Task *dialog, s32 type, s32 selling) {
    ShopItemList *list = createTask(func_800875AC, sizeof(ShopItemList), 0x50);

    list->start = func_80087EB0;
    list->close = func_80087ED8;
    list->getSelected = func_80087F1C;
    list->showCursor = func_80087E00;
    list->freezeCursor = func_80087D5C;
    list->refresh = func_80087F64;
    list->listBag = func_80087FD0;
    list->layer = 0x1000;
    list->depth = 4;
    list->dialog = dialog;
    list->selling = selling;
    list->type = type;
    return list;
}

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088150);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800884A4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088578);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088638);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008879C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80088960);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089104);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_800894EC);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089774);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008988C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089AE0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_80089DE8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A46C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A5E8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A91C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A9A4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A9C0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008A9F8);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AAB0);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AB04);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008ABA4);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AC8C);

#if VERSION_EU
/* The European splat cuts func_8008AC8C, func_8008AF88 and func_8008B614
 * where the names config/eu/symbols.txt gives three FIELDSTG functions for
 * the executable fall */
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AEB4);
#endif

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008AF88);

#if VERSION_EU
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B2C4);
#endif

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B614);

#if VERSION_EU
INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008B320);
#endif

void func_8008B728(ItemShop *shop) {
    ItemShopWindows *win = shop->children;

    win->money->setNumber(win->money, 0, GAME.money);
    win->money->setRightAlign(win->money, 1);
}

ItemShop *func_8008B77C(void) {
    ItemShop *shop = createTask(func_8008B614, sizeof(ItemShop), sizeof(ItemShopWindows));

    shop->showMoney = func_8008B728;
    shop->layer = 0x1000;
    shop->shop = GAME_FUNCS.getModeArg();
    return shop;
}

void func_8008B7E0(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry((FILE_SHOP_SPRITES + 1) << 16));
    FILE_CACHE.request(TEXT_FILE(0x72));
    FILE_CACHE.request(TEXT_FILE(0x6B));
    FILE_CACHE.request(TEXT_FILE(0x64));
    FILE_CACHE.request(TEXT_FILE(0x95));
}

s32 func_8008B880(void) {
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

void func_8008B908(PanelAnim *fade, s32 fadeIn) {
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

s32 func_8008B99C(PanelAnim *fade) {
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

void func_8008BA08(ShopLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 func_8008BA48(ShopLerp *lerp) {
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

u16 *func_8008BAB4(s32 shop) {
    if (shop < 0 || STITSHOP_shops[shop].items == NULL) {
        return NULL;
    }
    STITSHOP_funcs.count = STITSHOP_shops[shop].count;
    return STITSHOP_shops[shop].items;
}

s32 func_8008BAF8(s32 partner, s32 item) {
    return (GET_ITEM[0](item)->data[4] >> partner) & 1;
}

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BB3C);

INCLUDE_ASM("stitshop/nonmatchings/stitshop", func_8008BE2C);


s32 D_8008C0D4[] = {
    1, 2, 3, 4,
};
s32 D_8008C0E4[] = {
    23, 172, 23, 186,
    23, 200, 65, 200,
    23, 214, 65, 214,
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
u16 D_8008C1E4[] = {
    0x05C, 0x06A, 0x09D, 0x0A7, 0x0BE, 0x0D7, 0x0E2, 0x0EC,
    0x0F9, 0x106, 0x113, 0x000,
};
u16 D_8008C1FC[] = {
    0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
u16 D_8008C224[] = {
    0x02B, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048, 0x049,
    0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050, 0x051,
    0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C24C[] = {
    0x060, 0x06E, 0x07A, 0x086, 0x093, 0x0A1, 0x0AB, 0x0B2,
    0x0B9, 0x0C2, 0x0C9, 0x0D1, 0x0DB, 0x0E6, 0x0F0, 0x0FD,
    0x10A, 0x117, 0x000,
};
u16 D_8008C274[] = {
    0x02B, 0x02C, 0x000,
};
u16 D_8008C27C[] = {
    0x05D, 0x06B, 0x09E, 0x0A8, 0x0BF, 0x0D8, 0x0E3, 0x0ED,
    0x0FA, 0x107, 0x114, 0x000,
};
u16 D_8008C294[] = {
    0x02B, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048, 0x049,
    0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050, 0x051,
    0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C2BC[] = {
    0x05E, 0x06C, 0x09F, 0x0A9, 0x0C0, 0x0D9, 0x0E4, 0x0EE,
    0x0FB, 0x108, 0x115, 0x000,
};
u16 D_8008C2D4[] = {
    0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
u16 D_8008C2FC[] = {
    0x02B, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048, 0x049,
    0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050, 0x051,
    0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C324[] = {
    0x05F, 0x06D, 0x078, 0x084, 0x091, 0x0A0, 0x0AA, 0x0B0,
    0x0B7, 0x0C1, 0x0C7, 0x0CF, 0x0DA, 0x0E5, 0x0EF, 0x0FC,
    0x109, 0x116, 0x000,
};
u16 D_8008C34C[] = {
    0x05F, 0x06D, 0x078, 0x084, 0x091, 0x0A0, 0x0AA, 0x0B0,
    0x0B7, 0x0C1, 0x0C7, 0x0CF, 0x0DA, 0x0E5, 0x0EF, 0x0FC,
    0x109, 0x116, 0x000,
};
u16 D_8008C374[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C3A0[] = {
    0x061, 0x06F, 0x07B, 0x087, 0x094, 0x0A2, 0x0AC, 0x0B3,
    0x0BA, 0x0C3, 0x0CA, 0x0D2, 0x0DC, 0x0E7, 0x0F1, 0x0FE,
    0x10B, 0x118, 0x000,
};
u16 D_8008C3C8[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C3F4[] = {
    0x065, 0x073, 0x07F, 0x08C, 0x098, 0x0A6, 0x0AF, 0x0B6,
    0x0BD, 0x0C6, 0x0CE, 0x0D6, 0x0E1, 0x0EB, 0x0F8, 0x105,
    0x112, 0x123, 0x000,
};
u16 D_8008C41C[] = {
    0x125, 0x127, 0x129, 0x12B, 0x12D, 0x12F, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
u16 D_8008C444[] = {
    0x02B, 0x02C, 0x02D, 0x042, 0x043, 0x045, 0x046, 0x047,
    0x048, 0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F,
    0x050, 0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C470[] = {
    0x062, 0x070, 0x07C, 0x088, 0x089, 0x095, 0x0A3, 0x0CB,
    0x0D3, 0x0DD, 0x0DE, 0x0E8, 0x0F2, 0x0F3, 0x0F4, 0x0F5,
    0x0FF, 0x100, 0x101, 0x102, 0x10C, 0x10D, 0x10E, 0x10F,
    0x119, 0x11A, 0x11B, 0x11C, 0x11D, 0x11E, 0x11F, 0x120,
    0x000,
};
u16 D_8008C4B4[] = {
    0x02F, 0x030, 0x031, 0x032, 0x033, 0x034, 0x035, 0x036,
    0x037, 0x038, 0x039, 0x03A, 0x03B, 0x03C, 0x03D, 0x000,
};
u16 D_8008C4D4[] = {
    0x060, 0x06E, 0x07A, 0x086, 0x093, 0x0A1, 0x0AB, 0x0B2,
    0x0B9, 0x0C2, 0x0C9, 0x0D1, 0x0DB, 0x0E6, 0x0F0, 0x0FD,
    0x10A, 0x117, 0x000,
};
u16 D_8008C4FC[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C528[] = {
    0x061, 0x06F, 0x07B, 0x087, 0x094, 0x0A2, 0x0AC, 0x0B3,
    0x0BA, 0x0C3, 0x0CA, 0x0D2, 0x0DC, 0x0E7, 0x0F1, 0x0FE,
    0x10B, 0x118, 0x000,
};
u16 D_8008C550[] = {
    0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x131,
    0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139,
    0x13A, 0x13B, 0x000,
};
u16 D_8008C578[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C5A4[] = {
    0x063, 0x071, 0x07D, 0x08A, 0x096, 0x0A4, 0x0AD, 0x0B4,
    0x0BB, 0x0C4, 0x0CC, 0x0D4, 0x0DF, 0x0E9, 0x0F6, 0x103,
    0x110, 0x121, 0x000,
};
u16 D_8008C5CC[] = {
    0x064, 0x072, 0x07E, 0x08B, 0x097, 0x0A5, 0x0AE, 0x0B5,
    0x0BC, 0x0C5, 0x0CD, 0x0D5, 0x0E0, 0x0EA, 0x0F7, 0x104,
    0x111, 0x122, 0x000,
};
u16 D_8008C5F4[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C620[] = {
    0x064, 0x072, 0x07E, 0x08B, 0x097, 0x0A5, 0x0AE, 0x0B5,
    0x0BC, 0x0C5, 0x0CD, 0x0D5, 0x0E0, 0x0EA, 0x0F7, 0x104,
    0x111, 0x122, 0x000,
};
u16 D_8008C648[] = {
    0x02B, 0x02C, 0x042, 0x043, 0x045, 0x046, 0x047, 0x048,
    0x049, 0x04A, 0x04B, 0x04C, 0x04D, 0x04E, 0x04F, 0x050,
    0x051, 0x052, 0x053, 0x054, 0x000,
};
u16 D_8008C674[] = {
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
    func_8008B7E0,
    func_8008B880,
    func_8008B908,
    func_8008B99C,
    func_8008BA08,
    func_8008BA48,
    func_8008BAB4,
    func_8008BAF8,
    func_8008BB3C,
    func_8008BE2C,
};
