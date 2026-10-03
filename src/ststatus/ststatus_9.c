/* The ninth object of STSTATUS.PRO (see ststatus.c), the screen of
   func_800975FC: its rodata starts at 0x80082C88 (USA). */

#include "ststatus.h"

void func_80095D6C(StatusScreen9 *screen);
void func_80096830(StatusScreen9 *screen, StatusWindows9 *windows);

void func_8009597C(StatusScreen9 *screen, StatusWindows9 *windows) {
    s32 i;
    s32 j;
    WindowPos *pos;

    pos = &STSTATUS_data.layout[11];
    windows->title = createTextWindow(screen->layer, 1, pos->x, pos->y);
    pos = &STSTATUS_data.layout[12];
    windows->help = createTextWindow(screen->layer, 1, pos->x, pos->y);
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
}

/* As func_800830AC */
void func_80095B30(StatusScreen *screen, StatusPagesB *windows, s32 member, s32 show) {
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
            windows->pages[member].values[i]->setNumber(windows->pages[member].values[i], 0, stats.stats[D_80099C78[i]]);
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

INCLUDE_ASM("ststatus/nonmatchings/ststatus_9", func_80095D6C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_9", func_80096830);

void func_80097460(StatusScreen9 *screen, StatusWindows9 *windows) {
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
        }
        STSTATUS_data.funcs.startFade(&screen->pageFades[0], 1);
        for (i = 0; i < 2; i++) {
            screen->fades[i].duration = 10;
            STSTATUS_data.funcs.startFade(&screen->fades[i], 1);
            screen->fade.duration = 8;
            STSTATUS_data.funcs.startFade(&screen->fade, 0);
        }
        func_8009597C(screen, windows);
        break;
    case 1:
        func_80096830(screen, windows);
        func_80095D6C(screen);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_800975FC(FieldMenuScreen *menu, s32 extra) {
    StatusScreen9 *screen = createTask(func_80097460, sizeof(StatusScreen9), sizeof(StatusWindows9));

    screen->layer = 0x1000;
    screen->depth = 2;
    screen->menu = menu;
    return (Task *)screen;
}
