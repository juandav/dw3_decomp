#include "psyq.h"

extern int (*D_80055534)(PadPort *p);

void func_80020A54(PadPort *p);
int func_80020A7C(PadPort *p);

int PadSetActAlign(int port, u_char *data) {
    PadPort *p = D_8005552C(port);

    if (D_80055534(p) != 0) {
        return 0;
    }
    p->unk46 = 1;
    p->unk14 = func_80020A54;
    p->unk20 = data;
    p->unk18 = (void (*)())func_80020A7C;
    return 1;
}

void func_80020A54(PadPort *p) {
    _padSetCmd(p, 0x4D, p->unk20, 6);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdcmd2", func_80020A7C);

OBJECT_END();
