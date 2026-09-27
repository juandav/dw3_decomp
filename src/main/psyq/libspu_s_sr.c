#include "psyq.h"

extern long D_8005B9BC;
extern long D_8005B9C0;
extern long D_8005B9C4;
extern short D_8005B9D0[2];
long _SpuIsInAllocateArea_(u_long addr);

long SpuSetReverb(long on_off) {
    u_short cnt;

    switch (on_off) {
    case SPU_OFF:
        cnt = D_8005BA28[0xD5];
        D_8005B9BC = 0;
        D_8005BA28[0xD5] = cnt & ~0x80;
        D_8005BA28[0xC2] = 0;
        D_8005BA28[0xC3] = 0;
        D_8005B9D0[0] = 0;
        D_8005B9D0[1] = 0;
        break;
    case SPU_ON:
        if (D_8005B9C0 != on_off && _SpuIsInAllocateArea_(D_8005B9C4)) {
            cnt = D_8005BA28[0xD5];
            D_8005B9BC = 0;
            D_8005BA28[0xD5] = cnt & ~0x80;
        } else {
            cnt = D_8005BA28[0xD5];
            D_8005B9BC = on_off;
            D_8005BA28[0xD5] = cnt | 0x80;
        }
        break;
    }
    return D_8005B9BC;
}

OBJECT_END();
