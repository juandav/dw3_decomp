#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdcmd2", PadSetActAlign);

void func_80020A54(PadPort *p) {
    _padSetCmd(p, 0x4D, p->unk20, 6);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdcmd2", func_80020A7C);

OBJECT_END();
