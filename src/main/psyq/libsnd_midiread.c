#include "psyq.h"

void _SsGetSeqData(short, short);
void _SsVmSeqKeyOff(short seq_sep);
void _SsSndNextSep(short sep, short seq);

void _SsSeqPlay(short sep, short seq) {
    SeqStruct *s = &D_80080D38[sep][seq];
    long delta;

    if (s->delta - s->unk54 > 0) {
        if (s->unk52 > 0) {
            s->unk52--;
        } else if (s->unk52 == 0) {
            s->unk52 = s->unk54;
            s->delta--;
        } else {
            s->delta -= s->unk54;
        }
    } else if (s->unk54 >= s->delta) {
        delta = s->delta;
        for (;;) {
            _SsGetSeqData(sep, seq);
            if (s->delta == 0) continue;
            delta += s->delta;
            if (delta >= s->unk54) break;
        }
        s->delta = delta - s->unk54;
    }
}

void _SsSeqGetEof(short sep, short seq) {
    SeqStruct *score = &D_80080D38[sep][seq];

    score->unk21++;
    if (score->unk20 == 0) {
        score->unk88 = 0;
        score->unk1C = 0;
        score->delta = 0;
        if (D_80080D38[sep][seq].flags & 0x400) {
            score->readPos = score->unkC;
        } else {
            score->readPos = score->startPos;
        }
    } else if (score->unk21 < score->unk20) {
        score->unk88 = 0;
        score->unk1C = 0;
        score->delta = 0;
        if (D_80080D38[sep][seq].flags & 0x400) {
            score->readPos = score->unkC;
            score->loopPos = score->unkC;
        } else {
            score->readPos = score->startPos;
            score->loopPos = score->startPos;
        }
    } else {
        D_80080D38[sep][seq].flags &= ~1;
        D_80080D38[sep][seq].flags &= ~8;
        D_80080D38[sep][seq].flags &= ~2;
        D_80080D38[sep][seq].flags |= 0x200;
        D_80080D38[sep][seq].flags |= 4;
        score->unk14 = 0;
        if (D_80080D38[sep][seq].flags & 0x400) {
            score->loopPos = score->unkC;
        } else {
            score->loopPos = score->startPos;
        }
        if (score->unk22 != -1) {
            score->unk14 = 0;
            _SsSndNextSep(score->unk22, score->unk23);
            _SsVmSeqKeyOff(sep | (seq << 8));
        }
        _SsVmSeqKeyOff(sep | (seq << 8));
        score->delta = score->unk54;
    }
}

INCLUDE_ASM("main/nonmatchings/psyq/libsnd_midiread", _SsGetSeqData);

OBJECT_END();
