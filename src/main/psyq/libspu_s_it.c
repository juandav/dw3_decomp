#include "psyq.h"

void _spu_setInTransfer(int mode) {
    if (mode == 1) {
        D_8005BA5C = 0;
    } else {
        D_8005BA5C = 1;
    }
}

int _spu_getInTransfer(void) {
    return D_8005BA5C != 1;
}

OBJECT_END();
