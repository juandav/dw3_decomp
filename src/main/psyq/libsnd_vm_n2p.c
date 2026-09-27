#include "psyq.h"

extern u_short D_8005B888[];
extern u_short D_8005B8A0[];

u_short note2pitch(void) {
    u_char shift = D_80081E00.shift;

    if (shift >= 0x80) {
        shift = 0x7F;
    }
    return SsPitchFromNote(D_80081E00.note, 0, D_80081E00.center, shift);
}

u_short note2pitch2(short note, short fine) {
    short i = D_80081E00.prog * 16 + D_80081E00.tone;

    return SsPitchFromNote(note, fine, D_80081DF0[i].center, D_80081DF0[i].shift);
}

u_short SsPitchFromNote(short note, short fine, u_char center, u_char shift) {
    short sfine;
    int add;
    int div;
    short calc;
    short type;
    short n;
    u_int pitch;

    add = (short)(fine + shift);
    div = add / 128;
    sfine = add;
    note = note + div - center;
    calc = note;
    sfine -= div * 128;
    if (sfine < 0) {
        sfine += 128;
        note--;
        calc = note + sfine / 128;
    }
    type = calc / 12 - 2;
    n = calc % 12;
    if (n < 0) {
        n += 12;
        type = calc / 12 - 3;
    }
    pitch = (D_8005B888[n] * D_8005B8A0[sfine]) >> 16;
    if (type >= 0) {
        pitch = 0x3FFF;
    } else {
        pitch += 1 << (-type - 1);
        pitch >>= -type;
    }
    return pitch;
}

OBJECT_END();
