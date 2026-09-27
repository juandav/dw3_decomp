#include "psyq.h"

void SetDrawTPage(DR_TPAGE *p, int dfe, int dtd, int tpage) {
    setlen(p, 1);
    p->code[0] = (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
}

OBJECT_END();
