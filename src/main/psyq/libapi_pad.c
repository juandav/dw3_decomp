#include "psyq.h"

extern long *D_8005C2C0;

void SetInitPadFlag(long flag) {
    D_8005C2B8 = flag;
}

long ReadInitPadFlag(void) {
    return D_8005C2B8;
}

void PAD_init(char *bufA, long lenA, char *bufB, long lenB) {
    _remove_ChgclrPAD();
    EnterCriticalSection();
    _patch_pad();
    ExitCriticalSection();
    ChangeClearPAD(0);
    func_8003B444();
    func_8003B588(bufA, lenA, bufB, lenB);
    D_8005C2B8 = 1;
}

long InitPAD(char *bufA, long lenA, char *bufB, long lenB) {
    _remove_ChgclrPAD();
    EnterCriticalSection();
    _patch_pad();
    ExitCriticalSection();
    ChangeClearPAD(0);
    func_8003B444();
    func_8003B568(bufA, lenA, bufB, lenB);
    D_8005C2B8 = 1;
}

long StartPAD(void) {
    func_8003B578();
    ChangeClearPAD(0);
    EnablePAD();
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", func_8003B444);

int func_8003B4BC(void) {
    volatile int i, j, k;

    D_8005C2BC[5] = 0;
    i = 10;
    while (--i != -1) {
    }
    return 0;
}

int func_8003B524(void) {
    if ((D_8005C2C0[1] & 1) == 0 || (D_8005C2C0[0] & 1) == 0) {
        return 0;
    }
    return 1;
}

OBJECT_END();
