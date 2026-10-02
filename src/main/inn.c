#include "game.h"

void innStartPanel(PanelAnim *panel, s32 open) {
    panel->active = 1;
    if (open) {
        SOUND.playSound(0x40019);
        panel->level = 0;
        panel->step = 0x1000 / panel->duration;
    } else {
        SOUND.playSound(0x4001A);
        panel->level = 0x1000;
        panel->step = -((0x1000 / panel->duration) * 2);
    }
}

s32 innUpdatePanel(PanelAnim *panel) {
    if (!panel->active) {
        return 1;
    }
    panel->level += panel->step;
    if (panel->step > 0) {
        if (panel->level > 0x1000) {
            panel->level = 0x1000;
            panel->active = 0;
            return 1;
        }
    } else if (panel->level < 0) {
        panel->level = 0;
        panel->active = 0;
        return 1;
    }
    return 0;
}

/* Restores HP, MP and status of the party (the inn) */
void healParty(void) {
    PartnerVitals *p;
    s32 i;
    s32 j;
    s32 index;

    for (i = 0; i < 3; i++) {
        index = GAME.funcs.getPartyMember(i);
        if (index >= 0) {
            p = GAME.funcs.getPartnerStats(index);
            p->hp = p->maxHp;
            p->mp = p->maxMp;
            for (j = 2; j >= 0; j--) {
                p->status[j] = 0;
            }
        }
    }
}

/* One inn per game mode */
typedef struct InnInfo {
    /* 0x0 */ s32 mode;
    /* 0x4 */ s16 string; /* in file 0x5D */
    /* 0x6 */ s16 price;
} InnInfo;
extern InnInfo INNS[];

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);

ScreenFade *createScreenFade(s32 layerId);

/*
 * Substates: 0-3 open the panels and ask (price x party size), 10-12 close,
 * 20-23 pay, fade out, heal, play the jingle and fade back in, 30-32 the
 * "not enough money" message.
 */
void updateInnMenu(Inn *task, InnChildren *data) {
    s32 prev;

    switch (task->substate) {
    case 0:
    default:
        innStartPanel(&task->panels[0], 1);
        task->substate++;
        break;
    case 1:
        if (innUpdatePanel(&task->panels[0])) {
            data->windows[0]->setString(data->windows[0], FILE_CACHE.load(0x5D), INNS[task->inn].string);
            data->windows[1]->setNumber(data->windows[1], 0, GAME.money);
            data->windows[1]->setRightAlign(data->windows[1], 1);
            data->windows[2]->setString(data->windows[2], FILE_CACHE.load(0x5D), 0x10);
            innStartPanel(&task->panels[1], 1);
            task->substate++;
        }
        break;
    case 2:
        if (innUpdatePanel(&task->panels[1])) {
            data->windows[3]->setString(data->windows[3], FILE_CACHE.load(0x5D), 0x11);
            data->windows[3]->setNumber(data->windows[3], 1, INNS[task->inn].price);
            data->windows[4]->setString(data->windows[4], FILE_CACHE.load(0x5D), 0x12);
            data->windows[5]->setString(data->windows[5], FILE_CACHE.load(0x5D), 0x13);
            data->cursor->setVisible(data->cursor, 1);
            task->substate++;
        }
        break;
    case 3:
        prev = task->choice;
        if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
            ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
            task->choice = 0;
        } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
                   ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
            task->choice = 1;
        }
        if (prev != task->choice) {
            SOUND.playSound(0x8004513E);
            data->cursor->setPos(data->cursor, 0xB8, task->choice * 16 + 0x5F);
            break;
        }
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
            SOUND.playSound(0x8004503C);
            if (task->choice != 0) {
                task->substate = 10;
            } else if (GAME.money >= INNS[task->inn].price * task->count) {
                task->substate = 20;
            } else {
                task->substate = 10;
                task->step = 1;
            }
        } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
            SOUND.playSound(0x800450BD);
            task->substate = 10;
        }
        break;
    case 10:
        innStartPanel(&task->panels[1], 0);
        data->windows[3]->setVisible(data->windows[3], 0);
        data->windows[4]->setVisible(data->windows[4], 0);
        data->windows[5]->setVisible(data->windows[5], 0);
        data->cursor->setVisible(data->cursor, 0);
        task->substate++;
        break;
    case 11:
        if (innUpdatePanel(&task->panels[1])) {
            if (task->step != 0) {
                innStartPanel(&task->panels[2], 1);
                task->substate = 30;
            } else {
                innStartPanel(&task->panels[0], 0);
                data->windows[0]->setVisible(data->windows[0], 0);
                data->windows[1]->setVisible(data->windows[1], 0);
                data->windows[2]->setVisible(data->windows[2], 0);
                task->substate++;
            }
        }
        break;
    case 12:
        if (innUpdatePanel(&task->panels[0])) {
            task->state = 3;
        }
        break;
    case 20:
        task->music = SOUND_STATE.music;
        task->time = GFX_FUNCS.getTime();
        SOUND_STATE.playSound(0x4004000D);
        data->fade = createScreenFade(task->layerId);
        data->fade->start(data->fade, 0, 0x14);
        task->substate++;
        break;
    case 21:
        if (data->fade->state == 2) {
            task->panels[0].level = 0;
            task->panels[1].level = 0;
            data->windows[0]->setVisible(data->windows[0], 0);
            data->windows[1]->setVisible(data->windows[1], 0);
            data->windows[2]->setVisible(data->windows[2], 0);
            data->windows[3]->setVisible(data->windows[3], 0);
            data->windows[4]->setVisible(data->windows[4], 0);
            data->windows[5]->setVisible(data->windows[5], 0);
            data->cursor->setVisible(data->cursor, 0);
            GAME.money -= INNS[task->inn].price * task->count;
            healParty();
            task->substate++;
        }
        break;
    case 22:
        if (GFX_FUNCS.getTime() - task->time > 0xF0) {
            data->fade->start(data->fade, 1, 0x14);
            task->substate++;
        }
        break;
    case 23:
        if (data->fade->state == 2) {
            SOUND.playSound(task->music);
            task->state = 3;
        }
        break;
    case 30:
        if (innUpdatePanel(&task->panels[2])) {
            data->windows[3]->setString(data->windows[3], FILE_CACHE.load(0x5D), 0x14);
            task->step = 0;
            task->substate++;
        }
        break;
    case 31:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
            SOUND.playSound(0x4001C);
            data->windows[3]->setVisible(data->windows[3], 0);
            innStartPanel(&task->panels[2], 0);
            task->substate++;
        }
        break;
    case 32:
        if (innUpdatePanel(&task->panels[2])) {
            innStartPanel(&task->panels[1], 1);
            task->substate = 2;
        }
        break;
    }
}

void updateInn(Inn *task, InnChildren *data) {
    SpriteDrawer obj;
    s32 i;
    s32 n;
    s32 id;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        id = GAME_FUNCS.getMode();
        for (n = 0; INNS[n].mode != 0; n++) {
            if (id == INNS[n].mode) {
                break;
            }
        }
        task->inn = n;
        for (i = 0; i < 3; i++) {
            if (GAME.funcs.getPartyMember(i) >= 0) {
                task->count++;
            }
        }
        data->windows[0] = createTextWindow(task->layerId, 1, 0x1D, 0x14);
        data->windows[1] = createTextWindow(task->layerId, 3, 0x117, 0x17);
        data->windows[2] = createTextWindow(task->layerId, 3, 0x11A, 0x17);
        data->windows[3] = createTextWindow(task->layerId, 1, 0x79, 0x34);
        data->windows[4] = createTextWindow(task->layerId, 1, 0xC5, 0x5F);
        data->windows[5] = createTextWindow(task->layerId, 1, 0xC5, 0x6F);
        data->cursor = createCursor(task->layerId, 0, 0xB8, 0x5F);
        data->cursor->setVisible(data->cursor, 0);
        task->panels[0].duration = 10;
        task->panels[1].duration = 10;
        task->panels[2].duration = 10;
        break;
    case 1:
        updateInnMenu(task, data);
        initSpriteDrawer(&obj);
        obj.setTexture(0x140, 0);
        obj.setLayerId(task->layerId, task->depth);
        obj.setFollowScroll(0);
        if (task->panels[0].level != 0) {
            if (task->panels[0].level != 0x1000) {
                obj.setScale(task->panels[0].level, 0x1000, 0x1000);
                obj.setPivot(0x57, 0x19);
            }
            obj.draw(FILE_CACHE.getEntry(0x02770000), 0x41, 0x16, 0x12);
            if (task->panels[0].level != 0x1000) {
                obj.setPivot(0x140, 0x18);
            }
            obj.draw(FILE_CACHE.getEntry(0x02770000), 0x42, 0xD6, 0xF);
        }
        if (task->panels[1].level != 0) {
            if (task->panels[1].level != 0x1000) {
                obj.setScale(task->panels[1].level, 0x1000, 0x1000);
                obj.setPivot(0x140, 0x41);
            }
            obj.draw(FILE_CACHE.getEntry(0x02770000), 0x43, 0x4C, 0x2E);
            if (task->panels[1].level != 0x1000) {
                obj.setPivot(0x140, 0x6D);
            }
            obj.draw(FILE_CACHE.getEntry(0x02770000), 0x44, 0xAF, 0x59);
        }
        if (task->panels[2].level != 0) {
            if (task->panels[2].level != 0x1000) {
                obj.setScale(task->panels[2].level, 0x1000, 0x1000);
                obj.setPivot(0x140, 0x41);
            }
            obj.draw(FILE_CACHE.getEntry(0x02770000), 0x43, 0x4C, 0x2E);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

void createInn(s32 layerId) {
    Inn *task = createTask(updateInn, 0xA0, 0x20);

    task->layerId = layerId;
    task->depth = 1;
}

void screenFadeStart(ScreenFade *task, s32 fadeIn, s32 duration) {
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

/* A full-screen POLY_F4 with subtractive blending (tpage 0xE1000245) */
void drawScreenFade(ScreenFade *task) {
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

void updateScreenFade(ScreenFade *task) {
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
        drawScreenFade(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *createScreenFade(s32 layerId) {
    ScreenFade *task = createTask(updateScreenFade, 0x68, 0);

    task->start = screenFadeStart;
    task->layerId = layerId;
    task->depth = 0;
    return task;
}
