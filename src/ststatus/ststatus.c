/* The first object of STSTATUS.PRO, the screen with the party's pages of
   func_800843B4 and the fader, and the overlay's data. STSTATUS.PRO was ten
   objects, about one per screen: each one's jump tables are aligned to 8
   from the start of its own rodata, and three of them start 4 bytes past a
   multiple of 8. Where each object's code starts is only known to be
   between the function with the last jump table of the object before and
   the one with its first (or the screen's create function); the data is all
   here. */

#include "ststatus.h"

void func_80082CF0(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x14000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)func_80098DE4();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_80082DEC(void) {
    return createTask(func_80082CF0, sizeof(Task), 4);
}

/* Creates the windows of a screen with the party's pages */
void func_80082E18(StatusScreen1 *screen, StatusWindows1 *windows) {
    s32 i;
    s32 j;
    WindowPos *pos;
    TextWindow **children;

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
    children = screen->children;
    for (i = 0; i < screen->childCount - 2; i++, children++) {
        (*children)->setDepth(*children, screen->depth - 1);
    }
}

/* Shows or hides a party member's page: name and five stats (as showPartnerPage) */
void func_800830AC(StatusScreen1 *screen, StatusWindows1 *windows, s32 member, s32 show) {
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
            windows->pages[member].values[i]->setNumber(windows->pages[member].values[i], 0, stats.stats[D_80099A98[i]]);
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

/* Shows or hides the help and the two options with their cursor */
void func_800832E8(StatusScreen1 *screen, StatusWindows1 *windows, s32 show) {
    s32 i;

    if (show) {
        windows->unk8C->setString(windows->unk8C, FILE_CACHE.load(TEXT_FILE(0xB1)), 0xB);
        for (i = 0; i < 2; i++) {
            windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0xB1)), i + 0x4A);
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

/* Draws the party's portraits and their pages' panels */
void func_8008340C(StatusScreen1 *screen) {
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

/* Runs the screen: the pages come in one after the other, the cursor picks
   one of the two options, and the pages go out in reverse */
void func_800839B0(StatusScreen1 *screen, StatusWindows1 *windows) {
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
            func_800830AC(screen, windows, 0, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x4C);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_800832E8(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 2:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_800830AC(screen, windows, 0, 1);
            screen->substate = 4;
        }
        break;
    case 4:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[1]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_800830AC(screen, windows, 1, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x4C);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_800832E8(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 3:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[0])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 1);
            func_800830AC(screen, windows, 0, 1);
            screen->substate = 5;
        }
        break;
    case 5:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[2], 1);
            STSTATUS_data.funcs.startFade(&screen->fades[1], 1);
            func_800830AC(screen, windows, 1, 1);
            screen->substate++;
        }
        break;
    case 6:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            func_800830AC(screen, windows, 2, 1);
            windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x4C);
            windows->unk88->setString(windows->unk88, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x15);
            func_800832E8(screen, windows, 1);
            screen->substate = 10;
        }
        break;
    case 10:
        choice = screen->choice;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            screen->choice = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            screen->choice = 1;
        }
        if (choice != screen->choice) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0xB8, screen->choice * 14 + 0x3A);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            screen->setSubstate(screen, 100);
            if (screen->choice == 0) {
                screen->step = 1;
            } else {
                screen->step = 2;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->setSubstate(screen, 0x32);
        }
        break;
    case 100:
        if (windows->fader == NULL) {
            windows->fader = STSTATUS_createFader();
        }
        screen->substate++;
        break;
    case 101:
        windows->fader->start(windows->fader, 0, 10);
        screen->substate++;
        break;
    case 102:
        if (windows->fader->state == 2) {
            screen->substate = 0x39;
        }
        break;
    case 0x32:
        STSTATUS_data.funcs.startFade(&screen->pageFades[screen->count - 1], 0);
        func_800830AC(screen, windows, screen->count - 1, 0);
        STSTATUS_data.funcs.startFade(&screen->fades[1], 0);
        windows->help->setVisible(windows->help, 0);
        windows->unk88->setVisible(windows->unk88, 0);
        STSTATUS_data.funcs.startFade(&screen->fade, 0);
        func_800832E8(screen, windows, 0);
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
            func_800830AC(screen, windows, 0, 0);
            screen->substate = 0x36;
        }
        break;
    case 0x35:
        STSTATUS_data.funcs.updateFade(&screen->pageFades[2]);
        STSTATUS_data.funcs.updateFade(&screen->fade);
        if (STSTATUS_data.funcs.updateFade(&screen->fades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[1], 0);
            func_800830AC(screen, windows, 1, 0);
            screen->substate = 0x37;
        }
        break;
    case 0x37:
        if (STSTATUS_data.funcs.updateFade(&screen->pageFades[1])) {
            STSTATUS_data.funcs.startFade(&screen->pageFades[0], 0);
            func_800830AC(screen, windows, 0, 0);
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
        if (screen->step == 1) {
            GAME_FUNCS.requestMode(0x1200, 0);
        } else if (screen->step == 2) {
            GAME_FUNCS.requestMode(0x400, 0);
        } else {
            screen->state = 3;
        }
        break;
    }
}

/* The screen's update: counts the party and opens the pages */
void func_80084204(StatusScreen1 *screen, StatusWindows1 *windows) {
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
        func_80082E18(screen, windows);
        break;
    case 1:
        func_800839B0(screen, windows);
        func_8008340C(screen);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_800843B4(FieldMenuScreen *menu, s32 extra) {
    StatusScreen1 *screen = createTask(func_80084204, 0xD4, 0xA0);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}

void STSTATUS_startFader(ScreenFade *task, s32 fadeIn, s32 duration) {
    task->setState(task, TASK_RUN);
    task->substate = 1;
    task->fadeIn = fadeIn;
    if (fadeIn == 0) {
        task->level = 0;
        task->levelStep = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->levelStep = -(0xFF00 / duration);
    }
}

void STSTATUS_drawFader(ScreenFade *task) {
    Layer *layer = GFX.funcs.getLayer(task->layerId);
    u_long *ot = (u_long *)layer->getOtEntry(layer, task->depth);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->code = 0x2A;
    poly->r0 = poly->g0 = poly->b0 = task->level >> 8;
    poly->x0 = poly->x2 = 0;
    poly->x1 = poly->x3 = 320;
    poly->y0 = poly->y1 = 0;
    poly->y2 = poly->y3 = 256;
    addPrim(ot, poly);
    mode = (DR_TPAGE *)(poly + 1);
    setlen(mode, 1);
    mode->code[0] = 0xE1000245;
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void STSTATUS_updateFader(ScreenFade *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        if (task->substate == 0) {
            break;
        }
        task->level += task->levelStep;
        if (task->fadeIn == 0) {
            if (task->level > 0xFF00) {
                task->level = 0xFF00;
                task->state = 2;
            }
        } else if (task->level < 0) {
            task->level = 0;
            task->state = 2;
        }
        /* fallthrough */
    case 2:
        STSTATUS_drawFader(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *STSTATUS_createFader(void) {
    ScreenFade *task = createTask(STSTATUS_updateFader, sizeof(ScreenFade), 0);

    task->start = STSTATUS_startFader;
    task->layerId = 0x1000;
    task->depth = 0;
    return task;
}

Task *func_800975FC(FieldMenuScreen *menu, s32 extra);
Task *func_8009868C(FieldMenuScreen *menu, s32 extra);
Task *func_80095934(FieldMenuScreen *menu, s32 extra);
Task *func_8008DEA4(FieldMenuScreen *menu, s32 extra);
Task *func_80085B90(FieldMenuScreen *menu, s32 extra);
Task *func_800843B4(FieldMenuScreen *menu, s32 extra);
extern s32 D_8009A160[];
extern s32 D_8009A17C[];
extern s32 D_8009A1AC[];
extern s32 D_8009A1F4[];
extern s32 D_8009A250;
extern s32 D_80099CD4[];
extern s32 D_80099DB4[];
extern StatusMapSpot D_80099E74[];
extern StatusMapPoint D_8009A0A8[];

s32 D_80099A98[] = {
    0, 2, 3, 4,
    5,
};
s32 D_80099AAC[] = {
    0, 2, 3, 4,
    5,
};
s32 D_80099AC0[] = {
    65, 66, 67, 77,
    68, 68,
};
s32 D_80099AD8[] = {
    67, 77, 79, 65,
    66, 68, 80, 68,
};
s32 D_80099AF8[] = {
    6, 7, 5, 5,
    4, 4,
};
s32 D_80099B10[] = {
    6, 7, 8, 9,
    10, 11, 12, 13,
    14, 15, 16, 17,
    18,
};
s32 D_80099B44[] = {
    0, 2, 3, 4,
    5,
};
s32 D_80099B58[] = {
    6, 7, 8, 9,
    10, 11, 12, 13,
    14, 15, 16, 17,
    18,
};
s32 D_80099B8C[] = {
    65, 66, 67, 77,
    68, 68,
};
s32 D_80099BA4[] = {
    1, 0x80000002, 0x80000003, 0x80000004,
    0,
};
s32 D_80099BB8[] = {
    0, 2, 3, 4,
    5,
};
s32 D_80099BCC[] = {
    0, 67, 77, 79,
    65, 66, 68, 80,
    68,
};
StatusStatItem D_80099BF0[] = {
    { 2, 3, 9999 },
    { 3, 5, 9999 },
    { 4, 6, 999 },
    { 5, 7, 999 },
    { 6, 8, 999 },
    { 7, 9, 999 },
    { 8, 10, 999 },
    { 9, 11, 999 },
    { 10, 12, 999 },
    { 11, 13, 999 },
    { 12, 14, 999 },
    { 13, 15, 999 },
    { 14, 16, 999 },
    { 15, 17, 999 },
    { 16, 18, 999 },
    { -1, 0, 0 },
};
s32 D_80099C50[] = {
    0, 2, 3, 4,
    5,
};
s32 D_80099C64[] = {
    57, 56, 55, 54,
    45,
};
s32 D_80099C78[] = {
    0, 2, 3, 4,
    5,
};
s32 D_80099C8C[] = {
    0, 1, 2, 1,
};
Task *(*STSTATUS_screens[2][7])(FieldMenuScreen *menu, s32 extra) = {
    { func_80091318, func_800975FC, func_8009868C, func_80095934, func_8008DEA4, func_80085B90, NULL },
    { func_80091318, func_800975FC, func_8009868C, func_80095934, func_8008DEA4, func_800843B4, func_80085B90 },
};
s32 D_80099CD4[] = {
    7, 8, 9, 10,
    9, 8, -1, 14,
    15, 16, 15, -1,
    -1, -1, 11, 12,
    13, 12, -1, -1,
    -1, 3, 4, 5,
    6, 5, 4, -1,
    25, 26, 27, 28,
    27, 26, -1, 0,
    1, 2, 1, -1,
    -1, -1, 17, 18,
    19, 20, 19, 18,
    -1, 21, 22, 23,
    24, 23, 22, -1,
};
s32 D_80099DB4[] = {
    12, 55, 19, 1,
    16, 28, 2, 16,
    37, 4, 61, 37,
    3, 16, 46, 4,
    61, 46, 13, 44,
    28, 14, 59, 37,
    14, 94, 37, 14,
    59, 46, 14, 94,
    46, 14, 152, 19,
    14, 20, 198, 3,
    265, 212, 14, 300,
    212, 22, 189, 49,
};
StatusMapSpot D_80099E74[] = {
    0, 0, 0, 1,
    60, 53, 2, 100,
    59, 3, 126, 74,
    4, 174, 79, 4,
    208, 61, 5, 209,
    36, 6, 288, 52,
    7, 59, 98, 8,
    116, 102, 9, 149,
    104, 10, 204, 85,
    10, 251, 152, 10,
    253, 220, 11, 259,
    99, 12, 303, 115,
    13, 340, 105, 14,
    57, 123, 15, 162,
    138, 15, 158, 223,
    16, 186, 119, 17,
    251, 126, 17, 224,
    127, 18, 279, 130,
    19, 304, 141, 20,
    330, 130, 21, 60,
    169, 22, 122, 162,
    22, 109, 205, 22,
    89, 163, 23, 185,
    143, 24, 332, 153,
    24, 294, 190, 25,
    199, 167, 26, 47,
    199, 27, 72, 213,
    28, 185, 221, 29,
    265, 194, 30, 319,
    234, 31, 35, 254,
    32, 69, 248, 33,
    191, 247, 34, 224,
    227, 35, 297, 215,
    35, 276, 233, 36,
    296, 253, 37, 225,
    253,
};
StatusMapPoint D_8009A0A8[] = {
    0, 0, 171, 65,
    154, 123, 230, 104,
    182, 174, 286, 129,
    285, 56, 316, 133,
    262, 161, 249, 193,
    253, 251, 172, 221,
    160, 221, 21, 242,
    25, 160, 67, 151,
    30, 106, 32, 45,
    114, 78, 55, 34,
    128, 88, 165, 43,
    198, 36,
};
s32 D_8009A160[] = {
    1, 2, 3, 4,
    5, 7, 0,
};
s32 D_8009A17C[] = {
    1, 2, 3, 4,
    5, 7, 8, 9,
    10, 11, 12, 0,
};
s32 D_8009A1AC[] = {
    1, 2, 3, 4,
    5, 7, 8, 9,
    10, 11, 12, 6,
    13, 14, 15, 16,
    17, 0,
};
s32 D_8009A1F4[] = {
    1, 2, 3, 4,
    5, 7, 8, 9,
    10, 11, 12, 6,
    13, 14, 15, 16,
    17, 18, 19, 20,
    21, 22, 0,
};
s32 D_8009A250 = 0;
s32 *D_8009A254[][5] = {
    { D_8009A160, D_8009A17C, D_8009A1AC, D_8009A1AC, D_8009A1F4 },
    { &D_8009A250, &D_8009A250, &D_8009A250, D_8009A1AC, D_8009A1F4 },
};
StatusData STSTATUS_data = {
    (StatusAnim *)D_80099CD4,
    (WindowPos *)D_80099DB4,
    D_80099E74,
    D_8009A0A8,
    { 0 },
    0,
    { 0 },
    0,
    {
        STSTATUS_loadFiles, STSTATUS_filesLoading, STSTATUS_startFade, STSTATUS_updateFade, STSTATUS_startLerp,
        STSTATUS_updateLerp, func_80099270, STSTATUS_listItems, STSTATUS_canEquip, STSTATUS_equip,
    },
};
u8 D_8009A90C[] = {
    0x01, 0x02, 0x03, 0x07,
};
u8 D_8009A910[] = {
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x1D, 0x15, 0x20,
    0x11, 0x14, 0x14, 0x0B, 0x0B, 0x0D, 0x0D, 0x16,
    0x06, 0x17, 0x18, 0x0F, 0x1E, 0x1E, 0x0E, 0x0E,
    0x0E, 0x0E, 0x1F, 0x2A, 0x2A, 0x25, 0x25, 0x2B,
    0x0C, 0x24, 0x2C, 0x2D, 0x28, 0x12, 0x29, 0x29,
    0x29, 0x29, 0x23, 0x23, 0x23, 0x23, 0x23, 0x1B,
    0x22, 0x19, 0x1C, 0x1A, 0x10, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x22,
    0x27, 0x27, 0x26, 0x26, 0x26, 0x21, 0x21, 0x21,
    0x21, 0x09, 0x03, 0x0A, 0x04, 0x02, 0x01, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x05, 0x05,
    0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93,
    0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93,
    0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93,
    0x93, 0x93, 0x93, 0x93, 0x9D, 0x95, 0xA0, 0x91,
    0x94, 0x94, 0x8B, 0x8B, 0x8D, 0x8D, 0x96, 0x86,
    0x97, 0x98, 0x8F, 0x9E, 0x8E, 0x8E, 0x8E, 0x8E,
    0x9F, 0xAA, 0xAA, 0xA5, 0xAB, 0x8C, 0xA4, 0xAC,
    0xAD, 0xA8, 0x92, 0xA9, 0xA9, 0xA9, 0xA9, 0xA3,
    0xA3, 0x9B, 0xA2, 0x99, 0x9C, 0x9A, 0x90, 0x87,
    0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87,
    0xA2, 0xA7, 0xA7, 0xA6, 0xA6, 0xA6, 0xA1, 0xA1,
    0xA1, 0x89, 0x83, 0x8A, 0x84, 0x82, 0x81, 0x80,
    0x88, 0x88, 0x88, 0x88, 0x88, 0x85, 0x85, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
};
StatusAreaFuncs D_8009AA00 = {
    STSTATUS_isLateGame,
    STSTATUS_getArea,
    func_800999CC,
};
