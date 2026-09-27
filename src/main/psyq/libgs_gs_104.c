#include "psyq.h"
#include <libgte.h>
#include <libgs.h>

extern _GsPOSITION D_800809E8;
extern long D_80080A78;
extern long D_80080A7C;
extern long D_80080A80;
extern long D_80080A84;
extern long D_80080A88;

void GsInit3D(void) {
    D_800809E8.offx = D_80080A78 / 2;
    D_800809E8.offy = D_80080A7C / 2;
    GsSetDrawBuffOffset();
    D_80080A88 = 10;
    D_80080A84 = 0;
    D_80080A80 = 0x3FFF;
}

OBJECT_END();
