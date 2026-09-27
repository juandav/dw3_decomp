#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", SetRCnt);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", GetRCnt);

long StartRCnt(u_long spec) {
    int timer = spec & 0xFFFF;

    D_8005B868[1] |= D_8005B870[timer];
    return timer < 3;
}

long StopRCnt(u_long spec) {
    D_8005B868[1] &= ~D_8005B870[spec & 0xFFFF];
    return 1;
}

long ResetRCnt(unsigned long spec) {
    int c = spec & 0xFFFF;

    if (c >= 3) {
        return 0;
    }
    D_8005B86C[c * 8] = 0;
    return 1;
}

OBJECT_END();
