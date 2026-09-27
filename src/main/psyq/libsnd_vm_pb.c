#include "psyq.h"

extern char D_80081DF4;
short _SsVmPBVoice(short voice, short seqSep, short vabId, short prog, long pitch);

extern u_short D_80081B34[][8];
extern u_char D_80081B10[];
u_short note2pitch2(u_short note, u_short fine);

short _SsVmPBVoice(short vc, short seq_sep_no, short vabId, short prog, long pitch) {
    short pb;
    u_short base;
    u_short idx;
    u_short note;
    u_short fine;

    pb = pitch - 64;
    if (D_800815D0[vc].unk10 == seq_sep_no && D_800815D0[vc].vabId == vabId && D_800815D0[vc].prog == prog) {
        base = D_800815D0[vc].note;
        idx = D_800815D0[vc].tone + D_80081E00.prog * 16;
        if (pb > 0) {
            note = base + pb * D_80081DF0[idx].pbmax / 63;
            fine = (pb * D_80081DF0[idx].pbmax % 63) * 2;
        } else if (pb < 0) {
            note = base + pb * D_80081DF0[idx].pbmin / 64 - 1;
            fine = (pb * D_80081DF0[idx].pbmin % 64) * 2 + 0x7F;
        } else {
            note = base;
            fine = 0;
        }
        D_80081E00.tone = D_800815D0[vc].tone;
        D_80081E00.voice = vc;
        D_80081B34[vc][0] = note2pitch2(note, fine);
        D_80081B10[vc] |= 4;
        return 1;
    }
    return 0;
}

long _SsVmPitchBend(int seqSep, short vabId, short prog, u_short pitch) {
    long count = 0;
    short voice;

    _SsVmVSetUp(vabId, prog);
    D_80081E00.seqSep = seqSep;
    for (voice = 0; voice < D_80081DF4; voice++) {
        count += _SsVmPBVoice(voice, seqSep, vabId, prog, pitch);
    }
    return count;
}

OBJECT_END();
