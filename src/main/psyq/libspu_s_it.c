#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_s_it", _spu_setInTransfer);

int _spu_getInTransfer(void) {
    return D_8005BA5C != 1;
}

OBJECT_END();
