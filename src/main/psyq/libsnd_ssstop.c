#include "psyq.h"

void _SsVmSeqKeyOff(short seq_sep);

void _SsSndStop(short sep, short seq) {
    SeqStruct *score = &D_80080D38[sep][seq];
    int i;

    D_80080D38[sep][seq].flags &= ~1;
    D_80080D38[sep][seq].flags &= ~2;
    D_80080D38[sep][seq].flags &= ~8;
    D_80080D38[sep][seq].flags &= ~0x400;
    D_80080D38[sep][seq].flags |= 4;
    _SsVmSeqKeyOff(sep | (seq << 8));
    func_80034BE8();
    score->unk14 = 0;
    score->unk88 = 0;
    score->unk1C = 0;
    score->rpn1 = 0;
    score->rpn2 = 0;
    score->unk1E = 0;
    score->nrpn1 = 0;
    score->nrpn2 = 0;
    score->unk1F = 0;
    score->channel = 0;
    score->unk21 = 0;
    score->unk1C = 0;
    score->unk1D = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->delta = score->unk84;
    score->unk94 = score->unk8C;
    score->unk54 = score->unk56;
    score->readPos = score->startPos;
    score->loopPos = score->startPos;
    for (i = 0; i < 16; i++) {
        score->programs[i] = i;
        score->panpot[i] = 64;
        score->vol[i] = 127;
    }
    score->unk5C = 127;
    score->unk5E = 127;
}

void SsSeqStop(short seq) {
    _SsSndStop(seq, 0);
}

void SsSepStop(short seq, short sep) {
    _SsSndStop(seq, sep);
}

OBJECT_END();
