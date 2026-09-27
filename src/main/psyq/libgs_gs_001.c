#include "psyq.h"
#include <libgs.h>

typedef struct GsA04 {
    /* 0x0 */ u_short unk0;
    /* 0x2 */ u_char dith;
    /* 0x3 */ u_char unk3;
    /* 0x4 */ u_char unk4;
} GsA04;

extern GsA04 D_80080A04;
extern DISPENV D_80080A50;
extern TILE D_800809B8[2];
extern short D_800809D8[2];
extern short D_800809DC[2];
extern long D_80080A78;
extern long D_80080A7C;
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
    D_80080A50.disp.w = x;
    D_80080A50.disp.h = y;
    D_80080A50.isinter = intmode & 1;
    D_80080A76 = intmode & 4;
    D_80080A50.isrgb24 = vrammode;
    func_80028FF0(x, y);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgs_gs_001", func_80028FF0);

void GsSortClear(u_char r, u_char g, u_char b, GsOT *otp) {
    D_800809B8[D_80080A74].r0 = r;
    D_800809B8[D_80080A74].g0 = g;
    D_800809B8[D_80080A74].b0 = b;
    D_800809B8[D_80080A74].x0 = D_800809D8[D_80080A74];
    D_800809B8[D_80080A74].y0 = D_800809DC[D_80080A74];
    D_800809B8[D_80080A74].h = *(u_short *)&D_80080A7C;
    if (D_80080A50.isrgb24) {
        D_800809B8[D_80080A74].w = D_80080A78 * 3 / 2;
    } else {
        D_800809B8[D_80080A74].w = *(u_short *)&D_80080A78;
    }
    AddPrim(otp->tag, &D_800809B8[D_80080A74]);
}

OBJECT_END();
