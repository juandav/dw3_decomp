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

INCLUDE_ASM("main/nonmatchings/psyq/libspu_s_n2p", _spu_pitch2note);

OBJECT_END();
