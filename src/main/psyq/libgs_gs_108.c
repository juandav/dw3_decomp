#include "psyq.h"

extern long D_80080A84; /* GsLIGHT_MODE */

void GsSetLightMode(int mode) {
    switch (mode) {
    case 0:
        D_80080A84 = 0;
        break;
    case 1:
        D_80080A84 = 1;
        break;
    case 2:
        D_80080A84 = 2;
        break;
    case 3:
        D_80080A84 = 3;
        break;
    default:
        printf("not supported light mode %d\n", mode);
        break;
    }
}

OBJECT_END();
