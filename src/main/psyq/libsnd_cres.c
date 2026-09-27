#include "psyq.h"

void _SsVmSetSeqVol(short seq_sep, u_short voll, u_short volr, short flag);
short _SsVmGetSeqVol(short seq_sep, short *voll, short *volr);

void _SsSndCrescendo(short sep, short seq) {
    u_short voll;
    u_short volr;
    long vol;
    long l;
    long r;
    SeqStruct *score = &D_80080D38[sep][seq];

    if (++score->unkA0 > score->unk9C) {
        D_80080D38[sep][seq].flags &= ~0x10;
    } else {
        vol = score->unk48 * score->unkA0 / score->unk9C;
        vol -= score->unk4A;
        if (vol != 0) {
            score->unk4A += vol;
            _SsVmGetSeqVol(sep | (seq << 8), (short *)&voll, (short *)&volr);
            l = voll + vol;
            if (l > 127) {
                l = 127;
            }
            if (l < 0) {
                l = 0;
            }
            r = volr + vol;
            if (r > 127) {
                r = 127;
            }
            if (r < 0) {
                r = 0;
            }
            _SsVmSetSeqVol(sep | (seq << 8), l, r, 1);
            if ((l == 127 && r == 127) || (l == 0 && r == 0)) {
                D_80080D38[sep][seq].flags &= ~0x10;
            }
        }
    }
    _SsVmGetSeqVol(sep | (seq << 8), &score->unk5C, &score->unk5E);
}

OBJECT_END();
