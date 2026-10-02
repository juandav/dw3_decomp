/* libapi.h declares _96_remove without arguments, but it takes the callbacks */
#define _96_remove _96_remove_sdk
#include "psyq.h"
#undef _96_remove

/* libetc interrupt environment (intrEnv) */
typedef struct IntrEnv {
    /* 0x00 */ u_short initialized;
    /* 0x02 */ u_short inInterrupt;
    /* 0x04 */ void (*handlers[11])();
    /* 0x30 */ u_short enabledMask;
    /* 0x32 */ u_short savedMask;
    /* 0x34 */ long savedPcr;
    /* 0x38 */ long buf[12];
    /* 0x68 */ long stack[1024];
} IntrEnv;

extern IntrEnv D_8005A6F8;
extern volatile u_short *D_8005B784;
extern volatile long *D_8005B78C;
void func_8002ED18(void);
void func_8002ED28(long *buf);

int ResetCallback(void) {
    return D_8005B780->resetCallback();
}

void *InterruptCallback(int irq, void (*func)()) {
    return D_8005B780->interruptCallback(irq, func);
}

void *DMACallback(int dma, void (*func)()) {
    return D_8005B780->dmaCallback(dma, func);
}

int VSyncCallback(void (*func)()) {
    return (int)D_8005B780->vsyncCallbacks(4, func);
}

void *VSyncCallbacks(int ch, void (*func)()) {
    return D_8005B780->vsyncCallbacks(ch, func);
}

int StopCallback(void) {
    return D_8005B780->stopCallback();
}

int RestartCallback(void) {
    return D_8005B780->restartCallback();
}

int CheckCallback(void) {
    return D_8005A6FA;
}

u_short GetIntrMask(void) {
    return *D_8005B788;
}

u_short SetIntrMask(u_short mask) {
    u_short old = *D_8005B788;

    *D_8005B788 = mask;
    return old;
}

int setjmp(long *buf);
void func_8002E894(void);
void func_8002ECC4(long *p, int n);
void *startIntrVSync(void);
void *startIntrDMA(void);
void _96_remove();

void *func_8002E7BC(void) {
    if (D_8005A6F8.initialized != 0) {
        return NULL;
    }
    *D_8005B784 = *D_8005B788 = 0;
    *D_8005B78C = 0x33333333;
    func_8002ECC4((long *)&D_8005A6F8, sizeof(D_8005A6F8) / sizeof(long));
    if (setjmp(D_8005A6F8.buf)) {
        func_8002E894();
    }
    D_8005A6F8.buf[1] = (long)&D_8005A6F8.stack[1004];
    func_8002ED28(D_8005A6F8.buf);
    D_8005A6F8.initialized = 1;
    D_8005B780->vsyncCallbacks = startIntrVSync();
    D_8005B780->dmaCallback = startIntrDMA();
    _96_remove(D_8005B780);
    ExitCriticalSection();
    return &D_8005A6F8;
}

extern long D_8005B790;
void func_8002ED08(void);

void func_8002E894(void) {
    int i;
    u_short mask;
    short pending;

    if (D_8005A6F8.initialized == 0) {
        printf("unexpected interrupt(%04x)\n", *D_8005B784);
        func_8002ED08();
    }
    D_8005A6F8.inInterrupt = 1;
    while ((mask = D_8005A6F8.enabledMask & *D_8005B784 & *D_8005B788) != 0) {
        for (i = 0; mask != 0 && i < 11; i++, mask >>= 1) {
            if (mask & 1) {
                *D_8005B784 = ~(1 << i);
                if (D_8005A6F8.handlers[i] != NULL) {
                    D_8005A6F8.handlers[i]();
                }
            }
        }
    }
    pending = *D_8005B784 & *D_8005B788;
    if (pending) {
        if (D_8005B790++ > 0x800) {
            printf("intr timeout(%04x:%04x)\n", *D_8005B784, *D_8005B788);
            D_8005B790 = 0;
            *D_8005B784 = 0;
        }
    } else {
        D_8005B790 = 0;
    }
    D_8005A6F8.inInterrupt = 0;
    func_8002ED08();
}

void *func_8002EA64(int irq, void (*func)()) {
    void (*old)() = D_8005A6F8.handlers[irq];
    int mask;

    if (func != old && D_8005A6F8.initialized != 0) {
        mask = *D_8005B788;
        *D_8005B788 = 0;
        if (func != NULL) {
            D_8005A6F8.handlers[irq] = func;
            mask |= 1 << irq;
            D_8005A6F8.enabledMask |= 1 << irq;
        } else {
            D_8005A6F8.handlers[irq] = NULL;
            mask &= ~(1 << irq);
            D_8005A6F8.enabledMask &= ~(1 << irq);
        }
        if (irq == 0) {
            ChangeClearPAD(func == NULL);
            ChangeClearRCnt(3, func == NULL);
        }
        if (irq == 4) {
            ChangeClearRCnt(0, func == NULL);
        }
        if (irq == 5) {
            ChangeClearRCnt(1, func == NULL);
        }
        if (irq == 6) {
            ChangeClearRCnt(2, func == NULL);
        }
        *D_8005B788 = mask;
    }
    return old;
}

void *func_8002EBAC(void) {
    if (D_8005A6F8.initialized == 0) {
        return NULL;
    }
    EnterCriticalSection();
    D_8005A6F8.savedMask = *D_8005B788;
    D_8005A6F8.savedPcr = *D_8005B78C;
    *D_8005B784 = *D_8005B788 = 0;
    *D_8005B78C &= 0x77777777;
    func_8002ED18();
    D_8005A6F8.initialized = 0;
    return &D_8005A6F8;
}

void *func_8002EC4C(void) {
    if (D_8005A6F8.initialized != 0) {
        return NULL;
    }
    func_8002ED28(D_8005A6F8.buf);
    D_8005A6F8.initialized = 1;
    *D_8005B788 = D_8005A6F8.savedMask;
    *D_8005B78C = D_8005A6F8.savedPcr;
    ExitCriticalSection();
    return &D_8005A6F8;
}

void func_8002ECC4(long *p, int n) {
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = 0;
        } while (i-- != 0);
    }
}

/* ASPSX padded the string table of the object as well */
__asm__(".section .rodata\n\t.align 2\n\t.space 4\n");

OBJECT_END();
