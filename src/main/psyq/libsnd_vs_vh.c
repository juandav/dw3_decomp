#include "psyq.h"

short SsVabOpenHeadSticky(unsigned char *addr, short vabId, unsigned long sbaddr) {
    return _SsVabOpenHeadWithMode(addr, vabId, func_80037AF0, sbaddr);
}

short SsVabFakeHead(unsigned char *addr, short vabId, unsigned long sbaddr) {
    return _SsVabOpenHeadWithMode(addr, vabId, func_80037AF0, sbaddr);
}

int func_80037AF0(int arg0, int arg1) {
    return arg1;
}

OBJECT_END();
