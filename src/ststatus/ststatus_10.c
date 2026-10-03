/* The last object of STSTATUS.PRO (see ststatus.c), the mode's main task,
   the scroll bar and the helpers in STSTATUS_data: it has no rodata, so
   where its code starts is a guess. */

#include "ststatus.h"

/* One button of pad 1, held down */
#define PAD_HELD(button) ((PAD.getHeld(0) >> PAD.getButtonBit(0, button)) & 1)

void func_800977F8(StatusMapScreen *screen, s32 dx, s32 dy);
void func_80097F2C(StatusMapScreen *screen);

/* Finds the area under the cursor and shows its name */
void func_80097644(StatusMapScreen *screen, TextWindow **windows) {
    s32 wasHovering = screen->hovering;
    StatusMapSpot *spots;
    s32 spotX;
    s32 spotY;
    s32 x;
    s32 y;
    s32 i;

    screen->hovering = 0;
    x = screen->cursorX - screen->scrollX;
    y = screen->cursorY - screen->scrollY;
    spots = STSTATUS_data.spots;
    for (i = 1; i < 47; i++) {
        if (screen->visited[i - 1]) {
            spotX = spots[i].x;
            spotY = spots[i].y;
            if (spotX + 6 < x && x <= spotX + 0x12 && spotY + 6 < y && y <= spotY + 0x12) {
                screen->hovering = 1;
                screen->spot = i;
                break;
            }
        }
    }
    if (wasHovering != screen->hovering) {
        if (screen->hovering) {
            SOUND.playSound(0x4001C);
#if VERSION_EU
            screen->hoverX = screen->cursorX;
#endif
            screen->hoverY = screen->cursorY;
        } else {
            windows[0]->setVisible(windows[0], 0);
        }
    }
    if (screen->hovering) {
        if (screen->hoverY < screen->height / 2) {
            windows[0]->setPos(windows[0], 0x10, 0xB9);
        } else {
            windows[0]->setPos(windows[0], 0x10, 0x19);
        }
        windows[0]->setString(windows[0], FILE_CACHE.load(screen->textFile), screen->spot);
    }
}

/* Moves the cursor, or the map when the cursor is in the middle */
void func_800977F8(StatusMapScreen *screen, s32 dx, s32 dy) {
    s32 middle;

    if (dx < 0) {
        if (screen->cursorX > 0xA0) {
            screen->cursorX -= screen->speedX;
            if (screen->cursorX < 0xA0) {
                screen->cursorX = 0xA0;
            }
        } else if (screen->cursorX < 0xA0) {
            screen->cursorX -= screen->speedX;
            if (screen->cursorX < 0x16) {
                screen->cursorX = 0x16;
            }
        } else {
            screen->scrollX += screen->speedX;
            if (screen->scrollX > 0) {
                screen->scrollX = 0;
                screen->cursorX = 0x9F;
            }
        }
    } else if (dx > 0) {
        if (screen->cursorX < 0xA0) {
            screen->cursorX += screen->speedX;
            if (screen->cursorX > 0xA0) {
                screen->cursorX = 0xA0;
            }
        } else if (screen->cursorX > 0xA0) {
            screen->cursorX += screen->speedX;
            if (screen->cursorX > 0x12A) {
                screen->cursorX = 0x12A;
            }
        } else {
            screen->scrollX -= screen->speedX;
            if (screen->scrollX < -0x48) {
                screen->scrollX = -0x48;
                screen->cursorX = 0xA1;
            }
        }
    }
    middle = screen->height / 2;
    if (dy < 0) {
        if (screen->cursorY > middle) {
            screen->cursorY -= screen->speedY;
            if (screen->cursorY < middle) {
                screen->cursorY = middle;
            }
        } else if (screen->cursorY < middle) {
            screen->cursorY -= screen->speedY;
            if (screen->cursorY < 0xF) {
                screen->cursorY = 0xF;
            }
        } else {
            screen->scrollY += screen->speedY;
            if (screen->scrollY > 0) {
                screen->scrollY = 0;
                screen->cursorY = middle - 1;
            }
        }
    } else if (dy > 0) {
        if (screen->cursorY < middle) {
            screen->cursorY += screen->speedY;
            if (screen->cursorY > middle) {
                screen->cursorY = middle;
            }
        } else if (screen->cursorY > middle) {
            screen->cursorY += screen->speedY;
            if (screen->cursorY > screen->height - screen->top - 0x1E) {
                screen->cursorY = screen->height - screen->top - 0x1E;
            }
        } else {
            screen->scrollY -= screen->speedY;
            if (screen->scrollY < -0x60) {
                screen->scrollY = -0x60;
                screen->cursorY = middle + 1;
            }
        }
    }
}

/* Moves the cursor faster while the pad is held; triangle closes */
void func_80097A68(StatusMapScreen *screen, TextWindow **windows) {
    if (PAD_HELD(PAD_LEFT) || PAD_HELD(PAD_RIGHT)) {
        if (PAD_PRESSED(PAD_LEFT) || PAD_PRESSED(PAD_RIGHT)) {
            screen->speedX = 2;
        } else if (PAD_REPEATED(PAD_LEFT) || PAD_REPEATED(PAD_RIGHT)) {
            screen->speedX++;
            if (screen->speedX > 4) {
                screen->speedX = 4;
            }
        }
    } else {
        screen->speedX = 0;
    }
    if (PAD_HELD(PAD_UP) || PAD_HELD(PAD_DOWN)) {
        if (PAD_PRESSED(PAD_UP) || PAD_PRESSED(PAD_DOWN)) {
            screen->speedY = 2;
        } else if (PAD_REPEATED(PAD_UP) || PAD_REPEATED(PAD_DOWN)) {
            screen->speedY++;
            if (screen->speedY > 4) {
                screen->speedY = 4;
            }
        }
    } else {
        screen->speedY = 0;
    }
    if (PAD_HELD(PAD_LEFT)) {
        func_800977F8(screen, -1, 0);
    } else if (PAD_HELD(PAD_RIGHT)) {
        func_800977F8(screen, 1, 0);
    }
    if (PAD_HELD(PAD_UP)) {
        func_800977F8(screen, 0, -1);
    } else if (PAD_HELD(PAD_DOWN)) {
        func_800977F8(screen, 0, 1);
    }
    if (PAD_PRESSED(PAD_TRIANGLE)) {
        SOUND.playSound(0x800450BD);
        screen->state = TASK_KILL;
    }
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus_10", func_80097F2C);

/* The map screen's update */
void func_800984A4(StatusMapScreen *screen, TextWindow **windows) {
    s32 area;

    switch (screen->state) {
    case TASK_INIT:
    default:
        switch (screen->substate) {
        case 0:
        default:
            if (FILE_CACHE.isLoading(screen->textFile) == 0) {
                screen->substate++;
            }
            break;
        case 1:
            windows[0] = createTextWindow(screen->layer, 1, 0x14, 0x16);
            windows[0]->setLines(windows[0], 2);
            screen->fade.duration = 10;
            D_8009AA00.func_800999CC(screen->visited);
            area = D_8009AA00.getArea() + 1;
            screen->homeX = STSTATUS_data.spots[area].x + 0xC;
            screen->homeY = STSTATUS_data.spots[area].y + 0xC;
            screen->speedX = 1;
            screen->speedY = 1;
            while (screen->homeX + screen->scrollX != screen->cursorX) {
                func_800977F8(screen, 1, 0);
            }
            while (screen->homeY + screen->scrollY != screen->cursorY) {
                func_800977F8(screen, 0, 1);
            }
            screen->speedX = 0;
            screen->speedY = 0;
            screen->ready = 1;
            screen->nextState(screen);
            break;
        }
        break;
    case TASK_RUN:
        func_80097A68(screen, windows);
        func_80097644(screen, windows);
        func_80097F2C(screen);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_8009868C(FieldMenuScreen *menu, s32 extra) {
    StatusMapScreen *screen = createTask(func_800984A4, sizeof(StatusMapScreen), 4);

    screen->layer = 0x1000;
    screen->depth = 5;
    screen->menu = menu;
    screen->lateGame = D_8009AA00.isLateGame();
    if (screen->lateGame == 0) {
        screen->archive = FILE_STATUS_BG << 16;
        screen->archive1 = (FILE_STATUS_BG << 16) + 1;
        screen->archive2 = (FILE_STATUS_BG << 16) + 2;
        screen->textFile = TEXT_FILE(9);
        screen->file = FILE_STATUS_BG;
    } else {
        screen->archive = (FILE_STATUS_BG + 2) << 16;
        screen->archive1 = ((FILE_STATUS_BG + 2) << 16) + 1;
        screen->archive2 = ((FILE_STATUS_BG + 2) << 16) + 2;
        screen->textFile = TEXT_FILE(2);
        screen->file = FILE_STATUS_BG + 2;
    }
    FILE_CACHE.request(screen->textFile);
    screen->height = 0xF0;
    screen->top = 0x10;
    return (Task *)screen;
}

void STSTATUS_setScrollBarX(ScrollBar *bar, s32 x, s32 width) {
    bar->x = x;
    bar->width = width;
}

void STSTATUS_setScrollBarRange(ScrollBar *bar, s32 top, s32 bottom) {
    bar->top = top;
    bar->bottom = bottom;
    bar->hasRange = 1;
}

void STSTATUS_setScrollBarCount(ScrollBar *bar, s32 pageSize, s32 count) {
    bar->pageSize = pageSize;
    bar->count = count;
    bar->hasCount = 1;
}

void STSTATUS_setScrollBarPos(ScrollBar *bar, s32 pos) {
    bar->pos = pos;
}

void STSTATUS_updateScrollBar(ScrollBar *bar) {
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

ScrollBar *STSTATUS_createScrollBar(void) {
    ScrollBar *bar = createTask(STSTATUS_updateScrollBar, sizeof(ScrollBar), 0);

    bar->setX = STSTATUS_setScrollBarX;
    bar->setRange = STSTATUS_setScrollBarRange;
    bar->setCount = STSTATUS_setScrollBarCount;
    bar->setPos = STSTATUS_setScrollBarPos;
    bar->layer = 0x1000;
    bar->depth = 0;
    return bar;
}

void func_80098A50(FieldMenuScreen *menu, FieldMenuScreenChildren *children) {
    Task *(*open)(FieldMenuScreen *, s32);

    switch (menu->substate) {
    case 0:
    default:
        open = STSTATUS_screens[FIELD_MENU_CHOICE[1]][FIELD_MENU_CHOICE[0]];
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
            STSTATUS_data.funcs.loadFiles();
            menu->substate++;
            break;
        case 1:
            if (STSTATUS_data.funcs.filesLoading() == 0 && FILE_CACHE.isLoading(menu->bgFile) == 0 &&
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

void STSTATUS_loadFiles(void) {
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

s32 STSTATUS_filesLoading(void) {
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

void STSTATUS_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STSTATUS_updateFade(PanelAnim *fade) {
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

void STSTATUS_startLerp(StatusLerp *lerp, s32 from, s32 to, s32 frames) {
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

s32 STSTATUS_updateLerp(StatusLerp *lerp) {
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

void STSTATUS_listItems(s32 list, u16 *out) {
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

/* The items whose kind (data[2]) is one of D_8009A90C's four */
s32 func_8009930C(u16 *out) {
    s32 i;
    s32 j;
    s32 count;
    u8 *data;

    STSTATUS_data.itemCount = ITEM_FUNCS->list(2, (u16 *)STSTATUS_data.items);
    STSTATUS_data.item2Count = ITEM_FUNCS->list(3, (u16 *)STSTATUS_data.items2);
    count = 0;
    for (i = 0; i < STSTATUS_data.itemCount; i++) {
        data = GET_ITEM[0](STSTATUS_data.items[i])->data;
        for (j = 0; j < 4; j++) {
            if (data[2] == D_8009A90C[j]) {
                out[count++] = STSTATUS_data.items[i];
            }
        }
    }
    for (i = 0; i < STSTATUS_data.item2Count; i++) {
        data = GET_ITEM[0](STSTATUS_data.items2[i])->data;
        for (j = 0; j < 4; j++) {
            if (data[2] == D_8009A90C[j]) {
                out[count++] = STSTATUS_data.items2[i];
            }
        }
    }
    return count;
}

/* The items of one kind (data[2]) */
s32 func_800994D0(s32 kind, u16 *out) {
    s32 i;
    s32 count;

    STSTATUS_data.itemCount = ITEM_FUNCS->list(2, (u16 *)STSTATUS_data.items);
    STSTATUS_data.item2Count = ITEM_FUNCS->list(3, (u16 *)STSTATUS_data.items2);
    count = 0;
    for (i = 0; i < STSTATUS_data.itemCount; i++) {
        if (GET_ITEM[0](STSTATUS_data.items[i])->data[2] == kind) {
            out[count++] = STSTATUS_data.items[i];
        }
    }
    for (i = 0; i < STSTATUS_data.item2Count; i++) {
        if (GET_ITEM[0](STSTATUS_data.items2[i])->data[2] == kind) {
            out[count++] = STSTATUS_data.items2[i];
        }
    }
    return count;
}

/* Whether a partner can put an item in an equipment slot (-1: none): data[4]
   has a bit per partner; data[2] 1 can't go in slot 3, nor 2 in slot 2 */
s32 STSTATUS_canEquip(s32 partner, s32 slot, s32 item) {
    u8 *data;

    if (item != -1) {
        data = GET_ITEM[0](item)->data;
        if (!((data[4] >> partner) & 1)) {
            return 0;
        }
        if (data[2] == 1) {
            if (slot == 3) {
                return 0;
            }
        } else if (data[2] == 2) {
            if (slot == 2) {
                return 0;
            }
        }
    }
    return 1;
}

/* Puts an item in a partner's equipment slot (0 or less: empties it), moving
   the counts between GAME.items and GAME.equippedItems. Kind 7 takes slots 2
   and 3; kind 8 replaces one in slots 4 and 5 with the same data[3] */
void STSTATUS_equip(s32 partner, s32 slot, s32 item) {
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(partner);
    s16 *equip;
    s16 *pair;
    u8 *data;
    s32 group;
    s32 old;
    s32 i;
    s32 id = item; /* the match depends on this copy and on *(stats->equip + slot) */

    old = *(stats->equip + slot);
    if (old != 0) {
        GAME.equippedItems[old]--;
        GAME.items[old]++;
        data = GET_ITEM[0](old)->data;
        if (data[2] == 7) {
            stats->equip[2] = 0;
            stats->equip[3] = 0;
        } else {
            *(stats->equip + slot) = 0;
        }
    }
    if (id > 0) {
        data = GET_ITEM[0](id)->data;
        if (data[2] == 7) {
            pair = &stats->equip[2];
            if (stats->equip[2] == 0) {
                pair = NULL;
                if (stats->equip[3] != 0) {
                    pair = &stats->equip[3];
                }
            }
            if (pair != NULL) {
                GAME.equippedItems[*pair]--;
                GAME.items[*pair]++;
                *pair = 0;
            }
        } else if (data[2] == 8) {
            group = data[3];
            for (i = 0; i < 2; i++) {
                equip = &stats->equip[i + 4];
                if (*equip != 0) {
                    data = GET_ITEM[0](*equip)->data;
                    if (data[3] == group) {
                        GAME.equippedItems[*equip]--;
                        GAME.items[*equip]++;
                        *equip = 0;
                    }
                }
            }
        }
        GAME.equippedItems[id]++;
        GAME.items[id]--;
        data = GET_ITEM[0](id)->data;
        if (data[2] == 7) {
            stats->equip[2] = id;
            stats->equip[3] = id;
        } else {
            *(stats->equip + slot) = id;
        }
    }
}

s32 STSTATUS_isLateGame(void) {
    if (GAME.fieldMode >= 0x2D7) {
        return -1;
    }
    return GAME.fieldMode >= 0x270;
}

s32 STSTATUS_getArea(void) {
    return D_8009A910[(u8)GAME.fieldMode] & 0x7F;
}

void func_800999CC(s32 *out) {
    s32 first;
    s32 last;
    s32 i;
    s32 area;
    s32 found;

    if (STSTATUS_isLateGame() == 0) {
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
