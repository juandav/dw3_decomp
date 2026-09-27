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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", ResetRCnt);

OBJECT_END();
