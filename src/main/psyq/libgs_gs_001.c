#include "psyq.h"

typedef struct GsA04 {
    /* 0x0 */ u_short unk0;
    /* 0x2 */ u_char dith;
    /* 0x3 */ u_char unk3;
    /* 0x4 */ u_char unk4;
} GsA04;

typedef struct GsA54 {
    /* 0x0 */ u_short x;
    /* 0x2 */ u_short y;
    /* 0x4 */ u8 unk4[8];
    /* 0xC */ u_char intmode;
    /* 0xD */ u_char vrammode;
} GsA54;

extern GsA04 D_80080A04;
extern GsA54 D_80080A54;
extern u_short D_80080A76;

void GsInitGraph(u_short x, u_short y, u_short intmode, u_short dith, u_short vrammode) {
    func_80028E6C(x, y, intmode, dith, vrammode);
    gte_init();
    D_80080A74 = 0;
    func_80028FF0(x, y);
    GsSetDrawBuffClip();
    GsSetDrawBuffOffset();
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", func_80028E6C);

void GsInitGraph2(u_short x, u_short y, u_short intmode, u_short dith, u_short vrammode) {
    D_80080A04.unk0 = 0;
    D_80080A04.dith = dith;
    D_80080A04.unk3 = 0;
    D_80080A04.unk4 = 0;
    D_80080A54.x = x;
    D_80080A54.y = y;
    D_80080A54.intmode = intmode & 1;
    D_80080A76 = intmode & 4;
    D_80080A54.vrammode = vrammode;
    func_80028FF0(x, y);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", func_80028FF0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", GsSortClear);

OBJECT_END();
