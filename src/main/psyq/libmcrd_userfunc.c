#include "psyq.h"

extern UserFuncArg D_800820F8[];
extern long (*D_80082138[])(UserFuncArg *arg);

void UserFuncInit(void) {
    D_8005C2E8 = -1;
}

void UserFuncOpen(long (*func)(UserFuncArg *arg)) {
    int n = D_8005C2E8 + 1;
    int i;

    if (n >= 4) {
        printf("libmcrd: event overflow\n");
        return;
    }
    D_8005C2E8 = n;
    D_80082138[n] = func;
    for (i = 3; i >= 0; i--) {
        D_800820F8[n].data[i] = 0;
    }
}

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

/* ASPSX padded the string table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
