/* The eighth object of STSTATUS.PRO (see ststatus.c), the screen of
   func_80095934: its rodata starts at 0x80082BA4 (USA). */

#include "ststatus.h"

s32 func_80092C38(StatusScreen8 *screen, s32 member);
void func_80093B0C(StatusScreen8 *screen);
void func_800935C0(StatusScreen *screen, StatusPagesB *windows, s32 member, s32 show);
void func_8009440C(StatusScreen8 *screen, StatusTechWindows *windows);

void func_80092B80(StatusPanel0 *panel) {
    s32 i;

    if (panel->list == 0) {
        panel->count = ITEM_FUNCS->list(D_80099BA4[0], panel->bag);
        for (i = 0; i < panel->count; i++) {
            panel->items[i] = panel->bag[i];
        }
    } else {
        panel->count = ITEM_FUNCS->list(D_80099BA4[panel->list], panel->items);
    }
}

/* Lists the techniques of a party member that can be used here (0xB8-0xBC),
   each once, and returns how many */
s32 func_80092C38(StatusScreen8 *screen, s32 member) {
    StatusTechRow *row;
    StatusPartnerEntry *entry;
    s16 *techs;
    s32 partner;
    s32 count;
    s32 found;
    s32 i;
    s32 j;
    s32 k;
    s32 tech;

    partner = GAME.funcs.getPartyMember(member);
    GAME.funcs.getPartnerSlots(partner, screen->rows[member].slots);
    /* count set with i, row in the loop, techs and found set with k: the
       match depends on them, which give the registers */
    for (i = 0, count = 0; i < 3; i++) {
        row = &screen->rows[member];
        if (screen->rows[member].slots[i] >= 3) {
            entry = &row->entries[i];
            GAME_FUNCS.getPartnerEntry(partner, screen->rows[member].slots[i], entry);
            for (j = 0; j < 6; j++) {
                tech = entry->techs[j] & 0x1FFF;
                if (tech >= 0xB8 && tech < 0xBD) {
                    techs = row->techs;
                    for (k = 0, found = 0; k < 5; k++) {
                        if (tech == techs[k]) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        screen->rows[member].techs[count++] = tech;
                        if (count >= 5) {
                            return count;
                        }
                    }
                }
            }
        }
    }
    return count;
}

/* The chosen technique, or 0 if its user hasn't the MP for it */
s32 func_80092DC4(StatusScreen8 *screen) {
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(screen->member));
    s16 tech = screen->rows[screen->member].techs[screen->cursor];

    if (D_800427E8[tech - 1].mp <= stats->stats[4]) {
        return tech;
    }
    return 0;
}

/* A technique's healing: its power a bit more than 64 times, with a
   partner's stat 9 */
s32 func_80092E7C(s32 partner, s32 tech) {
    PartnerTotals stats;
    StatusTech *info;
    s32 power;

    GAME_FUNCS.computeStats(partner, &stats);
    info = D_800427E8 + tech - 1; /* the match depends on this pointer */
    power = info->power;
    return (power << 6) + power * stats.stats[9] / 8;
}

/* Uses the chosen healing technique on the target or on the whole party,
   then plays FAILSOUND and says so if no one needed it; returns whether it
   healed anyone */
s32 func_80092EEC(StatusScreen8 *screen, StatusTechWindows *windows, s32 failSound) {
    /* the user's and the target's ids: the match depends on them being in
       memory, as an array */
    s32 ids[2];
    PartnerStats *user;
    PartnerStats *target;
    s32 tech;
    s32 power;
    s32 healed;
    s32 full;
    s32 i;

    tech = screen->rows[screen->member].techs[screen->cursor];
    ids[0] = GAME.funcs.getPartyMember(screen->member);
    user = (PartnerStats *)GAME.funcs.getPartnerStats(ids[0]);
    power = func_80092E7C(ids[0], tech);
    if (D_800427E8[tech - 1].kind == 3) {
        ids[1] = GAME.funcs.getPartyMember(screen->target);
        target = (PartnerStats *)GAME.funcs.getPartnerStats(ids[1]);
        if (target->stats[2] < target->stats[3]) {
            user->stats[4] -= D_800427E8[tech - 1].mp;
            target->stats[2] += power;
            if (target->stats[2] > target->stats[3]) {
                target->stats[2] = target->stats[3];
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x52);
            } else {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x53);
                windows->help->setNumber(windows->help, 1, power);
            }
            for (i = 0; i < screen->count; i++) {
                func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, i, 1);
            }
            SOUND.playSound(0x40014);
            return 1;
        }
    } else {
        i = 0;
        healed = 0;
        full = 0;
        for (; i < screen->count; i++) {
            ids[1] = GAME.funcs.getPartyMember(i);
            if (ids[1] >= 0) {
                target = (PartnerStats *)GAME.funcs.getPartnerStats(ids[1]);
                if (target->stats[2] < target->stats[3]) {
                    target->stats[2] += power;
                    if (target->stats[2] > target->stats[3]) {
                        target->stats[2] = target->stats[3];
                        full++;
                    }
                    /* the match depends on this coming after full++ */
                    healed = 1;
                } else {
                    full++;
                }
            }
        }
        if (healed) {
            user->stats[4] -= D_800427E8[tech - 1].mp;
            for (i = 0; i < screen->count; i++) {
                func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, i, 1);
            }
            if (full == screen->count) {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x52);
            } else {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x53);
                windows->help->setNumber(windows->help, 1, power);
            }
            SOUND.playSound(0x40014);
            return 1;
        }
    }
    SOUND.playSound(failSound);
    windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x6A);
    return 0;
}

void func_80093300(StatusScreen8 *screen, StatusTechWindows *windows) {
    s32 i;
    s32 j;
    WindowPos *pos;
    WindowPos *layout;

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
    layout = STSTATUS_data.layout;
    pos = &layout[12];
    windows->help = createTextWindow(screen->layer, 1, pos->x, pos->y);
    windows->help->setLines(windows->help, 2);
    windows->help2 = createTextWindow(screen->layer, 1, pos->x, pos->y + 14);
    pos = &layout[13];
    windows->mpLabel = createTextWindow(screen->layer, 1, pos->x, pos->y);
    pos = &layout[14];
    windows->mp = createTextWindow(screen->layer, 1, pos->x, pos->y);
    windows->listTitle = createTextWindow(screen->layer, 1, 0x9C, 0x31);
    for (i = 0; i < 5; i++) {
        windows->techs[i] = createTextWindow(screen->layer, 1, 0xB1, 0x41 + i * 14);
    }
    windows->cursor = createCursor(screen->layer, screen->depth - 1, 0xA6, screen->cursor * 14 + 0x41);
    windows->cursor->setVisible(windows->cursor, 0);
}

/* As func_800830AC */
void func_800935C0(StatusScreen *screen, StatusPagesB *windows, s32 member, s32 show) {
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
            windows->pages[member].values[i]->setNumber(windows->pages[member].values[i], 0, stats.stats[D_80099C50[i]]);
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

/* Shows or hides the list of the party member's techniques */
void func_800937FC(StatusScreen8 *screen, StatusTechWindows *windows, s32 show) {
    s32 i;

    if (show) {
        windows->listTitle->setString(windows->listTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), 9);
        for (i = 0; i < screen->rows[screen->member].techCount; i++) {
            windows->techs[i]->setString(windows->techs[i], FILE_CACHE.load(TEXT_FILE(0xA3)),
                                         screen->rows[screen->member].techs[i] & 0x1FFF);
        }
    } else {
        windows->listTitle->setVisible(windows->listTitle, 0);
        for (i = 0; i < screen->rows[screen->member].techCount; i++) {
            windows->techs[i]->setVisible(windows->techs[i], 0);
        }
    }
}

/* Shows or hides the chosen technique's name and MP cost */
void func_800939BC(StatusScreen8 *screen, StatusTechWindows *windows, s32 show) {
    s32 tech;

    if (show) {
        tech = screen->rows[screen->member].techs[screen->cursor] & 0x1FFF;
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x9C)), tech);
        windows->mpLabel->setString(windows->mpLabel, FILE_CACHE.load(TEXT_FILE(0xB1)), 3);
        windows->mp->setNumber(windows->mp, 0, D_800427E8[tech - 1].mp);
        windows->mp->setRightAlign(windows->mp, 1);
    } else {
        windows->help->setVisible(windows->help, 0);
        windows->mpLabel->setVisible(windows->mpLabel, 0);
        windows->mp->setVisible(windows->mp, 0);
    }
}

/* Draws the partners' portraits and frames, the cursors and the help arrow */
void func_80093B0C(StatusScreen8 *screen) {
    SpriteDrawer sprite;
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
    for (i = 0; i < screen->count; i++) {
        if (screen->pageFades[i].level != 0) {
            if (screen->pageFades[i].level != 0x1000) {
                sprite.setScale(screen->pageFades[i].level, screen->pageFades[i].level, 0x1000);
                sprite.setPivot(0x7C, i * 0x2E + 0x27);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            id = GAME.funcs.getPartyMember(i);
            sprite.setTexture(0x280, 0x100);
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
    if (screen->fades[0].level != 0) {
        if (screen->fades[0].level != 0x1000) {
            sprite.setScale(screen->fades[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x19);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x18, 0x22, 0xD);
    }
    if (screen->fades[1].level != 0) {
        if (screen->blink) {
            if (GFX.funcs.getTime() - screen->blinkTime >= 4) {
                screen->blinkTime = GFX.funcs.getTime();
                screen->blinkFrame++;
                if (screen->blinkFrame >= 5) {
                    screen->blinkFrame = 0;
                }
            }
            sprite.setTexture(0x140, 0);
            sprite.setClutRow(screen->blinkFrame);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xA, 0x123, 0xD6);
            sprite.setClutRow(0);
        }
        if (screen->fades[1].level != 0x1000) {
            sprite.setScale(screen->fades[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xD3);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x20, 0, 0xC2);
    }
    if (GFX.funcs.getTime() - screen->cursorTime >= 9) {
        screen->cursorTime = GFX.funcs.getTime();
        screen->cursorFrame++;
        if (screen->cursorFrame >= 8) {
            screen->cursorFrame = 0;
        }
    }
    if (screen->targetShown) {
        initSpriteDrawer(&sprite);
        sprite.setLayerId(screen->layer, screen->depth - 1);
        sprite.setTexture(0x280, 0x100);
        sprite.setClutRow(screen->cursorFrame);
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x1E, 0, screen->target * 0x2E + 0x11);
    }
    if (screen->memberShown) {
        initSpriteDrawer(&sprite);
        sprite.setLayerId(screen->layer, screen->depth - 1);
        sprite.setTexture(0x280, 0x100);
        /* the match depends on two calls, not a conditional argument */
        if (screen->substate >= 0x1E) {
            sprite.setClutRow(8);
        } else {
            sprite.setClutRow(screen->cursorFrame);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x1E, 0, screen->member * 0x2E + 0x11);
    }
    if (screen->fade.level != 0) {
        initSpriteDrawer(&sprite);
        sprite.setLayerId(screen->layer, screen->depth);
        sprite.setTexture(0x280, 0x100);
        if (screen->fade.level != 0x1000) {
            sprite.setScale(screen->fade.level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x63);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), D_80099C64[screen->rows[screen->member].techCount - 1],
                    0x94, 0x2F);
    }
}

/* The technique screen's update: opens the pages, picks who uses a
   technique, which one and on whom, then closes them */
void func_8009440C(StatusScreen8 *screen, StatusTechWindows *windows) {
    s32 member; /* case 11 has its own variable: the match depends on it */
    s32 old;
    s32 tech;

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
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            screen->substate = 10;
        }
        break;
    case 2:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            screen->substate = 4;
        }
        break;
    case 4:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            screen->substate = 10;
        }
        break;
    case 3:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 1);
            screen->substate = 5;
        }
        break;
    case 5:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 1);
            screen->substate++;
        }
        break;
    case 6:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 2, 1);
            screen->substate = 10;
        }
        break;
    case 10:
        screen->memberShown = 1;
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x28);
        windows->help2->setString(windows->help2, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
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
            screen->substate = 15;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->substate = 0x32;
        }
        break;
    case 15:
        if (screen->rows[screen->member].techCount != 0) {
            screen->fade.duration = 8;
            STSTATUS_data.funcs.startFade(&screen->fade, 1);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2A);
            windows->help->setVisible(windows->help, 0);
            windows->help2->setVisible(windows->help2, 0);
            screen->substate = 0x1E;
        } else {
            screen->substate = 0x10;
        }
        break;
    case 0x10:
        screen->memberShown = 0;
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x29);
        windows->help2->setVisible(windows->help2, 0);
        screen->blink = 1;
        screen->substate++;
        break;
    case 0x11:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            screen->memberShown = 1;
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x28);
            windows->help2->setVisible(windows->help2, 1);
            screen->blink = 0;
            screen->substate = 11;
        }
        break;
    case 0x1E:
        if (STSTATUS_data.funcs.updateFade(&screen->fade)) {
            screen->cursor = 0;
            func_800937FC(screen, windows, 1);
            func_800939BC(screen, windows, 1);
            windows->cursor->setPos(windows->cursor, 0xA6, screen->cursor * 0xE + 0x41);
            windows->cursor->setVisible(windows->cursor, 1);
            screen->substate++;
        }
        break;
    case 0x1F:
        old = screen->cursor;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->cursor--;
            if (screen->cursor < 0) {
                screen->cursor = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->cursor++;
            if (screen->cursor > screen->rows[screen->member].techCount - 1) {
                screen->cursor = screen->rows[screen->member].techCount - 1;
            }
        }
        if (old != screen->cursor) {
            windows->cursor->setPos(windows->cursor, 0xA6, screen->cursor * 0xE + 0x41);
            func_800939BC(screen, windows, 1);
            SOUND.playSound(0x8004513E);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            tech = func_80092DC4(screen);
            if (tech != 0) {
                if (D_800427E8[tech - 1].kind == 3) {
                    SOUND.playSound(0x8004503C);
                    screen->targetShown = 1;
                    windows->cursor->setPalette(windows->cursor, 7);
                    windows->cursor->setStill(windows->cursor, 1);
                    windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2B);
                    screen->substate++;
                } else {
                    windows->cursor->setPalette(windows->cursor, 7);
                    windows->cursor->setStill(windows->cursor, 1);
                    func_800939BC(screen, windows, 0);
                    screen->step = screen->substate;
                    func_80092EEC(screen, windows, 0x8004503C);
                    screen->substate = 0x24;
                    screen->blink = 1;
                }
            } else {
                SOUND.playSound(0x8004503C);
                windows->cursor->setPalette(windows->cursor, 7);
                windows->cursor->setStill(windows->cursor, 1);
                func_800939BC(screen, windows, 0);
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x69);
                screen->substate = 0x23;
                screen->blink = 1;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            STSTATUS_data.funcs.startFade(&screen->fade, 0);
            func_800937FC(screen, windows, 0);
            func_800939BC(screen, windows, 0);
            windows->cursor->setVisible(windows->cursor, 0);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x27);
            screen->substate = 0x28;
        }
        break;
    case 0x20:
        old = screen->target;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->target--;
            if (screen->target < 0) {
                screen->target = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->target++;
            if (screen->target > screen->count - 1) {
                screen->target = screen->count - 1;
            }
        }
        if (old != screen->target) {
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            func_800939BC(screen, windows, 0);
            if (func_80092DC4(screen) != 0) {
                screen->targetShown = 0;
                screen->step = screen->substate;
                func_80092EEC(screen, windows, 0x4001C);
                screen->substate = 0x24;
            } else {
                SOUND.playSound(0x4001C);
                screen->memberShown = 0;
                screen->targetShown = 0;
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x69);
                screen->substate = 0x23;
            }
            screen->blink = 1;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->substate = 0x1F;
            screen->targetShown = 0;
            windows->cursor->setPalette(windows->cursor, 0);
            windows->cursor->setStill(windows->cursor, 0);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x2A);
        }
        break;
    case 0x23:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            func_800939BC(screen, windows, 1);
            windows->cursor->setPalette(windows->cursor, 0);
            windows->cursor->setStill(windows->cursor, 0);
            screen->substate = 0x1F;
            screen->blink = 0;
        }
        break;
    case 0x24:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            func_800939BC(screen, windows, 1);
            screen->substate = screen->step;
            /* the match depends on testing step, not substate */
            if (screen->step == 0x1F) {
                windows->cursor->setPalette(windows->cursor, 0);
                windows->cursor->setStill(windows->cursor, 0);
            } else {
                screen->targetShown = 1;
            }
            screen->blink = 0;
        }
        break;
    case 0x28:
        if (STSTATUS_data.funcs.updateFade(&screen->fade)) {
            screen->setSubstate(screen, 10);
        }
        break;
    case 0x32:
        screen->memberShown = 0;
        windows->help2->setVisible(windows->help2, 0);
        STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
        func_800939BC(screen, windows, 0);
        STSTATUS_data.funcs.startFade(&screen->pageFades[screen->count - 1], 0);
        func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, screen->count - 1, 0);
        if (screen->count == 1) {
            windows->title->setVisible(windows->title, 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
        }
        screen->substate = screen->count + 0x32;
        break;
    case 0x33:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            screen->state = 3;
        }
        break;
    case 0x34:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
            screen->substate = 0x36;
        }
        break;
    case 0x35:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 1, 0);
            screen->substate = 0x37;
        }
        break;
    case 0x37:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            STSTATUS_data.funcs.startFade(&screen->fades[0], 0);
            windows->title->setVisible(windows->title, 0);
            func_800935C0((StatusScreen *)screen, (StatusPagesB *)windows, 0, 0);
            screen->substate++;
        }
        break;
    case 0x36:
    case 0x38:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[0])) {
            screen->state = 3;
        }
        break;
    }
}

void func_8009576C(StatusScreen8 *screen, StatusTechWindows *windows) {
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
        for (i = 0; i < screen->count; i++) {
            screen->rows[i].techCount = func_80092C38(screen, i);
        }
        func_80093300(screen, windows);
        break;
    case 1:
        func_8009440C(screen, windows);
        func_80093B0C(screen);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_80095934(FieldMenuScreen *menu, s32 extra) {
    StatusScreen8 *screen = createTask(func_8009576C, sizeof(StatusScreen8), sizeof(StatusTechWindows));

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}
