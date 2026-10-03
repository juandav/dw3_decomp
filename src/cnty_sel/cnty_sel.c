#include "cnty_sel.h"

RECT CNTY_SEL_screenRect = {0, 0, 320, 240};
RECT CNTY_SEL_vramRect = {0, 0, 1024, 512};
/* A little larger than the screen */
RECT CNTY_SEL_fadeRect = {0, -15, 320, 260};

/* Sprite frames of the chosen option once Start is pressed */
AnimFrame CNTY_SEL_cursorFlash[] = {
    {8, 4}, {9, 4}, {10, 4}, {11, 30}, {0xFF, 999},
};

/* Opening (0) and closing (1) tweens of each panel's scale */
PanelTween CNTY_SEL_topPanelTweens[] = {
    {10, 0x1000, 0},
    {5, 0, 0x1000},
};
PanelTween CNTY_SEL_rightPanelTweens[] = {
    {10, 0x1000, 0},
    {5, 0, 0x1000},
};
LeftPanelTween CNTY_SEL_leftPanelTweens[] = {
    {10, 0x1000, 0, 0},
    {5, 0, 0x1000, 0},
};

#if VERSION_EU
/* The language of each option */
u8 CNTY_SEL_languages[] = {2, 3, 5, 4, 6, 1, 0};
#endif

void CNTY_SEL_tickScreen(Task *task, MenuTask **menu) {
    TimLoader loader;
    Layer *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        /* Wait for the sound bank requested by CNTY_SEL_start */
        if (SOUND_STATE.isLoading() == 0) {
            /* Free every draw layer, get two 0xA000-byte primitive buffers
               and a 320x240 display */
            GFX.funcs.reset();
            GFX.funcs.allocPrimBuffers(0xA000);
            GFX.funcs.setDisplayMode(320, 240, 0, 0);
            /* Upload the images to VRAM from (640, 0), their CLUTs from (0, 496) */
            initTimLoader(&loader);
            loader.setImagePos(0x280, 0);
            loader.setClutPos(0, 0x1F0);
            loader.loadArchive(FILE_CACHE_GET_ENTRY[0](CNTY_SEL_IMAGES));
            /* A full-screen layer cleared to dark gray */
            layer = GFX.funcs.createLayer(&CNTY_SEL_screenRect, 3, CNTY_SEL_LAYER);
            layer->setBgColor(layer, 0x1F, 0x1F, 0x1F);
            *menu = CNTY_SEL_startMenuTask();
            task->nextState(task);
            SOUND_STATE.playSound(CNTY_SEL_MUSIC);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
        break;
    case TASK_KILL:
        SOUND_STATE.stopSound(CNTY_SEL_MUSIC);
        break;
    }
}

Task *CNTY_SEL_start(void) {
    Task *task;

    ClearImage2(&CNTY_SEL_vramRect, 0, 0, 0);
    task = createTask(CNTY_SEL_tickScreen, sizeof(Task), sizeof(MenuTask *));
    SOUND_STATE.loadBank(CNTY_SEL_SOUND_BANK);
    return task;
}

void CNTY_SEL_drawBackground(BackgroundTask *task) {
    SpriteDrawer sprite;
    s32 offset;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(CNTY_SEL_LAYER, 1);
    sprite.setTexture(0x280, 0);
    /* The background repeats every 96 pixels */
    offset = (s16)((s16)(task->scroll / 2) % 96);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](CNTY_SEL_SPRITES), SPRITE_BACKGROUND, offset, offset);
}

s32 CNTY_SEL_getFadeLevel(s32 time) {
    if (time >= 30) {
        return 255;
    }
    return time * 255 / 30;
}

void CNTY_SEL_drawFade(s32 level) {
    Layer *layer = GFX.funcs.getLayer(CNTY_SEL_LAYER);
    u_long *ot = (u_long *)layer->getOtEntry(layer, 0);
    POLY_F4 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;

    setlen(poly, 5);
    poly->r0 = poly->g0 = poly->b0 = level;
    setcode(poly, 0x2A); /* semi-transparent POLY_F4 */
    poly->x0 = CNTY_SEL_fadeRect.x;
    poly->x1 = CNTY_SEL_fadeRect.x + CNTY_SEL_fadeRect.w;
    poly->x2 = CNTY_SEL_fadeRect.x;
    poly->x3 = CNTY_SEL_fadeRect.x + CNTY_SEL_fadeRect.w;
    poly->y0 = CNTY_SEL_fadeRect.y;
    poly->y1 = CNTY_SEL_fadeRect.y;
    poly->y2 = CNTY_SEL_fadeRect.y + CNTY_SEL_fadeRect.h;
    poly->y3 = CNTY_SEL_fadeRect.y + CNTY_SEL_fadeRect.h;
    mode = (DR_TPAGE *)(poly + 1);
    addPrim(ot, poly);
    /* Blending mode 2: subtract the polygon's color from the screen */
    setDrawTPage(mode, 0, 1, getTPage(0, 2, 320, 0));
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void CNTY_SEL_tickBackground(BackgroundTask *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->scroll = 0;
        break;
    case TASK_RUN:
        task->scroll = (s16)(task->scroll + 1) % 192;
        CNTY_SEL_drawBackground(task);
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->fade = 0;
            task->substate = 1;
        }
        task->scroll = (s16)(task->scroll + 1) % 192;
        CNTY_SEL_drawBackground(task);
        CNTY_SEL_drawFade(CNTY_SEL_getFadeLevel(task->fade++));
        if (task->fade >= 30) {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_KILL:
        break;
    }
}

BackgroundTask *CNTY_SEL_startBackgroundTask(void) {
    return createTask(CNTY_SEL_tickBackground, sizeof(BackgroundTask), 0);
}

/* Advances anim by the frames elapsed and returns the frame to show (0xFF at the end) */
s16 CNTY_SEL_stepAnimation(AnimState *anim, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 elapsed = GFX_FUNCS.getFrameTime();

    if (elapsed > 4) {
        elapsed = 4;
    }
    if (depth == 0) {
        anim->timer -= elapsed;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (frame->frame == 0xFF) {
            return 0xFF;
        }
        /* Skip the frames that were shorter than the time elapsed */
        CNTY_SEL_stepAnimation(anim, frames, depth + 1);
    }
    return frame->frame;
}

void CNTY_SEL_drawCursor(CursorTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(CNTY_SEL_LAYER, 1);
    sprite.setTexture(0x280, 0);
    sprite.setClutRow(task->frame);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](CNTY_SEL_SPRITES), SPRITE_OPTIONS + task->selection, 0, 0);
}

void CNTY_SEL_setCursorSelection(CursorTask *task, s16 selection) {
    task->selection = selection;
}

void CNTY_SEL_tickCursor(CursorTask *task) {
    s16 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        break;
    case TASK_RUN:
        task->blink++;
        task->blink %= 32;
        task->frame = task->blink / 4;
        CNTY_SEL_drawCursor(task);
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = CNTY_SEL_cursorFlash[0].duration;
            task->substate++;
        }
        frame = CNTY_SEL_stepAnimation(&task->anim, CNTY_SEL_cursorFlash, 0);
        task->frame = frame;
        if (frame != 0xFF) {
            CNTY_SEL_drawCursor(task);
        } else {
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_KILL:
        break;
    }
}

CursorTask *CNTY_SEL_startCursorTask(void) {
    CursorTask *task = createTask(CNTY_SEL_tickCursor, sizeof(CursorTask), 0);

    task->setSelection = CNTY_SEL_setCursorSelection;
    return task;
}

s32 CNTY_SEL_getTopPanelScale(PanelTask *task, s32 phase) {
    s32 time = task->time;
    s32 duration = CNTY_SEL_topPanelTweens[phase].duration;

    if (time >= duration) {
        return CNTY_SEL_topPanelTweens[phase].to;
    }
    return CNTY_SEL_topPanelTweens[phase].from +
           (CNTY_SEL_topPanelTweens[phase].to - CNTY_SEL_topPanelTweens[phase].from) * time / duration;
}

void CNTY_SEL_drawTopPanel(PanelTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(CNTY_SEL_LAYER, 1);
    sprite.setTexture(0x280, 0);
    sprite.setPivot(148, 0);
    sprite.setScale(task->scaleX, task->scaleY, 0x1000);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](CNTY_SEL_SPRITES), SPRITE_TOP_PANEL, 148, 0);
}

void CNTY_SEL_tickTopPanel(PanelTask *task) {
    s16 phase;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->scaleX = 0x1000;
        task->scaleY = 0;
        task->phase = 0;
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            phase = task->phase;
            if (CNTY_SEL_topPanelTweens[phase].duration < task->time++) {
                task->phase ^= 1;
                task->setSubstate(task, 0);
                task->scaleY = CNTY_SEL_topPanelTweens[phase].to;
            } else {
                task->scaleY = CNTY_SEL_getTopPanelScale(task, phase);
            }
            break;
        }
        CNTY_SEL_drawTopPanel(task);
        break;
    case TASK_DONE:
        task->time = 0;
        task->setState(task, TASK_RUN);
        task->setSubstate(task, 1);
        CNTY_SEL_drawTopPanel(task);
        break;
    case TASK_KILL:
        break;
    }
}

PanelTask *CNTY_SEL_startTopPanelTask(void) {
    return createTask(CNTY_SEL_tickTopPanel, sizeof(PanelTask), 0);
}

s32 CNTY_SEL_getRightPanelScale(PanelTask *task, s32 phase) {
    s32 time = task->time;
    s32 duration = CNTY_SEL_rightPanelTweens[phase].duration;

    if (time >= duration) {
        return CNTY_SEL_rightPanelTweens[phase].to;
    }
    return CNTY_SEL_rightPanelTweens[phase].from +
           (CNTY_SEL_rightPanelTweens[phase].to - CNTY_SEL_rightPanelTweens[phase].from) * time / duration;
}

void CNTY_SEL_drawRightPanel(PanelTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(CNTY_SEL_LAYER, 1);
    sprite.setTexture(0x280, 0);
    sprite.setPivot(320, 20);
    sprite.setScale(task->scaleX, task->scaleY, 0x1000);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](CNTY_SEL_SPRITES), SPRITE_RIGHT_PANEL, 320, 20);
}

void CNTY_SEL_tickRightPanel(PanelTask *task) {
    s16 phase;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->scaleY = 0x1000;
        task->scaleX = 0;
        task->phase = 0;
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            phase = task->phase;
            if (CNTY_SEL_rightPanelTweens[phase].duration < task->time++) {
                task->phase ^= 1;
                task->setSubstate(task, 0);
                task->scaleX = CNTY_SEL_rightPanelTweens[phase].to;
            } else {
                task->scaleX = CNTY_SEL_getRightPanelScale(task, phase);
            }
            break;
        }
        CNTY_SEL_drawRightPanel(task);
        break;
    case TASK_DONE:
        task->time = 0;
        task->setState(task, TASK_RUN);
        task->setSubstate(task, 1);
        CNTY_SEL_drawRightPanel(task);
        break;
    case TASK_KILL:
        break;
    }
}

PanelTask *CNTY_SEL_startRightPanelTask(void) {
    return createTask(CNTY_SEL_tickRightPanel, sizeof(PanelTask), 0);
}

s32 CNTY_SEL_getLeftPanelScale(PanelTask *task, s32 phase) {
    s32 time = task->time;
    s32 duration = CNTY_SEL_leftPanelTweens[phase].duration;

    if (time >= duration) {
        return CNTY_SEL_leftPanelTweens[phase].to;
    }
    return CNTY_SEL_leftPanelTweens[phase].from +
           (CNTY_SEL_leftPanelTweens[phase].to - CNTY_SEL_leftPanelTweens[phase].from) * time / duration;
}

void CNTY_SEL_drawLeftPanel(PanelTask *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
    sprite.setLayerId(CNTY_SEL_LAYER, 1);
    sprite.setTexture(0x280, 0);
    sprite.setAltClut(0, 0x1F0);
    sprite.setPivot(0, 158);
    sprite.setScale(task->scaleX, task->scaleY, 0x1000);
    sprite.draw(FILE_CACHE_GET_ENTRY[0](CNTY_SEL_SPRITES), SPRITE_LEFT_PANEL, 0, 158);
}

void CNTY_SEL_tickLeftPanel(PanelTask *task) {
    s16 phase;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        task->scaleY = 0x1000;
        task->scaleX = 0;
        task->phase = 0;
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            phase = task->phase;
            if (CNTY_SEL_leftPanelTweens[phase].duration < task->time++) {
                task->phase ^= 1;
                task->setSubstate(task, 0);
                task->scaleX = CNTY_SEL_leftPanelTweens[phase].to;
            } else {
                task->scaleX = CNTY_SEL_getLeftPanelScale(task, phase);
            }
            break;
        }
        CNTY_SEL_drawLeftPanel(task);
        break;
    case TASK_DONE:
        task->time = 0;
        task->setState(task, TASK_RUN);
        task->setSubstate(task, 1);
        CNTY_SEL_drawLeftPanel(task);
        break;
    case TASK_KILL:
        break;
    }
}

PanelTask *CNTY_SEL_startLeftPanelTask(void) {
    return createTask(CNTY_SEL_tickLeftPanel, sizeof(PanelTask), 0);
}

void CNTY_SEL_tickMenu(MenuTask *task, MenuChildren *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children->background = CNTY_SEL_startBackgroundTask();
        children->topPanel = CNTY_SEL_startTopPanelTask();
        children->rightPanel = CNTY_SEL_startRightPanelTask();
        children->leftPanel = CNTY_SEL_startLeftPanelTask();
        task->selection = 0;
        task->timer = 0;
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case MENU_OPEN_RIGHT_PANEL:
        default:
            children->rightPanel->setState(children->rightPanel, TASK_DONE);
            task->timer = 0;
            task->nextSubstate(task);
            break;
        case MENU_WAIT_RIGHT_PANEL:
            if (task->timer++ >= 6) {
                task->nextSubstate(task);
            }
            break;
        case MENU_OPEN_LEFT_PANEL:
            task->timer = 0;
            children->leftPanel->setState(children->leftPanel, TASK_DONE);
            task->nextSubstate(task);
            break;
        case MENU_WAIT_LEFT_PANEL:
            if (task->timer++ >= 11) {
                task->nextSubstate(task);
            }
            break;
        case MENU_OPEN_TOP_PANEL:
            task->timer = 0;
            children->topPanel->setState(children->topPanel, TASK_DONE);
            task->nextSubstate(task);
            break;
        case MENU_WAIT_TOP_PANEL:
            if (task->timer++ >= 6) {
                task->nextSubstate(task);
            }
            break;
        case MENU_SHOW_CURSOR:
            children->cursor = CNTY_SEL_startCursorTask();
            task->nextSubstate(task);
            break;
        case MENU_SELECT:
            if (PAD_PRESSED(PAD_START)) {
                SOUND_STATE.playSound(SE_START);
                children->cursor->setState(children->cursor, TASK_DONE);
                task->nextSubstate(task);
                task->timer = 0;
#if VERSION_EU
                LANGUAGE = CNTY_SEL_languages[task->selection];
#endif
            } else {
                /* Options 0-4 are a column moved through with Up and Down. Options 5
                   and 6 are a second one reached with step 1, which nothing sets */
                switch (task->step) {
                case 0:
                default:
                    if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
                        if (task->selection > 0) {
                            SOUND_STATE.playSound(SE_CURSOR);
                            task->selection--;
                        }
                    } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
                        if (task->selection < 4) {
                            SOUND_STATE.playSound(SE_CURSOR);
                            task->selection++;
                        }
                    } else if (PAD_PRESSED(PAD_LEFT)) {
                        /* Left does nothing in this column */
                    }
                    break;
                case 1:
                    if (PAD_PRESSED(PAD_LEFT) || PAD_REPEATED(PAD_LEFT)) {
                        if (task->selection != 6) {
                            SOUND_STATE.playSound(SE_CURSOR);
                        }
                        task->selection = 6;
                    } else if (PAD_PRESSED(PAD_RIGHT) || PAD_REPEATED(PAD_RIGHT)) {
                        if (task->selection == 6) {
                            SOUND_STATE.playSound(SE_CURSOR);
                            task->selection = 5;
                        } else {
                            task->selection = 1;
                            SOUND_STATE.playSound(SE_CURSOR);
                            task->setStep(task, 0);
                        }
                    }
                    break;
                }
            }
            children->cursor->setSelection(children->cursor, task->selection);
            break;
        case MENU_WAIT_FLASH:
            if (++task->timer >= 43) {
                task->nextSubstate(task);
            }
            break;
        case MENU_CLOSE_PANELS:
            children->rightPanel->setState(children->rightPanel, TASK_DONE);
            children->leftPanel->setState(children->leftPanel, TASK_DONE);
            children->topPanel->setState(children->topPanel, TASK_DONE);
            task->timer = 0;
            task->nextSubstate(task);
            break;
        case MENU_WAIT_PANELS:
            if (++task->timer >= 6) {
                task->nextSubstate(task);
            }
            break;
        case MENU_FADE_OUT:
            children->background->setState(children->background, TASK_DONE);
            task->nextSubstate(task);
            break;
        case MENU_WAIT_FADE:
            if (++task->timer >= 31) {
                task->nextSubstate(task);
            }
            break;
        case MENU_EXIT:
#if VERSION_US
            /* switch to game mode 0xE01 */
            GAME_FUNCS.requestMode(0xE01, 0);
#elif VERSION_EU
            /* switch to game mode 0xE01, or 0xE02 for a language but 0 */
            if (LANGUAGE == 0) {
                GAME_FUNCS.requestMode(0xE01, 0);
            } else {
                GAME_FUNCS.requestMode(0xE02, 0);
            }
#endif
            task->setState(task, TASK_KILL);
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

MenuTask *CNTY_SEL_startMenuTask(void) {
    return createTask(CNTY_SEL_tickMenu, sizeof(MenuTask), sizeof(MenuChildren));
}
