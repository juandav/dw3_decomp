#include "cnty_sel.h"

void CNTY_SEL_tickScreen(TaskHeader *task, MenuTask **menu) {
    Obj8001FBE0 loader;
    Resource *layer;

    switch (task->state) {
    case TASK_INIT:
    default:
        /* Wait for the sound bank requested by CNTY_SEL_start */
        if (D_80051194.unk4274() == 0) {
            D_8004D5B8.funcs.unk0[0]();
            D_8004D5B8.funcs.unk0[1](0xA000);
            D_8004D5B8.funcs.unk24(320, 240, 0, 0);
            func_8001FBE0(&loader);
            loader.methods[2](0x280, 0);
            loader.methods[3](0, 0x1F0);
            loader.methods[4](D_80044B68[0](CNTY_SEL_IMAGES));
            layer = D_8004D5B8.funcs.unk1C(&CNTY_SEL_screenRect, 3, CNTY_SEL_LAYER);
            layer->unk12C(layer, 0x1F, 0x1F, 0x1F);
            *menu = CNTY_SEL_startMenuTask();
            task->nextState(task);
            D_80051194.unk425C(CNTY_SEL_MUSIC);
        }
        break;
    case TASK_RUN:
    case TASK_TRIGGER:
        break;
    case TASK_END:
        D_80051194.unk427C(CNTY_SEL_MUSIC);
        break;
    }
}

TaskHeader *CNTY_SEL_start(void) {
    TaskHeader *task;

    ClearImage2(&CNTY_SEL_vramRect, 0, 0, 0);
    task = func_800144DC(CNTY_SEL_tickScreen, sizeof(TaskHeader), sizeof(MenuTask *));
    D_80051194.unk4268(CNTY_SEL_SOUND_BANK);
    return task;
}

void CNTY_SEL_drawBackground(BackgroundTask *task) {
    Obj8001F22C sprite;
    s32 offset;

    func_8001F22C(&sprite);
    sprite.methods[3](CNTY_SEL_LAYER, 1);
    sprite.methods[1](0x280, 0);
    /* The background repeats every 96 pixels */
    offset = (s16)((s16)(task->scroll / 2) % 96);
    sprite.methods[5](D_80044B68[0](CNTY_SEL_SPRITES), SPRITE_BACKGROUND, offset, offset);
}

s32 CNTY_SEL_getFadeLevel(s32 time) {
    if (time >= 30) {
        return 255;
    }
    return time * 255 / 30;
}

void CNTY_SEL_drawFade(s32 level) {
    Resource *layer = D_8004D5B8.funcs.unk2C(CNTY_SEL_LAYER);
    u_long *ot = (u_long *)layer->unk138(layer, 0);
    POLY_F4 *poly = D_8004D5B8.funcs.allocPrim();
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
    D_8004D5B8.funcs.setPrimEnd(mode + 1);
}

void CNTY_SEL_tickBackground(BackgroundTask *task) {
    switch (task->task.state) {
    case TASK_INIT:
    default:
        task->task.nextState(task);
        task->scroll = 0;
        break;
    case TASK_RUN:
        task->scroll = (s16)(task->scroll + 1) % 192;
        CNTY_SEL_drawBackground(task);
        break;
    case TASK_TRIGGER:
        if (task->task.substate == 0) {
            task->fade = 0;
            task->task.substate = 1;
        }
        task->scroll = (s16)(task->scroll + 1) % 192;
        CNTY_SEL_drawBackground(task);
        CNTY_SEL_drawFade(CNTY_SEL_getFadeLevel(task->fade++));
        if (task->fade >= 30) {
            task->task.setState(task, TASK_END);
        }
        break;
    case TASK_END:
        break;
    }
}

BackgroundTask *CNTY_SEL_startBackgroundTask(void) {
    return func_800144DC(CNTY_SEL_tickBackground, sizeof(BackgroundTask), 0);
}

/* Advances anim by the frames elapsed and returns the frame to show (0xFF at the end) */
s16 CNTY_SEL_stepAnimation(AnimState *anim, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 elapsed = D_8004D708.unk3C();

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
    Obj8001F22C sprite;

    func_8001F22C(&sprite);
    sprite.methods[3](CNTY_SEL_LAYER, 1);
    sprite.methods[1](0x280, 0);
    sprite.methods[6](task->frame);
    sprite.methods[5](D_80044B68[0](CNTY_SEL_SPRITES), SPRITE_OPTIONS + task->selection, 0, 0);
}

void CNTY_SEL_setCursorSelection(CursorTask *task, s16 selection) {
    task->selection = selection;
}

void CNTY_SEL_tickCursor(CursorTask *task) {
    s16 frame;

    switch (task->task.state) {
    case TASK_INIT:
    default:
        task->task.nextState(task);
        break;
    case TASK_RUN:
        task->blink++;
        task->blink %= 32;
        task->frame = task->blink / 4;
        CNTY_SEL_drawCursor(task);
        break;
    case TASK_TRIGGER:
        if (task->task.substate == 0) {
            task->anim.index = 0;
            task->anim.timer = CNTY_SEL_cursorFlash[0].duration;
            task->task.substate++;
        }
        frame = CNTY_SEL_stepAnimation(&task->anim, CNTY_SEL_cursorFlash, 0);
        task->frame = frame;
        if (frame != 0xFF) {
            CNTY_SEL_drawCursor(task);
        } else {
            task->task.setState(task, TASK_END);
        }
        break;
    case TASK_END:
        break;
    }
}

CursorTask *CNTY_SEL_startCursorTask(void) {
    CursorTask *task = func_800144DC(CNTY_SEL_tickCursor, sizeof(CursorTask), 0);

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

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawTopPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickTopPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startTopPanelTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_getRightPanelScale);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawRightPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickRightPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startRightPanelTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_getLeftPanelScale);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_drawLeftPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickLeftPanel);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startLeftPanelTask);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_tickMenu);

INCLUDE_ASM("asm/cnty_sel/nonmatchings/cnty_sel", CNTY_SEL_startMenuTask);
