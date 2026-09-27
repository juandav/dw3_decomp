#include "stcrdabm.h"

extern s32 D_80085168[6];
extern CardAlbumFuncs D_80085180;

void initCardDrawer(CardDrawer *obj);
void func_800825A8(CardAlbumFader *fader);
void func_8008290C(CardAlbumGrid *grid, s32 previous);
s32 func_80082ECC(CardAlbumGrid *grid);
void func_80083820(CardAlbum *album, CardAlbumWindows *win, s32 show);
void func_80083C4C(CardAlbum *album);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082520);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800825A8);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800826EC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800827A0);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800827E4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800828AC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800828E4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_8008290C);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082D54);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082ECC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082F18);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80082FE0);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083210);

Task *func_80084DB8(void);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083270);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083368);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083394);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800835AC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083820);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80083C4C);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084314);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084384);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084C8C);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084DB8);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084DF4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084ED4);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80084FBC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_80085050);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800850BC);

INCLUDE_ASM("asm/stcrdabm/nonmatchings/stcrdabm", func_800850FC);
