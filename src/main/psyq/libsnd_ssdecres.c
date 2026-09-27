#include "psyq.h"

inline void _SsSndSetDecres(short seq, short sep, short vol, long count) {
    _SsSndSetVolData(seq, sep, (short)-vol, count);
    D_80080D38[seq][sep].flags |= 0x20;
    D_80080D38[seq][sep].flags &= ~0x10;
}

void SsSeqSetDecrescendo(short seq, short vol, long count) {
    _SsSndSetDecres(seq, 0, vol, count);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssdecres", SsSepSetDecrescendo);

OBJECT_END();
