#include "common.h"
#include "stgdglab.h"

#define PAD_HELD(button) ((PAD.getHeld(0) >> PAD.getButtonBit(0, button)) & 1)

s32 func_80082ACC(LabScreen3 *screen, s32 row, u32 col, s32 slot);
void func_80082DF4(LabScreen3 *screen, LabScreen3Windows *win);

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

/* Puts in found[row][slot] the owned ids of the recipe (row, col) and clears
   complete[row] when they're fewer than the recipe needs; gives the ids
   checked, 0 for a column past the recipes */
s32 func_80082ACC(LabScreen3 *screen, s32 row, u32 col, s32 slot) {
    s32 i;
    s32 j;
    s32 table;
    s32 *found;
    s16 *ids;
    s16 id;

    if (col >= 5) {
        return 0;
    }
    table = screen->table;
    ids = &STGDGLAB_data.recipes[table][row * 4 + col][1];
    found = screen->found[row][slot];
    screen->foundCount[row] = 0;
    for (i = 0; i < 5; i++) {
        found[i] = 0;
        id = ids[i];
        if (id > 0) {
            for (j = 0; j < screen->ownedCount; j++) {
                if (screen->owned[j] == id) {
                    found[i] = screen->owned[j];
                    screen->foundCount[row]++;
                    break;
                }
            }
        }
    }
    if (screen->foundCount[row] < STGDGLAB_data.recipes[table][row * 4 + col][0]) {
        screen->complete[row] = 0;
    }
    return 5;
}

s32 func_80082C1C(LabScreen3 *screen, s32 row, u32 col) {
    s16 id;
    s32 i;
    s32 j;
    s16 *ids;

    if (col >= 5) {
        return 0;
    }
    id = 0;
    ids = &STGDGLAB_data.recipes[screen->table][row * 4 + col][1];
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

/* Draws the third screen: the picked id, the frames, the recipes of the row
   (the ids found, the empty slots after them) and the arrows */
void func_80082DF4(LabScreen3 *screen, LabScreen3Windows *win) {
    SpriteDrawer sprite;
    s32 complete;
    s32 frame;
    s32 id;
    s32 shown;
    /* The match depends on the slots' loop and the second pair of loops
       having their own counters, and on the first inner loop setting shown
       after j */
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;

    complete = 0;
    if (screen->complete[0] != 0 && screen->complete[1] != 0 && screen->complete[2] != 0) {
        complete = screen->complete[3] != 0;
    }
    initSpriteDrawer(&sprite);
    sprite.setLayerId(screen->layer, screen->depth - 1);
    if (screen->panels[1].level != 0) {
        id = screen->found[screen->row][screen->slot][screen->col];
        sprite.setTexture(0x140, 0x100);
        sprite.setAltClut(0x280, 0);
        sprite.setScale(screen->panels[1].level, 0x1000, 0x1000);
        if (screen->slot < 2) {
            sprite.setPivot(0, 0xC2);
            if (id != 0) {
                frame = STGDGLAB_data.funcs.getA(id);
                sprite.draw(FILE_CACHE.getEntry((FILE_LAB_SPRITES << 16) | 1), frame, 0x14, 0xAF);
            }
            sprite.setTexture(0x280, 0x100);
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x42, 0, 0xA8);
        } else {
            sprite.setPivot(0, 0x4C);
            if (id != 0) {
                frame = STGDGLAB_data.funcs.getA(id);
                sprite.draw(FILE_CACHE.getEntry((FILE_LAB_SPRITES << 16) | 1), frame, 0x14, 0x39);
            }
            sprite.setTexture(0x280, 0x100);
            sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x42, 0, 0x32);
        }
    }
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0x100);
    sprite.setLayerId(screen->layer, screen->depth);
    if (GFX.funcs.getTime() - screen->time >= 8) {
        screen->time = GFX.funcs.getTime();
        if (++screen->clutRow >= 4) {
            screen->clutRow = 0;
        }
    }
    sprite.setClutRow(screen->clutRow);
    if (screen->panels[4].level == 0x1000) {
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x47, screen->col * 0x28 + 0x4A, screen->slot * 0x2E + 0x32);
    }
    if (screen->arrowLeft != 0) {
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x45, 0x17, 0xC9);
    }
    if (screen->arrowRight != 0) {
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x46, 0x110, 0xC9);
    }
    sprite.setClutRow(0);
    if (screen->panels[0].level != 0x1000) {
        sprite.setScale(screen->panels[0].level, 0x1000, 0x1000);
        sprite.setPivot(0, 0x1F);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x44, 0, 0x11);
    if (screen->panels[0].level != 0x1000) {
        sprite.setPivot(0x140, 0x1F);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x43, 0xF0, 0x11);
    if (screen->panels[4].level != 0x1000) {
        sprite.setScale(screen->panels[4].level, 0x1000, 0x1000);
        sprite.setPivot(0x44, 0x42);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    if (screen->found[screen->row][0][0] != -1) {
        if (complete) {
            sprite.setClutRow(2);
        } else if (screen->complete[screen->row] != 0) {
            sprite.setClutRow(1);
        }
        for (i = 0; i < 4; i++) {
            for (j = 4, shown = 0; j >= 0; j--) {
                id = screen->found[screen->row][i][j];
                if (id != 0) {
                    if (STGDGLAB_data.funcs.getA(id) != -1) {
                        shown = 1;
                        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x3F, j * 0x28 + 0x4A, i * 0x2E + 0x32);
                    }
                } else if (shown) {
                    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x40, j * 0x28 + 0x4A, i * 0x2E + 0x32);
                }
            }
        }
    } else {
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x3F, 0x4A, 0x32);
    }
    if (complete) {
        sprite.setClutRow(2);
    } else {
        sprite.setClutRow(0);
    }
    if (screen->panels[3].level != 0x1000) {
        sprite.setScale(0x1000, screen->panels[3].level, 0x1000);
        sprite.setPivot(0x40, 0x3F);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    for (k = screen->slots - 2; k >= 0; k--) {
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x3C, 0x3D, k * 0x2E + 0x3F);
    }
    if (screen->panels[2].level != 0x1000) {
        sprite.setScale(0x1000, screen->panels[2].level, 0x1000);
        sprite.setPivot(0x3D, 0x42);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x3D, 0x14, 0x32);
    sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x40, 0x24, 0x32);
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x140, 0x100);
    sprite.setAltClut(0x280, 0);
    sprite.setLayerId(screen->layer, screen->depth - 1);
    if (screen->panels[2].level != 0x1000) {
        sprite.setScale(0x1000, screen->panels[2].level, 0x1000);
        sprite.setPivot(0x3D, 0x42);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    id = D_8008EC94[screen->table];
    sprite.draw(FILE_CACHE.getEntry((FILE_LAB_SPRITES << 16) | 1), STGDGLAB_data.funcs.getA(id), 0x14, 0x32);
    if (screen->panels[4].level != 0x1000) {
        sprite.setScale(screen->panels[4].level, 0x1000, 0x1000);
        sprite.setPivot(0x44, 0x42);
    } else {
        sprite.setScale(0x1000, 0x1000, 0x1000);
    }
    if (screen->found[screen->row][0][0] != -1) {
        for (m = 0; m < 4; m++) {
            for (n = 4; n >= 0; n--) {
                id = screen->found[screen->row][m][n];
                if (id != 0) {
                    frame = STGDGLAB_data.funcs.getA(id);
                    if (frame != -1) {
                        sprite.draw(FILE_CACHE.getEntry((FILE_LAB_SPRITES << 16) | 1), frame, n * 0x28 + 0x4A, m * 0x2E + 0x32);
                    }
                }
            }
        }
    } else {
        sprite.setTexture(0x280, 0x100);
        sprite.draw(FILE_CACHE.getEntry(FILE_LAB_SPRITES << 16), 0x49, 0x4A, 0x32);
    }
}

#if VERSION_EU
/* Moves the third screen's cursor by step slots, to the first column with
   an id; whether it moved */
s32 func_800841E4(LabScreen3 *screen, s32 step) {
    s32 old = screen->slot;
    s32 col;

    do {
        screen->slot += step;
        if (screen->slot < 0) {
            screen->slot = 0;
        } else if (screen->slots - 1 < screen->slot) {
            screen->slot = screen->slots - 1;
        }
        col = 0;
        while (screen->found[screen->row][screen->slot][col] == 0) {
            if (++col >= 5) {
                break;
            }
        }
    } while (screen->found[screen->row][screen->slot][col] == 0);
    if (old != screen->slot) {
        screen->col = col;
        return 1;
    }
    return 0;
}
#endif

#define FOUND(screen) ((screen)->found[(screen)->row][(screen)->slot][(screen)->col])

/* The third screen: a row of recipes at a time, the picked id's name and
   description on cross */
void func_8008397C(LabScreen3 *screen, LabScreen3Windows *win) {
    s32 i;
    s32 j;
    s32 n;
    s32 count;
    s32 found;
    s32 oldCol;
    s32 oldSlot;
    PartnerVitals *stats;
    s32 id;
    s32 nameId;

    switch (screen->state) {
    case TASK_INIT:
    default:
        if (screen->lab->menuOpen(screen->lab)) {
            screen->nextState(screen);
            screen->table = GAME.funcs.getPartyMember(screen->lab->unk64);
            screen->ownedCount = GAME.funcs.listPartnerEntries(screen->table, screen->owned);
            win->title = createTextWindow(screen->layer, 1, 0x14, 0x19);
            win->rowNumber = createTextWindow(screen->layer, 1, 0xFF, 0x19);
            win->rowLabel = createTextWindow(screen->layer, 1, 0x101, 0x19);
            win->prev = createTextWindow(screen->layer, 1, 0x27, 0xC4);
            win->prev->setDepth(win->prev, 2);
            win->next = createTextWindow(screen->layer, 1, 0x115, 0xC4);
            win->next->setDepth(win->next, 2);
            win->name = createTextWindow(screen->layer, 1, 0x14, 0x19);
            win->name->setDepth(win->name, 0);
            win->desc = createTextWindow(screen->layer, 1, 0x14, 0x19);
            win->desc->setDepth(win->desc, 0);
            for (i = 0; i < 4; i++) {
                screen->complete[i] = 1;
                for (j = 0, n = 0, count = 0; j < 4; j++) {                    found = func_80082C1C(screen, i, j);
                    count += found;
                    if (found) {
                        func_80082ACC(screen, i, j, n);
                        n++;
                    } else if (STGDGLAB_data.recipes[screen->table][i * 4 + j][0] != 0) {
                        screen->complete[i] = 0;
                    }
                }
                if (count == 0) {
                    screen->found[i][0][0] = -1;
                }
            }
            screen->unkC4[0] = 4;
            screen->slots = func_80082CE8(screen, screen->row);
            func_80082D64(screen);
            screen->panels[0].duration = 8;
            screen->panels[1].duration = 8;
            screen->panels[2].duration = 8;
            screen->panels[4].duration = 8;
            screen->panels[3].duration = 8;
            screen->arrowLeft = 0;
            screen->arrowRight = 1;
            STGDGLAB_data.funcs.startFade(&screen->panels[0], 1);
            STGDGLAB_data.funcs.startFade(&screen->panels[2], 1);
            STGDGLAB_data.funcs.startFade(&screen->panels[4], 1);
            STGDGLAB_data.funcs.startFade(&screen->panels[3], 1);
        }
        break;
    case TASK_RUN:
        switch (screen->substate) {
        case 0:
        default:
            STGDGLAB_data.funcs.updateFade(&screen->panels[0]);
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[2]) != 0) {
                stats = GAME_FUNCS.getPartnerStats(screen->table);
                win->title->setString(win->title, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x27);
                win->title->setSubString(win->title, stats, -1, 1);
                win->rowNumber->setNumber(win->rowNumber, 0, screen->row + 1);
                win->rowNumber->setRightAlign(win->rowNumber, 1);
                win->rowLabel->setString(win->rowLabel, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x28);
                win->prev->setString(win->prev, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x29);
                win->prev->setVisible(win->prev, 0);
                win->next->setString(win->next, FILE_CACHE.load(TEXT_FILE(0x3A)), 0x2A);
                STGDGLAB_data.funcs.startFade(&screen->panels[3], 1);
                screen->substate++;
            }
            break;
        case 1:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[3]) != 0) {
                STGDGLAB_data.funcs.startFade(&screen->panels[4], 1);
                screen->substate++;
            }
            break;
        case 2:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[4]) != 0) {
                screen->substate++;
            }
            break;
        case 3:
            screen->unkC4[1] = screen->row;
            if ((!PAD_HELD(PAD_R1) && PAD_PRESSED(PAD_L1)) || (!PAD_HELD(PAD_R1) && PAD_REPEATED(PAD_L1))) {
                if (--screen->unkC4[1] < 0) {
                    screen->unkC4[1] = 0;
                }
            } else if ((!PAD_HELD(PAD_L1) && PAD_PRESSED(PAD_R1)) || (!PAD_HELD(PAD_L1) && PAD_REPEATED(PAD_R1))) {
                if (++screen->unkC4[1] > screen->unkC4[0] - 1) {
                    screen->unkC4[1] = screen->unkC4[0] - 1;
                }
            }
            if (screen->unkC4[1] != screen->row) {
                SOUND.playSound(0x4001B);
                win->rowNumber->setNumber(win->rowNumber, 0, screen->unkC4[1] + 1);
                win->rowNumber->setRightAlign(win->rowNumber, 1);
                if (screen->unkC4[1] == 0) {
                    win->prev->setVisible(win->prev, 0);
                    screen->arrowLeft = 0;
                } else if (screen->unkC4[1] == screen->unkC4[0] - 1) {
                    win->next->setVisible(win->next, 0);
                    screen->arrowRight = 0;
                } else {
                    win->prev->setVisible(win->prev, 1);
                    win->next->setVisible(win->next, 1);
                    screen->arrowLeft = 1;
                    screen->arrowRight = 1;
                }
                screen->state = TASK_DONE;
                screen->step = 0;
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                screen->state = TASK_DONE;
                screen->substate = 7;
                screen->step = 0;
                screen->counter = 1;
                screen->arrowLeft = 0;
                screen->arrowRight = 0;
                win->prev->setVisible(win->prev, 0);
                win->next->setVisible(win->next, 0);
            } else if (screen->found[screen->row][0][0] != -1) {
                oldCol = screen->col;
                oldSlot = screen->slot;
#if VERSION_US
                if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                    do {
                        if (--screen->slot < 0) {
                            screen->slot = 0;
                            break;
                        }
                    } while (FOUND(screen) == 0);
                    if (FOUND(screen) == 0) {
                        screen->slot = oldSlot;
                        if (screen->slots != 0) {
                            if (screen->col == 0) {
                                screen->col = 1;
                            } else {
                                screen->col--;
                            }
                            do {
                                if (--screen->slot < 0) {
                                    screen->slot = 0;
                                    break;
                                }
                            } while (FOUND(screen) == 0);
                            if (FOUND(screen) == 0) {
                                screen->slot = oldSlot;
                                screen->col = oldCol;
                            }
                        }
                    }
                } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                    do {
                        if (++screen->slot > screen->slots - 1) {
                            screen->slot = screen->slots - 1;
                            break;
                        }
                    } while (FOUND(screen) == 0);
                    if (FOUND(screen) == 0) {
                        screen->slot = oldSlot;
                        if (screen->slots != 0) {
                            if (screen->col == 0) {
                                screen->col = 1;
                            } else {
                                screen->col--;
                            }
                            do {
                                if (++screen->slot > screen->slots - 1) {
                                    screen->slot = screen->slots - 1;
                                    break;
                                }
                            } while (FOUND(screen) == 0);
                            if (FOUND(screen) == 0) {
                                screen->slot = oldSlot;
                                screen->col = oldCol;
                            }
                        }
                    }
                }
#elif VERSION_EU
                if (screen->slots >= 2) {
                    if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                        func_800841E4(screen, -1);
                    } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                        func_800841E4(screen, 1);
                    }
                }
                if (oldSlot == screen->slot)
#endif
                {
                    if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
                        do {
                            if (--screen->col < 0) {
                                screen->col = 0;
                                break;
                            }
                        } while (FOUND(screen) == 0);
                        if (FOUND(screen) == 0) {
                            screen->col = oldCol;
                        }
                    } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
                        do {
                            if (++screen->col >= 5) {
                                screen->col = 4;
                                break;
                            }
                        } while (FOUND(screen) == 0);
                        if (FOUND(screen) == 0) {
                            screen->col = oldCol;
                        }
                    }
                }
                if (oldCol != screen->col || oldSlot != screen->slot) {
                    SOUND.playSound(0x4001B);
                }
#if VERSION_EU
                else
#endif
                if (PAD_PRESSED(PAD_CROSS)) {
                    SOUND.playSound(0x4001C);
                    STGDGLAB_data.funcs.startFade(&screen->panels[1], 1);
                    screen->substate++;
                }
            }
            break;
        case 4:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[1]) != 0) {
                id = FOUND(screen);
                nameId = ON_PARTNER_ENTRY_ADDED(id)->nameId;
                if (id != 0) {
                    if (screen->slot < 2) {
                        win->name->setPos(win->name, 0x3A, 0xAD);
                        win->desc->setPos(win->desc, 0x3A, 0xBC);
                    } else {
                        win->name->setPos(win->name, 0x3A, 0x37);
                        win->desc->setPos(win->desc, 0x3A, 0x46);
                    }
                    win->name->setString(win->name, FILE_CACHE.load(TEXT_FILE(0x4F)), nameId);
                    win->desc->setString(win->desc, FILE_CACHE.load(TEXT_FILE(0x48)), nameId);
                }
                screen->substate++;
            }
            break;
        case 5:
            if (PAD_PRESSED(PAD_CROSS)) {
                STGDGLAB_data.funcs.startFade(&screen->panels[1], 0);
                win->name->setVisible(win->name, 0);
                win->desc->setVisible(win->desc, 0);
                screen->substate++;
            }
            break;
        case 6:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[1]) != 0) {
                screen->substate = 3;
            }
            break;
        case 7:
            STGDGLAB_data.funcs.startFade(&screen->panels[0], 0);
            STGDGLAB_data.funcs.startFade(&screen->panels[2], 0);
            win->title->setVisible(win->title, 0);
            win->rowNumber->setVisible(win->rowNumber, 0);
            win->rowLabel->setVisible(win->rowLabel, 0);
            screen->substate++;
            break;
        case 8:
            STGDGLAB_data.funcs.updateFade(&screen->panels[0]);
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[2]) != 0) {
                screen->setState(screen, TASK_KILL);
            }
            break;
        }
        func_80082DF4(screen, win);
        break;
    case TASK_DONE:
        switch (screen->step) {
        case 0:
        default:
            STGDGLAB_data.funcs.startFade(&screen->panels[4], 0);
            screen->step++;
            break;
        case 1:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[4]) != 0) {
                STGDGLAB_data.funcs.startFade(&screen->panels[3], 0);
                screen->row = screen->unkC4[1];
                screen->step++;
            }
            break;
        case 2:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[3]) != 0) {
                if (screen->counter == 0) {
                    func_80082D64(screen);
                    STGDGLAB_data.funcs.startFade(&screen->panels[3], 1);
                    STGDGLAB_data.funcs.startFade(&screen->panels[4], 1);
                    screen->slots = func_80082CE8(screen, screen->row);
                    screen->step++;
                } else {
                    screen->state = TASK_RUN;
                }
            }
            break;
        case 3:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[3]) != 0) {
                screen->step++;
            }
            break;
        case 4:
            if (STGDGLAB_data.funcs.updateFade(&screen->panels[4]) != 0) {
                screen->state = TASK_RUN;
            }
            break;
        }
        func_80082DF4(screen, win);
        break;
    case TASK_KILL:
        break;
    }
}

Task *func_80084CF4(Lab *lab) {
    LabScreen3 *screen = createTask(func_8008397C, sizeof(LabScreen3), 0x1C);

    screen->layer = 0x1000;
    screen->depth = 2;
    screen->lab = lab;
    lab->closeMenu(lab);
    return (Task *)screen;
}

extern LabAnim D_8008ECE8[];
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
/* the partners' animation frames, -1 ends */
LabAnim D_8008ECE8[] = {
    { { 7, 8, 9, 10, 9, 8, -1 } },
    { { 14, 15, 16, 15, -1, -1, -1 } },
    { { 11, 12, 13, 12, -1, -1, -1 } },
    { { 3, 4, 5, 6, 5, 4, -1 } },
    { { 25, 26, 27, 28, 27, 26, -1 } },
    { { 0, 1, 2, 1, -1, -1, -1 } },
    { { 17, 18, 19, 20, 19, 18, -1 } },
    { { 21, 22, 23, 24, 23, 22, -1 } },
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
LabData STGDGLAB_data = {
    D_8008ECE8,
    D_8008EDC8,
    {
        D_8008EF8C, D_8008F04C, D_8008F10C, D_8008F1CC,
        D_8008F28C, D_8008F34C, D_8008F40C, D_8008F4CC,
    },
    {
        STGDGLAB_loadFiles, STGDGLAB_filesLoading, STGDGLAB_startFade, STGDGLAB_updateFade,
        STGDGLAB_startLerp, STGDGLAB_updateLerp, func_8008EBFC, func_8008EC48,
    },
};
