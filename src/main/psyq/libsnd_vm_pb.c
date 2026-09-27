#include "psyq.h"

extern char D_80081DF4;
short _SsVmPBVoice(short voice, short seqSep, short vabId, short prog, u_short pitch);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_pb", _SsVmPBVoice);

long _SsVmPitchBend(int seqSep, short vabId, short prog, u_short pitch) {
    long count = 0;
    short voice;

    _SsVmVSetUp(vabId, prog);
    D_80081E00.seqSep = seqSep;
    for (voice = 0; voice < D_80081DF4; voice++) {
        count += _SsVmPBVoice(voice, seqSep, vabId, prog, pitch);
    }
    return count;
}

OBJECT_END();
