#include "psyq.h"

void StUnSetRing(void) {
    EnterCriticalSection();
    if (D_8005A2E8 == 1) {
        func_8002E3D8(NULL);
        func_8002E3B8(0);
    } else {
        func_8002E388(NULL);
        func_8002DE88(0);
    }
    *D_8005A200 = 0;
    *D_8005A20C = 0;
    ExitCriticalSection();
}

OBJECT_END();
