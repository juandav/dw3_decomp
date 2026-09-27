#include "psyq.h"

extern VabHdr *D_80081DEC;
extern short D_80081DE0;
extern short D_80081B30[];
extern char D_80081B10[];
extern u_short D_800815C0;
extern u_short D_800815C2;
extern u_short D_80081CF8;
extern u_short D_80081CFA;
extern u_short D_800815C4;
extern u_short D_800815C6;
extern u_short D_800815C8;
extern u_short D_800815CA;

void _SsVmKeyOnNow(short vagCount, short pitch) {
    SeqStruct *score;
    u_short pos;
    u_int voll_t;
    u_int volr_t;
    u_int voll;
    u_int volr;
    u_int pan;
    u_short lo;
    u_short hi;

    pos = D_80081E00.voice * 8;
    score = D_80080D38[D_80081E00.seqSep & 0xFF] + ((D_80081E00.seqSep & 0xFF00) >> 8);
    voll_t = D_80081E00.vol * 0x3FFF * D_80081DEC->mvol / 16129;
    volr_t = voll_t * D_80081E00.progVol * D_80081E00.toneVol / 16129;
    voll_t = volr_t;
    if (D_80081E00.seqSep != 0x21) {
        voll_t = volr_t * score->voll / 127;
        volr_t = volr_t * score->volr / 127;
    }
    pan = (u_char)D_80081E00.tonePan;
    if (pan < 64) {
        voll = voll_t;
        volr = volr_t * pan / 63;
    } else {
        voll = voll_t * (127 - pan) / 63;
        volr = volr_t;
    }
    pan = (u_char)D_80081E00.progPan;
    if (pan < 64) {
        volr = volr * pan / 63;
    } else {
        voll = voll * (127 - pan) / 63;
    }
    pan = (u_char)D_80081E00.pan;
    if (pan < 64) {
        volr = volr * pan / 63;
    } else {
        voll = voll * (127 - pan) / 63;
    }
    if (D_80081DE0 == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    if (D_80081E00.seqSep != 0x21) {
        voll = voll * voll / 0x3FFF;
        volr = volr * volr / 0x3FFF;
    }
    *(D_80081B30 + pos + 2) = pitch;
    *(D_80081B30 + pos + 0) = voll;
    *(D_80081B30 + pos + 1) = volr;
    D_80081B10[D_80081E00.voice] |= 7;
    D_800815D0[D_80081E00.voice].unk4 = pitch;
    if (D_80081E00.voice < 16) {
        lo = 1 << D_80081E00.voice;
        hi = 0;
    } else {
        lo = 0;
        hi = 1 << (D_80081E00.voice - 16);
    }
    if (D_80081E00.mode & 4) {
        D_800815C4 |= lo;
        D_800815C6 |= hi;
    } else {
        D_800815C4 &= ~lo;
        D_800815C6 &= ~hi;
    }
    D_800815C8 &= ~lo;
    D_800815CA &= ~hi;
    D_800815C0 |= lo;
    D_800815C2 |= hi;
    D_80081CF8 &= ~D_800815C0;
    D_80081CFA &= ~D_800815C2;
}

OBJECT_END();
