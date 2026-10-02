#include "psyq.h"

extern long *PAD_INTR_REGS;
extern long D_80081FE8;
extern int (*D_80081FEC[2])(void);
extern long D_80081FF4;

void func_80024CF8(int, u_char *);
int func_8003B4BC(void);
int func_8003B524(void);

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

int func_8003B444(void) {
    EnterCriticalSection();
    D_80081FEC[0] = func_8003B4BC;
    D_80081FEC[1] = func_8003B524;
    D_80081FE8 = 0;
    D_80081FF4 = 0;
    SysDeqIntRP(1, (u_char *)&D_80081FEC[-1]);
    func_80024CF8(1, (u_char *)&D_80081FEC[-1]);
    ExitCriticalSection();
    return 1;
}

int func_8003B4BC(void) {
    volatile int i, j, k;

    PAD_SIO_REGS[5] = 0;
    i = 10;
    while (--i != -1) {
    }
    return 0;
}

int func_8003B524(void) {
    if ((PAD_INTR_REGS[1] & 1) == 0 || (PAD_INTR_REGS[0] & 1) == 0) {
        return 0;
    }
    return 1;
}

OBJECT_END();
