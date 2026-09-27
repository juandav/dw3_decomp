#include "psyq.h"

void _SsContBankChange(short seq, short sep) {
    SeqStruct *score = &D_80080D38[seq][sep];
    u_char vab = *score->readPos;

    score->readPos++;
    score->vabId = vab;
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
