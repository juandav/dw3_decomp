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
    p->unk18 = func_80020A7C;
    return 1;
}

void func_80020A54(PadPort *p) {
    _padSetCmd(p, 0x4D, p->unk20, 6);
}

int func_80020A7C(PadPort *p) {
    int i;
    int j;
    int cnt;
    int n;
    u_char *d;

    i = 0;
    if (p->unkE9 != 0) {
        do {
            d = p->unk20;
            cnt = 0;
            for (j = 0; j < 6; j++) {
                if (*d++ == i) {
                    cnt++;
                }
            }
            n = ((u_char *)p->unk4)[i * 5 + 2];
            d = p->unk20;
            if (n == 0) {
                n = 1;
            }
            for (j = 0; j < 6; j++) {
                if (*d++ == i) {
                    if (cnt < n) {
                        p->unk5D[j] = 0xFF;
                        cnt--;
                    } else {
                        p->unk5D[j] = i;
                    }
                }
            }
        } while (++i < p->unkE9);
    }
    p->unk46 = 0xFE;
    return 0;
}

OBJECT_END();
