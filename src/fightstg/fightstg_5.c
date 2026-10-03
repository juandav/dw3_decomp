/* The fifth object of FIGHTSTG.PRO (see fightstg.c), from the battle
   script: its rodata starts at 0x800825D0 (USA). */

#include "fightstg.h"

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008ADB0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008ADEC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008ADF4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008ADFC);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AE04);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AE0C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AE14);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AE1C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008AF74);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B400);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B628);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B784);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008B9A0);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008BA4C);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008BBD4);

INCLUDE_ASM("fightstg/nonmatchings/fightstg_5", func_8008BC94);

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
