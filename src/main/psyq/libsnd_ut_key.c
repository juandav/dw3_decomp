#include "psyq.h"

extern long D_80080D2C;
extern short D_80081E18;
void vmNoiseOff(u_char voice);
void _SsVmKeyOffNow(int mode);

extern char D_80081DF4;
u_char _SsVmAlloc(int vag);
void _SsVmDoAllocate(void);
void vmNoiseOn(u_char voice);
u_short note2pitch2(u_short note, u_short fine);
void _SsVmKeyOnNow(u_char count, u_short pitch);

short SsUtKeyOn(short vabId, short prog, short tone, short note, short fine, short voll, short volr) {
    short voice;
    short i;

    if (D_80080D2C == 1) {
        return -1;
    }
    D_80080D2C = 1;
    if (_SsVmVSetUp(vabId, prog) != 0) {
        D_80080D2C = 0;
        return -1;
    }
    D_80081E00.seqSep = 0x21;
    D_80081E00.note = note;
    D_80081E00.unk3 = fine;
    D_80081E00.tone = tone;
    if (voll == volr) {
        D_80081E00.pan = 0x40;
        D_80081E00.vol = voll;
    } else if (volr < voll) {
        D_80081E00.pan = (volr << 6) / voll;
        D_80081E00.vol = voll;
    } else {
        D_80081E00.pan = 0x7F - (voll << 6) / volr;
        D_80081E00.vol = volr;
    }
    D_80081E00.progVol = D_80081DE4[prog].mvol;
    D_80081E00.progPan = D_80081DE4[prog].mpan;
    D_80081E00.tones = D_80081DE4[prog].tones;
    i = D_80081E00.tone + D_80081E00.prog * 16;
    D_80081E00.priority = D_80081DF0[i].prior;
    D_80081E00.vag = D_80081DF0[i].vag;
    D_80081E00.toneVol = D_80081DF0[i].vol;
    D_80081E00.tonePan = D_80081DF0[i].pan;
    D_80081E00.center = D_80081DF0[i].center;
    D_80081E00.shift = D_80081DF0[i].shift;
    D_80081E00.mode = D_80081DF0[i].mode;
    if (D_80081E00.vag == 0) {
        D_80080D2C = 0;
        return -1;
    }
    voice = _SsVmAlloc(D_80081E00.vag);
    if (voice == D_80081DF4) {
        D_80080D2C = 0;
        return -1;
    }
    D_80081E00.voice = voice;
    D_800815D0[voice].unk10 = 0x21;
    D_800815D0[voice].vabId = vabId;
    D_800815D0[voice].unk12 = D_80081E00.prog;
    D_800815D0[voice].prog = prog;
    D_800815D0[voice].unk0 = D_80081E00.vag;
    D_800815D0[voice].tone = D_80081E00.tone;
    D_800815D0[voice].note = note;
    D_800815D0[voice].unk36 = D_80081E00.vol;
    D_800815D0[voice].unkA = D_80081E00.pan;
    D_800815D0[voice].unk1D = 1;
    D_800815D0[voice].unk2 = 0;
    _SsVmDoAllocate();
    if (D_80081E00.vag == 0xFF) {
        vmNoiseOn(voice);
    } else {
        _SsVmKeyOnNow(1, note2pitch2(note, fine));
    }
    D_80080D2C = 0;
    return voice;
}

short SsUtKeyOff(short voice, short vabId, short prog, short tone, short note) {
    if (D_80080D2C == 1) {
        return -1;
    }
    D_80080D2C = 1;
    if ((u_short)voice < 24) {
        if (D_800815D0[voice].vabId == vabId && D_800815D0[voice].prog == prog &&
            D_800815D0[voice].tone == tone && D_800815D0[voice].note == note &&
            D_800815D0[voice].unk0 == 0xFF) {
            vmNoiseOff(voice);
        } else {
            D_80081E18 = voice;
            _SsVmKeyOffNow(0);
        }
        D_800815D0[voice].unk2A = 0;
        D_800815D0[voice].unk1E = 0;
        D_80080D2C = 0;
        return 0;
    }
    D_80080D2C = 0;
    return -1;
}

OBJECT_END();
