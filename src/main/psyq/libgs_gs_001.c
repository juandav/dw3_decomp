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
extern DRAWENV D_800809F0;
extern TILE D_800809B8[2];
extern short D_800809D8[2];
extern short D_800809DC[2];
extern volatile long D_80080A78;
extern volatile long D_80080A7C;
extern u_short D_80080A76;
extern short D_800809E0[2];
extern short D_800809E4[2];
extern _GsPOSITION D_800809E8;
extern RECT D_80080A68;
extern long D_80080A70;
extern MATRIX D_80080A90;
extern MATRIX D_80080AB0;
extern MATRIX D_80080B10;
extern MATRIX D_80080B30;

void GsInitGraph(u_short x, u_short y, u_short intmode, u_short dith, u_short vrammode) {
    func_80028E6C(x, y, intmode, dith, vrammode);
    gte_init();
    D_80080A74 = 0;
    func_80028FF0(x, y);
    GsSetDrawBuffClip();
    GsSetDrawBuffOffset();
}

void func_80028E6C(u_short x, u_short y, u_short intmode, u_short dith, u_short vrammode) {
    int mode;

    ResetGraph(((intmode >> 4) & 3) == 3 ? 3 : 0);
    D_800809F0.ofs[0] = D_800809F0.ofs[1] = 0;
    D_800809F0.tw.x = D_800809F0.tw.y = D_800809F0.tw.w = D_800809F0.tw.h = 0;
    D_800809F0.tpage = 0;
    D_800809F0.dtd = dith;
    D_800809F0.dfe = 0;
    D_800809F0.isbg = 0;
    PutDrawEnv(&D_800809F0);
    setRECT(&D_80080A50.disp, 0, 0, x, y);
    setRECT(&D_80080A50.screen, 0, 0, 0, 0);
    if ((mode = GetVideoMode()) == 1) {
        D_80080A50.screen.y = 24;
        D_80080A50.pad0 = mode;
    }
    D_80080A50.isinter = intmode & 1;
    D_80080A76 = intmode & 4;
    D_80080A50.isrgb24 = vrammode;
    PutDispEnv(&D_80080A50);
}

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

void func_80028FF0(u_short w, u_short h) {
    long aspect;

    D_80080A78 = w;
    D_80080A7C = h;
    aspect = (D_80080A7C << 14) / D_80080A78;
    D_80080B10.m[2][2] = D_80080B10.m[1][1] = D_80080B10.m[0][0] = 0x1000;
    D_80080B10.m[0][1] = D_80080B10.m[0][2] = 0;
    D_80080B10.m[1][0] = D_80080B10.m[1][2] = 0;
    D_80080B10.m[2][0] = D_80080B10.m[2][1] = 0;
    D_80080B10.t[0] = D_80080B10.t[1] = D_80080B10.t[2] = 0;
    D_80080B30 = D_80080B10;
    D_80080A90 = D_80080B10;
    D_80080A90.m[0][0] = D_80080A90.m[1][1] = D_80080A90.m[2][2] = 0;
    D_80080AB0 = D_80080A90;
    D_800809E0[0] = 0;
    D_800809E0[1] = 0;
    D_800809E4[0] = 0;
    D_800809E4[1] = 0;
    D_800809E8.offx = D_800809E8.offy = 0;
    D_80080B30.m[1][1] = aspect / 3;
    D_80080A68.x = D_80080A68.y = 0;
    setlen(&D_800809B8[0], 3);
    setcode(&D_800809B8[0], 2);
    setlen(&D_800809B8[1], 3);
    setcode(&D_800809B8[1], 2);
    D_80080A70 = 1;
    D_80080A68.w = *(u_short *)&D_80080A78;
    D_80080A68.h = *(u_short *)&D_80080A7C;
}

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
