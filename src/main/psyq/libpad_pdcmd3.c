#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdcmd3", PadSetMainMode);

void func_80020BE4(PadPort *p) {
    switch (p->unk46) {
    case 2:
        _padSetCmd(p, 0x44, p->unk51, 2);
        break;
    case 3:
        _padSetCmd(p, 0x4D, p->unk5D, 6);
        break;
    }
}

int func_80020C3C(PadPort *port) {
    if (port->unk53 != 0) {
        if (port->unk46 == 2) {
            return 1;
        }
        port->unk46 = 0xFE;
    } else {
        D_8005551C();
    }
    return 0;
}

OBJECT_END();
