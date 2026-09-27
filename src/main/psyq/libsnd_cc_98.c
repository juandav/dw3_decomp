#include "psyq.h"

extern void (*D_80080DB8[][16])(short, short, u_char);

void _SsContNrpn1(short seq, short sep, u_char value) {
    SeqStruct *score = &D_80080D38[seq][sep];

    if (score->nrpn2 == 40) {
        if (D_80080DB8[seq][sep] != NULL) {
            D_80080DB8[seq][sep](seq, sep, value);
        }
    }
    if (score->nrpn2 != 30 && score->nrpn2 != 20 && score->nrpn2 != 40) {
        score->nrpn1 = value;
        score->unk1C = 0;
        score->unk1F++;
    }
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
