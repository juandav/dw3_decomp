#include "psyq.h"

extern u_long D_80080D34;

long _SsInitSoundSep(short sep, short seq, u_char vabId, u_char *addr) {
    SeqStruct *score;
    long i;
    long size = 0;
    long tempo;
    long b0;
    long b1;
    long b2;
    long b3;
    long b4;
    long len;

    score = &D_80080D38[sep][seq];
    score->unk20 = 1;
    score->unk15 = 0;
    score->status = 0;
    score->channel = 0;
    score->rpn1 = 0;
    score->rpn2 = 0;
    score->nrpn1 = 0;
    score->nrpn2 = 0;
    score->unk1C = 0;
    score->unk1D = 0;
    score->unk1E = 0;
    score->unk1F = 0;
    score->unk14 = 0;
    score->unk21 = 0;
    score->unk52 = 1;
    score->unk50 = 0;
    score->vabId = vabId;
    score->unk56 = 0;
    score->unk84 = 0;
    score->unk88 = 0;
    score->unk8C = 0;
    score->delta = 0;
    score->channelMute = 0;
    score->unk24[0] = 0;
    score->unk24[1] = 0;
    for (i = 0; i < 16; i++) {
        score->panpot[i] = 64;
        score->programs[i] = i;
        score->vol[i] = 127;
    }
    score->readPos = addr;
    if (seq == 0) {
        if (*score->readPos == 'S' || *score->readPos == 'p') {
            score->readPos += 5;
            if (*score->readPos++ != 0) {
                printf("This is not SEP Data.\n");
                return -1;
            }
            score->readPos += 2;
            size += 8;
        }
    } else {
        score->readPos += 2;
        size += 2;
    }
    b0 = *score->readPos++;
    b1 = *score->readPos++;
    score->unk50 = b1 | b0 << 8;
    b2 = *score->readPos++;
    b3 = *score->readPos++;
    b4 = *score->readPos++;
    tempo = b4 | (b2 << 16 | b3 << 8);
    score->unk8C = tempo;
    size += 5;
    if (tempo / 2 < 60000000 % tempo) {
        score->unk8C = 60000000 / tempo + 1;
    } else {
        score->unk8C = 60000000 / tempo;
    }
    score->unk94 = score->unk8C;
    score->unk24[0] = *score->readPos++;
    score->unk24[1] = *score->readPos++;
    b0 = *score->readPos++;
    b1 = *score->readPos++;
    b2 = *score->readPos++;
    b3 = *score->readPos++;
    len = b3 | ((b0 << 24) + (b1 << 16) + (b2 << 8));
    score->delta = score->unk84 = _SsReadDeltaValue(sep, seq);
    score->startPos = score->readPos;
    score->loopPos = score->readPos;
    score->unkC = score->readPos;
    score->endPos = NULL;
    size += 6;
    if (score->unk50 * score->unk8C * 10 < D_80080D34 * 60) {
        score->unk54 = score->unk52 = D_80080D34 * 600 / (score->unk50 * score->unk8C);
    } else {
        score->unk52 = -1;
        score->unk54 = score->unk50 * score->unk8C * 10 / (D_80080D34 * 60);
        if (D_80080D34 * 30 < score->unk50 * score->unk8C * 10 % (D_80080D34 * 60)) {
            score->unk54++;
        }
    }
    score->unk56 = score->unk54;
    return size + len;
}

__asm__(".section .rodata\n\t.align 4\n");
OBJECT_END();
