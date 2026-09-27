#include "psyq.h"

void StClearRing(void) {
    D_80080C0C = 0;
    D_80080C08 = 0;
    D_80080C04 = 0;
    D_80080BFC = 0;
    init_ring_status(0, D_80080C24);
    D_80080BEC = 0;
    D_80080BE4 = 0;
    D_80080BE0 = 0;
}

OBJECT_END();
