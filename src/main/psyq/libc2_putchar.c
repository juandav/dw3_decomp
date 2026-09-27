#include "psyq.h"

extern long D_800557F0;

inline void _putchar(char c) {
    long *p;
    long n;

    switch (c) {
    case '\n':
        _putchar('\r');
        D_800557F0 = 0;
        break;
    case '\t':
        do {
            _putchar(' ');
        } while (D_800557F0 & 7);
        return;
    default:
        if (((char *)D_800555C1)[(u_char)c] & 0x97) {
            D_800557F0++;
        }
        break;
    }
    if (D_800557F4 >= 32) {
        write(1, D_80080998, D_800557F4);
        D_800557F4 = 0;
    }
    p = &D_800557F4;
    n = *p;
    D_80080998[n] = c;
    *p = n + 1;
}

void _putchar_flash(void) {
    if (D_800557F4 > 0) {
        write(1, D_80080998, D_800557F4);
        D_800557F4 = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libc2_putchar", putchar);

OBJECT_END();
