#include "psyq.h"
#include <libgte.h>
#include <libgs.h>

extern MATRIX D_80080AB0;

extern MATRIX D_80080A90;
void func_80029A70(MATRIX *m);
void func_80029AD4(MATRIX *m);

int GsSetFlatLight(int id, GsF_LIGHT *lt) {
    MATRIX lm;
    MATRIX cm;
    long unused[10]; /* never used, but the ROM's frame has room for it */
    long r;
    u_char cr;
    u_char cg;
    u_char cb;

    cr = lt->r;
    cg = lt->g;
    cb = lt->b;
    lm = D_80080A90;
    func_80029AD4(&cm);
    r = SquareRoot0(lt->vx * lt->vx + lt->vy * lt->vy + lt->vz * lt->vz);
    if (r == 0) {
        return -1;
    }
    switch (id) {
    case 0:
        lm.m[0][0] = -lt->vx * 4096 / r;
        lm.m[0][1] = -lt->vy * 4096 / r;
        lm.m[0][2] = -lt->vz * 4096 / r;
        cm.m[0][0] = (cr << 12) / 255;
        cm.m[1][0] = (cg << 12) / 255;
        cm.m[2][0] = (cb << 12) / 255;
        break;
    case 1:
        lm.m[1][0] = -lt->vx * 4096 / r;
        lm.m[1][1] = -lt->vy * 4096 / r;
        lm.m[1][2] = -lt->vz * 4096 / r;
        cm.m[0][1] = (cr << 12) / 255;
        cm.m[1][1] = (cg << 12) / 255;
        cm.m[2][1] = (cb << 12) / 255;
        break;
    case 2:
        lm.m[2][0] = -lt->vx * 4096 / r;
        lm.m[2][1] = -lt->vy * 4096 / r;
        lm.m[2][2] = -lt->vz * 4096 / r;
        cm.m[0][2] = (cr << 12) / 255;
        cm.m[1][2] = (cg << 12) / 255;
        cm.m[2][2] = (cb << 12) / 255;
        break;
    }
    D_80080A90 = lm;
    func_80029A70(&cm);
    return 0;
}

void func_80029A70(MATRIX *m) {
    D_80080AB0 = *m;
    SetColorMatrix(m);
}

void func_80029AD4(MATRIX *m) {
    *m = D_80080AB0;
}

OBJECT_END();
