#include "psyq.h"

extern long D_80080C14;

u_long StGetNext(u_long **addr, u_long **header) {
    volatile u_short *hdr = (u_short *)(D_80080C20 + D_80080C0C * 32);

    if (*hdr == 1) {
        D_80080C0C = 0;
        if (D_80080C14 != 0) {
            *hdr = 0;
        }
        hdr = (u_short *)(D_80080C20 + D_80080C0C * 32);
    }
    if (*hdr != 2) {
        return 1;
    }
    *hdr = 4;
    *addr = (u_long *)(D_80080C20 + D_80080C24 * 32 + D_80080C0C * 2016);
    *header = (u_long *)hdr;
    return 0;
}

OBJECT_END();
