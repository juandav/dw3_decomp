/* The seventh object of STSTATUS.PRO (see ststatus.c), the first screen's
   panels (func_80092B0C): its rodata starts at 0x80082B90 (USA). */

#include "ststatus.h"

void func_8009205C(StatusPanel0 *panel, StatusPanel0Windows *windows);
s32 func_800919B8(StatusPanel0 *panel, StatusPanel0Windows *windows);
void func_80092440(StatusPanel0 *panel);
void func_80092B80(StatusPanel0 *panel);

void func_80091360(StatusPanel0 *panel, StatusPanel0Windows *windows) {
    TextWindow *window;
    s32 i;
    s32 j;

    windows->title = createTextWindow(panel->layer, 1, 0x13, 0x14);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            window = createTextWindow(panel->layer, 1, j * 0x83 + 0x38, i * 14 + 0x25);
            windows->items[i][j] = window;
            window->setDepth(window, panel->depth - 1);
        }
    }
    windows->page = createTextWindow(panel->layer, 1, 0x9B, 0x9C);
    windows->unk48 = createTextWindow(panel->layer, 1, 0x9E, 0x9C);
    windows->pageCount = createTextWindow(panel->layer, 1, 0xB2, 0x9C);
    windows->prev = createTextWindow(panel->layer, 1, 0x2D, 0x97);
    windows->next = createTextWindow(panel->layer, 1, 0x102, 0x97);
    windows->cursor = createCursor(panel->layer, panel->depth - 1, (panel->cursor % 2) * 0x83 + 0x1E,
                                   (panel->cursor % 16) / 2 * 14 + 0x25);
    windows->cursor->setVisible(windows->cursor, 0);
}

/* Shows or hides the list's page and its arrows */
void func_80091560(StatusPanel0 *panel, StatusPanel0Windows *windows, s32 show) {
    s32 first;
    s32 i;
    s32 j;

    if (show) {
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), panel->list + 0x16);
        first = panel->page * 16;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 2; j++) {
                if (panel->items[first + i * 2 + j] != 0) {
                    windows->items[i][j]->setString(windows->items[i][j], FILE_CACHE.load(TEXT_FILE(0x6B)),
                                                    panel->items[first + i * 2 + j]);
                } else {
                    windows->items[i][j]->setVisible(windows->items[i][j], 0);
                }
            }
        }
        if (panel->page == 0) {
            panel->hasPrev = 0;
            windows->prev->setVisible(windows->prev, 0);
        } else {
            panel->hasPrev = 1;
            windows->prev->setString(windows->prev, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x22);
        }
        if (panel->page != panel->pageCount - 1) {
            panel->hasNext = 1;
            windows->next->setString(windows->next, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x23);
        } else {
            panel->hasNext = 0;
            windows->next->setVisible(windows->next, 0);
        }
    } else {
        windows->title->setVisible(windows->title, 0);
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 2; j++) {
                windows->items[i][j]->setVisible(windows->items[i][j], 0);
            }
        }
        panel->hasPrev = 0;
        windows->prev->setVisible(windows->prev, 0);
        panel->hasNext = 0;
        windows->next->setVisible(windows->next, 0);
    }
}

/* Shows the page with the arrows, the chosen item and the page number */
void func_800917EC(StatusPanel0 *panel, StatusPanel0Windows *windows) {
    if (panel->page == 0) {
        panel->hasPrev = 0;
        windows->prev->setVisible(windows->prev, 0);
    } else {
        panel->hasPrev = 1;
        windows->prev->setString(windows->prev, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x22);
    }
    if (panel->page == panel->pageCount - 1) {
        panel->hasNext = 0;
        windows->next->setVisible(windows->next, 0);
    } else {
        panel->hasNext = 1;
        windows->next->setString(windows->next, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x23);
    }
    func_80091560(panel, windows, 1);
    panel->screen->item = panel->items[panel->cursor];
    func_8008E668(panel->screen, 1);
    func_8008E828(panel->screen, 1);
    windows->page->setNumber(windows->page, 0, panel->page + 1);
    windows->page->setRightAlign(windows->page, 1);
    windows->unk48->setString(windows->unk48, FILE_CACHE.load(TEXT_FILE(0xB1)), 4);
    windows->pageCount->setNumber(windows->pageCount, 0, panel->pageCount);
    windows->pageCount->setRightAlign(windows->pageCount, 1);
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus_7", func_800919B8);

/* The item list's update: fades in, lets an item be chosen, fades out */
void func_8009205C(StatusPanel0 *panel, StatusPanel0Windows *windows) {
    switch (panel->substate) {
    case 0:
    default:
        panel->fades[0].duration = 10;
        panel->fades[1].duration = 10;
        STSTATUS_data.funcs.startFade(&panel->fades[0], 1);
        STSTATUS_data.funcs.startFade(&panel->fades[1], 1);
        panel->substate++;
        break;
    case 1:
        STSTATUS_data.funcs.updateFade(&panel->fades[0]);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[1])) {
            windows->cursor->setVisible(windows->cursor, 1);
            func_800917EC(panel, windows);
            windows->cursor->setPos(windows->cursor, (panel->cursor % 2) * 0x83 + 0x1E,
                                    (panel->cursor % 16) / 2 * 14 + 0x25);
            panel->active = 1;
            panel->substate++;
        }
        break;
    case 2:
        if (func_800919B8(panel, windows) == 0) {
            if (PAD_PRESSED(PAD_CROSS)) {
                if (panel->list == 0) {
                    panel->screen->unk7C = panel->cursor;
                    panel->screen->item = panel->items[panel->cursor];
                    if (*GET_ITEM[0](panel->screen->item)->data & 1) {
                        SOUND.playSound(0x8004503C);
                        func_8008E828(panel->screen, -1);
                        panel->substate++;
                    }
                }
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                panel->screen->unk7C = -1;
                func_8008EA38(panel->screen, 0);
                panel->substate++;
            }
        }
        break;
    case 3:
        func_80091560(panel, windows, 0);
        windows->cursor->setVisible(windows->cursor, 0);
        windows->page->setVisible(windows->page, 0);
        windows->unk48->setVisible(windows->unk48, 0);
        windows->pageCount->setVisible(windows->pageCount, 0);
        STSTATUS_data.funcs.startFade(&panel->fades[0], 0);
        STSTATUS_data.funcs.startFade(&panel->fades[1], 0);
        panel->hasPrev = 0;
        panel->hasNext = 0;
        panel->active = 0;
        panel->substate++;
        break;
    case 4:
        func_8008EAAC(panel->screen);
        STSTATUS_data.funcs.updateFade(&panel->fades[0]);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[1])) {
            panel->state = TASK_KILL;
        }
        break;
    }
}

/* Draws the item list's icons, page arrows and frames */
void func_80092440(StatusPanel0 *panel) {
    SpriteDrawer sprite;
    ItemInfo *info;
    s32 first;
    s32 i;
    s32 j;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    sprite.setLayerId(panel->layer, panel->depth);
    if (panel->pageCount >= 2) {
        if (GFX.funcs.getTime() - panel->time >= 11) {
            panel->time = GFX.funcs.getTime();
            panel->arrowFrame++;
            if (panel->arrowFrame >= 4) {
                panel->arrowFrame = 0;
            }
        }
        sprite.setClutRow(panel->arrowFrame);
    }
    if (panel->hasPrev) {
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x34, 0x1E, 0x98);
    }
    if (panel->hasNext) {
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x35, 0xFD, 0x98);
    }
    sprite.setClutRow(0);
    if (panel->active) {
        info = GET_ITEM[0](panel->items[panel->cursor]);
        if ((info->type == 25 || info->type == 26) && (*info->data & 1)) {
            sprite.setTexture(0x140, 0);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x40, (panel->cursor % 2) * 0x83 + 0x29,
                        (panel->cursor % 16) / 2 * 14 + 0x25);
        }
        first = panel->page * 16;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 2; j++) {
                if (panel->items[first + i * 2 + j]) {
                    sprite.setTexture(0x140, 0);
                    sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16),
                                ITEM_FUNCS->getCategory(panel->items[first + i * 2 + j]), j * 0x83 + 0x29,
                                i * 14 + 0x25);
                    sprite.setTexture(0x280, 0x100);
                    sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x31, j * 0x83 + 0x29, i * 14 + 0x25);
                }
            }
        }
    }
    if (panel->fades[1].level != 0x1000) {
        sprite.setScale(panel->fades[1].level, 0x1000, 0x1000);
        sprite.setPivot(0xC, 0x17);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x30, 0xC, 0x12);
    if (panel->fades[0].level != 0x1000) {
        sprite.setScale(0x1000, panel->fades[0].level, 0x1000);
        sprite.setPivot(0xA0, 0x60);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x2E, 0, 0x1E);
    if (panel->fades[2].level) {
        sprite.setLayerId(panel->layer, panel->depth - 2);
        if (panel->fades[2].level != 0x1000) {
            sprite.setScale(panel->fades[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x26);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x26, 0xA0, 0x12);
    }
}

void func_80092974(StatusPanel0 *panel, StatusPanel0Windows *windows) {
    s32 found;
    s32 last;
    s32 i;

    switch (panel->state) {
    case 0:
    default:
        panel->nextState(panel);
        func_80092B80(panel);
        if (panel->count / 16 != 0) {
            panel->pageCount = panel->count / 16 + ((panel->count & 15) != 0);
        } else {
            panel->pageCount = 1;
        }
        if (panel->unk60 != 0) {
            found = 0;
            for (i = 0; panel->items[i] != 0; i++) {
                if (panel->unk60 == panel->items[i]) {
                    panel->cursor = i;
                    panel->page = i / 16;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                last = panel->screen->unk7C;
                if (panel->items[last] > 0) {
                    panel->cursor = last;
                    panel->page = panel->screen->unk7C / 16;
                } else if (last - 1 > 0) {
                    panel->cursor = last - 1;
                    panel->page = (last - 1) / 16;
                }
            }
        }
        func_80091360(panel, windows);
        break;
    case 1:
        func_8009205C(panel, windows);
        func_80092440(panel);
        break;
    case 2:
    case 3:
        break;
    }
}

StatusPanel0 *func_80092B0C(StatusScreen0 *screen, s32 list, s32 arg2) {
    StatusPanel0 *panel = createTask(func_80092974, sizeof(StatusPanel0), sizeof(StatusPanel0Windows));

    panel->layer = 0x1000;
    panel->depth = 3;
    panel->screen = screen;
    if (arg2 != 0) {
        panel->unk60 = arg2;
    }
    panel->list = list;
    return panel;
}
