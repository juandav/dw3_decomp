#include "stagslct.h"

extern char STAGSLCT_STR_STAGE_SELECT[]; /* "ステージセレクト" */
extern char STAGSLCT_STR_CURSOR[]; /* "＞" */
extern char *STAGSLCT_regionNames[6]; /* "ＵＳＡ", "ＥＮＧ", "ＦＲＡ", "ＩＴＡ", "ＧＥＲ", "ＳＰＮ" */
extern StageSelectEntry STAGSLCT_entries[];
extern RECT STAGSLCT_screenRect;
extern u16 STAGSLCT_biosVersion[10];
extern u16 STAGSLCT_biosVersionEnd;

Task *STAGSLCT_createStageSelect(void);
void STAGSLCT_updateStageSelect(Task *task, StageSelectWindows *win);

void STAGSLCT_updateScene(Task *task, Task **items) {
    switch (task->state) {
    case 0:
    default:
        items[0] = STAGSLCT_createStageSelect();
        task->nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

Task *STAGSLCT_start(void) {
    return createTask(STAGSLCT_updateScene, sizeof(Task), 4);
}

void STAGSLCT_moveCursor(StageSelect *sel, s32 delta) {
    s32 end = 0;
    s32 top = sel->top;
    s32 cursor = sel->cursor;

    do {
        sel->cursor += delta;
        if (sel->cursor < 0) {
            sel->cursor = 0;
            if (--sel->top < 0) {
                sel->top = 0;
                end = 1;
            }
        }
        if (sel->cursor > sel->lines - 1) {
            sel->cursor = sel->lines - 1;
            if (++sel->top > sel->count - sel->lines) {
                sel->top = sel->count - sel->lines;
                end = 1;
            }
        }
        if (STAGSLCT_entries[sel->top + sel->cursor].scene != 0) {
            return;
        }
    } while (end == 0);
    sel->top = top;
    sel->cursor = cursor;
}

void STAGSLCT_scrollPage(StageSelect *sel, s32 delta) {
    sel->top += delta;
    if (sel->top < 0) {
        sel->top = 0;
        return;
    }
    if (sel->top > sel->count - sel->lines) {
        sel->top = sel->count - sel->lines;
    }
}

INCLUDE_ASM("asm/stagslct/nonmatchings/stagslct", STAGSLCT_showBiosVersion);

void STAGSLCT_zoomTitle(StageSelect *sel, StageSelectWindows *win) {
    if (sel->fading != 0) {
        sel->fade += sel->fadeStep;
        if (sel->fadeStep > 0) {
            if (sel->fade > 0x1000) {
                sel->fade = 0x1000;
                sel->fading = 0;
            }
        } else if (sel->fade < 0) {
            sel->fade = 0;
            sel->fading = 0;
        }
        win->title->setScale(win->title, sel->fade, sel->fade);
    } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_SELECT)) & 1) {
        sel->fading = 1;
        if (sel->fade <= 0) {
            sel->fadeStep = 0x111;
        } else {
            sel->fadeStep = -0x111;
        }
        win->title->setPivot(win->title, 0x37, 0x28);
    }
}

INCLUDE_ASM("asm/stagslct/nonmatchings/stagslct", STAGSLCT_updateStageSelect);

Task *STAGSLCT_createStageSelect(void) {
    return createTask(STAGSLCT_updateStageSelect, 0, 0);
}

INCLUDE_RODATA("asm/stagslct/nonmatchings/stagslct", STAGSLCT_entryNames);

INCLUDE_RODATA("asm/stagslct/nonmatchings/stagslct", STAGSLCT_STR_STAGE_SELECT);

INCLUDE_RODATA("asm/stagslct/nonmatchings/stagslct", STAGSLCT_STR_CURSOR);
