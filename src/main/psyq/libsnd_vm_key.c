#include "psyq.h"

int _SsVmKeyOn(short seq_sep, short vab, short prog, u_short note, u_short voll, u_short volr);
int _SsVmKeyOff(short seq_sep, short vab, short prog, u_short note);

extern char D_80081DF4;
extern long D_8005B818;
void _SsVmKeyOffNow(int mode);
void vmNoiseOff(u8 voice);

extern VabHdr *D_80081DEC;
u_char _SsVmSelectToneAndVag(u_char *toneIdx, u_char *vagIdx);
u_char _SsVmAlloc(int mode);
void _SsVmDoAllocate(void);
u_short note2pitch(void);
void vmNoiseOn(u_char voice);
void _SsVmKeyOnNow(u_char count, u_short pitch);

int _SsVmKeyOn(short seq_sep, short vab, short prog, u_short note, u_short voll, u_short volr) {
    SeqStruct *score = &D_80080D38[seq_sep & 0xFF][(seq_sep & 0xFF00) >> 8];
    u_char vagIdx[0x80];
    u_char toneIdx[0x80];
    u_char i;
    int ret;
    u_short tone;
    u_char count;
    VagAtr *t;

    ret = 0;
    if (_SsVmVSetUp(vab, prog)) {
        return -1;
    }
    D_80081E00.seqSep = seq_sep;
    D_80081E00.note = note;
    D_80081E00.unk3 = 0;
    if (seq_sep == 0x21) {
        D_80081E00.vol = voll;
    } else {
        D_80081E00.vol = (voll * (short)score->vol[score->channel]) / 0x7F;
    }
    D_80081E00.pan = volr;
    D_80081E00.progVol = D_80081DE4[prog].mvol;
    D_80081E00.progPan = D_80081DE4[prog].mpan;
    D_80081E00.tones = D_80081DE4[prog].tones;
    if (D_80081E00.prog >= D_80081DEC->ps) {
        return -1;
    }
    if (voll == 0) {
        ret = _SsVmKeyOff(seq_sep, vab, prog, note);
    } else {
        count = _SsVmSelectToneAndVag(toneIdx, vagIdx);
        for (i = 0; i < count; i++) {
            D_80081E00.vag = vagIdx[i];
            D_80081E00.tone = toneIdx[i];
            tone = (D_80081E00.tone + D_80081E00.prog * 16);
            D_80081E00.priority = D_80081DF0[tone].prior;
            D_80081E00.toneVol = D_80081DF0[tone].vol;
            D_80081E00.tonePan = D_80081DF0[tone].pan;
            D_80081E00.center = D_80081DF0[tone].center;
            D_80081E00.shift = D_80081DF0[tone].shift;
            D_80081E00.mode = D_80081DF0[tone].mode;
            D_80081E00.voice = _SsVmAlloc(0);
            if (D_80081E00.voice < D_80081DF4) {
                D_800815D0[D_80081E00.voice].unk1D = 1;
                D_800815D0[D_80081E00.voice].unk2 = 0;
                D_800815D0[D_80081E00.voice].unk10 = seq_sep;
                D_800815D0[D_80081E00.voice].vabId = D_80081E00.vabId;
                D_800815D0[D_80081E00.voice].unk12 = D_80081E00.prog;
                D_800815D0[D_80081E00.voice].prog = prog;
                if (seq_sep != 0x21) {
                    D_800815D0[D_80081E00.voice].unk8 = voll;
                    D_800815D0[D_80081E00.voice].unkC = score->channel;
                }
                D_800815D0[D_80081E00.voice].unkA = volr;
                D_800815D0[D_80081E00.voice].unk36 = D_80081E00.vol;
                D_800815D0[D_80081E00.voice].tone = D_80081E00.tone;
                D_800815D0[D_80081E00.voice].note = note;
                D_800815D0[D_80081E00.voice].priority = D_80081E00.priority;
                D_800815D0[D_80081E00.voice].unk0 = D_80081E00.vag;
                _SsVmDoAllocate();
                if (D_80081E00.vag == 0xFF) {
                    vmNoiseOn(D_80081E00.voice);
                } else {
                    _SsVmKeyOnNow(count, note2pitch() & 0xFFFF);
                }
                ret |= 1 << D_80081E00.voice;
            } else {
                ret = -1;
            }
        }
    }
    return ret;
}

int _SsVmKeyOff(short seq_sep, short vab, short prog, u_short note) {
    u_char voice;
    int count = 0;

    for (voice = 0; voice < D_80081DF4; voice++) {
        if (!(D_8005B818 & (1 << voice)) && D_800815D0[voice].note == note &&
            D_800815D0[voice].prog == prog && D_800815D0[voice].unk10 == seq_sep &&
            D_800815D0[voice].vabId == vab) {
            if (D_800815D0[voice].unk0 == 0xFF) {
                vmNoiseOff(voice);
            } else {
                D_80081E00.voice = voice;
                _SsVmKeyOffNow(0);
            }
            count++;
        }
    }
    return count;
}

void _SsVmSeKeyOn(short vab, short prog, u_short note, int pitch, int voll, int volr) {
    int vol;
    short pan;
    u_short l = voll;
    u_short r = volr;

    if (l == r) {
        pan = 0x40;
        vol = voll;
    } else if (l > r) {
        pan = (r << 6) / l;
        vol = voll;
    } else {
        pan = 0x7F - (l << 6) / r;
        vol = volr;
    }
    _SsVmKeyOn(0x21, vab, prog, note, vol, pan);
}

void _SsVmSeKeyOff(short vab, short prog, u_short note) {
    _SsVmKeyOff(0x21, vab, prog, note);
}

OBJECT_END();
