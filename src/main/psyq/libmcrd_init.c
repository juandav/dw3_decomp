#include "psyq.h"

void MemCardInit(long val) {
    InitCARD(val);
    StartCARD();
    func_8003B1C8();
}

void MemCardEnd(void) {
    StopCARD();
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_init", func_8003B1C8);

OBJECT_END();
