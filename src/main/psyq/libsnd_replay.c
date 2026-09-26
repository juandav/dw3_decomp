#include "psyq.h"

void _SsSndReplay(short seq, short sep) {
    SeqStruct *score = &D_80080D38[seq][sep];

    score->unk14 = 1;
    D_80080D38[seq][sep].flags &= ~8;
}

OBJECT_END();
