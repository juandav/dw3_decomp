#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdmaiini", PadStartCom);

void PadStopCom(void) {
    EnterCriticalSection();
    ChangeClearRCnt(3, 1);
    SysDeqIntRP(2, D_80055578);
    ExitCriticalSection();
}

OBJECT_END();
