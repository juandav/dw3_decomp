/* _spu_tsa is read as a plain variable in this object */
#define D_8005BA40 D_8005BA40_volatile
#define _spu_t _spu_t_sdk
#include "psyq.h"
#undef D_8005BA40
#undef _spu_t
extern u_short D_8005BA40;

extern u_long *D_8005BA38;

extern long D_8005BA48;
extern long D_8005BA4C;
extern long D_8005BA54;
extern long D_8005BA58;
extern volatile long D_8005BA64;
extern u_char D_8005BA68[];
extern volatile short _spu_RQ[10];
void _spu_Fw1ts(void);
void func_800383F8(u_char *addr, u_long size);

long _spu_init(long mode) {
    int i;
    u_int t;
    volatile short *p;

    *D_8005BA38 |= 0xB0000;
    D_8005BA44 = 0;
    D_8005BA48 = 0;
    D_8005BA40 = 0;
    D_8005BA28[0xC0] = 0;
    D_8005BA28[0xC1] = 0;
    D_8005BA28[0xD5] = 0;
    _spu_Fw1ts();
    D_8005BA28[0xC0] = 0;
    D_8005BA28[0xC1] = 0;
    t = 0;
    while (D_8005BA28[0xD7] & 0x7FF) {
        if (++t > 0xF00) {
            printf("SPU:T/O [%s]\n", "wait (reset)");
            break;
        }
    }
    D_8005BA4C = 2;
    D_8005BA50 = 3;
    D_8005BA54 = 8;
    D_8005BA58 = 7;
    D_8005BA28[0xD6] = 4;
    D_8005BA28[0xC2] = 0;
    D_8005BA28[0xC3] = 0;
    D_8005BA28[0xC6] = 0xFFFF;
    D_8005BA28[0xC7] = 0xFFFF;
    D_8005BA28[0xCC] = 0;
    D_8005BA28[0xCD] = 0;
    for (i = 0, p = _spu_RQ; i < 10; i++) {
        *p++ = 0;
    }
    if (mode == 0) {
        D_8005BA40 = 0x200;
        D_8005BA28[0xC8] = 0;
        D_8005BA28[0xC9] = 0;
        D_8005BA28[0xCA] = 0;
        D_8005BA28[0xCB] = 0;
        D_8005BA28[0xD8] = 0;
        D_8005BA28[0xD9] = 0;
        D_8005BA28[0xDA] = 0;
        D_8005BA28[0xDB] = 0;
        func_800383F8(D_8005BA68, 0x10);
        for (i = 0; i < 24; i++) {
            D_8005BA28[i * 8 + 0] = 0;
            D_8005BA28[i * 8 + 1] = 0;
            D_8005BA28[i * 8 + 2] = 0x3FFF;
            D_8005BA28[i * 8 + 3] = 0x200;
            D_8005BA28[i * 8 + 4] = 0;
            D_8005BA28[i * 8 + 5] = 0;
        }
        D_8005BA28[0xC4] = 0xFFFF;
        D_8005BA28[0xC5] = 0xFF;
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
        D_8005BA28[0xC6] = 0xFFFF;
        D_8005BA28[0xC7] = 0xFF;
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
    }
    D_8005BA5C = 1;
    D_8005BA28[0xD5] = 0xC000;
    D_8005BA60 = 0;
    D_8005BA64 = 0;
    return 0;
}

void func_800383F8(u_char *addr, u_long size) {
    u_short stat;
    u_short cnt;
    long n;
    long i;
    u_long t;
    u_short *p = (u_short *)addr;

    stat = D_8005BA28[0xD7] & 0x7FF;
    D_8005BA28[0xD3] = D_8005BA40;
    _spu_Fw1ts();
    while (size != 0) {
        n = size > 64 ? 64 : size;
        for (i = 0; i < n; i += 2) {
            D_8005BA28[0xD4] = *p++;
        }
        cnt = D_8005BA28[0xD5];
        D_8005BA28[0xD5] = (cnt & ~0x30) | 0x10;
        _spu_Fw1ts();
        t = 0;
        while (D_8005BA28[0xD7] & 0x400) {
            if (++t > 0xF00) {
                printf("SPU:T/O [%s]\n", "wait (wrdy H -> L)");
                break;
            }
        }
        _spu_Fw1ts();
        _spu_Fw1ts();
        size -= n;
    }
    cnt = D_8005BA28[0xD5];
    D_8005BA28[0xD5] = cnt & ~0x30;
    t = 0;
    while ((D_8005BA28[0xD7] & 0x7FF) != stat) {
        if (++t > 0xF00) {
            printf("SPU:T/O [%s]\n", "wait (dmaf clear/W)");
            break;
        }
    }
}

extern long D_8005BA78;

void _spu_FiDMA(void) {
    u_int i;
    volatile u_short *regs;

    if (D_8005BA78 == 0) {
        _spu_Fw1ts();
    }
    regs = D_8005BA28;
    regs[0xD5] &= ~0x30;
    i = 0;
    while (regs[0xD5] & 0x30) {
        if (++i > 0xF00) {
            break;
        }
    }
    if (D_8005BA60 != 0) {
        ((void (*)(void))D_8005BA60)();
    } else {
        func_8002B6D8(0xF0000009, 0x20);
    }
}

extern volatile u_long *D_8005BA2C;
extern volatile u_long *D_8005BA30;
extern volatile u_long *D_8005BA34;
void func_80038C28(void);

void _spu_Fr_(u_char *addr, u_short tsa, u_long size) {
    D_8005BA28[0xD3] = tsa;
    _spu_Fw1ts();
    D_8005BA28[0xD5] |= 0x30;
    _spu_Fw1ts();
    func_80038C28();
    *D_8005BA2C = (u_long)addr;
    *D_8005BA30 = (size << 16) | 0x10;
    D_8005BA78 = 1;
    *D_8005BA34 = 0x1000200;
}

/* PsyQ's stdarg.h */
typedef char *va_list;
#define __va_rounded_size(TYPE) (((sizeof(TYPE) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#define va_start(AP, LASTARG) (AP = ((char *)&(LASTARG) + __va_rounded_size(LASTARG)))
#define va_arg(AP, TYPE) (AP += __va_rounded_size(TYPE), *((TYPE *)(AP - __va_rounded_size(TYPE))))

extern long D_8005BA7C;
extern long D_8005BA80;
void func_80038C00(void);

long _spu_t(long mode, ...) {
    va_list args;
    u_int i;
    u_short ck;
    u_long count;
    u_long dma;

    va_start(args, mode);
    switch (mode) {
    case 2:
        count = va_arg(args, u_long);
        D_8005BA40 = count >> D_8005BA50;
        D_8005BA28[0xD3] = D_8005BA40;
        break;
    case 1:
        D_8005BA78 = 0;
        i = 0;
        while (D_8005BA28[0xD3] != D_8005BA40) {
            if (++i > 0xF00) {
                return -2;
            }
        }
        D_8005BA28[0xD5] = (D_8005BA28[0xD5] & ~0x30) | 0x20;
        break;
    case 0:
        D_8005BA78 = 1;
        i = 0;
        while (D_8005BA28[0xD3] != D_8005BA40) {
            if (++i > 0xF00) {
                return -2;
            }
        }
        D_8005BA28[0xD5] = (D_8005BA28[0xD5] & ~0x30) | 0x30;
        break;
    case 3:
        if (D_8005BA78 == 1) {
            ck = 0x30;
        } else {
            ck = 0x20;
        }
        i = 0;
        while ((D_8005BA28[0xD5] & 0x30) != ck) {
            if (++i > 0xF00) {
                return -2;
            }
        }
        if (D_8005BA78 == 1) {
            func_80038C28();
        } else {
            func_80038C00();
        }
        count = va_arg(args, u_long);
        D_8005BA7C = count;
        count = va_arg(args, u_long);
        D_8005BA80 = count / 64;
        D_8005BA80 += (count % 64) ? 1 : 0;
        *D_8005BA2C = D_8005BA7C;
        *D_8005BA30 = (D_8005BA80 << 16) | 0x10;
        if (D_8005BA78 == 1) {
            dma = 0x1000200;
        } else {
            dma = 0x1000201;
        }
        *D_8005BA34 = dma;
        break;
    }
    return 0;
}

u_long _spu_Fw(u_char *addr, u_long size) {
    if (D_8005BA44 == 0) {
        _spu_t(2, D_8005BA40 << D_8005BA50);
        _spu_t(1);
        _spu_t(3, addr, size);
    } else {
        func_800383F8(addr, size);
    }
    return size;
}

u_long _spu_Fr(char *addr, u_long size) {
    _spu_t(2, D_8005BA40 << D_8005BA50);
    _spu_t(0);
    _spu_t(3, addr, size);
    return size;
}

void _spu_FsetRXX(int reg, u_long value, int mode) {
    if (mode == 0) {
        D_8005BA28[reg] = value;
    } else {
        D_8005BA28[reg] = value >> D_8005BA50;
    }
}

__asm__(".section .rodata\n\t.align 4\n");
OBJECT_END();
