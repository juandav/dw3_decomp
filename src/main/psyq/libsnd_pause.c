#include "psyq.h"

void _SsVmSeqKeyOff(short seq_sep);

void _SsSndPause(short seq, short sep) {
    SeqStruct *score = &D_80080D38[seq][sep];

    _SsVmSeqKeyOff(seq | (sep << 8));
    score->unk14 = 0;
    D_80080D38[seq][sep].flags &= ~2;
}

OBJECT_END();
