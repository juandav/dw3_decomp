#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssstart", func_80032B98);

void SsStart(void) {
    func_80032B98(1);
}

void SsStart2(void) {
    func_80032B98(0);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssstart", func_80032E08);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_ssstart", func_80032E54);

OBJECT_END();
