#include "shocktst.h"

/* The kernel's file functions (sim: opens the file on the PC) */
long func_80024CB8(char *name, long mode);
long func_80024CC8(long fd, void *buf, long n);
long write(long fd, void *buf, long n);
long func_80024CE8(long fd);
int atoi(u8 *s);
int strcspn(u8 *s, char *reject);

extern char D_80082490[]; /* "パターンじっこう" */
extern char D_80082500[]; /* "しんどうテスト" */
extern char D_80082510[]; /* "×：じっこうていし" */
extern char D_80082524[]; /* "ＳＴＡＲＴ：もどる" */
extern ShockTestRow D_80084160[4];
extern char D_800841C0[3][0x40];
extern char *D_80084280[2];
extern char *D_80084288;

Task *func_80084134(void);
s32 func_80082D8C(ShockTest *task, ShockTestWindows *win);
void func_80083B88(ShockLoader *task);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082538);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082630);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_8008265C);

void func_80082A0C(ShockTest *task, ShockTestWindows *win, s32 pattern);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_800827FC);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082A0C);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082AC4);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082B58);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082D8C);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80082E58);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_800832C4);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_8008354C);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082478);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082490);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_8008363C);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083A78);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083B04);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_800824BC);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083B88);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80083EAC);

INCLUDE_ASM("asm/shocktst/nonmatchings/shocktst", func_80084134);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082500);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082510);

INCLUDE_RODATA("asm/shocktst/nonmatchings/shocktst", D_80082524);
