/* The fifth object of FIGHTSTG.PRO (see fightstg.c), from the battle
   script: its rodata starts at 0x800825D0 (USA). */

#include "fightstg.h"

s32 func_8008ADB0(BattleScript *script, s32 type) {
    switch (type) {
    case 0:
    default:
        return script->unk50 != 0 ? 0x10 : 0;
    case 1:
        return 0;
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 0x10;
    case 5:
        return 0x11;
    case 6:
        return 0x12;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AE1C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AF74);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B400);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B628);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B784);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B9A0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008BA4C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008BBD4);

void func_8008BC94(BattleScript *script, Unk80092350 **fade) {
    s32 op = *script->pc++;
    s32 frames = *script->pc++;

    switch (op) {
    case 0:
        *fade = func_80092494(frames);
        break;
    case 1:
        if (*fade != NULL) {
            func_8009245C(*fade, frames);
        }
        break;
    }
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008BD10);

Task *func_8008C090(void) {
    return createTask(func_8008BD10, 0xB4, 16 * sizeof(Task *));
}

#if VERSION_EU
/* the European version has the task of func_800A1048 here */
INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_800A1048);

void func_800A120C(void) {
    createTask(func_800A1048, 0x54, sizeof(Task *));
}
#endif

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008C0BC);

void func_8008C8B8(s32 arg0) {
    ((Unk8008C0BC *)createTask(func_8008C0BC, sizeof(Unk8008C0BC), sizeof(Task *)))->unk50 = arg0;
}
