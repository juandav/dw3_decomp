/* The third object of STSTATUS.PRO (see ststatus.c), the fifth screen's
   panel of func_800879C8: its rodata starts at 0x800826CC (USA). */

#include "ststatus.h"

/* One button of pad 1, held down */
#define PAD_HELD(button) ((PAD.getHeld(0) >> PAD.getButtonBit(0, button)) & 1)

void func_80085BD8(StatusPanel4B *panel, StatusPanel4BWindows *windows) {
    s32 i;

    windows->title = createTextWindow(panel->layer, 1, 0x98, 0x13);
    windows->cursor = createCursor(panel->layer, panel->depth - 1, 0xA5, 0x31);
    windows->cursor->setVisible(windows->cursor, 0);
    for (i = 0; i < 6; i++) {
        windows->slots[i] = createTextWindow(panel->layer, 1, 0xC0, i * 14 + 0x31);
    }
    windows->listTitle = createTextWindow(panel->layer, 1, 0x7F, 0x3B);
    windows->listCursor = createCursor(panel->layer, panel->depth - 1, 0x86, 0x4B);
    windows->listCursor->setVisible(windows->listCursor, 0);
    for (i = 0; i < 8; i++) {
        windows->rows[i].name = createTextWindow(panel->layer, 1, 0xA0, i * 14 + 0x4B);
        windows->rows[i].times = createTextWindow(panel->layer, 1, 0x10D, i * 14 + 0x4B);
        windows->rows[i].count = createTextWindow(panel->layer, 1, 0x120, i * 14 + 0x4B);
    }
    windows->help = createTextWindow(panel->layer, 1, 0x14, 0xC6);
    windows->kind = createTextWindow(panel->layer, 1, 0x14, 0xD5);
    windows->slotTitle = createTextWindow(panel->layer, 1, 0xA7, 0x13);
    windows->slotItem = createTextWindow(panel->layer, 1, 0xC0, 0x23);
}

/* The partner's equipment, or the slots' names where it has none */
void func_80085DC0(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 show) {
    PartnerStats *stats;
    s16 item;
    s32 i;

    if (show) {
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(panel->partner);
        for (i = 0; i < 6; i++) {
            item = stats->equip[i];
            if (item > 0) {
                windows->slots[i]->setString(windows->slots[i], FILE_CACHE.load(TEXT_FILE(0x6B)), item);
            } else {
                windows->slots[i]->setString(windows->slots[i], FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AC0[i]);
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            windows->slots[i]->setVisible(windows->slots[i], 0);
        }
    }
}

/* An item's name and, for slots 2 and 3, its kind (none: string 0x51) */
void func_80085EE4(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 item) {
    u8 *data;

    if (item > 0) {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x64)), item);
        if (panel->slot == 2 || panel->slot == 3) {
            data = GET_ITEM[0](item)->data;
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AD8[data[2] - 1]);
            return;
        }
    } else {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x51);
    }
    windows->kind->setVisible(windows->kind, 0);
}

/* Fills the list of the items that fit the slot */
void func_80086010(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 show) {
    s32 i;
    s32 row;
    s32 item;

    if (show) {
        windows->listTitle->setString(windows->listTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AC0[panel->slot]);
        for (i = 0; i < 8; i++) {
            row = panel->scroll + i;
            if (row > panel->count - 1) {
                break;
            }
            item = panel->items[row];
            if (item > 0) {
                if (STSTATUS_data.funcs.canEquip(panel->partner, panel->slot, item)) {
                    windows->rows[i].name->setPalette(windows->rows[i].name, 0);
                } else {
                    windows->rows[i].name->setPalette(windows->rows[i].name, 7);
                }
                windows->rows[i].name->setString(windows->rows[i].name, FILE_CACHE.load(TEXT_FILE(0x6B)), item);
                windows->rows[i].times->setString(windows->rows[i].times, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x40);
                windows->rows[i].times->setRightAlign(windows->rows[i].times, 1);
                windows->rows[i].count->setNumber(windows->rows[i].count, 0, GAME.items[item]);
                windows->rows[i].count->setRightAlign(windows->rows[i].count, 1);
            } else {
                if (item == -1) {
                    windows->rows[i].name->setString(windows->rows[i].name, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x45);
                    windows->rows[i].name->setPalette(windows->rows[i].name, 0);
                } else {
                    windows->rows[i].name->setVisible(windows->rows[i].name, 0);
                }
                windows->help->setVisible(windows->help, 0);
                windows->kind->setVisible(windows->kind, 0);
                windows->rows[i].times->setVisible(windows->rows[i].times, 0);
                windows->rows[i].count->setVisible(windows->rows[i].count, 0);
            }
        }
        func_80085EE4(panel, windows, panel->items[panel->cursor + panel->scroll]);
    } else {
        windows->listTitle->setVisible(windows->listTitle, 0);
        for (i = 0; i < 8; i++) {
            windows->rows[i].name->setVisible(windows->rows[i].name, 0);
            windows->rows[i].times->setVisible(windows->rows[i].times, 0);
            windows->rows[i].count->setVisible(windows->rows[i].count, 0);
        }
        windows->help->setVisible(windows->help, 0);
        windows->kind->setVisible(windows->kind, 0);
    }
}

/* The item in the slot being changed, or the slot's name if it's empty */
void func_80086368(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 show) {
    PartnerStats *stats;
    s32 item;

    if (show) {
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(panel->partner);
        item = *(stats->equip + panel->slot); /* the match depends on this form */
        windows->slotTitle->setString(windows->slotTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x20);
        if (item > 0) {
            windows->slotItem->setString(windows->slotItem, FILE_CACHE.load(TEXT_FILE(0x6B)), item);
        } else {
            windows->slotItem->setString(windows->slotItem, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AC0[panel->slot]);
        }
    } else {
        windows->slotTitle->setVisible(windows->slotTitle, 0);
        windows->slotItem->setVisible(windows->slotItem, 0);
    }
}

/* Draws the equipment panels: the partner's equipment, the list of items
   that fit the slot and the slot's item */
void func_800864B0(StatusPanel4B *panel) {
    SpriteDrawer sprite;
    PartnerStats *stats;
    s32 level;
    s32 item;
    s32 index;
    s32 i;

    stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(panel->partner);
    initSpriteDrawer(&sprite);
    if (panel->panels[0].level != 0) {
        sprite.setTexture(0x140, 0);
        sprite.setLayerId(panel->layer, 6);
        level = panel->panels[0].level;
        if (level != 0x1000) {
            sprite.setScale(level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x19);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_MENU_SPRITES << 16), 0x18, 0x22, 0xD);
    }
    sprite.setLayerId(panel->layer, panel->depth);
    level = panel->panels[1].level;
    if (level != 0) {
        if (level != 0x1000) {
            sprite.setScale(level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x58);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            sprite.setTexture(0x140, 0);
            for (i = 0; i < 6; i++) {
                item = stats->equip[i];
                if (item > 0) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(item), 0xB2, i * 14 + 0x31);
                }
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_STATUS_SPRITES << 16), 0x2A, 0x9D, 0x28);
    }
    level = panel->panels[2].level;
    if (level != 0) {
        if (level != 0x1000) {
            sprite.setScale(level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x89);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            for (i = 0; i < 8; i++) {
                index = panel->scroll + i;
                if (index < panel->count) {
                    item = panel->items[index];
                    if (item == -1 || item > 0) {
                        sprite.setTexture(0x280, 0x100);
                        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x31, 0x91, i * 14 + 0x4B);
                        if (item > 0) {
                            sprite.setTexture(0x140, 0);
                            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(item), 0x91, i * 14 + 0x4B);
                        }
                    }
                }
            }
            if (panel->count > 8) {
                if (GFX.funcs.getTime() - panel->arrowTime >= 9) {
                    panel->arrowTime = GFX.funcs.getTime();
                    panel->arrowShown = 1 - panel->arrowShown;
                }
                sprite.setTexture(0x280, 0x100);
                if (panel->arrowShown) {
                    if (panel->scroll > 0) {
                        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_STATUS_SPRITES << 16), 0x32, 0x126, 0x45);
                    }
                    if (panel->scroll < panel->count - 8) {
                        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_STATUS_SPRITES << 16), 0x33, 0x126, 0xB3);
                    }
                }
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x2B, 0x77, 0x39);
        if (panel->panels[2].level != 0x1000) {
            sprite.setPivot(0, 0xD3);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x20, 0, 0xC2);
    }
    level = panel->panels[3].level;
    if (level != 0) {
        if (level != 0x1000) {
            sprite.setScale(level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x20);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            if (panel->showSlot) {
                item = *(stats->equip + panel->slot); /* the match depends on this form */
                if (item > 0) {
                    sprite.setTexture(0x140, 0);
                    sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(item), 0xB2, 0x23);
                }
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_STATUS_SPRITES << 16), 0x2C, 0xA0, 0x11);
    }
}

/* The equipment panel's steps: a slot is chosen, then an item from the list
   of those that fit it, the ones the partner can equip first */
void func_80086B28(StatusPanel4B *panel, StatusPanel4BWindows *windows) {
    s32 oldSlot;
    s32 oldCursor;
    s32 oldScroll;
    s32 count;
    s32 n;
    s32 item;
    s32 i;

    switch (panel->substate) {
    case 0:
    default:
        STSTATUS_data.funcs.startFade(&panel->panels[0], 1);
        panel->substate++;
        break;
    case 1:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[0])) {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x3F);
            STSTATUS_data.funcs.startFade(&panel->panels[1], 1);
            panel->substate++;
        }
        break;
    case 2:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[1])) {
            func_80085DC0(panel, windows, 1);
            windows->cursor->setVisible(windows->cursor, 1);
            panel->substate++;
        }
        break;
    case 3:
        oldSlot = panel->slot;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            panel->slot--;
            if (panel->slot < 0) {
                panel->slot = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            panel->slot++;
            if (panel->slot >= 6) {
                panel->slot = 5;
            }
        }
        if (oldSlot != panel->slot) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0xA5, panel->slot * 14 + 0x31);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            n = 1;
            count = STSTATUS_data.funcs.listItems(D_80099AF8[panel->slot], (u16 *)panel->owned);
            for (i = 0; i < count; i++) {
                if (STSTATUS_data.funcs.canEquip(panel->partner, panel->slot, panel->owned[i])) {
                    panel->items[n++] = panel->owned[i];
                }
            }
            for (i = 0; i < count; i++) {
                if (!STSTATUS_data.funcs.canEquip(panel->partner, panel->slot, panel->owned[i])) {
                    panel->items[n++] = panel->owned[i];
                }
            }
            panel->count = count + 1;
            panel->items[0] = -1;
            panel->substate = 10;
        }
        if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            panel->substate = 0x32;
        }
        break;
    case 10:
        STSTATUS_data.funcs.startFade(&panel->panels[1], 0);
        func_80085DC0(panel, windows, 0);
        windows->cursor->setVisible(windows->cursor, 0);
        panel->cursor = 0;
        panel->scroll = 0;
        panel->substate++;
        break;
    case 12:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[0])) {
            STSTATUS_data.funcs.startFade(&panel->panels[3], 1);
            panel->substate++;
        }
        break;
    case 13:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[3])) {
            panel->showSlot = 1;
            func_80086368(panel, windows, 1);
            STSTATUS_data.funcs.startFade(&panel->panels[2], 1);
            panel->substate++;
        }
        break;
    case 14:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[2])) {
            func_80086010(panel, windows, 1);
            windows->listCursor->setPos(windows->listCursor, 0x89, 0x4B);
            windows->listCursor->setVisible(windows->listCursor, 1);
            panel->screen->func_8008BA38(panel->screen, panel->slot, 0);
            if (panel->count >= 9) {
                windows->scrollBar = STSTATUS_createScrollBar();
                windows->scrollBar->setX(windows->scrollBar, 0x125, 0xC);
                windows->scrollBar->setRange(windows->scrollBar, 0x4E, 0xB3);
                windows->scrollBar->setCount(windows->scrollBar, 8, panel->count);
                windows->scrollBar->setPos(windows->scrollBar, 0);
            }
            panel->substate++;
        }
        break;
    case 15:
        oldCursor = panel->cursor;
        oldScroll = panel->scroll;
        if (panel->count >= 9) {
            if ((!PAD_HELD(PAD_R1) && PAD_PRESSED(PAD_L1)) || (!PAD_HELD(PAD_R1) && PAD_REPEATED(PAD_L1))) {
                panel->scroll -= 8;
                if (panel->scroll < 0) {
                    panel->scroll = 0;
                }
            } else if ((!PAD_HELD(PAD_L1) && PAD_PRESSED(PAD_R1)) || (!PAD_HELD(PAD_L1) && PAD_REPEATED(PAD_R1))) {
                panel->scroll += 8;
                if (panel->scroll > panel->count - 8) {
                    panel->scroll = panel->count - 8;
                }
            }
        }
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            panel->cursor--;
            if (panel->cursor < 0) {
                panel->cursor = 0;
                panel->scroll--;
                if (panel->scroll < 0) {
                    panel->scroll = 0;
                }
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (panel->count < 8) {
                panel->cursor++;
                if (panel->cursor > panel->count - 1) {
                    panel->cursor = panel->count - 1;
                }
            } else {
                panel->cursor++;
                if (panel->cursor >= 8) {
                    panel->cursor = 7;
                    panel->scroll++;
                    if (panel->scroll > panel->count - 8) {
                        panel->scroll = panel->count - 8;
                    }
                }
            }
        }
        if (oldCursor != panel->cursor) {
            SOUND.playSound(0x8004513E);
            windows->listCursor->setPos(windows->listCursor, 0x86, panel->cursor * 14 + 0x4B);
#if VERSION_US
            if (windows->scrollBar != NULL) {
                windows->scrollBar->setPos(windows->scrollBar, panel->cursor + panel->scroll);
            }
#endif
        }
        if (oldScroll != panel->scroll) {
            SOUND.playSound(0x8004513E);
            func_80086010(panel, windows, 1);
            if (windows->scrollBar != NULL) {
#if VERSION_US
                /* the USA version's bar follows the chosen item, the European one the page */
                windows->scrollBar->setPos(windows->scrollBar, panel->cursor + panel->scroll);
#else
                windows->scrollBar->setPos(windows->scrollBar, panel->scroll);
#endif
            }
        }
        item = panel->items[panel->cursor + panel->scroll];
        if (oldCursor != panel->cursor || oldScroll != panel->scroll) {
            if (STSTATUS_data.funcs.canEquip(panel->partner, panel->slot, item)) {
                panel->screen->func_8008BA38(panel->screen, panel->slot, item);
            } else {
                panel->screen->func_8008BA38(panel->screen, -1, 0);
            }
            func_80085EE4(panel, windows, item);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            if (STSTATUS_data.funcs.canEquip(panel->partner, panel->slot, item)) {
                STSTATUS_data.funcs.equip(panel->partner, panel->slot, item);
                panel->substate = 0x14;
                panel->showSlot = 0;
                panel->screen->func_8008BA38(panel->screen, panel->slot, item);
                if (windows->scrollBar != NULL) {
                    windows->scrollBar->state = 3;
                }
                SOUND.playSound(0x8004503C);
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            panel->screen->func_8008BA38(panel->screen, -1, 0);
            panel->substate = 0x14;
            panel->showSlot = 0;
            if (windows->scrollBar != NULL) {
                windows->scrollBar->state = 3;
            }
        }
        break;
    case 0x14:
        STSTATUS_data.funcs.startFade(&panel->panels[2], 0);
        func_80086010(panel, windows, 0);
        windows->listCursor->setVisible(windows->listCursor, 0);
        panel->substate++;
        break;
    case 0x15:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[2])) {
            STSTATUS_data.funcs.startFade(&panel->panels[3], 0);
            func_80086368(panel, windows, 0);
            panel->substate++;
        }
        break;
    case 0x16:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[3])) {
            panel->substate = 0;
        }
        break;
    case 0x32:
        STSTATUS_data.funcs.startFade(&panel->panels[1], 0);
        func_80085DC0(panel, windows, 0);
        windows->cursor->setVisible(windows->cursor, 0);
        panel->substate++;
        break;
    case 11:
    case 0x33:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[1])) {
            windows->title->setVisible(windows->title, 0);
            STSTATUS_data.funcs.startFade(&panel->panels[0], 0);
            panel->substate++;
        }
        break;
    case 0x34:
        if (STSTATUS_data.funcs.updateFade(&panel->panels[0])) {
            panel->state = 3;
        }
        break;
    }
}

void func_80087914(StatusPanel4B *panel, void *children) {
    switch (panel->state) {
    case TASK_INIT:
    default:
        panel->nextState(panel);
        panel->scroll = 0;
        func_80085BD8(panel, children);
        panel->panels[3].duration = 10;
        panel->panels[1].duration = 10;
        panel->panels[2].duration = 10;
        panel->panels[0].duration = 10;
        break;
    case TASK_RUN:
        func_80086B28(panel, children);
        func_800864B0(panel);
        break;
    case TASK_KILL:
        panel->screen->unk70 = 0;
        /* fallthrough */
    case TASK_DONE:
        break;
    }
}

StatusPanel4B *func_800879C8(StatusScreen4 *screen) {
    StatusPanel4B *panel = createTask(func_80087914, sizeof(StatusPanel4B), 0xA4);

    panel->layer = 0x1000;
    panel->depth = 4;
    panel->screen = screen;
    panel->partner = GAME_FUNCS.getPartyMember(screen->member);
    return panel;
}
