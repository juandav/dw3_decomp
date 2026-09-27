#include "soundtst.h"

extern char D_80083AC4[]; /* "－てんそうするＶＡＢをせんたくしてください－" */
extern char D_80083AF4[]; /* "サウンドテスト" */
extern char D_80083B04[]; /* "＞" */
extern SoundTestEntry *D_80084E7C[];
extern SoundTestEntry D_80084F98[];
extern RECT D_800851D8;

Task *func_800844E0(void);

void func_80083B08(Task *task, Task **items) {
    switch (task->state) {
    case 0:
    default:
        items[0] = func_800844E0();
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

Task *func_80083BA8(void) {
    return createTask(func_80083B08, sizeof(Task), 4);
}

void func_80083BD4(SoundTest *task, s32 delta, s32 *cursor, s32 *top, s32 count) {
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

void func_80083C40(SoundTest *task, SoundTestWindows *win) {
    SoundTestEntry *list = D_80084E7C[task->bankCursor];
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
        win->header->setText(win->header, D_80084F98[task->bankCursor].name);
        task->playing = 0;
        task->nextStep(task);
    case 1:
        break;
    }
    if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x40) {
        func_80083BD4(task, 1, &task->soundCursor, &task->soundTop, task->soundCount);
    } else if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x10) {
        func_80083BD4(task, -1, &task->soundCursor, &task->soundTop, task->soundCount);
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

void func_80083FA0(SoundTest *task, SoundTestWindows *win) {
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

void func_80084054(SoundTest *task, SoundTestWindows *win) {
    s32 i;
    s32 j;

    switch (task->step) {
    case 0:
    default:
        task->bankCount = 0;
        while (D_80084F98[task->bankCount].id != 0) {
            task->bankCount++;
        }
        win->header->setText(win->header, D_80083AC4);
        task->nextStep(task);
    case 1:
        break;
    }
    if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x40) {
        func_80083BD4(task, 1, &task->bankCursor, &task->bankTop, task->bankCount);
    } else if ((PAD.getPressed(0) | PAD.getRepeated(0)) & 0x10) {
        func_80083BD4(task, -1, &task->bankCursor, &task->bankTop, task->bankCount);
    } else if (PAD.getPressed(0) & 0x2000) {
        task->bank = D_80084F98[task->bankCursor].id;
        task->nextSubstate(task);
    }
    for (i = 0, j = task->bankTop; i < 8 && D_80084F98[j].id != 0; i++, j++) {
        win->lines[i]->setText(win->lines[i], D_80084F98[j].name);
        win->lines[i]->setVisible(win->lines[i], 1);
    }
    for (; i < 8; i++) {
        win->lines[i]->setVisible(win->lines[i], 0);
    }
    win->cursor->setPos(win->cursor, 0x20, (task->bankCursor - task->bankTop) * 16 + 0x46);
}

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_800842C4);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_800844E0);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80082448);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80083AC4);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80083AF4);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80083B04);
