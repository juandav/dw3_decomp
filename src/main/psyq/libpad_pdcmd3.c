#include "psyq.h"

extern int (*D_80055534)(PadPort *p);

void func_80020BE4(PadPort *p);
int func_80020C3C(PadPort *port);

int PadSetMainMode(int port, int offs, int lock) {
    PadPort *p = D_8005552C(port);

    if (D_80055534(p) != 0) {
        return 0;
    }
    p->unk51[0] = offs;
    p->unk51[1] = lock;
    p->unk46 = 1;
    p->unk14 = func_80020BE4;
    p->unk18 = (void (*)())func_80020C3C;
    p->unk53 = offs == p->unkE4;
    return 1;
}

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
