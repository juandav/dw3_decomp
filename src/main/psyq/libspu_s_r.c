#include "psyq.h"

u_long func_8003A3E8(u_char *addr, u_long size) {
    if (size > 0x7EFF0) {
        size = 0x7EFF0;
    }
    _spu_Fw(addr, size);
    if (D_8005BA60 == 0) {
        D_8005BA5C = 0;
    }
    return size;
}

OBJECT_END();
