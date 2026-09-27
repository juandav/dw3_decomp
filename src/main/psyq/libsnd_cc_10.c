#include "psyq.h"

void _SsContPanpot(short seq, short sep, u_char pan) {
    short seqSep = seq | (sep << 8);
    SeqStruct *score = &D_80080D38[seq][sep];
    u_char ch = score->channel;

    _SsVmSetVol(seqSep, score->vabId, score->programs[ch], score->vol[ch], pan);
    score->panpot[ch] = pan;
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
