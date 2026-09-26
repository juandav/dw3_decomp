#include "psyq.h"

void GsInitGraph(u_short x, u_short y, u_short intmode, u_short dith, u_short vrammode) {
    func_80028E6C(x, y, intmode, dith, vrammode);
    gte_init();
    D_80080A74 = 0;
    func_80028FF0(x, y);
    GsSetDrawBuffClip();
    GsSetDrawBuffOffset();
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", func_80028E6C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", GsInitGraph2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", func_80028FF0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", GsSortClear);

OBJECT_END();
