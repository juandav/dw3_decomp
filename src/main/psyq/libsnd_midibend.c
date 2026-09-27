#include "psyq.h"

void _SsVmPitchBend(short seq_sep, char vabId, u_char prog, u_char bend);

void _SsSetPitchBend(short seq, short sep) {
    SeqStruct *score = &D_80080D38[seq][sep];
    u_char bend = *score->readPos;
    u_char ch = score->channel;

    score->readPos++;
    _SsVmPitchBend(seq | (sep << 8), score->vabId, score->programs[ch], bend);
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
