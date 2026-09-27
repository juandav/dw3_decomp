#include "psyq.h"


extern volatile u_char *D_8005A270;
extern volatile u_char *D_8005A278;
extern volatile u_char *D_8005A27C;
extern volatile u_long *D_8005A280;
extern volatile u_long *D_8005A284;
extern volatile u_long *D_8005A290;
extern volatile u_long *D_8005A2A0;
extern long D_8005A2B8;
extern long D_80080BE0;
extern short D_80080BE4;
extern long D_80080BE8;
extern long D_80080BEC;
extern long D_80080BF0;
extern long D_80080BF4;
extern long D_80080BF8;
extern long D_80080BFC;
extern long D_80080C00;
extern long D_80080C08;
extern long D_80080C10;
extern long D_80080C18;
extern u_short *D_80080C1C;
extern void (*D_80080C3C)();
extern volatile u_short *D_80080C40;
extern long D_80080C80;
int func_8002DE48(int mode, u_char *result);
void func_8002C590(int ch, u_long *madr, int blocks, int size, u_long chcr, u_char irq, int unused);
void data_ready_callback(void);

void func_8002C564(long *dst, long *src, u_long n, int unused);
void StCdInterrupt(void) {
    volatile short status[4];
    CdlLOC loc;
    u_char result[8];
    long *dst;
    u_long chcr;
    long *src;
    u_int i;

    if (D_80080BFC == 1) {
        return;
    }
    if (D_80080BE8 != 0 && (*D_8005A290 & 0x01000000)) {
        D_80080BEC = 1;
        if (D_80080C10 != 0) {
            D_80080C00++;
        }
        D_8005A2B8 = 1;
        return;
    }
    if (func_8002DE48(1, result) == CdlDiskError) {
        return;
    }
    status[1] = result[0];
    status[2] = result[1];
    if (status[1] & 4) {
        D_8005A2B8 = 3;
        return;
    }
    D_80080C40 = (u_short *)&((StHEADER *)D_80080C20)[D_80080C04];
    if (D_80080C40[0] != 0) {
        if (D_80080C10 != 0) {
            D_80080C00++;
        }
        D_8005A2B8 = 4;
        return;
    }
    *D_8005A270 = 0;
    *D_8005A27C = 0;
    *D_8005A270 = 0;
    *D_8005A27C = 0x80;
    *D_8005A280 = 0x20943;
    *D_8005A284 = 0x1323;
    i = 0;
    if (D_80080C80 == 0) {
        for (; i < 4; i++) {
            ((u_char *)&loc)[i] = *D_8005A278;
        }
        for (i = 0; i < 8; i++) {
            *D_8005A278;
        }
    }
    chcr = 0x11000000;
    if (D_80080C10 != 0) {
        func_8002C564((long *)D_80080C40, (long *)(D_80080C10 + (D_80080C00 << 11)), 8, 0);
    } else {
        func_8002C590(3, (u_long *)D_80080C40, 0, 8, chcr, 0, 0);
    }
    while (*D_8005A2A0 & 0x01000000) {
    }
    ((StHEADER *)D_80080C40)->loc = loc;
    *D_8005A280 = 0x20843;
    *D_8005A284 = 0x1325;
    if (D_80080C18 == 1 && D_80080BF4 != 0) {
        if (D_80080BF4 != D_80080C40[4]) {
            D_80080C40[0] = 0;
            if (D_80080C10 != 0) {
                D_80080C00++;
            }
            return;
        }
        D_80080C18 = 0;
    }
    if (((StHEADER *)D_80080C40)->id != 0x160 || ((((StHEADER *)D_80080C40)->type >> 10) & 0x1F) != D_80080BF8) {
        if (D_80080C10 != 0) {
            D_80080C00 = 0;
        } else {
            D_80080C40[0];
        }
        D_8005A2B8 = 5;
        D_80080C40[0] = 0;
        return;
    }
    if (D_80080BE4 != D_80080C40[2] || (D_80080BE0 != 0 && D_80080BE0 != D_80080C40[4])) {
        D_80080BE0 = 0;
        D_80080BE4 = 0;
        init_ring_status(D_80080C08, D_80080C04 - D_80080C08);
        D_80080C04 = D_80080C08;
        D_80080C40[0] = 0;
        if (D_80080C10 != 0) {
            D_80080C00++;
        }
        D_8005A2B8 = 6;
        return;
    }
    if (D_80080C40[2] == 0) {
        D_80080BE4 = 0;
        D_80080BE0 = D_80080C40[4];
        if (D_80080C14 != 0 && D_80080BE0 >= D_80080C14) {
            D_80080BE0 = 0;
            D_80080BE4 = 0;
            init_ring_status(D_80080C08, D_80080C04 - D_80080C08);
            D_80080C04 = D_80080C08;
            D_80080C40[0] = 0;
            D_80080C18 = 1;
            if (D_80080C3C != NULL) {
                D_80080C3C();
            }
            if (D_80080C10 != 0) {
                D_80080C00++;
            }
            D_8005A2B8 = 7;
            return;
        }
        if ((u_long)(D_80080C24 - D_80080C04 - 1) < D_80080C40[3]) {
            if (D_80080C14 == 0) {
                D_80080C40[0] = 1;
                D_80080C18 = 1;
                if (D_80080C3C != NULL) {
                    D_80080C3C();
                }
                if (D_80080C10 != 0) {
                    D_80080C00++;
                }
                D_8005A2B8 = 8;
                return;
            }
            if ((short)((StHEADER *)D_80080C20)->id != 0) {
                D_80080C40[0] = 0;
                if (D_80080C10 != 0) {
                    D_80080C00++;
                }
                D_8005A2B8 = 9;
                return;
            }
            D_80080C40[0] = 1;
            dst = (long *)D_80080C20;
            src = (long *)D_80080C40;
            D_80080C04 = 0;
            for (i = 0; i < 8; i++) {
                *dst++ = *src++;
            }
            D_80080C40 = (u_short *)D_80080C20;
        }
        D_80080C08 = D_80080C04;
    }
    D_8005A2B8 = 10;
    D_80080BE4++;
    D_80080C1C = (u_short *)(&((StHEADER *)D_80080C20)[D_80080C24] + D_80080C04 * 0x3F);
    if (D_80080BE8 != 0) {
        chcr = 0x11000000;
        *D_8005A280 = 0x20943;
        *D_8005A284 = 0x1323;
    } else {
        *D_8005A280 = 0x21020843;
        chcr = 0x11400100;
    }
    if (D_80080C40[3] - 1 == D_80080C40[2]) {
        D_80080BFC = 1;
        if (D_80080C10 != 0) {
            func_8002C564((long *)D_80080C1C, (long *)(D_80080C10 + (D_80080C00 << 11) + 0x20), 0x1F8, 1);
            D_80080C00++;
        } else {
            func_8002C590(3, (u_long *)D_80080C1C, 0, 0x1F8, chcr, 1, 0);
        }
        D_80080BE4 = 0;
        D_80080BE0 = 0;
        D_80080BF8 = D_80080BF0;
    } else {
        if (D_80080C10 != 0) {
            func_8002C564((long *)D_80080C1C, (long *)(D_80080C10 + (D_80080C00 << 11) + 0x20), 0x1F8, 0);
            D_80080C00++;
        } else {
            func_8002C590(3, (u_long *)D_80080C1C, 0, 0x1F8, chcr, 0, 0);
        }
    }
    *D_8005A284 = 0x1325;
    D_80080C40[0] = 3;
    D_80080C04 += 1;
    if (D_80080C10 != 0 && D_80080BFC != 0) {
        data_ready_callback();
    }
}

void func_8002C564(long *dst, long *src, u_long n, int unused) {
    u_long i = 0;

    if (n != 0) {
        do {
            *dst++ = *src++;
            i++;
        } while (i < n);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_c_011", func_8002C590);

OBJECT_END();
