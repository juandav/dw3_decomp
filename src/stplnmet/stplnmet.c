#include "stplnmet.h"

extern TextStyle STPLNMET_nameStyle;

Task *STPLNMET_createScreen(void);
void func_800828DC();
void func_80082B80();
void func_80082D88();
void func_80082F0C();
void func_80085028();
void func_800852D8(PlayerNameTask *task, s32 arg);
void func_80087630();

void STPLNMET_centerLayer(Task *task, Task **children, Layer *layer, RECT *rect) {
    layer->setOffset(layer, rect->w / 2, rect->h / 2);
    layer->allocCallbacks(layer, 5);
}

void STPLNMET_updateScene(Task *task, Task **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x19000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        layer = GFX.funcs.createLayer(&rect, 1, 0x1000);
        layer->setBgColor(layer, 1, 1, 1);
        STPLNMET_centerLayer(task, children, layer, &rect);
        GFX.funcs.createLayer(&rect, 3, 0x1001);
        GFX.funcs.moveLayer(0x1001, 0x1000, 1);
        children[0] = STPLNMET_createScreen();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STPLNMET_start(void) {
    return createTask(STPLNMET_updateScene, sizeof(Task), 4);
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800828DC);

void STPLNMET_loadScroll(NameScroll *task, s32 x, s32 y) {
    TimLoader loader;

    task->vramX = x;
    task->vramY = y;
    initTimLoader(&loader);
    loader.setImagePos(x, y);
    loader.loadArchive(FILE_CACHE_GET_ENTRY[0](FILE_PLNMET_IMAGE << 16));
    task->loaded = 1;
}

void STPLNMET_setScrollLayer(NameScroll *task, s32 layer, s32 depth) {
    task->layer = layer;
    task->depth = depth;
}

NameScroll *STPLNMET_createScroll(void) {
    NameScroll *task = createTask(func_800828DC, sizeof(NameScroll), 0);

    task->load = STPLNMET_loadScroll;
    task->setLayer = STPLNMET_setScrollLayer;
    return task;
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80082B80);

NameSparkle *func_80082D5C(void) {
    return createTask(func_80082B80, sizeof(NameSparkle), 0);
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80082D88);

NameSparkle *func_80082EE0(void) {
    return createTask(func_80082D88, sizeof(NameSparkle), 0);
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80082F0C);

NameDialog *func_800834C0(s32 arg) {
    NameDialog *task = createTask(func_80082F0C, sizeof(NameDialog), 8);

    task->unk50 = arg;
    return task;
}

void STPLNMET_startTween(NameTween *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn != 0) {
        SOUND.playSound(0x40019);
        fade->value = 0;
        fade->step = 0x1000 / fade->duration;
    } else {
        SOUND.playSound(0x4001A);
        fade->value = 0x1000;
        fade->step = -((0x1000 / fade->duration) * 2);
    }
}

s32 STPLNMET_updateTween(NameTween *fade) {
    if (fade->active == 0) {
        return 1;
    }
    fade->value += fade->step;
    if (fade->step > 0) {
        if (fade->value > 0x1000) {
            fade->value = 0x1000;
            fade->active = 0;
            return 1;
        }
    } else if (fade->value < 0) {
        fade->value = 0;
        fade->active = 0;
        return 1;
    }
    return 0;
}

void STPLNMET_createNameWindows(PlayerNameTask *task, PlayerNameWindows *windows) {
    s32 i;

    windows->title = createTextWindow(task->layer, 1, 0x20, 0x1A);
    windows->title->setPalette(windows->title, 4);
    windows->name = createTextWindow(task->layer, 1, 0x4B, 0x40);
    windows->name->setSpacing(windows->name, 0x13, 0);
    windows->name->style = (u8 *)&STPLNMET_nameStyle;
    for (i = 0; i < 3; i++) {
        windows->tabs[i] = createTextWindow(task->layer, 1, 0x2F + i * 0x4E, 0x5B);
        windows->tabs[i]->setDepth(windows->tabs[i], task->depth - 1);
        windows->tabs[i]->setLines(windows->tabs[i], 7);
        windows->tabs[i]->setSpacing(windows->tabs[i], 0xE, 0x12);
        windows->tabs[i]->style = (u8 *)&STPLNMET_nameStyle;
    }
    windows->unk20 = createTextWindow(task->layer, 1, 0xCE, 0xC6);
    windows->unk24 = createTextWindow(task->layer, 1, 0xE1, 0xC6);
    windows->unk28 = createTextWindow(task->layer, 1, 0x13, 0x62);
    windows->unk28->setDepth(windows->unk28, task->depth - 1);
    windows->unk2C = createTextWindow(task->layer, 1, 0x123, 0x62);
    windows->unk2C->setDepth(windows->unk2C, task->depth - 1);
    windows->unk30 = createTextWindow(task->layer, 1, 0x3E, 0x72);
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800837E8);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80083AEC);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80084418);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80085028);

void STPLNMET_setNameVram(PlayerNameTask *task, s32 x, s32 y) {
    task->vramX = x;
    task->vramY = y;
}

void STPLNMET_setName(PlayerNameTask *task, char *name) {
    TextTools conv;
    s32 i;

    initTextTools(&conv);
    conv.convert(task->name, name, 0);
    for (i = strlen((char *)task->name) >> 1; i < task->maxLength; i++) {
        task->name[i] = 0x4081;
    }
}

void STPLNMET_getName(PlayerNameTask *task, char *out) {
    TextTools conv;
    s32 i;

    for (i = 0; i < task->maxLength * 2; i++) {
        out[i] = 0;
    }
    for (i = task->maxLength - 1; i >= 0 && task->name[i] == 0x4081; i--) {
        task->name[i] = 0;
    }
    for (i = 0; i < task->maxLength && task->name[i] == 0x4081; i++) {
    }
    initTextTools(&conv);
    conv.convert(out, &task->name[i], 1);
}

void func_800852CC(PlayerNameTask *task) {
    task->substate = 10;
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800852D8);

PlayerNameTask *STPLNMET_createNameEntry(char *name) {
    PlayerNameTask *task = createTask(func_80085028, sizeof(PlayerNameTask), sizeof(PlayerNameWindows));

    task->getName = STPLNMET_getName;
    task->unkF0 = func_800852D8;
    task->unkF4 = func_800852CC;
    task->layer = 0x1001;
    task->depth = 6;
    task->mode = 0;
    task->unk64 = -1;
#if VERSION_US
    task->maxLength = 8;
#elif VERSION_EU
    /* five full-width characters in Japanese */
    if (LANGUAGE == 0) {
        task->maxLength = 5;
    } else {
        task->maxLength = 8;
    }
#endif
    STPLNMET_setName(task, name);
    STPLNMET_setNameVram(task, 0x140, 0x100);
    return task;
}

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80085434);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800855DC);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80085834);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80085F0C);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086370);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800863DC);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800863E8);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086490);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800864F0);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800866C0);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086944);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086C74);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086EE0);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086F30);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80086FC0);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80087014);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_800870EC);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80087194);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80087568);

INCLUDE_ASM("stplnmet/nonmatchings/stplnmet", func_80087630);

Task *STPLNMET_createScreen(void) {
    PlayerNameScreen *screen = createTask(func_80087630, sizeof(PlayerNameScreen), 0x28);

    screen->layer = 0x1001;
    screen->depth = 5;
    return (Task *)screen;
}

void STPLNMET_loadFiles(void) {
    TimLoader loader;

    initTimLoader(&loader);
    loader.setImagePos(0x280, 0x100);
    loader.loadArchive(FILE_CACHE.getEntry(FILE_PLNMET_SPRITES << 16));
    FILE_CACHE.request(TEXT_FILE(0x8E));
    FILE_CACHE.request(TEXT_FILE(0x4F));
    FILE_CACHE.request(TEXT_FILE(0x87));
    FILE_CACHE.request(FILE_PLNMET_KEYBOARD);
}

s32 STPLNMET_filesLoading(void) {
    if (FILE_CACHE.isLoading(TEXT_FILE(0x8E)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x4F)) != 0) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x87)) != 0) {
        return 1;
    }
    return FILE_CACHE.isLoading(FILE_PLNMET_KEYBOARD) != 0;
}

void STPLNMET_startFade(PanelAnim *fade, s32 fadeIn) {
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

s32 STPLNMET_updateFade(PanelAnim *fade) {
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

void STPLNMET_startLerp(MenuLerp *lerp, s32 from, s32 to, s32 frames) {
    if (from != to) {
        lerp->duration = frames;
        lerp->fixed = from << 8;
        lerp->value = from;
        lerp->target = to;
        lerp->active = 1;
        lerp->step = ((to - from) << 8) / lerp->duration;
    }
}

s32 STPLNMET_updateLerp(MenuLerp *lerp) {
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
