#include "psyq.h"

void init_ring_status(int start, u_int count) {
    u_int i;
    long *p;

    i = 0;
    if (count != 0) {
        do {
            p = (long *)(D_80080C20 + ((i++ + start) << 5));
            *p = 0;
        } while (i < count);
    }
}

OBJECT_END();
