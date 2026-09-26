#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssstop", _SsSndStop);

void SsSeqStop(short seq) {
    _SsSndStop(seq, 0);
}

void SsSepStop(short seq, short sep) {
    _SsSndStop(seq, sep);
}

OBJECT_END();
