#include "psyq.h"

void _SsVmKeyOn(int, short, short, u_short, u_short, u_short);

extern char D_80081DF4;
extern long D_8005B818;
void _SsVmKeyOffNow(int mode);
void vmNoiseOff(u8 voice);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_key", _SsVmKeyOn);

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
