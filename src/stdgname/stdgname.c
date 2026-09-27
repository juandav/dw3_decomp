#include "stdgname.h"

void func_80082724(Task *task, void **children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x5000);
        GFX.funcs.setDisplayMode(320, 240, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 320;
        rect.h = 240;
        layer = GFX.funcs.createLayer(&rect, 3, 0x1000);
        layer->setBgColor(layer, 0, 0, 0);
        *children = func_80085B20();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *func_8008281C(void) {
    return createTask(func_80082724, sizeof(Task), sizeof(void *));
}

void func_80082848(FadeTask *task, s32 fadeIn, s32 duration) {
    task->setState(task, TASK_RUN);
    task->substate = 1;
    task->fadeIn = fadeIn;
    if (fadeIn == 0) {
        task->level = 0;
        task->delta = 0xFF00 / duration;
    } else {
        task->level = 0xFF00;
        task->delta = -(0xFF00 / duration);
    }
}

void func_800828D0(FadeTask *task) {
    Layer *layer = GFX.funcs.getLayer(task->layer);
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

void func_80082A14(FadeTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        if (task->substate != 0) {
            task->level += task->delta;
            if (task->fadeIn == 0) {
                if (task->level > 0xFF00) {
                    task->level = 0xFF00;
                    task->state = TASK_DONE;
                }
            } else if (task->level < 0) {
                task->level = 0;
                task->state = TASK_DONE;
            }
            func_800828D0(task);
        }
        break;
    case TASK_DONE:
        func_800828D0(task);
        break;
    case TASK_KILL:
        break;
    }
}

FadeTask *func_80082AC8(void) {
    FadeTask *task = createTask(func_80082A14, sizeof(FadeTask), 0);

    task->start = func_80082848;
    task->layer = 0x1000;
    task->depth = 6;
    return task;
}

void func_80082B10(Tween *tween, s32 open) {
    tween->active = 1;
    if (open) {
        SOUND.playSound(0x40019);
        tween->step = 0x1000 / tween->duration;
        tween->value = 0;
    } else {
        SOUND.playSound(0x4001A);
        tween->value = 0x1000;
        tween->step = -(0x1000 / tween->duration * 2);
    }
}

s32 func_80082BA4(Tween *tween) {
    if (tween->active == 0) {
        return 1;
    }
    tween->value += tween->step;
    if (tween->step > 0) {
        if (tween->value > 0x1000) {
            tween->value = 0x1000;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < 0) {
        tween->value = 0;
        tween->active = 0;
        return 1;
    }
    return 0;
}
#include "stdgname.h"

void func_80082C10(NameTask *task, NameWindows *windows) {
    s32 i;

    windows->title = createTextWindow(task->layer, 1, 0x20, 0x1A);
    windows->title->setPalette(windows->title, 4);
    windows->name = createTextWindow(task->layer, 1, 0x4B, 0x40);
    windows->name->setSpacing(windows->name, 0x13, 0);
    windows->name->style = (u8 *)&D_80086FC0;
    for (i = 0; i < 3; i++) {
        windows->tabs[i] = createTextWindow(task->layer, 1, 0x2F + i * 0x4E, 0x5B);
        windows->tabs[i]->setDepth(windows->tabs[i], task->depth - 1);
        windows->tabs[i]->setLines(windows->tabs[i], 7);
        windows->tabs[i]->setSpacing(windows->tabs[i], 0xE, 0x12);
        windows->tabs[i]->style = (u8 *)&D_80086FC0;
    }
    windows->unk20 = createTextWindow(task->layer, 1, 0xCE, 0xC6);
    windows->unk24 = createTextWindow(task->layer, 1, 0xE1, 0xC6);
    windows->unk28 = createTextWindow(task->layer, 1, 0x13, 0x62);
    windows->unk28->setDepth(windows->unk28, task->depth - 1);
    windows->unk2C = createTextWindow(task->layer, 1, 0x123, 0x62);
    windows->unk2C->setDepth(windows->unk2C, task->depth - 1);
    windows->unk30 = createTextWindow(task->layer, 1, 0x3E, 0x72);
}

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80082E00);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80083104);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80083A30);

void func_80084640(NameTask *task, NameWindows *windows) {
    TimLoader loader;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        initTimLoader(&loader);
        loader.setImagePos(task->vramX, task->vramY);
        loader.loadArchive(FILE_CACHE_GET_ENTRY[0](0x07620000));
        D_8008837C.pageCount = 1;
        D_8008837C.tabTexts = D_80086EE0;
        D_8008837C.keys = D_80086EEC;
        task->unkC0.duration = 10;
        task->unkE0.duration = 10;
        task->unkD0.duration = 10;
        func_80082C10(task, windows);
        break;
    case TASK_RUN:
        func_80083A30(task, windows);
        func_80083104(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_80084744(NameTask *task, s32 x, s32 y) {
    task->vramX = x;
    task->vramY = y;
}

void func_80084750(NameTask *task, char *name) {
    TextTools conv;
    s32 i;

    initTextTools(&conv);
    conv.convert(task->name, name, 0);
    for (i = strlen((char *)task->name) >> 1; i < task->maxLength; i++) {
        task->name[i] = 0x4081;
    }
}

void func_800847E4(NameTask *task, char *out) {
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

void func_800848E4(NameTask *task) {
    task->substate = 10;
}

NameTask *func_800848F0(char *name, s32 partner) {
    NameTask *task = createTask(func_80084640, sizeof(NameTask), sizeof(NameWindows));

    task->getName = func_800847E4;
    task->unkF4 = func_800848E4;
    task->layer = 0x1000;
    task->depth = 3;
    task->mode = 1;
    task->partner = partner;
    task->maxLength = 8;
    func_80084750(task, name);
    func_80084744(task, 0x280, 0x100);
    return task;
}

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084998);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80084B0C);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800850E0);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085354);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800856B4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800856F4);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800858D8);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_800859CC);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085ADC);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085B20);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085B60);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085C08);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085C78);

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname", func_80085D0C);
