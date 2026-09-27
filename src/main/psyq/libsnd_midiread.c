#include "psyq.h"

void _SsGetSeqData(short, short);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_midiread", _SsSeqGetEof);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_midiread", _SsGetSeqData);

OBJECT_END();
