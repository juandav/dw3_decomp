#include "psyq.h"

extern long D_80080C80;
extern CdlLOC D_80080C28;
extern long D_80080C2C;

void data_ready_callback(void) {
    u_long *h = (u_long *)D_80080C20 + D_80080C08 * 8;

    *(u_short *)h = 2;
    D_80080C28 = *(CdlLOC *)&h[7];
    D_80080C2C = h[2];
    D_80080C08 = D_80080C04;
    if (D_80080C38 != NULL) {
        D_80080C38();
    }
    D_80080BFC = 0;
}

int StGetBackloc(CdlLOC *loc) {
    if (D_80080C80 != 0) {
        return -1;
    }
    CdIntToPos(CdPosToInt(&D_80080C28) + 1, loc);
    return D_80080C2C;
}

OBJECT_END();
