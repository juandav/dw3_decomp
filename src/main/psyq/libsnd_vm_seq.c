#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_seq", _SsVmSetSeqVol);

extern short D_80081E14;

short _SsVmGetSeqVol(short seq_sep, short *voll, short *volr) {
    SeqStruct *score;
    short *cur = &D_80081E14;

    score = D_80080D38[seq_sep & 0xFF];
    *cur = seq_sep;
    score += (seq_sep & 0xFF00) >> 8;
    *voll = score->voll;
    *volr = score->volr;
    return *cur;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_seq", _SsVmSeqKeyOff);

OBJECT_END();
