#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_midiread", _SsSeqPlay);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_midiread", _SsSeqGetEof);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_midiread", _SsGetSeqData);

OBJECT_END();
