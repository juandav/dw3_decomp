#include "psyq.h"

void StSetRing(u_long *ring_addr, u_long ring_size) {
    D_80080C20 = (long)ring_addr;
    D_80080C24 = ring_size;
    StClearRing();
}

OBJECT_END();
