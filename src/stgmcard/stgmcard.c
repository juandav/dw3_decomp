#include "stgmcard.h"

extern MemCardScreenFuncs STGMCARD_funcs;
extern SaveIcon STGMCARD_saveIcon;

void func_800833A0();
void func_80082E28();
void func_80082904();
void func_80086BA0();
void func_80083B10();

Task *func_80087174(void);
Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);
void func_800844DC(MemCardSaves *saves, MemCardSavesWindows *win);
void func_80086E5C();
extern MemCardWindowSpec D_800876BC[];
extern s32 D_80087838[][7];
extern s32 D_80087918[];
extern s32 D_80087938[];
extern s32 STGMCARD_errorTexts[]; /* the texts of the results, by count */
extern s32 D_80087970[];
extern MemCardModeEntry D_800879D8[];

void STGMCARD_updateScene(MemCardScene *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x5000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 2, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        children[0] = (Task *)func_80087174();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STGMCARD_start(void) {
    return createTask(STGMCARD_updateScene, sizeof(MemCardScene), 4);
}

void STGMCARD_startFader(ScreenFade *task, s32 fadeIn, s32 duration) {
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

void STGMCARD_drawFader(ScreenFade *task) {
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

void STGMCARD_updateFader(ScreenFade *task) {
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
        STGMCARD_drawFader(task);
        break;
    case 3:
        break;
    }
}

ScreenFade *STGMCARD_createFader(void) {
    ScreenFade *task = createTask(STGMCARD_updateFader, sizeof(ScreenFade), 0);

    task->start = STGMCARD_startFader;
    task->layerId = 0x1000;
    task->depth = 0;
    return task;
}

void STGMCARD_showInfo(MemCardInfo *info) {
    info->setSubstate(info, 1);
}

void STGMCARD_hideInfo(MemCardInfo *info) {
    TextWindow **windows;
    s32 i;

    info->setSubstate(info, 2);
    windows = info->children;
    for (i = 0; i < info->childCount; i++, windows++) {
        if (*windows != NULL) {
            (*windows)->setVisible(*windows, 0);
        }
    }
}

/* Fills the details window with the selected save, or hides it */
void func_80082904(MemCardInfo *info) {
    MemCardSave *save;
    TextWindow **windows;
    TextWindow **w;
    s32 *partners;
    s32 i;

    save = &info->saves->file.saves[STGMCARD_funcs.slot];
    windows = info->children;
    if (info->shown == 0) {
        for (i = 0, w = windows; i < info->childCount; i++, w++) {
            (*w)->setVisible(*w, 0);
        }
    } else if (save->name[0] == 0) {
        for (i = 0, w = windows; i < info->childCount; i++, w++) {
            (*w)->setString(*w, FILE_CACHE.load(TEXT_FILE(0x79)), D_800876BC[i].unk0);
            if (D_800876BC[i].unk10 != 0) {
                (*w)->setNumber(*w, 1, 0);
                (*w)->setRightAlign(*w, 1);
                (*w)->setPos(*w, D_800876BC[i].x, D_800876BC[i].y);
            }
        }
    } else {
        windows[0]->setString(windows[0], save, -1);
        windows[1]->setString(windows[1], FILE_CACHE.load(TEXT_FILE(0xAA)), save->unk18);
        windows[2]->setString(windows[2], FILE_CACHE.load(TEXT_FILE(0x95)), save->unk1C);
        for (i = 0; i < 2; i++) {
            windows[i + 3]->setString(windows[i + 3], FILE_CACHE.load(TEXT_FILE(0x79)), 0x15);
        }
        windows[5]->setNumber(windows[5], 0, save->money);
        windows[5]->setRightAlign(windows[5], 1);
        windows[12]->setNumber(windows[12], 0, save->time.hours);
        windows[13]->setNumber(windows[13], 0, save->time.minutes);
        windows[14]->setNumber(windows[14], 0, save->time.seconds);
        for (i = 0, w = &windows[12]; i < 3; i++, w++) {
            (*w)->setRightAlign(*w, 1);
        }
        if (save->time.minutes < 10) {
            windows[17]->setNumber(windows[17], 0, 0);
            windows[17]->setRightAlign(windows[17], 1);
            windows[17]->setPos(windows[17], 0x111, 0xB2);
        } else {
            windows[17]->setVisible(windows[17], 0);
        }
        if (save->time.seconds < 10) {
            windows[18]->setNumber(windows[18], 0, 0);
            windows[18]->setRightAlign(windows[18], 1);
            windows[18]->setPos(windows[18], 0x124, 0xB2);
        } else {
            windows[18]->setVisible(windows[18], 0);
        }
        for (i = 0; i < 2; i++) {
            windows[i + 15]->setString(windows[i + 15], FILE_CACHE.load(TEXT_FILE(0x79)), 0x13);
        }
        partners = info->saves->file.saves[STGMCARD_funcs.slot].partners;
        for (i = 0; i < 3; i++) {
            windows[i + 6]->setString(windows[i + 6], FILE_CACHE.load(TEXT_FILE(0x79)), 0x14);
            if (partners[i] - 3 < 0) {
                windows[i + 9]->setString(windows[i + 9], FILE_CACHE.load(TEXT_FILE(0x79)), 0x23);
            } else {
                windows[i + 9]->setNumber(windows[i + 9], 0, save->levels[i]);
            }
            windows[i + 9]->setRightAlign(windows[i + 9], 1);
            info->frames[i] = 0;
        }
        info->time = 0;
    }
}

/* The details window's task: creates its text windows, fades it in and out,
   and draws the selected save's partners and frame */
void func_80082E28(MemCardInfo *info) {
    SpriteDrawer sprite;
    TextWindow **windows;
    s32 *partners;
    s32 i;
    s32 j;

    switch (info->state) {
    case TASK_INIT:
    default:
        info->nextState(info);
#if VERSION_US
        D_800876BC[0].unk0 = 0x21;
#elif VERSION_EU
        D_800876BC[0].unk0 = LANGUAGE != 0 ? 0x21 : 0x20;
#endif
        windows = info->children;
        for (i = 0; i < info->childCount; i++, windows++) {
            if (*windows == NULL) {
                *windows = createTextWindow(info->layer, D_800876BC[i].type, D_800876BC[i].x, D_800876BC[i].y);
            }
            /* the match depends on the unsigned compare, which GCC makes a sltiu */
            if (i < 3U) {
                (*windows)->setPalette(*windows, 1);
            }
        }
        info->fade.duration = 8;
        break;
    case TASK_RUN:
        switch (info->substate) {
        case 0:
        default:
            break;
        case 1:
            switch (info->step) {
            case 0:
            default:
                STGMCARD_funcs.startFade(&info->fade, 1);
                info->step++;
                break;
            case 1:
                if (STGMCARD_funcs.updateFade(&info->fade) != 0) {
                    info->setSubstate(info, 0);
                }
                break;
            }
            break;
        case 2:
            switch (info->step) {
            case 0:
            default:
                STGMCARD_funcs.startFade(&info->fade, 0);
                info->shown = 0;
                func_80082904(info);
                info->step++;
                break;
            case 1:
                if (STGMCARD_funcs.updateFade(&info->fade) != 0) {
                    info->unk5C = 0;
                    info->setSubstate(info, 0);
                }
                break;
            }
            break;
        }
        if (info->unk5C == 0) {
            break;
        }
        initSpriteDrawer(&sprite);
        sprite.setTexture(0x280, 0);
        sprite.setLayerId(info->layer, info->depth);
        if (info->fade.level != 0x1000) {
            sprite.setScale(0x1000, info->fade.level, 0x1000);
            sprite.setPivot(160, 148);
        }
        partners = info->saves->file.saves[STGMCARD_funcs.slot].partners;
        if (GFX.funcs.getTime() - info->time >= 13) {
            info->time = GFX.funcs.getTime();
            for (j = 0; j < 3; j++) {
                if (partners[j] - 3 >= 0) {
                    info->frames[j]++;
                    if (info->frames[j] >= 8) {
                        info->frames[j] = 0;
                    }
                    if (D_80087838[partners[j] - 3][info->frames[j]] == -1) {
                        info->frames[j] = 0;
                    }
                }
            }
        }
        for (j = 0; j < 3; j++) {
            if (partners[j] - 3 >= 0) {
                sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), D_80087838[partners[j] - 3][info->frames[j]], 154 + j * 52, 133);
            }
        }
        sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), 36, 16, 116);
        sprite.setLayerId(info->layer, info->depth - 1);
        sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), 37, 16, 116);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

MemCardInfo *STGMCARD_createInfo(MemCardSaves *saves) {
    MemCardInfo *info = createTask(func_80082E28, sizeof(MemCardInfo), 0x4C);

    info->show = STGMCARD_showInfo;
    info->hide = STGMCARD_hideInfo;
    info->refresh = func_80082904;
    info->layer = 0x1000;
    info->saves = saves;
    info->depth = 1;
    return info;
}

void STGMCARD_resetPanel(MemCardPanel *panel) {
    panel->substate = 0;
    panel->duration = 0;
    panel->rate = 0;
    panel->done = 0;
    panel->scale.vx = 0;
    panel->scale.vz = 0x1000;
    panel->scale.vy = 0x1000;
    panel->pivotX = panel->x;
    panel->pivotY = panel->y;
}

void STGMCARD_startPanel(MemCardPanel *panel, s32 substate, s32 duration) {
    panel->substate = substate;
    panel->duration = duration;
    panel->rate = 0;
}

void STGMCARD_setPanelTopColor(MemCardPanel *panel, u8 r, u8 g, u8 b) {
    panel->top.r = r;
    panel->top.g = g;
    panel->top.b = b;
    panel->top.cd = 0;
}

void STGMCARD_setPanelBottomColor(MemCardPanel *panel, u8 r, u8 g, u8 b) {
    panel->bottom.r = r;
    panel->bottom.g = g;
    panel->bottom.b = b;
    panel->bottom.cd = 0;
}

void STGMCARD_setPanelPos(MemCardPanel *panel, s32 x, s32 y) {
    panel->x = x;
    panel->y = y;
}

/* The panel's task: opens it by scaling it horizontally, then draws it as a
   gradient with a sprite */
void func_800833A0(MemCardPanel *panel) {
    SVECTOR out[4];
    SVECTOR in[4];
    SpriteDrawer sprite;
    Layer *layer;
    u_long *ot;
    POLY_G4 *poly;
    s32 i;

    switch (panel->state) {
    case TASK_INIT:
    default:
        panel->nextState(panel);
        STGMCARD_resetPanel(panel);
        break;
    case TASK_RUN:
        if (panel->duration == 0) {
            break;
        }
        switch (panel->substate) {
        case 0:
        default:
            return;
        case 1:
            if (panel->rate == 0) {
                panel->rate = 0x1000 / panel->duration;
            }
            panel->scale.vx += panel->rate;
            if (panel->scale.vx > 0xF33) {
                panel->scale.vx = 0xF33;
            }
            break;
        case 2:
            if (panel->rate == 0) {
                panel->rate = 0x1000 / panel->duration;
            }
            panel->scale.vx += panel->rate;
            if (panel->scale.vx > 0x1000) {
                panel->scale.vx = 0x1000;
                panel->done = 1;
            }
            break;
        }
        if (panel->scale.vx == 0) {
            break;
        }
        layer = GFX.funcs.getLayer(panel->layer);
        ot = (u_long *)layer->getOtEntry(layer, panel->depth);
        RotMatrixYXZ_gte(&panel->rot, &panel->matrix);
        ScaleMatrix(&panel->matrix, &panel->scale);
        poly = GFX.funcs.getPrim();
        setlen(poly, 8);
        poly->code = 0x38;
        poly->r0 = panel->top.r;
        poly->g0 = panel->top.g;
        poly->b0 = panel->top.b;
        poly->r1 = panel->bottom.r;
        poly->g1 = panel->bottom.g;
        poly->b1 = panel->bottom.b;
        poly->r2 = panel->top.r;
        poly->g2 = panel->top.g;
        poly->b2 = panel->top.b;
        poly->r3 = panel->bottom.r;
        poly->g3 = panel->bottom.g;
        poly->b3 = panel->bottom.b;
        in[0].vx = in[2].vx = panel->x - panel->pivotX;
        in[1].vx = in[3].vx = in[0].vx + panel->w;
        in[0].vy = in[1].vy = panel->y - panel->pivotY;
        in[2].vy = in[3].vy = in[0].vy + panel->h;
        in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
        for (i = 0; i < 4; i++) {
            ApplyMatrixSV(&panel->matrix, &in[i], &out[i]);
            out[i].vx += panel->pivotX;
            out[i].vy += panel->pivotY;
        }
        poly->x0 = out[0].vx;
        poly->y0 = out[0].vy;
        poly->x1 = out[1].vx;
        poly->y1 = out[1].vy;
        poly->x2 = out[2].vx;
        poly->y2 = out[2].vy;
        poly->x3 = out[3].vx;
        poly->y3 = out[2].vy; /* the same as out[3].vy unless the panel is rotated */
        addPrim(ot, poly);
        GFX.funcs.setPrim(poly + 1);
        initSpriteDrawer(&sprite);
        sprite.setLayerId(panel->layer, panel->depth);
        sprite.setTexture(0x280, 0);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_GMCARD_SHEET << 16), 38, 204, 192);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

MemCardPanel *STGMCARD_createPanel(s32 x, s32 y, s32 w, s32 h) {
    MemCardPanel *panel = createTask(func_800833A0, sizeof(MemCardPanel), 0);

    panel->reset = STGMCARD_resetPanel;
    panel->start = STGMCARD_startPanel;
    panel->setTopColor = STGMCARD_setPanelTopColor;
    panel->setBottomColor = STGMCARD_setPanelBottomColor;
    panel->setPos = STGMCARD_setPanelPos;
    panel->layer = 0x1000;
    panel->depth = 1;
    panel->x = x;
    panel->y = y;
    panel->w = w;
    panel->h = h;
    return panel;
}

void func_8008385C(MemCardMenu *menu) {
    TextWindow **windows = menu->children;

    STGMCARD_funcs.startLerp(&menu->lerps[1], -0x55, 0, 10);
    windows[0]->setNumber(windows[0], 1, menu->saves->port + 1);
#if VERSION_EU
    windows[0]->setVisible(windows[0], 0);
#endif
    menu->substate = 1;
}

void func_800838CC(MemCardMenu *menu, s32 arg) {
    STGMCARD_funcs.startLerp(&menu->lerps[2], 0, 0x2F, 8);
    menu->substate = 5;
    STGMCARD_funcs.slot = arg;
    STGMCARD_funcs.unk8 = 0;
}

void func_80083934(MemCardMenu *menu) {
    STGMCARD_funcs.startLerp(&menu->lerps[1], 0, -0x55, 5);
    menu->substate = 4;
}

void func_80083978(MemCardMenu *menu) {
    STGMCARD_funcs.startLerp(&menu->lerps[3], STGMCARD_funcs.unk8 * 0x44, STGMCARD_funcs.slot * 0x44, 5);
    menu->substate = 7;
}

void func_800839D8(MemCardMenu *menu) {
    STGMCARD_funcs.startLerp(&menu->lerps[0], 0xDE, 0, 10);
    menu->substate = 2;
}

void func_80083A1C(MemCardMenu *menu) {
    STGMCARD_funcs.startLerp(&menu->lerps[0], 0, 0xDE, 5);
    menu->substate = 3;
}

void STGMCARD_resetMenu(MemCardMenu *menu) {
    menu->substate = 0;
    menu->unkCC = 0;
    STGMCARD_funcs.slot = 0;
    STGMCARD_funcs.unk8 = 0;
    STGMCARD_funcs.startLerp(&menu->lerps[0], 0xDE, 0, 10);
    STGMCARD_funcs.startLerp(&menu->lerps[1], -0x55, 0, 10);
    STGMCARD_funcs.startLerp(&menu->lerps[2], 0, 0x2F, 8);
    STGMCARD_funcs.startLerp(&menu->lerps[3], -1, 0, 1);
    menu->lerps[3].value = 0;
}

/* The save picker's task: slides in and out, moves between the first three
   saves with left and right, and draws each one's lead partner */
void func_80083B10(MemCardMenu *menu, TextWindow **windows) {
    SpriteDrawer sprite;
    s32 prev;
    s32 i;

    switch (menu->state) {
    case TASK_INIT:
    default:
        menu->nextState(menu);
        STGMCARD_resetMenu(menu);
        if (*windows == NULL) {
            *windows = createTextWindow(menu->layer, 1, 0x15, menu->lerps[1].value + 0x18);
        }
        (*windows)->setString(*windows, FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 3);
        (*windows)->setNumber(*windows, 1, menu->saves->port + 1);
#if VERSION_EU
        (*windows)->setVisible(*windows, 0);
#endif
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    case TASK_RUN:
        switch (menu->substate) {
        case 0:
            break;
        case 1:
            if (STGMCARD_funcs.updateLerp(&menu->lerps[1]) != 0) {
                menu->substate = 0;
                menu->unkCC = 1;
            }
            break;
        case 2:
            if (STGMCARD_funcs.updateLerp(&menu->lerps[0]) != 0) {
                menu->substate = 0;
                menu->unkCC = 2;
            }
            break;
        case 3:
            if (STGMCARD_funcs.updateLerp(&menu->lerps[0]) != 0) {
                menu->substate = 0;
                menu->unkCC = 3;
            }
            break;
        case 4:
            if (STGMCARD_funcs.updateLerp(&menu->lerps[1]) != 0) {
                STGMCARD_resetMenu(menu);
            }
            break;
        case 5:
            if (STGMCARD_funcs.updateLerp(&menu->lerps[2]) != 0) {
                func_80083978(menu);
            }
            break;
        case 6:
            if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
                prev = STGMCARD_funcs.slot;
                STGMCARD_funcs.unk8 = prev;
                STGMCARD_funcs.slot = prev - 1;
                if (STGMCARD_funcs.slot < 0) {
                    STGMCARD_funcs.slot = 0;
                }
                if (STGMCARD_funcs.slot != prev) {
                    menu->saves->refresh(menu->saves);
                    func_80083978(menu);
                    SOUND.playSound(0x4001B);
                }
            } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
                prev = STGMCARD_funcs.slot;
                STGMCARD_funcs.slot = prev + 1;
                STGMCARD_funcs.unk8 = prev;
                if (STGMCARD_funcs.slot >= 3) {
                    STGMCARD_funcs.slot = 2;
                }
                if (STGMCARD_funcs.slot != prev) {
                    menu->saves->refresh(menu->saves);
                    func_80083978(menu);
                    SOUND.playSound(0x4001B);
                }
            }
            break;
        case 7:
            if (STGMCARD_funcs.updateLerp(&menu->lerps[3]) != 0) {
                menu->substate = 6;
            }
            break;
        }
        initSpriteDrawer(&sprite);
        sprite.setLayerId(menu->layer, menu->depth);
        sprite.setTexture(0x280, 0);
        i = 0;
        if (GFX.funcs.getTime() - menu->blinkTime >= 3) {
            menu->blinkTime = GFX.funcs.getTime();
            if (menu->blinkDown == 0) {
                if (++menu->blinkFrame >= 12) {
                    menu->blinkFrame = 10;
                    menu->blinkDown = 1;
                }
            } else {
                if (--menu->blinkFrame <= 0) {
                    menu->blinkFrame = 0;
                    menu->blinkDown = 0;
                }
            }
        }
        sprite.setClutRow(menu->blinkFrame);
        sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), 0x23, menu->lerps[2].value + 0x30 + menu->lerps[3].value, menu->lerps[1].value + 0x12);
        sprite.setClutRow(0);
        sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), 0x20, 0, menu->lerps[1].value + 0x10);
        (*windows)->setPos(*windows, 0x15, menu->lerps[1].value + 0x18);
        for (i = 0; i < 3; i++) {
            if (menu->saves->file.saves[i].name[0] != 0) {
                sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), D_80087918[menu->saves->file.saves[i].partners[0] - 3], D_80087938[i] + menu->lerps[0].value, 0x23);
            }
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_GMCARD_SHEET << 16), 0x22, menu->lerps[0].value + 0x62, 0x20);
        break;
    }
}

MemCardMenu *STGMCARD_createMenu(MemCardSaves *saves) {
    MemCardMenu *menu = createTask(func_80083B10, sizeof(MemCardMenu), 4);

    menu->reset = STGMCARD_resetMenu;
    menu->unkE0 = func_8008385C;
    menu->unkE4 = func_800838CC;
    menu->unkE8 = func_80083934;
    menu->unkEC = func_800839D8;
    menu->unkF0 = func_80083A1C;
    menu->layer = 0x1000;
    menu->depth = 2;
    menu->saves = saves;
    return menu;
}

void STGMCARD_showPort(MemCardSaves *saves, MemCardSavesWindows *win, s32 show) {
    if (show) {
        win->windows[4]->setString(win->windows[4], FILE_CACHE.load(TEXT_FILE(0x79)), 0x28);
        win->windows[4]->setNumber(win->windows[4], 1, saves->port + 1);
    } else {
        win->windows[4]->setVisible(win->windows[4], 0);
    }
}

void func_80084230(MemCardSaves *saves, MemCardSavesWindows *win) {
    saves->substate = 100;
    saves->choice = 0;
    saves->count--;
    if (win->windows[1] != NULL) {
        win->windows[1]->setVisible(win->windows[1], 0);
    }
    if (win->windows[2] != NULL) {
        win->windows[2]->setVisible(win->windows[2], 0);
    }
    if (win->windows[3] != NULL) {
        win->windows[3]->setVisible(win->windows[3], 0);
    }
    if (win->cursor != NULL) {
        win->cursor->setVisible(win->cursor, 0);
    }
    if (win->panel != NULL) {
        win->panel->reset(win->panel);
    }
}

void func_80084308(MemCardSaves *saves, MemCardSavesWindows *win) {
    win->windows[1]->setVisible(win->windows[1], 0);
    win->panel->reset(win->panel);
    saves->substate = 90;
    saves->step = 100;
    win->menu->substate = 0;
}

void STGMCARD_refreshSaves(MemCardSaves *saves) {
    MemCardSavesWindows *win = saves->children;

    win->info->refresh(win->info);
}

void STGMCARD_hideSaves(MemCardSaves *saves) {
    MemCardSavesWindows *win = saves->children;

    if (win->windows[0] != NULL) {
        win->windows[0]->setVisible(win->windows[0], 0);
    }
    if (win->windows[4] != NULL) {
        win->windows[4]->setVisible(win->windows[4], 0);
    }
    if (win->windows[1] != NULL) {
        win->windows[1]->setVisible(win->windows[1], 0);
    }
    if (win->windows[2] != NULL) {
        win->windows[2]->setVisible(win->windows[2], 0);
    }
    if (win->windows[3] != NULL) {
        win->windows[3]->setVisible(win->windows[3], 0);
    }
    if (win->cursor != NULL) {
        win->cursor->setVisible(win->cursor, 0);
    }
    if (win->panel != NULL) {
        win->panel->reset(win->panel);
    }
    saves->setState(saves, 2);
}

/*
 * The save list's states (saves->substate): picks the port, reads the card's
 * info section, lets the menu pick a slot, then loads or saves it. A failed
 * operation leaves its result in count and goes to 100, which shows
 * STGMCARD_errorTexts[count] and can format the card (110) or create the save
 * file (120). 400 waits for the card and goes on to step.
 * Match depends on the separate variables: result lives across calls, status,
 * check, member and j each keep their own register.
 */
void func_800844DC(MemCardSaves *saves, MemCardSavesWindows *win) {
    MemCardSave *save;
    s32 prev;
    s32 result;
    s32 j;
    s32 blocks;
    s32 ask;
    s32 i;
    s32 status;
    s32 member;
    s32 check;

    switch (saves->substate) {
    case 0:
    default:
        win->unk0->setDepth(win->unk0, 1);
        if (saves->screen->saving == 0) {
            win->unk0->setString(win->unk0, FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 1);
        } else {
            win->unk0->setString(win->unk0, FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0xE);
        }
        if (win->info == NULL) {
            win->info = STGMCARD_createInfo(saves);
        }
        saves->substate++;
    case 1:
        if (STGMCARD_funcs.updateLerp(&saves->slide[1]) != 0) {
            win->windows[0]->setVisible(win->windows[0], 0);
            if (saves->screen->saving == 0) {
                win->windows[4]->setString(win->windows[4], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 2);
            } else {
                win->windows[4]->setString(win->windows[4], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0xF);
            }
            win->windows[1]->setDepth(win->windows[1], 1);
            win->windows[1]->setString(win->windows[1], FILE_CACHE.load(TEXT_FILE(0x79)), 0x1D);
            win->windows[2]->setString(win->windows[2], FILE_CACHE.load(TEXT_FILE(0x79)), 3);
            win->windows[2]->setNumber(win->windows[2], 1, 1);
            win->windows[3]->setString(win->windows[3], FILE_CACHE.load(TEXT_FILE(0x79)), 3);
            win->windows[3]->setNumber(win->windows[3], 1, 2);
            win->cursor->setVisible(win->cursor, 1);
            win->cursor->setPos(win->cursor, 0xC2, saves->port * 14 + 0xBD);
            saves->unk2844 = 1;
            saves->substate++;
        }
        win->unk0->setPos(win->unk0, saves->unk58[0] + (s16)(saves->slide[0].value + 200), saves->unk58[1] + (s16)(saves->slide[1].value + 9));
        break;
    case 2:
        prev = saves->port;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            saves->port = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            saves->port = 1;
        }
        if (prev != saves->port) {
            win->cursor->setPos(win->cursor, 0xC2, saves->port * 14 + 0xBD);
            SOUND.playSound(0x8004513E);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            win->windows[0]->setString(win->windows[0], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 4);
            STGMCARD_showPort(saves, win, 1);
            win->windows[1]->setVisible(win->windows[1], 0);
            win->windows[2]->setVisible(win->windows[2], 0);
            win->windows[3]->setVisible(win->windows[3], 0);
            win->cursor->setVisible(win->cursor, 0);
            if (win->panel == NULL) {
                win->panel = STGMCARD_createPanel(0xCD, 0xC1, 0x62, 0xA);
            }
            win->panel->setTopColor(win->panel, 0x7F, 0x32, 0xF2);
            win->panel->setBottomColor(win->panel, 0xD1, 0x2F, 0xDE);
            saves->substate = 10;
            SOUND.playSound(0x8004503C);
            saves->unk2844 = 0;
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            saves->hide(saves);
            saves->unk2844 = 0;
            saves->screen->step = 1;
        }
        break;
    case 10:
        if (win->panel->substate == 0) {
            win->panel->start(win->panel, 1, 0x4C);
        }
        status = saves->count = MEMCARD_SYSTEM.funcs.accept(saves->port);
        if (status != 0) {
            if (status == 1 || status - 1 == 3) {
                saves->substate++;
            } else {
                win->panel->start(win->panel, 2, 0x14);
                saves->substate += 2;
            }
        }
        break;
    case 11:
        status = saves->count = MEMCARD_SYSTEM.funcs.list(saves->port);
        if (status != 0) {
            win->panel->start(win->panel, 2, 0x14);
            saves->substate++;
        }
        break;
    case 12:
        if (win->panel->done != 0) {
            if (saves->count == 1) {
                saves->substate = 20;
            } else {
                func_80084230(saves, win);
            }
        }
        break;
    case 20:
        if (win->panel->done != 0) {
            win->windows[0]->setString(win->windows[0], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 5);
            STGMCARD_showPort(saves, win, 1);
            win->panel->reset(win->panel);
            win->panel->start(win->panel, 1, 0x4C);
            saves->substate++;
        }
    case 21:
        status = saves->count = MEMCARD_SYSTEM.funcs.read(saves->port, (u8 *)STGMCARD_funcs.infoBuf, sizeof(MemCardFile), 1);
        if (status != 0) {
            win->panel->start(win->panel, 2, 0x14);
            saves->substate++;
        }
        break;
    case 22:
        if (win->panel->done != 0) {
            if (saves->count == 1) {
                if (STGMCARD_funcs.infoBuf->magic != MEMCARD_FILE_MAGIC) {
                    HEAP.zero(STGMCARD_funcs.infoBuf, 0x44);
                    STGMCARD_funcs.infoBuf->magic = MEMCARD_FILE_MAGIC;
                    STGMCARD_funcs.infoBuf->version = MEMCARD_SAVE_VERSION;
                } else if (MEMCARD_SYSTEM.funcs.computeChecksum((u8 *)&STGMCARD_funcs.infoBuf->magic, sizeof(MemCardFile) - 4) & ~STGMCARD_funcs.infoBuf->checksum) {
                    saves->count = 9;
                    func_80084230(saves, win);
                    break;
                } else {
                    saves->file = *STGMCARD_funcs.infoBuf;
                    STGMCARD_funcs.unk0 = STGMCARD_funcs.infoBuf->last;
                }
                win->windows[0]->setVisible(win->windows[0], 0);
                win->windows[4]->setVisible(win->windows[4], 0);
                win->panel->reset(win->panel);
                saves->substate = 30;
            } else {
                func_80084230(saves, win);
            }
        }
        break;
    case 30:
        win->windows[0]->setVisible(win->windows[0], 0);
        win->windows[4]->setVisible(win->windows[4], 0);
        if (win->menu->unkCC != 5) {
            win->menu->reset(win->menu);
        }
        if (win->info != NULL) {
            win->info->show(win->info);
        }
        saves->substate++;
        break;
    case 31:
        if (win->menu->substate == 0) {
            if (win->menu->unkCC == 0) {
                win->menu->unkE0(win->menu);
            } else if (win->menu->unkCC == 1) {
                win->menu->unkEC(win->menu);
            } else if (win->menu->unkCC == 2) {
                win->menu->unkE4(win->menu, STGMCARD_funcs.unk0);
                saves->substate++;
            }
        }
        break;
    case 32:
        if (win->menu->substate == 6) {
            if (saves->screen->saving == 0) {
                win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 6);
            } else {
                win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x10);
            }
            win->info->unk5C = 1;
            win->info->shown = 1;
            win->info->refresh(win->info);
            saves->nextSubstate(saves);
            win->menu->substate = 6;
        }
        break;
    case 33:
        if (win->menu->substate == 6) {
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x4001C);
                saves->substate = 400;
                win->menu->substate = 0;
                if (saves->screen->saving == 0) {
                    if (STGMCARD_funcs.infoBuf->saves[STGMCARD_funcs.slot].name[0] != 0) {
                        saves->step = 40;
                        saves->choice = 0;
                        win->windows[1]->setString(win->windows[1], FILE_CACHE.load(TEXT_FILE(0x79)), 7);
                        win->windows[2]->setString(win->windows[2], FILE_CACHE.load(TEXT_FILE(0x79)), 0x16);
                        win->windows[3]->setString(win->windows[3], FILE_CACHE.load(TEXT_FILE(0x79)), 0x17);
                        win->cursor->setVisible(win->cursor, 1);
                        saves->unk2844 = 1;
                        win->cursor->setPos(win->cursor, 0xC2, saves->choice * 14 + 0xBD);
                    } else {
                        saves->step = 50;
                    }
                } else {
                    saves->step = 70;
                }
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                win->menu->substate = 0;
                saves->substate = 90;
                saves->step = 1;
            } else {
                status = MEMCARD_SYSTEM.funcs.check(saves->port);
                if (status != 0) {
                    if (status != 1) {
                        saves->count = status - 1;
                        func_80084308(saves, win);
                    }
                }
            }
        }
        break;
    case 90:
        if (win->menu->substate == 0) {
            switch (win->menu->unkCC) {
            case 3:
                win->menu->unkE8(win->menu);
                saves->substate = saves->step;
                saves->step = saves->counter;
                saves->counter = 0;
                break;
            case 2:
                win->info->hide(win->info);
                win->menu->unkF0(win->menu);
                break;
            }
        }
        break;
    case 600:
        if (win->menu->substate == 0) {
            if (win->menu->unkCC == 2) {
                win->info->hide(win->info);
                win->menu->unkF0(win->menu);
            } else if (win->menu->unkCC == 3) {
                win->menu->unkE8(win->menu);
                saves->substate++;
            }
        }
        break;
    case 601:
        saves->hide(saves);
        break;
    case 70:
        if (STGMCARD_funcs.infoBuf->saves[STGMCARD_funcs.slot].name[0] == 0) {
            win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x18);
            saves->unk2838 = 1;
            saves->substate = 501;
            saves->step = 32;
            saves->unk2848 = 1;
        } else {
            win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x11);
            win->panel->start(win->panel, 1, MEMCARD_LOAD_FRAMES);
            saves->substate++;
        }
        break;
    case 71:
        status = saves->count = MEMCARD_SYSTEM.funcs.read(saves->port, (u8 *)STGMCARD_funcs.dataBuf, sizeof(GameSave), STGMCARD_funcs.slot + 2);
        if (status != 0) {
            if (status == 1) {
                if (MEMCARD_SYSTEM.funcs.computeChecksum(&STGMCARD_funcs.dataBuf->unk0[4], sizeof(GameSave) - 4) & ~STGMCARD_funcs.dataBuf->unk0[0]) {
                    saves->count = 8;
                    func_80084308(saves, win);
                } else if (STGMCARD_funcs.dataBuf->unk0[2] != MEMCARD_SAVE_VERSION && saves->screen->saving != 0) {
                    saves->count = 8;
                    func_80084308(saves, win);
                } else {
                    *(GameSave *)&GAME = *(GameSave *)STGMCARD_funcs.dataBuf;
                    win->panel->start(win->panel, 2, 0x14);
                    saves->substate = 500;
                    win->menu->substate = 0;
                    saves->unk2848 = 0;
                }
            } else {
                saves->count = status - 1;
                func_80084308(saves, win);
            }
        }
        break;
    case 40:
        prev = saves->choice;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            saves->choice = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            saves->choice = 1;
        }
        if (prev != saves->choice) {
            win->cursor->setPos(win->cursor, 0xC2, saves->choice * 14 + 0xBD);
            SOUND.playSound(0x8004513E);
        }
        if (PAD_PRESSED(PAD_CROSS)) {
            win->windows[2]->setVisible(win->windows[2], 0);
            win->windows[3]->setVisible(win->windows[3], 0);
            win->cursor->setVisible(win->cursor, 0);
            SOUND.playSound(0x8004503C);
            /* match depends on the 400 going through status */
            status = 400;
            saves->unk2844 = 0;
            saves->substate = status;
            if (saves->choice == 0) {
                saves->step = 50;
            } else {
                saves->step = 32;
                win->menu->substate = 6;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            win->windows[2]->setVisible(win->windows[2], 0);
            win->windows[3]->setVisible(win->windows[3], 0);
            win->cursor->setVisible(win->cursor, 0);
            SOUND.playSound(0x800450BD);
            saves->substate = 400;
            saves->unk2844 = 0;
            saves->step = 32;
            win->menu->substate = 6;
        } else {
            result = MEMCARD_SYSTEM.funcs.check(saves->port);
            if (result != 0) {
                if (result != 1) {
                    win->windows[2]->setVisible(win->windows[2], 0);
                    win->windows[3]->setVisible(win->windows[3], 0);
                    win->cursor->setVisible(win->cursor, 0);
                    saves->unk2844 = 0;
                    saves->count = result - 1;
                    func_80084308(saves, win);
                }
            }
        }
        break;
    case 50:
        win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 8);
        win->panel->start(win->panel, 1, MEMCARD_SAVE_FRAMES);
        saves->substate++;
        break;
    case 51:
        save = &STGMCARD_funcs.infoBuf->saves[STGMCARD_funcs.slot];
        *(GameSave *)STGMCARD_funcs.dataBuf = *(GameSave *)&GAME;
        STGMCARD_funcs.dataBuf->unk0[0] = MEMCARD_SYSTEM.funcs.computeChecksum(&STGMCARD_funcs.dataBuf->unk0[4], sizeof(GameSave) - 4);
        STGMCARD_funcs.dataBuf->unk0[2] = MEMCARD_SAVE_VERSION;
        strcpy(save->name, STGMCARD_funcs.dataBuf->name);
        save->unk18 = saves->screen->unk68;
        save->unk1C = saves->screen->unk6C;
        save->money = STGMCARD_funcs.dataBuf->money;
        save->time = *(PlayTime *)&STGMCARD_funcs.dataBuf->playFrames;
        for (i = 0; i < 3; i++) {
            member = GAME.funcs.getPartyMember(i);
            save->levels[i] = STGMCARD_funcs.dataBuf->partners[member].level;
            save->partners[i] = STGMCARD_funcs.dataBuf->partners[member].unlocked;
        }
        STGMCARD_funcs.infoBuf->last = STGMCARD_funcs.slot;
        STGMCARD_funcs.infoBuf->checksum = MEMCARD_SYSTEM.funcs.computeChecksum((u8 *)&STGMCARD_funcs.infoBuf->magic, sizeof(MemCardFile) - 4);
        saves->substate++;
        break;
    case 52:
        status = saves->count = MEMCARD_SYSTEM.funcs.write(saves->port, (u8 *)STGMCARD_funcs.infoBuf, sizeof(MemCardFile), 1);
        if (status != 0) {
            if (status == 1) {
                saves->substate++;
            } else {
                saves->count = status - 1;
                func_80084308(saves, win);
            }
        }
        break;
    case 53:
        status = saves->count = MEMCARD_SYSTEM.funcs.write(saves->port, (u8 *)STGMCARD_funcs.dataBuf, sizeof(GameSave), STGMCARD_funcs.slot + 2);
        if (status != 0) {
            if (status == 1) {
                win->panel->start(win->panel, 2, 0x14);
                saves->substate = 500;
            } else {
                saves->count = status - 1;
                func_80084308(saves, win);
            }
        }
        break;
    case 500:
        if (win->panel->done != 0) {
            if (saves->screen->saving == 0) {
                saves->file = *STGMCARD_funcs.infoBuf;
                saves->refresh(saves);
                win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 9);
                saves->step = 32;
            } else {
                win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x12);
                saves->step = 400;
                saves->substate++;
            }
            saves->substate++;
            win->panel->reset(win->panel);
            saves->unk2838 = 1;
        }
        break;
    case 501:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            saves->unk2838 = 0;
            saves->substate = saves->step;
            if (saves->screen->saving == 0) {
                saves->setStep(saves, 0);
                win->menu->substate = 6;
            } else {
                win->windows[1]->setVisible(win->windows[1], 0);
                saves->step = 600;
                if (saves->unk2848 != 0) {
                    win->menu->substate = 6;
                } else {
                    win->menu->substate = 0;
                }
            }
        } else {
            check = MEMCARD_SYSTEM.funcs.check(saves->port);
            if (check != 0) {
                if (check != 1) {
                    saves->unk2838 = 0;
                    saves->count = 1;
                    func_80084308(saves, win);
                }
            }
        }
        break;
    case 502:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            saves->unk2838 = 0;
            saves->substate = saves->step;
            win->windows[1]->setVisible(win->windows[1], 0);
            saves->step = 600;
            win->menu->substate = 0;
        }
        break;
    case 100:
        win->windows[0]->setString(win->windows[0], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), STGMCARD_errorTexts[saves->count]);
        STGMCARD_showPort(saves, win, 1);
        if (saves->screen->saving == 0) {
            if (saves->count == 4) {
                saves->choice = 1;
                ask = 1;
            } else if (saves->count == 5) {
                if (MEMCARD.fileCount != 0) {
                    blocks = 0;
                    for (j = 0; j < MEMCARD.fileCount; j++) {
                        blocks += MEMCARD.files[j].size / 0x2000;
                    }
                    if (blocks + 4 >= 16) {
                        win->windows[0]->setVisible(win->windows[0], 0);
                        saves->count = 7;
                        saves->substate = 100;
                        break;
                    }
                }
                ask = 1;
            } else {
                saves->unk2838 = 1;
                ask = 0;
                if (saves->count == 7) {
                    win->windows[0]->setNumber(win->windows[0], 1, 4);
                }
            }
            if (ask) {
                if (saves->count == 4) {
                    win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x19);
                } else {
                    win->windows[1]->setString(win->windows[1], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x1A);
                }
                win->windows[2]->setString(win->windows[2], FILE_CACHE.load(TEXT_FILE(0x79)), 0x16);
                win->windows[3]->setString(win->windows[3], FILE_CACHE.load(TEXT_FILE(0x79)), 0x17);
                win->cursor->setVisible(win->cursor, 1);
                saves->unk2844 = 1;
                win->cursor->setPos(win->cursor, 0xC2, saves->choice * 14 + 0xBD);
            }
        } else {
            saves->unk2838 = 1;
        }
        saves->substate++;
        break;
    case 101:
        if (saves->screen->saving == 0 && (u32)(saves->count - 4) < 2) {
            prev = saves->choice;
            if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                saves->choice = 0;
            } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                saves->choice = 1;
            }
            if (prev != saves->choice) {
                SOUND.playSound(0x8004513E);
                win->cursor->setPos(win->cursor, 0xC2, saves->choice * 14 + 0xBD);
            }
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x8004503C);
                win->windows[0]->setVisible(win->windows[0], 0);
                win->windows[4]->setVisible(win->windows[4], 0);
                win->windows[1]->setVisible(win->windows[1], 0);
                win->windows[2]->setVisible(win->windows[2], 0);
                win->windows[3]->setVisible(win->windows[3], 0);
                win->cursor->setVisible(win->cursor, 0);
                saves->substate = 400;
                saves->unk2844 = 0;
                if (saves->count == 4) {
                    if (saves->choice == 0) {
                        saves->step = 110;
                        win->windows[0]->setString(win->windows[0], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x1E);
                        STGMCARD_showPort(saves, win, 1);
                        win->panel->start(win->panel, 1, 0x90);
                    } else {
                        saves->step = 1;
                        win->panel->reset(win->panel);
                    }
                } else if (saves->choice == 0) {
                    saves->step = 120;
                    win->windows[0]->setString(win->windows[0], FILE_CACHE_LOAD[0](TEXT_FILE(0x79)), 0x1F);
                    STGMCARD_showPort(saves, win, 1);
                    win->panel->start(win->panel, 1, 0x90);
                } else {
                    saves->step = 1;
                    win->panel->reset(win->panel);
                }
            } else if (PAD_PRESSED(PAD_TRIANGLE)) {
                SOUND.playSound(0x800450BD);
                win->windows[0]->setVisible(win->windows[0], 0);
                win->windows[4]->setVisible(win->windows[4], 0);
                win->windows[1]->setVisible(win->windows[1], 0);
                win->windows[2]->setVisible(win->windows[2], 0);
                win->windows[3]->setVisible(win->windows[3], 0);
                win->cursor->setVisible(win->cursor, 0);
                saves->substate = 400;
                saves->unk2844 = 0;
                saves->step = 1;
                win->panel->reset(win->panel);
            }
            status = MEMCARD_SYSTEM.funcs.check(saves->port);
            if (status != 0) {
                if (status != 1) {
                    saves->count = status;
                    saves->unk2844 = 0;
                    func_80084230(saves, win);
                }
            }
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            saves->substate = 400;
            saves->unk2838 = 0;
            saves->step = 1;
        }
        break;
    case 400:
        status = saves->count = MEMCARD_SYSTEM.funcs.check(saves->port);
        if (status != 0) {
            saves->substate++;
        }
        break;
    case 401:
        if (saves->count != 1) {
            func_80084230(saves, win);
        }
        saves->substate = saves->step;
        saves->step = saves->counter;
        saves->counter = 0;
        break;
    case 110:
        status = saves->count = MEMCARD_SYSTEM.funcs.format(saves->port);
        if (status != 0) {
            if (status == 1) {
                win->panel->start(win->panel, 2, 0x14);
                saves->substate++;
            } else {
                func_80084230(saves, win);
            }
        }
        break;
    case 111:
        if (win->panel->done != 0) {
            func_80084230(saves, win);
            saves->count = 5;
        }
        break;
    case 120:
        saves->substate = 121;
        break;
    case 121:
        status = saves->count = MEMCARD_SYSTEM.funcs.create(saves->port);
        if (status != 0) {
            if (status == 1) {
                saves->substate++;
            } else {
                func_80084230(saves, win);
            }
        }
        break;
    case 122:
        status = saves->count = MEMCARD_SYSTEM.funcs.write(saves->port, (u8 *)&MEMCARD.header, sizeof(CardHeader), 0);
        if (status != 0) {
            if (status == 1) {
                if ((u32)(MEMCARD.iconCount - 1) >= 3) {
                    saves->count = 3;
                    func_80084230(saves, win);
                } else {
                    MEMCARD.unk324 = 0;
                    saves->substate++;
                }
            } else {
                saves->count = 10;
                func_80084230(saves, win);
            }
        }
        break;
    case 123:
        status = saves->count = MEMCARD_SYSTEM.funcs.write(saves->port, (u8 *)MEMCARD.icons[MEMCARD.unk324], 0x80, (MEMCARD.unk324 * 0x80 + 0x80) << 8);
        if (status != 0) {
            if (status == 1) {
                MEMCARD.unk324++;
                if (MEMCARD.unk324 > MEMCARD.iconCount - 1) {
                    HEAP.zero(STGMCARD_funcs.infoBuf, sizeof(MemCardFile));
                    STGMCARD_funcs.infoBuf->magic = MEMCARD_FILE_MAGIC;
                    STGMCARD_funcs.infoBuf->version = MEMCARD_SAVE_VERSION;
                    STGMCARD_funcs.infoBuf->checksum = MEMCARD_SYSTEM.funcs.computeChecksum((u8 *)&STGMCARD_funcs.infoBuf->magic, sizeof(MemCardFile) - 4);
                    saves->file = *STGMCARD_funcs.infoBuf;
                    STGMCARD_funcs.unk0 = STGMCARD_funcs.infoBuf->last;
                    saves->substate++;
                }
            } else {
                saves->count = 11;
                func_80084230(saves, win);
            }
        }
        break;
    case 124:
        status = saves->count = MEMCARD_SYSTEM.funcs.write(saves->port, (u8 *)STGMCARD_funcs.infoBuf, sizeof(MemCardFile), 1);
        if (status != 0) {
            win->panel->start(win->panel, 2, 0x14);
            saves->substate++;
        }
        break;
    case 125:
        if (win->panel->done != 0) {
            win->panel->reset(win->panel);
            if (saves->count == 1) {
                saves->substate = 30;
            } else {
                func_80084230(saves, win);
            }
        }
        break;
    }
}

/* Draws the save list's sprites: a menu sprite whose palette cycles while
   unk2838 is set, the list's own sprite and, while unk2844 is set, one more */
void func_800869D4(MemCardSaves *saves) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(saves->layer, 2);
    sprite.setTexture(0x140, 0);
    if (saves->unk2838 != 0) {
        if ((GFX.funcs.getTime() - saves->blinkTime) / 3 != 0) {
            saves->blinkTime = GFX.funcs.getTime();
            saves->blinkFrame++;
            if (saves->blinkFrame >= 5) {
                saves->blinkFrame = 0;
            }
        }
        sprite.setClutRow(saves->blinkFrame);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_MENU_SPRITES << 16), 10, 294, 208);
    }
    sprite.setTexture(0x280, 0);
    sprite.setClutRow(0);
    sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), 33, saves->unk58[0] + saves->slide[0].value, saves->unk58[1] + saves->slide[1].value);
    if (saves->unk2844 != 0) {
        sprite.setLayerId(saves->layer, 1);
        sprite.draw(FILE_CACHE.getEntry(FILE_GMCARD_SHEET << 16), 29, 188, 185);
    }
}

/* The save list's task: creates its windows, then runs it */
void func_80086BA0(MemCardSaves *saves, MemCardSavesWindows *win) {
    switch (saves->state) {
    case TASK_INIT:
    default:
        saves->nextState(saves);
        saves->unk58[0] = 5;
        saves->unk58[1] = 89;
        STGMCARD_funcs.startLerp(&saves->slide[1], 151, 0, 10);
        win->unk0 = createTextWindow(saves->layer, 1, saves->unk58[0] + 200, saves->unk58[1] + (s16)(saves->slide[1].value + 9));
        win->windows[4] = createTextWindow(saves->layer, 1, saves->unk58[0] + 15, saves->unk58[1] + 24);
        win->windows[0] = createTextWindow(saves->layer, 1, saves->unk58[0] + 15, saves->unk58[1] + 40);
        win->windows[0]->setLines(win->windows[0], 5);
        win->windows[0]->setDepth(win->windows[0], 1);
        win->windows[1] = createTextWindow(saves->layer, 1, saves->unk58[0] + 15, saves->unk58[1] + 103);
        win->windows[1]->setLines(win->windows[1], 2);
        win->windows[2] = createTextWindow(saves->layer, 1, 207, 189);
        win->windows[3] = createTextWindow(saves->layer, 1, 207, 203);
        win->cursor = createCursor(saves->layer, 0, 207, 189);
        win->cursor->setVisible(win->cursor, 0);
        win->menu = STGMCARD_createMenu(saves);
        break;
    case TASK_RUN:
        func_800844DC(saves, win);
        func_800869D4(saves);
        break;
    case TASK_DONE:
        switch (saves->substate) {
        case 0:
        default:
            win->unk0->setVisible(win->unk0, 0);
            saves->substate++;
            break;
        case 1:
            break;
        }
        func_800869D4(saves);
        break;
    case TASK_KILL:
        break;
    }
}

MemCardSaves *STGMCARD_createSaves(MemCardScreen *screen) {
    MemCardSaves *saves = createTask(func_80086BA0, sizeof(MemCardSaves), sizeof(MemCardSavesWindows));

    saves->refresh = STGMCARD_refreshSaves;
    saves->hide = STGMCARD_hideSaves;
    saves->screen = screen;
    saves->layer = 0x1000;
    return saves;
}

/* The main task: loads the files, runs the save list, then fades out and
   requests the next mode */
void func_80086E5C(MemCardScreen *screen, MemCardScreenTasks *tasks) {
    SpriteDrawer sprite;

    switch (screen->state) {
    case TASK_INIT:
    default:
        switch (screen->substate) {
        case 0:
        default:
            STGMCARD_funcs.loadFiles();
            screen->substate++;
            break;
        case 1:
            if (STGMCARD_funcs.filesLoading() == 0 && SOUND_STATE.isLoading() == 0) {
                SOUND_STATE.playSound(0x60800000);
                screen->nextState(screen);
            }
            break;
        }
        break;
    case TASK_RUN:
        switch (screen->substate) {
        case 0:
        default:
            if (tasks->saves == NULL) {
                tasks->saves = STGMCARD_createSaves(screen);
            }
            screen->nextSubstate(screen);
            break;
        case 1:
            if (tasks->saves->state == 2) {
                tasks->fade = STGMCARD_createFader();
                tasks->fade->start(tasks->fade, 0, 30);
                screen->substate++;
            }
            break;
        case 2:
            if (tasks->fade->state == 2) {
                screen->state = TASK_KILL;
            }
            break;
        }
        initSpriteDrawer(&sprite);
        sprite.setLayerId(screen->layer, 3);
        sprite.setTexture(0x280, 0);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_GMCARD_SHEET << 16), 31, 25, 0);
        if (screen->unk5C != 0) {
            screen->unk58++;
            screen->unk58 = screen->unk58 < 96 ? screen->unk58 : 0;
            screen->unk5C = 0;
        } else {
            screen->unk5C = 1;
        }
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FILE_GMCARD_SHEET << 16), 30, screen->unk58, screen->unk58);
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        SOUND_STATE.stopSound(0x60800000);
        if (screen->step != 0) {
            if (screen->saving == 0) {
                GAME.funcs.requestMode(GAME.funcs.getPrevMode(), 0);
            } else {
                GAME.funcs.requestMode(0xE00, 0);
            }
        } else {
            GAME.funcs.requestMode(GAME.fieldMode, 0);
        }
        STGMCARD_funcs.freeBuffers();
        break;
    }
}

/* Creates the screen's main task, with what it needs from the mode it was
   opened from and the one it was opened for */
Task *func_80087174(void) {
    MemCardScreen *screen = createTask(func_80086E5C, sizeof(MemCardScreen), 8);
    s32 mode;
    s32 prev;
    s32 i;

    screen->layer = 0x1000;
    mode = GAME.funcs.getMode() & 0xFF;
    screen->saving = (u32)GAME.funcs.getModeArg() >> 31 ^ 1;
    prev = GAME.funcs.getPrevMode();
    for (i = 0; D_800879D8[i].mode != 0; i++) {
        if (D_800879D8[i].mode == prev) {
            screen->unk68 = D_800879D8[i].value;
        }
    }
    screen->unk6C = D_80087970[mode];
    SOUND.loadBank(0x20);
    return (Task *)screen;
}

void STGMCARD_loadFiles(void) {
    TimLoader loader;
    TextTools conv;
    char title[0x48];
    s32 frames[3];
    CardClut *clut;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0);
    loader.loadArchive(FILE_CACHE.getEntry(FILE_GMCARD_SPRITES << 16));
    HEAP.zero(title, 0x41);
    initTextTools(&conv);
    conv.convert(title, conv.getString(FILE_CACHE.load(TEXT_FILE(0x79)), 0x27), 0);
    clut = STGMCARD_saveIcon.clut;
    frames[0] = STGMCARD_saveIcon.frames[0];
    frames[1] = STGMCARD_saveIcon.frames[1];
    frames[2] = STGMCARD_saveIcon.frames[2];
    MEMCARD_FUNCS.setHeader(title, clut, 3, frames);
    if (STGMCARD_funcs.dataBuf != NULL) {
        HEAP.free(STGMCARD_funcs.dataBuf);
    }
    STGMCARD_funcs.dataSize = 0x2780;
    STGMCARD_funcs.dataBuf = HEAP.alloc(0x2780, 2);
    if (STGMCARD_funcs.infoBuf != NULL) {
        HEAP.free(STGMCARD_funcs.infoBuf);
    }
    STGMCARD_funcs.infoSize = 0x180;
    STGMCARD_funcs.infoBuf = HEAP.alloc(0x180, 2);
    FILE_CACHE.request(TEXT_FILE(0x79));
    FILE_CACHE.request(TEXT_FILE(0xAA));
    FILE_CACHE.request(TEXT_FILE(0x95));
}

s32 STGMCARD_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x79)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0xAA)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x95)) != 0;
}

void STGMCARD_freeBuffers(void) {
    if (STGMCARD_funcs.dataBuf != NULL) {
        HEAP.free(STGMCARD_funcs.dataBuf);
    }
    if (STGMCARD_funcs.infoBuf != NULL) {
        HEAP.free(STGMCARD_funcs.infoBuf);
    }
}

void STGMCARD_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STGMCARD_updateFade(PanelAnim *fade) {
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

void STGMCARD_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STGMCARD_updateLerp(MenuLerp *lerp) {
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


MemCardWindowSpec D_800876BC[] = {
    { 32, 1, 24, 109, 0 },
    { 33, 1, 24, 123, 0 },
    { 33, 1, 24, 138, 0 },
    { 21, 3, 29, 155, 0 },
    { 21, 3, 118, 163, 0 },
    { 34, 3, 115, 163, 1 },
    { 20, 3, 156, 125, 0 },
    { 20, 3, 208, 125, 0 },
    { 20, 3, 260, 125, 0 },
    { 35, 3, 185, 125, 1 },
    { 35, 3, 237, 125, 1 },
    { 35, 3, 289, 125, 1 },
    { 35, 3, 261, 178, 1 },
    { 35, 3, 280, 178, 1 },
    { 35, 3, 299, 178, 1 },
    { 19, 3, 261, 178, 0 },
    { 19, 3, 280, 178, 0 },
    { 35, 3, 280, 178, 1 },
    { 35, 3, 299, 178, 1 },
};
s32 D_80087838[][7] = {
    { 7, 8, 9, 10, 9, 8, -1 },
    { 14, 15, 16, 15, -1, -1, -1 },
    { 11, 12, 13, 12, -1, -1, -1 },
    { 3, 4, 5, 6, 5, 4, -1 },
    { 25, 26, 27, 28, 27, 26, -1 },
    { 0, 1, 2, 1, -1, -1, -1 },
    { 17, 18, 19, 20, 19, 18, -1 },
    { 21, 22, 23, 24, 23, 22, -1 },
};
s32 D_80087918[] = {
    42, 44, 43, 41,
    47, 40, 45, 46,
};
s32 D_80087938[] = {
    109, 177, 245,
};
s32 STGMCARD_errorTexts[] = {
    1, 10, 27, 10,
    11, 12, 28, 13,
    38, 36, 37,
};
s32 D_80087970[] = {
    43, 43, 44, 45,
    46, 47, 48, 49,
    50, 51, 52, 53,
    54, 55, 56, 57,
    58, 59, 60, 61,
    62, 63, 64, 65,
    66, 67,
};
MemCardModeEntry D_800879D8[] = {
    { 0x0B, 0x01, 0x200 }, { 0x0B, 0x76, 0x270 }, { 0x0B, 0x01, 0x201 }, { 0x0B, 0x76, 0x271 },
    { 0x0B, 0x02, 0x202 }, { 0x0B, 0x77, 0x272 }, { 0x01, 0x03, 0x203 }, { 0x06, 0x03, 0x273 },
    { 0x01, 0x03, 0x204 }, { 0x0B, 0x01, 0x205 }, { 0x0B, 0x76, 0x274 }, { 0x01, 0x04, 0x206 },
    { 0x06, 0x04, 0x275 }, { 0x01, 0x05, 0x207 }, { 0x06, 0x05, 0x276 }, { 0x01, 0x06, 0x208 },
    { 0x06, 0x06, 0x277 }, { 0x01, 0x07, 0x209 }, { 0x06, 0x07, 0x278 }, { 0x01, 0x08, 0x20A },
    { 0x06, 0x78, 0x279 }, { 0x01, 0x87, 0x20B }, { 0x06, 0x87, 0x27A }, { 0x01, 0x09, 0x20C },
    { 0x06, 0x79, 0x27B }, { 0x01, 0x0A, 0x20D }, { 0x06, 0x7A, 0x27C }, { 0x01, 0x0B, 0x20E },
    { 0x06, 0x0B, 0x27D }, { 0x01, 0x0C, 0x20F }, { 0x06, 0x0C, 0x27E }, { 0x01, 0x0D, 0x210 },
    { 0x06, 0x0D, 0x27F }, { 0x01, 0x0E, 0x211 }, { 0x06, 0x0E, 0x280 }, { 0x01, 0x0F, 0x212 },
    { 0x06, 0x0F, 0x281 }, { 0x01, 0x10, 0x213 }, { 0x06, 0x10, 0x282 }, { 0x01, 0x11, 0x214 },
    { 0x06, 0x11, 0x283 }, { 0x01, 0x12, 0x215 }, { 0x06, 0x12, 0x284 }, { 0x01, 0x13, 0x216 },
    { 0x06, 0x13, 0x285 }, { 0x01, 0x14, 0x217 }, { 0x06, 0x14, 0x286 }, { 0x01, 0x15, 0x218 },
    { 0x06, 0x15, 0x287 }, { 0x01, 0x16, 0x219 }, { 0x06, 0x16, 0x288 }, { 0x01, 0x17, 0x21A },
    { 0x06, 0x17, 0x289 }, { 0x01, 0x18, 0x21B }, { 0x06, 0x7B, 0x28A }, { 0x01, 0x19, 0x21C },
    { 0x06, 0x19, 0x28B }, { 0x0B, 0x1A, 0x21D }, { 0x0B, 0x1A, 0x28C }, { 0x0B, 0x1B, 0x21E },
    { 0x0B, 0x1B, 0x28D }, { 0x0B, 0x1C, 0x21F }, { 0x0B, 0x1C, 0x28E }, { 0x0B, 0x1D, 0x220 },
    { 0x0B, 0x1D, 0x28F }, { 0x0C, 0x1E, 0x221 }, { 0x0C, 0x1E, 0x290 }, { 0x0C, 0x1F, 0x222 },
    { 0x0C, 0x1F, 0x291 }, { 0x0C, 0x20, 0x223 }, { 0x0C, 0x20, 0x292 }, { 0x0C, 0x21, 0x224 },
    { 0x0C, 0x21, 0x293 }, { 0x0C, 0x22, 0x225 }, { 0x0C, 0x22, 0x294 }, { 0x0C, 0x23, 0x226 },
    { 0x0C, 0x23, 0x295 }, { 0x0C, 0x24, 0x227 }, { 0x0C, 0x24, 0x296 }, { 0x0C, 0x25, 0x228 },
    { 0x0C, 0x25, 0x297 }, { 0x0C, 0x26, 0x229 }, { 0x0C, 0x26, 0x298 }, { 0x0C, 0x27, 0x22A },
    { 0x0C, 0x27, 0x299 }, { 0x0C, 0x28, 0x22B }, { 0x0C, 0x28, 0x29A }, { 0x0C, 0x29, 0x22C },
    { 0x0C, 0x29, 0x29B }, { 0x0C, 0x2A, 0x22D }, { 0x0C, 0x2B, 0x22E }, { 0x0C, 0x7C, 0x29C },
    { 0x02, 0x2C, 0x22F }, { 0x07, 0x2C, 0x29D }, { 0x02, 0x2D, 0x230 }, { 0x07, 0x7D, 0x29E },
    { 0x02, 0x2E, 0x231 }, { 0x07, 0x2E, 0x29F }, { 0x0D, 0x2F, 0x232 }, { 0x0D, 0x2F, 0x2A0 },
    { 0x0D, 0x30, 0x233 }, { 0x0D, 0x30, 0x2A1 }, { 0x0D, 0x31, 0x234 }, { 0x0D, 0x31, 0x2A2 },
    { 0x0D, 0x32, 0x235 }, { 0x0D, 0x32, 0x2A3 }, { 0x0D, 0x33, 0x236 }, { 0x0D, 0x34, 0x237 },
    { 0x0D, 0x34, 0x2A4 }, { 0x0D, 0x35, 0x238 }, { 0x0D, 0x35, 0x2A5 }, { 0x0D, 0x36, 0x239 },
    { 0x0D, 0x36, 0x2A6 }, { 0x0D, 0x37, 0x23A }, { 0x0D, 0x37, 0x2A7 }, { 0x0D, 0x38, 0x23B },
    { 0x0D, 0x38, 0x2A8 }, { 0x0D, 0x39, 0x23C }, { 0x0D, 0x39, 0x2A9 }, { 0x0D, 0x3A, 0x23D },
    { 0x0D, 0x3A, 0x2AA }, { 0x0D, 0x3B, 0x23E }, { 0x0D, 0x7E, 0x2AB }, { 0x03, 0x3C, 0x23F },
    { 0x08, 0x7F, 0x2AC }, { 0x03, 0x3D, 0x240 }, { 0x08, 0x80, 0x2AD }, { 0x0D, 0x3E, 0x241 },
    { 0x0D, 0x81, 0x2AE }, { 0x0D, 0x3F, 0x242 }, { 0x0D, 0x3F, 0x2AF }, { 0x0D, 0x40, 0x243 },
    { 0x0D, 0x40, 0x244 }, { 0x0D, 0x40, 0x2B0 }, { 0x10, 0x42, 0x245 }, { 0x10, 0x43, 0x246 },
    { 0x0E, 0x44, 0x247 }, { 0x0E, 0x44, 0x2B1 }, { 0x0E, 0x45, 0x248 }, { 0x0E, 0x45, 0x2B2 },
    { 0x0E, 0x46, 0x249 }, { 0x0E, 0x46, 0x2B3 }, { 0x0E, 0x47, 0x24A }, { 0x0E, 0x47, 0x2B4 },
    { 0x0E, 0x48, 0x24B }, { 0x0E, 0x48, 0x2B5 }, { 0x0E, 0x49, 0x24C }, { 0x0E, 0x49, 0x2B6 },
    { 0x0E, 0x4A, 0x24D }, { 0x0E, 0x4A, 0x2B7 }, { 0x0E, 0x4B, 0x24E }, { 0x0E, 0x4B, 0x2B8 },
    { 0x0E, 0x4C, 0x24F }, { 0x0E, 0x4C, 0x2B9 }, { 0x0E, 0x4D, 0x250 }, { 0x0E, 0x4D, 0x2BA },
    { 0x0E, 0x4E, 0x251 }, { 0x0E, 0x4E, 0x2BB }, { 0x0E, 0x4F, 0x252 }, { 0x0E, 0x4F, 0x2BC },
    { 0x0E, 0x50, 0x253 }, { 0x0E, 0x50, 0x2BD }, { 0x0E, 0x51, 0x254 }, { 0x0E, 0x51, 0x2BE },
    { 0x0E, 0x53, 0x255 }, { 0x0E, 0x53, 0x2BF }, { 0x0E, 0x53, 0x256 }, { 0x0E, 0x54, 0x257 },
    { 0x0E, 0x54, 0x2C0 }, { 0x0E, 0x55, 0x258 }, { 0x0E, 0x56, 0x2C1 }, { 0x0E, 0x56, 0x259 },
    { 0x0E, 0x56, 0x2C2 }, { 0x0E, 0x57, 0x25A }, { 0x0E, 0x57, 0x2C3 }, { 0x0E, 0x58, 0x25B },
    { 0x0E, 0x58, 0x2C4 }, { 0x0E, 0x59, 0x25C }, { 0x0E, 0x59, 0x2C5 }, { 0x0E, 0x5A, 0x25D },
    { 0x0E, 0x82, 0x2C6 }, { 0x04, 0x5B, 0x25E }, { 0x09, 0x83, 0x2C7 }, { 0x04, 0x5C, 0x25F },
    { 0x04, 0x5D, 0x260 }, { 0x09, 0x5D, 0x2C8 }, { 0x0F, 0x5E, 0x261 }, { 0x0F, 0x5E, 0x2C9 },
    { 0x0F, 0x5F, 0x262 }, { 0x0F, 0x5F, 0x2CA }, { 0x0F, 0x60, 0x263 }, { 0x0F, 0x60, 0x2CB },
    { 0x0F, 0x61, 0x264 }, { 0x0F, 0x61, 0x2CC }, { 0x0F, 0x62, 0x265 }, { 0x0F, 0x62, 0x2CD },
    { 0x0F, 0x63, 0x266 }, { 0x0F, 0x63, 0x2CE }, { 0x0F, 0x64, 0x267 }, { 0x0F, 0x64, 0x2CF },
    { 0x0F, 0x65, 0x268 }, { 0x0F, 0x65, 0x2D0 }, { 0x0F, 0x66, 0x269 }, { 0x0F, 0x66, 0x2D1 },
    { 0x0F, 0x67, 0x26A }, { 0x0F, 0x67, 0x2D2 }, { 0x0F, 0x68, 0x26B }, { 0x0F, 0x68, 0x2D3 },
    { 0x0F, 0x69, 0x26C }, { 0x0F, 0x69, 0x2D4 }, { 0x0F, 0x6A, 0x26D }, { 0x0F, 0x6B, 0x26E },
    { 0x0F, 0x6B, 0x2D5 }, { 0x0F, 0x6C, 0x26F }, { 0x0F, 0x84, 0x2D6 }, { 0x11, 0x6D, 0x2D7 },
    { 0x11, 0x6E, 0x2D8 }, { 0x11, 0x6A, 0x2D9 }, { 0x12, 0x70, 0x2DA }, { 0x12, 0x71, 0x2DB },
    { 0x12, 0x72, 0x2DC }, { 0x13, 0x73, 0x2DD }, { 0x13, 0x74, 0x2DE }, { 0x13, 0x75, 0x2DF },
    { 0x15, 0x85, 0x2E0 }, { 0x15, 0x85, 0x2E1 }, { 0x15, 0x85, 0x2E2 }, { 0x15, 0x85, 0x2E3 },
    { 0x15, 0x85, 0x2E4 }, { 0x15, 0x85, 0x2E5 }, { 0x15, 0x85, 0x2E6 }, { 0x15, 0x85, 0x2E7 },
    { 0x15, 0x86, 0x2E8 }, { 0x15, 0x86, 0x2E9 }, { 0x15, 0x86, 0x2EA }, { 0x15, 0x86, 0x2EB },
    { 0x15, 0x86, 0x2EC }, { 0x15, 0x86, 0x2ED }, { 0x15, 0x86, 0x2EE }, { 0x01, 0x03, 0x1500 },
    { 0x00, 0x00, 0x0 },
};
MemCardScreenFuncs STGMCARD_funcs = {
    0, 0, 0, NULL, NULL, 0, 0,
    STGMCARD_loadFiles, STGMCARD_filesLoading, STGMCARD_freeBuffers,
    STGMCARD_startFade, STGMCARD_updateFade, STGMCARD_startLerp, STGMCARD_updateLerp,
};
s32 STGMCARD_iconClut[] = {
    0x2D6B0000, 0x469320E7, 0x71C85167, 0x3A0F635A,
    0x28C473DD, 0x185944, 0x71C87E8D, 0x7E587E13,
};
s32 STGMCARD_iconFrames[3][32] = {
    {
        0x2EFFFFFF, 0xF2222222, 0xA2EFFFFF, 0x29AAAAAA,
        0x5A2FFFFF, 0x9AA55555, 0xC5AEFFFF, 0xAAA5555C,
        0x65A9FFFF, 0xAAAAAA65, 0x3712FFFF, 0xAA237211,
        0x2612FF8F, 0xA2626117, 0x2817283F, 0x21628117,
        0x121172FF, 0x21622116, 0x36621768, 0x11777773,
        0x23621723, 0x17733322, 0x33211168, 0x227773B3,
        0x22111723, 0x22222222, 0x2111112E, 0x22221211,
        0x721112EE, 0x22212111, 0x12222EEE, 0x22111111,
    },
    {
        0xA2EFFFFF, 0xF999AAAA, 0x5A2FFFFF, 0x9AAA5555,
        0xC5AEFFFF, 0xAAA5555C, 0x65A9FFFF, 0xAAAA5565,
        0x1122FF8F, 0xAA211211, 0x2712F63F, 0xA2627117,
        0x281222FF, 0x21628117, 0x72117768, 0x21622116,
        0x3662172F, 0x11777773, 0x23621768, 0x17733322,
        0x3321112F, 0x217771B3, 0x721112FF, 0x222177B7,
        0x211112EF, 0x22221212, 0x12112EEF, 0x22212111,
        0x1122EEEF, 0x22221111, 0x172EEEEE, 0x22211111,
    },
    {
        -1, 0x999EFFFF, 0xEFFFFFFF, 0x55A99999,
        0x99EFF83F, 0x222AAAAA, 0xC59FF63F, 0xAAA5555C,
        0xCC5F22F8, 0xAAA55555, 0x5C5912E6, 0xAAAA5555,
        0x65521163, 0xAAA25565, 0x11121128, 0x22211111,
        0x22121163, 0x21221111, 0x7171112F, 0x21122173,
        0x3677122F, 0x11777773, 0x2767221E, 0x17733772,
        0x337222EE, 0x22777333, 0x222121EE, 0x22222222,
        0x71222EEE, 0x22212121, 0x1722EEEE, 0x22111111,
    },
};
SaveIcon STGMCARD_saveIcon = {
    (CardClut *)STGMCARD_iconClut,
    {(s32)STGMCARD_iconFrames[0], (s32)STGMCARD_iconFrames[1], (s32)STGMCARD_iconFrames[2]},
};
