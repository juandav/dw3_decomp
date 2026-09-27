#include "psyq.h"

void _SsVmKeyOn(int, short, short, u_short, u_short, u_short);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_key", _SsVmKeyOn);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_key", _SsVmKeyOff);

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
