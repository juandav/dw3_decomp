#include "psyq.h"

extern u_short D_8005BE98[];
extern u_short D_8005BEB0[];

u_short _spu_note2pitch(short cenHigh, short cenLow, short noteHigh, short noteLow) {
    u_short fine;
    short note;
    short type;
    short rem;
    u_int pitch;

    fine = noteLow + cenLow;
    note = noteHigh + (fine >> 7) - cenHigh;
    type = note / 12 - 2;
    rem = note % 12;
    fine = fine % 128;
    if (rem < 0) {
        rem += 12;
        type = note / 12 - 3;
    }
    pitch = (D_8005BE98[rem] * D_8005BEB0[fine]) >> 16;
    if (type >= 0) {
        pitch = 0x3FFF;
    } else {
        pitch += 1 << (-type - 1);
        pitch >>= -type;
    }
    return pitch;
}

int _spu_pitch2note(short note_high, int note_low, u_short pitch) {
    int octave = 0;
    int i;
    u_short semitone;
    int fine;
    int step;
    u_int lo;
    u_short frac;

    if (pitch >= 0x4000) {
        pitch = 0x3FFF;
    }
    for (i = 0; i < 14; i++) {
        if ((pitch >> i) & 1) {
            octave = i;
        }
    }
    pitch = pitch << (15 - octave);
    for (i = 11; i >= 0; i--) {
        if (pitch >= D_8005BE98[i]) {
            semitone = i;
            break;
        }
    }
    frac = ((u_int)pitch << 15) / D_8005BE98[semitone];
    for (i = 127; i >= 0; i--) {
        if (frac >= D_8005BEB0[i]) {
            fine = i;
            break;
        }
    }
    step = fine + 1;
    fine = note_low;
    fine += step;
    semitone = semitone + (note_high + (octave - 12) * 12) + ((lo = (u_short)fine) >> 7);
    return (semitone << 8) | (lo & 0x7E);
}

OBJECT_END();
