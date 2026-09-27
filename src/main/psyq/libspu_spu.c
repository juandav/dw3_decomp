#include "psyq.h"

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libspu_spu", D_80010BCC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_init);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", func_800383F8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FiDMA);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_Fr_);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_t);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_Fw);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_Fr);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FsetRXX);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FsetRXXa);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FgetRXXa);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_FsetPCR);

void func_80038C00(void) {
    *D_8005BA3C = (*D_8005BA3C & 0xF0FFFFFF) | 0x20000000;
}

void func_80038C28(void) {
    *D_8005BA3C = (*D_8005BA3C & 0xF0FFFFFF) | 0x22000000;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_spu", _spu_Fw1ts);

OBJECT_END();
