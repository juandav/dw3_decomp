/* The fifth object of STSTATUS.PRO (see ststatus.c), the fifth screen
   (func_8008DEA4): its rodata starts at 0x800828B0 (USA). */

#include "ststatus.h"

void func_8008AB58(StatusScreen4 *screen, StatusScreen4Windows *windows);
void func_8008BF2C(StatusScreen4 *screen);
void func_8008D380(StatusScreen4 *screen, StatusScreen4Windows *windows);

/* Creates the windows of the fifth screen */
void func_8008AB58(StatusScreen4 *screen, StatusScreen4Windows *windows) {
    WindowPos *pos;
    s32 i;
    s32 j;

    pos = &STSTATUS_data.layout[11];
    windows->title = createTextWindow(screen->layer, 1, pos->x, pos->y);
    for (j = 0; j < 3; j++) {
        pos = &STSTATUS_data.layout[0];
        windows->pages[j].name = createTextWindow(screen->layer, 1, pos->x, pos->y + j * 46);
        pos = &STSTATUS_data.layout[1];
        for (i = 0; i < 5; i++, pos++) {
            windows->pages[j].labels[i] = createTextWindow(screen->layer, 3, pos->x, pos->y + j * 46);
        }
        pos = &STSTATUS_data.layout[6];
        for (i = 0; i < 5; i++, pos++) {
            windows->pages[j].values[i] = createTextWindow(screen->layer, 3, pos->x, pos->y + j * 46);
        }
    }
    pos = &STSTATUS_data.layout[12];
    windows->help = createTextWindow(screen->layer, 1, pos->x, pos->y);
    windows->help->setLines(windows->help, 2);
    windows->help2 = createTextWindow(screen->layer, 1, pos->x, pos->y + 14);
    for (i = 0; i < 2; i++) {
        windows->options[i] = createTextWindow(screen->layer, 1, 0xAC, 0x13 + i * 14);
    }
    windows->cursor = createCursor(screen->layer, screen->depth - 1, 0x98, screen->option * 14 + 0x13);
    windows->cursor->setVisible(windows->cursor, 0);
    windows->unk9C = createTextWindow(screen->layer, 3, 0x42, 0x45);
    windows->unkA0 = createTextWindow(screen->layer, 3, 0x46, 0x45);
    windows->slotTitle = createTextWindow(screen->layer, 1, 0xA7, 0x37);
    for (i = 0; i < 3; i++) {
        windows->slots[i] = createTextWindow(screen->layer, 1, 0xB2, 0x47 + i * 14);
    }
    windows->equipTitle = createTextWindow(screen->layer, 1, 0xA7, 0x79);
    for (i = 0; i < 6; i++) {
        windows->equip[i] = createTextWindow(screen->layer, 1, 0xC0, 0x89 + i * 14);
    }
    for (i = 0; i < 6; i++) {
        windows->values[i] = createTextWindow(screen->layer, 1, 0x32, 0x5B + i * 14);
    }
    for (i = 0; i < 7; i++) {
        windows->values[6 + i] = createTextWindow(screen->layer, 1, 0x5B, 0x5B + i * 14);
    }
    windows->unk108 = createTextWindow(screen->layer, 1, 0x10, 0xCB);
    windows->unk108->setDepth(windows->unk108, screen->depth - 1);
    windows->unk104 = createTextWindow(screen->layer, 1, 0x2D, 0xCB);
    windows->unk104->setDepth(windows->unk104, screen->depth - 1);
}

/* As func_800830AC */
void func_8008AF7C(StatusScreen *screen, StatusPagesB *windows, s32 member, s32 show) {
    PartnerTotals stats;
    WindowPos *layout;
    s32 id;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(member);
        GAME.funcs.computeStats(id, &stats);
        windows->pages[member].name->setString(windows->pages[member].name, GAME.funcs.getPartnerStats(id), -1);
        layout = &STSTATUS_data.layout[1];
        for (i = 0; i < 5; i++, layout++) {
            windows->pages[member].labels[i]->setString(windows->pages[member].labels[i],
                                                        FILE_CACHE.load(TEXT_FILE(0xB1)), layout->string);
        }
        for (i = 0; i < 5; i++) {
            windows->pages[member].values[i]->setNumber(windows->pages[member].values[i], 0, stats.stats[D_80099B44[i]]);
            windows->pages[member].values[i]->setRightAlign(windows->pages[member].values[i], 1);
        }
    } else {
        windows->pages[member].name->setVisible(windows->pages[member].name, 0);
        for (i = 0; i < 5; i++) {
            windows->pages[member].labels[i]->setVisible(windows->pages[member].labels[i], 0);
        }
        for (i = 0; i < 5; i++) {
            windows->pages[member].values[i]->setVisible(windows->pages[member].values[i], 0);
        }
    }
}

/* As func_8008AF7C, on the first page */
void func_8008B1B8(StatusScreen4 *screen, StatusScreen4Windows *windows, s32 member, s32 show) {
    PartnerTotals stats;
    WindowPos *layout;
    PartnerVitals *partner;
    s32 id;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(member);
        partner = GAME.funcs.getPartnerStats(id);
        GAME.funcs.computeStats(id, &stats);
        windows->pages[0].name->setString(windows->pages[0].name, partner, -1);
        layout = &STSTATUS_data.layout[1];
        for (i = 0; i < 5; i++, layout++) {
            windows->pages[0].labels[i]->setString(windows->pages[0].labels[i], FILE_CACHE.load(TEXT_FILE(0xB1)),
                                                   layout->string);
        }
        for (i = 0; i < 5; i++) {
            windows->pages[0].values[i]->setNumber(windows->pages[0].values[i], 0, stats.stats[D_80099B44[i]]);
            windows->pages[0].values[i]->setRightAlign(windows->pages[0].values[i], 1);
        }
    } else {
        windows->pages[0].name->setVisible(windows->pages[0].name, 0);
        for (i = 0; i < 5; i++) {
            windows->pages[0].labels[i]->setVisible(windows->pages[0].labels[i], 0);
        }
        for (i = 0; i < 5; i++) {
            windows->pages[0].values[i]->setVisible(windows->pages[0].values[i], 0);
        }
    }
}

void func_8008B38C(StatusScreen4 *screen, StatusScreen4Windows *windows, s32 show) {
    s32 i;

    if (show != 0) {
        for (i = 0; i < 2; i++) {
            windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0xB1)), i + 0x2D);
        }
    } else {
        for (i = 0; i < 2; i++) {
            windows->options[i]->setVisible(windows->options[i], 0);
        }
    }
}

/* The partner's slots: the entries in it (getPartnerSlots), the one it starts
   battles as (unk8) in palette 1, or hides them */
void func_8008B440(StatusScreen4 *screen, StatusScreen4Windows *windows, s32 show) {
    s16 slots[4];
    Partner *partner;
    DigimonData *entry;
    s32 id;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(screen->member);
        GAME.funcs.getPartnerSlots(id, slots);
        partner = &GAME.partners[id];
        windows->slotTitle->setString(windows->slotTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x34);
        for (i = 0; i < 3; i++) {
            if (slots[i] >= 4) {
                entry = ON_PARTNER_ENTRY_ADDED(slots[i]);
                windows->slots[i]->setString(windows->slots[i], FILE_CACHE.load(TEXT_FILE(0x4F)), entry->nameId);
                if (partner->unk8 == slots[i]) {
                    windows->slots[i]->setPalette(windows->slots[i], 1);
                } else {
                    windows->slots[i]->setPalette(windows->slots[i], 0);
                }
            } else {
                windows->slots[i]->setVisible(windows->slots[i], 0);
            }
        }
    } else {
        windows->slotTitle->setVisible(windows->slotTitle, 0);
        for (i = 0; i < 3; i++) {
            windows->slots[i]->setVisible(windows->slots[i], 0);
        }
    }
}

/* The party member's equipment, or the slots' names where it has none */
void func_8008B628(StatusScreen4 *screen, StatusScreen4Windows *windows, s32 show) {
    PartnerStats *stats;
    s16 item;
    s32 i;

    if (show) {
        stats = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(screen->member));
        windows->equipTitle->setString(windows->equipTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x20);
        for (i = 0; i < 6; i++) {
            item = stats->equip[i];
            if (item != 0) {
                windows->equip[i]->setString(windows->equip[i], FILE_CACHE.load(TEXT_FILE(0x6B)), item);
            } else {
                windows->equip[i]->setString(windows->equip[i], FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099B8C[i]);
            }
        }
    } else {
        windows->equipTitle->setVisible(windows->equipTitle, 0);
        for (i = 0; i < 6; i++) {
            windows->equip[i]->setVisible(windows->equip[i], 0);
        }
    }
}

/* Shows the party member's stats, in another palette the ones that are raised */
void func_8008B7A0(StatusScreen4 *screen, StatusScreen4Windows *windows, s32 show) {
    PartnerTotals totals;
    s32 value;
    s32 i;

    if (show) {
        GAME.funcs.computeStats(GAME.funcs.getPartyMember(screen->member), &totals);
        for (i = 0; i < 6; i++) {
            value = totals.stats[D_80099B58[i]];
            if (value >= 1000) {
                value = 999;
            }
            windows->values[i]->setNumber(windows->values[i], 0, value);
        }
        for (i = 0; i < 7; i++) {
            value = totals.stats[D_80099B58[i + 6]];
            if (value >= 1000) {
                value = 999;
            }
            windows->values[i + 6]->setNumber(windows->values[i + 6], 0, value);
        }
        for (i = 0; i < 13; i++) {
            windows->values[i]->setRightAlign(windows->values[i], 1);
            windows->values[i]->setPalette(windows->values[i], 0);
        }
        windows->unk108->setString(windows->unk108, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x4E);
        windows->unk104->setNumber(windows->unk104, 0, totals.stats[1]);
        windows->unk104->setRightAlign(windows->unk104, 1);
        if (totals.stats[19]) {
            windows->values[0]->setPalette(windows->values[0], 6);
        }
        if (totals.stats[20]) {
            windows->values[1]->setPalette(windows->values[1], 6);
        }
        if (totals.stats[21]) {
            windows->values[4]->setPalette(windows->values[4], 6);
        }
    } else {
        for (i = 0; i < 13; i++) {
            windows->values[i]->setVisible(windows->values[i], 0);
        }
        windows->unk108->setVisible(windows->unk108, 0);
        windows->unk104->setVisible(windows->unk104, 0);
    }
}

/* Shows the party member's stats as they would be with the item in the
   slot, in another palette the ones it changes (slot -1: as they are) */
void func_8008BA38(StatusScreen4 *screen, s32 slot, s32 item) {
    StatusScreen4Windows *windows = screen->children;
    PartnerTotals now;
    PartnerTotals then;
    StatusEquip saved;
    PartnerStats *stats;
    s16 *equip;
    s16 *hand;
    u8 *data;
    s32 id;
    s32 kind;
    s32 i;
    s32 j;
    s32 before;
    s32 after;

    if (slot == -1) {
        func_8008B7A0(screen, windows, 1);
        return;
    }
    id = GAME.funcs.getPartyMember(screen->member);
    stats = (PartnerStats *)GAME.funcs.getPartnerStats(id);
    GAME.funcs.computeStats(id, &now);
    saved = *(StatusEquip *)stats->equip;
    if (*(stats->equip + slot) != 0) {
        data = GET_ITEM[0](*(stats->equip + slot))->data;
        if (data[2] == 7) {
            stats->equip[2] = 0;
            stats->equip[3] = 0;
        } else {
            *(stats->equip + slot) = 0;
        }
    }
    if (item > 0) {
        data = GET_ITEM[0](item)->data;
        if (data[2] == 7) {
            hand = &stats->equip[2];
            if (*hand == 0) {
                hand = NULL;
                if (stats->equip[3] != 0) {
                    hand = &stats->equip[3];
                }
            }
            if (hand != NULL) {
                *hand = 0;
            }
        } else if (data[2] == 8) {
            kind = data[3];
            for (j = 0; j < 2; j++) {
                equip = &stats->equip[j + 4];
                if (*equip != 0) {
                    data = GET_ITEM[0](*equip)->data;
                    if (data[3] == kind) {
                        *equip = 0;
                    }
                }
            }
        }
        data = GET_ITEM[0](item)->data;
        if (data[2] == 7) {
            stats->equip[2] = item;
            stats->equip[3] = item;
        } else {
            *(stats->equip + slot) = item;
        }
    }
    GAME_FUNCS.computeStats(id, &then);
    *(StatusEquip *)stats->equip = saved;
    for (i = 0; i < 6; i++) {
        /* sums and not then.stats[...]: the match depends on them, which put
           the index first in the addu */
        after = *(then.stats + D_80099B58[i]);
        before = *(now.stats + D_80099B58[i]);
        if (after >= 1000) {
            windows->values[i]->setNumber(windows->values[i], 0, 999);
        } else {
            windows->values[i]->setNumber(windows->values[i], 0, after);
        }
        if (before < after) {
            windows->values[i]->setPalette(windows->values[i], 1);
        } else if (after < before) {
            windows->values[i]->setPalette(windows->values[i], 5);
        } else {
            windows->values[i]->setPalette(windows->values[i], 0);
            if (i == 0) {
                if (now.stats[19]) {
                    windows->values[0]->setPalette(windows->values[0], 6);
                }
            } else if (i == 1) {
                if (now.stats[20]) {
                    windows->values[1]->setPalette(windows->values[1], 6);
                }
            } else if (i == 4 && now.stats[21]) {
                windows->values[4]->setPalette(windows->values[4], 6);
            }
        }
    }
    for (i = 0; i < 7; i++) {
        after = *(then.stats + D_80099B58[i + 6]);
        before = *(now.stats + D_80099B58[i + 6]);
        if (after >= 1000) {
            windows->values[i + 6]->setNumber(windows->values[i + 6], 0, 999);
        } else {
            windows->values[i + 6]->setNumber(windows->values[i + 6], 0, after);
        }
        if (before < after) {
            windows->values[i + 6]->setPalette(windows->values[i + 6], 1);
        } else if (after < before) {
            windows->values[i + 6]->setPalette(windows->values[i + 6], 5);
        } else {
            windows->values[i + 6]->setPalette(windows->values[i + 6], 0);
        }
    }
    for (i = 0; i < 13; i++) {
        windows->values[i]->setRightAlign(windows->values[i], 1);
    }
}

/* Draws the partners' portraits and frames, the chosen one's, its equipment
   and the panels' frames */
void func_8008BF2C(StatusScreen4 *screen) {
    SpriteDrawer sprite;
    PartnerStats *stats;
    s32 item;
    s32 id;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layer, screen->depth);
    if (GFX.funcs.getTime() - screen->frameTime >= 13) {
        screen->frameTime = GFX.funcs.getTime();
        for (i = 0; i < screen->count; i++) {
            id = GAME.funcs.getPartyMember(i);
            screen->frames[i]++;
            if (STSTATUS_data.partnerAnims[id].frames[screen->frames[i]] == -1 ||
                screen->frames[i] >= 7) {
                screen->frames[i] = 0;
            }
        }
    }
    sprite.setTexture(0x280, 0x100);
    for (i = 0; i < screen->count; i++) {
        if (screen->pageFades[i].level != 0) {
            if (screen->pageFades[i].level != 0x1000) {
                sprite.setScale(screen->pageFades[i].level, screen->pageFades[i].level, 0x1000);
                sprite.setPivot(0x7C, i * 0x2E + 0x27);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            id = GAME.funcs.getPartyMember(i);
            sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16),
                        STSTATUS_data.partnerAnims[id].frames[screen->frames[i]], 0x6B,
                        i * 0x2E + 0x13);
        }
    }
    sprite.setTexture(0x140, 0);
    for (i = 0; i < screen->count; i++) {
        if (screen->pageFades[i].level != 0) {
            /* both branches draw the frame's last part: the match depends on it */
            if (screen->pageFades[i].level != 0x1000) {
                sprite.setScale(screen->pageFades[i].level, 0x1000, 0x1000);
                sprite.setPivot(0, i * 0x2E + 0x25);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, i * 0x2E + 0x11);
                sprite.setScale(screen->pageFades[i].level, screen->pageFades[i].level, 0x1000);
                sprite.setPivot(0x7C, i * 0x2E + 0x27);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, i * 0x2E + 0x13);
                sprite.setScale(screen->pageFades[i].level, 0x1000, 0x1000);
                sprite.setPivot(0, i * 0x2E + 0x25);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, i * 0x2E + 0x11);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, i * 0x2E + 0x11);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, i * 0x2E + 0x13);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, i * 0x2E + 0x11);
            }
        }
    }
    if (screen->panelFades[0].level != 0) {
        sprite.setTexture(0x280, 0x100);
        if (screen->panelFades[0].level != 0x1000) {
            sprite.setScale(screen->panelFades[0].level, screen->panelFades[0].level, 0x1000);
            sprite.setPivot(0x7C, 0x27);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        id = GAME_FUNCS.getPartyMember(screen->member);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16),
                    STSTATUS_data.partnerAnims[id].frames[screen->frames[screen->member]], 0x6B, 0x13);
        sprite.setTexture(0x140, 0);
        if (screen->panelFades[0].level != 0x1000) {
            sprite.setScale(screen->panelFades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x25);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, 0x11);
            sprite.setScale(screen->panelFades[0].level, screen->panelFades[0].level, 0x1000);
            sprite.setPivot(0x7C, 0x27);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, 0x13);
            sprite.setScale(screen->panelFades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x25);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, 0x11);
        } else {
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, 0x11);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, 0x13);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, 0x11);
        }
    }
    if (screen->fades[0].level != 0) {
        if (screen->fades[0].level != 0x1000) {
            sprite.setScale(screen->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x19);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x18, 0x22, 0xD);
    }
    if (screen->panelFades[5].level != 0) {
        if (screen->panelFades[5].level != 0x1000) {
            sprite.setScale(screen->panelFades[5].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x47);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x1A, 0, 0x3D);
    }
    sprite.setTexture(0x280, 0x100);
    if (screen->fades[1].level != 0) {
        if (screen->fades[1].level != 0x1000) {
            sprite.setScale(screen->fades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xD3);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x20, 0, 0xC2);
    }
    if (screen->panelFades[2].level != 0) {
        if (screen->panelFades[2].level != 0x1000) {
            sprite.setScale(screen->panelFades[2].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x88);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xF, 0, 0x57);
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x21, 0, 0x54);
        if (screen->panelFades[2].level != 0x1000) {
            sprite.setPivot(0, 0xD0);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x3C, 0, 0xC4);
    }
    if (screen->panelFades[3].level != 0) {
        if (screen->panelFades[3].level != 0x1000) {
            sprite.setScale(screen->panelFades[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x55);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x22, 0xA0, 0x35);
    }
    if (screen->panelFades[4].level != 0) {
        if (screen->panelFades[4].level != 0x1000) {
            sprite.setScale(screen->panelFades[4].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xAC);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            stats = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(screen->member));
            for (i = 0; i < 6; i++) {
                item = stats->equip[i];
                if (item > 0) {
                    sprite.setTexture(0x140, 0);
                    sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), ITEM_FUNCS->getCategory(item), 0xB2,
                                i * 14 + 0x89);
                }
            }
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x23, 0xA0, 0x77);
    }
    if (screen->panelFades[1].level != 0) {
        if (screen->panelFades[1].level != 0x1000) {
            sprite.setScale(screen->panelFades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x20);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x1F, 0x14, 0xD);
    }
    if (screen->cursorShown) {
        if (GFX.funcs.getTime() - screen->cursorTime >= 9) {
            screen->cursorTime = GFX.funcs.getTime();
            screen->cursorFrame++;
            if (screen->cursorFrame >= 8) {
                screen->cursorFrame = 0;
            }
        }
        initSpriteDrawer(&sprite);
        sprite.setLayerId(screen->layer, screen->depth - 1);
        sprite.setTexture(0x280, 0x100);
        sprite.setClutRow(screen->cursorFrame);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x1E, 0, screen->member * 0x2E + 0x11);
    }
}

/* Runs the fifth screen's question: the panels come in, the cursor picks
   one of the two options and the panels go out */
void func_8008CC5C(StatusScreen4 *screen, StatusScreen4Windows *windows) {
    s32 option;
    s16 unused[4]; /* unused, but it is in the original stack frame */

    switch (screen->step) {
    case 0:
    default:
        if (screen->counter == 0) {
            STSTATUS_data.funcs.startFade(&screen->panelFades[0], 1);
        }
        STSTATUS_data.funcs.startFade(&screen->panelFades[1], 1);
        screen->step++;
        break;
    case 1:
        if (screen->counter == 0) {
            STSTATUS_data.funcs.updateFade(&screen->panelFades[0]);
        }
        if (STSTATUS_data.funcs.updateFade(&screen->panelFades[1])) {
            if (screen->panelFades[5].level == 0) {
                STSTATUS_data.funcs.startFade(&screen->panelFades[5], 1);
            }
            STSTATUS_data.funcs.startFade(&screen->panelFades[3], 1);
            func_8008B1B8(screen, windows, screen->member, 1);
            func_8008B38C(screen, windows, 1);
            screen->step++;
        }
        break;
    case 2:
        STSTATUS_data.funcs.updateFade(&screen->panelFades[5]);
        if (STSTATUS_data.funcs.updateFade(&screen->panelFades[3])) {
            if (screen->panelFades[2].level == 0) {
                STSTATUS_data.funcs.startFade(&screen->panelFades[2], 1);
            }
            STSTATUS_data.funcs.startFade(&screen->panelFades[4], 1);
            func_8008B440(screen, windows, 1);
            windows->unk9C->setNumber(windows->unk9C, 0,
                                      ((PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(screen->member)))->unk18);
            windows->unk9C->setRightAlign(windows->unk9C, 1);
            windows->unkA0->setString(windows->unkA0, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x35);
            windows->cursor->setPos(windows->cursor, 0x98, screen->option * 14 + 0x13);
            windows->cursor->setVisible(windows->cursor, 1);
            screen->step++;
        }
        break;
    case 3:
        STSTATUS_data.funcs.updateFade(&screen->panelFades[2]);
        if (STSTATUS_data.funcs.updateFade(&screen->panelFades[4])) {
            func_8008B628(screen, windows, 1);
            func_8008B7A0(screen, windows, 1);
            screen->step = 5;
        }
        break;
    case 5:
        option = screen->option;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->option = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->option = 1;
        }
        if (option != screen->option) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0x98, screen->option * 14 + 0x13);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            screen->step = 10;
            screen->counter = 0;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->step = 10;
            screen->option = 0;
            screen->counter = 1;
        }
        break;
    case 10:
        if (screen->counter) {
            STSTATUS_data.funcs.startFade(&screen->panelFades[0], 0);
            func_8008B1B8(screen, windows, 0, 0);
        }
        STSTATUS_data.funcs.startFade(&screen->panelFades[1], 0);
        STSTATUS_data.funcs.startFade(&screen->panelFades[3], 0);
        STSTATUS_data.funcs.startFade(&screen->panelFades[4], 0);
        func_8008B38C(screen, windows, 0);
        func_8008B440(screen, windows, 0);
        func_8008B628(screen, windows, 0);
        if (screen->option == 0) {
            STSTATUS_data.funcs.startFade(&screen->panelFades[5], 0);
            STSTATUS_data.funcs.startFade(&screen->panelFades[2], 0);
            func_8008B7A0(screen, windows, 0);
            windows->unk9C->setVisible(windows->unk9C, 0);
            windows->unkA0->setVisible(windows->unkA0, 0);
        }
        windows->cursor->setVisible(windows->cursor, 0);
        screen->step++;
        break;
    case 11:
        if (screen->counter) {
            STSTATUS_data.funcs.updateFade(&screen->panelFades[0]);
        }
        STSTATUS_data.funcs.updateFade(&screen->panelFades[1]);
        STSTATUS_data.funcs.updateFade(&screen->panelFades[3]);
        if (screen->option == 0) {
            STSTATUS_data.funcs.updateFade(&screen->panelFades[2]);
            STSTATUS_data.funcs.updateFade(&screen->panelFades[5]);
        }
        if (STSTATUS_data.funcs.updateFade(&screen->panelFades[4])) {
            screen->step++;
        }
        break;
    case 12:
        if (screen->counter) {
            screen->setSubstate(screen, 0);
        } else {
            screen->setSubstate(screen, 0x14);
        }
        break;
    }
}

/* The fifth screen's steps: the pages fade in, a party member is chosen and
   its panel opens, then the pages fade out */
void func_8008D380(StatusScreen4 *screen, StatusScreen4Windows *windows) {
    s32 member;

    switch (screen->substate) {
    case 0:
    default:
        STSTATUS_data.funcs.startFade(&screen->pageFades[0], 1);
        STSTATUS_data.funcs.startFade(&screen->fades[0], 1);
        if (screen->count == 1) {
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
        }
        screen->substate = screen->count;
        break;
    case 1:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x30);
            windows->help2->setString(windows->help2, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            screen->substate = 10;
        }
        break;
    case 2:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            screen->substate = 4;
        }
        break;
    case 4:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x30);
            windows->help2->setString(windows->help2, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            screen->substate = 10;
        }
        break;
    case 3:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            screen->substate = 5;
        }
        break;
    case 5:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            screen->substate++;
        }
        break;
    case 6:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 2, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x30);
            windows->help2->setString(windows->help2, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            screen->substate = 10;
        }
        break;
    case 10:
        screen->cursorShown = 1;
        screen->substate++;
        break;
    case 11:
        member = screen->member;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->member--;
            if (screen->member < 0) {
                screen->member = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->member++;
            if (screen->member > screen->count - 1) {
                screen->member = screen->count - 1;
            }
        }
        if (member != screen->member) {
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            screen->cursorShown = 0;
            screen->option = 0;
            screen->setSubstate(screen, 0x32);
            screen->step = 1;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->cursorShown = 0;
            screen->setSubstate(screen, 0x32);
        }
        break;
    case 15:
        func_8008CC5C(screen, windows);
        break;
    case 0x14:
        if (screen->option == 0) {
            if (windows->panel == NULL) {
                windows->panel = func_8008AB04(screen);
            }
        } else if (windows->panel == NULL) {
            windows->panel = func_800879C8(screen);
        }
        screen->substate++;
        break;
    case 0x15:
        if (windows->panel == NULL) {
            screen->setSubstate(screen, 15);
            screen->counter = 1;
        }
        break;
    case 0x32:
        STSTATUS_data.funcs.startFade(&screen->pageFades[screen->count - 1], 0);
        func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, screen->count - 1, 0);
        STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
        windows->help->setVisible(windows->help, 0);
        windows->help2->setVisible(windows->help2, 0);
        if (screen->count == 1) {
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
        }
        screen->substate = screen->count + 0x32;
        break;
    case 0x33:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            screen->substate = 0x39;
        }
        break;
    case 0x34:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            windows->title->setVisible(windows->title, 0);
            screen->substate = 0x36;
        }
        break;
    case 0x35:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 1, 0);
            screen->substate = 0x37;
        }
        break;
    case 0x37:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            func_8008AF7C((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            windows->title->setVisible(windows->title, 0);
            screen->substate++;
        }
        break;
    case 0x36:
    case 0x38:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            screen->substate = 0x39;
        }
        break;
    case 0x39:
        if (screen->step) {
            screen->setSubstate(screen, 15);
        } else {
            screen->state = 3;
        }
        break;
    }
}

void func_8008DCF0(StatusScreen4 *screen, StatusScreen4Windows *windows) {
    s32 i;

    switch (screen->state) {
    case 0:
    default:
        screen->nextState(screen);
        for (i = 0; i < 3; i++) {
            if (GAME.funcs.getPartyMember(i) >= 0) {
                screen->count++;
            }
        }
        for (i = 0; i < screen->count; i++) {
            screen->pageFades[i].duration = 10;
            STSTATUS_data.funcs.startFade(&screen->pageFades[i], 1);
        }
        for (i = 0; i < 2; i++) {
            screen->fades[i].duration = 10;
            STSTATUS_data.funcs.startFade(&screen->fades[i], 1);
        }
        screen->panelFades[0].duration = 10;
        screen->panelFades[1].duration = 10;
        screen->panelFades[2].duration = 10;
        screen->panelFades[4].duration = 10;
        screen->panelFades[3].duration = 10;
        screen->panelFades[5].duration = 10;
        screen->fade.duration = 8;
        func_8008AB58(screen, windows);
        break;
    case 1:
        func_8008D380(screen, windows);
        func_8008BF2C(screen);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_8008DEA4(FieldMenuScreen *menu, s32 extra) {
    StatusScreen4 *screen = createTask(func_8008DCF0, sizeof(StatusScreen4), sizeof(StatusScreen4Windows));

    screen->func_8008BA38 = func_8008BA38;
    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}
