#include "psyq.h"

void SetDrawMove(DR_MOVE *p, RECT *rect, int x, int y) {
    int len = 5;

    if (rect->w == 0 || rect->h == 0) {
        len = 0;
    }
    setlen(p, len);
    p->code[0] = 0x01000000;
    p->code[1] = 0x80000000;
    p->code[2] = *(u_long *)&rect->x;
    p->code[3] = (y << 16) | (x & 0xFFFF);
    p->code[4] = *(u_long *)&rect->w;
}

OBJECT_END();
