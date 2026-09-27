#include "stcrdabm.h"

extern s32 D_80085168[6];
extern CardAlbumFuncs D_80085180;

void initCardDrawer(CardDrawer *obj);
void func_800825A8(CardAlbumFader *fader);
void func_8008290C(CardAlbumGrid *grid, s32 previous);
s32 func_80082ECC(CardAlbumGrid *grid);
void func_80083820(CardAlbum *album, CardAlbumWindows *win, s32 show);
void func_80083C4C(CardAlbum *album);

void func_80082520(CardAlbumFader *fader, s32 fadeIn, s32 frames) {
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

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800825A8);

void func_800826EC(CardAlbumFader *fader) {
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
        func_800825A8(fader);
    case 3:
        break;
    }
}

CardAlbumFader *func_800827A0(void) {
    CardAlbumFader *fader = createTask(func_800826EC, sizeof(CardAlbumFader), 0);

    fader->start = func_80082520;
    fader->layer = 0x1000;
    fader->depth = 0;
    return fader;
}

void func_800827E4(CardAlbumGrid *grid) {
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

void func_800828AC(CardAlbumGrid *grid, s32 first) {
    grid->prevFirst = grid->first;
    grid->first = first;
    grid->turned = 0;
    grid->frame = 0;
    grid->setState(grid, 2);
}

void func_800828E4(CardAlbumGrid *grid) {
    grid->setSubstate(grid, 1);
}

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_8008290C);

void func_80082D54(CardAlbumGrid *grid) {
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

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082ECC);

void func_80082F18(CardAlbumGrid *grid) {
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

void func_80082FE0(CardAlbumGrid *grid) {
    switch (grid->state) {
    case 0:
    default:
        grid->nextState(grid);
        grid->first = 1;
        func_800828AC(grid, 1);
        break;
    case 1:
        func_80082F18(grid);
        func_8008290C(grid, 0);
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
            func_800827E4(grid);
            grid->shown = ALBUM_PAGE_CARDS;
            grid->time = GFX_FUNCS.getTime();
            grid->nextSubstate(grid);
            if (func_80082ECC(grid) != 0) {
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
        func_80082D54(grid);
        if (grid->substate < 3) {
            func_8008290C(grid, 1);
        } else {
            func_8008290C(grid, 0);
        }
        break;
    case 3:
        break;
    }
}

CardAlbumGrid *func_80083210(CardAlbum *album) {
    CardAlbumGrid *grid = createTask(func_80082FE0, sizeof(CardAlbumGrid), 0);

    grid->setPage = func_800828AC;
    grid->hide = func_800828E4;
    grid->layer = 0x1000;
    grid->depth = 6;
    grid->album = album;
    return grid;
}

Task *func_80084DB8(void);

void func_80083270(Task *task, Task **items) {
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
        items[0] = func_80084DB8();
        task->nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

Task *func_80083368(void) {
    return createTask(func_80083270, sizeof(Task), 4);
}

void func_80083394(CardAlbum *album, CardAlbumWindows *win) {
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

void func_800835AC(CardAlbum *album, CardAlbumWindows *win, s32 show) {
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

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083820);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083C4C);

void func_80084314(CardAlbum *album) {
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

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084384);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084C8C);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084DB8);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084DF4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084ED4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084FBC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80085050);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800850BC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800850FC);
