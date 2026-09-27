#include "psyq.h"

void _SsContNrpn2(short seq, short sep, u_char value) {
    SeqStruct *score = *(D_80080D38 + seq) + sep;

    switch (value) {
    case 20:
        score->nrpn2 = value;
        score->unk1C = 1;
        score->delta = _SsReadDeltaValue(seq, sep);
        score->loopPos = score->readPos;
        break;
    case 30:
        score->nrpn2 = value;
        if (score->unk1D == 0) {
            score->unk15 = 0;
            score->delta = _SsReadDeltaValue(seq, sep);
        } else if (score->unk1D < 127) {
            score->unk1D--;
            score->delta = _SsReadDeltaValue(seq, sep);
            if (score->unk1D != 0) {
                score->readPos = score->loopPos;
            } else {
                score->unk15 = 0;
            }
        } else {
            _SsReadDeltaValue(seq, sep);
            score->delta = 0;
            score->readPos = score->loopPos;
        }
        break;
    default:
        score->nrpn2 = value;
        score->unk1F++;
        score->delta = _SsReadDeltaValue(seq, sep);
        break;
    }
}

OBJECT_END();
