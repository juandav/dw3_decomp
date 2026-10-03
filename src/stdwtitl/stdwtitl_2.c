#include "stdwtitl.h"

/* The screen's edges, from which it fades out */
EdgeLine STDWTITL_edgeFadeLines[] = {
    {0, -15, 320, -15}, {320, -15, 320, 260}, {0, 260, 320, 260},
    {0, -15, 0, 260},
};

AnimFrame STDWTITL_backgroundAnim0[] = {
    {300, 180}, {0, 2}, {1, 3}, {2, 5}, {3, 4}, {4, 4}, {5, 4}, {6, 5}, {7, 4},
    {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {300, 12}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim1[] = {
    {300, 240}, {83, 1}, {14, 1}, {82, 1}, {84, 2}, {85, 2}, {86, 2}, {87, 2},
    {14, 6}, {88, 2}, {89, 2}, {90, 3}, {91, 3}, {92, 3}, {93, 3}, {94, 3},
    {95, 3}, {96, 3}, {97, 3}, {300, 10}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim2[] = {
    {0xF, 1}, {14, 1}, {16, 1}, {14, 1}, {17, 1}, {14, 1}, {18, 1}, {24, 1},
    {19, 1}, {25, 1}, {20, 1}, {26, 1}, {21, 1}, {27, 1}, {22, 1}, {28, 1},
    {23, 1}, {29, 1}, {33, 1}, {30, 1}, {34, 1}, {31, 1}, {35, 1}, {32, 1},
    {36, 1}, {14, 1}, {37, 1}, {49, 1}, {38, 1}, {48, 1}, {39, 1}, {47, 1},
    {40, 1}, {46, 1}, {14, 1}, {45, 1}, {14, 1}, {44, 1}, {14, 1}, {43, 1},
    {14, 1}, {42, 1}, {14, 1}, {41, 1}, {300, 20}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim3[] = {
    {300, 25}, {50, 1}, {14, 1}, {51, 1}, {14, 1}, {52, 1}, {14, 1}, {53, 1},
    {14, 1}, {54, 1}, {14, 1}, {55, 1}, {14, 1}, {56, 1}, {14, 1}, {57, 1},
    {14, 1}, {58, 1}, {66, 1}, {59, 1}, {67, 1}, {60, 1}, {68, 1}, {61, 1},
    {69, 1}, {62, 1}, {70, 1}, {63, 1}, {71, 1}, {64, 1}, {72, 1}, {65, 1},
    {73, 1}, {14, 1}, {74, 1}, {14, 1}, {75, 1}, {14, 1}, {76, 1}, {14, 1},
    {77, 1}, {14, 1}, {78, 1}, {14, 1}, {79, 1}, {14, 1}, {80, 1}, {14, 1},
    {81, 1}, {300, 30}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim4[] = {
    {300, 240}, {27, 1}, {5, 1}, {28, 1}, {5, 1}, {29, 1}, {5, 1}, {30, 1},
    {5, 1}, {31, 1}, {5, 1}, {32, 1}, {5, 1}, {33, 1}, {5, 1}, {34, 1}, {5, 1},
    {35, 1}, {5, 1}, {36, 1}, {5, 1}, {37, 1}, {5, 1}, {38, 1}, {5, 1},
    {39, 1}, {5, 1}, {40, 1}, {5, 1}, {13, 1}, {14, 1}, {0xF, 1}, {16, 1},
    {17, 1}, {40, 1}, {18, 1}, {39, 1}, {19, 1}, {38, 1}, {20, 1}, {37, 1},
    {21, 1}, {36, 1}, {22, 1}, {35, 1}, {23, 1}, {34, 1}, {24, 1}, {33, 1},
    {25, 1}, {32, 1}, {26, 1}, {31, 1}, {5, 1}, {30, 1}, {5, 1}, {29, 1},
    {5, 1}, {28, 1}, {5, 1}, {27, 1}, {300, 60}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim5[] = {
    {300, 180}, {41, 2}, {5, 1}, {41, 1}, {5, 1}, {42, 2}, {5, 1}, {42, 1},
    {5, 1}, {43, 2}, {5, 1}, {43, 1}, {5, 1}, {44, 2}, {5, 1}, {44, 1}, {5, 9},
    {45, 2}, {5, 1}, {45, 1}, {5, 1}, {46, 2}, {5, 1}, {46, 1}, {5, 1},
    {47, 2}, {5, 1}, {47, 1}, {300, 180}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim6[] = {
    {300, 180}, {0, 1}, {5, 1}, {0, 2}, {5, 1}, {1, 2}, {5, 1}, {2, 2}, {5, 1},
    {2, 1}, {5, 1}, {3, 1}, {5, 1}, {3, 1}, {5, 1}, {4, 1}, {5, 1}, {4, 1},
    {300, 240}, {0xFF, 0},
};
AnimFrame STDWTITL_backgroundAnim7[] = {
    {300, 120}, {6, 1}, {5, 1}, {7, 1}, {5, 1}, {6, 1}, {5, 1}, {7, 1}, {5, 1},
    {8, 1}, {5, 1}, {8, 1}, {5, 1}, {9, 1}, {5, 1}, {10, 1}, {5, 1}, {11, 1},
    {5, 1}, {12, 1}, {300, 240}, {0xFF, 0},
};

Point16 STDWTITL_background6Positions[] = {
    {16, 165}, {265, 85}, {200, 0},
};
Point16 STDWTITL_background7Positions[] = {
    {150, 0}, {282, 8}, {290, 178}, {0, 0}, {0, 108},
};

s32 STDWTITL_spriteBank = 0;

TitleFuncs STDWTITL_titleFuncs = {
    STDWTITL_loadTitleImages, STDWTITL_startFade, STDWTITL_stepFade,
    STDWTITL_startTween, STDWTITL_stepTween,
};

/* The title's TIM archives and sprite banks; the European version picks one
   by the language */
TitleImages STDWTITL_titleImages[] = {
#if VERSION_US
    {0x08750001, 0x08750000}, {0x08930001, 0x08930000},
    {0x08750001, 0x08750000}, {0x08750001, 0x08750000},
    {0x08750001, 0x08750000}, {0x08750001, 0x08750000},
    {0x08750001, 0x08750000},
#elif VERSION_EU
    {0x08860001, 0x08860000}, {0x08A40001, 0x08A40000},
    {0x094D0001, 0x094D0000}, {0x094D0001, 0x094D0000},
    {0x094D0001, 0x094D0000}, {0x094D0001, 0x094D0000},
    {0x094D0001, 0x094D0000},
#endif
};

s32 STDWTITL_getEdgeFadeLevel(s32 time) {
    if (time >= 30) {
        return 255;
    }
    return rsin(time * 1024 / 30) * 30 / 4096 * 255 / 30;
}

void STDWTITL_drawEdgeFade(s32 level) {
    Layer *layer = GFX.funcs.getLayer(STDWTITL_TITLE_LAYER);
    u_long *ot = (u_long *)layer->getOtEntry(layer, 0);
    POLY_G3 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;
    s32 edge;
    s32 i;

    edge = level * 2;
    for (i = 0; i < 4; i++) {
        setPolyG3(poly);
        setSemiTrans(poly, 1);
        poly->r0 = poly->g0 = poly->b0 = level;
        if (edge >= 256) {
            edge = 255;
        }
        poly->r1 = poly->g1 = poly->b1 = poly->r2 = poly->g2 = poly->b2 = edge;
        /* From the centre of the screen to one of its edges */
        poly->x0 = 160;
        poly->y0 = 120;
        poly->x1 = STDWTITL_edgeFadeLines[i].x1;
        poly->y1 = STDWTITL_edgeFadeLines[i].y1;
        poly->x2 = STDWTITL_edgeFadeLines[i].x2;
        poly->y2 = STDWTITL_edgeFadeLines[i].y2;
        addPrim(ot, poly);
        poly++;
    }
    mode = (DR_TPAGE *)poly;
    setDrawTPage(mode, 0, 1, getTPage(0, 2, 320, 0));
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void STDWTITL_startEdgeFade(EdgeFadeTask *task) {
    task->done = 0;
    task->time = 0;
    task->setSubstate(task, 1);
}

s32 STDWTITL_isEdgeFadeDone(EdgeFadeTask *task) {
    return task->done;
}

void STDWTITL_tickEdgeFade(EdgeFadeTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->level = 0;
        task->time = 0;
        task->done = 0;
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            task->level = STDWTITL_getEdgeFadeLevel(task->time++);
            if (task->time >= 30) {
                task->setSubstate(task, 0);
                task->done = 1;
            }
            break;
        }
        STDWTITL_drawEdgeFade(task->level);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

EdgeFadeTask *STDWTITL_startEdgeFadeTask(void) {
    EdgeFadeTask *task = createTask(STDWTITL_tickEdgeFade, sizeof(EdgeFadeTask), 0);

    task->start = STDWTITL_startEdgeFade;
    task->isDone = STDWTITL_isEdgeFadeDone;
    return task;
}

s32 STDWTITL_stepLoopingAnimation(AnimState *anim, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[anim->index];

    if (depth == 0) {
        anim->timer--;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (frame->frame == 0xFF) {
            /* Back to the first frame */
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        STDWTITL_stepLoopingAnimation(anim, frames, depth + 1);
    }
    return frame->frame;
}

void STDWTITL_drawBackground(BackgroundTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layerId, 0);
    sprite.setAltClut(0, 0x1F3);
    sprite.setTexture(0x300, 0);
    sprite.draw(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(0)), 0, 0, 0);
    sprite.setTexture(0x340, 0);
    sprite.draw(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(1)), 0, 0, 0);
    sprite.setTexture(0x380, 0);
    sprite.draw(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(2)), 0, 0, 0);
}

void STDWTITL_drawBackgroundSprites(BackgroundTask *task) {
    SpriteDrawer sprite;
    s32 frame0 = STDWTITL_stepLoopingAnimation(&task->anims[0], STDWTITL_backgroundAnim0, 0);
    s32 frame1 = STDWTITL_stepLoopingAnimation(&task->anims[1], STDWTITL_backgroundAnim1, 0);
    s32 frame2 = STDWTITL_stepLoopingAnimation(&task->anims[2], STDWTITL_backgroundAnim2, 0);
    s32 frame3 = STDWTITL_stepLoopingAnimation(&task->anims[3], STDWTITL_backgroundAnim3, 0);
    s32 frame4 = STDWTITL_stepLoopingAnimation(&task->anims[4], STDWTITL_backgroundAnim4, 0);
    s32 frame5 = STDWTITL_stepLoopingAnimation(&task->anims[5], STDWTITL_backgroundAnim5, 0);
    s32 frame6 = STDWTITL_stepLoopingAnimation(&task->anims[6], STDWTITL_backgroundAnim6, 0);
    s32 frame7 = STDWTITL_stepLoopingAnimation(&task->anims[7], STDWTITL_backgroundAnim7, 0);

    initSpriteDrawer(&sprite);
    sprite.setLayerId(task->layerId, 0);
    sprite.setTexture(0x3C0, 0);
    if (frame0 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(3)), frame0, 0, 0);
    }
    if (frame1 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(3)), frame1, 0, 0);
    }
    if (frame2 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(3)), frame2, 0, 0);
    }
    if (frame3 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(3)), frame3, 0, 0);
    }
    if (frame4 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(8)), frame4, 0, 0);
    }
    if (frame5 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(8)), frame5, 0, 0);
    }
    if (frame6 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(8)), frame6, task->pos6.x, task->pos6.y);
    }
    if (frame7 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](STDWTITL_BACKGROUND(8)), frame7, task->pos7.x, task->pos7.y);
    }
}

void STDWTITL_tickBackground(BackgroundTask *task) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anims[0].index = 0;
            task->anims[0].timer = STDWTITL_backgroundAnim0[0].duration;
            task->anims[1].index = 0;
            task->anims[1].timer = STDWTITL_backgroundAnim1[0].duration;
            task->anims[2].index = 0;
            task->anims[2].timer = STDWTITL_backgroundAnim2[0].duration;
            task->anims[3].index = 0;
            task->anims[3].timer = STDWTITL_backgroundAnim3[0].duration;
            task->anims[4].index = 0;
            task->anims[4].timer = STDWTITL_backgroundAnim4[0].duration;
            task->anims[5].index = 0;
            task->anims[5].timer = STDWTITL_backgroundAnim5[0].duration;
            task->anims[6].index = 0;
            task->anims[6].timer = STDWTITL_backgroundAnim6[0].duration + RANDOM.next() % 300;
            task->anims[7].index = 0;
            task->anims[7].timer = STDWTITL_backgroundAnim7[0].duration + RANDOM.next() % 240;
            i = RANDOM.next() % 3;
            task->pos6.x = STDWTITL_background6Positions[i].x;
            task->pos6.y = STDWTITL_background6Positions[i].y;
            i = RANDOM.next() % 5;
            task->pos7.x = STDWTITL_background7Positions[i].x;
            task->pos7.y = STDWTITL_background7Positions[i].y;
            task->setSubstate(task, 1);
        }
        STDWTITL_drawBackgroundSprites(task);
    case TASK_RUN:
        STDWTITL_drawBackground(task);
        break;
    case TASK_KILL:
        break;
    }
}

void STDWTITL_animateBackground(BackgroundTask *task) {
    if (task->state == TASK_RUN) {
        task->setState(task, TASK_DONE);
    }
}

BackgroundTask *STDWTITL_startBackgroundTask(s32 skip) {
    BackgroundTask *task = createTask(STDWTITL_tickBackground, sizeof(BackgroundTask), 0);

    task->animate = STDWTITL_animateBackground;
    task->layerId = STDWTITL_TITLE_LAYER;
    task->depth = 2;
    task->skip = skip;
    return task;
}

/* Once the fade out ends, starts the chosen mode; returns 1 then */
s32 STDWTITL_leaveTitle(TitleTask *task, TitleChildren *children) {
    s32 left = 0;

    if (children->fade->isDone(children->fade)) {
        switch (task->choice) {
        case 0:
            break;
        case 1:
            left = 1;
            GAME.funcs.newGame();
            GAME.funcs.resetPlayTime();
            D_80042728.clearUnk58();
            MEMCARD_FUNCS.setFileName();
            GAME.funcs.requestMode(0x2D7, 0);
            break;
        case 2:
            left = 1;
            GAME.funcs.newGame();
            D_80042728.clearUnk58();
            MEMCARD_FUNCS.setFileName();
            GAME.funcs.requestMode(0xC00, 0);
            break;
        case 3:
#if VERSION_US
            GAME_FUNCS.requestMode(0xE01, 0);
#elif VERSION_EU
            if (LANGUAGE == 0) {
                if (GAME.funcs.getPrevMode() == 0xE01) {
                    GAME.funcs.requestMode(0xE02, 0);
                } else {
                    GAME.funcs.requestMode(0xE01, 0);
                }
            } else {
                GAME_FUNCS.requestMode(0xE02, 0);
            }
#endif
            left = 1;
            break;
        }
    }
    return left;
}

/* Brings in the titles, the glint, the logo and the menu, then waits for an
   option; returns 1 once the chosen mode starts */
s32 STDWTITL_stepTitle(TitleTask *task, TitleChildren *children) {
    s32 left = 0;

    switch (task->substate) {
    case 0:
    default:
        children->title0->show(children->title0);
        children->title1->show(children->title1);
        task->timer = 0;
        task->setSubstate(task, 2);
        break;
    case 1:
        if (task->timer++ >= 0) {
            task->timer = 0;
            children->title1->show(children->title1);
            task->nextSubstate(task);
        }
        break;
    case 2:
        if (task->timer >= 10) {
            task->timer = 0;
            SOUND.playSound(0x611C0000);
            children->glint->show(children->glint);
            task->nextSubstate(task);
        }
        task->timer += GFX_FUNCS.getFrameTime();
        break;
    case 3:
        if (task->timer >= 12) {
            task->timer = 0;
            task->nextSubstate(task);
        }
        task->timer += GFX_FUNCS.getFrameTime();
        break;
    case 4:
        if (task->timer >= 12) {
            task->timer = 0;
            children->logo->show(children->logo);
            task->nextSubstate(task);
        }
        task->timer += GFX_FUNCS.getFrameTime();
        break;
    case 5:
        if (task->timer >= 12) {
            task->timer = 0;
            children->menu->show(children->menu);
            children->background->animate(children->background);
            task->nextSubstate(task);
        }
        task->timer += GFX_FUNCS.getFrameTime();
        break;
    case 6:
        task->choice = children->menu->getChoice(children->menu);
        if (task->choice != 0) {
            task->nextSubstate(task);
            children->fade = STDWTITL_startEdgeFadeTask();
            if (task->choice == 1) {
#if VERSION_US
                FILE_CACHE_REQUEST(0x158);
#elif VERSION_EU
                FILE_CACHE_REQUEST(0x166);
#endif
            }
        }
        break;
    case 7:
        children->fade->start(children->fade);
        task->nextSubstate(task);
        break;
    case 8:
        left = STDWTITL_leaveTitle(task, children);
        break;
    }
    return left;
}

void STDWTITL_tickTitle(TitleTask *task, TitleChildren *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        children->background = STDWTITL_startBackgroundTask(0);
#if VERSION_US
        children->title0 = STDWTITL_startTitle0Task(0);
        children->title1 = STDWTITL_startTitle1Task(0);
        children->glint = STDWTITL_startGlintTask(0);
        children->logo = STDWTITL_startLogoTask(0);
        children->menu = STDWTITL_startMenuTask(0);
#elif VERSION_EU
        if (LANGUAGE == 0) {
            children->title0 = STDWTITL_startTitle0AltTask(0);
            children->title1 = STDWTITL_startTitle1AltTask(0);
            children->logo = STDWTITL_startLogoTask(0);
            children->glint = STDWTITL_startGlintAltTask(0);
            children->menu = STDWTITL_startMenuTask(0);
        } else {
            children->title0 = STDWTITL_startTitle0Task(0);
            children->title1 = STDWTITL_startTitle1Task(0);
            children->glint = STDWTITL_startGlintTask(0);
            children->logo = STDWTITL_startLogoTask(0);
            children->menu = STDWTITL_startMenuTask(0);
        }
#endif
        task->timer = 0;
        break;
    case TASK_RUN:
        if (STDWTITL_stepTitle(task, children)) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        SOUND_STATE.stopSound(0x611C0000);
        break;
    }
}

TitleTask *STDWTITL_startTitleTask(Task *parent) {
    TitleTask *task = createTask(STDWTITL_tickTitle, sizeof(TitleTask), sizeof(TitleChildren));

    task->layerId = 0x1000;
    task->depth = 2;
    task->parent = parent;
    return task;
}

void STDWTITL_loadTitleImages(void) {
    TimLoader loader;

    initTimLoader(&loader);
#if VERSION_US
    loader.setImagePos(0x280, 0);
    loader.setClutPos(0, 0x1F0);
    loader.loadArchive(FILE_CACHE.getEntry(STDWTITL_titleImages[1].images));
    STDWTITL_spriteBank = STDWTITL_titleImages[1].sprites;
#elif VERSION_EU
    loader.setImagePos(0x280, 0x100);
    loader.setClutPos(0, 0x1F0);
    loader.loadArchive(FILE_CACHE.getEntry(STDWTITL_titleImages[LANGUAGE].images));
    STDWTITL_spriteBank = STDWTITL_titleImages[LANGUAGE].sprites;
#endif
    loader.setClutPos(0, 0x1F3);
    loader.setImagePos(0x300, 0);
    loader.loadArchive(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(4)));
    loader.setImagePos(0x340, 0);
    loader.loadArchive(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(5)));
    loader.setImagePos(0x380, 0);
    loader.loadArchive(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(6)));
    loader.setImagePos(0x3C0, 0);
    loader.loadArchive(FILE_CACHE.getEntry(STDWTITL_BACKGROUND(7)));
}

void STDWTITL_startFade(Fade *fade, s32 fadeIn) {
    fade->active = 1;
    if (fadeIn) {
        SOUND.playSound(0x40019);
        fade->step = 0x1000 / fade->duration;
        fade->level = 0;
    } else {
        SOUND.playSound(0x4001A);
        fade->level = 0x1000;
        fade->step = -(0x1000 / fade->duration * 2);
    }
}

s32 STDWTITL_stepFade(Fade *fade) {
    if (!fade->active) {
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

void STDWTITL_startTween(Tween *tween, s32 from, s32 to, s32 duration) {
    if (from != to) {
        tween->duration = duration;
        tween->fixed = from << 8;
        tween->value = from;
        tween->target = to;
        tween->active = 1;
        tween->step = ((to - from) << 8) / tween->duration;
    }
}

s32 STDWTITL_stepTween(Tween *tween) {
    if (!tween->active) {
        return 1;
    }
    tween->fixed += tween->step;
    tween->value = tween->fixed >> 8;
    if (tween->step > 0) {
        if (tween->target < tween->value) {
            tween->value = tween->target;
            tween->active = 0;
            return 1;
        }
    } else if (tween->value < tween->target) {
        tween->value = tween->target;
        tween->active = 0;
        return 1;
    }
    return 0;
}
