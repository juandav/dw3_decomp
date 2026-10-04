/* The third object of STGTRAIN.PRO (see stgtrain.c), the training
   session (func_80087E34), the partner's sprites and the menu: its rodata
   starts at 0x800825E8 (USA). */

#include "stgtrain.h"

/* Creates the training session's text windows and cursor */
void func_8008778C(TrainSession *session, TrainSessionWindows *win) {
    win->text[0] = createTextWindow(session->layerId, 1, 0xA2, 0x49);
    win->text[1] = createTextWindow(session->layerId, 1, 0xBC, 0x14);
    win->text[2] = createTextWindow(session->layerId, 1, 0xC0, 0x29);
    win->intensities[0] = createTextWindow(session->layerId, 1, 0x98, 0x66);
    win->intensities[1] = createTextWindow(session->layerId, 1, 0xC0, 0x66);
    win->intensities[2] = createTextWindow(session->layerId, 1, 0xE6, 0x66);
    win->notice = createTextWindow(session->layerId, 1, 0x94, 0x87);
    win->answers[0] = createTextWindow(session->layerId, 1, 0xA2, 0x64);
    win->answers[1] = createTextWindow(session->layerId, 1, 0xA2, 0x74);
    win->cursor = createCursor(session->layerId, session->depth - 1, 0, 0);
    win->cursor->setVisible(win->cursor, 0);
}

/*
 * Draws a training session: the training's icon, its panels and the cursor
 * over the three columns.
 */
void func_800878C0(TrainSession *session) {
    SpriteDrawer sprite;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(session->layerId, session->depth);
    sprite.setTexture(0x240, 0x100);
    if (session->panels[2].level != 0) {
        if (session->panels[2].level != 0x1000) {
            sprite.setScale(session->panels[2].level, session->panels[2].level, 0x1000);
            sprite.setPivot(0xA6, 0x26);
        }
        if (GFX.funcs.getTime() - session->iconTime >= 0x10) {
            session->iconTime = GFX.funcs.getTime();
            session->iconFrame++;
            if (session->iconFrame >= 4) {
                session->iconFrame = 0;
            }
        }
        /* the match depends on i holding the icon too */
        i = D_8008C4D4.trainings[session->screen->unk78].icons[session->iconFrame];
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_FILE_SPRITES << 16), i, 0x94, 0x14);
    }
    if (session->panels[3].level != 0) {
        if (session->panels[3].level != 0x1000) {
            sprite.setScale(session->panels[3].level, session->panels[3].level, 0x1000);
            sprite.setPivot(0xCE, 0x2F);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x2A, 0xBC, 0x26);
    }
    if (session->panels[1].level != 0) {
        sprite.setScale(session->panels[1].level, 0x1000, 0x1000);
        if (session->panels[1].level != 0x1000) {
            sprite.setPivot(0x140, 0x26);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x25, 0x8F, 0xF);
    }
    if (session->panels[0].level != 0) {
        if (session->panels[0].level != 0x1000) {
            sprite.setScale(session->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x4E);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x26, 0x85, 0x43);
    }
    if (session->cursorShown != 0) {
        if (GFX.funcs.getTime() - session->cursorTime >= 0xB) {
            session->cursorTime = GFX.funcs.getTime();
            session->cursorClut++;
            if (session->cursorClut >= 4) {
                session->cursorClut = 0;
            }
        }
        sprite.setClutRow(session->cursorClut);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x29, session->unk5C * 40 + 0x94, 0x63);
        sprite.setClutRow(0);
    }
    if (session->panels[6].level != 0) {
        if (session->panels[6].level != 0x1000) {
            sprite.setScale(session->panels[6].level, session->panels[6].level, 0x1000);
        }
        for (i = 0; i < 3; i++) {
            if (session->panels[6].level != 0x1000) {
                sprite.setPivot(i * 40 + 0xA6, 0x6C);
            }
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x2A, i * 40 + 0x94, 0x63);
        }
    }
    if (session->panels[5].level != 0) {
        sprite.setScale(session->panels[5].level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x6C);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x27, 0x82, 0x5E);
    }
    if (session->panels[7].level != 0) {
        sprite.setScale(session->panels[7].level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x8D);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x27, 0x82, 0x7F);
    }
    if (session->panels[4].level != 0) {
        sprite.setScale(session->panels[4].level, 0x1000, 0x1000);
        sprite.setPivot(0x140, 0x72);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x1D, 0x82, 0x5E);
    }
}

/*
 * Runs a training session: opens its panels, picks one of three
 * intensities (it costs D_8008B9E0's points of totals.unk2), asks to confirm
 * and closes, with the intensity in the screen's unk7C. The match depends on
 * each loop and each cursor's last value having a variable of its own:
 * shared, they take other registers.
 */
void func_80087E34(TrainSession *session, TrainSessionWindows *win) {
    TrainTotals totals;
    PartnerStats *stats;
    s32 i;
    s32 j;
    s32 k;
    s32 last;
    s32 choice;
    s32 name;

    switch (session->substate) {
    case 0:
    default:
        D_8008C4D4.startFade(&session->panels[1], 1);
        session->substate++;
        break;
    case 1:
        if (D_8008C4D4.updateFade(&session->panels[1])) {
            name = D_8008C4D4.trainings[session->screen->unk78].name;
            win->text[1]->setString(win->text[1], FILE_CACHE.load(STGTRAIN_TEXT), name);
            D_8008C4D4.startFade(&session->panels[2], 1);
            session->substate++;
        }
        break;
    case 2:
        if (D_8008C4D4.updateFade(&session->panels[2])) {
            D_8008C4D4.startFade(&session->panels[0], 1);
            session->substate++;
        }
        break;
    case 3:
        if (D_8008C4D4.updateFade(&session->panels[0])) {
            win->text[0]->setString(win->text[0], FILE_CACHE.load(STGTRAIN_TEXT), 8);
            D_8008C4D4.startFade(&session->panels[5], 1);
            session->substate++;
        }
        break;
    case 4:
        if (D_8008C4D4.updateFade(&session->panels[5])) {
            D_8008C4D4.startFade(&session->panels[6], 1);
            session->substate++;
        }
        break;
    case 5:
        if (D_8008C4D4.updateFade(&session->panels[6])) {
            for (i = 0; i < 3; i++) {
                win->intensities[i]->setString(win->intensities[i], FILE_CACHE.load(STGTRAIN_TEXT), i + 0xE);
            }
            session->cursorShown = 1;
            session->substate++;
        }
        break;
    case 6:
        last = session->unk5C;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            if (--session->unk5C < 0) {
                session->unk5C = 0;
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            if (++session->unk5C >= 3) {
                session->unk5C = 2;
            }
        }
        if (last != session->unk5C) {
            SOUND.playSound(0x4001B);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            GAME.funcs.computeStats(GAME.funcs.getPartyMember(session->screen->partner), (PartnerTotals *)&totals);
            if (totals.unk2 < D_8008B9E0[session->unk5C]) {
                session->substate = 0xA;
            } else {
                session->substate = 0xF;
                session->screen->unk7C = session->unk5C;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            session->substate = 0x32;
            session->step = 1;
        }
        break;
    case 0xA:
        session->cursorShown = 0;
        D_8008C4D4.startFade(&session->panels[7], 1);
        session->substate++;
        break;
    case 0xB:
        if (D_8008C4D4.updateFade(&session->panels[7])) {
            win->notice->setString(win->notice, FILE_CACHE.load(STGTRAIN_TEXT), 0x12);
            session->substate++;
        }
        break;
    case 0xC:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            win->notice->setVisible(win->notice, 0);
            D_8008C4D4.startFade(&session->panels[7], 0);
            session->substate++;
        }
        break;
    case 0xD:
        if (D_8008C4D4.updateFade(&session->panels[7])) {
            session->cursorShown = 1;
            session->substate = 6;
        }
        break;
    case 0xF:
        session->cursorShown = 0;
        win->text[0]->setVisible(win->text[0], 0);
        for (j = 0; j < 3; j++) {
            win->intensities[j]->setVisible(win->intensities[j], 0);
        }
        session->panels[6].level = 0;
        D_8008C4D4.startFade(&session->panels[5], 0);
        D_8008C4D4.startFade(&session->panels[0], 0);
        session->substate++;
        break;
    case 0x10:
        D_8008C4D4.updateFade(&session->panels[5]);
        if (D_8008C4D4.updateFade(&session->panels[0])) {
            D_8008C4D4.startFade(&session->panels[0], 1);
            D_8008C4D4.startFade(&session->panels[4], 1);
            D_8008C4D4.startFade(&session->panels[3], 1);
            session->substate++;
        }
        break;
    case 0x11:
        D_8008C4D4.updateFade(&session->panels[3]);
        D_8008C4D4.updateFade(&session->panels[0]);
        if (D_8008C4D4.updateFade(&session->panels[4])) {
            win->text[2]->setString(win->text[2], FILE_CACHE.load(STGTRAIN_TEXT), session->unk5C + 0xE);
            win->text[0]->setString(win->text[0], FILE_CACHE.load(STGTRAIN_TEXT), 9);
            win->answers[0]->setString(win->answers[0], FILE_CACHE.load(STGTRAIN_TEXT), 0xA);
            win->answers[1]->setString(win->answers[1], FILE_CACHE.load(STGTRAIN_TEXT), 0xB);
            session->unk6C = 0;
            win->cursor->setPos(win->cursor, 0x94, 0x64);
            win->cursor->setVisible(win->cursor, 1);
            session->substate++;
        }
        break;
    case 0x12:
        choice = session->unk6C;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            session->unk6C = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            session->unk6C = 1;
        }
        if (choice != session->unk6C) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0x94, session->unk6C * 16 + 0x64);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (session->unk6C == 0) {
                session->substate = 0x19;
                stats = (PartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(session->screen->partner));
                stats->stats[1] -= D_8008B9E0[session->unk5C];
            } else {
                session->substate++;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            session->substate++;
        }
        break;
    case 0x13:
        D_8008C4D4.startFade(&session->panels[0], 0);
        D_8008C4D4.startFade(&session->panels[4], 0);
        D_8008C4D4.startFade(&session->panels[3], 0);
        win->text[2]->setVisible(win->text[2], 0);
        win->text[0]->setVisible(win->text[0], 0);
        win->answers[0]->setVisible(win->answers[0], 0);
        win->answers[1]->setVisible(win->answers[1], 0);
        win->cursor->setVisible(win->cursor, 0);
        session->substate++;
        break;
    case 0x14:
        D_8008C4D4.updateFade(&session->panels[3]);
        D_8008C4D4.updateFade(&session->panels[0]);
        if (D_8008C4D4.updateFade(&session->panels[4])) {
            D_8008C4D4.startFade(&session->panels[0], 1);
            session->substate = 3;
        }
        break;
    case 0x19:
        D_8008C4D4.startFade(&session->panels[0], 0);
        win->text[0]->setVisible(win->text[0], 0);
        D_8008C4D4.startFade(&session->panels[4], 0);
        win->answers[0]->setVisible(win->answers[0], 0);
        win->answers[1]->setVisible(win->answers[1], 0);
        win->cursor->setVisible(win->cursor, 0);
        session->substate++;
        break;
    case 0x1A:
        D_8008C4D4.updateFade(&session->panels[0]);
        if (D_8008C4D4.updateFade(&session->panels[4])) {
            session->substate = 0x23;
        }
        break;
    case 0x1E:
        win->text[1]->setVisible(win->text[1], 0);
        win->text[2]->setVisible(win->text[2], 0);
        session->panels[2].level = 0;
        session->panels[3].level = 0;
        D_8008C4D4.startFade(&session->panels[1], 0);
        session->substate++;
        break;
    case 0x1F:
        if (D_8008C4D4.updateFade(&session->panels[1])) {
            session->state = TASK_KILL;
        }
        break;
    case 0x23: /* a step that does nothing: its table entry leaves the switch */
        break;
    case 0x32:
        session->cursorShown = 0;
        win->text[0]->setVisible(win->text[0], 0);
        for (k = 0; k < 3; k++) {
            win->intensities[k]->setVisible(win->intensities[k], 0);
        }
        win->text[1]->setVisible(win->text[1], 0);
        D_8008C4D4.startFade(&session->panels[1], 0);
        D_8008C4D4.startFade(&session->panels[2], 0);
        D_8008C4D4.startFade(&session->panels[0], 0);
        D_8008C4D4.startFade(&session->panels[6], 0);
        D_8008C4D4.startFade(&session->panels[5], 0);
        session->substate++;
        break;
    case 0x33:
        D_8008C4D4.updateFade(&session->panels[1]);
        D_8008C4D4.updateFade(&session->panels[2]);
        D_8008C4D4.updateFade(&session->panels[0]);
        D_8008C4D4.updateFade(&session->panels[6]);
        if (D_8008C4D4.updateFade(&session->panels[5]) && session->step != 0) {
            session->state = TASK_DONE;
        }
        break;
    }
}


/* A training session */
void func_80088BDC(TrainSession *session, TrainSessionWindows *win) {
    switch (session->state) {
    case TASK_INIT:
    default:
        session->nextState(session);
        func_8008778C(session, win);
        session->panels[6].duration = 8;
        session->panels[5].duration = 10;
        session->panels[4].duration = 10;
        session->panels[0].duration = 10;
        session->panels[1].duration = 10;
        session->panels[3].duration = 6;
        session->panels[2].duration = 6;
        session->panels[7].duration = 10;
        session->unk5C = session->screen->unk7C;
        break;
    case TASK_RUN:
        func_80087E34(session, win);
    case TASK_DONE:
        func_800878C0(session);
    case TASK_KILL:
        break;
    }
}

void func_80088C9C(TrainSession *session) {
    session->substate = 0x1E;
}

/* Creates a training session */
TrainSession *func_80088CA8(TrainScreen *screen) {
    TrainSession *session = createTask(func_80088BDC, sizeof(TrainSession), sizeof(TrainSessionWindows));

    session->finish = func_80088C9C;
    session->layerId = 0x1000;
    session->depth = 6;
    session->screen = screen;
    return session;
}

INCLUDE_ASM("stgtrain/nonmatchings/stgtrain_3", func_80088CFC);

void func_80089638(TrainActor *actor) {
    TrainActorSprites *sprites = actor->children;

    if (sprites->sprite != NULL) {
        sprites->sprite->setPaused(sprites->sprite, 1);
    }
    if (sprites->effect != NULL) {
        sprites->effect->setPaused(sprites->effect, 1);
    }
}

void func_8008969C(TrainActor *actor) {
    TrainActorSprites *sprites = actor->children;

    if (sprites->sprite != NULL) {
        sprites->sprite->setPaused(sprites->sprite, 0);
    }
    if (sprites->effect != NULL) {
        sprites->effect->setPaused(sprites->effect, 0);
    }
    actor->mode = 4;
}

void func_80089714(TrainActor *actor, s32 x, s32 y) {
    actor->pos[0] = x;
    actor->pos[1] = y;
    actor->posSet = 1;
}

void func_80089728(TrainActor *actor, s32 x, s32 y) {
    actor->pos[2] = x;
    actor->pos[3] = y;
    actor->clutSet = 1;
}

void func_8008973C(TrainActor *actor, s32 chance) {
    actor->chance = chance;
}

void func_80089744(TrainActor *actor) {
    actor->scaleStep = 0x199;
    actor->scale = 0;
    actor->mode = 2;
}

void func_8008975C(TrainActor *actor) {
    actor->scale = 0x1000;
    actor->scaleStep = -0x333;
    actor->mode = 2;
}

void func_80089778(TrainActor *actor, s32 scale) {
    actor->scaleChanged = 1;
    actor->scale = scale;
}

s32 func_80089788(TrainActor *actor) {
    if (actor->mode & 1) {
        return actor->result;
    }
    return -1;
}

void func_800897A8(TrainActor *actor) {
    actor->mode = 8;
    actor->substate = 0;
}

/* Creates an animated sprite of an image set */
TrainActor *func_800897B8(s32 set, s32 file, s32 layerId, s32 depth) {
    TrainActor *actor = createTask(func_80088CFC, sizeof(TrainActor), sizeof(TrainActorSprites));

    actor->setPos = func_80089714;
    actor->setClutPos = func_80089728;
    actor->setChance = func_8008973C;
    actor->grow = func_80089744;
    actor->shrink = func_8008975C;
    actor->play = func_8008969C;
    actor->pause = func_80089638;
    actor->setScale = func_80089778;
    actor->getResult = func_80089788;
    actor->set = set;
    actor->file = file;
    actor->layerId = layerId;
    actor->depth = depth;
    actor->end = func_800897A8;
    return actor;
}

/* Creates the training menu's text windows */
void func_80089898(TrainMenu *menu, TextWindow **win) {
    win[0] = createTextWindow(menu->layerId, 1, 0xAE, 0x49);
    win[1] = createTextWindow(menu->layerId, 1, 0xA3, 0xA0);
    win[2] = createTextWindow(menu->layerId, 1, 0x74, 0xC0);
    win[3] = createTextWindow(menu->layerId, 1, 0x74, 0xCE);
}

/* Shows the name and description of the selected training (show) or hides them */
void func_80089924(TrainMenu *menu, TextWindow **win, s32 show) {
    s32 entry;

    if (show != 0) {
        entry = menu->trainings[menu->page][menu->col + menu->row * 4];
        if (entry > 0) {
            win[2]->setString(win[2], FILE_CACHE.load(STGTRAIN_TEXT), D_8008C4D4.trainings[entry].name);
            win[3]->setString(win[3], FILE_CACHE.load(STGTRAIN_TEXT), D_8008C4D4.trainings[entry].desc);
            return;
        }
    }
    win[2]->setVisible(win[2], 0);
    win[3]->setVisible(win[3], 0);
}

/* Draws the training menu: its panels, the trainings of the page and the cursor */
void func_80089A54(TrainMenu *menu) {
    SpriteDrawer sprite;
    s32 i;
    s32 entry;
    s32 x;
    s32 y;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(menu->layerId, menu->depth);
    sprite.setTexture(0x240, 0x100);
    if (menu->panels[0].level != 0) {
        if (menu->panels[0].level != 0x1000) {
            sprite.setScale(menu->panels[0].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x4E);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x22, 0x92, 0x43);
    }
    if (menu->cursorShown != 0) {
        if (GFX.funcs.getTime() - menu->cursorTime >= 0xB) {
            menu->cursorTime = GFX.funcs.getTime();
            menu->cursorClut++;
            if (menu->cursorClut >= 4) {
                menu->cursorClut = 0;
            }
        }
        sprite.setClutRow(menu->cursorClut);
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x1E, menu->col * 40 + 0x94, menu->row * 40 + 0x64);
        sprite.setClutRow(0);
    }
    if (menu->panels[2].level != 0) {
        if (GFX.funcs.getTime() - menu->iconTime >= 0x10) {
            menu->iconTime = GFX.funcs.getTime();
            menu->iconFrame++;
            if (menu->iconFrame >= 4) {
                menu->iconFrame = 0;
            }
        }
        if (menu->panels[2].level != 0x1000) {
            sprite.setScale(menu->panels[2].level, menu->panels[2].level, 0x1000);
        }
        for (i = 0; i < 8; i++) {
            entry = menu->trainings[menu->page][i];
            if (entry != 0) {
                x = (i % 4) * 40;
                y = (i / 4) * 40;
                if (menu->panels[2].level != 0x1000) {
                    sprite.setPivot(x + 0xA8, y + 0x76);
                }
                if (entry == -1) {
                    sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x5F, x + 0x94, y + 0x64);
                } else if (i == menu->col + menu->row * 4) {
                    sprite.setClutRow(0);
                    sprite.draw(FILE_CACHE.getEntry(STGTRAIN_FILE_SPRITES << 16),
                                D_8008C4D4.trainings[entry].icons[menu->iconFrame], x + 0x94, y + 0x64);
                } else {
                    sprite.setClutRow(1);
                    sprite.draw(FILE_CACHE.getEntry(STGTRAIN_FILE_SPRITES << 16), D_8008C4D4.trainings[entry].icons[0],
                                x + 0x94, y + 0x64);
                }
            }
        }
    }
    if (menu->arrowShown != 0) {
        if (GFX.funcs.getTime() - menu->arrowTime >= 0xB) {
            menu->arrowTime = GFX.funcs.getTime();
            menu->arrowClut++;
            if (menu->arrowClut >= 4) {
                menu->arrowClut = 0;
            }
        }
        sprite.setClutRow(menu->arrowClut);
        if (menu->page == 0) {
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x2C, 0xE4, 0xA0);
        } else {
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x2B, 0x94, 0xA0);
        }
    }
    sprite.setClutRow(0);
    if (menu->panels[1].level != 0) {
        sprite.setScale(menu->panels[1].level, 0x1000, 0x1000);
        if (menu->panels[1].level != 0x1000) {
            sprite.setPivot(0x140, 0x8A);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x24, 0x8F, 0x5F);
    }
    if (menu->panels[3].level != 0) {
        if (menu->panels[3].level != 0x1000) {
            sprite.setScale(menu->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xCD);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x23, 0x46, 0xBA);
    }
}

/*
 * Runs the training menu: opens its panels, moves the cursor over the
 * trainings of a page (L1 and R1 turn the pages when the gym has more than
 * five), and closes with a training picked (cross) or none (triangle).
 */
void func_8008A004(TrainMenu *menu, TextWindow **win) {
    s32 col;
    s32 row;

    switch (menu->substate) {
    case 0:
    default:
        D_8008C4D4.startFade(&menu->panels[0], 1);
        menu->substate++;
        break;
    case 1:
        if (D_8008C4D4.updateFade(&menu->panels[0])) {
            win[0]->setString(win[0], FILE_CACHE.load(STGTRAIN_TEXT), 7);
            D_8008C4D4.startFade(&menu->panels[1], 1);
            menu->substate++;
        }
        break;
    case 2:
        if (D_8008C4D4.updateFade(&menu->panels[1])) {
            D_8008C4D4.startFade(&menu->panels[2], 1);
            menu->substate++;
        }
        break;
    case 3:
        if (D_8008C4D4.updateFade(&menu->panels[2])) {
            if (D_8008C4D4.tableCount >= 6) {
                menu->arrowShown = 1;
                if (menu->page == 0) {
                    win[1]->setString(win[1], FILE_CACHE.load(STGTRAIN_TEXT), 0x45);
                    win[1]->setPos(win[1], 0xE4, 0xA0);
                } else {
                    win[1]->setString(win[1], FILE_CACHE.load(STGTRAIN_TEXT), 0x44);
                    win[1]->setPos(win[1], 0xA3, 0xA0);
                }
            }
            D_8008C4D4.startFade(&menu->panels[3], 1);
            menu->substate++;
        }
        break;
    case 4:
        if (D_8008C4D4.updateFade(&menu->panels[3])) {
            func_80089924(menu, win, 1);
            menu->cursorShown = 1;
            menu->substate = 10;
        }
        break;
    case 10:
        col = menu->page;
        if (D_8008C4D4.tableCount >= 6) {
            if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_R1)) & 1) && PAD_PRESSED(PAD_L1)) {
                menu->page = 0;
            } else if (!((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) && PAD_PRESSED(PAD_R1)) {
                menu->page = 1;
            }
        }
        if (col != menu->page) {
            SOUND.playSound(0x4001B);
            if (menu->page == 0) {
                win[1]->setString(win[1], FILE_CACHE.load(STGTRAIN_TEXT), 0x45);
                win[1]->setPos(win[1], 0xE4, 0xA0);
            } else {
                win[1]->setString(win[1], FILE_CACHE.load(STGTRAIN_TEXT), 0x44);
                win[1]->setPos(win[1], 0xA3, 0xA0);
            }
            for (col = 0; col < 8; col++) {
                if (menu->trainings[menu->page][col] > 0) {
                    menu->col = col % 4;
                    menu->row = col / 4;
                    break;
                }
            }
            func_80089924(menu, win, 1);
            menu->iconFrame = 0;
            break;
        }
        col = menu->col;
        row = menu->row;
        if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
            for (;;) {
                if (--menu->col < 0) {
                    menu->col = 0;
                    break;
                }
                if (menu->trainings[menu->page][menu->col + menu->row * 4] > 0) {
                    break;
                }
            }
        } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
            for (;;) {
                if (++menu->col >= 4) {
                    menu->col = 3;
                    break;
                }
                if (menu->trainings[menu->page][menu->col + menu->row * 4] > 0) {
                    break;
                }
            }
        }
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            for (;;) {
                if (--menu->row < 0) {
                    menu->row = 0;
                    break;
                }
                if (menu->trainings[menu->page][menu->col + menu->row * 4] > 0) {
                    break;
                }
            }
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            for (;;) {
                if (++menu->row >= 2) {
                    menu->row = 1;
                    break;
                }
                if (menu->trainings[menu->page][menu->col + menu->row * 4] > 0) {
                    break;
                }
            }
        }
        if (col != menu->col || row != menu->row) {
            if (menu->trainings[menu->page][menu->col + menu->row * 4] > 0) {
                SOUND.playSound(0x4001B);
                func_80089924(menu, win, 1);
            } else {
                menu->col = col;
                menu->row = row;
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001B);
            menu->screen->unk78 = menu->trainings[menu->page][menu->col + menu->row * 4];
            if (menu->screen->unk78 > 0) {
                menu->substate = 0x32;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            menu->substate = 0x32;
            menu->step = 1;
        }
        break;
    case 0x32:
        menu->cursorShown = 0;
        menu->arrowShown = 0;
        win[1]->setVisible(win[1], 0);
        D_8008C4D4.startFade(&menu->panels[2], 0);
        menu->substate++;
        break;
    case 0x33:
        if (D_8008C4D4.updateFade(&menu->panels[2])) {
            func_80089924(menu, win, 0);
            win[0]->setVisible(win[0], 0);
            D_8008C4D4.startFade(&menu->panels[0], 0);
            D_8008C4D4.startFade(&menu->panels[1], 0);
            D_8008C4D4.startFade(&menu->panels[3], 0);
            menu->substate++;
        }
        break;
    case 0x34:
        D_8008C4D4.updateFade(&menu->panels[0]);
        D_8008C4D4.updateFade(&menu->panels[1]);
        if (D_8008C4D4.updateFade(&menu->panels[3])) {
            if (menu->step != 0) {
                menu->setState(menu, TASK_DONE);
            } else {
                menu->state = TASK_KILL;
            }
        }
        break;
    }
}

/*
 * The training menu's task: a grid of trainings on two pages, filled from
 * the gym's table (the trainings it has), with the cursor on the last one.
 */
void func_8008AA28(TrainMenu *menu, TextWindow **win) {
    s32 *table;
    s32 i;
    s32 page;
    s32 row;
    s32 col;

    switch (menu->state) {
    case TASK_INIT:
    default:
        menu->nextState(menu);
        func_80089898(menu, win);
        menu->panels[0].duration = 10;
        menu->panels[1].duration = 10;
        menu->panels[2].duration = 10;
        menu->panels[3].duration = 10;
        table = D_8008C4D4.getTable(GAME.funcs.getModeArg());
        for (row = 0; row < 2; row++) {
            for (col = 0; col < 3; col++) {
                if (row == 1 && col == 2) {
                    break;
                }
                menu->trainings[0][col + row * 4] = -1;
            }
        }
        for (row = 0; row < 2; row++) {
            for (col = 0; col < 4; col++) {
                if (row != 1 || col != 0) {
                    menu->trainings[1][col + row * 4] = -1;
                }
            }
        }
        for (i = 0; i < 16; i++) {
            switch (table[i * 2]) {
            case 1:
            case 13:
                menu->trainings[0][0] = table[i * 2];
                break;
            case 2:
            case 14:
                menu->trainings[0][1] = table[i * 2];
                break;
            case 3:
            case 15:
                menu->trainings[0][2] = table[i * 2];
                break;
            case 4:
            case 16:
                menu->trainings[0][4] = table[i * 2];
                break;
            case 5:
            case 17:
                menu->trainings[0][5] = table[i * 2];
                break;
            case 6:
            case 18:
                menu->trainings[1][0] = table[i * 2];
                break;
            case 7:
            case 19:
                menu->trainings[1][1] = table[i * 2];
                break;
            case 8:
            case 20:
                menu->trainings[1][2] = table[i * 2];
                break;
            case 9:
            case 21:
                menu->trainings[1][3] = table[i * 2];
                break;
            case 10:
            case 22:
                menu->trainings[1][5] = table[i * 2];
                break;
            case 11:
            case 23:
                menu->trainings[1][6] = table[i * 2];
                break;
            case 12:
            case 24:
                menu->trainings[1][7] = table[i * 2];
                break;
            }
        }
        if (menu->screen->unk78 > 0) {
            for (page = 0; page < 2; page++) {
                for (row = 0; row < 2; row++) {
                    for (col = 0; col < 4; col++) {
                        if (menu->trainings[page][col + row * 4] == menu->screen->unk78) {
                            menu->page = page;
                            menu->col = col;
                            menu->row = row;
                            break;
                        }
                    }
                }
            }
        }
        break;
    case TASK_RUN:
        func_8008A004(menu, win);
        func_80089A54(menu);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_8008ACF8(TrainMenu *menu) {
    menu->state = TASK_RUN;
    menu->substate = 0;
}

void func_8008AD08(TrainMenu *menu) {
    menu->state = TASK_RUN;
    menu->substate = 0x32;
}

void func_8008AD1C(TrainMenu *menu) {
    func_80089924(menu, menu->children, 1);
}

/* Creates the training menu */
TrainMenu *func_8008AD40(TrainScreen *screen) {
    TrainMenu *menu = createTask(func_8008AA28, sizeof(TrainMenu), 0x10);

    menu->open = func_8008ACF8;
    menu->close = func_8008AD08;
    menu->unk110 = func_8008AD1C;
    menu->layerId = 0x1000;
    menu->depth = 6;
    menu->screen = screen;
    return menu;
}

void func_8008ADAC(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x240, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry(STGTRAIN_FILE_IMAGES << 16));
}

void func_8008AE04(PanelAnim *fade, s32 fadeIn) {
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

s32 func_8008AE98(PanelAnim *fade) {
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

void func_8008AF04(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 func_8008AF44(MenuLerp *lerp) {
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

/* Starts loading a file of D_8008C344, unless it is the one loaded */
s32 func_8008AFB0(s32 index) {
    if (index < 0) {
        return 0;
    }
    if (index != D_8008C4D4.fileIndex) {
        HEAP.zero(&D_8008C4D4.data, 0x2D8);
        D_8008C4D4.fileIndex = index;
        FILE_CACHE.request(D_8008C344[index].file);
        D_8008C4D4.data = NULL;
    }
    return 1;
}

/* The requested file, or NULL while it loads */
u8 *func_8008B040(void) {
    if (FILE_CACHE.isLoading(D_8008C344[D_8008C4D4.fileIndex].file) == 0) {
        D_8008C4D4.data = FILE_CACHE.load(D_8008C344[D_8008C4D4.fileIndex].file);
    }
    return D_8008C4D4.data;
}

void func_8008B0D8(void) {
    if (D_8008C4D4.fileIndex != -1) {
        FILE_CACHE.free(D_8008C344[D_8008C4D4.fileIndex].file);
    }
}

/* The set's sprite bank, and the two values after its offsets */
s32 func_8008B124(TrainSetHeader *header, s32 set) {
    D_8008C800.set = header;
    D_8008C4D4.sets[set].bank = (TrainSpriteBank *)(D_8008C4D4.data + header->bank);
    D_8008C800.w += *D_8008C800.w + 1;
    D_8008C4D4.sets[set].bankOffset = *D_8008C800.w++;
    D_8008C4D4.sets[set].unkC = *D_8008C800.w;
    return 1;
}

/* The set's animations */
s32 func_8008B19C(TrainSetHeader *header, s32 set) {
    s32 i;

    D_8008C804.set = header;
    for (i = 0; i < 6; i++) {
        if (D_8008C804.set->anims[i] != 0) {
            D_8008C4D4.sets[set].anims[i] = (TrainAnim *)(D_8008C4D4.data + D_8008C804.set->anims[i]);
        } else {
            D_8008C4D4.sets[set].anims[i] = NULL;
        }
    }
    return 1;
}

/* The images of a set: the rest of its offsets */
s32 func_8008B210(TrainSetHeader *header, s32 set) {
    s32 i;

    D_8008C808.set = header;
    D_8008C4D4.sets[set].imageCount = header->count - 7;
    for (i = 0; i < D_8008C4D4.sets[set].imageCount; i++) {
        D_8008C4D4.sets[set].images[i] = D_8008C4D4.data + D_8008C808.set->images[i];
    }
    return 1;
}

/* Reads an image set of the loaded file */
s32 func_8008B298(s32 set) {
    if (D_8008C4D4.data != NULL && set < 9) {
        D_8008C4D4.sets[set].id = set;
        D_8008C80C.w = (s32 *)(D_8008C4D4.data + set * 4);
        D_8008C80C.w = (s32 *)(D_8008C4D4.data + *D_8008C80C.w);
        if (D_8008C80C.set->count == 0) {
            return 0;
        }
        if (func_8008B124(D_8008C80C.set, set) == 0) {
            return 0;
        }
        if (func_8008B19C(D_8008C80C.set, set) != 0) {
            return func_8008B210(D_8008C80C.set, set) != 0;
        }
    }
    return 0;
}

INCLUDE_ASM("stgtrain/nonmatchings/stgtrain_3", func_8008B35C);

s32 func_8008B56C(s32 index) {
    return D_8008C344[index].file;
}

s32 func_8008B588(s32 index) {
    return D_8008C344[index].y << 16 | D_8008C344[index].x;
}

s32 func_8008B5AC(s32 index) {
    return D_8008C344[index].unkC;
}

TrainSpriteBank *func_8008B5C8(s32 set) {
    return D_8008C4D4.sets[set].bank;
}

s32 func_8008B5EC(s32 set) {
    return D_8008C4D4.sets[set].bankOffset;
}

s32 func_8008B610(s32 set) {
    return D_8008C4D4.sets[set].unkC;
}

TrainAnim *func_8008B634(s32 set, s32 i) {
    return D_8008C4D4.sets[set].anims[i];
}

/* The trainings of a gym level, counting them */
s32 *func_8008B660(s32 index) {
    s32 i;

    if (index < 1 || index > 14) {
        index = 0;
    }
    D_8008C4D4.tableCount = 0;
    for (i = 0; i < 16; i++) {
        if (D_8008B9EC[index][i][0] != 0) {
            D_8008C4D4.tableCount++;
        }
    }
    return D_8008B9EC[index][0];
}

/* A training of a gym level, by its id */
s32 *func_8008B6D0(s32 index, s32 id) {
    s32 i;

    if (index < 1 || index > 14) {
        index = 0;
    }
    for (i = 0; i < 16; i++) {
        if (D_8008B9EC[index][i][0] == id) {
            return D_8008B9EC[index][i];
        }
    }
    return NULL;
}
