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

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_80083BA8);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_80083BD4);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_80083C40);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_80083FA0);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_80084054);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_800842C4);

INCLUDE_ASM("asm/soundtst/nonmatchings/soundtst", func_800844E0);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80082448);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80083AC4);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80083AF4);

INCLUDE_RODATA("asm/soundtst/nonmatchings/soundtst", D_80083B04);
