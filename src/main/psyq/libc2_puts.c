#include "psyq.h"

void puts(char *s) {
    char c;

    if (s == NULL) {
        s = "<NULL>";
    }
    while ((c = *s++) != 0) {
        _putchar(c);
    }
    _putchar_flash();
}

/* ASPSX padded the string table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
