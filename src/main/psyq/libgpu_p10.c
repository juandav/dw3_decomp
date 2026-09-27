#include "psyq.h"

void SetSemiTrans(void *p, int abe) {
    u_char code;

    if (abe) {
        code = ((P_TAG *)p)->code | 2;
    } else {
        code = ((P_TAG *)p)->code & ~2;
    }
    ((P_TAG *)p)->code = code;
}

OBJECT_END();
