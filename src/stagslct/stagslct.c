#include "stagslct.h"

extern char D_800844D8[]; /* "ステージセレクト" */
extern char D_800844FC[]; /* "＞" */
extern char *D_800859A4[6]; /* "ＵＳＡ", "ＥＮＧ", "ＦＲＡ", "ＩＴＡ", "ＧＥＲ", "ＳＰＮ" */
extern StageSelectEntry D_800859BC[];
extern RECT D_80086F1C;
extern u16 D_80086F24[10];
extern u16 D_80086F38;

Task *func_80085974(void);

void func_80084500(Task *task, Task **items) {
    switch (task->state) {
    case 0:
    default:
        items[0] = func_80085974();
        task->nextState(task);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}

Task *func_80084564(void) {
    return createTask(func_80084500, sizeof(Task), 4);
}

void func_80084590(StageSelect *sel, s32 delta) {
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
        if (D_800859BC[sel->top + sel->cursor].scene != 0) {
            return;
        }
    } while (end == 0);
    sel->top = top;
    sel->cursor = cursor;
}

void func_80084660(StageSelect *sel, s32 delta) {
    sel->top += delta;
    if (sel->top < 0) {
        sel->top = 0;
        return;
    }
    if (sel->top > sel->count - sel->lines) {
        sel->top = sel->count - sel->lines;
    }
}

INCLUDE_ASM("asm/stagslct/nonmatchings/stagslct", func_800846A4);

INCLUDE_ASM("asm/stagslct/nonmatchings/stagslct", func_800847C8);

INCLUDE_ASM("asm/stagslct/nonmatchings/stagslct", func_800848D0);

INCLUDE_ASM("asm/stagslct/nonmatchings/stagslct", func_80085974);

INCLUDE_RODATA("asm/stagslct/nonmatchings/stagslct", D_80082448);

INCLUDE_RODATA("asm/stagslct/nonmatchings/stagslct", D_800844D8);

INCLUDE_RODATA("asm/stagslct/nonmatchings/stagslct", D_800844FC);
