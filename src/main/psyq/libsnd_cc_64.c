#include "psyq.h"

void func_80034BF8(void);

void _SsContDamper(short seq, short sep, u_char damper) {
    SeqStruct *score = &D_80080D38[seq][sep];

    if (damper < 64) {
        func_80034BE8();
    } else {
        func_80034BF8();
    }
    score->delta = _SsReadDeltaValue(seq, sep);
}

OBJECT_END();
