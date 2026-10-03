/* The eighth object of STSTATUS.PRO (see ststatus.c), the screen of
   func_80095934: its rodata starts at 0x80082BA4 (USA). */

#include "ststatus.h"

s32 func_80092C38(StatusScreen8 *screen, s32 member);
void func_80093B0C(StatusScreen8 *screen);
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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_8", func_80092EEC);

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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_8", func_80093B0C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_8", func_8009440C);

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
