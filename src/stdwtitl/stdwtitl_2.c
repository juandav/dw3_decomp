#include "stdwtitl.h"

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
    sprite.draw(FILE_CACHE.getEntry(0x08760000), 0, 0, 0);
    sprite.setTexture(0x340, 0);
    sprite.draw(FILE_CACHE.getEntry(0x08760001), 0, 0, 0);
    sprite.setTexture(0x380, 0);
    sprite.draw(FILE_CACHE.getEntry(0x08760002), 0, 0, 0);
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
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760003), frame0, 0, 0);
    }
    if (frame1 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760003), frame1, 0, 0);
    }
    if (frame2 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760003), frame2, 0, 0);
    }
    if (frame3 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760003), frame3, 0, 0);
    }
    if (frame4 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760008), frame4, 0, 0);
    }
    if (frame5 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760008), frame5, 0, 0);
    }
    if (frame6 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760008), frame6, task->pos6.x, task->pos6.y);
    }
    if (frame7 != 300) {
        sprite.draw(FILE_CACHE_GET_ENTRY[0](0x08760008), frame7, task->pos7.x, task->pos7.y);
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

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_animateBackground);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startBackgroundTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_leaveTitle);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepTitle);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_tickTitle);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startTitleTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_loadTitleImages);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startFade);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepFade);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startTween);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepTween);
