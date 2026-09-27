#include "psyq.h"

extern volatile u_long *D_80055800;
extern volatile u_long *D_80055804;
extern volatile u_long *D_80055808;
extern volatile u_long *D_80055810;

void _GPU_ResetCallback(void);

u_long *BreakDraw(void) {
    volatile u_long addr;

    if (!(*D_80055808 & 0x01000000)) {
        return 0;
    }
    if (((*D_80055808 & 0x700) >> 8) == 4) {
        *D_80055808 &= ~0x01000000;
        addr = *D_80055808;
        addr = *D_80055800;
        if ((addr & 0xFFFFFF) == 0xFFFFFF) {
            return 0;
        }
        return (u_long *)addr;
    }
    return (u_long *)-1;
}

int IsIdleGPU(int max_count) {
    int count = 0;

    while (!(*D_80055810 & 0x04000000)) {
        if (count++ > max_count) {
            return -1;
        }
    }
    return 0;
}

void ContinueDraw(u_long *insaddr, u_long *contaddr) {
    u_long *p;
    u_long *prev;

    _GPU_ResetCallback();
    if (insaddr != NULL) {
        if (contaddr != NULL) {
            p = prev = insaddr;
            while ((*(u_long *)((*p & 0xFFFFFF) | 0x80000000) & 0xFFFFFF) != 0xFFFFFF) {
                prev = p;
                p = (u_long *)((*p & 0xFFFFFF) | 0x80000000);
            }
            *prev = (*prev & 0xFF000000) | ((u_long)contaddr & 0xFFFFFF);
        }
    } else {
        if (contaddr == NULL) {
            return;
        }
        insaddr = contaddr;
    }
    *D_80055810 = 0x04000002;
    *D_80055800 = (u_long)insaddr;
    *D_80055804 = 0;
    *D_80055808 = 0x01000401;
}

OBJECT_END();
