#include "psyq.h"

void _SsSndSetVolData(short seq, short sep, int vol, long count) {
    SeqStruct *s = &D_80080D38[seq][sep];

    if (s->flags & 4) {
        return;
    }
    if (s->flags & 0x100) {
        return;
    }
    if ((short)vol == 0) {
        return;
    }
    s->unk48 = vol;
    s->unk9C = count;
    s->unkA0 = 0;
    s->unk4A = 0;
}

OBJECT_END();
