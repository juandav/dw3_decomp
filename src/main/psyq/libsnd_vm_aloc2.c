#include "psyq.h"

extern u_long D_80081CB8[];
extern u_short D_80081B30[];
extern u_char D_80081B10[];

void _SsVmDoAllocate(void) {
    int i;
    short sreg;
    int tone;
    u_short adsr2;
    short rr;

    sreg = D_80081E00.voice << 3;
    D_800815D0[D_80081E00.voice].unk6 = 0x7FFF;
    for (i = 0; i < 16; i++) {
        D_80081CB8[i] &= ~(1 << D_80081E00.voice);
    }
    if ((D_80081E00.vag & 1) > 0) {
        (D_80081B30 + sreg)[3] = D_80081DE4[(D_80081E00.vag - 1) / 2].reserved2;
        D_80081B10[D_80081E00.voice] |= 8;
    } else {
        (D_80081B30 + sreg)[3] = D_80081DE4[(D_80081E00.vag - 1) / 2].reserved2 >> 16;
        D_80081B10[D_80081E00.voice] |= 8;
    }
    tone = D_80081E00.prog * 16 + D_80081E00.tone;
    (D_80081B30 + sreg)[4] = D_80081DF0[tone].adsr1;
    adsr2 = D_80081DF0[tone].adsr2;
    rr = D_80081D98 + (adsr2 & 0x1F);
    adsr2 &= 0xFFE0;
    if (rr >= 0x20) {
        rr = 0x1F;
    }
    rr |= adsr2;
    (D_80081B30 + sreg)[5] = rr;
    D_80081B10[D_80081E00.voice] |= 0x30;
}

OBJECT_END();
