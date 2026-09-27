#include "psyq.h"

extern int D_80055550;
extern int D_80055564;
extern PadPort *D_8005554C;

void _padInitDirPort(void);

void PadInitDirect(u_char *pad1, u_char *pad2) {
    int i;
    int j;
    PadPort *p;
    u_char *d;

    D_80055550 = 0;
    D_80055564 = 0;
    _padInitDirPort();
    D_8005554C[0].unk30 = pad1;
    D_8005554C[1].unk30 = pad2;
    p = D_8005554C;
    for (i = 0; i < 2; i++, p++) {
        p->unkC = NULL;
        p->unk10 = p;
        p->unk30[0] = 0xFF;
        p->unk30[1] = 0;
        d = p->unk5D;
        for (j = 0; j < 6; j++) {
            *d++ = 0xFF;
        }
    }
    D_80055550 = 1;
}

OBJECT_END();
