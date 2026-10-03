#include "ststatus.h"

Task *createFieldMenu(s32 layerId, s32 cursor);
Task *func_80091318(FieldMenuScreen *menu, s32 extra);
FieldMenuScreen *func_80098DE4(void);
void func_80098BF8(FieldMenuScreen *menu, FieldMenuScreenChildren *children);
void func_80098ED0(void);
s32 func_80098FA0(void);
void func_80099070(PanelAnim *fade, s32 fadeIn);
s32 func_80099104(PanelAnim *fade);
void func_80099170(StatusLerp *lerp, s32 from, s32 to, s32 frames);
s32 func_80099204(StatusLerp *lerp);
s32 *func_80099270(s32 list, s32 index);
void func_80099298(s32 list, u16 *out);
s32 func_80099658(s32 partner, s32 slot, s32 item);
void func_800996FC(s32 partner, s32 slot, s32 item);
s32 func_80099984(void);
s32 func_800999AC(void);
void func_800999CC(s32 *out);

void func_80084204(StatusScreen *screen, void *children);
void func_800859E0(StatusScreen *screen, void *children);
void func_800911E4(StatusScreen0 *screen, void *children);
void func_8009576C(StatusScreen *screen, void *children);
void func_80097460(StatusScreen *screen, void *children);
void func_8008DCF0(StatusScreen4 *screen, void *children);
void func_8008AA00(StatusPanel4A *panel, void *children);
void func_80087914(StatusPanel4B *panel, void *children);
void func_80092974(StatusPanel0 *panel, void *children);
void func_800843FC(ScreenFade *task, s32 fadeIn, s32 duration);
void func_800845C8(ScreenFade *task);
void func_8008BA38(StatusScreen4 *screen);
void func_8008E668(StatusScreen0 *screen, s32 arg);
void func_8008E828(StatusScreen0 *screen, s32 arg);
ScreenFade *func_8008467C(void);
StatusPanel4B *func_800879C8(StatusScreen4 *screen);
StatusPanel4A *func_8008AB04(StatusScreen4 *screen);
StatusPanel0 *func_80092B0C(StatusScreen0 *screen, s32 list, s32 arg2);
void func_80084484(ScreenFade *task);
void func_80085BD8(StatusPanel4B *panel, void *children);
void func_80086B28(StatusPanel4B *panel, void *children);
void func_800864B0(StatusPanel4B *panel);
s32 func_8009930C(u16 *out);
s32 func_800994D0(s32 list, u16 *out);
extern s32 FIELD_MENU_CHOICE[2];
extern s32 D_80099BA4[];
extern Task *(*D_80099C9C[2][7])(FieldMenuScreen *menu, s32 extra);
extern s32 *D_8009A254[][5];
extern u8 D_8009A910[];
extern StatusAreaFuncs D_8009AA00;

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

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80082E18);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800830AC);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800832E8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008340C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800839B0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80084204);

Task *func_800843B4(FieldMenuScreen *menu, s32 extra) {
    StatusScreen *screen = createTask(func_80084204, 0xD4, 0xA0);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}

void func_800843FC(ScreenFade *task, s32 fadeIn, s32 duration) {
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

void func_80084484(ScreenFade *task) {
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

void func_800845C8(ScreenFade *task) {
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
        func_80084484(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *func_8008467C(void) {
    ScreenFade *task = createTask(func_800845C8, sizeof(ScreenFade), 0);

    task->start = func_800843FC;
    task->layerId = 0x1000;
    task->depth = 0;
    return task;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800846C0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80084908);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80084B44);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80084D14);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800852B8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800859E0);

Task *func_80085B90(FieldMenuScreen *menu, s32 extra) {
    StatusScreen *screen = createTask(func_800859E0, 0xD4, 0x9C);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80085BD8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80085DC0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80085EE4);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80086010);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80086368);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800864B0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80086B28);

void func_80087914(StatusPanel4B *panel, void *children) {
    switch (panel->state) {
    case TASK_INIT:
    default:
        panel->nextState(panel);
        panel->unk6C = 0;
        func_80085BD8(panel, children);
        panel->panels[3].duration = 10;
        panel->panels[1].duration = 10;
        panel->panels[2].duration = 10;
        panel->panels[0].duration = 10;
        break;
    case TASK_RUN:
        func_80086B28(panel, children);
        func_800864B0(panel);
        break;
    case TASK_KILL:
        panel->screen->unk70 = 0;
        /* fallthrough */
    case TASK_DONE:
        break;
    }
}

StatusPanel4B *func_800879C8(StatusScreen4 *screen) {
    StatusPanel4B *panel = createTask(func_80087914, sizeof(StatusPanel4B), 0xA4);

    panel->layer = 0x1000;
    panel->depth = 4;
    panel->screen = screen;
    panel->partner = GAME_FUNCS.getPartyMember(screen->member);
    return panel;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80087A3C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80087D5C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80087F5C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80088114);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80088850);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800889E8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80088C54);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008927C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008AA00);

StatusPanel4A *func_8008AB04(StatusScreen4 *screen) {
    StatusPanel4A *panel = createTask(func_8008AA00, sizeof(StatusPanel4A), 0x90);

    panel->layer = 0x1000;
    panel->depth = 6;
    panel->screen = screen;
    panel->member = screen->member;
    return panel;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008AB58);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008AF7C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008B1B8);

void func_8008B38C(StatusPanel4A *panel, StatusPanel4AWindows *windows, s32 show) {
    s32 i;

    if (show != 0) {
        for (i = 0; i < 2; i++) {
            windows->labels[i]->setString(windows->labels[i], FILE_CACHE.load(TEXT_FILE(0xB1)), i + 0x2D);
        }
    } else {
        for (i = 0; i < 2; i++) {
            windows->labels[i]->setVisible(windows->labels[i], 0);
        }
    }
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008B440);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008B628);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008B7A0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008BA38);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008BF2C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008CC5C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008D380);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008DCF0);

Task *func_8008DEA4(FieldMenuScreen *menu, s32 extra) {
    StatusScreen4 *screen = createTask(func_8008DCF0, sizeof(StatusScreen4), 0x110);

    screen->func_8008BA38 = func_8008BA38;
    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008DEF8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008E2B0);

void func_8008E4EC(StatusScreen0 *screen, StatusScreen0Windows *windows, s32 show) {
    if (show != 0) {
        windows->moneyLabel->setString(windows->moneyLabel, FILE_CACHE.load(TEXT_FILE(0xB1)), 5);
        windows->money->setNumber(windows->money, 0, GAME.money);
        windows->money->setRightAlign(windows->money, 1);
    } else {
        windows->moneyLabel->setVisible(windows->moneyLabel, 0);
        windows->money->setVisible(windows->money, 0);
    }
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008E59C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008E668);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008E828);

void func_8008EA38(StatusScreen0 *screen, s32 show) {
    if (show != 0) {
        STSTATUS_funcs.startFade(&screen->fade, 1);
        return;
    }
    STSTATUS_funcs.startFade(&screen->fade, 0);
    func_8008E668(screen, 0);
    func_8008E828(screen, 0);
}

s32 func_8008EAAC(StatusScreen0 *screen) {
    return STSTATUS_funcs.updateFade(&screen->fade) != 0;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008EAD4);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008EE2C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8008F7A0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800911E4);

Task *func_80091318(FieldMenuScreen *menu, s32 extra) {
    StatusScreen0 *screen = createTask(func_800911E4, sizeof(StatusScreen0), 0xD4);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80091360);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80091560);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800917EC);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800919B8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8009205C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80092440);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80092974);

StatusPanel0 *func_80092B0C(StatusScreen0 *screen, s32 list, s32 arg2) {
    StatusPanel0 *panel = createTask(func_80092974, sizeof(StatusPanel0), 0x6C);

    panel->layer = 0x1000;
    panel->depth = 3;
    panel->screen = screen;
    if (arg2 != 0) {
        panel->unk60 = arg2;
    }
    panel->list = list;
    return panel;
}

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

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80092C38);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80092DC4);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80092E7C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80092EEC);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80093300);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800935C0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800937FC);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800939BC);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80093B0C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8009440C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8009576C);

Task *func_80095934(FieldMenuScreen *menu, s32 extra) {
    StatusScreen *screen = createTask(func_8009576C, 0x1F4, 0xB4);

    screen->layer = 0x1000;
    screen->depth = 6;
    screen->menu = menu;
    return (Task *)screen;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8009597C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80095B30);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80095D6C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80096830);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80097460);

Task *func_800975FC(FieldMenuScreen *menu, s32 extra) {
    StatusScreen *screen = createTask(func_80097460, 0xF4, 0x8C);

    screen->layer = 0x1000;
    screen->depth = 2;
    screen->menu = menu;
    return (Task *)screen;
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80097644);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800977F8);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80097A68);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80097F2C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800984A4);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8009868C);

void func_80098780(ScrollBar *bar, s32 x, s32 width) {
    bar->x = x;
    bar->width = width;
}

void func_8009878C(ScrollBar *bar, s32 top, s32 bottom) {
    bar->top = top;
    bar->bottom = bottom;
    bar->hasRange = 1;
}

void func_800987A0(ScrollBar *bar, s32 pageSize, s32 count) {
    bar->pageSize = pageSize;
    bar->count = count;
    bar->hasCount = 1;
}

void func_800987B4(ScrollBar *bar, s32 pos) {
    bar->pos = pos;
}

void func_800987BC(ScrollBar *bar) {
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

ScrollBar *func_800989E8(void) {
    ScrollBar *bar = createTask(func_800987BC, sizeof(ScrollBar), 0);

    bar->setX = func_80098780;
    bar->setRange = func_8009878C;
    bar->setCount = func_800987A0;
    bar->setPos = func_800987B4;
    bar->layer = 0x1000;
    bar->depth = 0;
    return bar;
}

void func_80098A50(FieldMenuScreen *menu, FieldMenuScreenChildren *children) {
    Task *(*open)(FieldMenuScreen *, s32);

    switch (menu->substate) {
    case 0:
    default:
        open = D_80099C9C[FIELD_MENU_CHOICE[1]][FIELD_MENU_CHOICE[0]];
        if (open != NULL) {
            children->screen = open(menu, FIELD_MENU_CHOICE[1]);
        } else {
            children->screen = func_80091318(menu, FIELD_MENU_CHOICE[1]);
        }
        menu->substate++;
        break;
    case 1:
        if (children->screen == NULL) {
            children->fieldMenu = createFieldMenu(menu->layer, FIELD_MENU_CHOICE[0]);
            menu->setState(menu, 2);
        }
        break;
    }
}

void func_80098B38(FieldMenuScreen *menu) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(menu->layer, 7);
    sprite.setTexture(0x280, 0x100);
    if (menu->blinkSkip != 0) {
        menu->blinkPos++;
        menu->blinkPos = menu->blinkPos < 0x60 ? menu->blinkPos : 0;
        menu->blinkSkip = 0;
    } else {
        menu->blinkSkip = 1;
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_STATUS_SPRITES << 16), 0x1D, menu->blinkPos, menu->blinkPos);
}

void func_80098BF8(FieldMenuScreen *menu, FieldMenuScreenChildren *children) {
    TimLoader loader;

    switch (menu->state) {
    case TASK_INIT:
    default:
        switch (menu->substate) {
        case 0:
        default:
            STSTATUS_funcs.loadFiles();
            menu->substate++;
            break;
        case 1:
            if (STSTATUS_funcs.filesLoading() == 0 && FILE_CACHE.isLoading(menu->bgFile) == 0 &&
                FILE_CACHE.isLoading(menu->bgFile2) == 0) {
                initTimLoader(&loader);
                loader.setImagePos(0x380, 0x100);
                loader.loadArchive(FILE_CACHE.getEntry(menu->bgArchive1));
                loader.setImagePos(0x300, 0x100);
                loader.loadArchive(FILE_CACHE.getEntry(menu->bgArchive2));
                loader.setImagePos(0x280, 0);
                loader.setClutPos(0x140, 0x100);
                loader.loadArchive(FILE_CACHE.getEntry(menu->bgArchive));
                menu->nextState(menu);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_80098A50(menu, children);
        func_80098B38(menu);
        break;
    case TASK_DONE:
        if (children->fieldMenu == NULL) {
            menu->state = TASK_RUN;
        }
        func_80098B38(menu);
        break;
    case TASK_KILL:
        break;
    }
}

FieldMenuScreen *func_80098DE4(void) {
    FieldMenuScreen *menu = createTask(func_80098BF8, sizeof(FieldMenuScreen), sizeof(FieldMenuScreenChildren));

    menu->layer = 0x1000;
    menu->lateGame = D_8009AA00.isLateGame();
    if (menu->lateGame == 0) {
        menu->bgArchive = (FILE_STATUS_BG + 1) << 16;
        menu->bgFile = FILE_STATUS_BG + 1;
        menu->bgArchive1 = ((FILE_STATUS_BG + 1) << 16) + 1;
        menu->bgArchive2 = ((FILE_STATUS_BG + 1) << 16) + 2;
        menu->bgFile2 = FILE_STATUS_BG;
    } else {
        menu->bgArchive = (FILE_STATUS_BG + 3) << 16;
        menu->bgFile = FILE_STATUS_BG + 3;
        menu->bgArchive1 = ((FILE_STATUS_BG + 3) << 16) + 1;
        menu->bgArchive2 = ((FILE_STATUS_BG + 3) << 16) + 2;
        menu->bgFile2 = FILE_STATUS_BG + 2;
    }
    FILE_CACHE.request(menu->bgFile);
    FILE_CACHE.request(menu->bgFile2);
    return menu;
}

void func_80098ED0(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry((FILE_STATUS_SPRITES + 1) << 16));
    FILE_CACHE.request(TEXT_FILE(0xB1));
    FILE_CACHE.request(TEXT_FILE(0x6B));
    FILE_CACHE.request(TEXT_FILE(0x64));
    FILE_CACHE.request(TEXT_FILE(0x4F));
    FILE_CACHE.request(TEXT_FILE(0x48));
    FILE_CACHE.request(TEXT_FILE(0xA3));
    FILE_CACHE.request(TEXT_FILE(0x9C));
}

s32 func_80098FA0(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0xB1)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x6B)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x64)) != 0) {
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

void func_80099070(PanelAnim *fade, s32 fadeIn) {
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

s32 func_80099104(PanelAnim *fade) {
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

void func_80099170(StatusLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        SOUND.playSound(0x40019);
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 func_80099204(StatusLerp *lerp) {
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

s32 *func_80099270(s32 list, s32 index) {
    return D_8009A254[list][index];
}

void func_80099298(s32 list, u16 *out) {
    if (list < 5) {
        ITEM_FUNCS->list(list, out);
        return;
    }
    switch (list) {
    case 5:
    default:
        func_8009930C(out);
        break;
    case 6:
        func_800994D0(4, out);
        break;
    case 7:
        func_800994D0(5, out);
        break;
    }
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_8009930C);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800994D0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_80099658);

INCLUDE_ASM("ststatus/nonmatchings/ststatus", func_800996FC);

s32 func_80099984(void) {
    if (GAME.fieldMode >= 0x2D7) {
        return -1;
    }
    return GAME.fieldMode >= 0x270;
}

s32 func_800999AC(void) {
    return D_8009A910[(u8)GAME.fieldMode] & 0x7F;
}

void func_800999CC(s32 *out) {
    s32 first;
    s32 last;
    s32 i;
    s32 area;
    s32 found;

    if (func_80099984() == 0) {
        first = 0x200;
        last = 0x26F;
    } else {
        first = 0x270;
        last = 0x2D6;
    }
    for (i = first; i <= last; i++) {
        area = D_8009A910[i & 0xFF] & 0x7F;
        found = FLAGS_00.checkCondition((i & 0xFF) | 0x2000, 1);
        if (found == 1) {
            out[area] = found;
        }
    }
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
extern s32 D_80099E74[];
extern s32 D_8009A0A8[];

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
s32 D_80099BF0[] = {
    0x30002, 0x3270F, 0x270F0005, 0x60004,
    0x503E7, 0x3E70007, 0x80006, 0x703E7,
    0x3E70009, 0xA0008, 0x903E7, 0x3E7000B,
    0xC000A, 0xB03E7, 0x3E7000D, 0xE000C,
    0xD03E7, 0x3E7000F, 0x10000E, 0xF03E7,
    0x3E70011, 0x120010, -64537, 0,
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
Task *(*D_80099C9C[2][7])(FieldMenuScreen *menu, s32 extra) = {
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
s32 D_80099E74[] = {
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
s32 D_8009A0A8[] = {
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
s32 D_8009A27C = (s32)D_80099CD4;
s32 D_8009A280 = (s32)D_80099DB4;
s32 D_8009A284[] = {
    (s32)D_80099E74, (s32)D_8009A0A8,
};
s32 D_8009A28C[] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0,
};
StatusFuncs STSTATUS_funcs = {
    func_80098ED0, func_80098FA0, func_80099070, func_80099104, func_80099170,
    func_80099204, func_80099270, func_80099298, func_80099658, func_800996FC,
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
    func_80099984,
    func_800999AC,
    func_800999CC,
};
