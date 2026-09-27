#include "psyq.h"

/* BIOS device control block; the table is at 0x150, its size in bytes at 0x154 */
typedef struct {
    char *name;
    long unk4[12];
    int (*func)();
    long unk38[6];
} Dcb;

extern int (*D_800820C8)();
extern char D_800820D0[];
int strcmp(const char *, const char *);
struct DIRENTRY *func_8003D508(char *name, struct DIRENTRY *dir);
int func_8003D404(int *fcb, int a1, int a2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_first", firstfile);

int func_8003D404(int *fcb, int a1, int a2) {
    Dcb *d;
    Dcb *start;
    u_long n;
    int (*func)();

    if (*fcb == 0) {
        *fcb = 1;
    }
    n = *(u_long *)0x154 / sizeof(Dcb);
    start = *(Dcb **)0x150;
    func = D_800820C8;
    for (d = start; d < start + n; d++) {
        if (d->name != NULL && strcmp(d->name, D_800820D0) == 0) {
            d->func = func;
            break;
        }
    }
    return D_800820C8(fcb, a1, a2);
}

OBJECT_END();
