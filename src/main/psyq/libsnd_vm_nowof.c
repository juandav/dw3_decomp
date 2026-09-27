#include "psyq.h"

extern u_short D_80081CF8;
extern u_short D_80081CFA;
extern u_short D_800815C0;
extern u_short D_800815C2;

void _SsVmKeyOffNow(int mode) {
    u_short voice = D_80081E00.voice;
    u_short lo;
    u_short hi;

    if (voice < 16) {
        lo = 1 << voice;
        hi = 0;
    } else {
        lo = 0;
        hi = 1 << (voice - 16);
    }
    D_800815D0[voice].unk1D = 0;
    D_800815D0[voice].unk4 = 0;
    D_800815D0[voice].unk0 = 0;
    D_80081CF8 |= lo;
    D_80081CFA |= hi;
    D_800815C0 &= ~D_80081CF8;
    D_800815C2 &= ~D_80081CFA;
}

OBJECT_END();
