#include "psyq.h"

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_n2p", SsPitchFromNote);

OBJECT_END();
