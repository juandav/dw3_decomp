#include "psyq.h"

int PadChkVsync(void) {
    int ret = D_80055588;

    D_80055588 = 0;
    return ret;
}

OBJECT_END();
