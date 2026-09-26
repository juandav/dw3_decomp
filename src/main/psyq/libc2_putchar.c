#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libc2_putchar", _putchar);

void _putchar_flash(void) {
    if (D_800557F4 > 0) {
        write(1, D_80080998, D_800557F4);
        D_800557F4 = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libc2_putchar", putchar);

OBJECT_END();
