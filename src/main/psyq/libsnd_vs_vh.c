#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vs_vh", SsVabOpenHeadSticky);

short SsVabFakeHead(unsigned char *addr, short vabId, unsigned long sbaddr) {
    return _SsVabOpenHeadWithMode(addr, vabId, func_80037AF0, sbaddr);
}

int func_80037AF0(int arg0, int arg1) {
    return arg1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vs_vh", _SsVabOpenHeadWithMode);

OBJECT_END();
