#include "psyq.h"

int PadInfoAct(int port, int acno, int term) {
    PadPort *p = D_8005552C(port);
    u_char *act;

    if (acno < 0) {
        return p->unkE9;
    }
    if (acno < p->unkE9) {
        act = (u_char *)p->unk4 + acno * 5;
        switch (term) {
        case 1:
            return act[0];
        case 2:
            return act[1];
        case 3:
            return act[2];
        case 4:
            return act[3];
        case 5:
            return act[4];
        }
    }
    return 0;
}

/* ASPSX padded the jump table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
