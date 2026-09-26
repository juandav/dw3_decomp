#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_131", func_80029DB8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_131", func_8002A188);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_131", func_8002A274);

long func_8002A33C(long value) {
    long bits = 0;

    while (value > 0) {
        value >>= 1;
        bits++;
    }
    return bits;
}

OBJECT_END();
