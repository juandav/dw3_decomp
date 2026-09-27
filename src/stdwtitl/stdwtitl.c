#include "stdwtitl.h"

void STDWTITL_tickSplashLoader(Task *task, Task **splash) {
    TimLoader loader;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0xA000);
        GFX.funcs.setDisplayMode(320, 240, 0, 0);
        initTimLoader(&loader);
        loader.setImagePos(0x280, 0);
        loader.loadArchive(FILE_CACHE_GET_ENTRY[0](SPLASH_IMAGES));
        layer = GFX.funcs.createLayer(&STDWTITL_screenRect, 2, STDWTITL_SPLASH_LAYER);
        layer->setBgColor(layer, 0x1F, 0x1F, 0x1F);
        *splash = STDWTITL_startSplashTask();
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STDWTITL_startSplashLoaderTask(void) {
    return createTask(STDWTITL_tickSplashLoader, sizeof(Task), sizeof(Task *));
}

void STDWTITL_tickScreen(Task *task, ScreenChildren *children) {
    RECT rect;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        switch (GAME_FUNCS.getMode() & 0xFF) {
        case 0:
            GFX.funcs.reset();
            GFX.funcs.allocPrimBuffers(0x14000);
            GFX.funcs.setDisplayMode(320, 240, 0, 0);
            rect.x = 0;
            rect.y = 0;
            rect.w = 320;
            rect.h = 240;
            layer = GFX.funcs.createLayer(&rect, 2, STDWTITL_TITLE_LAYER);
            layer->setBgColor(layer, 0, 0, 0);
            children->title = STDWTITL_startTitleLoaderTask();
            break;
        case 12:
            children->splash = STDWTITL_startSplashLoaderTask();
            break;
        default:
            children->movie = STDWTITL_startMovieTask((GAME_FUNCS.getMode() & 0xFF) - 1);
            break;
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *STDWTITL_start(void) {
    return createTask(STDWTITL_tickScreen, sizeof(Task), sizeof(ScreenChildren));
}

void STDWTITL_drawLogo(LogoTask *task) {
    SpriteDrawer sprite;

    if (task->visible) {
        initSpriteDrawer(&sprite);
        sprite.setLayerId(task->layerId, 0);
        sprite.setTexture(0x280, 0);
        sprite.draw(FILE_CACHE.getEntry(STDWTITL_spriteBank), 6, 29, 209);
        initSpriteDrawer(&sprite);
        sprite.setLayerId(task->layerId, 0);
        sprite.setTexture(0x280, 0);
        sprite.setClutRow(task->anims[0].frame);
        sprite.draw(FILE_CACHE.getEntry(STDWTITL_spriteBank), 3, 8, 28);
        initSpriteDrawer(&sprite);
        sprite.setLayerId(task->layerId, 0);
        sprite.setTexture(0x280, 0);
        sprite.setClutRow(task->anims[1].frame);
        sprite.draw(FILE_CACHE.getEntry(STDWTITL_spriteBank), 5, 20, 202);
    }
}

void STDWTITL_tickLogo(LogoTask *task) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        if (task->skip == 0) {
            task->nextState(task);
        } else {
            task->setState(task, TASK_DONE);
        }
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            task->visible = 1;
            task->nextSubstate(task);
            task->anims[0].index = 0;
            task->anims[1].index = 0;
        case 2:
            for (i = 0; i < 2; i++) {
                if (!task->anims[i].done) {
                    if (STDWTITL_logoFrames[i][task->anims[i].index] == -1) {
                        task->anims[i].done = 1;
                        task->anims[i].index--;
                    }
                    task->anims[i].frame = STDWTITL_logoFrames[i][task->anims[i].index];
                    task->anims[i].index++;
                }
            }
            if (task->anims[0].done + task->anims[1].done == 2) {
                task->setSubstate(task, 2);
            }
            STDWTITL_drawLogo(task);
            break;
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anims[0].frame = 11;
            task->anims[1].frame = 7;
            task->visible = 1;
            task->nextSubstate(task);
        }
        STDWTITL_drawLogo(task);
        break;
    case TASK_KILL:
        break;
    }
}

void STDWTITL_showLogo(LogoTask *task) {
    if (task->state == TASK_RUN) {
        task->setSubstate(task, 1);
    }
}

LogoTask *STDWTITL_startLogoTask(s32 skip) {
    LogoTask *task = createTask(STDWTITL_tickLogo, sizeof(LogoTask), 0);

    task->show = STDWTITL_showLogo;
    task->layerId = STDWTITL_TITLE_LAYER;
    task->depth = 2;
    task->skip = skip;
    return task;
}

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_clearVram);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_initDecEnv);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_readStream);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_initStream);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_getNextFrame);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_decodeNextFrame);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_onSliceDecoded);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_waitFrameDecoded);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickMoviePlayer);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startMoviePlayerTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickMovie);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startMovieTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawGlintAlt);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickGlintAlt);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_showGlint);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startGlintAltTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawGlint);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickGlint);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startGlintTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawSplash);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickSplash);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startSplashTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_runTitleLoader);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickTitleLoader);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startTitleLoaderTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawTitle1Alt);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickTitle1Alt);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_showTitle1);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startTitle1AltTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawTitle1);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickTitle1);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startTitle1Task);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawTitle0Alt);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickTitle0Alt);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_showTitle0);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startTitle0AltTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawTitle0);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickTitle0);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startTitle0Task);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_drawMenu);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_tickMenu);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_showMenu);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_resetMenu);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_getMenuChoice);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl", STDWTITL_startMenuTask);
