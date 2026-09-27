#include "psyq.h"

void _SsSndSetDecres(short seq, short sep, int vol, long count) {
    _SsSndSetVolData(seq, sep, -vol, count);
    D_80080D38[seq][sep].flags |= 0x20;
    D_80080D38[seq][sep].flags &= ~0x10;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssdecres", SsSeqSetDecrescendo);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssdecres", SsSepSetDecrescendo);

OBJECT_END();
