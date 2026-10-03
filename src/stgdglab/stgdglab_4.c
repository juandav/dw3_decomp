#include "common.h"
#include "stgdglab.h"

void STGDGLAB_openMenu(LabMenu *menu) {
    menu->state = TASK_DONE;
    menu->counter = 0;
    STGDGLAB_data.funcs.startFade(&menu->panels[3], 1);
}

void STGDGLAB_closeMenu(LabMenu *menu) {
    LabMenuWindows *windows;
    s32 i;

    menu->state = TASK_DONE;
    menu->counter = 1;
    windows = menu->children;
    STGDGLAB_data.funcs.startFade(&menu->panels[3], 0);
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

void func_80088164(LabMenu *menu, LabMenuWindows *windows) {
    PartnerTotals totals;
    s32 *pos;
    s32 member;
    s32 i;

    for (i = 0; i < 5; i++) {
        pos = &STGDGLAB_data.pos[i * 3];
        if (windows->unk14[i] == NULL) {
            windows->unk14[i] = createTextWindow(menu->layer, 3, pos[1], pos[2]);
            windows->unk14[i]->setDepth(windows->unk14[i], menu->depth - 1);
        }
        windows->unk14[i]->setString(windows->unk14[i], FILE_CACHE.load(TEXT_FILE(0x3A)), pos[0]);
    }
    member = GAME.funcs.getPartyMember(menu->lab->unk64);
    if (member >= 0) {
        GAME.funcs.computeStats(member, &totals);
    }
    for (i = 0; i < 5; i++) {
        pos = &STGDGLAB_data.pos[(i + 5) * 3];
        if (windows->unk28[i] == NULL) {
            windows->unk28[i] = createTextWindow(menu->layer, 3, pos[1], pos[2]);
            windows->unk28[i]->setDepth(windows->unk28[i], menu->depth - 1);
        }
        if (member < 0) {
            if (i == 0) {
                windows->unk28[0]->setString(windows->unk28[0], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1C);
            } else {
                windows->unk28[i]->setString(windows->unk28[i], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x12);
            }
        } else {
            windows->unk28[i]->setNumber(windows->unk28[i], 0, totals.stats[D_8008ECB4[i]]);
        }
        windows->unk28[i]->setRightAlign(windows->unk28[i], 1);
    }
    pos = &STGDGLAB_data.pos[30];
    if (windows->unk3C == NULL) {
        windows->unk3C = createTextWindow(menu->layer, 1, pos[1], pos[2]);
        windows->unk3C->setDepth(windows->unk3C, menu->depth - 1);
    }
    if (member < 0) {
        windows->unk3C->setString(windows->unk3C, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1B);
        if (windows->unk40 != NULL) {
            windows->unk40->setPalette(windows->unk40, 7);
        }
    } else {
        windows->unk3C->setString(windows->unk3C, GAME_FUNCS.getPartnerStats(member)->name, -1);
        if (windows->unk40 != NULL) {
            windows->unk40->setPalette(windows->unk40, 0);
        }
    }
    menu->unkFC[3] = 0;
}

/* The main menu's states: fades its panels in, picks one of the three
   screens with up and down, then shows the party's stats while left and
   right go through them; circle opens the partner's entries */
void func_800884A0(LabMenu *menu, LabMenuWindows *windows) {
    TextWindow **items;
    s32 old;
    /* The match depends on cases 4, 5 and 18 having their own counters, and
       on case 5 clearing its count after i */
    s32 closed;
    s32 faded;
    s32 done;
    s32 i;
    s32 m;
    s32 j;
    s32 k;

    switch (menu->substate) {
    case 0:
    default:
        STGDGLAB_data.funcs.startFade(&menu->panels[0], 1);
        STGDGLAB_data.funcs.startFade(&menu->panels[2], 1);
        menu->substate++;
        break;
    case 1:
        done = 0;
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[0])) {
            if (windows->title == NULL) {
                windows->title = createTextWindow(menu->layer, 1, 0xAE, 0x15);
                windows->title->setDepth(windows->title, menu->depth - 1);
            }
            windows->title->setPos(windows->title, 0xAE, 0x15);
            done = 1;
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x3A)), 1);
        }
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[2])) {
            if (windows->label == NULL) {
                windows->label = createTextWindow(menu->layer, 1, 0xD3, 0xCC);
                windows->label->setDepth(windows->label, menu->depth - 1);
            }
            windows->label->setPos(windows->label, 0xD3, 0xCC);
            done++;
            windows->label->setString(windows->label, FILE_CACHE.load(TEXT_FILE(0x3A)), 5);
        }
        if (done == 2) {
            STGDGLAB_data.funcs.startFade(&menu->panels[1], 1);
            menu->substate++;
        }
        break;
    case 2:
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[1])) {
            for (i = 0; i < 3; i++) {
                if (windows->options[i] == NULL) {
                    windows->options[i] = createTextWindow(menu->layer, 1, 0xA7, i * 0xE + 0x31);
                    windows->options[i]->setDepth(windows->options[i], menu->depth - 1);
                }
                windows->options[i]->setString(windows->options[i], FILE_CACHE.load(TEXT_FILE(0x3A)), i + 2);
            }
            if (windows->cursor == NULL) {
                windows->cursor = createCursor(menu->layer, 1, 0x9A, menu->choice * 0xE + 0x31);
            }
            windows->cursor->setVisible(windows->cursor, 1);
            menu->substate++;
        }
        break;
    case 3:
        old = menu->choice;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            if (--menu->choice < 0) {
                menu->choice = 0;
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            if (++menu->choice >= 3) {
                menu->choice = 2;
            }
        }
        if (old != menu->choice) {
            SOUND.playSound(0x8004513E);
            windows->cursor->setPos(windows->cursor, 0x9A, menu->choice * 0xE + 0x31);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            menu->step = 0;
            menu->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            menu->step = 1;
            menu->substate++;
            menu->lab->fadeOut(menu->lab);
        }
        break;
    case 4:
        for (j = 0, items = menu->children; j < menu->childCount - 2; j++, items++) {
            if (*items != NULL) {
                (*items)->setVisible(*items, 0);
            }
        }
        windows->cursor->setVisible(windows->cursor, 0);
        STGDGLAB_data.funcs.startFade(&menu->panels[0], 0);
        STGDGLAB_data.funcs.startFade(&menu->panels[1], 0);
        STGDGLAB_data.funcs.startFade(&menu->panels[2], 0);
        menu->substate++;
        break;
    case 5:
        for (k = 0, faded = 0; k < 3; k++) {
            faded += STGDGLAB_data.funcs.updateFade(&menu->panels[k]);
            if (faded == 3) {
                if (menu->step == 0) {
                    menu->setSubstate(menu, 10);
                    STGDGLAB_data.funcs.startFade(&menu->panels[3], 1);
                    menu->lab->unk64 = 0;
                    if (menu->choice == 0) {
                        menu->unk110 = menu->lab->unk5C;
                    } else {
                        menu->unk110 = menu->lab->partyCount;
                    }
                } else {
                    menu->setState(menu, TASK_KILL);
                }
            }
        }
        break;
    case 10:
        STGDGLAB_data.funcs.startFade(&menu->panels[4], 1);
        STGDGLAB_data.funcs.startFade(&menu->panels[5], 1);
        STGDGLAB_data.funcs.startFade(&menu->panels[6], 1);
        STGDGLAB_data.funcs.startFade(&menu->panels[7], 1);
        if (menu->choice == 0) {
            STGDGLAB_data.funcs.startFade(&menu->panels[8], 1);
        }
        menu->substate++;
        break;
    case 11:
        STGDGLAB_data.funcs.updateFade(&menu->panels[3]);
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[4])) {
            func_80088164(menu, windows);
            if (windows->label == NULL) {
                windows->label = createTextWindow(menu->layer, 1, 0xA1, 0x17);
                windows->label->setDepth(windows->label, menu->depth - 1);
            }
            windows->label->setPos(windows->label, 0xA1, 0x17);
            windows->label->setString(windows->label, FILE_CACHE.load(TEXT_FILE(0x3A)), 6);
            menu->substate++;
        }
        break;
    case 12:
        if (menu->choice == 0 && STGDGLAB_data.funcs.updateFade(&menu->panels[8])) {
            if (windows->unk40 == NULL) {
                windows->unk40 = createTextWindow(menu->layer, 1, 0xF, 0x55);
                windows->unk40->setDepth(windows->unk40, menu->depth - 1);
            }
            windows->unk40->setString(windows->unk40, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x14);
        }
        STGDGLAB_data.funcs.updateFade(&menu->panels[5]);
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[6])) {
            if (windows->title == NULL) {
                windows->title = createTextWindow(menu->layer, 1, 0xAE, 0x49);
            }
            windows->title->setPos(windows->title, 0xAE, 0x49);
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x3A)), menu->choice + 0x18);
            menu->substate++;
        }
        break;
    case 14:
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[7])) {
            menu->substate++;
        }
        break;
    case 15:
        old = menu->lab->unk64;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            if (--menu->lab->unk64 < 0) {
                menu->lab->unk64 = menu->unk110 - 1;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            if (++menu->lab->unk64 > menu->unk110 - 1) {
                menu->lab->unk64 = 0;
            }
        }
        if (old != menu->lab->unk64) {
            SOUND.playSound(0x4001B);
            func_80088164(menu, windows);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            menu->step = 1;
            menu->substate++;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            menu->step = 0;
            menu->substate++;
        } else if (PAD_PRESSED(PAD_CIRCLE) && menu->choice == 0 &&
                   GAME.funcs.getPartyMember(menu->lab->unk64) >= 0) {
            menu->step = 2;
            menu->substate++;
            SOUND.playSound(0x4001C);
        }
        break;
    case 16:
        STGDGLAB_data.funcs.startFade(&menu->panels[7], 0);
        menu->substate++;
        break;
    case 17:
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[7])) {
            if (menu->step == 0) {
                STGDGLAB_data.funcs.startFade(&menu->panels[3], 0);
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
            }
            STGDGLAB_data.funcs.startFade(&menu->panels[4], 0);
            STGDGLAB_data.funcs.startFade(&menu->panels[5], 0);
            STGDGLAB_data.funcs.startFade(&menu->panels[6], 0);
            if (menu->choice == 0) {
                STGDGLAB_data.funcs.startFade(&menu->panels[8], 0);
            }
            if (windows->title != NULL) {
                windows->title->setVisible(windows->title, 0);
            }
            if (windows->label != NULL) {
                windows->label->setVisible(windows->label, 0);
            }
            if (windows->unk40 != NULL) {
                windows->unk40->setVisible(windows->unk40, 0);
            }
            menu->substate++;
        }
        break;
    case 18:
        closed = 0;
        for (m = menu->step != 0; m < 6; m++) {
            closed += STGDGLAB_data.funcs.updateFade(&menu->panels[m + 3]);
        }
        if (menu->step == 1) {
            if (closed == 5) {
                menu->nextSubstate(menu);
                menu->picked = 1;
            }
        } else if (menu->step == 2) {
            if (closed == 5) {
                menu->setSubstate(menu, 30);
            }
        } else if (closed == 6) {
            menu->setSubstate(menu, 0);
        }
        break;
    case 19:
        if (menu->picked == 0) {
            menu->setSubstate(menu, 10);
            if (menu->panels[3].level == 0) {
                STGDGLAB_data.funcs.startFade(&menu->panels[3], 1);
            }
        }
        break;
    case 30:
        if (windows->panel == NULL) {
            windows->panel = func_8008E320(GAME.funcs.getPartyMember(menu->lab->unk64), 1, 1);
        }
        menu->substate++;
        break;
    case 31:
        if (windows->panel == NULL) {
            menu->setSubstate(menu, 10);
        }
        break;
    }
}

/* Draws the main menu's frames and the party's animations */
void func_800893FC(LabMenu *menu, void *children) {
    SpriteDrawer sprite;
    LabAnim *anim;
    s32 member;
    s32 id;
    s32 i;

    initSpriteDrawer(&sprite);
    if (menu->substate < 10) {
        sprite.setTexture(0x280, 0x100);
        sprite.setLayerId(menu->layer, menu->depth);
        if (menu->panels[0].level != 0) {
            if (menu->panels[0].level != 0x1000) {
                sprite.setScale(menu->panels[0].level, 0x1000, 0x1000);
                sprite.setPivot(0x140, 0x15);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x20, 0x92, 0xF);
        }
        if (menu->panels[1].level != 0) {
            if (menu->panels[1].level != 0x1000) {
                sprite.setScale(menu->panels[1].level, 0x1000, 0x1000);
                sprite.setPivot(0x140, 0x45);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x21, 0x92, 0x2A);
        }
        if (menu->panels[2].level != 0) {
            if (menu->panels[2].level != 0x1000) {
                sprite.setScale(menu->panels[2].level, 0x1000, 0x1000);
                sprite.setPivot(0x140, 0xD2);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x24, 0xC6, 0xC4);
        }
        return;
    }
    member = GAME_FUNCS.getPartyPartner(menu->lab->unk64);
    if (GFX.funcs.getTime() - menu->unkF4 >= 12) {
        menu->unkF4 = GFX.funcs.getTime();
        if (member >= 0) {
            anim = &STGDGLAB_data.anim[member];
            menu->unkFC[3]++;
            if (anim->frames[menu->unkFC[3]] == -1 || menu->unkFC[3] >= 7) {
                menu->unkFC[3] = 0;
            }
        }
        for (i = 0; i < menu->lab->unk5C; i++) {
            id = GAME.funcs.getPartyPartner(i);
            if (id >= 0) {
                anim = &STGDGLAB_data.anim[id];
                menu->unkFC[i]++;
                if (anim->frames[menu->unkFC[i]] == -1) {
                    menu->unkFC[i] = 0;
                }
            }
        }
    }
    if (GFX.funcs.getTime() - menu->unkF8 >= 10) {
        menu->unkF8 = GFX.funcs.getTime();
        menu->unkFC[4]++;
        if (menu->unkFC[4] >= 4) {
            menu->unkFC[4] = 0;
        }
    }
    sprite.setTexture(0x280, 0x100);
    sprite.setLayerId(menu->layer, menu->depth);
    if (menu->panels[7].level != 0) {
        if (menu->panels[7].level != 0x1000) {
            sprite.setScale(menu->panels[7].level, 0x1000, 0x1000);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            sprite.setTexture(0x140, 0);
            sprite.setLayerId(menu->layer, menu->depth - 1);
            sprite.setClutRow(menu->unkFC[4]);
            sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xD, menu->lab->unk64 * 0x30 + 0xA5, 0x65);
            sprite.setLayerId(menu->layer, menu->depth);
            sprite.setClutRow(0);
        }
        sprite.setTexture(0x280, 0x100);
        for (i = 0; i < menu->lab->unk5C; i++) {
            id = GAME.funcs.getPartyPartner(i);
            if (id >= 0) {
                if (menu->panels[7].level != 0x1000) {
                    sprite.setPivot(i * 0x30 + 0xB4, 0x8A);
                }
                anim = &STGDGLAB_data.anim[id];
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), anim->frames[menu->unkFC[i]], i * 0x30 + 0xA5, 0x81);
            }
        }
    }
    if (menu->panels[6].level != 0) {
        if (menu->panels[6].level != 0x1000) {
            sprite.setScale(menu->panels[6].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x8A);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x140, 0);
        sprite.setLayerId(menu->layer, menu->depth - 1);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x10, 0x90, 0x5F);
        sprite.setTexture(0x140, 0);
        sprite.setLayerId(menu->layer, menu->depth);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x11, 0x90, 0x5F);
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x27, 0x90, 0x5F);
    }
    if (menu->panels[3].level != 0) {
        if (menu->panels[3].level != 0x1000) {
            sprite.setScale(menu->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x2F);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        if (member >= 0) {
            anim = &STGDGLAB_data.anim[member];
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), anim->frames[menu->unkFC[3]], 0x10, 0x16);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xE, 0, 0x13);
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x1E, 0, 0x13);
    }
    sprite.setTexture(0x280, 0x100);
    if (menu->panels[4].level != 0) {
        if (menu->panels[4].level != 0x1000) {
            sprite.setScale(menu->panels[4].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x1D);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x25, 0x8F, 0xF);
    }
    if (menu->panels[5].level != 0) {
        if (menu->panels[5].level != 0x1000) {
            sprite.setScale(menu->panels[5].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x4E);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x20, 0x92, 0x43);
    }
    if (menu->panels[8].level != 0) {
        if (menu->panels[8].level != 0x1000) {
            sprite.setScale(menu->panels[8].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x5A);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x26, 0, 0x4D);
    }
}

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
        if (STGDGLAB_data.funcs.updateFade(&menu->panels[3]) != 0) {
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

void func_8008A250(LabScreen1 *screen, LabScreen1Windows *windows) {
    PartnerTotals totals;
    s32 *pos;
    s32 member;
    s32 i;

    for (i = 0; i < 5; i++) {
        pos = &STGDGLAB_data.pos[i * 3];
        if (windows->labels[i] == NULL) {
            windows->labels[i] = createTextWindow(screen->layer, 3, pos[1], pos[2]);
            windows->labels[i]->setDepth(windows->labels[i], screen->depth - 1);
        }
        windows->labels[i]->setString(windows->labels[i], FILE_CACHE.load(TEXT_FILE(0x3A)), pos[0]);
        windows->labels[i]->setPos(windows->labels[i], pos[1], pos[2] + screen->unk5C * 0x7A);
    }
    member = screen->partners[screen->unk60];
    if (member >= 0) {
        GAME.funcs.computeStats(member, &totals);
    }
    for (i = 0; i < 5; i++) {
        pos = &STGDGLAB_data.pos[(i + 5) * 3];
        if (windows->values[i] == NULL) {
            windows->values[i] = createTextWindow(screen->layer, 3, pos[1], pos[2]);
            windows->values[i]->setDepth(windows->values[i], screen->depth - 1);
        }
        windows->values[i]->setPos(windows->values[i], pos[1], pos[2] + screen->unk5C * 0x7A);
        if (member < 0) {
            if (i == 0) {
                windows->values[0]->setString(windows->values[0], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1C);
            } else {
                windows->values[i]->setString(windows->values[i], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x12);
            }
        } else {
            windows->values[i]->setNumber(windows->values[i], 0, totals.stats[D_8008ECC8[i]]);
        }
        windows->values[i]->setRightAlign(windows->values[i], 1);
    }
    pos = &STGDGLAB_data.pos[30];
    if (windows->name == NULL) {
        windows->name = createTextWindow(screen->layer, 1, pos[1], pos[2]);
        windows->name->setDepth(windows->name, screen->depth - 1);
    }
    if (member < 0) {
        windows->name->setString(windows->name, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1B);
        windows->unk30->setPalette(windows->unk30, 7);
    } else {
        windows->name->setString(windows->name, GAME_FUNCS.getPartnerStats(member)->name, -1);
        windows->unk30->setPalette(windows->unk30, 0);
    }
    windows->name->setPos(windows->name, pos[1], pos[2] + screen->unk5C * 0x7A);
    screen->frame = 0;
}

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

/* Draws the first screen's frames and the party's animations */
void func_8008A6A4(LabScreen1 *screen, void *children) {
    SpriteDrawer sprite;
    LabAnim *anim;
    s32 member;
    s32 id;
    s32 i;

    member = screen->partners[screen->unk60];
    if (GFX.funcs.getTime() - screen->animTime >= 12) {
        screen->animTime = GFX.funcs.getTime();
        if (member >= 0) {
            anim = &STGDGLAB_data.anim[member];
            screen->frame++;
            if (anim->frames[screen->frame] == -1 || screen->frame >= 7) {
                screen->frame = 0;
            }
        }
        for (i = 0; i < screen->lab->unk5C; i++) {
            id = GAME.funcs.getPartyPartner(i);
            if (id >= 0) {
                screen->frames[i]++;
                anim = &STGDGLAB_data.anim[id];
                if (anim->frames[screen->frames[i]] == -1) {
                    screen->frames[i] = 0;
                }
            }
        }
    }
    if (GFX.funcs.getTime() - screen->blinkTime >= 10) {
        screen->blinkTime = GFX.funcs.getTime();
        screen->clut++;
        if (screen->clut >= 4) {
            screen->clut = 0;
        }
        screen->clut2++;
        if (screen->clut2 >= 6) {
            screen->clut2 = 0;
        }
    }
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    sprite.setLayerId(screen->layer, screen->depth);
    if (screen->panels[0].level != 0) {
        if (screen->panels[0].level != 0x1000) {
            sprite.setScale(screen->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0, screen->unk5C * 0x7A + 0x2F);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        if (member >= 0) {
            anim = &STGDGLAB_data.anim[member];
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), anim->frames[screen->frame], 0x10,
                        screen->unk5C * 0x7A + 0x16);
        }
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xE, 0, screen->unk5C * 0x7A + 0x13);
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x1E, 0, screen->unk5C * 0x7A + 0x13);
    }
    if (screen->panels[1].level != 0) {
        if (screen->panels[1].level != 0x1000) {
            sprite.setScale(screen->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0, 0xD1);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x26, 0, 0xC4);
    }
    if (screen->panels[2].level != 0) {
        if (screen->panels[2].level != 0x1000) {
            sprite.setScale(screen->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x15);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x20, 0x92, 0xF);
    }
    if (screen->panels[4].level != 0) {
        if (screen->panels[4].level != 0x1000) {
            sprite.setScale(screen->panels[4].level, 0x1000, 0x1000);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
            if (screen->count >= 2) {
                sprite.setLayerId(screen->layer, screen->depth - 1);
                sprite.setClutRow(screen->clut);
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x31, 0xB8, 0xB6);
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x32, 0x100, 0xB6);
                sprite.setLayerId(screen->layer, screen->depth);
                sprite.setClutRow(0);
            }
        }
        for (i = 0; i < screen->lab->unk5C; i++) {
            id = GAME.funcs.getPartyPartner(i);
            if (id >= 0) {
                if (screen->panels[4].level != 0x1000) {
                    sprite.setPivot(i * 0x30 + 0xB4, 0x4E);
                }
                anim = &STGDGLAB_data.anim[id];
                sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), anim->frames[screen->frames[i]], i * 0x30 + 0xA5, 0x47);
            }
        }
        if (member >= 0) {
            if (screen->panels[4].level != 0x1000) {
                sprite.setPivot(0xE4, 0xB5);
            }
            anim = &STGDGLAB_data.anim[member];
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), anim->frames[screen->frame], 0xD5, 0xAE);
        }
    }
    if (screen->panels[3].level != 0) {
        if (screen->panels[3].level != 0x1000) {
            sprite.setScale(screen->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x85);
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        sprite.setTexture(0x280, 0x100);
        sprite.setLayerId(screen->layer, screen->depth - 1);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x33, 0xAD, 0x66);
        sprite.setClutRow(screen->clut);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), screen->lab->unk64 + 0x38, 0xA5, 0x41);
        sprite.setClutRow(0);
        sprite.setTexture(0x140, 0);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x10, 0x90, 0x25);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xB, 0xD5, 0x92);
        sprite.setLayerId(screen->layer, screen->depth);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0x11, 0x90, 0x25);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xC, 0xD5, 0x92);
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x2D, 0x90, 0x2A);
        if (screen->panels[3].level != 0x1000) {
            sprite.setPivot(0x48, 0x69);
        }
        sprite.setClutRow(screen->clut2);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x3B, 0x33, 0x4A);
    }
}

/* The first screen's states: fades its panels in, picks a partner with left
   and right, then swaps it into the party (cross) or shows its entries
   (circle) */
void func_8008B0A4(LabScreen1 *screen, LabScreen1Windows *windows) {
    s32 old;

    switch (screen->substate) {
    case 0:
    default:
        STGDGLAB_data.funcs.startFade(&screen->panels[1], 1);
        STGDGLAB_data.funcs.startFade(&screen->panels[2], 1);
        screen->substate++;
        break;
    case 1:
        STGDGLAB_data.funcs.updateFade(&screen->panels[1]);
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[2])) {
            STGDGLAB_data.funcs.startFade(&screen->panels[0], 1);
            STGDGLAB_data.funcs.startFade(&screen->panels[3], 1);
            if (windows->title == NULL) {
                windows->title = createTextWindow(screen->layer, 1, 0xAE, 0x15);
            }
            windows->title->setString(windows->title, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x1D);
            if (windows->unk30 == NULL) {
                windows->unk30 = createTextWindow(screen->layer, 1, 0xF, 0xCC);
            }
            windows->unk30->setString(windows->unk30, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x14);
            if (screen->count == 0) {
                windows->unk30->setPalette(windows->unk30, 7);
            } else {
                windows->unk30->setPalette(windows->unk30, 0);
            }
            screen->substate++;
        }
        break;
    case 2:
        STGDGLAB_data.funcs.updateFade(&screen->panels[0]);
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[3])) {
            STGDGLAB_data.funcs.startFade(&screen->panels[4], 1);
            func_8008A250(screen, windows);
            screen->substate++;
        }
        break;
    case 3:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[4])) {
            screen->substate++;
        }
        break;
    case 4:
        old = screen->unk60;
        if (screen->count >= 2) {
            if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
                screen->unk60--;
                if (screen->unk60 < 0) {
                    screen->unk60 = screen->count - 1;
                }
            } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
                screen->unk60++;
                if (screen->unk60 > screen->count - 1) {
                    screen->unk60 = 0;
                }
            }
        }
        if (old != screen->unk60) {
            SOUND.playSound(0x4001B);
            func_8008A250(screen, windows);
        } else if (PAD_PRESSED(PAD_CIRCLE)) {
            if (screen->partners[screen->unk60] >= 0) {
                screen->step = 2;
                screen->substate++;
                SOUND.playSound(0x4001C);
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            if (GAME.funcs.getPartyMember(screen->lab->unk64) >= 0 || screen->partners[screen->unk60] >= 0) {
                screen->step = 1;
                screen->substate++;
                SOUND.playSound(0x4001C);
            } else {
                SOUND.playSound(0x800450BD);
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            screen->step = 0;
            screen->substate++;
        }
        break;
    case 5:
        STGDGLAB_data.funcs.startFade(&screen->panels[4], 0);
        screen->substate++;
        break;
    case 6:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[4])) {
            func_8008A624((Task *)screen);
            STGDGLAB_data.funcs.startFade(&screen->panels[0], 0);
            STGDGLAB_data.funcs.startFade(&screen->panels[1], 0);
            STGDGLAB_data.funcs.startFade(&screen->panels[2], 0);
            STGDGLAB_data.funcs.startFade(&screen->panels[3], 0);
            if (screen->step != 0) {
                screen->lab->closeMenu(screen->lab);
            }
            screen->substate++;
        }
        break;
    case 7:
        STGDGLAB_data.funcs.updateFade(&screen->panels[0]);
        STGDGLAB_data.funcs.updateFade(&screen->panels[1]);
        STGDGLAB_data.funcs.updateFade(&screen->panels[2]);
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[3]) && screen->lab->menuOpen(screen->lab)) {
            screen->substate++;
        }
        break;
    case 8:
        if (screen->step == 1) {
            GAME.party[screen->lab->unk64] = screen->partners[screen->unk60];
            screen->lab->packParty(screen->lab);
        }
        if (screen->step == 2) {
            screen->unk5C = 0;
            STGDGLAB_data.funcs.startFade(&screen->panels[0], 1);
            if (windows->panel == NULL) {
                windows->panel = func_8008E320(screen->partners[screen->unk60], 1, 1);
            }
            screen->substate++;
        } else {
            screen->setState(screen, TASK_KILL);
        }
        break;
    case 9:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[0])) {
            func_8008A250(screen, windows);
            screen->substate++;
        }
        break;
    case 10:
        if (windows->panel->substate >= 2 && PAD_PRESSED(PAD_TRIANGLE)) {
            STGDGLAB_data.funcs.startFade(&screen->panels[0], 0);
            func_8008A624((Task *)screen);
            screen->substate++;
        }
        break;
    case 11:
        if (STGDGLAB_data.funcs.updateFade(&screen->panels[0]) && windows->panel == NULL) {
            if (screen->lab->menuOpen(screen->lab)) {
                screen->lab->openMenu(screen->lab);
                screen->substate++;
            }
            screen->unk5C = 1;
            screen->setSubstate(screen, 0);
        }
        break;
    }
}

void func_8008B960(LabScreen1 *screen, void *children) {
    s32 party[3];
    s32 i;
    s32 j;
    s32 id;
    s32 free;

    switch (screen->state) {
    case TASK_INIT:
    default:
        screen->nextState(screen);
        screen->panels[0].duration = 10;
        screen->panels[1].duration = 8;
        screen->panels[2].duration = 10;
        screen->panels[3].duration = 10;
        screen->panels[4].duration = 8;
        screen->unk5C = 1;
        for (i = 0; i < 3; i++) {
            party[i] = GAME.funcs.getPartyPartner(i);
        }
        for (i = 0; i < 8; i++) {
            id = GAME.partners[i].unlocked - 3;
            screen->partners[i] = -1;
            if (id >= 0) {
                j = 0;
                free = 1;
                for (; j < 3; j++) {
                    if (party[j] >= 0 && id == party[j]) {
                        free = 0;
                    }
                }
            } else {
                free = 0;
            }
            if (free) {
                screen->partners[screen->count++] = id;
            }
        }
        id = party[screen->lab->unk64];
        if (screen->lab->partyCount >= 2 && id >= 0) {
            screen->count++;
        }
        break;
    case TASK_RUN:
        func_8008B0A4(screen, children);
        func_8008A6A4(screen, children);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_8008BB30(Lab *lab) {
    LabScreen1 *screen = createTask(func_8008B960, sizeof(LabScreen1), 0x38);

    screen->layer = 0x1000;
    screen->depth = 2;
    screen->lab = lab;
    return (Task *)screen;
}

/* Creates the panel's windows and cursors */
void func_8008BB78(LabPanel2 *panel, LabPanel2Windows *windows) {
    s32 i;
    TextWindow **items;

    windows->unk0 = createTextWindow(panel->layer, 1, 0x9A, 0x46);
    windows->unk4 = createTextWindow(panel->layer, 1, 0x122, 0x46);
    windows->unk8 = createTextWindow(panel->layer, 1, 0x121, 0x46);
    for (i = 0; i < 6; i++) {
        windows->left[i] = createTextWindow(panel->layer, 1, 0x6B, i * 0x11 + 0x58);
        windows->right[i] = createTextWindow(panel->layer, 1, 0xF1, i * 0x11 + 0x58);
    }
    windows->unk3C = createTextWindow(panel->layer, 1, 0x9A, 0x1A);
    windows->unk40 = createTextWindow(panel->layer, 1, 0xC3, 0x38);
    windows->unk44 = createTextWindow(panel->layer, 1, 0xC3, 0x48);
    windows->help = createTextWindow(panel->layer, 1, 0x14, 0xC3);
    windows->help->setLines(windows->help, 2);
    windows->unk4C = createTextWindow(panel->layer, 1, 0x109, 0xD1);
    windows->unk50 = createTextWindow(panel->layer, 1, 0x12C, 0xD1);
    for (i = 0, items = panel->children; i < panel->childCount - 2; i++, items++) {
        if (*items != NULL) {
            (*items)->setDepth(*items, panel->depth - 1);
        }
    }
    windows->unk40->setDepth(windows->unk40, 0);
    windows->unk44->setDepth(windows->unk44, 0);
    windows->optionCursor = createCursor(panel->layer, 0, 0xB8, 0x38);
    windows->optionCursor->setVisible(windows->optionCursor, 0);
    windows->cursor = createCursor(panel->layer, panel->depth - 1, 0x4C, 0x58);
    windows->cursor->setVisible(windows->cursor, 0);
}

void func_8008BDEC(LabPanel2 *panel, LabPanel2Windows *windows, s32 show) {
    TextWindow **items;
    u16 skill;
    s32 id;
    s32 i;

    if (show) {
        if (panel->entry.id >= 3) {
            windows->unk0->setString(windows->unk0, FILE_CACHE.load(TEXT_FILE(0x4F)),
                                     ON_PARTNER_ENTRY_ADDED(panel->entry.id)->nameId);
            panel->learned = 0;
            for (i = 0; i < panel->skillCount; i++) {
                skill = panel->entry.skills[i];
                if (panel->entry.skills[i] != 0) {
                    windows->left[i]->setString(windows->left[i], FILE_CACHE.load(TEXT_FILE(0xA3)), skill & 0x1FFF);
                    if (skill & 0x4000) {
                        windows->right[i]->setString(windows->right[i], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x11);
                        panel->learned++;
                    } else {
                        windows->right[i]->setString(windows->right[i], FILE_CACHE.load(TEXT_FILE(0x3A)), 0x12);
                    }
                    if (skill & 0x4000) {
                        windows->left[i]->setPalette(windows->left[i], 4);
                        windows->right[i]->setPalette(windows->right[i], 4);
                    } else if (skill & 0x8000) {
                        windows->left[i]->setPalette(windows->left[i], 3);
                        windows->right[i]->setPalette(windows->right[i], 3);
                    } else if (!(skill & 0x2000)) {
                        windows->left[i]->setPalette(windows->left[i], 7);
                        windows->right[i]->setPalette(windows->right[i], 7);
                    } else {
                        windows->left[i]->setPalette(windows->left[i], 0);
                        windows->right[i]->setPalette(windows->right[i], 0);
                    }
                } else {
                    windows->left[i]->setVisible(windows->left[i], 0);
                    windows->right[i]->setVisible(windows->right[i], 0);
                }
            }
            windows->unk4->setString(windows->unk4, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x10);
            windows->unk8->setNumber(windows->unk8, 0, panel->learned);
            windows->unk8->setRightAlign(windows->unk8, 1);
            id = panel->entry.skills[panel->cursor] & 0x1FFF;
            if (id != 0) {
                windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x9C)), id);
                windows->unk4C->setString(windows->unk4C, FILE_CACHE.load(TEXT_FILE(0x3A)), 0xE);
                windows->unk50->setNumber(windows->unk50, 0, D_800427E8[id - 1].mp);
                windows->unk50->setRightAlign(windows->unk50, 1);
            } else {
                windows->help->setVisible(windows->help, 0);
                windows->unk4C->setVisible(windows->unk4C, 0);
                windows->unk50->setVisible(windows->unk50, 0);
            }
        }
    } else {
        for (i = 0, items = panel->children; i < panel->childCount - 2; i++, items++) {
            if (*items != NULL) {
                (*items)->setVisible(*items, 0);
            }
        }
    }
}

INCLUDE_ASM("stgdglab/nonmatchings/stgdglab_4", func_8008C234);

LabPanel2 *func_8008D014(s32 arg0, s32 arg1) {
    LabPanel2 *panel = createTask(func_8008C234, sizeof(LabPanel2), 0x5C);

    panel->layer = 0x1000;
    panel->depth = 2;
    panel->member = arg0;
    panel->slot = arg1;
    return panel;
}
