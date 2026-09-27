#include "psyq.h"

u_long SpuSetTransferStartAddr(u_long addr) {
    if (addr - 0x1010 > 0x7EFE8) {
        return 0;
    }
    D_8005BA40 = _spu_FsetRXXa(-1, addr);
    return D_8005BA40 << D_8005BA50;
}

OBJECT_END();
