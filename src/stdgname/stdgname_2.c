#include "stdgname.h"

void func_800856F4(ScreenTask *task, ScreenChildren *children) {
    s32 partner;

    switch (task->substate) {
    case 0:
    default:
        if (children->menu == NULL) {
            children->menu = func_800856B4(task);
        }
        task->substate++;
        break;
    case 1:
        if (children->menu == NULL) {
            if (task->choice == -1) {
                task->substate = 5;
                break;
            }
            task->substate++;
        }
        break;
    case 2:
        if (children->name == NULL) {
            partner = GAME.funcs.getPartyMember(D_80087480.partner);
            children->name = func_800848F0(GAME.funcs.getPartnerStats(partner)->name, partner);
        }
        task->substate++;
        break;
    case 3:
        if (children->name->substate == 100) {
            children->name->getName(children->name,
                                    GAME.funcs.getPartnerStats(GAME.funcs.getPartyMember(D_80087480.partner))->name);
            children->name->unkF4(children->name);
            task->substate++;
        }
        break;
    case 4:
        if (children->name->state == TASK_DONE) {
            children->name->state = TASK_KILL;
            task->setSubstate(task, 0);
        }
        break;
    case 5:
        if (children->fade->state == TASK_DONE) {
            task->setState(task, TASK_KILL);
        }
        break;
    }
}

void func_800858D8(ScreenTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layer, 7);
    sprite.setTexture(0x280, 0);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](STDGNAME_SPRITES), 0x31, 0, 0);
    /* Scroll one pixel every other frame, wrapping at 96 */
    if (task->tick) {
        task->scroll = task->scroll++ < 95 ? task->scroll : 0;
        task->tick = 0;
    } else {
        task->tick = 1;
    }
    sprite.draw(FILE_CACHE_GET_ENTRY[0](STDGNAME_SPRITES), 0x24, task->scroll, task->scroll);
}

void func_800859CC(ScreenTask *task, ScreenChildren *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        switch (task->substate) {
        case 0:
        default:
            D_80087480.loadFiles();
            task->substate++;
            break;
        case 1:
            if (D_80087480.isLoading() == 0) {
                task->nextState(task);
            }
            break;
        }
        break;
    case TASK_RUN:
        func_800856F4(task, children);
        func_800858D8(task);
        break;
    case TASK_DONE:
        if (children->unkC == NULL) {
            task->setState(task, TASK_RUN);
        }
        func_800858D8(task);
        break;
    case TASK_KILL:
        GAME.funcs.requestMode(GAME.fieldMode, 0);
        break;
    }
}

void func_80085ADC(ScreenTask *task) {
    ScreenChildren *children = task->children;
    FadeTask *fade;

    children->fade = fade = func_80082AC8();
    fade->start(fade, 0, 30);
}

ScreenTask *func_80085B20(void) {
    ScreenTask *task = createTask(func_800859CC, sizeof(ScreenTask), sizeof(ScreenChildren));

    task->fadeOut = func_80085ADC;
    task->layer = 0x1000;
    return task;
}

void func_80085B60(void) {
    TimLoader loader;

    HEAP.zero(&D_80087480.partner, sizeof(D_80087480.partner));
    initTimLoader(&loader);
    loader.setImagePos(0x280, 0);
    loader.loadArchive(FILE_CACHE.getEntry(STDGNAME_FILE_IMAGES << 16));
    FILE_CACHE.request(TEXT_FILE(0x41));
    FILE_CACHE.request(STDGNAME_FILE_KEYBOARD);
    FILE_CACHE.request(TEXT_FILE(0x87));
}

s32 func_80085C08(void) {
    if (FILE_CACHE.isLoading(STDGNAME_FILE_KEYBOARD)) {
        return 1;
    }
    if (FILE_CACHE.isLoading(TEXT_FILE(0x41))) {
        return 1;
    }
    return FILE_CACHE.isLoading(TEXT_FILE(0x87)) != 0;
}

void func_80085C78(Tween *tween, s32 open) {
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

s32 func_80085D0C(Tween *tween) {
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
