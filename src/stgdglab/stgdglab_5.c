#include "common.h"
#include "stgdglab.h"

/* Creates the panel's windows */
void func_8008D06C(LabPanel3 *panel, LabPanel3Windows *windows) {
    s32 i;
    TextWindow **items;

    windows->title = createTextWindow(panel->layer, 1, 0xAE, 0x15);
    for (i = 0; i < 3; i++) {
        windows->options[i] = createTextWindow(panel->layer, 1, 0xA7, i * 0xE + 0x31);
    }
    windows->unk10 = createTextWindow(panel->layer, 1, 0x5B, 0x6A);
    for (i = 0; i < 6; i++) {
        windows->values[i] = createTextWindow(panel->layer, 1, 0x7D, i * 0xE + 0x7F);
    }
    for (i = 0; i < 7; i++) {
        windows->values[i + 6] = createTextWindow(panel->layer, 1, 0xA7, i * 0xE + 0x7F);
    }
    windows->unk14 = createTextWindow(panel->layer, 1, 0xEB, 0x6A);
    windows->values[13] = createTextWindow(panel->layer, 1, 0x12D, 0x6A);
    for (i = 0; i < 6; i++) {
        windows->skills[i] = createTextWindow(panel->layer, 1, 0xC2, i * 0xE + 0x8B);
    }
    for (i = 0, items = panel->children; i < panel->childCount - 2; i++, items++) {
        if (*items != NULL) {
            (*items)->setDepth(*items, panel->depth - 1);
        }
    }
}

/* Shows the list of ids and the stats and skills of the one under the
   cursor; or hides the panel's windows */
void func_8008D25C(LabPanel3 *panel, LabPanel3Windows *windows, s32 show) {
    PartnerTotals totals;
    LabPartnerEntry entry;
    DigimonData *data;
    Partner *partner;
    TextWindow **items;
    s16 *stats;
    s32 id;
    s32 value;
    s32 i;

    if (show) {
        if (panel->count == 0) {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1E);
        } else {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1F);
        }
        partner = &GAME.partners[panel->unk54];
        for (i = 0; i < 3; i++) {
            id = panel->ids[panel->scroll + i];
            if (id < 3) {
                if (i == 0) {
                    windows->options[0]->setString(windows->options[0], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1B);
                } else {
                    windows->options[i]->setVisible(windows->options[i], 0);
                }
            } else {
                windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0x4F)),
                                               ON_PARTNER_ENTRY_ADDED(id)->nameId);
                if (partner->unk8 == id) {
                    windows->options[i]->setPalette(windows->options[i], 1);
                } else {
                    windows->options[i]->setPalette(windows->options[i], 0);
                }
            }
        }
        id = panel->ids[panel->scroll + panel->cursor];
        if (id != 0) {
            GAME.funcs.getPartnerEntry(panel->unk54, id, &entry);
            GAME.funcs.computeStats(panel->unk54, &totals);
            data = ON_PARTNER_ENTRY_ADDED(id);
            windows->unk10->setString(windows->unk10, FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
            windows->unk14->setString(windows->unk14, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x13);
            windows->values[13]->setNumber(windows->values[13], 0, entry.level);
            for (i = 0; i < 6; i++) {
                /* the match depends on indexing from &totals.stats[6] */
                value = (&totals.stats[6])[i] + data->battleStats[i];
                if (value >= 1000) {
                    value = 999;
                }
                windows->values[i]->setNumber(windows->values[i], 0, value);
                if ((i == 0 && totals.stats[19] != 0) || (i == 1 && totals.stats[20] != 0) ||
                    (i == 4 && totals.stats[21] != 0)) {
                    windows->values[i]->setPalette(windows->values[i], 6);
                }
            }
            stats = totals.stats;
            for (i = 0; i < 7; i++) {
                value = stats[i + 12] + data->resistances[i];
                if (value >= 1000) {
                    value = 999;
                }
                windows->values[i + 6]->setNumber(windows->values[i + 6], 0, value);
            }
            for (i = 0; i < 6; i++) {
                if (entry.skills[i] != 0) {
                    windows->skills[i]->setString(windows->skills[i], FILE_CACHE.load(TEXT_FILE(0xA3)),
                                                  entry.skills[i] & 0x1FFF);
                    if (entry.skills[i] & 0x8000) {
                        windows->skills[i]->setPalette(windows->skills[i], 3);
                    } else if (entry.skills[i] & 0x4000) {
                        windows->skills[i]->setPalette(windows->skills[i], 4);
                    } else {
                        windows->skills[i]->setPalette(windows->skills[i], 0);
                    }
                } else {
                    windows->skills[i]->setVisible(windows->skills[i], 0);
                }
            }
            for (i = 0; i < 14; i++) {
                windows->values[i]->setRightAlign(windows->values[i], 1);
            }
        } else {
            windows->unk10->setVisible(windows->unk10, 0);
            windows->unk14->setVisible(windows->unk14, 0);
            for (i = 0; i < 14; i++) {
                windows->values[i]->setVisible(windows->values[i], 0);
            }
        }
    } else {
        for (i = 0, items = panel->children; i < panel->childCount - 2; i++, items++) {
            if (*items != NULL) {
                (*items)->setVisible(*items, 0);
            }
        }
    }
}

void func_8008D80C(LabPanel3 *panel) {
    LabPanel3Windows *windows = panel->children;

    STGDGLAB_data.funcs.startFade(&panel->fade, 0);
    func_8008D25C(panel, windows, 0);
    windows->cursor->setVisible(windows->cursor, 0);
    panel->substate++;
}

/* The panel's states: fades in, moves the cursor through the ids and
   scrolls the list; triangle closes it */
void func_8008D884(LabPanel3 *panel, LabPanel3Windows *windows) {
    s32 cursor;
    s32 scroll;

    switch (panel->substate) {
    case 0:
    default:
        STGDGLAB_data.funcs.startFade(&panel->fade, 1);
        panel->substate++;
        break;
    case 1:
        if (STGDGLAB_data.funcs.updateFade(&panel->fade)) {
            func_8008D25C(panel, windows, 1);
            windows->cursor->setVisible(windows->cursor, 1);
            if (panel->count >= 4) {
                windows->scrollBar = STGDGLAB_createScrollBar();
                windows->scrollBar->setX(windows->scrollBar, 0x122, 0xC);
                windows->scrollBar->setRange(windows->scrollBar, 0x35, 0x55);
                windows->scrollBar->setCount(windows->scrollBar, 3, panel->count);
                windows->scrollBar->setPos(windows->scrollBar, panel->cursor);
            }
            panel->substate++;
        }
        break;
    case 2:
        if (panel->count > 0) {
            cursor = panel->cursor;
            scroll = panel->scroll;
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
                if (panel->count >= 3) {
                    panel->cursor++;
                    if (panel->cursor >= 3) {
                        panel->cursor = 2;
                        panel->scroll++;
                        if (panel->scroll > panel->count - 3) {
                            panel->scroll = panel->count - 3;
                        }
                    }
                } else {
                    panel->cursor++;
                    if (panel->cursor > panel->count - 1) {
                        panel->cursor = panel->count - 1;
                    }
                }
            }
#if VERSION_EU
            if (windows->scrollBar != NULL && scroll != panel->scroll) {
                windows->scrollBar->setPos(windows->scrollBar, panel->scroll);
            }
#endif
            if (cursor != panel->cursor || scroll != panel->scroll) {
                SOUND.playSound(0x8004513E);
                func_8008D25C(panel, windows, 1);
                windows->cursor->setPos(windows->cursor, 0x9A, panel->cursor * 0xE + 0x31);
#if VERSION_US
                if (windows->scrollBar != NULL) {
                    windows->scrollBar->setPos(windows->scrollBar, panel->cursor + panel->scroll);
                }
#endif
            }
        }
        if (panel->unk16C != 0 && PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            func_8008D80C(panel);
            if (windows->scrollBar != NULL) {
                windows->scrollBar->state = TASK_KILL;
            }
        }
        break;
    case 3:
        if (STGDGLAB_data.funcs.updateFade(&panel->fade)) {
            panel->setState(panel, TASK_KILL);
        }
        break;
    case 4:
        windows->cursor->setVisible(windows->cursor, 0);
        break;
    case 5:
        windows->cursor->setVisible(windows->cursor, 1);
        panel->substate = 2;
        break;
    }
    panel->unk60.level = panel->unk70.level = panel->fade.level;
}

/* Draws the panel's frames, its scroll arrows and the icons of the skills
   of the id under the cursor */
void func_8008DD30(LabPanel3 *panel, LabPanel3Windows *windows) {
    SpriteDrawer sprite;
    LabPartnerEntry entry;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    sprite.setLayerId(panel->layer, panel->depth);
    if (panel->unk60.level != 0x1000) {
        sprite.setScale(panel->unk60.level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x15);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x20, 0x92, 0xF);
    if (panel->unk70.level != 0x1000) {
        sprite.setScale(panel->unk70.level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x45);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    if (panel->unk70.level == 0x1000) {
        if (GFX.funcs.getTime() - panel->blinkTime >= 8) {
            panel->blinkTime = GFX.funcs.getTime();
            panel->blink = 1 - panel->blink;
        }
        if (panel->blink) {
            if (panel->scroll != 0) {
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x34, 0x123, 0x2D);
            }
            if (panel->scroll < panel->count - 3) {
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x35, 0x123, 0x55);
            }
        }
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x22, 0x92, 0x2A);
    if (panel->count > 0) {
        if (panel->fade.level != 0x1000) {
            sprite.setScale(panel->unk70.level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xA4);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x2A, 0x54, 0x64);
        sprite.setTexture(0x140, 0);
        sprite.setLayerId(panel->layer, panel->depth - 1);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x14, 0x5B, 0x7F);
        GAME.funcs.getPartnerEntry(panel->unk54, panel->ids[panel->scroll + panel->cursor], &entry);
        for (i = 0; i < 6; i++) {
            if (entry.skills[i] != 0) {
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16),
                            D_800427E8[(entry.skills[i] & 0x1FFF) - 1].icon + 0x37, 0xB4, i * 0xE + 0x8B);
            }
        }
    }
}

void func_8008E134(LabPanel3 *panel, LabPanel3Windows *windows) {
    s16 slots[4];
    s16 entries[44];
    s32 i;

    switch (panel->state) {
    case TASK_INIT:
    default:
        panel->nextState(panel);
        GAME.funcs.getPartnerSlots(panel->unk54, slots);
        for (i = 0; i < 3; i++) {
            if (slots[i] < 3) {
                break;
            }
            panel->ids[panel->count] = slots[i];
            panel->count++;
        }
        if (panel->unk50 != 0) {
            GAME.funcs.listPartnerEntries(panel->unk54, entries);
            for (i = 0; i < 44; i++) {
                if (entries[i] >= 3 && panel->ids[0] != entries[i] && panel->ids[1] != entries[i] &&
                    panel->ids[2] != entries[i]) {
                    panel->ids[panel->count] = entries[i];
                    panel->count++;
                }
            }
        }
        func_8008D06C(panel, windows);
        windows->cursor = createCursor(panel->layer, panel->depth - 1, 0x9A, panel->cursor * 0xE + 0x31);
        windows->cursor->setVisible(windows->cursor, 0);
        panel->unk60.duration = 10;
        panel->unk70.duration = 10;
        panel->fade.duration = 10;
        break;
    case TASK_RUN:
        func_8008D884(panel, windows);
        func_8008DD30(panel, windows);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

LabPanel3 *func_8008E320(s32 arg0, s32 arg1, s32 arg2) {
    LabPanel3 *panel = createTask(func_8008E134, sizeof(LabPanel3), 0x70);

    panel->close = func_8008D80C;
    panel->layer = 0x1000;
    panel->depth = 2;
    panel->unk50 = arg1;
    panel->unk54 = arg0;
    panel->unk16C = arg2;
    return panel;
}

void func_8008E394(Lab *lab, LabChildren *children) {
    switch (lab->substate) {
    case 0:
    default:
        if (children->menu == NULL) {
            children->menu = STGDGLAB_createMenu(lab);
        }
        lab->substate++;
        break;
    case 1:
        if (children->menu != NULL) {
            if (children->menu->picked != 0) {
                children->screen = STGDGLAB_screens[children->menu->choice](lab);
                lab->substate++;
            }
        } else {
            lab->substate = 3;
        }
        break;
    case 2:
        if (children->screen == NULL) {
            lab->substate = 1;
            children->menu->picked = 0;
        }
        break;
    case 3:
        if (children->fade->state == 2) {
            lab->setState(lab, TASK_KILL);
        }
        break;
    }
}

void STGDGLAB_packParty(Lab *lab) {
    s32 i;
    s32 j;

    lab->partyCount = 0;
    for (i = 0; i < 3; i++) {
        if (GAME.party[i] >= 0) {
            lab->partyCount++;
        }
    }
    for (i = 0; i < 3; i++) {
        if (GAME.party[i] < 0) {
            for (j = i; j < 3; j++) {
                if (GAME.party[j] >= 0) {
                    GAME.party[i] = GAME.party[j];
                    GAME.party[j] = -1;
                    break;
                }
            }
        }
    }
}

void STGDGLAB_updateLab(Lab *lab, LabChildren *children) {
    SpriteDrawer sprite;

    switch (lab->state) {
    case TASK_INIT:
    default:
        switch (lab->substate) {
        case 0:
        default:
            STGDGLAB_data.funcs.loadFiles();
            lab->substate++;
            break;
        case 1:
            if (STGDGLAB_data.funcs.filesLoading() == 0) {
                lab->nextState(lab);
                lab->unk5C = 3;
                STGDGLAB_packParty(lab);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_8008E394(lab, children);
        initSpriteDrawer(&sprite);
        sprite.setLayerId(lab->layer, 7);
        sprite.setTexture(0x280, 0x100);
        if (lab->blinkSkip != 0) {
            lab->blinkPos++;
            lab->blinkPos = lab->blinkPos < 0x60 ? lab->blinkPos : 0;
            lab->blinkSkip = 0;
        } else {
            lab->blinkSkip = 1;
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x37, lab->blinkPos, lab->blinkPos);
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        GAME.funcs.requestMode(GAME.fieldMode, 0);
        break;
    }
}

s32 func_8008E704(Lab *lab) {
    LabMenu *menu = ((LabChildren *)lab->children)->menu;

    if (menu != NULL && menu->state == TASK_RUN) {
        menu->open(menu);
        return 1;
    }
    return 0;
}

s32 func_8008E760(Lab *lab) {
    LabMenu *menu = ((LabChildren *)lab->children)->menu;

    if (menu != NULL && menu->state == TASK_RUN) {
        menu->close(menu);
        return 1;
    }
    return 0;
}

s32 func_8008E7BC(Lab *lab) {
    LabMenu *menu = ((LabChildren *)lab->children)->menu;

    if (menu != NULL && menu->state == TASK_RUN) {
        return 1;
    }
    return 0;
}

void func_8008E7F0(Lab *lab) {
    LabChildren *children = lab->children;

    children->fade = STGDGLAB_createFader();
    children->fade->start(children->fade, 0, 0x1E);
}

Lab *STGDGLAB_createLab(void) {
    Lab *lab = createTask(STGDGLAB_updateLab, sizeof(Lab), sizeof(LabChildren));

    lab->openMenu = func_8008E704;
    lab->closeMenu = func_8008E760;
    lab->menuOpen = func_8008E7BC;
    lab->packParty = STGDGLAB_packParty;
    lab->fadeOut = func_8008E7F0;
    lab->layer = 0x1000;
    return lab;
}

void STGDGLAB_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry((FILE_LAB_SPRITES + 1) << 16));
    loader.setImagePos(0x140, 0x100);
    loader.setClutPos(0x280, 0);
    loader.setBufferSize(0x10000);
    loader.loadArchive(FILE_CACHE.getEntry(((FILE_LAB_SPRITES + 1) << 16) + 2));
    FILE_CACHE.request(TEXT_FILE(0x3A));
    FILE_CACHE.request(TEXT_FILE(0x4F));
    FILE_CACHE.request(TEXT_FILE(0x48));
    FILE_CACHE.request(TEXT_FILE(0xA3));
    FILE_CACHE.request(TEXT_FILE(0x9C));
}

s32 STGDGLAB_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x3A)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x4F)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x48)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0xA3)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x9C)) != 0;
}

void STGDGLAB_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STGDGLAB_updateFade(PanelAnim *fade) {
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

void STGDGLAB_startLerp(LabLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STGDGLAB_updateLerp(LabLerp *lerp) {
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

s32 func_8008EBFC(s32 id) {
    s32 i;

    for (i = 0; D_8008EE4C[i].id != 0; i++) {
        if (D_8008EE4C[i].id == id) {
            return D_8008EE4C[i].a;
        }
    }
    return 0;
}

s32 func_8008EC48(s32 id) {
    s32 i;

    for (i = 0; D_8008EE4C[i].id != 0; i++) {
        if (D_8008EE4C[i].id == id) {
            return D_8008EE4C[i].b;
        }
    }
    return 0;
}
