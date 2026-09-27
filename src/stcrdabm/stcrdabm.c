#include "stcrdabm.h"

extern s32 STCRDABM_cursorBlink[6];
extern CardAlbumFuncs STCRDABM_funcs;

void initCardDrawer(CardDrawer *obj);
void STCRDABM_drawFader(CardAlbumFader *fader);
void STCRDABM_drawCards(CardAlbumGrid *grid, s32 previous);
s32 STCRDABM_pageHasCards(CardAlbumGrid *grid);
void STCRDABM_showCardInfo(CardAlbum *album, CardAlbumWindows *win, s32 show);
void STCRDABM_drawAlbum(CardAlbum *album);

void STCRDABM_startFader(CardAlbumFader *fader, s32 fadeIn, s32 frames) {
    fader->setState(fader, 1);
    fader->substate = 1;
    fader->fadeIn = fadeIn;
    if (fadeIn == 0) {
        fader->level = 0;
        fader->levelStep = 0xFF00 / frames;
    } else {
        fader->level = 0xFF00;
        fader->levelStep = -(0xFF00 / frames);
    }
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", STCRDABM_drawFader);

void STCRDABM_updateFader(CardAlbumFader *fader) {
    switch (fader->state) {
    case 0:
    default:
        fader->nextState(fader);
        break;
    case 1:
        if (fader->substate == 0) {
            break;
        }
        fader->level += fader->levelStep;
        if (fader->fadeIn == 0) {
            if (fader->level > 0xFF00) {
                fader->level = 0xFF00;
                fader->state = 2;
            }
        } else if (fader->level < 0) {
            fader->level = 0;
            fader->state = 2;
        }
    case 2:
        STCRDABM_drawFader(fader);
    case 3:
        break;
    }
}

CardAlbumFader *STCRDABM_createFader(void) {
    CardAlbumFader *fader = createTask(STCRDABM_updateFader, sizeof(CardAlbumFader), 0);

    fader->start = STCRDABM_startFader;
    fader->layer = 0x1000;
    fader->depth = 0;
    return fader;
}

void STCRDABM_loadIcons(CardAlbumGrid *grid) {
    CardDrawer icon;
    s32 card;
    s32 col;
    s32 row;

    initCardDrawer(&icon);
    icon.setImagePos(0x140, 0x100);
    icon.setClutPos(0x300, 0x100);
    card = grid->first;
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 6 && card < CARD_COUNT; col++) {
            icon.setCard(card++);
            icon.setCell(col, row);
            icon.loadImage();
        }
    }
}

void STCRDABM_setPage(CardAlbumGrid *grid, s32 first) {
    grid->prevFirst = grid->first;
    grid->first = first;
    grid->turned = 0;
    grid->frame = 0;
    grid->setState(grid, 2);
}

void STCRDABM_hideCards(CardAlbumGrid *grid) {
    grid->setSubstate(grid, 1);
}

void STCRDABM_drawCards(CardAlbumGrid *grid, s32 previous) {
    SpriteDrawer sprite;
    CardDrawer icon;
    s32 digits[5];
    s32 i;
    s32 j;
    s32 card;
    s32 col;
    s32 row;
    s32 x;
    s32 y;
    s32 value;
    s32 dx;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(grid->layer, grid->depth);
    sprite.setTexture(0x280, 0);
    initCardDrawer(&icon);
    icon.setImagePos(0x140, 0x100);
    icon.setClutPos(0x300, 0x100);
    icon.setLayer(grid->layer, grid->depth);
    for (i = 0; i < grid->shown; i++) {
        if (previous != 0) {
            card = grid->prevFirst + i;
        } else {
            card = grid->first + i;
        }
        if (card >= CARD_COUNT) {
            break;
        }
        col = i % 6;
        row = i / 6;
        x = col * 42;
        y = row * 54;
        if (GAME.cardsSeen[card] != 0) {
            icon.setCard(card);
            icon.setCell(col, row);
            icon.draw(x + 0x27, y + 0x34);
            if (icon.getKind() != 0) {
                sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0x1D, x + 0x27, y + 0x53);
            } else {
                value = icon.card[1];
                j = value / 10;
                if (j != 0) {
                    digits[0] = j + 0x1E;
                } else {
                    digits[0] = 0;
                }
                j = value % 10;
                digits[1] = j + 0x1E;
                digits[2] = 0x1C;
                for (j = 0, dx = 0x27; j < 3; j++, dx += 7) {
                    if (digits[j] != 0) {
                        sprite.draw(FILE_CACHE.getEntry(0x05F50000), digits[j], x + dx, y + 0x53);
                    }
                }
                value = icon.card[2];
                j = value / 10;
                if (j != 0) {
                    digits[0] = j + 0x1E;
                } else {
                    digits[0] = 0;
                }
                j = value % 10;
                digits[1] = j + 0x1E;
                for (j = 0, dx = 0x3A; j < 2; j++, dx += 7) {
                    if (digits[j] != 0) {
                        sprite.draw(FILE_CACHE.getEntry(0x05F50000), digits[j], x + dx, y + 0x53);
                    }
                }
            }
            sprite.draw(FILE_CACHE.getEntry(0x05F50000), icon.card[0] - 1, x + 0x23, y + 0x32);
        } else {
            sprite.draw(FILE_CACHE.getEntry(0x05F50000), 6, x + 0x23, y + 0x32);
        }
    }
}

void STCRDABM_drawTurningSlots(CardAlbumGrid *grid) {
    SpriteDrawer sprite;
    s32 i;
    s32 card;
    s32 col;
    s32 row;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(grid->layer, grid->depth - 1);
    sprite.setTexture(0x280, 0);
    for (i = 0; i < grid->turned; i++) {
        card = grid->first + i;
        col = i % 6;
        row = i / 6;
        if (GAME.cardsSeen[card] != 0 || card >= CARD_COUNT) {
            sprite.setClutRow(grid->frame);
        } else {
            sprite.setClutRow(0);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 6, col * 42 + 0x23, row * 54 + 0x32);
    }
}

s32 STCRDABM_pageHasCards(CardAlbumGrid *grid) {
    s32 card;
    s32 i;

    for (i = 0; i < ALBUM_PAGE_CARDS; i++) {
        card = grid->first + i;
        if (GAME.cardsSeen[card] != 0 || card >= CARD_COUNT) {
            return 1;
        }
    }
    return 0;
}

void STCRDABM_updateHiding(CardAlbumGrid *grid) {
    switch (grid->substate) {
    case 0:
        break;
    case 1:
        if (grid->shown != 0) {
            grid->shown--;
            grid->nextSubstate(grid);
            grid->counter = GFX_FUNCS.getTime();
        } else {
            grid->state = 3;
        }
        break;
    case 2:
        if (GFX_FUNCS.getTime() - grid->counter >= 2) {
            grid->substate = 1;
        }
        break;
    }
}

void STCRDABM_updateGrid(CardAlbumGrid *grid) {
    switch (grid->state) {
    case 0:
    default:
        grid->nextState(grid);
        grid->first = 1;
        STCRDABM_setPage(grid, 1);
        break;
    case 1:
        STCRDABM_updateHiding(grid);
        STCRDABM_drawCards(grid, 0);
        break;
    case 2:
        switch (grid->substate) {
        case 0:
        default:
            if (++grid->turned < ALBUM_PAGE_CARDS) {
                grid->nextSubstate(grid);
                grid->counter = GFX_FUNCS.getTime();
            } else {
                grid->turned = ALBUM_PAGE_CARDS;
                grid->substate = 2;
            }
            break;
        case 1:
            if (GFX_FUNCS.getTime() - grid->counter >= 2) {
                grid->substate = grid->step;
            }
            break;
        case 2:
            STCRDABM_loadIcons(grid);
            grid->shown = ALBUM_PAGE_CARDS;
            grid->time = GFX_FUNCS.getTime();
            grid->nextSubstate(grid);
            if (STCRDABM_pageHasCards(grid) != 0) {
                SOUND_STATE.playSound(0x4001C);
            }
            break;
        case 3:
            if (GFX.funcs.getTime() - grid->time >= 2) {
                grid->time = GFX.funcs.getTime();
                if (++grid->frame >= 11) {
                    grid->state = 1;
                }
            }
            break;
        }
        STCRDABM_drawTurningSlots(grid);
        if (grid->substate < 3) {
            STCRDABM_drawCards(grid, 1);
        } else {
            STCRDABM_drawCards(grid, 0);
        }
        break;
    case 3:
        break;
    }
}

CardAlbumGrid *STCRDABM_createGrid(CardAlbum *album) {
    CardAlbumGrid *grid = createTask(STCRDABM_updateGrid, sizeof(CardAlbumGrid), 0);

    grid->setPage = STCRDABM_setPage;
    grid->hide = STCRDABM_hideCards;
    grid->layer = 0x1000;
    grid->depth = 6;
    grid->album = album;
    return grid;
}

Task *STCRDABM_createAlbum(void);

void STCRDABM_updateScene(Task *task, Task **items) {
    RECT rect;
    Layer *res;

    switch (task->state) {
    case 0:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0xF000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        res = GFX.funcs.createLayer(&rect, 3, 0x1000);
        res->setBgColor(res, 0, 0, 0);
        items[0] = STCRDABM_createAlbum();
        task->nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

Task *STCRDABM_start(void) {
    return createTask(STCRDABM_updateScene, sizeof(Task), 4);
}

void STCRDABM_createWindows(CardAlbum *album, CardAlbumWindows *win) {
    TextWindow **items;
    s32 i;

    win->title = createTextWindow(album->layer, 1, 0x10, 0x19);
    win->help = createTextWindow(album->layer, 1, 0xD0, 0x19);
    win->page = createTextWindow(album->layer, 1, 0x34, 0x9E);
    win->pageSlash = createTextWindow(album->layer, 1, 0x35, 0x9E);
    win->pageCount = createTextWindow(album->layer, 1, 0x4A, 0x9E);
    win->prev = createTextWindow(album->layer, 1, 0x12, 0x6C);
    win->next = createTextWindow(album->layer, 1, 0x121, 0x6C);
    win->name = createTextWindow(album->layer, 1, 0x88, 0xA1);
    win->levelLabel = createTextWindow(album->layer, 1, 0x115, 0xA1);
    win->level = createTextWindow(album->layer, 1, 0x126, 0xA1);
    win->countLabel = createTextWindow(album->layer, 1, 0x115, 0xC7);
    win->count = createTextWindow(album->layer, 1, 0x12C, 0xC7);
    win->text = createTextWindow(album->layer, 1, 0x50, 0xB8);
    win->stat1Label = createTextWindow(album->layer, 1, 0xCE, 0xB8);
    win->stat1 = createTextWindow(album->layer, 1, 0xF0, 0xB8);
    win->stat2Label = createTextWindow(album->layer, 1, 0xCE, 0xC5);
    win->stat2 = createTextWindow(album->layer, 1, 0xF0, 0xC5);
    for (i = 0, items = album->children; i < album->childCount - 2; i++, items++) {
        (*items)->setDepth(*items, album->depth - 3);
    }
}

void STCRDABM_showPageInfo(CardAlbum *album, CardAlbumWindows *win, s32 show) {
    if (show != 0) {
        win->title->setString(win->title, FILE_CACHE.load(0x25), 1);
        win->help->setString(win->help, FILE_CACHE.load(0x25), 2);
        win->page->setNumber(win->page, 0, album->page + 1);
        win->page->setRightAlign(win->page, 1);
        win->pageSlash->setString(win->pageSlash, FILE_CACHE.load(0x25), 5);
        win->pageCount->setNumber(win->pageCount, 0, album->pageCount);
        win->pageCount->setRightAlign(win->pageCount, 1);
        if (album->active != 0) {
            if (album->page > 0) {
                win->prev->setString(win->prev, FILE_CACHE.load(0x25), 3);
            } else {
                win->prev->setVisible(win->prev, 0);
            }
            if (album->page < album->pageCount - 1) {
                win->next->setString(win->next, FILE_CACHE_LOAD[0](0x25), 4);
            } else {
                win->next->setVisible(win->next, 0);
            }
        }
    } else {
        win->title->setVisible(win->title, 0);
        win->help->setVisible(win->help, 0);
        win->page->setVisible(win->page, 0);
        win->pageSlash->setVisible(win->pageSlash, 0);
        win->pageCount->setVisible(win->pageCount, 0);
        win->prev->setVisible(win->prev, 0);
        win->next->setVisible(win->next, 0);
    }
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", STCRDABM_showCardInfo);

void STCRDABM_drawAlbum(CardAlbum *album) {
    SpriteDrawer sprite;
    CardDrawer icon;
    s32 kind;
    s32 frame;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0);
    sprite.setLayerId(album->layer, album->depth);
    if (album->frameToggle != 0) {
        album->frame = ++album->frame < 0x60 ? album->frame : 0;
        album->frameToggle = 0;
    } else {
        album->frameToggle = 1;
    }
    sprite.draw(FILE_CACHE.getEntry(0x05F50000), 8, album->frame, album->frame);
    sprite.setLayerId(album->layer, album->depth - 2);
    if (album->fade.level != 0) {
        if (album->fade.level != 0x1000) {
            sprite.setScale(album->fade.level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x20);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 9, 0, 0x15);
        if (album->fade.level != 0x1000) {
            sprite.setPivot(0x140, 0x20);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xF, 0xC8, 0x15);
        if (album->fade.level != 0x1000) {
            sprite.setScale(album->fade.level, album->fade.level, 0x1000);
            sprite.setPivot(0x3A, 0xA5);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xE, 0x22, 0x9A);
    }
    if (album->active != 0) {
        if (album->pageCount >= 2) {
            if (GFX.funcs.getTime() - album->blinkTime > 0x10) {
                album->blinkTime = GFX.funcs.getTime();
                album->blink = 1 - album->blink;
            }
            if (album->blink != 0) {
                if (album->page > 0) {
                    sprite.draw(FILE_CACHE_GET_ENTRY[0](0x05F50000), 0x1A, 0xE, 0x5A);
                }
                if (album->page < album->pageCount - 1) {
                    sprite.draw(FILE_CACHE_GET_ENTRY[0](0x05F50000), 0x1B, 0x121, 0x5A);
                }
            }
        }
        if (album->pageHasCards != 0) {
            if (GFX.funcs.getTime() - album->cursorTime > 0x10) {
                album->cursorTime = GFX.funcs.getTime();
                if (++album->cursorFrame >= 6) {
                    album->cursorFrame = 0;
                }
            }
            sprite.setClutRow(STCRDABM_cursorBlink[album->cursorFrame]);
            sprite.draw(FILE_CACHE_GET_ENTRY[0](0x05F50000), 7, album->slot % 6 * 42 + 0x24, album->slot / 6 * 54 + 0x32);
            sprite.setClutRow(0);
        }
    }
    if (album->infoFade.level != 0) {
        initCardDrawer(&icon);
        icon.setCard(album->card);
        if (album->infoFade.level != 0x1000) {
            sprite.setScale(album->infoFade.level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xA8);
        }
        kind = icon.getKind();
        if (kind == 1) {
            frame = 0x12;
        } else if (kind == 2) {
            frame = 0x13;
        } else {
            frame = icon.card[0] + 0x13;
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), frame, 0x103, 0x9F);
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xD, 0xFC, 0x9D);
        if (album->infoFade.level != 0x1000) {
            sprite.setPivot(0x140, 0xA8);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xA, 0x82, 0x9D);
        if (album->infoFade.level != 0x1000) {
            sprite.setPivot(0x140, 0xD0);
        }
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0x10, 0x103, 0xC5);
        sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xD, 0xFC, 0xC3);
        if (album->infoFade.level != 0x1000) {
            sprite.setPivot(0x140, 0xC6);
        }
        if (kind != 0) {
            sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xB, 0x4A, 0xB3);
        } else if (album->card == 0x45 || album->card == 0x70 || album->card == 0x9B || album->card == 0xC6 ||
                   album->card == 0xF1) {
            sprite.draw(FILE_CACHE_GET_ENTRY[0](0x05F50000), 0xB, 0x4A, 0xB3);
        } else {
            sprite.draw(FILE_CACHE.getEntry(0x05F50000), 0xC, 0xC7, 0xB3);
        }
    }
}

void STCRDABM_findPageCards(CardAlbum *album) {
    s32 i;
    s32 card;

    album->pageHasCards = 0;
    card = album->page * ALBUM_PAGE_CARDS;
    for (i = 0; i < ALBUM_PAGE_CARDS; i++) {
        card++;
        if (card < CARD_COUNT && GAME.cardsSeen[card] != 0) {
            album->slotHasCard[i] = 1;
            album->pageHasCards = 1;
        } else {
            album->slotHasCard[i] = 0;
        }
    }
}

void STCRDABM_runAlbum(CardAlbum *album, CardAlbumWindows *win) {
    s32 prev;
    s32 slot;
    s32 i;

    switch (album->substate) {
    case 0:
    default:
        STCRDABM_funcs.startFade(&album->fade, 1);
        STCRDABM_findPageCards(album);
        win->grid = STCRDABM_createGrid(album);
        album->substate++;
        break;
    case 1:
        if (STCRDABM_funcs.updateFade(&album->fade) != 0) {
            STCRDABM_showPageInfo(album, win, 1);
            if (album->pageHasCards != 0) {
                STCRDABM_funcs.startFade(&album->infoFade, 1);
            }
            album->substate = 11;
        }
        break;
    case 3:
        album->active = 1;
        album->substate++;
        break;
    case 4:
        prev = album->page;
        if ((!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) &&
             ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_L1)) & 1)) ||
            (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) &&
             ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_L1)) & 1))) {
            if (--album->page < 0) {
                album->page = 0;
            }
        } else if ((!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) &&
                    ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_R1)) & 1)) ||
                   (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) &&
                    ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_R1)) & 1))) {
            if (++album->page > album->pageCount - 1) {
                album->page = album->pageCount - 1;
            }
        }
        if (prev != album->page) {
            SOUND_STATE.playSound(0x4001B);
            album->active = 0;
            album->slot = 0;
            STCRDABM_findPageCards(album);
            STCRDABM_showPageInfo(album, win, 1);
            if (album->infoFade.level == 0) {
                if (album->pageHasCards != 0) {
                    album->substate = 10;
                    album->step = 1;
                    win->grid->setPage(win->grid, album->page * ALBUM_PAGE_CARDS | 1);
                } else {
                    album->substate = 15;
                }
            } else {
                win->grid->setPage(win->grid, album->page * ALBUM_PAGE_CARDS | 1);
                if (album->pageHasCards == 0) {
                    album->substate = 10;
                    album->step = 0;
                } else {
                    album->substate = 15;
                }
            }
        } else {
            slot = album->slot;
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) {
                if (album->slot >= 6) {
                    album->slot -= 6;
                }
            } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) {
                if (album->slot < 6) {
                    album->slot += 6;
                }
            }
            if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1) ||
                ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1)) {
                if (--album->slot < 0) {
                    album->slot = 0;
                }
            } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1) ||
                       ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1)) {
                if (++album->slot >= ALBUM_PAGE_CARDS) {
                    album->slot = ALBUM_PAGE_CARDS - 1;
                }
            }
            if (album->page * ALBUM_PAGE_CARDS + album->slot >= CARD_COUNT - 1) {
                album->slot = CARD_COUNT - 2 - album->page * ALBUM_PAGE_CARDS;
            }
            if (slot != album->slot) {
                i = album->slot;
                album->slot = -1;
                if (i < slot) {
                    for (; i >= 0; i--) {
                        if (album->slotHasCard[i] != 0) {
                            album->slot = i;
                            break;
                        }
                    }
                } else if (slot < i) {
                    for (; i < ALBUM_PAGE_CARDS; i++) {
                        if (album->slotHasCard[i] != 0) {
                            album->slot = i;
                            break;
                        }
                    }
                }
                if (album->slot == -1) {
                    album->slot = slot;
                } else {
                    STCRDABM_showCardInfo(album, win, 1);
                    SOUND_STATE.playSound(0x4001B);
                }
            }
        }
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            SOUND_STATE.playSound(0x800450BD);
            album->active = 0;
            album->substate = 50;
            win->fader = STCRDABM_createFader();
            win->fader->start(win->fader, 0, 10);
        }
        break;
    case 10:
        if (album->step == 0) {
            STCRDABM_showCardInfo(album, win, 0);
        }
        STCRDABM_funcs.startFade(&album->infoFade, album->step);
        album->nextSubstate(album);
        break;
    case 11:
        if (STCRDABM_funcs.updateFade(&album->infoFade) != 0) {
            album->substate = 15;
        }
        break;
    case 15:
        if (win->grid->state == 1) {
            album->active = win->grid->state;
            STCRDABM_showPageInfo(album, win, 1);
            if (album->infoFade.level != 0) {
                while (1) {
                    if (album->slotHasCard[album->slot] != 0) {
                        break;
                    }
                    album->slot++;
                }
                STCRDABM_showCardInfo(album, win, 1);
            }
            album->substate = 3;
        }
        break;
    case 50:
        if (win->fader->state == 2) {
            album->state = 3;
        }
        break;
    case 51:
        if (STCRDABM_funcs.updateFade(&album->infoFade) != 0) {
            STCRDABM_showPageInfo(album, win, 0);
            STCRDABM_funcs.startFade(&album->fade, 0);
            album->substate++;
        }
        break;
    case 52:
        if (STCRDABM_funcs.updateFade(&album->fade) != 0) {
            album->substate++;
        }
        break;
    case 53:
        if (win->grid == NULL) {
            album->setState(album, 3);
        }
        break;
    }
}

void STCRDABM_updateAlbum(CardAlbum *album, CardAlbumWindows *win) {
    switch (album->state) {
    case 0:
    default:
        switch (album->substate) {
        case 0:
        default:
            STCRDABM_funcs.loadFiles();
            album->substate++;
            break;
        case 1:
            if (STCRDABM_funcs.filesLoading() == 0) {
                STCRDABM_createWindows(album, win);
                album->fade.duration = 8;
                album->infoFade.duration = 8;
                album->pageCount = 27;
                album->card = 1;
                album->nextState(album);
            }
            break;
        }
        break;
    case 1:
        STCRDABM_runAlbum(album, win);
        STCRDABM_drawAlbum(album);
        break;
    case 2:
        break;
    case 3:
        GAME.funcs.requestMode(GAME.funcs.getPrevMode(), 0);
        break;
    }
}

Task *STCRDABM_createAlbum(void) {
    CardAlbum *album = createTask(STCRDABM_updateAlbum, sizeof(CardAlbum), sizeof(CardAlbumWindows));

    album->layer = 0x1000;
    album->depth = 7;
    return (Task *)album;
}

void STCRDABM_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0);
    loader.loadArchive(FILE_CACHE.getEntry(0x05F60000));
    FILE_CACHE.request(0x7E7);
    FILE_CACHE.request(0x7E8);
    FILE_CACHE.request(0x7E9);
    FILE_CACHE.request(0x7EA);
    FILE_CACHE.request(0x7EB);
    FILE_CACHE.request(0x17);
    FILE_CACHE.request(0x1E);
    FILE_CACHE.request(0x25);
}

s32 STCRDABM_filesLoading(void) {
    if (FILE_CACHE.isLoading(0x7E7) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x7E8) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x7E9) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x7EA) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x7EB) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x17) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x1E) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(0x25) != 0;
}

void STCRDABM_startFade(PanelAnim *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn != 0) {
        SOUND_STATE.playSound(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        SOUND_STATE.playSound(0x4001A);
        fade->level = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

s32 STCRDABM_updateFade(PanelAnim *fade) {
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

void STCRDABM_startLerp(CardAlbumLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", STCRDABM_updateLerp);
