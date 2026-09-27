#include "stdgname.h"

INCLUDE_ASM("asm/stdgname/nonmatchings/stdgname_2", func_800856F4);

void func_800858D8(ScreenTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layer, 7);
    sprite.setTexture(0x280, 0);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](0x02790000), 0x31, 0, 0);
    /* Scroll one pixel every other frame, wrapping at 96 */
    if (task->tick) {
        task->scroll = task->scroll++ < 95 ? task->scroll : 0;
        task->tick = 0;
    } else {
        task->tick = 1;
    }
    sprite.draw(FILE_CACHE_GET_ENTRY[0](0x02790000), 0x24, task->scroll, task->scroll);
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
    loader.loadArchive(FILE_CACHE.getEntry(0x027A0000));
    FILE_CACHE.request(0x41);
    FILE_CACHE.request(0x762);
    FILE_CACHE.request(0x87);
}

s32 func_80085C08(void) {
    if (FILE_CACHE.isLoading(0x762)) {
        return 1;
    }
    if (FILE_CACHE.isLoading(0x41)) {
        return 1;
    }
    return FILE_CACHE.isLoading(0x87) != 0;
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
