/* The last object of FIGHTSTG.PRO (see fightstg.c). The USA version has the
   task of func_800A1048 here, which the European one has in fightstg_5.c;
   the European version has a task of its own here instead, whose jump table
   starts its rodata at 0x800832B8. */

#include "fightstg.h"

#if VERSION_US
INCLUDE_ASM("fightstg/nonmatchings/fightstg_7", func_800A1048);

void func_800A120C(void) {
    createTask(func_800A1048, 0x54, sizeof(Task *));
}
#elif VERSION_EU
/* a task of the European version's own */
INCLUDE_ASM("fightstg/nonmatchings/fightstg_7", func_800A1FE0);

void func_800A246C(void) {
    createTask(func_800A1FE0, 0xA4, 0);
}
#endif
