#include "psyq.h"

extern MATRIX D_80080B10;

void Gssub_make_matrix(MATRIX *m, short s, short c, char axis) {
    *m = D_80080B10;
    switch (axis) {
    case 'x':
    case 'X':
        m->m[1][1] = c;
        m->m[2][2] = c;
        m->m[1][2] = -s;
        m->m[2][1] = s;
        break;
    case 'y':
    case 'Y':
        m->m[0][0] = c;
        m->m[2][2] = c;
        m->m[0][2] = s;
        m->m[2][0] = -s;
        break;
    case 'z':
    case 'Z':
        m->m[0][0] = c;
        m->m[1][1] = c;
        m->m[0][1] = -s;
        m->m[1][0] = s;
        break;
    }
}

/* ASPSX padded the jump table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
