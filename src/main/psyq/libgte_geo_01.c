#include "psyq.h"

extern short D_80055830[]; /* rsin_tbl */

int rcos(int a) {
    if (a < 0) {
        a = -a;
    }
    a &= 0xFFF;
    if (a <= 0x800) {
        if (a <= 0x400) {
            return D_80055830[0x400 - a];
        }
        return -D_80055830[a - 0x400];
    }
    if (a <= 0xC00) {
        return -D_80055830[0xC00 - a];
    }
    return D_80055830[a - 0xC00];
}

INCLUDE_ASM("main/nonmatchings/psyq/libgte_geo_01", func_8002A948);

INCLUDE_ASM("main/nonmatchings/psyq/libgte_geo_01", InitGeom);

OBJECT_END();
