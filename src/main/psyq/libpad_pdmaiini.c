#include "psyq.h"

extern int D_80055550;
extern PadPort *D_8005554C;
extern volatile u_long *D_800554E0;
extern long D_8007F140[2];

void func_80024CF8(int, u_char *);

void PadStartCom(void) {
    volatile u_long *rc;

    D_80055550 = 0;
    EnterCriticalSection();
    SysDeqIntRP(2, D_80055578);
    func_80024CF8(2, D_80055578);
    rc = D_800554E0;
    rc[0] = -2;
    rc[1] |= 1;
    ChangeClearRCnt(3, 0);
    ExitCriticalSection();
    D_8005551C(D_8005554C);
    D_8005551C(D_8005554C + 1);
    D_8007F140[0] = D_8007F140[1] = 0;
    D_80055550 = 1;
}

void PadStopCom(void) {
    EnterCriticalSection();
    ChangeClearRCnt(3, 1);
    SysDeqIntRP(2, D_80055578);
    ExitCriticalSection();
}

OBJECT_END();
