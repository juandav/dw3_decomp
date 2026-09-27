#include "stdgname.h"

/* One bit of pad 1: newly pressed, or auto-repeated while held */
#define PAD_PRESSED(button) ((PAD.getPressed(0) >> PAD.getButtonBit(0, button)) & 1)
#define PAD_REPEATED(button) ((PAD.getRepeated(0) >> PAD.getButtonBit(0, button)) & 1)

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

void func_80084998(MenuTask *task, TextWindow **window, s32 index, s32 show) {
    s32 layer = 0;
    char *name;

    if (index < 5) {
        layer = task->layer;
    }
    if (show) {
        if (*window == NULL) {
            *window = createTextWindow(layer, 1, D_800872E0[index].x, D_800872E0[index].y);
            (*window)->setDepth(*window, 1);
        }
        if (index >= 2 && index <= 4) {
            name = GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(index - 2))->name;
            (*window)->style = (u8 *)D_80087480.style;
            (*window)->setString(*window, name, -1);
        } else {
            (*window)->setString(*window, FILE_CACHE_LOAD[0](0x41), D_800872E0[index].text);
        }
        (*window)->setPalette(*window, 0);
    } else if (*window != NULL) {
        (*window)->setVisible(*window, 0);
    }
}

void func_80084B0C(MenuTask *task, TextWindow **windows) {
    SpriteDrawer sprite;
    s32 i;
    s32 value;
    s32 partner;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layer, 2);
    sprite.setTexture(0x280, 0);
    for (i = 0; i < 3; i++) {
        if (D_8008710C[i].sprite == -1) {
            break;
        }
        value = task->tweens[i].value;
        if (value != 0x1000) {
            if (D_8008710C[i].vertical) {
                sprite.setScale(0x1000, value, 0x1000);
            } else {
                sprite.setScale(value, 0x1000, 0x1000);
            }
            if (D_8008710C[i].sprite == 0x20) {
                sprite.setPivot(D_8008710C[i].pivotX, D_8008710C[i].pivotY + D_80087480.partner * 43);
            } else {
                sprite.setPivot(D_8008710C[i].pivotX, D_8008710C[i].pivotY);
            }
        } else {
            sprite.setScale(0x1000, 0x1000, 0x1000);
        }
        if (D_8008710C[i].sprite == 0x20) {
            if ((GFX_FUNCS.getTime() & 3) == 3) {
                if (++task->titleClut >= 16) {
                    task->titleClut = 0;
                }
            }
            sprite.setClutRow(task->titleClut);
            sprite.draw(FILE_CACHE.getEntry(0x02790000), D_8008710C[i].sprite, D_8008710C[i].x, D_8008710C[i].y + D_80087480.partner * 43);
            sprite.setClutRow(0);
        } else {
            sprite.draw(FILE_CACHE.getEntry(0x02790000), D_8008710C[i].sprite, D_8008710C[i].x, D_8008710C[i].y);
        }
    }
    for (i = 0; i < task->partyCount; i++) {
        partner = GAME.funcs.getPartyPartner(i);
        if (partner >= 0 && task->tweens[i + 3].value != 0) {
            if (GFX.funcs.getTime() - task->anims[i].time >= 13) {
                task->anims[i].time = GFX.funcs.getTime();
                if (D_800873A0[partner][++task->anims[i].frame] == -1) {
                    task->anims[i].frame = 0;
                }
            }
            if (task->tweens[i + 3].value != 0x1000) {
                sprite.setScale(task->tweens[i + 3].value, 0x1000, 0x1000);
                sprite.setPivot(D_800872B0[0].pivotX + 2, D_800872B0[0].pivotY + 2);
            } else {
                sprite.setScale(0x1000, 0x1000, 0x1000);
            }
            sprite.draw(FILE_CACHE_GET_ENTRY[0](0x02790000), D_800873A0[partner][task->anims[i].frame],
                        D_800872B0[0].x + 2, D_800872B0[0].y + 2 + i * 43);
        }
    }
    if ((GFX_FUNCS.getTime() & 3) == 3) {
        if (++task->cursorClut >= 14) {
            task->cursorClut = 0;
        }
    }
    for (i = 0; i < task->partyCount; i++) {
        if (GAME.funcs.getPartyPartner(i) >= 0) {
            if (task->tweens[i + 3].value != 0) {
                if (task->tweens[i + 3].value != 0x1000) {
                    sprite.setScale(task->tweens[i + 3].value, 0x1000, 0x1000);
                    sprite.setPivot(D_800872B0[0].pivotX, D_800872B0[0].pivotY + i * 43);
                } else {
                    sprite.setScale(0x1000, 0x1000, 0x1000);
                }
                sprite.setLayerId(task->layer, 1);
                sprite.setClutRow(task->cursorClut);
                sprite.draw(FILE_CACHE.getEntry(0x02790000), 0x1F, D_800872B0[0].x, D_800872B0[0].y + i * 43);
                sprite.setLayerId(task->layer, 2);
                sprite.setClutRow(0);
                sprite.draw(FILE_CACHE.getEntry(0x02790000), 0x1E, D_800872B0[0].x, D_800872B0[0].y + i * 43);
            }
        }
    }
}

s32 func_800850E0(MenuTask *task, TextWindow **windows) {
    if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
        if (--D_80087480.partner < 0) {
            D_80087480.partner = task->partyCount - 1;
        }
        SOUND.playSound(0x4001B);
    } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
        if (++D_80087480.partner > task->partyCount - 1) {
            D_80087480.partner = 0;
        }
        SOUND.playSound(0x4001B);
    }
    if (PAD_PRESSED(PAD_CROSS)) {
        SOUND.playSound(0x4001C);
        task->screen->choice = D_80087480.partner;
        return 1;
    }
    if (PAD_PRESSED(PAD_TRIANGLE)) {
        SOUND.playSound(0x800450BD);
        task->screen->choice = -1;
        task->screen->fadeOut(task->screen);
        return 1;
    }
    return 0;
}

void func_80085354(MenuTask *task, TextWindow **windows) {
    s32 i;
    s32 j;
    s32 done;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        for (i = 5; i >= 0; i--) {
            task->tweens[i].duration = 10;
        }
        for (i = 0; i < 3; i++) {
            if (GAME.funcs.getPartyPartner(i) >= 0) {
                task->partyCount++;
            }
        }
        break;
    case TASK_RUN:
        done = 0;
        switch (task->substate) {
        case 0:
        default:
            D_80087480.startTween(&task->tweens[0], 1);
            D_80087480.startTween(&task->tweens[1], 1);
            task->substate++;
            break;
        case 1:
            done += D_80087480.tickTween(&task->tweens[0]);
            done += D_80087480.tickTween(&task->tweens[1]);
            if (done == 2) {
                func_80084998(task, &windows[0], 0, 1);
                func_80084998(task, &windows[1], 1, 1);
                D_80087480.startTween(&task->tweens[3], 1);
                task->nextSubstate(task);
            }
            break;
        case 2:
            if (D_80087480.tickTween(&task->tweens[task->step + 3])) {
                func_80084998(task, &windows[task->step + 2], task->step + 2, 1);
                if (task->step < task->partyCount - 1) {
                    task->step++;
                    D_80087480.startTween(&task->tweens[task->step + 3], 1);
                } else {
                    D_80087480.startTween(&task->tweens[2], 1);
                    task->nextSubstate(task);
                }
            }
            break;
        case 4:
            if (func_800850E0(task, windows)) {
                task->substate++;
                for (i = 0; i < 6; i++) {
                    D_80087480.startTween(&task->tweens[i], 0);
                    func_80084998(task, &windows[i], i, 0);
                }
            }
            break;
        case 3:
        case 5:
            if (D_80087480.tickTween(&task->tweens[2])) {
                task->substate++;
            }
            break;
        case 6:
            for (j = 0; j < 6; j++) {
                done += D_80087480.tickTween(&task->tweens[j]);
            }
            if (done == 6) {
                task->setState(task, TASK_KILL);
            }
            break;
        }
        func_80084B0C(task, windows);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

MenuTask *func_800856B4(ScreenTask *screen) {
    MenuTask *task = createTask(func_80085354, sizeof(MenuTask), 10 * sizeof(TextWindow *));

    task->screen = screen;
    task->layer = 0x1000;
    return task;
}
