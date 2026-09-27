#include "psyq.h"

void _SsVmSetSeqVol(short seq_sep, u_short voll, u_short volr, short flag);

void Snd_SetPlayMode(short sep, short seq, char play_mode, short count) {
    int mode = play_mode;
    SeqStruct *score = &D_80080D38[sep][seq];

    score->readPos = score->startPos;
    score->loopPos = score->startPos;
    score->unkC = score->startPos;
    D_80080D38[sep][seq].flags &= ~0x200;
    D_80080D38[sep][seq].flags &= ~0x4;
    score->unk20 = count;
    if (mode == 1) {
        D_80080D38[sep][seq].flags |= 1;
        score->unk14 = mode;
        score->unk21 = 0;
        _SsVmSetSeqVol(sep | (seq << 8), score->voll, score->volr, 1);
    } else if (mode == 0) {
        D_80080D38[sep][seq].flags |= 2;
    }
}

OBJECT_END();
