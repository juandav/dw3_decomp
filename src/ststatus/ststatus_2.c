/* The second object of STSTATUS.PRO (see ststatus.c), the second screen
   with the party's pages (func_80085B90): its rodata starts at 0x800825E4
   (USA). */

#include "ststatus.h"

/* As func_80082E18, without moving the children above the screen */
void func_800846C0(StatusScreen1 *screen, StatusWindows1 *windows) {
    s32 i;
    s32 j;
    WindowPos *pos;

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
    windows->unk88 = createTextWindow(screen->layer, 1, pos->x, pos->y + 14);
    windows->unk8C = createTextWindow(screen->layer, 1, 0xB2, 0x2A);
    for (i = 0; i < 2; i++) {
        windows->options[i] = createTextWindow(screen->layer, 1, 0xC5, 0x3A + i * 14);
    }
    windows->cursor = createCursor(screen->layer, screen->depth - 1, 0xB8, 0x3A);
    windows->cursor->setVisible(windows->cursor, 0);
}

/* As func_800830AC */
void func_80084908(StatusScreen1 *screen, StatusWindows1 *windows, s32 member, s32 show) {
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
            windows->pages[member].values[i]->setNumber(windows->pages[member].values[i], 0, stats.stats[D_80099AAC[i]]);
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

/* As func_800832E8, for the second screen: the options are GAME.unk4's two
   values, the current one highlighted */
void func_80084B44(StatusScreen1 *screen, StatusWindows1 *windows, s32 show) {
    s32 i;

    if (show) {
        windows->unk8C->setString(windows->unk8C, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x46);
        for (i = 0; i < 2; i++) {
            windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0xB1)), i + 0x47);
        }
        screen->choice = 1 - (u8)GAME.unk4;
        windows->cursor->setPos(windows->cursor, 0xB8, screen->choice * 14 + 0x3A);
        if (screen->choice == 0) {
            windows->options[0]->setPalette(windows->options[0], 1);
            windows->options[1]->setPalette(windows->options[1], 0);
        } else {
            windows->options[0]->setPalette(windows->options[0], 0);
            windows->options[1]->setPalette(windows->options[1], 1);
        }
        windows->cursor->setVisible(windows->cursor, 1);
    } else {
        windows->unk8C->setVisible(windows->unk8C, 0);
        for (i = 0; i < 2; i++) {
            windows->options[i]->setVisible(windows->options[i], 0);
        }
        windows->cursor->setVisible(windows->cursor, 0);
    }
}

/* As func_8008340C, for the second screen */
void func_80084D14(StatusScreen1 *screen) {
    SpriteDrawer sprite;
    s32 member;
    s32 level;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layer, screen->depth);
    if (GFX.funcs.getTime() - screen->frameTime >= 13) {
        screen->frameTime = GFX.funcs.getTime();
        for (i = 0; i < screen->count; i++) {
            member = GAME.funcs.getPartyMember(i);
            screen->frames[i]++;
            if (STSTATUS_data.partnerAnims[member].frames[screen->frames[i]] == -1 || screen->frames[i] >= 7) {
                screen->frames[i] = 0;
            }
        }
    }
    for (i = 0; i < screen->count; i++) {
        level = screen->pageFades[i].level;
        if (level != 0) {
            if (level != 0x1000) {
                sprite.setScale(level, level, 0x1000);
                sprite.setPivot(0x7C, i * 46 + 0x27);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            member = GAME.funcs.getPartyMember(i);
            sprite.setTexture(0x280, 0x100);
            sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16),
                        STSTATUS_data.partnerAnims[member].frames[screen->frames[i]], 0x6B, i * 46 + 0x13);
        }
    }
    sprite.setTexture(0x140, 0);
    for (i = 0; i < screen->count; i++) {
        level = screen->pageFades[i].level;
        if (level != 0) {
            /* both branches draw the frame's last part: the match depends on it */
            if (level != 0x1000) {
                sprite.setScale(level, 0x1000, 0x1000);
                sprite.setPivot(0, i * 46 + 0x25);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, i * 46 + 0x11);
                sprite.setScale(screen->pageFades[i].level, screen->pageFades[i].level, 0x1000);
                sprite.setPivot(0x7C, i * 46 + 0x27);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, i * 46 + 0x13);
                sprite.setScale(screen->pageFades[i].level, 0x1000, 0x1000);
                sprite.setPivot(0, i * 46 + 0x25);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, i * 46 + 0x11);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x15, 0, i * 46 + 0x11);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x16, 0x67, i * 46 + 0x13);
                sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x17, 0, i * 46 + 0x11);
            }
        }
    }
    level = screen->fades[1].level;
    if (level != 0) {
        if (level != 0x1000) {
            sprite.setScale(level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xD3);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_STATUS_SPRITES << 16), 0x20, 0, 0xC2);
    }
    if (screen->fade.level != 0) {
        initSpriteDrawer(&sprite);
        sprite.setLayerId(screen->layer, screen->depth);
        sprite.setTexture(0x280, 0x100);
        level = screen->fade.level;
        if (level != 0x1000) {
            sprite.setScale(level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x40);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_STATUS_SPRITES << 16), 0x3A, 0xA8, 0x28);
    }
}

/* As func_800839B0, for the second screen: the choice sets GAME.unk4 */
void func_800852B8(StatusScreen1 *screen, StatusWindows1 *windows) {
    s32 choice;

    switch (screen->substate) {
    case 0:
    default:
        STSTATUS_data.funcs.startFade(&screen->pageFades[0], 1);
        if (screen->count == 1) {
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fade, 1);
        }
        screen->substate = screen->count;
        break;
    case 1:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_80084908(screen, windows, 0, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x49);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_80084B44(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 2:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_80084908(screen, windows, 0, 1);
            screen->substate = 4;
        }
        break;
    case 4:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_80084908(screen, windows, 1, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x49);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_80084B44(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 3:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            func_80084908(screen, windows, 0, 1);
            screen->substate = 5;
        }
        break;
    case 5:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_80084908(screen, windows, 1, 1);
            screen->substate++;
        }
        break;
    case 6:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_80084908(screen, windows, 2, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x49);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_80084B44(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 10:
        choice = screen->choice;
        if (PAD_PRESSED(PAD_UP)) {
            screen->choice = 0;
        } else if (PAD_PRESSED(PAD_DOWN)) {
            screen->choice = 1;
        }
        if (choice != screen->choice) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0xB8, screen->choice * 14 + 0x3A);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (screen->choice == 0) {
                GAME.unk4 = 1;
            } else {
                GAME.unk4 = 0;
            }
            screen->substate = 0x32;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->substate = 0x32;
        }
        break;
    case 0x32:
        STSTATUS_data.funcs.startFade(&screen->pageFades[screen->count - 1], 0);
        func_80084908(screen, windows, screen->count - 1, 0);
        STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
        windows->help->setVisible(windows->help, 0);
        windows->unk88->setVisible(windows->unk88, 0);
        STSTATUS_data.funcs.startFade(&screen->fade, 0);
        func_80084B44(screen, windows, 0);
        screen->substate = screen->count + 0x32;
        break;
    case 0x33:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[0]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            screen->substate = 0x39;
        }
        break;
    case 0x34:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            func_80084908(screen, windows, 0, 0);
            screen->substate = 0x36;
        }
        break;
    case 0x35:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            func_80084908(screen, windows, 1, 0);
            screen->substate = 0x37;
        }
        break;
    case 0x37:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            func_80084908(screen, windows, 0, 0);
            screen->substate++;
        }
        break;
    case 0x36:
    case 0x38:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[0])) {
            screen->substate = 0x39;
        }
        break;
    case 0x39:
        screen->state = 3;
        break;
    }
}

/* As func_80084204, for the second screen */
void func_800859E0(StatusScreen1 *screen, StatusWindows1 *windows) {
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
        screen->fade.duration = 10;
        STSTATUS_data.funcs.startFade(&screen->fade, 1);
        func_800846C0(screen, windows);
        break;
    case 1:
        func_800852B8(screen, windows);
        func_80084D14(screen);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_80085B90(FieldMenuScreen *menu, s32 extra) {
    StatusScreen1 *screen = createTask(func_800859E0, 0xD4, 0x9C);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}
