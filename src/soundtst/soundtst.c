#include "soundtst.h"

extern char SOUNDTST_STR_SELECT_VAB[]; /* "－てんそうするＶＡＢをせんたくしてください－" */
extern char SOUNDTST_STR_SOUND_TEST[]; /* "サウンドテスト" */
extern char SOUNDTST_STR_CURSOR[]; /* "＞" */
extern SoundTestEntry *SOUNDTST_soundLists[];
extern SoundTestEntry SOUNDTST_banks[];
extern RECT SOUNDTST_screenRect;

Task *SOUNDTST_createSoundTest(void);

void SOUNDTST_updateScene(Task *task, Task **items) {
    switch (task->state) {
    case 0:
    default:
        items[0] = SOUNDTST_createSoundTest();
        task->nextState(task);
        break;
    case 1:
        if (PAD.getPressed(0) & 8) {
            GAME_FUNCS.requestMode(0x1500, 0);
            task->nextState(task);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task *SOUNDTST_start(void) {
    return createTask(SOUNDTST_updateScene, sizeof(Task), 4);
}

void SOUNDTST_moveCursor(SoundTest *task, s32 delta, s32 *cursor, s32 *top, s32 count) {
    s32 pos = *cursor + delta;

    if (pos >= 0 && pos < count) {
        *cursor = pos;
        if (pos >= *top + 8) {
            *top = pos - 7;
        }
        if (*top > *cursor) {
            *top = *cursor;
        }
    }
}

void SOUNDTST_playSounds(SoundTest *task, SoundTestWindows *win) {
    SoundTestEntry *list = SOUNDTST_soundLists[task->bankCursor];
    s32 i;
    s32 j;

    switch (task->step) {
    case 0:
    default:
        task->soundCursor = 0;
        task->soundTop = 0;
        task->soundCount = 0;
        while (list[task->soundCount].id != 0) {
            task->soundCount++;
        }
        win->header->setText(win->header, SOUNDTST_banks[task->bankCursor].name);
        task->playing = 0;
        task->nextStep(task);
    case 1:
        break;
    }
    if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x40) {
        SOUNDTST_moveCursor(task, 1, &task->soundCursor, &task->soundTop, task->soundCount);
    } else if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x10) {
        SOUNDTST_moveCursor(task, -1, &task->soundCursor, &task->soundTop, task->soundCount);
    } else if (PAD.getPressed(0) & 0x8000) {
        SOUND_STATE.stopAll();
    } else if (PAD.getPressed(0) & 0x4000) {
        task->setSubstate(task, 0);
    } else if (PAD.getPressed(0) & 0x2000) {
        task->voice = SOUND_STATE.playSound(list[task->soundCursor].id);
        task->playing = 1;
    } else if (task->playing != 0 && !(PAD.getHeld(0) & 0x2000)) {
        task->playing = 0;
        SOUND_STATE.keyOff(list[task->soundCursor].id, task->voice);
    }
    for (i = 0, j = task->soundTop; i < 8 && list[j].id != 0; i++, j++) {
        win->lines[i]->setText(win->lines[i], list[j].name);
        win->lines[i]->setVisible(win->lines[i], 1);
    }
    for (; i < 8; i++) {
        win->lines[i]->setVisible(win->lines[i], 0);
    }
    win->cursor->setPos(win->cursor, 0x20, (task->soundCursor - task->soundTop) * 16 + 0x46);
}

void SOUNDTST_loadBank(SoundTest *task, SoundTestWindows *win) {
    switch (task->step) {
    case 0:
    default:
        if (task->bank == 1) {
            SOUND_STATE.loadBankInto(0, 1);
        } else {
            SOUND_STATE.loadBank(task->bank);
        }
        task->step++;
    case 1:
        break;
    }
    if (SOUND_STATE.isLoading() == 0) {
        task->nextSubstate(task);
    }
}

void SOUNDTST_selectBank(SoundTest *task, SoundTestWindows *win) {
    s32 i;
    s32 j;

    switch (task->step) {
    case 0:
    default:
        task->bankCount = 0;
        while (SOUNDTST_banks[task->bankCount].id != 0) {
            task->bankCount++;
        }
        win->header->setText(win->header, SOUNDTST_STR_SELECT_VAB);
        task->nextStep(task);
    case 1:
        break;
    }
    if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x40) {
        SOUNDTST_moveCursor(task, 1, &task->bankCursor, &task->bankTop, task->bankCount);
    } else if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x10) {
        SOUNDTST_moveCursor(task, -1, &task->bankCursor, &task->bankTop, task->bankCount);
    } else if (PAD.getPressed(0) & 0x2000) {
        task->bank = SOUNDTST_banks[task->bankCursor].id;
        task->nextSubstate(task);
    }
    for (i = 0, j = task->bankTop; i < 8 && SOUNDTST_banks[j].id != 0; i++, j++) {
        win->lines[i]->setText(win->lines[i], SOUNDTST_banks[j].name);
        win->lines[i]->setVisible(win->lines[i], 1);
    }
    for (; i < 8; i++) {
        win->lines[i]->setVisible(win->lines[i], 0);
    }
    win->cursor->setPos(win->cursor, 0x20, (task->bankCursor - task->bankTop) * 16 + 0x46);
}

void SOUNDTST_updateSoundTest(SoundTest *task, SoundTestWindows *win) {
    Layer *res;
    s32 i;

    switch (task->state) {
    case 0:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x5000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        res = GFX.funcs.createLayer(&SOUNDTST_screenRect, 1, 0x1000);
        res->setBgColor(res, 0x1F, 0x1F, 0x1F);
        win->title = createTextWindow(0x1000, 1, 0x10, 0x1E);
        win->title->setText(win->title, SOUNDTST_STR_SOUND_TEST);
        win->header = createTextWindow(0x1000, 1, 0x20, 0x32);
        for (i = 0; i < 8; i++) {
            win->lines[i] = createTextWindow(0x1000, 1, 0x30, i * 16 + 0x46);
        }
        win->cursor = createTextWindow(0x1000, 1, 0x20, 0x46);
        win->cursor->setText(win->cursor, SOUNDTST_STR_CURSOR);
        task->nextState(task);
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            SOUNDTST_selectBank(task, win);
            break;
        case 1:
            SOUNDTST_loadBank(task, win);
            break;
        case 2:
            SOUNDTST_playSounds(task, win);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        GAME_FUNCS.requestMode(0x1500, 0);
        break;
    }
}

Task *SOUNDTST_createSoundTest(void) {
    return createTask(SOUNDTST_updateSoundTest, sizeof(SoundTest), sizeof(SoundTestWindows));
}

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", SOUNDTST_entryNames);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", SOUNDTST_STR_SELECT_VAB);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", SOUNDTST_STR_SOUND_TEST);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", SOUNDTST_STR_CURSOR);
