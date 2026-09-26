#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssclose", func_8002FFF8);

void SsSeqClose(short seq) {
    func_8002FFF8(seq);
}

OBJECT_END();
