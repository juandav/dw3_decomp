#include "psyq.h"

extern long D_80080D30;
extern short D_800815BA;
void _SsVmSetSeqVol(short seq_sep, u_short voll, u_short volr, short flag);
void _SsVmSeqKeyOff(short seq_sep);

void func_8002FFF8(short sep) {
    int i;

    _SsVmSetSeqVol(sep, 0, 0, 1);
    _SsVmSeqKeyOff(sep);
    D_80080D30 &= ~(1 << sep);
    for (i = 0; i < D_800815BA; i++) {
        D_80080D38[sep][i].flags = 0;
        D_80080D38[sep][i].unk22 = -1;
        D_80080D38[sep][i].unk23 = 0;
        D_80080D38[sep][i].unk48 = 0;
        D_80080D38[sep][i].unk4A = 0;
        D_80080D38[sep][i].unk9C = 0;
        D_80080D38[sep][i].unkA0 = 0;
        D_80080D38[sep][i].unk4C = 0;
        D_80080D38[sep][i].unkAC = 0;
        D_80080D38[sep][i].unkA8 = 0;
        D_80080D38[sep][i].unkA4 = 0;
        D_80080D38[sep][i].unk4E = 0;
        D_80080D38[sep][i].voll = 0x7F;
        D_80080D38[sep][i].volr = 0x7F;
    }
}

void SsSeqClose(short seq) {
    func_8002FFF8(seq);
}

OBJECT_END();
