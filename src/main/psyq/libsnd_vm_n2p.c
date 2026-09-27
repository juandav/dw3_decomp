#include "psyq.h"

/* libsnd's current voice state */
typedef struct SvmCur {
    /* 0x00 */ u8 unk0[2];
    /* 0x02 */ char note;
    /* 0x03 */ u8 unk3[4];
    /* 0x07 */ char prog;
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ char tone;
    /* 0x0D */ u8 unkD[3];
    /* 0x10 */ u_char center;
    /* 0x11 */ u_char shift;
} SvmCur;

extern SvmCur D_80081E00;
extern VagAtr *D_80081DF0;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_n2p", note2pitch);

u_short note2pitch2(short note, short fine) {
    short i = D_80081E00.prog * 16 + D_80081E00.tone;

    return SsPitchFromNote(note, fine, D_80081DF0[i].center, D_80081DF0[i].shift);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_n2p", SsPitchFromNote);

OBJECT_END();
