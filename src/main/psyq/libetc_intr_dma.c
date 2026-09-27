/* DICR is volatile here and the callback table holds function pointers */
#define D_8005B7D0 D_8005B7D0_sdk
#define D_8005B7D4 D_8005B7D4_sdk
#include "psyq.h"
#undef D_8005B7D0
#undef D_8005B7D4

extern volatile u_long *D_8005B7D0;
extern void (*D_8005B7D4[])();
extern volatile u_long *D_8005B7F4;

void *startIntrDMA(void) {
    func_8002F150((long *)D_8005B7D4, 8);
    *D_8005B7D0 = 0;
    InterruptCallback(3, func_8002EF24);
    return func_8002F0A4;
}

void func_8002EF24(void) {
    int i;
    u_long mask;

    while ((mask = (*D_8005B7D0 >> 24) & 0x7F) != 0) {
        for (i = 0; mask != 0 && i < 7; i++, mask >>= 1) {
            if (mask & 1) {
                *D_8005B7D0 &= (1 << (i + 24)) | 0xFFFFFF;
                if (D_8005B7D4[i] != NULL) {
                    D_8005B7D4[i]();
                }
            }
        }
    }
    if ((*D_8005B7D0 & 0xFF000000) == 0x80000000 || (*D_8005B7D0 & 0x8000)) {
        printf("DMA bus error: code=%08x\n", *D_8005B7D0);
        for (i = 0; i < 7; i++) {
            printf("MADR[%d]=%08x\n", i, D_8005B7F4[i * 4]);
        }
    }
}

void (*func_8002F0A4(int index, void (*callback)(void)))(void) {
    void (*prev)(void) = D_8005B7D4[index];

    if (callback != prev) {
        if (callback != NULL) {
            D_8005B7D4[index] = callback;
            *D_8005B7D0 = (*D_8005B7D0 & 0xFFFFFF) | 0x800000 | (1 << (index + 16));
        } else {
            D_8005B7D4[index] = NULL;
            *D_8005B7D0 = ((*D_8005B7D0 & 0xFFFFFF) | 0x800000) & ~(1 << (index + 16));
        }
    }
    return prev;
}

void func_8002F150(long *p, int n) {
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = 0;
        } while (i-- != 0);
    }
}

/* ASPSX padded the string table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
