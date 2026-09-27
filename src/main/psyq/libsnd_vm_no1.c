#include "psyq.h"

/* _svm_sreg_buf: shadow of the SPU voice registers */
typedef struct SvmSreg {
    /* 0x0 */ short voll;
    /* 0x2 */ short volr;
    /* 0x4 */ short pitch;
    /* 0x6 */ short addr;
    /* 0x8 */ short adsr1;
    /* 0xA */ short adsr2;
    /* 0xC */ short unkC;
    /* 0xE */ short unkE;
} SvmSreg;

extern VabHdr *D_80081DEC;
extern short D_80081DE0;
extern SvmSreg D_80081B30[];
extern char D_80081B10[];
extern char D_80081DF4;
extern long D_8005B818;
extern u_short D_800815C0;
extern u_short D_800815C2;
extern u_short D_80081CF8;
extern u_short D_80081CFA;
extern u_short D_800815C4;
extern u_short D_800815C6;
extern u_short D_800815C8;
extern u_short D_800815CA;

void vmNoiseOn(u_char voice) {
    SeqStruct *score;
    u_int voll_t;
    u_int volr_t;
    u_int voll;
    u_int volr;
    u_int pan;
    u_short lo;
    u_short hi;
    short i;
    u_int v;

    score = D_80080D38[D_80081E00.seqSep & 0xFF] + ((D_80081E00.seqSep & 0xFF00) >> 8);
    voll_t = D_80081E00.vol * 0x3FFF * D_80081DEC->mvol / 16129;
    volr_t = voll_t * D_80081E00.progVol * D_80081E00.toneVol / 16129;
    voll_t = volr_t;
    if (D_80081E00.seqSep != 0x21) {
        voll_t = volr_t * score->voll / 127;
        volr_t = volr_t * score->volr / 127;
    }
    pan = D_80081E00.tonePan;
    if (pan < 64) {
        voll = voll_t;
        volr = volr_t * pan / 63;
    } else {
        voll = voll_t * (127 - pan) / 63;
        volr = volr_t;
    }
    pan = D_80081E00.progPan;
    if (pan < 64) {
        volr = volr * pan / 63;
    } else {
        voll = voll * (127 - pan) / 63;
    }
    pan = D_80081E00.pan;
    if (pan < 64) {
        volr = pan * volr / 63;
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
    v = voice;
    SpuSetNoiseClock((D_80081E00.note - D_80081E00.center) & 0x3F);
    D_80081B30[v].volr = volr;
    D_80081B30[v].voll = voll;
    D_80081B10[v] |= 3;
    if (v < 16) {
        lo = 1 << v;
        hi = 0;
    } else {
        lo = 0;
        hi = 1 << (v - 16);
    }
    D_800815D0[voice].unk4 = 10;
    for (i = 0; i < D_80081DF4; i++) {
        if (!(D_8005B818 & (1 << i))) {
            D_800815D0[i].unk1D &= 1;
        }
    }
    D_800815D0[voice].unk1D = 2;
    D_800815C0 |= lo;
    D_800815C2 |= hi;
    D_80081CF8 &= ~D_800815C0;
    D_80081CFA &= ~D_800815C2;
    if (D_80081E00.mode & 4) {
        D_800815C4 |= lo;
        D_800815C6 |= hi;
    } else {
        D_800815C4 &= ~lo;
        D_800815C6 &= ~hi;
    }
    D_800815C8 = lo;
    D_800815CA = hi;
}

OBJECT_END();
