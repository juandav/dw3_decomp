#include "shocktst.h"

/* The kernel's file functions (sim: opens the file on the PC) */
long func_80024CB8(char *name, long mode);
long func_80024CC8(long fd, void *buf, long n);
long write(long fd, void *buf, long n);
long func_80024CE8(long fd);
int atoi(u8 *s);
int strcspn(u8 *s, char *reject);

extern char D_80082490[]; /* "パターンじっこう" */
extern char D_80082500[]; /* "しんどうテスト" */
extern char D_80082510[]; /* "×：じっこうていし" */
extern char D_80082524[]; /* "ＳＴＡＲＴ：もどる" */
extern ShockTestRow D_80084160[4];
extern char D_800841C0[3][0x40];
extern char *D_80084280[2];
extern char *D_80084288;

Task *func_80084134(void);
s32 func_80082D8C(ShockTest *task, ShockTestWindows *win);
void func_80083B88(ShockLoader *task);

void func_80082538(Task *task, Task **items) {
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
        items[0] = func_80084134();
        task->nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

Task *func_80082630(void) {
    return createTask(func_80082538, sizeof(Task), 4);
}

void func_8008265C(ShockTest *task, ShockTestWindows *win, s32 highlight) {
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

void func_80082A0C(ShockTest *task, ShockTestWindows *win, s32 pattern);

s32 func_800827FC(ShockTest *task, ShockTestWindows *win) {
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
    func_80082A0C(task, win, task->pattern);
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
        return 1;
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
        return -1;
    }
    return 0;
}

void func_80082A0C(ShockTest *task, ShockTestWindows *win, s32 pattern) {
    s32 i;

    win->pattern->setNumber(win->pattern, 1, pattern);
    for (i = 0; i < 2; i++) {
        win->powers[i]->setNumber(win->powers[i], 1, task->steps[i][pattern].power);
        win->times[i]->setNumber(win->times[i], 1, task->steps[i][pattern].time);
    }
}

void func_80082AC4(ShockTest *task, ShockTestWindows *win, s32 pattern) {
    s32 i;

    for (i = 0; i < 2; i++) {
        win->powers[i]->setNumber(win->powers[i], 1, task->steps[i][pattern].power);
        win->times[i]->setNumber(win->times[i], 1, task->timers[i]);
    }
}

s32 func_80082B58(ShockTest *task, ShockTestWindows *win, s32 pattern) {
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
        func_80082A0C(task, win, task->pattern);
        return 1;
    }
    func_80082AC4(task, win, task->pattern);
    return 0;
}

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082D8C);

s32 func_80082E58(ShockTest *task, ShockTestWindows *win) {
    if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1) ||
        ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_LEFT)) & 1)) {
        do {
            if (--task->column < 0) {
                task->column = 1;
            }
        } while (D_80084160[task->row].enabled[task->column] == 0);
    } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1) ||
               ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_RIGHT)) & 1)) {
        do {
            if (++task->column >= 2) {
                task->column = 0;
            }
        } while (D_80084160[task->row].enabled[task->column] == 0);
    }
    if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
        ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
        do {
            if (--task->row < 0) {
                task->row = 3;
            }
        } while (D_80084160[task->row].enabled[task->column] == 0);
    } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
               ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
        do {
            if (++task->row >= 4) {
                task->row = 0;
            }
        } while (D_80084160[task->row].enabled[task->column] == 0);
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
        func_8008265C(task, win, D_80084160[task->row].highlight[task->column + 2]);
        if (task->row == 3) {
            return -1;
        }
        return 1;
    }
    if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CIRCLE)) & 1) {
        return 2;
    }
    func_8008265C(task, win, D_80084160[task->row].highlight[task->column]);
    return 0;
}

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_800832C4);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_8008354C);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082478);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082490);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_8008363C);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083A78);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083B04);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_800824BC);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083B88);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083EAC);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80084134);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082500);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082510);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082524);
