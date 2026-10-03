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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_4", func_80088114);

/* Moves the list to the panel's scroll position */
void func_80088850(StatusPanel4A *panel, StatusPanel4AWindows *windows) {
    s32 i;

    /* the match depends on the (s16) casts in the loops */
    windows->unk28->setPos(windows->unk28, 0x4F, panel->scroll + 0x68);
    windows->unk30->setPos(windows->unk30, 0xEB, panel->scroll + 0x68);
    windows->unk2C->setPos(windows->unk2C, 0x12F, panel->scroll + 0x68);
    for (i = 0; i < 6; i++) {
        windows->list[i]->setPos(windows->list[i], 0x71, i * 14 + (s16)(panel->scroll + 0x7C));
    }
    for (i = 0; i < 7; i++) {
        windows->list[i + 6]->setPos(windows->list[i + 6], 0x9B, i * 14 + (s16)(panel->scroll + 0x7C));
    }
    for (i = 0; i < 6; i++) {
        windows->values[i]->setPos(windows->values[i], 0xC4, i * 14 + (s16)(panel->scroll + 0x88));
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
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x14, 0x4F, panel->scroll + 0x7C);
        if (panel->listShown) {
            id = GAME.funcs.getPartyMember(panel->member);
            if (panel->fromEntry) {
                GAME.funcs.getPartnerEntry(id, panel->slots[panel->slot], &entry);
                for (i = 0; i < 6; i++) {
                    tech = entry.techs[i] & 0x1FFF;
                    if (tech != 0) {
                        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), D_800427E8[tech - 1].icon + 0x37, 0xB6,
                                    panel->scroll + 0x88 + i * 14);
                    }
                }
            } else {
                data = &DIGIMON_DATA[id];
                for (i = 0; i < 6; i++) {
                    tech = data->skills[i + 1];
                    if (tech > 0) {
                        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), D_800427E8[tech - 1].icon + 0x37, 0xB6,
                                    panel->scroll + 0x88 + i * 14);
                    }
                }
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x27, 0x48, panel->scroll + 0x61);
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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_4", func_8008927C);

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
