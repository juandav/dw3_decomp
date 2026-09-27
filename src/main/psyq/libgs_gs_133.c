#include "psyq.h"
#include <libgte.h>
#include <libgs.h>

extern GsCOORDINATE2 *D_80080B50[100];
extern long D_80080A70;

void GsGetLw(GsCOORDINATE2 *coord, MATRIX *m) {
    GsCOORDINATE2 *cp;
    int i;
    int hit;
    long flg;

    cp = coord;
    i = 0;
    hit = 100;
    for (;; i++) {
        D_80080B50[i] = cp;
        if (cp->super == NULL) {
            if (cp->flg == D_80080A70 || cp->flg == 0) {
                cp->workm = cp->coord;
                flg = D_80080A70;
                *m = cp->workm;
                cp->flg = flg;
                break;
            }
            if (hit == 100) {
                *m = D_80080B50[0]->workm;
                i = 0;
            } else {
                i = hit + 1;
                *m = D_80080B50[i]->workm;
            }
            break;
        }
        if (cp->flg == D_80080A70) {
            *m = cp->workm;
            break;
        }
        if (cp->flg == 0) {
            hit = i;
        }
        cp = cp->super;
    }
    for (; i > 0; i--) {
        GsMulCoord3(m, &D_80080B50[i - 1]->coord);
        D_80080B50[i - 1]->workm = *m;
        D_80080B50[i - 1]->flg = D_80080A70;
    }
}

OBJECT_END();
