#include "psyq.h"

typedef struct UserFuncArg {
    long data[4];
} UserFuncArg;

extern UserFuncArg D_800820F8[];
extern long (*D_80082138[])(UserFuncArg *arg);

void UserFuncInit(void) {
    D_8005C2E8 = -1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_userfunc", UserFuncOpen);

void UserFuncExecute(void) {
    if (D_8005C2E8 >= 0) {
        if (D_80082138[D_8005C2E8](&D_800820F8[D_8005C2E8]) != 0) {
            D_8005C2E8--;
        }
    }
}

long UserFuncComplete(void) {
    return (u_long)D_8005C2E8 >> 31;
}

OBJECT_END();
