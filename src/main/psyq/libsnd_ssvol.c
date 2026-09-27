#include "psyq.h"

void _SsVmSetSeqVol(short seq_sep, u_short voll, u_short volr, int flag);

void _SsSndSetVol(short sep, short seq, u_short voll, u_short volr) {
    SeqStruct *score = *(D_80080D38 + sep) + seq;

    if (score->flags != 1) {
        score->voll = voll;
        score->volr = volr;
    } else {
        _SsVmSetSeqVol(sep | (seq << 8), voll, volr, 1);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssvol", SsSeqSetVol);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssvol", SsSepSetVol);

OBJECT_END();
