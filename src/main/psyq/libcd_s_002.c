#include "psyq.h"

#define ENCODE_BCD(n) (((n) / 10) * 16 + (n) % 10)

CdlLOC *CdIntToPos(int i, CdlLOC *p) {
    int sec, min, frame;

    i += 150;
    sec = i / 75;
    frame = i % 75;
    min = sec / 60;
    sec = sec % 60;
    p->sector = ENCODE_BCD(frame);
    p->second = ENCODE_BCD(sec);
    p->minute = ENCODE_BCD(min);
    return p;
}

OBJECT_END();
