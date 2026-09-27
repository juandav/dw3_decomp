#include "psyq.h"

long SpuSetNoiseClock(long n) {
    long clock;

    if (n < 0) {
        clock = 0;
    } else if (n >= 0x40) {
        clock = 0x3F;
    } else {
        clock = n;
    }
    D_8005BA28[0xD5] = (D_8005BA28[0xD5] & 0xC0FF) | ((clock & 0x3F) << 8);
    return clock;
}

OBJECT_END();
