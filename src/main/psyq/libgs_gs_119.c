#include "psyq.h"
#include <libgte.h>

void gte_rotate_z_matrix(MATRIX *m, int angle) {
    MATRIX rot;
    int a = angle / 360;
    int c = rcos(a);
    int s = rsin(a);

    if (angle == 0) {
        return;
    }
    rot.m[0][0] = c;
    rot.m[0][1] = -s;
    rot.m[0][2] = 0;
    rot.m[1][0] = s;
    rot.m[1][1] = c;
    rot.m[1][2] = 0;
    rot.m[2][0] = 0;
    rot.m[2][1] = 0;
    rot.m[2][2] = 0x1000;
    rot.t[0] = 0;
    rot.t[1] = 0;
    rot.t[2] = 0;
    MulMatrix(m, &rot);
}

OBJECT_END();
