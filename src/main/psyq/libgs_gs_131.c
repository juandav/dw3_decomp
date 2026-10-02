#include "psyq.h"
#include <libgte.h>
#include <libgs.h>

extern MATRIX D_80080AD0;
extern MATRIX D_80080AF0; /* GsWSMATRIX */
extern MATRIX D_80080B30;
void gte_rotate_z_matrix(MATRIX *m, int angle);
void Gssub_make_matrix(MATRIX *m, short s, short c, char axis);
void func_8002A188(long *src, long *dst);

long func_8002A274(long *v);
long func_8002A33C(long value);

int func_80029DB8(GsRVIEW2 *pv) {
    GsRVIEW2 v;
    MATRIX tmp;
    MATRIX tmp2;
    MATRIX unused; /* unused, but it is in the original stack frame */
    VECTOR vec;
    long r;
    long t;
    long a;
    long b;

    D_80080AF0 = D_80080B30;
    gte_rotate_z_matrix(&D_80080AF0, -pv->rz);
    func_8002A188((long *)pv, (long *)&v);
    r = SquareRoot0((v.vrx - v.vpx) * (v.vrx - v.vpx) + (v.vry - v.vpy) * (v.vry - v.vpy) +
                    (v.vrz - v.vpz) * (v.vrz - v.vpz));
    if (r == 0) {
        return 1;
    }
    t = v.vpy - v.vry;
    a = -((t << 12) / r);
    t = SquareRoot0((v.vrx - v.vpx) * (v.vrx - v.vpx) + (v.vrz - v.vpz) * (v.vrz - v.vpz));
    b = (t << 12) / r;
    Gssub_make_matrix(&tmp, a, b, 'x');
    MulMatrix(&D_80080AF0, &tmp);
    if (t != 0) {
        r = t;
        t = v.vrx - v.vpx;
        a = (t << 12) / r;
        t = v.vrz - v.vpz;
        b = (t << 12) / r;
        Gssub_make_matrix(&tmp, -a, b, 'y');
        MulMatrix(&D_80080AF0, &tmp);
    }
    vec.vx = -pv->vpx;
    vec.vy = -pv->vpy;
    vec.vz = -pv->vpz;
    ApplyMatrixLV(&D_80080AF0, &vec, (VECTOR *)D_80080AF0.t);
    if (pv->super != NULL) {
        GsGetLw(pv->super, &tmp);
        TransposeMatrix(&tmp, &tmp2);
        ApplyMatrixLV(&tmp2, (VECTOR *)tmp.t, &vec);
        tmp2.t[0] = -vec.vx;
        tmp2.t[1] = -vec.vy;
        tmp2.t[2] = -vec.vz;
        GsMulCoord2(&D_80080AF0, &tmp2);
        D_80080AF0 = tmp2;
    }
    D_80080AD0 = D_80080AF0;
    return 0;
}

void func_8002A188(long *src, long *dst) {
    long shift = func_8002A33C(func_8002A274(src));

    if (shift >= 16) {
        shift -= 15;
        dst[0] = src[0] >> shift;
        dst[1] = src[1] >> shift;
        dst[2] = src[2] >> shift;
        dst[3] = src[3] >> shift;
        dst[4] = src[4] >> shift;
        dst[5] = src[5] >> shift;
    } else {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
    }
}

long func_8002A274(long *v) {
    long max;
    long t;

    max = (v[0] >= 0) ? v[0] : -v[0];
    t = (v[1] >= 0) ? v[1] : -v[1];
    if (max < t) max = t;
    t = (v[2] >= 0) ? v[2] : -v[2];
    if (max < t) max = t;
    t = (v[3] >= 0) ? v[3] : -v[3];
    if (max < t) max = t;
    t = (v[4] >= 0) ? v[4] : -v[4];
    if (max < t) max = t;
    t = (v[5] >= 0) ? v[5] : -v[5];
    if (max < t) max = t;
    return max;
}

long func_8002A33C(long value) {
    long bits = 0;

    while (value > 0) {
        value >>= 1;
        bits++;
    }
    return bits;
}

OBJECT_END();
