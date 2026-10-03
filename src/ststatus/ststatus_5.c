/* The fifth object of STSTATUS.PRO (see ststatus.c), the fifth screen
   (func_8008DEA4): its rodata starts at 0x800828B0 (USA). */

#include "ststatus.h"

void func_8008AB58(StatusScreen4 *screen, StatusScreen4Windows *windows);
void func_8008BF2C(StatusScreen4 *screen);
void func_8008D380(StatusScreen4 *screen, StatusScreen4Windows *windows);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_5", func_8008AB58);

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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_5", func_8008B440);

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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_5", func_8008BA38);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_5", func_8008BF2C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_5", func_8008CC5C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_5", func_8008D380);

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
