#include "psyq.h"

void PadSetAct(int port, u_char *table, int len) {
    PadPort *p = D_8005552C(port);

    p->actTable = table;
    p->actLen = len;
}

OBJECT_END();
