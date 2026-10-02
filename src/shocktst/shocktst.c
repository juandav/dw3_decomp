#include "shocktst.h"

/* The kernel's file functions (sim: opens the file on the PC) */
long func_80024CB8(char *name, long mode);
long func_80024CC8(long fd, void *buf, long n);
long write(long fd, void *buf, long n);
long func_80024CE8(long fd);
int atoi(u8 *s);
int strcspn(u8 *s, char *reject);

extern char SHOCKTST_STR_PLAY_PATTERN[]; /* "パターンじっこう" */
extern char SHOCKTST_STR_VIBRATION_TEST[]; /* "しんどうテスト" */
extern char SHOCKTST_STR_CROSS_STOP[]; /* "×：じっこうていし" */
extern char SHOCKTST_STR_START_BACK[]; /* "ＳＴＡＲＴ：もどる" */
extern ShockTestRow SHOCKTST_menuRows[4];
extern char SHOCKTST_numberFormats[3][0x40];
extern char *SHOCKTST_motorNames[2];
extern char *SHOCKTST_textPath;

Task *SHOCKTST_createLoader(void);
s32 SHOCKTST_playAllPatterns(ShockTest *task, ShockTestWindows *win);
void SHOCKTST_convertText(ShockLoader *task);

void SHOCKTST_updateScene(Task *task, Task **items) {
    RECT rect;
    Layer *res;

    switch (task->state) {
    case 0:
    default:
        GFX.funcs.reset();
        GFX.funcs.allocPrimBuffers(0x5000);
        GFX.funcs.setDisplayMode(0x140, 0xF0, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0xF0;
        res = GFX.funcs.createLayer(&rect, 1, 0x1000);
        res->setBgColor(res, 0, 0, 0);
        items[0] = SHOCKTST_createLoader();
        task->nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

Task *SHOCKTST_start(void) {
    return createTask(SHOCKTST_updateScene, sizeof(Task), 4);
}

void SHOCKTST_highlight(ShockTest *task, ShockTestWindows *win, s32 highlight) {
    s32 i;

    win->pattern->setPalette(win->pattern, 0);
    for (i = 0; i < 2; i++) {
        win->times[i]->setPalette(win->times[i], 0);
        win->powers[i]->setPalette(win->powers[i], 0);
    }
    win->play->setPalette(win->play, 0);
    switch (highlight) {
    default:
        win->pattern->setPalette(win->pattern, 3);
        break;
    case 2:
        win->times[0]->setPalette(win->times[0], 3);
        break;
    case 3:
        win->times[1]->setPalette(win->times[1], 3);
        break;
    case 4:
        win->powers[0]->setPalette(win->powers[0], 3);
        break;
    case 5:
        win->powers[1]->setPalette(win->powers[1], 3);
        break;
    case 10:
        win->play->setPalette(win->play, 3);
        break;
    case 0:
        win->pattern->setPalette(win->pattern, 1);
        break;
    case 6:
        win->times[0]->setPalette(win->times[0], 1);
        break;
    case 7:
        win->times[1]->setPalette(win->times[1], 1);
        break;
    case 8:
        win->powers[0]->setPalette(win->powers[0], 1);
        break;
    case 9:
        win->powers[1]->setPalette(win->powers[1], 1);
        break;
    case 11:
        win->play->setPalette(win->play, 1);
        break;
    }
}

void SHOCKTST_showPattern(ShockTest *task, ShockTestWindows *win, s32 pattern);

s32 SHOCKTST_selectPattern(ShockTest *task, ShockTestWindows *win) {
    if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
        ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
        if (--task->pattern < 0) {
            task->pattern = 0;
        }
    } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
               ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
        if (++task->pattern > task->count - 1) {
            task->pattern = task->count - 1;
        }
    }
    win->pattern->setNumber(win->pattern, 1, task->pattern);
    SHOCKTST_showPattern(task, win, task->pattern);
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
        return 1;
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
        return -1;
    }
    return 0;
}

void SHOCKTST_showPattern(ShockTest *task, ShockTestWindows *win, s32 pattern) {
    s32 i;

    win->pattern->setNumber(win->pattern, 1, pattern);
    for (i = 0; i < 2; i++) {
        win->powers[i]->setNumber(win->powers[i], 1, task->steps[i][pattern].power);
        win->times[i]->setNumber(win->times[i], 1, task->steps[i][pattern].time);
    }
}

void SHOCKTST_showTimers(ShockTest *task, ShockTestWindows *win, s32 pattern) {
    s32 i;

    for (i = 0; i < 2; i++) {
        win->powers[i]->setNumber(win->powers[i], 1, task->steps[i][pattern].power);
        win->times[i]->setNumber(win->times[i], 1, task->timers[i]);
    }
}

s32 SHOCKTST_playPattern(ShockTest *task, ShockTestWindows *win, s32 pattern) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (task->motors[i] == 0) {
            if (task->steps[i][pattern].power != 0 && task->steps[i][pattern].time != 0) {
                PAD.setVibration(0, i, task->steps[i][pattern].time, task->steps[i][pattern].power);
                task->timers[i] = task->steps[i][pattern].time;
                task->motors[i] = 1;
            } else {
                task->motors[i] = -1;
            }
            win->powers[i]->setNumber(win->powers[i], 1, task->steps[i][pattern].power);
            win->times[i]->setNumber(win->times[i], 1, task->steps[i][pattern].time);
        } else if (task->motors[i] == 1) {
            if (--task->timers[i] < 0) {
                task->timers[i] = 0;
                task->motors[i] = -1;
            }
        }
    }
    if ((task->motors[0] == -1 && task->motors[1] == -1) ||
        ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1)) {
        for (i = 0; i < 2; i++) {
            PAD.setVibration(0, i, 0, 0);
        }
        SHOCKTST_showPattern(task, win, task->pattern);
        return 1;
    }
    SHOCKTST_showTimers(task, win, task->pattern);
    return 0;
}

INCLUDE_ASM("shocktst/nonmatchings/shocktst", SHOCKTST_playAllPatterns);

s32 SHOCKTST_moveCursor(ShockTest *task, ShockTestWindows *win) {
    if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1) ||
        ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1)) {
        do {
            if (--task->column < 0) {
                task->column = 1;
            }
        } while (SHOCKTST_menuRows[task->row].enabled[task->column] == 0);
    } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1) ||
               ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1)) {
        do {
            if (++task->column >= 2) {
                task->column = 0;
            }
        } while (SHOCKTST_menuRows[task->row].enabled[task->column] == 0);
    }
    if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
        ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
        do {
            if (--task->row < 0) {
                task->row = 3;
            }
        } while (SHOCKTST_menuRows[task->row].enabled[task->column] == 0);
    } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
               ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
        do {
            if (++task->row >= 4) {
                task->row = 0;
            }
        } while (SHOCKTST_menuRows[task->row].enabled[task->column] == 0);
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
        SHOCKTST_highlight(task, win, SHOCKTST_menuRows[task->row].highlight[task->column + 2]);
        if (task->row == 3) {
            return -1;
        }
        return 1;
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CIRCLE)) & 1) {
        return 2;
    }
    SHOCKTST_highlight(task, win, SHOCKTST_menuRows[task->row].highlight[task->column]);
    return 0;
}

s32 SHOCKTST_editValue(ShockTest *task, ShockTestWindows *win, TextWindow **windows, u8 *value, u8 toggle) {
    if (toggle) {
        if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
            ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
            *value = 1 - *value;
        }
    } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) {
        *value += 1;
    } else if ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) {
        *value += 10;
    } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) {
        *value -= 1;
    } else if ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) {
        *value -= 10;
    }
    SHOCKTST_showPattern(task, win, task->pattern);
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
        return 1;
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
        return -1;
    }
    return 0;
}

s32 SHOCKTST_editRow(ShockTest *task, ShockTestWindows *win) {
    switch (task->row) {
    case 0:
    default:
        if (SHOCKTST_selectPattern(task, win) != 0) {
            return 1;
        }
        break;
    case 1:
        task->step = task->column;
        if (SHOCKTST_editValue(task, win, win->times, &task->steps[task->step][task->pattern].time, 0) != 0) {
            return 1;
        }
        break;
    case 2:
        task->step = task->column;
        if (task->step != 0) {
            if (SHOCKTST_editValue(task, win, win->times, &task->steps[task->step][task->pattern].power, 0) != 0) {
                return 1;
            }
        } else if (SHOCKTST_editValue(task, win, win->times, &task->steps[0][task->pattern].power, 1) != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_STR_SLOW);

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_STR_FAST);

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_STR_PLAY_PATTERN);

void SHOCKTST_updateEditor(ShockTest *task, ShockTestWindows *win) {
    s32 i;
    s32 motor;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->windowId = 0x1000;
        win->pattern = createTextWindow(task->windowId, 1, 0x28, 0x3C);
        task->unk50 = FILE_CACHE_LOAD[0](0xC5);
        win->pattern->setString(win->pattern, SHOCKTST_numberFormats[0], -1);
        win->pattern->setNumber(win->pattern, 1, task->pattern);
        for (i = 0; i < 2; i++) {
            win->motors[i] = createTextWindow(task->windowId, 1, i * 100 + 0x3C, 0x50);
            win->motors[i]->setText(win->motors[i], SHOCKTST_motorNames[i]);
            win->times[i] = createTextWindow(task->windowId, 1, i * 100 + 0x3C, 0x64);
            win->times[i]->setString(win->times[i], SHOCKTST_numberFormats[1], -1);
            win->times[i]->setNumber(win->times[i], 1, task->steps[i][0].time);
            win->powers[i] = createTextWindow(task->windowId, 1, i * 100 + 0x3C, 0x78);
            win->powers[i]->setString(win->powers[i], SHOCKTST_numberFormats[2], -1);
            win->powers[i]->setNumber(win->powers[i], 1, task->steps[i][0].power);
        }
        win->play = createTextWindow(task->windowId, 1, 0x28, 0x8C);
        win->play->setText(win->play, SHOCKTST_STR_PLAY_PATTERN);
        break;
    case 1:
        switch (task->substate) {
        default:
            task->setSubstate(task, 0);
        case 0:
            switch (SHOCKTST_moveCursor(task, win)) {
            case 2:
                task->setSubstate(task, 4);
                break;
            case 1:
                task->nextSubstate(task);
                break;
            case -1:
                if ((PAD.getHeld(0) >> PAD.getButtonBit(0, PAD_L1)) & 1) {
                    task->setSubstate(task, 2);
                } else {
                    task->setSubstate(task, 3);
                }
                task->motors[0] = task->motors[1] = task->timers[0] = task->timers[1] = task->playing = 0;
                break;
            }
            break;
        case 1:
            if (SHOCKTST_editRow(task, win) != 0) {
                task->setSubstate(task, 0);
            }
            break;
        case 2:
            if (SHOCKTST_playAllPatterns(task, win) != 0) {
                task->setSubstate(task, 0);
            }
            break;
        case 3:
            if (SHOCKTST_playPattern(task, win, task->pattern) != 0) {
                task->setSubstate(task, 0);
            }
            break;
        case 4:
            if (MEMCARD_FUNCS.check(0) != 0) {
                task->setSubstate(task, 0);
            }
            break;
        }
        break;
    case 2:
        break;
    case 3:
        HEAP.free(task->steps[0]);
        HEAP.free(task->steps[1]);
        for (motor = 0; motor < 2; motor++) {
            PAD.setVibration(0, motor, 0, 0);
        }
        break;
    }
}

void SHOCKTST_loadPatterns(ShockTest *task, ShockFile *file) {
    s32 i;
    u8 *times = (u8 *)file + file->timesOffset;
    u8 *powers = (u8 *)file + file->powersOffset;

    for (i = 0; i < task->count; i++) {
        task->steps[0][i].time = times[0];
        task->steps[1][i].time = times[1];
        times += 2;
        task->steps[0][i].power = powers[0];
        task->steps[1][i].power = powers[1];
        powers += 2;
    }
}

ShockTest *SHOCKTST_createEditor(s32 count) {
    ShockTest *task = createTask(SHOCKTST_updateEditor, sizeof(ShockTest), sizeof(ShockTestWindows));

    task->count = count;
    task->steps[0] = HEAP.allocZeroed(count * sizeof(ShockStep), 2);
    task->steps[1] = HEAP.allocZeroed(task->count * sizeof(ShockStep), 2);
    return task;
}

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_PATH_DLSKDATA_TXT);

INCLUDE_ASM("shocktst/nonmatchings/shocktst", SHOCKTST_convertText);

void SHOCKTST_updateLoader(ShockLoader *task, ShockLoaderWindows *win) {
    s32 fd;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        win->title = createTextWindow(0x1000, 0, 0x14, 0x1E);
        win->title->setText(win->title, SHOCKTST_STR_VIBRATION_TEST);
        win->help[0] = createTextWindow(0x1000, 1, 0xDC, 0xB4);
        win->help[0]->setText(win->help[0], SHOCKTST_STR_CROSS_STOP);
        win->help[1] = createTextWindow(0x1000, 1, 0xDC, 0xC8);
        win->help[1]->setText(win->help[1], SHOCKTST_STR_START_BACK);
        task->text = HEAP.allocZeroed(0x4000, 2);
        task->file = HEAP.allocZeroed(0x4000, 2);
        if (task->text == NULL || task->file == NULL) {
            task->setState(task, 3);
            break;
        }
        fd = func_80024CB8(SHOCKTST_textPath, 1);
        if (fd == -1) {
            task->setState(task, 3);
            break;
        }
        func_80024CC8(fd, task->text, 0x4000);
        func_80024CE8(fd);
        SHOCKTST_convertText(task);
        if (task->file != NULL) {
            win->test = SHOCKTST_createEditor(task->file->count);
            SHOCKTST_loadPatterns(win->test, task->file);
        } else {
            win->test = SHOCKTST_createEditor(10);
        }
        break;
    case 1:
        if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_START)) & 1) {
            task->setState(task, 3);
        }
        break;
    case 2:
        break;
    case 3:
        if (task->file != NULL) {
            HEAP.free(task->file);
        }
        if (task->text != NULL) {
            HEAP.free(task->text);
        }
        GAME_FUNCS.requestMode(0x1500, 0);
        break;
    }
}

Task *SHOCKTST_createLoader(void) {
    return createTask(SHOCKTST_updateLoader, sizeof(ShockLoader), sizeof(ShockLoaderWindows));
}

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_STR_VIBRATION_TEST);

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_STR_CROSS_STOP);

INCLUDE_RODATA("shocktst/nonmatchings/shocktst", SHOCKTST_STR_START_BACK);
