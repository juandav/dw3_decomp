#include "common.h"
#include "stgdglab.h"

Task *func_80084CF4(Lab *lab);
Task *func_80087FF0(Lab *lab);
LabMenu *STGDGLAB_createMenu(Lab *lab);
Task *func_8008BB30(Lab *lab);
ScreenFade *STGDGLAB_createFader(void);
void STGDGLAB_drawFader(ScreenFade *task);
void func_800869FC(LabScreen2 *screen, void *children);
void func_80086F6C(LabScreen2 *screen, void *children);
void func_80087B68(LabScreen2 *screen, void *children);
void func_80088164(LabMenu *menu, void *children);
void func_800884A0(LabMenu *menu, void *children);
void func_800893FC(LabMenu *menu, void *children);
void func_8008397C(LabScreen3 *screen, void *children);
void func_8008568C(LabPanel1 *panel, void *children);
void func_8008B960(LabScreen1 *screen, void *children);
void func_8008C234(LabPanel2 *panel, void *children);
void func_8008E134(LabPanel3 *panel, void *children);
void func_8008D25C(LabPanel3 *panel, LabPanel3Windows *windows, s32 arg);
void STGDGLAB_openMenu(LabMenu *menu);
void STGDGLAB_closeMenu(LabMenu *menu);
void STGDGLAB_updateMenu(LabMenu *menu, void *children);
void func_8008D80C(LabPanel3 *panel);
void func_80087F48(LabScreen2 *screen, void *children);
s32 func_80082C1C(LabScreen3 *screen, s32 row, u32 col);
void STGDGLAB_setScrollBarX(ScrollBar *bar, s32 x, s32 width);
void STGDGLAB_setScrollBarRange(ScrollBar *bar, s32 top, s32 bottom);
void STGDGLAB_setScrollBarCount(ScrollBar *bar, s32 pageSize, s32 count);
void STGDGLAB_setScrollBarPos(ScrollBar *bar, s32 pos);
void func_8008E394(Lab *lab, LabChildren *children);
void STGDGLAB_packParty(Lab *lab);
s32 func_8008E704(Lab *lab);
s32 func_8008E760(Lab *lab);
s32 func_8008E7BC(Lab *lab);
void func_8008E7F0(Lab *lab);
Lab *STGDGLAB_createLab(void);
void STGDGLAB_loadFiles(void);
s32 STGDGLAB_filesLoading(void);
void STGDGLAB_startFade(PanelAnim *fade, s32 fadeIn);
s32 STGDGLAB_updateFade(PanelAnim *fade);
void STGDGLAB_startLerp(LabLerp *lerp, s32 from, s32 to, s32 frames);
s32 STGDGLAB_updateLerp(LabLerp *lerp);
s16 func_8008EBFC(s32 id);
s16 func_8008EC48(s32 id);

extern Task *(*STGDGLAB_screens[])(Lab *lab);
extern LabEntry D_8008EE4C[];

void func_800826E0(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0xF000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)STGDGLAB_createLab();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_800827D8(void) {
    return createTask(func_800826E0, sizeof(Task), 4);
}

void STGDGLAB_startFader(ScreenFade *task, s32 fadeIn, s32 duration) {
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

void STGDGLAB_drawFader(ScreenFade *task) {
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

void STGDGLAB_updateFader(ScreenFade *task) {
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
        STGDGLAB_drawFader(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *STGDGLAB_createFader(void) {
    ScreenFade *task = createTask(STGDGLAB_updateFader, sizeof(ScreenFade), 0);

    task->start = STGDGLAB_startFader;
    task->layerId = 0x1000;
    task->depth = 6;
    return task;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80082ACC);

s32 func_80082C1C(LabScreen3 *screen, s32 row, u32 col) {
    s16 id;
    s32 i;
    s32 j;
    s16 *ids;

    if (col >= 5) {
        return 0;
    }
    id = 0;
    ids = &STGDGLAB_tables.recipes[screen->table][row * 4 + col][1];
    for (i = 0; i < 5; i++) {
        if (*ids > 0) {
            id = *ids;
            break;
        }
        ids++;
    }
    if (id != 0) {
        for (j = 0; j < screen->ownedCount; j++) {
            if (screen->owned[j] == id) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_80082CE8(LabScreen3 *screen, u32 row) {
    s32 i;
    s32 count;

    if (row >= 4) {
        return 0;
    }
    i = 0;
    count = 0;
    for (; i < 4; i++) {
        count += func_80082C1C(screen, row, i);
    }
    return count;
}

void func_80082D64(LabScreen3 *screen) {
    screen->slot = 0;
    screen->col = 0;
    while (screen->found[screen->row][screen->slot][screen->col] == 0) {
        if (++screen->col >= 5) {
            screen->col = 4;
            break;
        }
    }
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80082DF4);

#if VERSION_EU
INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_800841E4);
#endif

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008397C);

Task *func_80084CF4(Lab *lab) {
    LabScreen3 *screen = createTask(func_8008397C, sizeof(LabScreen3), 0x1C);

    screen->layer = 0x1000;
    screen->depth = 2;
    screen->lab = lab;
    lab->closeMenu(lab);
    return (Task *)screen;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80084D5C);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008501C);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80085524);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008568C);

LabPanel1 *func_800869A4(s32 arg0, s32 arg1) {
    LabPanel1 *panel = createTask(func_8008568C, sizeof(LabPanel1), 0xA0);

    panel->layer = 0x1000;
    panel->depth = 6;
    panel->unk58 = arg0;
    panel->unk5C = arg1;
    return panel;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_800869FC);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80086BD4);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80086F6C);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80087B68);

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

void STGDGLAB_openMenu(LabMenu *menu) {
    menu->state = TASK_DONE;
    menu->counter = 0;
    STGDGLAB_funcs.startFade(&menu->panels[3], 1);
}

void STGDGLAB_closeMenu(LabMenu *menu) {
    LabMenuWindows *windows;
    s32 i;

    menu->state = TASK_DONE;
    menu->counter = 1;
    windows = menu->children;
    STGDGLAB_funcs.startFade(&menu->panels[3], 0);
    for (i = 0; i < 5; i++) {
        if (windows->unk14[i] != NULL) {
            windows->unk14[i]->setVisible(windows->unk14[i], 0);
        }
        if (windows->unk28[i] != NULL) {
            windows->unk28[i]->setVisible(windows->unk28[i], 0);
        }
    }
    if (windows->unk3C != NULL) {
        windows->unk3C->setVisible(windows->unk3C, 0);
    }
    for (i = 4; i >= 0; i--) {
        menu->unkFC[i] = 0;
    }
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_80088164);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_800884A0);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_800893FC);

void STGDGLAB_updateMenu(LabMenu *menu, void *children) {
    switch (menu->state) {
    case TASK_INIT:
    default:
        menu->nextState(menu);
        menu->panels[0].duration = 10;
        menu->panels[1].duration = 10;
        menu->panels[2].duration = 8;
        menu->panels[3].duration = 10;
        menu->panels[4].duration = 10;
        menu->panels[5].duration = 10;
        menu->panels[6].duration = 10;
        menu->panels[7].duration = 8;
        menu->panels[8].duration = 8;
        break;
    case TASK_RUN:
        func_800884A0(menu, children);
        func_800893FC(menu, children);
        break;
    case TASK_DONE:
        if (STGDGLAB_funcs.updateFade(&menu->panels[3]) != 0) {
            menu->state = TASK_RUN;
            if (menu->counter == 0) {
                func_80088164(menu, children);
            }
        }
        func_800893FC(menu, children);
        break;
    case TASK_KILL:
        break;
    }
}

LabMenu *STGDGLAB_createMenu(Lab *lab) {
    LabMenu *menu = createTask(STGDGLAB_updateMenu, sizeof(LabMenu), sizeof(LabMenuWindows));

    menu->open = STGDGLAB_openMenu;
    menu->close = STGDGLAB_closeMenu;
    menu->layer = 0x1000;
    menu->depth = 2;
    menu->lab = lab;
    return menu;
}

void STGDGLAB_setScrollBarX(ScrollBar *bar, s32 x, s32 width) {
    bar->x = x;
    bar->width = width;
}

void STGDGLAB_setScrollBarRange(ScrollBar *bar, s32 top, s32 bottom) {
    bar->top = top;
    bar->bottom = bottom;
    bar->hasRange = 1;
}

void STGDGLAB_setScrollBarCount(ScrollBar *bar, s32 pageSize, s32 count) {
    bar->pageSize = pageSize;
    bar->count = count;
    bar->hasCount = 1;
}

void STGDGLAB_setScrollBarPos(ScrollBar *bar, s32 pos) {
    bar->pos = pos;
}

void STGDGLAB_updateScrollBar(ScrollBar *bar) {
    Layer *layer;
    u_long *ot;
    POLY_F4 *poly;
    s32 range;
#if VERSION_US
    s32 pages;
#endif

    switch (bar->state) {
    case TASK_INIT:
    default:
        if (bar->hasRange != 0 && bar->hasCount != 0) {
#if VERSION_US
            bar->nextState(bar);
            pages = bar->count / bar->pageSize + (bar->count % bar->pageSize != 0);
            range = (bar->bottom - bar->top) << 8;
            bar->size = range / pages;
            bar->posStep = range / bar->count;
#elif VERSION_EU
            /* the European version sizes the thumb for the visible items */
            range = (bar->bottom - bar->top) << 8;
            bar->size = range / bar->count * bar->pageSize;
            bar->posStep = range / bar->count;
            bar->nextState(bar);
#endif
        }
        break;
    case TASK_RUN:
        layer = GFX.funcs.getLayer(bar->layer);
        ot = (u_long *)layer->getOtEntry(layer, bar->depth);
        poly = GFX.funcs.getPrim();
        if (bar->pos < bar->count - 1) {
            bar->y = bar->top + ((bar->pos * bar->posStep) >> 8);
            if (bar->bottom - (bar->size >> 8) < bar->y) {
                bar->y = bar->bottom - (bar->size >> 8);
            }
        } else {
            bar->y = bar->bottom - (bar->size >> 8);
        }
        setlen(poly, 5);
        poly->code = 0x28;
        poly->r0 = poly->g0 = poly->b0 = 0xFF;
        poly->x0 = poly->x2 = bar->x;
        poly->x1 = poly->x3 = bar->x + bar->width;
        poly->y0 = poly->y1 = bar->y;
        poly->y2 = poly->y3 = bar->y + (bar->size >> 8);
        addPrim(ot, poly);
        GFX.funcs.setPrim(poly + 1);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

ScrollBar *STGDGLAB_createScrollBar(void) {
    ScrollBar *bar = createTask(STGDGLAB_updateScrollBar, sizeof(ScrollBar), 0);

    bar->setX = STGDGLAB_setScrollBarX;
    bar->setRange = STGDGLAB_setScrollBarRange;
    bar->setCount = STGDGLAB_setScrollBarCount;
    bar->setPos = STGDGLAB_setScrollBarPos;
    bar->layer = 0x1000;
    bar->depth = 0;
    return bar;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008A250);

void func_8008A624(Task *task) {
    s32 i;
    TextWindow **windows = task->children;

    for (i = 0; i < task->childCount - 1; i++, windows++) {
        TextWindow *w = *windows;
        if (w != NULL) {
            w->setVisible(w, 0);
        }
    }
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008A6A4);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008B0A4);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008B960);

Task *func_8008BB30(Lab *lab) {
    LabScreen1 *screen = createTask(func_8008B960, sizeof(LabScreen1), 0x38);

    screen->layer = 0x1000;
    screen->depth = 2;
    screen->lab = lab;
    return (Task *)screen;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008BB78);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008BDEC);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008C234);

LabPanel2 *func_8008D014(s32 arg0, s32 arg1) {
    LabPanel2 *panel = createTask(func_8008C234, sizeof(LabPanel2), 0x5C);

    panel->layer = 0x1000;
    panel->depth = 2;
    panel->unk78 = arg0;
    panel->unk7C = arg1;
    return panel;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008D06C);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008D25C);

void func_8008D80C(LabPanel3 *panel) {
    LabPanel3Windows *windows = panel->children;

    STGDGLAB_funcs.startFade(&panel->fade, 0);
    func_8008D25C(panel, windows, 0);
    windows->cursor->setVisible(windows->cursor, 0);
    panel->substate++;
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008D884);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008DD30);

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab", func_8008E134);

LabPanel3 *func_8008E320(s32 arg0, s32 arg1, s32 arg2) {
    LabPanel3 *panel = createTask(func_8008E134, sizeof(LabPanel3), 0x70);

    panel->close = func_8008D80C;
    panel->layer = 0x1000;
    panel->depth = 2;
    panel->unk50 = arg1;
    panel->unk54 = arg0;
    panel->unk16C = arg2;
    return panel;
}

void func_8008E394(Lab *lab, LabChildren *children) {
    switch (lab->substate) {
    case 0:
    default:
        if (children->menu == NULL) {
            children->menu = STGDGLAB_createMenu(lab);
        }
        lab->substate++;
        break;
    case 1:
        if (children->menu != NULL) {
            if (children->menu->picked != 0) {
                children->screen = STGDGLAB_screens[children->menu->choice](lab);
                lab->substate++;
            }
        } else {
            lab->substate = 3;
        }
        break;
    case 2:
        if (children->screen == NULL) {
            lab->substate = 1;
            children->menu->picked = 0;
        }
        break;
    case 3:
        if (children->fade->state == 2) {
            lab->setState(lab, TASK_KILL);
        }
        break;
    }
}

void STGDGLAB_packParty(Lab *lab) {
    s32 i;
    s32 j;

    lab->partyCount = 0;
    for (i = 0; i < 3; i++) {
        if (GAME.party[i] >= 0) {
            lab->partyCount++;
        }
    }
    for (i = 0; i < 3; i++) {
        if (GAME.party[i] < 0) {
            for (j = i; j < 3; j++) {
                if (GAME.party[j] >= 0) {
                    GAME.party[i] = GAME.party[j];
                    GAME.party[j] = -1;
                    break;
                }
            }
        }
    }
}

void STGDGLAB_updateLab(Lab *lab, LabChildren *children) {
    SpriteDrawer sprite;

    switch (lab->state) {
    case TASK_INIT:
    default:
        switch (lab->substate) {
        case 0:
        default:
            STGDGLAB_funcs.loadFiles();
            lab->substate++;
            break;
        case 1:
            if (STGDGLAB_funcs.filesLoading() == 0) {
                lab->nextState(lab);
                lab->unk5C = 3;
                STGDGLAB_packParty(lab);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_8008E394(lab, children);
        initSpriteDrawer(&sprite);
        sprite.setLayerId(lab->layer, 7);
        sprite.setTexture(0x280, 0x100);
        if (lab->blinkSkip != 0) {
            lab->blinkPos++;
            lab->blinkPos = lab->blinkPos < 0x60 ? lab->blinkPos : 0;
            lab->blinkSkip = 0;
        } else {
            lab->blinkSkip = 1;
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x37, lab->blinkPos, lab->blinkPos);
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        GAME.funcs.requestMode(GAME.fieldMode, 0);
        break;
    }
}

s32 func_8008E704(Lab *lab) {
    LabMenu *menu = ((LabChildren *)lab->children)->menu;

    if (menu != NULL && menu->state == TASK_RUN) {
        menu->open(menu);
        return 1;
    }
    return 0;
}

s32 func_8008E760(Lab *lab) {
    LabMenu *menu = ((LabChildren *)lab->children)->menu;

    if (menu != NULL && menu->state == TASK_RUN) {
        menu->close(menu);
        return 1;
    }
    return 0;
}

s32 func_8008E7BC(Lab *lab) {
    LabMenu *menu = ((LabChildren *)lab->children)->menu;

    if (menu != NULL && menu->state == TASK_RUN) {
        return 1;
    }
    return 0;
}

void func_8008E7F0(Lab *lab) {
    LabChildren *children = lab->children;

    children->fade = STGDGLAB_createFader();
    children->fade->start(children->fade, 0, 0x1E);
}

Lab *STGDGLAB_createLab(void) {
    Lab *lab = createTask(STGDGLAB_updateLab, sizeof(Lab), sizeof(LabChildren));

    lab->openMenu = func_8008E704;
    lab->closeMenu = func_8008E760;
    lab->menuOpen = func_8008E7BC;
    lab->packParty = STGDGLAB_packParty;
    lab->fadeOut = func_8008E7F0;
    lab->layer = 0x1000;
    return lab;
}

void STGDGLAB_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry((FILE_LAB_SPRITES + 1) << 16));
    loader.setImagePos(0x140, 0x100);
    loader.setClutPos(0x280, 0);
    loader.setBufferSize(0x10000);
    loader.loadArchive(FILE_CACHE.getEntry(((FILE_LAB_SPRITES + 1) << 16) + 2));
    FILE_CACHE.request(TEXT_FILE(0x3A));
    FILE_CACHE.request(TEXT_FILE(0x4F));
    FILE_CACHE.request(TEXT_FILE(0x48));
    FILE_CACHE.request(TEXT_FILE(0xA3));
    FILE_CACHE.request(TEXT_FILE(0x9C));
}

s32 STGDGLAB_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x3A)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x4F)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x48)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0xA3)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x9C)) != 0;
}

void STGDGLAB_startFade(PanelAnim *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn != 0) {
        SOUND.playSound(0x40019);
        fade->level = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        SOUND.playSound(0x4001A);
        fade->level = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

s32 STGDGLAB_updateFade(PanelAnim *fade) {
    if (fade->active == 0) {
        return 1;
    }
    fade->level += fade->step;
    if (fade->step > 0) {
        if (fade->level > 0x1000) {
            fade->level = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->level < 0) {
        fade->level = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

void STGDGLAB_startLerp(LabLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STGDGLAB_updateLerp(LabLerp *lerp) {
    if (lerp->active == 0) {
        return 1;
    }
    lerp->fixed += lerp->step;
    lerp->value = lerp->fixed >> 8;
    if (lerp->step > 0) {
        if (lerp->target < lerp->value) {
            lerp->value = lerp->target;
            lerp->active = 0;
            return 1;
        }
    } else if (lerp->value < lerp->target) {
        lerp->value = lerp->target;
        lerp->active = 0;
        return 1;
    }
    return 0;
}

s16 func_8008EBFC(s32 id) {
    s32 i;

    for (i = 0; D_8008EE4C[i].id != 0; i++) {
        if (D_8008EE4C[i].id == id) {
            return D_8008EE4C[i].a;
        }
    }
    return 0;
}

s16 func_8008EC48(s32 id) {
    s32 i;

    for (i = 0; D_8008EE4C[i].id != 0; i++) {
        if (D_8008EE4C[i].id == id) {
            return D_8008EE4C[i].b;
        }
    }
    return 0;
}

extern s32 D_8008ECE8[];
extern s32 D_8008EDC8[];
extern LabRecipe D_8008EF8C[];
extern LabRecipe D_8008F04C[];
extern LabRecipe D_8008F10C[];
extern LabRecipe D_8008F1CC[];
extern LabRecipe D_8008F28C[];
extern LabRecipe D_8008F34C[];
extern LabRecipe D_8008F40C[];
extern LabRecipe D_8008F4CC[];

s32 D_8008EC94[] = {
    383, 385, 384, 3,
    145, 366, 373, 31,
};
s32 D_8008ECB4[] = {
    0, 2, 3, 4,
    5,
};
s32 D_8008ECC8[] = {
    0, 2, 3, 4,
    5,
};
/* the main menu's screens */
Task *(*STGDGLAB_screens[])(Lab *lab) = {
    func_8008BB30, func_80087FF0, func_80084CF4,
};
s32 D_8008ECE8[] = {
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
s32 D_8008EDC8[] = {
    21, 51, 38, 22,
    51, 48, 23, 95,
    48, 14, 51, 57,
    23, 95, 57, 18,
    80, 38, 18, 93,
    48, 18, 128, 48,
    18, 93, 57, 18,
    128, 57, -1, 51,
    23,
};
LabEntry D_8008EE4C[] = {
    { 0x017F, 0x0002, 0x010C },
    { 0x0181, 0x0004, 0x011D },
    { 0x0180, 0x0003, 0x0114 },
    { 0x0003, 0x0001, 0x012A },
    { 0x0091, 0x0007, 0x012B },
    { 0x016E, 0x0000, 0x012C },
    { 0x0175, 0x0005, 0x0115 },
    { 0x001F, 0x0006, 0x010D },
    { 0x0005, 0x0022, 0x0127 },
    { 0x0006, 0x001D, 0x0132 },
    { 0x000C, 0x0023, 0x0125 },
    { 0x0013, 0x0017, 0x011C },
    { 0x0014, 0x000B, 0x010A },
    { 0x001A, 0x0028, 0x0131 },
    { 0x001B, 0x0025, 0x0108 },
    { 0x0038, 0x0021, 0x0135 },
    { 0x003B, 0x0010, 0x0123 },
    { 0x0042, 0x001E, 0x0130 },
    { 0x0090, 0x000F, 0x0119 },
    { 0x0094, 0x0013, 0x0121 },
    { 0x0096, 0x002A, 0x011E },
    { 0x0097, 0x0019, 0x012D },
    { 0x00C4, 0x0026, 0x0117 },
    { 0x00D3, 0x000C, 0x0105 },
    { 0x00D5, 0x0024, 0x0102 },
    { 0x00D6, 0x000D, 0x0134 },
    { 0x00E6, 0x0018, 0x0118 },
    { 0x00EA, 0x000E, 0x0106 },
    { 0x00FE, 0x0012, 0x0124 },
    { 0x0103, 0x0011, 0x0129 },
    { 0x0104, 0x0016, 0x010B },
    { 0x010B, 0x0029, 0x0133 },
    { 0x0167, 0x0014, 0x0120 },
    { 0x016F, 0x0008, 0x0128 },
    { 0x0170, 0x0009, 0x0126 },
    { 0x0171, 0x000A, 0x011F },
    { 0x0174, 0x0027, 0x0122 },
    { 0x0176, 0x001A, 0x0112 },
    { 0x0177, 0x001B, 0x0110 },
    { 0x0178, 0x001C, 0x010F },
    { 0x0179, 0x0020, 0x012F },
    { 0x017A, 0x001F, 0x012E },
    { 0x017D, 0x0015, 0x0100 },
    { 0x0182, 0x0031, 0x0109 },
    { 0x0183, 0x002B, 0x0113 },
    { 0x0184, 0x002E, 0x011B },
    { 0x0185, 0x0032, 0x0107 },
    { 0x0186, 0x002C, 0x0111 },
    { 0x0187, 0x002F, 0x011A },
    { 0x0188, 0x0033, 0x0101 },
    { 0x0189, 0x002D, 0x010E },
    { 0x018A, 0x0030, 0x0116 },
    { 0x0000, 0x0000, 0x0000 },
};
#if VERSION_US
LabRecipe D_8008EF8C[] = {
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F04C[] = {
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 3, 0, 0x182, 0x185, 0x188, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F10C[] = {
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0, 0x01B, 0x0C4, 0x174, 0 },
    { 1, 0, 0x038, 0, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0, 0x0EA, 0x090, 0x03B, 0 },
    { 3, 0, 0x176, 0x177, 0x178, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0, 0x16F, 0x170, 0x171, 0 },
    { 3, 0, 0x184, 0x187, 0x18A, 0 },
};
LabRecipe D_8008F1CC[] = {
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 1, 0, 0x038, 0, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0, 0x0EA, 0x090, 0x03B, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
};
LabRecipe D_8008F28C[] = {
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0, 0x01B, 0x0C4, 0x174, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0, 0x0EA, 0x090, 0x03B, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
};
LabRecipe D_8008F34C[] = {
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F40C[] = {
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F4CC[] = {
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x005, 0x00C, 0x0D5, 0, 0 },
    { 3, 0, 0x01A, 0x10B, 0x096, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0, 0x01B, 0x0C4, 0x174, 0 },
    { 3, 0, 0x16F, 0x170, 0x171, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
};
#elif VERSION_EU
LabRecipe D_8008EF8C[] = {
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F04C[] = {
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 3, 0, 0x182, 0x185, 0x188, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F10C[] = {
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0, 0x01B, 0x0C4, 0x174, 0 },
    { 1, 0, 0x038, 0, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0, 0x0EA, 0x090, 0x03B, 0 },
    { 3, 0, 0x176, 0x177, 0x178, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0, 0x16F, 0x170, 0x171, 0 },
    { 3, 0, 0x184, 0x187, 0x18A, 0 },
};
LabRecipe D_8008F1CC[] = {
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 1, 0, 0x038, 0, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0, 0x0EA, 0x090, 0x03B, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
};
LabRecipe D_8008F28C[] = {
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0, 0x01B, 0x0C4, 0x174, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0, 0x0EA, 0x090, 0x03B, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
};
LabRecipe D_8008F34C[] = {
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F40C[] = {
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 3, 0x16F, 0x170, 0x171, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x01B, 0x0C4, 0x174, 0, 0 },
    { 4, 0x006, 0x042, 0x17A, 0x179, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};
LabRecipe D_8008F4CC[] = {
    { 3, 0x014, 0x0D3, 0x0D6, 0, 0 },
    { 1, 0x038, 0, 0, 0, 0 },
    { 3, 0x0EA, 0x090, 0x03B, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 4, 0x104, 0x013, 0, 0x0E6, 0x097 },
    { 4, 0x005, 0x00C, 0x0D5, 0x096, 0 },
    { 2, 0, 0x01A, 0x10B, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 3, 0x183, 0x186, 0x189, 0, 0 },
    { 3, 0, 0x01B, 0x0C4, 0x174, 0 },
    { 3, 0, 0x16F, 0x170, 0x171, 0 },
    { 4, 0, 0x006, 0x042, 0x17A, 0x179 },
    { 3, 0x176, 0x177, 0x178, 0, 0 },
    { 3, 0x182, 0x185, 0x188, 0, 0 },
    { 5, 0x103, 0x0FE, 0x094, 0x167, 0x17D },
    { 3, 0x184, 0x187, 0x18A, 0, 0 },
};
#endif
LabTables STGDGLAB_tables = {
    D_8008ECE8,
    D_8008EDC8,
    {
        D_8008EF8C, D_8008F04C, D_8008F10C, D_8008F1CC,
        D_8008F28C, D_8008F34C, D_8008F40C, D_8008F4CC,
    },
};
LabFuncs STGDGLAB_funcs = {
    STGDGLAB_loadFiles, STGDGLAB_filesLoading, STGDGLAB_startFade, STGDGLAB_updateFade,
    STGDGLAB_startLerp, STGDGLAB_updateLerp, func_8008EBFC, func_8008EC48,
};
