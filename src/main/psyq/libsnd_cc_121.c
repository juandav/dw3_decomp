#include "psyq.h"

void _SsContResetAll(short seq, short sep) {
    SeqStruct *score = &D_80080D38[seq][sep];
    int ch;

    func_80034598();
    func_80034BE8();
    ch = score->channel;
    score->programs[ch] = ch;
    score->rpn1 = 0;
    score->rpn2 = 0;
    score->vol[score->channel] = 0x7F;
    score->panpot[score->channel] = 0x40;
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
