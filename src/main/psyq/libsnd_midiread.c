#include "psyq.h"

int _SsGetSeqData(short, short);
extern _SsFCALL D_80080C98; /* SsFCALL */
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

/* _SsGetSeqData passes a byte of the sequence too, which this doesn't use */
void _SsSeqGetEof(short sep, short seq, u_char type) {
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

int _SsGetSeqData(short sep, short seq) {
    SeqStruct *score = &D_80080D38[sep][seq];
    u_char c;
    u_char d1, d2;
    u_char data;
    int eof = 0;

    c = *score->readPos++;
    if ((D_80080D38[sep][seq].flags & 0x401) == 0x401 && score->readPos == score->endPos + 1) {
        _SsSeqGetEof(sep, seq, *score->readPos);
        return -1;
    }
    if (c & 0x80) {
        score->channel = c & 0xF;
        switch (c & 0xF0) {
        case 0x90:
            score->status = 0x90;
            d1 = *score->readPos++;
            d2 = *score->readPos++;
            score->delta = _SsReadDeltaValue(sep, seq);
            D_80080C98.noteon(sep, seq, d1, d2);
            break;
        case 0xB0:
            score->status = 0xB0;
            data = *score->readPos++;
            D_80080C98.control[CC_NUMBER](sep, seq, data);
            break;
        case 0xC0:
            score->status = 0xC0;
            data = *score->readPos++;
            D_80080C98.programchange(sep, seq, data);
            break;
        case 0xE0:
            score->status = 0xE0;
            score->readPos++;
            D_80080C98.pitchbend(sep, seq);
            break;
        case 0xF0:
            score->status = 0xFF;
            data = *score->readPos++;
            if (data == 0x2F) {
                eof = 1;
                _SsSeqGetEof(sep, seq, 0x2F);
            } else {
                D_80080C98.metaevent(sep, seq, data);
            }
            break;
        }
    } else {
        switch (score->status) {
        case 0x90:
            d2 = *score->readPos++;
            score->delta = _SsReadDeltaValue(sep, seq);
            D_80080C98.noteon(sep, seq, c, d2);
            break;
        case 0xB0:
            D_80080C98.control[CC_NUMBER](sep, seq, c);
            break;
        case 0xC0:
            D_80080C98.programchange(sep, seq, c);
            break;
        case 0xE0:
            D_80080C98.pitchbend(sep, seq);
            break;
        case 0xFF:
            if (c == 0x2F) {
                eof = 1;
                _SsSeqGetEof(sep, seq, 0x2F);
            } else {
                D_80080C98.metaevent(sep, seq, c);
            }
            break;
        }
    }
    return eof;
}

OBJECT_END();
