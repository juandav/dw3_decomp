#include "psyq.h"

void _SsSetProgramChange(short seq, short sep, u_char prog) {
    SeqStruct *score = &D_80080D38[seq][sep];

    score->programs[score->channel] = prog;
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
