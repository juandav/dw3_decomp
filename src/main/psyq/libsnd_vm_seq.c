#include "psyq.h"

extern VabHdr *D_80081DEC;
extern short D_80081DE0;
extern u_short D_80081B30[];
extern u_char D_80081B10[];
extern char D_80081DF4;
extern long D_8005B818;

short _SsVmSetSeqVol(short seq_sep_no, u_short voll, u_short volr, short mode) {
    SeqStruct *score;
    short i;
    u_int voll_t;
    u_int volr_t;
    u_short l;
    u_short r;
    u_char pan;
    int v;

    score = *(D_80080D38 + (seq_sep_no & 0xFF)) + ((seq_sep_no & 0xFF00) >> 8);
    score->voll = voll;
    score->volr = volr;
    if (score->voll >= 127) {
        score->voll = 127;
    }
    if (score->volr >= 127) {
        score->volr = 127;
    }
    for (i = 0; i < D_80081DF4; i++) {
        if (!(D_8005B818 & (1 << i)) && D_800815D0[i].unk10 == seq_sep_no && D_800815D0[i].vabId == score->vabId) {
            _SsVmVSetUp(D_800815D0[i].vabId, D_800815D0[i].unk12);
            v = D_800815D0[i].unk8 * (short)*(score->vol + D_800815D0[i].unkC) / 127 * 0x3FFF;
            voll_t = D_80081DEC->mvol * v / 16129;
            volr_t = voll_t * D_80081DE4[D_800815D0[i].prog].mvol * D_80081DF0[D_800815D0[i].unk12 * 16 + D_800815D0[i].tone].vol / 16129;
            voll_t = volr_t * score->voll / 127;
            volr_t = volr_t * score->volr / 127;
            pan = D_80081DF0[D_800815D0[i].unk12 * 16 + D_800815D0[i].tone].pan;
            if (pan < 64) {
                l = voll_t;
                r = volr_t * pan / 63;
            } else {
                l = voll_t * (127 - pan) / 63;
                r = volr_t;
            }
            pan = D_80081DE4[D_800815D0[i].prog].mpan;
            if (pan < 64) {
                r = r * pan / 63;
            } else {
                l = l * (127 - pan) / 63;
            }
            pan = D_800815D0[i].unkA;
            if (pan < 64) {
                r = r * pan / 63;
            } else {
                l = l * (127 - pan) / 63;
            }
            if (D_80081DE0 == 1) {
                if (l < r) {
                    l = r;
                } else {
                    r = l;
                }
            }
            l = l * l / 0x3FFF;
            r = r * r / 0x3FFF;
            *(D_80081B30 + i * 8) = l;
            *(D_80081B30 + i * 8 + 1) = r;
            D_80081B10[i] |= 3;
        }
    }
    return seq_sep_no;
}


short _SsVmGetSeqVol(short seq_sep, short *voll, short *volr) {
    SeqStruct *score;
    short *cur = &D_80081E00.seqSep;

    score = D_80080D38[seq_sep & 0xFF];
    *cur = seq_sep;
    score += (seq_sep & 0xFF00) >> 8;
    *voll = score->voll;
    *volr = score->volr;
    return *cur;
}

void _SsVmKeyOffNow(int mode);

void _SsVmSeqKeyOff(short seq_sep) {
    u_char voice;

    for (voice = 0; voice < D_80081DF4; voice++) {
        if (!(D_8005B818 & (1 << voice)) && D_800815D0[voice].unk10 == seq_sep) {
            D_80081E00.voice = voice;
            _SsVmKeyOffNow(0);
        }
    }
}

OBJECT_END();
