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

extern char D_80081DF4;
extern long D_8005B818;
extern short D_80081E18;
void _SsVmKeyOffNow(int mode);

void _SsVmSeqKeyOff(short seq_sep) {
    u_char voice;

    for (voice = 0; voice < D_80081DF4; voice++) {
        if (!(D_8005B818 & (1 << voice)) && D_800815D0[voice].unk10 == seq_sep) {
            D_80081E18 = voice;
            _SsVmKeyOffNow(0);
        }
    }
}

OBJECT_END();
