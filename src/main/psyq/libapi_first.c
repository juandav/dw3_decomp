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

static inline int get_device_func(void) {
    Dcb *dev;
    Dcb *start;
    u_long n;

    n = *(u_long *)0x154 / sizeof(Dcb);
    start = *(Dcb **)0x150;
    for (dev = start; dev < start + n; dev++) {
        if (dev->name != NULL && strcmp(dev->name, D_800820D0) == 0) {
            D_800820C8 = dev->func;
            return 1;
        }
    }
    return 0;
}

struct DIRENTRY *firstfile(char *name, struct DIRENTRY *dir) {
    char *s = name;
    char *d = D_800820D0;
    Dcb *dev;
    Dcb *start;
    u_long n;

    while (*s > ':') {
        *d++ = *s++;
    }
    *d = 0;
    if (!get_device_func()) {
        return NULL;
    }
    n = *(u_long *)0x154 / sizeof(Dcb);
    start = *(Dcb **)0x150;
    for (dev = start; dev < start + n; dev++) {
        if (dev->name != NULL && strcmp(dev->name, D_800820D0) == 0) {
            dev->func = func_8003D404;
            break;
        }
    }
    return func_8003D508(name, dir);
}

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
