#include "stgmcard.h"

extern MemCardScreenFuncs STGMCARD_funcs;
extern SaveIcon STGMCARD_saveIcon;

void func_800833A0();
void func_80082E28();
void func_80082904();
void func_80086BA0();
void func_80083B10();

Task *func_80087174(void);

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

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_80082904);

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_80082E28);

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

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_800833A0);

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
    STGMCARD_funcs.unk4 = arg;
    STGMCARD_funcs.unk8 = 0;
}

void func_80083934(MemCardMenu *menu) {
    STGMCARD_funcs.startLerp(&menu->lerps[1], 0, -0x55, 5);
    menu->substate = 4;
}

void func_80083978(MemCardMenu *menu) {
    STGMCARD_funcs.startLerp(&menu->lerps[3], STGMCARD_funcs.unk8 * 0x44, STGMCARD_funcs.unk4 * 0x44, 5);
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
    STGMCARD_funcs.unk4 = 0;
    STGMCARD_funcs.unk8 = 0;
    STGMCARD_funcs.startLerp(&menu->lerps[0], 0xDE, 0, 10);
    STGMCARD_funcs.startLerp(&menu->lerps[1], -0x55, 0, 10);
    STGMCARD_funcs.startLerp(&menu->lerps[2], 0, 0x2F, 8);
    STGMCARD_funcs.startLerp(&menu->lerps[3], -1, 0, 1);
    menu->lerps[3].value = 0;
}

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_80083B10);

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
    saves->unk27FC = 0;
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

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_800844DC);

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_800869D4);

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_80086BA0);

MemCardSaves *STGMCARD_createSaves(s32 arg) {
    MemCardSaves *saves = createTask(func_80086BA0, sizeof(MemCardSaves), sizeof(MemCardSavesWindows));

    saves->refresh = STGMCARD_refreshSaves;
    saves->hide = STGMCARD_hideSaves;
    saves->unk50 = arg;
    saves->layer = 0x1000;
    return saves;
}

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_80086E5C);

INCLUDE_ASM("stgmcard/nonmatchings/stgmcard", func_80087174);

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


s32 D_800876BC[] = {
    32, 1, 24, 109,
    0, 33, 1, 24,
    123, 0, 33, 1,
    24, 138, 0, 21,
    3, 29, 155, 0,
    21, 3, 118, 163,
    0, 34, 3, 115,
    163, 1, 20, 3,
    156, 125, 0, 20,
    3, 208, 125, 0,
    20, 3, 260, 125,
    0, 35, 3, 185,
    125, 1, 35, 3,
    237, 125, 1, 35,
    3, 289, 125, 1,
    35, 3, 261, 178,
    1, 35, 3, 280,
    178, 1, 35, 3,
    299, 178, 1, 19,
    3, 261, 178, 0,
    19, 3, 280, 178,
    0, 35, 3, 280,
    178, 1, 35, 3,
    299, 178, 1,
};
s32 D_80087838[] = {
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
s32 D_80087918[] = {
    42, 44, 43, 41,
    47, 40, 45, 46,
};
s32 D_80087938[] = {
    109, 177, 245,
};
s32 D_80087944[] = {
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
s32 D_800879D8[] = {
    0x200010B, 0x270760B, 0x201010B, 0x271760B,
    0x202020B, 0x272770B, 0x2030301, 0x2730306,
    0x2040301, 0x205010B, 0x274760B, 0x2060401,
    0x2750406, 0x2070501, 0x2760506, 0x2080601,
    0x2770606, 0x2090701, 0x2780706, 0x20A0801,
    0x2797806, 0x20B8701, 0x27A8706, 0x20C0901,
    0x27B7906, 0x20D0A01, 0x27C7A06, 0x20E0B01,
    0x27D0B06, 0x20F0C01, 0x27E0C06, 0x2100D01,
    0x27F0D06, 0x2110E01, 0x2800E06, 0x2120F01,
    0x2810F06, 0x2131001, 0x2821006, 0x2141101,
    0x2831106, 0x2151201, 0x2841206, 0x2161301,
    0x2851306, 0x2171401, 0x2861406, 0x2181501,
    0x2871506, 0x2191601, 0x2881606, 0x21A1701,
    0x2891706, 0x21B1801, 0x28A7B06, 0x21C1901,
    0x28B1906, 0x21D1A0B, 0x28C1A0B, 0x21E1B0B,
    0x28D1B0B, 0x21F1C0B, 0x28E1C0B, 0x2201D0B,
    0x28F1D0B, 0x2211E0C, 0x2901E0C, 0x2221F0C,
    0x2911F0C, 0x223200C, 0x292200C, 0x224210C,
    0x293210C, 0x225220C, 0x294220C, 0x226230C,
    0x295230C, 0x227240C, 0x296240C, 0x228250C,
    0x297250C, 0x229260C, 0x298260C, 0x22A270C,
    0x299270C, 0x22B280C, 0x29A280C, 0x22C290C,
    0x29B290C, 0x22D2A0C, 0x22E2B0C, 0x29C7C0C,
    0x22F2C02, 0x29D2C07, 0x2302D02, 0x29E7D07,
    0x2312E02, 0x29F2E07, 0x2322F0D, 0x2A02F0D,
    0x233300D, 0x2A1300D, 0x234310D, 0x2A2310D,
    0x235320D, 0x2A3320D, 0x236330D, 0x237340D,
    0x2A4340D, 0x238350D, 0x2A5350D, 0x239360D,
    0x2A6360D, 0x23A370D, 0x2A7370D, 0x23B380D,
    0x2A8380D, 0x23C390D, 0x2A9390D, 0x23D3A0D,
    0x2AA3A0D, 0x23E3B0D, 0x2AB7E0D, 0x23F3C03,
    0x2AC7F08, 0x2403D03, 0x2AD8008, 0x2413E0D,
    0x2AE810D, 0x2423F0D, 0x2AF3F0D, 0x243400D,
    0x244400D, 0x2B0400D, 0x2454210, 0x2464310,
    0x247440E, 0x2B1440E, 0x248450E, 0x2B2450E,
    0x249460E, 0x2B3460E, 0x24A470E, 0x2B4470E,
    0x24B480E, 0x2B5480E, 0x24C490E, 0x2B6490E,
    0x24D4A0E, 0x2B74A0E, 0x24E4B0E, 0x2B84B0E,
    0x24F4C0E, 0x2B94C0E, 0x2504D0E, 0x2BA4D0E,
    0x2514E0E, 0x2BB4E0E, 0x2524F0E, 0x2BC4F0E,
    0x253500E, 0x2BD500E, 0x254510E, 0x2BE510E,
    0x255530E, 0x2BF530E, 0x256530E, 0x257540E,
    0x2C0540E, 0x258550E, 0x2C1560E, 0x259560E,
    0x2C2560E, 0x25A570E, 0x2C3570E, 0x25B580E,
    0x2C4580E, 0x25C590E, 0x2C5590E, 0x25D5A0E,
    0x2C6820E, 0x25E5B04, 0x2C78309, 0x25F5C04,
    0x2605D04, 0x2C85D09, 0x2615E0F, 0x2C95E0F,
    0x2625F0F, 0x2CA5F0F, 0x263600F, 0x2CB600F,
    0x264610F, 0x2CC610F, 0x265620F, 0x2CD620F,
    0x266630F, 0x2CE630F, 0x267640F, 0x2CF640F,
    0x268650F, 0x2D0650F, 0x269660F, 0x2D1660F,
    0x26A670F, 0x2D2670F, 0x26B680F, 0x2D3680F,
    0x26C690F, 0x2D4690F, 0x26D6A0F, 0x26E6B0F,
    0x2D56B0F, 0x26F6C0F, 0x2D6840F, 0x2D76D11,
    0x2D86E11, 0x2D96A11, 0x2DA7012, 0x2DB7112,
    0x2DC7212, 0x2DD7313, 0x2DE7413, 0x2DF7513,
    0x2E08515, 0x2E18515, 0x2E28515, 0x2E38515,
    0x2E48515, 0x2E58515, 0x2E68515, 0x2E78515,
    0x2E88615, 0x2E98615, 0x2EA8615, 0x2EB8615,
    0x2EC8615, 0x2ED8615, 0x2EE8615, 0x15000301,
    0,
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
