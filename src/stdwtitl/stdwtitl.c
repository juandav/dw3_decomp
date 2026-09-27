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

void STDWTITL_clearVram(void) {
    ResetGraph(1);
    ClearImage2(&STDWTITL_vramRect, 0, 0, 0);
    DrawSync(0);
}

void STDWTITL_initDecEnv(DecEnv *dec, s16 x0, s16 y0, s16 x1, s16 y1) {
    dec->vlcbuf[0] = STDWTITL_vlcBuffer0;
    dec->vlcbuf[1] = STDWTITL_vlcBuffer1;
    dec->vlcid = GFX.buffer ^ 1;
    dec->imgbuf[0] = STDWTITL_imageBuffer0;
    dec->imgbuf[1] = STDWTITL_imageBuffer1;
    dec->imgid = GFX.buffer ^ 1;
    dec->rect[0].x = x0;
    dec->rect[0].y = y0;
    dec->rect[1].x = x1;
    dec->rect[1].y = y1;
    dec->rectid = GFX.buffer ^ 1;
    dec->slice.x = x0;
    dec->slice.y = y0;
    dec->slice.w = 24;
    dec->isdone = 0;
}

void STDWTITL_readStream(CdlLOC *loc) {
    u_char param;

    param = CdlModeSpeed;
    do {
        while (CdControl(CdlSetloc, (u_char *)loc, 0) == 0) {
        }
        while (CdControl(CdlSetmode, &param, 0) == 0) {
        }
    } while (CdRead2(CdlModeStream | CdlModeSpeed | CdlModeRT | CdlModeSize1) == 0);
}

void STDWTITL_initStream(CdlLOC *loc, void (*callback)()) {
    DecDCTReset(0);
    DecDCToutCallback(callback);
    StSetRing(STDWTITL_ringBuffer, 32);
    StSetStream(1, 1, -1, 0, 0);
    STDWTITL_readStream(loc);
}

u_long *STDWTITL_getNextFrame(DecEnv *dec) {
    u_long *addr;
    StHEADER *sector;
    s32 count = 2000;

    while (StGetNext(&addr, (u_long **)&sector) != 0) {
        if (--count == 0) {
            return NULL;
        }
    }
    if (sector->frameCount >= STDWTITL_movieEndFrame) {
        STDWTITL_movieEnded = 1;
    }
    if (STDWTITL_movieWidth != sector->width || STDWTITL_movieHeight != sector->height) {
        STDWTITL_clearVram();
        STDWTITL_movieWidth = sector->width;
        STDWTITL_movieHeight = sector->height;
    }
    dec->rect[0].w = dec->rect[1].w = STDWTITL_movieWidth * 3 / 2;
    dec->rect[0].h = dec->rect[1].h = STDWTITL_movieHeight;
    dec->slice.h = STDWTITL_movieHeight;
    return addr;
}

s32 STDWTITL_decodeNextFrame(DecEnv *dec) {
    s32 count = 2000;
    u_long *next;

    while ((next = STDWTITL_getNextFrame(dec)) == NULL) {
        if (--count == 0) {
            return -1;
        }
    }
    dec->vlcid = dec->vlcid == 0;
    DecDCTvlc2(next, dec->vlcbuf[dec->vlcid], STDWTITL_vlcTable);
    StFreeRing(next);
    return 0;
}

void STDWTITL_onSliceDecoded(void) {
    RECT rect;
    s32 id;

    if (D_80080BEC) {
        StCdInterrupt();
        D_80080BEC = 0;
    }
    id = STDWTITL_decEnv.imgid;
    rect = STDWTITL_decEnv.slice;
    STDWTITL_decEnv.imgid = STDWTITL_decEnv.imgid == 0;
    STDWTITL_decEnv.slice.x += STDWTITL_decEnv.slice.w;
    if (STDWTITL_decEnv.rectid) {
        rect.x += 480;
    }
    rect.y = 36;
    if (STDWTITL_decEnv.slice.x < STDWTITL_decEnv.rect[STDWTITL_decEnv.rectid].x + STDWTITL_decEnv.rect[STDWTITL_decEnv.rectid].w) {
        DecDCTout((u_long *)STDWTITL_decEnv.imgbuf[STDWTITL_decEnv.imgid], STDWTITL_decEnv.slice.w * STDWTITL_decEnv.slice.h / 2);
    } else {
        STDWTITL_decEnv.isdone = 1;
        STDWTITL_decEnv.rectid = STDWTITL_decEnv.rectid == 0;
        STDWTITL_decEnv.slice.x = STDWTITL_decEnv.rect[STDWTITL_decEnv.rectid].x;
        STDWTITL_decEnv.slice.y = STDWTITL_decEnv.rect[STDWTITL_decEnv.rectid].y;
    }
    DrawSync(0);
    LoadImage(&rect, (u_long *)STDWTITL_decEnv.imgbuf[id]);
}

void STDWTITL_waitFrameDecoded(DecEnv *dec, s32 mode) {
    volatile s32 count = 0x800000;

    while (dec->isdone == 0) {
        if (--count == 0) {
            dec->isdone = 1;
            dec->rectid = dec->rectid == 0;
            dec->slice.x = dec->rect[dec->rectid].x;
            dec->slice.y = dec->rect[dec->rectid].y;
        }
    }
    dec->isdone = 0;
}

void STDWTITL_tickMoviePlayer(MoviePlayerTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        STDWTITL_clearVram();
        STDWTITL_ringBuffer = HEAP.alloc(0x10000, 2);
        STDWTITL_vlcBuffer0 = HEAP.alloc(0x28000, 2);
        STDWTITL_vlcBuffer1 = HEAP.alloc(0x28000, 2);
        STDWTITL_imageBuffer0 = HEAP.alloc(0x4E00, 2);
        STDWTITL_imageBuffer1 = HEAP.alloc(0x4E00, 2);
        STDWTITL_vlcTable = HEAP.alloc(0x11000, 2);
        STDWTITL_initDecEnv(&STDWTITL_decEnv, 0, 0, 0, 416);
        FILE_TABLE.getPos(STDWTITL_movieFile, 0, (u8 *)&task->loc);
        STDWTITL_initStream(&task->loc, STDWTITL_onSliceDecoded);
        DecDCTvlcBuild(STDWTITL_vlcTable);
        STDWTITL_decodeNextFrame(&STDWTITL_decEnv);
        STDWTITL_movieEnded = 0;
        task->nextState(task);
    case TASK_RUN:
        DecDCTin(STDWTITL_decEnv.vlcbuf[STDWTITL_decEnv.vlcid], 3);
        DecDCTout((u_long *)STDWTITL_decEnv.imgbuf[STDWTITL_decEnv.imgid], STDWTITL_decEnv.slice.w * STDWTITL_decEnv.slice.h / 2);
        STDWTITL_decodeNextFrame(&STDWTITL_decEnv);
        STDWTITL_waitFrameDecoded(&STDWTITL_decEnv, 0);
        if (STDWTITL_movieEnded == 1 || (PAD.getPressed(0) & 8)) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        CdControlB(CdlPause, 0, 0);
        DecDCToutCallback(NULL);
        StUnSetRing();
        HEAP.free(STDWTITL_ringBuffer);
        HEAP.free(STDWTITL_vlcBuffer0);
        HEAP.free(STDWTITL_vlcBuffer1);
        HEAP.free(STDWTITL_imageBuffer0);
        HEAP.free(STDWTITL_imageBuffer1);
        HEAP.free(STDWTITL_vlcTable);
        DrawSync(0);
        STDWTITL_clearVram();
        GFX_FUNCS.setDisplayArea(0, 0, 320, 240);
        break;
    }
}

MoviePlayerTask *STDWTITL_startMoviePlayerTask(s32 file, u32 endFrame) {
    MoviePlayerTask *task = createTask(STDWTITL_tickMoviePlayer, sizeof(MoviePlayerTask), 0);

    STDWTITL_movieFile = file;
    STDWTITL_movieEndFrame = endFrame;
    return task;
}

void STDWTITL_tickMovie(MovieTask *task, MoviePlayerTask **player) {
    switch (task->state) {
    case TASK_INIT:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x2800);
        GFX.funcs.setDisplayMode(320, 480, 1, 1);
        if (task->movie != 10) {
            *player = STDWTITL_startMoviePlayerTask(STDWTITL_movies[task->movie].file, STDWTITL_movies[task->movie].endFrame);
            task->nextMode = STDWTITL_movies[task->movie].nextMode;
        } else {
            *player = STDWTITL_startMoviePlayerTask(STDWTITL_movies[11].file, STDWTITL_movies[11].endFrame);
            task->nextMode = STDWTITL_movies[11].nextMode;
        }
        SOUND_STATE.stopAll();
        task->nextState(task);
        break;
    case TASK_RUN:
        if (*player == NULL) {
            FONT.load();
            GAME_FUNCS.requestMode(task->nextMode, 0);
            task->setState(task, TASK_DONE);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

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
