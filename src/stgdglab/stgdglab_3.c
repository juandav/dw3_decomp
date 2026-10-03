#include "common.h"
#include "stgdglab.h"

/* Creates the second screen's windows and cursor */
void func_800869FC(LabScreen2 *screen, LabScreen2Windows *windows) {
    s32 i;
    TextWindow **items;

    windows->title = createTextWindow(screen->layer, 1, 0xAE, 0x57);
    for (i = 0; i < 3; i++) {
        windows->unk38[i] = createTextWindow(screen->layer, 1, 0xA7, i * 0xE + 0x16);
    }
    for (i = 0; i < 2; i++) {
        windows->options[i] = createTextWindow(screen->layer, 1, 0xA7, i * 0xE + 0x73);
    }
    for (i = 0; i < 6; i++) {
        windows->list[i] = createTextWindow(screen->layer, 1, 0x32, i * 0xE + 0x4F);
    }
    for (i = 0; i < 7; i++) {
        windows->list[i + 6] = createTextWindow(screen->layer, 1, 0x5B, i * 0xE + 0x4F);
    }
    for (i = 0, items = screen->children; i < screen->childCount - 4; i++, items++) {
        if (*items != NULL) {
            (*items)->setDepth(*items, screen->depth - 1);
        }
    }
    windows->cursor = createCursor(screen->layer, screen->depth - 1, 0x9A, 0x73);
    windows->cursor->setVisible(windows->cursor, 0);
}

/* Shows the party member's slots and stats, or hides the screen's windows */
void func_80086BD4(LabScreen2 *screen, LabScreen2Windows *windows, s32 show) {
    PartnerTotals totals;
    TextWindow **items;
    Partner *partner;
    s32 member;
    s32 value;
    s32 i;
    s16 *stats;

    if (show) {
        member = GAME.funcs.getPartyMember(screen->lab->unk64);
        GAME.funcs.computeStats(member, &totals);
        partner = &GAME.partners[member];
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x3A)), 1);
        for (i = 0; i < 3; i++) {
            if (screen->slots[i] < 2) {
                if (i == 0) {
                    windows->unk38[0]->setString(windows->unk38[0], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1B);
                } else {
                    windows->unk38[i]->setVisible(windows->unk38[i], 0);
                }
            } else {
                windows->unk38[i]->setString(windows->unk38[i], FILE_CACHE.load(TEXT_FILE(0x4F)),
                                             ON_PARTNER_ENTRY_ADDED(screen->slots[i])->nameId);
                if (partner->unk8 == screen->slots[i]) {
                    windows->unk38[i]->setPalette(windows->unk38[i], 1);
                } else {
                    windows->unk38[i]->setPalette(windows->unk38[i], 0);
                }
            }
        }
        for (i = 0; i < 2; i++) {
            windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0x3A)), i + 0x21);
        }
        stats = totals.stats;
        for (i = 0; i < 13; i++) {
            value = stats[i + 6];
            if (value >= 1000) {
                value = 999;
            }
            windows->list[i]->setNumber(windows->list[i], 0, value);
        }
        if (totals.stats[19] != 0) {
            windows->list[0]->setPalette(windows->list[0], 6);
        }
        if (totals.stats[20] != 0) {
            windows->list[1]->setPalette(windows->list[1], 6);
        }
        if (totals.stats[21] != 0) {
            windows->list[4]->setPalette(windows->list[4], 6);
        }
        for (i = 0; i < 13; i++) {
            windows->list[i]->setRightAlign(windows->list[i], 1);
        }
        windows->cursor->setVisible(windows->cursor, 1);
    } else {
        for (i = 0, items = screen->children; i < screen->childCount - 4; i++, items++) {
            if (*items != NULL) {
                (*items)->setVisible(*items, 0);
            }
        }
        windows->cursor->setVisible(windows->cursor, 0);
    }
}

/* The second screen's states: picks between the entries and the skills,
   opens the list of the member's entries and then the picked one's panel */
void func_80086F6C(LabScreen2 *screen, LabScreen2Windows *windows) {
    s16 slots[4];
    LabPartnerEntry entry;
    s32 member;
    s32 found;
    s32 old;
    s32 i;

    switch (screen->substate) {
    case 0:
    default:
        member = GAME.funcs.getPartyMember(screen->lab->unk64);
        GAME.funcs.getPartnerSlots(member, screen->slots);
        screen->entryCount = GAME.funcs.listPartnerEntries(member, screen->entries);
        STGDGLAB_data.funcs.startFade(&screen->panels[0], 1);
        STGDGLAB_data.funcs.startFade(&screen->panels[1], 1);
        STGDGLAB_data.funcs.startFade(&screen->panels[2], 1);
        STGDGLAB_data.funcs.startFade(&screen->panels[3], 1);
        screen->substate++;
        break;
    case 1:
        STGDGLAB_data.funcs.updateFade(&screen->panels[0]);
        STGDGLAB_data.funcs.updateFade(&screen->panels[1]);
        STGDGLAB_data.funcs.updateFade(&screen->panels[2]);
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[3])) {
            func_80086BD4(screen, windows, 1);
            screen->substate++;
        }
        break;
    case 2:
        old = screen->choice;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->choice--;
            if (screen->choice < 0) {
                screen->choice = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->choice++;
            if (screen->choice >= 2) {
                screen->choice = 1;
            }
        }
        if (old != screen->choice) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0x9A, screen->choice * 0xE + 0x72);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if ((screen->choice == 0 && screen->entryCount < 4) || (screen->choice == 1 && screen->entryCount == 0)) {
                screen->setSubstate(screen, 30);
                STGDGLAB_data.funcs.startFade(&screen->panels[4], 1);
                windows->cursor->setVisible(windows->cursor, 0);
            } else {
                screen->step = 0;
                screen->substate++;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->step = 1;
            screen->substate++;
        }
        break;
    case 3:
        STGDGLAB_data.funcs.startFade(&screen->panels[0], 0);
        STGDGLAB_data.funcs.startFade(&screen->panels[1], 0);
        STGDGLAB_data.funcs.startFade(&screen->panels[2], 0);
        STGDGLAB_data.funcs.startFade(&screen->panels[3], 0);
        func_80086BD4(screen, windows, 0);
        screen->substate++;
        break;
    case 4:
        STGDGLAB_data.funcs.updateFade(&screen->panels[0]);
        STGDGLAB_data.funcs.updateFade(&screen->panels[1]);
        STGDGLAB_data.funcs.updateFade(&screen->panels[2]);
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[3])) {
            if (screen->step == 0) {
                screen->picked = 0;
                screen->setSubstate(screen, 40);
                switch (screen->choice) {
                case 0:
                default:
                    screen->step = 10;
                    break;
                case 1:
                    screen->step = 20;
                    break;
                case 2:
                    screen->setState(screen, TASK_KILL);
                    break;
                }
            } else {
                screen->setState(screen, TASK_KILL);
            }
        }
        break;
    case 40:
        if (windows->entryList == NULL) {
            windows->entryList = func_8008E320(GAME.funcs.getPartyMember(screen->lab->unk64), 0, 0);
        }
        windows->entryList->cursor = screen->picked;
        screen->substate++;
        break;
    case 41:
        if (windows->entryList == NULL || windows->entryList->substate >= 2) {
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x8004503C);
                if (screen->step == 20) {
                    found = GAME.funcs.getPartyMember(screen->lab->unk64);
                    GAME.funcs.getPartnerSlots(found, slots);
                    GAME.funcs.getPartnerEntry(found, slots[windows->entryList->cursor], &entry);
                    found = 0; /* the match depends on reusing the member's variable */
                    for (i = 0; i < 6; i++) {
                        if (entry.skills[i] != 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        screen->setSubstate(screen, 50);
                        STGDGLAB_data.funcs.startFade(&screen->panels[5], 1);
                        windows->cursor->setVisible(windows->cursor, 0);
                        windows->entryList->substate = 4;
                        break;
                    }
                }
                screen->picked = windows->entryList->cursor;
                screen->substate = screen->step;
                screen->setStep(screen, 0);
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                windows->entryList->close(windows->entryList);
                screen->substate++;
            }
        }
        break;
    case 42:
        if (windows->entryList == NULL) {
            screen->setSubstate(screen, 0);
        }
        break;
    case 10:
        screen->lab->closeMenu(screen->lab);
        windows->entryList->close(windows->entryList);
        screen->substate++;
        break;
    case 11:
        if (screen->lab->menuOpen(screen->lab) && windows->entryList == NULL) {
            if (windows->entryPanel == NULL) {
                windows->entryPanel = func_800869A4(GAME.funcs.getPartyMember(screen->lab->unk64), screen->picked);
            }
            screen->substate++;
        }
        break;
    case 12:
        if (windows->entryPanel == NULL) {
            screen->lab->openMenu(screen->lab);
            screen->setSubstate(screen, 40);
            screen->step = 10;
        }
        break;
    case 20:
        windows->entryList->close(windows->entryList);
        screen->substate++;
        break;
    case 21:
        if (windows->entryList == NULL) {
            if (windows->skillsPanel == NULL) {
                windows->skillsPanel = func_8008D014(GAME.funcs.getPartyMember(screen->lab->unk64), screen->picked);
            }
            screen->substate++;
        }
        break;
    case 22:
        if (windows->skillsPanel == NULL) {
            screen->setSubstate(screen, 40);
            screen->step = 20;
        }
        break;
    case 30:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[4])) {
            if (windows->unk4C == NULL) {
                windows->unk4C = createTextWindow(screen->layer, 1, 0xA4, 0xB8);
            }
            windows->unk4C->setDepth(windows->unk4C, screen->depth - 1);
            windows->unk4C->setString(windows->unk4C, FILE_CACHE.load(TEXT_FILE(0x3A)), screen->choice + 0x24);
            screen->substate++;
        }
        break;
    case 31:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            STGDGLAB_data.funcs.startFade(&screen->panels[4], 0);
            windows->unk4C->setVisible(windows->unk4C, 0);
            screen->substate++;
        }
        break;
    case 32:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[4])) {
            windows->cursor->setVisible(windows->cursor, 1);
            screen->setSubstate(screen, 2);
        }
        break;
    case 50:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[5])) {
            if (windows->unk4C == NULL) {
                windows->unk4C = createTextWindow(screen->layer, 1, 0xA4, 0xB8);
            }
            windows->unk4C->setDepth(windows->unk4C, 0);
            windows->unk4C->setString(windows->unk4C, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x25);
            screen->substate++;
        }
        break;
    case 51:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            STGDGLAB_data.funcs.startFade(&screen->panels[5], 0);
            windows->unk4C->setVisible(windows->unk4C, 0);
            screen->substate++;
        }
        break;
    case 52:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[5])) {
            screen->setSubstate(screen, 41);
            screen->step = 20;
            windows->entryList->substate = 5;
        }
        break;
    }
}

/* Draws the second screen's frames */
void func_80087B68(LabScreen2 *screen, void *children) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layer, screen->depth);
    if (screen->panels[5].level != 0) {
        sprite.setLayerId(screen->layer, 1);
        if (screen->panels[5].level != 0x1000) {
            sprite.setScale(screen->panels[5].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xBE);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x25, 0x92, 0xB0);
    }
    if (screen->panels[0].level != 0x1000) {
        sprite.setScale(screen->panels[0].level, 0x1000, 0x1000);
        sprite.setPivot(0, 0x7F);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    sprite.setTexture(0x140, 0);
    sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xF, 0, 0x4B);
    sprite.setTexture(0x280, 0x100);
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x1F, 0, 0x4B);
    if (screen->panels[1].level != 0x1000) {
        sprite.setScale(screen->panels[1].level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x2A);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x22, 0x92, 0xF);
    if (screen->panels[2].level != 0x1000) {
        sprite.setScale(screen->panels[3].level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x5C);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x20, 0x92, 0x51);
    if (screen->panels[3].level != 0x1000) {
        sprite.setScale(screen->panels[3].level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x87);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x23, 0x92, 0x6C);
    if (screen->panels[4].level != 0) {
        if (screen->panels[4].level != 0x1000) {
            sprite.setScale(screen->panels[4].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xBE);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x25, 0x92, 0xB0);
    }
}

void func_80087F48(LabScreen2 *screen, void *children) {
    switch (screen->state) {
    case TASK_INIT:
    default:
        screen->nextState(screen);
        screen->panels[0].duration = 8;
        screen->panels[1].duration = 10;
        screen->panels[2].duration = 10;
        screen->panels[3].duration = 10;
        screen->panels[4].duration = 10;
        screen->panels[5].duration = 8;
        func_800869FC(screen, children);
        break;
    case TASK_RUN:
        func_80086F6C(screen, children);
        func_80087B68(screen, children);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_80087FF0(Lab *lab) {
    LabScreen2 *screen = createTask(func_80087F48, sizeof(LabScreen2), 0x60);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->lab = lab;
    return (Task *)screen;
}
