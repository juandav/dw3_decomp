#include "common.h"
#include "stgdglab.h"

#define PAD_HELD(button) ((PAD.getHeld(0) >> PAD.getButtonBit(0, button)) & 1)

/* Creates the panel's windows and cursors */
void func_80084D5C(LabPanel1 *panel, LabPanel1Windows *windows) {
    s32 i;
    TextWindow **items;

    for (i = 0; i < 10; i++) {
        windows->entries[i] = createTextWindow(panel->layer, 1, (i % 2) * 0x85 + 0x27, (i / 2) * 0xE + 0x16);
    }
    windows->unk28 = createTextWindow(panel->layer, 1, 0x5B, 0x6A);
    windows->unk2C = createTextWindow(panel->layer, 1, 0xF5, 0x6A);
    windows->values[13] = createTextWindow(panel->layer, 1, 0x12D, 0x6A);
    for (i = 0; i < 6; i++) {
        windows->skills[i] = createTextWindow(panel->layer, 1, 0xC2, i * 0xE + 0x8B);
    }
    for (i = 0; i < 6; i++) {
        windows->values[i] = createTextWindow(panel->layer, 1, 0x7D, i * 0xE + 0x7F);
    }
    for (i = 0; i < 7; i++) {
        windows->values[i + 6] = createTextWindow(panel->layer, 1, 0xA7, i * 0xE + 0x7F);
    }
    for (i = 0, items = panel->children; i < panel->childCount - 3; i++, items++) {
        if (*items != NULL) {
            (*items)->setDepth(*items, panel->depth - 1);
        }
    }
    windows->cursor = createCursor(panel->layer, panel->depth - 1, 0x1A, 0x16);
    windows->cursor->setVisible(windows->cursor, 0);
    windows->optionCursor = createCursor(panel->layer, panel->depth - 3, 0x9A, 0x83);
    windows->optionCursor->setVisible(windows->optionCursor, 0);
    for (i = 0; i < 4; i++) {
        windows->options[i] = createTextWindow(panel->layer, 1, 0xA7, i * 0xE + 0x83);
    }
    windows->help = createTextWindow(panel->layer, 1, 0x14, 0xC3);
}

/* Shows the page of the partner's entries, and the stats and skills of the
   one under the cursor; or hides the panel's windows */
void func_8008501C(LabPanel1 *panel, LabPanel1Windows *windows, s32 show) {
    PartnerTotals totals;
    LabPartnerEntry entry;
    DigimonData *data;
    TextWindow **items;
    s32 id;
    s32 value;
    s32 i;
    s32 j;
    s16 *stats;

    if (show) {
        for (i = 0; i < 10; i++) {
            id = panel->entries[panel->scroll * 2 + i];
            if (id >= 3) {
                windows->entries[i]->setPalette(windows->entries[i], 0);
                for (j = 0; j < 3; j++) {
                    if (panel->slots[j] == id) {
                        windows->entries[i]->setPalette(windows->entries[i], 7);
                        break;
                    }
                }
                windows->entries[i]->setString(windows->entries[i], FILE_CACHE.load(TEXT_FILE(0x4F)),
                                               ON_PARTNER_ENTRY_ADDED(id)->nameId);
            } else {
                windows->entries[i]->setVisible(windows->entries[i], 0);
            }
        }
        id = panel->entries[(panel->scroll + panel->row) * 2 + panel->col];
        if (id != 0) {
            GAME.funcs.getPartnerEntry(panel->unk58, id, &entry);
            GAME.funcs.computeStats(panel->unk58, &totals);
            data = ON_PARTNER_ENTRY_ADDED(id);
            windows->unk28->setString(windows->unk28, FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
            windows->unk2C->setString(windows->unk2C, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x13);
            windows->values[13]->setNumber(windows->values[13], 0, entry.level);
            stats = totals.stats;
            for (i = 0; i < 6; i++) {
                value = stats[i + 6] + data->battleStats[i];
                if (value >= 1000) {
                    value = 999;
                }
                windows->values[i]->setNumber(windows->values[i], 0, value);
            }
            if (totals.stats[19] != 0) {
                windows->values[0]->setPalette(windows->values[0], 6);
            }
            if (totals.stats[20] != 0) {
                windows->values[1]->setPalette(windows->values[1], 6);
            }
            if (totals.stats[21] != 0) {
                windows->values[4]->setPalette(windows->values[4], 6);
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
        }
        windows->cursor->setVisible(windows->cursor, 1);
    } else {
        for (i = 0, items = panel->children; i < panel->childCount - 3; i++, items++) {
            if (*items != NULL) {
                (*items)->setVisible(*items, 0);
            }
        }
        windows->cursor->setVisible(windows->cursor, 0);
    }
}

/* Shows the panel's options (the names of its three slots, then two strings
   of file 0x3A), or hides them */
void func_80085524(LabPanel1 *panel, LabPanel1Windows *windows, s32 show) {
    s32 i;

    if (show) {
        for (i = 0; i < 3; i++) {
            windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0x4F)),
                                           ON_PARTNER_ENTRY_ADDED(panel->slots[i])->nameId);
        }
        windows->options[3]->setString(windows->options[3], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x2C);
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x2B);
    } else {
        for (i = 0; i < 4; i++) {
            windows->options[i]->setVisible(windows->options[i], 0);
        }
        windows->help->setVisible(windows->help, 0);
    }
}

/* The panel's task: lists the partner's entries two by two, with the
   shoulder buttons scrolling five rows at a time; cross puts the picked
   entry in the slot and, when the slot held the partner's current entry,
   asks for the new one; triangle closes it */
void func_8008568C(LabPanel1 *panel, LabPanel1Windows *windows) {
    SpriteDrawer sprite;
    LabPartnerEntry entry;
    Partner *partner;
    Partner *current;
    s32 scroll;
    s32 row;
    s32 moved;
    s32 rows;
    s32 old;
    s32 id;
    /* The match depends on the four loops having their own counters, and on
       the two Partner pointers being separate */
    s32 i;
    s32 j;
    s32 k;
    s32 n;

    switch (panel->state) {
    case TASK_INIT:
    default:
        panel->nextState(panel);
        panel->fades[0].duration = 10;
        STGDGLAB_data.funcs.startFade(panel->fades, 1);
        GAME.funcs.getPartnerSlots(panel->unk58, panel->slots);
        panel->entryCount = GAME.funcs.listPartnerEntries(panel->unk58, panel->entries);
        func_80084D5C(panel, windows);
        panel->fades[1].duration = 10;
        break;
    case TASK_RUN:
        switch (panel->substate) {
        case 0:
        default:
            if (STGDGLAB_data.funcs.updateFade(panel->fades)) {
                if (panel->step) {
                    panel->setState(panel, TASK_KILL);
                } else {
#if VERSION_US
                    if (panel->entryCount >= 11) {
                        windows->scrollBar = STGDGLAB_createScrollBar();
                        windows->scrollBar->setX(windows->scrollBar, 0x122, 0xC);
                        windows->scrollBar->setRange(windows->scrollBar, 0x1B, 0x55);
                        windows->scrollBar->setCount(windows->scrollBar, 10, panel->entryCount / 2);
                        windows->scrollBar->setPos(windows->scrollBar, 0);
                    }
#endif
                    func_8008501C(panel, windows, 1);
                    panel->substate++;
                }
            }
            break;
        case 1:
            scroll = panel->scroll;
            moved = 0;
            if (panel->entryCount >= 11) {
                if ((!PAD_HELD(PAD_R1) && PAD_PRESSED(PAD_L1)) || (!PAD_HELD(PAD_R1) && PAD_REPEATED(PAD_L1))) {
                    panel->scroll -= 5;
                    if (panel->scroll < 0) {
                        panel->scroll = 0;
                    }
                } else if ((!PAD_HELD(PAD_L1) && PAD_PRESSED(PAD_R1)) ||
                           (!PAD_HELD(PAD_L1) && PAD_REPEATED(PAD_R1))) {
                    rows = panel->entryCount - panel->entryCount / 2;
                    for (n = 0; n < 5; n++) {
                        panel->scroll++;
                        if (panel->scroll + 4 > rows - 1) {
                            panel->scroll = rows - 5;
                            break;
                        }
                    }
                }
                if (scroll != panel->scroll) {
                    moved = 1;
                    panel->row = 0;
                }
            }
            if (!moved) {
                row = panel->row;
                if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                    panel->row--;
                    if (panel->row < 0) {
                        panel->row = 0;
                        panel->scroll--;
                        if (panel->scroll < 0) {
                            panel->scroll = 0;
                        }
                    }
                    if (row != panel->row || scroll != panel->scroll) {
                        moved = 1;
                    }
                } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                    if (panel->entryCount >= 10) {
                        panel->row++;
                        if (panel->row >= 5) {
                            panel->row = 4;
                            panel->scroll++;
                            if (panel->scroll > panel->entryCount - panel->entryCount / 2 - 1) {
                                panel->scroll = panel->entryCount - panel->entryCount / 2 - 1;
                            }
                        }
                    } else {
                        panel->row++;
                        if (panel->row > panel->entryCount - panel->entryCount / 2 - 1) {
                            panel->row = panel->entryCount - panel->entryCount / 2 - 1;
                        }
                    }
                    if (scroll != panel->scroll || row != panel->row) {
                        if (panel->col != 0) {
                            if (panel->entries[(panel->scroll + panel->row) * 2 + panel->col] >= 3) {
                                moved = 1;
                            } else if (panel->entries[(panel->scroll + panel->row) * 2] >= 3) {
                                panel->col = 0;
                                moved = 1;
                            }
                        } else if (panel->entries[(panel->scroll + panel->row) * 2] >= 3) {
                            moved = 1;
                        }
                        if (!moved) {
                            panel->row = row;
                            panel->scroll = scroll;
                        }
                    }
                }
                if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
                    if (panel->col != 0) {
                        panel->col = 0;
                        moved = 1;
                    }
                } else if ((PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) && panel->col == 0 &&
                           panel->entries[(panel->scroll + panel->row) * 2 + 1] >= 3) {
                    panel->col = 1;
                    moved = 1;
                }
            }
            if (moved) {
                SOUND.playSound(0x8004513E);
                windows->cursor->setPos(windows->cursor, panel->col * 0x85 + 0x1A, panel->row * 0xE + 0x16);
                func_8008501C(panel, windows, 1);
#if VERSION_US
                if (windows->scrollBar != NULL) {
                    windows->scrollBar->setPos(windows->scrollBar, panel->scroll);
                }
#endif
            } else if (PAD_PRESSED(PAD_CROSS)) {
                id = panel->entries[(panel->scroll + panel->row) * 2 + panel->col];
                for (k = 0; k < 3; k++) {
                    if (panel->slots[k] == id) {
                        id = 0;
                        break;
                    }
                }
                if (id == 0) {
                    SOUND.playSound(0x800450BD);
                } else {
                    SOUND.playSound(0x8004503C);
                    current = &GAME.partners[panel->unk58];
                    if (panel->slots[panel->unk5C] == current->unk8) {
                        panel->substate = 2;
                    } else {
                        func_8008501C(panel, windows, 0);
                        STGDGLAB_data.funcs.startFade(panel->fades, 0);
                        panel->substate = 0;
                        panel->step = 1;
                    }
                    panel->slots[panel->unk5C] = id;
                    GAME.funcs.setPartnerSlots(panel->unk58, panel->slots);
#if VERSION_US
                    if (windows->scrollBar != NULL) {
                        windows->scrollBar->state = TASK_KILL;
                    }
#endif
                }
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                func_8008501C(panel, windows, 0);
                STGDGLAB_data.funcs.startFade(panel->fades, 0);
                panel->substate = 0;
                panel->step = 1;
#if VERSION_US
                if (windows->scrollBar != NULL) {
                    windows->scrollBar->state = TASK_KILL;
                }
#endif
            }
            break;
        case 2:
            panel->fades[1].duration = 10;
            STGDGLAB_data.funcs.startFade(&panel->fades[1], 1);
            windows->cursor->setPalette(windows->cursor, 7);
            windows->cursor->setStill(windows->cursor, 1);
            panel->substate++;
            break;
        case 3:
            if (STGDGLAB_data.funcs.updateFade(&panel->fades[1])) {
                func_80085524(panel, windows, 1);
                panel->unkFC = 0;
                windows->optionCursor->setPos(windows->optionCursor, 0x9A, 0x83);
                windows->optionCursor->setVisible(windows->optionCursor, 1);
                panel->substate++;
            }
            break;
        case 4:
            old = panel->unkFC;
            if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                panel->unkFC--;
                if (panel->unkFC < 0) {
                    panel->unkFC = 0;
                }
            } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                panel->unkFC++;
                if (panel->unkFC >= 4) {
                    panel->unkFC = 3;
                }
            }
            if (old != panel->unkFC) {
                SOUND.playSound(0x8004513E);
                windows->optionCursor->setPos(windows->optionCursor, 0x9A, panel->unkFC * 0xE + 0x83);
            }
            partner = &GAME.partners[panel->unk58];
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x8004503C);
                if (panel->unkFC < 3) {
                    partner->unk8 = panel->slots[panel->unkFC];
                } else {
                    partner->unk8 = 0;
                }
                panel->substate++;
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                partner->unk8 = 0;
                panel->substate++;
            }
            break;
        case 5:
            STGDGLAB_data.funcs.startFade(&panel->fades[1], 0);
            func_80085524(panel, windows, 0);
            windows->optionCursor->setVisible(windows->optionCursor, 0);
            panel->substate++;
            break;
        case 6:
            if (STGDGLAB_data.funcs.updateFade(&panel->fades[1])) {
                panel->substate = 0;
                panel->step = 1;
            }
            break;
        }
        initSpriteDrawer(&sprite);
        sprite.setLayerId(panel->layer, panel->depth);
        sprite.setTexture(0x280, 0x100);
        if (panel->fades[0].level != 0x1000) {
            sprite.setScale(panel->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x37);
        } else {
            for (j = 0; j < 10; j++) {
                if (panel->entries[panel->scroll * 2 + j] >= 3) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x3E, (j % 2) * 0x85 + 0x18,
                                (j / 2) * 0xE + 0x16);
                }
            }
        }
        if (GFX.funcs.getTime() - panel->blinkTime >= 8) {
            panel->blinkTime = GFX.funcs.getTime();
            panel->blink = 1 - panel->blink;
        }
        if (panel->fades[0].level == 0x1000 && panel->blink) {
            if (panel->scroll > 0) {
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x34, 0x123, 0x13);
            }
            if (panel->entryCount >= 10 && panel->scroll < panel->entryCount - panel->entryCount / 2 - 5) {
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x35, 0x123, 0x55);
            }
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x29, 0x12, 0xF);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x2A, 0x54, 0x64);
        sprite.setTexture(0x140, 0);
        sprite.setLayerId(panel->layer, panel->depth - 1);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x14, 0x5B, 0x7F);
        GAME.funcs.getPartnerEntry(panel->unk58, panel->entries[(panel->scroll + panel->row) * 2 + panel->col],
                                   &entry);
        for (i = 0; i < 6; i++) {
            if (entry.skills[i] != 0) {
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16),
                            D_800427E8[(entry.skills[i] & 0x1FFF) - 1].icon + 0x37, 0xB4, i * 0xE + 0x8B);
            }
        }
        if (panel->fades[1].level != 0) {
            initSpriteDrawer(&sprite);
            sprite.setLayerId(panel->layer, panel->depth - 2);
            sprite.setTexture(0x280, 0x100);
            if (panel->fades[1].level != 0x1000) {
                sprite.setScale(panel->fades[1].level, 0x1000, 0x1000);
                sprite.setPivot(0x140, 0x9D);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x2C, 0x95, 0x7C);
            if (panel->fades[1].level != 0x1000) {
                sprite.setPivot(0, 0xD0);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x2B, 0, 0xBF);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

LabPanel1 *func_800869A4(s32 arg0, s32 arg1) {
    LabPanel1 *panel = createTask(func_8008568C, sizeof(LabPanel1), 0xA0);

    panel->layer = 0x1000;
    panel->depth = 6;
    panel->unk58 = arg0;
    panel->unk5C = arg1;
    return panel;
}
