#include "psyq.h"

u_long _SpuGetAnyVoice(int lo, int hi) {
    u_long h = D_8005BA28[hi] & 0xFF;

    return D_8005BA28[lo] | (h << 16);
}

OBJECT_END();
