#include "psyq.h"

u_short GetTPage(int tp, int abr, int x, int y) {
    return ((tp & 3) << 7) | ((abr & 3) << 5) | ((y & 0x100) >> 4) | ((x & 0x3FF) >> 6) | ((y & 0x200) << 2);
}

OBJECT_END();
