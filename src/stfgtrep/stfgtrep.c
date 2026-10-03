#include "stfgtrep.h"

void STFGTREP_drawPartner(ReportPartner *partner);
s32 func_80085A38(s32 partner);
void STFGTREP_runPartner(ReportPartner *partner, ReportPartnerWindows *windows);
void STFGTREP_runReport(FightReport *report, FightReportChildren *children);
void STFGTREP_updatePartner();
void STFGTREP_updateReport();
FightReport *STFGTREP_createScreen(void);
extern s32 STFGTREP_animations[][7];

void STFGTREP_updateScene(Task *task, Task **children) {
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
        children[0] = (Task *)STFGTREP_createScreen();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STFGTREP_start(void) {
    return createTask(STFGTREP_updateScene, sizeof(Task), 4);
}

void STFGTREP_startFader(ScreenFade *task, s32 fadeIn, s32 duration) {
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

void STFGTREP_drawFader(ScreenFade *task) {
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

void STFGTREP_updateFader(ScreenFade *task) {
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
        STFGTREP_drawFader(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *STFGTREP_createFader(void) {
    ScreenFade *task = createTask(STFGTREP_updateFader, sizeof(ScreenFade), 0);

    task->start = STFGTREP_startFader;
    task->layerId = 0x1000;
    task->depth = 6;
    return task;
}

/* Creates the text windows of a partner's panel */
void STFGTREP_createPartnerWindows(ReportPartner *partner, ReportPartnerWindows *windows) {
    TextWindow *window;
    s32 y = partner->index * 50;
    s32 i;

    windows->name = createTextWindow(partner->layer, 1, 0x3D, y + 0x28);
    windows->levelLabel = createTextWindow(partner->layer, 3, 0x3E, y + 0x38);
    windows->level = createTextWindow(partner->layer, 3, 0x5B, y + 0x38);
    windows->expLabel = createTextWindow(partner->layer, 3, 0x6A, y + 0x45);
    windows->exp = createTextWindow(partner->layer, 3, 0x67, y + 0x45);
    for (i = 0; i < 3; i++) {
        y = partner->index * 50 + i * 15;
        windows->slots[i].name = createTextWindow(partner->layer, 1, 0x8D, y + 0x28);
        windows->slots[i].level = createTextWindow(partner->layer, 3, 0x114, y + 0x2C);
    }
    window = createTextWindow(partner->layer, 1, 0x14, 0xC2);
    windows->message = window;
    window->setLines(window, 2);
}

/* Fills a partner's panel with its name, level, exp and Digimon, or hides it */
void STFGTREP_fillPartnerWindows(ReportPartner *partner, ReportPartnerWindows *windows, s32 show) {
    PartnerVitals *stats;
    s32 member;
    s32 i;

    if (show != 0) {
        member = GAME.funcs.getPartyMember(partner->index);
        stats = GAME.funcs.getPartnerStats(member);
        windows->name->setString(windows->name, stats, -1);
        windows->level->setNumber(windows->level, 0, stats->level);
        windows->level->setRightAlign(windows->level, 1);
        windows->levelLabel->setString(windows->levelLabel, FILE_CACHE.load(TEXT_FILE(0x56)), 3);
        windows->exp->setNumber(windows->exp, 0, partner->shownExp);
        windows->exp->setRightAlign(windows->exp, 1);
        windows->exp->setSpacing(windows->exp, 7, 0);
        windows->expLabel->setString(windows->expLabel, FILE_CACHE.load(TEXT_FILE(0x56)), 1);
        GAME.funcs.getPartnerSlots(member, partner->slots);
        for (i = 0; i < 3; i++) {
            if (partner->slots[i] >= 4) {
                GAME.funcs.getPartnerEntry(member, partner->slots[i], &partner->entry);
                windows->slots[i].name->setString(windows->slots[i].name, FILE_CACHE.load(TEXT_FILE(0x4F)), ON_PARTNER_ENTRY_ADDED(partner->slots[i])->nameId);
                windows->slots[i].level->setNumber(windows->slots[i].level, 0, partner->entry.level);
                windows->slots[i].level->setRightAlign(windows->slots[i].level, 1);
            } else {
                windows->slots[i].name->setVisible(windows->slots[i].name, 0);
                windows->slots[i].level->setVisible(windows->slots[i].level, 0);
            }
        }
    } else {
        windows->name->setVisible(windows->name, 0);
        windows->level->setVisible(windows->level, 0);
        windows->levelLabel->setVisible(windows->levelLabel, 0);
        windows->exp->setVisible(windows->exp, 0);
        windows->expLabel->setVisible(windows->expLabel, 0);
        for (i = 0; i < 3; i++) {
            windows->slots[i].name->setVisible(windows->slots[i].name, 0);
            windows->slots[i].level->setVisible(windows->slots[i].level, 0);
        }
    }
}

/* Draws a partner's panel: the level and slot blinks, the cursor, the
   partner's animation and its frames */
void STFGTREP_drawPartner(ReportPartner *partner) {
    SpriteDrawer sprite;
    s32 digimon;
    s32 y;
    s32 i;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(partner->layer, partner->depth);
    sprite.setTexture(0x280, 0);
    if (partner->substate >= 20) {
        if (partner->levelBlink.on != 0) {
            if (GFX.funcs.getTime() - partner->levelBlink.time >= 3) {
                partner->levelBlink.time = GFX.funcs.getTime();
                if (++partner->levelBlink.frame >= 11) {
                    partner->levelBlink.frame = 10;
                }
            }
            sprite.setClutRow(partner->levelBlink.frame);
            y = partner->index * 50;
            sprite.draw(FILE_CACHE_GET_ENTRY[0]((FILE_FGTREP_SPRITES - 1) << 16), 0x22, 0x63, y + 0x2B);
            sprite.setClutRow(0);
        }
        for (i = 0; i < 3; i++) {
            if (partner->slotBlinks[i].blink.on != 0) {
                if (GFX.funcs.getTime() - partner->slotBlinks[i].blink.time >= 3) {
                    partner->slotBlinks[i].blink.time = GFX.funcs.getTime();
                    if (++partner->slotBlinks[i].blink.frame >= 11) {
                        partner->slotBlinks[i].blink.frame = 10;
                    }
                }
                sprite.setClutRow(partner->slotBlinks[i].blink.frame);
                y = partner->index * 50 + i * 15;
                sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x23, 0xEF, y + 0x23);
            }
        }
        sprite.setClutRow(0);
    }
    if (partner->selected != 0) {
        if (GFX.funcs.getTime() - partner->cursorTime >= 5) {
            partner->cursorTime = GFX.funcs.getTime();
            if (++partner->cursorFrame >= 4) {
                partner->cursorFrame = 0;
            }
        }
        sprite.setClutRow(partner->cursorFrame);
        y = partner->index * 50;
        sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x24, 0x11, y + 0x26);
        if (partner->substate >= 20) {
            if (partner->slot >= 0 && partner->slots[partner->slot] >= 4) {
                y = partner->index * 50 + partner->slot * 15;
                sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x25, 0x87, y + 0x26);
            }
        }
        sprite.setClutRow(0);
    }
    if (partner->fade.level != 0) {
        if (partner->fade.level != 0x1000) {
            sprite.setScale(partner->fade.level, 0x1000, 0x1000);
        }
        digimon = GAME_FUNCS.getPartyMember(partner->index);
        y = partner->index * 50;
        if (partner->fade.level != 0x1000) {
            sprite.setPivot(0x11, y + 0x3A);
        }
        if (GFX.funcs.getTime() - partner->frameTime >= 13) {
            partner->frameTime = GFX.funcs.getTime();
            if (++partner->frame >= 8 || STFGTREP_animations[digimon][partner->frame] == -1) {
                partner->frame = 0;
            }
        }
        sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), STFGTREP_animations[digimon][partner->frame], 0x14, y + 0x28);
        if (partner->levelBlink.on != 0) {
            sprite.setClutRow(partner->levelBlink.frame);
        }
        sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x1F, 0x11, y + 0x26);
        if (partner->levelBlink.on != 0) {
            sprite.setClutRow(0);
        }
        for (i = 0; i < 3; i++) {
            y = partner->index * 50 + i * 15;
            if (partner->fade.level != 0x1000) {
                sprite.setPivot(0x87, y + 0x2D);
            }
            if (partner->slotBlinks[i].blink.on != 0) {
                sprite.setClutRow(partner->slotBlinks[i].blink.frame);
            } else {
                sprite.setClutRow(0);
            }
            sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x20, 0x87, y + 0x26);
        }
    }
}

/* Rolls the shown exp towards the target, digit by digit; 0 once it is there */
s32 STFGTREP_rollExp(ReportPartner *partner) {
    ReportPartnerWindows *windows = partner->children;
    s32 digits = 0;
    s32 n;
    s32 step;
    s32 i;

    if (++partner->rollTime >= 10) {
        partner->shownExp = partner->targetExp;
        STFGTREP_fillPartnerWindows(partner, windows, 1);
        return 0;
    }
    n = partner->targetExp;
    for (i = 10; n != 0; i *= 10) {
        digits++;
        n -= n % i;
    }
    step = 1;
    for (i = digits - 1; i != 0; i--) {
        step *= 10;
        step++;
    }
    partner->shownExp += step;
    if (partner->shownExp > step * 9) {
        partner->shownExp -= step * 9 + 1;
    }
    STFGTREP_fillPartnerWindows(partner, windows, 1);
    return 1;
}

/* A panel's steps: it fades in and out, gives each slot's Digimon its exp,
   with the levels and skills that brings, then the partner's exp and the
   Digimon it learns, each with its message */
void STFGTREP_runPartner(ReportPartner *partner, ReportPartnerWindows *windows) {
    s32 member;
    s32 id;
    s32 done;
    s32 i;

    switch (partner->substate) {
    case 0: /* the match depends on it, which starts the jump table at 0 */
        break;
    case 1:
        STFGTREP_funcs.startFade(&partner->fade, 1);
        partner->substate++;
        break;
    case 2:
        if (STFGTREP_funcs.updateFade(&partner->fade) != 0) {
            STFGTREP_fillPartnerWindows(partner, windows, 1);
            partner->substate = 5;
        }
        break;
    case 11:
        STFGTREP_funcs.startFade(&partner->fade, 0);
        STFGTREP_fillPartnerWindows(partner, windows, 0);
        partner->substate++;
        break;
    case 12:
        if (STFGTREP_funcs.updateFade(&partner->fade) != 0) {
            partner->substate = 15;
        }
        break;
    case 20:
        member = GAME.funcs.getPartyMember(partner->index);
        GAME.funcs.getPartnerSlots(member, partner->slots);
        if (D_80042790.partners[partner->index].used[partner->slot] != 0 && partner->slots[partner->slot] >= 4) {
            partner->slotBlinks[partner->slot].blink.on = STFGTREP_funcs.addDigimonExp(
                member, partner->slots[partner->slot],
                STFGTREP_funcs.getDigimonExp(member, partner->slots[partner->slot],
                                             STFGTREP_rewards[D_80042790.battle].digimonExp, partner->report->used));
        }
        partner->substate++;
        break;
    case 21:
        if (partner->slotBlinks[partner->slot].blink.on != 0) {
            if (partner->voice != -1) {
                SOUND.keyOff(partner->sound, partner->voice);
                partner->voice = -1;
            }
            partner->voice = SOUND.playSound(0x4000C);
            partner->sound = 0x4000C;
            windows->message->setString(windows->message, FILE_CACHE_LOAD[0](TEXT_FILE(0x56)), 4);
            windows->message->setTypeDelay(windows->message, 6);
            STFGTREP_fillPartnerWindows(partner, windows, 1);
            partner->substate = 25;
            partner->step = 0;
        } else {
            partner->substate = 24;
        }
        break;
    case 22:
        member = GAME.funcs.getPartyMember(partner->index);
        GAME.funcs.getPartnerSlots(member, partner->slots);
        id = STFGTREP_funcs.addSkill(member, partner->slots[partner->slot]);
        if (id != 0) {
            windows->message->setString(windows->message, FILE_CACHE.load(TEXT_FILE(0x56)), 5);
            windows->message->setSubString(windows->message, FILE_CACHE.load(TEXT_FILE(0xA3)), id, 1);
            windows->message->setTypeDelay(windows->message, 6);
            partner->substate = 25;
            partner->step = 1;
        } else {
            partner->substate = 23;
        }
        break;
    case 23:
        member = GAME.funcs.getPartyMember(partner->index);
        GAME.funcs.getPartnerSlots(member, partner->slots);
        id = STFGTREP_funcs.learnSkill(member, partner->slots[partner->slot]);
        if (id != 0) {
            windows->message->setString(windows->message, FILE_CACHE.load(TEXT_FILE(0x56)), 6);
            windows->message->setSubString(windows->message, FILE_CACHE.load(TEXT_FILE(0xA3)), id, 1);
            windows->message->setTypeDelay(windows->message, 6);
            partner->substate = 25;
            partner->step = 2;
        } else {
            partner->substate = 24;
        }
        break;
    case 24:
        if (++partner->slot >= 3) {
            partner->slot = -1;
            partner->substate = 40;
        } else {
            partner->substate = 20;
        }
        break;
    case 25:
    case 45:
        if (windows->message->isFinished(windows->message) != 0) {
            windows->message->setVisible(windows->message, 0);
            partner->report->arrowOn = 0;
            switch (partner->step) {
            case 0:
            case 1:
            default:
                partner->substate = 22;
                break;
            case 2:
                partner->substate = 23;
                break;
            case 3:
            case 4:
                partner->substate = 41;
                break;
            case 5:
                partner->substate = 50;
                break;
            }
        } else if (windows->message->isWaitingForButton(windows->message) != 0) {
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x4001C);
            } else {
                partner->report->arrowOn = 1;
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            windows->message->showPage(windows->message);
        }
        break;
    case 40: {
        /* this case's and the next one's own locals: the match depends on
           them, which keep the partner and the Digimon learnt out of the
           registers member and id get */
        s32 raised = GAME.funcs.getPartyMember(partner->index);
        ReportPartnerStats *stats;

        if (STFGTREP_funcs.addExp(raised, partner->exp) != 0) {
            stats = (ReportPartnerStats *)GAME.funcs.getPartnerStats(raised);
            partner->levelBlink.on = 1;
            if (partner->voice != -1) {
                SOUND.keyOff(partner->sound, partner->voice);
                partner->voice = -1;
            }
            partner->voice = SOUND.playSound(0x4000B);
            partner->sound = 0x4000B;
            windows->message->setString(windows->message, FILE_CACHE_LOAD[0](TEXT_FILE(0x56)), 7);
            windows->message->setSubString(windows->message, stats->name, -1, 1);
            windows->message->setNumber(windows->message, 2, stats->stats[0]);
            windows->message->setTypeDelay(windows->message, 6);
            partner->substate = 45;
            partner->step = 3;
        } else {
            partner->substate = 41;
        }
        STFGTREP_fillPartnerWindows(partner, windows, 1);
        break;
    }
    case 41: {
        s32 learnt;
        DigimonData *digimon;

        learnt = STFGTREP_funcs.learnDigimon(GAME_FUNCS.getPartyMember(partner->index));
        if (learnt != 0) {
            digimon = ON_PARTNER_ENTRY_ADDED(learnt);
            windows->message->setString(windows->message, FILE_CACHE.load(TEXT_FILE(0x56)), 8);
            windows->message->setSubString(windows->message, FILE_CACHE.load(TEXT_FILE(0x4F)), digimon->nameId, 1);
            windows->message->setTypeDelay(windows->message, 6);
            STFGTREP_fillPartnerWindows(partner, windows, 1);
            partner->substate = 45;
            partner->step = 4;
            partner->learned = 1;
        } else if (partner->learned != 0) {
            partner->substate = 42;
        } else {
            partner->substate = 50;
        }
        break;
    }
    case 42:
        if (GAME.funcs.listPartnerEntries(GAME.funcs.getPartyMember(partner->index), partner->entries) >= 4) {
            windows->message->setString(windows->message, FILE_CACHE_LOAD[0](TEXT_FILE(0x56)), 9);
            windows->message->setTypeDelay(windows->message, 6);
            partner->substate = 45;
            partner->step = 5;
        } else {
            partner->substate = 50;
        }
        break;
    case 50:
        done = 1;
        if (partner->levelBlink.on != 0) {
            done = partner->levelBlink.frame >= 10;
        }
        if (done) {
            for (i = 0; i < 3; i++) {
                if (partner->slotBlinks[i].blink.on != 0 && partner->slotBlinks[i].blink.frame < 10) {
                    done = 0;
                }
            }
            if (done) {
                partner->substate = 5;
                partner->selected = 0;
            }
        }
        break;
    }
    if (partner->substate >= 20 && STFGTREP_rollExp(partner) != 0) {
        SOUND.playSound(0x800452C6);
    }
}

/* A partner's panel task */
void STFGTREP_updatePartner(ReportPartner *partner, ReportPartnerWindows *windows) {
    ReportPartnerStats *stats;

    switch (partner->state) {
    case TASK_INIT:
    default:
        partner->nextState(partner);
        STFGTREP_createPartnerWindows(partner, windows);
        partner->fade.duration = 10;
        stats = (ReportPartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(partner->index));
        partner->shownExp = stats->exp;
        if (partner->shownExp > 999998) {
            partner->rollTime = 10;
        }
        if (partner->boosted == 0) {
            partner->boostExp(partner);
        }
        partner->targetExp = stats->exp + partner->exp;
        if (partner->targetExp > 999999) {
            partner->targetExp = 999999;
        }
        break;
    case TASK_RUN:
        STFGTREP_runPartner(partner, windows);
        STFGTREP_drawPartner(partner);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void STFGTREP_showPartner(ReportPartner *partner) {
    partner->substate = 1;
}

void STFGTREP_hidePartner(ReportPartner *partner) {
    partner->substate = 11;
}

void STFGTREP_raisePartner(ReportPartner *partner) {
    partner->substate = 20;
}

/* Adds a fifth to the exp once, if the partner wears item 0x141 */
s32 STFGTREP_boostExp(ReportPartner *partner) {
    ReportPartnerStats *stats;

    if (partner->boosted == 0) {
        stats = (ReportPartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(partner->index));
        if (stats->equip[4] == 0x141 || stats->equip[5] == 0x141) {
            partner->exp += partner->exp / 5;
        }
    }
    partner->boosted = 1;
    return partner->exp;
}

void STFGTREP_selectPartner(ReportPartner *partner) {
    partner->selected = 1;
}

ReportPartner *STFGTREP_createPartner(FightReport *report, s32 index, s32 exp) {
    ReportPartner *partner = createTask(STFGTREP_updatePartner, sizeof(ReportPartner), 0x30);

    partner->show = STFGTREP_showPartner;
    partner->hide = STFGTREP_hidePartner;
    partner->raise = STFGTREP_raisePartner;
    partner->boostExp = STFGTREP_boostExp;
    partner->select = STFGTREP_selectPartner;
    partner->layer = 0x1000;
    partner->depth = 6;
    partner->report = report;
    partner->voice = -1;
    partner->index = index;
    partner->exp = exp;
    return partner;
}

void STFGTREP_createWindows(FightReport *report, FightReportChildren *children) {
    TextWindow *window;

    children->exp = createTextWindow(report->layer, 3, 0x42, 0x17);
    children->expLabel = createTextWindow(report->layer, 3, 0x45, 0x17);
    window = createTextWindow(report->layer, 1, 0x14, 0xC2);
    children->message = window;
    window->setLines(window, 2);
}

/* Draws the report's message arrow, background, header and footer */
void STFGTREP_drawReport(FightReport *report) {
    SpriteDrawer sprite;

    if (report->arrowOn != 0) {
        if (GFX.funcs.getTime() - report->arrowTime >= 5) {
            report->arrowTime = GFX.funcs.getTime();
            if (++report->arrowFrame >= 5) {
                report->arrowFrame = 0;
            }
        }
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x140, 0);
        sprite.setLayerId(report->layer, report->depth - 2);
        sprite.setClutRow(report->arrowFrame);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_MENU_SPRITES << 16), 10, 0x123, 0xD0);
    }
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x280, 0);
    sprite.setLayerId(report->layer, report->depth);
    if (report->bgSkip != 0) {
        report->bgScroll++;
        report->bgScroll = report->bgScroll < 0x60 ? report->bgScroll : 0;
        report->bgSkip = 0;
    } else {
        report->bgSkip = 1;
    }
    sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x1E, report->bgScroll, report->bgScroll);
    sprite.setLayerId(report->layer, report->depth - 1);
    if (report->header.level != 0) {
        if (report->header.level != 0x1000) {
            sprite.setScale(report->header.level, 0x1000, 0x1000);
            sprite.setPivot(0, 0x18);
        }
        sprite.draw(FILE_CACHE.getEntry((FILE_FGTREP_SPRITES - 1) << 16), 0x21, 0, 0xF);
    }
    if (report->footer.level != 0) {
        sprite.setScale(0x1000, report->footer.level, 0x1000);
        if (report->footer.level != 0x1000) {
            sprite.setPivot(0xA0, 0xCE);
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0]((FILE_FGTREP_SPRITES - 1) << 16), 0x1D, 0xB, 0xBC);
    }
}

/* The report while it runs: shows the panels, then for each partner that
   got exp its message and the raise, then the money and the item won, and
   fades out */
void STFGTREP_runReport(FightReport *report, FightReportChildren *children) {
    ReportPartnerStats *stats;
    s32 money;
    s32 shown;
    s32 hidden;
    s32 i;
    s32 j;

    switch (report->substate) {
    case 1:
        for (i = 0; i < report->count; i++) {
            children->partners[i]->show(children->partners[i]);
        }
    case 0:
    default:
        report->substate++;
        break;
    case 4:
        shown = 1;
        for (j = 0; j < report->count; j++) {
            if (children->partners[j]->substate != 5) {
                shown = 0;
                break;
            }
        }
        if (shown) {
            STFGTREP_funcs.startFade(&report->footer, 1);
            report->substate++;
        }
        break;
    case 5:
        if (STFGTREP_funcs.updateFade(&report->footer) != 0) {
            report->substate++;
        }
        break;
    case 6:
        if (report->step < report->count) {
            if (report->exp[report->step] == 0) {
                report->step++;
            } else {
                STFGTREP_funcs.startFade(&report->header, 1);
                children->partners[report->step]->select(children->partners[report->step]);
                report->substate++;
            }
        } else {
            report->setSubstate(report, 0x14);
        }
        break;
    case 7:
        if (STFGTREP_funcs.updateFade(&report->header) != 0) {
            children->message->setString(children->message, FILE_CACHE.load(TEXT_FILE(0x56)), 2);
            children->message->setNumber(children->message, 1, report->exp[report->step]);
            children->message->setTypeDelay(children->message, 6);
            children->exp->setNumber(children->exp, 0, report->exp[report->step]);
            children->exp->setRightAlign(children->exp, 1);
            children->expLabel->setString(children->expLabel, FILE_CACHE.load(TEXT_FILE(0x56)), 1);
            report->substate++;
        }
        break;
    case 8:
        if (children->message->isFinished(children->message) != 0) {
            report->arrowOn = 0;
            children->message->setVisible(children->message, 0);
            report->substate = 10;
        } else if (children->message->isWaitingForButton(children->message) != 0) {
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x4001C);
            } else {
                report->arrowOn = 1;
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            children->message->showPage(children->message);
        }
        break;
    case 10:
        children->partners[report->step]->raise(children->partners[report->step]);
        report->substate++;
        break;
    case 11:
        if (children->partners[report->step]->substate == 5) {
            STFGTREP_funcs.startFade(&report->header, 0);
            children->exp->setVisible(children->exp, 0);
            children->expLabel->setVisible(children->expLabel, 0);
            report->substate++;
            report->step++;
        }
        break;
    case 12:
        if (STFGTREP_funcs.updateFade(&report->header) != 0) {
            report->substate = 6;
        }
        break;
    case 0x14:
        stats = (ReportPartnerStats *)GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_80042790.member));
        money = STFGTREP_rewards[D_80042790.battle].money;
        if (stats->equip[4] == 0x142 || stats->equip[5] == 0x142) {
            money += STFGTREP_rewards[D_80042790.battle].money / 5;
        }
        children->message->setString(children->message, FILE_CACHE.load(TEXT_FILE(0x56)), 10);
        children->message->setNumber(children->message, 1, money);
        children->message->setTypeDelay(children->message, 6);
        report->substate = 0x19;
        report->step = 0;
        GAME.money += money;
        if (GAME.money > 9999999) {
            GAME.money = 9999999;
        }
        break;
    case 0x15:
        if (D_80042790.item != 0) {
            children->message->setString(children->message, FILE_CACHE.load(TEXT_FILE(0x56)), 11);
            children->message->setSubString(children->message, FILE_CACHE.load(TEXT_FILE(0x6B)), D_80042790.item, 1);
            children->message->setTypeDelay(children->message, 6);
            report->substate = 0x19;
            report->step = 1;
            GAME.items[D_80042790.item]++;
            if (GAME.items[D_80042790.item] >= 100) {
                GAME.items[D_80042790.item] = 99;
            }
        } else {
            report->substate = 0x32;
        }
        break;
    case 0x19:
        if (children->message->isFinished(children->message) != 0) {
            children->message->setVisible(children->message, 0);
            report->arrowOn = 0;
            switch (report->step) {
            case 0:
            default:
                report->substate = 0x15;
                break;
            case 1:
                report->substate = 0x32;
                break;
            }
        } else if (children->message->isWaitingForButton(children->message) != 0) {
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x4001C);
            } else {
                report->arrowOn = 1;
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            children->message->showPage(children->message);
        }
        break;
    case 0x32:
        children->fade = STFGTREP_createFader();
        children->fade->start(children->fade, 0, 30);
        STFGTREP_funcs.startFade(&report->footer, 0);
        children->message->setVisible(children->message, 0);
        report->substate++;
        break;
    case 0x33:
        if (STFGTREP_funcs.updateFade(&report->footer) != 0) {
            for (i = 0; i < report->count; i++) {
                children->partners[i]->hide(children->partners[i]);
            }
            report->substate++;
        }
        break;
    case 0x34:
        hidden = 1;
        for (j = 0; j < report->count; j++) {
            if (children->partners[j]->substate != 15) {
                hidden = 0;
                break;
            }
        }
        if (hidden) {
            report->substate++;
        }
        break;
    case 0x35:
        if (children->fade->state == TASK_DONE) {
            report->state = TASK_KILL;
        }
        break;
    }
}

/* The report's main task: loads the files, shares the battle's exp among the
   partners who fought and creates their panels */
void STFGTREP_updateReport(FightReport *report, FightReportChildren *children) {
    s32 fought;
    s32 exp;
    s32 i;
    s32 j;

    switch (report->state) {
    case TASK_INIT:
    default:
        switch (report->substate) {
        case 0:
        default:
            STFGTREP_funcs.loadFiles();
            report->substate++;
            break;
        case 1:
            if (STFGTREP_funcs.filesLoading() != 0) {
                break;
            }
            report->nextState(report);
            STFGTREP_createWindows(report, children);
            for (i = 0; i < 3; i++) {
                if (GAME.funcs.getPartyMember(i) >= 0) {
                    report->count++;
                }
            }
            fought = 0;
            for (i = 0; i < 3; i++) {
                if (D_80042790.partners[i].fought != 0) {
                    fought++;
                    for (j = 0; j < 3; j++) {
                        if (D_80042790.partners[i].used[j] != 0) {
                            report->used++;
                        }
                    }
                }
            }
            switch (fought) {
            case 1:
            default:
                exp = STFGTREP_rewards[D_80042790.battle].exp;
                break;
            case 2:
                exp = STFGTREP_rewards[D_80042790.battle].exp * 6 / 10;
                break;
            case 3:
                exp = STFGTREP_rewards[D_80042790.battle].exp / 3;
                break;
            }
            for (i = 0; i < report->count; i++) {
                if (D_80042790.partners[i].fought != 0) {
                    children->partners[i] = STFGTREP_createPartner(report, i, exp);
                    report->exp[i] = children->partners[i]->boostExp(children->partners[i]);
                } else {
                    children->partners[i] = STFGTREP_createPartner(report, i, 0);
                }
            }
            report->header.duration = 10;
            report->footer.duration = 10;
            break;
        }
        break;
    case TASK_RUN:
        STFGTREP_runReport(report, children);
        STFGTREP_drawReport(report);
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        GAME.funcs.requestMode(GAME.fieldMode, 0);
        break;
    }
}

FightReport *STFGTREP_createScreen(void) {
    FightReport *report = createTask(STFGTREP_updateReport, sizeof(FightReport), 0x1C);

    report->layer = 0x1000;
    report->depth = 7;
    return report;
}

void STFGTREP_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0);
    loader.loadArchive(FILE_CACHE.getEntry(FILE_FGTREP_SPRITES << 16));
    FILE_CACHE.request(TEXT_FILE(0x56));
    FILE_CACHE.request(TEXT_FILE(0x4F));
    FILE_CACHE.request(TEXT_FILE(0x6B));
}

s32 STFGTREP_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x56)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x4F)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x6B)) != 0;
}

void STFGTREP_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STFGTREP_updateFade(PanelAnim *fade) {
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

void STFGTREP_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STFGTREP_updateLerp(MenuLerp *lerp) {
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

/* Raises a partner's max HP, max MP, battle stats and, up to level 40, its
   resistances for a new level, by its growth (DIGIMON_DATA) and at random */
void STFGTREP_raiseStats(s32 partner, s32 level) {
    ReportPartnerStats *stats = (ReportPartnerStats *)GAME_FUNCS.getPartnerStats(partner);
    DigimonData *digimon = &DIGIMON_DATA[partner];
    s32 tier;
    s32 i;
    s32 growth;
    s32 gain;
    s16 *values;

    if (level < 5) {
        tier = 0;
    } else if (level < 20) {
        tier = 1;
    } else if (level < 40) {
        tier = 2;
    } else {
        tier = 3;
    }
    /* read into a variable of its own: the match depends on it, since the
       original reads the growth before it calls RANDOM.next and adds the
       gain as a whole */
    growth = digimon->hpGrowth;
    gain = growth - STFGTREP_vitalCuts[tier] + STFGTREP_vitalRandom[RANDOM.next() % 9];
    stats->stats[3] += gain;
    if (stats->stats[3] >= 10000) {
        stats->stats[3] = 9999;
    }
    growth = digimon->mpGrowth;
    gain = growth - STFGTREP_vitalCuts[tier] + STFGTREP_vitalRandom[RANDOM.next() % 9];
    stats->stats[5] += gain;
    if (stats->stats[5] >= 10000) {
        stats->stats[5] = 9999;
    }
    values = stats->stats;
    if (level < 5) {
        tier = 0;
    } else if (level < 20) {
        tier = 1;
    } else if (level < 40) {
        tier = 2;
    } else if (level < 60) {
        tier = 3;
    } else if (level < 80) {
        tier = 4;
    } else {
        tier = 5;
    }
    for (i = 0; i < 6; i++) {
        growth = digimon->statGrowth[i];
        gain = STFGTREP_statGains[tier][growth + RANDOM.next() % 5];
        values[6 + i] += gain;
        if (values[6 + i] >= 1000) {
            values[6 + i] = 999;
        }
    }
    if (level < 41) {
        for (i = 0; i < 7; i++) {
            growth = digimon->resistGrowth[i];
            gain = STFGTREP_resistGains[growth + RANDOM.next() % 4];
            values[12 + i] += gain;
            if (values[12 + i] >= 1000) {
                values[12 + i] = 999;
            }
        }
    }
}

/* Adds exp to a partner and raises its level, and its stats with it, as far
   as the exp reaches; whether it went up */
s32 STFGTREP_addExp(s32 partner, s32 exp) {
    ReportPartnerStats *stats = (ReportPartnerStats *)GAME_FUNCS.getPartnerStats(partner);
    DigimonData *digimon = &DIGIMON_DATA[partner];
    s32 leveled;
    s32 level;
    s32 tier;
    s32 up;

    stats->exp += exp;
    if (stats->exp > 999999) {
        stats->exp = 999999;
    }
    leveled = 0;
    /* two statements: the match depends on it, since the level is loaded
       into the register that counts the levels */
    level = stats->stats[0];
    level++;
    do {
        if (level < 5) {
            tier = 0;
        } else if (level < 20) {
            tier = 1;
        } else if (level < 40) {
            tier = 2;
        } else if (level < 100) {
            tier = 3;
        } else {
            break;
        }
        if ((level * level * level + level * 5 - 6) * digimon->expRate / 10 + STFGTREP_levelExp[tier] < stats->exp) {
            if (++stats->stats[0] < 100) {
                STFGTREP_raiseStats(partner, stats->stats[0]);
            } else {
                stats->stats[0] = 99;
            }
            stats->stats[1] += 5;
            if (stats->stats[1] >= 100) {
                stats->stats[1] = 99;
            }
            leveled = 1;
            up = 1;
        } else {
            up = 0;
        }
        level++;
    } while (up);
    return leveled;
}

INCLUDE_ASM("stfgtrep/nonmatchings/stfgtrep", func_80085A38);

/* Adds exp to one of a partner's Digimon and raises its level as far as the
   exp reaches, up to 99; whether it went up */
s32 STFGTREP_addDigimonExp(s32 partner, s32 id, s32 exp) {
    DigimonData *digimon = ON_PARTNER_ENTRY_ADDED(id);
    ReportEntry entry;
    s32 leveled;
    s32 need;
    s32 up;
    s32 n;

    GAME_FUNCS.getPartnerEntry(partner, id, &entry);
    entry.exp += exp;
    if (entry.exp > 9999999) {
        entry.exp = 9999999;
    }
    if (entry.level >= 99) {
        return 0;
    }
    leveled = 0;
    do {
        /* 10 exp a level up to expLevel, 50 after it */
        if (digimon->expLevel >= entry.level + 1) {
            need = entry.level * 10;
        } else {
            n = digimon->expLevel - 1;
            need = n * 10 + (entry.level - n) * 50;
        }
        up = 0;
        if (entry.exp >= need) {
            leveled = 1;
            entry.level++;
            up = entry.level < 99;
        }
    } while (up);
    GAME_FUNCS.setPartnerEntry(partner, id, &entry);
    return leveled;
}

/* Gives one of a partner's Digimon the first skill whose level it has
   reached and that it hasn't yet (DigimonData.skills); the skill, or 0 */
s32 STFGTREP_addSkill(s32 partner, s32 id) {
    ReportEntry entry;
    DigimonData *digimon;
    s32 i;

    GAME.funcs.getPartnerEntry(partner, id, &entry);
    for (i = 0; i < 6; i++) {
        if (entry.skills[i] == 0) {
            digimon = ON_PARTNER_ENTRY_ADDED(id);
            if (digimon->skills[i + 1] != 0 && entry.level >= digimon->skillLevels[i]) {
                entry.skills[i] = digimon->skills[i + 1];
                if (i == 5) {
                    entry.skills[i] |= 0x8000;
                }
                GAME.funcs.setPartnerEntry(partner, id, &entry);
                return digimon->skills[i + 1];
            }
        }
    }
    return 0;
}

/* Marks known (0x2000) the first skill of one of a partner's Digimon whose
   level it has reached (DigimonData.knownLevels); the skill, or 0 */
s32 STFGTREP_learnSkill(s32 partner, s32 id) {
    ReportEntry entry;
    DigimonData *digimon;
    s32 i;

    GAME.funcs.getPartnerEntry(partner, id, &entry);
    digimon = ON_PARTNER_ENTRY_ADDED(id);
    for (i = 0; i < 5; i++) {
        if (entry.skills[i] > 0 && !(entry.skills[i] & 0x2000) && entry.level >= digimon->knownLevels[i]) {
            entry.skills[i] |= 0x2000;
            GAME.funcs.setPartnerEntry(partner, id, &entry);
            return entry.skills[i] & 0x1FFF;
        }
    }
    return 0;
}

/* The exp one of a partner's Digimon gets of a battle's: less as the partner
   goes up in level, shared by the Digimon used, at least 1 and at most 10,
   or 50 once the Digimon is past its expLevel */
s32 STFGTREP_getDigimonExp(s32 partner, s32 id, s32 exp, s32 used) {
    ReportEntry entry;
    DigimonData *digimon;
    s32 level = ((ReportPartnerStats *)GAME_FUNCS.getPartnerStats(partner))->stats[0];
    s32 share;
    s32 n;
    s32 tenfold;

    /* computed apart: the match depends on it, since the original multiplies
       before it compares the level */
    tenfold = exp * 10;
    if (level < 51) {
        n = tenfold / level;
    } else {
        n = exp / 5;
    }
    switch (used) {
    case 0:
    case 1:
        share = n;
        break;
    case 2:
        share = n * 6 / 10;
        break;
    default:
        share = n / used;
        break;
    }
    digimon = ON_PARTNER_ENTRY_ADDED(id);
    GAME_FUNCS.getPartnerEntry(partner, id, &entry);
    if (share <= 0) {
        share = 1;
    } else if (entry.level < digimon->expLevel) {
        if (share > 10) {
            share = 10;
        }
    } else if (share > 50) {
        share = 50;
    }
    return share;
}


#if VERSION_US
BattleReward STFGTREP_rewards[] = {
    { 0, 0, 0 },
    { 12, 120, 240 },
    { 14, 140, 280 },
    { 11, 176, 475 },
    { 14, 216, 675 },
    { 27, 268, 645 },
    { 29, 435, 870 },
    { 32, 325, 500 },
    { 32, 320, 740 },
    { 34, 340, 1000 },
    { 35, 718, 1490 },
    { 40, 380, 800 },
    { 43, 440, 800 },
    { 45, 450, 900 },
    { 41, 627, 1220 },
    { 46, 460, 930 },
    { 43, 649, 1335 },
    { 47, 470, 960 },
    { 46, 705, 1430 },
    { 46, 703, 1410 },
    { 47, 715, 1420 },
    { 48, 719, 1395 },
    { 49, 737, 1470 },
    { 55, 550, 1100 },
    { 57, 570, 1300 },
    { 50, 757, 1450 },
    { 52, 788, 1560 },
    { 52, 783, 1515 },
    { 53, 795, 1580 },
    { 56, 842, 1655 },
    { 99, 990, 1980 },
    { 53, 530, 1060 },
    { 57, 1224, 2515 },
    { 57, 1700, 3000 },
    { 1, 6, 10 },
    { 1, 5, 20 },
    { 3, 17, 30 },
    { 4, 19, 40 },
    { 8, 39, 80 },
    { 2, 10, 25 },
    { 4, 20, 40 },
    { 2, 11, 20 },
    { 3, 16, 30 },
    { 3, 15, 35 },
    { 4, 21, 40 },
    { 4, 22, 45 },
    { 16, 80, 160 },
    { 5, 27, 55 },
    { 13, 66, 130 },
    { 5, 25, 50 },
    { 6, 31, 60 },
    { 6, 30, 60 },
    { 6, 29, 70 },
    { 8, 41, 85 },
    { 8, 40, 80 },
    { 9, 46, 90 },
    { 31, 154, 310 },
    { 13, 96, 160 },
    { 10, 50, 190 },
    { 18, 91, 180 },
    { 29, 145, 290 },
    { 20, 98, 200 },
    { 27, 136, 240 },
    { 40, 200, 400 },
    { 24, 118, 200 },
    { 20, 101, 490 },
    { 12, 58, 120 },
    { 23, 116, 220 },
    { 20, 100, 205 },
    { 20, 102, 200 },
    { 22, 112, 200 },
    { 44, 220, 400 },
    { 45, 223, 440 },
    { 22, 109, 220 },
    { 22, 110, 225 },
    { 25, 125, 250 },
    { 29, 147, 290 },
    { 23, 115, 235 },
    { 23, 117, 230 },
    { 24, 123, 250 },
    { 24, 120, 200 },
    { 25, 124, 300 },
    { 26, 129, 190 },
    { 47, 235, 470 },
    { 47, 234, 100 },
    { 27, 135, 270 },
    { 27, 134, 270 },
    { 46, 233, 450 },
    { 29, 145, 320 },
    { 30, 152, 300 },
    { 29, 146, 280 },
    { 31, 155, 330 },
    { 36, 225, 770 },
    { 43, 215, 420 },
    { 34, 168, 340 },
    { 38, 189, 380 },
    { 35, 176, 350 },
    { 35, 175, 400 },
    { 45, 225, 450 },
    { 34, 172, 320 },
    { 36, 183, 400 },
    { 36, 179, 360 },
    { 45, 225, 420 },
    { 37, 185, 370 },
    { 44, 221, 440 },
    { 35, 174, 350 },
    { 34, 170, 340 },
    { 36, 180, 360 },
    { 39, 196, 390 },
    { 36, 180, 360 },
    { 41, 205, 450 },
    { 41, 204, 400 },
    { 41, 205, 410 },
    { 41, 205, 420 },
    { 41, 206, 420 },
    { 43, 215, 420 },
    { 46, 230, 460 },
    { 43, 218, 430 },
    { 49, 244, 490 },
    { 43, 217, 430 },
    { 43, 214, 390 },
    { 44, 223, 420 },
    { 44, 221, 470 },
    { 44, 223, 460 },
    { 43, 215, 430 },
    { 43, 216, 480 },
    { 44, 220, 450 },
    { 44, 222, 610 },
    { 54, 273, 520 },
    { 49, 247, 490 },
    { 45, 225, 460 },
    { 45, 224, 440 },
    { 44, 222, 460 },
    { 45, 226, 500 },
    { 45, 227, 440 },
    { 55, 276, 530 },
    { 47, 235, 440 },
    { 48, 243, 500 },
    { 56, 280, 560 },
    { 47, 235, 500 },
    { 55, 277, 530 },
    { 56, 282, 550 },
    { 49, 246, 490 },
    { 55, 277, 540 },
    { 56, 279, 600 },
    { 9, 45, 90 },
    { 30, 150, 290 },
    { 8, 40, 80 },
    { 21, 105, 210 },
    { 22, 112, 220 },
    { 33, 167, 350 },
    { 33, 165, 330 },
    { 19, 76, 190 },
    { 41, 205, 400 },
    { 21, 104, 215 },
    { 37, 186, 370 },
    { 22, 158, 300 },
    { 36, 180, 360 },
    { 37, 184, 370 },
    { 35, 175, 350 },
    { 47, 236, 460 },
    { 42, 210, 430 },
    { 46, 232, 460 },
    { 48, 242, 480 },
    { 46, 231, 460 },
    { 31, 222, 660 },
    { 39, 299, 770 },
    { 43, 344, 880 },
    { 43, 366, 990 },
    { 44, 399, 1110 },
    { 40, 201, 400 },
    { 43, 215, 430 },
    { 45, 227, 470 },
    { 32, 160, 330 },
    { 40, 250, 800 },
    { 48, 241, 480 },
    { 36, 179, 360 },
    { 41, 203, 410 },
    { 47, 235, 420 },
    { 44, 221, 450 },
    { 48, 240, 480 },
    { 48, 239, 480 },
    { 44, 220, 500 },
    { 48, 243, 480 },
    { 47, 236, 460 },
    { 54, 271, 550 },
    { 54, 272, 510 },
    { 49, 245, 490 },
    { 29, 291, 600 },
    { 29, 299, 590 },
    { 29, 451, 890 },
    { 32, 160, 325 },
    { 29, 289, 580 },
    { 44, 672, 1370 },
    { 55, 558, 1080 },
    { 49, 493, 990 },
    { 50, 503, 1000 },
    { 51, 770, 1500 },
    { 53, 530, 1060 },
    { 50, 508, 990 },
    { 1, 4, 50 },
    { 4, 65, 145 },
    { 41, 661, 1250 },
    { 7, 125, 220 },
    { 7, 79, 155 },
    { 6, 103, 200 },
    { 9, 45, 180 },
    { 43, 737, 1475 },
    { 6, 100, 225 },
    { 7, 109, 210 },
    { 10, 101, 190 },
    { 10, 105, 210 },
    { 10, 100, 200 },
    { 40, 700, 1305 },
    { 17, 269, 530 },
    { 9, 158, 290 },
    { 41, 205, 820 },
    { 38, 569, 1195 },
    { 38, 565, 1175 },
    { 38, 595, 1110 },
    { 40, 607, 1255 },
    { 40, 682, 1335 },
    { 41, 642, 1265 },
    { 42, 210, 840 },
    { 58, 904, 1730 },
    { 42, 641, 1220 },
    { 42, 638, 1145 },
    { 34, 342, 725 },
    { 35, 524, 990 },
    { 35, 533, 1110 },
    { 35, 357, 715 },
    { 35, 523, 1050 },
    { 36, 361, 680 },
    { 35, 544, 1110 },
    { 44, 665, 1330 },
    { 44, 664, 1510 },
    { 44, 656, 1375 },
    { 45, 454, 545 },
    { 44, 671, 1320 },
    { 44, 669, 1380 },
    { 45, 680, 1485 },
    { 45, 456, 910 },
    { 45, 458, 900 },
    { 52, 791, 1625 },
    { 52, 800, 1565 },
    { 52, 525, 1570 },
    { 52, 814, 1600 },
    { 52, 786, 1570 },
    { 52, 791, 1740 },
    { 53, 813, 1680 },
    { 57, 977, 1920 },
    { 53, 529, 1120 },
    { 53, 535, 1600 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 10, 161, 300 },
    { 17, 160, 340 },
    { 26, 250, 520 },
    { 28, 280, 560 },
    { 29, 300, 580 },
    { 28, 280, 560 },
    { 28, 280, 560 },
    { 28, 280, 560 },
    { 19, 200, 380 },
    { 6, 63, 115 },
    { 11, 173, 320 },
    { 17, 255, 440 },
    { 24, 243, 520 },
    { 25, 379, 720 },
    { 25, 375, 800 },
    { 23, 240, 480 },
    { 36, 538, 1080 },
    { 33, 336, 640 },
    { 26, 394, 820 },
    { 34, 520, 1040 },
    { 13, 204, 420 },
    { 31, 468, 980 },
    { 34, 339, 310 },
    { 31, 475, 940 },
    { 29, 445, 925 },
    { 36, 544, 1220 },
    { 40, 406, 810 },
    { 44, 448, 880 },
    { 37, 566, 1165 },
    { 19, 297, 580 },
    { 23, 230, 470 },
    { 5, 77, 155 },
    { 41, 621, 1240 },
    { 42, 635, 1410 },
    { 30, 466, 980 },
    { 37, 601, 1190 },
    { 40, 399, 840 },
    { 23, 230, 470 },
    { 7, 108, 305 },
    { 11, 171, 630 },
    { 29, 435, 870 },
    { 43, 660, 1340 },
    { 40, 607, 1180 },
    { 42, 634, 1310 },
    { 45, 687, 1320 },
    { 50, 763, 1510 },
    { 12, 120, 240 },
    { 14, 140, 280 },
    { 32, 325, 500 },
    { 32, 320, 740 },
    { 34, 340, 1000 },
    { 40, 380, 800 },
    { 44, 450, 815 },
    { 45, 450, 900 },
    { 46, 460, 930 },
    { 47, 470, 960 },
    { 55, 550, 1100 },
    { 57, 570, 1300 },
    { 53, 530, 1060 },
    { 28, 144, 0 },
    { 15, 153, 275 },
    { 68, 4, 0 },
    { 70, 4, 0 },
    { 70, 4, 0 },
    { 7, 35, 70 },
    { 12, 60, 120 },
    { 17, 85, 170 },
    { 27, 135, 270 },
    { 37, 185, 370 },
    { 42, 210, 420 },
    { 47, 235, 470 },
    { 47, 235, 470 },
};
#elif VERSION_EU
BattleReward STFGTREP_rewards[] = {
    { 0, 0, 0 },
    { 12, 120, 240 },
    { 14, 140, 280 },
    { 11, 176, 475 },
    { 14, 216, 675 },
    { 27, 268, 645 },
    { 29, 435, 870 },
    { 32, 325, 500 },
    { 32, 320, 740 },
    { 34, 340, 1000 },
    { 35, 718, 1490 },
    { 40, 380, 800 },
    { 43, 440, 800 },
    { 45, 450, 900 },
    { 41, 627, 1220 },
    { 46, 460, 930 },
    { 43, 649, 1335 },
    { 47, 470, 960 },
    { 46, 705, 1430 },
    { 46, 703, 1410 },
    { 47, 715, 1420 },
    { 48, 719, 1395 },
    { 49, 737, 1470 },
    { 55, 550, 1100 },
    { 57, 570, 1300 },
    { 50, 757, 1450 },
    { 52, 788, 1560 },
    { 52, 783, 1515 },
    { 53, 795, 1580 },
    { 56, 842, 1655 },
    { 99, 990, 1980 },
    { 53, 530, 1060 },
    { 57, 1224, 2515 },
    { 57, 1700, 3000 },
    { 1, 6, 10 },
    { 1, 5, 20 },
    { 3, 17, 30 },
    { 4, 19, 40 },
    { 8, 39, 80 },
    { 2, 10, 25 },
    { 4, 20, 40 },
    { 2, 11, 20 },
    { 3, 16, 30 },
    { 3, 15, 35 },
    { 4, 21, 40 },
    { 4, 22, 45 },
    { 16, 80, 160 },
    { 5, 27, 55 },
    { 13, 66, 130 },
    { 5, 25, 50 },
    { 6, 31, 60 },
    { 6, 30, 60 },
    { 6, 29, 70 },
    { 8, 41, 85 },
    { 8, 40, 80 },
    { 9, 46, 90 },
    { 31, 154, 310 },
    { 13, 96, 160 },
    { 10, 50, 190 },
    { 18, 91, 180 },
    { 29, 145, 290 },
    { 20, 98, 200 },
    { 27, 136, 240 },
    { 40, 200, 400 },
    { 24, 118, 200 },
    { 20, 101, 490 },
    { 12, 58, 120 },
    { 23, 116, 220 },
    { 20, 100, 205 },
    { 20, 102, 200 },
    { 22, 112, 200 },
    { 44, 220, 400 },
    { 45, 223, 440 },
    { 22, 109, 220 },
    { 22, 110, 225 },
    { 25, 125, 250 },
    { 29, 147, 290 },
    { 23, 115, 235 },
    { 23, 117, 230 },
    { 24, 123, 250 },
    { 24, 120, 200 },
    { 25, 124, 300 },
    { 26, 129, 190 },
    { 47, 235, 470 },
    { 47, 234, 100 },
    { 27, 135, 270 },
    { 27, 134, 270 },
    { 46, 233, 450 },
    { 29, 145, 320 },
    { 30, 152, 300 },
    { 29, 146, 280 },
    { 31, 155, 330 },
    { 36, 225, 770 },
    { 43, 215, 420 },
    { 34, 168, 340 },
    { 38, 189, 380 },
    { 35, 176, 350 },
    { 35, 175, 400 },
    { 45, 225, 450 },
    { 34, 172, 320 },
    { 36, 183, 400 },
    { 36, 179, 360 },
    { 45, 225, 420 },
    { 37, 185, 370 },
    { 44, 221, 440 },
    { 35, 174, 350 },
    { 34, 170, 340 },
    { 36, 180, 360 },
    { 39, 196, 390 },
    { 36, 180, 360 },
    { 41, 205, 450 },
    { 41, 204, 400 },
    { 41, 205, 410 },
    { 41, 205, 420 },
    { 41, 206, 420 },
    { 43, 215, 420 },
    { 46, 230, 460 },
    { 43, 218, 430 },
    { 49, 244, 490 },
    { 43, 217, 430 },
    { 43, 214, 390 },
    { 44, 223, 420 },
    { 44, 221, 470 },
    { 44, 223, 460 },
    { 43, 215, 430 },
    { 43, 216, 480 },
    { 44, 220, 450 },
    { 44, 222, 610 },
    { 54, 273, 520 },
    { 49, 247, 490 },
    { 45, 225, 460 },
    { 45, 224, 440 },
    { 44, 222, 460 },
    { 45, 226, 500 },
    { 45, 227, 440 },
    { 55, 276, 530 },
    { 47, 235, 440 },
    { 48, 243, 500 },
    { 56, 280, 560 },
    { 47, 235, 500 },
    { 55, 277, 530 },
    { 56, 282, 550 },
    { 49, 246, 490 },
    { 55, 277, 540 },
    { 56, 279, 600 },
    { 9, 45, 90 },
    { 30, 150, 290 },
    { 8, 40, 80 },
    { 21, 105, 210 },
    { 22, 112, 220 },
    { 33, 167, 350 },
    { 33, 165, 330 },
    { 19, 76, 190 },
    { 41, 205, 400 },
    { 21, 104, 215 },
    { 37, 186, 370 },
    { 22, 158, 300 },
    { 36, 180, 360 },
    { 37, 184, 370 },
    { 35, 175, 350 },
    { 47, 236, 460 },
    { 42, 210, 430 },
    { 46, 232, 460 },
    { 48, 242, 480 },
    { 46, 231, 460 },
    { 31, 222, 660 },
    { 39, 299, 770 },
    { 43, 344, 880 },
    { 43, 366, 990 },
    { 44, 399, 1110 },
    { 40, 201, 400 },
    { 43, 215, 430 },
    { 45, 227, 470 },
    { 32, 160, 330 },
    { 40, 250, 800 },
    { 48, 241, 480 },
    { 36, 179, 360 },
    { 41, 203, 410 },
    { 47, 235, 420 },
    { 44, 221, 450 },
    { 48, 240, 480 },
    { 48, 239, 480 },
    { 44, 220, 500 },
    { 48, 243, 480 },
    { 47, 236, 460 },
    { 54, 271, 550 },
    { 54, 272, 510 },
    { 49, 245, 490 },
    { 29, 291, 600 },
    { 29, 299, 590 },
    { 29, 451, 890 },
    { 32, 160, 325 },
    { 29, 289, 580 },
    { 44, 672, 1370 },
    { 55, 558, 1080 },
    { 49, 493, 990 },
    { 50, 503, 1000 },
    { 51, 770, 1500 },
    { 53, 530, 1060 },
    { 50, 508, 990 },
    { 1, 4, 50 },
    { 4, 65, 145 },
    { 41, 661, 1250 },
    { 7, 125, 220 },
    { 7, 79, 155 },
    { 6, 103, 200 },
    { 9, 45, 180 },
    { 43, 737, 1475 },
    { 6, 100, 225 },
    { 7, 109, 210 },
    { 10, 101, 190 },
    { 10, 105, 210 },
    { 10, 100, 200 },
    { 40, 700, 1305 },
    { 17, 269, 530 },
    { 9, 158, 290 },
    { 41, 205, 820 },
    { 38, 569, 1195 },
    { 38, 565, 1175 },
    { 38, 595, 1110 },
    { 40, 607, 1255 },
    { 40, 682, 1335 },
    { 41, 642, 1265 },
    { 42, 210, 840 },
    { 58, 904, 1730 },
    { 42, 641, 1220 },
    { 42, 638, 1145 },
    { 34, 342, 725 },
    { 35, 524, 990 },
    { 35, 533, 1110 },
    { 35, 357, 715 },
    { 35, 523, 1050 },
    { 36, 361, 680 },
    { 35, 544, 1110 },
    { 44, 665, 1330 },
    { 44, 664, 1510 },
    { 44, 656, 1375 },
    { 45, 454, 545 },
    { 44, 671, 1320 },
    { 44, 669, 1380 },
    { 45, 680, 1485 },
    { 45, 456, 910 },
    { 45, 458, 900 },
    { 52, 791, 1625 },
    { 52, 800, 1565 },
    { 52, 525, 1570 },
    { 52, 814, 1600 },
    { 52, 786, 1570 },
    { 52, 791, 1740 },
    { 53, 813, 1680 },
    { 57, 977, 1920 },
    { 53, 529, 1120 },
    { 53, 535, 1600 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 1, 6, 10 },
    { 94, 2365, 5475 },
    { 10, 161, 300 },
    { 17, 160, 340 },
    { 26, 250, 520 },
    { 28, 280, 560 },
    { 29, 300, 580 },
    { 28, 280, 560 },
    { 28, 280, 560 },
    { 28, 280, 560 },
    { 19, 200, 380 },
    { 6, 63, 115 },
    { 43, 215, 430 },
    { 43, 216, 480 },
    { 44, 223, 460 },
    { 44, 221, 470 },
    { 45, 225, 420 },
    { 23, 240, 480 },
    { 36, 538, 1080 },
    { 33, 336, 640 },
    { 26, 394, 820 },
    { 34, 520, 1040 },
    { 13, 204, 420 },
    { 31, 468, 980 },
    { 34, 339, 310 },
    { 31, 475, 940 },
    { 29, 445, 925 },
    { 36, 544, 1220 },
    { 40, 406, 810 },
    { 44, 448, 880 },
    { 37, 566, 1165 },
    { 19, 297, 580 },
    { 23, 230, 470 },
    { 5, 77, 155 },
    { 41, 621, 1240 },
    { 42, 635, 1410 },
    { 30, 466, 980 },
    { 37, 601, 1190 },
    { 40, 399, 840 },
    { 23, 230, 470 },
    { 60, 565, 1200 },
    { 60, 577, 1200 },
    { 65, 684, 1300 },
    { 60, 621, 1200 },
    { 75, 1855, 3660 },
    { 75, 1857, 3875 },
    { 75, 1541, 2695 },
    { 75, 1503, 3180 },
    { 60, 600, 1200 },
    { 70, 700, 1400 },
    { 70, 700, 1400 },
    { 70, 320, 740 },
    { 34, 340, 1000 },
    { 40, 380, 800 },
    { 44, 450, 815 },
    { 65, 650, 1300 },
    { 65, 650, 1310 },
    { 70, 700, 1430 },
    { 70, 700, 1400 },
    { 75, 750, 1710 },
    { 75, 750, 1500 },
    { 28, 144, 0 },
    { 15, 153, 275 },
    { 68, 4, 0 },
    { 70, 4, 0 },
    { 70, 4, 0 },
    { 7, 35, 70 },
    { 12, 60, 120 },
    { 17, 85, 170 },
    { 27, 135, 270 },
    { 37, 185, 370 },
    { 42, 210, 420 },
    { 47, 235, 470 },
    { 47, 235, 470 },
};
#endif
Evolution D_80087128[] = {
    { 9, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 10, { { 14, 20 }, { 0, 1 } }, 0, 1 },
    { 11, { { 14, 30 }, { 0, 1 } }, 5, 280 },
    { 12, { { 9, 20 }, { 0, 1 } }, 0, 1 },
    { 13, { { 12, 10 }, { 0, 1 } }, 0, 1 },
    { 14, { { 27, 50 }, { 0, 1 } }, 8, 200 },
    { 15, { { 33, 20 }, { 0, 1 } }, 0, 1 },
    { 16, { { 27, 30 }, { 0, 1 } }, 11, 200 },
    { 17, { { 32, 20 }, { 0, 1 } }, 0, 1 },
    { 18, { { 33, 10 }, { 0, 1 } }, 0, 1 },
    { 19, { { 27, 20 }, { 0, 1 } }, 9, 360 },
    { 20, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 12, 40 }, { 0, 1 } }, 7, 15 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 140 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 14, 50 }, { 0, 1 } }, 0, 1 },
    { 27, { { 15, 40 }, { 0, 1 } }, 0, 1 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 40 }, { 0, 1 } }, 0, 1 },
    { 30, { { 20, 20 }, { 0, 1 } }, 13, 140 },
    { 31, { { 18, 40 }, { 0, 1 } }, 0, 1 },
    { 32, { { 27, 40 }, { 0, 1 } }, 4, 280 },
    { 33, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 13, 200 },
    { 42, { { 19, 40 }, { 0, 1 } }, 0, 1 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_800873E8[] = {
    { 9, { { 23, 30 }, { 0, 1 } }, 0, 1 },
    { 10, { { 31, 20 }, { 0, 1 } }, 0, 1 },
    { 11, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 12, { { 26, 20 }, { 0, 1 } }, 8, 200 },
    { 13, { { 15, 10 }, { 0, 1 } }, 0, 1 },
    { 14, { { 35, 20 }, { 0, 1 } }, 1, 480 },
    { 15, { { 11, 20 }, { 0, 1 } }, 3, 80 },
    { 16, { { 29, 20 }, { 0, 1 } }, 11, 280 },
    { 17, { { 35, 10 }, { 0, 1 } }, 0, 1 },
    { 18, { { 35, 30 }, { 0, 1 } }, 5, 400 },
    { 19, { { 16, 20 }, { 0, 1 } }, 9, 280 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 23, { { 12, 40 }, { 0, 1 } }, 0, 1 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 160 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 14, 50 }, { 0, 1 } }, 0, 1 },
    { 27, { { 15, 40 }, { 0, 1 } }, 7, 15 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 50 }, { 0, 1 } }, 0, 1 },
    { 30, { { 22, 20 }, { 0, 1 } }, 13, 150 },
    { 31, { { 18, 50 }, { 0, 1 } }, 0, 1 },
    { 32, { { 11, 30 }, { 0, 1 } }, 4, 80 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 13, 200 },
    { 42, { { 19, 40 }, { 0, 1 } }, 0, 1 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_800876A8[] = {
    { 9, { { 23, 20 }, { 0, 1 } }, 1, 250 },
    { 10, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 11, { { 14, 20 }, { 0, 1 } }, 2, 460 },
    { 12, { { 34, 10 }, { 0, 1 } }, 0, 1 },
    { 13, { { 10, 20 }, { 0, 1 } }, 0, 1 },
    { 14, { { 20, 20 }, { 0, 1 } }, 5, 320 },
    { 15, { { 19, 10 }, { 0, 1 } }, 3, 200 },
    { 16, { { 21, 40 }, { 0, 1 } }, 11, 120 },
    { 17, { { 24, 20 }, { 0, 1 } }, 3, 300 },
    { 18, { { 23, 30 }, { 0, 1 } }, 12, 200 },
    { 19, { { 28, 30 }, { 0, 1 } }, 9, 110 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 12, 40 }, { 0, 1 } }, 0, 1 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 300 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 14, 50 }, { 0, 1 } }, 0, 1 },
    { 27, { { 15, 40 }, { 0, 1 } }, 0, 1 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 40 }, { 0, 1 } }, 0, 1 },
    { 30, { { 21, 20 }, { 0, 1 } }, 13, 180 },
    { 31, { { 18, 50 }, { 0, 1 } }, 0, 1 },
    { 32, { { 21, 30 }, { 0, 1 } }, 1, 160 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 13, 240 },
    { 42, { { 19, 40 }, { 0, 1 } }, 0, 1 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_80087968[] = {
    { 9, { { 36, 20 }, { 0, 1 } }, 0, 1 },
    { 10, { { 26, 30 }, { 0, 1 } }, 0, 1 },
    { 11, { { 41, 30 }, { 0, 1 } }, 2, 400 },
    { 12, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 13, { { 23, 30 }, { 0, 1 } }, 10, 100 },
    { 14, { { 12, 20 }, { 0, 1 } }, 0, 1 },
    { 15, { { 23, 20 }, { 0, 1 } }, 3, 300 },
    { 16, { { 31, 20 }, { 0, 1 } }, 4, 300 },
    { 17, { { 28, 30 }, { 0, 1 } }, 14, 250 },
    { 18, { { 36, 30 }, { 0, 1 } }, 5, 260 },
    { 19, { { 28, 20 }, { 0, 1 } }, 0, 1 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 130 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 14, 40 }, { 0, 1 } }, 7, 15 },
    { 27, { { 15, 40 }, { 0, 1 } }, 0, 1 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 40 }, { 0, 1 } }, 0, 1 },
    { 30, { { 36, 10 }, { 0, 1 } }, 0, 1 },
    { 31, { { 18, 50 }, { 0, 1 } }, 0, 1 },
    { 32, { { 41, 20 }, { 0, 1 } }, 0, 1 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 0, 1 },
    { 42, { { 19, 40 }, { 0, 1 } }, 0, 1 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_80087C28[] = {
    { 9, { { 37, 30 }, { 0, 1 } }, 0, 1 },
    { 10, { { 37, 35 }, { 0, 1 } }, 13, 160 },
    { 11, { { 37, 45 }, { 0, 1 } }, 2, 200 },
    { 12, { { 25, 35 }, { 0, 1 } }, 2, 200 },
    { 13, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 14, { { 25, 30 }, { 0, 1 } }, 8, 90 },
    { 15, { { 25, 40 }, { 0, 1 } }, 10, 200 },
    { 16, { { 25, 45 }, { 0, 1 } }, 4, 230 },
    { 17, { { 25, 25 }, { 0, 1 } }, 14, 160 },
    { 18, { { 13, 30 }, { 0, 1 } }, 0, 1 },
    { 19, { { 28, 20 }, { 0, 1 } }, 0, 1 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 12, 40 }, { 0, 1 } }, 0, 1 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 190 },
    { 25, { { 18, 5 }, { 0, 1 } }, 7, 20 },
    { 26, { { 14, 50 }, { 0, 1 } }, 0, 1 },
    { 27, { { 15, 50 }, { 0, 1 } }, 0, 1 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 40 }, { 0, 1 } }, 0, 1 },
    { 30, { { 25, 20 }, { 0, 1 } }, 13, 100 },
    { 31, { { 18, 40 }, { 0, 1 } }, 0, 1 },
    { 32, { { 37, 20 }, { 0, 1 } }, 4, 300 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 7, 40 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 13, 140 },
    { 42, { { 19, 40 }, { 0, 1 } }, 0, 1 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_80087EE8[] = {
    { 9, { { 23, 20 }, { 0, 1 } }, 1, 400 },
    { 10, { { 9, 20 }, { 0, 1 } }, 0, 1 },
    { 11, { { 38, 10 }, { 0, 1 } }, 0, 1 },
    { 12, { { 38, 30 }, { 0, 1 } }, 8, 280 },
    { 13, { { 38, 20 }, { 0, 1 } }, 11, 300 },
    { 14, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 15, { { 19, 10 }, { 0, 1 } }, 3, 200 },
    { 16, { { 26, 20 }, { 0, 1 } }, 3, 180 },
    { 17, { { 22, 20 }, { 0, 1 } }, 14, 160 },
    { 18, { { 14, 30 }, { 0, 1 } }, 12, 80 },
    { 19, { { 26, 40 }, { 0, 1 } }, 9, 140 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 12, 40 }, { 0, 1 } }, 0, 1 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 140 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 27, { { 15, 40 }, { 0, 1 } }, 0, 1 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 50 }, { 0, 1 } }, 0, 1 },
    { 30, { { 14, 20 }, { 0, 1 } }, 2, 100 },
    { 31, { { 18, 40 }, { 0, 1 } }, 0, 1 },
    { 32, { { 26, 30 }, { 0, 1 } }, 14, 120 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 13, 190 },
    { 42, { { 19, 40 }, { 0, 1 } }, 0, 1 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_800881A8[] = {
    { 9, { { 11, 20 }, { 0, 1 } }, 0, 1 },
    { 10, { { 20, 20 }, { 0, 1 } }, 0, 1 },
    { 11, { { 29, 20 }, { 0, 1 } }, 1, 300 },
    { 12, { { 11, 30 }, { 0, 1 } }, 2, 280 },
    { 13, { { 27, 20 }, { 0, 1 } }, 11, 120 },
    { 14, { { 18, 20 }, { 0, 1 } }, 2, 80 },
    { 15, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 16, { { 39, 30 }, { 0, 1 } }, 11, 150 },
    { 17, { { 39, 10 }, { 0, 1 } }, 0, 1 },
    { 18, { { 15, 20 }, { 0, 1 } }, 1, 80 },
    { 19, { { 15, 30 }, { 0, 1 } }, 3, 160 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 12, 40 }, { 0, 1 } }, 0, 1 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 250 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 14, 40 }, { 0, 1 } }, 7, 25 },
    { 27, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 28, { { 16, 50 }, { 0, 1 } }, 0, 1 },
    { 29, { { 17, 50 }, { 0, 1 } }, 0, 1 },
    { 30, { { 27, 30 }, { 0, 1 } }, 13, 100 },
    { 31, { { 18, 40 }, { 0, 1 } }, 0, 1 },
    { 32, { { 39, 20 }, { 0, 1 } }, 4, 400 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 40, { { 28, 99 }, { 0, 1 } }, 0, 1 },
    { 41, { { 30, 40 }, { 0, 1 } }, 13, 120 },
    { 42, { { 19, 40 }, { 0, 1 } }, 7, 15 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution D_80088468[] = {
    { 9, { { 14, 20 }, { 0, 1 } }, 0, 1 },
    { 10, { { 40, 10 }, { 0, 1 } }, 0, 1 },
    { 11, { { 14, 40 }, { 0, 1 } }, 1, 240 },
    { 12, { { 28, 30 }, { 0, 1 } }, 8, 140 },
    { 13, { { 14, 30 }, { 0, 1 } }, 11, 320 },
    { 14, { { 30, 20 }, { 0, 1 } }, 0, 1 },
    { 15, { { 21, 40 }, { 0, 1 } }, 3, 300 },
    { 16, { { 0, 1 }, { 0, 1 } }, 7, 5 },
    { 17, { { 21, 30 }, { 0, 1 } }, 14, 300 },
    { 18, { { 28, 20 }, { 0, 1 } }, 12, 100 },
    { 19, { { 16, 30 }, { 0, 1 } }, 4, 180 },
    { 20, { { 9, 50 }, { 0, 1 } }, 0, 1 },
    { 21, { { 10, 50 }, { 0, 1 } }, 0, 1 },
    { 22, { { 11, 50 }, { 0, 1 } }, 0, 1 },
    { 23, { { 12, 40 }, { 0, 1 } }, 0, 1 },
    { 24, { { 12, 50 }, { 0, 1 } }, 14, 220 },
    { 25, { { 13, 5 }, { 18, 5 } }, 0, 1 },
    { 26, { { 14, 50 }, { 0, 1 } }, 0, 1 },
    { 27, { { 15, 40 }, { 0, 1 } }, 0, 1 },
    { 28, { { 0, 1 }, { 0, 1 } }, 7, 20 },
    { 29, { { 17, 50 }, { 0, 1 } }, 0, 1 },
    { 30, { { 21, 20 }, { 0, 1 } }, 13, 140 },
    { 31, { { 18, 40 }, { 0, 1 } }, 0, 1 },
    { 32, { { 16, 20 }, { 0, 1 } }, 1, 100 },
    { 33, { { 20, 99 }, { 0, 1 } }, 0, 1 },
    { 34, { { 21, 99 }, { 0, 1 } }, 0, 1 },
    { 35, { { 22, 99 }, { 0, 1 } }, 0, 1 },
    { 36, { { 23, 99 }, { 0, 1 } }, 0, 1 },
    { 37, { { 25, 50 }, { 0, 1 } }, 0, 1 },
    { 38, { { 26, 99 }, { 0, 1 } }, 0, 1 },
    { 39, { { 27, 99 }, { 0, 1 } }, 0, 1 },
    { 40, { { 0, 1 }, { 0, 1 } }, 7, 40 },
    { 41, { { 30, 50 }, { 0, 1 } }, 0, 1 },
    { 42, { { 19, 40 }, { 0, 1 } }, 7, 15 },
    { 43, { { 24, 99 }, { 0, 1 } }, 0, 1 },
    { 44, { { 37, 99 }, { 0, 1 } }, 0, 1 },
    { 45, { { 29, 99 }, { 0, 1 } }, 0, 1 },
    { 46, { { 41, 99 }, { 0, 1 } }, 0, 1 },
    { 47, { { 37, 40 }, { 31, 40 } }, 0, 1 },
    { 48, { { 42, 99 }, { 0, 1 } }, 0, 1 },
    { 49, { { 36, 40 }, { 41, 40 } }, 0, 1 },
    { 50, { { 44, 40 }, { 49, 40 } }, 0, 1 },
    { 51, { { 45, 40 }, { 38, 40 } }, 0, 1 },
    { 52, { { 47, 99 }, { 43, 99 } }, 0, 1 },
};
Evolution *STFGTREP_evolutions[] = {
    D_80087128, D_800873E8, D_800876A8, D_80087968,
    D_80087C28, D_80087EE8, D_800881A8, D_80088468,
};
s32 STFGTREP_animations[][7] = {
    { 7, 8, 9, 10, 9, 8, -1 },
    { 14, 15, 16, 15, -1, -1, -1 },
    { 11, 12, 13, 12, -1, -1, -1 },
    { 3, 4, 5, 6, 5, 4, -1 },
    { 25, 26, 27, 28, 27, 26, -1 },
    { 0, 1, 2, 1, -1, -1, -1 },
    { 17, 18, 19, 20, 19, 18, -1 },
    { 21, 22, 23, 24, 23, 22, -1 },
};
FightReportFuncs STFGTREP_funcs = {
    STFGTREP_loadFiles, STFGTREP_filesLoading, STFGTREP_startFade, STFGTREP_updateFade,
    STFGTREP_startLerp, STFGTREP_updateLerp, STFGTREP_addExp, func_80085A38,
    STFGTREP_addDigimonExp, STFGTREP_addSkill, STFGTREP_learnSkill, STFGTREP_getDigimonExp,
};
s32 STFGTREP_levelExp[] = {
    0, 50, 800, 3000,
};
s32 STFGTREP_vitalCuts[] = {
    0, 5, 10, 15,
};
s32 STFGTREP_vitalRandom[] = {
    -4, -3, -2, -1,
    0, 1, 2, 3,
    4,
};
s32 STFGTREP_statGains[][9] = {
    { 2, 3, 4, 6, 8, 10, 12, 13, 14 },
    { 1, 2, 3, 4, 6, 8, 9, 10, 11 },
    { 0, 1, 3, 4, 4, 4, 5, 7, 8 },
    { 0, 1, 1, 2, 3, 4, 5, 5, 6 },
    { 0, 0, 1, 2, 2, 2, 3, 4, 4 },
    { 0, 0, 1, 1, 1, 1, 1, 2, 2 },
};
s32 STFGTREP_resistGains[] = {
    0, 0, 0, 1,
    1, 1, 2, 2,
};
