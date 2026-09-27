#include "psyq.h"

u_long StFreeRing(u_long *base) {
    int i;
    int index;
    short *hdr;
    short *p;
    short n;

    index = (base - (u_long *)(D_80080C20 + D_80080C24 * 32)) / 504;
    hdr = (short *)(D_80080C20 + index * 32);
    n = hdr[3];
    if (hdr[0] != 4) {
        return 1;
    }
    i = 0;
    if (n > 0) {
        do {
            p = (short *)(D_80080C20 + ((i++ + index) << 5));
            *p = 0;
        } while (i < n);
    }
    D_80080C0C = i + index;
    return 0;
}

OBJECT_END();
