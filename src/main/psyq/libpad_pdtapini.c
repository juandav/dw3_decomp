#include "psyq.h"

extern PadPort *D_8005554C;
extern long D_80055500[2];
extern long D_80055550;
extern long D_80055564;
void _padInitMtapPort(void);

void PadInitMtap(u_char *buf1, u_char *buf2) {
    PadPort *p;
    PadPort *q;
    int i, j, k;
    u_char *d;

    D_80055550 = 0;
    D_80055564 = 1;
    _padInitMtapPort();
    D_8005554C[0].unk30 = buf1;
    D_8005554C[1].unk30 = buf2;
    for (i = 0, p = D_8005554C; i < 2; i++, p++) {
        p->unk10 = p;
        p->unk30[0] = 0xFF;
        p->unk30[1] = 0;
        D_80055500[i] = 0;
        d = p->unk5D;
        for (k = 0; k < 6; k++) {
            *d++ = 0xFF;
        }
        q = p->unkC;
        for (j = 0; j < 4; j++, q++) {
            q->unk10 = p;
            q->unk30 = p->unk30 + 2 + j * 8;
            q->prevCmd = 0xFF;
            q->len = 0;
            q->actLen = 0;
            q->unk30[0] = 0xFF;
            q->unk30[1] = 0;
            q->unk3C = p->unk3C + 2 + j * 8;
            q->unk40 = p->unk40 + 3 + j * 8;
            d = q->unk5D;
            for (k = 0; k < 6; k++) {
                *d++ = 0xFF;
            }
        }
    }
    D_80055550 = 1;
}

OBJECT_END();
