#include "psyq.h"

extern u_long D_80080D34;

void _SsGetMetaEvent(short sep, short seq, u_char event) {
    SeqStruct *score = &D_80080D38[sep][seq];
    u_char b0, b1, b2;
    u_char *p;
    long tempo;

    p = score->readPos;
    b0 = *p++;
    score->readPos = p;
    b1 = *score->readPos;
    score->readPos++;
    b2 = *score->readPos;
    score->readPos++;
    tempo = 60000000 / ((b0 << 16) | (b1 << 8) | b2);
    score->unk94 = tempo;
    if ((u_long)(score->unk50 * tempo * 10) < D_80080D34 * 60) {
        score->unk52 = (D_80080D34 * 600) / (score->unk50 * tempo);
        score->unk54 = score->unk52;
    } else {
        score->unk52 = -1;
        score->unk54 = (u_long)(score->unk50 * score->unk94 * 10) / (D_80080D34 * 60);
        if ((u_long)(score->unk50 * score->unk94 * 10) % (D_80080D34 * 60) > D_80080D34 * 30) {
            score->unk54++;
        }
    }
    score->delta = _SsReadDeltaValue(sep, seq);
}

OBJECT_END();
