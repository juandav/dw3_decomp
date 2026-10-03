/* The fourth object of STSTATUS.PRO (see ststatus.c), the fifth screen's
   panel of func_8008AB04: its rodata starts at 0x800827A0 (USA). */

#include "ststatus.h"

void func_80088C54(StatusPanel4A *panel);
void func_8008927C(StatusPanel4A *panel, StatusPanel4AWindows *windows);

void func_80087A3C(StatusPanel4A *panel, StatusPanel4AWindows *windows) {
    WindowPos *layout;
    WindowPos *pos;
    s32 i;

    for (i = 0; i < 3; i++) {
        windows->slots[i] = createTextWindow(panel->layer, 1, 0xBD, i * 14 + 0x31);
    }
    windows->slotCursor = createCursor(panel->layer, panel->depth - 1, 0xB0, panel->slot * 14 + 0x31);
    windows->slotCursor->setVisible(windows->slotCursor, 0);
    windows->unk10 = createTextWindow(panel->layer, 1, 0x5E, 0x4D);
    windows->unk14 = createTextWindow(panel->layer, 1, 0xB2, 0x2A);
    for (i = 0; i < 2; i++) {
        windows->options[i] = createTextWindow(panel->layer, 1, 0xBD, i * 14 + 0x3A);
    }
    windows->optionCursor = createCursor(panel->layer, panel->depth - 1, 0xB4, panel->option * 14 + 0x3A);
    windows->optionCursor->setVisible(windows->optionCursor, 0);
    windows->unk28 = createTextWindow(panel->layer, 1, 0x4F, 0x68);
    windows->unk30 = createTextWindow(panel->layer, 1, 0xEB, 0x68);
    windows->unk2C = createTextWindow(panel->layer, 1, 0x12F, 0x68);
    for (i = 0; i < 6; i++) {
        windows->list[i] = createTextWindow(panel->layer, 1, 0x71, i * 14 + 0x7C);
    }
    for (i = 0; i < 7; i++) {
        windows->list[i + 6] = createTextWindow(panel->layer, 1, 0x9B, i * 14 + 0x7C);
    }
    for (i = 0; i < 6; i++) {
        windows->values[i] = createTextWindow(panel->layer, 1, 0xC4, i * 14 + 0x88);
    }
    windows->listCursor = createCursor(panel->layer, panel->depth - 1, 0xA9, 0x88);
    windows->listCursor->setVisible(windows->listCursor, 0);
    windows->title = createTextWindow(panel->layer, 1, 0x98, 0x13);
    layout = STSTATUS_data.layout;
    pos = &layout[12];
    windows->help = createTextWindow(panel->layer, 1, pos->x, pos->y);
    pos = &layout[13];
    windows->unk88 = createTextWindow(panel->layer, 1, pos->x, pos->y);
    pos = &layout[14];
    windows->unk8C = createTextWindow(panel->layer, 1, pos->x, pos->y);
}

/* The Digimon in the partner's three slots, the one it is highlighted, and
   the partner's own name */
void func_80087D5C(StatusPanel4A *panel, StatusPanel4AWindows *windows, s32 show) {
    Partner *partner;
    DigimonData *data;
    s32 id;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(panel->member);
        partner = &GAME.partners[id];
        for (i = 0; i < 3; i++) {
            if (panel->slots[i] > 0) {
                data = ON_PARTNER_ENTRY_ADDED(panel->slots[i]);
                windows->slots[i]->setString(windows->slots[i], FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
                if (partner->unk8 == panel->slots[i]) {
                    windows->slots[i]->setPalette(windows->slots[i], 1);
                } else {
                    windows->slots[i]->setPalette(windows->slots[i], 0);
                }
            } else {
                windows->slots[i]->setVisible(windows->slots[i], 0);
            }
        }
        data = &DIGIMON_DATA[id];
        windows->unk10->setString(windows->unk10, FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
    } else {
        for (i = 0; i < 3; i++) {
            windows->slots[i]->setVisible(windows->slots[i], 0);
        }
        windows->unk10->setVisible(windows->unk10, 0);
    }
}

void func_80087F5C(StatusPanel4A *panel, StatusPanel4AWindows *windows, s32 show) {
    Partner *partner;
    DigimonData *data;
    s32 i;

    if (show) {
        partner = &GAME.partners[GAME.funcs.getPartyMember(panel->member)];
        data = ON_PARTNER_ENTRY_ADDED(panel->slots[panel->slot]);
        windows->unk14->setString(windows->unk14, FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
        if (partner->unk8 == panel->slots[panel->slot]) {
            windows->options[0]->setString(windows->options[0], FILE_CACHE.load(TEXT_FILE(0xB1)), 0x3A);
        } else {
            windows->options[0]->setString(windows->options[0], FILE_CACHE.load(TEXT_FILE(0xB1)), 0x39);
        }
        windows->options[1]->setString(windows->options[1], FILE_CACHE.load(TEXT_FILE(0xB1)), 0x3B);
    } else {
        windows->unk14->setVisible(windows->unk14, 0);
        for (i = 0; i < 2; i++) {
            windows->options[i]->setVisible(windows->options[i], 0);
        }
    }
}

/* The stats and techniques of the slot's entry (or of the partner itself),
   or hides them */
void func_80088114(StatusPanel4A *panel, StatusPanel4AWindows *windows, s32 show) {
    PartnerTotals totals;
    StatusPartnerEntry entry;
    DigimonData *data;
    s32 id;
    s32 slot;
    s32 value;
    s32 tech;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(panel->member);
        if (panel->fromEntry) {
            slot = panel->slots[panel->slot];
            GAME.funcs.getPartnerEntry(id, slot, &entry);
            GAME.funcs.computeStats(id, &totals);
            data = ON_PARTNER_ENTRY_ADDED(slot);
            windows->unk28->setString(windows->unk28, FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
            windows->unk30->setString(windows->unk30, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x38);
            windows->unk2C->setNumber(windows->unk2C, 0, entry.level);
            windows->unk2C->setRightAlign(windows->unk2C, 1);
            for (i = 0; i < 6; i++) {
                value = totals.stats[D_80099B10[i]] + data->battleStats[i];
                if (value >= 1000) {
                    value = 999;
                }
                windows->list[i]->setNumber(windows->list[i], 0, value);
                if (i == 0) {
                    if (totals.stats[19]) {
                        windows->list[0]->setPalette(windows->list[0], 6);
                    }
                } else if (i == 1) {
                    if (totals.stats[20]) {
                        windows->list[1]->setPalette(windows->list[1], 6);
                    }
                } else if (i == 4 && totals.stats[21]) {
                    windows->list[4]->setPalette(windows->list[4], 6);
                }
            }
            for (i = 0; i < 7; i++) {
                value = totals.stats[D_80099B10[i + 6]] + data->resistances[i];
                if (value >= 1000) {
                    value = 999;
                }
                windows->list[i + 6]->setNumber(windows->list[i + 6], 0, value);
            }
            for (i = 0; i < 13; i++) {
                windows->list[i]->setRightAlign(windows->list[i], 1);
            }
            for (i = 0; i < 6; i++) {
                tech = entry.techs[i];
                if (tech != 0) {
                    windows->values[i]->setString(windows->values[i], FILE_CACHE.load(TEXT_FILE(0xA3)), tech & 0x1FFF);
                    if (tech & 0x8000) {
                        windows->values[i]->setPalette(windows->values[i], 3);
                    } else if (tech & 0x4000) {
                        windows->values[i]->setPalette(windows->values[i], 4);
                    } else {
                        windows->values[i]->setPalette(windows->values[i], 0);
                    }
                } else {
                    windows->values[i]->setVisible(windows->values[i], 0);
                }
            }
        } else {
            data = &DIGIMON_DATA[id];
            GAME.funcs.computeStats(id, &totals);
            windows->unk28->setString(windows->unk28, FILE_CACHE.load(TEXT_FILE(0x4F)), data->nameId);
            windows->unk30->setString(windows->unk30, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x38);
            windows->unk2C->setString(windows->unk2C, FILE_CACHE.load(TEXT_FILE(0xB1)), 0xD);
            windows->unk2C->setRightAlign(windows->unk2C, 1);
            for (i = 0; i < 6; i++) {
                value = totals.stats[D_80099B10[i]];
                if (value >= 1000) {
                    value = 999;
                }
                windows->list[i]->setNumber(windows->list[i], 0, value);
                if (i == 0) {
                    if (totals.stats[19]) {
                        windows->list[0]->setPalette(windows->list[0], 6);
                    }
                } else if (i == 1) {
                    if (totals.stats[20]) {
                        windows->list[1]->setPalette(windows->list[1], 6);
                    }
                } else if (i == 4 && totals.stats[21]) {
                    windows->list[4]->setPalette(windows->list[4], 6);
                }
            }
            for (i = 0; i < 7; i++) {
                value = totals.stats[D_80099B10[i + 6]];
                if (value >= 1000) {
                    value = 999;
                }
                windows->list[i + 6]->setNumber(windows->list[i + 6], 0, value);
            }
            for (i = 0; i < 13; i++) {
                windows->list[i]->setRightAlign(windows->list[i], 1);
            }
            for (i = 0; i < 6; i++) {
                if (data->skills[i + 1] != 0) {
                    windows->values[i]->setString(windows->values[i], FILE_CACHE.load(TEXT_FILE(0xA3)), data->skills[i + 1]);
                    windows->values[i]->setPalette(windows->values[i], 3);
                } else {
                    windows->values[i]->setVisible(windows->values[i], 0);
                }
            }
        }
        panel->listShown = 1;
    } else {
        windows->unk28->setVisible(windows->unk28, 0);
        windows->unk30->setVisible(windows->unk30, 0);
        windows->unk2C->setVisible(windows->unk2C, 0);
        for (i = 0; i < 13; i++) {
            windows->list[i]->setVisible(windows->list[i], 0);
        }
        for (i = 0; i < 6; i++) {
            windows->values[i]->setVisible(windows->values[i], 0);
        }
        panel->listShown = 0;
    }
}

/* Moves the list to the panel's scroll position */
void func_80088850(StatusPanel4A *panel, StatusPanel4AWindows *windows) {
    s32 i;

    /* the match depends on the (s16) casts in the loops */
    windows->unk28->setPos(windows->unk28, 0x4F, panel->scroll.value + 0x68);
    windows->unk30->setPos(windows->unk30, 0xEB, panel->scroll.value + 0x68);
    windows->unk2C->setPos(windows->unk2C, 0x12F, panel->scroll.value + 0x68);
    for (i = 0; i < 6; i++) {
        windows->list[i]->setPos(windows->list[i], 0x71, i * 14 + (s16)(panel->scroll.value + 0x7C));
    }
    for (i = 0; i < 7; i++) {
        windows->list[i + 6]->setPos(windows->list[i + 6], 0x9B, i * 14 + (s16)(panel->scroll.value + 0x7C));
    }
    for (i = 0; i < 6; i++) {
        windows->values[i]->setPos(windows->values[i], 0xC4, i * 14 + (s16)(panel->scroll.value + 0x88));
    }
}

/* Shows the cost of the technique under the list's cursor */
void func_800889E8(StatusPanel4A *panel, StatusPanel4AWindows *windows, s32 show) {
    StatusPartnerEntry entry;
    DigimonData *data;
    s32 id;
    s32 tech;

    if (show) {
        id = GAME.funcs.getPartyMember(panel->member);
        if (panel->fromEntry) {
            GAME.funcs.getPartnerEntry(id, panel->slots[panel->slot], &entry);
            tech = entry.techs[panel->tech] & 0x1FFF;
            if (tech > 0) {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x9C)), tech);
                windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 3);
                windows->unk8C->setNumber(windows->unk8C, 0, D_800427E8[tech - 1].mp);
                windows->unk8C->setRightAlign(windows->unk8C, 1);
                return;
            }
        } else {
            data = &DIGIMON_DATA[id];
            tech = data->skills[panel->tech + 1];
            if (tech > 0) {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x9C)), tech);
                windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 3);
                windows->unk8C->setNumber(windows->unk8C, 0, D_800427E8[tech - 1].mp);
                windows->unk8C->setRightAlign(windows->unk8C, 1);
                return;
            }
        }
    }
    windows->help->setVisible(windows->help, 0);
    windows->unk88->setVisible(windows->unk88, 0);
    windows->unk8C->setVisible(windows->unk8C, 0);
}

/* Draws the panel's frames, the technique icons and the help arrow */
void func_80088C54(StatusPanel4A *panel) {
    SpriteDrawer sprite;
    StatusPartnerEntry entry;
    DigimonData *data;
    s32 id;
    s32 tech;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(panel->layer, panel->depth);
    sprite.setTexture(0x280, 0x100);
    if (panel->fades[1].level != 0) {
        if (panel->fades[1].level != 0x1000) {
            sprite.setScale(panel->fades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x44);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x24, 0xA8, 0x28);
    }
    if (panel->fades[2].level != 0) {
        if (panel->fades[2].level != 0x1000) {
            sprite.setScale(panel->fades[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x41);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x26, 0xA8, 0x28);
    }
    if (panel->fades[3].level != 0) {
        if (panel->fades[3].level != 0x1000) {
            sprite.setScale(panel->fades[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xA2);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x14, 0x4F, panel->scroll.value + 0x7C);
        if (panel->listShown) {
            id = GAME.funcs.getPartyMember(panel->member);
            if (panel->fromEntry) {
                GAME.funcs.getPartnerEntry(id, panel->slots[panel->slot], &entry);
                for (i = 0; i < 6; i++) {
                    tech = entry.techs[i] & 0x1FFF;
                    if (tech != 0) {
                        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), D_800427E8[tech - 1].icon + 0x37, 0xB6,
                                    panel->scroll.value + 0x88 + i * 14);
                    }
                }
            } else {
                data = &DIGIMON_DATA[id];
                for (i = 0; i < 6; i++) {
                    tech = data->skills[i + 1];
                    if (tech > 0) {
                        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), D_800427E8[tech - 1].icon + 0x37, 0xB6,
                                    panel->scroll.value + 0x88 + i * 14);
                    }
                }
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x27, 0x48, panel->scroll.value + 0x61);
    }
    if (panel->fades[4].level != 0) {
        if (panel->blink) {
            if (GFX.funcs.getTime() - panel->time >= 4) {
                panel->time = GFX.funcs.getTime();
                panel->blinkFrame++;
                if (panel->blinkFrame >= 5) {
                    panel->blinkFrame = 0;
                }
            }
            sprite.setTexture(0x140, 0);
            sprite.setClutRow(panel->blinkFrame);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xA, 0x123, 0xD6);
            sprite.setClutRow(0);
        }
        if (panel->fades[4].level != 0x1000) {
            sprite.setScale(panel->fades[4].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xD3);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x20, 0, 0xC2);
    }
    if (panel->fades[0].level != 0) {
        if (panel->fades[0].level != 0x1000) {
            sprite.setScale(panel->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xD);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x18, 0x22, 0xD);
    }
}

/* The panel's update: picks a slot, then shows its entry's techniques or
   makes the battle start as it */
void func_8008927C(StatusPanel4A *panel, StatusPanel4AWindows *windows) {
    StatusPartnerEntry entry;
    Partner *partner;
    DigimonData *data;
    /* the cursors' old rows: the match depends on cases 4 and 13 having
       their own variables */
    s32 old;
    s32 slot;
    s32 option;
    s32 tech;
    s32 i;

    switch (panel->substate) {
    case 0:
    default:
        STSTATUS_data.funcs.startFade(&panel->fades[0], 1);
        panel->substate++;
        break;
    case 1:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[0])) {
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x37);
            STSTATUS_data.funcs.startFade(&panel->fades[1], 1);
            panel->substate++;
        }
        break;
    case 2:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[1])) {
            func_80087D5C(panel, windows, 1);
            STSTATUS_data.funcs.startFade(&panel->fades[3], 1);
            panel->substate++;
        }
        break;
    case 3:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[3])) {
            func_80088114(panel, windows, 1);
            windows->slotCursor->setPos(windows->slotCursor, 0x50, 0x4D);
            windows->slotCursor->setVisible(windows->slotCursor, 1);
            panel->substate++;
        }
        break;
    case 4:
        if (panel->fromEntry) {
            slot = panel->slot;
            if (PAD_PRESSED(PAD_LEFT)) {
                panel->fromEntry = 0;
                func_80088114(panel, windows, 1);
                windows->slotCursor->setPos(windows->slotCursor, 0x50, 0x4D);
                SOUND.playSound(0x8004513E);
                break;
            }
            if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                panel->slot--;
                if (panel->slot < 0) {
                    panel->slot = 0;
                }
            } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                panel->slot++;
                if (panel->slot > panel->slotCount - 1) {
                    panel->slot = panel->slotCount - 1;
                }
            }
            if (slot != panel->slot) {
                func_80088114(panel, windows, 1);
                windows->slotCursor->setPos(windows->slotCursor, 0xB0, panel->slot * 0xE + 0x31);
                SOUND.playSound(0x8004513E);
            } else if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x8004503C);
                panel->substate = 10;
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                panel->substate = 0x32;
            }
        } else if (panel->slotCount > 0 && PAD_PRESSED(PAD_RIGHT)) {
            panel->fromEntry = 1;
            func_80088114(panel, windows, 1);
            windows->slotCursor->setPos(windows->slotCursor, 0xB0, panel->slot * 0xE + 0x31);
            SOUND.playSound(0x8004513E);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            panel->substate = 0x3C;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            panel->substate = 0x32;
        }
        break;
    case 10:
        STSTATUS_data.funcs.startFade(&panel->fades[1], 0);
        func_80087D5C(panel, windows, 0);
        windows->slotCursor->setVisible(windows->slotCursor, 0);
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2C);
        panel->substate++;
        break;
    case 11:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[1])) {
            STSTATUS_data.funcs.startFade(&panel->fades[2], 1);
            panel->substate++;
        }
        break;
    case 12:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[2])) {
            func_80087F5C(panel, windows, 1);
            windows->optionCursor->setVisible(windows->optionCursor, 1);
            panel->substate++;
        }
        break;
    case 13:
        option = panel->option;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            panel->option = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            panel->option = 1;
        }
        if (option != panel->option) {
            SOUND.playSound(0x8004513E);
            windows->optionCursor->setPos(windows->optionCursor, 0xB4, panel->option * 0xE + 0x3A);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (panel->option == 0) {
                partner = &GAME.partners[GAME.funcs.getPartyMember(panel->member)];
                if (partner->unk8 == panel->slots[panel->slot]) {
                    partner->unk8 = 0;
                } else {
                    partner->unk8 = panel->slots[panel->slot];
                }
                panel->substate = 0x19;
            } else {
                panel->substate = 0x28;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            panel->substate = 0x14;
        }
        break;
    case 0x14:
        STSTATUS_data.funcs.startFade(&panel->fades[2], 0);
        func_80087F5C(panel, windows, 0);
        windows->optionCursor->setVisible(windows->optionCursor, 0);
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x37);
        panel->substate++;
        break;
    case 0x15:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[2])) {
            STSTATUS_data.funcs.startFade(&panel->fades[1], 1);
            panel->substate++;
        }
        break;
    case 0x19:
        STSTATUS_data.funcs.startFade(&panel->fades[0], 0);
        windows->title->setVisible(windows->title, 0);
        STSTATUS_data.funcs.startFade(&panel->fades[2], 0);
        func_80087F5C(panel, windows, 0);
        windows->optionCursor->setVisible(windows->optionCursor, 0);
        panel->substate++;
        break;
    case 0x1A:
        STSTATUS_data.funcs.updateFade(&panel->fades[0]);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[2])) {
            STSTATUS_data.funcs.startLerp(&panel->scroll, 0, -0x22, 4);
            panel->substate++;
        }
        break;
    case 0x1B:
        if (STSTATUS_data.funcs.updateLerp(&panel->scroll)) {
            STSTATUS_data.funcs.startFade(&panel->fades[4], 1);
            panel->substate++;
        }
        func_80088850(panel, windows);
        break;
    case 0x1C:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[4])) {
            /* the match depends on taking the partner's address */
            if ((&GAME.partners[GAME.funcs.getPartyMember(panel->member)])->unk8 != 0) {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x3C);
            } else {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x3D);
            }
            panel->blink = 1;
            panel->substate++;
        }
        break;
    case 0x1D:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            panel->blink = 0;
            panel->substate++;
        }
        break;
    case 0x1E:
        STSTATUS_data.funcs.startFade(&panel->fades[4], 0);
        windows->help->setVisible(windows->help, 0);
        STSTATUS_data.funcs.startFade(&panel->fades[3], 0);
        func_80088114(panel, windows, 0);
        panel->substate++;
        break;
    case 0x1F:
        STSTATUS_data.funcs.updateFade(&panel->fades[4]);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[3])) {
            panel->fromEntry = 0;
            STSTATUS_data.funcs.startLerp(&panel->scroll, 0, -0x22, 4);
            func_80088850(panel, windows);
            panel->substate = 0;
        }
        break;
    case 0x28:
        STSTATUS_data.funcs.startFade(&panel->fades[2], 0);
        func_80087F5C(panel, windows, 0);
        windows->optionCursor->setVisible(windows->optionCursor, 0);
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2A);
        panel->substate++;
        break;
    case 0x29:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[2])) {
            STSTATUS_data.funcs.startLerp(&panel->scroll, 0, -0x22, 4);
            panel->substate++;
        }
        break;
    case 0x2A:
        if (STSTATUS_data.funcs.updateLerp(&panel->scroll)) {
            STSTATUS_data.funcs.startFade(&panel->fades[4], 1);
            panel->substate++;
        }
        func_80088850(panel, windows);
        break;
    case 0x2B:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[4])) {
            GAME.funcs.getPartnerEntry(GAME.funcs.getPartyMember(panel->member), panel->slots[panel->slot], &entry);
            panel->tech = -1;
            panel->techCount = 0;
            for (i = 0; i < 6; i++) {
                if (entry.techs[i] & 0x1FFF) {
                    panel->techCount++;
                    if (panel->tech == -1) {
                        panel->tech = i;
                    }
                }
            }
            if (panel->techCount != 0) {
                /* the match depends on this order of the terms */
                windows->listCursor->setPos(windows->listCursor, 0xA9, panel->tech * 0xE + 0x88 + panel->scroll.value);
                windows->listCursor->setVisible(windows->listCursor, 1);
                func_800889E8(panel, windows, 1);
                panel->substate++; /* in both branches: the match depends on it */
            } else {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x3E);
                panel->substate++;
            }
        }
        break;
    case 0x2C:
        if (panel->techCount != 0) {
            old = panel->tech;
            GAME.funcs.getPartnerEntry(GAME.funcs.getPartyMember(panel->member), panel->slots[panel->slot], &entry);
            if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                do {
                    panel->tech--;
                    if (panel->tech < 0) {
                        panel->tech = old;
                        break;
                    }
                } while ((entry.techs[panel->tech] & 0x1FFF) <= 0);
            } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                do {
                    panel->tech++;
                    if (panel->tech >= 6) {
                        panel->tech = old;
                        break;
                    }
                } while ((entry.techs[panel->tech] & 0x1FFF) <= 0);
            }
            if (old != panel->tech) {
                SOUND.playSound(0x8004513E);
                windows->listCursor->setPos(windows->listCursor, 0xA9, panel->tech * 0xE + 0x88 + panel->scroll.value);
                func_800889E8(panel, windows, 1);
            }
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            panel->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            panel->substate++;
        }
        break;
    case 0x2D:
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2C);
        windows->listCursor->setVisible(windows->listCursor, 0);
        func_800889E8(panel, windows, 0);
        STSTATUS_data.funcs.startLerp(&panel->scroll, -0x22, 0, 4);
        STSTATUS_data.funcs.startFade(&panel->fades[4], 0);
        panel->substate++;
        break;
    case 0x2E:
        STSTATUS_data.funcs.updateLerp(&panel->scroll);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[4])) {
            STSTATUS_data.funcs.startFade(&panel->fades[2], 1);
            panel->substate++;
        }
        func_80088850(panel, windows);
        break;
    case 0x2F:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[2])) {
            windows->optionCursor->setVisible(windows->optionCursor, 1);
            func_80087F5C(panel, windows, 1);
            panel->substate = 13;
        }
        break;
    case 0x32:
        STSTATUS_data.funcs.startFade(&panel->fades[0], 0);
        STSTATUS_data.funcs.startFade(&panel->fades[1], 0);
        STSTATUS_data.funcs.startFade(&panel->fades[3], 0);
        func_80087D5C(panel, windows, 0);
        func_80088114(panel, windows, 0);
        windows->slotCursor->setVisible(windows->slotCursor, 0);
        windows->title->setVisible(windows->title, 0);
        panel->substate++;
        break;
    case 0x33:
        STSTATUS_data.funcs.updateFade(&panel->fades[0]);
        STSTATUS_data.funcs.updateFade(&panel->fades[1]);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[3])) {
            panel->state = 3;
        }
        break;
    case 0x3C:
        STSTATUS_data.funcs.startFade(&panel->fades[1], 0);
        func_80087D5C(panel, windows, 0);
        windows->slotCursor->setVisible(windows->slotCursor, 0);
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2A);
        panel->substate++;
        break;
    case 0x3D:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[1])) {
            STSTATUS_data.funcs.startLerp(&panel->scroll, 0, -0x22, 4);
            panel->substate++;
        }
        break;
    case 0x3E:
        if (STSTATUS_data.funcs.updateLerp(&panel->scroll)) {
            STSTATUS_data.funcs.startFade(&panel->fades[4], 1);
            panel->substate++;
        }
        func_80088850(panel, windows);
        break;
    case 0x3F:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[4])) {
            data = &DIGIMON_DATA[GAME_FUNCS.getPartyMember(panel->member)];
            tech = data->skills[6];
            panel->tech = 5;
            windows->listCursor->setPos(windows->listCursor, 0xA9, panel->scroll.value + 0xCE);
            windows->listCursor->setVisible(windows->listCursor, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x9C)), tech);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 3);
            windows->unk8C->setNumber(windows->unk8C, 0, D_800427E8[tech - 1].mp);
            windows->unk8C->setRightAlign(windows->unk8C, 1);
            panel->substate++;
        }
        break;
    case 0x40:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            panel->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            panel->substate++;
        }
        break;
    case 0x41:
        windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x37);
        windows->listCursor->setVisible(windows->listCursor, 0);
        func_800889E8(panel, windows, 0);
        STSTATUS_data.funcs.startLerp(&panel->scroll, -0x22, 0, 4);
        STSTATUS_data.funcs.startFade(&panel->fades[4], 0);
        panel->substate++;
        break;
    case 0x42:
        STSTATUS_data.funcs.updateLerp(&panel->scroll);
        if (STSTATUS_data.funcs.updateFade(&panel->fades[4])) {
            STSTATUS_data.funcs.startFade(&panel->fades[1], 1);
            panel->substate++;
        }
        func_80088850(panel, windows);
        break;
    case 0x16:
    case 0x43:
        if (STSTATUS_data.funcs.updateFade(&panel->fades[1])) {
            func_80087D5C(panel, windows, 1);
            windows->slotCursor->setVisible(windows->slotCursor, 1);
            panel->substate = 4;
        }
        break;
    }
}

void func_8008AA00(StatusPanel4A *panel, StatusPanel4AWindows *windows) {
    s32 i;

    switch (panel->state) {
    case 0:
    default:
        panel->nextState(panel);
        func_80087A3C(panel, windows);
        GAME.funcs.getPartnerSlots(GAME.funcs.getPartyMember(panel->member), panel->slots);
        for (i = 0; i < 3; i++) {
            if (panel->slots[i] >= 4) {
                panel->slotCount++;
            }
        }
        panel->fades[0].duration = 10;
        panel->fades[1].duration = 10;
        panel->fades[2].duration = 10;
        panel->fades[3].duration = 10;
        panel->fades[4].duration = 10;
        break;
    case 1:
        func_8008927C(panel, windows);
        func_80088C54(panel);
        break;
    case 2:
    case 3:
        break;
    }
}

StatusPanel4A *func_8008AB04(StatusScreen4 *screen) {
    StatusPanel4A *panel = createTask(func_8008AA00, sizeof(StatusPanel4A), 0x90);

    panel->layer = 0x1000;
    panel->depth = 6;
    panel->screen = screen;
    panel->member = screen->member;
    return panel;
}
