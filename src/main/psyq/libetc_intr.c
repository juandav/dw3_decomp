#include "psyq.h"

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002E7BC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002E894);

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

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", func_8002ECE8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_intr", _96_remove);

OBJECT_END();
