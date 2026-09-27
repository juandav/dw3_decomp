#include "psyq.h"

typedef struct GsPosition {
    /* 0x0 */ short offx;
    /* 0x2 */ short offy;
} GsPosition;

extern short D_80080A76;
extern GsPosition D_800809E8;
extern short D_800809D8[2];
extern short D_800809DC[2];
extern DRAWENV D_800809F0;

void GsSetDrawBuffOffset(void) {
    if (D_80080A76 != 0) {
        D_800809F0.ofs[0] = D_800809E8.offx + D_800809D8[D_80080A74];
        D_80080A66 = 0;
        D_80080A64 = 0;
        D_800809F0.ofs[1] = D_800809E8.offy + D_800809DC[D_80080A74];
        PutDrawEnv(&D_800809F0);
    } else {
        int x, y;

        x = D_800809E8.offx + D_800809D8[D_80080A74 == 0];
        y = D_800809E8.offy + D_800809DC[D_80080A74 == 0];
        SetGeomOffset(x, y);
        D_80080A64 = x;
        D_80080A66 = y;
    }
}

OBJECT_END();
