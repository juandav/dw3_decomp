#include "psyq.h"

void UserFuncInit(void) {
    D_8005C2E8 = -1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_userfunc", UserFuncOpen);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_userfunc", UserFuncExecute);

long UserFuncComplete(void) {
    return (u_long)D_8005C2E8 >> 31;
}

OBJECT_END();
