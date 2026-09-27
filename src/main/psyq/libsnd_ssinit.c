#include "psyq.h"

extern u_short D_8005B824[16];
extern long D_80080DB8[32][16];
extern long D_80080D2C;
extern long D_80080D30;
extern long D_80080D34;

void _SsVmInit(int voices);

void _SsInit(void) {
    u_short *reg;
    int i;
    int j;

    reg = (u_short *)0x1F801D80;
    for (i = 0; i < 16; i++) {
        *reg++ = D_8005B824[i];
    }
    _SsVmInit(24);
    for (j = 0; j < 32; j++) {
        for (i = 0; i < 16; i++) {
            D_80080DB8[j][i] = 0;
        }
    }
    D_80080D34 = 60;
    D_80080D30 = 0;
    D_80080D2C = 0;
}

OBJECT_END();
