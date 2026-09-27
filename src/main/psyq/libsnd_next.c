#include "psyq.h"

void _SsSndNextSep(short seq, short sep) {
    SeqStruct *score = &D_80080D38[seq][sep];

    score->unk20 = 1;
    score->unk21 = 0;
    D_80080D38[seq][sep].flags &= ~0x100;
    D_80080D38[seq][sep].flags &= ~8;
    D_80080D38[seq][sep].flags &= ~2;
    D_80080D38[seq][sep].flags &= ~4;
    D_80080D38[seq][sep].flags &= ~0x200;
    score->unk14 = 1;
    score->readPos = score->startPos;
    D_80080D38[seq][sep].flags |= 1;
}

OBJECT_END();
