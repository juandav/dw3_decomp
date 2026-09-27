#include "psyq.h"

void _SsContRpn1(short seq, short sep, u_char value) {
    SeqStruct *score = &D_80080D38[seq][sep];

    score->rpn1 = value;
    score->unk1E++;
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
