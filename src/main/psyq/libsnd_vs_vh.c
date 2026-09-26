#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vs_vh", SsVabOpenHeadSticky);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vs_vh", SsVabFakeHead);

int func_80037AF0(int arg0, int arg1) {
    return arg1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vs_vh", _SsVabOpenHeadWithMode);

OBJECT_END();
