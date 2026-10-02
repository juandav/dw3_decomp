#include "psyq.h"

void MemCardInit(long val) {
    InitCARD(val);
    StartCARD();
    func_8003B1C8();
}

void MemCardEnd(void) {
    StopCARD();
}

OBJECT_END();
