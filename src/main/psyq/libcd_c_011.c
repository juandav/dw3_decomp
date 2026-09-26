#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_c_011", StCdInterrupt);

void func_8002C564(long *dst, long *src, u_long n) {
    u_long i = 0;

    if (n != 0) {
        do {
            *dst++ = *src++;
            i++;
        } while (i < n);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_c_011", func_8002C590);

OBJECT_END();
